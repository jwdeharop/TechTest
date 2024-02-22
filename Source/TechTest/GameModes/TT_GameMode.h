#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TT_GameMode.generated.h"

UCLASS(Blueprintable)
class ATT_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void SpawnPlayerAtRandomPlayerStart(APlayerController* PlayerController);

private:
	bool GetRandomStartPointTransform(APlayerController* PlayerController, FTransform& Transform) const;
};