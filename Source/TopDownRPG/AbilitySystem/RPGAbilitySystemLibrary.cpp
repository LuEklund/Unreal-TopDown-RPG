


#include "RPGAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
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
