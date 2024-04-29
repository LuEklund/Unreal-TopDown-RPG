

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RPGHUD.generated.h"

class UAttributeMenuWidgetController;
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
	UAttributeMenuWidgetController *GetAttributeMenuWidgetController(const FWidgetControllerParams &Params);

	void InitOverlay(APlayerController *PC, APlayerState *PS, UAbilitySystemComponent *ASC, UAttributeSet *AS);

private:
	UPROPERTY()
	TObjectPtr<URPGUserWidget>	OverlayWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<URPGUserWidget>	OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController>	OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController>	OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController>	AttributeMenuWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController>	AttributeMenuWidgetControllerClass;
	
};
