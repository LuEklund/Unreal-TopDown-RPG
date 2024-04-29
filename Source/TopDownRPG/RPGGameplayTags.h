

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * RPGGameplayTags
 *
 * Singleton containing native Gameplay Tags (C++)
 */

struct FRPGGameplayTags
{
private:
 static FRPGGameplayTags GameplayTags;
protected:
public:
 static  const FRPGGameplayTags &Get() {return GameplayTags;}
 static  void  InitializeNativeGameplayTags();

 FGameplayTag Attribute_Secondary_armor;
};
