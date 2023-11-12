/*!
	@brief Система заправок (Fuel gas station)
	@author Found (evg.savosin)
	@date 26.04.2018
*/

// Defines
#define FILL_CAR_PRICE			2


// Structures
enum E_GAS_STATION
{
	Float: gs_pos				[3],
	bool: gs_state
}

new const gas_statios_pos		[][E_GAS_STATION] =
{
	{{1940.9303, -1772.9000, 13.6406}, false},
	{{1941.5695, -1769.3093, 13.6406}, false},
	{{1941.5525, -1776.9375, 13.6406}, false},
	{{1000.5898, -937.3073, 42.3281}, false},
	{{1007.6913, -936.3011, 42.3281}, false},
	{{-89.8909, -1175.3433, 2.3145}, false},
	{{-96.6654, -1172.4891, 2.4991}, false},
	{{-92.7253, -1162.9189, 2.4453}, false},
	{{-86.0279, -1166.0699, 2.4050}, false},
	{{-1612.3071, -2719.7390, 48.9453}, false},
	{{-1608.7179, -2715.3926, 48.9453}, false},
	{{-1605.4535, -2711.0969, 48.9453}, false},
	{{-1602.1294, -2706.5850, 48.9453}, false},
	{{655.6650, -557.9935, 16.5015}, false},
	{{655.4059, -559.7579, 16.5015}, false},
	{{655.7224, -570.2836, 16.5015}, false},
	{{1384.2739, 458.6854, 20.3452}, false},
	{{1379.7408, 460.4866, 20.3452}, false}
};


// Function
Gas_OnGameModeInit()
{
	for (new i; i < sizeof gas_statios_pos; i++)
	{
		CreatePickupWith3DTextLabel("" #cWHITE "АЗС\n" #cPROJECT "ALT", 
			INVALID_PARAM, 
			gas_statios_pos[i][gs_pos][0], 
			gas_statios_pos[i][gs_pos][1], 
			gas_statios_pos[i][gs_pos][2] - 5.0
		);
	}
}

Gas_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_FIRE))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
			
		if (vehicleid && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			for (new i; i < sizeof gas_statios_pos; i++)
			{
				if (GetVehicleDistanceFromPoint(vehicleid,
				gas_statios_pos[i][gs_pos][0],
				gas_statios_pos[i][gs_pos][1],
				gas_statios_pos[i][gs_pos][2]) > 6.0)
				{
					continue;
				}
			
				SetPVarInt(playerid, "Gas:Index", i);
				
				ShowGasMenu(playerid, vehicleid);
				return 0;
			}
		}
	}
	
	return 1;
}

Gas_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused listitem
	if (dialogid == D_GAS)
	{
		if (!response)
		{
			DeletePVar(playerid, "Gas:Index");
			return 1;
		}
		
		new index = GetPVarInt(playerid, "Gas:Index"),
			value = strval(inputtext),
			vehicleid = GetPlayerVehicleID(playerid);
		
		if (!vehicleid)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Вы должны находиться в транспорте.");
			DeletePVar(playerid, "Gas:Index");
			return 1;
		}
		
		if (GetVehicleDistanceFromPoint(vehicleid,
		gas_statios_pos[index][gs_pos][0],
		gas_statios_pos[index][gs_pos][1],
		gas_statios_pos[index][gs_pos][2]) > 6.0)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Вы должны находиться около АЗС.");
			DeletePVar(playerid, "Gas:Index");
			return 1;
		}
		
		if (vehicle_data[vehicleid][v_engine] != VEHICLE_PARAMS_OFF)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Заглушите двигатель транспорта.");
			DeletePVar(playerid, "Gas:Index");
			return 1;
		}
		
		if (value <= 0)
		{	
			ShowGasMenu(playerid, vehicleid, "Вы ввели неверное значение.");
			return 1;
		}
		
		if (!VehicleFill(vehicleid, value))
		{
			ShowGasMenu(playerid, vehicleid, "Столько топлива не может быть залито в Ваш топливный бак.");
			return 1;
		}
		
		if (!GivePlayerCash(playerid, -(value * FILL_CAR_PRICE)))
		{
			SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
			DeletePVar(playerid, "Gas:Index");
			return 1;
		}
	}
	
	return 1;
}

ShowGasMenu(playerid, vehicleid, error[] = "")
{
	format:g_string("" #DEFAULT " Заправить транспорт\n\n\
		Расценки:\n\
		1 галлон - " #cGREEN "$%i" #cWHITE ".\n\n\
		Ваш объем топливного бака: " #cPROJECT "%0.2f" #cWHITE "\n\
		Введите количество галлонов:%s%s",
		FILL_CAR_PRICE,
		GetVehicleInfo(vehicle_data[vehicleid][v_model], v_max_fuel),
		!isnull(error) ? ("\n\n" #cRED "") : (""),
		error
	);
	
	ShowPlayerDialog(playerid, D_GAS, DIALOG_STYLE_INPUT, " ",
		g_string,
		"Далее", "Закрыть"
	);
}

