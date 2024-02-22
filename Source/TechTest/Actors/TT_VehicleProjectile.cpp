#include "Actors/TT_VehicleProjectile.h"
#include "Characters/TT_CharacterBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameStates/TT_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "Libraries/TT_NetLibrary.h"
#include "PlayerStates/TT_PlayerState.h"

ATT_VehicleProjectile::ATT_VehicleProjectile()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = SphereComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	InitialLifeSpan = 10.f;
	bReplicates = true;
	SetReplicateMovement(true);
}

void ATT_VehicleProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (UTT_NetLibrary::IsServer(this))
	{
		// We will handle the collisions on server.
		SphereComponent->OnComponentHit.AddUniqueDynamic(this, &ATT_VehicleProjectile::OnComponentHit);
	}
}

void ATT_VehicleProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor->IsA<ATT_CharacterBase>())
	{
		const ATT_GameState* GameState = Cast<ATT_GameState>(UGameplayStatics::GetGameState(this));
		const ATT_CharacterBase* CharacterBase = Cast<ATT_CharacterBase>(GetOwner());
		ATT_PlayerState* PlayerState = CharacterBase ? CharacterBase->GetPlayerState<ATT_PlayerState>() : nullptr;

		if (GameState && PlayerState)
		{
			// Handle score here.
			PlayerState->AddScore(GameState->PointsAmount);
		}
	}

	Destroy();
}
