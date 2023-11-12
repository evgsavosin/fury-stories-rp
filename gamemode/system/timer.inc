/*!
	@brief Файл с таймерами
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
*/

/*!
	Выполняет обновление 25 раз в секунду
	@param [in] playerid Игрок
*/

public OnPlayerUpdate(playerid)
{	
	if (user_login{playerid} && GetPVarInt(playerid,"Player:IsBot"))
	{
		return 0;
	}
	
	new tick = GetTickCount();
	
	player_afk[playerid] = 0;
	
	if (timer_second_tick < tick) // 400 ms
	{	
		if (player_speedometer[playerid] == INVALID_PARAM)
		{
			Timer:static_attach(playerid);
		}
		
		timer_second_tick = tick + 400;
	}
	
	if (player_speedometer[playerid] != INVALID_PARAM)
	{
		new vehicleid = GetPlayerVehicleID(playerid);
			
		if (vehicle_data[vehicleid][v_limit])
		{
			if (GetVehicleSpeed(vehicleid) >= 60.0)
			{
				SetVehicleSpeed(vehicleid, 59.0);
			}
		}
	}
	
	return 1;
}

/*!
	Выполняет обновление 1 раз в секунду
*/
function OnUpdateSecond()
{
	new player_state;
	
	// Загрузка игрового мода
	if (g_delay != 0)
	{	
		g_delay--;
		if (g_delay == 0)
		{
			format:g_small_string("hostname " #__PROJECT_NAME #__SERVER_NAME);
			SendRconCommand(g_small_string);
		}
	}
	
	foreach (new playerid : Player)
	{	
		Timer:anticheat(playerid);
		
        if (!IsPlayerLogged(playerid))
        {
            player_state = GetPlayerState(playerid);
            
            if (player_state != PLAYER_STATE_NONE && player_state != PLAYER_STATE_SPECTATING)
            {
                Kick(playerid);
            }
            
            continue;
        }
		
		player_afk[playerid]++;
		
		Timer:fraction_second(playerid);
		Timer:player_second(playerid);
		Timer:death(playerid);
		
		if (character_data[playerid][c_drugs_effect][drug_effect_minute_timer] != 0)
		{
			character_data[playerid][c_drugs_effect][drug_effect_second_timer] += 1;
		
			ShowPlayerDrugEffect(playerid, GetPVarInt(playerid, "Inventory:DrugSelect"));
		}
	}
	
	Timer:vehicle_second();
		
	return 1;
}


/*!
	Выполняет обновление 1 раз в минуту
*/
function OnUpdateMinute()
{	
	g_hour = 
	g_minute = 
	g_second = 0;
	
	gettime(g_hour, g_minute, g_second);
	
	if (g_hour == 3)
	{
		if (g_minute == 40)
		{
			SendSplitMessageToAll(C_LIGHTRED, !"Внимание! Плановый рестарт сервера произойдет через 20 минут.");
		}
		else if (g_minute == 55)
		{
			SendSplitMessageToAll(C_LIGHTRED, !"Плановый рестарт сервера произойдет через 5 минут.");
		}
	}
	
	if (g_minute == 0)
	{
		Timer:weather();
		Timer:house();
		Timer:premise();
		Timer:site_hour();
	}
	
	if ((g_hour % 12) == 0)
	{
		Timer:business();
	}
	
	Timer:textdraw_minute();
	Timer:corpse();
	Timer:phone();
	Timer:vehicle_minute();
	
	foreach (new playerid : Player)
	{
		if (!IsPlayerLogged(playerid))
		{
			continue;
		}
		
		Timer:player_minute(playerid);
		
		if (character_data[playerid][c_drugs_effect][drug_effect_minute_timer] != 0)
		{
			character_data[playerid][c_drugs_effect][drug_effect_minute_timer] -= 1;
			continue;
		}

		Timer:weather(playerid);
		Timer:fraction_minute(playerid);
	}
	
	return 1;
}