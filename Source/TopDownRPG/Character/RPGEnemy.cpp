


#include "RPGEnemy.h"

#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TopDownRPG/RPGGameplayTags.h"
#include "TopDownRPG/TopDownRPG.h"
#include "TopDownRPG/AbilitySystem/RPGAbilitySystemComponent.h"
#include "TopDownRPG/AbilitySystem/RPGAbilitySystemLibrary.h"
#include "TopDownRPG/AbilitySystem/RPGAttributeSet.h"
#include "TopDownRPG/UI/Widget/RPGUserWidget.h"

ARPGEnemy::ARPGEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<URPGAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(RootComponent);
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

int32 ARPGEnemy::GetPlayerLevel()
{
	return Level;
}

void ARPGEnemy::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}


void ARPGEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

	InitAbilityActorInfo();
	URPGAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent);

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
}


void ARPGEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<URPGAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
	
	InitializeDefaultAttributes();
}

void ARPGEnemy::InitializeDefaultAttributes() const
{
	URPGAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}


