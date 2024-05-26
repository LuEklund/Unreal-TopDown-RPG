

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameModeBase.generated.h"

class ULoadScreenSaveGame;
class USaveGame;
class UMVVM_LoadSlot;
class UAbilityInfo;
class UCharacterClassInfo;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ARPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults")
	TObjectPtr<UCharacterClassInfo>	CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Ability info")
	TObjectPtr<UAbilityInfo>	AbilityInfo;

	void	SaveSlotData(UMVVM_LoadSlot *LoadSlot, int32 SlotIndex);
	ULoadScreenSaveGame *GetSaveSlotData(const FString &SlotName, int32 SlotIndex) const;
	static void	DeleteSlot(const FString &LoadName, int32 SlotIndex);
	ULoadScreenSaveGame* RetrieveInGameSaveData();
	void	SaveInGameProgressData(ULoadScreenSaveGame *saveObject);

	void	SaveWorldState(UWorld *World, const FString &DestinationMapAssetName = FString("")) const;
	void	LoadWorldState(UWorld *World) const;

	void	TravelToMap(UMVVM_LoadSlot* Slot);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame>	LoadScreenSaveGameClass;

	UPROPERTY(EditDefaultsOnly)
	FString	DefaultMapName;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> DefaultMap;

	FString	GetMapNameFromMapAssetName(const FString &MapAssetName) const;

	UPROPERTY(EditDefaultsOnly)
	FName	DefaultPlayerStartTag;

	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>> Maps;

	virtual AActor *ChoosePlayerStart_Implementation(AController* Player) override;

protected:
	virtual void BeginPlay() override;
};
