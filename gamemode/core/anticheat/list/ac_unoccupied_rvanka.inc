/*!
	@brief Античит: Unoccupied Rvanka
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_UNOCCUPIED_SYNC:AC_UNOCCUPIED_RVANKA(playerid, data[PR_UnoccupiedSync])
{
	if (data[PR_seatId] <= 0)
	{
		return 1;
	}
	
	new vehicleid = GetPlayerVehicleID(playerid);
	if (vehicleid != data[PR_vehicleId])
	{
		if (!AntiCheatDetect(playerid, AC_UNOCCUPIED_RVANKA))
		{
			AntiCheatDebug(playerid, AC_UNOCCUPIED_RVANKA, "PLAYERID", float(playerid), "VEHICLEID1", float(vehicleid), "VEHICLEID2", float(data[PR_vehicleId]));
			return 0;
		}
	}

	return 1;
}