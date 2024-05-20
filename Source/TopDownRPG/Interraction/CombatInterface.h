

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TopDownRPG/AbilitySystem/Data/CharacterClassInfo.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"


class UNiagaraSystem;
class UAnimMontage;
class UAbilitySystemComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnASCRegistered, UAbilitySystemComponent*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, AActor*, DeadActor);

USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage	*Montage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag	MontageTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag	SocketTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USoundBase>	ImpactSound = nullptr;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TOPDOWNRPG_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	int32	GetPlayerLevel();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector	GetCombatSocketLocation(const FGameplayTag &MontageTag);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void	UpdateFacingTarget(const FVector &Target);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage *GetHitReactMontage();

	virtual void Die(const FVector &DeathImpulse) = 0;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool	IsDead() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor *GetAvatar();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<FTaggedMontage>	GetAttackMontages();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UNiagaraSystem *GetBloodEffect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FTaggedMontage GetTaggedMontageByTag(const FGameplayTag &MontageTag);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	int32 GetMinionCount();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void IncrementMinionCount(int32 Amount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ECharacterClass	GetCharacterClass();

	virtual FOnASCRegistered	GetOnAscRegisteredDelegate() = 0;
	virtual FOnDeath			GetOnDeathDelegate() = 0;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void	SetInShockLoop(bool bInLoop);
	
};
