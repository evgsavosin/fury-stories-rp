/*!
	@brief Античит (FAC)
	@author Found (evg.savosin)
	@date 12.05.2019
*/

// Constants
const MAX_ATTACH_SLOTS = 10;

// Structures
/// Для динамичных диалогов
enum
{
	AC_ITEM_LIST_NEXT = INVALID_PARAM - 2,
	AC_ITEM_LIST_BACK,
	AC_ITEM_LIST_BEGIN,
	AC_ITEM_LIST_CURRENT,
	AC_ITEM_LIST_NONE
};

/// Данные об игроке
enum AC_PLAYER_DATA 
{	
	ac_weapon_warning	[MAX_WEAPON_SLOTS],
	ac_weapon_id		[MAX_WEAPON_SLOTS],
	ac_ammo				[MAX_WEAPON_SLOTS],
	
	ac_attach_id		[MAX_ATTACH_SLOTS],
	
	ac_vehicle_id, // ID текущего транспорта
	ac_vehicle_seat_id, // Место
	
	bool: ac_is_allow_entered,
	ac_enter_vehicle_id, // ID транспорта, в который садится игрок
	ac_enter_tick, // Сохраненный тик во время посадки
	
	Float: ac_pos_x,
	Float: ac_pos_y,
	Float: ac_pos_z,
	
	Float: spawn_pos_x,
	Float: spawn_pos_y,
	Float: spawn_pos_z,
	
	bool: ac_is_put_in_car,
	bool: ac_is_in_car,
	bool: ac_is_spectated, // TogglePlayerSpectating
	bool: ac_is_remove_from_vehicle, // RemovePlayerFromVehicle
	bool: ac_is_set_pos, // У игрока изменена позиция
	bool: ac_is_moved, // У игрока изменена позиция, вторая проверка на валидацию позиции
	bool: ac_is_death, // Умер ли игрок
	
	ac_tick, // Актуальный тик
	ac_ping, // Актуальный пинг
	
	ac_dump_pos_count, // Количество дампов позици
	
	ac_debug_flood_tick, // Тик, ответственный за флуд в AntiCheatDebug
	ac_detect_flood_tick, // Тик, ответственный за флуд в AntiCheatDetect
	ac_timeout_tick				[MAX_ANTICHEAT_LIST], // Таймаут античита по тикам
	ac_detect_tick				[MAX_ANTICHEAT_LIST], // Тик последнего варнинга
	ac_detect_count				[MAX_ANTICHEAT_LIST], // Количество варнингов по античиту
}

new ac_player_data				[MAX_PLAYERS][AC_PLAYER_DATA],
	Float: ac_player_pos		[MAX_PLAYERS][AC_POSITION_COUNT][3];

/// Данные о транспорте
enum AC_VEH_DATA
{
	Float: ac_distance,
	ac_attach_to_vehicleid
}

new ac_veh_data					[MAX_VEHICLES][AC_VEH_DATA];

/// Логирование пакетов
new ac_log;

Clear:ac_player_data(playerid)
{
	// Int
	ac_player_data[playerid][ac_enter_tick] = 
	ac_player_data[playerid][ac_tick] = 
	ac_player_data[playerid][ac_debug_flood_tick] =
	ac_player_data[playerid][ac_detect_flood_tick] = 0;
	
	ac_player_data[playerid][ac_vehicle_id] =
	ac_player_data[playerid][ac_enter_vehicle_id] = INVALID_VEHICLE_ID;
	
	ac_player_data[playerid][ac_vehicle_seat_id] = 
	ac_player_data[playerid][ac_dump_pos_count] = INVALID_PARAM;
	
	for (new i; i < MAX_ANTICHEAT_LIST; i++)
	{
		ac_player_data[playerid][ac_detect_tick][i] =
		ac_player_data[playerid][ac_detect_count][i] =
		ac_player_data[playerid][ac_timeout_tick][i] = 0;
	}
	
	for (new i; i < MAX_WEAPON_SLOTS; i++)
	{
		ac_player_data[playerid][ac_weapon_warning][i] =
		ac_player_data[playerid][ac_weapon_id][i] =
		ac_player_data[playerid][ac_ammo][i] = 0;
	}
	
	for (new i; i < MAX_ATTACH_SLOTS; i++)
	{
		ac_player_data[playerid][ac_attach_id][i] = INVALID_OBJECT_ID;
	}
	
	// Float
	ac_player_data[playerid][ac_pos_x] =
	ac_player_data[playerid][ac_pos_y] =
	ac_player_data[playerid][ac_pos_z] = 0.0;
	
	for (new i; i < AC_POSITION_COUNT; i++)
	{
		ac_player_pos[playerid][i][0] =
		ac_player_pos[playerid][i][1] =
		ac_player_pos[playerid][i][2] = 0.0;
	}
	
	// Bool 
	ac_player_data[playerid][ac_is_put_in_car] =
	ac_player_data[playerid][ac_is_in_car] =
	ac_player_data[playerid][ac_is_allow_entered] =
	ac_player_data[playerid][ac_is_death] = 
	ac_player_data[playerid][ac_is_set_pos] =
	ac_player_data[playerid][ac_is_remove_from_vehicle] =
	ac_player_data[playerid][ac_is_spectated] = false;
}

Clear:ac_veh_data(vehicleid)
{
	ac_veh_data[vehicleid][ac_attach_to_vehicleid] = INVALID_VEHICLE_ID;
}

Clear:anticheat(playerid)
{
	Clear:ac_player_data(playerid);
}
