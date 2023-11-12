/*!
	@brief Текстдравы реновации
	@author Found (evg.savosin)
	@date 25.11.2019
*/

// Variables
new Text: td_renovation,
	PlayerText: td_ren_text					[	MAX_PLAYERS		];
	
	
// Functions
TD_Global_Renovation() 
{
	td_renovation = TextDrawCreate(157.764846, 356.250030, "box");
	TextDrawLetterSize(td_renovation, 0.000000, 3.694108);
	TextDrawTextSize(td_renovation, 237.000000, 0.000000);
	TextDrawAlignment(td_renovation, 1);
	TextDrawColor(td_renovation, -1);
	TextDrawUseBox(td_renovation, 1);
	TextDrawBoxColor(td_renovation, 336860415);
	TextDrawSetShadow(td_renovation, 0);
	TextDrawSetOutline(td_renovation, 0);
	TextDrawBackgroundColor(td_renovation, 255);
	TextDrawFont(td_renovation, 1);
	TextDrawSetProportional(td_renovation, 1);
	TextDrawSetShadow(td_renovation, 0);
}

TD_Player_Renovation(playerid)
{
	td_ren_text[playerid] = CreatePlayerTextDraw(playerid, 161.529373, 360.916595, "Renovation ~g~On~w~~h~~n~Object All: ~r~185~n~~w~~h~Limit: 200");
	PlayerTextDrawLetterSize(playerid, td_ren_text[playerid], 0.153882, 0.835833);
	PlayerTextDrawAlignment(playerid, td_ren_text[playerid], 1);
	PlayerTextDrawColor(playerid, td_ren_text[playerid], -1);
	PlayerTextDrawSetShadow(playerid, td_ren_text[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_ren_text[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, td_ren_text[playerid], 255);
	PlayerTextDrawFont(playerid, td_ren_text[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_ren_text[playerid], 1);
	PlayerTextDrawSetShadow(playerid, td_ren_text[playerid], 0);
}