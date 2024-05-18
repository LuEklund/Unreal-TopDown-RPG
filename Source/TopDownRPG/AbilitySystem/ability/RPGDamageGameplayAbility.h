

#pragma once

#include "CoreMinimal.h"
#include "RPGGameplayAbility.h"
#include "TopDownRPG/Interraction/CombatInterface.h"
#include "RPGDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGDamageGameplayAbility : public URPGGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void	CauseDamage(AActor *TargetActor);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FGameplayTag	DamageType;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FScalableFloat	Damage;

	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage> &TaggedMontages) const;
};
