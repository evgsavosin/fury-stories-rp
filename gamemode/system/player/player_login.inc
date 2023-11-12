/*!
	@brief Авторизация на основе UCP - (User Control Panel)
	@date 16.12.2016, update 28.02.2018
*/

/**
    Variables
*/

static player_relogin  [MAX_PLAYERS char];

/**
    Data manipulation function
*/

stock HasPlayerRelogin(playerid)
{
    return player_relogin{playerid};
}

stock SetPlayerRelogin(playerid, bool: value)
{
    player_relogin{playerid} = value;
}

/**
    Public function
*/

function OnPlayerDataReset(playerid, bool: is_relogin)
{
    if (is_relogin)
    {
        return 1;
    }

    // Reset relogin status
    SetPlayerRelogin(playerid, false);

	#if defined PlayerLogin_OnPlayerDataReset
		return PlayerLogin_OnPlayerDataReset(playerid, is_relogin);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDataReset
    #undef OnPlayerDataReset
#else
    #define _ALS_OnPlayerDataReset
#endif

#define	OnPlayerDataReset	PlayerLogin_OnPlayerDataReset
#if defined PlayerLogin_OnPlayerDataReset
	forward PlayerLogin_OnPlayerDataReset(playerid, bool: is_relogin);
#endif


function OnPlayerAfterSpawn(playerid)
{
    // Reset relogin status
    if (HasPlayerRelogin(playerid))
    {
        pformat:(SUCCESS " Вы успешно перезашли за персонажа - " #cPROJECT "%s" #cWHITE ".",
            GetPlayerCurrentName(playerid)
        );

        psend:(playerid, C_WHITE);

        SetPlayerRelogin(playerid, false);
    }

	#if defined PlayerLogin_OnPlayerAfterSpawn
		return PlayerLogin_OnPlayerAfterSpawn(playerid);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerAfterSpawn
    #undef OnPlayerAfterSpawn
#else
    #define _ALS_OnPlayerAfterSpawn
#endif

#define	OnPlayerAfterSpawn	PlayerLogin_OnPlayerAfterSpawn
#if defined PlayerLogin_OnPlayerAfterSpawn
	forward PlayerLogin_OnPlayerAfterSpawn(playerid);
#endif


public OnPlayerConnect(playerid)
{	
	if (g_delay != 0)
	{
		SendClientMessage(playerid, C_LIGHTRED, "Сервер загружается, подождите...");
		Kick(playerid);
		return 1;
	}
	
	GetPlayerIp(playerid, user_data[playerid][u_ip], 18);
	
	SetPlayerScore(playerid, 0);
	SetPlayerColor(playerid, 0xFFFFFF00);
	SetPlayerVirtualWorld(playerid, 2147483646);
	
	format:g_string("SELECT COUNT(ib_user_ip) AS ipbans_count FROM `" #__IPBANS "` WHERE `ib_user_ip` = '%q' LIMIT 1",
		GetUserIp(playerid)
	);
	
	mysql_tquery(db, g_string, "OnPlayerCheckBanIp", "i", playerid);
	
	#if defined Login_OnPlayerConnect
		return Login_OnPlayerConnect(playerid);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define	OnPlayerConnect	Login_OnPlayerConnect
#if defined Login_OnPlayerConnect
	forward Login_OnPlayerConnect(playerid);
#endif


function OnPlayerCheckBanIp(playerid)
{
	new count;
	
	cache_get_value_name_int(0, "ipbans_count", count);
	
	if (count == 0)
	{
		return 1;
	}
	
	SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете присоединиться к серверу, так как были заблокированы.");
	Kick(playerid);
	return 1;
}

Player_OnPlayerRequestClass(playerid, classid) 
{
	#pragma unused classid
	
	if (!IsUserAllowQuery(playerid))
	{
		return 1;
	}
	
	if (IsPlayerNPC(playerid)) 
	{
		return 1;
	}
	
   	if (IsPlayerLogged(playerid))
	{
		new Float: x,
			Float: y,
			Float: z,
			Float: angle;
			
		GetSpawnInfo(playerid, x, y, z, angle);
		TogglePlayerSpectating(playerid, true); 
		SetSpawnInfo(playerid, 264, character_data[playerid][c_skin], x, y, z, angle, 0, 0, 0, 0, 0, 0);
		TogglePlayerSpectating(playerid, false); 
		return 1;
	}
	
    InitPlayerLoginCamera(playerid);
	GetPlayerName(playerid, player_temp_name[playerid], MAX_PLAYER_NAME);
	
	format:g_string("\
		SELECT \
			u.u_id, u.u_name, u.u_online, u.u_status - 1 AS u_status_int, u.u_last_ip \
		FROM \
			" #__USERS " u \
		LEFT JOIN " #__CHARACTERS " c ON c.c_user_id = u.u_id \
		WHERE \
			(u.u_name = '%q' OR c.c_name = '%q')", 
		player_temp_name[playerid],
		player_temp_name[playerid]
	);
	
	mysql_tquery(db, g_string, "OnUserCheck", "d", playerid);
	
	SetUserAllowQuery(playerid, false);
    return 1;
}

function OnUserCheck(playerid)
{	
	SetUserAllowQuery(playerid, true);

	new rows,
		online,
		status;
	
	cache_get_row_count(rows);
	
	if (rows == 0)
	{	
		ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", DIALOG_REGISTER, "Закрыть", "");
		Kick(playerid);
		return 1;
	}
	
	cache_get_value_name_int(0, "u_online", online);
	cache_get_value_name_int(0, "u_status_int", status);
	
	if (status == USER_RETEST)
	{
		ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", DIALOG_RETEST, "Закрыть", "");
		Kick(playerid);
		return 1;
	}
	else if (status == USER_DISABLED)
	{
		ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", DIALOG_DISABLED, "Закрыть", "");
		Kick(playerid);
		return 1;
	}
	
	if (online)
	{
		ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", DIALOG_IS_ONLINE, "Закрыть", "");
		Kick(playerid);
		return 1;
	}
	
	cache_get_value_name_int(0, "u_id", user_data[playerid][u_id]);
	cache_get_value_name(0, "u_name", user_data[playerid][u_name], MAX_PLAYER_NAME);
	cache_get_value_name(0, "u_last_ip", user_data[playerid][u_last_ip], MAX_PLAYER_IP);
	
	ShowPlayerDialog(playerid, D_LOGIN, DIALOG_STYLE_PASSWORD, " ", DIALOG_LOGIN, "Далее", "Закрыть");

    return 1;
}


Load:check_player_login(playerid, const inputtext[] = "")
{
	format:g_string("AND u.u_password = " #__HASH_METHOD, inputtext);
	
	format:g_big_string("\
	SELECT \
		b.b_id, \
		b.b_reason, \
		b.b_admin_name, \
		IFNULL(UNIX_TIMESTAMP(b.b_ban_date), 0) AS b_ban_time, \
		IFNULL(UNIX_TIMESTAMP(b.b_before_date), 0) AS b_before_time, \
		IFNULL(b.b_id, 0) AS is_null_bans, \
		s.set_google_auth \
	FROM \
		" #__USERS " u \
	LEFT JOIN \
		" #__BANS " b ON b.b_account_id = u.u_id AND b.b_active = 1 AND b.b_type = %i \
	LEFT JOIN \
		" #__USETTINGS " s ON s.set_user_id = u.u_id \
	WHERE \
		u.u_id = %i %s",
		TYPE_BAN_USER,
		user_data[playerid][u_id],
		g_string
	);
		
	mysql_tquery(db, g_big_string, "OnPlayerLogin", "i", playerid);
}

function OnPlayerLogin(playerid)
{	
	new rows;
		
	cache_get_row_count(rows);
	
	if (!rows)
	{
		GivePVarInt(playerid, "Player:CountAttempts", 1);
		if (GetPVarInt(playerid, "Player:CountAttempts") == 3)
		{
			Kick(playerid);
			return 1;
		}
		
		format:g_string("%s\n\n" #cRED "Вы ввели неверный пароль от акаунта. (%i/3)", 
			DIALOG_LOGIN,
			GetPVarInt(playerid, "Player:CountAttempts")
		);
		
		ShowPlayerDialog(playerid, D_LOGIN, DIALOG_STYLE_PASSWORD, " ", g_string, "Далее", "Закрыть");
		return 1;
	}
	
	DeletePVar(playerid, "Player:CountAttempts");
	
	// Проверяем блокировку аккаунта
	if (CheckUserBan(playerid))
	{
		// Проверяем двухфакторную аутентификацию
		if (CheckUserGoogleAuth(playerid))
		{
			ShowPlayerDialog(playerid, D_LOGIN + 3, DIALOG_STYLE_INPUT, " ", DIALOG_GOOGLE_AUTH, "Далее", "Выйти");
			return 1;
		}
		
		ShowUserCharacterList(playerid);
	}
	
	return 1;
}

ShowUserCharacterList(playerid)
{
	new server_tick = GetTickCount();
	
	if (GetPVarInt(playerid, "Player:CheckCharacters") > server_tick)
	{
		ShowPlayerDialog(playerid, D_LOGIN + 4, DIALOG_STYLE_MSGBOX, " ",
			"" #ERROR " Подождите...\n\n\
			Подождите, не флудите.\n\
			Нажмите 'Далее', спустя 5 секунд.",
			"Далее", "Закрыть"
		);
		
		return;
	}
	
	format:g_big_string("\
		SELECT \
			c.c_id, \
			c.c_name, \
			c.c_status - 1 AS c_status, \
			c.c_death, \
			IFNULL(UNIX_TIMESTAMP(c.c_last_date), 0) AS c_last_time, \
			b.b_reason, \
			b.b_admin_name, \
			IFNULL(UNIX_TIMESTAMP(b.b_ban_date), 0) AS b_ban_time, \
			IFNULL(UNIX_TIMESTAMP(b.b_before_date), 0) AS b_before_time, \
			IFNULL(b.b_id, 0) AS is_null_bans \
		FROM \
			" #__CHARACTERS " c \
		LEFT JOIN \
			" #__BANS " b ON b.b_account_id = c.c_id AND b.b_active = 1 AND b.b_type = %i \
		WHERE \
			c_user_id = %i \
		LIMIT %i", 
		TYPE_BAN_CHARACTER,
		GetUserId(playerid),
		MAX_CHARACTERS
	);
	
	mysql_tquery(db, g_big_string, "OnUserCharacterListShow", "i", playerid);
	SetPVarInt(playerid, "Player:CheckCharacters", server_tick + 5000);
}

function OnUserCharacterListShow(playerid)
{
	new rows,
		ban_id,
		death,
		last_time,
		year,
		month,
		day,
		hour,
		minute;
	
	cache_get_row_count(rows);
	
	if (!rows)
	{
		ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ",
			"" #ERROR " Ошибка\n\n\
			У Вас отсутствуют игровые персонажи.\n\n\
			Для создания перейдите на сайт - " #cPROJECT "" #__PROJECT_SITE "" #cWHITE ".",
			"Закрыть", ""
		);
		
		Kick(playerid);
		return 1;
	}

	if (strcmp(player_temp_name[playerid], user_data[playerid][u_name]) != 0 
	&& SetPlayerName(playerid, user_data[playerid][u_name]) != 1)
	{	
		printf("[OnUserCharacterListShow]: Player (ID: %d) not logged and has been kicked. (%s, %s)",
			playerid,
            player_temp_name[playerid],
            user_data[playerid][u_name]
		);
		
		Kick(playerid);
		return 1;
	}
	
	Clear:character_select(playerid);

	clean:<g_big_string>;
	strcat(g_big_string, "" #cPROJECT "Имя\t" #cPROJECT "Состояние\t" #cPROJECT "Статус\t" #cPROJECT "Последний заход\n");
	for (new i; i < rows; i++)
	{
		if (i == MAX_CHARACTERS)
		{
			break;
		}
		
		cache_get_value_name(i, "c_name", character_select[playerid][i][cs_name], MAX_PLAYER_NAME);
		cache_get_value_name_int(i, "c_status", character_select[playerid][i][cs_status]);
		cache_get_value_name_int(i, "c_death", death);
		cache_get_value_name_int(i, "c_id", character_select[playerid][i][cs_id]);
		cache_get_value_name_int(i, "c_last_time", last_time);
		cache_get_value_name_int(i, "is_null_bans", ban_id);
		
		if (ban_id != 0)
		{
			cache_get_value_name_int(i, "b_before_time", character_select[playerid][i][cs_ban_before_date]);
			
			if (character_select[playerid][i][cs_ban_before_date] < gettime())
			{
				format:g_string("UPDATE " #__BANS " SET b_active = 0 WHERE b_id = %i LIMIT 1",
					ban_id
				);
				
				mysql_pquery(db, g_string);
				
				pformat:("" #SUCCESS " Срок блокировки у персонажа " #cPROJECT "%s" #cWHITE " истёк.",
					character_select[playerid][i][cs_name]
				);
				
				psend:(playerid, C_WHITE);
			}
			else 
			{
				character_select[playerid][i][cs_is_banned] = true;
				cache_get_value_name(i, "b_reason", character_select[playerid][i][cs_ban_reason], 64);
				cache_get_value_name(i, "b_admin_name", character_select[playerid][i][cs_ban_admin_name], MAX_PLAYER_NAME);
				cache_get_value_name_int(i, "b_ban_time", character_select[playerid][i][cs_ban_date]);
			}
		}
		
		gmtime(last_time, year, month, day, hour, minute);
		
		clean:<g_small_string>;
		if (last_time > 0)
		{
			format:g_small_string(DATE_FORMAT,
				hour, minute,
				day, month, year
			);
		}
		else 
		{
			strcat(g_small_string, #cGRAY "Отсутствует");
		}
		
		format:g_big_string("%s %s%s\t%s\t%s\t%s\n",
			g_big_string,
			character_select[playerid][i][cs_name],
			character_select[playerid][i][cs_is_banned] ? (" [" #cDARKRED "заблокирован " #cWHITE "]") : (""),
			character_status_info[character_select[playerid][i][cs_status]],
			(character_select[playerid][i][cs_status] == STATUS_CK) ? ("Мёртв") : ((!death) ? ("Жив") : ("Ранен")),
			g_small_string
		);
	}
	
	ShowPlayerDialog(playerid, D_LOGIN + 1, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "Выбрать", "Выйти");
	
	return 1;
}

function OnCharacterLoad(playerid)
{
	new rows;
	
	cache_get_row_count(rows);
	
	if (rows == 0)
	{
		printf("[OnCharacterLoad]: Player (ID: %d) not logged and has been kicked.",
			playerid
		);
		
		Kick(playerid);
		return 1;
	}
	
	// Load character data
	Load:character(playerid);

    OnPlayerBeforeSpawn(playerid);
	return 1;
}

ShowCharacterBanInformation(playerid, index)
{
	new year,
		month,
		day,
		hour,
		minute;
	
	gmtime(character_select[playerid][index][cs_ban_date], year, month, day, hour, minute);
				
	strcat(g_big_string, "" #ERROR " Ваш персонаж был заблокирован.\n\n");
	format:g_big_string("%s" #cWHITE "Имя персонажа: " #cPROJECT "%s" #cWHITE "\n", g_big_string, character_select[playerid][index][cs_name]);
	format:g_big_string("%s" #cWHITE "Администратор: " #cPROJECT "%s" #cWHITE "\n", g_big_string, character_select[playerid][index][cs_ban_admin_name]);
	format:g_big_string("%s" #cWHITE "Дата блокировки: " #cPROJECT "" #DATE_FORMAT "" #cWHITE "\n", 
		g_big_string,
		hour,
		minute,
		day,
		month,
		year
	);

	gmtime(character_select[playerid][index][cs_ban_before_date], year, month, day, hour, minute);
	
	format:g_big_string("%s" #cWHITE "Дата разблокировки: " #cPROJECT "" #DATE_FORMAT "" #cWHITE "\n", 
		g_big_string,
		hour,
		minute,
		day,
		month,
		year
	);
	
	format:g_big_string("%s" #cWHITE "Причина: " #cPROJECT "%s" #cWHITE "\n\n", 
		g_big_string,
		character_select[playerid][index][cs_ban_reason]
	);
	
	strcat(g_big_string, "" #cWHITE "Если Вы владелец аккаунта и Вас не устраивает вердикт, то\n\ 
	Вы можете подать апелляцию на - " #cPROJECT "" #__PROJECT_SITE "" #cWHITE ".");
	
	ShowPlayerDialog(playerid, D_LOGIN + 2, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Назад", "");
	
	SendClientMessage(playerid, C_LIGHTRED, "Данный персонаж заблокирован.");
}

CheckUserGoogleAuth(playerid)
{
	cache_get_value_name(0, "set_google_auth", user_data[playerid][u_settings][SET_GOOGLE_AUTH], MAX_GOOGLE_AUTH);
	
	if (!isnull(user_data[playerid][u_settings][SET_GOOGLE_AUTH]))
	{
		if (strcmp(GetUserIp(playerid), user_data[playerid][u_last_ip]) == 0)
		{
			return 0;
		}
		
		return 1;
	}
	
	return 0;
}

CheckUserBan(playerid)
{
	new ban_id;
		
	cache_get_value_name_int(0, "is_null_bans", ban_id);
	
	if (!ban_id)
	{
		return 1;
	}
	
	new before_date,
		ban_date;
		
	cache_get_value_name_int(0, "b_before_time", before_date);
	cache_get_value_name_int(0, "b_ban_time", ban_date);

	if (before_date > gettime())
	{
		clean:<g_big_string>;
		
		new year,
			month,
			day,
			hour,
			minute,
			reason					[	64	],
			admin_name				[	MAX_PLAYER_NAME		];
			
		cache_get_value_name(0, "b_reason", reason);
		cache_get_value_name(0, "b_admin_name", admin_name);
		
		gmtime(ban_date, year, month, day, hour, minute);
		
		strcat(g_big_string, "" #ERROR " Ваш аккаунт заблокирован на сервере.\n\n");
		format:g_big_string("%s" #cWHITE "Имя персонажа: " #cPROJECT "%s\n", g_big_string, GetUserName(playerid));
		format:g_big_string("%s" #cWHITE "Администратор: " #cPROJECT "%s\n", g_big_string, admin_name);
		format:g_big_string("%s" #cWHITE "Дата блокировки: " #cPROJECT "" #DATE_FORMAT "\n", 
			g_big_string,
			hour,
			minute,
			day,
			month,
			year
		);

		gmtime(before_date, year, month, day, hour, minute);
		
		format:g_big_string("%s" #cWHITE "Дата разблокировки: " #cPROJECT "" #DATE_FORMAT "\n", 
			g_big_string,
			hour,
			minute,
			day,
			month,
			year
		);
		
		format:g_big_string("%s" #cWHITE "Причина: " #cPROJECT "%s\n\n", 
			g_big_string,
			reason
		);
		
		strcat(g_big_string, "" #cWHITE "Если Вы владелец аккаунта и Вас не устраивает вердикт, то\n\ 
		Вы можете подать апелляцию на - " #cPROJECT "" #__PROJECT_SITE "" #cWHITE ".");
		
		ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Закрыть", "");
		
		SendClientMessage(playerid, C_LIGHTRED, !"Для того, чтобы покинуть сервер, введите /q.");
		Kick(playerid);
	}
	else 
	{
		format:g_string("UPDATE " #__BANS " SET b_active = 0 WHERE b_id = %i LIMIT 1",
			ban_id
		);
		
		mysql_pquery(db, g_string);
		
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Срок блокировки аккаунта истёк.");
		return 1;
	}
	
	return 0;
}

/**
    Other function
*/

static stock InitPlayerLoginCamera(playerid)
{
    TogglePlayerSpectating(playerid, true); 
    SetTimerEx("OnPlayerLoginCameraReady", 500, false, "d", playerid);
}

/**
    Commands
*/

CMD:relogin(playerid)
{
    // Log out as admin
    if (IsAdminLogged(playerid))
    {
        cmd_aduty(playerid);
    }

    // Log out as helper
    if (IsHelperLogged(playerid))
    {
        cmd_hduty(playerid);
    }

    // If user name is used, then hide name
    if (!ReplacePlayerName(playerid, TYPE_OOC))
    {
        ReplacePlayerName(playerid, TYPE_HIDDEN);
    }

    SetPlayerRelogin(playerid, true);
    OnCharacterBeforeLogout(playerid);
    return 1;
}

function OnCharacterLogout(playerid)
{
    // Clear data with
    CallLocalFunction("OnPlayerDisconnect", "dd", playerid, 1);
    CallLocalFunction("OnPlayerDataReset", "db", playerid, true);

    // Init login camera
    InitPlayerLoginCamera(playerid);

    // Show user character list
    ShowUserCharacterList(playerid);

    // Success message
    SendClientMessage(playerid, C_WHITE, !SUCCESS " Вы успешно вышли из системы и перешли в меню выбора персонажа.");
    return 1;
}
