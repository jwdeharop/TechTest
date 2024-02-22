#include "GameStates/TT_GameState.h"

void ATT_GameState::AddPlayerState(APlayerState* PlayerState)
{
	Super::AddPlayerState(PlayerState);
	PlayerStateAdded.Broadcast(PlayerState);
}