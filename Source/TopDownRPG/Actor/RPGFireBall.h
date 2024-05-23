

#pragma once

#include "CoreMinimal.h"
#include "RPGProjectile.h"
#include "RPGFireBall.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ARPGFireBall : public ARPGProjectile
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void StartOutGoingTimeline();

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AActor>	ReturnToActor;
	
	UPROPERTY(BlueprintReadWrite)
	FDamageEffectParams	ExplosionDamageParams;
protected:
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void BeginPlay() override;

};
