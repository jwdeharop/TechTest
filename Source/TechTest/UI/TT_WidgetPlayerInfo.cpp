#include "UI/TT_WidgetPlayerInfo.h"
#include "PlayerStates/TT_PlayerState.h"
#include "TextBlock.h"

void UTT_WidgetPlayerInfo::SetPlayerInformation(const ATT_PlayerState* PlayerState)
{
	if (!PlayerState)
		return;

	PlayerName->SetText(FText::FromString(PlayerState->GetTTPlayerName()));
	PlayerScore->SetText(FText::AsNumber(PlayerState->GetScore()));
}
