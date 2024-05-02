#pragma once

#include "GameplayEffectTypes.h"
#include "RPGAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FRPGGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	// bool
	bool IsBlockedHit() const {return bIsBlockedHit;}
	bool IsCriticalHit() const {return bIsCriticalHit;}

	void SetIsBlockedHit(bool bInIsBlockedHit){ bIsBlockedHit = bInIsBlockedHit; }
	void SetIsCriticalHit(bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	
	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FGameplayEffectContext::StaticStruct();
	}
	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);


protected:
	UPROPERTY()
	bool	bIsBlockedHit = false;

protected:
	UPROPERTY()
	bool	bIsCriticalHit = false;
	
};


