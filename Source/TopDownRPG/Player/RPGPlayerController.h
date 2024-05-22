

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "NiagaraSystem.h"
#include "RPGPlayerController.generated.h"


class AMagicCircle;
class UDamageTextComponent;
class URPGInputConfig;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
class URPGAbilitySystemComponent;
class USplineComponent;
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
	UPROPERTY(EditAnywhere, Category="Input")
    TObjectPtr<UInputAction> ShiftAction;

	bool bShiftDown = false;
	void	ShiftPressed() {bShiftDown = true; }
	void	ShiftReleased() {bShiftDown = false; }
	void	Move(const FInputActionValue &InputActionValue);
	
	void	CursorTrace();
	IEnemyInterface	*LastActor;
	IEnemyInterface	*CurrentActor;
	FHitResult	CursorHit;
	

	void	AbilityInputTagPressed(FGameplayTag InputTag);
	void	AbilityInputTagReleased(FGameplayTag InputTag);
	void	AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<URPGInputConfig>	InputConfig;
	

	UPROPERTY()
	TObjectPtr<URPGAbilitySystemComponent>	RPGAbilitySystemComponent;

	URPGAbilitySystemComponent *GetASC();

	//Movement
	FVector	CachedDestination = FVector::ZeroVector;
	float	FollowTime = 0.f;
	float	ShortPressThreshHold = 0.5f;
	bool	bAutoRunning = false;
	bool	bTargeting = false;
	UPROPERTY(EditDefaultsOnly)
	float	AutoRunAcceptanceRadius = 50.f;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent>	Spline;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UNiagaraSystem>		ClickNiagaraSystem;

	void	AutoRun();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent>	DamageTextComponentClass;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMagicCircle>	MagicCircleClass;

	UPROPERTY()
	TObjectPtr<AMagicCircle>	MagicCircle;

	void	UpdateMagicCircleLocation();
public:
	ARPGPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

	UFUNCTION(Client, Reliable)
	void	ShowDamageNumber(float DamageAmount, ACharacter *TargetCharacter, bool bBlockHit, bool bCriticalHit);

	UFUNCTION(BlueprintCallable)
	void	ShowMagicCircle(UMaterialInterface *DecalMaterial = nullptr);

	UFUNCTION(BlueprintCallable)
	void	HideMagicCircle();

	

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

};
