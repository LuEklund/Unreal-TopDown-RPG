

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGAbilitySystemLibrary.generated.h"

class UAttributeMenuWidgetController;
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

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController	*GetAttributeMenuWidgetController(const UObject *WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject *WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent *ASC);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject *WorldContextObject, UAbilitySystemComponent *ASC);
};
