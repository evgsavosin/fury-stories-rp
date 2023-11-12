/*!
	@brief Система загрузки инвентаря
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

Load:inventory(const id, type)
{
	format:g_big_string("\
		SELECT *, \
			   IFNULL(UNIX_TIMESTAMP(inv_create_date), 0) AS inv_created_time, \
			   IFNULL(UNIX_TIMESTAMP(inv_update_date), 0) AS inv_update_time \
		FROM " #__ITEMS " \
		WHERE \
			inv_owner_type = %i \
				AND \
			inv_owner_id = %i \
		LIMIT %i",
		type,
		GetInventoryOwnerId(id, type),
		MAX_INVENTORY_SLOTS
	);

	mysql_tquery(db, g_big_string, "OnInventoryLoad", "ii", id, type);
}

function OnInventoryLoad(const id, type)
{
	clean:<g_string>;
	
	new rows,
		index,
		itindex,
		item_type,
		item_enum				[E_INVENTORY_DATA];
		
	cache_get_row_count(rows);
	
	if (rows == 0)
	{
		return 1;
	}
	
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "inv_index", index);
		
		if (index == INVALID_PARAM)
		{
			continue;
		}
		
		cache_get_value_name_int(i, "inv_id", item_enum[inv_id]);
		cache_get_value_name_int(i, "inv_item_id", item_enum[inv_item_id]);
		cache_get_value_name_int(i, "inv_param_1", item_enum[inv_param_1]);
		cache_get_value_name_int(i, "inv_param_2", item_enum[inv_param_2]);
		cache_get_value_name_int(i, "inv_use_slot", item_enum[inv_use_slot]);
		
		SetInventoryEnumItem(id, index, type, inv_id, item_enum[inv_id]);
		SetInventoryEnumItem(id, index, type, inv_item_id, item_enum[inv_item_id]);
		SetInventoryEnumItem(id, index, type, inv_param_1, item_enum[inv_param_1]);
		SetInventoryEnumItem(id, index, type, inv_param_2, item_enum[inv_param_2]);
		SetInventoryEnumItem(id, index, type, inv_use_slot, item_enum[inv_use_slot]);
		
		if (type == TYPE_INV_PLAYER)
		{
			cache_get_value_name_float(i, "inv_pos_x", item_enum[inv_pos_x]);
			cache_get_value_name_float(i, "inv_pos_y", item_enum[inv_pos_y]);
			cache_get_value_name_float(i, "inv_pos_z", item_enum[inv_pos_z]);
			cache_get_value_name_float(i, "inv_rot_x", item_enum[inv_rot_x]);
			cache_get_value_name_float(i, "inv_rot_y", item_enum[inv_rot_y]);
			cache_get_value_name_float(i, "inv_rot_z", item_enum[inv_rot_z]);
			cache_get_value_name_float(i, "inv_scale_x", item_enum[inv_scale_x]);
			cache_get_value_name_float(i, "inv_scale_y", item_enum[inv_scale_y]);
			cache_get_value_name_float(i, "inv_scale_z", item_enum[inv_scale_z]);
			cache_get_value_name_int(i, "inv_bone", item_enum[inv_bone]);
			
			SetInventoryEnumItem(id, index, type, inv_pos_x, item_enum[inv_pos_x]);
			SetInventoryEnumItem(id, index, type, inv_pos_y, item_enum[inv_pos_y]);
			SetInventoryEnumItem(id, index, type, inv_pos_z, item_enum[inv_pos_z]);
			SetInventoryEnumItem(id, index, type, inv_rot_x, item_enum[inv_rot_x]);
			SetInventoryEnumItem(id, index, type, inv_rot_y, item_enum[inv_rot_y]);
			SetInventoryEnumItem(id, index, type, inv_rot_z, item_enum[inv_rot_z]);
			SetInventoryEnumItem(id, index, type, inv_scale_x, item_enum[inv_scale_x]);
			SetInventoryEnumItem(id, index, type, inv_scale_y, item_enum[inv_scale_y]);
			SetInventoryEnumItem(id, index, type, inv_scale_z, item_enum[inv_scale_z]);
			SetInventoryEnumItem(id, index, type, inv_bone, item_enum[inv_bone]);
		
			if (GetInventoryEnumItem(id, index, type, inv_bone)) // если не 0, то это аттач
			{
				SetInventoryEnumItem(id, index, type, inv_use_attach, true);
			}
		}
		
		itindex = GetItemIndexById(GetInventoryEnumItem(id, index, type, inv_item_id));
		item_type = item_list[itindex][it_type];
		if (item_type == INV_BAG && type != TYPE_INV_BAG)
		{
			Create:bag(id, index, type, true);
		}
		else if (item_type == INV_PHONE)
		{
			format:g_string("SELECT p.*, c.*, IFNULL(c.pc_phone_id, 0) AS is_null_contacts \
				FROM \
					" #__PHONES " p \
				LEFT JOIN \
					" #__CONTACTS " c \
				ON \
					c.pc_phone_id = p.ph_id \
				WHERE \
					p.ph_id = %i \
				ORDER BY \
					c.pc_created_time ASC",
				GetInventoryEnumItem(id, index, type, inv_param_1)
			);
			
			mysql_tquery(db, g_string, "OnPhoneLoad", "ii", id, type);
		}
	}
	
	return 1;
}