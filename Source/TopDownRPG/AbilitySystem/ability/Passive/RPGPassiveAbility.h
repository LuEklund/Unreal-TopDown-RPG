

#pragma once

#include "CoreMinimal.h"
#include "TopDownRPG/AbilitySystem/ability/RPGGameplayAbility.h"
#include "RPGPassiveAbility.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNRPG_API URPGPassiveAbility : public URPGGameplayAbility
{
	GENERATED_BODY()
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	void	ReceiveDeactivate(const FGameplayTag &AbilityTag);
};
