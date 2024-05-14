

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWNRPG_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent)
	void	AddToXP(int32 InXp);

	UFUNCTION(BlueprintNativeEvent)
	void	AddToPlayerLevel(int32 InPlayerLevel);

	UFUNCTION(BlueprintNativeEvent)
	void	AddToAttributePoints(int32 InAttributePoints);

	UFUNCTION(BlueprintNativeEvent)
	void	AddToSpellPoints(int32 InSpellPoints);

	UFUNCTION(BlueprintNativeEvent)
	int32	GetXP() const;

	UFUNCTION(BlueprintNativeEvent)
	int32	GetAttributePointsReward(int32 InLevel) const;

	UFUNCTION(BlueprintNativeEvent)
	int32	GetSpellPointsReward(int32 InLevel) const;
	
	UFUNCTION(BlueprintNativeEvent)
	int32 FindLevelForXP(int32 InXp) const;

	UFUNCTION(BlueprintNativeEvent)
	void LevelUp();
};
