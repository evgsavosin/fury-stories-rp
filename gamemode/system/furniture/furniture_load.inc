/*!
	@brief Функция загрузки фурнитуры из базы данных
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

Load:furn(const id, index, type)
{
	format:g_string("SELECT * FROM " #__FURN " WHERE f_owner_type = %i AND f_owner_id = %i",
		type, id
	);
	
	mysql_tquery(db, g_string, "OnFurnLoad", "iii", id, index, type);
}

function OnFurnLoad(id, index, type)
{
	new rows,
		fid,
		item_id,
		item_index;
		
	cache_get_row_count(rows);
	
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "f_id", fid);
		cache_get_value_name_int(i, "f_item_id", item_id);
		
		if (fid == 0)
		{
			continue;
		}
		
		if ((item_index = GetFurnItemIndexByItemId(item_id)) == INVALID_PARAM)
		{
			Remove:furn_data(fid);
			continue;
		}
			
		for (new j; j < sizeof furn_data; j++)
		{
			if (GetFurnId(j) != 0)
			{
				continue;
			}
			
			furn_data[j][f_id] = fid;
			furn_data[j][f_item_index] = item_index;
			
			cache_get_value_name_int(i, "f_state", furn_data[j][f_state]);
			
			cache_get_value_name_float(i, "f_pos_x", furn_data[j][f_pos_x]);
			cache_get_value_name_float(i, "f_pos_y", furn_data[j][f_pos_y]);
			cache_get_value_name_float(i, "f_pos_z", furn_data[j][f_pos_z]);
			cache_get_value_name_float(i, "f_rot_x", furn_data[j][f_rot_x]);
			cache_get_value_name_float(i, "f_rot_y", furn_data[j][f_rot_y]);
			cache_get_value_name_float(i, "f_rot_z", furn_data[j][f_rot_z]);
			
			cache_get_value_name_int(i, "f_texture_type", furn_data[j][f_texture_type]);
			cache_get_value_name_int(i, "f_texture_index", furn_data[j][f_texture_index]);
			
			furn_data[j][f_owner_index] = index;
			furn_data[j][f_owner_type] = type;
			
			if (furn_data[j][f_state])
			{
				Create:furn(
					id, 
					j, 
					type,
					furn_data[j][f_pos_x],
					furn_data[j][f_pos_y],
					furn_data[j][f_pos_z],
					furn_data[j][f_rot_x],
					furn_data[j][f_rot_y],
					furn_data[j][f_rot_z]
				);
			}
			
			Load:inventory(j, TYPE_INV_FURN);
			break;
		}
	}

	return 1;
}