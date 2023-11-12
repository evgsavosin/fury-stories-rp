/*!
	@brief Античит: Invisible surf
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_PLAYER_SYNC:AC_INVISIBLE_SURF(playerid, data[PR_OnFootSync])
{
	new objectid = data[PR_surfingVehicleId],
		bool: is_cheat = false;
	
	if (objectid != 0 && objectid != INVALID_OBJECT_ID && objectid != INVALID_VEHICLE_ID)
	{
		if ((floatabs(data[PR_surfingOffsets][0]) >= 10.0) ||
			(floatabs(data[PR_surfingOffsets][1]) >= 10.0) ||
			(floatabs(data[PR_surfingOffsets][2]) >= 10.0)
		) {
			AntiCheatDebug(playerid, AC_INVISIBLE_SURF, "PLAYERID", float(playerid), "OBJECTID", float(objectid));
			return 0; // ignore bad packet
		} 
	}
	
	if (is_cheat)
	{
		return AntiCheatDetect(playerid, AC_INVISIBLE_SURF);
	}
	
	return 1;
}