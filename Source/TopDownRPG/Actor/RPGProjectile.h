

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "RPGProjectile.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class TOPDOWNRPG_API ARPGProjectile : public AActor
{
	GENERATED_BODY()

private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent>	SphereComponent;

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan = 15.f;
	bool	bHit = false;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UNiagaraSystem>	ImpactEffect;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase>	ImpactSound;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase>	LoopingSound;
	UPROPERTY()
	TObjectPtr<UAudioComponent>	LoopingSoundComponent;
	
protected:
	UFUNCTION()
	void	OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	
public:	
	ARPGProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent>	ProjectileMovementComponent;

	UPROPERTY(BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	FGameplayEffectSpecHandle	DamageEffectSpecHandle;




};
