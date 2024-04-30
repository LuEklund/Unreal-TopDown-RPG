


#include "RPGProjectileSpell.h"

#include "TopDownRPG/Actor/RPGProjectile.h"
#include "TopDownRPG/Interraction/CombatInterface.h"


void URPGProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

}

void URPGProjectileSpell::SpawnProjectile()
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (bIsServer == false)	return;

	if (ICombatInterface *CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

		//TODO: Set the Projectile Rotation
		
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		// GetAvatarActorFromActorInfo()->GetActorForwardVector();

		ARPGProjectile *Projectile = GetWorld()->SpawnActorDeferred<ARPGProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		//TODO: Give the projectile a Gameplay Effect Spec for causing Damage.
		
		Projectile->FinishSpawning(SpawnTransform);
	}
}
