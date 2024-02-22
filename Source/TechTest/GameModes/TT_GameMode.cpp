#include "GameModes/TT_GameMode.h"

#include "Actors/TT_PlayerStart.h"
#include "Controllers/TT_PlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "PlayerStates/TT_PlayerState.h"

void ATT_GameMode::SpawnPlayerAtRandomPlayerStart(APlayerController* PlayerController)
{
	// If the controller already has a pawn, we will destroy it.
	APawn* Pawn = PlayerController ? PlayerController->GetPawn() : nullptr;
	if (Pawn)
	{
		Pawn->Destroy();
	}

	FTransform PlayerStartTransform;
	const bool bRandomLocationFound = GetRandomStartPointTransform(PlayerController, PlayerStartTransform);
	if (bRandomLocationFound; APawn* SpawnedActor = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, PlayerStartTransform))
	{
		PlayerController->Possess(SpawnedActor);
	}
}

bool ATT_GameMode::GetRandomStartPointTransform(APlayerController* PlayerController, FTransform& Transform) const
{
	const ATT_PlayerController* MyPlayerController = Cast<ATT_PlayerController>(PlayerController);
	const ATT_PlayerState* MyPlayerState = MyPlayerController ? MyPlayerController->GetPlayerState<ATT_PlayerState>() : nullptr;
	if (!MyPlayerState)
		return false;

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), FoundActors);
	// We only want to find player starts that matches our team.

	ATT_PlayerStart* FoundActor = Cast<ATT_PlayerStart>(*(FoundActors.FindByPredicate([](const AActor* Actor)
	{
		const ATT_PlayerStart* PlayerStart = Cast<ATT_PlayerStart>(Actor);
		return PlayerStart && !PlayerStart->IsVisited();
	})));

	if (!FoundActor)
		return false;

	FoundActor->SetVisited(true);

	const int32 RandomIndex = UKismetMathLibrary::RandomInteger(FoundActors.Num());
	const AActor* RandomActor = FoundActors[RandomIndex];
	Transform = RandomActor ? RandomActor->GetActorTransform() : Transform;
	return RandomActor != nullptr;
}
