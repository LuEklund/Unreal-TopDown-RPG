

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "RPGPlayerController.generated.h"


class URPGInputConfig;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class URPGAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ARPGPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> RPGContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void	Move(const FInputActionValue &InputActionValue);
	
	void	CurserTrace();

	IEnemyInterface	*LastActor;
	IEnemyInterface	*CurrentActor;

	void	AvilityInputTagPressed(FGameplayTag InputTag);
	void	AvilityInputTagReleased(FGameplayTag InputTag);
	void	AvilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<URPGInputConfig>	InputConfig;

	UPROPERTY()
	TObjectPtr<URPGAbilitySystemComponent>	RPGAbilitySystemComponent;

	URPGAbilitySystemComponent *GetASC();
public:
	ARPGPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

};
