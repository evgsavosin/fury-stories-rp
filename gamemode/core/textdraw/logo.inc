/**
	@brief Текстдравы логотипа
	@date 07.02.2019
*/

/**
    Variables
*/

new Text: td_logo;

TD_Global_Logo()
{
	td_logo = TextDrawCreate(545.0, 8.892557, "Fury Roleplay");
	TextDrawLetterSize(td_logo, 0.204423, 0.973666);
	TextDrawAlignment(td_logo, 1);
	TextDrawColor(td_logo, -1);
	TextDrawSetShadow(td_logo, 0);
	TextDrawSetOutline(td_logo, 0);
	TextDrawBackgroundColor(td_logo, 255);
	TextDrawFont(td_logo, 2);
	TextDrawSetProportional(td_logo, 1);
	TextDrawSetShadow(td_logo, 0);
}

ShowPlayerLogo(playerid, bool: states)
{
	if (states)
	{
		TextDrawShowForPlayer(playerid, td_logo);
	}
	else 
	{
		TextDrawHideForPlayer(playerid, td_logo);
	}
}