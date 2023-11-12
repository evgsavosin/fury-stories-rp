/*!
	@brief Система подразделений для системы фракций
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

GetFreeIndexForFractionUnit(index)
{
	for (new i; i < MAX_FRACTION_UNITS; i++)
	{
		if (fraction_unit_data[index][i][fr_id] == 0)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

GetFreeIndexForUnitSkin(findex, index)
{
	for (new i; i < MAX_FRACTION_SKINS; i++)
	{
		if (fraction_unit_data[findex][index][fr_skins][i] == 0)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

GetFractionUnitById(index, id)
{
	if (id == 0)
	{
		return INVALID_PARAM;
	}
	
	for (new i; i < MAX_FRACTION_UNITS; i++)
	{
		if (fraction_unit_data[index][i][fr_id] == id)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

Load:fraction_unit_data(index)
{
	format:g_string("\
		SELECT fru.*, \
			   IFNULL(c.c_name, '') AS fr_leader_name \
		FROM " #__FRACTIONS_UNIT " fru \
		LEFT JOIN " #__CHARACTERS " c \
			ON c.c_id = fru.fr_leader_id \
		WHERE fr_fraction_id = %d \
		LIMIT %d", 
		fraction_data[index][fr_id], 
		MAX_FRACTION_UNITS
	);
	
	mysql_tquery(db, g_string, "OnFractionUnitLoad", "d", index);
}

function OnFractionUnitLoad(id)
{
	new rows;
		
	cache_get_row_count(rows);
	
	for (new i; i < rows; i++)
	{
		if (rows >= MAX_FRACTION_UNITS)
		{
			printf("[OnFractionUnitLoad]: Limit exceeded. All - %d. Limit - %d", rows, MAX_FRACTION_RANKS);
			break;
		}
		
		// Int
		cache_get_value_name_int(i, "fr_id", fraction_unit_data[id][i][fr_id]);
		cache_get_value_name_int(i, "fr_int", fraction_unit_data[id][i][fr_int]);
		cache_get_value_name_int(i, "fr_world", fraction_unit_data[id][i][fr_world]);
		cache_get_value_name_int(i, "fr_leader_id", fraction_unit_data[id][i][fr_leader_id]);
		
		// Float
		cache_get_value_name_float(i, "fr_pos_x", fraction_unit_data[id][i][fr_pos_x]);
		cache_get_value_name_float(i, "fr_pos_y", fraction_unit_data[id][i][fr_pos_y]);
		cache_get_value_name_float(i, "fr_pos_z", fraction_unit_data[id][i][fr_pos_z]);
		
		// String
		cache_get_value_name(i, "fr_name", fraction_unit_data[id][i][fr_name], MAX_FRACTION_NAME);
		cache_get_value_name(i, "fr_alt_name", fraction_unit_data[id][i][fr_alt_name], MAX_FRACTION_ALT_NAME);
		cache_get_value_name(i, "fr_leader_name", fraction_unit_data[id][i][fr_leader_name], MAX_PLAYER_NAME);
		
		clean:<g_string>;
		cache_get_value_name(i, "fr_skins", g_string, sizeof g_string);
		format:g_small_string("p<|>a<d>[%d]", MAX_FRACTION_SKINS);
		sscanf(g_string, g_small_string, fraction_unit_data[id][i][fr_skins]);
	}

	return 1;
}