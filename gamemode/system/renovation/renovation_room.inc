/*!
	@brief Загрузка комнат для системы ремонта
	@author Found (evg.savosin)
	@date 12.02.2020
*/

Load:room(const id, index, type)
{
	format:g_string("SELECT * FROM " #__ROOMS " WHERE r_owner_id = %i AND r_owner_type = %i LIMIT %i", 
		id,
		type,
		MAX_ROOMS
	);
	
	mysql_tquery(db, g_string, "OnRoomLoad", "ii", index, type);
}

function OnRoomLoad(index, type)
{
	new rows,
		roof,
		floor,
		wall,
		room,
		count;
	
	new bool: is_room_exists	[MAX_ROOMS];
	
	cache_get_row_count(rows);
	
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "r_number", room);
		cache_get_value_name_int(i, "r_roof", roof);
		cache_get_value_name_int(i, "r_floor", floor);
		cache_get_value_name_int(i, "r_wall", wall);
		
		if (type == TYPE_REN_HOUSE)
		{
			hroom_data[index][room][r_roof] = roof;
			hroom_data[index][room][r_floor] = floor;
			hroom_data[index][room][r_wall] = wall;
		
			SetHouseInteriorMaterial(index, room, 
				hint_wall_begin, 
				hint_wall_end, 
				TEXTURE_WALL,
				hroom_data[index][room][r_wall] 
			);
			
			SetHouseInteriorMaterial(index, room, 
				hint_roof_begin, 
				hint_roof_end, 
				TEXTURE_ROOF,
				hroom_data[index][room][r_roof] 
			);
			
			SetHouseInteriorMaterial(index, room, 
				hint_floor_begin,
				hint_floor_end, 
				TEXTURE_FLOOR,
				hroom_data[index][room][r_floor] 
			);
		}
		else if (type == TYPE_REN_PREMISE)
		{
			proom_data[index][room][r_roof] = roof;
			proom_data[index][room][r_floor] = floor;
			proom_data[index][room][r_wall] = wall;
		
			SetPremiseInteriorMaterial(index, room, 
				pint_wall_begin, 
				pint_wall_end, 
				TEXTURE_WALL,
				proom_data[index][room][r_wall] 
			);
			
			SetPremiseInteriorMaterial(index, room, 
				pint_roof_begin, 
				pint_roof_end, 
				TEXTURE_ROOF,
				proom_data[index][room][r_roof] 
			);
			
			SetPremiseInteriorMaterial(index, room, 
				pint_floor_begin,
				pint_floor_end, 
				TEXTURE_FLOOR,
				proom_data[index][room][r_floor] 
			);
		}
		
		is_room_exists[room] = true;
		count++;
	}
	
	// Проверяем на предмет утери записей из базы данных
	if (type == TYPE_REN_HOUSE)
	{
		new interior_type = house_data[index][h_int_type],
			room_count = house_settings[interior_type][hset_rooms];
		
		if (count == room_count)
		{
			return 1;
		}
		
		for (new i; i < room_count; i++)
		{
			if (is_room_exists[i])
			{
				continue;
			}
			
			format:g_big_string("INSERT INTO " #__ROOMS " (r_owner_type, r_owner_id, r_number) \
			VALUES (%i, %i, %i)", TYPE_REN_HOUSE, house_data[index][h_id], i);
			mysql_pquery(db, g_big_string);
		}
	}
	else if (type == TYPE_REN_PREMISE)
	{
		new interior_type = premise_data[index][pr_int_type],
			room_count = premise_settings[interior_type][pset_rooms];
			
		if (count == room_count)
		{
			return 1;
		}
		
		for (new i; i < room_count; i++)
		{
			if (is_room_exists[i])
			{
				continue;
			}
			
			format:g_big_string("INSERT INTO " #__ROOMS " (r_owner_type, r_owner_id, r_number) \
			VALUES (%i, %i, %i)", TYPE_REN_PREMISE, premise_data[index][pr_id], i);
			mysql_pquery(db, g_big_string);
		}
	}
	
	return 1;
}

ShowRoomList(playerid, index, dialogid, type = TYPE_REN_HOUSE)
{
	clean:<g_big_string>;
	
	new rooms = (type == TYPE_REN_HOUSE ? GetHouseSettings(index, hset_rooms) : GetPremiseSettings(index, pset_rooms));
		
	for (new i; i < rooms; i++)
	{	
		format:g_big_string("%s Зона #%d\n", g_big_string, i + 1);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", g_big_string, "Выбрать", "Назад");
}