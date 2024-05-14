

#pragma once

#include "CoreMinimal.h"
#include "RPGWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
struct FRPGAttributeInfo;
struct FGameplayTag;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FRPGAttributeInfo&, Info);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class TOPDOWNRPG_API UAttributeMenuWidgetController : public URPGWidgetController
{
	GENERATED_BODY()
private:
	void	BroadcastAttributeInfo(const FGameplayTag &AttributeTag, const FGameplayAttribute &Attribute) const;
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo>	AttributeInfo;
	
public:
	virtual void BindCallbacksToDependencies() override;
	virtual void BroadcastInitialValues() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeInfoSignature	AttributeInfoDelegate;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnPlayerStatChangedSignature	AttributePointsChangedDelegate;

	UFUNCTION(BlueprintCallable)
	void	UpgardeAttribute(const FGameplayTag &AttributeTag);

	
};
