

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadScreen.generated.h"

class UMVVM_LoadSlot;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UMVVM_LoadScreen : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
public:
	void	InitializeLoadSlots();
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_LoadSlot>	LoadSlotViewModelClass;

	UFUNCTION(BlueprintPure)
	UMVVM_LoadSlot	*GetLoadSlotViewModelByIndex(int32 Index) const;

	UFUNCTION(BlueprintCallable)
	void	NewSlotButtonPressed(int32 Slot, const FString &EnteredName);

	UFUNCTION(BlueprintCallable)
	void	NewGameButtonPressed(int32 Slot);

	UFUNCTION(BlueprintCallable)
	void	SelectButtonPressed(int32 Slot);

	void	LoadData();

	void	SetNumLoadSlot(int32 InNumLoadSlots);
	int32	GetNumLoadSlot() const {return NumLoadSlot;}
private:
	UPROPERTY()
	TMap<int32, UMVVM_LoadSlot *>	LoadSlots;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot>		LoadSlot_0;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot>		LoadSlot_1;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot>		LoadSlot_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(AllowPrivateAccess="true"))
	int32	NumLoadSlot;
};
