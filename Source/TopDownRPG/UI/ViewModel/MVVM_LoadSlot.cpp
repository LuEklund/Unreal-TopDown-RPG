


#include "MVVM_LoadSlot.h"

void UMVVM_LoadSlot::InitializeSlot()
{
	//TODO: CHECK slot status based on loaded data
	SetWidgetSwitcherIndex.Broadcast(1);
}

void UMVVM_LoadSlot::SetLoadSlotName(FString InLoadSlotName)
{
	UE_MVVM_SET_PROPERTY_VALUE(LoadSlotName, InLoadSlotName);
}
