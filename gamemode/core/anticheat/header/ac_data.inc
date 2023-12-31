/*!
	@brief ������� (FAC)
	@author Found (evg.savosin)
	@date 12.05.2019
*/

// Constants
const MAX_ATTACH_SLOTS = 10;

// Structures
/// ��� ���������� ��������
enum
{
	AC_ITEM_LIST_NEXT = INVALID_PARAM - 2,
	AC_ITEM_LIST_BACK,
	AC_ITEM_LIST_BEGIN,
	AC_ITEM_LIST_CURRENT,
	AC_ITEM_LIST_NONE
};

/// ������ �� ������
enum AC_PLAYER_DATA 
{	
	ac_weapon_warning	[MAX_WEAPON_SLOTS],
	ac_weapon_id		[MAX_WEAPON_SLOTS],
	ac_ammo				[MAX_WEAPON_SLOTS],
	
	ac_attach_id		[MAX_ATTACH_SLOTS],
	
	ac_vehicle_id, // ID �������� ����������
	ac_vehicle_seat_id, // �����
	
	bool: ac_is_allow_entered,
	ac_enter_vehicle_id, // ID ����������, � ������� ������� �����
	ac_enter_tick, // ����������� ��� �� ����� �������
	
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
	bool: ac_is_set_pos, // � ������ �������� �������
	bool: ac_is_moved, // � ������ �������� �������, ������ �������� �� ��������� �������
	bool: ac_is_death, // ���� �� �����
	
	ac_tick, // ���������� ���
	ac_ping, // ���������� ����
	
	ac_dump_pos_count, // ���������� ������ ������
	
	ac_debug_flood_tick, // ���, ������������� �� ���� � AntiCheatDebug
	ac_detect_flood_tick, // ���, ������������� �� ���� � AntiCheatDetect
	ac_timeout_tick				[MAX_ANTICHEAT_LIST], // ������� �������� �� �����
	ac_detect_tick				[MAX_ANTICHEAT_LIST], // ��� ���������� ��������
	ac_detect_count				[MAX_ANTICHEAT_LIST], // ���������� ��������� �� ��������
}

new ac_player_data				[MAX_PLAYERS][AC_PLAYER_DATA],
	Float: ac_player_pos		[MAX_PLAYERS][AC_POSITION_COUNT][3];

/// ������ � ����������
enum AC_VEH_DATA
{
	Float: ac_distance,
	ac_attach_to_vehicleid
}

new ac_veh_data					[MAX_VEHICLES][AC_VEH_DATA];

/// ����������� �������
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
