

#pragma once

#include "CoreMinimal.h"
#include "RPGGameplayAbility.h"
#include "RPGProjectileSpell.generated.h"

class ARPGProjectile;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGProjectileSpell : public URPGGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category="Projectile")
	void	SpawnProjectile();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ARPGProjectile>	ProjectileClass;
};
