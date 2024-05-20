


#include "RPGEnemy.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TopDownRPG/RPGGameplayTags.h"
#include "TopDownRPG/TopDownRPG.h"
#include "TopDownRPG/AbilitySystem/RPGAbilitySystemComponent.h"
#include "TopDownRPG/AbilitySystem/RPGAbilitySystemLibrary.h"
#include "TopDownRPG/AbilitySystem/RPGAttributeSet.h"
#include "TopDownRPG/AI/RPGAIController.h"
#include "TopDownRPG/UI/Widget/RPGUserWidget.h"

ARPGEnemy::ARPGEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	
	AttributeSet = CreateDefaultSubobject<URPGAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(RootComponent);

	BaseWalkSpeed = 250.f;
}

void ARPGEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!HasAuthority()) return ;
	RPGAIController = Cast<ARPGAIController>(NewController);
	//Setup behaviour tree
	RPGAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	RPGAIController->RunBehaviorTree(BehaviorTree);
	RPGAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	RPGAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), CharacterClass != ECharacterClass::Warrior);
}

void ARPGEnemy::HighLightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

}

void ARPGEnemy::UnHighLightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 ARPGEnemy::GetPlayerLevel_Implementation()
{
	return Level;
}

void ARPGEnemy::Die(const FVector &DeathImpulse)
{
	SetLifeSpan(LifeSpan);
	if (RPGAIController)
	{
		RPGAIController->GetBlackboardComponent()->SetValueAsBool(FName("Dead"), true);
	}
	Super::Die(DeathImpulse);
}

void ARPGEnemy::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ARPGEnemy::GetCombatTarget_Implementation() const
{
	return (CombatTarget);
}


void ARPGEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

	InitAbilityActorInfo();
	if (HasAuthority())
	{
		URPGAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
	}

	if (URPGUserWidget *RPGUserWidget = Cast<URPGUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		RPGUserWidget->SetWidgetController(this);
	}
	
	if (const URPGAttributeSet *RPGAS = CastChecked<URPGAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData &Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData &Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);
		
		AbilitySystemComponent->RegisterGameplayTagEvent(FRPGGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&ARPGEnemy::HitReactTagChanged
		);

		OnHealthChanged.Broadcast(RPGAS->GetHealth());
		OnMaxHealthChanged.Broadcast(RPGAS->GetMaxHealth());
	}
}

void ARPGEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	if (RPGAIController && RPGAIController->GetBlackboardComponent())
	{
		RPGAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
}


void ARPGEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<URPGAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	AbilitySystemComponent->RegisterGameplayTagEvent(FRPGGameplayTags::Get().Debuff_Stun, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &ARPGEnemy::StunTagChanged);

	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
	OnAscRegistered.Broadcast(AbilitySystemComponent);
}

void ARPGEnemy::InitializeDefaultAttributes() const
{
	URPGAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}

void ARPGEnemy::StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	Super::StunTagChanged(CallbackTag, NewCount);
	if (RPGAIController && RPGAIController->GetBlackboardComponent())
	{
		RPGAIController->GetBlackboardComponent()->SetValueAsBool(FName("Stunned"), bIsStunned);
	}
}


