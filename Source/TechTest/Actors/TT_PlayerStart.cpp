#include "Actors/TT_PlayerStart.h"

#include "UnrealNetwork.h"

ATT_PlayerStart::ATT_PlayerStart(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bReplicates = true;
	bAlwaysRelevant = true;
}

void ATT_PlayerStart::SetVisited(bool bIsVisited)
{
	bVisited = bIsVisited;
}

bool ATT_PlayerStart::IsVisited() const
{
	return bVisited;
}

void ATT_PlayerStart::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATT_PlayerStart, bVisited);
}
