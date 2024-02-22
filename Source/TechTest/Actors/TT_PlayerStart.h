#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "TT_PlayerStart.generated.h"

UCLASS(Blueprintable)
class ATT_PlayerStart : public APlayerStart
{
	GENERATED_BODY()

public:
	ATT_PlayerStart(const FObjectInitializer& ObjectInitializer);
	void SetVisited(bool bIsVisited);
	bool IsVisited() const;

protected:
	UPROPERTY(Replicated, Transient)
		bool bVisited = false;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};