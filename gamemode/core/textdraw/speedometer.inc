/*!
	@brief Текстдравы спидометра
	@author Found (evg.savosin)
	@date 25.11.2019
*/

// Defines
#define TD_SPEEDOMETER_ARRAY				(	8 	)

// Variables
new Text: td_speedometer					[	3	],
	PlayerText: ptd_speedometer		[	MAX_PLAYERS	][	TD_SPEEDOMETER_ARRAY	];

	
// Functions
ShowSpeedometer(playerid, states)
{
	new i = 0;
		
	if (states)
	{
		for (; i < sizeof td_speedometer; i++)
		{
			TextDrawShowForPlayer(playerid, td_speedometer[i]);
		}
		
		for (i = 0; i < TD_SPEEDOMETER_ARRAY; i++)
		{
			PlayerTextDrawShow(playerid, ptd_speedometer[playerid][i]);
		}
	}
	else 
	{
		for (; i < sizeof td_speedometer; i++)
		{
			TextDrawHideForPlayer(playerid, td_speedometer[i]);
		}
		
		for (i = 0; i < TD_SPEEDOMETER_ARRAY; i++)
		{
			PlayerTextDrawHide(playerid, ptd_speedometer[playerid][i]);
		}
	}
	
	SetPVarInt(playerid, "Speedometer:States", states);
}

TD_Global_Speedometer()
{
	td_speedometer[0] = TextDrawCreate(517.764343, 378.999877, "box");
	TextDrawLetterSize(td_speedometer[0], 0.000000, 5.011763);
	TextDrawTextSize(td_speedometer[0], 615.000000, 0.000000);
	TextDrawAlignment(td_speedometer[0], 1);
	TextDrawColor(td_speedometer[0], -1);
	TextDrawUseBox(td_speedometer[0], 1);
	TextDrawBoxColor(td_speedometer[0], C_TD_BACKGROUND_FIRST);
	TextDrawSetShadow(td_speedometer[0], 0);
	TextDrawSetOutline(td_speedometer[0], 0);
	TextDrawBackgroundColor(td_speedometer[0], 255);
	TextDrawFont(td_speedometer[0], 1);
	TextDrawSetProportional(td_speedometer[0], 1);
	TextDrawSetShadow(td_speedometer[0], 0);

	td_speedometer[1] = TextDrawCreate(522.470458, 384.833404, "box");
	TextDrawLetterSize(td_speedometer[1], 0.000000, 0.776470);
	TextDrawTextSize(td_speedometer[1], 610.000000, 0.000000);
	TextDrawAlignment(td_speedometer[1], 1);
	TextDrawColor(td_speedometer[1], -2139062017);
	TextDrawUseBox(td_speedometer[1], 1);
	TextDrawBoxColor(td_speedometer[1], -2139062241);
	TextDrawSetShadow(td_speedometer[1], 0);
	TextDrawSetOutline(td_speedometer[1], 0);
	TextDrawBackgroundColor(td_speedometer[1], 255);
	TextDrawFont(td_speedometer[1], 1);
	TextDrawSetProportional(td_speedometer[1], 1);
	TextDrawSetShadow(td_speedometer[1], 0);
	
	td_speedometer[2] = TextDrawCreate(596.351196, 384.833557, "MP/H");
	TextDrawLetterSize(td_speedometer[2], 0.140705, 0.748332);
	TextDrawAlignment(td_speedometer[2], 1);
	TextDrawColor(td_speedometer[2], -1);
	TextDrawSetShadow(td_speedometer[2], 0);
	TextDrawSetOutline(td_speedometer[2], 0);
	TextDrawBackgroundColor(td_speedometer[2], 255);
	TextDrawFont(td_speedometer[2], 2);
	TextDrawSetProportional(td_speedometer[2], 1);
	TextDrawSetShadow(td_speedometer[2], 0);
}

TD_Player_Speedometer(playerid)
{
	// 519 - begin
	// 610 - end
	ptd_speedometer[playerid][0] = CreatePlayerTextDraw(playerid, 522.468933, 384.833526, "0");
	PlayerTextDrawLetterSize(playerid, ptd_speedometer[playerid][0], 0.140705, 0.748332);
	PlayerTextDrawTextSize(playerid, ptd_speedometer[playerid][0], 519.000000, 0.000000);
	PlayerTextDrawAlignment(playerid, ptd_speedometer[playerid][0], 1);
	PlayerTextDrawColor(playerid, ptd_speedometer[playerid][0], -1);
	PlayerTextDrawUseBox(playerid, ptd_speedometer[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, ptd_speedometer[playerid][0], C_PROJECT);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, ptd_speedometer[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_speedometer[playerid][0], 255);
	PlayerTextDrawFont(playerid, ptd_speedometer[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, ptd_speedometer[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][0], 0);


	ptd_speedometer[playerid][1] = CreatePlayerTextDraw(playerid, 521.057434, 396.500152, "FUEL: 55.0");
	PlayerTextDrawLetterSize(playerid, ptd_speedometer[playerid][1], 0.140705, 0.748332);
	PlayerTextDrawAlignment(playerid, ptd_speedometer[playerid][1], 1);
	PlayerTextDrawColor(playerid, ptd_speedometer[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, ptd_speedometer[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_speedometer[playerid][1], 255);
	PlayerTextDrawFont(playerid, ptd_speedometer[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, ptd_speedometer[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][1], 0);

	ptd_speedometer[playerid][2] = CreatePlayerTextDraw(playerid, 521.057373, 404.666809, "MILEAGE: 500k");
	PlayerTextDrawLetterSize(playerid, ptd_speedometer[playerid][2], 0.140705, 0.748332);
	PlayerTextDrawAlignment(playerid, ptd_speedometer[playerid][2], 1);
	PlayerTextDrawColor(playerid, ptd_speedometer[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, ptd_speedometer[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_speedometer[playerid][2], 255);
	PlayerTextDrawFont(playerid, ptd_speedometer[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, ptd_speedometer[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][2], 0);

	ptd_speedometer[playerid][3] = CreatePlayerTextDraw(playerid, 578.939208, 398.833435, "ENG");
	PlayerTextDrawLetterSize(playerid, ptd_speedometer[playerid][3], 0.140705, 0.748332);
	PlayerTextDrawTextSize(playerid, ptd_speedometer[playerid][3], 0.000000, 17.000000);
	PlayerTextDrawAlignment(playerid, ptd_speedometer[playerid][3], 2);
	PlayerTextDrawColor(playerid, ptd_speedometer[playerid][3], -1);
	PlayerTextDrawUseBox(playerid, ptd_speedometer[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, ptd_speedometer[playerid][3], -2139062241);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, ptd_speedometer[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_speedometer[playerid][3], 40);
	PlayerTextDrawFont(playerid, ptd_speedometer[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, ptd_speedometer[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][3], 0);

	ptd_speedometer[playerid][4] = CreatePlayerTextDraw(playerid, 578.939208, 412.833435, "LIGHT");
	PlayerTextDrawLetterSize(playerid, ptd_speedometer[playerid][4], 0.140705, 0.754166);
	PlayerTextDrawTextSize(playerid, ptd_speedometer[playerid][4], 0.000000, 17.000000);
	PlayerTextDrawAlignment(playerid, ptd_speedometer[playerid][4], 2);
	PlayerTextDrawColor(playerid, ptd_speedometer[playerid][4], -1);
	PlayerTextDrawUseBox(playerid, ptd_speedometer[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, ptd_speedometer[playerid][4], -2139062241);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, ptd_speedometer[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_speedometer[playerid][4], 40);
	PlayerTextDrawFont(playerid, ptd_speedometer[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, ptd_speedometer[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][4], 0);

	ptd_speedometer[playerid][5] = CreatePlayerTextDraw(playerid, 601.527709, 398.833435, "LOCK");
	PlayerTextDrawLetterSize(playerid, ptd_speedometer[playerid][5], 0.140705, 0.748332);
	PlayerTextDrawTextSize(playerid, ptd_speedometer[playerid][5], 0.000000, 17.000000);
	PlayerTextDrawAlignment(playerid, ptd_speedometer[playerid][5], 2);
	PlayerTextDrawColor(playerid, ptd_speedometer[playerid][5], -1);
	PlayerTextDrawUseBox(playerid, ptd_speedometer[playerid][5], 1);
	PlayerTextDrawBoxColor(playerid, ptd_speedometer[playerid][5], -2139062241);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, ptd_speedometer[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_speedometer[playerid][5], 40);
	PlayerTextDrawFont(playerid, ptd_speedometer[playerid][5], 2);
	PlayerTextDrawSetProportional(playerid, ptd_speedometer[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][5], 0);

	ptd_speedometer[playerid][6] = CreatePlayerTextDraw(playerid, 601.527709, 412.833496, "LIMIT");
	PlayerTextDrawLetterSize(playerid, ptd_speedometer[playerid][6], 0.140705, 0.748332);
	PlayerTextDrawTextSize(playerid, ptd_speedometer[playerid][6], 0.000000, 17.000000);
	PlayerTextDrawAlignment(playerid, ptd_speedometer[playerid][6], 2);
	PlayerTextDrawColor(playerid, ptd_speedometer[playerid][6], -1);
	PlayerTextDrawUseBox(playerid, ptd_speedometer[playerid][6], 1);
	PlayerTextDrawBoxColor(playerid, ptd_speedometer[playerid][6], -2139062241);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, ptd_speedometer[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_speedometer[playerid][6], 40);
	PlayerTextDrawFont(playerid, ptd_speedometer[playerid][6], 2);
	PlayerTextDrawSetProportional(playerid, ptd_speedometer[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][6], 0);

	ptd_speedometer[playerid][7] = CreatePlayerTextDraw(playerid, 520.586791, 412.833526, "TEST");
	PlayerTextDrawLetterSize(playerid, ptd_speedometer[playerid][7], 0.140705, 0.748332);
	PlayerTextDrawAlignment(playerid, ptd_speedometer[playerid][7], 1);
	PlayerTextDrawColor(playerid, ptd_speedometer[playerid][7], -1);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, ptd_speedometer[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_speedometer[playerid][7], 255);
	PlayerTextDrawFont(playerid, ptd_speedometer[playerid][7], 2);
	PlayerTextDrawSetProportional(playerid, ptd_speedometer[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, ptd_speedometer[playerid][7], 0);
}