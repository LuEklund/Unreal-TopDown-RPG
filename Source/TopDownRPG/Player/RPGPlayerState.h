

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "RPGPlayerState.generated.h"

class ULevelUpInfo;
class UAbilitySystemComponent;
class UAttributeSet;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChange, int32)

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ARPGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32	Level = 1;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_XP)
	int32	XP = 1;

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

	UFUNCTION()
	void OnRep_XP(int32 OldXP);
	
public:
	ARPGPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet	*GetAttributeSet() const {return (AttributeSet);}

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<ULevelUpInfo>	LevelUpInfo;

	FOnPlayerStatChange	OnXPChangedDelegate;
	FOnPlayerStatChange	OnLevelChangedDelegate;

	FORCEINLINE int32 GetPlayerLevel() const {return Level;}
	FORCEINLINE int32 GetXP() const {return XP;}

	void	AddToXP(int32 InXP);
	void	AddToLevel(int32 InLevel);
	
	void	SetToLevel(int32 InLevel);
	void	SetToXP(int32 InXP);


protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet>			AttributeSet;
};
