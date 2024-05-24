

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadSlot.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndex, int32, WidgetSwitcherIndex);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UMVVM_LoadSlot : public UMVVMViewModelBase
{
	GENERATED_BODY()


public:
	void	InitializeSlot();
	
	UPROPERTY(BlueprintAssignable)
	FSetWidgetSwitcherIndex	SetWidgetSwitcherIndex;


	void	SetLoadSlotName(FString InLoadSlotName);
	void	SetPlayerName(FString InPlayerName);
	
	FString	GetLoadSlotName() const {return LoadSlotName;}
	FString	GetPlayerName() const {return PlayerName;}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	FString PlayerName;

	UPROPERTY()
	FString SlotIndex;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess="true"))
	FString	LoadSlotName;
};
