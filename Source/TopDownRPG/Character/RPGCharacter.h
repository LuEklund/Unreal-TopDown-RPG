

#pragma once

#include "CoreMinimal.h"
#include "RPGCharacterBase.h"
#include "TopDownRPG/Interraction/PlayerInterface.h"
#include "RPGCharacter.generated.h"

class UNiagaraComponent;
class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ARPGCharacter : public ARPGCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()
public:
	ARPGCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	//Player Interface
	virtual	void	AddToXP_Implementation(int32 InXp) override;
	virtual	void	LevelUp_Implementation() override;
	virtual int32	GetXP_Implementation() const override;
	virtual int32	FindLevelForXP_Implementation(int32 InXp) const override;
	virtual int32	GetAttributePointsReward_Implementation(int32 InLevel) const override;
	virtual int32	GetSpellPointsReward_Implementation(int32 InLevel) const override;
	virtual void	AddToPlayerLevel_Implementation(int32 InPlayerLevel) override;
	virtual	void	AddToSpellPoints_Implementation(int32 InSpellPoints) override;
	virtual void	AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	virtual int32	GetAttributePoints_Implementation() const override;
	virtual int32	GetSpellPoints_Implementation() const override;
	virtual void	ShowMagicCircle_Implementation(UMaterialInterface* DecalMaterial) override;
	virtual void	HideMagicCircle_Implementation() override;
	virtual void	SaveProgress_Implementation(const FName& CheckPointTag) override;
	//ENd Player Interface
	
	
	//Combat Interface
	virtual int32 GetPlayerLevel_Implementation() override;
	//End Combat Interface

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraComponent>	LevelUpNiagaraComponent;

	virtual void OnRep_Stunned() override;
	virtual void OnRep_Burned() override;

	void	LoadProgress();
	
private:
	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<USpringArmComponent>	SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category="Camera")
	TObjectPtr<UCameraComponent>	CameraComponent;

	virtual void	InitAbilityActorInfo() override;

	UFUNCTION(NetMulticast, Reliable)
	void	MulticastLevelUpParticles();

};
