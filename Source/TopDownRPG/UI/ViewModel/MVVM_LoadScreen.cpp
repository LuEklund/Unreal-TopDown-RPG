


#include "MVVM_LoadScreen.h"

#include "MVVM_LoadSlot.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownRPG/Game/RPGGameModeBase.h"

void UMVVM_LoadScreen::InitializeLoadSlots()
{
	LoadSlot_0 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_0->SetLoadSlotName(FString("LoadSlot_0"));
	LoadSlot_0->SlotIndex = 0;
	LoadSlots.Add(0, LoadSlot_0);

	LoadSlot_1 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_1->SetLoadSlotName(FString("LoadSlot_1"));
	LoadSlot_1->SlotIndex = 1;
	LoadSlots.Add(1, LoadSlot_1);

	LoadSlot_2 = NewObject<UMVVM_LoadSlot>(this, LoadSlotViewModelClass);
	LoadSlot_2->SetLoadSlotName(FString("LoadSlot_2"));
	LoadSlot_2->SlotIndex = 2;
	LoadSlots.Add(2, LoadSlot_2);

	SetNumLoadSlot(LoadSlots.Num());
}

UMVVM_LoadSlot* UMVVM_LoadScreen::GetLoadSlotViewModelByIndex(int32 Index) const
{
	return LoadSlots.FindChecked(Index);
}

void UMVVM_LoadScreen::NewSlotButtonPressed(int32 Slot, const FString& EnteredName)
{
	ARPGGameModeBase *RPGGameMode = Cast<ARPGGameModeBase>(UGameplayStatics::GetGameMode(this));
	LoadSlots[Slot]->SetPlayerName(EnteredName);
	LoadSlots[Slot]->SlotStatus = ESaveSlotStatus::Taken;

	RPGGameMode->SaveSlotData(LoadSlots[Slot], Slot);
	LoadSlots[Slot]->InitializeSlot();
}

void UMVVM_LoadScreen::NewGameButtonPressed(int32 Slot)
{
	LoadSlots[Slot]->SetWidgetSwitcherIndex.Broadcast(1);
}

void UMVVM_LoadScreen::SelectButtonPressed(int32 Slot)
{
	SlotSelected.Broadcast();
	for (const TTuple<int32, UMVVM_LoadSlot *> LoadSlot : LoadSlots)
	{
		LoadSlot.Value->EnableSelectSlotButton.Broadcast(LoadSlot.Key != Slot);
	}
	SelectedSlot = LoadSlots[Slot];
}

void UMVVM_LoadScreen::DeleteButtonPressed()
{
	if (IsValid(SelectedSlot))
	{
		ARPGGameModeBase::DeleteSlot(SelectedSlot->GetLoadSlotName(), SelectedSlot->SlotIndex);
		SelectedSlot->SlotStatus = ESaveSlotStatus::Vacant;
		SelectedSlot->InitializeSlot();
		SelectedSlot->EnableSelectSlotButton.Broadcast(true);
	}
}

void UMVVM_LoadScreen::LoadData()
{
	ARPGGameModeBase *RPGGameMode = Cast<ARPGGameModeBase>(UGameplayStatics::GetGameMode(this));
	for (const TTuple<int32, UMVVM_LoadSlot *> LoadSlot : LoadSlots)
	{
		ULoadScreenSaveGame *SaveObject = RPGGameMode->GetSaveSlotData(LoadSlot.Value->GetLoadSlotName(), LoadSlot.Key);

		const FString PlayerName = SaveObject->PlayerName;
		
		TEnumAsByte<ESaveSlotStatus>	SaveSlotStatus = SaveObject->SaveSlotStatus;
		LoadSlot.Value->SlotStatus = SaveSlotStatus;
		LoadSlot.Value->InitializeSlot();
		
		LoadSlot.Value->SetPlayerName(PlayerName);
		
	}
}

void UMVVM_LoadScreen::SetNumLoadSlot(int32 InNumLoadSlots)
{
	UE_MVVM_SET_PROPERTY_VALUE(NumLoadSlot, InNumLoadSlots);
}
