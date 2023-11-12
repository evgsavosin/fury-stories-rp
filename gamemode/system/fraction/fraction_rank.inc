/*!
	@brief Система рангов для системы фракций
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

GetFractionRankId(playerid, rindex)
{
	new findex = GetFractionMember(playerid);
	
	if (findex != INVALID_PARAM)
	{
		return fraction_rank_data[findex][rindex][fr_id];
	}
	
	return INVALID_PARAM;
}			

GetFractionRankName(playerid, name[MAX_FRACTION_RANK_NAME])
{
	clean:<name>;
	
	new findex = GetFractionMember(playerid),
		rindex = GetFractionMemberRank(playerid);
	
	if (findex != INVALID_PARAM && rindex != INVALID_PARAM)
	{
		strcat(name, fraction_rank_data[findex][rindex][fr_name]);
	}
	else 
	{
		strcat(name, "");
	}
}	

GetFreeIndexForFractionRank(index)
{
	for (new i; i < MAX_FRACTION_RANKS; i++)
	{
		if (fraction_rank_data[index][i][fr_id] == 0)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

GetFractionRankById(index, id)
{
	if (id == 0)
	{
		return INVALID_PARAM;
	}
	
	for (new i; i < MAX_FRACTION_RANKS; i++)
	{
		if (fraction_rank_data[index][i][fr_id] == id)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

Load:fraction_rank_data(index)
{
	format:g_string("SELECT * FROM " #__FRACTIONS_RANK " WHERE fr_fraction_id = %d LIMIT %d", 
		fraction_data[index][fr_id], 
		MAX_FRACTION_RANKS
	);
	
	mysql_tquery(db, g_string, "OnFractionRankLoad", "d", index);
}

function OnFractionRankLoad(id)
{
	new rows;
		
	cache_get_row_count(rows);

	for (new i; i < rows; i++)
	{
		if (rows >= MAX_FRACTION_RANKS)
		{
			printf("[OnFractionRankLoad]: Limit exceeded. All - %d. Limit - %d", rows, MAX_FRACTION_RANKS);
			break;
		}
		
		// Int
		cache_get_value_name_int(i, "fr_id", fraction_rank_data[id][i][fr_id]);	
		cache_get_value_name_int(i, "fr_salary", fraction_rank_data[id][i][fr_salary]);
		cache_get_value_name_int(i, "fr_perm_invite", fraction_rank_data[id][i][fr_perm_invite]);
		cache_get_value_name_int(i, "fr_perm_uninvite", fraction_rank_data[id][i][fr_perm_uninvite]);
		cache_get_value_name_int(i, "fr_perm_set_rank", fraction_rank_data[id][i][fr_perm_set_rank]);
		cache_get_value_name_int(i, "fr_perm_set_unit", fraction_rank_data[id][i][fr_perm_set_unit]);
		cache_get_value_name_int(i, "fr_perm_manage", fraction_rank_data[id][i][fr_perm_manage]);
		cache_get_value_name_int(i, "fr_perm_radio", fraction_rank_data[id][i][fr_perm_radio]);
		cache_get_value_name_int(i, "fr_perm_object", fraction_rank_data[id][i][fr_perm_object]);
		cache_get_value_name_int(i, "fr_perm_attach", fraction_rank_data[id][i][fr_perm_attach]);
		cache_get_value_name_int(i, "fr_perm_vehicle", fraction_rank_data[id][i][fr_perm_vehicle]);
		cache_get_value_name_int(i, "fr_perm_clothes", fraction_rank_data[id][i][fr_perm_clothes]);
		cache_get_value_name_int(i, "fr_perm_items", fraction_rank_data[id][i][fr_perm_items]);
		cache_get_value_name_int(i, "fr_perm_weapon", fraction_rank_data[id][i][fr_perm_weapon]);
		cache_get_value_name_int(i, "fr_perm_spawn_vehicle", fraction_rank_data[id][i][fr_perm_spawn_vehicle]);
		
		// String
		cache_get_value_name(i, "fr_name", fraction_rank_data[id][i][fr_name], MAX_FRACTION_RANK_NAME);
		
		clean:<g_string>;
		cache_get_value_name(i, "fr_perm_custom", g_string, sizeof g_string);
		format:g_small_string("p<|>a<d>[%d]", MAX_FRACTION_RANK_PERM);
		sscanf(g_string, g_small_string, fraction_rank_data[id][i][fr_perm_custom]);
	}
	
	return 1;
}