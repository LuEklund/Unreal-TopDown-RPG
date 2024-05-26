

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TopDownRPG/Interraction/SaveInterface.h"
#include "RPGEnemySpawnVolume.generated.h"

class ARPGEnemySpawnPoint;
class UBoxComponent;

UCLASS()
class TOPDOWNRPG_API ARPGEnemySpawnVolume : public AActor, public ISaveInterface
{
	GENERATED_BODY()
	
public:	
	ARPGEnemySpawnVolume();

	//Save Interface
	virtual void LoadActor_Implementation() override;
	//End Save Interface

	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool bReached = false;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void	OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UPROPERTY(EditAnywhere)
	TArray<ARPGEnemySpawnPoint *>	SpawnPoints;
	
private:

	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> Box;

};
