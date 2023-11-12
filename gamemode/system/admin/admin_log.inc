/*!
	@brief Лог для системы администрирования
	@author Found (evg.savosin)
	@date 16.12.2016, update 08.03.2018
	
*/

AdminLog_OnGameModeInit()
{
	for (new i, Float: y = 250.0; i < MAX_ADMIN_LOG_LINES; i++)
	{
		y += 7.5; 
		
		alog_data[i][alog_textdraw] = TextDrawCreate(380.000, y, "_");   
		TextDrawLetterSize(alog_data[i][alog_textdraw], 0.159997, 0.905831);
		TextDrawTextSize(alog_data[i][alog_textdraw], 543.000000, -20.000000);
		TextDrawAlignment(alog_data[i][alog_textdraw], 1);
		TextDrawColor(alog_data[i][alog_textdraw], -1);
		TextDrawUseBox(alog_data[i][alog_textdraw], 1);
		TextDrawBoxColor(alog_data[i][alog_textdraw], 0);
		TextDrawSetShadow(alog_data[i][alog_textdraw], 0);
		TextDrawSetOutline(alog_data[i][alog_textdraw], 0);
		TextDrawBackgroundColor(alog_data[i][alog_textdraw], 255);
		TextDrawFont(alog_data[i][alog_textdraw], 1);
		TextDrawSetProportional(alog_data[i][alog_textdraw], 1);
		TextDrawSetShadow(alog_data[i][alog_textdraw], 0);
	}
	
	ClearAdminLog();
}

ClearAdminLog()
{
	for (new i; i < MAX_ADMIN_LOG_LINES; i++)
	{
		clean:<alog_data[i][alog_text]>;
		TextDrawSetString(alog_data[i][alog_textdraw], "_");
	}
}

SendAdminLog(text[])
{
	new bool: is_exists;
	
	for (new i; i < MAX_ADMIN_LOG_LINES; i++)
	{
		if (!isnull(alog_data[i][alog_text]))
		{
			continue;
		}
		
		clean:<alog_data[i][alog_text]>;
		strcat(alog_data[i][alog_text], text, MAX_ADMIN_LOG_LINE_LENGHT);
		TextDrawSetString(alog_data[i][alog_textdraw], alog_data[i][alog_text]);
		is_exists = true;
		break;
	}
	
	if (!is_exists)
	{
		for (new i; i < MAX_ADMIN_LOG_LINES; i++)
		{	
			clean:<alog_data[i][alog_text]>;
			
			if (i == (MAX_ADMIN_LOG_LINES - 1))
			{
				strcat(alog_data[i][alog_text], text, MAX_ADMIN_LOG_LINE_LENGHT);
			}
			else 
			{
				strcat(alog_data[i][alog_text], alog_data[i + 1][alog_text], MAX_ADMIN_LOG_LINE_LENGHT);
			}
			
			TextDrawSetString(alog_data[i][alog_textdraw], alog_data[i][alog_text]);
		}
	}
}

ShowAdminLog(playerid, bool: states)
{
	if (playerid != INVALID_PLAYER_ID)
	{
		if (states)
		{
			for (new i; i < MAX_ADMIN_LOG_LINES; i++)
			{
				TextDrawShowForPlayer(playerid, alog_data[i][alog_textdraw]);
			}
		}
		else 
		{
			for (new i; i < MAX_ADMIN_LOG_LINES; i++)
			{
				TextDrawHideForPlayer(playerid, alog_data[i][alog_textdraw]);
			}
		}
	}
	else 
	{
		foreach (new i : Player)
		{
			if (!IsPlayerLogged(i) || !CheckAdminAccess(i, ADMIN_TRAINEE))
			{
				continue;
			}
			
			if (states)
			{
				for (new j; j < MAX_ADMIN_LOG_LINES; j++)
				{
					TextDrawShowForPlayer(i, alog_data[j][alog_textdraw]);
				}
			}
			else 
			{
				for (new j; j < MAX_ADMIN_LOG_LINES; j++)
				{
					TextDrawHideForPlayer(i, alog_data[j][alog_textdraw]);
				}
			}
		}
	}
}

SetAdminLogForPlayer(playerid, reason, log_type, killerid = INVALID_PLAYER_ID)
{	
	if (log_type == a_deathlog)
	{
		if (isnull(admin_logs[0][alog_death][alog_user_name]))
		{
			clean:<admin_logs[0][alog_death][alog_user_name]>;
			strcat(admin_logs[0][alog_death][alog_user_name], GetUserName(playerid), MAX_PLAYER_NAME);
			
			clean:<admin_logs[0][alog_death][alog_character_name]>;
			strcat(admin_logs[0][alog_death][alog_character_name], GetCharacterRPName(playerid), MAX_PLAYER_NAME);
			
			admin_logs[0][alog_death][alog_reason] = reason;
			gettime(admin_logs[0][alog_death][alog_time_hour], admin_logs[0][alog_death][alog_time_minute], admin_logs[0][alog_death][alog_time_second]);
			
			clean:<admin_logs[0][alog_death][alog_killer_name]>;
			
			if (killerid != INVALID_PLAYER_ID)
			{
				strcat(admin_logs[0][alog_death][alog_killer_name], GetCharacterRPName(killerid), MAX_PLAYER_NAME);
			}
			
			return 1;
		}
	}
	else if (log_type == a_dislog)
	{
		if (isnull(admin_logs[0][alog_disconnect][alog_user_name]))
		{
			clean:<admin_logs[0][alog_disconnect][alog_user_name]>;
			strcat(admin_logs[0][alog_disconnect][alog_user_name], GetUserName(playerid), MAX_PLAYER_NAME);
			
			clean:<admin_logs[0][alog_disconnect][alog_character_name]>;
			strcat(admin_logs[0][alog_disconnect][alog_character_name], GetCharacterRPName(playerid), MAX_PLAYER_NAME);
			
			admin_logs[0][alog_disconnect][alog_reason] = reason;
			gettime(admin_logs[0][alog_disconnect][alog_time_hour], admin_logs[0][alog_disconnect][alog_time_minute], admin_logs[0][alog_disconnect][alog_time_second]);
			
			clean:<admin_logs[0][alog_disconnect][alog_killer_name]>;
			
			return 1;
		}
	}
	
	if (log_type == a_deathlog)
	{
		for (new i = MAX_ADMIN_LOGS - 1, end_i; i > INVALID_PARAM; i--)
		{
			if (end_i >= 1)
			{
				clean:<admin_logs[0][alog_death][alog_user_name]>;
				strcat(admin_logs[0][alog_death][alog_user_name], GetUserName(playerid), MAX_PLAYER_NAME);
				
				clean:<admin_logs[0][alog_death][alog_character_name]>;
				strcat(admin_logs[0][alog_death][alog_character_name], GetCharacterRPName(playerid), MAX_PLAYER_NAME);
				
				admin_logs[0][alog_death][alog_reason] = reason;
				gettime(admin_logs[0][alog_death][alog_time_hour], admin_logs[0][alog_death][alog_time_minute], admin_logs[0][alog_death][alog_time_second]);
				
				clean:<admin_logs[0][alog_death][alog_killer_name]>;
				
				if (killerid != INVALID_PLAYER_ID)
				{
					strcat(admin_logs[0][alog_death][alog_killer_name], GetCharacterRPName(killerid), MAX_PLAYER_NAME);
				}
				
				break;
			}
		
			if ((i - 2) > INVALID_PARAM)
			{
				if (isnull(admin_logs[i - 1][alog_death][alog_user_name]))
				{
					continue;
				}
				
				clean:<admin_logs[i][alog_death][alog_user_name]>;
				strcat(admin_logs[i][alog_death][alog_user_name], admin_logs[i - 1][alog_death][alog_user_name], MAX_PLAYER_NAME);
				
				clean:<admin_logs[i][alog_death][alog_character_name]>;
				strcat(admin_logs[i][alog_death][alog_character_name], admin_logs[i - 1][alog_death][alog_character_name], MAX_PLAYER_NAME);
				
				clean:<admin_logs[i][alog_death][alog_killer_name]>;
				strcat(admin_logs[i][alog_death][alog_killer_name], admin_logs[i - 1][alog_death][alog_killer_name], MAX_PLAYER_NAME);
				
				admin_logs[i][alog_death][alog_reason] = admin_logs[i - 1][alog_death][alog_reason];
				admin_logs[i][alog_death][alog_time_hour] = admin_logs[i - 1][alog_death][alog_time_hour];
				admin_logs[i][alog_death][alog_time_minute] = admin_logs[i - 1][alog_death][alog_time_minute];
				admin_logs[i][alog_death][alog_time_second] = admin_logs[i - 1][alog_death][alog_time_second];
				
				continue;
			}
			
			clean:<admin_logs[i][alog_death][alog_user_name]>;
			strcat(admin_logs[i][alog_death][alog_user_name], admin_logs[i - 1][alog_death][alog_user_name], MAX_PLAYER_NAME);
			
			clean:<admin_logs[i][alog_death][alog_character_name]>;
			strcat(admin_logs[i][alog_death][alog_character_name], admin_logs[i - 1][alog_death][alog_character_name], MAX_PLAYER_NAME);
			
			clean:<admin_logs[i][alog_death][alog_killer_name]>;
			strcat(admin_logs[i][alog_death][alog_killer_name], admin_logs[i - 1][alog_death][alog_killer_name], MAX_PLAYER_NAME);
			
			admin_logs[i][alog_death][alog_reason] = admin_logs[i - 1][alog_death][alog_reason];
			admin_logs[i][alog_death][alog_time_hour] = admin_logs[i - 1][alog_death][alog_time_hour];
			admin_logs[i][alog_death][alog_time_minute] = admin_logs[i - 1][alog_death][alog_time_minute];
			admin_logs[i][alog_death][alog_time_second] = admin_logs[i - 1][alog_death][alog_time_second];
			
			end_i++;
		}
	}
	else if (log_type == a_dislog)
	{
		for (new i = MAX_ADMIN_LOGS - 1, end_i; i > INVALID_PARAM; i--)
		{
			if (end_i >= 1)
			{
				clean:<admin_logs[0][alog_disconnect][alog_user_name]>;
				strcat(admin_logs[0][alog_disconnect][alog_user_name], GetUserName(playerid), MAX_PLAYER_NAME);
				
				clean:<admin_logs[0][alog_disconnect][alog_character_name]>;
				strcat(admin_logs[0][alog_disconnect][alog_character_name], GetCharacterRPName(playerid), MAX_PLAYER_NAME);
				
				admin_logs[0][alog_disconnect][alog_reason] = reason;
				gettime(admin_logs[0][alog_disconnect][alog_time_hour], admin_logs[0][alog_disconnect][alog_time_minute], admin_logs[0][alog_disconnect][alog_time_second]);
				
				clean:<admin_logs[0][alog_disconnect][alog_killer_name]>;
				
				break;
			}
		
			if ((i - 2) > INVALID_PARAM)
			{
				if (isnull(admin_logs[i - 1][alog_disconnect][alog_user_name]))
				{
					continue;
				}
				
				clean:<admin_logs[i][alog_disconnect][alog_user_name]>;
				strcat(admin_logs[i][alog_disconnect][alog_user_name], admin_logs[i - 1][alog_disconnect][alog_user_name], MAX_PLAYER_NAME);
				
				clean:<admin_logs[i][alog_disconnect][alog_character_name]>;
				strcat(admin_logs[i][alog_disconnect][alog_character_name], admin_logs[i - 1][alog_disconnect][alog_character_name], MAX_PLAYER_NAME);
				
				clean:<admin_logs[i][alog_disconnect][alog_killer_name]>;
				
				admin_logs[i][alog_disconnect][alog_reason] = admin_logs[i - 1][alog_disconnect][alog_reason];
				admin_logs[i][alog_disconnect][alog_time_hour] = admin_logs[i - 1][alog_disconnect][alog_time_hour];
				admin_logs[i][alog_disconnect][alog_time_minute] = admin_logs[i - 1][alog_disconnect][alog_time_minute];
				admin_logs[i][alog_disconnect][alog_time_second] = admin_logs[i - 1][alog_disconnect][alog_time_second];
				
				continue;
			}
			
			clean:<admin_logs[i][alog_disconnect][alog_user_name]>;
			strcat(admin_logs[i][alog_disconnect][alog_user_name], admin_logs[i - 1][alog_disconnect][alog_user_name], MAX_PLAYER_NAME);
			
			clean:<admin_logs[i][alog_disconnect][alog_character_name]>;
			strcat(admin_logs[i][alog_disconnect][alog_character_name], admin_logs[i - 1][alog_disconnect][alog_character_name], MAX_PLAYER_NAME);
			
			clean:<admin_logs[i][alog_disconnect][alog_killer_name]>;
			
			admin_logs[i][alog_disconnect][alog_reason] = admin_logs[i - 1][alog_disconnect][alog_reason];
			admin_logs[i][alog_disconnect][alog_time_hour] = admin_logs[i - 1][alog_disconnect][alog_time_hour];
			admin_logs[i][alog_disconnect][alog_time_minute] = admin_logs[i - 1][alog_disconnect][alog_time_minute];
			admin_logs[i][alog_disconnect][alog_time_second] = admin_logs[i - 1][alog_disconnect][alog_time_second];
			
			end_i++;
		}
	}

	return 1;
}