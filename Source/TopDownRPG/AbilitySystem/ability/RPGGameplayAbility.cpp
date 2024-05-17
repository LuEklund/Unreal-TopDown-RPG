


#include "RPGGameplayAbility.h"

#include "TopDownRPG/AbilitySystem/RPGAttributeSet.h"

FString URPGGameplayAbility::GetDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default> %s, </><Level>%d</>"), L"Default Ability Name - LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum", Level);
}

FString URPGGameplayAbility::GetNextLevelDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default> Next Level, </><Level>%d</><Default> Caouses more damage </>"), Level);
}

FString URPGGameplayAbility::GetLockedDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default> Spell locked until level: </><Level>%d</>"), Level);
}

float URPGGameplayAbility::GetManaCost(const float InLevel) const
{
	float	ManaCost = 0.f;
	if (const UGameplayEffect *CostEffect = GetCostGameplayEffect())
	{
		for (FGameplayModifierInfo Mod : CostEffect->Modifiers)
		{
			if (Mod.Attribute == URPGAttributeSet::GetManaAttribute())
			{
				Mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel, ManaCost);
				break ;
			}
		}
	}
	return ManaCost;
}

float URPGGameplayAbility::GetCooldown(float InLevel) const
{
	float	Cooldown = 0.f;
	if (const UGameplayEffect *CooldownEffect = GetCooldownGameplayEffect())
	{
		CooldownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel, Cooldown);
	}
	return Cooldown;
}
