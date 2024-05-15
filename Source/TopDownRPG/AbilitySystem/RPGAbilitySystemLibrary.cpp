


#include "RPGAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "TopDownRPG/RPGAbilityTypes.h"
#include "TopDownRPG/Game/RPGGameModeBase.h"
#include "TopDownRPG/Interraction/CombatInterface.h"
#include "TopDownRPG/Player/RPGPlayerState.h"
#include "TopDownRPG/UI/WidgetController/RPGWidgetController.h"
#include "TopDownRPG/UI/HUD/RPGHUD.h"



bool URPGAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject,
	FWidgetControllerParams& OutWCParams, ARPGHUD *&OutRPGHUD)
{
	if (APlayerController *PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		OutRPGHUD = Cast<ARPGHUD>(PC->GetHUD());
		if (OutRPGHUD)
		{
			ARPGPlayerState *PS = PC->GetPlayerState<ARPGPlayerState>();
			UAbilitySystemComponent *ASC = PS->GetAbilitySystemComponent();
			UAttributeSet *AS = PS->GetAttributeSet();
			OutWCParams.AttributeSet = AS;
			OutWCParams.AbilitySystemComponent = ASC;
			OutWCParams.PlayerState = PS;
			OutWCParams.PlayerController = PC;
			return (true);
		}
	}
	return false;
}

UOverlayWidgetController* URPGAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	ARPGHUD	*RPGHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, RPGHUD))
	{
		return (RPGHUD->GetOverlayWidgetController(WCParams));
	}
	return (nullptr);
}

UAttributeMenuWidgetController* URPGAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	ARPGHUD	*RPGHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, RPGHUD))
	{
		return (RPGHUD->GetAttributeMenuWidgetController(WCParams));
	}
	return (nullptr);
}

USpellMenuWidgetController* URPGAbilitySystemLibrary::GetSpellMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	ARPGHUD	*RPGHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, RPGHUD))
	{
		return (RPGHUD->GetSpellMenuWidgetController(WCParams));
	}
	return (nullptr);
}

void URPGAbilitySystemLibrary::InitializeDefaultAttributes(const UObject *WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent *ASC)
{
	 if (ARPGGameModeBase *RPGGM = Cast<ARPGGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject)))
	 {
	 	UCharacterClassInfo *CharacterClassInfo = RPGGM->CharacterClassInfo;
	 	FCharacterDefaultInfo ClassDefaultInfo =  CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

		AActor *AvatarActor = ASC->GetAvatarActor();
	 	
	 	FGameplayEffectContextHandle PrimaryAttributeContextHandle = ASC->MakeEffectContext();
	 	PrimaryAttributeContextHandle.AddSourceObject(AvatarActor);
	 	const FGameplayEffectSpecHandle PrimaryAttributeSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributeContextHandle);
	 	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributeSpecHandle.Data.Get());

	 	FGameplayEffectContextHandle SecondaryAttributeContextHandle = ASC->MakeEffectContext();
	 	SecondaryAttributeContextHandle.AddSourceObject(AvatarActor);
	 	const FGameplayEffectSpecHandle SecondaryAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributeContextHandle);
	 	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributeSpecHandle.Data.Get());

	 	FGameplayEffectContextHandle VitalAttributeContextHandle = ASC->MakeEffectContext();
	 	VitalAttributeContextHandle.AddSourceObject(AvatarActor);
	 	const FGameplayEffectSpecHandle VitalAttributeSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributeContextHandle);
	 	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributeSpecHandle.Data.Get());
	 }
}

void URPGAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	ARPGGameModeBase *RPGGM = Cast<ARPGGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!RPGGM) return ;

	UCharacterClassInfo *CharacterClassInfo = RPGGM->CharacterClassInfo;
	if (CharacterClassInfo == nullptr) return ;

	for (TSubclassOf<UGameplayAbility> AbilityClass  : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterDefaultInfo &DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{
		if (ASC->GetAvatarActor()->Implements<UCombatInterface>())
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, ICombatInterface::Execute_GetPlayerLevel(ASC->GetAvatarActor()));
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

int32 URPGAbilitySystemLibrary::GetXPRewardForClassAndLevel(const UObject* WorldContextObject,
	ECharacterClass CharacterClass, int32 CharacterLevel)
{
	UCharacterClassInfo *CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (CharacterClassInfo == nullptr) return 0;

	const FCharacterDefaultInfo Info = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	const float XPReward = Info.XPReward.GetValueAtLevel(CharacterLevel);

	return (static_cast<int32>(XPReward));
	
}

UCharacterClassInfo* URPGAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	ARPGGameModeBase *RPGGM = Cast<ARPGGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!RPGGM)
	{
		return nullptr;
	}
	
	return (RPGGM->CharacterClassInfo);
}

/*
 * Damage Calculations Getters and Setters 
 */

bool URPGAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FRPGGameplayEffectContext *RPGContext = static_cast<const FRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return RPGContext->IsBlockedHit();
	}
	return false;
}

bool URPGAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FRPGGameplayEffectContext *RPGContext = static_cast<const FRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return RPGContext->IsCriticalHit();
	}
	return false;
}

void URPGAbilitySystemLibrary::SetIsBlockedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if (FRPGGameplayEffectContext *RPGContext = static_cast< FRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		RPGContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void URPGAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	if (FRPGGameplayEffectContext *RPGContext = static_cast< FRPGGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		RPGContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void URPGAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject,
	TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius,
	const FVector& SphereOrigin)
{
	FCollisionQueryParams	SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	TArray<FOverlapResult> Overlaps;
	if (const UWorld *World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		// DrawDebugSphere(World, SphereOrigin, Radius, 16, FColor::Red, false, 4.f);
		for (FOverlapResult &Overlap : Overlaps)
		{
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}
}

bool URPGAbilitySystemLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	const bool bBothArePlayers = FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"));
	const bool bBothAreEnemies = FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy"));
	const bool bFriends = bBothArePlayers || bBothAreEnemies;
	return !bFriends;
}


