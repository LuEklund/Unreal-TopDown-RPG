


#include "RPGEnemySpawnPoint.h"

#include "TopDownRPG/Character/RPGEnemy.h"

void ARPGEnemySpawnPoint::SpawnEnemy()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ARPGEnemy *Enemy = GetWorld()->SpawnActorDeferred<ARPGEnemy>(EnemyClass, GetActorTransform());
	// Enemy->
}
