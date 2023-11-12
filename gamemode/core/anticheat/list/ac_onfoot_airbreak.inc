/*!
	@brief Античит: Onfoot AirBreak
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_PLAYER_SYNC:AC_ONFOOT_AIRBREAK(playerid, data[PR_OnFootSync])
{
	if (!CheckAntiCheatTimeout(playerid, AC_ONFOOT_AIRBREAK))
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
		),
		speed = GetAntiCheatSpeed(playerid);
	
	#if __AC_DEBUG >= __AC_REPORTING_ALL
		printf("ID_PLAYER_SYNC:AC_ONFOOT_AIRBREAK [%i %i %0.3f %i]", 
			floatcmp(ac_player_data[playerid][ac_pos_z], -95.0),
			floatcmp(data[PR_position][2], -95.0),
			distance,
			speed
		);
	#endif
				
	if (floatcmp(distance, 30.0) == -1
	&& floatcmp(ac_player_data[playerid][ac_pos_z], -95.0) == 1
	&& floatcmp(data[PR_position][2], -95.0) == 1
	&& (data[PR_surfingVehicleId] == 0 || data[PR_surfingVehicleId] == INVALID_VEHICLE_ID)
	&& floatcmp(floatdiv(distance, float(speed == 0 ? 1 : speed)), 2.0) == 1 
	&& floatcmp(distance, float(speed == 0 ? 1 : speed)) == 1)
	{
		if (!AntiCheatDetect(playerid, AC_ONFOOT_AIRBREAK))
		{
			AntiCheatDebug(playerid, 
				AC_ONFOOT_AIRBREAK, 
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