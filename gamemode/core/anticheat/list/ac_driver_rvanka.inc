/*!
	@brief Античит: Driver Rvanka
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_VEHICLE_SYNC:AC_DRIVER_RVANKA(playerid, data[PR_InCarSync])
{
	new Float: velocity = floatadd(
		floatadd(floatabs(data[PR_velocity][0]), floatabs(data[PR_velocity][1])), 
		floatabs(data[PR_velocity][2])
	);

	if (floatcmp(velocity, 3.5) == 1)
	{
		if (!AntiCheatDetect(playerid, AC_DRIVER_RVANKA))
		{
			AntiCheatDebug(playerid, AC_DRIVER_RVANKA, "PLAYERID", float(playerid), "VELOCITY", velocity);
			return 0;
		}
	}
	
	return 1;
}