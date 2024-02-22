#include "UI/TT_WidgetScoreInfo.h"
#include "GameStates/TT_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerStates/TT_PlayerState.h"
#include "TT_WidgetPlayerInfo.h"
#include "VerticalBox.h"

void UTT_WidgetScoreInfo::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ATT_GameState* GameState = Cast<ATT_GameState>(UGameplayStatics::GetGameState(this)))
	{
		GameState->PlayerStateAdded.AddUniqueDynamic(this, &UTT_WidgetScoreInfo::OnPlayerStateAdded);
	}

	CleanAndCreateWidgets();
}

void UTT_WidgetScoreInfo::OnPlayerStateAdded(APlayerState* PlayerState)
{
	CleanAndCreateWidgets();
}

void UTT_WidgetScoreInfo::OnScoreUpdated(float Score)
{
	CleanAndCreateWidgets();
}

void UTT_WidgetScoreInfo::CleanAndCreateWidgets()
{
	if (ATT_GameState* GameState = Cast<ATT_GameState>(UGameplayStatics::GetGameState(this)))
	{
		Players->ClearChildren();
		for (APlayerState* Player : GameState->PlayerArray)
		{
			ATT_PlayerState* TTPlayerState = Cast<ATT_PlayerState>(Player);
			if (!TTPlayerState)
				continue;

			if (!TTPlayerState->ScoreUpdated.IsBoundToObject(this))
			{
				TTPlayerState->ScoreUpdated.AddUObject(this, &UTT_WidgetScoreInfo::OnScoreUpdated);
			}

			if (UTT_WidgetPlayerInfo* PlayerInfoWidget = CreateWidget<UTT_WidgetPlayerInfo>(this, PlayerInfo))
			{
				PlayerInfoWidget->SetPlayerInformation(TTPlayerState);
				Players->AddChild(PlayerInfoWidget);
			}
		}
	}
}
