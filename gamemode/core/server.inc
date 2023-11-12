/*!
	@brief Серверные настройки
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
*/

Server_OnGameModeInit()
{
	print("[Server_OnGameModeInit]: " __VERSION " started...");
	
	DisableInteriorEnterExits();
 	EnableStuntBonusForAll(0);
 	ShowPlayerMarkers(1);
 	SetNameTagDrawDistance(30.0);
    ManualVehicleEngineAndLights();
	LimitGlobalChatRadius(13.0);
	LimitPlayerMarkerRadius(12.0);
	
	SendRconCommand("hostname " #__PROJECT_NAME #__SERVER_NAME" (RESTART)");
	SetGameModeText(__VERSION);
	
	SetTimer("OnUpdateSecond", 1000, true);
    SetTimer("OnUpdateMinute", 60000, true);
	
	Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, MAX_VISIBLE_OBJECTS);
	
	gettime(g_hour, g_minute, g_second);
	return 1;
}

#if defined __DEBUG
	public OnRuntimeError(code, &bool: suppress)
	{
		clean:<g_big_string>;
		clean:<g_small_string>;

		new pos_start,
			pos_end,
			playerid = INVALID_PLAYER_ID,
			vehicleid = INVALID_VEHICLE_ID;

		GetAmxBacktrace(g_big_string);

		pos_start = strfind(g_big_string, "playerid=", true);

		if(pos_start == -1)
		{
			pos_start = strfind(g_big_string, "vehicleid=", true) + 10; // (10) strlen("vehicleid=")

			if(pos_start == -1) return 1;

			pos_end = strfind(g_big_string, ",", true, pos_start);
			if(pos_end == -1) strfind(g_big_string, ")", true, pos_start);

			strmid(g_small_string, g_big_string, pos_start, pos_end);

			vehicleid = strval(g_small_string);

			if(vehicleid != INVALID_VEHICLE_ID && vehicleid < 2001 && vehicleid > 0)
			{
				foreach(new id : Player)
				{
					if(IsPlayerInVehicle(id, vehicleid))
					{
						playerid = id;
						break;
				   }
			   }
		   }
	   }
		else
		{
			pos_start += 9; // (9) strlen("playerid=")
			pos_end = strfind(g_big_string, ",", true, pos_start);
			if(pos_end == -1) strfind(g_big_string, ")", true, pos_start);
			strmid(g_small_string, g_big_string, pos_start, pos_end);

			playerid = strval(g_small_string);
	   }

		pos_end = 0;

		for(new i; i < 10; i++)
		{
			pos_start = strfind(g_big_string, ":\\", true, pos_end );

			if(pos_start == -1) break;
			pos_start--; // удалим букву диска

			pos_end = strfind(g_big_string, "gamemodes", true, pos_start);

			if(pos_end == -1) 
			{
				pos_end = strfind(g_big_string, "include", true, pos_start);
				if(pos_end == -1) break;

				pos_end += 7; // (7) strlen("include")
		   }
			else
			{
				pos_end += 9; // (9) strlen("gamemodes")
		   }

			if(strdel(g_big_string, pos_start, pos_end) == false) break;
	   }

		if(playerid == INVALID_PLAYER_ID || playerid > MAX_PLAYERS || playerid < 0) 
		{
			return 1;
		}
		
		ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "Код ошибки", g_big_string, "Закрыть", "" );

		SendClientMessage(playerid, -1, " ");
		SendClientMessage(playerid, C_LIGHTRED, "Произошла критическая ошибка в игровом моде.");
		SendClientMessage(playerid, C_LIGHTRED, "Сделайте скриншот с кодом ошибки (F8), а после напишите в наш баг-трекер.");
		SendClientMessage(playerid, C_LIGHTRED, "В избежании быть отсоединённым от сервера мы рекомендуем не повторять подобное действие.");
		return 1;
	}
#endif