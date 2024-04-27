

#pragma once

#include "CoreMinimal.h"
#include "RPGCharacterBase.h"
#include "TopDownRPG/Interraction/EnemyInterface.h"
#include "RPGEnemy.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ARPGEnemy : public ARPGCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	ARPGEnemy();

	//Enemy Interface
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	//End Enemy interface

protected:
	virtual void BeginPlay() override;
};
