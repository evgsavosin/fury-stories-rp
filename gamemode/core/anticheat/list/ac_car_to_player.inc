/*!
	@brief Античит: Unoccupied Car To Player
	@author Found (evg.savosin)
	@date 12.05.2019
*/

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float: new_x, Float: new_y, Float: new_z, Float: vel_x, Float: vel_y, Float: vel_z)
{
	new Float: x,
		Float: y,
		Float: z,
		Float: angle,
		Float: distance = GetVehicleDistanceFromPoint(vehicleid, new_x, new_y, new_z),
		Float: distance_calc;

	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, angle);

	distance_calc = ac_veh_data[vehicleid][ac_distance] + ((distance / 3) * 1.6);
	
	#if __AC_DEBUG >= __AC_REPORTING_ALL
		printf("ID_UNOCCUPIED_SYNC:AC_CAR_TO_PLAYER [%i %0.2f %i %0.2f]",
			floatcmp(distance, 15.0) == 1,
			distance,
			floatcmp(z, -70.0) == 1,
			distance_calc
		);
	#endif
	
	if (floatcmp(distance, 15.0) == 1 
	&& floatcmp(z, -70.0) == 1 
	&& floatcmp(distance, distance_calc) == 1)
	{
		AntiCheatDebug(playerid, 
			AC_CAR_TO_PLAYER, 
			"PLAYERID", 
			float(playerid),
			"VEHICLEID",
			float(vehicleid),
			"DISTANCE", 
			distance,
			"DISTANCE CALC",
			distance_calc
		);
		
		SetVehiclePos(vehicleid, x, y, z);
		SetVehicleZAngle(vehicleid, angle);
		return 0;
	}
	
	ac_veh_data[vehicleid][ac_distance] = distance;
	
#if defined AC_OnUnoccupiedVehicleUpdate
    return AC_OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float: new_x, Float: new_y, Float: new_z, Float: vel_x, Float: vel_y, Float: vel_z);
#else
	return 1;
#endif
}
#if defined _ALS_OnUnoccupiedVehicleUpdate
    #undef OnUnoccupiedVehicleUpdate
#else
    #define _ALS_OnUnoccupiedVehicleUpdate
#endif
#define	OnUnoccupiedVehicleUpdate	AC_OnUnoccupiedVehicleUpdate
#if defined AC_OnUnoccupiedVehicleUpdate
	forward AC_OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float: new_x, Float: new_y, Float: new_z, Float: vel_x, Float: vel_y, Float: vel_z);
#endif
