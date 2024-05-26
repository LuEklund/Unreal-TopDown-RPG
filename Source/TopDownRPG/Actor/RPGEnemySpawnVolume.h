

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPGEnemySpawnVolume.generated.h"

UCLASS()
class TOPDOWNRPG_API ARPGEnemySpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARPGEnemySpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
