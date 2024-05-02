


#include "RPGAbilitySystemGlobals.h"

#include "TopDownRPG/RPGAbilityTypes.h"

FGameplayEffectContext* URPGAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FRPGGameplayEffectContext();

}
