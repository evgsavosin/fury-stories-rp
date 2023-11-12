/*!
	@brief Античит: Driver Enter
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_VEHICLE_SYNC:AC_DRIVER_ENTER(playerid, data[PR_InCarSync])
{
	return (!CheckAntiCheatVehicleEnter(playerid, data[PR_vehicleId]) ? AntiCheatDetect(playerid, AC_DRIVER_ENTER) : 1);
}