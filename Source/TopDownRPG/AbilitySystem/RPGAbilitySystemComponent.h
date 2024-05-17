

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "RPGAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer & /*AssetTags*/)
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FAbilityStatusChanged, const FGameplayTag&, const FGameplayTag&, int32);
DECLARE_MULTICAST_DELEGATE_FourParams(FAbilityEquipped, const FGameplayTag&, const FGameplayTag&, const FGameplayTag&, const FGameplayTag&);

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
	FAbilityEquipped		AbilityEquipped;

	void	AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> &StartupAbilities);
	void	AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>> &StartupPassiveAbilities);
	bool	bStartupAbilitiesGive = false;

	void	AbilityInputTagHeld(const FGameplayTag &InputTag);
	void	AbilityInputTagReleased(const FGameplayTag &InputTag);
	void	ForEachAbility(const FForEachAbility &Delegate);

	static FGameplayTag		GetAbilityTagFromSpec(const FGameplayAbilitySpec &AbilitySpec);
	static FGameplayTag		GetInputTagFromSpec(const FGameplayAbilitySpec &AbilitySpec);
	static FGameplayTag		GetStatusFromSpec(const FGameplayAbilitySpec &AbilitySpec);
	FGameplayTag			GetStatusFromAbilityTag(const FGameplayTag &AbilityTag);
	FGameplayTag			GetInpuTagFromAbilityTag(const FGameplayTag &AbilityTag);

	
	FGameplayAbilitySpec	*GetSpecFromAbilityTag(const FGameplayTag &AbilityTag);

	void	UpgardeAttribute(const FGameplayTag &AttributeTag);
	
	UFUNCTION(Client, Reliable)
	void	ServerUpgradeAttribute(const FGameplayTag &Attribute);

	void	UpdateAbilityStatuses(int32 Level);

	UFUNCTION(Server, Reliable)
	void	ServerSpendSpellPoint(const FGameplayTag &AbilityTag);
	
	UFUNCTION(Server, Reliable)
	void	ServerEquipAbility(const FGameplayTag &AbilityTag, const FGameplayTag  &Slot);

	bool	GetDescriptionsByAbilityTag(const FGameplayTag &AbilityTag, FString &OutDesc, FString &OutNextLevelDesc);

	void	ClientEquipAbility(const FGameplayTag &AbilityTag, const FGameplayTag &Status, const FGameplayTag &Slot, const FGameplayTag &PreviousSlot);

	void	ClearSlot(FGameplayAbilitySpec *Spec);
	void	ClearAbilitiesOfSlot(const FGameplayTag &Slot);
	bool	AbilityHasSlot(FGameplayAbilitySpec *Spec, const FGameplayTag &Slot);

protected:
	virtual void OnRep_ActivateAbilities() override;
	
	UFUNCTION(Client, Reliable)
	void	ClientEffectApplied(UAbilitySystemComponent *AbilitySystemComponent, const FGameplayEffectSpec & EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);
	UFUNCTION(Client, Reliable)
	void	ClientUpdateAbilityStatus(const FGameplayTag &AbilityTag, const FGameplayTag &StatusTag, int32 AbilityLevel);
};
