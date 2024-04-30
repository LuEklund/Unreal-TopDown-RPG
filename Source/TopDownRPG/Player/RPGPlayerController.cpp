


#include "RPGPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Components/SplineComponent.h"
#include "TopDownRPG/RPGGameplayTags.h"
#include "TopDownRPG/AbilitySystem/RPGAbilitySystemComponent.h"
#include "TopDownRPG/Input/RPGInputComponent.h"
#include "TopDownRPG/Interraction/EnemyInterface.h"


URPGAbilitySystemComponent* ARPGPlayerController::GetASC()
{
	if (RPGAbilitySystemComponent == nullptr)
	{
		RPGAbilitySystemComponent = Cast<URPGAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return RPGAbilitySystemComponent;
}



ARPGPlayerController::ARPGPlayerController()
{
	//Multiplayer
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void ARPGPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();

}

void ARPGPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn *ControlledPawn = GetPawn())
	{
		const FVector	LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector	Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}

void ARPGPlayerController::CursorTrace()
{
	FHitResult	CurserHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CurserHit);
	if (!CurserHit.bBlockingHit) return;
	
	LastActor = CurrentActor;
	CurrentActor = Cast<IEnemyInterface>(CurserHit.GetActor());

	/**
	 * Line trace from cursor. There are several scenarios:
	 *  A. LastActor is null && CurrentActor is null
	 *		- Do nothing
	 *	B. LastActor is null && CurrentActor is valid
	 *		- Highlight CurrentActor
	 *	C. LastActor is valid && CurrentActor is null
	 *		- UnHighlight LastActor
	 *	D. Both actors are valid, but LastActor != CurrentActor
	 *		- UnHighlight LastActor, and Highlight CurrentActor
	 *	E. Both actors are valid, and are the same actor
	 *		- Do nothing
	 */

	if (LastActor == nullptr)
	{
		if (CurrentActor != nullptr)
		{
			// Case B
			CurrentActor->HighLightActor();
		}
		else
		{
			// Case A - both are null, do nothing
		}
	}
	else // LastActor is valid
	{
		if (CurrentActor == nullptr)
		{
			// Case C
			LastActor->UnHighLightActor();
		}
		else // both actors are valid
		{
			if (LastActor != CurrentActor)
			{
				// Case D
				LastActor->UnHighLightActor();
				CurrentActor->HighLightActor();
			}
			else
			{
				// Case E - do nothing
			}
		}
	}
}

void ARPGPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FRPGGameplayTags::Get().Input_Mouse_RMB))
	{
		bTargeting = CurrentActor != nullptr;
		bAutoRunning = false;
	}

}

void ARPGPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FRPGGameplayTags::Get().Input_Mouse_RMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return ;
	}
	if (bTargeting)
    {
    	if (GetASC())
    	{
    		GetASC()->AbilityInputTagReleased(InputTag);
    	}
    }
	else
	{
		APawn *ControlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshHold && ControlledPawn)
		{
			if (UNavigationPath *NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector &PointLoc : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLoc, ESplineCoordinateSpace::World);
					DrawDebugSphere(GetWorld(), PointLoc, 8.f, 8, FColor::Green, false, 5.f);
				}
				CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
				bAutoRunning = true;
			}
		}
		FollowTime = 0;
		bTargeting = false;
	}
}

void ARPGPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FRPGGameplayTags::Get().Input_Mouse_RMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return ;
	}
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_Visibility, false, Hit))
		{
			CachedDestination = Hit.ImpactPoint;
		}
		if (APawn *ControllerPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControllerPawn->GetActorLocation()).GetSafeNormal();
			ControllerPawn->AddMovementInput(WorldDirection);
		}
	}
}

void ARPGPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	check(RPGContext);
	
	UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(RPGContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ARPGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	URPGInputComponent *RPGInputComponent = CastChecked<URPGInputComponent>(InputComponent);
	RPGInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARPGPlayerController::Move);
	RPGInputComponent->BindAbilityActions(
		InputConfig,
		this,
		&ARPGPlayerController::AbilityInputTagPressed,
		&ARPGPlayerController::AbilityInputTagReleased,
		&ARPGPlayerController::AbilityInputTagHeld);
	
}


void ARPGPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotator = GetControlRotation();
	const FRotator YawRotation(0.f, Rotator.Yaw, 0.f);

	const FVector	ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector	RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn *ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	
}

