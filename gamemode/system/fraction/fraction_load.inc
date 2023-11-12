/*!
	@brief Загрузка данных для системы фракций
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

Load:fraction_data()
{
	mysql_tquery(db, "\
		SELECT \
			fr.*, \ 
			fr.fr_type_budget + 0 AS fr_type_budget_int, \
			IFNULL(c.c_name, '') AS fr_leader_name \
		FROM " #__FRACTIONS " fr \
		LEFT JOIN " #__CHARACTERS " c \
			ON c.c_id = fr.fr_leader_id", 
		"OnFractionLoad"
	);
}

function OnFractionLoad()
{
	new rows,
		server_tick = GetTickCount();
		
	cache_get_row_count(rows);
	
	for (new i; i < rows; i++)
	{
		// Int
		cache_get_value_name_int(i, "fr_id", fraction_data[i][fr_id]);
		cache_get_value_name_int(i, "fr_type_budget_int", fraction_data[i][fr_type_budget]);
		cache_get_value_name_int(i, "fr_main", fraction_data[i][fr_main]);
		cache_get_value_name_int(i, "fr_leader_id", fraction_data[i][fr_leader_id]);
		cache_get_value_name_int(i, "fr_join_rank_id", fraction_data[i][fr_join_rank_id]);
		cache_get_value_name_int(i, "fr_spawn_int", fraction_data[i][fr_spawn_int]);
		cache_get_value_name_int(i, "fr_spawn_world", fraction_data[i][fr_spawn_world]);
		
		// Float
		cache_get_value_name_float(i, "fr_budget", fraction_data[i][fr_budget]);
		cache_get_value_name_float(i, "fr_spawn_pos_x", fraction_data[i][fr_spawn_pos][0]);
		cache_get_value_name_float(i, "fr_spawn_pos_y", fraction_data[i][fr_spawn_pos][1]);
		cache_get_value_name_float(i, "fr_spawn_pos_z", fraction_data[i][fr_spawn_pos][2]);
		cache_get_value_name_float(i, "fr_spawn_pos_angle", fraction_data[i][fr_spawn_pos][3]);
		
		// String
		cache_get_value_name(i, "fr_name", fraction_data[i][fr_name], MAX_FRACTION_NAME);
		cache_get_value_name(i, "fr_alt_name", fraction_data[i][fr_alt_name], MAX_FRACTION_ALT_NAME);
		cache_get_value_name(i, "fr_leader_name", fraction_data[i][fr_leader_name], MAX_FRACTION_NAME);
		
		clean:<g_small_string>;
		cache_get_value_name(i, "fr_color", g_small_string, sizeof g_small_string);
		sscanf(g_small_string, "x", fraction_data[i][fr_color]);
		
		// Load vehicles
		Load:vehicle(fraction_data[i][fr_id], TYPE_VEH_FRACTION, false, MAX_FRACTION_VEHICLES);
		
		// Load ranks
		Load:fraction_rank_data(i);
		
		// Load units
		Load:fraction_unit_data(i);
		
		// Load doors
		Create:fraction_door_all(i);
	}
	
	printf("[OnFractionLoad]: Fractions have been loaded. All - %i. Time - %0.4fs.", 
		rows, 
		((GetTickCount() - server_tick) / 1000)
	);
	
	return 1;
}

Load:character_fraction(playerid)
{
	new fraction_id,
		unit_id,
		rank_id,
		skin,
		duty;
	
	// Результат при загрузке аккаунта
	cache_get_value_name_int(0, "c_fraction_id", fraction_id);
	cache_get_value_name_int(0, "c_fraction_rank_id", rank_id);
	cache_get_value_name_int(0, "c_fraction_unit_id", unit_id);
	cache_get_value_name_int(0, "c_fraction_skin", skin);
	cache_get_value_name_int(0, "c_fraction_duty", duty);
	
	if (fraction_id == 0)
	{
		return;
	}
	
	// Получаем индекс фракции
	for (new i; i < sizeof fraction_data; i++)
	{
		if (fraction_data[i][fr_id] == fraction_id)
		{
			character_data[playerid][c_fraction_index] = i;
			character_data[playerid][c_fraction_skin] = skin;
			character_data[playerid][c_fraction_duty] = duty;
			
			if (fraction_data[i][fr_leader_id] == GetCharacterId(playerid))
			{
				character_data[playerid][c_fraction_leader] = i;
			}
			
			if (rank_id != 0)
			{
				// Получаем индекс ранга
				for (new j = 0; j < MAX_FRACTION_RANKS; j++)
				{
					if (fraction_rank_data[i][j][fr_id] == rank_id)
					{
						character_data[playerid][c_fraction_rank_index] = j;
						break;
					}
				}
			}
			
			if (unit_id != 0)
			{
				// Получаем индекс подразделения
				for (new j = 0; j < MAX_FRACTION_UNITS; j++)
				{
					if (fraction_unit_data[i][j][fr_id] == unit_id)
					{
						character_data[playerid][c_fraction_unit_index] = j;
						
						if (fraction_unit_data[i][j][fr_leader_id] == GetCharacterId(playerid))
						{
							character_data[playerid][c_fraction_unit_leader_index] = j;
						}
						
						break;
					}
				}
			}
			
			printf("[Load:character_fraction]: Fraction [ID:%d] has been loaded for player %s. (%d, %d, %d, %d)",
				GetFractionId(i),
				GetCharacterName(playerid),
				character_data[playerid][c_fraction_index],
				character_data[playerid][c_fraction_rank_index],
				character_data[playerid][c_fraction_unit_index],
				character_data[playerid][c_fraction_unit_leader_index]
			);
			
			break;
		}
	}
}