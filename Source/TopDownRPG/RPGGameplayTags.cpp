


#include "RPGGameplayTags.h"
#include "GameplayTagsManager.h"

FRPGGameplayTags FRPGGameplayTags::GameplayTags;

void FRPGGameplayTags::InitializeNativeGameplayTags()
{
	//Primary Attributes
	GameplayTags.Attribute_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"),
		FString("Increases physical damage"));

	GameplayTags.Attribute_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Increases magical damage"));

	GameplayTags.Attribute_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Resilience"),
		FString("Increases armor and armor penetration"));

	GameplayTags.Attribute_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Vigor"),
		FString("Increases health"));

	
	//Secondary Attributes
	GameplayTags.Attribute_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.Armor"),
		FString("Reduces damage taken, improves block chance"));

	GameplayTags.Attribute_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ArmorPenetration"),
		FString("Increases damage dealt to enemies with armor"));

	GameplayTags.Attribute_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.BlockChance"),
		FString("Increases chance to block attacks"));

	GameplayTags.Attribute_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitChance"),
		FString("Increases chance to deal critical hits"));

	GameplayTags.Attribute_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitDamage"),
		FString("Increases damage dealt by critical hits"));

	GameplayTags.Attribute_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CriticalHitResistance"),
		FString("Decreases damage taken from critical hits"));

	GameplayTags.Attribute_Secondary_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.HealthRegeneration"),
		FString("Increases health regeneration rate"));

	GameplayTags.Attribute_Secondary_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.ManaRegeneration"),
		FString("Increases mana regeneration rate"));

	GameplayTags.Attribute_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"),
		FString("Increases maximum health"));

	GameplayTags.Attribute_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxMana"),
		FString("Increases maximum mana"));

	
	// Input Tags
	GameplayTags.Input_Mouse_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Input.Mouse.LMB"),
	FString("Left Mouse Button")
	);

	GameplayTags.Input_Mouse_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Mouse.RMB"),
		FString("Right Mouse Button")
	);

	GameplayTags.Input_Keyboard_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Keyboard.1"),
		FString("Number Key 1")
	);

	GameplayTags.Input_Keyboard_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Keyboard.2"),
		FString("Number Key 2")
	);

	GameplayTags.Input_Keyboard_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Keyboard.3"),
		FString("Number Key 3")
	);

	GameplayTags.Input_Keyboard_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Input.Keyboard.4"),
		FString("Number Key 4")
	);

	GameplayTags.Input_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Input.Passive.1"),
	FString("Input for passive 1")
);

	GameplayTags.Input_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Input.Passive.2"),
	FString("Input for passive 2")
);

	
	// Damage types
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage"),
	FString("Damage")
	);
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Fire"),
	FString("Fire Damage type")
	);
	GameplayTags.Damage_Lighting = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Lighting"),
	FString("Lighting Damage type")
	);
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Arcane"),
	FString("Arcane Damage type")
	);
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Damage.Physical"),
	FString("Physical Damage type")
	);

	
	// Resistances types
	GameplayTags.Attribute_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resistance.Fire"),
	FString("Fire Resistance")
	);
	GameplayTags.Attribute_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resistance.Lighting"),
	FString("Lighting Resistance")
	);
	GameplayTags.Attribute_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resistance.Arcane"),
	FString("Arcane Resistance")
	);
	GameplayTags.Attribute_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Resistance.Physical"),
	FString("Physical Resistance")
	);

	
	// Meta Attributes
	GameplayTags.Attribute_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Attributes.Meta.IncomingXP"),
	FString("IncomingXP XP Meta Attribute")
	);


	
	// Map of Damage types to resistances
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attribute_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attribute_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lighting, GameplayTags.Attribute_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attribute_Resistance_Physical);

	
	// Effects
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Effects.HitReact"),
	FString("Tag Granted when hit Reacting")
	);

	
	// Abilities
	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Attack"),
	FString("Attack Ability tag")
	);
	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Summon"),
	FString("Summon Ability tag")
	);
	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Fire.FireBolt"),
	FString("FireBolt Ability tag")
	);
	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.HitReact"),
	FString("HitReact Ability")
	);
	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.Eligible"),
	FString("Eligible Status")
	);
	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.Equipped"),
	FString("Equipped Status")
	);
	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(
    FName("Abilities.Status.Locked"),
    FString("Locked Status")
    );
	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Status.Unlocked"),
	FString("Unlocked Status")
	);
	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Type.Passive"),
	FString("Passive Type")
	);
	GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Type.Offensive"),
	FString("Offensive Type")
	);
	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Abilities.Type.None"),
	FString("None Type")
	);


	// Cooldown
	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Cooldown.Fire.FireBolt"),
	FString("Firebolt Cooldown tag")
	);

	
	// Combat Sockets
	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.Weapon"),
	FString("Weapon")
	);

	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.LeftHand"),
	FString("Left Hand")
	);

	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.RightHand"),
	FString("Right Hand")
	);

	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("CombatSocket.Tail"),
	FString("Tail")
	);

	
	// Montages Tags
	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack.1"),
	FString("Attack 1")
	);

	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack.2"),
	FString("Attack 2")
	);

	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack.3"),
	FString("Attack 3")
	);

	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
	FName("Montage.Attack.4"),
	FString("Attack 4")
	);
	
}

FRPGGameplayTags::~FRPGGameplayTags()
{
	UE_LOG(LogTemp, Error, TEXT("DESTYRUED"));
}
