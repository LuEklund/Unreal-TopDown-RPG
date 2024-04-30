

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "RPGInputConfig.h"
#include "RPGInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename  HeldFuncType>
	void	BindAbilityActions(const URPGInputConfig *InputConfig, UserClass *Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void URPGInputComponent::BindAbilityActions(const URPGInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const FRPGInputAction &Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
				UE_LOG(LogTemp, Warning, TEXT("%s: %s, - PressedFunc"), *Action.InputAction->GetName(), *Action.InputTag.GetTagName().ToString());
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
				UE_LOG(LogTemp, Warning, TEXT("%s: %s, - ReleasedFunc"), *Action.InputAction->GetName(), *Action.InputTag.GetTagName().ToString());
			}
			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
				UE_LOG(LogTemp, Warning, TEXT("%s: %s, - HeldFunc"), *Action.InputAction->GetName(), *Action.InputTag.GetTagName().ToString());
			}
		}
	}
}
