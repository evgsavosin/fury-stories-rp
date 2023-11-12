/*!
	@brief Заголовок системы инвентаря
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
*/

// Defines
#define DIALOG_INV_BONE 		"\
" #cGRAY "Выберите часть тела:" #cWHITE "\n \
	Спина\n \
	Голова\n \
	Плечо левой руки\n \
	Плечо правой руки\n \
	Левая рука\n \
	Правая рука\n \
	Левое бедро\n \
	Правое бедро\n \
	Левая нога\n \
	Правая нога\n \
	Правые икры\n \
	Левые икры\n \
	Левое предплечье\n \
	Правое предплечье\n \
	Левая ключица\n \
	Правая ключица\n \
	Шея\n \
	Челюсть\
"

#define DIALOG_INV_SELECT				" Информация\n %s\n Передать\n Выбросить\n Удалить"

#define ATTACH_INV_FUEL					0.124999, 0.013999, 0.019, 0.0, -97.9, 0.0

#define GetMaskId(%0)					100+%0		
#define GetWeaponSerialNumber(%0)		16_000+%0			

#define IsInventoryTypeShow(%0,%1)		(GetUserSettings(%0,SET_INVENTORY)==%1)
#define IsInventoryTextDrawShowed(%0)	(GetPVarInt(%0,!"Inventory:States"))

// Constants 
const INVENTORY_FRACTION_ITEM = -1;

// Structures
/// Типы интерфейсов инвентаря
enum 
{
	TEXTDRAW_INVENTORY = 0,
	DIALOG_INVENTORY
};

/// Типы инвентарей у систем
enum 
{
	TYPE_INV_PLAYER = 0, /// 0
	TYPE_INV_VEHICLE, /// 1 
	TYPE_INV_FURN, /// 2 
	TYPE_INV_BAG, /// 3 
	TYPE_INV_VEH_GLOVE /// 4
};

/// Типы слотов
enum 
{
	DEFAULT_SLOT = 0, /// Обычный, серый
	ACTIVE_SLOT, /// Активный, бирюзовый
	WEAPON_BIG_SLOT /// С оружием, красный
};

/// Типы использования оружия 
enum 
{
	TYPE_USE_NONE,
	TYPE_USE_DEFAULT = 1, /// 1 - взять в руки
	TYPE_USE_ATTACH /// 2 - прикрепить
};

/// Типы аттачей
enum 
{
	DEFAULT_ATTACH,
	WEAPON_ATTACH,
	BAG_ATTACH
};

/// Attach State
enum 
{
	ATTACH_STATE_OFF,
	ATTACH_STATE_DEFAULT,
	ATTACH_STATE_SMOKE,
	ATTACH_STATE_BAG
};

enum 
{
	INV_ACTION_PUT = 0, /// положить 
	INV_ACTION_TAKE /// Взять
};

enum E_INVENTORY_DATA
{
	inv_id,
	
	inv_item_id,					
	inv_use_slot,		
	inv_param_1,
	inv_param_2,
	
	Float: inv_pos_x, /// позиция на теле
	Float: inv_pos_y, /// позиция на теле
	Float: inv_pos_z, /// позиция на теле
	Float: inv_rot_x, /// Угол на теле
	Float: inv_rot_y,
	Float: inv_rot_z,
	Float: inv_scale_x, /// Размер на теле
	Float: inv_scale_y,
	Float: inv_scale_z,
	inv_bone, /// кость
	
	inv_use_attach
};

enum E_ITEM_DROP_DATA
{
	drop_item_id,
	drop_item_param_1,
	drop_item_param_2,
	drop_object,
	
	Float: drop_pos_x,
	Float: drop_pos_y,
	Float: drop_pos_z,
	
	Text3D: drop_label,
	drop_character_id,
	
	drop_use_inv,
	drop_func,
	drop_area,
	
	drop_boombox_url					[		MAX_MUSIC_URL		]
};

enum E_ATTACH_DATA
{
	a_slot,
	a_object
};

new inv_data							[	MAX_PLAYERS		][	MAX_INVENTORY_SLOTS	][	E_INVENTORY_DATA	],
	vehicle_inv_data					[	MAX_VEHICLES	][	MAX_INVENTORY_SLOTS	][	E_INVENTORY_DATA	],
	veh_comp_inv_data					[	MAX_VEHICLES	][	MAX_INVENTORY_SLOTS	][	E_INVENTORY_DATA	],
	bag_inv_data						[	MAX_BAGS		][	MAX_INVENTORY_SLOTS	][	E_INVENTORY_DATA 	],
	drop_data							[	MAX_DROP_ITEMS	][	E_ITEM_DROP_DATA],
	furn_inv_data						[	MAX_FURN_OBJECTS	][	MAX_INVENTORY_SLOTS][E_INVENTORY_DATA	],
	
	inventory_list_id					[	MAX_PLAYERS		][ MAX_INVENTORY_SLOTS	+ 1],
	inventory_select_slot				[	MAX_PLAYERS		][	MAX_INVENTORY_SLOTS	+ 1],
	inventory_attach					[  MAX_PLAYERS		][ MAX_INVENTORY_ATTACH + 1], // + 1 for bag
	inventory_veh_attach				[	MAX_VEHICLES	][	MAX_INVENTORY_ATTACH][ E_ATTACH_DATA 	],
	
	PlayerText: inventory_td_select		[	MAX_PLAYERS	];
	

Clear:drop_data(index)
{
	drop_data[index][drop_item_id] = 
	drop_data[index][drop_item_param_1] =
	drop_data[index][drop_item_param_2] =
	drop_data[index][drop_character_id] = 
	
	drop_data[index][drop_func] =
	drop_data[index][drop_use_inv] =
	drop_data[index][drop_area] = 0;
	
	drop_data[index][drop_object] = INVALID_OBJECT_ID;
	
	drop_data[index][drop_pos_x] =
	drop_data[index][drop_pos_y] =
	drop_data[index][drop_pos_z] = 0.0;
	
	drop_data[index][drop_label] = Text3D: INVALID_3DTEXT_ID;
	
	drop_data[index][drop_boombox_url][0] = EOS;
}

Clear:inv_data_slot(const id, index, type = TYPE_INV_PLAYER)
{
	SetInventoryEnumItem(id, index, type, inv_id, 0);
	SetInventoryEnumItem(id, index, type, inv_item_id, 0);
	SetInventoryEnumItem(id, index, type, inv_use_slot, 0);
	SetInventoryEnumItem(id, index, type, inv_use_attach, 0);
	SetInventoryEnumItem(id, index, type, inv_param_1, 0);
	SetInventoryEnumItem(id, index, type, inv_param_2, 0);
	
	Clear:attach_inv_data(id, index, type);
}

GetInventoryEnumItem(const id, index, type, E_INVENTORY_DATA: enum_item)
{
	if (id == INVALID_PARAM)
	{
		return 0;
	}
	
	if ((enum_item == inv_use_slot && type != TYPE_INV_PLAYER) 
	|| (inv_pos_x <= enum_item <= inv_bone) && type != TYPE_INV_PLAYER)
	{
		return 0;
	}
	
	if (type == TYPE_INV_PLAYER)
	{
		return _: inv_data[id][index][enum_item];
	}
	else if (type == TYPE_INV_VEHICLE)
	{
		return _: vehicle_inv_data[id][index][enum_item];
	}
	else if (type == TYPE_INV_BAG)
	{
		return _: bag_inv_data[id][index][enum_item];
	}
	else if (type == TYPE_INV_FURN)
	{
		return _: furn_inv_data[id][index][enum_item];
	}
	else if (type == TYPE_INV_VEH_GLOVE)
	{
		return _: veh_comp_inv_data[id][index][enum_item];
	}
	
	return 0;
}

SetInventoryEnumItem(const id, index, type, E_INVENTORY_DATA: enum_item, {Float, _}: ...)
{
	#define STATIC_ARGS 	(	4 	)
	
	if (index <= INVALID_PARAM)
	{
		return;
	}

	if (type == TYPE_INV_PLAYER)
	{
		inv_data[id][index][enum_item] = getarg(STATIC_ARGS);
	}
	else if (type == TYPE_INV_VEHICLE)
	{
		vehicle_inv_data[id][index][enum_item] = getarg(STATIC_ARGS);
	}
	else if (type == TYPE_INV_BAG)
	{
		bag_inv_data[id][index][enum_item] = getarg(STATIC_ARGS);
	}
	else if (type == TYPE_INV_FURN)
	{
		furn_inv_data[id][index][enum_item] = getarg(STATIC_ARGS);
	}
	else if (type == TYPE_INV_VEH_GLOVE)
	{
		veh_comp_inv_data[id][index][enum_item] = getarg(STATIC_ARGS);
	}
	
	#undef STATIC_ARGS
}

Clear:attach_inv_data(const id, index, type)
{
	if (type == TYPE_INV_PLAYER)
	{
		for (new i; i < MAX_INVENTORY_ATTACH + 1; i++)
		{
			if (inventory_attach[id][i] != index)
			{
				continue;
			}
			
			inventory_attach[id][i] = INVALID_PARAM;
		}
	}
	else if (type == TYPE_INV_VEHICLE)
	{
		for (new i; i < MAX_INVENTORY_ATTACH; i++)
		{
			if (inventory_veh_attach[id][i][a_slot] != index)
			{
				continue;
			}
			
			inventory_veh_attach[id][i][a_object] =
			inventory_veh_attach[id][i][a_slot] = INVALID_PARAM;
		}
	}

	SetInventoryEnumItem(id, index, type, inv_use_attach, false);
	
	SetInventoryEnumItem(id, index, type, inv_pos_x, 0.0);
	SetInventoryEnumItem(id, index, type, inv_pos_y, 0.0);
	SetInventoryEnumItem(id, index, type, inv_pos_z, 0.0);
	
	SetInventoryEnumItem(id, index, type, inv_rot_x, 0.0);
	SetInventoryEnumItem(id, index, type, inv_rot_y, 0.0);
	SetInventoryEnumItem(id, index, type, inv_rot_z, 0.0);
	
	SetInventoryEnumItem(id, index, type, inv_scale_x, 0.0);
	SetInventoryEnumItem(id, index, type, inv_scale_y, 0.0);
	SetInventoryEnumItem(id, index, type, inv_scale_z, 0.0);
	
	SetInventoryEnumItem(id, index, type, inv_bone, 0);
}

Clear:inv_data(playerid)
{
	new i = 0x0;
	
	do
	{
		Clear:inv_data_slot(playerid, i, TYPE_INV_PLAYER);
	} 
	while (++i < MAX_INVENTORY_SLOTS);
	
	inventory_td_select[playerid] = INVALID_PTD;
}	

Clear:vehicle_inv_data(vehicleid)
{
	new i = 0x0;
		
	do
	{
		Clear:inv_data_slot(vehicleid, i, TYPE_INV_VEHICLE);
	} 
	while (++i < MAX_INVENTORY_SLOTS);
}	

Clear:veh_comp_inv_data(vehicleid)
{
	new i = 0x0;
		
	do
	{
		Clear:inv_data_slot(vehicleid, i, TYPE_INV_VEH_GLOVE);
	} 
	while (++i < MAX_INVENTORY_SLOTS);
}

Clear:furn_inv_data(index)
{
	new i = 0x0;
		
	do
	{
		Clear:inv_data_slot(index, i, TYPE_INV_FURN);
	} 
	while (++i < MAX_INVENTORY_SLOTS);
}

Recreate:item_data(const id, index, type, db_id)
{
	strglobalclear();
	
	SetInventoryEnumItem(id, index, type, inv_id, db_id);
	
	format:g_big_string(
		"INSERT INTO " #__ITEMS " (inv_id, inv_owner_type, inv_owner_id, inv_item_id, inv_param_1, inv_param_2, inv_index, inv_create_date, inv_update_date) \
			VALUES \
		(%i, %i, %i, %i, %i, %i, %i, NOW(), NOW())",
		db_id,
		type,
		GetInventoryOwnerId(id, type),
		GetInventoryEnumItem(id, index, type, inv_item_id),
		GetInventoryEnumItem(id, index, type, inv_param_1),
		GetInventoryEnumItem(id, index, type, inv_param_2),
		index
	);
	
	mysql_tquery(db, g_big_string);
	return 1;
}

Create:item_data(const id, index, type)
{
	strglobalclear();
	
	format:g_big_string(
		"INSERT INTO " #__ITEMS " (inv_owner_type, inv_owner_id, inv_item_id, inv_param_1, inv_param_2, inv_index, inv_create_date, inv_update_date) \
			VALUES \
		(%i, %i, %i, %i, %i, %i, NOW(), NOW())",
		type,
		GetInventoryOwnerId(id, type),
		GetInventoryEnumItem(id, index, type, inv_item_id),
		GetInventoryEnumItem(id, index, type, inv_param_1),
		GetInventoryEnumItem(id, index, type, inv_param_2),
		index
	);
	
	mysql_tquery(db, g_big_string, "OnItemCreate", "iii", id, index, type);
	return 1;
}

function OnItemCreate(const id, index, type)
{
	SetInventoryEnumItem(id, index, type, inv_id, cache_insert_id());
	
	new itindex = GetItemIndexById(GetInventoryEnumItem(id, index, type, inv_item_id));
	
	if (item_list[itindex][it_type] == INV_BAG)
	{
		Create:bag(id, index, type);
	}
	
	return 1;
}

Update:item_data(const id, index, type, new_owner_id = INVALID_PARAM, newslot = INVALID_PARAM, newtype = INVALID_PARAM, bool: ignore_allow_query = false)
{	
	strglobalclear();
	
	new_owner_id = (new_owner_id == INVALID_PARAM) ? GetInventoryOwnerId(id, type) : new_owner_id;
	newslot = (newslot == INVALID_PARAM) ? index : newslot;
	newtype = (newtype == INVALID_PARAM) ? type : newtype;
	
	if (new_owner_id == INVALID_PARAM)
	{
		return 0;
	}
	
	if (type == TYPE_INV_PLAYER && !ignore_allow_query)
	{
		if (!IsUserAllowQuery(id))
		{
			return 0;
		}
	}
	
	format:g_big_string(
		"UPDATE " #__ITEMS " \
			SET \
				inv_index = %i, \
				inv_item_id = %i, \
				inv_use_slot = %i, \
				inv_param_1 = %i, \
				inv_param_2 = %i, \
				inv_pos_x = %f, \
				inv_pos_y = %f, \
				inv_pos_z = %f, \
				inv_rot_x = %f, \
				inv_rot_y = %f, \
				inv_rot_z = %f, \
				inv_scale_x = %f, \
				inv_scale_y = %f, \
				inv_scale_z = %f, \
				inv_bone = %i, \
				inv_update_date = NOW(), \
				inv_owner_type = %i, \
				inv_owner_id = %i \
			WHERE \
				inv_id = %i AND inv_owner_type = %i \
			LIMIT 1",
		newslot,
		GetInventoryEnumItem(id, index, type, inv_item_id),
		GetInventoryEnumItem(id, index, type, inv_use_slot),
		GetInventoryEnumItem(id, index, type, inv_param_1),
		GetInventoryEnumItem(id, index, type, inv_param_2),
		GetInventoryEnumItem(id, index, type, inv_pos_x),
		GetInventoryEnumItem(id, index, type, inv_pos_y),
		GetInventoryEnumItem(id, index, type, inv_pos_z),
		GetInventoryEnumItem(id, index, type, inv_rot_x),
		GetInventoryEnumItem(id, index, type, inv_rot_y),
		GetInventoryEnumItem(id, index, type, inv_rot_z),
		GetInventoryEnumItem(id, index, type, inv_scale_x),
		GetInventoryEnumItem(id, index, type, inv_scale_y),
		GetInventoryEnumItem(id, index, type, inv_scale_z),
		GetInventoryEnumItem(id, index, type, inv_bone),
		newtype,
		new_owner_id,
		GetInventoryEnumItem(id, index, type, inv_id),
		type
	);
	
	mysql_tquery(db, g_big_string, "OnInventoryItemUpdate", "ddd", id, type, _: ignore_allow_query);
	
	if (type == TYPE_INV_PLAYER && !ignore_allow_query)
	{
		SetUserAllowQuery(id, false);
	}
	
	return 1;
}

function OnInventoryItemUpdate(id, type, ignore_allow_query)
{
	if (type == TYPE_INV_PLAYER && !ignore_allow_query)
	{
		SetUserAllowQuery(id, true);
	}
	
	return 1;
}

Remove:item_data(const id, index, type)
{	
	format:g_string("DELETE FROM " #__ITEMS " WHERE inv_id = %d LIMIT 1",
		GetInventoryEnumItem(id, index, type, inv_id)
	);
	
	mysql_tquery(db, g_string);
	
	Clear:inv_data_slot(id, index, type);
}

GetInventoryMaxTypeItems(type, bool: is_use) // максимальное количество типовых предметов используется
{
	switch(type)
	{
		case INV_WEAPON_BIG : 
		{
			return 1;
		}
		
		case INV_WEAPON_SMALL : 
		{
			return is_use ? 1 : 5;
		}
		
		case INV_ATTACH : 
		{
			return is_use ? MAX_INVENTORY_ATTACH : MAX_INVENTORY_SLOTS;
		}
		
		case INV_BAG : 
		{
			return 1;
		}
		
		case INV_PHONE :
		{
			return is_use ? 2 : MAX_PLAYER_PHONES;
		}
		
		case INV_RADIO :
		{
			return is_use ? 1 : 3;
		}
	}
	
	return MAX_INVENTORY_SLOTS;
}