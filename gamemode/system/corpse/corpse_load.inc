/*!
	@brief Загрузка системы трупов
	@author Found (evg.savosin)
	@date 26.04.2017
*/

function OnCorpseLoad()
{
	new rows;
		
	cache_get_row_count(rows);
	
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "corp_id", corpse_data[i][corp_id]);
		cache_get_value_name_int(i, "corp_state", corpse_data[i][corp_state]);
		cache_get_value_name_int(i, "corp_reason", corpse_data[i][corp_reason]);
		cache_get_value_name_int(i, "corp_weapon_id", corpse_data[i][corp_weapon_id]);
		cache_get_value_name_int(i, "corp_skin", corpse_data[i][corp_skin]);
		cache_get_value_name_int(i, "corp_world", corpse_data[i][corp_world]);
		cache_get_value_name_int(i, "corp_int", corpse_data[i][corp_int]);
		cache_get_value_name_int(i, "corp_created_time", corpse_data[i][corp_created_time]);
		
		cache_get_value_name_float(i, "corp_pos_x", corpse_data[i][corp_pos][0]);
		cache_get_value_name_float(i, "corp_pos_y", corpse_data[i][corp_pos][1]);
		cache_get_value_name_float(i, "corp_pos_z", corpse_data[i][corp_pos][2]);
		cache_get_value_name_float(i, "corp_pos_angle", corpse_data[i][corp_pos][3]);
		
		cache_get_value_name(i, "corp_character_name", corpse_data[i][corp_character_name], MAX_PLAYER_NAME);
		cache_get_value_name(i, "corp_attack_name_fist", corpse_data[i][corp_attack_name_fist], MAX_PLAYER_NAME);
		cache_get_value_name(i, "corp_attack_name_cold", corpse_data[i][corp_attack_name_cold], MAX_PLAYER_NAME);
		cache_get_value_name(i, "corp_camera_name", corpse_data[i][corp_camera_name], MAX_PLAYER_NAME);
	
		corpse_data[i][corp_type] = TYPE_CORP_DB;
		
		Create:corpse(i);
	}
	
	printf("[OnCorpseLoad]: Corpses have been loaded. All - %i.", rows);
	return 1;
}