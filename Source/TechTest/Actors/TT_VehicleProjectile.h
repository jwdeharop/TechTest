#pragma once

#include "CoreMinimal.h"
#include "TT_VehicleProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS(Blueprintable)
class ATT_VehicleProjectile : public AActor
{
	GENERATED_BODY()

public:
	ATT_VehicleProjectile();
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly)
		USphereComponent* SphereComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UStaticMeshComponent* MeshComponent = nullptr;
	UPROPERTY(EditDefaultsOnly)
		UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

private:
	UFUNCTION()
		void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};