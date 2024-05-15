


#include "RPGHUD.h"
#include "Blueprint/UserWidget.h"
#include "TopDownRPG/UI/Widget/RPGUserWidget.h"
#include "TopDownRPG/UI/WidgetController/AttributeMenuWidgetController.h"
#include "TopDownRPG/UI/WidgetController/OverlayWidgetController.h"
#include "TopDownRPG/UI/WidgetController/SpellMenuWidgetController.h"


UOverlayWidgetController* ARPGHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(Params);
		OverlayWidgetController->BindCallbacksToDependencies();
	}
	return (OverlayWidgetController);
}

UAttributeMenuWidgetController* ARPGHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& Params)
{
	if (AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(Params);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
	}
	return AttributeMenuWidgetController;
}

USpellMenuWidgetController* ARPGHUD::GetSpellMenuWidgetController(const FWidgetControllerParams& Params)
{
	if (SpellMenuWidgetController == nullptr)
	{
		SpellMenuWidgetController = NewObject<USpellMenuWidgetController>(this, SpellMenuWidgetControllerClass);
		SpellMenuWidgetController->SetWidgetControllerParams(Params);
		SpellMenuWidgetController->BindCallbacksToDependencies();
	}
	return SpellMenuWidgetController;
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
	WidgetController->BroadcastInitialValues();
	
	Widget->AddToViewport();
}
