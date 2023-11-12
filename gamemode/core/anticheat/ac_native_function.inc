/*!
	@brief Перехват нативных функций
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
	
	Синтаксис:
	
	AC_*(...)
*/

// Original
native SAMP_GetPlayerWeaponData(playerid, slot, &weaponid, &ammo) = GetPlayerWeaponData;

stock AC_GetPlayerWeaponData(playerid, slot, &weaponid, &ammo)
{
	if (!IsPlayerConnected(playerid) 
	|| !(0 <= slot <= MAX_WEAPON_SLOTS))
	{
		weaponid = 
		ammo = 0;
		return 0;
	}
	
	weaponid = ac_player_data[playerid][ac_weapon_id][slot];
	ammo = ac_player_data[playerid][ac_ammo][slot];
	return 1;
}

#if defined ALS_GetPlayerWeaponData
    #undef GetPlayerWeaponData
#else
    #define _ALS_GetPlayerWeaponData
#endif

#undef GetPlayerWeaponData
#define GetPlayerWeaponData AC_GetPlayerWeaponData


stock AC_CreateVehicle(modelid, Float: x, Float: y, Float: z, Float: angle, color1, color2, respawn_delay, addsiren = 0)
{
	new vehicleid = CreateVehicle(modelid, Float: x, Float: y, Float: z, Float: angle, color1, color2, respawn_delay, addsiren);
	
	Clear:ac_veh_data(vehicleid);
	
	return vehicleid;
}

#if defined ALS_CreateVehicle
    #undef CreateVehicle
#else
    #define _ALS_CreateVehicle
#endif

#undef CreateVehicle
#define CreateVehicle AC_CreateVehicle