


#include "SpellMenuWidgetController.h"

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
