


#include "RPGFireBall.h"

void ARPGFireBall::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ARPGFireBall::BeginPlay()
{
	Super::BeginPlay();
	StartOutGoingTimeline();
}
