/*!
	@brief Таймер
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

Timer:fraction_second(playerid)
{
	new follow = GetPVarInt(playerid, "Player:Follow"),
		cuff = GetPVarInt(playerid, "Player:Cuff");
		
	if (follow != INVALID_PLAYER_ID && cuff != 0) 
	{
		if (!IsPlayerInAnyVehicle(follow)) 
		{
			if (!IsPlayerInAnyVehicle(playerid)) 
			{
				if (GetDistanceBetweenPlayers(playerid, follow) < 1.5) 
				{
					ClearAnimations(playerid);
				}
				else if (GetDistanceBetweenPlayers(playerid, follow) > 1.0 && GetDistanceBetweenPlayers(playerid, follow) < 10.0) 
				{
					SetPlayerFacePlayer(playerid, follow);
					ApplyAnimation(playerid, "ped", "WALK_civi", 6.0, 1, 1, 1, 1, 0, 1);
				}
				else if (GetDistanceBetweenPlayers(playerid, follow) > 10.0) 
				{
					SendClientMessage(follow, C_WHITE, !#DEFAULT " Вы отошли слишком далеко от персонажа, которго Вы ведёте." );
					
					SetPVarInt(follow, "Player:Lead", INVALID_PLAYER_ID );
					SetPVarInt(playerid, "Player:Follow", INVALID_PLAYER_ID );
					
					TogglePlayerControllable(playerid, false);
				}
			}
			else 
			{
				SetPVarInt(follow, "Player:Lead", INVALID_PLAYER_ID);
				SetPVarInt(playerid, "Player:Follow", INVALID_PLAYER_ID);
			}
		}
		else 
		{
			SetPVarInt(follow, "Player:Lead", INVALID_PLAYER_ID);
			SetPVarInt(playerid, "Player:Follow", INVALID_PLAYER_ID);
		}
	}
	
	// Тазер
	if (GetPVarInt(playerid, "Player:Stunned") > 0) 
	{
		TakePVarInt(playerid, "Player:Stunned", 1);
		
		if (GetPlayerAnimationIndex(playerid) != 388)
		{
			ApplyAnimation(playerid, "CRACK", "crckdeth4", 4.0, 0, 0, 0, 1, 0, 1);
		}
		
		if (!GetPVarInt(playerid, "Player:Stunned"))
		{
			TogglePlayerControllable(playerid, true);
		}
	}
}

Timer:fraction_minute(playerid)
{
	if (IsCharacterArrested(playerid) && character_data[playerid][c_arrest_time] < gettime())
	{
		if (GetCharacterRole(playerid) == ROLE_CONVICTED 
		&& character_data[playerid][c_arrest_type] == TYPE_ARREST_JAIL)
		{
			return;
		}
		
		ResetPlayerArrest(playerid);
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Ваш срок заключения подошёл к концу и Вы были освобождены.");
	}
}