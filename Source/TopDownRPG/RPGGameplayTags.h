

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


 
 FGameplayTag Attribute_Meta_IncomingXP;

 FGameplayTag Input_Mouse_LMB;
 FGameplayTag Input_Mouse_RMB;
 FGameplayTag Input_Keyboard_1;
 FGameplayTag Input_Keyboard_2;
 FGameplayTag Input_Keyboard_3;
 FGameplayTag Input_Keyboard_4;
 FGameplayTag Input_Passive_1;
 FGameplayTag Input_Passive_2;


 
 FGameplayTag Damage;
 FGameplayTag Damage_Fire;
 FGameplayTag Damage_Lighting;
 FGameplayTag Damage_Arcane;
 FGameplayTag Damage_Physical;

 FGameplayTag Attribute_Resistance_Fire;
 FGameplayTag Attribute_Resistance_Lightning;
 FGameplayTag Attribute_Resistance_Arcane;
 FGameplayTag Attribute_Resistance_Physical;
 
 FGameplayTag Debuff_Burn;
 FGameplayTag Debuff_Stun;
 FGameplayTag Debuff_Arcane;
 FGameplayTag Debuff_Physical;
 
 FGameplayTag Debuff_Chance;
 FGameplayTag Debuff_Damage;
 FGameplayTag Debuff_Duration;
 FGameplayTag Debuff_Frequency;
 

 FGameplayTag Abilities_None;
 FGameplayTag Abilities_Attack;
 FGameplayTag Abilities_Summon;
 
 FGameplayTag Abilities_HitReact;
 
 FGameplayTag Abilities_Status_Locked;
 FGameplayTag Abilities_Status_Eligible;
 FGameplayTag Abilities_Status_Unlocked;
 FGameplayTag Abilities_Status_Equipped;

 FGameplayTag Abilities_Type_Offensive;
 FGameplayTag Abilities_Type_Passive;
 FGameplayTag Abilities_Type_None;
 
 FGameplayTag Abilities_Fire_FireBolt;
 FGameplayTag Abilities_Lightning_Electrocute;
 
 FGameplayTag Cooldown_Fire_FireBolt;

 FGameplayTag CombatSocket_Weapon;
 FGameplayTag CombatSocket_LeftHand;
 FGameplayTag CombatSocket_RightHand;
 FGameplayTag CombatSocket_Tail;

 FGameplayTag Montage_Attack_1;
 FGameplayTag Montage_Attack_2;
 FGameplayTag Montage_Attack_3;
 FGameplayTag Montage_Attack_4;
 
 TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
 TMap<FGameplayTag, FGameplayTag> DamageTypesToDebuffs;

 FGameplayTag Effects_HitReact;

 FGameplayTag Player_Block_InputPressed;
 FGameplayTag Player_Block_InputHeld;
 FGameplayTag Player_Block_InputReleased;
 FGameplayTag Player_Block_CursorTrace;
};
