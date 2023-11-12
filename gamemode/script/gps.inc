/*!
	@brief Система GPS
	@author Found (evg.savosin)
	@date 16.12.2016
*/

// Defines
#define IsGPSIncluded(%0)				(player_gps{%0})


// Structures
enum 
{
	GPS_MAIN_CATEGORY = 0,
	GPS_ORGANIZATION,
	GPS_PLACES,
	GPS_REDCOUNTY,
	GPS_WHETSTONE,
	GPS_VEH,
	GPS_OTHER
};

enum E_GPS_DATA
{
	gps_cat,
	gps_text			[128],
	Float: gps_pos		[3],
};

new gps_list			[][E_GPS_DATA]	=
{
	{GPS_MAIN_CATEGORY, "Организации", {0.0, 0.0, 0.0}},
		{GPS_ORGANIZATION, "Полицейская станция «11th, Headquarters»", {1554.5465, -1675.4574, 16.1953}},
		{GPS_ORGANIZATION, "Полицейская станция «64th, Saints»", {2762.7485, -1448.3290, 31.1719}},
		{GPS_ORGANIZATION, "Полицейская станция «96th, Verona»", {1009.8740, -1597.2062, 15.1765}},
		{GPS_ORGANIZATION, "Центральный госпиталь", {1172.6677, -1323.4054, 15.4023}},
		{GPS_ORGANIZATION, "Департамент шерифа округа Лос-Сантос «Red County»", {311.5608, -176.7916, 2.0558}},
        {GPS_ORGANIZATION, "Департамент шерифа округа Лос-Сантос «Ganton»", {2405.3479, -1951.2976, 13.5469}},
		{GPS_ORGANIZATION, "Мэрия Лос-Сантоса", {1481.0111, -1771.3430, 18.7958}},
		{GPS_ORGANIZATION, "Суд Лос-Сантоса", {1382.1494, -1088.8030, 28.2129}},
		{GPS_ORGANIZATION, "Штаб-квартира рейнджеров «Whetstone National Park»", {-2048.4644, -2367.6904, 30.6318}},
		{GPS_ORGANIZATION, "«San Andreas Network News»", {1677.0424, -1631.4310, 14.2266}},		
		
	{GPS_MAIN_CATEGORY, "Развлечения и досуг", {0.0, 0.0, 0.0}},
        {GPS_PLACES, "Пляж Санта-Мария", {531.2509, -1765.3330, 14.2936}},
		{GPS_PLACES, "Боулинг-клуб", {1284.5297, -1585.2948, 13.5469}},
		{GPS_PLACES, "Торговый центр", {1567.7717, -1896.8376, 13.5606}},
		{GPS_PLACES, "Плавательный бассейн", {939.9956, -1717.8418, 13.8893}},
		
	{GPS_MAIN_CATEGORY, "Округ «Red County»", {0.0, 0.0, 0.0}},
        {GPS_REDCOUNTY, "«Blueberry»", {191.3046, -187.6596, 1.5781}},
        {GPS_REDCOUNTY, "«Dillimore»", {650.2819, -551.6368, 16.2903}}, 
        {GPS_REDCOUNTY, "«Montgomery»", {1289.5962, 265.2941, 19.5547}}, 
        {GPS_REDCOUNTY, "«Palomino Creek»", {2336.5862, 39.5787, 26.4810}},
	
	{GPS_MAIN_CATEGORY, "Округ «Whetstone»", {0.0, 0.0, 0.0}},
        {GPS_WHETSTONE, "«Angel Pine»", {-2134.9983, -2338.9053, 30.6250}},
        {GPS_WHETSTONE, "База отдыха вблизи национального парка", {-1961.5460, -2440.0457, 30.6250}}, 
	
	{GPS_MAIN_CATEGORY, "Транспортная промышленность", {0.0, 0.0, 0.0}},
		{GPS_VEH, "Станция технического обслуживания", {1698.3555, -1450.2852, 13.5469}},
		{GPS_VEH, "Транспортное агентство", {1830.2181, -1172.0491, 24.2656}},
		{GPS_VEH, "Автосалон «Grotti»", {1115.6359, -923.2931, 43.3906}},
		{GPS_VEH, "Веломагазин «Mr.Grant's Bike Shed»", {2139.4226, -1191.9657, 23.9922}},
		{GPS_VEH, "Мотосалон «Legendary Motorcycle»", {2131.5974, -1150.0253, 24.2002}},
		{GPS_VEH, "Утилизация транспорта в Лос-Сантосе", {2411.1807, -1426.2781, 23.9841}},
        {GPS_VEH, "Утилизация транспорта в Диллиморе", {642.1848, -499.1554, 16.3359}},

	{GPS_MAIN_CATEGORY, "Разное", {0.0, 0.0, 0.0}},
		{GPS_OTHER, "Банк", {1575.8866, -1330.6776, 16.4844}},
		{GPS_OTHER, "Бизнес агенство", {1471.9044, -1263.9343, 14.5625}},
		{GPS_OTHER, "Оружейный магазин в деловом районе", {1368.6759, -1279.6840, 13.5469}},
		{GPS_OTHER, "Студия звукозаписи", {816.1984, -1387.2885, 13.6105}},
		{GPS_OTHER, "Портовый склад", {2354.1294, -2288.0442, 17.4219}},
		{GPS_OTHER, "Центр лицензирования", {1809.9598, -1166.2878, 24.2266}}
};

// Public function
GPS_OnPlayerEnterCheckpoint(playerid)
{
	if (IsGPSIncluded(playerid))
	{
		DisablePlayerCheckpoint(playerid);
		player_gps{playerid} = 0;
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы достигли указанного места назначения.");
	}
	
    return 1;
}

GPS_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	
	if (dialogid == D_GPS)
	{
		if (!response)
		{
			DeletePVar(playerid, "GPS:Count");
			return 1;
		}
		
		new count = GetPVarInt(playerid, "GPS:Count");
			
		if (listitem == count)
		{
			FindVehicleOfPlayer(playerid);
			return 1;
		}
		else if (listitem == count + 1)
		{
			FindHouseOfPlayer(playerid);
			return 1;
		}
		else if (listitem == count + 2)
		{
			FindPremiseOfPlayer(playerid);
			return 1;
		}
		
		ShowGPSList(playerid, D_GPS + 1, listitem + 1);
	}
	else if (dialogid == D_GPS + 1)
	{
		if (!response)
		{
			cmd_gps(playerid);
			return 1;
		}
		
		new index = g_dialog_select[playerid][listitem];
			
		SetIncludeGPS(playerid, 
			gps_list[index][gps_pos][0], 
			gps_list[index][gps_pos][1], 
			gps_list[index][gps_pos][2] 
		);
		
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Место было отмечено на Вашем GPS навигаторе. " #cGRAY "(/gps - отмена)");
	}
	else if (dialogid == D_GPS + 2)
	{
		if (!response)
		{
			cmd_gps(playerid);
			return 1;
		}
		
		new vehicleid = player_vehicle[playerid][pv_server_id][listitem],
			Float: x,
			Float: y,
			Float: z;
		
		if (vehicleid == 0)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Данный транспорт не заспавнен.");
			return 1;
		}
		
		GetVehiclePos(vehicleid, x, y, z);
		
		SetIncludeGPS(playerid, 
			x, 
			y, 
			z 
		);
		
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Личный транспорт был отмечен на Вашем GPS навигаторе. " #cGRAY "(/gps - отмена)");
	}
	else if (dialogid == D_GPS + 3)
	{
		if (!response)
		{
			cmd_gps(playerid);
			return 1;
		}
		
		SetHouseMark(playerid, g_dialog_select[playerid][listitem]);
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Жилищное помещение было отмечено на Вашем GPS навигаторе. " #cGRAY "(/gps - отмена)");
	}
	else if (dialogid == D_GPS + 4)
	{
		if (!response)
		{
			cmd_gps(playerid);
			return 1;
		}
		
		SetPremiseMark(playerid, g_dialog_select[playerid][listitem]);
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Помещение было отмечено на Вашем GPS навигаторе. " #cGRAY "(/gps - отмена)");
	}
	else if (dialogid == D_GPS + 5)
	{
		if (!response)
		{
			cmd_amenu(playerid);
			return 1;
		}
		
		ShowGPSList(playerid, D_GPS + 6, listitem + 1);
	}
	else if (dialogid == D_GPS + 6)
	{
		if (!response)
		{
			ShowAdminTeleportList(playerid, GPS_MAIN_CATEGORY);
			return 1;
		}
		
		new index = g_dialog_select[playerid][listitem];
		
		Move:player(
			playerid,
			gps_list[index][gps_pos][0], 
			gps_list[index][gps_pos][1], 
			gps_list[index][gps_pos][2]
		);
	}
	
	return 1;
}

// Functions
ShowGPSList(playerid, dialogid, cat)
{
	clean:<g_big_string>;
	
	new count;
	
	for (new i; i < sizeof gps_list; i++)
	{
		if (cat != gps_list[i][gps_cat])
		{
			continue;
		}
		
		format:g_big_string("%s %s\n", g_big_string, gps_list[i][gps_text]);
		g_dialog_select[playerid][count++] = i; 
	}
	
	if (cat == GPS_MAIN_CATEGORY)
	{
		strcat(g_big_string, " Местоположение личного транспорта\n \
			 Местоположеное жилищного помещения\n \
			 Местоположение помещения" 
		);
	}
	
	SetPVarInt(playerid, "GPS:Count", count);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", g_big_string, "Далее", "Закрыть");
}

ShowAdminTeleportList(playerid, cat = GPS_MAIN_CATEGORY)
{
	clean:<g_big_string>;
	
	new count;
	
	for (new i; i < sizeof gps_list; i++)
	{
		if (cat != gps_list[i][gps_cat])
		{
			continue;
		}
		
		format:g_big_string("%s %s\n", g_big_string, gps_list[i][gps_text]);
		g_dialog_select[playerid][count++] = i; 
	}
	
	ShowPlayerDialog(playerid, D_GPS + 5, DIALOG_STYLE_LIST, "Телепортироваться", g_big_string, "Далее", "Закрыть");
}

SetIncludeGPS(playerid, Float: x, Float: y, Float: z)
{
	if (IsGPSIncluded(playerid))
	{
		DisablePlayerCheckpoint(playerid);
	}
	
	SetPlayerCheckpoint(playerid, x, y, z, 3.0);
	player_gps{playerid} = 1;
}

FindVehicleOfPlayer(playerid)
{
	if (!ShowVehicleList(playerid, D_GPS + 2, "Выбрать", "Назад"))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CAR);
	}
	
	return 1;
}

FindHouseOfPlayer(playerid)
{
	if (!ShowHouseList(playerid, D_GPS + 3, "Выбрать", "Назад"))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_HOUSE);
	}
	
	return 1;
}

FindPremiseOfPlayer(playerid)
{
	if (!ShowPremiseList(playerid, D_GPS + 4, "Выбрать", "Назад"))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_PREMISE);
	}
	
	return 1;
}

// Commands
CMD:gps(playerid)
{
	if (fuber_driver_start_area[playerid] != INVALID_STREAMER_ID)
	{
		SendClientMessage(playerid, C_WHITE, #ERROR " Вы не можете использовать GPS в данный момент.");
		return 1;
	}

	if (IsGPSIncluded(playerid))
	{
		DisablePlayerCheckpoint(playerid);
		player_gps{playerid} = 0;
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы убрали указанную метку на GPS навигаторе.");
	}
	
	ShowGPSList(playerid, D_GPS, GPS_MAIN_CATEGORY);
	return 1;
}