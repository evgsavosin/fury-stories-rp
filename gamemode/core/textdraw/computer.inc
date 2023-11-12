/*!
	@brief Текстдравы компьютера
	@author Found (evg.savosin)
	@date 25.11.2019
*/

// Defines 
#define IsComputerShowed(%0)			GetPVarInt(%0,"Computer:States")
#define IsComputerWindowExit(%0)		(td_computer[TD_COMP_WINDOW_PANEL_EXIT] == %0)

// Constants 
const MAX_COMP_PC_DISK_NAME = 64;

// Structures
enum Text:
{
	TD_COMP_START = 0,
	TD_COMP_SCREEN_BACKGROUND = TD_COMP_START,
	TD_COMP_DESKTOP,
	TD_COMP_DESKTOP_SHADOW,
	TD_COMP_INTERFACE_BOTTOM,
	TD_COMP_INTERFACE_START, // Пуск 
	TD_COMP_INTERFACE_START_LINE1, // Горизонтальная линия пуска
	TD_COMP_INTERFACE_START_LINE2, // Вертикальная линия пуска
	TD_COMP_INTERFACE_DATE,
	TD_COMP_DESKTOP_END = TD_COMP_INTERFACE_DATE,
	
	/*
		
		@brief Окно приложения
		
	*/
	
	TD_COMP_WINDOW_START,
	TD_COMP_WINDOW_BACKGROUND = TD_COMP_WINDOW_START,
	TD_COMP_WINDOW_PANEL,
	TD_COMP_WINDOW_PANEL_EXIT,
	TD_COMP_WINDOW_PANEL_COLLAPSE,
	TD_COMP_WINDOW_PANEL_TURN,
	TD_COMP_WINDOW_PANEL_BACK,
	TD_COMP_WINDOW_END = TD_COMP_WINDOW_PANEL_BACK,
	
	TD_COMP_END
};

new Text: td_computer				[TD_COMP_END];

enum E_COMP_PC_DISK
{
	c_name							[MAX_COMP_PC_DISK_NAME],
	c_is_flash_drive
}

new disk_list[][E_COMP_PC_DISK] =
{
	{"Local Disk (C:)", false},
	{"Local Disk (D:)", false},
	{"USB Flash Drive", true}
};

// Player TextDraw
enum PlayerText:
{
	PTD_COMP_START = 0,
	PTD_COMP_SHADOW = PTD_COMP_START,
	PTD_COMP_WINDOW_TITLE,
	
	/*
	
		@brief This PC
		
	*/
	
	PTD_COMP_PC_START,
	PTD_COMP_PC_SIDEBAR = PTD_COMP_PC_START,
	PTD_COMP_PC_SIDEBAR_TEXT,
	PTD_COMP_PC_TITLE,
	PTD_COMP_PC_DISK_START,
	PTD_COMP_PC_DISK_ICON			[sizeof disk_list],	
	PTD_COMP_PC_DISK_TITLE			[sizeof disk_list],
	PTD_COMP_PC_DISK_BOX			[sizeof disk_list],
	PTD_COMP_PC_DISK_BOX_ACTIVE		[sizeof disk_list],
	PTD_COMP_PC_DISK_END			[sizeof disk_list],
	
	PTD_COMP_PC_END = PTD_COMP_PC_DISK_END,
	
	/*
	
		@brief Police
		
	*/
	
	PTD_COMP_POLICE_START, 
	
	PTD_COMP_POLICE_BACKGROUND = PTD_COMP_POLICE_START,
	
	// Menu
	PTD_COMP_POLICE_MENU_START,
	PTD_COMP_POLICE_MENU_INFO = PTD_COMP_POLICE_MENU_START,
	PTD_COMP_POLICE_MENU_CALLS,
	PTD_COMP_POLICE_MENU_UNITS,
	PTD_COMP_POLICE_MENU_WANTED,
	PTD_COMP_POLICE_MENU_CASES,
	PTD_COMP_POLICE_MENU_END = PTD_COMP_POLICE_MENU_CASES,
	
	// Page: Info
	PTD_COMP_POLICE_INFO_START,
	PTD_COMP_POLICE_PHOTO = PTD_COMP_POLICE_INFO_START,
	PTD_COMP_POLICE_BACKGROUND_2,
	PTD_COMP_POLICE_TEXT_1,
	PTD_COMP_POLICE_TEXT_1_VALUE,
	PTD_COMP_POLICE_TEXT_2,
	PTD_COMP_POLICE_TEXT_3,
	PTD_COMP_POLICE_TEXT_3_VALUE,
	PTD_COMP_POLICE_BOTTOM_MENU,
	PTD_COMP_POLICE_BOTTOM_UNIT,
	PTD_COMP_POLICE_INFO_END = PTD_COMP_POLICE_BOTTOM_UNIT,
	// End page
	
	PTD_COMP_POLICE_END = PTD_COMP_POLICE_INFO_END,
	
	PTD_COMP_END
};

// POLICE: Pages
new PlayerText: ptd_computer		[MAX_PLAYERS][PTD_COMP_END];


// Labels
enum E_PTD_COMP_LABELS
{
	c_label,
	PlayerText: c_label_textdraw_id,
	PlayerText: c_text_textdraw_id
};

new PlayerText: ptd_computer_labels	[MAX_PLAYERS][MAX_COMPUTER_LABELS][E_PTD_COMP_LABELS];

// Data function
Clear:ptd_computer_labels(playerid)
{
	for (new i; i < MAX_COMPUTER_LABELS; i++)
	{
		ptd_computer_labels[playerid][i][c_label] = INVALID_PARAM;
		ptd_computer_labels[playerid][i][c_label_textdraw_id] =
		ptd_computer_labels[playerid][i][c_text_textdraw_id] = INVALID_PTD;
	}
}

// Public function
TD_Global_Computer()
{
	new	Text: td;
	
	td_computer[TD_COMP_SCREEN_BACKGROUND] = td = TextDrawCreate(147.411804, 110.083343, "box"); //  
	TextDrawLetterSize(td, 0.000000, 33.377323);
	TextDrawTextSize(td, 511.504638, 297.000000);
	TextDrawAlignment(td, 1);
	TextDrawColor(td, -1);
	TextDrawUseBox(td, 1);
	TextDrawBoxColor(td, 255);
	TextDrawSetShadow(td, 0);
	TextDrawSetOutline(td, 0);
	TextDrawBackgroundColor(td, 255);
	TextDrawFont(td, 1);
	TextDrawSetProportional(td, 1);
	TextDrawSetShadow(td, 0);

	td_computer[TD_COMP_DESKTOP] = td = TextDrawCreate(152.588317, 117.083328, "box"); //  
	TextDrawLetterSize(td, 0.000000, 30.094121);
	TextDrawTextSize(td, 506.000000, 252.000000);
	TextDrawAlignment(td, 1);
	TextDrawColor(td, -1);
	TextDrawUseBox(td, 1);
	TextDrawBoxColor(td, 1030660351);
	TextDrawSetShadow(td, 0);
	TextDrawSetOutline(td, 0);
	TextDrawBackgroundColor(td, -1);
	TextDrawFont(td, 1);
	TextDrawSetProportional(td, 1);
	TextDrawSetShadow(td, 0);

	td_computer[TD_COMP_DESKTOP_SHADOW] = td = TextDrawCreate(213.705917, 183.483291, "particle:lamp_shad_64"); //  
	TextDrawLetterSize(td, 0.000000, 0.000000);
	TextDrawTextSize(td, 245.000000, 207.000000);
	TextDrawAlignment(td, 1);
	TextDrawColor(td, 1702273279);
	TextDrawSetShadow(td, 0);
	TextDrawSetOutline(td, 0);
	TextDrawBackgroundColor(td, 255);
	TextDrawFont(td, 4);
	TextDrawSetProportional(td, 0);
	TextDrawSetShadow(td, 0);


	td_computer[TD_COMP_INTERFACE_BOTTOM] = td = TextDrawCreate(152.629348, 370.950775, "box"); // Bottom-panel 
	TextDrawLetterSize(td, 0.000000, 1.913056);
	TextDrawTextSize(td, 506.109771, -97.000000);
	TextDrawAlignment(td, 1);
	TextDrawColor(td, -1);
	TextDrawUseBox(td, 1);
	TextDrawBoxColor(td, 216);
	TextDrawSetShadow(td, 0);
	TextDrawSetOutline(td, 0);
	TextDrawBackgroundColor(td, 255);
	TextDrawFont(td, 1);
	TextDrawSetProportional(td, 1);
	TextDrawSetShadow(td, 0);

	td_computer[TD_COMP_INTERFACE_START] = td = TextDrawCreate(156.653152, 372.133392, ""); // Пуск
	TextDrawLetterSize(td, 0.000000, 0.000000);
	TextDrawTextSize(td, 14.000000, 15.000000);
	TextDrawAlignment(td, 1);
	TextDrawColor(td, -1);
	TextDrawSetShadow(td, 0);
	TextDrawSetOutline(td, 0);
	TextDrawBackgroundColor(td, 0);
	TextDrawFont(td, 5);
	TextDrawSetProportional(td, 0);
	TextDrawSetShadow(td, 0);
	TextDrawSetPreviewModel(td, 19201);
	TextDrawSetPreviewRot(td, 90.000000, -20.000000, 0.000000, 0.200000);

	td_computer[TD_COMP_INTERFACE_START_LINE1] = td = TextDrawCreate(160.488265, 382.750000, "box"); //  
	TextDrawLetterSize(td, 0.000000, -0.635294);
	TextDrawTextSize(td, 166.400878, -136.000000);
	TextDrawAlignment(td, 1);
	TextDrawColor(td, -1);
	TextDrawUseBox(td, 1);
	TextDrawBoxColor(td, 255);
	TextDrawSetShadow(td, 0);
	TextDrawSetOutline(td, 0);
	TextDrawBackgroundColor(td, 255);
	TextDrawFont(td, 1);
	TextDrawSetProportional(td, 1);
	TextDrawSetShadow(td, 0);

	td_computer[TD_COMP_INTERFACE_START_LINE2] = td = TextDrawCreate(165.718429, 376.499725, "box"); //  
	TextDrawLetterSize(td, 0.000000, 0.684584);
	TextDrawTextSize(td, 160.999755, -117.000000);
	TextDrawAlignment(td, 1);
	TextDrawColor(td, -1);
	TextDrawUseBox(td, 1);
	TextDrawBoxColor(td, 255);
	TextDrawSetShadow(td, 0);
	TextDrawSetOutline(td, 0);
	TextDrawBackgroundColor(td, 255);
	TextDrawFont(td, 1);
	TextDrawSetProportional(td, 1);
	TextDrawSetShadow(td, 0);

	td_computer[TD_COMP_INTERFACE_DATE] = td = TextDrawCreate(486.923583, 374.133239, "3:05~n~01/01/2019"); //  
	TextDrawLetterSize(td, 0.135996, 0.637498);
	TextDrawAlignment(td, 2);
	TextDrawColor(td, -1);
	TextDrawSetShadow(td, 0);
	TextDrawSetOutline(td, 0);
	TextDrawBackgroundColor(td, 255);
	TextDrawFont(td, 1);
	TextDrawSetProportional(td, 1);
	TextDrawSetShadow(td, 0);

	/*
		
		@brief Window
		
	*/

	td_computer[TD_COMP_WINDOW_BACKGROUND] = td = TextDrawCreate(192.688476, 129.733428, "box"); //  
	TextDrawLetterSize(td, 0.000000, 25.358327);
	TextDrawTextSize(td, 465.100006, 203.000000);
	TextDrawAlignment(td, 1);
	TextDrawColor(td, -1);
	TextDrawUseBox(td, 1);
	TextDrawBoxColor(td, -1);
	TextDrawSetShadow(td, 0);
	TextDrawSetOutline(td, 0);
	TextDrawBackgroundColor(td, 255);
	TextDrawFont(td, 1);
	TextDrawSetProportional(td, 1);
	TextDrawSetShadow(td, 0);

	td_computer[TD_COMP_WINDOW_PANEL] = td = TextDrawCreate(192.488235, 129.333358, "box"); //  
	TextDrawLetterSize(td, 0.000000, 1.058822);
	TextDrawTextSize(td, 465.170257, -111.000000);
	TextDrawAlignment(td, 1);
	TextDrawColor(td, -1);
	TextDrawUseBox(td, 1);
	TextDrawBoxColor(td, 1032912895);
	TextDrawSetShadow(td, 0);
	TextDrawSetOutline(td, 0);
	TextDrawBackgroundColor(td, 255);
	TextDrawFont(td, 1);
	TextDrawSetProportional(td, 1);
	TextDrawSetShadow(td, 0);

	td_computer[TD_COMP_WINDOW_PANEL_EXIT] = td = TextDrawCreate(457.759307, 129.566818, "X"); //  
	TextDrawLetterSize(td, 0.252705, 0.899999);
	TextDrawTextSize(td, 13.000000, 13.000000);
	TextDrawAlignment(td, 2);
	TextDrawColor(td, -1);
	TextDrawSetShadow(td, 0);
	TextDrawSetOutline(td, 0);
	TextDrawBackgroundColor(td, 255);
	TextDrawFont(td, 2);
	TextDrawSetProportional(td, 1);
	TextDrawSetShadow(td, 0);
	TextDrawSetSelectable(td, true);

	td_computer[TD_COMP_WINDOW_PANEL_COLLAPSE] = td = TextDrawCreate(444.199615, 130.150146, "O"); //  
	TextDrawLetterSize(td, 0.252705, 0.899999);
	TextDrawAlignment(td, 2);
	TextDrawColor(td, -1);
	TextDrawSetShadow(td, 0);
	TextDrawSetOutline(td, 0);
	TextDrawBackgroundColor(td, 255);
	TextDrawFont(td, 2);
	TextDrawSetProportional(td, 1);
	TextDrawSetShadow(td, 0);

	td_computer[TD_COMP_WINDOW_PANEL_TURN] = td = TextDrawCreate(428.206146, 129.066787, "-"); //  
	TextDrawLetterSize(td, 0.532939, 1.072499);
	TextDrawAlignment(td, 2);
	TextDrawColor(td, -1);
	TextDrawSetShadow(td, 0);
	TextDrawSetOutline(td, 0);
	TextDrawBackgroundColor(td, 255);
	TextDrawFont(td, 2);
	TextDrawSetProportional(td, 1);
	TextDrawSetShadow(td, 0);
}

TD_Player_Computer(playerid)
{
	new PlayerText: ptd;
	
	ptd_computer[playerid][PTD_COMP_SHADOW] = ptd = CreatePlayerTextDraw(playerid, 20.800048, -100.616348, ""); // Lighter on screen 
	PlayerTextDrawLetterSize(playerid, ptd, 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, ptd, 492.000000, 513.213134);
	PlayerTextDrawAlignment(playerid, ptd, 1);
	PlayerTextDrawColor(playerid, ptd, -247);
	PlayerTextDrawSetShadow(playerid, ptd, 0);
	PlayerTextDrawSetOutline(playerid, ptd, 0);
	PlayerTextDrawBackgroundColor(playerid, ptd, 0);
	PlayerTextDrawFont(playerid, ptd, 5);
	PlayerTextDrawSetProportional(playerid, ptd, 0);
	PlayerTextDrawSetShadow(playerid, ptd, 0);
	PlayerTextDrawSetPreviewModel(playerid, ptd, 2153);
	PlayerTextDrawSetPreviewRot(playerid, ptd, 10.000000, -45.000000, -90.000000, 0.500000);
	
	ptd_computer[playerid][PTD_COMP_WINDOW_TITLE] = ptd = CreatePlayerTextDraw(playerid, 195.882553, 130.500015, "Title"); //  
	PlayerTextDrawLetterSize(playerid, ptd, 0.199055, 0.783333);
	PlayerTextDrawAlignment(playerid, ptd, 1);
	PlayerTextDrawColor(playerid, ptd, -1);
	PlayerTextDrawSetShadow(playerid, ptd, 0);
	PlayerTextDrawSetOutline(playerid, ptd, 0);
	PlayerTextDrawBackgroundColor(playerid, ptd, 255);
	PlayerTextDrawFont(playerid, ptd, 2);
	PlayerTextDrawSetProportional(playerid, ptd, 1);
	PlayerTextDrawSetShadow(playerid, ptd, 0);
}

TD_UpdateComputerDate()
{
	new year,
		month,
		day,
		hour,
		minute;
	
	getdate(year, month, day);
	gettime(hour, minute);
	
	format:g_small_string("%d:%02d~n~%02d/%02d/%04d",
		hour,
		minute,
		day,
		month,
		year
	);
	
	TextDrawSetString(td_computer[TD_COMP_INTERFACE_DATE], g_small_string);
}

TD_Player_ComputerClick(playerid, PlayerText: playertextid)
{
	for (new i; i < MAX_COMPUTER_LABELS; i++)
	{
		if (!IsValidComputerLabel(playerid, i))
		{
			continue;
		}
		
		if (playertextid == ptd_computer_labels[playerid][i][c_label_textdraw_id]
		|| playertextid == ptd_computer_labels[playerid][i][c_text_textdraw_id])
		{
			OnComputerShowApp(
				playerid, 
				ptd_computer_labels[playerid][i][c_label]
			);
			
			break;
		}
	}
	
	/*
	
		@brief Police DB
	
	*/
	
	for (new PlayerText: i = PTD_COMP_POLICE_MENU_START; i <= PTD_COMP_POLICE_MENU_END; i++)
	{
		if (playertextid == ptd_computer[playerid][i])
		{
			ShowComputerAppPolice(playerid, true, i);
		}
	}
}

// Functions
CreateComputerLabel(playerid, label)
{
	const Float: START_X = 158.923812,
		  Float: START_Y = 81.247071,
		  Float: DIFF = 46.302787;
		  
	new index = INVALID_PARAM,
		label_index;
	
	// Ищем свободный индекс
	for (new i; i < MAX_COMPUTER_LABELS; i++)
	{
		if (IsValidComputerLabel(playerid, i))
		{
			continue;
		}
		
		index = i;
		break;
	}
	
	if (index == INVALID_PARAM)
	{
		return 0;
	}
	
	new PlayerText: ptd;

	new Float: x = (START_X + (((index + 1) / 5) * DIFF)),
		Float: y = (START_Y + (((index + 1) % 5) * DIFF));
	
	label_index = GetComputerLabelIndex(label);
	if (label_index == INVALID_PARAM)
	{
		return 0;
	}
	
	// Получаем индекс
	ptd_computer_labels[playerid][index][c_label] = computer_label_list[label_index][c_label];
	
	// Создаем ярлык
	ptd_computer_labels[playerid][index][c_label_textdraw_id] = ptd = CreatePlayerTextDraw(
		playerid, 
		x, 
		y, 
		""
	); // Иконка
	
	PlayerTextDrawLetterSize(playerid, ptd, 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, ptd, 20.000000, 22.000000);
	PlayerTextDrawAlignment(playerid, ptd, 1);
	PlayerTextDrawColor(playerid, ptd, computer_label_list[label_index][c_color]);
	PlayerTextDrawSetShadow(playerid, ptd, 0);
	PlayerTextDrawSetOutline(playerid, ptd, 0);
	PlayerTextDrawBackgroundColor(playerid, ptd, 255);
	PlayerTextDrawFont(playerid, ptd, 5);
	PlayerTextDrawSetProportional(playerid, ptd, 0);
	PlayerTextDrawSetShadow(playerid, ptd, 0);
	PlayerTextDrawSetSelectable(playerid, ptd, true);
	PlayerTextDrawSetPreviewModel(playerid, ptd, 2500);
	PlayerTextDrawSetPreviewRot(playerid, ptd, 0.000000, 0.000000, 0.000000, 0.200000);
	PlayerTextDrawSetSelectable(playerid, ptd, true);
	PlayerTextDrawShow(playerid, ptd);
	
	// Создаем текст
	x += 10.034989;
	y += 24.583824;
	
	ptd_computer_labels[playerid][index][c_text_textdraw_id] = ptd = CreatePlayerTextDraw(
		playerid, 
		x, 
		y, 
		computer_label_list[label_index][c_name]
	); //  Текст
	
	PlayerTextDrawLetterSize(playerid, ptd, 0.138352, 0.759998);
	PlayerTextDrawTextSize(playerid, ptd, 41.000000, 16.489988);
	PlayerTextDrawAlignment(playerid, ptd, 2);
	PlayerTextDrawColor(playerid, ptd, -1);
	PlayerTextDrawUseBox(playerid, ptd, 1);
	PlayerTextDrawBoxColor(playerid, ptd, 11272036);
	PlayerTextDrawSetShadow(playerid, ptd, 0);
	PlayerTextDrawSetOutline(playerid, ptd, 0);
	PlayerTextDrawBackgroundColor(playerid, ptd, 255);
	PlayerTextDrawFont(playerid, ptd, 1);
	PlayerTextDrawSetProportional(playerid, ptd, 1);
	PlayerTextDrawSetShadow(playerid, ptd, 0);
	PlayerTextDrawSetSelectable(playerid, ptd, true);
	PlayerTextDrawShow(playerid, ptd);
	return 1;
}

IsValidComputerLabel(playerid, index)
{
	return (ptd_computer_labels[playerid][index][c_label] != INVALID_PARAM);
}

DestroyComputerLabel(playerid, index)
{
	PlayerTextDrawDestroy(
		playerid, 
		ptd_computer_labels[playerid][index][c_label_textdraw_id]
	);
	
	PlayerTextDrawDestroy(
		playerid, 
		ptd_computer_labels[playerid][index][c_text_textdraw_id]
	);
	
	ptd_computer_labels[playerid][index][c_label] = INVALID_PARAM;
	ptd_computer_labels[playerid][index][c_label_textdraw_id] = 
	ptd_computer_labels[playerid][index][c_text_textdraw_id] = INVALID_PTD;
}

SelectComputer(playerid)
{
	return SelectTextDraw(playerid, 0xECECECFF);
}

ShowComputerDesktop(playerid, bool: states, labels[MAX_COMPUTER_LABELS] = {INVALID_PARAM, ...})
{	
	if (states)
	{
		if (IsInterfaceActive(playerid))
		{
			return 0;
		}
		
		SelectComputer(playerid);
		
		// Показываем текстдравы рабочего стола
		for (new Text: i = TD_COMP_START; i <= TD_COMP_DESKTOP_END; i++)
		{
			TextDrawShowForPlayer(playerid, td_computer[i]);
		}
		
		// Показываем отдельные элементы
		PlayerTextDrawShow(playerid, ptd_computer[playerid][PTD_COMP_SHADOW]);
		
		// Создаем ярлыки на рабочем столе
		for (new i; i < MAX_COMPUTER_LABELS; i++)
		{
			if (labels[i] != INVALID_PARAM)
			{
				CreateComputerLabel(playerid, labels[i]);
			}
		}
	}
	else 
	{
		// Скрываем основные текстдравы рабочего стола
		for (new Text: i = TD_COMP_START; i < TD_COMP_END; i++)
		{
			TextDrawHideForPlayer(playerid, td_computer[i]);
		}
		
		// Скрываем персональные текстдравы рабочего стола
		for (new PlayerText: i = PTD_COMP_START; i < PTD_COMP_END; i++)
		{
			PlayerTextDrawHide(playerid, ptd_computer[playerid][i]);
		}
		
		// Скрываем и удаляем ярлыки
		for (new i; i < MAX_COMPUTER_LABELS; i++)
		{
			if (IsValidComputerLabel(playerid, i))
			{
				DestroyComputerLabel(playerid, i);
			}
		}
	}
	
	SetPVarInt(playerid, "Computer:States", states);
	return 1;
}

ShowComputerWindow(playerid, bool: states, title[] = "")
{
	if (states)
	{
		PlayerTextDrawSetString(playerid, ptd_computer[playerid][PTD_COMP_WINDOW_TITLE], title);
		PlayerTextDrawShow(playerid, ptd_computer[playerid][PTD_COMP_WINDOW_TITLE]);
	
		for (new Text: i = TD_COMP_WINDOW_START; i <= TD_COMP_WINDOW_END; i++)
		{
			TextDrawShowForPlayer(playerid, td_computer[i]);
		}
	}
	else 
	{
		PlayerTextDrawHide(playerid, ptd_computer[playerid][PTD_COMP_WINDOW_TITLE]);
		
		for (new Text: i = TD_COMP_WINDOW_START; i <= TD_COMP_WINDOW_END; i++)
		{
			TextDrawHideForPlayer(playerid, td_computer[i]);
		}
	}
}

ShowComputerAppPolice(playerid, bool: states, PlayerText: page = PlayerText: INVALID_PARAM)
{	
	const MENU_COLOR_ACTIVE = -1,
		  MENU_COLOR_DEFAULT = 255;
		  
	const MENU_BACKGROUND_ACTIVE = 641113855,
		  MENU_BACKGROUND_DEFAULT = -1061109634;
	
	static const police_menu[][] = 
	{
		"INFO",
		"CALLS",
		"UNITS",
		"WANTED",
		"CASE-FILES"
	};
	
	new PlayerText: ptd;

	if (states)
	{
		ShowComputerWindow(playerid, true, "Police DB");
		
		if (page == PlayerText: INVALID_PARAM)
		{
			// Создаем меню
			for (new PlayerText: i = PTD_COMP_POLICE_MENU_START, Float: x = 175.299958, j; i <= PTD_COMP_POLICE_MENU_END; i++, j++)
			{
				x += 42.700103;
				
				ptd_computer[playerid][i] = ptd = CreatePlayerTextDraw(playerid, x, 151.050140, police_menu[j]); //  
				PlayerTextDrawLetterSize(playerid, ptd, 0.155763, 0.841665);
				PlayerTextDrawTextSize(playerid, ptd, 15.000000, 36.000000);
				PlayerTextDrawAlignment(playerid, ptd, 2);
				PlayerTextDrawColor(playerid, ptd, MENU_COLOR_DEFAULT);
				PlayerTextDrawUseBox(playerid, ptd, 1);
				PlayerTextDrawBoxColor(playerid, ptd, MENU_BACKGROUND_DEFAULT);
				PlayerTextDrawSetShadow(playerid, ptd, 0);
				PlayerTextDrawSetOutline(playerid, ptd, 0);
				PlayerTextDrawBackgroundColor(playerid, ptd, 255);
				PlayerTextDrawFont(playerid, ptd, 2);
				PlayerTextDrawSetProportional(playerid, ptd, 1);
				PlayerTextDrawSetShadow(playerid, ptd, 0);
				PlayerTextDrawSetSelectable(playerid, ptd, true);
				PlayerTextDrawShow(playerid, ptd);
			}
		
			ptd_computer[playerid][PTD_COMP_POLICE_BACKGROUND] = ptd = CreatePlayerTextDraw(playerid, 192.758499, 172.000045, "box"); //  
			PlayerTextDrawLetterSize(playerid, ptd, 0.000000, 20.648696);
			PlayerTextDrawTextSize(playerid, ptd, 465.100006, 141.000000);
			PlayerTextDrawAlignment(playerid, ptd, 1);
			PlayerTextDrawColor(playerid, ptd, -1);
			PlayerTextDrawUseBox(playerid, ptd, 1);
			PlayerTextDrawBoxColor(playerid, ptd, -1061109602);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetOutline(playerid, ptd, 0);
			PlayerTextDrawBackgroundColor(playerid, ptd, 255);
			PlayerTextDrawFont(playerid, ptd, 1);
			PlayerTextDrawSetProportional(playerid, ptd, 1);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawShow(playerid, ptd);
		}
		else 
		{
			for (new PlayerText: i = PTD_COMP_POLICE_INFO_START; i <= PTD_COMP_POLICE_INFO_END; i++)
			{
				PlayerTextDrawDestroy(playerid, ptd_computer[playerid][i]);
			}
		}
		
		// Обнуляем активность меню
		for (new PlayerText: i = PTD_COMP_POLICE_MENU_START; i <= PTD_COMP_POLICE_MENU_END; i++)
		{
			PlayerTextDrawColor(playerid, ptd_computer[playerid][i], MENU_COLOR_DEFAULT);
			PlayerTextDrawBoxColor(playerid, ptd_computer[playerid][i], MENU_BACKGROUND_DEFAULT);
			PlayerTextDrawShow(playerid, ptd_computer[playerid][i]);
		}
		
		if (page != PlayerText: INVALID_PARAM)
		{
			PlayerTextDrawColor(playerid, ptd_computer[playerid][page], MENU_COLOR_ACTIVE);
			PlayerTextDrawBoxColor(playerid, ptd_computer[playerid][page], MENU_BACKGROUND_ACTIVE);
			PlayerTextDrawShow(playerid, ptd_computer[playerid][page]);
		}
		
		/*
			
			@brief Page: Info
		
		*/
		
		if (page == PTD_COMP_POLICE_MENU_INFO)
		{	
			ptd_computer[playerid][PTD_COMP_POLICE_PHOTO] = ptd = CreatePlayerTextDraw(playerid, 153.941284, 177.083343, ""); //  
			PlayerTextDrawLetterSize(playerid, ptd, 0.000000, 0.000000);
			PlayerTextDrawTextSize(playerid, ptd, 157.000000, 178.000000);
			PlayerTextDrawAlignment(playerid, ptd, 1);
			PlayerTextDrawColor(playerid, ptd, -1);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetOutline(playerid, ptd, 0);
			PlayerTextDrawBackgroundColor(playerid, ptd, 0);
			PlayerTextDrawFont(playerid, ptd, 5);
			PlayerTextDrawSetProportional(playerid, ptd, 0);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetPreviewModel(playerid, ptd, 0);
			PlayerTextDrawSetPreviewRot(playerid, ptd, 0.000000, 0.000000, 0.000000, 0.800000);
			PlayerTextDrawShow(playerid, ptd);

			ptd_computer[playerid][PTD_COMP_POLICE_BACKGROUND_2] = ptd = CreatePlayerTextDraw(playerid, 197.935089, 254.200149, "box"); //  
			PlayerTextDrawLetterSize(playerid, ptd, 0.000000, 11.142814);
			PlayerTextDrawTextSize(playerid, ptd, 291.000000, 39.000000);
			PlayerTextDrawAlignment(playerid, ptd, 1);
			PlayerTextDrawColor(playerid, ptd, -1);
			PlayerTextDrawUseBox(playerid, ptd, 1);
			PlayerTextDrawBoxColor(playerid, ptd, -656877313);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetOutline(playerid, ptd, 0);
			PlayerTextDrawBackgroundColor(playerid, ptd, 255);
			PlayerTextDrawFont(playerid, ptd, 1);
			PlayerTextDrawSetProportional(playerid, ptd, 1);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawShow(playerid, ptd);

			ptd_computer[playerid][PTD_COMP_POLICE_TEXT_1] = ptd = CreatePlayerTextDraw(playerid, 271.176483, 216.549621, "IN SERVICE:~n~ACCEPTED CALLS:~n~ISSUED TICKETS:~n~ARRESTS:"); //  
			PlayerTextDrawLetterSize(playerid, ptd, 0.201882, 0.899998);
			PlayerTextDrawAlignment(playerid, ptd, 1);
			PlayerTextDrawColor(playerid, ptd, 255);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetOutline(playerid, ptd, 0);
			PlayerTextDrawBackgroundColor(playerid, ptd, 255);
			PlayerTextDrawFont(playerid, ptd, 2);
			PlayerTextDrawSetProportional(playerid, ptd, 1);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawShow(playerid, ptd);
			
			ptd_computer[playerid][PTD_COMP_POLICE_TEXT_1_VALUE] = ptd = CreatePlayerTextDraw(playerid, 380.885559, 216.983062, "1 HOUR~n~0~n~0~n~0"); //  
			PlayerTextDrawLetterSize(playerid, ptd, 0.201882, 0.899998);
			PlayerTextDrawAlignment(playerid, ptd, 1);
			PlayerTextDrawColor(playerid, ptd, -2139062017);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetOutline(playerid, ptd, 0);
			PlayerTextDrawBackgroundColor(playerid, ptd, 255);
			PlayerTextDrawFont(playerid, ptd, 2);
			PlayerTextDrawSetProportional(playerid, ptd, 1);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawShow(playerid, ptd);

			ptd_computer[playerid][PTD_COMP_POLICE_TEXT_2] = ptd = CreatePlayerTextDraw(playerid, 205.294143, 254.186004, "INFORMATION"); //  
			PlayerTextDrawLetterSize(playerid, ptd, 0.193882, 0.917499);
			PlayerTextDrawTextSize(playerid, ptd, 423.000000, -10.000000);
			PlayerTextDrawAlignment(playerid, ptd, 1);
			PlayerTextDrawColor(playerid, ptd, 255);
			PlayerTextDrawUseBox(playerid, ptd, 1);
			PlayerTextDrawBoxColor(playerid, ptd, 58);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetOutline(playerid, ptd, 0);
			PlayerTextDrawBackgroundColor(playerid, ptd, 255);
			PlayerTextDrawFont(playerid, ptd, 2);
			PlayerTextDrawSetProportional(playerid, ptd, 1);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawShow(playerid, ptd);

			ptd_computer[playerid][PTD_COMP_POLICE_TEXT_3] = ptd = CreatePlayerTextDraw(playerid, 203.882476, 267.299621, "EMPLOYEES AT SERVICE:~n~ACTIVE CALLS:~n~UNITS:"); //  
			PlayerTextDrawLetterSize(playerid, ptd, 0.201882, 0.899998);
			PlayerTextDrawAlignment(playerid, ptd, 1);
			PlayerTextDrawColor(playerid, ptd, 255);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetOutline(playerid, ptd, 0);
			PlayerTextDrawBackgroundColor(playerid, ptd, 255);
			PlayerTextDrawFont(playerid, ptd, 2);
			PlayerTextDrawSetProportional(playerid, ptd, 1);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawShow(playerid, ptd);

			ptd_computer[playerid][PTD_COMP_POLICE_TEXT_3_VALUE] = ptd = CreatePlayerTextDraw(playerid, 381.356140, 266.449707, "0~n~0~n~0"); //  
			PlayerTextDrawLetterSize(playerid, ptd, 0.201882, 0.899998);
			PlayerTextDrawAlignment(playerid, ptd, 1);
			PlayerTextDrawColor(playerid, ptd, -2139062017);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetOutline(playerid, ptd, 0);
			PlayerTextDrawBackgroundColor(playerid, ptd, 255);
			PlayerTextDrawFont(playerid, ptd, 2);
			PlayerTextDrawSetProportional(playerid, ptd, 1);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawShow(playerid, ptd);
			
			ptd_computer[playerid][PTD_COMP_POLICE_BOTTOM_MENU] = ptd = CreatePlayerTextDraw(playerid, 192.658798, 344.583404, "box"); //  
			PlayerTextDrawLetterSize(playerid, ptd, 0.000000, 1.529411);
			PlayerTextDrawTextSize(playerid, ptd, 465.230590, -108.000000);
			PlayerTextDrawAlignment(playerid, ptd, 1);
			PlayerTextDrawColor(playerid, ptd, -1);
			PlayerTextDrawUseBox(playerid, ptd, 1);
			PlayerTextDrawBoxColor(playerid, ptd, 205);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetOutline(playerid, ptd, 0);
			PlayerTextDrawBackgroundColor(playerid, ptd, 255);
			PlayerTextDrawFont(playerid, ptd, 1);
			PlayerTextDrawSetProportional(playerid, ptd, 1);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawShow(playerid, ptd);

			ptd_computer[playerid][PTD_COMP_POLICE_BOTTOM_UNIT] = ptd = CreatePlayerTextDraw(playerid, 218.941253, 347.883361, "ADD UNIT"); //  
			PlayerTextDrawLetterSize(playerid, ptd, 0.155763, 0.841665);
			PlayerTextDrawTextSize(playerid, ptd, 15.000000, 36.000000);
			PlayerTextDrawAlignment(playerid, ptd, 2);
			PlayerTextDrawColor(playerid, ptd, -1);
			PlayerTextDrawUseBox(playerid, ptd, 1);
			PlayerTextDrawBoxColor(playerid, ptd, -1061109634);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetOutline(playerid, ptd, 0);
			PlayerTextDrawBackgroundColor(playerid, ptd, 255);
			PlayerTextDrawFont(playerid, ptd, 2);
			PlayerTextDrawSetProportional(playerid, ptd, 1);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetSelectable(playerid, ptd, true);
			PlayerTextDrawShow(playerid, ptd);
		}
		else if (page == PTD_COMP_POLICE_MENU_CALLS)
		{
		}
		else if (page == PTD_COMP_POLICE_MENU_UNITS)
		{
		}
		else if (page == PTD_COMP_POLICE_MENU_WANTED)
		{
		}
		else if (page == PTD_COMP_POLICE_MENU_CASES)
		{
		}
		
		SelectComputer(playerid);
	}
	else
	{
		ShowComputerWindow(playerid, false);
		
		for (new PlayerText: i = PTD_COMP_POLICE_START; i <= PTD_COMP_POLICE_END; i++)
		{
			PlayerTextDrawDestroy(playerid, ptd_computer[playerid][i]);
			ptd_computer[playerid][i] = INVALID_PTD;
		}
	}
}

ShowComputerAppThisPC(playerid, bool: states, bool: flash_drive = false)
{
	new PlayerText: ptd;
	
	if (states)
	{
		ptd_computer[playerid][PTD_COMP_PC_SIDEBAR] = ptd = CreatePlayerTextDraw(playerid, 192.588272, 142.750061, "box"); //  
		PlayerTextDrawLetterSize(playerid, ptd, 0.000000, 23.929409);
		PlayerTextDrawTextSize(playerid, ptd, 274.000000, 177.000000);
		PlayerTextDrawAlignment(playerid, ptd, 1);
		PlayerTextDrawColor(playerid, ptd, -1);
		PlayerTextDrawUseBox(playerid, ptd, 1);
		PlayerTextDrawBoxColor(playerid, ptd, 51);
		PlayerTextDrawSetShadow(playerid, ptd, 0);
		PlayerTextDrawSetOutline(playerid, ptd, 0);
		PlayerTextDrawBackgroundColor(playerid, ptd, 255);
		PlayerTextDrawFont(playerid, ptd, 1);
		PlayerTextDrawSetProportional(playerid, ptd, 1);
		PlayerTextDrawSetShadow(playerid, ptd, 0);
		
		ptd_computer[playerid][PTD_COMP_PC_SIDEBAR_TEXT] = ptd = CreatePlayerTextDraw(playerid, 197.835189, 146.833343, "Quick Access~n~~n~My Drive~n~~n~Libraries~n~~n~Desktop"); //  
		PlayerTextDrawLetterSize(playerid, ptd, 0.213176, 0.899999);
		PlayerTextDrawAlignment(playerid, ptd, 1);
		PlayerTextDrawColor(playerid, ptd, 136);
		PlayerTextDrawSetShadow(playerid, ptd, 0);
		PlayerTextDrawSetOutline(playerid, ptd, 0);
		PlayerTextDrawBackgroundColor(playerid, ptd, 255);
		PlayerTextDrawFont(playerid, ptd, 2);
		PlayerTextDrawSetProportional(playerid, ptd, 1);
		PlayerTextDrawSetShadow(playerid, ptd, 0);
		
		ptd_computer[playerid][PTD_COMP_PC_TITLE] = ptd = CreatePlayerTextDraw(playerid, 280.188140, 145.083312, "Devices and Drives"); //  
		PlayerTextDrawLetterSize(playerid, ptd, 0.213176, 0.899999);
		PlayerTextDrawAlignment(playerid, ptd, 1);
		PlayerTextDrawColor(playerid, ptd, 6328063);
		PlayerTextDrawSetShadow(playerid, ptd, 0);
		PlayerTextDrawSetOutline(playerid, ptd, 0);
		PlayerTextDrawBackgroundColor(playerid, ptd, 255);
		PlayerTextDrawFont(playerid, ptd, 2);
		PlayerTextDrawSetProportional(playerid, ptd, 1);
		PlayerTextDrawSetShadow(playerid, ptd, 0);

		for (new i = _: PTD_COMP_PC_DISK_START, Float: y = 120.18051; i < _: PTD_COMP_PC_DISK_END; i++)
		{
			if (!flash_drive && disk_list[i][c_is_flash_drive])
			{
				continue;
			}
			
			y += 45.902802;
			
			ptd_computer[playerid][PTD_COMP_PC_DISK_ICON][i] = ptd = CreatePlayerTextDraw(playerid, 280.058837, y, ""); // Local Disk Icon 
			PlayerTextDrawLetterSize(playerid, ptd, 0.000000, 0.000000);
			PlayerTextDrawTextSize(playerid, ptd, 30.120025, 30.110002);
			PlayerTextDrawAlignment(playerid, ptd, 1);
			PlayerTextDrawColor(playerid, ptd, -1);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetOutline(playerid, ptd, 0);
			PlayerTextDrawBackgroundColor(playerid, ptd, 255);
			PlayerTextDrawFont(playerid, ptd, 5);
			PlayerTextDrawSetProportional(playerid, ptd, 0);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetPreviewModel(playerid, ptd, 2500);
			PlayerTextDrawSetPreviewRot(playerid, ptd, 0.000000, 0.000000, 0.000000, 0.200000);

			ptd_computer[playerid][PTD_COMP_PC_DISK_TITLE][i] = ptd = CreatePlayerTextDraw(playerid, 313.600067, y, disk_list[i][c_name]); //  
			PlayerTextDrawLetterSize(playerid, ptd, 0.161882, 0.684166);
			PlayerTextDrawAlignment(playerid, ptd, 1);
			PlayerTextDrawColor(playerid, ptd, 255);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetOutline(playerid, ptd, 0);
			PlayerTextDrawBackgroundColor(playerid, ptd, 255);
			PlayerTextDrawFont(playerid, ptd, 2);
			PlayerTextDrawSetProportional(playerid, ptd, 1);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			
			ptd_computer[playerid][PTD_COMP_PC_DISK_BOX][i] = ptd = CreatePlayerTextDraw(playerid, 314.941223, y + 17.099961, "box"); // BoxGray 
			PlayerTextDrawLetterSize(playerid, ptd, 0.000000, 1.199998);
			PlayerTextDrawTextSize(playerid, ptd, 434.000000, -104.000000);
			PlayerTextDrawAlignment(playerid, ptd, 1);
			PlayerTextDrawColor(playerid, ptd, -1);
			PlayerTextDrawUseBox(playerid, ptd, 1);
			PlayerTextDrawBoxColor(playerid, ptd, -1061109505);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetOutline(playerid, ptd, 0);
			PlayerTextDrawBackgroundColor(playerid, ptd, 255);
			PlayerTextDrawFont(playerid, ptd, 1);
			PlayerTextDrawSetProportional(playerid, ptd, 1);
			PlayerTextDrawSetShadow(playerid, ptd, 0);

			ptd_computer[playerid][PTD_COMP_PC_DISK_BOX_ACTIVE][i] = ptd = CreatePlayerTextDraw(playerid, 315.041229, y + 17.099961, "box"); // BoxBlue 
			PlayerTextDrawLetterSize(playerid, ptd, 0.000000, 1.199998);
			PlayerTextDrawTextSize(playerid, ptd, 369.100006, -105.000000);
			PlayerTextDrawAlignment(playerid, ptd, 1);
			PlayerTextDrawColor(playerid, ptd, -1);
			PlayerTextDrawUseBox(playerid, ptd, 1);
			PlayerTextDrawBoxColor(playerid, ptd, 7208959);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
			PlayerTextDrawSetOutline(playerid, ptd, 0);
			PlayerTextDrawBackgroundColor(playerid, ptd, 255);
			PlayerTextDrawFont(playerid, ptd, 1);
			PlayerTextDrawSetProportional(playerid, ptd, 1);
			PlayerTextDrawSetShadow(playerid, ptd, 0);
		}

		ShowComputerWindow(playerid, true, "This PC");
	}
	else 
	{
		ShowComputerWindow(playerid, false);
		
		for (new PlayerText: i = PTD_COMP_PC_START; i <= PTD_COMP_PC_END; i++)
		{
			PlayerTextDrawDestroy(playerid, ptd_computer[playerid][i]);
			ptd_computer[playerid][i] = INVALID_PTD;
		}
	}

}