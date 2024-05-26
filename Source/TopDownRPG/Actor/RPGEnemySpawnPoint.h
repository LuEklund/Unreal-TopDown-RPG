

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "TopDownRPG/AbilitySystem/Data/CharacterClassInfo.h"
#include "RPGEnemySpawnPoint.generated.h"

class ARPGEnemy;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ARPGEnemySpawnPoint : public ATargetPoint
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy CLass")
	TSubclassOf<ARPGEnemy>	EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy CLass")
	int32	EnemyLevel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy CLass")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;
};
