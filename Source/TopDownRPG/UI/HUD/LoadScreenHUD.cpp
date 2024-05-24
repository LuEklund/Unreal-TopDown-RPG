


#include "LoadScreenHUD.h"

#include "Blueprint/UserWidget.h"
#include "TopDownRPG/UI/ViewModel/MVVM_LoadScreen.h"
#include "TopDownRPG/UI/Widget/LoadScreenWidget.h"

void ALoadScreenHUD::BeginPlay()
{
	Super::BeginPlay();

	LoadScreenViewMode = NewObject<UMVVM_LoadScreen>(this, LoadScreenViewModelClass);
	LoadScreenViewMode->InitializeLoadSlots();
	
	LoadScreenWidget = CreateWidget<ULoadScreenWidget>(GetWorld(), LoadScreenWidgetClass);
	LoadScreenWidget->AddToViewport();
	LoadScreenWidget->BlueprintInitializeWidget();
}
