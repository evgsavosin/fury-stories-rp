/*!
	@brief Античит (FAC) - Список античитов
	@author Found (evg.savosin)
	@date 12.05.2019
*/

/// Список античитов
enum
{
	AC_SPECIAL_ACTION = 0x0, // 0 - Special Action (Jetpack)
	AC_DRIVER_RVANKA, // 1 - Driver Rvanka
	AC_ONFOOT_RVANKA, // 2 - Onfoot Rvanka
	AC_UNOCCUPIED_RVANKA, // 3 - Unoccupied Rvanka
	AC_ONFOOT_FLYHACK, // 4 - Onfoot Flyhack 
	AC_INVISIBLE_SURF, // 5 - Invisible Surf
	AC_ONFOOT_TELEPORT, // 6 - Onfoot Teleport
	AC_CAR_TO_PLAYER, // 7 - Teleport Car2player
	AC_DRIVER_TELEPORT, // 8 - Driver Teleport
	AC_CAR_SLAPPER, // 9 - Car slapper
	AC_ONFOOT_AIRBREAK, // 10 - Onfoot Airbreak
	AC_DRIVER_AIRBREAK, // 11 - Driver Airbreak
	AC_FAKE_DEATH, // 12 - Fake death
	AC_DRIVER_ENTER, // 13 - Driver Enter
	AC_PASSENGER_ENTER, // 14 - Passenger Enter
	AC_DRIVER_FAST_ENTER, // 15 - Driver Fast Enter
	AC_PASSENGER_FAST_ENTER, // 16 - Passenger Fast Enter
	AC_WEAPON_HACK, // 17 - Weapon Hack
	AC_DRIVER_SPEED_HACK, // 18 - Speed Hack
	AC_RAKNET_HACK, // 19 - Invalid raknet data
	
	AC_ATTACH_CRASHER, // 20 - Attach crasher
	AC_WEAPON_CRASHER, // 21 - Weapon crasher
	
	AC_TRAILER_TELEPORT, // 22 - Trailer teleport
	
	NOP_PLAYER_SPECTATE,
	NOP_REMOVE_FROM_VEHICLE,
	
	MAX_ANTICHEAT_LIST
};

// Режим работы античита
enum
{
	AC_PUNISH_IGNORE = 0x0,
	AC_PUNISH_WARNING,
	AC_PUNISH_KICK,
	
	MAX_ANTICHEAT_PUNISH_LIST
};

new const anticheat_punish_list	[MAX_ANTICHEAT_PUNISH_LIST][] =
{
	{#cGRAY "Игнорирование" #cWHITE},
	{#cWHITE "Предупреждение" #cWHITE},
	{#cRED "Отсоединение" #cWHITE}
};

/// Данные об античите
enum E_ANTICHEAT_LIST_DATA
{
	ac_code, // Код античита
	ac_name				[32], // Название
	ac_type_punish, // Тип наказания
	ac_logic_warning_count, // Количество предупреждений до наказания в логике
	ac_timeout_tick, // Задержка в миллисекундах для избежания ложных срабатываний
	bool: ac_is_nop // Проверка на NOP
};

new anticheat_list		[MAX_ANTICHEAT_LIST][E_ANTICHEAT_LIST_DATA] =
{
	// AntiCheats
	{AC_SPECIAL_ACTION, "Special Action", AC_PUNISH_KICK, 0, 0, false},
	{AC_DRIVER_RVANKA, "Driver Rvanka", AC_PUNISH_KICK, 0, 0, false},
	{AC_ONFOOT_RVANKA, "Onfoot Rvanka", AC_PUNISH_KICK, 0, 0, false},
	{AC_UNOCCUPIED_RVANKA, "Unoccupied Rvanka", AC_PUNISH_KICK, 0, 0, false},
	{AC_ONFOOT_FLYHACK, "Onfoot Flyhack", AC_PUNISH_KICK, 2, 0, false},
	{AC_INVISIBLE_SURF, "Invisible Surf", AC_PUNISH_WARNING, 1, 0, false},
	{AC_ONFOOT_TELEPORT, "Onfoot Teleport", AC_PUNISH_WARNING, 0, 1000, false},
	{AC_CAR_TO_PLAYER, "Teleport Car2layer", AC_PUNISH_KICK, 3, 0, false},
	{AC_DRIVER_TELEPORT, "Driver Teleport", AC_PUNISH_WARNING, 0, 1000, false},
	{AC_CAR_SLAPPER, "Car Slapper", AC_PUNISH_KICK, 0, 0, false},
	{AC_ONFOOT_AIRBREAK, "Onfoot Airbreak", AC_PUNISH_WARNING, 2, 3500, false},
	{AC_DRIVER_AIRBREAK, "Driver Airbreak", AC_PUNISH_KICK, 2, 3500, false},
	{AC_FAKE_DEATH, "Fake Death", AC_PUNISH_KICK, 0, 0, false},
	{AC_DRIVER_ENTER, "Driver Enter", AC_PUNISH_WARNING, 0, 0, false},
	{AC_PASSENGER_ENTER, "Passenger Enter", AC_PUNISH_WARNING, 0, 0, false},
	{AC_DRIVER_FAST_ENTER, "Driver Fast Enter", AC_PUNISH_WARNING, 0, 4000, false},
	{AC_PASSENGER_FAST_ENTER, "Passenger Fast Enter", AC_PUNISH_WARNING, 0, 4000, false},
	{AC_WEAPON_HACK, "Weapon Hack", AC_PUNISH_KICK, 0, 2000, false},
	{AC_DRIVER_SPEED_HACK, "Driver Speedhack", AC_PUNISH_KICK, 0, 0, false},
	{AC_RAKNET_HACK, "Invalid Raknet Packet", AC_PUNISH_KICK, 0, 0, false},
	{AC_ATTACH_CRASHER, "Attach Crasher", AC_PUNISH_KICK, 0, 0, false},
	{AC_WEAPON_CRASHER, "Weapon Crasher", AC_PUNISH_KICK, 0, 0, false},
	{AC_TRAILER_TELEPORT, "Trailer Teleport", AC_PUNISH_KICK, 0, 0, false},
	
	// NOP's
	{NOP_PLAYER_SPECTATE, "NOP TogglePlayerSpectating", AC_PUNISH_KICK, 0, 0, true},
	{NOP_REMOVE_FROM_VEHICLE, "NOP RemovePlayerFromVehicle", AC_PUNISH_KICK, 1, 1000, true}
};
