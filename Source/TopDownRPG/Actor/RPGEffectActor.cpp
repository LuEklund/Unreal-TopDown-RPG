


#include "RPGEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/SphereComponent.h"
#include "TopDownRPG/AbilitySystem/RPGAttributeSet.h"

// Sets default values
ARPGEffectActor::ARPGEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
	
}

void ARPGEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface *ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		//TODO: Change this to apply a Gameplay effect. For now, using const_cast as a hack!
		const URPGAttributeSet *RPGAttributeSet = Cast<URPGAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(URPGAttributeSet::StaticClass()));
		URPGAttributeSet *MutableRPGAttributeSet = const_cast<URPGAttributeSet*>(RPGAttributeSet);
		MutableRPGAttributeSet->SetHealth(RPGAttributeSet->GetHealth() + 25.f);
		Destroy();
	}
}

void ARPGEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void ARPGEffectActor::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ARPGEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ARPGEffectActor::EndOverlap);
}



