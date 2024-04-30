


#include "RPGCharacterBase.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "TopDownRPG/AbilitySystem/RPGAbilitySystemComponent.h"

ARPGCharacterBase::ARPGCharacterBase()
{

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	
	PrimaryActorTick.bCanEverTick = true;
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ARPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ARPGCharacterBase::GetCombatSocketLocation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

UAbilitySystemComponent* ARPGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARPGCharacterBase::InitAbilityActorInfo()
{
	
}

void ARPGCharacterBase::ApplyEffectToSelf(const TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ARPGCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultPrimaryAttributes, 1);
	ApplyEffectToSelf(DefaultSecondaryAttributes, 1);
	ApplyEffectToSelf(DefaultVitalAttributes, 1);
}

void ARPGCharacterBase::AddCharacterAbilities()
{
	if (!HasAuthority()) return;
	URPGAbilitySystemComponent *RPGASC = CastChecked<URPGAbilitySystemComponent>(AbilitySystemComponent);
	RPGASC->AddCharacterAbilities(StartupAbilities);
	
}

