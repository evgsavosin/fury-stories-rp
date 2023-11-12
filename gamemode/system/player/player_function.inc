/*!
	@brief Функции для системы игрока
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/


/**
    Public function
*/
Player_OnGameModeInit()
{
}

public OnPlayerConnect(playerid)
{
    OnPlayerDataReset(playerid, false);

	#if defined Player_OnPlayerConnect
		return Player_OnPlayerConnect(playerid);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define	OnPlayerConnect	Player_OnPlayerConnect
#if defined Player_OnPlayerConnect
	forward Player_OnPlayerConnect(playerid);
#endif


function OnPlayerDataReset(playerid, bool: is_relogin)
{
    Clear:player_data(playerid, is_relogin);

	#if defined Player_OnPlayerDataReset
		return Player_OnPlayerDataReset(playerid, is_relogin);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDataReset
    #undef OnPlayerDataReset
#else
    #define _ALS_OnPlayerDataReset
#endif

#define	OnPlayerDataReset	Player_OnPlayerDataReset
#if defined Player_OnPlayerDataReset
	forward Player_OnPlayerDataReset(playerid, bool: is_relogin);
#endif

Player_OnPlayerRequestSpawn(playerid) 
{
	if (!IsPlayerLogged(playerid))
	{
	    return 0;
	}
	
    return 1;
}

Player_OnPlayerStateChange(playerid, newstate, oldstate) 
{	
	#pragma unused oldstate
	
	if (newstate == PLAYER_STATE_DRIVER)
	{
		SetPlayerArmedWeapon(playerid, 0);
	}
	
	return 1;
}

Player_OnPlayerDisconnect(playerid, reason)
{
	if (!user_login{playerid})
	{
		return 1;
	}
	
	new Float: x,
		Float: y,
		Float: z,
		Float: angle;
		
	// Обновляем пользователя
	format:g_big_string("\
		UPDATE " #__USERS " \
		SET \
			u_last_date = NOW(), \
			u_last_ip = '%q', \
			u_online = 0 \
		WHERE \
			u_id = %i \
		LIMIT 1",
		GetUserIp(playerid),
		GetUserId(playerid)
	);
	
	mysql_pquery(db, g_big_string);
	
	// Обновляем персонажа
	GetPlayerPos(playerid, 
		x,
		y,
		z
	);
	
	GetPlayerFacingAngle(playerid, angle);
	
	format:g_big_string("\
		UPDATE " #__CHARACTERS " \
		SET \
			c_pos_x = %f, \
			c_pos_y = %f, \
			c_pos_z = %f, \
			c_pos_angle = %f, \
			c_world = %i, \
			c_int = %i, \
			c_health = %f, \
			c_last_date = NOW(), \
			c_online = 0, \
			c_payday = %i, \
			c_attack_weapon_id = %i, \
			c_attack_name_fist = '%q', \
			c_attack_name_cold = '%q' \
		WHERE \
			c_id = %i \
		LIMIT 1",
		x,
		y,
		z,
		angle,
		GetPlayerVirtualWorld(playerid),
		character_data[playerid][c_int],
		character_data[playerid][c_health],
		character_data[playerid][c_payday],
		character_data[playerid][c_attack_weapon_id],
		character_data[playerid][c_attack_name_fist],
		character_data[playerid][c_attack_name_cold],
		GetCharacterId(playerid)
	);
	
	mysql_pquery(db, g_big_string);
	
	
	if (!GetPVarInt(playerid, "Admin:SpectateMode"))
	{
		clean:<g_small_string>;
		format:g_small_string("(( %s[%i] ", GetPlayerCurrentName(playerid), playerid);
		
		if (reason == 0)
		{
			strcat(g_small_string, "вылетел. ))");
		}	
		else if (reason == 1) 
		{
			strcat(g_small_string, "вышел. ))");
		}
		else
		{
			strcat(g_small_string, "отсоединён сервером. ))");
		}
		
		ProxDetector(15.0, playerid, g_small_string, COLOR_FADE3, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, COLOR_FADE5, _, true);
	}
	
	// Удялем действия 
	for (new i; i < MAX_ACTIONS; i++)
	{
		if (isnull(character_action[playerid][i][c_text]))
		{
			continue;
		}
		
		clean:<character_action[playerid][i][c_text]>;
		
		if (IsValidDynamic3DTextLabel(character_action[playerid][i][c_text_id]))
		{
			DestroyDynamic3DTextLabel(character_action[playerid][i][c_text_id]);
		}
		
		character_action[playerid][i][c_text_id] = Text3D: INVALID_3DTEXT_ID;
	}
	
	// Удаляем объект для вип аккаунтов
	if (donate_object[playerid][d_object_id] != INVALID_OBJECT_ID)
	{
		if (IsValidDynamicObject(donate_object[playerid][d_object_id]))
		{
			DestroyDynamicObject(donate_object[playerid][d_object_id]);
		}
		donate_object[playerid][d_object_id] = INVALID_OBJECT_ID;
		
		if (IsValidDynamic3DTextLabel(donate_object[playerid][d_text_id]))
		{
			DestroyDynamic3DTextLabel(donate_object[playerid][d_text_id]);
		}
		
		donate_object[playerid][d_text_id] = Text3D: INVALID_3DTEXT_ID;
	}
	
	SetAdminLogForPlayer(playerid, reason, a_dislog);
	
	return 1;
}


/**
    Other function
*/

Move:player(playerid, Float: x, Float: y, Float: z, worldid = 0, interiorid = 0, use_angle = false, Float: angle = 0.0, use_pos = true)
{		
	new world = GetCharacterWorld(playerid),
		interior = GetCharacterInt(playerid);
	
	if (world && !worldid || world != worldid || interior != interiorid)
	{
		if (IsPlayerRenovation(playerid))
		{
			SetRenovationMode(playerid, false);
		}
	}
	
	if (interiorid != 0)
	{
		SetPVarInt(playerid, "Player:InInterior", true);
		Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, MAX_VISIBLE_OBJECTS_ALL);
	}
	else 
	{
		DeletePVar(playerid, "Player:InInterior");
		Streamer_SetVisibleItems(
			STREAMER_TYPE_OBJECT, 
			GetUserSettings(playerid, SET_VISIBLE_OBJECT),
			playerid
		);
	}
	
	Update:player_weather(playerid);
	
	HidePlayerDialog(playerid);
	
	SetPlayerVirtualWorld(playerid, worldid);
	SetPlayerInterior(playerid, interiorid);
	
	if (use_pos)
	{
		SetPlayerPos(playerid, x, y, z);
					
		if (use_angle)
		{
			SetPlayerFacingAngle(playerid, angle);
		}
		
		SetCameraBehindPlayer(playerid);
		
		Streamer_UpdateEx(
			playerid, 
			x, 
			y, 
			z, 
			worldid, 
			interiorid, 
			STREAMER_TYPE_OBJECT, 
			(1000 + GetPlayerPing(playerid))
		);
	}
		
	return 1;
}

PlayerBan(playerid, type, time, adminid, const reason[])
{
	new name		[	MAX_PLAYER_NAME		],
		player		[	MAX_PLAYER_NAME		],
		ip			[	MAX_PLAYER_IP		];

	if (adminid == ANTICHEAT_ID)
	{
		strcat(name, "SERVER");
		strcat(ip, "127.0.0.1");
	}
	else 
	{
		strcat(name, GetUserName(adminid), MAX_PLAYER_NAME);
		strcat(ip, GetUserIp(adminid), MAX_PLAYER_IP);
	}
	
	if (type == TYPE_BAN_CHARACTER)
	{
		strcat(player, GetCharacterName(playerid), MAX_PLAYER_NAME);
	}
	else if (type == TYPE_BAN_USER)
	{
		strcat(player, GetUserName(playerid), MAX_PLAYER_NAME);
	}
	
	format:g_big_string("INSERT INTO " #__BANS " \ 
		(b_type, b_account_id, b_account_name, b_account_ip, b_admin_id, b_admin_name, b_admin_ip, b_ban_date, b_before_date, b_reason, b_active) \ 
			VALUES \
		(%i, %i, '%q', '%q', %i, '%q', '%q', NOW(), FROM_UNIXTIME(%i), '%q', 1)",
		type,
		type == TYPE_BAN_CHARACTER ? GetCharacterId(playerid) : GetUserId(playerid),
		player,
		GetUserIp(playerid),
		(adminid != ANTICHEAT_ID) ? GetUserId(adminid) : INVALID_PARAM,
		name,
		ip,
		time,
		reason
	);
	
	mysql_tquery(db, g_big_string);
	
	SendClientMessage(playerid, C_LIGHTRED, 
		type == TYPE_BAN_CHARACTER ? ("Ваш персонаж был заблокирован.") : ("Ваш аккаунт был заблокирован.") 
	);
	
	KickWithDialog(playerid, adminid, reason);
}

KickWithDialog(playerid, adminid, const reason[] = "", code = 0x0)
{
	new bool: is_anticheat = (adminid == ANTICHEAT_ID), 
		year,
		month,
		day,
		minute,
		hour;
		
	getdate(year, month, day);
	gettime(hour, minute);
	
	clean:<g_big_string>;

	if (is_anticheat)
	{
		strcat(g_big_string, "" #ERROR " Вы были отсоединены от сервера античитом " #cPROJECT "" #__AC_VERSION "" #cWHITE ".\n\n");
	}
	else 
	{
		strcat(g_big_string, "" #ERROR " Вы были отсоединены от сервера.\n\n");
	
		if (adminid != INVALID_PLAYER_ID)
		{
			format:g_big_string("%sАдминистратор: " #cPROJECT "%s" #cWHITE "\n", 
				g_big_string,
				GetCharacterName(adminid)
			); 
		}
	}

	format:g_big_string("%sИмя аккаунта: " #cPROJECT "%s" #cWHITE "\n", 
		g_big_string,
		GetUserName(playerid)
	); 
	
	format:g_big_string("%sИмя персонажа: " #cPROJECT "%s" #cWHITE "\n", 
		g_big_string,
		GetCharacterName(playerid)
	); 
	
	format:g_big_string("%sДата: %02d.%02d.%04d\n", 
		g_big_string,
		day, 
		month, 
		year
	); 
	
	format:g_big_string("%sВремя: %02d:%02d\n", 
		g_big_string,
		hour, 
		minute
	); 
	
	if (is_anticheat)
	{
		format:g_big_string("%sПодозрение в использовании чит-программ. " #cRED "(#%d)", 
			g_big_string,
			code
		); 
		
		format:g_small_string("" #AC_MESSAGE " %s[%d] (%s) отсоединен по подозрению в читерстве. [%s | #%d]",
			GetCharacterName(playerid),
			playerid,
			GetUserName(playerid),
			reason,
			code
		);
		
		SendAdminMessage(C_RED, g_small_string);
		
		SendClientMessage(playerid, C_LIGHTRED, "" #AC_MESSAGE " Если это ложное срабатывание античита, то отправьте разработчикам сведения на сайт - " #__PROJECT_SITE ".");
	}
	else
	{
		format:g_big_string("%sПричина: " #cPROJECT "%s", 
			g_big_string,
			reason 
		);
	}
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Закрыть", "");
	
	#if defined __DEBUG
		Kick(playerid);
	#endif
	return 1;
}

KillPlayer(playerid)
{
	new Float: x,
		Float: y,
		Float: z,
		Float: angle;
		
	SetCharacterDeath(playerid, TYPE_DEATH_NONE);
	Update:character_int(playerid, "c_death", TYPE_DEATH_NONE);
	Update:death(playerid);
	
	format:g_small_string("(( %s[%i] получил «Player Kill» ))",
		GetPlayerCurrentName(playerid),
		playerid
	);
	
	ProxDetector(20.0, playerid, g_small_string, COLOR_FADE3, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, COLOR_FADE5);
	
	Create:corpse_data(playerid, TYPE_CORP_TEMP);
	
	GetSpawnInfo(playerid, x, y, z, angle, true);
	SetSpawnInfo(playerid, 264, GetCharacterSkin(playerid), x, y, z, angle, 0, 0, 0, 0, 0, 0);
	SpawnPlayer(playerid);
}

KillPlayerCharacter(playerid, offerid)
{	
	format:g_small_string("(( %s[%i] принимает «Character Kill» от %s[%i] ))",
		GetPlayerCurrentName(playerid),
		playerid,
		GetPlayerCurrentName(offerid),
		offerid
	);
	
	ProxDetector(20.0, playerid, g_small_string, COLOR_FADE3, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, COLOR_FADE5);
	
	Create:corpse_data(playerid, TYPE_CORP_DB);
				
	format:g_string("INSERT INTO " #__CKILL " \
		VALUES (%i, '%q', %i, '%q', NOW())",
		GetCharacterId(playerid),
		GetCharacterName(playerid),
		offerid,
		GetCharacterName(offerid)
	);
	
	mysql_pquery(db, g_string);
	
	Update:character_int(playerid, "c_status", STATUS_CK);
	KickWithDialog(playerid, INVALID_PLAYER_ID, "" #GRAY "«Character Kill»" #cWHITE "");
}

HealthPlayer(playerid, bool: is_help = false)
{	
	if (!IsUserAllowQuery(playerid))
	{
		return;
	}
	
	format:g_string("\
		UPDATE " #__CHARACTERS " \
		SET \
			c_death = 0, \
			c_health = %f, \
			c_attack_weapon_id = 0, \
			c_attack_name_cold = '', \
			c_attack_name_fist = '', \
			c_attack_name_camera = '' \
		WHERE \
			c_id = %i \
		LIMIT 1",
		is_help ? 10.0 : 100.0,
		GetCharacterId(playerid)
	);
	
	mysql_pquery(db, g_string, "OnPlayerHealth", "d", playerid);
	
	character_data[playerid][c_death] = 0;
	character_data[playerid][c_attack_weapon_id] = 0;
	character_data[playerid][c_attack_name_fist][0] =
	character_data[playerid][c_attack_name_cold][0] =
	character_data[playerid][c_attack_name_camera][0] = EOS;
	
	Update:death(playerid, is_help);
	
	SetPlayerHealth(playerid, is_help ? 10.0 : 100.0);
	TogglePlayerControllable(playerid, true);
	
	SetUserAllowQuery(playerid, false);
}

function OnPlayerHealth(playerid)
{	
	SetUserAllowQuery(playerid, true);
	return 1;
}

FreezePlayer(playerid, time = 3000)
{
	TogglePlayerControllable(playerid, false);
	SetTimerEx("OnPlayerUnfreeze", time, false, "i", playerid);
}

function OnPlayerUnfreeze(playerid)
{
	TogglePlayerControllable(playerid, true);
	return 1;
}

SetPlayerCash(const playerid, money)
{
	ResetPlayerMoney(playerid);
	GivePlayerCash(playerid, money);
	
	character_data[playerid][c_money] = money;
	Update:character_int(playerid, "c_money", money);
}

GivePlayerCash(const playerid, money)
{	
	if (character_data[playerid][c_money] + money < 0)
	{
		return 0;
	}
	
	character_data[playerid][c_money] += money;
	Update:character_int(playerid, "c_money", character_data[playerid][c_money]);
	
	ResetPlayerMoney(playerid);
	GivePlayerMoney(playerid, character_data[playerid][c_money]);
	
	return 1;
}

GivePlayerStartCapital(const playerid, money)
{	
	if (character_data[playerid][c_start_capital] + money < 0)
	{
		return 0;
	}
	
	character_data[playerid][c_start_capital] += money;
	Update:character_int(playerid, "c_start_capital", character_data[playerid][c_start_capital]);
	return 1;
}

GiveDebitCardMoney(const playerid, money)
{	
	if (character_data[playerid][c_card] + money < 0)
	{
		return 0;
	}
	
	character_data[playerid][c_card] += money;
	Update:character_int(playerid, "c_card", character_data[playerid][c_card]);
	
	return 1;
}

stock SetDebitCardMoney(const playerid, const money)
{	
	character_data[playerid][c_card] = money;
	Update:character_int(playerid, "c_card", character_data[playerid][c_card]);
}

GivePlayerBank(const playerid, money)
{	
	if (character_data[playerid][c_bank] + money < 0)
	{
		return 0;
	}
	
	character_data[playerid][c_bank] += money;
	Update:character_int(playerid, "c_bank", character_data[playerid][c_bank]);
	
	return 1;
}

stock SetPlayerBank(const playerid, const money)
{	
	character_data[playerid][c_bank] = money;
	Update:character_int(playerid, "c_bank", character_data[playerid][c_bank]);
}

GiveHealthPlayer(playerid, Float: health)
{
	character_data[playerid][c_health] = (character_data[playerid][c_health] += health) > 100.0 ? 
	100.0 : character_data[playerid][c_health];
	
	return SetPlayerHealth(playerid, character_data[playerid][c_health]);
}

GetPlayerIdByCharacterId(const character_id)
{
	foreach (new playerid : Player)
	{
		if (GetCharacterId(playerid) == character_id)
		{
			return playerid;
		}
	}
	
	return INVALID_PLAYER_ID;
}

GetPlayerIdByDebitCard(const number)
{
	foreach (new playerid : Player)
	{
		if (!IsPlayerLogged(playerid))
		{
			continue;
		}
		
		if (GetCharacterCardNumber(playerid) == number)
		{
			return playerid;
		}
	}
	
	return INVALID_PLAYER_ID;
}

IsValidPlayerDebitCard(const number)
{
	foreach (new playerid : Player)
	{	
		if (!IsPlayerLogged(playerid))
		{
			continue;
		}
		
		if (GetCharacterCardNumber(playerid) == number)
		{
			return 1;
		}
	}
	
	return 0;
}

SendRadioMessage(channel, slot = INVALID_PARAM, text[])
{
	new index;
	
	foreach (new playerid : Player)
	{
		if (!IsPlayerLogged(playerid))
		{
			continue;
		}
		
		if ((index = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_RADIO, _, true)) == INVALID_PARAM)
		{
			continue;
		}
		
		if (channel != GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1))
		{
			continue;
		}
		
		if (slot != INVALID_PARAM && slot != GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_2))
		{
			continue;
		}

		SendSplitMessage(playerid, (slot == INVALID_PARAM ? 0xF5DEB3AA : 0xF5D79FAA), text);
	}
}

ShowPlayerPass(playerid, targetid)
{
	clean:<g_big_string>;

	new first_name		[MAX_PLAYER_NAME],
		last_name		[MAX_PLAYER_NAME];
		
	sscanf(GetCharacterName(playerid), "p<_>s[20]s[20]", first_name, last_name);

	format:g_big_string(#DEFAULT " Данные о персонаже\n\n\
		Имя: " #cPROJECT "%s" #cWHITE "\n\
		Фамилия: " #cPROJECT "%s" #cWHITE "\n\
		Пол: " #cPROJECT "%s" #cWHITE "\n\
		Раса: " #cPROJECT "%s" #cWHITE "\n\
		Возраст: " #cPROJECT "%d лет" #cWHITE "\n\n",
		first_name,
		last_name,
		(!character_data[playerid][c_sex]) ? ("Мужской") : ("Женский"),
		GetCharacterRaceText(playerid),
		character_data[playerid][c_age]
	);
	
	strcat(g_big_string, #DEFAULT " Лицензии\n\n");
	
	new day,
		month,
		year;
	
	for (new E_LICENSES_INFO: i = li_start; i < li_end; i++)
	{
		if (IsPlayerLicenseExists(playerid, i))
		{
			gmtime(
				license_data[playerid][i][l_gave_time],
				year,
				month,
				day
			);
			
			format:g_big_string("%s%s: #%d от %02d.%02d.%d\n",
				g_big_string,
				license_info[_: i],
				license_data[playerid][i][l_id],
				day,
				month,
				year
			);
			
			if (license_data[playerid][i][l_take_time] > 0)
			{
				gmtime(license_data[playerid][i][l_gave_time],
					year,
					month,
					day
				);
			
				format:g_big_string("%s\t" #cRED "Изъято до: %02d.%02d.%d (%s)\n", 
					g_big_string,
					day,
					month,
					year,
					license_data[playerid][i][l_take_name]
				);
			}
		}
	}
	
	return ShowPlayerDialog(targetid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Закрыть", "");
}

