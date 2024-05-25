

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FName	PlayerStartTag = FName();

	UPROPERTY()
	FString	LoadSlotName = FString();

	int32	LoadSlotIndex = 0;
};
