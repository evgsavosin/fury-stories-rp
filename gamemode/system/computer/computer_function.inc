/*!
	@brief Функции для системы компьютера
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

// Public functions
Computer_OnPlayerClickTextDraw(playerid, Text: clickedid)
{
	if (clickedid == INVALID_TEXT_DRAW
	|| IsComputerWindowExit(clickedid))
	{
		// Скрываем открытое приложение
		if (GetPVarInt(playerid, "Computer:AppStates"))
		{
			ShowComputerShowApp(playerid, false);
			SelectComputer(playerid);
			return 1;
		}
		
		// Скрываем весь компьютер
		if (GetPVarInt(playerid, "Computer:States"))
		{
			ShowComputer(playerid, false);
			return 1;
		}
	}
	
	return 1;
}

function OnComputerShowApp(playerid, app)
{
	// Скрываем все приложения и их текстдравы
	ShowComputerAppPolice(playerid, false);
	
	if (!app)
	{
		DeletePVar(playerid, "Computer:AppStates");
		return 1;
	}
	
	if (app == COMP_APP_COMPUTER)
	{
		ShowComputerAppThisPC(playerid, true);
	}
	else if (app == COMP_APP_POLICE)
	{
		// Показываем базовый текстдрав
		ShowComputerAppPolice(playerid, true);
		
		// Показываем конкретную страницу
		ShowComputerAppPolice(playerid, true, PTD_COMP_POLICE_MENU_INFO);
	}
	
	SetPVarInt(playerid, "Computer:AppStates", true);
	return 1;
}

// Functions
GetComputerLabelIndex(app)
{
	for (new i; i < sizeof computer_label_list; i++)
	{
		if (computer_label_list[i][c_label] == app)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}