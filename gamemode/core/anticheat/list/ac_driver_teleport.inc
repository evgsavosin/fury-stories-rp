/*!
	@brief Античит: Driver Teleport
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_VEHICLE_SYNC:AC_DRIVER_TELEPORT(playerid, data[PR_InCarSync])
{
	#pragma unused data
	
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
		printf("ID_VEHICLE_SYNC:AC_DRIVER_TELEPORT [distance: %0.2f speed: %i z: %0.2f]", 
			distance,
			speed,
			ac_player_data[playerid][ac_pos_z]
		);
	#endif
	
	if (floatcmp(ac_player_data[playerid][ac_pos_z], -95.0) == 1)
	{
		if(floatcmp(distance, 25.0) == 1
		&& floatcmp(speed, 20) == -1)
		{
			if (!AntiCheatDetect(playerid, AC_DRIVER_TELEPORT))
			{
				AntiCheatDebug(playerid, 
					AC_DRIVER_TELEPORT, 
					"[01] PLAYERID", 
					float(playerid),
					"DISTANCE", 
					distance,
					"SPEED",
					float(speed)
				);
				
				return 0;
			}
		}
		else if (floatcmp(distance, 40.0) == 1
		&& floatcmp(speed, 20) == 1)
		{
			if (!AntiCheatDetect(playerid, AC_DRIVER_TELEPORT))
			{
				AntiCheatDebug(playerid, 
					AC_DRIVER_TELEPORT, 
					"[02] PLAYERID", 
					float(playerid),
					"DISTANCE", 
					distance,
					"SPEED",
					float(speed)
				);
				
				return 0;
			}
		}
	}
	
	return 1;
}