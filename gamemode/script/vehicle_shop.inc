/*!
	@brief Система автосалона
	@author Found (evg.savosin)
	@date 16.12.2016
*/

/// Типы автосалонов 
enum 
{
	VEHSHOP_GROTTI = 0,
	VEHSHOP_LM,
	VEHSHOP_BIKE_SHED
};

#define VEHSHOP_MAX_POS				(3)

#define VEHSHOP_PAGES 				(50)
#define VEHSHOP_PAGE_PREV			(0)
#define VEHSHOP_PAGE_NEXT			(1)

#define BUY_GROTTI_POS					1357.5076, 1461.8929, 2171.8215
#define BUY_LM_POS						511.7986, 1342.5146, 2515.1497
#define BUY_BIKE_SHED_POS				1946.9370, 1928.4915, 3272.2026

new const Float: vehshop_pos_vehicle		[][][] = 
{
	{
		{1120.3217, -869.2026, 43.0190, 1.0474},
		{1107.7045, -869.3093, 43.0176, 1.0580},
		{1095.5532, -869.3990, 43.0162, 1.0629}
	}, // grotti
	
	{
		{2118.9351, -1147.7559, 23.9402, 304.8801},
		{2118.5847, -1144.1497, 24.2147, 305.1199},
		{2118.4915 ,-1135.5052, 24.7982, 305.3217}
	}, // lm 
	
	{
		{2141.9287, -1198.5446, 23.7301, 269.3746},
		{2142.0420, -1194.5969, 23.5466, 269.1537},
		{2141.8062, -1188.2740, 23.5462, 271.0558}
	} // bike shed
};

new vehshop_begin_index				[	MAX_PLAYERS		][	VEHSHOP_PAGES	];

// Public function
VehShop_OnGameModeInit()
{
	/// Grotti
	CreateVehicleInVehShop(
		560, 
		1373.9926, 
		1453.5510, 
		2171.2939,
		22.2642,
		1, 
		1,
		WORLD_OTHER + 1,
		INT_OTHER
	); /// 1
	
	CreateVehicleInVehShop(
		533,
		1366.4069,
		1453.5867,
		2171.3013,
		334.7952,
		16,
		16,
		WORLD_OTHER + 1,
		INT_OTHER
	); /// 2
	
	CreateVehicleInVehShop(
		562,
		1366.7786,
		1471.8988,
		2171.2473,
		199.0762,
		3,
		3,
		WORLD_OTHER + 1,
		INT_OTHER
	); /// 3
	
	CreateVehicleInVehShop(
		411,
		1374.1626,
		1471.7018,
		2171.3213,
		148.6580,
		61,
		61,
		WORLD_OTHER + 1,
		INT_OTHER
	); /// 4
	
	CreatePickupWith3DTextLabel("Покупка", 1239, BUY_GROTTI_POS, WORLD_OTHER + 1, INT_OTHER);
	
	/// Legendary Motorcycle
	CreateVehicleInVehShop(
		471,
		498.1629,
		1342.2733,
		2515.7061,
		89.7370,
		54,
		54,
		WORLD_OTHER + 2,
		INT_OTHER
	); /// 1
	
	CreatePickupWith3DTextLabel("Покупка", 1239, BUY_LM_POS, WORLD_OTHER + 2, INT_OTHER);
	
	/// Mr.Grants Bike Shed
	CreateVehicleInVehShop(
		509,
		1943.9498,
		1925.4232,
		3271.9382,
		86.4634,
		144,
		144,
		WORLD_OTHER + 3,
		INT_OTHER
	); /// 1
	
	CreateVehicleInVehShop(
		481,
		1941.8263,
		1927.9962,
		3271.9382,
		0.1791,
		133,
		133,
		WORLD_OTHER + 3,
		INT_OTHER
	); /// 2
	
	CreatePickupWith3DTextLabel("Покупка", 1239, BUY_BIKE_SHED_POS, WORLD_OTHER + 3, INT_OTHER);
}

VehShop_OnPlayerClickPTD(playerid, PlayerText: playertextid)
{
	if (!GetPVarInt(playerid, "VehicleShop:States"))
	{
		return 1;
	}
		
	new index;
		
	for (new i; i < TD_SELECT_MENU_ARRAY; i++)
	{
		if (playertextid == ptd_select_menu[playerid][i])
		{
			index = g_td_select[playerid][i];
			SetPVarInt(playerid, "VehicleShop:BuyIndex", index);
			ShowVehicleInformation(playerid, index, INVALID_PARAM, D_VEHSHOP, "Далее", "Закрыть");
			break;
		}
	}
	
	return 1;
}

VehShop_OnPlayerClickTextDraw(playerid, Text: clickedid)
{
	if (!GetPVarInt(playerid, "VehicleShop:States"))
	{
		return 1;
	}
	
	if (clickedid == INVALID_TEXT_DRAW)
	{
		ShowVehicleShopList(playerid, false, INVALID_PARAM, INVALID_PARAM);
	}
	else if (clickedid == td_select_menu[1]) // next
	{
		UpdateVehicleShopList(playerid, VEHSHOP_PAGE_NEXT);
	}
	else if (clickedid == td_select_menu[2]) // last 
	{
		UpdateVehicleShopList(playerid, VEHSHOP_PAGE_PREV);
	}
	
	return 1;
}

VehShop_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{
		if (IsPlayerInRangeOfPoint(playerid, 
		FACTOR_TELEPORT_RADIUS, 
		BUY_GROTTI_POS))
		{
			ShowVehicleShopList(playerid, true, SALE_CAR, VEHSHOP_GROTTI);
			return 0;
		}
		else if (IsPlayerInRangeOfPoint(playerid, 
		FACTOR_TELEPORT_RADIUS, 
		BUY_LM_POS))
		{
			ShowVehicleShopList(playerid, true, SALE_MOTO, VEHSHOP_LM);
			return 0;
		}
		else if (IsPlayerInRangeOfPoint(playerid, 
		FACTOR_TELEPORT_RADIUS, 
		BUY_BIKE_SHED_POS))
		{
			ShowVehicleShopList(playerid, true, SALE_BIKE, VEHSHOP_BIKE_SHED);
			return 0;
		}
	}
	
	return 1;
}

function VehShop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == D_VEHSHOP)
	{
		if (!response)
		{
			return 1;
		}
		
		if (!GetPlayerAvaibleVehicle(playerid))
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете приобрести больше транспортных средств.");
			return 1;
		}
		
		ShowPlayerDialog(playerid, D_VEHSHOP + 1, DIALOG_STYLE_LIST, " ", DIALOG_BASICVEH_COLOR, "Выбрать", "Закрыть");
	}
	
	else if (dialogid == D_VEHSHOP + 1)
	{
		if (!response)
		{
			return 1;
		}
		
		new color;

		switch(listitem)
		{
			case 0 :
			{
				ShowPlayerDialog(playerid, D_VEHSHOP + 1, DIALOG_STYLE_LIST, " ", DIALOG_BASICVEH_COLOR, "Выбрать", "Закрыть");
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
		
		SetPVarInt(playerid, "VehicleShop:Color", color);
		
		MakePayment(playerid, GetVehicleInfo(GetPVarInt(playerid, "VehicleShop:BuyIndex"), v_cost), "buy_vehicle");
	}
	
	
	return 1;
}

function PAY:buy_vehicle(playerid, status)
{
	new modelid = GetPVarInt(playerid, "VehicleShop:BuyIndex"),
		type = GetPVarInt(playerid, "VehicleShop:TypeShop"),
		color[2],
		rand = random(VEHSHOP_MAX_POS);
		
	color[0] = GetPVarInt(playerid, "VehicleShop:Color");
	color[1] = color[0];
	
	if (!GetPlayerAvaibleVehicle(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете приобрести больше транспортного средства.");
		return 1;
	}
	
	if (!IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, BUY_GROTTI_POS) 
	&& !IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, BUY_LM_POS) 
	&& !IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, BUY_BIKE_SHED_POS))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Для покупки транспорта, Вы должны находиться в специализированном месте.");
		return 1;
	}

	if (!status)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
		return 1;
	}
	
	if (GetPVarInt(playerid, "Buy:StartCapital") == 1)
	{
		GivePlayerVehicle(playerid, TYPE_BUY_START_CAPITAL, modelid, color, vehshop_pos_vehicle[type][rand]);

		DeletePVar(playerid, "Buy:StartCapital");
	}
	else
	{
		GivePlayerVehicle(playerid, TYPE_BUY_FULLY, modelid, color, vehshop_pos_vehicle[type][rand]);
	}
		
	pformat:("" #SUCCESS " Вы успешно приобрели транспортное средство " #cPROJECT "%s" #cWHITE ".",
		GetVehicleInfo(modelid, v_name)
	);
	
	psend:(playerid, C_WHITE);
	
	return 1;
}

ShowVehicleShopList(playerid, states, type, type_shop)
{
	new end_index;
		
	if (!ShowSelectMenu(playerid, states, "Buy Vehicle"))
	{
		SendClientMessage(playerid, C_WHITE, !ERROR_INTERFACE);
		return;
	}
	
	if (states)
	{
		for (new j; j < VEHSHOP_PAGES; j++)
		{
			vehshop_begin_index[playerid][j] = INVALID_PARAM;
		}
		
		GetVehShopIdentifyEnds(type, _, end_index);
		
		SetPVarInt(playerid, "VehicleShop:Page", 0);
		SetPVarInt(playerid, "VehicleShop:EndIndex", end_index);
		SetPVarInt(playerid, "VehicleShop:NextIndex", 0);
		SetPVarInt(playerid, "VehicleShop:Type", type);
		SetPVarInt(playerid, "VehicleShop:TypeShop", type_shop);
		
		SelectTextDraw(playerid, C_GRAY);
		UpdateVehicleShopList(playerid, INVALID_PARAM);
	}
	else 
	{	
		for (new i = 0; i < TD_SELECT_MENU_ARRAY; i++)
		{
			g_td_select[playerid][i] = INVALID_PARAM;
		}
		
		DeletePVar(playerid, "VehicleShop:Page");
		DeletePVar(playerid, "VehicleShop:Type");
		DeletePVar(playerid, "VehicleShop:NextIndex");
		DeletePVar(playerid, "VehicleShop:EndIndex");
		DeletePVar(playerid, "VehicleShop:TypeShop");
	}
	
	SetPVarInt(playerid, "VehicleShop:States", states);
}

UpdateVehicleShopList(playerid, action)
{
	new i,
		type = GetPVarInt(playerid, "VehicleShop:Type"),
		item,
		page,
		end_index = GetPVarInt(playerid, "VehicleShop:EndIndex");
		
	if (action == INVALID_PARAM)
	{
		i = GetPVarInt(playerid, "VehicleShop:NextIndex");
	}
	else if (action == VEHSHOP_PAGE_NEXT) 
	{
		if ((GetPVarInt(playerid, "VehicleShop:NextIndex") + 1) >= end_index)
		{
			return;
		}
		
		i = GetPVarInt(playerid, "VehicleShop:NextIndex") + 1;
		GivePVarInt(playerid, "VehicleShop:Page", 1);

	}
	else if (action == VEHSHOP_PAGE_PREV)
	{
		if ((GetPVarInt(playerid, "VehicleShop:Page") - 1) < 0)
		{
			return;
		}
		
		TakePVarInt(playerid, "VehicleShop:Page", 1);
		i = vehshop_begin_index[playerid][GetPVarInt(playerid, "VehicleShop:Page")];
	}
	
	page = GetPVarInt(playerid, "VehicleShop:Page");
	
	for (new j; j < TD_SELECT_MENU_ARRAY; j++)
	{
		PlayerTextDrawHide(playerid, ptd_select_menu[playerid][j]);
		g_td_select[playerid][j] = INVALID_PARAM;
	}
	
	for (; i < sizeof vehicle_info; i++)
	{	
		if (vehicle_info[i][v_sale] != type || i > end_index)
		{
			continue;
		}
		
		if (vehshop_begin_index[playerid][page] == INVALID_PARAM)
		{
			vehshop_begin_index[playerid][page] = i;
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
		
		g_td_select[playerid][item] = i + 400;
		SetPVarInt(playerid, "VehicleShop:NextIndex", i);
		
		item++;
		if (item == TD_SELECT_MENU_ARRAY)
		{
			break;
		}
	}
}

GetVehShopIdentifyEnds(type, &begin_index = 0, &end_index)
{
	for (new i; i < sizeof vehicle_info; i++)
	{
		if (vehicle_info[i][v_sale] != type)
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

CreateVehicleInVehShop(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, world, int)
{
	new vehicleid = CreateVehicle(modelid, Float:x, Float:y, Float:z, Float:angle, color1, color2, -1);
	
	LinkVehicleToInterior(vehicleid, int);
	SetVehicleVirtualWorld(vehicleid, world);
	
	vehicle_data[vehicleid][v_fuel] = 0.0;
}