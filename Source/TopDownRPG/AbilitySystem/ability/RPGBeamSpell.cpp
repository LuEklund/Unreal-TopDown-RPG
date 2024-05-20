


#include "RPGBeamSpell.h"

#include "GameFramework/Character.h"

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
