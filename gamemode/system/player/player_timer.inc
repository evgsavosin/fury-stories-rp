/*!
	@brief Таймер для системы аккаунта и персонажа
	@author Found (evg.savosin)
	@date 26.04.2017
*/

Timer:player_second(playerid)
{
	if (!IsCharacterLoaded(playerid))
	{
		return;
	}
	
	if (GetPlayerMoney(playerid) != character_data[playerid][c_money])
	{
		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, character_data[playerid][c_money]);
	}
	
	new Float: health,
		Float: armour;
	
	GetPlayerHealth(playerid, health);

	if (floatcmp(character_data[playerid][c_health], health) == 1)
	{
		SetPlayerHealth(playerid, character_data[playerid][c_health]);
	}
	else 
	{
		character_data[playerid][c_health] = health;
		SetPlayerHealth(playerid, health);
	}
	
	GetPlayerArmour(playerid, armour);
	
	if (floatcmp(0.0, armour) == 1)
	{
		SetPlayerArmour(playerid, 0.0);
	}
}

Timer:player_minute(playerid)
{		
	new unix_time = gettime();
	Timer:player_premise(playerid);
	
    if (++character_data[playerid][c_payday] >= MAX_PAYDAY)
    {
        CallLocalFunction("OnPlayerPayDay", "d", playerid);
        character_data[playerid][c_payday] = 0;
        Update:character_int(playerid, "c_payday", 0);
    }

	
	if (GetPVarInt(playerid, "Player:AttackNameTime") != 0 
	&& GetPVarInt(playerid, "Player:AttackNameTime") <= (unix_time - (60 * 30)))
	{
		character_data[playerid][c_attack_name_fist][0] = 
		character_data[playerid][c_attack_name_cold][0] = EOS;
		DeletePVar(playerid, "Player:AttackNameTime");
	}
	
	if (IsPlayerMuted(playerid) && user_data[playerid][u_mute] < unix_time)
	{
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " OOC блокировка чата окончилась, Вы снова можете пользоваться чатом.");
		
		user_data[playerid][u_mute] = 0;
		Update:user_int(playerid, "u_mute", 0);
		
		SendClientMessage(playerid, C_WHITE, !HELP_PUNISHMENT);
	}
}