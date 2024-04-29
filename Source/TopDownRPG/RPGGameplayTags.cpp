


#include "RPGGameplayTags.h"
#include "GameplayTagsManager.h"

FRPGGameplayTags FRPGGameplayTags::GameplayTags;

void FRPGGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attribute_Secondary_armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("Reduces damage taken, improves block chance"));
	
}
