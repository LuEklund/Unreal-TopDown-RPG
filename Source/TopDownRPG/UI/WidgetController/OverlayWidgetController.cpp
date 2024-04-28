


#include "OverlayWidgetController.h"

#include "TopDownRPG/AbilitySystem/RPGAbilitySystemComponent.h"
#include "TopDownRPG/AbilitySystem/RPGAttributeSet.h"

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
	const URPGAttributeSet *RPGAttributeSet = CastChecked<URPGAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		RPGAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		RPGAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		RPGAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		RPGAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);

	Cast<URPGAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
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

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
