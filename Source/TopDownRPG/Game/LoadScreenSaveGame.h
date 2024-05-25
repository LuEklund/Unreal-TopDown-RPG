

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/SaveGame.h"
#include "LoadScreenSaveGame.generated.h"

class UGameplayAbility;

UENUM()
enum ESaveSlotStatus
{
	Vacant,
	EnterName,
	Taken
};

USTRUCT(BlueprintType)
struct FSavedAbility
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ClassDefaults")
	TSubclassOf<UGameplayAbility>	GameplayAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityStatus = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilitySlot = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AbilityType = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 AbilityLevel;
};

inline bool operator==(const FSavedAbility &Left, const FSavedAbility &Right)
{
	return Left.AbilityTag.MatchesTagExact(Right.AbilityTag);
}

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ULoadScreenSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString	SlotName = FString();

	UPROPERTY()
	int32	SlotIndex = 0;

	UPROPERTY()
	FString PlayerName = FString("Default Name");

	UPROPERTY()
	FString MapName = FString("Default Map Name");

	UPROPERTY()
	FName	PlayerStartTag;

	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus>	SaveSlotStatus = Vacant;

	UPROPERTY()
	bool	bFirstTimeLoadIn = true;

	//Player
	UPROPERTY()
	int32	PlayerLevel = 1;

	UPROPERTY()
	int32	XP = 0;

	UPROPERTY()
	int32	SpellPoints = 0;

	UPROPERTY()
	int32	AttributesPoints = 0;

	//Attributes
	UPROPERTY()
	float	Strength = 0;

	UPROPERTY()
	float	Intelligence = 0;

	UPROPERTY()
	float	Resilience = 0;

	UPROPERTY()
	float	Vigor = 0;


	//Abilities
	UPROPERTY()
	TArray<FSavedAbility>	SavedAbilities;
};