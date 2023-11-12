/*!
	@brief Античит: Passenger Enter
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_PASSENGER_SYNC:AC_PASSENGER_ENTER(playerid, data[PR_PassengerSync])
{
	return (!CheckAntiCheatVehicleEnter(playerid, data[PR_vehicleId]) ? AntiCheatDetect(playerid, AC_PASSENGER_ENTER) : 1);
}