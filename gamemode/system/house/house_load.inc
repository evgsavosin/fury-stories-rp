/*!
	@brief Загрузка для системы домов
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

function OnHouseLoad()
{
	new rows;
	
	cache_get_row_count(rows);
		
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "h_id", house_data[i][h_id]);
		cache_get_value_name_int(i, "h_character_id", house_data[i][h_character_id]);
		cache_get_value_name_int(i, "h_buy_type", house_data[i][h_buy_type]);
		
		cache_get_value_name_float(i, "h_pos_x", house_data[i][h_pos][0]);
		cache_get_value_name_float(i, "h_pos_y", house_data[i][h_pos][1]);
		cache_get_value_name_float(i, "h_pos_z", house_data[i][h_pos][2]);
		cache_get_value_name_float(i, "h_pos_angle", house_data[i][h_pos][3]);
		
		cache_get_value_name_int(i, "h_price", house_data[i][h_price]);
		cache_get_value_name_int(i, "h_int_type", house_data[i][h_int_type]);
		cache_get_value_name_int(i, "h_world", house_data[i][h_world]);
		cache_get_value_name_int(i, "h_interior", house_data[i][h_interior]);
		cache_get_value_name_int(i, "h_lock", house_data[i][h_lock]);
		cache_get_value_name_int(i, "h_money", house_data[i][h_money]);
		cache_get_value_name_int(i, "h_debt", house_data[i][h_debt]);
		cache_get_value_name_int(i, "h_time", house_data[i][h_time]);
		
		Create:house(i);
		
		Load:room(GetHouseId(i), i, TYPE_REN_HOUSE);
		Load:furn(GetHouseId(i), i, TYPE_REN_HOUSE);
		
		format:g_string("SELECT * FROM " #__HGARAGE " WHERE g_house_id = %i LIMIT 1", 
			house_data[i][h_id]
		);
		
		mysql_tquery(db, g_string, "OnHouseGarageLoad", "d", i);
	}
	
	printf("[OnHouseLoad]: Houses has been loaded on the server. (ALL: %d)", rows);
	
	return 1;
}

Load:character_houses(playerid)
{
	new debt;
	
	for (new i; i < sizeof house_data; i++)
	{
		if (house_data[i][h_character_id] != GetCharacterId(playerid))
		{
			continue;
		}
		
		GiveHouseOwner(playerid, i);
		
		if (GetHouseDebt(i) > 0)
		{
			debt++;
		}
		
		printf("[HOUSES]: House [ID:%d] has been loaded for player %s.",
			house_data[i][h_id],
			GetCharacterName(playerid)
		);
	}
	
	if (debt != 0)
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Внимание!" #cWHITE " У Вас имеются непогашенные задолжности за жилищные помещения.");
	}
}
