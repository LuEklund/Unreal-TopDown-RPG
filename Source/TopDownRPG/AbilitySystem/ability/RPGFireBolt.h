

#pragma once

#include "CoreMinimal.h"
#include "RPGProjectileSpell.h"
#include "RPGFireBolt.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGFireBolt : public URPGProjectileSpell
{
	GENERATED_BODY()
public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString	GetNextLevelDescription(int32 Level) override;

	UFUNCTION(BlueprintCallable)
	void	SpawnProjectiles(const FVector &ProjectileTargetLocation, const FGameplayTag &SocketTag, bool bOverridePitch, float PitchOverride, AActor *HomingTarget);

protected:
	
	UPROPERTY(EditDefaultsOnly, Category="FireBolt")
	float	ProjectileSpread = 90.f;


	UPROPERTY(EditDefaultsOnly, Category="FireBolt")
	int32	MaxNumProjectiles = 5;
};
