/*!
	@brief Античит: Onfoot Teleport
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_PLAYER_SYNC:AC_ONFOOT_TELEPORT(playerid, data[PR_OnFootSync])
{
	if (!CheckAntiCheatTimeout(playerid, AC_ONFOOT_TELEPORT))
	{
		return 1;
	}
	
	new is_not_cheat = true;
	
	// NOP SetPlayerPos
	if (ac_player_data[playerid][ac_is_set_pos])
	{
		new bool: is_position_valid = false,
			index;
		
		for (new i = AC_POSITION_COUNT - 1; i >= 0; i--)
		{
			if (ac_player_pos[playerid][i][0] != 0.0 
			&& ac_player_pos[playerid][i][1] != 0.0 
			&& IsPlayerInRangeOfPoint(playerid, 200.0, ac_player_pos[playerid][i][0], ac_player_pos[playerid][i][1], ac_player_pos[playerid][i][2]))
			{
				is_position_valid = true;
				index = i;
				break;
			}
		}
		
		if (!is_position_valid)
		{
			new Float: distance = GetDistanceBetweenPoints( 
				data[PR_position][0],
				data[PR_position][1],
				data[PR_position][2],
				ac_player_pos[playerid][index][0], 
				ac_player_pos[playerid][index][1], 
				ac_player_pos[playerid][index][2]
			);
			
			is_not_cheat = AntiCheatDetect(playerid, AC_ONFOOT_TELEPORT);
			
			if (!is_not_cheat)
			{
				AntiCheatDebug(playerid, 
					AC_ONFOOT_TELEPORT, 
					"[01]PLAYERID", 
					float(playerid),
					"DISTANCE", 
					distance
				);
			}
		}
		
		if (is_not_cheat && is_position_valid)
		{
			ac_player_data[playerid][ac_is_moved] = true;
			ac_player_data[playerid][ac_is_set_pos] = false;
		}
	}
	else 
	{
		if (ac_player_data[playerid][ac_is_moved])
		{	
			ac_player_data[playerid][ac_is_moved] = false;

			for (new i = AC_POSITION_COUNT - 1, Float: distance; i >= 0; i--)
			{
				distance = GetDistanceBetweenPoints(
					data[PR_position][0], 
					data[PR_position][1], 
					data[PR_position][2], 
					ac_player_pos[playerid][i][0], 
					ac_player_pos[playerid][i][1], 
					ac_player_pos[playerid][i][2]
				);
				
				if (ac_player_pos[playerid][i][0] != 0.0 
				&& ac_player_pos[playerid][i][1] != 0.0 
				&& floatcmp(distance, 50.000) != 1)
				{	
					ac_player_data[playerid][ac_is_moved] = true;
					break;
				}
			}
		}
		
		if (!ac_player_data[playerid][ac_is_moved])
		{
			if (ac_player_data[playerid][ac_dump_pos_count] != INVALID_PARAM)
			{
				for (new i = AC_POSITION_COUNT - 1; i >= 0; i--)
				{
					ac_player_pos[playerid][i][0] =
					ac_player_pos[playerid][i][1] =
					ac_player_pos[playerid][i][2] = 0.0;
				}
				
				ac_player_data[playerid][ac_dump_pos_count] = INVALID_PARAM;
			}
			
			new Float: distance = GetDistanceBetweenPoints( 
				data[PR_position][0],
				data[PR_position][1],
				data[PR_position][2],
				ac_player_data[playerid][ac_pos_x], 
				ac_player_data[playerid][ac_pos_y], 
				ac_player_data[playerid][ac_pos_z]
			);
			
			#if __AC_DEBUG >= __AC_REPORTING_ALL
				printf("ID_PLAYER_SYNC:AC_ONFOOT_TELEPORT [%i %i %i %0.2f %i %i]", 
					floatcmp(ac_player_data[playerid][ac_pos_z], -95.0),
					floatcmp(data[PR_position][2], -95.0),
					(floatcmp(distance, 30.0) == 1),
					distance,
					data[PR_surfingVehicleId],
					data[PR_specialAction]
				);
			#endif
	
			if (floatcmp(ac_player_data[playerid][ac_pos_z], -95.0) == 1
			&& floatcmp(data[PR_position][2], -95.0) == 1
			&& floatcmp(distance, 30.0) == 1
			&& (data[PR_surfingVehicleId] == 0 || data[PR_surfingVehicleId] == INVALID_VEHICLE_ID)
			&& data[PR_specialAction] != SPECIAL_ACTION_ENTER_VEHICLE)
			{
				is_not_cheat = AntiCheatDetect(playerid, AC_ONFOOT_TELEPORT);
				
				if (!is_not_cheat)
				{
					AntiCheatDebug(playerid, 
						AC_ONFOOT_TELEPORT, 
						"[02]PLAYERID", 
						float(playerid),
						"DISTANCE", 
						distance
					);
				}
			}
		}
	}
	
	return _: is_not_cheat;
}