#include "Characters/TT_CharacterVehicle.h"
#include "Components/TT_FiringComponent.h"

ATT_CharacterVehicle::ATT_CharacterVehicle()
{
	ProjectileSpawnPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPosition"));
	ProjectileSpawnPosition->SetupAttachment(RootComponent);
	
	FiringComponent = CreateDefaultSubobject<UTT_FiringComponent>(TEXT("FiringComponent"));
}

FTransform ATT_CharacterVehicle::GetProjectileSpawnPositionTransform() const
{
	return ProjectileSpawnPosition ? ProjectileSpawnPosition->GetComponentTransform() : FTransform();
}

void ATT_CharacterVehicle::Fire()
{
	FiringComponent->Fire();
}
