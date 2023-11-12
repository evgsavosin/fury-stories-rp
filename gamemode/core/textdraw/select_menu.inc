/*!
	@brief Текстдравы меню выбора
	@author Found (evg.savosin)
	@date 25.11.2019
*/

// Defines
#define TD_SELECT_MENU_ARRAY				(	6 	)

// Variables
new Text: td_select_menu					[	3 	],
	PlayerText: td_select_menu_title		[	MAX_PLAYERS		],
	PlayerText: ptd_select_menu				[	MAX_PLAYERS		][	TD_SELECT_MENU_ARRAY 	];

	
// Functions
TD_Global_SelectMenu()
{
	//td_select_menu[0] = TextDrawCreate(500.323394, 151.283309, "box");
	td_select_menu[0] = TextDrawCreate(500.5000, 149.00000, "box");
	TextDrawLetterSize(td_select_menu[0], 0.000000, 20.780);
	//TextDrawTextSize(td_select_menu[0], 609.2000, 0.000000);
	TextDrawTextSize(td_select_menu[0], 608.8000, 0.000000);
	TextDrawAlignment(td_select_menu[0], 1);
	TextDrawColor(td_select_menu[0], -1);
	TextDrawUseBox(td_select_menu[0], 1);
	TextDrawBoxColor(td_select_menu[0], C_TD_BACKGROUND_FIRST);
	TextDrawBackgroundColor(td_select_menu[1], 255);
	TextDrawSetShadow(td_select_menu[0], 0);
	TextDrawSetOutline(td_select_menu[0], 0);
	TextDrawFont(td_select_menu[0], 1);
	TextDrawSetProportional(td_select_menu[0], 1);
	TextDrawSetShadow(td_select_menu[0], 0);
	
	//td_select_menu[1] = TextDrawCreate(584.271850, 325.550842, ">>");
	td_select_menu[1] = TextDrawCreate(582.0000, 325.550842, ">>");
	TextDrawLetterSize(td_select_menu[1], 0.2, 1.016666);
	TextDrawTextSize(td_select_menu[1], 11.000000, 54.0000);
	TextDrawAlignment(td_select_menu[1], 2);
	TextDrawColor(td_select_menu[1], -1);
	TextDrawUseBox(td_select_menu[1], 1);
	TextDrawBoxColor(td_select_menu[1], C_TD_BACKGROUND_FIRST);
	TextDrawSetShadow(td_select_menu[1], 0);
	TextDrawSetOutline(td_select_menu[1], 0);
	TextDrawBackgroundColor(td_select_menu[1], 255);
	TextDrawFont(td_select_menu[1], 2);
	TextDrawSetProportional(td_select_menu[1], 1);
	TextDrawSetShadow(td_select_menu[1], 0);
	TextDrawSetSelectable(td_select_menu[1], true);

	//td_select_menu[2] = TextDrawCreate(527.389221, 325.550811, "<<");
	td_select_menu[2] = TextDrawCreate(528.000, 325.550811, "<<");
	TextDrawLetterSize(td_select_menu[2], 0.2, 1.016666);
	TextDrawTextSize(td_select_menu[2], 13.000000, 54.000000);
	TextDrawAlignment(td_select_menu[2], 2);
	TextDrawColor(td_select_menu[2], -1);
	TextDrawUseBox(td_select_menu[2], 1);
	TextDrawBoxColor(td_select_menu[2], C_TD_BACKGROUND_FIRST);
	TextDrawSetShadow(td_select_menu[2], 0);
	TextDrawSetOutline(td_select_menu[2], 0);
	TextDrawBackgroundColor(td_select_menu[2], 255);
	TextDrawFont(td_select_menu[2], 2);
	TextDrawSetProportional(td_select_menu[2], 1);
	TextDrawSetShadow(td_select_menu[2], 0);
	TextDrawSetSelectable(td_select_menu[2], true);
}


TD_Player_SelectMenu(playerid)
{
	new i = 0,
		Float: x = 502.988250,
		Float: y = 153.249984;
		
	while (i < TD_SELECT_MENU_ARRAY)
	{
		ptd_select_menu[playerid][i] = CreatePlayerTextDraw(playerid, 
			((i % 2) == 1) ? x + 53.759247 : x, 
			y, "" 
		);
		
		PlayerTextDrawLetterSize(playerid, ptd_select_menu[playerid][i], 0.000000, 0.000000);
		PlayerTextDrawTextSize(playerid, ptd_select_menu[playerid][i], 51.000000, 53.000000);
		PlayerTextDrawAlignment(playerid, ptd_select_menu[playerid][i], 1);
		PlayerTextDrawColor(playerid, ptd_select_menu[playerid][i], -1);
		PlayerTextDrawSetShadow(playerid, ptd_select_menu[playerid][i], 0);
		PlayerTextDrawSetOutline(playerid, ptd_select_menu[playerid][i], 0);
		PlayerTextDrawBackgroundColor(playerid, ptd_select_menu[playerid][i], C_TD_BACKGROUND_SECOND);
		PlayerTextDrawFont(playerid, ptd_select_menu[playerid][i], 5);
		PlayerTextDrawSetProportional(playerid, ptd_select_menu[playerid][i], 0);
		PlayerTextDrawSetShadow(playerid, ptd_select_menu[playerid][i], 0);
		PlayerTextDrawSetPreviewModel(playerid, ptd_select_menu[playerid][i], 0);
		PlayerTextDrawSetPreviewRot(playerid, ptd_select_menu[playerid][i], 0.000000, 0.000000, 0.000000, 1.000000);
		PlayerTextDrawSetSelectable(playerid, ptd_select_menu[playerid][i], true);
		
		if (i % 2 == 1)
		{
			y += 55.999146;
		}
		
		i++;
	}
	
	td_select_menu_title[playerid] = CreatePlayerTextDraw(playerid, 554.5, 139.000000, "Furniture List");
	PlayerTextDrawLetterSize(playerid, td_select_menu_title[playerid], 0.159999, 0.841666);
	PlayerTextDrawTextSize(playerid, td_select_menu_title[playerid], 0.000000, 109.000000);
	PlayerTextDrawAlignment(playerid, td_select_menu_title[playerid], 2);
	PlayerTextDrawColor(playerid, td_select_menu_title[playerid], -1);
	PlayerTextDrawUseBox(playerid, td_select_menu_title[playerid], 1);
	PlayerTextDrawBoxColor(playerid, td_select_menu_title[playerid], C_PROJECT);
	PlayerTextDrawSetShadow(playerid, td_select_menu_title[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_select_menu_title[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, td_select_menu_title[playerid], 255);
	PlayerTextDrawFont(playerid, td_select_menu_title[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_select_menu_title[playerid], 1);
	PlayerTextDrawSetShadow(playerid, td_select_menu_title[playerid], 0);
}


ShowSelectMenu(playerid, states, title[] = "Furniture List")
{	
	if (states)
	{
		if (IsInterfaceActive(playerid))
		{
			return 0;
		}
	
		for (new i; i < sizeof td_select_menu; i++)
		{
			TextDrawShowForPlayer(playerid, td_select_menu[i]);
		}
		
		PlayerTextDrawShow(playerid, td_select_menu_title[playerid]);
		PlayerTextDrawSetString(playerid, td_select_menu_title[playerid], title);
	}
	else 
	{
		for (new i; i < sizeof td_select_menu; i++)
		{
			TextDrawHideForPlayer(playerid, td_select_menu[i]);
		}
		
		for (new i; i < TD_SELECT_MENU_ARRAY; i++)
		{
			PlayerTextDrawHide(playerid, ptd_select_menu[playerid][i]);
		}
		
		PlayerTextDrawHide(playerid, td_select_menu_title[playerid]);
	}
	
	SetPVarInt(playerid, "SelectMenu:States", states);
	return 1;
}

