/*!
	@brief Система транспортного агенства
	@author Found (evg.savosin)
	@date 16.01.2018
*/

#define USE_RENT_POS				829.3311, 2546.0237, 2610.9063

#define RENT_MAX_POS			(10)

#define RENT_PAGES				(20)
#define RENT_PAGE_PREV			(0)
#define RENT_PAGE_NEXT			(1)

#define RENT_TAXI_COLOR_ID		(6)

enum
{
	RENT_TYPE_TERRESTRIAL = 0, /// позиции для наземного тс
	RENT_TYPE_WATER, /// позиции для водного тс
	RENT_TYPE_FLY /// позиции для воздушного тс
}

new const Float: rent_pos		[	][	][	] =
{
	{
		{1616.6520, -1128.1394, 25.6333, 89.8865},
		{1649.2209, -1111.6340, 25.6411, 269.7438},
		{1653.0009, -1135.7614, 25.6333, 179.6092},
		{1675.7660, -1124.9247, 25.6379, 270.0464},
		{1648.8888, -1111.5619, 25.6411, 268.9396},
		{1562.9844, -1012.2938, 25.6333, 359.7091},
		{1571.9236, -1011.9119, 25.6333, 0.1238},
		{1627.2758, -1037.2949, 25.6255, 177.7311},
		{1631.7166, -1037.2977, 25.6255, 179.7729},
		{1654.3594, -1036.7424, 25.6255, 177.8793}
	}, // Terrestrial
	
	{
		{719.6836, -1694.3164, -0.7021, 180.7408},
		{719.9637, -1628.3718, -0.3404, 181.2489},
		{727.8937, -1494.7296, -0.4939, 180.8260},
		{2321.2678, -2401.7273, -0.4730, 135.6720},
		{2521.3677, -2268.7170, -0.6951, 90.8356},
		{2355.4280, -2527.7891, -0.8162, 180.0390},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0}
	}, // Water
	
	{
		{2112.2261, -2435.0105, 13.1220, 179.4164},
		{1890.1434, -2627.4429, 13.1088, 357.8617},
		{1822.3744, -2627.7502, 13.1653, 357.8618},
		{1753.9930, -2625.2500, 13.1196, 1.6294},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0}
	} // Fly
};

new rent_begin_index			[	MAX_PLAYERS		][	RENT_PAGES	];

// Public function

Rent_OnGameModeInit()
{
	CreatePickupWith3DTextLabel("Аренда", 1239, USE_RENT_POS, WORLD_OTHER + 4, INT_OTHER);
}

Rent_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{
		if (IsPlayerInRangeOfPoint(playerid, 
			FACTOR_TELEPORT_RADIUS, 
			USE_RENT_POS
		))
		{
			ShowPlayerDialog(playerid, D_RENT, DIALOG_STYLE_LIST, " ",
				"" #cGRAY "Тип транспорта\n \
				" #cWHITE "Автомобиль\n \
				Мотоцикл\n \
				Специальный транспорт\n \
				Вертолет\n \
				Водный транспорт",
				"Выбрать", "Назад" 
			);
			
			return 0;
		}
	}
	
	return 1;
}

Rent_OnPlayerClickPTD(playerid, PlayerText: playertextid)
{
	if (!GetPVarInt(playerid, !"Rent:States"))
	{
		return 1;
	}
		
	new index,
		dialogid = D_RENT + 1;
		
	for (new i; i < TD_SELECT_MENU_ARRAY; i++)
	{
		if (playertextid == ptd_select_menu[playerid][i])
		{
			index = g_td_select[playerid][i] + 400;
			SetPVarInt(playerid, !"Rent:BuyIndex", index);
			
			// Цвет для такси
			if (IsRentVehicleTaxi(index))
			{
				SetPVarInt(playerid, !"Rent:Color", RENT_TAXI_COLOR_ID);
				dialogid = D_RENT + 2;
			}
			
			ShowVehicleInformation(playerid, index, INVALID_PARAM, dialogid, "Далее", "Закрыть");
			break;
		}
	}
	
	return 1;
}

Rent_OnPlayerClickTextDraw(playerid, Text: clickedid)
{
	if (clickedid == INVALID_TEXT_DRAW)
	{
		if (GetPVarInt(playerid, !"Rent:States"))
		{
			ShowRentList(playerid, false, INVALID_PARAM, INVALID_PARAM);
		}
	}
	else if (clickedid == td_select_menu[1]) // next
	{
		UpdateRentList(playerid, RENT_PAGE_NEXT);
	}
	else if (clickedid == td_select_menu[2]) // last 
	{
		UpdateRentList(playerid, RENT_PAGE_PREV);
	}
	
	return 1;
}

function Rent_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == D_RENT)
	{
		if (!response)
		{
			return 1;
		}
		
		switch(listitem)
		{
			case 0 :
			{
				ShowPlayerDialog(playerid, D_RENT, DIALOG_STYLE_LIST, " ",
					"" #cGRAY "Тип транспорта\n \
					" #cWHITE "Автомобиль\n \
					Мотоцикл\n \
					Специальный транспорт\n \
					Вертолет\n \
					Водный транспорт",
					"Выбрать", "Назад" 
				);
				
				return 1;
			}
			
			case 1 : /// car
			{
				ShowRentList(playerid, true, RENT_CAR, RENT_TYPE_TERRESTRIAL);
			}
			case 2 : /// moto
			{
				ShowRentList(playerid, true, RENT_MOTO, RENT_TYPE_TERRESTRIAL);
			}
			
			case 3 : /// special
			{
				ShowRentList(playerid, true, RENT_SPECIAL, RENT_TYPE_TERRESTRIAL);
			}
			
			case 4 : /// fly
			{
				ShowRentList(playerid, true, RENT_FLY, RENT_TYPE_FLY);
			}
			
			case 5 : /// water
			{
				ShowRentList(playerid, true, RENT_WATER, RENT_TYPE_WATER);	
			}
		}
		
	}
	else if (dialogid == D_RENT + 1)
	{
		if (!response)
		{
			return 1;
		}
		
		ShowPlayerDialog(playerid, D_RENT + 2, DIALOG_STYLE_LIST, " ", DIALOG_BASICVEH_COLOR, "Выбрать", "Закрыть");
	}
	else if (dialogid == D_RENT + 2)
	{
		if (!response)
		{
			DeletePVar(playerid, !"Rent:Color");
			return 1;
		}
		
		new color,
			days,
			modelid = GetPVarInt(playerid, !"Rent:BuyIndex");
		
		if (!GetPVarInt(playerid, !"Rent:Color"))
		{
			switch(listitem)
			{
				case 0 :
				{
					ShowPlayerDialog(playerid, D_RENT + 1, DIALOG_STYLE_LIST, " ", DIALOG_BASICVEH_COLOR, "Выбрать", "Закрыть");
					return 1;
				}
				
				case 1 :
				{
					color = 0;
				}
				
				case 2 :
				{
					color = 1;
				}
				
				case 3 :
				{
					color = 20;
				}
				
				case 4 :
				{
					color = 44;
				}
				
				case 5 :
				{
					color = 57;
				}
				
				case 6 :
				{
					color = 29;
				}
			}
		}
		else 
		{
			color = GetPVarInt(playerid, !"Rent:Color");
		}
		
		new rent = GetVehicleInfo(modelid, v_rent);
		if (rent == RENT_SPECIAL || rent == RENT_FLY || rent == RENT_WATER)
		{
			days = 1;
		}
		else
		{
			days = 7;
		}
		
		SetPVarInt(playerid, !"Rent:Color", color);
		SetPVarInt(playerid, !"Rent:Days", days);
		
		format:g_string("" #DEFAULT " Аренда транспорта\n\n\
		Вы собираетесь арендовать " #cPROJECT "%s" #cWHITE ".\n\
		Стоимость аренды на %d %s составляет: " #cGREEN "$%i" #cWHITE ".\n\
		Вы подтверждаете аренду?",
			GetVehicleInfo(modelid, v_name),
			days,
			days == 1 ? ("день") : ("дней"),
			GetVehicleRent(modelid, days)
		);
		
		ShowPlayerDialog(playerid, D_RENT + 3, DIALOG_STYLE_MSGBOX, " ", g_string, "Да", "Назад");
	}
	else if (dialogid == D_RENT + 3)
	{
		if (!response)
		{
			ShowPlayerDialog(playerid, D_RENT + 2, DIALOG_STYLE_LIST, " ", DIALOG_BASICVEH_COLOR, "Выбрать", "Закрыть");
			return 1;
		}
		
		if (!GetPlayerAvaibleVehicle(playerid))
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете арендовать больше транспортного средства.");
			DeletePVar(playerid, !"Rent:Color");
			DeletePVar(playerid, !"Rent:Days");
			return 1;
		}
		
		new days = GetPVarInt(playerid, !"Rent:Days");
		
		MakePayment(
			playerid, 
			GetVehicleRent(GetPVarInt(playerid, !"Rent:BuyIndex"), days), 
			"rent_vehicle"
		);
	}
	
	return 1;
}

function PAY:rent_vehicle(playerid, status, type)
{
	new modelid = GetPVarInt(playerid, !"Rent:BuyIndex"),
		vehicle_type = GetPVarInt(playerid, !"Rent:TypeVehicle"),
		days = GetPVarInt(playerid, !"Rent:Days"),
		color[2],
		rand;
		
	color[0] = GetPVarInt(playerid, !"Rent:Color");
	color[1] = color[0];
	
	if (vehicle_type == RENT_TYPE_TERRESTRIAL)
	{
		rand = random(RENT_MAX_POS);
	}
	else if (vehicle_type == RENT_TYPE_FLY)
	{
		rand = random(RENT_MAX_POS - 6);
	}
	else if (vehicle_type == RENT_TYPE_WATER)
	{
		rand = random(RENT_MAX_POS - 4);
	}
	
	DeletePVar(playerid, !"Rent:BuyIndex");
	DeletePVar(playerid, !"Rent:TypeVehicle");
	DeletePVar(playerid, !"Rent:Color");
	DeletePVar(playerid, !"Rent:Days");
	
	if (!GetPlayerAvaibleVehicle(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете арендовать больше транспортного средства.");
		return 1;
	}
	
	if (!IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, USE_RENT_POS))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Для аренды транспорта, Вы должны находиться в специализированном месте.");
		return 1;
	}

	if (!status)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
		return 1;
	}
	
	GivePlayerVehicle(playerid, TYPE_BUY_RENT, modelid, color, rent_pos[vehicle_type][rand], bool: (type == TYPE_PAY_CREDIT), days);
		
	pformat:("" #SUCCESS " Вы успешно арендовали транспортное средство " #cPROJECT "%s" #cWHITE " на %d дней.",
		GetVehicleInfo(modelid, v_name),
		days
	);
	
	psend:(playerid, C_WHITE);
	
	return 1;
}

ShowRentList(playerid, states, type, type_vehicle)
{
	new end_index;
		
	if (!ShowSelectMenu(playerid, states, "Rent Vehicle"))
	{
		SendClientMessage(playerid, C_WHITE, !ERROR_INTERFACE);
		return;
	}
	
	if (states)
	{
		for (new j; j < RENT_PAGES; j++)
		{
			rent_begin_index[playerid][j] = INVALID_PARAM;
		}
		
		GetRentIdentifyEnds(type, _, end_index);
		
		SetPVarInt(playerid, !"Rent:Page", 0);
		SetPVarInt(playerid, !"Rent:EndIndex", end_index);
		SetPVarInt(playerid, !"Rent:NextIndex", 0);
		SetPVarInt(playerid, !"Rent:Type", type);
		SetPVarInt(playerid, !"Rent:TypeVehicle", type_vehicle);
		
		SelectTextDraw(playerid, C_GRAY);
		UpdateRentList(playerid, INVALID_PARAM);
	}
	else 
	{	
		for (new i = 0; i < TD_SELECT_MENU_ARRAY; i++)
		{
			g_td_select[playerid][i] = INVALID_PARAM;
		}
		
		DeletePVar(playerid, !"Rent:Page");
		DeletePVar(playerid, !"Rent:Type");
		DeletePVar(playerid, !"Rent:NextIndex");
		DeletePVar(playerid, !"Rent:EndIndex");
		DeletePVar(playerid, !"Rent:TypeVehicle");
	}
	
	SetPVarInt(playerid, !"Rent:States", states);
}

UpdateRentList(playerid, action)
{
	new i,
		type = GetPVarInt(playerid, !"Rent:Type"),
		item,
		page,
		end_index = GetPVarInt(playerid, !"Rent:EndIndex");
		
	if (action == INVALID_PARAM)
	{
		i = GetPVarInt(playerid, !"Rent:NextIndex");
	}
	else if (action == RENT_PAGE_NEXT) 
	{
		if ((GetPVarInt(playerid, !"Rent:NextIndex") + 1) >= end_index)
		{
			return;
		}
		
		i = GetPVarInt(playerid, !"Rent:NextIndex") + 1;
		GivePVarInt(playerid, "Rent:Page", 1);

	}
	else if (action == RENT_PAGE_PREV)
	{
		if ((GetPVarInt(playerid, !"Rent:Page") - 1) < 0)
		{
			return;
		}
		
		TakePVarInt(playerid, "Rent:Page", 1);
		i = rent_begin_index[playerid][GetPVarInt(playerid, "Rent:Page")];
	}
	
	page = GetPVarInt(playerid, !"Rent:Page");

	for (new j; j < TD_SELECT_MENU_ARRAY; j++)
	{
		PlayerTextDrawHide(playerid, ptd_select_menu[playerid][j]);
		g_td_select[playerid][j] = INVALID_PARAM;
	}
	
	for (; i < sizeof vehicle_info; i++)
	{	
		if (vehicle_info[i][v_rent] != type || i > end_index)
		{	
			continue;
		}
		
		if (rent_begin_index[playerid][page] == INVALID_PARAM)
		{
			rent_begin_index[playerid][page] = i;
		}
		
		PlayerTextDrawSetPreviewModel(
			playerid, 
			ptd_select_menu[playerid][item], 
			i + 400
		);
		
		PlayerTextDrawSetPreviewRot(
			playerid, 
			ptd_select_menu[playerid][item], 
			0.0, 
			0.0, 
			30.0, 
			0.9
		);
		
		PlayerTextDrawShow(playerid, ptd_select_menu[playerid][item]);
		
		g_td_select[playerid][item] = i;
		SetPVarInt(playerid, !"Rent:NextIndex", i);
		
		item++;
		if (item == TD_SELECT_MENU_ARRAY)
		{
			break;
		}
	}
}

GetRentIdentifyEnds(type, &begin_index = 0, &end_index)
{
	for (new i; i < sizeof vehicle_info; i++)
	{
		if (vehicle_info[i][v_rent] != type)
		{
			continue;
		}
		
		if (!begin_index)
		{
			begin_index = i;
		}
		
		end_index = i;
	}
}

IsRentVehicleTaxi(modelid)
{
	return modelid == 420 || modelid == 438;
}