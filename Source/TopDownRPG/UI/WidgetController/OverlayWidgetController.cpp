


#include "OverlayWidgetController.h"

#include "TopDownRPG/RPGGameplayTags.h"
#include "TopDownRPG/AbilitySystem/RPGAbilitySystemComponent.h"
#include "TopDownRPG/AbilitySystem/RPGAttributeSet.h"
#include "TopDownRPG/AbilitySystem/Data/AbilityInfo.h"
#include "TopDownRPG/AbilitySystem/Data/LevelUpInfo.h"
#include "TopDownRPG/Player/RPGPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChanged.Broadcast(GetRPG_AS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetRPG_AS()->GetMaxHealth());
	OnManaChanged.Broadcast(GetRPG_AS()->GetMana());
	OnMaxManaChanged.Broadcast(GetRPG_AS()->GetMaxMana());

}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	GetRPG_PS()->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	GetRPG_PS()->OnLevelChangedDelegate.AddLambda(
		[this](int32 NewLevel, bool bLevelUp)
		{
				OnPlayerLevelChangedDelegate.Broadcast(NewLevel, bLevelUp);
		});


	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GetRPG_AS()->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData &Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	GetRPG_AS()->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData &Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	GetRPG_AS()->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData &Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	GetRPG_AS()->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData &Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
		);

	GetRPG_ASC()->AbilityEquipped.AddUObject(this, &UOverlayWidgetController::OnAbilityEquipped);
	if (GetRPG_ASC()->bStartupAbilitiesGive)
	{
		BroadcastAbilityInfo();
	}
	else
	{
		GetRPG_ASC()->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BroadcastAbilityInfo);
	}

	GetRPG_ASC()->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer &AssetTags)
		{
			for (const FGameplayTag &Tag : AssetTags)
			{
				//"Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					if (const FUIWidgetRow *Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag))
					{
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		}
	);
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP)
{
	const ULevelUpInfo	*LevelUpInfo = GetRPG_PS()->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("%s: Unable to find LevelUpInfo. Please fill out RPGPlayerState Blueprint"), *__FUNCTION__);

	const int32 Level = LevelUpInfo->FindLevelForXP(NewXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		const int32	PreviousLevelUpRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;
		
		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelUpRequirement;
		const int32 XPForThisLevel = NewXP - PreviousLevelUpRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);
		OnXPPercentChangeDelegate.Broadcast(XPBarPercent);
	}
}

void UOverlayWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,
	const FGameplayTag& Slot, const FGameplayTag& PreviousSlot) const
{
	const FRPGGameplayTags &GameplayTags = FRPGGameplayTags::Get();
	
	FRPGAbilityInfo LastSlotInfo;
	LastSlotInfo.StatusTag = GameplayTags.Abilities_Status_Unlocked;
	LastSlotInfo.InputTag = PreviousSlot;
	LastSlotInfo.AbilityTag = GameplayTags.Abilities_None;

	AbilityInfoDelegate.Broadcast(LastSlotInfo);

	FRPGAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	Info.StatusTag = Status;
	Info.InputTag = Slot;
	AbilityInfoDelegate.Broadcast(Info);
}

