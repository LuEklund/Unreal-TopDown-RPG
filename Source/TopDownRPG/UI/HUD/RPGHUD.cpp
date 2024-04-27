


#include "RPGHUD.h"
#include "Blueprint/UserWidget.h"
#include "TopDownRPG/UI/Widget/RPGUserWidget.h"
#include "TopDownRPG/UI/WidgetController/OverlayWidgetController.h"



UOverlayWidgetController* ARPGHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetCOntrollerParams(Params);
		return (OverlayWidgetController);
	}
	return (OverlayWidgetController);
}

void ARPGHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitalized, please fil out BP_RPGHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitalized, please fil out BP_RPGHUD"));
	
	UUserWidget *Widget =  CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<URPGUserWidget>(Widget);
	
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	UOverlayWidgetController	*WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	OverlayWidget->SetWidgetController(WidgetController);
	
	Widget->AddToViewport();
}
