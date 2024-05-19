

#pragma once

#include "CoreMinimal.h"
#include "RPGCharacterBase.h"
#include "TopDownRPG/Interraction/EnemyInterface.h"
#include "TopDownRPG/UI/WidgetController/OverlayWidgetController.h"
#include "RPGEnemy.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class ARPGAIController;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ARPGEnemy : public ARPGCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	ARPGEnemy();
	virtual void PossessedBy(AController* NewController) override;

	
	
	//Enemy Interface
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	//End Enemy interface

	//Combat Interface
	virtual int32 GetPlayerLevel_Implementation() override;
	virtual void	Die(const FVector &DeathImpulse) override;
	virtual void	SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor	*GetCombatTarget_Implementation() const override;
	//End Combat Interface

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature	OnHealthChanged;
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature	OnMaxHealthChanged;
	
	void	HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	
	UPROPERTY(BlueprintReadOnly, Category="Combat")
	bool bHitReacting = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	float	BaseWalkSpeed = 250.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	float	LifeSpan = 5.f;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TObjectPtr<AActor>	CombatTarget;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void	InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character class defaults")
	int32	Level = 1;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent>	HealthBar;

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree>	BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<ARPGAIController>	RPGAIController;


};
