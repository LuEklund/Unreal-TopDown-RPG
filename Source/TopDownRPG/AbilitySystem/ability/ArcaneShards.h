

#pragma once

#include "CoreMinimal.h"
#include "RPGDamageGameplayAbility.h"
#include "ArcaneShards.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UArcaneShards : public URPGDamageGameplayAbility
{
	GENERATED_BODY()
public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString	GetNextLevelDescription(int32 Level) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxNumShards = 11;
	
};
