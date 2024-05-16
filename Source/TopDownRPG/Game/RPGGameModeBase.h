

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RPGGameModeBase.generated.h"

class UAbilityInfo;
class UCharacterClassInfo;

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ARPGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults")
	TObjectPtr<UCharacterClassInfo>	CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Ability info")
	TObjectPtr<UAbilityInfo>	AbilityInfo;
	
	
};
