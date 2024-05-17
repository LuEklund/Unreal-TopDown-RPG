


#include "RPGGameplayAbility.h"

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
