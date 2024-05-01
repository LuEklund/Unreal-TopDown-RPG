

#pragma once

#include "CoreMinimal.h"
#include "RPGCharacterBase.h"
#include "TopDownRPG/AbilitySystem/Data/CharacterClassInfo.h"
#include "TopDownRPG/Interraction/EnemyInterface.h"
#include "TopDownRPG/UI/WidgetController/OverlayWidgetController.h"
#include "RPGEnemy.generated.h"

class UWidgetComponent;
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

	//Combat Interface
	virtual int32 GetPlayerLevel() override;
	virtual void	Die() override;
	//End Combat Interface

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature	OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature	OnMaxHealthChanged;
	
	void	HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool bHitReacting = false;
	
	UPROPERTY(BlueprintReadOnly, Category="Combat")
	float	BaseWalkSpeed = 250.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	float	LifeSpan = 5.f;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void	InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character class defaults")
	int32	Level = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character class defaults")
	ECharacterClass	CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent>	HealthBar;


};
