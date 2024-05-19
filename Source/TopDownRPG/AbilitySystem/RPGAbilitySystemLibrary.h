

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Data/CharacterClassInfo.h"
#include "Kismet/BlueprintFunctionLibrary.h"
// #include "TopDownRPG/RPGAbilityTypes.h"
#include "RPGAbilitySystemLibrary.generated.h"

struct FGameplayTag;
class UAbilityInfo;
class ARPGHUD;
class USpellMenuWidgetController;
struct FGameplayEffectContextHandle;
struct FWidgetControllerParams;
struct FDamageEffectParams;
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

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|CharacterClassDefaults")
	static UAbilityInfo *GetAbilityInfo(const UObject *WorldContextObject);

	/*========================
	 * ExeCalc - START
	 ========================*/
	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static bool IsBlockedHit(const FGameplayEffectContextHandle &EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static bool IsCriticalHit(const FGameplayEffectContextHandle &EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static bool IsSuccessfulDebuff(const FGameplayEffectContextHandle &EffectContextHandle);
	
	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static float GetDebuffDamage(const FGameplayEffectContextHandle &EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static float GetDebuffDuration(const FGameplayEffectContextHandle &EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static float GetDebuffFrequency(const FGameplayEffectContextHandle &EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static FGameplayTag GetDamageType(const FGameplayEffectContextHandle &EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static FVector GetDeathImpulse(const FGameplayEffectContextHandle &EffectContextHandle);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static FVector GetKnockbackFOrce(const FGameplayEffectContextHandle &EffectContextHandle);
	
	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static void SetIsBlockedHit(UPARAM(ref) FGameplayEffectContextHandle &EffectContextHandle, bool bInIsBlockedHit);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static void SetIsCriticalHit(UPARAM(ref) FGameplayEffectContextHandle &EffectContextHandle, bool bInIsCriticalHit);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static void SetIsSuccessfulDebuff(UPARAM(ref) FGameplayEffectContextHandle &EffectContextHandle, bool bInSuccessfulDebuff);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static void SetDebuffDamage(UPARAM(ref) FGameplayEffectContextHandle &EffectContextHandle, float InDebuffDamage);
	
	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static void SetDebuffDuration(UPARAM(ref) FGameplayEffectContextHandle &EffectContextHandle, float InDebuffDuration);
	
	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static void SetDebuffFrequency(UPARAM(ref) FGameplayEffectContextHandle &EffectContextHandle, float InDebuffFrequency);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static void SetDamageType(UPARAM(ref) FGameplayEffectContextHandle &EffectContextHandle, const FGameplayTag &InDamageType);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static void SetDeathImpulse(UPARAM(ref) FGameplayEffectContextHandle &EffectContextHandle, const FVector &InImpulse);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|GameplayEffects")
	static void SetKnockbackForce(UPARAM(ref) FGameplayEffectContextHandle &EffectContextHandle, const FVector &InKnockbackForce);
	/*========================
	 * ExeCalc - END
	 ========================*/

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayersWithinRadius(const UObject *WorldContextObject, TArray<AActor*> &OutOverlappingActors, const TArray<AActor*> &ActorsToIgnore, float Radius, const FVector &SphereOrigin);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayMechanics")
	static bool IsNotFriend(AActor *FirstActor, AActor *SecondActor);

	UFUNCTION(BlueprintCallable, Category="RPGAbilitySystemLibrary|DamageEffect")
	static FGameplayEffectContextHandle ApplyDamageEffect(const FDamageEffectParams &DamageEffectParams);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayMechanics")
	static TArray<FRotator>	EvenlySpacedRotators(const FVector& Forward, const FVector &Axis, float Spread, int32 NumRotators);

	UFUNCTION(BlueprintPure, Category="RPGAbilitySystemLibrary|GameplayMechanics")
	static TArray<FVector>	EvenlyRotatedVectors(const FVector& Forward, const FVector &Axis, float Spread, int32 NumVectors);

	static int32	GetXPRewardForClassAndLevel(const UObject *WorldContextObject, ECharacterClass CharacterClass, int32 CharacterLevel);
};
