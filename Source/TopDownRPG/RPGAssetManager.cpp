


#include "RPGAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "RPGGameplayTags.h"
URPGAssetManager& URPGAssetManager::Get()
{
	check(GEngine);
	URPGAssetManager *RPGAssetManager = Cast<URPGAssetManager>(GEngine->AssetManager);
	return (*RPGAssetManager);
}

void URPGAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	FRPGGameplayTags::InitializeNativeGameplayTags();

	// This is required to use target data. But automatically enabled in Unreal 5.3+
	UAbilitySystemGlobals::Get().InitGlobalData();
}
