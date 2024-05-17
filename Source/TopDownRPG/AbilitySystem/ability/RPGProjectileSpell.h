

#pragma once

#include "CoreMinimal.h"
#include "RPGDamageGameplayAbility.h"
#include "RPGProjectileSpell.generated.h"

class ARPGProjectile;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGProjectileSpell : public URPGDamageGameplayAbility
{
	GENERATED_BODY()


protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category="Projectile")
	void	SpawnProjectile(const FVector &ProjectileTargetLocation, const FGameplayTag &SocketTag, bool bOverridePitch = false, float PitchOverride = 0.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ARPGProjectile>	ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	int32	NumProjectiles = 5;

};
