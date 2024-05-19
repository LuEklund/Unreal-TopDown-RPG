

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "TopDownRPG/Interraction/CombatInterface.h"
#include "TopDownRPG/AbilitySystem/Data/CharacterClassInfo.h"
#include "RPGCharacterBase.generated.h"

class UDebuffNiagaraComponent;
class UNiagaraSystem;
class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;

UCLASS(Abstract)
class TOPDOWNRPG_API ARPGCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>>	StartupAbilities;

	UPROPERTY(EditAnywhere, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>>	StartupPassiveAbilities;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<UAnimMontage>	HitReactMontage;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<USkeletalMeshComponent>	Weapon;
	UPROPERTY(EditAnywhere, Category="Combat")
	FName WeaponTipSocketName;
	UPROPERTY(EditAnywhere, Category="Combat")
	FName LeftHandSocketName;
	UPROPERTY(EditAnywhere, Category="Combat")
	FName RightHandSocketName;
	UPROPERTY(EditAnywhere, Category="Combat")
	FName TailSocketName;
	bool bDead = false;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet>			AttributeSet;

	virtual void	InitAbilityActorInfo();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect>	DefaultPrimaryAttributes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect>	DefaultSecondaryAttributes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes")
	TSubclassOf<UGameplayEffect>	DefaultVitalAttributes;

	void	ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	virtual void	InitializeDefaultAttributes() const;

	void	AddCharacterAbilities();

	//Dissolve Effects
	void Dissolve();

	UFUNCTION(BlueprintImplementableEvent)
	void	StartDissolveTimeline(UMaterialInstanceDynamic *DynamicMaterialInstance);

	UFUNCTION(BlueprintImplementableEvent)
	void	StartWeaponDissolveTimeline(UMaterialInstanceDynamic *DynamicMaterialInstance);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance>	DissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance>	WeaponDissolveMaterialInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<UNiagaraSystem>	BloodEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<USoundBase>		DeathSound;

	// Minions

	int32 MinionCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character class defaults")
	ECharacterClass	CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDebuffNiagaraComponent>	BurnDebuffComponent;
	
public:
	ARPGCharacterBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet	*GetAttributeSet() const {return (AttributeSet);}

	//Combat Interface
	virtual UAnimMontage *GetHitReactMontage_Implementation() override;
	virtual void Die(const FVector &DeathImpulse) override;
	FVector	GetCombatSocketLocation_Implementation(const FGameplayTag &MontageTag) override;
	virtual bool IsDead_Implementation() const override;
	virtual AActor *GetAvatar_Implementation() override;
	virtual TArray<FTaggedMontage>	GetAttackMontages_Implementation() override;
	virtual	UNiagaraSystem *GetBloodEffect_Implementation() override;
	virtual FTaggedMontage	GetTaggedMontageByTag_Implementation(const FGameplayTag& MontageTag) override;
	virtual int32 GetMinionCount_Implementation() override;
	virtual void IncrementMinionCount_Implementation(int32 Amount) override;
	virtual ECharacterClass GetCharacterClass_Implementation() override;
	virtual FOnASCRegistered GetOnAscRegisteredDelegate() override;
	virtual	FOnDeath GetOnDeathDelegate() override;
	// END Combat Interface

	FOnASCRegistered	OnAscRegistered;
	FOnDeath			OnDeath;
	
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastHandleDeath(const FVector &DeathImpulse);

	UPROPERTY(EditAnywhere, Category="Combat")
	TArray<FTaggedMontage>	AttackMontages;

};
