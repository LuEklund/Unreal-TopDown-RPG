

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Elementalist,
	Warrior,
	Ranger
};

USTRUCT(BlueprintType)
struct FCharacterDefaultInfo
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, Category="Class Deafults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Class Deafults")
	TArray<TSubclassOf<UGameplayAbility>>	StartupAbilities;
	
};

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Character Class Deafults")
	TMap<ECharacterClass, FCharacterDefaultInfo> CharacterClassInformation;
	
	UPROPERTY(EditDefaultsOnly, Category="Common Class Deafults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Common Class Deafults")
	TSubclassOf<UGameplayEffect> VitalAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Common Class Deafults")
	TArray<TSubclassOf<UGameplayAbility>>	CommonAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category="Common Class Deafults")
	TObjectPtr<UCurveTable> DamageCalculationCoefficients;
	
	FCharacterDefaultInfo	GetClassDefaultInfo(ECharacterClass CharacterClass);
};
