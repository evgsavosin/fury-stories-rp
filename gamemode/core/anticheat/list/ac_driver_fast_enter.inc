/*!
	@brief Античит: Driver Fast Enter
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_VEHICLE_SYNC:AC_DRIVER_FAST_ENTER(playerid, data[PR_InCarSync])
{
	if (!CheckAntiCheatTimeout(playerid, AC_DRIVER_FAST_ENTER))
	{
		return 1;
	}
	
	return (!CheckAntiCheatVehicleFastEnter(playerid, data[PR_vehicleId], 0) ? AntiCheatDetect(playerid, AC_DRIVER_FAST_ENTER) : 1);
}