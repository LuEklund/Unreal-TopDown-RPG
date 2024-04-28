

#pragma once

#include "CoreMinimal.h"
#include "RPGWidgetController.h"
#include "OverlayWidgetController.generated.h"

class URPGUserWidget;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag	MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText	Message = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<URPGUserWidget>	MessageWidget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D>	Image = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealtChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, NewMaxMana);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TOPDOWNRPG_API UOverlayWidgetController : public URPGWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealthChangedSignature	OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealtChangedSignature	OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnManaChangedSignature		OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxManaChangedSignature	OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Messages")
	FMessageWidgetRowSignature	MessageWidgetRowDelegate;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WidgetData")
	TObjectPtr<UDataTable>	MessageWidgetDataTable;
	
	void	HealthChanged(const FOnAttributeChangeData &Data) const;
	void	MaxHealthChanged(const FOnAttributeChangeData &Data) const;
	void	ManaChanged(const FOnAttributeChangeData &Data) const;
	void	MaxManaChanged(const FOnAttributeChangeData &Data) const;

	template<typename T>
	T* GetDataTableRowByTag(UDataTable *DataTable, const FGameplayTag &Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return (DataTable->FindRow<T>(Tag.GetTagName(), TEXT("")));
}
