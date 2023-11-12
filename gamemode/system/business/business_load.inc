/*!
	@brief Загрузка системы бизнесов
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

function OnBusinessLoad()
{
	new rows,
		time,
		weekly_time;
	
	cache_get_row_count(rows);
		
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "b_id", business_data[i][b_id]);
		cache_get_value_name_int(i, "b_character_id", business_data[i][b_character_id]);
		cache_get_value_name_int(i, "b_type", business_data[i][b_type]);
		cache_get_value_name_int(i, "b_subtype", business_data[i][b_subtype]);
		cache_get_value_name_int(i, "b_created_time", business_data[i][b_created_time]);
		cache_get_value_name_int(i, "b_profit", business_data[i][b_profit]);
		cache_get_value_name_int(i, "b_profit_weekly", business_data[i][b_profit_weekly]);
		
		cache_get_value_name(i, "b_name", business_data[i][b_name], MAX_BUSINESS_NAME);
	
		cache_get_value_name_int(i, "b_profit_weekly_time", weekly_time);
		if ((weekly_time + (60 * 60 * 24 * 7)) < (time = gettime()))
		{
			business_data[i][b_profit_weekly] = 0;
			Update:business_int(i, "b_profit_weekly", 0, true);
			Update:business_int(i, "b_profit_weekly_time", time, true);
		}
		
		format:g_string("SELECT * FROM " #__BASSORT " WHERE ba_business_id = %i LIMIT %i", 
			business_data[i][b_id],
			MAX_BUSINESS_NAME 
		);
		
		mysql_tquery(db, g_string, "OnBusinessAssortLoad", "i", i);
	}
	
	printf("[OnBusinessLoad]: Business Company has been loaded on the server. (ALL: %d)", rows);
	
	return 1;
}

function OnBusinessAssortLoad(index)
{
	new rows;
	
	cache_get_row_count(rows);
		
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "ba_item_id", bassort_data[index][i][ba_item_id]);
		cache_get_value_name_int(i, "ba_item_param", bassort_data[index][i][ba_item_param]);
		cache_get_value_name_int(i, "ba_cost", bassort_data[index][i][ba_cost]);
	}
	
	printf("[OnBusinessAssortLoad]: Assortment has been loaded for business company (ID:%i). (ALL: %d)", 
		business_data[index][b_id],
		rows 
	);
	
	return 1;
}

Load:character_business(playerid)
{
	for (new i; i < sizeof business_data; i++)
	{
		if (business_data[i][b_character_id] != GetCharacterId(playerid))
		{
			continue;
		}
		
		GiveBusinessOwner(playerid, i);

		printf("[Load:character_business]: Business [ID:%d] has been loaded for player %s.",
			GetBusinessId(i),
			GetCharacterName(playerid)
		);
	}
}