/*!
	@brief Античит: Onfoot Rvanka
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_PLAYER_SYNC:AC_ONFOOT_RVANKA(playerid, data[PR_OnFootSync])
{
	new Float: velocity = floatadd(
		floatadd(floatabs(data[PR_velocity][0]), floatabs(data[PR_velocity][1])), 
		floatabs(data[PR_velocity][2])
	);
	
	if (floatcmp(velocity, 2.8) == 1)
	{
		if (!AntiCheatDetect(playerid, AC_ONFOOT_RVANKA))
		{
			AntiCheatDebug(playerid, AC_ONFOOT_RVANKA, "PLAYERID", float(playerid), "VELOCITY", velocity);
			return 0;
		}
	}
	
	return 1;
}