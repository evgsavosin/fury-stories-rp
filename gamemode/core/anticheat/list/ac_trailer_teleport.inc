/*!
	@brief Античит: Trailer teleport
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_TRAILER_SYNC:AC_TRAILER_TELEPORT(playerid, data[PR_TrailerSync])
{
	new Float: distance = GetVehicleDistanceFromPoint(
		data[PR_trailerId], 
		data[PR_position][0], 
		data[PR_position][1], 
		data[PR_position][2]
	);
	
	if (ac_veh_data[data[PR_trailerId]][ac_attach_to_vehicleid] == INVALID_VEHICLE_ID 
	|| distance >= 70.0)
	{
		new Float: x,
			Float: y,
			Float: z,
			Float: angle;
			
		GetVehiclePos(data[PR_trailerId], x, y, z);
		GetVehicleZAngle(data[PR_trailerId], angle);
		SetVehicleZAngle(data[PR_trailerId], angle);
		SetVehiclePos(data[PR_trailerId], x, y, z);
		
		AntiCheatDetect(playerid, AC_TRAILER_TELEPORT);
		return 0;
	}
	
	return 1;
}