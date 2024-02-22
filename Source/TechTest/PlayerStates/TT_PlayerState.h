#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TT_PlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnScoreUpdated, float);

UCLASS(Blueprintable)
class ATT_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	FOnScoreUpdated ScoreUpdated;

	FString GetTTPlayerName() const;
	void AddScore(float Amount);

protected:
	UPROPERTY(Replicated, Transient)
		FString PlayerName;

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void OnRep_Score() override;
};
