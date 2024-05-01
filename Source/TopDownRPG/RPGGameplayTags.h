

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
public:
 static  const FRPGGameplayTags &Get() {return GameplayTags;}
 static  void  InitializeNativeGameplayTags();

 ~FRPGGameplayTags();

 FGameplayTag Attribute_Primary_Strength;
 FGameplayTag Attribute_Primary_Intelligence;
 FGameplayTag Attribute_Primary_Resilience;
 FGameplayTag Attribute_Primary_Vigor;
 
 FGameplayTag Attribute_Secondary_Armor;
 FGameplayTag Attribute_Secondary_ArmorPenetration;
 FGameplayTag Attribute_Secondary_BlockChance;
 FGameplayTag Attribute_Secondary_CriticalHitChance;
 FGameplayTag Attribute_Secondary_CriticalHitDamage;
 FGameplayTag Attribute_Secondary_CriticalHitResistance;
 FGameplayTag Attribute_Secondary_HealthRegeneration;
 FGameplayTag Attribute_Secondary_ManaRegeneration;
 FGameplayTag Attribute_Secondary_MaxHealth;
 FGameplayTag Attribute_Secondary_MaxMana;

 FGameplayTag Input_Mouse_LMB;
 FGameplayTag Input_Mouse_RMB;
 FGameplayTag Input_Keyboard_1;
 FGameplayTag Input_Keyboard_2;
 FGameplayTag Input_Keyboard_3;
 FGameplayTag Input_Keyboard_4;

 FGameplayTag Damage;

};
