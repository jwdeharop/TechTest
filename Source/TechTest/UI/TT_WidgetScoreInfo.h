#pragma once

#include "CoreMinimal.h"
#include "UserWidget.h"
#include "TT_WidgetScoreInfo.generated.h"

class UTT_WidgetPlayerInfo;
class UVerticalBox;

UCLASS()
class UTT_WidgetScoreInfo : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
		UVerticalBox* Players;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UTT_WidgetPlayerInfo> PlayerInfo;

private:
	UFUNCTION()
		void OnPlayerStateAdded(APlayerState* PlayerState);

	void OnScoreUpdated(float Score);
	void CleanAndCreateWidgets();

};
