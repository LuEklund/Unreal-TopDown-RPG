


#include "MapEntrance.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TopDownRPG/Game/RPGGameModeBase.h"
#include "TopDownRPG/Interraction/PlayerInterface.h"

class ARPGGameModeBase;

AMapEntrance::AMapEntrance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Sphere->SetupAttachment(MoveToComponent);
}

void AMapEntrance::HighLightActor_Implementation()
{
	CheckpointMesh->SetRenderCustomDepth(true);
}

void AMapEntrance::LoadActor_Implementation()
{
	// Do nothing when loading a map entrance.
}

void AMapEntrance::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UPlayerInterface>())
	{
		bReached = true;
		if (ARPGGameModeBase *RPGGM = Cast<ARPGGameModeBase>(UGameplayStatics::GetGameMode(this)))
		{
			RPGGM->SaveWorldState(GetWorld(), DestinationMap.ToSoftObjectPath().GetAssetName());
		}
		IPlayerInterface::Execute_SaveProgress(OtherActor, DestinationPlayerStartTag);

		UGameplayStatics::OpenLevelBySoftObjectPtr(this, DestinationMap);
	}
}
