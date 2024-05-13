

#pragma once

#include "CoreMinimal.h"
#include "RPGCharacterBase.h"
#include "TopDownRPG/Interraction/PlayerInterface.h"
#include "RPGCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ARPGCharacter : public ARPGCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()
public:
	ARPGCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	//Player Interface
	virtual void AddToXP_Implementation(int32 InXp) override;
	virtual void LevelUp_Implementation() override;
	//ENd Player Interface
	
	
	//Combat Interface
	virtual int32 GetPlayerLevel_Implementation() override;
	//End Combat Interface
	
private:
	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<USpringArmComponent>	SpringArmComponent;

	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<UCameraComponent>	CameraComponent;

	virtual void	InitAbilityActorInfo() override;

};
