/*!
	@brief Текстдравы инвентаря
	@author Found (evg.savosin)
	@date 25.11.2019
*/

// Defines
#define	TD_INVENTORY_SLOTS					(	10 	)

// Variables
new Text: td_inventory						[	 12	],
	PlayerText: td_inv_header				[	MAX_PLAYERS	],
	PlayerText: td_inv_button				[	MAX_PLAYERS	],
	PlayerText: td_inv_slot					[	MAX_PLAYERS	][	TD_INVENTORY_SLOTS],
	PlayerText: td_inv_addslot				[	MAX_PLAYERS	][	TD_INVENTORY_SLOTS];

// Functions
TD_Global_Inv() 
{
	td_inventory[0] = TextDrawCreate(487.246856, 176.983398, "box"); // Gray background
	TextDrawLetterSize(td_inventory[0], 0.000000, 20.553187);
	TextDrawTextSize(td_inventory[0], 546.152587, 0.000000);
	TextDrawAlignment(td_inventory[0], 1);
	TextDrawColor(td_inventory[0], -1);
	TextDrawUseBox(td_inventory[0], 1);
	TextDrawBoxColor(td_inventory[0], C_TD_BACKGROUND_FIRST);
	TextDrawSetShadow(td_inventory[0], 0);
	TextDrawSetOutline(td_inventory[0], 0);
	TextDrawBackgroundColor(td_inventory[0], 858993508);
	TextDrawFont(td_inventory[0], 2);
	TextDrawSetProportional(td_inventory[0], 1);
	TextDrawSetShadow(td_inventory[0], 0);

	td_inventory[1] = TextDrawCreate(555.382019, 176.983398, "box"); // Gray background 188.416793
	TextDrawLetterSize(td_inventory[1], 0.000000, 20.553187);
	TextDrawTextSize(td_inventory[1], 614.038696, 0.000000);
	TextDrawAlignment(td_inventory[1], 1);
	TextDrawColor(td_inventory[1], -1);
	TextDrawUseBox(td_inventory[1], 1);
	TextDrawBoxColor(td_inventory[1], C_TD_BACKGROUND_FIRST);
	TextDrawSetShadow(td_inventory[1], 0);
	TextDrawSetOutline(td_inventory[1], 0);
	TextDrawBackgroundColor(td_inventory[1], 858993508);
	TextDrawFont(td_inventory[1], 2);
	TextDrawSetProportional(td_inventory[1], 1);
	TextDrawSetShadow(td_inventory[1], 0);

	td_inventory[2] = TextDrawCreate(516.682250, 176.983398, "INVENTORY");
	TextDrawLetterSize(td_inventory[2], 0.153411, 0.859166);
	TextDrawTextSize(td_inventory[2], 0.000000, 59.000000);
	TextDrawAlignment(td_inventory[2], 2);
	TextDrawColor(td_inventory[2], -1);
	TextDrawUseBox(td_inventory[2], 1);
	TextDrawBoxColor(td_inventory[2], C_PROJECT);
	TextDrawSetShadow(td_inventory[2], 0);
	TextDrawSetOutline(td_inventory[2], 0);
	TextDrawBackgroundColor(td_inventory[2], 255);
	TextDrawFont(td_inventory[2], 2);
	TextDrawSetProportional(td_inventory[2], 1);
	TextDrawSetShadow(td_inventory[2], 0);

	td_inventory[3] = TextDrawCreate(452.423004, 176.983398, "box"); // Darkgray background
	TextDrawLetterSize(td_inventory[3], 0.000000, 20.553187);
	TextDrawTextSize(td_inventory[3], 484.500000, 0.000000);
	TextDrawAlignment(td_inventory[3], 1);
	TextDrawColor(td_inventory[3], -1);
	TextDrawUseBox(td_inventory[3], 1);
	TextDrawBoxColor(td_inventory[3], 0x151c20FF);
	TextDrawSetShadow(td_inventory[3], 0);
	TextDrawSetOutline(td_inventory[3], 0);
	TextDrawBackgroundColor(td_inventory[3], 858993508);
	TextDrawFont(td_inventory[3], 2);
	TextDrawSetProportional(td_inventory[3], 1);
	TextDrawSetShadow(td_inventory[3], 0);

	td_inventory[4] = TextDrawCreate(468.411651, 194.803100, "INFO");
	TextDrawLetterSize(td_inventory[4], 0.156705, 0.929166);
	TextDrawTextSize(td_inventory[4], 11.000000, 26.000000);
	TextDrawAlignment(td_inventory[4], 2);
	TextDrawColor(td_inventory[4], 0x70818aFF);
	TextDrawUseBox(td_inventory[4], 1);
	TextDrawBoxColor(td_inventory[4], C_TD_BACKGROUND_SECOND);
	TextDrawSetShadow(td_inventory[4], 0);
	TextDrawSetOutline(td_inventory[4], 0);
	TextDrawBackgroundColor(td_inventory[4], 255);
	TextDrawFont(td_inventory[4], 2);
	TextDrawSetProportional(td_inventory[4], 1);
	TextDrawSetShadow(td_inventory[4], 0);
	TextDrawSetSelectable(td_inventory[4], true);

	td_inventory[5] = TextDrawCreate(468.411651, 210.004028, "TRANSF.");
	TextDrawLetterSize(td_inventory[5], 0.156705, 0.929166);
	TextDrawTextSize(td_inventory[5], 11.000000, 26.000000);
	TextDrawAlignment(td_inventory[5], 2);
	TextDrawColor(td_inventory[5], 0x70818aFF);
	TextDrawUseBox(td_inventory[5], 1);
	TextDrawBoxColor(td_inventory[5], C_TD_BACKGROUND_SECOND);
	TextDrawSetShadow(td_inventory[5], 0);
	TextDrawSetOutline(td_inventory[5], 0);
	TextDrawBackgroundColor(td_inventory[5], 255);
	TextDrawFont(td_inventory[5], 2);
	TextDrawSetProportional(td_inventory[5], 1);
	TextDrawSetShadow(td_inventory[5], 0);
	TextDrawSetSelectable(td_inventory[5], true);

	td_inventory[6] = TextDrawCreate(468.411651, 225.304962, "DROP");
	TextDrawLetterSize(td_inventory[6], 0.156705, 0.929166);
	TextDrawTextSize(td_inventory[6], 11.000000, 26.000000);
	TextDrawAlignment(td_inventory[6], 2);
	TextDrawColor(td_inventory[6], 0x70818aFF);
	TextDrawUseBox(td_inventory[6], 1);
	TextDrawBoxColor(td_inventory[6], C_TD_BACKGROUND_SECOND);
	TextDrawSetShadow(td_inventory[6], 0);
	TextDrawSetOutline(td_inventory[6], 0);
	TextDrawBackgroundColor(td_inventory[6], 255);
	TextDrawFont(td_inventory[6], 2);
	TextDrawSetProportional(td_inventory[6], 1);
	TextDrawSetShadow(td_inventory[6], 0);
	TextDrawSetSelectable(td_inventory[6], true);

	td_inventory[7] = TextDrawCreate(468.411651, 255.906828, "REMOVE");
	TextDrawLetterSize(td_inventory[7], 0.156705, 0.929166);
	TextDrawTextSize(td_inventory[7], 11.000000, 26.000000);
	TextDrawAlignment(td_inventory[7], 2);
	TextDrawColor(td_inventory[7], 0x70818aFF);
	TextDrawUseBox(td_inventory[7], 1);
	TextDrawBoxColor(td_inventory[7], C_TD_BACKGROUND_SECOND);
	TextDrawSetShadow(td_inventory[7], 0);
	TextDrawSetOutline(td_inventory[7], 0);
	TextDrawBackgroundColor(td_inventory[7], 255);
	TextDrawFont(td_inventory[7], 2);
	TextDrawSetProportional(td_inventory[7], 1);
	TextDrawSetShadow(td_inventory[7], 0);
	TextDrawSetSelectable(td_inventory[7], true);
	
	td_inventory[8] = TextDrawCreate(468.411651, 240.605895, "UNDRESS");
	TextDrawLetterSize(td_inventory[8], 0.156705, 0.929166);
	TextDrawTextSize(td_inventory[8], 11.000000, 26.000000);
	TextDrawAlignment(td_inventory[8], 2);
	TextDrawColor(td_inventory[8], 0x70818aFF);
	TextDrawUseBox(td_inventory[8], 1);
	TextDrawBoxColor(td_inventory[8], C_TD_BACKGROUND_SECOND);
	TextDrawSetShadow(td_inventory[8], 0);
	TextDrawSetOutline(td_inventory[8], 0);
	TextDrawBackgroundColor(td_inventory[8], 255);
	TextDrawFont(td_inventory[8], 2);
	TextDrawSetProportional(td_inventory[8], 1);
	TextDrawSetShadow(td_inventory[8], 0);
	TextDrawSetSelectable(td_inventory[8], true);

	/*td_inventory[8] = TextDrawCreate(499.340881, 358.919342, "EXIT");
	TextDrawLetterSize(td_inventory[8], 0.184469, 0.952498);
	TextDrawTextSize(td_inventory[8], 11.000000, 94.000000);
	TextDrawAlignment(td_inventory[8], 2);
	TextDrawColor(td_inventory[8], -1);
	TextDrawUseBox(td_inventory[8], 1);
	TextDrawBoxColor(td_inventory[8], 336860415);
	TextDrawSetShadow(td_inventory[8], 0);
	TextDrawSetOutline(td_inventory[8], 0);
	TextDrawBackgroundColor(td_inventory[8], 255);
	TextDrawFont(td_inventory[8], 2);
	TextDrawSetProportional(td_inventory[8], 1);
	TextDrawSetShadow(td_inventory[8], 0);
	TextDrawSetSelectable(td_inventory[8], true);

	td_inventory[9] = TextDrawCreate(569.117187, 359.019348, "<<");
	TextDrawLetterSize(td_inventory[9], 0.156705, 0.952498);
	TextDrawTextSize(td_inventory[9], 11.000000, 27.400032);
	TextDrawAlignment(td_inventory[9], 2);
	TextDrawColor(td_inventory[9], -1);
	TextDrawUseBox(td_inventory[9], 1);
	TextDrawBoxColor(td_inventory[9], 336860415);
	TextDrawSetShadow(td_inventory[9], 0);
	TextDrawSetOutline(td_inventory[9], 0);
	TextDrawBackgroundColor(td_inventory[9], 255);
	TextDrawFont(td_inventory[9], 2);
	TextDrawSetProportional(td_inventory[9], 1);
	TextDrawSetShadow(td_inventory[9], 0);
	TextDrawSetSelectable(td_inventory[9], true);

	td_inventory[10] = TextDrawCreate(600.163757, 359.019317, ">>");
	TextDrawLetterSize(td_inventory[10], 0.156705, 0.952498);
	TextDrawTextSize(td_inventory[10], 11.000000, 27.400032);
	TextDrawAlignment(td_inventory[10], 2);
	TextDrawColor(td_inventory[10], -1);
	TextDrawUseBox(td_inventory[10], 1);
	TextDrawBoxColor(td_inventory[10], 336860415);
	TextDrawSetShadow(td_inventory[10], 0);
	TextDrawSetOutline(td_inventory[10], 0);
	TextDrawBackgroundColor(td_inventory[10], 255);
	TextDrawFont(td_inventory[10], 2);
	TextDrawSetProportional(td_inventory[10], 1);
	TextDrawSetShadow(td_inventory[10], 0);
	TextDrawSetSelectable(td_inventory[10], true);*/
}

TD_Player_Inv(playerid)
{
	td_inv_button[playerid] = CreatePlayerTextDraw(playerid, 468.411651, 179.702178, "(UN)USE");
	PlayerTextDrawLetterSize(playerid, td_inv_button[playerid], 0.156705, 0.929166);
	PlayerTextDrawTextSize(playerid, td_inv_button[playerid], 11.000000, 26.000000);
	PlayerTextDrawAlignment(playerid, td_inv_button[playerid], 2);
	PlayerTextDrawColor(playerid, td_inv_button[playerid], 0x70818aFF);
	PlayerTextDrawUseBox(playerid, td_inv_button[playerid], 1);
	PlayerTextDrawBoxColor(playerid, td_inv_button[playerid], C_TD_BACKGROUND_SECOND);
	PlayerTextDrawSetShadow(playerid, td_inv_button[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_inv_button[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, td_inv_button[playerid], 255);
	PlayerTextDrawFont(playerid, td_inv_button[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_inv_button[playerid], 1);
	PlayerTextDrawSetShadow(playerid, td_inv_button[playerid], 0);
	PlayerTextDrawSetSelectable(playerid, td_inv_button[playerid], true);

	td_inv_header[playerid] = CreatePlayerTextDraw(playerid, 584.737609, 176.983398, "BUY");
	PlayerTextDrawLetterSize(playerid, td_inv_header[playerid], 0.153411, 0.859166);
	PlayerTextDrawTextSize(playerid, td_inv_header[playerid], 0.000000, 59.000000);
	PlayerTextDrawAlignment(playerid, td_inv_header[playerid], 2);
	PlayerTextDrawColor(playerid, td_inv_header[playerid], -1);
	PlayerTextDrawUseBox(playerid, td_inv_header[playerid], 1);
	PlayerTextDrawBoxColor(playerid, td_inv_header[playerid], C_PROJECT);
	PlayerTextDrawSetShadow(playerid, td_inv_header[playerid], 0);
	PlayerTextDrawSetOutline(playerid, td_inv_header[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, td_inv_header[playerid], 255);
	PlayerTextDrawFont(playerid, td_inv_header[playerid], 2);
	PlayerTextDrawSetProportional(playerid, td_inv_header[playerid], 1);
	PlayerTextDrawSetShadow(playerid, td_inv_header[playerid], 0);
	// Player Inventory
	
	new i = 0,
		Float: x = 488.812561,
		Float: y = 190.966659;
		
	while (i < TD_INVENTORY_SLOTS)
	{
		td_inv_slot[playerid][i] = CreatePlayerTextDraw(playerid, 
			((i % 2) == 1) ? x + 28.504211 : x, 
			y, "" 
		);
		PlayerTextDrawLetterSize(playerid, td_inv_slot[playerid][i], 0.000000, 0.000000);
		PlayerTextDrawTextSize(playerid, td_inv_slot[playerid][i], 27.000000, 31.000000);
		PlayerTextDrawAlignment(playerid, td_inv_slot[playerid][i], 1);
		PlayerTextDrawColor(playerid, td_inv_slot[playerid][i], -1);
		PlayerTextDrawSetShadow(playerid, td_inv_slot[playerid][i], 0);
		PlayerTextDrawSetOutline(playerid, td_inv_slot[playerid][i], 0);
		PlayerTextDrawBackgroundColor(playerid, td_inv_slot[playerid][i], C_TD_BACKGROUND_SECOND);
		PlayerTextDrawFont(playerid, td_inv_slot[playerid][i], 5);
		PlayerTextDrawSetProportional(playerid, td_inv_slot[playerid][i], 0);
		PlayerTextDrawSetShadow(playerid, td_inv_slot[playerid][i], 0);
		PlayerTextDrawSetSelectable(playerid, td_inv_slot[playerid][i], true);
		PlayerTextDrawSetPreviewModel(playerid, td_inv_slot[playerid][i], 0);
		PlayerTextDrawSetPreviewRot(playerid, td_inv_slot[playerid][i], 0.000000, 0.000000, 0.000000, 1.000000);
		
		if (i % 2 == 1)
		{
			y += 32.96666;
		}
		
		i++;
	}
	// Player Inventory - end
	
	// Additional Inventory
	
	i = 0;
	x = 556.674804;
	y = 190.966659;
	
	while (i < TD_INVENTORY_SLOTS)
	{
		td_inv_addslot[playerid][i] = CreatePlayerTextDraw(playerid, 
			((i % 2) == 1) ? x + 28.504211 : x, 
			y, "" 
		);
		PlayerTextDrawLetterSize(playerid, td_inv_addslot[playerid][i], 0.000000, 0.000000);
		PlayerTextDrawTextSize(playerid, td_inv_addslot[playerid][i], 27.000000, 31.000000);
		PlayerTextDrawAlignment(playerid, td_inv_addslot[playerid][i], 1);
		PlayerTextDrawColor(playerid, td_inv_addslot[playerid][i], -1);
		PlayerTextDrawSetShadow(playerid, td_inv_addslot[playerid][i], 0);
		PlayerTextDrawSetOutline(playerid, td_inv_addslot[playerid][i], 0);
		PlayerTextDrawBackgroundColor(playerid, td_inv_addslot[playerid][i], C_TD_BACKGROUND_SECOND);
		PlayerTextDrawFont(playerid, td_inv_addslot[playerid][i], 5);
		PlayerTextDrawSetProportional(playerid, td_inv_addslot[playerid][i], 0);
		PlayerTextDrawSetShadow(playerid, td_inv_addslot[playerid][i], 0);
		PlayerTextDrawSetSelectable(playerid, td_inv_addslot[playerid][i], true);
		PlayerTextDrawSetPreviewModel(playerid, td_inv_addslot[playerid][i], 0);
		PlayerTextDrawSetPreviewRot(playerid, td_inv_addslot[playerid][i], 0.000000, 0.000000, 0.000000, 1.000000);
		
		if (i % 2 == 1)
		{
			y += 32.96666;
		}
		
		i++;
	}
	// Additional Inventory - end
}