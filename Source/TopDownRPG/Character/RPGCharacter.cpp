


#include "RPGCharacter.h"

#include "AbilitySystemComponent.h"
#include "NiagaraComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownRPG/RPGGameplayTags.h"
#include "TopDownRPG/AbilitySystem/RPGAbilitySystemComponent.h"
#include "TopDownRPG/AbilitySystem/RPGAbilitySystemLibrary.h"
#include "TopDownRPG/AbilitySystem/RPGAttributeSet.h"
#include "TopDownRPG/AbilitySystem/Data/LevelUpInfo.h"
#include "TopDownRPG/AbilitySystem/Debuff/DebuffNiagaraComponent.h"
#include "TopDownRPG/Game/LoadScreenSaveGame.h"
#include "TopDownRPG/Game/RPGGameInstance.h"
#include "TopDownRPG/Game/RPGGameModeBase.h"
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
	LoadProgress();

	//TODO: LoadWorld Sate
	// if (ARPGGameModeBase *RPGGAmeMode = Cast<ARPGGameModeBase>(UGameplayStatics::GetGameMode(this)))
	// {
	// 	RPGGAmeMode->LoadWo
	// }

}

void ARPGCharacter::LoadProgress()
{
	if (ARPGGameModeBase *RPGGAmeMode = Cast<ARPGGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		ULoadScreenSaveGame *SaveData = RPGGAmeMode->RetrieveInGameSaveData();
		if (SaveData == nullptr) return;
		
		if (SaveData->bFirstTimeLoadIn)
		{
			InitializeDefaultAttributes();
			AddCharacterAbilities();
		}
		else
		{
			//TODO: Load in abilities from disk
			if (ARPGPlayerState *RPGPlayerState = Cast<ARPGPlayerState>(GetPlayerState()))
			{
				RPGPlayerState->SetLevel(SaveData->PlayerLevel);
				RPGPlayerState->SetXP(SaveData->XP);
				RPGPlayerState->SetAttributePoints(SaveData->AttributesPoints);
				RPGPlayerState->SetSpellPoints(SaveData->SpellPoints);
			}
			URPGAbilitySystemLibrary::InitializeDefaultAttributesFromSaveData(this, AbilitySystemComponent, SaveData);
		}
		
	}
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
	RPGPlayerState->AddToLevel(InPlayerLevel);

	if (URPGAbilitySystemComponent	*RPGASC = Cast<URPGAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		RPGASC->UpdateAbilityStatuses(RPGPlayerState->GetPlayerLevel());
	}
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

int32 ARPGCharacter::GetAttributePoints_Implementation() const
{
	ARPGPlayerState *RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	return RPGPlayerState->GetAttributePoints();
}

int32 ARPGCharacter::GetSpellPoints_Implementation() const
{
	ARPGPlayerState *RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	return RPGPlayerState->GetSpellPoints();

}

void ARPGCharacter::ShowMagicCircle_Implementation(UMaterialInterface* DecalMaterial)
{
	if (ARPGPlayerController *RPGPlayerController = Cast<ARPGPlayerController>(GetController()))
	{
		RPGPlayerController->ShowMagicCircle(DecalMaterial);
		RPGPlayerController->bShowMouseCursor = false;
	}
}

void ARPGCharacter::HideMagicCircle_Implementation()
{
	if (ARPGPlayerController *RPGPlayerController = Cast<ARPGPlayerController>(GetController()))
	{
		RPGPlayerController->HideMagicCircle();
		RPGPlayerController->bShowMouseCursor = true;
	}
}

void ARPGCharacter::SaveProgress_Implementation(const FName& CheckPointTag)
{
	if (ARPGGameModeBase *RPGGAmeMode = Cast<ARPGGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		ULoadScreenSaveGame *SaveData = RPGGAmeMode->RetrieveInGameSaveData();
		if (SaveData == nullptr) return;

		SaveData->PlayerStartTag = CheckPointTag;

		if (ARPGPlayerState *RPGPLayerState = Cast<ARPGPlayerState>(GetPlayerState()))
		{
			SaveData->PlayerLevel = RPGPLayerState->GetPlayerLevel();
			SaveData->XP = RPGPLayerState->GetXP();
			SaveData->AttributesPoints = RPGPLayerState->GetAttributePoints();
			SaveData->SpellPoints = RPGPLayerState->GetSpellPoints();
		}
		SaveData->Strength = URPGAttributeSet::GetStrengthAttribute().GetNumericValue(GetAttributeSet());
		SaveData->Intelligence = URPGAttributeSet::GetIntelligenceAttribute().GetNumericValue(GetAttributeSet());
		SaveData->Resilience = URPGAttributeSet::GetResilienceAttribute().GetNumericValue(GetAttributeSet());
		SaveData->Vigor = URPGAttributeSet::GetVigorAttribute().GetNumericValue(GetAttributeSet());

		SaveData->bFirstTimeLoadIn = false;

		RPGGAmeMode->SaveInGameProgressData(SaveData);
	}
}

int32 ARPGCharacter::GetPlayerLevel_Implementation()
{
	const ARPGPlayerState *RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	return RPGPlayerState->GetPlayerLevel();
}

void ARPGCharacter::OnRep_Stunned()
{
	if (URPGAbilitySystemComponent *RPGASC = Cast<URPGAbilitySystemComponent>(AbilitySystemComponent))
	{
		const FRPGGameplayTags &GameplayTags = FRPGGameplayTags::Get();
		FGameplayTagContainer BlockedTags;

		BlockedTags.AddTag(GameplayTags.Player_Block_CursorTrace);
		BlockedTags.AddTag(GameplayTags.Player_Block_InputHeld);
		BlockedTags.AddTag(GameplayTags.Player_Block_InputPressed);
		BlockedTags.AddTag(GameplayTags.Player_Block_InputReleased);
		if (bIsStunned)
		{
			RPGASC->AddLooseGameplayTags(BlockedTags);
			StunDebuffComponent->Activate();
		}
		else
		{
			RPGASC->RemoveLooseGameplayTags(BlockedTags);
			StunDebuffComponent->Deactivate();

		}
	}
	
}

void ARPGCharacter::OnRep_Burned()
{
	if (bIsBurned)
	{
		BurnDebuffComponent->Activate();
	}
	else
	{
		BurnDebuffComponent->Deactivate();
	}
}



void ARPGCharacter::InitAbilityActorInfo()
{
	ARPGPlayerState *RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	AbilitySystemComponent = RPGPlayerState->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(RPGPlayerState, this);
	Cast<URPGAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AttributeSet = RPGPlayerState->GetAttributeSet();
	OnAscRegistered.Broadcast(AbilitySystemComponent);
	AbilitySystemComponent->RegisterGameplayTagEvent(FRPGGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ARPGCharacter::StunTagChanged);

	if (ARPGPlayerController *RPGPlayerController = Cast<ARPGPlayerController>(GetController()))
	{
		if (ARPGHUD *RPGHUD = Cast<ARPGHUD>(RPGPlayerController->GetHUD()))
		{
			RPGHUD->InitOverlay(RPGPlayerController, RPGPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	// InitializeDefaultAttributes();
}
