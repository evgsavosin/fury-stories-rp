/*!
	@brief Система подъездов
	@author Found (evg.savosin)
	@date 16.12.2016, update 21.03.2018
*/

function Hostel_OnGameModeInit()
{
	mysql_tquery(db, "SELECT * FROM " #__HOSTELS "", "OnHostelLoad");
	
	for (new i; i < sizeof hostel_settings; i++)
	{
		CreateDynamic3DTextLabel(
			"Выход", 
			-1, 
			hostel_settings[i][hos_set_pos][0],
			hostel_settings[i][hos_set_pos][1],
			hostel_settings[i][hos_set_pos][2],
			TEXT3D_DRAW_DISTANCE, 
			_, 
			_, 
			1, 
			_, 
			INT_HOSTEL, 
			_, 
			TEXT3D_DRAW_DISTANCE
		);
	}
	
	return 1;
}

function Hostel_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{
		for (new index, htype; index < sizeof hostel_data; index++)
		{
			if (!hostel_data[index][hos_id])
			{
				continue;
			}
			
			htype = hostel_data[index][hos_int_type];
				
			if (IsPlayerInRangeOfPoint(playerid, 
				FACTOR_TELEPORT_RADIUS, 
				hostel_data[index][hos_pos][0], 
				hostel_data[index][hos_pos][1], 
				hostel_data[index][hos_pos][2])
			)
			{
				
				Move:player(playerid, 
					hostel_settings[htype][hos_set_pos][0], 
					hostel_settings[htype][hos_set_pos][1], 
					hostel_settings[htype][hos_set_pos][2], 
					WORLD_HOSTEL + hostel_data[index][hos_id], 
					INT_HOSTEL, 
					true, 
					hostel_settings[htype][hos_set_pos][3] 
				);
				
				return 0;
			}
			else if (GetPlayerVirtualWorld(playerid) == (WORLD_HOSTEL + hostel_data[index][hos_id])
			&& IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, 
				hostel_settings[htype][hos_set_pos][0], 
				hostel_settings[htype][hos_set_pos][1], 
				hostel_settings[htype][hos_set_pos][2]) 
			)
			{

				Move:player(playerid, 
					hostel_data[index][hos_pos][0], 
					hostel_data[index][hos_pos][1], 
					hostel_data[index][hos_pos][2], 
					_, 
					_, 
					true, 
					hostel_data[index][hos_pos][3] 
				);
				
				return 0;
			}
		}
	}
	
	return 1;
}

function OnHostelLoad()
{
	new rows;
	
	cache_get_row_count(rows);
	
	for (new index; index < rows; index++)
	{
		cache_get_value_name_int(index, "hos_id", hostel_data[index][hos_id]);
		cache_get_value_name_int(index, "hos_int_type", hostel_data[index][hos_int_type]);
		cache_get_value_name_float(index, "hos_pos_x", hostel_data[index][hos_pos][0]);
		cache_get_value_name_float(index, "hos_pos_y", hostel_data[index][hos_pos][1]);
		cache_get_value_name_float(index, "hos_pos_z", hostel_data[index][hos_pos][2]);
		cache_get_value_name_float(index, "hos_pos_angle", hostel_data[index][hos_pos][3]);
		Create:hostel(index);
	}
	
	printf("[HOSTEL]: Hostels has been loaded on the server. (HOSTELS: %d)", rows);
	return 1;
}

Create:hostel(index)
{
	format:g_small_string("Подъезд #%d", 
		hostel_data[index][hos_id]
	);
	
	hostel_data[index][hos_text] = CreateDynamic3DTextLabel(
		g_small_string, 
		-1, 
		hostel_data[index][hos_pos][0], 
		hostel_data[index][hos_pos][1], 
		hostel_data[index][hos_pos][2], 
		TEXT3D_DRAW_DISTANCE, 
		_, 
		_, 
		1, 
		_, 
		_, 
		_, 
		TEXT3D_DRAW_DISTANCE
	);
	
	hostel_data[index][hos_pickup] = CreateDynamicPickup(
		PICKUP_MODEL, 
		1, 
		hostel_data[index][hos_pos][0], 
		hostel_data[index][hos_pos][1], 
		hostel_data[index][hos_pos][2], 
		0, 
		0, 
		-1, 
		PICKUP_DRAW_DISTANCE
	);
}

Destroy:hostel(index)
{
	if (IsValidDynamic3DTextLabel(hostel_data[index][hos_text]))
	{
		DestroyDynamic3DTextLabel(hostel_data[index][hos_text]);
	}
	
	if (IsValidDynamicPickup(hostel_data[index][hos_pickup]))
	{
		DestroyDynamicPickup(hostel_data[index][hos_pickup]);
	}
}

CreateHousesInHostel(index, price)
{
	new type = hostel_data[index][hos_int_type],
		type_hostel = hostel_settings[type][hos_set_type];
		
	for (new i; i < sizeof hostel_house_pos; i++)
	{
		if (hostel_house_pos[i][hos_hp_id] != type)
		{
			continue;
		}
		
		for (new j; j < sizeof house_data; j++)
		{
			if (house_data[j][h_id] != 0)
			{
				continue;
			}
			
			house_data[j][h_lock] = 0;
			
			house_data[j][h_pos][0] = hostel_house_pos[i][hos_hp_pos][0];
			house_data[j][h_pos][1] = hostel_house_pos[i][hos_hp_pos][1];
			house_data[j][h_pos][2] = hostel_house_pos[i][hos_hp_pos][2];
			house_data[j][h_pos][3] = hostel_house_pos[i][hos_hp_pos][3];

			house_data[j][h_world] = WORLD_HOSTEL + hostel_data[index][hos_id];
			house_data[j][h_interior] = INT_HOSTEL;
			
			if (type_hostel == TYPE_HOSTEL_LOW)
			{
				house_data[j][h_int_type] = 1;
			}
			else if (type_hostel == TYPE_HOSTEL_MEDIUM)
			{
				house_data[j][h_int_type] = random(2) == 1 ? 2 : 3; 
			}
			else if (type_hostel == TYPE_HOSTEL_HIGH)
			{
				house_data[j][h_int_type] = 1; 
			}
			
			house_data[j][h_price] = floatround((price * (random(10) + 1) / 100) + price); // Генерируем цену
			house_data[j][h_id] = INVALID_PARAM;
			
			Create:house_data(j);

			break;
		}
	}
}

GetHostelIndexByHouse(index)
{
	for (new i; i < sizeof hostel_data; i++)
	{
		if ((house_data[index][h_world] - WORLD_HOSTEL) == hostel_data[i][hos_id] 
		&& house_data[index][h_interior] == INT_HOSTEL)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

GetHostelIndexById(id)
{
	for (new i; i < sizeof hostel_data; i++)
	{
		if (hostel_data[i][hos_id] == id)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}