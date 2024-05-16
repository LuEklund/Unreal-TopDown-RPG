

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RPGAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer & /*AssetTags*/)
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FAbilityStatusChanged, const FGameplayTag&, const FGameplayTag&);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void	AbilityActorInfoSet();
	FEffectAssetTags		EffectAssetTags;
	FAbilitiesGiven			AbilitiesGivenDelegate;
	FAbilityStatusChanged	AbilityStatusChanged;

	void	AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> &StartupAbilities);
	void	AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>> &StartupPassiveAbilities);
	bool	bStartupAbilitiesGive = false;

	void	AbilityInputTagHeld(const FGameplayTag &InputTag);
	void	AbilityInputTagReleased(const FGameplayTag &InputTag);
	void	ForEachAbility(const FForEachAbility &Delegate);

	static FGameplayTag		GetAbilityTagFromSpec(const FGameplayAbilitySpec &AbilitySpec);
	static FGameplayTag		GetInputTagFromSpec(const FGameplayAbilitySpec &AbilitySpec);
	static FGameplayTag		GetStatusFromSpec(const FGameplayAbilitySpec &AbilitySpec);
	FGameplayAbilitySpec	*GetSpecFromAbilityTag(const FGameplayTag &AbilityTag);

	void	UpgardeAttribute(const FGameplayTag &AttributeTag);
	
	UFUNCTION(Client, Reliable)
	void	ServerUpgradeAttribute(const FGameplayTag &Attribute);

	// UFUNCTION()
	void	UpdateAbilityStatuses(int32 Level);

protected:
	virtual void OnRep_ActivateAbilities() override;
	
	UFUNCTION(Client, Reliable)
	void	ClientEffectApplied(UAbilitySystemComponent *AbilitySystemComponent, const FGameplayEffectSpec & EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	UFUNCTION(Client, Reliable)
	void	ClientUpdateAbilityStatus(const FGameplayTag &AbilityTag, const FGameplayTag &StatusTag);
};
