

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "TopDownRPG/TopDownRPG.h"
#include "TopDownRPG/Interraction/HighlightInterface.h"
#include "TopDownRPG/Interraction/SaveInterface.h"
#include "Checkpoint.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ACheckpoint : public APlayerStart, public ISaveInterface, public IHighlightInterface
{
	GENERATED_BODY()
public:
	ACheckpoint(const FObjectInitializer& ObjectInitializer);

	// Save Interface
	virtual bool ShouldLoadTransform_Implementation() override {return false;}
	virtual void LoadActor_Implementation() override;
	// End Save Interface


	UPROPERTY(EditDefaultsOnly)
	int32	CustomDepthStencilOverride = CUSTOM_DEPTH_TAN;
	
	UPROPERTY(BlueprintReadWrite, SaveGame)
	bool bReached = false;

	UPROPERTY(EditAnywhere)
	bool	bBindOverlapCallback = true;

protected:
	UFUNCTION()
	virtual void	OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent>	MoveToComponent;
	
	// Highlight Interface
	virtual void SetMoveToLocation_Implementation(FVector& OutDestination) override;
	virtual void HighLightActor_Implementation() override;
	virtual void UnHighLightActor_Implementation() override;
	// End Highlight Interface
	
	UFUNCTION(BlueprintImplementableEvent)
	void	CheckPointReached(UMaterialInstanceDynamic *DynamicMaterialInstance);

	UFUNCTION(BlueprintCallable)
	void	HandleGlowEffects();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent>	CheckpointMesh;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>	Sphere;
};
