

#pragma once

#include "CoreMinimal.h"
#include "RPGWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

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
	
};
