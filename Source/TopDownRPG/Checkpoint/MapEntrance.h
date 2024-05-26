

#pragma once

#include "CoreMinimal.h"
#include "Checkpoint.h"
#include "MapEntrance.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API AMapEntrance : public ACheckpoint
{
	GENERATED_BODY()

public:
	AMapEntrance(const FObjectInitializer& ObjectInitializer);
	// Highlight Interface
	virtual void HighLightActor_Implementation() override;
	// End Highlight Interface

	// Save Interface
	virtual void LoadActor_Implementation() override;
	// End Save Interface

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld>	DestinationMap;

	UPROPERTY(EditAnywhere)
	FName	DestinationPlayerStartTag;

protected:
	virtual void	OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;

	
};
