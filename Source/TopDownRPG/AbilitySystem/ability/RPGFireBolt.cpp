


#include "RPGFireBolt.h"

#include "TopDownRPG/RPGGameplayTags.h"
#include "TopDownRPG/AbilitySystem/RPGAbilitySystemLibrary.h"
#include "TopDownRPG/Actor/RPGProjectile.h"

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

void URPGFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag,
	bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (bIsServer == false)	return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
	FRotator	Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch) Rotation.Pitch = PitchOverride;
	const FVector Forward = Rotation.Vector();

	TArray<FRotator> Rotations = URPGAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);

	for (const FRotator &Rot : Rotations)
	{
		FTransform	SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());

		ARPGProjectile *Projectile = GetWorld()->SpawnActorDeferred<ARPGProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		Projectile->DamageEffectParams = MakeDefaultEffectParamsFromClassDefaults();
	
		Projectile->FinishSpawning(SpawnTransform);
	}
}
