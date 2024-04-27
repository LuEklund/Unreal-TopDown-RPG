

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGEffectActor.generated.h"

class USphereComponent;

UCLASS()
class TOPDOWNRPG_API ARPGEffectActor : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>	Sphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent>	Mesh;
public:	
	ARPGEffectActor();
	
	UFUNCTION()
	virtual void	OnOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor, UPrimitiveComponent *OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	virtual void	EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	virtual void BeginPlay() override;


};
