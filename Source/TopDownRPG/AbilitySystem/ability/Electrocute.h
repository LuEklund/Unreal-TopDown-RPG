

#pragma once

#include "CoreMinimal.h"
#include "RPGBeamSpell.h"
#include "Electrocute.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UElectrocute : public URPGBeamSpell
{
	GENERATED_BODY()
public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString	GetNextLevelDescription(int32 Level) override;
	
};
