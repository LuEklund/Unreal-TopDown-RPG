


#include "SpellMenuWidgetController.h"

#include "TopDownRPG/RPGGameplayTags.h"
#include "TopDownRPG/AbilitySystem/RPGAbilitySystemComponent.h"
#include "TopDownRPG/AbilitySystem/Data/AbilityInfo.h"
#include "TopDownRPG/Player/RPGPlayerState.h"

void USpellMenuWidgetController::BroadcastInitialValues()
{
	BroadcastAbilityInfo();
	SpellPointsChanged.Broadcast(GetRPG_PS()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallbacksToDependencies()
{
	GetRPG_ASC()->AbilityStatusChanged.AddLambda([this](const FGameplayTag &AbilityTag, const FGameplayTag &StatusTag)
	{
		if (AbilityInfo)
		{
			FRPGAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			Info.StatusTag = StatusTag;
			AbilityInfoDelegate.Broadcast(Info);
		}
	});

	GetRPG_PS()->OnSpellPointsChangedDelegate.AddLambda([this](int32 SpellPoints)
	{
		SpellPointsChanged.Broadcast(SpellPoints);
	});
}

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	const FRPGGameplayTags &GameplayTags = FRPGGameplayTags::Get();
	const int32 SpellPoints = GetRPG_PS()->GetSpellPoints();
	FGameplayTag	AbilityStatus;

	const bool bTagValid = AbilityTag.IsValid();
	const bool bTagNone = AbilityTag.MatchesTag(GameplayTags.Abilities_None);
	const FGameplayAbilitySpec *AbilitySpec = GetRPG_ASC()->GetSpecFromAbilityTag(AbilityTag);
	// const bool bSpecValid =  != nullptr;
	if (!bTagValid || bTagNone || AbilitySpec == nullptr)
	{
		AbilityStatus = GameplayTags.Abilities_Status_Locked;
	}
	else
	{
		AbilityStatus = GetRPG_ASC()->GetStatusFromSpec(*AbilitySpec);
	}
	bool bEnableSpendPoints = false;
	bool bEnableEquip = false;
	ShouldEnableButtons(AbilityStatus, SpellPoints, bEnableSpendPoints, bEnableEquip);
	SpellGlobeSelectedDelegate.Broadcast(bEnableSpendPoints, bEnableEquip);
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatus, int32 SpellPoints,
	bool& bShouldEnableSpellPointsButton, bool &bShouldEnableEquipButton)
{
	const FRPGGameplayTags &GameplayTags = FRPGGameplayTags::Get();

	bShouldEnableSpellPointsButton = false;
	bShouldEnableEquipButton = false;
	if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Equipped))
	{
		bShouldEnableEquipButton = true;
		if (SpellPoints > 0)
		{
			bShouldEnableSpellPointsButton = true;
		}
	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Eligible))
	{
		if (SpellPoints > 0)
		{
			bShouldEnableSpellPointsButton = true;
		}

	}
	else if (AbilityStatus.MatchesTagExact(GameplayTags.Abilities_Status_Unlocked))
	{
		bShouldEnableEquipButton = true;
		if (SpellPoints > 0)
		{
			bShouldEnableSpellPointsButton = true;
		}

	}
}
