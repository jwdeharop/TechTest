#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "TT_WidgetPlayerInfo.generated.h"

class UTextBlock;
class ATT_PlayerState;

UCLASS()
class UTT_WidgetPlayerInfo : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlayerInformation(const ATT_PlayerState* PlayerState);

protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		UTextBlock* PlayerName = nullptr;
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		UTextBlock* PlayerScore = nullptr;
};
