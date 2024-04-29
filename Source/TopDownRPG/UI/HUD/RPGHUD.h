

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RPGHUD.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class URPGUserWidget;
/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API ARPGHUD : public AHUD
{
	GENERATED_BODY()

public:
	

	UOverlayWidgetController *GetOverlayWidgetController(const FWidgetControllerParams &Params);

	void InitOverlay(APlayerController *PC, APlayerState *PS, UAbilitySystemComponent *ASC, UAttributeSet *AS);

private:
	UPROPERTY()
	TObjectPtr<URPGUserWidget>	OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<URPGUserWidget>	OverlayWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController>	OverlayWidgetControllerClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController>	OverlayWidgetController;
	
};
