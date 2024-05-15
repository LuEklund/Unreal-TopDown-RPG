

#pragma once

#include "CoreMinimal.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGAbilitySystemLibrary.generated.h"

class ARPGHUD;
class USpellMenuWidgetController;
struct FGameplayEffectContextHandle;
struct FWidgetControllerParams;
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
	static bool	MakeWidgetControllerParams(const UObject *WorldContextObject, FWidgetControllerParams& OutWCParams, ARPGHUD *&OutRPGHUD);
	
	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|WidgetController",  meta=(DefaultToSelf="WorldContextObject"))
	static UOverlayWidgetController	*GetOverlayWidgetController(const UObject *WorldContextObject);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|WidgetController",  meta=(DefaultToSelf="WorldContextObject"))
	static UAttributeMenuWidgetController	*GetAttributeMenuWidgetController(const UObject *WorldContextObject);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|WidgetController",  meta=(DefaultToSelf="WorldContextObject"))
	static USpellMenuWidgetController	*GetSpellMenuWidgetController(const UObject *WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject *WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent *ASC);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject *WorldContextObject, UAbilitySystemComponent *ASC, ECharacterClass CharacterClass);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo *GetCharacterClassInfo(const UObject *WorldContextObject);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle &EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle &EffectContextHandle);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle &EffectContextHandle, bool bInIsBlockedHit);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle &EffectContextHandle, bool bInIsCriticalHit);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayersWithinRadius(const UObject *WorldContextObject, TArray<AActor*> &OutOverlappingActors, const TArray<AActor*> &ActorsToIgnore, float Radius, const FVector &SphereOrigin);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayMechanics")
	static bool IsNotFriend(AActor *FirstActor, AActor *SecondActor);

	static int32	GetXPRewardForClassAndLevel(const UObject *WorldContextObject, ECharacterClass CharacterClass, int32 CharacterLevel);
};
