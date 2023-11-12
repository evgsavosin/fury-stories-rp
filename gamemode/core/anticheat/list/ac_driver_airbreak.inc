/*!
	@brief Античит: Driver AirBreak
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_VEHICLE_SYNC:AC_DRIVER_AIRBREAK(playerid, data[PR_InCarSync])
{
	if (!CheckAntiCheatTimeout(playerid, AC_DRIVER_AIRBREAK))
	{
		return 1;
	}
	
	new Float: distance = GetDistanceBetweenPoints( 
		data[PR_position][0],
		data[PR_position][1],
		data[PR_position][2],
		ac_player_data[playerid][ac_pos_x], 
		ac_player_data[playerid][ac_pos_y], 
		ac_player_data[playerid][ac_pos_z]
	);
	
	if (floatcmp(ac_player_data[playerid][ac_pos_z], -95.0) == 1
	&& floatcmp(data[PR_position][2], -95.0) == 1
	&& floatcmp(distance, 3.0) == 1 
	&& GetAntiCheatSpeed(playerid) < 2)
	{
		if (!AntiCheatDetect(playerid, AC_DRIVER_AIRBREAK))
		{
			AntiCheatDebug(playerid, 
				AC_DRIVER_AIRBREAK, 
				"PLAYERID", 
				float(playerid),
				"DISTANCE", 
				distance
			);
			
			return 0;
		}
	}
	
	return 1;
}
