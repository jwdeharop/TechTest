#include "Libraries/TT_NetLibrary.h"

bool UTT_NetLibrary::IsServer(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return World && World->GetNetMode() < ENetMode::NM_Client;
}

bool UTT_NetLibrary::IsDedicatedServer(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return World && World->GetNetMode() == ENetMode::NM_DedicatedServer;
}

bool UTT_NetLibrary::IsClient(const UObject* WorldContextObject)
{
	const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	return World && World->GetNetMode() != ENetMode::NM_DedicatedServer;
}
