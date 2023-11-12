/*!
	@brief Меню транспорта
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.01.2018
*/

ShowVehicleListControl(playerid, const vehicleid)
{
	new index = GetPlayerVehicleIndexByServerId(playerid, vehicleid);
	
	if (index == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Транспорт не вызван на сервере.");
		return;
	}
	
	new delete = player_vehicle[playerid][pv_delete][GetPlayerVehicleIndexByServerId(playerid, vehicleid)];
	
	format:g_string(" Информация о транспорте\n \
		Управление транспортом\n \
		%s",
		(delete == 1) ? ("Отменить удаление транспорта") : ("Убрать транспорт")
	);
	
	ShowPlayerDialog(playerid, D_CAR + 1, DIALOG_STYLE_LIST, 
		GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name), 
		g_string,
		"Выбрать", "Назад"
	);
}

ShowVehicleInformation(playerid, modelid, vehicleid, const dialogid, btn_1[] = "", btn_2[] = "")
{
	clean:<g_big_string>;
	
	new slots = GetVehicleInfo(modelid, v_max_slots),
		seat = GetVehicleInfo(modelid, v_seat);
	
	if (vehicleid != INVALID_PARAM)
	{
		format:g_big_string("" #DEFAULT " Информация о транспорте #%d\n\n",
			GetVehicleId(vehicleid)
		);
	}
	else 
	{
		format:g_big_string("" #DEFAULT " Информация о транспорте\n\n");
	}
	
	if (vehicleid != INVALID_PARAM)
	{
		format:g_big_string("%sТип собственности: " #cPROJECT "%s" #cWHITE ".\n", 
			g_big_string,
			GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT ? ("Арендованная") : ("Во владении") 
		);
	}
	
	format:g_big_string("%sИмя: " #cPROJECT "%s" #cWHITE ".\n", 
		g_big_string,
		GetVehicleInfo(modelid, v_name) 
	);
	
	format:g_big_string("%sТип: " #cPROJECT "%s" #cWHITE ".\n", 
		g_big_string,
		GetVehicleInfo(modelid, v_type) 
	);
	
	format:g_big_string("%sПривод: " #cPROJECT "%s" #cWHITE ".\n", 
		g_big_string, 
		GetVehicleInfo(modelid, v_drive) 
	);
	
	format:g_big_string("%sРыночная стоимость: " #cGREEN "$%i" #cWHITE "\n", 
		g_big_string,
		GetVehicleInfo(modelid, v_cost) 
	);

	if (vehicleid == INVALID_PARAM)
	{
		format:g_big_string("%sСтоимость недельной аренды: " #cGREEN "$%i" #cWHITE ".\n", 
			g_big_string,
			GetVehicleRent(modelid, 7) 
		);
	}
	
	format:g_big_string("%sМеста: " #cPROJECT "%i" #cWHITE ".\n", 
		g_big_string,
		seat + GetVehicleMaxSeats(modelid)
	);
	
	format:g_big_string("%sВместительность багажника: " #cPROJECT "%i" #cWHITE " слот%s.\n", 
		g_big_string,
		slots,
		EndWordSlot(slots)
	);
	
	format:g_big_string("%sОбъем топливного бака: " #cPROJECT "%0.2f" #cWHITE " галлон.\n", 
		g_big_string,
		GetVehicleInfo(modelid, v_max_fuel)
	);
	
	format:g_big_string("%sРасход топлива: " #cPROJECT "%0.2f" #cWHITE " MPG.\n", 
		g_big_string,
		GetFuelRate(modelid)
	);

	if (vehicleid != INVALID_PARAM && vehicle_data[vehicleid][v_owner_id] == GetCharacterId(playerid)) // если просматривает владелец
	{
		format:g_big_string("%sСостояние двигателя: %s.", 
			g_big_string,
			("Исправен")
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, " ", g_big_string, btn_1, btn_2);
	return 1;
}

ShowVehicleMenu(playerid, vehicleid, dialogid = D_CAR + 3)
{
	clean:<g_big_string>;
	
	new is_owner = IsOwnerVehicle(playerid, vehicleid),
		in_vehicle = IsPlayerInVehicle(playerid, vehicleid);
	
	if (in_vehicle && !IsBikeVehicle(vehicleid))
	{
		format:g_big_string(" " #cWHITE "%s" #cWHITE " двигатель\t" #cGRAY "2 | NUM | /en\n",
			vehicle_data[vehicleid][v_engine] == VEHICLE_PARAMS_ON ? ("" #cGRAY "Заглушить") : ("" #cPROJECT "Завести")
		);
		
		format:g_big_string("%s " #cWHITE "%s" #cWHITE " фары\t" #cGRAY "CTRL\n",
			g_big_string,
			vehicle_data[vehicleid][v_light] == VEHICLE_PARAMS_ON ? ("" #cGRAY "Выключить") : ("" #cPROJECT "Включить")
		);
		
		strcat(g_big_string, " " #cWHITE "Окна\t" #cGRAY "/window\n");
			
		format:g_big_string("%s " #cWHITE "%s" #cWHITE " огран. скорости\n",
			g_big_string,
			vehicle_data[vehicleid][v_limit] == VEHICLE_PARAMS_ON ? ("" #cGRAY "Выключить") : ("" #cPROJECT "Включить")
		);
		
		format:g_big_string("%s " #cWHITE "%s" #cWHITE " радиостанцию\n",
			g_big_string,
			vehicle_data[vehicleid][v_radio] ? ("" #cGRAY "Выключить") : ("" #cPROJECT "Включить")
		);
	}
	
	if (!IsBikeVehicle(vehicleid))
	{
		format:g_big_string("%s " #cWHITE "%s" #cWHITE " капот\t" #cGRAY "/hood\n",
			g_big_string,
			vehicle_data[vehicleid][v_hood] == VEHICLE_PARAMS_ON ? ("" #cGRAY "Закрыть") : ("" #cPROJECT "Открыть")
		);
		
		format:g_big_string("%s " #cWHITE "%s" #cWHITE " багажник\t" #cGRAY "/boot\n",
			g_big_string,
			vehicle_data[vehicleid][v_boot] == VEHICLE_PARAMS_ON ? ("" #cGRAY "Закрыть") : ("" #cPROJECT "Открыть")
		);
	}
	
	if (is_owner)
	{
		if (in_vehicle)
		{
			strcat(g_big_string, " " #cWHITE "Припарковать\t" #cGRAY "/park\n");
		}
		else 
		{
			strcat(g_big_string, " " #cWHITE "Вернуть транспорт на парковочное место\t\n");
		}
		
		format:g_big_string("%s " #cWHITE "%s" #cWHITE " транспорт\t" #cGRAY "/clock\n",
			g_big_string,
			vehicle_data[vehicleid][v_lock] == VEHICLE_PARAMS_ON ? ("" #cPROJECT "Открыть") : ("" #cGRAY "Закрыть")
		);
		
		if (!in_vehicle && !IsBikeVehicle(vehicleid))
		{
			strcat(g_big_string, " " #cWHITE "Детали транспорта\t" #cGRAY "/cdetails\n");
		}
		
		if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
		{
			strcat(g_big_string, " " #cWHITE "Разорвать договор аренды\t" #cGRAY "/unrentcar\n");
		}
		else 
		{
			strcat(g_big_string, " " #cWHITE "Продать\t" #cGRAY "/sellcar\n");
		}
		
		strcat(g_big_string, " " #cWHITE "Обменять\t" #cGRAY "/swapcar\n");
		strcat(g_big_string, " " #cWHITE "Доверить\t" #cGRAY "/trustcar\n");
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, " ", g_big_string, "Выбрать", "Закрыть");
	return 1;
}

ShowVehicleList(playerid, const dialogid = D_CAR, btn_1[] = "Выбрать", btn_2[] = "Закрыть")
{
	clean:<g_string>;
	
	new count;
	
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		if (player_vehicle[playerid][pv_id][i] == 0)
		{
			continue;
		}
		
		format:g_string("%s " #cWHITE "%s\t%s" #cWHITE " %s\n",
			g_string,
			GetVehicleInfo(player_vehicle[playerid][pv_model][i], v_name),
			(player_vehicle[playerid][pv_server_id][i] != 0) ? ("" #cPROJECT "Вызван") : (" "),
			(player_vehicle[playerid][pv_delete][i]) ? ("[" #cDARKRED "будет убран" #cWHITE "]") : (" ")
		);
		
		g_dialog_select[playerid][count] = i;
		count++;
	}
	
	return count ? ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, " ", g_string, btn_1, btn_2) : 0;
}

ShowVehicleAroundOfPlayerList(playerid, const dialogid, limit_display = 0)
{
	clean:<g_string>;
	
	new count;
	
	for (new i = 1, vehicles = GetVehiclePoolSize(); i <= vehicles; i++)
	{		
		if (!IsOwnerVehicle(playerid, i) 
		|| !IsPlayerAroundVehicle(playerid, i, 30.0)
		|| IsBikeVehicle(i))
		{
			continue;
		}

		format:g_string("%s " #cWHITE "%s\n",
			g_string,
			GetVehicleInfo(vehicle_data[i][v_model], v_name)
		);
		
		g_dialog_select[playerid][count] = i;
		count++;
	}
	
	printf("[ShowVehicleAroundOfPlayerList]: count %d", count);
	if (count > limit_display)
	{
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, "Транспорт в радиусе", g_string, "Выбрать", "Закрыть");
		return count;
	}
	
	return count;
}