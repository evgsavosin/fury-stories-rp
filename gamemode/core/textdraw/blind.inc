/*!
	@brief Текстдравы blind
	@author Found (evg.savosin)
	@date 25.11.2019
*/

new Text: blind_background;

TD_Global_Blind()
{
	blind_background = TextDrawCreate(641.199951, 1.500000, "usebox");
	TextDrawLetterSize(blind_background, 0.000000, 49.378147);
	TextDrawTextSize(blind_background, -2.000000, 0.000000);
	TextDrawAlignment(blind_background, 3);
	TextDrawColor(blind_background, -1);
	TextDrawUseBox(blind_background, true);
	TextDrawBoxColor(blind_background, 255);
	TextDrawSetShadow(blind_background, 0);
	TextDrawSetOutline(blind_background, 0);
	TextDrawBackgroundColor(blind_background, 255);
	TextDrawFont(blind_background, 1);
}

ShowBlind(playerid, states)
{
	if (states)
	{
		TextDrawShowForPlayer(playerid, blind_background);
	}
	else 
	{
		TextDrawHideForPlayer(playerid, blind_background);
	}
}