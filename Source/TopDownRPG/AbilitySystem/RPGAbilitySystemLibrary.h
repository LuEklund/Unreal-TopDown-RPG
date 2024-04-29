

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGAbilitySystemLibrary.generated.h"

class UOverlayWidgetController;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController	*GetOverlayWidgetController(const UObject *WorldContextObject);
};
