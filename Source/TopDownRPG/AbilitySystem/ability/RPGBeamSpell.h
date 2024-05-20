

#pragma once

#include "CoreMinimal.h"
#include "RPGDamageGameplayAbility.h"
#include "RPGBeamSpell.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGBeamSpell : public URPGDamageGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void StoreMouseDataInfo(const FHitResult &HitResult);

	UFUNCTION(BlueprintCallable)
	void StoreOwnerVariables();
	
	UFUNCTION(BlueprintCallable)
	void	TraceFirstTarget(const FVector &BeamTargetLocation);

	UFUNCTION(BlueprintCallable)
	void	StoreAdditionalTargets(TArray<AActor *> &OutAdditionalTargets);
	
protected:
	UPROPERTY(BlueprintReadWrite, Category="Beam")
	FVector MouseHitLocation;

	UPROPERTY(BlueprintReadWrite, Category="Beam")
	TObjectPtr<AActor> MouseHitActor;

	UPROPERTY(BlueprintReadWrite, Category="Beam")
	TObjectPtr<APlayerController>	OwningPlayerController;

	UPROPERTY(BlueprintReadWrite, Category="Beam")
	TObjectPtr<ACharacter>	OwningCharacter;

	UPROPERTY(EditDefaultsOnly)
	int32	MaxNumShockTargets = 5;

	UPROPERTY(EditDefaultsOnly)
	float	ShockRadius = 850.f;
	
};