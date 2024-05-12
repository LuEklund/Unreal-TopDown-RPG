


#include "LevelUpInfo.h"

int32 ULevelUpInfo::FindLevelForXP(int32 XP) const
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		//LevelUpInformation[1] = Level 1 Information
		//LevelUpInformation[2] = Level 1 Information
		//Because start counting levels from level 0
		if (LevelUpInformation.Num() - 1 <= Level) return Level;
		if (XP >= LevelUpInformation[Level].LevelUpRequirement)
		{
			++Level;
		}
		else
		{
			bSearching = false;
		}

	}
	return Level;
}