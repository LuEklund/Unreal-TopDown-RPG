

#pragma once

#include "CoreMinimal.h"
#include "RPGWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API UAttributeMenuWidgetController : public URPGWidgetController
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;
	
};
