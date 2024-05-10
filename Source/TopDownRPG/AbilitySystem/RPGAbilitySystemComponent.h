

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RPGAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer & /*AssetTags*/)
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGiven, URPGAbilitySystemComponent *);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void	AbilityActorInfoSet();
	FEffectAssetTags	EffectAssetTags;
	FAbilitiesGiven		AbilitiesGivenDelegate;

	void	AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> &StartupAbilities);
	bool	bStartupAbilitiesGive = false;

	void	AbilityInputTagHeld(const FGameplayTag &InputTag);
	void	AbilityInputTagReleased(const FGameplayTag &InputTag);
	void	ForEachAbility(const FForEachAbility &Delegate);

	static FGameplayTag	GetAbilityTagFromSpec(const FGameplayAbilitySpec &AbilitySpec);
	static FGameplayTag	GetInputTagFromSpec(const FGameplayAbilitySpec &AbilitySpec);

protected:
	UFUNCTION(Client, Reliable)
	void	ClientEffectApplied(UAbilitySystemComponent *AbilitySystemComponent, const FGameplayEffectSpec & EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
};
