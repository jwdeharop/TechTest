#include "Components/TT_FiringComponent.h"
#include "Characters/TT_CharacterBase.h"
#include "Libraries/TT_NetLibrary.h"
#include "TechTest.h"

void UTT_FiringComponent::Fire()
{
	// Fire should only be invoked from server because it will spawn the projectile.
	// Also, we only want to fire the projectile if we have a correct owner.
	const bool bIsServer = UTT_NetLibrary::IsServer(this);
	const ATT_CharacterBase* Character = bIsServer ? Cast<ATT_CharacterBase>(GetOwner()) : nullptr;
	if (!Character)
		return;

	// We get the position from where we want to spawn the projectile.
	const FTransform& SpawnPosition = Character->GetProjectileSpawnPositionTransform();
	FActorSpawnParameters Params;
	Params.Owner = GetOwner();
	const AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(Projectile,SpawnPosition,Params);
	if (!SpawnedActor)
	{
		UE_LOG(LogTechTest, Error, TEXT("UTT_FiringComponent::Fire Projectile didnt spawn correclty"));
	}
	
}
