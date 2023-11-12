
enum E_TMP_FACTION_DUTY
{
	f_id,
	Float: f_pos[3],
}

new tmp_faction_duty [][E_TMP_FACTION_DUTY] =
{
	{FRACTION_PD, {1066.3141,1924.2925,1504.2787}}, // saints
	{FRACTION_PD, {-347.1355,2535.1946,1504.4490}}, // hq
	{FRACTION_PD, {875.6721,878.0556,1503.8021}}, // verona
	
	{FRACTION_SD, {2377.9919,562.3474,2500.9688}}, // ls
	{FRACTION_SD, {351.3710,2325.0142,1504.3427}}, // blueberry
	
	{FRACTION_NP, {-15.6952,2029.2394,1504.0242}} // np
};

enum E_TMP_FACTION_STOCK
{
	f_id,
	Float: f_pos[3],
}

new tmp_faction_stock [][E_TMP_FACTION_STOCK] =
{
	{FRACTION_PD, {1063.4415,2450.9316,1500.7565}}, // saints
	{FRACTION_PD, {-116.0587,1097.5430,1604.0436}}, // hq
	{FRACTION_PD, {1373.5503,897.9427,1503.8021}}, // verona
	
	{FRACTION_SD, {2365.0078,548.9154,2500.9688}}, // ls
	{FRACTION_SD, {332.1859,2314.5383,1504.3427}}, // blueberry
	
	{FRACTION_NP, {-10.2806,2053.9685,1504.0242}} // np
};

new pd_skins [] =
{
	265,
	266,
	267,
	280,
	281,
	283,
	284,
	285,
	288,
	300,
	301,
	302,
	303,
	304,
	305,
	310,
	311
};

new sd_skins [] =
{
	265,
	266,
	267,
	280,
	281,
	283,
	284,
	285,
	288,
	300,
	301,
	302,
	303,
	304,
	305,
	310,
	311,
	306,
	307,
	309
};

new np_skins [] =
{
	311,
	310,
	305,
	304,
	303,
	302,
	282,
	309
};

new move_objects 			[20],
	move_objects_status 	[20];
	

enum E_TMP_FACTION_GARAGE
{
	Float: f_pos		[4],
	Float: f_pos_end 	[4],
	f_int,
	f_world
}

new faction_garage [][E_TMP_FACTION_GARAGE] = 
{
	{{1588.3870,-1634.1078,13.1134,0.1921}, {1932.6331,294.9254,2792.5850,198.5401}, INT_OTHER, WORLD_PD_HEADQUARTERS},
	{{988.5991,-1587.3367,13.2681,0.9270}, {1932.6331,294.9254,2792.5850,198.5401}, INT_OTHER, WORLD_PD_96_VERONA},
	{{2784.2678,-1444.4941,30.1102,180.3634}, {1932.6331,294.9254,2792.5850,198.5401}, INT_OTHER, WORLD_PD_64_SAINTS},
	{{2380.7434,-1937.7092,13.2633,89.9945}, {1932.6331,294.9254,2792.5850,198.5401}, INT_OTHER, WORLD_SD_LOSSANTOS}
};

FractionTmpGameMode()
{
	// Транспорт
	Gov_Vehicles();
	LSPD_HQ_Vehicles();
	LSPD_Verona_Vehicles();
	LSPD_Saints_Vehicles();
	SD_Blueberry_Vehicles();
	SD_LS_Vehicles();
	
	for (new i; i < sizeof tmp_faction_duty; i++)
	{
		CreatePickupWith3DTextLabel(
			"Раздевалка", 
			1275, 
			tmp_faction_duty[i][f_pos][0], 
			tmp_faction_duty[i][f_pos][1], 
			tmp_faction_duty[i][f_pos][2]
		);
	}
	
	for (new i; i < sizeof tmp_faction_stock; i++)
	{
		CreatePickupWith3DTextLabel(
			"Склад", 
			INVALID_PARAM, 
			tmp_faction_stock[i][f_pos][0], 
			tmp_faction_stock[i][f_pos][1], 
			tmp_faction_stock[i][f_pos][2]
		);
	}
}

function Frac_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{
		new findex = GetFractionMember(playerid);
		
		for (new i; i < sizeof tmp_faction_duty; i++)
		{
			if (IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, 
			tmp_faction_duty[i][f_pos][0], 
			tmp_faction_duty[i][f_pos][1], 
			tmp_faction_duty[i][f_pos][2]))
			{
				if (findex != INVALID_PARAM)
				{
					new id = GetFractionId(findex);
					
					ShowSkins(playerid, id);
					return 0;
				}
			}
		}
		
		for (new i; i < sizeof tmp_faction_stock; i++)
		{
			if (IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, 
			tmp_faction_stock[i][f_pos][0], 
			tmp_faction_stock[i][f_pos][1], 
			tmp_faction_stock[i][f_pos][2]))
			{
				if (findex != INVALID_PARAM)
				{					
					ShowFractionItemList(playerid, D_FRACTION + 17, findex);
					return 0;
				}
			}
		}
	}
	
	if(PRESSED(KEY_CROUCH))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		if (vehicleid > 0)
		{
			for (new i; i < sizeof faction_garage; i++)
			{
				if (GetPlayerVirtualWorld(playerid) == 0
				&& IsPlayerInRangeOfPoint(playerid, 
					10.0, 
					faction_garage[i][f_pos][0], 
					faction_garage[i][f_pos][1], 
					faction_garage[i][f_pos][2])) 
				{
					Move:vehicle(vehicleid, 
						faction_garage[i][f_pos_end][0], 
						faction_garage[i][f_pos_end][1], 
						faction_garage[i][f_pos_end][2],
						faction_garage[i][f_world],
						faction_garage[i][f_int]
					);
					
					return 0;
				}
				else if (GetPlayerVirtualWorld(playerid) != 0
				&& IsPlayerInRangeOfPoint(playerid, 
					10.0, 
					faction_garage[i][f_pos_end][0], 
					faction_garage[i][f_pos_end][1], 
					faction_garage[i][f_pos_end][2])) 
				{
					Move:vehicle(vehicleid, 
						faction_garage[i][f_pos][0], 
						faction_garage[i][f_pos][1], 
						faction_garage[i][f_pos][2],
						0,
						0
					);
					
					return 0;
				}
			}
		}
	}
	
	return 1;
}

ShowSkins(playerid, id)
{
	clean:<g_big_string>;
	
	SetPVarInt(playerid, "FractionTmp:Type", id);
	
	for (new i; i < sizeof pd_skins; i++)
	{
		if (id == FRACTION_PD)
		{
			format:g_big_string("%s Одежда #%d\n", g_big_string, pd_skins[i]);
		}
		else if (id == FRACTION_SD)
		{
			format:g_big_string("%s Одежда #%d\n", g_big_string, sd_skins[i]);
		}
		else if (id == FRACTION_NP)
		{
			format:g_big_string("%s Одежда #%d\n", g_big_string, np_skins[i]);
		}
	}
	
	ShowPlayerDialog(playerid, D_FRACTION + 16, DIALOG_STYLE_LIST, "Дежурство", g_big_string, "Выбрать", "Закрыть");
}

CMD:setsub(playerid, params[])
{
	new findex = GetFractionMember(playerid),
		id = GetFractionId(findex);
	
	new value;
	
	if (id == FRACTION_PD)
	{
		if (sscanf(params, "d", value))
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /setsub [номер станции (1-3)]");
			return 1;
		}
	
		if ((1 <= value <= 3))
		{
			character_data[playerid][c_fraction_sub] = value;
			Update:character_int(playerid, "c_fraction_sub", value);
		}
	}
	else if (id == FRACTION_SD)
	{
		if (sscanf(params, "d", value))
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /setsub [номер станции (1-2)]");
			return 1;
		}
		
		if ((1 <= value <= 2))
		{
			character_data[playerid][c_fraction_sub] = value;
			Update:character_int(playerid, "c_fraction_sub", value);
		}
	}
	
	return 1;
}