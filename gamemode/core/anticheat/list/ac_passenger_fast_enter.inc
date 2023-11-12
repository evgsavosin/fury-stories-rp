/*!
	@brief Античит: Passenger Fast Enter
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_PASSENGER_SYNC:AC_PASSENGER_FAST_ENTER(playerid, data[PR_PassengerSync])
{
	if (!CheckAntiCheatTimeout(playerid, AC_PASSENGER_FAST_ENTER))
	{
		return 1;
	}
	
	return (!CheckAntiCheatVehicleFastEnter(playerid, data[PR_vehicleId], data[PR_seatId]) ? AntiCheatDetect(playerid, AC_PASSENGER_FAST_ENTER) : 1);
}