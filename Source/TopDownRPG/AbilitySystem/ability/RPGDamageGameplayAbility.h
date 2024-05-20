

#pragma once

#include "CoreMinimal.h"
#include "RPGGameplayAbility.h"
#include "TopDownRPG/RPGAbilityTypes.h"
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

	UFUNCTION(BlueprintPure)
	FDamageEffectParams	MakeDefaultEffectParamsFromClassDefaults(AActor *TargetActor = nullptr) const;
	
	UFUNCTION(BlueprintPure)
	float	GetDamageAtLevel() const;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FGameplayTag	DamageType;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FScalableFloat	Damage;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float			DebuffChance = 20.f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float			DebuffDamage = 5.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Damage")	
	float			DebuffFrquency = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float			DebuffDuration = 5.f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float			DeathImpulseMagnitude = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float			KnockbackForceMagnitude = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float			KnockbackChance = 0.f;
	
	UFUNCTION(BlueprintPure)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage> &TaggedMontages) const;
};
