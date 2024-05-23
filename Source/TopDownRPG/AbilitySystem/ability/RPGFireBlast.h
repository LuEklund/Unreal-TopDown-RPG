

#pragma once

#include "CoreMinimal.h"
#include "RPGDamageGameplayAbility.h"
#include "RPGFireBlast.generated.h"

class ARPGFireBall;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGFireBlast : public URPGDamageGameplayAbility
{
	GENERATED_BODY()
public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString	GetNextLevelDescription(int32 Level) override;

	UFUNCTION(BlueprintCallable)
	TArray<ARPGFireBall *>	SpawnFireBalls();
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="FireBall")
	int32	NumFireBalls = 12;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ARPGFireBall>	FireBallClass;
	
	
};
