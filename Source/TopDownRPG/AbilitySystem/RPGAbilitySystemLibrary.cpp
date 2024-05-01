


#include "RPGAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "TopDownRPG/Game/RPGGameModeBase.h"
#include "TopDownRPG/Player/RPGPlayerState.h"
#include "TopDownRPG/UI/HUD/RPGHUD.h"
#include "TopDownRPG/UI/WidgetController/RPGWidgetController.h"


UOverlayWidgetController* URPGAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController *PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ARPGHUD *RPGHUD = Cast<ARPGHUD>(PC->GetHUD()))
		{
			ARPGPlayerState *PS = PC->GetPlayerState<ARPGPlayerState>();
			UAbilitySystemComponent *ASC = PS->GetAbilitySystemComponent();
			UAttributeSet *AS = PS->GetAttributeSet();
			const FWidgetControllerParams	WidgetControllerParams(PC, PS, ASC, AS);
			return (RPGHUD->GetOverlayWidgetController(WidgetControllerParams));
		}
	}
	return (nullptr);
}

UAttributeMenuWidgetController* URPGAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController *PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ARPGHUD *RPGHUD = Cast<ARPGHUD>(PC->GetHUD()))
		{
			ARPGPlayerState *PS = PC->GetPlayerState<ARPGPlayerState>();
			UAbilitySystemComponent *ASC = PS->GetAbilitySystemComponent();
			UAttributeSet *AS = PS->GetAttributeSet();
			const FWidgetControllerParams	WidgetControllerParams(PC, PS, ASC, AS);
			return (RPGHUD->GetAttributeMenuWidgetController(WidgetControllerParams));
		}
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

void URPGAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	ARPGGameModeBase *RPGGM = Cast<ARPGGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!RPGGM)
	{
		return ;
	}
	
	UCharacterClassInfo *CharacterClassInfo = RPGGM->CharacterClassInfo;
	for (TSubclassOf<UGameplayAbility> AbilityClass  : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
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
