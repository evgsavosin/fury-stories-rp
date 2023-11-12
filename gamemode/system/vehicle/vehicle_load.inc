/*!
	@brief Загрузка транспорта
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

Load:vehicle(id, type, bool: is_primary, limit = MAX_PLAYER_VEHICLES)
{
	new playerid = INVALID_PLAYER_ID;
	
	if (type == TYPE_VEH_PLAYER)
	{
		playerid = id;
		id = GetCharacterId(playerid);
	}
	
	format:g_string("SELECT * FROM " #__VEHICLES " WHERE v_owner_id = %i AND v_owner_type = %i LIMIT %i",
		id,
		type,
		limit
	);
	
	mysql_tquery(db, g_string, "OnVehicleLoad", "ii", playerid, is_primary);
}

Load:vehicle_by_id(id)
{
	format:g_string("SELECT * FROM " #__VEHICLES " WHERE v_id = %d LIMIT 1",
		id
	);
	
	mysql_tquery(db, g_string, "OnVehicleLoad", "ii", INVALID_PLAYER_ID, false);
}

function OnVehicleLoad(playerid, is_primary)
{
	new rows,
		temp								[	E_VEHICLE_DATA 	],
		vehicleid,
		load;
		
	cache_get_row_count(rows);
	
	for (new i; i < rows; i++)
	{	
		/// int
		cache_get_value_name_int(i, "v_id", temp[v_id]);
		cache_get_value_name_int(i, "v_model", temp[v_model]);
		cache_get_value_name_int(i, "v_spawned", temp[v_spawned]);
		
		/// Если это транспорт игрока
		if (playerid != INVALID_PLAYER_ID)
		{
			if (is_primary)
			{
				player_vehicle[playerid][pv_id][i] = temp[v_id];
				player_vehicle[playerid][pv_model][i] = temp[v_model];
				
				if (!temp[v_spawned])
				{
					continue;
				}
			}
			
			load = true;
			
			for (new j = 1, v = GetVehiclePoolSize(); j <= v; j++) 
			{
				if (vehicle_data[j][v_id] != temp[v_id])
				{
					continue;
				}
				
				if (is_primary && vehicle_data[j][v_del_type] == DELVEH_BY_PLAYER)
				{
					player_vehicle[playerid][pv_delete][i] = true;
				}
				
				KillTimer(vehicle_data[j][v_del_timer]);
				vehicle_data[j][v_del_timer] = INVALID_PARAM;
				
				GiveVehicleOwner(playerid, vehicle_data[j][v_id], j);
				
				load = false;
				break;
			}
			
			if (!load)
			{
				continue;
			}
		}
		
		/// Int
		cache_get_value_name_int(i, "v_siren", temp[v_siren]);
		
		/// Float
		cache_get_value_name_float(i, "v_pos_x", temp[v_pos_x]);
		cache_get_value_name_float(i, "v_pos_y", temp[v_pos_y]);
		cache_get_value_name_float(i, "v_pos_z", temp[v_pos_z]);
		cache_get_value_name_float(i, "v_pos_angle", temp[v_pos_angle]);
		
		clean:<g_string>;
		cache_get_value_name(i, "v_color", g_string);
		sscanf(g_string, "p<|>a<d>[2]", temp[v_color]);
		
		vehicleid = CreateVehicle(
			temp[v_model], 
			temp[v_pos_x],
			temp[v_pos_y],
			temp[v_pos_z],
			temp[v_pos_angle], 
			temp[v_color][0], 
			temp[v_color][1], 
			-1,
			temp[v_siren]
		);
		
		/// int
		cache_get_value_name_int(i, "v_owner_type", vehicle_data[vehicleid][v_owner_type]);
		cache_get_value_name_int(i, "v_owner_id", vehicle_data[vehicleid][v_owner_id]);
		cache_get_value_name_int(i, "v_buy_type", vehicle_data[vehicleid][v_buy_type]);
		cache_get_value_name_int(i, "v_world", vehicle_data[vehicleid][v_world]);
		cache_get_value_name_int(i, "v_int", vehicle_data[vehicleid][v_int]);
		cache_get_value_name_int(i, "v_lock", vehicle_data[vehicleid][v_lock]);
		cache_get_value_name_int(i, "v_is_credit", vehicle_data[vehicleid][v_is_credit]);
		cache_get_value_name_int(i, "v_radio", vehicle_data[vehicleid][v_radio]);
		
		/// float
		cache_get_value_name_float(i, "v_health", vehicle_data[vehicleid][v_health]);
		cache_get_value_name_float(i, "v_mileage", vehicle_data[vehicleid][v_mileage]);
		cache_get_value_name_float(i, "v_fuel", vehicle_data[vehicleid][v_fuel]);
		cache_get_value_name_float(i, "v_state", vehicle_data[vehicleid][v_state]);
		
		/// other
		vehicle_data[vehicleid][v_id] = temp[v_id];
		vehicle_data[vehicleid][v_model] = temp[v_model];
		vehicle_data[vehicleid][v_color][0] = temp[v_color][0];
		vehicle_data[vehicleid][v_color][1] = temp[v_color][1];
		vehicle_data[vehicleid][v_pos_x] = temp[v_pos_x];
		vehicle_data[vehicleid][v_pos_y] = temp[v_pos_y];
		vehicle_data[vehicleid][v_pos_z] = temp[v_pos_z];
		vehicle_data[vehicleid][v_pos_angle] = temp[v_pos_angle];
		vehicle_data[vehicleid][v_spawned] = temp[v_spawned];
		vehicle_data[vehicleid][v_siren] = temp[v_siren];

		cache_get_value_name(i, "v_desc", vehicle_data[vehicleid][v_desc]);
		
		LinkVehicleToInterior(vehicleid, vehicle_data[vehicleid][v_int]);
		SetVehicleVirtualWorld(vehicleid, vehicle_data[vehicleid][v_world]);
		SetVehicleHealth(vehicleid, vehicle_data[vehicleid][v_health]);
		
		SetVehicleParams(vehicleid);
		
		cache_get_value_name(i, "v_number", vehicle_data[vehicleid][v_number], 32);
		if (!isnull(vehicle_data[vehicleid][v_number])) 
		{
			SetVehicleNumberPlate(vehicleid, vehicle_data[vehicleid][v_number]);
		}
			
		if (playerid != INVALID_PLAYER_ID)
		{	
			GiveVehicleOwner(playerid, vehicle_data[vehicleid][v_id], vehicleid);
			
			Load:inventory(vehicleid, TYPE_INV_VEHICLE);
			Load:inventory(vehicleid, TYPE_INV_VEH_GLOVE);
			
			if (!is_primary)
			{	
				vehicle_data[vehicleid][v_spawned] = true;
				
				pformat:("" #SUCCESS " Ваш транспорт " #cPROJECT "%s" #cWHITE " успешно вызван.",
					GetVehicleInfo(temp[v_model], v_name)
				);
				
				psend:(playerid, C_WHITE);
				
				Update:vehicle_data(vehicleid, playerid);
			}
		}
	
		printf("[VEHICLE]: Vehicle %d[%d] has been loaded on the server. (VEHICLEID: %d)",	
			vehicle_data[vehicleid][v_model],
			vehicle_data[vehicleid][v_id],
			vehicleid
		);
	}
	
	return 1;
}


