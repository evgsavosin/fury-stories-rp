/*!
	@brief Античит: Action - (SetPlayerAction)
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_PLAYER_SYNC:AC_SPECIAL_ACTION(playerid, data[PR_OnFootSync])
{
	if (data[PR_specialAction] == SPECIAL_ACTION_USEJETPACK)
	{
		if (!AntiCheatDetect(playerid, AC_SPECIAL_ACTION))
		{
			AntiCheatDebug(playerid, AC_SPECIAL_ACTION, "PLAYERID", float(playerid), "ACTION", float(data[PR_specialAction]));
			return 0;
		}
	}
	
	return 1;
}