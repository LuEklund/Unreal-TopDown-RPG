


#include "AttributeMenuWidgetController.h"

#include "TopDownRPG/RPGGameplayTags.h"
#include "TopDownRPG/AbilitySystem/RPGAttributeSet.h"
#include "TopDownRPG/AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	URPGAttributeSet *AS = CastChecked<URPGAttributeSet>(AttributeSet);
	check(AttributeInfo);

	FRPGAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FRPGGameplayTags::Get().Attribute_Primary_Strength);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);
}
