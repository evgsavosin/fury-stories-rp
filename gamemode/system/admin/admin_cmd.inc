/*!
	@brief Команды для системы администрирования
	@author Found (evg.savosin)
	@date 16.12.2016, update 08.03.2018
	
*/

/// Level: 1 (ADMIN_TRAINEE)
CMD:amenu(playerid)
{
	if (!IsPlayerGameAdmin(playerid))
	{
		return 0;
	}
	
	clean:<g_string>;
	
	format:g_string(" \
			Администраторы в сети\t" #cGRAY "/admins\n \
			Хелперы в сети\t" #cGRAY "/helpers\n \
			Список команд\t\n \
			Телепортироваться\t\n \
			Фракции\t" #cGRAY "/mfraction\n \
			Криминальные организации\t" #cGRAY "/mcrime\n \
			Античит\t" #cGRAY "/manticheat\n \
			Лог отключений\t" #cGRAY "/dislog\n \
			Лог смертей\t" #cGRAY "/deathlog"
	);
	
	ShowPlayerDialog(playerid, D_ADMIN, DIALOG_STYLE_TABLIST, " ", g_string, "Далее", "Закрыть");
	
	return 1;
}

CMD:admins(playerid)
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE) && !IsPlayerHelper(playerid))
	{
		return 0;
	}
	
	clean:<g_big_string>;
	strcat(g_big_string, #DEFAULT " Администраторы в сети:\n\n");
	foreach (new i : Player)
	{
		if (!IsPlayerGameAdmin(i))
		{
			continue;
		}
		
		format:g_small_string(" " #cPROJECT "(AFK: %d)" #cWHITE "", GetPlayerAfk(i));
		format:g_big_string("%s %s[%i]"cWHITE" - уровень: %i%s\n",
			g_big_string,
			GetUserName(i),
			i,
			GetAdminLevel(i),
			IsPlayerAfk(i) ? (g_small_string) : ("")
		);
	}
	
	ShowPlayerDialog(playerid, D_ADMIN + 1, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Назад", "");
	return 1;
}

CMD:helpers(playerid)
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE) && !IsPlayerHelper(playerid))
	{
		return 0;
	}
	
	clean:<g_big_string>;
	strcat(g_big_string, #DEFAULT " Хелперы:\n\n");
	foreach (new i : Player)
	{
		if (!IsPlayerHelper(i))
		{
			continue;
		}
		
		format:g_small_string(" " #cPROJECT "(AFK: %d)" #cWHITE "", GetPlayerAfk(i));
		format:g_big_string("%s %s[%i] (%s)" #cWHITE "%s\n",
			g_big_string,
			GetUserName(i),
			i,
			GetCharacterName(i),
			IsPlayerAfk(i) ? (g_small_string) : ("")
		);
	}
	
	ShowPlayerDialog(playerid, D_ADMIN + 1, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Назад", "");
	return 1;
}

CMD:aduty(playerid)
{
	new server_tick = GetTickCount();
		
	if (GetPVarInt(playerid, "TimeCMD:Aduty") > server_tick)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
		return 1;
	}
	
	if (IsAdminLogged(playerid))
	{	
		ReplacePlayerName(playerid, TYPE_IC);
		
		// Admin log
		ShowAdminLog(playerid, false);
		
		if (!IsPlayerDeveloper(playerid))
		{
			format:g_small_string("" ADMIN_MESSAGE " %s[%d] покинул администрирование. [IP: %s]",
				GetUserName(playerid),
				playerid,
				GetUserIp(playerid)
			);
		}
		else 
		{
			format:g_small_string(ADMIN_MESSAGE " %s[%d] покинул администрирование.",
				GetUserName(playerid),
				playerid
			);
		}
		
		SendAdminMessage(C_GRAY, g_small_string);
		
		Clear:admin_data(playerid);
		
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы покинули администрирование. Для возвращения используйте " #cPROJECT "/aduty" #cWHITE ".");
	}
	else 
	{
		printf("[cmd_aduty]: The player %s[%d] is trying to log in as admin.",
			GetPlayerCurrentName(playerid),
			playerid
		);
		
		format:g_string("SELECT * FROM " #__ADMINS " WHERE a_user_id = %i LIMIT 1",
			GetUserId(playerid)
		);
		
		mysql_tquery(db, g_string, "OnAdminLogin", "i", playerid);
		SetPVarInt(playerid, "TimeCMD:Aduty", server_tick + 10000);
	}
	
	return 1;
}

CMD:a(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /a [текст]");
		return 1;
	}
	
	format:g_small_string("" ADMIN_MESSAGE " %s[%d]: %s",
		GetUserName(playerid),
		playerid,
		params
	);
	
	SendAdminMessage(C_GREEN, g_small_string, true);
	
	return 1;
}

CMD:setworld(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	SetPlayerVirtualWorld(playerid, strval(params));
	return 1;
}

CMD:setint(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	SetPlayerInterior(playerid, strval(params));
	return 1;
}

CMD:astats(playerid, params[])
{
	if (!IsPlayerGameAdmin(playerid))
	{
	    return 0;
	}
	
	if (isnull(params) || !IsInt(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /astats [ID игрока]");
		return 1;
	}
	
	new targetid = strval(params);
		
	if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	ShowPlayerStats(targetid, playerid, true);
	return 1;
}

CMD:afrisk(playerid, params[])
{
	if (!IsPlayerGameAdmin(playerid))
	{
	    return 0;
	}
	
	new targetid = strval(params);
	
	if (isnull(params) || !IsInt(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /afrisk [ID игрока]");
		return 1;
	}
		
	if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	ShowInventoryItems(targetid, playerid);
	return 1;
}

CMD:ans(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE) && !IsPlayerHelper(playerid))
	{
		return 0;
	}
	
	new targetid,
		text			[	128		];
		
	if (sscanf(params, "is[128]", targetid, text))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /ans [ID игрока] [текст]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || targetid == playerid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	format:g_small_string("%s %s[%d] для %s[%d]: %s",
		IsPlayerHelper(playerid) ? ("" #HELPER_MESSAGE "") : ("" #ADMIN_MESSAGE ""),
		GetPlayerCurrentName(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		targetid,
		text
	);
	
	if (IsPlayerHelper(playerid))
	{
		SendHelperMessage(C_ORANGE, g_small_string, true);
	}
	else 
	{
		SendAdminMessage(C_ORANGE, g_small_string, true);
	}
	
	format:g_small_string("%s %s[%d] ответил Вам: %s",
		IsPlayerGameAdmin(playerid) ? ("Администратор") : ("Хелпер"),
		GetPlayerCurrentName(playerid),
		playerid,
		text
	);
	
	psend:(targetid, C_YELLOW);
	
	return 1;
}

CMD:sp(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	if (isnull(params) || !IsInt(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /sp [ID игрока]");
		return 1;
	}
	
	new targetid = strval(params);
		
	if (!IsPlayerLogged(targetid) || targetid == playerid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	AdminStartSpectate(playerid, targetid);
	return 1;
}

CMD:gotohouse(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new id;
	
	if (sscanf(params, "i", id))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /gotohouse [ID жилищного помещения]");
		return 1;
	}
	
	new index = GetHouseIndexById(id);
	
	if (index == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Неверный ID жилищного помещения.");
		return 1;
	}
	
	Move:player(playerid, 
		house_data[index][h_pos][0], 
		house_data[index][h_pos][1], 
		house_data[index][h_pos][2], 
		house_data[index][h_world], 
		house_data[index][h_interior]
	);
	
	return 1;
}

CMD:gotopremise(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new id;
	
	if (sscanf(params, "i", id))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /gotopremise [ID помещения]");
		return 1;
	}
	
	new index = GetPremiseIndexById(id);
	
	if (index == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Неверный ID помещения.");
		return 1;
	}
	
	Move:player(playerid, 
		premise_data[index][pr_pos][0], 
		premise_data[index][pr_pos][1], 
		premise_data[index][pr_pos][2], 
		premise_data[index][pr_world], 
		premise_data[index][pr_interior]
	);
	
	return 1;
}

CMD:kick(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new targetid,
		reason				[	 32 ];
		
	if (sscanf(params, "is[32]", targetid, reason))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /kick [ID игрока] [причина]");
		return 1;
	}
	
	if (!IsPlayerConnected(targetid) || targetid == playerid || IsPlayerDeveloper(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}

	format:g_small_string("Администратор %s[%d] отсоединил от сервера %s. Причина: %s",
		GetUserName(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		reason
	);
	
	format:g_string("(( Администратор %s[%d] отсоединил от сервера %s. Причина: %s ))",
		GetUserName(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		reason
	);
	
	SendGlobalAdminMessage(g_small_string, targetid, g_string);
	KickWithDialog(targetid, playerid, reason);
	return 1;
}

CMD:mute(playerid, params[])
{	
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
		
	new targetid,
		time,
		reason		[	 32  	];
		
	if (sscanf(params, "iis[32]", targetid, time, reason))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /mute [ID игрока] [срок(в минутах)] [причина]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || targetid == playerid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (IsPlayerMuted(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У данного игрока уже заблокирован OOC чат.");
		return 1;
	}
	
	if (!(0 < time <= 300))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Указываемое время должно быть не меньше 1 и не большее 300 минут.");
		return 1;
	}
	
	format:g_small_string("Администратор %s[%d] заблокировал OOC чат %s на %d мин. Причина: %s",
		GetUserName(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		time,
		reason
	);
	
	format:g_string("(( Администратор %s[%d] заблокировал OOC чат %s на %d мин. Причина: %s ))",
		GetUserName(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		time,
		reason
	);
	
	SendGlobalAdminMessage(g_small_string, targetid, g_string);

	pformat:("" #ERROR " Вам заблокировали использование OOC чата на %d мин.",
		time
	);
	
	psend:(targetid, C_WHITE);
	
	time = gettime() + time * 60;
	
	user_data[targetid][u_mute] = time;
	Update:user_int(targetid, "u_mute", time);

	return 1;
}

CMD:unmute(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new targetid;
		
	if (sscanf(params, "i", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /unmute [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || targetid == playerid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
		
	if (!IsPlayerMuted(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У данного игрока не заблокирован OOC чат.");
		return 1;
	}
	
	format:g_small_string("Администратор %s[%d] разблокировал OOC чат %s.",
		GetUserName(playerid),
		playerid,
		GetPlayerCurrentName(targetid)
	);
	
	format:g_string("(( Администратор %s[%d] разблокировал OOC чат %s. ))",
		GetUserName(playerid),
		playerid,
		GetPlayerCurrentName(targetid)
	);
	
	SendGlobalAdminMessage(g_small_string, playerid, g_string);
	
	SendClientMessage(targetid, C_WHITE, !#SUCCESS " OOC блокировка чата окончилась, Вы снова можете пользоваться им.");
	
	user_data[targetid][u_mute] = 0;
	Update:user_int(targetid, "u_mute", 0);

	return 1;
}

CMD:slap(playerid, params[]) 
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new targetid;
	
 	if (sscanf(params, "i", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /slap [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	new Float: x,
		Float: y,
		Float: z;
		
	GetPlayerPos(targetid, x, y, z);
	SetPlayerPos(targetid, x, y, z + 5.0);

	if (targetid != playerid)
	{	
		format:g_small_string("Admin %s(%i) has slapped %s(%i).",
			GetPlayerCurrentName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			targetid
		);
		
		SendAdminLog(g_small_string);
	}
	
	return 1;
}

CMD:goto(playerid, params[]) 
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new targetid;
		
    if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /goto [ID игрока]");
		return 1;
	}
	
    if (!IsPlayerLogged(targetid) || targetid == playerid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}	
	
	new Float: x,
		Float: y,
		Float: z;
		
	GetPlayerPos(targetid, x, y, z);
	
	if (GetPlayerState(playerid) == PLAYER_STATE_DRIVER) 
	{
		new Float: v_x,
			Float: v_y,
			Float: v_z,
			vehicleid = GetPlayerVehicleID(playerid);
			
		GetVehicleVelocity(vehicleid, v_x, v_y, v_z);
		
		SetVehiclePos(vehicleid, x + 1.0, y + 1.0, z + 1.0);
		SetVehicleVelocity(vehicleid, v_x, v_y, v_z);
	}
	else
	{
		Move:player(
			playerid, 
			x + 1.0, 
			y + 1.0, 
			z, 
			GetPlayerVirtualWorld(targetid), 
			GetPlayerInterior(targetid)
		);
	}
	
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
	SetPlayerInterior(playerid, GetPlayerInterior(targetid));
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно телепортировались к игроку.");
	return 1;
}

CMD:aspawn( playerid, params[] ) 
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new targetid;
		
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /aspawn [ID игрока]");
		return 1;
	}
		
	if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
		
	new Float: x, 
		Float: y, 
		Float: z, 
		Float: angle;
		
	GetSpawnInfo(targetid, x, y, z, angle);
	SetSpawnInfo(targetid, 264, GetCharacterSkin(targetid), x, y, z, angle, 0, 0, 0, 0, 0, 0 );
	
	SpawnPlayer(targetid);
	
	pformat:(#SUCCESS " Вы зареспавнили игрока %s[%d].",
		GetPlayerCurrentName(targetid),
		targetid
	);
	
	psend:(playerid, C_LIGHTRED);
	
	pformat:("Администратор %s[%i] зареспавнил Вас.",
		GetUserName(playerid),
		playerid
	);
	
	psend:(targetid, C_LIGHTRED);
	
	return 1;
}

CMD:gethere(playerid, params[]) 
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new targetid;
		
    if (sscanf(params, "i", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /gethere [ID игрока]");
		return 1;
	}
	
    if (!IsPlayerLogged(targetid) || targetid == playerid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
		
	new player_state = GetPlayerState(targetid),
		Float: x,
		Float: y,
		Float: z;
		
	new world = GetPlayerVirtualWorld(playerid),
		int = GetPlayerInterior(playerid);
		
	GetPlayerPos(playerid, x, y, z);
	
	if (player_state == PLAYER_STATE_SPECTATING)
	{
		if (GetPVarInt(targetid, "Admin:SpectateMode"))
		{
			AdminStopSpectate(targetid);
		}
		else 
		{
			TogglePlayerSpectating(playerid, false);
		}
	}
	
	Move:player(targetid, x + 1.0, y + 1.0, z, world, int);
	
	pformat:("" #SUCCESS " Вы успешно телепортировали к себе %s[%i].",
		GetPlayerCurrentName(targetid),
		targetid
	);
	
	psend:(playerid, C_WHITE);
	
	pformat:("Администратор %s[%i] телепортировал Вас к себе.",
		GetUserName(playerid),
		playerid
	);
	
	psend:(targetid, C_LIGHTRED);
	
	format:g_small_string("Admin %s(%i) teleported %s(%i) to himself.",
		GetUserName(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		targetid
	);
	
	SendAdminLog(g_small_string);
	return 1;
}

CMD:weapons(playerid, params[]) 
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new targetid;
		
	if (sscanf(params, "i", targetid)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /weapons [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	new 
		weapon,
		ammo,
		str_weapon_name				[		32 		],
		bool: is_exists;
		
	clean:<g_string>;
	strcat(g_string, "" #cPROJECT "Название оружия\t" #cPROJECT "Патроны\t" #cPROJECT "Слот\n");
	
	for (new i; i < MAX_WEAPON_SLOTS; i++)
	{
		GetPlayerWeaponData(targetid, i, weapon, ammo);
		
		if (weapon == 0)
		{
			continue;
		}
		
		GetWeaponName(weapon, str_weapon_name, sizeof str_weapon_name);
		
		format:g_string("%s%s\t%i\t%i\n",
			g_string,
			str_weapon_name,
			ammo,
			i
		);
		
		is_exists = true;
	}
	
	if (!is_exists)
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " У данного игрока отсутствует оружие.");
		return 1;
	}
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_TABLIST_HEADERS, GetPlayerCurrentName(targetid), g_string, "Закрыть", "");
	return 1;
}

CMD:aafk(playerid, params[]) 
{
    if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new time,
		count;
	
    if (sscanf(params, "i", time))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /aafk [время в секундах]");
		return 1;
	}
	
	clean:<g_big_string>;
	strcat(g_big_string, "" #DEFAULT " Игроки в AFK:\n\n");
	
	foreach (new i : Player)
	{
		if (!IsPlayerLoggedforeach(i) 
		|| GetPlayerAfk(i) < time)
		{
			continue;
		}
		
		format:g_big_string("%s%s[%i] - %i сек.\n", 
			g_big_string,
			GetPlayerCurrentName(i),
			i, 
			GetPlayerAfk(i)
		);
		
		if (count++ > 30)
		{
			break;
		}
	}
	
	if (count == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " На данный момент нет игроков в AFK.");
		return 1;
	}
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Закрыть", "");
	return 1;
}

CMD:ddesc(playerid, params[]) 
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new targetid,
		reason		[	32 	];
		
	if (sscanf(params, "is[32]", targetid, reason)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /ddesc [ID игрока] [причина]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (isnull(character_data[targetid][c_desc]))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У данного персонажа не установлено описание.");
		return 1;
	}
	
	clean:<character_data[targetid][c_desc]>;
	Update:character_string(targetid, "c_desc", "");
	
	pformat:("" #SUCCESS " Вы успешно удалили описание персонажа %s[%i].",
		GetPlayerCurrentName(targetid),
		targetid
	);
	
	psend:(playerid, C_WHITE);
	
	pformat:("Администратор %s[%i] удалил Ваше описание. Причина: %s.",
		GetPlayerCurrentName(playerid),
		playerid,
		reason
	);
	
	psend:(targetid, C_LIGHTRED);
	
	format:g_small_string("~r~Admin %s(%i) has deleted description %s(%i).",
		GetPlayerCurrentName(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		targetid
	);

	SendAdminLog(g_small_string);
	return 1;
}

CMD:daction(playerid, params[]) 
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new targetid;
		
	if (sscanf(params, "i", targetid)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /daction [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	SetPVarInt(playerid, "Admin:SelectActionTargetId", targetid);
	ShowPlayerActionList(targetid, D_ADMIN + 51, playerid);
	return 1;
}

CMD:aheal(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new targetid;
		
    if (sscanf(params, "i", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /aheal [ID игрока]");
		return 1;
	}
	
    if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	HealthPlayer(targetid);
	
	pformat:("" #SUCCESS " Вы успешно вылечили игрока %s[%i].",
		GetPlayerCurrentName(targetid),
		targetid
	);
	
	psend:(playerid, C_WHITE);
	
	pformat:("Администратор %s[%i] вылечил Вас.",
		GetUserName(playerid),
		playerid
	);
	
	psend:(targetid, C_LIGHTRED);
	
	format:g_small_string("Admin %s(%i) has healed %s(%i).",
		GetUserName(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		targetid
	);

	SendAdminLog(g_small_string);
	return 1;
}

CMD:getcar(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new vehicleid;
	
	if (sscanf(params, "i", vehicleid)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /getcar [ID транспорта]");
		return 1;
	}
	
	new Float: x,
		Float: y,
		Float: z;
		
	GetPlayerPos(playerid, x, y, z);
	SetVehiclePos(vehicleid, x, y, z);
	
	format:g_small_string("Admin %s(%i) teleported vehicle (%d).",
		GetUserName(playerid),
		playerid,
		vehicleid
	);

	SendAdminLog(g_small_string);
	return 1;
}

CMD:warn(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	new targetid,
		reason		[	32	];
		
    if (sscanf(params, "us[32]", targetid, reason))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /warn [ID игрока] [причина]");
		return 1;
	}
	
    if (!IsPlayerLogged(targetid) || targetid == playerid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}

	new bool: is_ban,
		warn = user_data[targetid][u_warn] + 1,
		days;
	
	
	if (warn >= 5)
	{
		days = UNIXTIME_END;
		is_ban = true;
	}
	else if (warn == 4)
	{
		days = gettime() + (60 * 60 * 24 * 7);
		is_ban = true;
	}
	else if (warn == 3)
	{
		days = gettime() + (60 * 60 * 24);
		is_ban = true;
	}
	
	if (is_ban)
	{
		format:g_small_string("Администратор %s[%i] заблокировал персонажа %s на %i дней - [%d/%d предупреждений]. Причина: %s",
			GetPlayerCurrentName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			days,
			warn,
			MAX_USER_WARNS,
			reason
		);
		
		format:g_string("(( Администратор %s[%i] заблокировал персонажа %s на %i дней - [%d/%d предупреждений]. Причина: %s ))",
			GetPlayerCurrentName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			days,
			warn,
			MAX_USER_WARNS,
			reason
		);
		
		PlayerBan(targetid, TYPE_BAN_USER, days, playerid, reason);
	}
	else 
	{
		format:g_small_string("Администратор %s[%i] выдал предупреждение %s - [%d/%d предупреждений]. Причина: %s",
			GetPlayerCurrentName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			warn,
			MAX_USER_WARNS,
			reason
		);
		
		format:g_string("(( Администратор %s[%i] выдал предупреждение %s - [%d/%d предупреждений]. Причина: %s ))",
			GetPlayerCurrentName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			warn,
			MAX_USER_WARNS,
			reason
		);
		
		KickWithDialog(targetid, playerid, reason);
	}
	
	SendGlobalAdminMessage(g_small_string, playerid, g_string);
	
	user_data[targetid][u_warn] = warn;
	Update:user_int(targetid, "u_warn", user_data[targetid][u_warn]);
	Update:user_string(targetid, "u_status", "RETEST");
	return 1;
}


/// Level: 2 (ADMIN_JUNIOR)
CMD:dcorpse(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_JUNIOR))
	{
		return 0;
	}
	
	new index;
	
	if (sscanf(params, "i", index))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /corpse [ID трупа]");
		return 1;
	}
	
	index--;
	
	if (!(0 <= (index) <= MAX_CORPSES) || corpse_data[index][corp_type] == TYPE_CORP_NONE)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы указали неверный ID трупа.");
		return 1;
	}
	
	format:g_small_string("Admin %s(%i) has removed corpse %s (#%d).",
		GetUserName(playerid),
		playerid,
		corpse_data[index][corp_character_name],
		index + 1
	);

	SendAdminLog(g_small_string);
	
	Remove:corpse_data(index);
	return 1;
}

CMD:gotocorpse(playerid, params[])
{	
	if (!CheckAdminAccess(playerid, ADMIN_JUNIOR))
	{
		return 0;
	}
	
	new index;
	
	if (sscanf(params, "i", index))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /corpse [ID трупа]");
		return 1;
	}
	
	index--;
	
	if (!(0 <= (index) <= MAX_CORPSES) || corpse_data[index][corp_type] == TYPE_CORP_NONE)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы указали неверный ID трупа.");
		return 1;
	}
	
	Move:player(playerid, 
		corpse_data[index][corp_pos][0], 
		corpse_data[index][corp_pos][1], 
		corpse_data[index][corp_pos][2], 
		corpse_data[index][corp_world], 
		corpse_data[index][corp_int]
	);
	
	return 1;
}


CMD:sethp(playerid, params[]) 
{
	if (!CheckAdminAccess(playerid, ADMIN_JUNIOR))
	{
		return 0;
	}
	
	new targetid,
		health;
		
    if (sscanf(params, "ii", targetid, health))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /sethp [ID игрока] [Количество HP]");
		return 1;
	}
	
    if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	SetPlayerHealth(targetid, float(health));
	
	pformat:("" #SUCCESS " Вы успешно установили игроку %s[%i] здоровье.",
		GetPlayerCurrentName(targetid),
		targetid
	);
	
	psend:(playerid, C_WHITE);
	
	pformat:("Администратор %s[%i] установил Вам здоровье.",
		GetUserName(playerid),
		playerid
	);
	
	psend:(targetid, C_LIGHTRED);
	
	format:g_small_string("Admin %s(%i) has set health %s(%i) (%0.2f HP).",
		GetUserName(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		targetid,
		float(health)
	);

	SendAdminLog(g_small_string);
	return 1;
}

CMD:aunarrest(playerid, params[]) 
{
	if (!CheckAdminAccess(playerid, ADMIN_JUNIOR))
	{
		return 0;
	}
	
	new targetid,
		reason	[64];
		
    if (sscanf(params, "is[64]", targetid, reason))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /aunarrest [ID игрока] [Причина]");
		return 1;
	}
	
    if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	ResetPlayerArrest(targetid);
	
	pformat:("" #SUCCESS " Вы успешно освободили игрока %s[%i].",
		GetPlayerCurrentName(targetid),
		targetid
	);
	
	psend:(playerid, C_WHITE);
	
	pformat:("Администратор %s[%i] освободил Вас. Причина: %s",
		GetUserName(playerid),
		playerid, 
		reason
	);
	
	psend:(targetid, C_LIGHTRED);
	
	format:g_small_string(ADMIN_MESSAGE " %s[%d] освободил %s[%d]. Причина: %s",
		GetUserName(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		targetid,
		reason
	);

	SendAdminMessage(C_GRAY, g_small_string);
	return 1;
}

CMD:ban(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_JUNIOR))
	{
		return 0;
	}
	
	new targetid,
		days,
		reason				[32];
	
	if (sscanf(params, "iis[32]", targetid, days, reason))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /ban [ID игрока] [дни " #cRED "(1 до 90)" #cWHITE " | " #cRED "(0 - навсегда)" #cWHITE "] [причина]");
		return 1;
	}
	
	if (!IsPlayerRegister(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок незарегистрирован и был заблокирован серверной блокировкой.");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || targetid == playerid || IsPlayerDeveloper(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (!(0 <= days <= 90))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Количество дней может быть от 1 до 90. Блокировка навсегда выдается со значением 0.");
		return 1;
	}
	
	if (days == 0)
	{
		format:g_small_string("Администратор %s[%i] заблокировал персонажа %s навсегда. Причина: %s",
			GetUserName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			reason
		);
		
		format:g_string("(( Администратор %s[%i] заблокировал персонажа %s навсегда. Причина: %s ))",
			GetUserName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			reason
		);
		
		days = UNIXTIME_END;
	}
	else 
	{
		format:g_small_string("Администратор %s[%i] заблокировал персонажа %s на %i дней. Причина: %s",
			GetUserName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			days,
			reason
		);
		
		format:g_string("(( Администратор %s[%i] заблокировал персонажа %s на %i дней. Причина: %s ))",
			GetUserName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			days,
			reason
		);
		
		days = gettime() + (60 * 60 * 24 * days);
	}
	
	SendGlobalAdminMessage(g_small_string, playerid, g_string);
	
	format:g_small_string(#ADMIN_MESSAGE " ID: %i | Имя: %s(%s) | IP адрес: %s", 
		GetUserId(targetid),
		GetUserName(targetid),
		GetCharacterName(targetid),
		GetUserIp(targetid)
	);
	
	SendAdminMessage(C_LIGHTRED, g_small_string);
	
	PlayerBan(targetid, TYPE_BAN_CHARACTER, days, playerid, reason);
	
	printf("[cmd_ban]: Admin %s(%d)[%d] has been blocked %s[%d] (%d, %s)",
		GetPlayerCurrentName(playerid),
		GetUserId(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		targetid,
		GetAdminLevel(playerid),
		admin_data[playerid][a_ip]
		
	);
	return 1;
}

CMD:unban(playerid, params[])
{
	if (!IsPlayerGameAdmin(playerid))
	{
		return 0;
	}
	
	if (GetAdminLevel(playerid) < ADMIN_JUNIOR)
	{
		SendClientMessage(playerid, C_WHITE, PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /unban [Nick_Name]");
		return 1;
	}
	
	format:g_string("UPDATE " #__BANS " SET b_active = 0 WHERE b_type = %i AND b_account_name = '%q' AND b_active = 1 LIMIT 1",
		TYPE_BAN_CHARACTER,
		params
	);
	
	mysql_tquery(db, g_string, "OnAdminUnban", "is", playerid, params);

	return 1;
}

function OnAdminUnban(playerid, params[])
{
	if (cache_affected_rows() == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный персонаж не заблокирован или Вы ввели неверное имя персонажа.");
		return 1;
	}

	format:g_small_string("" #ADMIN_MESSAGE " %s[%i] разблокировал персонажа: %s.",
		GetPlayerCurrentName(playerid),
		playerid,
		params
	);
	
	SendAdminMessage(C_GRAY, g_small_string);
	return 1;
}

CMD:g(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_JUNIOR))
	{
		return 0;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /g [текст]");
		return 1;
	}
	
	format:g_small_string("Администратор %s[%i]: %s",
		GetUserName(playerid),
		playerid,
		params
	);
	
	SendSplitMessageToAll(C_LIGHTRED, g_small_string);
	
	return 1;
}

CMD:vrespawn(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_JUNIOR))
	{
		return 0;
	}
		
	if (isnull(params) || !IsInt(params))
	{	
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /vrespawn [радиус]");
		return 1;
	}
	
	new Float: radius = floatstr(params),
		Float: x,
		Float: y,
		Float: z;
	
	for (new i, j = GetVehiclePoolSize(); i < j; i++)
	{
		GetVehiclePos(i, x, y, z);
		
		if (IsPlayerInRangeOfPoint(playerid, radius, x, y, z))
		{
			SetVehicleToRespawn(i);
		}
	}
	
	format:g_small_string("Admin %s(%i) has respawn vehicles in radius %0.1f.",
		GetUserName(playerid),
		playerid,
		radius
	);

	SendAdminLog(g_small_string);
	return 1;
}

/// Level: 3 (ADMIN_NORMAL)
CMD:afuninvite(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_NORMAL))
	{
		return 0;
	}
	
	new targetid,
		reason	[64];
	
	if (sscanf(params, "us[64]", targetid, reason))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /afuninvite [ID игрока] [причина]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (!IsFractionMember(targetid))
	{
		SendClientMessage(playerid, C_WHITE, #ERROR " Данный игрок не состоит в организации.");
		return 1;
	}
	
	// Сброс фракции
	ResetPlayerFraction(targetid);
	
	pformat:("" #SUCCESS " Вы уволили игрока " #cPROJECT "%s[%d]" #cWHITE" из организации с причиной: %s.",
		GetPlayerCurrentName(targetid),
		targetid,
		reason
	);
	
	psend:(playerid, C_WHITE);
	
	pformat:("Администратор %s[%d] уволил Вас из организации. Причина: %s",
		GetUserName(playerid),
		playerid,
		reason
	);
	
	psend:(targetid, C_LIGHTRED);
	return 1;
}

CMD:vrepair(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_NORMAL))
	{
		return 0;
	}
	
	new vehicleid;
	
	if (sscanf(params, "i", vehicleid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /vrepair [ID транспорта]");
		return 1;
	}

	if (!(0 < vehicleid < MAX_VEHICLES) || vehicle_data[vehicleid][v_model] == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы указали несуществующий ID транспорта.");
		return 1;
	}

	vehicle_data[vehicleid][v_health] = 1000.0;
	RepairVehicle(vehicleid);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS" Вы успешно починили данный транспорт.");
	
	format:g_small_string("Admin %s(%i) has repaired vehicle (ID:%i).",
		GetPlayerCurrentName(playerid),
		playerid,
		vehicleid
	);

	SendAdminLog(g_small_string);
	return 1;
}


CMD:vfuel(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_NORMAL))
	{
		return 0;
	}
	
	new vehicleid;
	
	if (sscanf(params, "i", vehicleid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /vfuel [ID транспорта]");
		return 1;
	}

	if (!(0 < vehicleid < MAX_VEHICLES) || vehicle_data[vehicleid][v_model] == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы указали несуществующий ID транспорта.");
		return 1;
	}

	vehicle_data[vehicleid][v_fuel] = 100.0;
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS" Вы заправили данный транспорт.");
	
	format:g_small_string("Admin %s(%i) has filled vehicle (ID:%i).",
		GetPlayerCurrentName(playerid),
		playerid,
		vehicleid
	);

	SendAdminLog(g_small_string);
	return 1;
}

CMD:tmpskin(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_NORMAL))
	{
		return 0;
	}
	
	new targetid,
		skinid;
		
	if (sscanf(params, "ii", targetid, skinid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /setskin [ID игрока] [ID скина]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	pformat:("" #SUCCESS " Вы установили временный скин " #cPROJECT "%s[%i]" #cWHITE" - %i.",
		GetPlayerCurrentName(targetid),
		targetid,
		skinid
	);
	
	psend:(playerid, C_WHITE);
	
	pformat:("Администратор %s[%i] установил Вам временный скин.",
		GetUserName(playerid),
		playerid
	);
	
	psend:(targetid, C_LIGHTRED);
	
	SetPlayerSkin(targetid, skinid);
	return 1;
}

CMD:aban(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_NORMAL))
	{
		return 0;
	}
	
	new targetid,
		days,
		reason				[	32	];
	
	if (sscanf(params, "iis[32]", targetid, days, reason))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /aban [ID игрока] [дни " #cRED "(1 до 90)" #cWHITE " | " #cRED "(0 - навсегда)" #cWHITE "] [причина]");
		return 1;
	}
	
	if (!IsPlayerRegister(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок незарегистрирован.");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || targetid == playerid || IsPlayerDeveloper(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (!(0 <= days <= 90))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Количество дней может быть от 1 до 90. Блокировка навсегда выдается со значением 0.");
		return 1;
	}
	
	if (days == 0)
	{
		format:g_small_string("Администратор %s[%i] заблокировал аккаунт %s навсегда. Причина: %s",
			GetUserName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			reason
		);
		
		format:g_string("(( Администратор %s[%i] заблокировал аккаунт %s навсегда. Причина: %s ))",
			GetUserName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			reason
		);
		
		days = UNIXTIME_END;
	}
	else 
	{
		format:g_small_string("Администратор %s[%i] заблокировал аккаунт %s на %i дней. Причина: %s",
			GetUserName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			days,
			reason
		);
		
		format:g_string("(( Администратор %s[%i] заблокировал аккаунт %s на %i дней. Причина: %s ))",
			GetUserName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			days,
			reason
		);
		
		days = gettime() + (60 * 60 * 24 * days);
	}
	
	SendGlobalAdminMessage(g_small_string, playerid, g_string);
	
	format:g_small_string("" #ADMIN_MESSAGE " ID: %i | Имя: %s(%s) | IP адрес: %s", 
		GetUserId(targetid),
		GetUserName(targetid),
		GetCharacterName(targetid),
		GetUserIp(targetid)
	);
	
	SendAdminMessage(C_LIGHTRED, g_small_string);
	
	PlayerBan(targetid, TYPE_BAN_USER, days, playerid, reason);
	
	printf("[cmd_aban]: Admin %s(%d)[%d] has been blocked %s[%d] (%d, %s)",
		GetPlayerCurrentName(playerid),
		GetUserId(playerid),
		playerid,
		GetUserName(targetid),
		targetid,
		GetAdminLevel(playerid),
		admin_data[playerid][a_ip]
		
	);
	
	return 1;
}

CMD:aunban(playerid, params[])
{
	if (!IsPlayerGameAdmin(playerid))
	{
		return 0;
	}
	
	if (GetAdminLevel(playerid) < ADMIN_NORMAL)
	{
		SendClientMessage(playerid, C_WHITE, PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /aunban [Nick_Name]");
		return 1;
	}
	
	format:g_string("UPDATE " #__BANS " SET b_active = 0 WHERE b_type = %i AND b_account_name = '%q' AND b_active = 1 LIMIT 1",
		TYPE_BAN_USER,
		params
	);
	
	mysql_tquery(db, g_string, "OnAdminAccountUnban", "is", playerid, params);
	return 1;
}

function OnAdminAccountUnban(playerid, name[])
{
	if (cache_affected_rows() == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный персонаж не заблокирован или Вы ввели неверное имя персонажа.");
		return 1;
	}

	format:g_small_string("" #ADMIN_MESSAGE " %s[%i] разблокировал аккаунт: %s.",
		GetPlayerCurrentName(playerid),
		playerid,
		name
	);
	
	SendAdminMessage(C_GRAY, g_small_string);
	return 1;
}

CMD:banip(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_NORMAL))
	{
		return 0;
	}
	
	new ip				[	MAX_PLAYER_IP	],
		reason 			[	32	];
	
	if (sscanf(params, "s[17]s[32]", ip, reason))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /banip [IP адрес] [причина]");
		return 1;
	}
	
	format:g_string("INSERT INTO " #__IPBANS " VALUES ('%q', %i, '%q', '%q')",
		ip,
		GetUserName(playerid),
		GetUserId(playerid),
		reason
	);
	
	mysql_tquery(db, g_string);
	
	format:g_small_string("" #ADMIN_MESSAGE " %s[%i] заблокировал IP адрес: %s. Причина: %s",
		GetUserName(playerid),
		playerid,
		ip,
		reason
	);
	
	SendAdminMessage(C_GRAY, g_small_string);
	
	return 1;
}

CMD:unbanip(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_NORMAL))
	{
		return 0;
	}
		
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /unbanip [IP адрес]");
		return 1;
	}
	
	new str_unbanip			[		32 		];
	
	if (GetAdminLevel(playerid) < ADMIN_SENIOR)
	{
		format:str_unbanip(" AND ib_admin_id = %i");
	}
	
	format:g_string("DELETE FROM " #__IPBANS " WHERE ib_user_ip = '%q'%s LIMIT 1",
		params,
		str_unbanip
	);
	
	mysql_tquery(db, g_string, "OnAdminUnbanIp", "is", playerid, params);
	return 1;
}

function OnAdminUnbanIp(playerid, ip[])
{
	if (!cache_affected_rows())
	{
		if (GetAdminLevel(playerid) < ADMIN_SENIOR)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Данный IP адрес заблокирован не Вами или Вы ввели неверный.");
		}
		else 
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Данный IP адрес не заблокирован или Вы ввели неверный.");
		}
		
		return 1;
	}
	
	format:g_small_string("" #ADMIN_MESSAGE " %s[%i] разблокировал IP адрес: %s.",
		GetPlayerCurrentName(playerid),
		playerid,
		ip
	);
	
	SendAdminMessage(C_GRAY, g_small_string);
	
	return 1;
}

CMD:ddropitem(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_NORMAL))
	{
		return 0;
	}
	
	if (isnull(params) || !IsInt(params))
	{	
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /ddropitem [радиус]");
		return 1;
	}
	
	new Float: radius = floatstr(params);
	
	for (new i; i < sizeof drop_data; i++)
	{
		if (!IsPlayerInRangeOfPoint(playerid, radius, 
		drop_data[i][drop_pos_x], 
		drop_data[i][drop_pos_y],
		drop_data[i][drop_pos_z]))
		{
			continue;
		}
		
		if (drop_data[i][drop_item_id] == 0)
		{
			continue;
		}
		
		InventoryTakeItem(INVALID_PLAYER_ID, i);
	}
	
	format:g_small_string("Admin %s(%i) has deleted dropped items in radius %0.1f.",
		GetUserName(playerid),
		playerid,
		radius
	);

	SendAdminLog(g_small_string);
	return 1;
}

/// Level: 4 (ADMIN_SENIOR)
CMD:setfraction(playerid, params[]) 
{	
	if (!CheckAdminAccess(playerid, ADMIN_SENIOR))
	{
		return 0;
	}
	
	if (GetPVarInt(playerid, "Admin:SetFraction"))
	{
		character_data[playerid][c_fraction_index] = 
		character_data[playerid][c_fraction_rank_index] = INVALID_PARAM;
		
		SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы убрали временную фракцию.");
		DeletePVar(playerid, "Admin:SetFraction");
		return 1;
	}
	
	ShowAdminFractionList(playerid, D_ADMIN + 53, false);
	return 1;
}

CMD:veh(playerid, params[])
{
    return cmd_vcreate(playerid, params);
}

CMD:vcreate(playerid, params[]) 
{	
	if (!CheckAdminAccess(playerid, ADMIN_SENIOR))
	{
		return 0;
	}
		
	new model,
		color1,
		color2;
		
 	if (sscanf(params, "iii", model, color1, color2))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /vcreate [модель] [цвет 1] [цвет 2]");
		return 1;
	}
	
	if (!(400 <= model <= 611))
	{
	    SendClientMessage(playerid, C_WHITE, !#ERROR " Модель создаваемого транспорта должна быть от 400 до 600.");
		return 1;
	}
	
	if (!(0 <= color1 <= 255))
	{
	    SendClientMessage(playerid, C_WHITE, !#ERROR " Цвет создаваемого транспорта должен быть от 0 до 255.");
		return 1;
	}
	
	if (!(0 <= color2 <= 255))
	{
	    SendClientMessage(playerid, C_WHITE, !#ERROR " Цвет создаваемого транспорта должен быть от 0 до 255.");
		return 1;
	}
	
	if (GetCharacterInt(playerid) != 0)
	{
	    SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете создать транспорт в интерьере.");
		return 1;
	}
	
	new Float:x,
	    Float:y,
	    Float:z,
		vehicleid;

	GetPlayerPos(playerid, x, y, z);

	vehicleid = CreateVehicle(model, x + 1.5, y + 1.5, z, 0.0, color1, color2, 60000);

	is_admin_vehicle{vehicleid} = true;
	
	format:g_small_string("Admin %s(%i) has created vehicle: %s - %i [ID:%i].",
		GetPlayerCurrentName(playerid),
		playerid,
		GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name),
		GetVehicleModel(vehicleid),
		vehicleid
	);

	SendAdminLog(g_small_string);
	
	return 1;
}

CMD:dveh(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_SENIOR))
	{
		return 0;
	}
	
	new vehicleid = GetPlayerVehicleID(playerid);
	
	if (vehicleid == 0)
	{
		if (sscanf(params, "i", vehicleid))
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /dveh [ID транспорта]");
			return 1;
		}

		if (!(0 < vehicleid <= GetVehiclePoolSize()))
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Вы указали несуществующий ID транспорта.");
			return 1;
		}
	}
	
	if (!is_admin_vehicle{vehicleid})
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете удалить транспорт созданный сервером.");
		return 1;
	}	
	
	DestroyVehicle(vehicleid);
	
	return 1;
}

CMD:dvehall(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_SENIOR))
	{
		return 0;
	}

	for (new i = 1, j = GetVehiclePoolSize(); i <= j; i++)
	{
		if (is_admin_vehicle{i})
		{
			DestroyVehicle(i);
		}
	}
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно удалили весь созданный транспорт.");
	return 1;
}

/// Level: 5 (ADMIN_LEAD)
CMD:setweather(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD))
	{
		return 0;
	}
		
	new weatherid,
		minutes;
	
	if (sscanf(params, "ii", weatherid, minutes))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /setweather [ID погоды] [длительность (минуты)]");
		return 1;
	}
	
	if (!(0 < minutes < (60 * 24)))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы указали неверную длительность. Минимум 1 минута, а максимум 1440.");
		return 1;
	}
	
	SetSVarInt("Weather:UpdateTime", 0);
	GenerateWeather(weatherid, minutes);
	return 1;
}

CMD:xyz(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD))
	{
		return 0;
	}
	
	new Float: x,
		Float: y,
		Float: z;
		
	if(sscanf(params, "p<,>fff", x, y, z))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /xyz [x, y, z]");
		return 1;
	}
	
	SetPlayerPos(playerid, x, y, z);
	return 1;
}

// Permissions
CMD:givemoney(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE, ap_property))
	{
		return 0;
	}
	
	new targetid,
		money;
	
	if (sscanf(params, "ui", targetid, money))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /givemoney [ID игрока] [сумма]");
		return 1;
	}
	
	if (!(0 <= money <= 1_000_000))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы ввели неверную сумму.");
		return 1;
	}
	
	GivePlayerCash(targetid, money);
	
	format:g_small_string(ADMIN_MESSAGE " %s[%d] выдал наличные %s[%d] - $%d.",
		GetUserName(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		targetid,
		money
	);

	SendAdminMessage(C_GRAY, g_small_string);
	return 1;
}


CMD:giveitem(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE, ap_property))
	{
		return 0;
	}
	
	new targetid = strval(params);
	
	if (isnull(params) && !IsInt(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /giveitem [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	SetPVarInt(playerid, "Admin:GiveItemTargetId", targetid);
	ShowInventoryItemList(playerid, ITEM_LIST_BEGIN, "admin_give_item");
	return 1;
}

function INV:admin_give_item(playerid, item_id, param_1, param_2)
{
	new targetid = GetPVarInt(playerid, "Admin:GiveItemTargetId"),
		itindex = GetItemIndexById(item_id);
	
	if (GiveInventoryItem(targetid, item_id, param_1, param_2) != INVALID_PARAM)
	{
		format:g_small_string(ADMIN_MESSAGE " %s[%d] выдал предмет %s[%d] - %s.",
			GetUserName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			targetid,
			item_list[itindex][it_name]
		);
	
		SendAdminMessage(C_GRAY, g_small_string);
	}
	else 
	{
		SendClientMessage(playerid, C_WHITE, !ERROR " Вы ввели неверный параметр или у игрока нет места в инвентаре.");
	}
	
	return 1;
}

CMD:mfraction(playerid)
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE, ap_manage_fraction))
	{
		return 0;
	}
	
	ShowAdminFractionList(playerid);
	return 1;
}

CMD:mcrime(playerid)
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE, ap_manage_crime))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 0;
	}
	
	ShowAdminCrimeList(playerid);
	return 1;
}

// ADMIN_LEAD > ap_developer
CMD:manticheat(playerid)
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 0;
	}
	
	ShowAntiCheatMenu(playerid, ITEM_LIST_BEGIN);
	return 1;
}

CMD:rlog(playerid)
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	ac_log = !ac_log;
	SendClientMessage(playerid, C_WHITE, ac_log ? (#SUCCESS " Вы включили лог входящих Raknet пакетов.") : (#SUCCESS " Вы отключили лог входящих Raknet пакетов."));
	return 1;
}

CMD:netstats(playerid) 
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	clean:<g_big_string>;
	GetNetworkStats(g_big_string, sizeof(g_big_string)); 
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "NetStats", g_big_string, "Закрыть", ""); 
	return 1; 
}

CMD:restart(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	new seconds,
	    timer = GetSVarInt("Server:Restart");
	
	sscanf(params, "I(0)", seconds);
	
	if (seconds == 0 && timer == 0)
	{
		ShowPlayerDialog(playerid, D_ADMIN + 22, DIALOG_STYLE_MSGBOX, " ", 
			"" #ERROR " Рестарта сервера\n\n\
			Внимание!\n\
			Вы действительно желаете сделать рестарт в данный момент?\n\n\
			" #cGRAY "Рестарт сервера можно сделать с задержкой, уведомив игроков.\n\
			Для этого используйте команду вида: /restart [задержка в секундах]\n\
			Для отмены введите повторно команду без параметров.",
			"Далее", "Отмена"
		);
		
		return 1;
	}
	
	if (!(0 <= seconds <= 60 * 30))
	{
		SendClientMessage( playerid, C_WHITE, !#ERROR " Вы указали неверное количество секунд. Минимальное - 0, а максимальное - 2400.");
		return 1;
	}
	
	if (seconds == 0 && timer != 0)
	{
		KillTimer(timer);
		DeleteSVar("Server:Restart");
		SendSplitMessageToAll(C_LIGHTRED, !"Технический рестарт был отменён.");
		SendClientMessage( playerid, C_WHITE, !#SUCCESS " Вы отменили рестарт сервера." );
	}
	else
	{
		timer = SetTimer("OnAdminServerRestart", (seconds * 1000), false);
		SetSVarInt("Server:Restart", timer);
		
		new str_time[16];
		
		if (seconds >= 60)
		{
			new minutes = floatround((seconds / 60), floatround_round);
			format:str_time("%i мин.", minutes);
		}
		else 
		{
			format:str_time("%i сек.", seconds);
		}
		
		format:g_small_string("Внимание! Через %s произойдет внеплановый технический рестарт сервера.",
			str_time
		);
		
		SendSplitMessageToAll(C_LIGHTRED, g_small_string);
	}
	
	return 1;
}

function OnAdminServerRestart()
{
	SendSplitMessageToAll(C_LIGHTRED, "Выполняется рестарт сервера...");
	foreach (new playerid : Player)
	{
		if (IsPlayerConnected(playerid))
		{
			Kick(playerid);
		}
	}
	
	GameModeExit();
	return 1;
}

CMD:kickall(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /kickall [Причина]");
		return 1;
	}
	
	format:g_small_string("Администратор %s[%d] отсоединил от сервера всех игроков. Причина: %s",
		GetUserName(playerid),
		playerid,
		params
	);
	
	SendSplitMessageToAll(C_LIGHTRED, g_small_string);
	
	foreach (new i : Player)
	{
		if (!IsPlayerGameAdmin(i))
		{
			KickWithDialog(i, playerid, params);
		}
	}
	
	return 1;
}

CMD:skick(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	new targetid;
	
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /skick [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerConnected(targetid) || playerid == targetid || IsPlayerDeveloper(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	format:g_small_string("Admin %s(%i) has quietly kicked %s(%i).",
		GetPlayerCurrentName(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		targetid
	);

	SendAdminLog(g_small_string);
	
	Kick(targetid);
	return 1;
}

// House System
CMD:addhouse(playerid)
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	ShowAdminHouseInteriors(playerid, D_ADMIN + 6);
	
	return 1;
}

CMD:edithouse(playerid, params[])
{
	new index;
	
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	if (isnull(params) || !IsInt(params))
	{
		return SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /edithouse [ID жилищного помещения]");
	}
	
	if ((index = GetHouseIndexById(strval(params))) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Неверный ID жилищного помещения.");
		return 1;
	}
	
	SetPVarInt(playerid, "Admin:HouseSelect", index);
	
	ShowAdminEditHouse(playerid);

	return 1;
}

CMD:delhouse(playerid, params[])
{	
	new id,
		index;
	
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	if (sscanf(params, "i", id))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /delhouse [ID жилищного помещения]");
		return 1;
	}
	
	if ((index = GetHouseIndexById(id)) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Неверный ID жилищного помещения.");
		return 1;
	}
	
	Destroy:house(index);
	
	if (IsHouseBought(index))
	{
		ResetHouseLodgers(index, false);
		ResetHouseInterior(index);
	}
	
	format:g_string("DELETE FROM " #__HOUSES " WHERE h_id = %i LIMIT 1", id);
	mysql_tquery(db, g_string);
	
	format:g_string("DELETE FROM " #__ROOMS " WHERE r_owner_type = %i AND r_owner_id = %i", TYPE_REN_HOUSE, id);
	mysql_tquery(db, g_string);
	
	Clear:house_data(index);
	return 1;
}

CMD:lasthouse(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	for (new i = sizeof house_data - 1; i; --i)
	{
		if (house_data[i][h_id] != 0)
		{
			pformat:("" #DEFAULT " Последний созданный дом: " #cPROJECT "#%i" #cWHITE ".", 
				house_data[i][h_id] 
			);
			
			psend:(playerid, C_WHITE);
			
			break;
		}
	}
	
	return 1;
}

// Hostel System
CMD:addhostel(playerid)
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	ShowAdminHostelInteriors(playerid, D_ADMIN + 13);
	return 1;
}

CMD:delhostel(playerid, params[])
{	
	new id,
		index;
	
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	if (sscanf(params, "i", id))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /delhostel [ID подъезда]");
		return 1;
	}
	
	if ((index = GetHostelIndexById(id)) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Неверный ID подъезда.");
		return 1;
	}
	
	Remove:hostel_delete(index, playerid);
	return 1;
}

// Garage System 
CMD:addgarage(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	new id,
		int_type;
		
	if (sscanf(params, "ii", id, int_type))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /addgarage [ID жилищного помещения] [тип гаража]");
		pformat:("" #DEFAULT " Интерьер от " #cPROJECT "1" #cWHITE " до " #cPROJECT "%d" #cWHITE ".", sizeof(hgarage_settings) - 1);
		psend:(playerid, C_WHITE);
		return 1;
	}
	
	if (!(0 < int_type < sizeof hgarage_settings))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы указали неверный интерьер гаража.");
		return 1;
	}
	
	new index;
	
	if ((index = GetHouseIndexById(id)) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы указали неверный ID жилищного помещения.");
		return 1;
	}
	
	new Float: x,
		Float: y,
		Float: z,
		Float: angle;
	
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);
	
	SetPVarFloat(playerid, "Admin:GaragePosX", x);
	SetPVarFloat(playerid, "Admin:GaragePosY", y);
	SetPVarFloat(playerid, "Admin:GaragePosZ", z);
	SetPVarFloat(playerid, "Admin:GaragePosAngle", angle);
	
	SetPVarInt(playerid, "Admin:GaragePosition", true);
	SetPVarInt(playerid, "Admin:GarageAdditionalPos", int_type == 3 ? true : false);
	SetPVarInt(playerid, "Admin:GarageSelect", index);
	SetPVarInt(playerid, "Admin:GarageInt", int_type);

	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Координаты входа в гараж для персонажа успешно сохранены.");
	SendClientMessage(playerid, C_WHITE, !#DEFAULT " Для того, чтобы указать позицию въезда транспорта, необходимо ввести команду: " #cPROJECT "/garageposition" #cWHITE ".");
	return 1;
}

CMD:garageposition(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	if (!GetPVarInt(playerid, "Admin:GaragePosition") 
	&& GetPVarInt(playerid, "Admin:GarageVehicle") != 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Гараж не создан. Для создания гаража используйте " #cPROJECT "/addgarage" #cWHITE ".");
		return 1;
	}
	
	new Float: x,
		Float: y,
		Float: z,
		Float: angle;
	
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);
	
	SetPVarInt(playerid, "Admin:GarageAccept", true);
	SetPVarInt(playerid, "Admin:GarageVehicle",
		CreateVehicle(560, x, y, z + 2.0, angle, 0, 0, -1)
	);
	
	PutPlayerInVehicle(playerid, GetPVarInt(playerid, "Admin:GarageVehicle"), 0);
	
	SendClientMessage(playerid, C_WHITE, !#DEFAULT " Укажите позицию выезжащего транспорта. Для подтверждения используйте " #cPROJECT "/acceptgarage" #cWHITE ".");
	return 1;
}

CMD:acceptgarage(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	if (!GetPVarInt(playerid, "Admin:GarageAccept"))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Не указана позиция выезжающего транспорта. Для указания используйте " #cPROJECT "/garageposition" #cWHITE ".");
		return 1;
	}
	
	new vehicleid = GetPVarInt(playerid, "Admin:GarageVehicle"),
		Float: veh_x,
		Float: veh_y,
		Float: veh_z,
		Float: veh_angle,
		index = GetPVarInt(playerid, "Admin:GarageSelect");
	
	GetVehiclePos(vehicleid, veh_x, veh_y, veh_z);
	GetVehicleZAngle(vehicleid, veh_angle);
		
	if (GetPVarInt(playerid, "Admin:GarageAdditionalPos"))
	{
		house_data[index][hg_addveh_pos][0] = veh_x;
		house_data[index][hg_addveh_pos][1] = veh_y;
		house_data[index][hg_addveh_pos][2] = veh_z;
		house_data[index][hg_addveh_pos][3] = veh_angle;
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Координаты сохренены. Укажите дополнительные координаты и введите снова " #cPROJECT "/acceptgarage" #cWHITE ".");
		DeletePVar(playerid, "Admin:GarageAdditionalPos");
	}
	else 
	{
		house_data[index][hg_int_type] = GetPVarInt(playerid, "Admin:GarageInt");
		house_data[index][hg_pos][0] = GetPVarFloat(playerid, "Admin:GaragePosX");
		house_data[index][hg_pos][1] = GetPVarFloat(playerid, "Admin:GaragePosY");
		house_data[index][hg_pos][2] = GetPVarFloat(playerid, "Admin:GaragePosZ");
		house_data[index][hg_pos][3] = GetPVarFloat(playerid, "Admin:GaragePosAngle");
		
		house_data[index][hg_veh_pos][0] = veh_x;
		house_data[index][hg_veh_pos][1] = veh_y;
		house_data[index][hg_veh_pos][2] = veh_z;
		house_data[index][hg_veh_pos][3] = veh_angle;
		
		Create:garage_data(index, playerid);
		
		DestroyVehicle(vehicleid);
		
		DeletePVar(playerid, "Admin:GaragePosition");
		DeletePVar(playerid, "Admin:GarageAccept");
		DeletePVar(playerid, "Admin:GarageSelect");
		DeletePVar(playerid, "Admin:GarageInt");
		DeletePVar(playerid, "Admin:GarageVehicle");
		DeletePVar(playerid, "Admin:GaragePosX");
		DeletePVar(playerid, "Admin:GaragePosY");
		DeletePVar(playerid, "Admin:GaragePosZ");
		DeletePVar(playerid, "Admin:GaragePosAngle");
		DeletePVar(playerid, "Admin:GarageAdditionalPos");
	}

	return 1;
}

CMD:delgarage(playerid, params[])
{
	new id,
		index;
	
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	if (sscanf(params, "i", id))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /delgarage [ID жилищного помещения]");
		return 1;
	}
	
	if ((index = GetHouseIndexById(id)) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Неверный ID жилищного помещения.");
		return 1;
	}
	
	Remove:garage_data(index, playerid);
	return 1;
}

// Premise
CMD:addpremise(playerid)
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	ShowAdminPremiseInteriors(playerid, D_ADMIN + 15);
	
	return 1;
}

CMD:editpremise(playerid, params[])
{
	new index;
	
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	if (isnull(params) || !IsInt(params))
	{
		return SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /editpremise[id помещения]");
	}
	
	if ((index = GetPremiseIndexById(strval(params))) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Неверный ID помещения.");
		return 1;
	}
	
	SetPVarInt(playerid, "Admin:PremiseSelect", index);
	
	ShowAdminEditPremise(playerid);

	return 1;
}

CMD:delpremise(playerid, params[])
{	
	new id,
		index;
	
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	if (sscanf(params, "i", id))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /delpremise [ID помещения]");
		return 1;
	}
	
	if ((index = GetPremiseIndexById(id)) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Неверный ID помещения.");
		return 1;
	}
	
	Destroy:premise(index);
	
	if (IsPremiseBought(index))
	{
		ResetPremiseInterior(index);
	}
	
	format:g_string("DELETE FROM " #__PREMISES " WHERE pr_id = %i LIMIT 1", id);
	mysql_tquery(db, g_string);
	
	format:g_string("DELETE FROM " #__ROOMS " WHERE r_owner_type = %i AND r_owner_id = %i", TYPE_REN_PREMISE, id);
	mysql_tquery(db, g_string);
	
	Clear:premise_data(index);
	return 1;
}

CMD:lastpremise(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	for (new i = sizeof premise_data - 1; i; --i)
	{
		if (premise_data[i][pr_id] != 0)
		{
			pformat:("" #DEFAULT " Последний созданное помещение: " #cPROJECT "#%i" #cWHITE ".", 
				premise_data[i][pr_id] 
			);
			
			psend:(playerid, C_WHITE);
			
			break;
		}
	}
	
	return 1;
}

CMD:resetcredit(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	new targetid;
	
	if (sscanf(params, "i", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /resetcredit [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	ResetPlayerCredit(targetid, true);
	
	pformat:("Администратор %s[%i] сбросил Вам кредит.",
		GetPlayerCurrentName(playerid),
		playerid
	);
	
	psend:(targetid, C_LIGHTRED);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно сбросили кредит игроку.");
	return 1;
}

CMD:getbuycar(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_JUNIOR))
	{
		return 0;
	}
	
	new targetid,
		status = INVALID_PARAM;
	
	if (sscanf(params, "i", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /getbuycar [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	format:g_small_string("" #cGRAY "Личный транспорт игрока не заспавнен.");
	
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		if (player_vehicle[targetid][pv_server_id][i] <= 0)
		{
			continue;
		}
		
		format:g_string("%s\n %s[%d]",
			g_string,
			GetVehicleInfo(player_vehicle[targetid][pv_model][i], v_name),
			player_vehicle[targetid][pv_server_id][i]
		);
		
		status++;
	}
	
	ShowPlayerDialog(playerid, D_ADMIN_GETBUYCAR, DIALOG_STYLE_LIST, character_data[targetid][c_rpname],
		(status > INVALID_PARAM) ? (g_string) : (g_small_string),
		"Выбрать", "Отмена"
	);
	
	if (status > INVALID_PARAM)
	{
		SetPVarInt(playerid, "AdminCmd:GetBuyCar", targetid);
	}
	else
	{
		SetPVarInt(playerid, "AdminCmd:GetBuyCar", INVALID_PARAM);
	}
	
	return 1;
}

CMD:mban(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_JUNIOR))
	{
		return 0;
	}
	
	new targetid,
		minutes,
		reason				[32];
	
	if (sscanf(params, "iis[32]", targetid, minutes, reason))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /mban [ID игрока] [минуты " #cGRAY "(макс. 1440 мин.)" #cWHITE "] [причина]");
		return 1;
	}
	
	if (!IsPlayerRegister(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок незарегистрирован и был заблокирован серверной блокировкой.");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || targetid == playerid || IsPlayerDeveloper(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (!(1 <= minutes <= 1440))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Количество минут может быть от 1 до 1440.");
		return 1;
	}
	else 
	{
		format:g_small_string("Администратор %s[%i] заблокировал персонажа %s на %i минут. Причина: %s",
			GetUserName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			minutes,
			reason
		);
		
		format:g_string("(( Администратор %s[%i] заблокировал персонажа %s на %i минут. Причина: %s ))",
			GetUserName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			minutes,
			reason
		);
		
		minutes = gettime() + (60 * minutes);
	}
	
	SendGlobalAdminMessage(g_small_string, playerid, g_string);
	
	format:g_small_string(#ADMIN_MESSAGE " ID: %i | Имя: %s(%s) | IP адрес: %s", 
		GetUserId(targetid),
		GetUserName(targetid),
		GetCharacterName(targetid),
		GetUserIp(targetid)
	);
	
	SendAdminMessage(C_LIGHTRED, g_small_string);
	
	PlayerBan(targetid, TYPE_BAN_CHARACTER, minutes, playerid, reason);
	
	printf("[cmd_mban]: Admin %s(%d)[%d] has been blocked %s[%d] for %d minutes (%d, %s)",
		GetPlayerCurrentName(playerid),
		GetUserId(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		targetid,
		minutes,
		GetAdminLevel(playerid),
		admin_data[playerid][a_ip]
		
	);
	return 1;
}

CMD:amban(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_NORMAL))
	{
		return 0;
	}
	
	new targetid,
		minutes,
		reason				[32];
	
	if (sscanf(params, "iis[32]", targetid, minutes, reason))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /amban [ID игрока] [минуты " #cGRAY "(макс. 1440 мин.)" #cWHITE "] [причина]");
		return 1;
	}
	
	if (!IsPlayerRegister(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный аккаунт незарегистрирован и был заблокирован серверной блокировкой.");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || targetid == playerid || IsPlayerDeveloper(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (!(1 <= minutes <= 1440))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Количество минут может быть от 1 до 1440.");
		return 1;
	}
	else 
	{
		format:g_small_string("Администратор %s[%i] заблокировал аккаунт %s на %i минут. Причина: %s",
			GetUserName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			minutes,
			reason
		);
		
		format:g_string("(( Администратор %s[%i] заблокировал аккаунт %s на %i минут. Причина: %s ))",
			GetUserName(playerid),
			playerid,
			GetPlayerCurrentName(targetid),
			minutes,
			reason
		);
		
		minutes = gettime() + (60 * minutes);
	}
	
	SendGlobalAdminMessage(g_small_string, playerid, g_string);
	
	format:g_small_string("" #ADMIN_MESSAGE " ID: %i | Имя: %s(%s) | IP адрес: %s", 
		GetUserId(targetid),
		GetUserName(targetid),
		GetCharacterName(targetid),
		GetUserIp(targetid)
	);
	
	SendAdminMessage(C_LIGHTRED, g_small_string);
	
	PlayerBan(targetid, TYPE_BAN_USER, minutes, playerid, reason);
	
	printf("[cmd_amban]: Admin %s(%d)[%d] has been blocked %s[%d] for %d minutes (%d, %s)",
		GetPlayerCurrentName(playerid),
		GetUserId(playerid),
		playerid,
		GetUserName(targetid),
		targetid,
		minutes,
		GetAdminLevel(playerid),
		admin_data[playerid][a_ip]
	);
	return 1;
}

CMD:dislog(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}
	
	ShowAdminDisconnectionLog(playerid);
	
	return 1;
}

CMD:deathlog(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 0;
	}

	ShowAdminDeathLog(playerid);
	
	return 1;
}

CMD:ahlock(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_SENIOR))
	{
		return 0;
	}
	
	new server_tick = GetTickCount();
	
	if (GetPVarInt(playerid, "House:LockTime") > server_tick)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
		return 1;
	}
	
	new index = GetHouseAroundOfPlayer(playerid);
			
	if (index == INVALID_PARAM)
	{
		pformat:("" #ERROR " Чтобы использовать встаньте возле входа в дом.");
		psend:(playerid, C_WHITE);
		return 1;
	}
	
	house_data[index][h_lock] = !house_data[index][h_lock];
	GameTextForPlayer(playerid, (house_data[index][h_lock]) ? ("~r~ADM-LOCKED") : ("~g~ADM-UNLOCKED"), 2000, 4);
	Update:house_int(index, "h_lock", house_data[index][h_lock]);
	
	SetPVarInt(playerid, "House:LockTime", server_tick + 1000);
	
	return 1;
}

CMD:aprlock(playerid, params[])
{	
	if (!CheckAdminAccess(playerid, ADMIN_SENIOR))
	{
		return 0;
	}
	
	new server_tick = GetTickCount();
	
	if (GetPVarInt(playerid, "Premise:LockTime") > server_tick)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
		return 1;
	}

	new index = GetPremiseAroundOfPlayer(playerid, false);
		
	if (index == INVALID_PARAM)
	{
		pformat:("" #ERROR " Чтобы использовать встаньте возле входа в бизнес.");
		psend:(playerid, C_WHITE);
		return 1;
	}
	
	premise_data[index][pr_lock] = !premise_data[index][pr_lock];
	GameTextForPlayer(playerid, (premise_data[index][pr_lock]) ? ("~r~ADM-LOCKED") : ("~g~ADM-UNLOCKED"), 2000, 4);
	Update:premise_int(index, "pr_lock", premise_data[index][pr_lock]);
	
	SetPVarInt(playerid, "Premise:LockTime", server_tick + 1000);
	
	return 1;
}

CMD:aclock(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_SENIOR))
	{
		return 0;
	}

	new vehicleid = GetVehicleAroundOfPlayer(playerid);
		
	if (!vehicleid)
	{
		pformat:("" #ERROR " Чтобы использовать встаньте возле транспортного средства игрока.");
		psend:(playerid, C_WHITE);
		return 1;
	}
	
	CheckVehicleLock(playerid, vehicleid);
	Update:vehicle_data(vehicleid, playerid);
	
	return 1;
}

CMD:auncuff(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_NORMAL))
	{
		return 0;
	}
	
	new targetid;
	
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /auncuff [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (GetPVarInt(targetid, "Player:Follow") != INVALID_PLAYER_ID) 
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Нельзя снять наручники с этого игрока.");
		return 1;
	}
	
	if (!GetPVarInt(targetid, "Player:Cuff")) 
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок уже не в наручниках.");
		return 1;
	}
	
	RemovePlayerAttachedObject(targetid, SLOT_ATTACH_TEMP);
	SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
	
	DeletePVar(targetid, "Player:Cuff");
	
	pformat:(#cLIGHTRED "Администратор %s снял с Вас наручники.", 
		GetUserName(playerid)
	);
	
	psend:(targetid, C_WHITE);
	
	format:g_small_string("Admin %s(%i) has uncuffed %s(%i).",
		GetUserName(playerid),
		playerid,
		GetPlayerCurrentName(targetid),
		targetid
	);

	SendAdminLog(g_small_string);
	
	return 1;
}