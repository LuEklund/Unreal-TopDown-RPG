


#include "OverlayWidgetController.h"

#include "TopDownRPG/AbilitySystem/RPGAbilitySystemComponent.h"
#include "TopDownRPG/AbilitySystem/RPGAttributeSet.h"
#include "TopDownRPG/AbilitySystem/Data/AbilityInfo.h"
#include "TopDownRPG/AbilitySystem/Data/LevelUpInfo.h"
#include "TopDownRPG/Player/RPGPlayerState.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	
	const URPGAttributeSet *RPGAttributeSet = CastChecked<URPGAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(RPGAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(RPGAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(RPGAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(RPGAttributeSet->GetMaxMana());

}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	ARPGPlayerState *RPGPlayerState = CastChecked<ARPGPlayerState>(PlayerState);
	RPGPlayerState->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);
	RPGPlayerState->OnLevelChangedDelegate.AddLambda(
		[this](int32 NewLevel)
		{
				OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
		});

	const URPGAttributeSet *RPGAttributeSet = CastChecked<URPGAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		RPGAttributeSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData &Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	RPGAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData &Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	RPGAttributeSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData &Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	RPGAttributeSet->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData &Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			}
		);

	URPGAbilitySystemComponent *RPGASC = Cast<URPGAbilitySystemComponent>(AbilitySystemComponent);

	if (RPGASC->bStartupAbilitiesGive)
	{
		OnIntializeStartupAbilities(RPGASC);
	}
	else
	{
		RPGASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnIntializeStartupAbilities);
	}

	RPGASC->EffectAssetTags.AddLambda(
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

void UOverlayWidgetController::OnIntializeStartupAbilities(URPGAbilitySystemComponent *RPGAbilitySystemComponent)
{
	//TODO: Get information about all given abilities, look up their ability info, and broadcast it to widgets.
	if (!RPGAbilitySystemComponent->bStartupAbilitiesGive) return;
	FForEachAbility	BroadcastDelegate;
	BroadcastDelegate.BindLambda(
		[this](const FGameplayAbilitySpec &AbilitySpec)
		{
			//TODO: NEED a way to figure out the ability tag for a given spec.
			FRPGAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(URPGAbilitySystemComponent::GetAbilityTagFromSpec(AbilitySpec));
			Info.InputTag = URPGAbilitySystemComponent::GetInputTagFromSpec(AbilitySpec);
			AbilityInfoDelegate.Broadcast(Info);
		});
	RPGAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
	
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP) const
{
	const ARPGPlayerState *RPGPlayerState = CastChecked<ARPGPlayerState>(PlayerState);
	const ULevelUpInfo	*LevelUpInfo = RPGPlayerState->LevelUpInfo;
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

