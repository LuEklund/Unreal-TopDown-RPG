#pragma once

#include "GameplayEffectTypes.h"
#include "RPGAbilityTypes.generated.h"


class UGameplayEffect;

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()
	
	FDamageEffectParams(){};

	UPROPERTY()
	TObjectPtr<UObject>	WorldContextObject = nullptr;

	UPROPERTY()
	TSubclassOf<UGameplayEffect>	DamageGameplayEffectClass = nullptr;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>	SourceAbilitySystemComponent = nullptr;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent>	TargetAbilitySystemComponent = nullptr;

	UPROPERTY()
	float	BaseDamage = 0.f;

	UPROPERTY()
	float	AbilityLevel = 1.f;

	UPROPERTY()
	FGameplayTag	DamageType = FGameplayTag();

	UPROPERTY()
	float	DebuffChance = 0.f;

	UPROPERTY()
	float	DebuffDamage = 0.f;

	UPROPERTY()
	float	DebuffDuration = 0.f;

	UPROPERTY()
	float	DebuffFrequency = 0.f;

	UPROPERTY()
	FVector	DeathImpulse = FVector::ZeroVector;
	
	UPROPERTY()
	float	DeathImpulseMagnitude = 0.f;
};
USTRUCT(BlueprintType)
struct FRPGGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	// bool
	bool                        IsBlockedHit() const {return bIsBlockedHit;}
	bool                        IsCriticalHit() const {return bIsCriticalHit;}
	bool                        IsSuccessfulDebuff() const {return bIssuccefulDebuff;}
	float	                    GetDebuffDamage() const {return DebuffDamage;}
	float	                    GetDebuffDuration() const {return DebuffDuration;}
	float	                    GetDebuffFrequency() const {return DebuffFrequency;}
	TSharedPtr<FGameplayTag>	GetDamageType() const {return DamageType;}
	FVector						GetDeathImpulse() const {return DeathImpulse;}

	void    SetIsBlockedHit(bool bInIsBlockedHit){ bIsBlockedHit = bInIsBlockedHit; }
	void    SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void	SetIsSuccefulDebuff(bool bInIsSuccessfulDebuff) {bIssuccefulDebuff = bInIsSuccessfulDebuff; } 
	void	SetDebuffDamage(float bInDebuffDamage) {DebuffDamage = bInDebuffDamage; } 
	void	SetDebuffDuration(float bInDebuffDuration) {DebuffDuration = bInDebuffDuration; } 
	void	SetDebuffFrequency(float bInDebuffFrequency) {DebuffFrequency = bInDebuffFrequency; }
	void	SetDamageType(TSharedPtr<FGameplayTag> InDamageType) { DamageType = InDamageType; }
	void	SetDeathImpulse(const FVector &bInDeathImpulse) {DeathImpulse = bInDeathImpulse; }

	
	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}
	
	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FRPGGameplayEffectContext* Duplicate() const
	{
		FRPGGameplayEffectContext* NewContext = new FRPGGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}
	
	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);


protected:
	UPROPERTY()
	bool	bIsBlockedHit = false;

	UPROPERTY()
	bool	bIsCriticalHit = false;

	UPROPERTY()
	bool	bIssuccefulDebuff = false;

	UPROPERTY()
	float	DebuffDamage = 0.f;
	
	UPROPERTY()
	float	DebuffDuration = 0.f;
	
	UPROPERTY()
	float	DebuffFrequency = 0.f;

	TSharedPtr<FGameplayTag>	DamageType;

	UPROPERTY()
	float	DeathImpulseMagnitude = 0.f;
	
	UPROPERTY()
	FVector	DeathImpulse = FVector::ZeroVector;
	
};


template<>
struct TStructOpsTypeTraits<FRPGGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FRPGGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};