


#include "RPGFireBolt.h"

#include "TopDownRPG/RPGGameplayTags.h"

FString URPGFireBolt::GetDescription(int32 Level)
{
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return (FString::Printf(TEXT("<Title>FIRE BOLT</> \n\n"
			
								"<Small>Level: </><Level>%i</> \n"
								"<Small>ManaCost: </><ManaCost> %.1f </>\n"
								"<Small>Cooldown: </><Cooldown> %.1f </>\n\n"
								
							   "<Default>Launches a bolt of fire, exploding on impact and dealing: </>"
							   "<Damage>%i</><Default> Fire Damage with a chance to burn</>\n\n"
							   ),
							   Level,
							   ManaCost,
							   Cooldown,
							   ScaledDamage
							   ));
	}
	else
	{
		return (FString::Printf(TEXT("<Title>FIRE BOLT</> \n\n"
			
								"<Small>Level: </><Level>%i</> \n"
								"<Small>ManaCost: </><ManaCost> %.1f </>\n"
								"<Small>Cooldown: </><Cooldown> %.1f </>\n\n"

								
							   "<Default>Launches %i bolts of fire, exploding on impact and dealing: </>"
							   "<Damage>%i</><Default> Fire Damage with a chance to burn</>\n\n"),
							   Level,
							   ManaCost,
							   Cooldown,
							   FMath::Min(Level, NumProjectiles),
							   ScaledDamage
							   ));
	}
}

FString URPGFireBolt::GetNextLevelDescription(int32 Level)
{
	const float ManaCost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = GetCooldown(Level);
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	return (FString::Printf(TEXT("<Title>NEXT LEVEL</> \n\n"
		
								"<Small>Level: </><Level>%i</> \n"
								"<Small>ManaCost: </><ManaCost> %.1f </>\n"
								"<Small>Cooldown: </><Cooldown> %.1f </>\n\n"

								
							  "<Default>Launches %i bolts of fire, exploding on impact and dealing: </>"
							  "<Damage>%i</><Default> Fire Damage with a chance to burn</>\n\n"),
							  Level,
							  ManaCost,
							  Cooldown,
							  FMath::Min(Level, NumProjectiles),
							  ScaledDamage
							  ));
}