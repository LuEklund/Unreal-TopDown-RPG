


#include "RPGBeamSpell.h"

#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

void URPGBeamSpell::StoreMouseDataInfo(const FHitResult& HitResult)
{
	if (HitResult.bBlockingHit)
	{
		MouseHitLocation = HitResult.ImpactPoint;
		MouseHitActor = HitResult.GetActor();
	}
	else
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}

void URPGBeamSpell::StoreOwnerVariables()
{
	if (CurrentActorInfo)
	{
		OwningPlayerController = CurrentActorInfo->PlayerController.Get();
		OwningCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
	}
	
}

void URPGBeamSpell::TraceFirstTarget(const FVector& BeamTargetLocation)
{
	check(OwningCharacter);
	if (OwningCharacter->Implements<UCombatInterface>())
	{
		if (USkeletalMeshComponent *Weapon = ICombatInterface::Execute_GetWeapon(OwningCharacter))
		{
			TArray<AActor*>	ActorsToIgnore;
			ActorsToIgnore.Add(OwningCharacter);
			const FVector SocketLocation = Weapon->GetSocketLocation(FName("TipSocket"));
			FHitResult HitResult;
			UKismetSystemLibrary::SphereTraceSingle(OwningCharacter,
				SocketLocation,
				BeamTargetLocation,
				10.f,
				TraceTypeQuery1,
				false,
				ActorsToIgnore,
				EDrawDebugTrace::None,
				HitResult,
				true);
			if (HitResult.bBlockingHit)
			{
				MouseHitLocation = HitResult.ImpactPoint;
				MouseHitActor = HitResult.GetActor();
			}
		}
	}
}
