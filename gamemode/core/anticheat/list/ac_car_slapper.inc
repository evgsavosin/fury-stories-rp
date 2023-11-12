/*!
	@brief Античит: Car Slapper
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_VEHICLE_SYNC:AC_CAR_SLAPPER(playerid, data[PR_InCarSync])
{
	if (floatcmp(data[PR_velocity][2], 3.50) == 1)
	{
		if (!AntiCheatDetect(playerid, AC_CAR_SLAPPER))
		{
			return 0;
		}
	}
	
	return 1;
}