


#include "RPGPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
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
}

void ARPGPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CurserTrace();
}

void ARPGPlayerController::CurserTrace()
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

void ARPGPlayerController::AvilityInputTagPressed(FGameplayTag InputTag)
{
	// GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

void ARPGPlayerController::AvilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void ARPGPlayerController::AvilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
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
		&ARPGPlayerController::AvilityInputTagPressed,
		&ARPGPlayerController::AvilityInputTagReleased,
		&ARPGPlayerController::AvilityInputTagHeld);
	
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

