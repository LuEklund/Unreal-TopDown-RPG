

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RPGAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;
	
	UPROPERTY()
	UAbilitySystemComponent	*SourceASC = nullptr;

	UPROPERTY()
	AActor					*SourceAvatarActor = nullptr;

	UPROPERTY()
	AController				*SourceController = nullptr;

	UPROPERTY()
	ACharacter				*SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent	*TargetASC = nullptr;

	UPROPERTY()
	AActor					*TargetAvatarActor = nullptr;

	UPROPERTY()
	AController				*TargetController = nullptr;

	UPROPERTY()
	ACharacter				*TargetCharacter = nullptr;
};

// typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFunPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	URPGAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void	PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void	PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void	PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	/*	TMap that contains FGameplayTag and Function pointers.
	 *	The function takes zero parameters and returns a FGameplayAttribute.
	 */
	TMap<FGameplayTag, TStaticFunPtr<FGameplayAttribute()>>	TagsToAttributes;

	
	/*
	 * Primary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category="Primary Attributes")
	FGameplayAttributeData	Strength;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category="Primary Attributes")
	FGameplayAttributeData	Intelligence;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category="Primary Attributes")
	FGameplayAttributeData	Resilience;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Resilience);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category="Primary Attributes")
	FGameplayAttributeData	Vigor;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Vigor);

	/*
	 * Secondary Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category="Primary Attributes")
	FGameplayAttributeData	Armor;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Armor);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category="Primary Attributes")
	FGameplayAttributeData	ArmorPenetration;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ArmorPenetration);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category="Primary Attributes")
	FGameplayAttributeData	BlockChance;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, BlockChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category="Primary Attributes")
	FGameplayAttributeData	CriticalHitChance;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, CriticalHitChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category="Primary Attributes")
	FGameplayAttributeData	CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, CriticalHitDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category="Primary Attributes")
	FGameplayAttributeData	CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, CriticalHitResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category="Primary Attributes")
	FGameplayAttributeData	HealthRegeneration;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, HealthRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category="Primary Attributes")
	FGameplayAttributeData	ManaRegeneration;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ManaRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category="Vital Attributes")
	FGameplayAttributeData	MaxHealth;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category="Vital Attributes")
	FGameplayAttributeData	MaxMana;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxMana);

	/*
	 * Secondary Attributes [Resistances]
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireResistance, Category="Resistance Attributes")
	FGameplayAttributeData	FireResistance;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, FireResistance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningResistance, Category="Resistance Attributes")
	FGameplayAttributeData	LightningResistance;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, LightningResistance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArcaneResistance, Category="Resistance Attributes")
	FGameplayAttributeData	ArcaneResistance;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ArcaneResistance);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalResistance, Category="Resistance Attributes")
	FGameplayAttributeData	PhysicalResistance;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, PhysicalResistance);
	
	/*
	 * Vital Attributes
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category="Vital Attributes")
	FGameplayAttributeData	Health;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Health);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category="Vital Attributes")
	FGameplayAttributeData	Mana;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Mana);

	/*
	 * Meta Attributes
	 */
	UPROPERTY(BlueprintReadOnly, Category="Meta Attribute")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, IncomingDamage);

	UPROPERTY(BlueprintReadOnly, Category="Meta Attribute")
	FGameplayAttributeData IncomingXP;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, IncomingXP);



	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData &OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData &OldMaxHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData &OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData &OldMaxMana) const;


	UFUNCTION()
	void OnRep_FireResistance(const FGameplayAttributeData &OldFireResistance) const;
	UFUNCTION()
	void OnRep_LightningResistance(const FGameplayAttributeData &OldLightningResistance) const;
	UFUNCTION()
	void OnRep_ArcaneResistance(const FGameplayAttributeData &OldArcaneResistance) const;
	UFUNCTION()
	void OnRep_PhysicalResistance(const FGameplayAttributeData &OldPhysicalResistance) const;
	

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData &OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData &OldIntelligence) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData &OldResilience) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData &OldVigor) const;

	/*
	 * Secondary attributes
	 */
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData &OldArmor) const;
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData &OldArmorPenetration) const;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData &OldBlockChance) const;
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData &OldCriticalHitChance) const;
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData &OldCriticalHitDamage) const;
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData &OldCriticalHitResistance) const;
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData &OldHealthRegeneration) const;
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData &OldManaRegeneration) const;
	
private:
	void	HandleIncomingDamage(const FEffectProperties &Props);
	void	HandleIncomingXP(const FEffectProperties &Props);
	void	HandleDebuff(const FEffectProperties &Props);
	void	SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties &Props) const;
	void	ShowFloatingText(const FEffectProperties &Props, float Damage);
	void	SendXPEvent(const FEffectProperties &Props);
	bool	bTopOfHealth = false;
	bool	bTopOfMana = false;

	
};
