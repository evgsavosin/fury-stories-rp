/*!
	@brief Загрузка системы телефонов
	@author Found (evg.savosin)
	@date 16.12.2016, update 26.01.2018
*/

function OnPhoneLoad(id, type)
{
	new rows,
		is_null_contacts,
		phone_index = GetFreeIndexForPhone();
		
	if (phone_index == INVALID_PARAM)
	{
		return 1;
	}
	
	cache_get_row_count(rows);
	
	if (rows == 0)
	{
		return 1;
	}

	Clear:phone_data(phone_index);
	
	/// Integer
	cache_get_value_name_int(0, "ph_id", phone_data[phone_index][ph_id]);
	cache_get_value_name_int(0, "ph_col_panel", phone_data[phone_index][ph_col_panel]);
	cache_get_value_name_int(0, "ph_music", phone_data[phone_index][ph_music]);
	cache_get_value_name_int(0, "ph_number", phone_data[phone_index][ph_number]);
	cache_get_value_name_int(0, "ph_status", phone_data[phone_index][ph_status]);
	cache_get_value_name_int(0, "ph_radio", phone_data[phone_index][ph_radio]);
	cache_get_value_name_int(0, "ph_paid_time", phone_data[phone_index][ph_paid_time]);
	
	if (type == TYPE_INV_PLAYER)
	{
		phone_data[phone_index][ph_player_id] = id;
	}
	
	cache_get_value_name_int(0, "is_null_contacts", is_null_contacts);

	if (is_null_contacts > 0)
	{
		/// Загрузка контактов
		for (new i; i < rows; i++)
		{
			/// String
			cache_get_value_name(i, "pc_name", contact_data[phone_index][i][pc_name], MAX_PLAYER_NAME);
			
			/// Integer
			cache_get_value_name_int(i, "pc_number", contact_data[phone_index][i][pc_number]);
			cache_get_value_name_int(i, "pc_created_time", contact_data[phone_index][i][pc_created_time]);
		}
	}
	
	printf("[OnPhoneLoad]: Phone with index %i has been loaded with contacts. (ID: %i, Contacts: %i)",
		phone_index, 
		GetPhoneId(phone_index),
		rows
	);
	
	return 1;
}

