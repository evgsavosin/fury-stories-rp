/*!
	@brief Античит: Onfoot Fly
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_PLAYER_SYNC:AC_ONFOOT_FLYHACK(playerid, data[PR_OnFootSync])
{
	if(data[PR_weaponId] != WEAPON_PARACHUTE
	&& data[PR_specialAction] != SPECIAL_ACTION_ENTER_VEHICLE
	&& data[PR_surfingVehicleId] == 0
	&& GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_ENTER_VEHICLE 
	&& GetPlayerSurfingVehicleID(playerid) == INVALID_VEHICLE_ID 
	&& GetPlayerSurfingObjectID(playerid) == INVALID_OBJECT_ID)
	{
		if ((floatcmp(floatabs(data[PR_quaternion][1]), 0.0) == 1 
		|| floatcmp(floatabs(data[PR_quaternion][2]), 0.0) == 1)) 
		{
			return AntiCheatDetect(playerid, AC_ONFOOT_FLYHACK);
		}
	}
	
	return 1;
}