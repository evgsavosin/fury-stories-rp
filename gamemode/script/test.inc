/*
*	FOR TESTING
*/

// Important
Test_OnGameModeInit()
{
	
}

function Test_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if (GetPVarInt(playerid, "Admin:MapTeleportIgnore"))
	{
		return 1;
	}
	
	SetPlayerPos(playerid, fX, fY, fZ + 0.5);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);

	return 1;
}

// AntiCheat test
CMD:attach_trailer(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid),
		trailerid = strval(params);
	
	
	AttachTrailerToVehicle(trailerid, vehicleid);
	return 1;
}

CMD:deattach_trailer(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid);
	
	DetachTrailerFromVehicle(vehicleid);
	return 1;
}

CMD:attachreset(playerid)
{
	for (new i; i < MAX_ATTACH_SLOTS; i++)
	{
		ac_player_data[playerid][ac_attach_id][i] = INVALID_OBJECT_ID;
	}
	
	return 1;
}

CMD:aceject(playerid, params[])
{
	RemovePlayerFromVehicle(playerid);
	return 1;
}

CMD:acspec_on(playerid, params[])
{
	TogglePlayerSpectating(playerid, 1);
	return 1;
}

CMD:acspec_off(playerid, params[])
{
	TogglePlayerSpectating(playerid, 0);
	return 1;
}

CMD:acpos(playerid, params[])
{
	SetPlayerPos(playerid, 0.0, 0.0, 0.0);
	return 1;
}

CMD:ac_count(playerid)
{
	clean:<g_string>;
	for (new i; i < MAX_ANTICHEAT_LIST; i++)
	{
		format:g_string("%s%i - %i\n",
			g_string,
			i,
			ac_player_data[playerid][ac_detect_count][i]
		);
	}
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", g_string, "Закрыть", "");
	return 1;
}

CMD:giveweapon(playerid, params[])
{
	new weaponid,
		ammo;
		
	if (sscanf(params, "dd", weaponid, ammo))
	{
		return 1;
	}
	
	GivePlayerWeapon(playerid, weaponid, ammo);
	return 1;
}

CMD:resetweapon(playerid)
{
	ResetPlayerWeapons(playerid);
	return 1;
}

CMD:myweapon(playerid)
{

	clean:<g_string>;
	for (new i; i < MAX_WEAPON_SLOTS; i++)
	{
		format:g_string("%s[%i]%i - %i\n",
			g_string,
			i,
			ac_player_data[playerid][ac_weapon_id][i],
			ac_player_data[playerid][ac_ammo][i]
		);
	}
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", g_string, "Закрыть", "");
	return 1;
}

// For local

CMD:gotocar(playerid, params[])
{
	new vehicleid = strval(params),
		Float: x,
		Float: y,
		Float: z;
		
	GetVehiclePos(vehicleid, x, y, z);
	SetPlayerPos(playerid, x, y, z);
	
	return 1;
}

CMD:go(playerid, params[])
{
	if(sscanf(params, "u", params[0]))
		return SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /go [ID игрока] ");
		
	new Float:x,
		Float:y,
		Float:z;

	GetPlayerPos(params[0], x, y, z);
	
	if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER) 
	{
		new Float:vehicle_x,
		    Float:vehicle_y,
		    Float:vehicle_z;
		    
		GetVehicleVelocity(GetPlayerVehicleID(playerid), vehicle_x, vehicle_y, vehicle_z);
		SetVehiclePos(GetPlayerVehicleID(playerid), x + 1.0, y + 1.0, z);
		SetVehicleVelocity(GetPlayerVehicleID(playerid), vehicle_x, vehicle_y, vehicle_z);
	} 
	else 
	{
		SetPlayerPos(playerid, x + 1.0, y + 1.0, z);
	}
	
	SetPlayerInterior(playerid, GetPlayerInterior(params[0]));
    SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(params[0]));

	return 1;
}

CMD:sel(playerid)
{
	SelectObject(playerid);
	return 1;
}

// Other


/*CMD:debug_select(playerid)
{
	new slot;
		
	strglobalclear();
	
	if((slot = GetPVarInt(playerid, "Inventory:Select")))
	{
		format:g_small_string("inv_item_id = %i\n", inv_data[playerid][slot][inv_item_id]);
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("inv_use_slot = %i\n", inv_data[playerid][slot][inv_use_slot]);
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("inv_param_1 = %i\n", inv_data[playerid][slot][inv_param_1]);
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("inv_param_2 = %i\n", inv_data[playerid][slot][inv_param_2]);
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("inv_use_attach = %i\n", inv_data[playerid][slot][inv_use_attach]);
		strcat(g_big_string, g_small_string);
		
		ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, "Debug", g_big_string, "Close", "");
	}
	
	return 1;
}*/

CMD:getworld(playerid)
{
	pformat:("World: %d", GetPlayerVirtualWorld(playerid));
	psend:(playerid, C_WHITE);
	return 1;
}

CMD:getint(playerid)
{
	pformat:("Interior: %d", GetPlayerInterior(playerid));
	psend:(playerid, C_WHITE);
	return 1;
}

CMD:world(playerid, params[])
{
	SetPlayerVirtualWorld(playerid, strval(params));
	return 1;
}

CMD:int(playerid, params[])
{
	SetPlayerInterior(playerid, strval(params));
	return 1;
}

// Count object
CMD:count_object(playerid)
{
	new timer = GetPVarInt(playerid, "Timer:CountObject");
	
	if(timer == 0)
	{
		SetPVarInt(playerid, "Timer:CountObject", SetTimerEx("OnCheckCountObject", 1000, 1, "i", playerid));
	}
	else 
	{
		KillTimer(timer);
	}
	
	return 1;
}

function OnCheckCountObject(playerid)
{
	new string	[	128	];
	
	format:string("%i", Streamer_CountVisibleItems(playerid, STREAMER_TYPE_OBJECT));
	GameTextForPlayer(playerid, string, 1000, 4);
	return 1;
}

CMD:item(playerid, params[])
{
	if(sscanf(params, "ddd", params[0], params[1], params[2]))
	{
		return SendClientMessage(playerid, -1, "Ошибка - /item [id item] [param (for bag 0)] [additional(for phone)]");
	}
	
	if (GiveInventoryItem(playerid, params[0], params[1], params[2]) != INVALID_PARAM)
	{
		SendClientMessage(playerid, -1, "Предмет выдан");
	}
	else 
	{
		SendClientMessage(playerid, -1, "Ошибка");
	}
	
	return 1;
}

CMD:item_list(playerid, params[])
{
	clean:<g_big_string>;
	for (new i; i < sizeof item_list; i++)
	{
		format:g_big_string("%s%s(%i)\n", g_big_string, item_list[i][it_name], item_list[i][it_id]);
	}
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_LIST, " ", g_big_string, "Закрыть", "");
	return 1;
}

// =========================================================================================

CMD:setskin(playerid, params[])
{
	new skinid;
	
	if(sscanf(params, "i", skinid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /setskin [скин (1-311)]");
		return 1;
	}
	
	if (!(0 < skinid <= 311))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы ввели неверный ID скина.");
		return 1;
	}
	
	character_data[playerid][c_skin] = skinid;
	SetPlayerSkin(playerid, skinid);
	Update:character_int(playerid, "c_skin", skinid);

	pformat:( #DEFAULT " Вы успешно изменили скин на: %i", skinid);
	psend:(playerid, C_WHITE);
	return 1;
}

CMD:setmoney(playerid, params[])
{
	new money;
	
	if(sscanf(params, "i", money))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /givemoney [сумма]");
		return 1;
	}
	
	if (!(0 <= money <= 1_000_000))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы ввели неверную сумму.");
		return 1;
	}
	
	GivePlayerCash(playerid, money);
	return 1;
}

CMD:resetmoney(playerid)
{
	SetPlayerCash(playerid, 0);
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно обнулили средства.");
	return 1;
}

// =========================================================================================

CMD:createuser(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	new name		[	MAX_PLAYER_NAME		],
		password	[	MAX_PLAYER_PASSWORD	];
	
	if(sscanf(params, "s[24]s[32]", name, password))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /createuser [имя аккаунта] [пароль]");
		return 1;
	}
	
	format:g_string(
		"INSERT INTO " #__USERS " \
		(u_name, u_password, u_register_date) \
		VALUES \
		('%q', " #__HASH_METHOD ", NOW())",
		name,
		password
	);
	
	mysql_tquery(db, g_string, "OnAdminCreateAccount", "iss", playerid, name, password);
	
	return 1;
}

function OnAdminCreateAccount(playerid, name[], password[])
{
	pformat:("" #SUCCESS " Аккаунт %s (Пароль: %s) создан с ID: " #cPROJECT "%i" #cWHITE ".", name, password, cache_insert_id());
	psend:(playerid, C_WHITE);
	
	format:g_string(
		"INSERT INTO " #__USETTINGS " \
		(set_user_id) \
		VALUES \
		(%i)",
		cache_insert_id()
	);
	
	mysql_tquery(db, g_string);

	format:g_small_string("%i %s", cache_insert_id(), name);
	cmd_createcharacter(playerid, g_small_string);
	return 1;
}

CMD:createcharacter(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	new userid,
		name	[	MAX_PLAYER_NAME	];
	
	if(sscanf(params, "is[24]", userid, name))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /createcharacter [ID аккаунта] [имя персонажа]");
		return 1;
	}
	
	format:g_string(
		"INSERT INTO " #__CHARACTERS " \
		(c_user_id, c_name, c_status, c_sex, c_register_date) \
		VALUES \
		(%i, '%q', 1, 0, NOW())",
		userid,
		name
	);
	
	mysql_tquery(db, g_string, "OnAdminCreateCharacter", "i", playerid);
	return 1;
}

function OnAdminCreateCharacter(playerid)
{
	pformat:("" #SUCCESS " Персонаж создан с ID: " #cPROJECT "%i" #cWHITE ".", cache_insert_id());
	psend:(playerid, C_WHITE);
	
	format:g_string(
		"INSERT INTO " #__CSETTINGS " \
		(set_character_id) \
		VALUES \
		(%i)",
		cache_insert_id()
	);
	
	mysql_tquery(db, g_string);
	return 1;
}

CMD:setadmin(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_LEAD, ap_developer))
	{
		return 0;
	}
	
	new userid,
		level;
	
	if(sscanf(params, "ii", userid, level))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /setadmin [ID аккаунта] [уровень]");
		return 1;
	}
	
	if (!(0 <= level <= 5))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Уровень может быть от 0 до 5.");
		return 1;
	}
	
	if (level == 0)
	{
		format:g_string("DELETE FROM " #__ADMINS " WHERE a_user_id = %i",
			userid
		);
		
		foreach (new i : Player)
		{
			if (!IsPlayerLogged(i))
			{
				continue;
			}
			
			if (user_data[i][u_id] == userid)
			{
				Clear:admin_data(i);
			}
		}
		
		SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы успешно сняли админку.");
	}
	else 
	{
		format:g_string("INSERT INTO " #__ADMINS " \
			(a_user_id, a_level, ap_developer, ap_manage_admins) \
			VALUES \
			(%i, %i, 1, 1)",
			userid,
			level
		);
		
		SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы успешно выдали админку.");
	}
	
	mysql_tquery(db, g_string);
	
	return 1;
}

// =========================================================================================

CMD:sethouserent(playerid, params[])
{
	new index,
		id,
		seconds;
	
	if(sscanf(params, "ii", id, seconds))
	{
		return 1;
	}
	
	if(!(index = GetHouseIndexById(id)))
	{
		SendClientMessage(playerid, C_WHITE, "Неверный ид дома");
		return 1;
	}
	
	house_data[index][h_time] = gettime() + seconds;
	Update:house_int(index, "h_time", house_data[index][h_time]);
	SendClientMessage(playerid, C_WHITE, "Обновили дату аренды дома");
	return 1;
}

CMD:setpremiserent(playerid, params[])
{
	new index,
		id,
		seconds;
	
	if(sscanf(params, "ii", id, seconds))
	{
		return 1;
	}
	
	if(!(index = GetPremiseIndexById(id)))
	{
		SendClientMessage(playerid, C_WHITE, "Неверный ид помещения");
		return 1;
	}
	
	premise_data[index][pr_time] = gettime() + seconds;
	Update:premise_int(index, "pr_time", premise_data[index][pr_time]);
	SendClientMessage(playerid, C_WHITE, "Обновили дату аренды помещения");
	return 1;
}

// Credit
CMD:credit_check(playerid)
{
	Check:credit(playerid);
	return 1;
}

CMD:credit_givetime(playerid, params[])
{
	new time;
	
	if(sscanf(params, "i", time))
	{
		return 1;
	}
	
	credit_data[playerid][credit_give_time] = time;
	Update:credit_data(playerid);
	return 1;
}

// =========================================================================================

// =========================================================================================
CMD:start_pos(playerid)
{
	new Float: x,
		Float: y,
		Float: z;
	
	GetPlayerPos(playerid, x, y, z);
	
	SetPVarFloat(playerid, "X", x);
	SetPVarFloat(playerid, "Y", y);
	SetPVarFloat(playerid, "Z", z);
	return 1;
}

CMD:end_pos(playerid)
{
	new Float: x,
		Float: y,
		Float: z;
	
	GetPlayerPos(playerid, x, y, z);
	
	new Float: distance = GetDistanceBetweenPoints(
		GetPVarFloat(playerid, "X"), 
		GetPVarFloat(playerid, "Y"), 
		GetPVarFloat(playerid, "Z"), 
		x, 
		y, 
		z
	);
	
	pformat:("Distance: %0.2f", distance);
	psend:(playerid, C_WHITE);
	return 1;
}

// =========================================================================================

DialogCreate:test(playerid)
{
	Dialog_Open(playerid, Dialog:test, DIALOG_STYLE_MSGBOX,
	            "Hello",
	            "Are you ok?",
	            "Yes", "No");
}


DialogCreate:test2(playerid)
{
	Dialog_Open(playerid, Dialog:test2, DIALOG_STYLE_MSGBOX,
	            "Hello",
	            "Are you ok?2222",
	            "Yes", "No");
}

DialogResponse:test(playerid, response, listitem, inputtext[])
{
	if (!response) 
    {
		SendClientMessage(playerid, -1, "This club only for OK guys!");
		Dialog_Show(playerid, Dialog:test);
		return 1;
	}

	SendClientMessage(playerid, -1, "Welcome to the club");
    Dialog_Show(playerid, Dialog:test2);
	return 1;
}

DialogResponse:test2(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        return 1;
    }

    SendClientMessage(playerid, -1, "okk!!");
    return 1;
}

CMD:show_test(playerid)
{
    Dialog_Show(playerid, Dialog:test);
    return 1;
}