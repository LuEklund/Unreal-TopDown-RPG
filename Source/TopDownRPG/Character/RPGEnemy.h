

#pragma once

#include "CoreMinimal.h"
#include "RPGCharacterBase.h"
#include "TopDownRPG/Interraction/EnemyInterface.h"
#include "TopDownRPG/Interraction/HighlightInterface.h"
#include "TopDownRPG/UI/WidgetController/OverlayWidgetController.h"
#include "RPGEnemy.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class ARPGAIController;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ARPGEnemy : public ARPGCharacterBase, public IEnemyInterface, public IHighlightInterface
{
	GENERATED_BODY()
public:
	ARPGEnemy();
	virtual void PossessedBy(AController* NewController) override;

	
	
	//Highlight Interface
	virtual void HighLightActor_Implementation() override;
	virtual void UnHighLightActor_Implementation() override;
	virtual void SetMoveToLocation_Implementation(FVector& OutDestination) override;
	//End Highlight interface

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
	float	LifeSpan = 5.f;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TObjectPtr<AActor>	CombatTarget;

	void	SetLevel(int32 InLevel) {Level = InLevel;}

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void	InitializeDefaultAttributes() const override;
	virtual void	StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character class defaults")
	int32	Level = 1;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent>	HealthBar;

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree>	BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<ARPGAIController>	RPGAIController;


};
