#include "PlayerStates/TT_PlayerState.h"
#include "Libraries/TT_NetLibrary.h"
#include "TechTest.h"
#include "UnrealNetwork.h"

FString ATT_PlayerState::GetTTPlayerName() const
{
	// This player name should be fill using EOS or the system we want to use.
	return PlayerName.IsEmpty() ? GetName()  : PlayerName;
}

void ATT_PlayerState::AddScore(float Amount)
{
	if (!UTT_NetLibrary::IsServer(this))
	{
		UE_LOG(LogTechTest, Error, TEXT("ATT_PlayerState::AddScore Tring to add score from client."));
		return;
	}

	SetScore(GetScore() + Amount);
	if (!UTT_NetLibrary::IsDedicatedServer(this))
	{
		//Listener server doesnt call On_Rep callbacks.
		OnRep_Score();
	}
}

void ATT_PlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (UTT_NetLibrary::IsServer(this))
	{
		SetScore(0);
	}
}

void ATT_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATT_PlayerState, PlayerName);
}

void ATT_PlayerState::OnRep_Score()
{
	Super::OnRep_Score();
	ScoreUpdated.Broadcast(GetScore());
}
