


#include "RPGCharacter.h"

#include "AbilitySystemComponent.h"
#include "NiagaraComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TopDownRPG/AbilitySystem/RPGAbilitySystemComponent.h"
#include "TopDownRPG/AbilitySystem/Data/LevelUpInfo.h"
#include "TopDownRPG/Player/RPGPlayerController.h"
#include "TopDownRPG/Player/RPGPlayerState.h"
#include "TopDownRPG/UI/HUD/RPGHUD.h"


ARPGCharacter::ARPGCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	// SpringArmComponent->SetUsingAbsoluteLocation(true);
	SpringArmComponent->bDoCollisionTest = false;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;
	
	LevelUpNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("LevelUpNiagaraComponent");
	LevelUpNiagaraComponent->SetupAttachment(GetRootComponent());
	LevelUpNiagaraComponent->bAutoActivate = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CharacterClass = ECharacterClass::Elementalist;
}

void ARPGCharacter::PossessedBy(AController* NewController)
{

	Super::PossessedBy(NewController);

	// Init ability actor info for the: SERVER
	//Attributes
	InitAbilityActorInfo();
	//Abilities
	AddCharacterAbilities();

}

void ARPGCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	// Init ability actor info for the: CLIENT
	InitAbilityActorInfo();

}

void ARPGCharacter::AddToXP_Implementation(int32 InXP)
{
	ARPGPlayerState *RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	RPGPlayerState->AddToXP(InXP);
}

void ARPGCharacter::LevelUp_Implementation()
{
	MulticastLevelUpParticles();
}


void ARPGCharacter::MulticastLevelUpParticles_Implementation()
{
	if (IsValid(LevelUpNiagaraComponent))
	{
		const FVector CameraLocation = CameraComponent->GetComponentLocation();
		const FVector NiagaraSystemLocation = LevelUpNiagaraComponent->GetComponentLocation();
		const FRotator ToCameraRotation = (CameraLocation - NiagaraSystemLocation).Rotation();
		LevelUpNiagaraComponent->SetWorldRotation(ToCameraRotation);
		LevelUpNiagaraComponent->Activate(true);
	}
}


int32 ARPGCharacter::GetXP_Implementation() const
{
	ARPGPlayerState *RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	return RPGPlayerState->GetXP();
}

int32 ARPGCharacter::FindLevelForXP_Implementation(int32 InXp) const
{
	ARPGPlayerState *RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	return RPGPlayerState->LevelUpInfo->FindLevelForXP(InXp);
}

int32 ARPGCharacter::GetAttributePointsReward_Implementation(int32 InLevel) const
{
	const ARPGPlayerState *RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	return RPGPlayerState->LevelUpInfo->LevelUpInformation[InLevel].AttributePointAward;
}

int32 ARPGCharacter::GetSpellPointsReward_Implementation(int32 InLevel) const
{
	const ARPGPlayerState *RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	return RPGPlayerState->LevelUpInfo->LevelUpInformation[InLevel].SpellPointsAward;
}

void ARPGCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevel)
{
	ARPGPlayerState *RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	return RPGPlayerState->AddToLevel(InPlayerLevel);
}

void ARPGCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	ARPGPlayerState *RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	RPGPlayerState->AddToSpellPoints(InSpellPoints);
}

void ARPGCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	ARPGPlayerState *RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	RPGPlayerState->AddToAttributePoints(InAttributePoints);
}

int32 ARPGCharacter::GetPlayerLevel_Implementation()
{
	const ARPGPlayerState *RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	return RPGPlayerState->GetPlayerLevel();
}

void ARPGCharacter::InitAbilityActorInfo()
{
	ARPGPlayerState *RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	AbilitySystemComponent = RPGPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(RPGPlayerState, this);
	Cast<URPGAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AttributeSet = RPGPlayerState->GetAttributeSet();

	if (ARPGPlayerController *RPGPlayerController = Cast<ARPGPlayerController>(GetController()))
	{
		if (ARPGHUD *RPGHUD = Cast<ARPGHUD>(RPGPlayerController->GetHUD()))
		{
			RPGHUD->InitOverlay(RPGPlayerController, RPGPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitializeDefaultAttributes();
}
