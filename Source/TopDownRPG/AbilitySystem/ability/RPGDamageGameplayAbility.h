

#pragma once

#include "CoreMinimal.h"
#include "RPGGameplayAbility.h"
#include "RPGDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGDamageGameplayAbility : public URPGGameplayAbility
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
	
};
