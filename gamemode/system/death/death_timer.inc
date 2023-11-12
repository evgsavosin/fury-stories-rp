/*!
	@brief Таймер для системы смерти
	@author Found (evg.savosin)
	@date 26.04.2017
*/

Timer:death(playerid)
{
	new death,
		player_state = GetPlayerState(playerid);
	
	if ((death = GetCharacterDeath(playerid)) == TYPE_DEATH_NONE)
	{
		return;
	}
	
	if (player_state == PLAYER_STATE_DRIVER || player_state == PLAYER_STATE_PASSENGER)
	{
		RemovePlayerFromVehicle(playerid);
	}
	
	if (!IsPlayerInRangeOfPoint(playerid, 5.0,
	character_data[playerid][c_pos][0], 
	character_data[playerid][c_pos][1], 
	character_data[playerid][c_pos][2]))
	{
		SetPlayerPos(
			playerid, 
			character_data[playerid][c_pos][0], 
			character_data[playerid][c_pos][1], 
			character_data[playerid][c_pos][2]
		);
	}
	
	if (death == TYPE_DEATH_INJURED)
	{
		if (GetPlayerAnimationIndex(playerid) != 1701)
		{
			ApplyDeathAnimation(playerid, death);
		}
	}	
	else if (death == TYPE_DEATH_DIED)
	{
		if (GetPlayerAnimationIndex(playerid) != 1151)
		{
			ApplyDeathAnimation(playerid, death);
		}
		
		if (death_data[playerid][d_timer] > 0)
		{			
			death_data[playerid][d_timer]--;
			
			format:g_small_string("%i", death_data[playerid][d_timer]);
			GameTextForPlayer(playerid, g_small_string, 2000, 4);
			
			if (GetCharacterHealth(playerid) < 100.0)
			{
				SetPlayerHealth(playerid, 100.0);
			}
			
			if (death_data[playerid][d_timer] == 0)
			{
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Для того, чтобы принять " #cPROJECT "«PK»" #cWHITE ", используйте " #cPROJECT "/pk" #cWHITE ".");
			}
		}
	}
}