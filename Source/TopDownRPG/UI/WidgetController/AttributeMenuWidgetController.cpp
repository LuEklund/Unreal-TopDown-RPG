


#include "AttributeMenuWidgetController.h"

#include "TopDownRPG/AbilitySystem/RPGAttributeSet.h"
#include "TopDownRPG/AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FRPGAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfo);
	URPGAttributeSet *AS = CastChecked<URPGAttributeSet>(AttributeSet);
	for (auto &Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
		[this, Pair](const FOnAttributeChangeData &Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	URPGAttributeSet *AS = CastChecked<URPGAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto &Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}

}
