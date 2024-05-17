

#pragma once

#include "CoreMinimal.h"
#include "RPGWidgetController.h"
#include "GameplayTagContainer.h"
#include "TopDownRPG/RPGGameplayTags.h"
#include "SpellMenuWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSpellGlobeSelectedSignature, bool, bSpendPointsButtonEnabled, bool, bEquipButtonEnabled, FString, DescString, FString, NextLevelDescString);

struct FSelectedAbility
{
	FGameplayTag	Ability = FGameplayTag();
	FGameplayTag	Status = FGameplayTag();
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TOPDOWNRPG_API USpellMenuWidgetController : public URPGWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerStatChangedSignature	SpellPointsChanged;

	UPROPERTY(BlueprintAssignable)
	FSpellGlobeSelectedSignature	SpellGlobeSelectedDelegate;

	UFUNCTION(BlueprintCallable)
	void	SpellGlobeSelected(const FGameplayTag &AbilityTag);

	UFUNCTION(BlueprintCallable)
	void	SpendPointsButtonSelected();

private:
	static void	ShouldEnableButtons(const FGameplayTag &AbilityStatus, int32 SpellPoints, bool &bShouldEnableSpellPointsButton, bool &bShouldEnableEquipButton);
	FSelectedAbility	SelectedAbility = {FRPGGameplayTags::Get().Abilities_None, FRPGGameplayTags::Get().Abilities_Status_Locked};
	int32				CurrentSpellPoints = 0;
};
