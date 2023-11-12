/*!
	@brief Система гаража для системы домов
	@author Found (evg.savosin)
	@date 16.12.2016, update 21.03.2018
*/

Garage_OnGameModeInit()
{
	GarageInteriorObjects();
	
	for (new i = 1; i < sizeof hgarage_settings; i++)
	{
		CreateDynamic3DTextLabel(
			"Улица", 
			-1, 
			hgarage_settings[i][hgset_pos][0], 
			hgarage_settings[i][hgset_pos][1], 
			hgarage_settings[i][hgset_pos][2] - 0.2, 
			TEXT3D_DRAW_DISTANCE, 
			_, 
			_, 
			_, 
			_,
			INT_GARAGE,
			_, 
			TEXT3D_DRAW_DISTANCE
		);
		
		CreateDynamic3DTextLabel(
			"Войти в дом\n" #cPROJECT "H", 
			-1, 
			hgarage_settings[i][hgset_alt_pos][0], 
			hgarage_settings[i][hgset_alt_pos][1], 
			hgarage_settings[i][hgset_alt_pos][2] - 0.2, 
			TEXT3D_DRAW_DISTANCE, 
			_, 
			_, 
			_, 
			_,
			INT_GARAGE,
			_, 
			TEXT3D_DRAW_DISTANCE
		);
	}
}

function OnHouseGarageLoad(index)
{
	new rows;
	
	cache_get_row_count(rows);
	
	if (rows == 0)
	{
		return 1;
	}
	
	cache_get_value_name_int(0, "g_type", house_data[index][hg_int_type]);
	
	cache_get_value_name_float(0, "g_pos_x", house_data[index][hg_pos][0]);
	cache_get_value_name_float(0, "g_pos_y", house_data[index][hg_pos][1]);
	cache_get_value_name_float(0, "g_pos_z", house_data[index][hg_pos][2]);
	cache_get_value_name_float(0, "g_pos_angle", house_data[index][hg_pos][3]);
	
	cache_get_value_name_float(0, "g_veh_pos_x", house_data[index][hg_veh_pos][0]);
	cache_get_value_name_float(0, "g_veh_pos_y", house_data[index][hg_veh_pos][1]);
	cache_get_value_name_float(0, "g_veh_pos_z", house_data[index][hg_veh_pos][2]);
	cache_get_value_name_float(0, "g_veh_pos_angle", house_data[index][hg_veh_pos][3]);
	
	cache_get_value_name_float(0, "g_addveh_pos_x", house_data[index][hg_addveh_pos][0]);
	cache_get_value_name_float(0, "g_addveh_pos_y", house_data[index][hg_addveh_pos][1]);
	cache_get_value_name_float(0, "g_addveh_pos_z", house_data[index][hg_addveh_pos][2]);
	cache_get_value_name_float(0, "g_addveh_pos_angle", house_data[index][hg_addveh_pos][3]);
	
	cache_get_value_name_int(0, "g_lock", house_data[index][hg_lock]);
	cache_get_value_name_int(0, "g_set_furn", house_data[index][hg_set_furn]);
	
	Create:garage(index);

	return 1;
}

HGarage_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{	
		for (new i, gtype, htype; i < sizeof house_data; i++)
		{
			if (GetHouseId(i) == 0)
			{
				continue;
			}
			
			gtype = house_data[i][hg_int_type];
			htype = house_data[i][h_int_type];
			
			if (GetPlayerVirtualWorld(playerid) == 0
			&& IsPlayerInRangeOfPoint(playerid, 
				FACTOR_TELEPORT_RADIUS, 
				house_data[i][hg_pos][0], 
				house_data[i][hg_pos][1], 
				house_data[i][hg_pos][2]) 
			)
			{
				if (house_data[i][hg_lock])
				{
					GameTextForPlayer(playerid, "~w~CLOSED", 2000, 4);
					return 1;
				}
				
				Move:player(playerid, 
					hgarage_settings[gtype][hgset_pos][0], 
					hgarage_settings[gtype][hgset_pos][1], 
					hgarage_settings[gtype][hgset_pos][2], 
					house_data[i][h_id], 
					INT_GARAGE,
					true,
					hgarage_settings[gtype][hgset_pos][3]
				);	
				
				return 0;
			}
	
			else if (house_data[i][h_id] == GetPlayerVirtualWorld(playerid) 
			&& IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, 
				hgarage_settings[gtype][hgset_pos][0], 
				hgarage_settings[gtype][hgset_pos][1], 
				hgarage_settings[gtype][hgset_pos][2])
			)
			{
				if (house_data[i][hg_lock])
				{
					GameTextForPlayer(playerid, "~w~CLOSED", 2000, 4);
					return 1;
				}
				
				Move:player(playerid, 
					house_data[i][hg_pos][0], 
					house_data[i][hg_pos][1], 
					house_data[i][hg_pos][2],
					_, 
					_,
					true,
					house_data[i][hg_pos][3]
				);	
				
				return 0;
			}
			
			else if (house_data[i][h_id] == GetPlayerVirtualWorld(playerid) 
			&& IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, 
				hgarage_settings[gtype][hgset_alt_pos][0], 
				hgarage_settings[gtype][hgset_alt_pos][1], 
				hgarage_settings[gtype][hgset_alt_pos][2])
			)
			{
				Move:player(playerid, 
					house_settings[htype][hset_pos][0], 
					house_settings[htype][hset_pos][1], 
					house_settings[htype][hset_pos][2], 
					house_data[i][h_id], 
					INT_HOUSE,
					true,
					house_settings[htype][hset_pos][3]
				);
				
				return 0;
			}
		}
	}
	else if (PRESSED(KEY_FIRE))
	{
		new vehicleid = GetPlayerVehicleID(playerid);
			
		if (vehicleid && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			for (new i, gtype; i < sizeof house_data; i++)
			{
				if (!house_data[i][h_id])
				{
					continue;
				}
				
				gtype = house_data[i][hg_int_type];
				
				if (GetPlayerVirtualWorld(playerid) == 0
				&& IsPlayerInRangeOfPoint(playerid, 
				FACTOR_TELEPORT_RADIUS, 
				house_data[i][hg_veh_pos][0], 
				house_data[i][hg_veh_pos][1], 
				house_data[i][hg_veh_pos][2]))
				{
					if (house_data[i][hg_lock])
					{
						GameTextForPlayer(playerid, "~w~Closed", 2000, 4);
						return 1;
					}
					
					Move:vehicle(
						vehicleid, 
						hgarage_settings[gtype][hgset_veh_pos][0], 
						hgarage_settings[gtype][hgset_veh_pos][1], 
						hgarage_settings[gtype][hgset_veh_pos][2], 
						house_data[i][h_id], 
						INT_GARAGE, 
						true, 
						hgarage_settings[gtype][hgset_veh_pos][3] 
					);	
					
					return 0;
				}
				else if (GetPlayerVirtualWorld(playerid) == house_data[i][h_id]
				&& IsPlayerInRangeOfPoint(playerid, 
				FACTOR_TELEPORT_RADIUS, 
				hgarage_settings[gtype][hgset_veh_pos][0], 
				hgarage_settings[gtype][hgset_veh_pos][1], 
				hgarage_settings[gtype][hgset_veh_pos][2]))
				{
					if (house_data[i][hg_lock])
					{
						GameTextForPlayer(playerid, "~w~Closed", 2000, 4);
						return 1;
					}
					
					Move:vehicle(
						vehicleid, 
						house_data[i][hg_veh_pos][0], 
						house_data[i][hg_veh_pos][1], 
						house_data[i][hg_veh_pos][2],
						_, 
						_, 
						true, 
						house_data[i][hg_veh_pos][3]
					);	
					
					return 0;
				}
				else 
				{
					if (house_data[i][hg_int_type] != 3)
					{
						continue;
					}
					
					/// Additional vehicle pos
					if (GetPlayerVirtualWorld(playerid) == 0
					&& IsPlayerInRangeOfPoint(playerid, 
					FACTOR_TELEPORT_RADIUS, 
					house_data[i][hg_addveh_pos][0], 
					house_data[i][hg_addveh_pos][1], 
					house_data[i][hg_addveh_pos][2]))
					{
						if (house_data[i][hg_lock])
						{
							GameTextForPlayer(playerid, "~w~Closed", 2000, 4);
							return 1;
						}
						
						Move:vehicle(
							vehicleid, 
							hgarage_settings[gtype][hgset_addveh_pos][0], 
							hgarage_settings[gtype][hgset_addveh_pos][1], 
							hgarage_settings[gtype][hgset_addveh_pos][2], 
							house_data[i][h_id], 
							INT_GARAGE, 
							true, 
							hgarage_settings[gtype][hgset_addveh_pos][3] 
						);	
						
						return 0;
					}
					else if (GetPlayerVirtualWorld(playerid) == house_data[i][h_id]
					&& IsPlayerInRangeOfPoint(playerid, 
						FACTOR_TELEPORT_RADIUS, 
						hgarage_settings[gtype][hgset_addveh_pos][0], 
						hgarage_settings[gtype][hgset_addveh_pos][1], 
						hgarage_settings[gtype][hgset_addveh_pos][2]) 
					)
					{
						if (house_data[i][hg_lock])
						{
							GameTextForPlayer(playerid, "~w~Closed", 2000, 4);
							return 1;
						}
						
						Move:vehicle(
							vehicleid, 
							house_data[i][hg_addveh_pos][0], 
							house_data[i][hg_addveh_pos][1], 
							house_data[i][hg_addveh_pos][2],
							_, 
							_, 
							true, 
							house_data[i][hg_addveh_pos][3]
						);	
						
						return 0;
					}
				}
			}
		}
	}
	
	if (PRESSED(KEY_NO))
	{
		if (!IsPlayerRenovation(playerid))
		{
			if (HouseMenu(playerid, false))
			{
				return 0;
			}
		}
	}
	
	return 1;
}

Create:garage(index)
{
	house_data[index][hg_text] = CreateDynamic3DTextLabel(
		"Гараж\n" #cPROJECT "ALT",
		-1, 
		house_data[index][hg_pos][0], 
		house_data[index][hg_pos][1], 
		house_data[index][hg_pos][2] - 0.2, 
		TEXT3D_DRAW_DISTANCE, 
		_, 
		_, 
		0, 
		_,
		_,
		-1, 
		TEXT3D_DRAW_DISTANCE
	);
	
	if (!house_data[index][hg_set_furn])
	{
		Create:static_furn(index, house_data[index][hg_int_type]);
	}
	else 
	{
		Load:furn(house_data[index][h_id], index, TYPE_REN_GARAGE);
	}
}

Destroy:garage(index)
{
	if (IsValidDynamic3DTextLabel(house_data[index][hg_text]))
	{
		DestroyDynamic3DTextLabel(house_data[index][hg_text]);
	}
	
	if (house_data[index][hg_set_furn])
	{
		Remove:all_furn_data(index, TYPE_REN_GARAGE);
	}
	else 
	{
		Destroy:static_furn(index);
	}
}

GetGarageAroundOfPlayer(playerid)
{
	for (new i; i < sizeof house_data; i++)
	{
		if (GetPlayerDistanceFromPoint(playerid, 
			house_data[i][h_pos][0],
			house_data[i][h_pos][1],
			house_data[i][h_pos][2]
		) <= 3.0 || IsPlayerInGarage(playerid, i))
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

IsPlayerInGarage(playerid, index, Float: distance = 30.0)
{
	if (index == INVALID_PARAM)
	{
		return 0;
	}
	
	if (GetPlayerInterior(playerid) != INT_GARAGE)
	{
		return 0;
	}
	
	if (GetHouseId(index) != GetCharacterWorld(playerid))
	{
		return 0;
	}
	
	new type;
	
	if ((type = house_data[index][hg_int_type]) == 0)
	{
		return 0;
	}
	
	return (GetPlayerDistanceFromPoint(playerid,
		hgarage_settings[type][hgset_pos][0],
		hgarage_settings[type][hgset_pos][1],
		hgarage_settings[type][hgset_pos][2]) <= distance);
}

GarageLock(playerid, index = INVALID_PARAM)
{
	if (index == INVALID_PARAM)
	{
		index = GetGarageAroundOfPlayer(playerid);
			
		if (index == INVALID_PARAM)
		{
			return;
		}
		
		if (!CheckHouseAccess(TYPE_HOUSE_LODGER, playerid, index, lod_perm_garage))
		{
			return;
		}
	}
	
	house_data[index][hg_lock] = !house_data[index][hg_lock];
	GameTextForPlayer(playerid, (house_data[index][hg_lock]) ? ("~r~LOCKED") : ("~g~UNLOCKED"), 2000, 4);
}

Create:static_furn(index, type)
{
	new world = GetHouseId(index),
		tmpobjid;
		
	switch(type)
	{
		case 1 :
		{
			hgarage_static_furn[index][0] = CreateDynamicObject(994, -1576.014160, -1780.325073, 2500.868896, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(hgarage_static_furn[index][0], 0, 10837, "airroadsigns_sfse", "CJ_LAMPPOST1", 0x00000000);
			tmpobjid = CreateDynamicObject(19990, -1577.863769, -1777.231689, 2499.118408, 0.000000, -3.299998, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 19480, "signsurf", "sign", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
			tmpobjid = CreateDynamicObject(14826, -1578.427490, -1783.456665, 2501.668457, 0.000000, 0.000000, -37.900009, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 19480, "signsurf", "sign", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 4, 19480, "signsurf", "sign", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 5, 19480, "signsurf", "sign", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 6, 19480, "signsurf", "sign", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 7, 19480, "signsurf", "sign", 0x00000000);
			tmpobjid = CreateDynamicObject(2569, -1577.406738, -1776.823974, 2500.198974, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 119480, "signsurf", "sign", 0xFFFFFAFA);
			SetDynamicObjectMaterial(tmpobjid, 1, 10778, "airportcpark_sfse", "ws_crashbarrier", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 2, 19480, "signsurf", "sign", 0x00000000);
			tmpobjid = CreateDynamicObject(19966, -1577.869628, -1778.307739, 2499.879638, 0.000000, 5.099998, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 19480, "signsurf", "sign", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
			tmpobjid = CreateDynamicObject(2659, -1573.600585, -1773.463745, 2499.968750, 90.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 16640, "a51", "ventb128", 0x00000000);
			tmpobjid = CreateDynamicObject(2659, -1573.600585, -1775.373901, 2499.968750, 90.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 16640, "a51", "ventb128", 0x00000000);
			tmpobjid = CreateDynamicObject(2659, -1573.600585, -1777.284179, 2499.968750, 90.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 16640, "a51", "ventb128", 0x00000000);
			tmpobjid = CreateDynamicObject(19815, -1577.875976, -1775.316406, 2501.768554, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19903, -1570.104980, -1779.566284, 2499.968750, 0.000000, 0.000000, 180.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(18633, -1575.315673, -1779.665161, 2500.858398, 0.000000, 90.000000, 61.099998, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19900, -1575.421142, -1779.701660, 2499.968750, 0.000000, 0.000000, -7.099998, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19621, -1575.488769, -1779.792236, 2500.938964, 0.000000, 0.000000, 42.699996, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(3632, -1570.117675, -1778.799560, 2500.448730, 0.000000, 0.000000, -32.600002, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1348, -1577.341064, -1771.782470, 2500.638916, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1431, -1573.716796, -1779.885375, 2500.508789, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1098, -1577.383056, -1774.230224, 2500.418701, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19996, -1572.336914, -1779.787963, 2499.968750, 0.000000, 0.000000, -160.999984, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1098, -1577.383056, -1774.540527, 2500.418701, 0.000000, 0.000000, -88.600036, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1098, -1577.374755, -1774.880615, 2500.418701, 0.000000, 0.000000, -88.600036, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1098, -1577.365966, -1775.240844, 2500.418701, 0.000000, 0.000000, -80.200027, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19996, -1577.561035, -1772.924804, 2499.968750, 0.000000, 0.000000, 72.599998, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1220, -1577.485107, -1775.834350, 2500.299072, 0.000000, 0.000000, 2.499999, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1558, -1570.366210, -1783.185913, 2501.563964, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19848, -1578.026367, -1775.314575, 2499.993164, 0.000000, 0.000000, 540.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(918, -1570.173095, -1783.379760, 2502.363769, 0.000000, 0.000000, 179.500015, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(3034, -1569.767089, -1773.938354, 2501.979003, 0.000000, 0.000000, 270.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(922, -1573.311279, -1783.290283, 2501.869628, 0.000000, 0.000000, 360.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1449, -1569.976806, -1777.156127, 2500.458984, 0.000000, 0.000000, 270.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19921, -1577.233154, -1776.325927, 2501.029052, 0.000000, 0.000000, 117.300025, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19918, -1577.634765, -1775.932373, 2500.958740, 0.000000, 0.000000, -17.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(11713, -1577.850830, -1773.281494, 2501.778808, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1650, -1572.874023, -1779.696411, 2500.799316, 0.000000, 0.000000, -18.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19572, -1573.278808, -1779.838378, 2501.058837, 0.000000, 0.000000, 55.100002, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1841, -1577.524414, -1774.021240, 2500.948730, 0.000000, 0.000000, 143.399993, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19624, -1571.461181, -1783.180175, 2502.327636, -17.600000, 0.000000, 101.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19825, -1577.831054, -1776.887939, 2502.678955, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1893, -1574.059570, -1781.490356, 2503.838867, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1893, -1574.059570, -1777.940185, 2503.658935, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1893, -1574.059570, -1773.990356, 2503.658935, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2066, -1577.324218, -1777.313842, 2499.948730, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			hgarage_static_furn[index][1] = CreateDynamicObject(1738, -1569.931152, -1773.815307, 2500.390625, 0.000000, 0.000000, 270.000000, world, INT_GARAGE); 
		}
		
		case 2 :
		{
			hgarage_static_furn[index][0] = CreateDynamicObject(2063, -521.554077, 1798.962768, 1237.751342, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 14738, "whorebar", "AH_wdblinds", 0xFFFFFFFF);
			SetDynamicObjectMaterial(tmpobjid, 1, 8419, "vgsbldng1", "buildng01_64", 0x00000000);
			tmpobjid = CreateDynamicObject(2210, -521.119201, 1806.460571, 1237.534667, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
			tmpobjid = CreateDynamicObject(19921, -517.242492, 1797.993530, 1238.167114, 0.000000, 0.000000, 180.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "greenbackgroundsign", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19921, -517.242492, 1797.993530, 1238.367065, 0.000000, 0.000000, 180.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "greenbackgroundsign", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2289, -512.092224, 1806.781250, 1239.185180, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 14530, "estate2", "Auto_hustler", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 1, 14652, "ab_trukstpa", "CJ_WOOD6", 0x00000000);
			tmpobjid = CreateDynamicObject(2286, -513.808288, 1806.793823, 1238.415771, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 14530, "estate2", "Auto_Slamvan2", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
			tmpobjid = CreateDynamicObject(19477, -512.884826, 1797.475463, 1239.365234, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 12853, "cunte_gas01", "starspangban1_256", 0x00000000);
			tmpobjid = CreateDynamicObject(2286, -519.668884, 1806.793823, 1238.625976, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 14654, "ab_trukstpe", "bbar_signs1", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
			tmpobjid = CreateDynamicObject(1550, -521.524475, 1803.434204, 1237.195312, 0.000000, 0.000000, 148.199966, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 19480, "signsurf", "sign", 0x00000000);
			tmpobjid = CreateDynamicObject(2286, -521.809020, 1798.952270, 1239.086303, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 14654, "ab_trukstpe", "bbar_plates2", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
			tmpobjid = CreateDynamicObject(936, -521.335815, 1801.217407, 1237.311767, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19828, -521.821289, 1804.142578, 1238.052246, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19899, -516.280029, 1797.893676, 1236.854003, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19899, -518.859191, 1797.900146, 1235.614013, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(3632, -511.289825, 1806.460815, 1237.323974, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(3632, -511.297729, 1805.820068, 1237.323974, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2752, -520.875854, 1806.593750, 1238.086059, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(1650, -520.382080, 1806.277343, 1237.155273, 0.000000, 0.000000, 12.300001, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19900, -514.676269, 1797.756835, 1236.854980, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2689, -517.614379, 1798.442382, 1238.974853, -7.000000, 0.000000, 230.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19903, -521.484069, 1802.581542, 1236.855468, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19815, -516.790405, 1806.839721, 1238.745605, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(936, -516.874694, 1806.278686, 1237.311767, 0.000000, 0.000000, 360.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19921, -517.366760, 1806.163818, 1237.865600, 0.000000, 0.000000, 16.999998, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(11706, -520.529724, 1797.954101, 1236.835083, 0.000000, 0.000000, 34.399997, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19825, -521.790893, 1801.441894, 1239.645141, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2587, -518.172241, 1797.523681, 1238.974975, 0.000000, 0.000000, 180.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(1650, -520.465820, 1806.506591, 1237.155273, 0.000000, 0.000000, -30.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2752, -520.769897, 1806.605957, 1238.086059, 0.000000, 0.000000, 37.699993, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2749, -520.800842, 1806.555541, 1238.085815, 0.000000, 0.000000, -131.700027, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2749, -521.051574, 1806.604614, 1238.085815, 0.000000, 0.000000, -131.700027, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2752, -520.938110, 1806.618408, 1238.086059, 0.000000, 0.000000, -174.900009, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2000, -518.063415, 1806.314941, 1236.845092, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19917, -521.340637, 1801.296264, 1237.766357, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(1437, -521.067016, 1803.355346, 1236.833740, -2.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19621, -515.988830, 1797.808105, 1238.206909, 0.000000, 0.000000, -150.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(18633, -516.305419, 1797.932250, 1238.956054, 0.000000, 90.000000, 190.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(18633, -516.247497, 1798.075195, 1238.956054, 0.000000, 90.000000, 190.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(3017, -516.549682, 1805.982299, 1237.796020, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2000, -518.573913, 1806.314941, 1236.845092, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(1893, -514.658447, 1802.145141, 1240.817016, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(1893, -518.770263, 1802.145141, 1240.817016, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2836, -520.682800, 1804.619140, 1236.854736, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1082, -518.737976, 1797.877441, 1237.194946, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1082, -519.018005, 1797.877441, 1237.194946, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1082, -519.548217, 1797.877441, 1237.194335, 0.000000, 360.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1082, -519.297973, 1797.877441, 1237.194335, 0.000000, 360.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2969, -511.330078, 1797.839721, 1236.974121, 0.000000, 0.000000, 30.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2969, -511.330078, 1797.839843, 1237.214111, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2103, -519.104614, 1797.809692, 1238.128051, 0.000000, 0.000000, 160.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(3025, -521.810119, 1803.055297, 1240.336059, -0.740000, 0.000000, 90.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19621, -516.109497, 1797.813720, 1238.206909, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(18634, -516.972351, 1797.784423, 1238.952148, 0.000000, 90.000000, 50.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(18634, -516.530212, 1797.918579, 1238.952148, 0.000000, 90.000000, 50.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(18635, -515.613403, 1797.827636, 1238.916748, 90.000000, 90.000000, -30.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(18635, -515.781127, 1797.764892, 1238.916748, 90.000000, 90.000000, -30.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(341, -515.975891, 1798.048583, 1238.550048, 90.000000, 0.000000, -10.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1082, -519.828491, 1797.877441, 1237.194335, 0.000000, 360.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1759, -515.510803, 1806.311767, 1236.835083, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19918, -516.147888, 1806.627685, 1237.785644, 0.000000, 0.000000, -5.799999, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19572, -521.544616, 1799.965942, 1238.535278, 0.000000, 0.000000, -55.099994, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19624, -517.749694, 1797.783691, 1238.545532, 0.000000, 0.000000, -104.799980, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2690, -515.836730, 1806.668823, 1237.205444, 0.000000, 0.000000, -69.999992, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2426, -521.626708, 1799.665283, 1237.675781, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2855, -518.495056, 1806.535400, 1238.245971, 0.000000, 0.000000, 2.900002, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(18978, -521.304809, 1806.432495, 1237.914794, 0.000000, -26.600000, -49.699996, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19623, -521.308959, 1806.400512, 1238.146240, 0.000000, 0.000000, 17.800003, world, INT_GARAGE); 
			hgarage_static_furn[index][1] = CreateDynamicObject(2828, -521.158508, 1806.428588, 1237.565307, 0.000000, 0.000000, 180.000000, world, INT_GARAGE); 
		}
		
		case 3 :
		{
			hgarage_static_furn[index][0] = CreateDynamicObject(18783, 1249.800781, -17.996656, 1005.889648, 0.000000, 180.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 14665, "genintint711_1", "interiorwindowglow", 0xFF464646);
			SetDynamicObjectMaterial(tmpobjid, 1, 10023, "bigwhitesfe", "sfe_arch10", 0x00000000);
			tmpobjid = CreateDynamicObject(1235, 1270.783325, -19.383911, 1000.380065, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19827, 1271.170898, -15.087403, 1001.272521, 0.000000, 0.000000, 270.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2387, 1265.486206, -16.880453, 999.917480, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 19480, "signsurf", "sign", 0xFFFFFFFF);
			SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 3, 10765, "airportgnd_sfse", "white", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 4, 1560, "7_11_door", "cj_sheetmetal2", 0x00000000);
			tmpobjid = CreateDynamicObject(19787, 1269.029174, -24.742124, 1001.924743, 3.199999, 0.000000, 180.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "cj_sheetmetal2", 0xFF464646);
			tmpobjid = CreateDynamicObject(19918, 1268.710937, -24.345211, 1000.934814, 0.000000, 0.000000, 12.399997, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2713, 1267.862060, -24.433763, 1000.068298, 0.000000, 0.000000, 60.499996, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19903, 1264.139770, -17.653570, 999.927856, 0.000000, 0.000000, -144.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19815, 1271.167724, -21.280855, 1001.439697, 0.000000, 0.000000, 270.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2063, 1269.936157, -9.061835, 1000.831542, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "cj_sheetmetal2", 0xFFFFFFFF);
			SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
			tmpobjid = CreateDynamicObject(2063, 1270.975952, -10.091823, 1000.829589, 0.000000, 0.000000, 270.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "cj_sheetmetal2", 0xFFFFFFFF);
			SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
			tmpobjid = CreateDynamicObject(19622, 1271.045043, -11.836882, 1000.624389, -10.499999, 0.000000, -86.299995, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2063, 1267.345336, -9.061835, 1000.831542, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "cj_sheetmetal2", 0xFFFFFFFF);
			SetDynamicObjectMaterial(tmpobjid, 1, 19480, "signsurf", "sign", 0x00000000);
			tmpobjid = CreateDynamicObject(18890, 1267.106933, -9.031935, 1000.209777, 90.000000, 90.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19921, 1266.699829, -16.393722, 1000.017456, 0.000000, 0.000000, -152.099990, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(18633, 1269.275878, -8.910313, 1000.768432, 0.000000, 90.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(18633, 1269.345947, -9.000314, 1000.768432, 0.000000, 90.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(18633, 1269.426025, -9.080315, 1000.768432, 0.000000, 90.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(1650, 1270.302001, -9.749894, 1000.221313, 0.000000, 0.000000, -118.000015, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(1650, 1270.683227, -9.975752, 999.973083, 90.000000, 90.000000, -88.000015, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(633, 1261.048950, -16.847902, 1000.896057, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2749, 1266.067626, -16.511224, 1000.930786, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19814, 1263.643676, -16.776113, 1000.246093, 0.000000, 0.000000, 90.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(19814, 1268.333251, -24.766119, 1001.036132, 0.000000, 0.000000, 180.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2723, 1269.193481, -22.894781, 1000.235107, 0.000000, 0.000007, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "CJ_CHROME2", 0xFFFFFFFF);
			SetDynamicObjectMaterial(tmpobjid, 1, 14665, "genintint711_1", "interiorwindowglow", 0x00000000);
			tmpobjid = CreateDynamicObject(2689, 1267.770996, -16.776700, 1001.444152, 0.000000, 0.000000, 450.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
			tmpobjid = CreateDynamicObject(2725, 1268.897460, -22.279350, 1000.351318, 0.000000, 0.000007, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "CJ_CHROME2", 0xFFFFFFFF);
			SetDynamicObjectMaterial(tmpobjid, 1, 14665, "genintint711_1", "interiorwindowglow", 0x00000000);
			SetDynamicObjectMaterial(tmpobjid, 2, 19480, "signsurf", "sign", 0x00000000);
			tmpobjid = CreateDynamicObject(2723, 1269.223510, -21.694782, 1000.235107, 0.000000, 0.000007, 0.000000, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "CJ_CHROME2", 0xFFFFFFFF);
			SetDynamicObjectMaterial(tmpobjid, 1, 14665, "genintint711_1", "interiorwindowglow", 0x00000000);
			tmpobjid = CreateDynamicObject(2723, 1268.150634, -22.165550, 1000.235107, -0.000006, 0.000004, -57.599990, world, INT_GARAGE); 
			SetDynamicObjectMaterial(tmpobjid, 0, 1560, "7_11_door", "CJ_CHROME2", 0xFFFFFFFF);
			SetDynamicObjectMaterial(tmpobjid, 1, 14665, "genintint711_1", "interiorwindowglow", 0x00000000);
			tmpobjid = CreateDynamicObject(2134, 1270.659301, -21.234113, 999.873596, -0.000014, 0.000000, -89.999954, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2133, 1269.664062, -24.218315, 999.873779, -0.000014, 0.000000, 180.000045, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2131, 1270.658691, -22.227582, 999.859375, -0.000014, 0.000000, -89.999954, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2341, 1270.644042, -24.226285, 999.873657, -0.000007, 0.000000, -89.999977, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2134, 1268.656372, -24.225086, 999.873596, -0.000014, 0.000000, 180.000045, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19621, 1270.940307, -21.050518, 1001.043823, 0.000000, 0.000000, -52.299991, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19627, 1265.601806, -16.771015, 1000.939453, 0.000000, 0.000000, 27.299999, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(18635, 1265.736694, -16.867628, 1000.985717, -87.600013, 58.600002, 63.500000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2824, 1269.493041, -24.345705, 1000.907104, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2133, 1270.654296, -20.228303, 999.873779, -0.000014, 0.000000, 270.000061, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19627, 1270.771972, -20.224559, 1000.929443, 0.000000, 0.000000, 27.299999, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1082, 1270.490234, -8.940871, 1002.320373, 0.000000, 0.000000, 270.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(1082, 1269.219604, -8.940871, 1002.320373, 0.000000, 0.000000, 270.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19626, 1269.614624, -9.072511, 1001.656433, 270.000000, 270.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(19626, 1269.614624, -9.072511, 1001.206054, 270.000000, 270.000000, 5.699999, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(18632, 1270.921752, -11.018756, 1001.229309, 0.000000, 270.000000, 90.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2816, 1265.439331, -17.052347, 1000.929321, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(18634, 1270.496704, -9.093156, 1000.306152, 0.000000, 90.000000, 90.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2261, 1262.944458, -24.287487, 1001.288269, 0.000000, 0.000000, 180.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2263, 1265.439208, -24.279512, 1001.987854, 0.000000, 0.000000, 180.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2260, 1264.617065, -24.285718, 1000.922912, 0.000000, 0.000000, 180.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2262, 1262.016845, -9.296922, 1001.470520, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			tmpobjid = CreateDynamicObject(2264, 1263.865844, -9.334376, 1000.627014, 0.000000, 0.000000, 0.000000, world, INT_GARAGE); 
			hgarage_static_furn[index][1] = CreateDynamicObject(2265, 1263.372680, -9.303144, 1002.029052, 0.000000, 0.000000, 0.000000, world, INT_GARAGE);			
		}
	}
}

Destroy:static_furn(index)
{
	for (new i = hgarage_static_furn[index][0], j = hgarage_static_furn[index][1]; i <= j; i++)
	{
		if (IsValidDynamicObject(i))
		{
			DestroyDynamicObject(i);
		}
	}
	
	hgarage_static_furn[index][0] =
	hgarage_static_furn[index][1] = 0;
}

ShowGarageSettings(playerid, index, dialogid = D_GARAGE + 2)
{
	format:g_string(" Кастомизация объектов\t%s" #cWHITE "",
		house_data[index][hg_set_furn] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет")
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", g_string, "Выбрать", "Назад");
}

GarageInteriorObjects()
{
	new tmpobjid;
	
	
	// Garage - 1 
	tmpobjid = CreateObject(6959, -1571.241210, -1773.226196, 2500.000000, 0.000000, 0.000000, 90.000000, 300.00); // fco
	SetObjectMaterial(tmpobjid, 0, 5397, "barrio1_lae", "snpdwargrn1", 0x00000000);
	
	tmpobjid = CreateDynamicObject(19445, -1577.949707, -1775.553466, 2501.708496, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1573.149902, -1770.733886, 2501.708496, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1569.680664, -1775.553466, 2501.708496, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1577.949707, -1785.183593, 2501.708496, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1569.680664, -1787.502685, 2501.708496, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1571.161132, -1780.271850, 2499.228027, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1575.910400, -1783.741333, 2499.208007, 0.000000, 0.000000, 180.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateObject(19445, -1573.449462, -1781.980224, 2500.897949, 180.000000, 90.000000, 270.000000, 300.00); // fco
	SetObjectMaterial(tmpobjid, 0, 3080, "adjumpx", "planks64", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1564.950683, -1780.302734, 2501.708496, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1564.950683, -1782.744628, 2501.708496, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1562.379882, -1780.322753, 2503.618652, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1564.910156, -1782.743286, 2504.863769, -36.099994, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1566.420654, -1782.763427, 2503.618652, 0.000000, 0.000000, 180.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1562.907958, -1781.980224, 2502.178222, 180.000000, 90.000000, 270.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1562.948974, -1781.980224, 2505.408691, 180.000000, 90.000000, 270.000000, -1, INT_GARAGE); // roof
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1565.865722, -1781.980224, 2506.309082, -144.199935, 90.000000, 270.000000, -1, INT_GARAGE); // roof
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1574.561279, -1783.811889, 2501.708496, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1564.910156, -1780.312744, 2504.863769, -36.099994, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(19445, -1562.329589, -1782.704711, 2503.618652, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "dockwall1", 0x00000000);
	tmpobjid = CreateDynamicObject(17951, -1573.733642, -1770.809448, 2501.648681, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // door
	tmpobjid = CreateDynamicObject(14407, -1577.978515, -1778.406616, 2497.788574, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // lestnica
	tmpobjid = CreateDynamicObject(14407, -1569.550048, -1782.317504, 2499.077880, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // lesctina
	tmpobjid = CreateDynamicObject(6959, -1590.391601, -1772.534423, 2503.390136, 0.000000, 180.000000, 0.000000, -1, INT_GARAGE); // roof
	tmpobjid = CreateDynamicObject(1498, -1566.470214, -1782.381713, 2502.229980, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // door2
	
	// Garage - 2 
	tmpobjid = CreateObject(6959, -527.506958, 1801.712646, 1236.886352, 0.000000, 0.000000, 0.000000, 300.00); // floor fco
	SetObjectMaterial(tmpobjid, 0, 18065, "ab_sfammumain", "pavea256", 0xFFFFFAFA);
	tmpobjid = CreateDynamicObject(6517, -510.886505, 1802.014648, 1238.603637, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // door
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "gz_vicdoor1", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(1498, -521.865051, 1804.343872, 1236.854736, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // door
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19454, -510.796813, 1802.191406, 1238.591186, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);
	tmpobjid = CreateDynamicObject(19454, -515.526794, 1797.371459, 1238.591186, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);
	tmpobjid = CreateDynamicObject(19454, -515.526794, 1806.911621, 1238.591186, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);
	tmpobjid = CreateDynamicObject(19454, -521.916625, 1802.151123, 1238.591186, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);
	tmpobjid = CreateDynamicObject(19435, -521.146789, 1797.371459, 1238.591186, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);
	tmpobjid = CreateDynamicObject(6959, -527.527587, 1801.728027, 1240.296386, 0.000000, 180.000000, 0.000000, -1, INT_GARAGE); // roof
	SetDynamicObjectMaterial(tmpobjid, 0, 5986, "chateau_lawn", "chatwall01_law", 0xFFFFFAFA);
	tmpobjid = CreateDynamicObject(19435, -521.146789, 1806.901611, 1238.591186, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); 
	SetDynamicObjectMaterial(tmpobjid, 0, 3820, "boxhses_sfsx", "ws_mixedbrick", 0x00000000);

	// Garage - 3
	tmpobjid = CreateObject(18783, 1269.170410, -16.826646, 997.419738, 0.000000, 0.000000, 0.000000, 300.0000); // floor fco
	SetObjectMaterial(tmpobjid, 0, 19480, "signsurf", "sign", 0x9FFFFFFF);
	SetObjectMaterial(tmpobjid, 1, 18065, "ab_sfammumain", "gun_floor2", 0x99FFFFFF);
	tmpobjid = CreateDynamicObject(19461, 1259.279541, -22.105808, 1001.649902, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 9507, "boxybld2_sfw", "gz_vic4c", 0x00000000);
	tmpobjid = CreateDynamicObject(19461, 1259.279541, -12.485816, 1001.649902, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 9507, "boxybld2_sfw", "gz_vic4c", 0x00000000);
	tmpobjid = CreateDynamicObject(19461, 1264.148803, -8.725819, 1001.649902, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 9507, "boxybld2_sfw", "gz_vic4c", 0x00000000);
	tmpobjid = CreateDynamicObject(19461, 1273.768920, -8.725817, 1001.649902, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 9507, "boxybld2_sfw", "gz_vic4c", 0x00000000);
	tmpobjid = CreateDynamicObject(19461, 1271.250854, -22.095808, 1001.649902, 0.000000, 0.000007, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 9507, "boxybld2_sfw", "gz_vic4c", 0x00000000);
	tmpobjid = CreateDynamicObject(19461, 1271.250854, -12.455816, 1001.649902, 0.000000, 0.000007, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 9507, "boxybld2_sfw", "gz_vic4c", 0x00000000);
	tmpobjid = CreateDynamicObject(19461, 1264.158813, -24.865789, 1001.649902, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 9507, "boxybld2_sfw", "gz_vic4c", 0x00000000);
	tmpobjid = CreateDynamicObject(19461, 1273.789916, -24.865789, 1001.649902, 0.000000, 0.000000, 90.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 9507, "boxybld2_sfw", "gz_vic4c", 0x00000000);
	tmpobjid = CreateDynamicObject(18783, 1269.349853, -27.626653, 1005.879638, 0.000000, 180.000000, 0.000000, -1, INT_GARAGE); // roof
	SetDynamicObjectMaterial(tmpobjid, 0, 14665, "genintint711_1", "interiorwindowglow", 0xFF464646);
	SetDynamicObjectMaterial(tmpobjid, 1, 10023, "bigwhitesfe", "sfe_arch10", 0x00000000);
	tmpobjid = CreateDynamicObject(6517, 1259.375000, -20.740627, 1001.579772, 0.000000, 0.000000, 179.600006, -1, INT_GARAGE); // door
	SetDynamicObjectMaterial(tmpobjid, 0, 9515, "bigboxtemp1", "garagedoor5_law", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(6517, 1259.431640, -12.950775, 1001.579772, 0.000000, 0.000000, 179.600006, -1, INT_GARAGE); // door
	SetDynamicObjectMaterial(tmpobjid, 0, 9515, "bigboxtemp1", "garagedoor5_law", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(11714, 1271.183349, -16.815206, 1001.139709, 0.000000, 0.000000, 720.000000, -1, INT_GARAGE); // door
	SetDynamicObjectMaterial(tmpobjid, 0, 6284, "bev_law2", "lasjmposh2", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(18783, 1269.349853, -6.066651, 1005.879638, 0.000000, 180.000000, 0.000000, -1, INT_GARAGE); // roof
	SetDynamicObjectMaterial(tmpobjid, 0, 14665, "genintint711_1", "interiorwindowglow", 0xFF464646);
	SetDynamicObjectMaterial(tmpobjid, 1, 10023, "bigwhitesfe", "sfe_arch10", 0x00000000);
	tmpobjid = CreateDynamicObject(18783, 1269.349853, -11.996650, 1006.159912, 0.000000, 180.000000, 0.000000, -1, INT_GARAGE); // roof
	SetDynamicObjectMaterial(tmpobjid, 0, 14665, "genintint711_1", "interiorwindowglow", 0xFF464646);
	SetDynamicObjectMaterial(tmpobjid, 1, 14665, "genintint711_1", "interiorwindowglow", 0xFF323232);
	tmpobjid = CreateDynamicObject(18783, 1249.800781, -17.996656, 1005.889648, 0.000000, 180.000000, 0.000000, -1, INT_GARAGE); // roof
	SetDynamicObjectMaterial(tmpobjid, 0, 14665, "genintint711_1", "interiorwindowglow", 0xFF464646);
	SetDynamicObjectMaterial(tmpobjid, 1, 10023, "bigwhitesfe", "sfe_arch10", 0x00000000);
	tmpobjid = CreateDynamicObject(18783, 1280.721069, -17.996656, 1005.889648, 0.000000, 180.000000, 0.000000, -1, INT_GARAGE); // roof
	SetDynamicObjectMaterial(tmpobjid, 0, 14665, "genintint711_1", "interiorwindowglow", 0xFF464646);
	SetDynamicObjectMaterial(tmpobjid, 1, 10023, "bigwhitesfe", "sfe_arch10", 0x00000000);
	tmpobjid = CreateDynamicObject(2075, 1263.242919, -12.714185, 1002.999572, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // light
	SetDynamicObjectMaterial(tmpobjid, 0, 14665, "genintint711_1", "interiorwindowglow", 0xFF323232);
	SetDynamicObjectMaterial(tmpobjid, 1, 10778, "airportcpark_sfse", "ws_fluorescent2", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 19480, "signsurf", "sign", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1269.336181, -16.799627, 1003.634216, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // light
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(2075, 1263.212890, -21.554195, 1002.999572, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // light
	SetDynamicObjectMaterial(tmpobjid, 0, 14665, "genintint711_1", "interiorwindowglow", 0xFF323232);
	SetDynamicObjectMaterial(tmpobjid, 1, 10778, "airportcpark_sfse", "ws_fluorescent2", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 19480, "signsurf", "sign", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1265.335205, -16.799627, 1003.634216, 0.000000, 0.000014, 0.000000, -1, INT_GARAGE); // light
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(2075, 1267.073242, -12.714185, 1002.999572, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // light
	SetDynamicObjectMaterial(tmpobjid, 0, 14665, "genintint711_1", "interiorwindowglow", 0xFF323232);
	SetDynamicObjectMaterial(tmpobjid, 1, 10778, "airportcpark_sfse", "ws_fluorescent2", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 19480, "signsurf", "sign", 0x00000000);
	tmpobjid = CreateDynamicObject(957, 1261.604858, -16.799627, 1003.634216, 0.000000, 0.000014, 0.000000, -1, INT_GARAGE); // light
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(2075, 1267.013916, -21.554195, 1002.999572, 0.000000, 0.000000, 0.000000, -1, INT_GARAGE); // light
	SetDynamicObjectMaterial(tmpobjid, 0, 14665, "genintint711_1", "interiorwindowglow", 0xFF323232);
	SetDynamicObjectMaterial(tmpobjid, 1, 10778, "airportcpark_sfse", "ws_fluorescent2", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 19480, "signsurf", "sign", 0x00000000);
	tmpobjid = CreateDynamicObject(2000, 1267.478637, -17.060253, 1000.879882, 0.000000, 0.000022, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 9507, "boxybld2_sfw", "gz_vic4c", 0x00000000);
	tmpobjid = CreateDynamicObject(2000, 1263.386596, -17.050252, 1002.269897, 0.000000, 0.000022, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 9507, "boxybld2_sfw", "gz_vic4c", 0x00000000);
	tmpobjid = CreateDynamicObject(2000, 1267.478637, -17.060253, 1002.269897, 0.000000, 0.000022, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 9507, "boxybld2_sfw", "gz_vic4c", 0x00000000);
	tmpobjid = CreateDynamicObject(2000, 1267.478637, -17.060253, 999.499755, 0.000000, 0.000022, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 9507, "boxybld2_sfw", "gz_vic4c", 0x00000000);
	tmpobjid = CreateDynamicObject(2000, 1263.386596, -17.050252, 1000.879882, 0.000000, 0.000022, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 9507, "boxybld2_sfw", "gz_vic4c", 0x00000000);
	tmpobjid = CreateDynamicObject(2000, 1263.386596, -17.050252, 999.499755, 0.000000, 0.000022, 0.000000, -1, INT_GARAGE); // wall
	SetDynamicObjectMaterial(tmpobjid, 0, 9507, "boxybld2_sfw", "gz_vic4c", 0x00000000);
}