

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "TopDownRPG/Game/LoadScreenSaveGame.h"
#include "MVVM_LoadSlot.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndex, int32, WidgetSwitcherIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnableSelectSlotButton, bool, bEnable);

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UMVVM_LoadSlot : public UMVVMViewModelBase
{
	GENERATED_BODY()


public:
	UPROPERTY(BlueprintAssignable)
	FSetWidgetSwitcherIndex	SetWidgetSwitcherIndex;

	UPROPERTY(BlueprintAssignable)
	FEnableSelectSlotButton	EnableSelectSlotButton;
	
	void	InitializeSlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	FString PlayerName;

	UPROPERTY()
	FString SlotIndex;

	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus>	SlotStatus;

	void	SetLoadSlotName(FString InLoadSlotName);
	void	SetPlayerName(FString InPlayerName);
	
	FString	GetLoadSlotName() const {return LoadSlotName;}
	FString	GetPlayerName() const {return PlayerName;}

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess="true"))
	FString	LoadSlotName;
};
