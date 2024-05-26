


#include "RPGGameModeBase.h"

#include "EngineUtils.h"
#include "LoadScreenSaveGame.h"
#include "RPGGameInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "TopDownRPG/RPGLogChannels.h"
#include "TopDownRPG/Interraction/SaveInterface.h"
#include "TopDownRPG/UI/ViewModel/MVVM_LoadSlot.h"

void ARPGGameModeBase::SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex)
{
	DeleteSlot(LoadSlot->GetLoadSlotName(), SlotIndex);

	USaveGame *SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
	ULoadScreenSaveGame *LoadScreenSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject);
	LoadScreenSaveGame->PlayerName = LoadSlot->GetPlayerName();
	LoadScreenSaveGame->SaveSlotStatus = ESaveSlotStatus::Taken;
	LoadScreenSaveGame->MapName = LoadSlot->GetMapName();
	LoadScreenSaveGame->MapAssetName = LoadSlot->MapAssetName;
	LoadScreenSaveGame->PlayerStartTag = LoadSlot->PlayerStartTag;
	
	UGameplayStatics::SaveGameToSlot(LoadScreenSaveGame, LoadSlot->GetLoadSlotName(), SlotIndex);
}

ULoadScreenSaveGame* ARPGGameModeBase::GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const
{
	USaveGame * SaveGameObject = nullptr;
	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
	{
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SlotName, SlotIndex);
	}
	else
	{
		SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
	}
	ULoadScreenSaveGame *LoadScreenSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject);
	return LoadScreenSaveGame;
}

void ARPGGameModeBase::DeleteSlot(const FString &LoadName, int32 SlotIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(LoadName, SlotIndex))
	{
		UGameplayStatics::DeleteGameInSlot(LoadName, SlotIndex);
	}
}

ULoadScreenSaveGame* ARPGGameModeBase::RetrieveInGameSaveData()
{
	URPGGameInstance *RPGGameInstance = Cast<URPGGameInstance>(GetGameInstance());
	const FString	InGameLoadSlotName = RPGGameInstance->LoadSlotName;
	const int32		InGameLoadSlotIndex = RPGGameInstance->LoadSlotIndex;

	return GetSaveSlotData(InGameLoadSlotName, InGameLoadSlotIndex);
}

void ARPGGameModeBase::SaveInGameProgressData(ULoadScreenSaveGame* saveObject)
{
	URPGGameInstance *RPGGameInstance = Cast<URPGGameInstance>(GetGameInstance());
	const FString	InGameLoadSlotName = RPGGameInstance->LoadSlotName;
	const int32		InGameLoadSlotIndex = RPGGameInstance->LoadSlotIndex;
	RPGGameInstance->PlayerStartTag = saveObject->PlayerStartTag;
	
	UGameplayStatics::SaveGameToSlot(saveObject, InGameLoadSlotName, InGameLoadSlotIndex);
}

void ARPGGameModeBase::SaveWorldState(UWorld* World, const FString &DestinationMapAssetName) const
{
	FString WorldName = World->GetMapName();
	WorldName.RemoveFromStart(World->StreamingLevelsPrefix);

	URPGGameInstance *RPGGI = Cast<URPGGameInstance>(GetGameInstance());

	if (ULoadScreenSaveGame *SaveGame = GetSaveSlotData(RPGGI->LoadSlotName, RPGGI->LoadSlotIndex))
	{
		if (DestinationMapAssetName != FString(""))
		{
			SaveGame->MapAssetName = DestinationMapAssetName;
			SaveGame->MapName = GetMapNameFromMapAssetName(DestinationMapAssetName);
		}
		if (!SaveGame->HasMap(WorldName))
		{
			FSavedMap NewSavedMap;
			NewSavedMap.MapAssetName = WorldName;
			SaveGame->SavedMaps.Add(NewSavedMap);
		}

		FSavedMap SavedMap = SaveGame->GetSavedMapWithMapName(WorldName);
		SavedMap.SavedActors.Empty();

		for (FActorIterator It(World); It; ++It)
		{
			AActor* Actor = *It;

			if(!IsValid(Actor) || !Actor->Implements<USaveInterface>()) continue;
			UE_LOG(LogRPG, Warning, TEXT("Actor: %s; "), *Actor->GetFName().ToString());

			FSavedActor	SavedActor;
			SavedActor.ActorName = Actor->GetFName();
			SavedActor.Transform = Actor->GetTransform();

			FMemoryWriter MemoryWriter(SavedActor.Bytes);

			FObjectAndNameAsStringProxyArchive	Archive(MemoryWriter, true);
			Archive.ArIsSaveGame = true;
			Actor->Serialize(Archive);
			SavedMap.SavedActors.AddUnique(SavedActor);
		}
		for (FSavedMap &MapToReplace : SaveGame->SavedMaps)
		{
			if (MapToReplace.MapAssetName == WorldName)
			{
				MapToReplace = SavedMap;
			}
		}
		UGameplayStatics::SaveGameToSlot(SaveGame, RPGGI->LoadSlotName, RPGGI->LoadSlotIndex);
	}
}

void ARPGGameModeBase::LoadWorldState(UWorld* World) const
{
	FString WorldName = World->GetMapName();
	WorldName.RemoveFromStart(World->StreamingLevelsPrefix);
	
	URPGGameInstance *RPGGI = Cast<URPGGameInstance>(GetGameInstance());

	if (UGameplayStatics::DoesSaveGameExist(RPGGI->LoadSlotName, RPGGI->LoadSlotIndex))
	{

		ULoadScreenSaveGame *SaveGame = Cast<ULoadScreenSaveGame>(UGameplayStatics::LoadGameFromSlot(RPGGI->LoadSlotName, RPGGI->LoadSlotIndex));
		if (SaveGame == nullptr)
		{
			UE_LOG(LogRPG, Error, TEXT("FAILED TO LOAD SLOT"));
			return ;
		}
		
		for (FActorIterator It(World); It; ++It)
		{
			AActor *Actor = *It;

			if (!Actor->Implements<USaveInterface>()) continue;
			
			for (FSavedActor SavedActor : SaveGame->GetSavedMapWithMapName(WorldName).SavedActors)
			{
				if (SavedActor.ActorName == Actor->GetFName())
				{
					UE_LOG(LogRPG, Error, TEXT("Actor: %s; "), *Actor->GetFName().ToString());
					if (ISaveInterface::Execute_ShouldLoadTransform(Actor))
					{
						Actor->SetActorTransform(SavedActor.Transform);
					}
					FMemoryReader MemoryReader(SavedActor.Bytes);
					FObjectAndNameAsStringProxyArchive Archive(MemoryReader, true);
					Archive.ArIsSaveGame = true;
					Actor->Serialize(Archive); //Converts binary bytes back into variables.

					ISaveInterface::Execute_LoadActor(Actor);
				}
			}
		}
	}
}

void ARPGGameModeBase::TravelToMap(UMVVM_LoadSlot* Slot)
{
	const FString SlotName = Slot->GetLoadSlotName();
	const int32 SlotIndex = Slot->SlotIndex;
	UGameplayStatics::OpenLevelBySoftObjectPtr(Slot, Maps.FindChecked(Slot->GetMapName()));
}

FString ARPGGameModeBase::GetMapNameFromMapAssetName(const FString& MapAssetName) const
{
	for (auto &Map : Maps)
	{
		if (Map.Value.ToSoftObjectPath().GetAssetName() == MapAssetName)
		{
			return Map.Key;
		}
	}
	return FString();
}

AActor* ARPGGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	URPGGameInstance *RPGGameInstance = Cast<URPGGameInstance>(GetGameInstance());

	
	TArray<AActor *> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(),  Actors);
	if (Actors.Num() > 0)
	{
		AActor *SelectedActor = Actors[0];
		for (AActor *Actor : Actors)
		{
			if (APlayerStart *PlayerStart = Cast<APlayerStart>(Actor))
			{
				if (PlayerStart->PlayerStartTag == RPGGameInstance->PlayerStartTag)
				{
					SelectedActor = PlayerStart;
					break;
				}
			}
		}
		return SelectedActor;
	}
	return nullptr;
}

void ARPGGameModeBase::PlayerDied(ACharacter* DeadCharacter)
{
	ULoadScreenSaveGame *SaveGame = RetrieveInGameSaveData();
	if (!IsValid(SaveGame)) return;

	UGameplayStatics::OpenLevel(DeadCharacter, FName(SaveGame->MapAssetName));
}

void ARPGGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	Maps.Add(DefaultMapName, DefaultMap);
}
