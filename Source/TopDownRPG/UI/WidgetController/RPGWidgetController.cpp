


#include "RPGWidgetController.h"

#include "TopDownRPG/AbilitySystem/RPGAbilitySystemComponent.h"
#include "TopDownRPG/AbilitySystem/RPGAttributeSet.h"
#include "TopDownRPG/AbilitySystem/Data/AbilityInfo.h"
#include "TopDownRPG/Player/RPGPlayerController.h"
#include "TopDownRPG/Player/RPGPlayerState.h"

ARPGPlayerController* URPGWidgetController::GetRPG_PC()
{
	if (RPGPlayerController == nullptr)
	{
		RPGPlayerController = Cast<ARPGPlayerController>(PlayerController);
	}
	return RPGPlayerController;
}

ARPGPlayerState* URPGWidgetController::GetRPG_PS()
{
	if (RPGPlayerState == nullptr)
	{
		RPGPlayerState = Cast<ARPGPlayerState>(PlayerState);
	}
	return RPGPlayerState;
}

URPGAbilitySystemComponent* URPGWidgetController::GetRPG_ASC()
{
	if (RPGAbilitySystemComponent == nullptr)
	{
		RPGAbilitySystemComponent = Cast<URPGAbilitySystemComponent>(AbilitySystemComponent);
	}
	return RPGAbilitySystemComponent;
}

URPGAttributeSet* URPGWidgetController::GetRPG_AS()
{
	if (RPGAttributeSet == nullptr)
	{
		RPGAttributeSet = Cast<URPGAttributeSet>(AttributeSet);
	}
	return RPGAttributeSet;
}

void URPGWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void URPGWidgetController::BroadcastInitialValues()
{
}

void URPGWidgetController::BindCallbacksToDependencies()
{
}

void URPGWidgetController::BroadcastAbilityInfo()
{
	if (!GetRPG_ASC()->bStartupAbilitiesGive) return;
	FForEachAbility	BroadcastDelegate;
	BroadcastDelegate.BindLambda(
		[this](const FGameplayAbilitySpec &AbilitySpec)
		{
			FRPGAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(URPGAbilitySystemComponent::GetAbilityTagFromSpec(AbilitySpec));
			Info.InputTag = URPGAbilitySystemComponent::GetInputTagFromSpec(AbilitySpec);
			AbilityInfoDelegate.Broadcast(Info);
		});
	GetRPG_ASC()->ForEachAbility(BroadcastDelegate);
}
