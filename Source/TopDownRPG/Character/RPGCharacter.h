

#pragma once

#include "CoreMinimal.h"
#include "RPGCharacterBase.h"
#include "RPGCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ARPGCharacter : public ARPGCharacterBase
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<USpringArmComponent>	SpringArmComponent;

	UPROPERTY(EditAnywhere, Category="Camera")
	TObjectPtr<UCameraComponent>	CameraComponent;

public:
	ARPGCharacter();
};
