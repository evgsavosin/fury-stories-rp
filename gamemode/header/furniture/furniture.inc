/*!
	@brief Заголовок для системы фурнитуры (House & Garages & Business)
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

// Defines
#define GetFurnId(%0)					furn_data[%0][f_id]
#define IsFurnChangeMaterial(%0)		(furniture_list[%0][fitem_material_index] != INVALID_PARAM)

// Structures
enum E_FURNITURE_DATA
{
	f_id,
	f_owner_index,
	f_owner_type,
	f_item_index,
	f_state,
	
	Float: f_pos_x,
	Float: f_pos_y,
	Float: f_pos_z,
	Float: f_rot_x,
	Float: f_rot_y,
	Float: f_rot_z,
	
	f_texture_type,
	f_texture_index,
	
	f_object,
}

new furn_data				[	MAX_FURN_OBJECTS 	][	E_FURNITURE_DATA	];
	
Clear:furniture_data(index)
{
	furn_data[index][f_owner_index] = INVALID_PARAM;
	furn_data[index][f_owner_type] = TYPE_REN_NONE;
	
	furn_data[index][f_id] =
	furn_data[index][f_state] =
	furn_data[index][f_texture_type] =
	furn_data[index][f_texture_index] = 0;
	
	Clear:furniture_pos(index);
	
	furn_data[index][f_object] = INVALID_OBJECT_ID;
}

Clear:furniture_pos(index)
{
	furn_data[index][f_pos_x] =
	furn_data[index][f_pos_y] =
	furn_data[index][f_pos_z] =
	furn_data[index][f_rot_x] =
	furn_data[index][f_rot_y] =
	furn_data[index][f_rot_z] = 0.0;
}

Create:furn_data(id, index, type, furn_list_index, playerid = INVALID_PLAYER_ID)
{
	new i;
	
	for (; i < sizeof furn_data; i++)
	{
		if (furn_data[i][f_id])
		{
			continue;
		}
		
		Clear:furniture_data(i);
		furn_data[i][f_item_index] = furn_list_index;
		break;
	}
	
	if (i == sizeof furn_data)
	{
		return;
	}
	
	furn_data[i][f_owner_index] = index;
	furn_data[i][f_owner_type] = type;
	
	clean:<g_big_string>;
	format:g_big_string("INSERT INTO " #__FURN " \
		(f_owner_type, f_owner_id, f_item_id, f_pos_x, f_pos_y, f_pos_z, f_rot_x, f_rot_y, f_rot_z) \
		VALUES \
		(%i, %i, %i, %f, %f, %f, %f, %f, %f)",
		type, 
		id,
		furniture_list[furn_list_index][fitem_id],
		furn_data[i][f_pos_x],
		furn_data[i][f_pos_y],
		furn_data[i][f_pos_z],
		furn_data[i][f_rot_x],
		furn_data[i][f_rot_y],
		furn_data[i][f_rot_z]
	);
	
	mysql_tquery(db, g_big_string, "OnFurnCreate", "ii", i, playerid);
}

function OnFurnCreate(index, playerid)
{
	furn_data[index][f_id] = cache_insert_id();
	printf("f_id = %d | cache insert id = %d", furn_data[index][f_id], cache_insert_id());
	
	if (playerid != INVALID_PLAYER_ID)
	{
		UpdateRenovationInfo(playerid);
	}
	
	return 1;
}

Update:furn_data(index)
{
	format:g_big_string("UPDATE " #__FURN " \
		SET \
			f_item_id = %i, \
			f_pos_x = %f, \
			f_pos_y = %f, \
			f_pos_z = %f, \
			f_rot_x = %f, \
			f_rot_y = %f, \
			f_rot_z = %f, \
			f_texture_type = %i, \
			f_texture_index = %i, \
			f_state = %i \
		WHERE \
			f_id = %i \
		LIMIT 1",
		furniture_list[furn_data[index][f_item_index]][fitem_id],
		furn_data[index][f_pos_x],
		furn_data[index][f_pos_y],
		furn_data[index][f_pos_z],
		furn_data[index][f_rot_x],
		furn_data[index][f_rot_y],
		furn_data[index][f_rot_z],
		furn_data[index][f_texture_type],
		furn_data[index][f_texture_index],
		furn_data[index][f_state],
		furn_data[index][f_id]
	);
	
	mysql_tquery(db, g_big_string);
}

Remove:furn_data(const id)
{
	clean:<g_string>;
	
	format:g_string("DELETE FROM " #__FURN " WHERE f_id = %i LIMIT 1",
		id
	);
	
	mysql_pquery(db, g_string);
}
		
Remove:all_furn_data(index, type)
{
	new owner_id = GetFurnOwnerId(index, type);
	
	if (owner_id == INVALID_PARAM)
	{
		return;
	}
	
	for (new i; i < sizeof furn_data; i++)
	{
		if (furn_data[i][f_owner_index] == index 
		&& furn_data[i][f_owner_type] == type)
		{
			Remove:furn(i);
		}
	}
		
	format:g_big_string("\
		DELETE f, i \
		FROM " #__FURN " f \
		LEFT JOIN " #__ITEMS " i \
		ON f.f_id = i.inv_owner_id AND i.inv_owner_type = %i \
		WHERE f.f_owner_id = %i \
		AND f.f_owner_type = %i",
		TYPE_INV_FURN,
		owner_id,
		type
	);
	
	mysql_tquery(db, g_big_string);
}
