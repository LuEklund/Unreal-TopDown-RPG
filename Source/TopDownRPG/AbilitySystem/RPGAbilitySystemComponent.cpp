


#include "RPGAbilitySystemComponent.h"

#include "TopDownRPG/RPGGameplayTags.h"

void URPGAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &URPGAbilitySystemComponent::EffectApplied);

	const FRPGGameplayTags &GameplayTags = FRPGGameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attribute_Secondary_armor.ToString()));
	
}

void URPGAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
                                               const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
	
}
