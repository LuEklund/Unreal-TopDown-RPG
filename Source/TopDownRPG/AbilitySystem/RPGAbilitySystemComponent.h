

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RPGAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer & /*AssetTags*/)

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void	AbilityActorInfoSet();
	FEffectAssetTags EffectAssetTags;

	void	AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> &StartupAbilities);

protected:
	void	EffectApplied(UAbilitySystemComponent *AbilitySystemComponent, const FGameplayEffectSpec & EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
