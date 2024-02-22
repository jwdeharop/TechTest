#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TT_GameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateAdded, APlayerState*, PlayerState);

UCLASS(Blueprintable)
class ATT_GameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		int32 PointsAmount = 1;

	FOnPlayerStateAdded PlayerStateAdded;

protected:
	virtual void AddPlayerState(APlayerState* PlayerState) override;

};