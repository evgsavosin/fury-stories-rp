/*!
	@brief Комманды
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
*/

// Chat - Commands
CMD:rep(playerid, params[])
{
	cmd_report(playerid, params);
	return 1;
}

CMD:id(playerid, params[])
{
	new targetid = INVALID_PARAM,
		server_tick = GetTickCount();
	
	if (GetPVarInt(playerid, "Cmd:Id") > server_tick)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
		return 1;
	}
	
	if (sscanf(params, "d", targetid))
	{
		clean:<g_small_string>;

		if (sscanf(params, "s[sizeof g_small_string]", g_small_string))
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /id [ID / Имя игрока]");
			return 1;
		}
	}

	if (targetid == INVALID_PARAM)
	{
		for (new i, j = GetPlayerPoolSize(); i <= j; i++)
		{
			if (strlen(GetCharacterName(i)) < 1)
			{
				continue;
			}

			clean:<g_string>;
			strcat(g_string, GetCharacterName(i));
			
			if (strfind(g_string, g_small_string, true) == INVALID_PARAM)
			{
				continue;
			}
			else
			{
				targetid = i;
				break;
			}
		}
	}
	
	if (!IsPlayerLoggedForCMD(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " По Вашему запросу ничего не найдено.");
		return 1;
	}
	
	pformat:("" #SUCCESS " %s - %s[%i].",
		GetUserName(targetid),
		GetCharacterName(targetid),
		targetid
	);
	
	psend:(playerid, C_WHITE);

	SetPVarInt(playerid, "Cmd:Id", server_tick + 2000);
	
	return 1;
}

CMD:afk(playerid, params[])
{
	new targetid;
	
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /afk [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLoggedForCMD(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (!IsPlayerAfk(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Данный игрок не находится в AFK.");
		return 1;
	}
	
	pformat:("" #SUCCESS " %s[%i] - %i секунд.",
		GetPlayerCurrentName(targetid),
		targetid,
		GetPlayerAfk(targetid)
	);
	
	psend:(playerid, C_WHITE);
	
	return 1;
}

CMD:report(playerid, params[]) 
{
	new server_tick = GetTickCount();
	
	if (GetPVarInt(playerid, "CmdTime:Report") > server_tick)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
		return 1;
	}
	
	if (isnull(params)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /report [Текст]");
		return 1;
	}
	
	SendMessageToReport(playerid, params);
	
	SetPVarInt(playerid, "CmdTime:Report", server_tick + 5000);
	
	return 1;
}

CMD:ask(playerid, params[])
{
	new server_tick = GetTickCount();
	
	if (GetPVarInt(playerid, "CmdTime:Report") > server_tick)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
		return 0;
	}
	
	if (isnull(params)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /ask [Текст]");
		return 1;
	}
	
	SendMessageToAsk(playerid, params);
	
	SetPVarInt(playerid, "CmdTime:Report", server_tick + 5000);
	
	return 1;
}

CMD:b(playerid, params[])
{
	if (GetUserSettings(playerid, SET_B_MESSAGE) == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас отключен OOC чат, но Вы можете использовать /ab.");
		return 1;
	}
	
	if (IsPlayerMuted(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_MUTED);
		return 1;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /b [Текст]");
		return 1;
	}
	
	if (IsAdminLogged(playerid))
	{
		format:g_small_string("(( Администратор %s[%i]: %s ))", 
			GetPlayerCurrentName(playerid), 
			playerid,
			params
		);
		
		ProxDetector(20.0, playerid, g_small_string, COLOR_FADE1, COLOR_FADE1, COLOR_FADE1, COLOR_FADE2, COLOR_FADE2);
	}
	else 
	{
		format:g_small_string("(( %s[%i]: %s ))", 
			GetPlayerCurrentName(playerid), 
			playerid,
			params
		);
		
		ProxDetector(15.0, playerid, g_small_string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, _, _, _, true);
	}
	
	return 1;
}

CMD:boff(playerid, params[])
{
	if (GetUserSettings(playerid, SET_B_MESSAGE) == 1)
	{
		SetUserSettings(playerid, SET_B_MESSAGE, 0);
		pformat:("" #SUCCESS " Вы успешно отключили ООС чат.");
		psend:(playerid, C_WHITE);

		ApplyUserSettings(playerid);
		Update:user_settings(playerid);
	}

	return 1;
}

CMD:bon(playerid, params[])
{
	if (GetUserSettings(playerid, SET_B_MESSAGE) == 0)
	{
		SetUserSettings(playerid, SET_B_MESSAGE, 1);
		pformat:("" #SUCCESS " Вы успешно включили ООС чат.");
		psend:(playerid, C_WHITE);

		ApplyUserSettings(playerid);
		Update:user_settings(playerid);
	}

	return 1;
}

CMD:ab(playerid, params[])
{	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /ab [Текст]");
		return 1;
	}
	
	pformat:("> (( %s[%i]: %s ))", 
		GetPlayerCurrentName(playerid),
		playerid,
		params
	);
	
	psend:(playerid, C_WHITE);
	
	SetPlayerChatBubble(playerid, g_small_string, COLOR_FADE2, 15.0, 5500);
	
	return 1;
}

CMD:pm(playerid, params[])
{
	new targetid,
		text		[	128		];
	
	if (GetUserSettings(playerid, SET_PM_MESSAGE) == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас отключены личные сообщения.");
		return 1;
	}
	
	if (IsPlayerMuted(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_MUTED);
		return 1;
	}
	
	if (sscanf(params, "us[128]", targetid, text))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /pm [ID игрока] [Текст]");
		return 1;
	}
	
	if (!IsPlayerLoggedForCMD(targetid) || targetid == playerid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (GetUserSettings(targetid, SET_PM_MESSAGE) == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У данного игрока отключены личные сообщения.");
		return 1;
	}
	
	format:g_small_string("PM > К %s[%i]: %s", 
		GetPlayerCurrentName(targetid), 
		targetid,
		text
	);
	
	SendSplitMessage(playerid, C_GOLD, g_small_string);
	
	format:g_small_string("PM > От %s[%i]: %s", 
		GetPlayerCurrentName(playerid), 
		playerid,
		text
	);
	
	SendSplitMessage(targetid, C_GOLD, g_small_string);
	
	return 1;
}

CMD:pmoff(playerid, params[])
{
	if (GetUserSettings(playerid, SET_PM_MESSAGE) == 1)
	{
		SetUserSettings(playerid, SET_PM_MESSAGE, 0);
		pformat:("" #SUCCESS " Вы успешно отключили личные сообщения.");
		psend:(playerid, C_WHITE);

		ApplyUserSettings(playerid);
		Update:user_settings(playerid);
	}

	return 1;
}

CMD:pmon(playerid, params[])
{
	if (GetUserSettings(playerid, SET_PM_MESSAGE) == 0)
	{
		SetUserSettings(playerid, SET_PM_MESSAGE, 1);
		pformat:("" #SUCCESS " Вы успешно включили личные сообщения.");
		psend:(playerid, C_WHITE);

		ApplyUserSettings(playerid);
		Update:user_settings(playerid);
	}

	return 1;
}

CMD:me(playerid, params[])
{	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /me [Текст]");
		return 1;
	}
	
	SendRPMessage(ACTION_ME, playerid, params);
	
	return 1;
}

CMD:do(playerid, params[])
{
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /do [Текст]");
		return 1;
	}
	
	SendRPMessage(ACTION_DO, playerid, params);
	
	return 1;
}

CMD:coin(playerid)
{	
	format:g_small_string("(( %s[%i] подкидывает монетку, выпадает %s. ))", 
		GetPlayerCurrentName(playerid), 
		playerid,
		random(2) == 1 ? ("орёл") : ("решка")
	);
	
	ProxDetector(15.0, playerid, g_small_string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, _, _, _, true);
	return 1;
}

CMD:s(playerid, params[])
{
	new character_death = GetCharacterDeath(playerid);
	if (character_death == TYPE_DEATH_DIED)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_DIED);
		return 1;
	}
		
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /s [Текст]");
		return 1;
	}
	
	new house_index = GetHouseAroundOfPlayer(playerid, 6.0, false);
	if (house_index != INVALID_PARAM)
	{
		format:g_small_string(#STREET_MESSAGE " %s кричит: %s",
			GetPlayerCurrentName(playerid), 
			params
		);
		
		SendHouseMessage(house_index, COLOR_FADE2, g_small_string, 20.0);
	}
	
	format:g_small_string("%s кричит: %s", 
		GetPlayerCurrentName(playerid), 
		params
	);
	
	ProxDetector(35.0, playerid, g_small_string, C_WHITE, COLOR_FADE1, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3); 
	
	return 1;
}

CMD:low(playerid, params[])
{
	return cmd_l(playerid, params);
}

CMD:l(playerid, params[])
{
	new character_death = GetCharacterDeath(playerid);
	if (character_death == TYPE_DEATH_DIED)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_DIED);
		return 1;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /l [Текст]");
		return 1;
	}
	
	format:g_small_string("%s говорит тихо: %s", 
		GetPlayerCurrentName(playerid), 
		params
	);
	
	ProxDetector(5.0, playerid, g_small_string, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE4, COLOR_FADE4); 
	
	return 1;
}

CMD:w(playerid, params[])
{
	new character_death = GetCharacterDeath(playerid);
	if (character_death == TYPE_DEATH_DIED)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_DIED);
		return 1;
	}
	
	new targetid,
		text			[	128		];
		
	if (sscanf(params, "us[128]", targetid, text) 
	|| isnull(text))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /w [ID игрока] [Текст]");
		return 1;
	}
	
	if (!IsPlayerLoggedForCMD(targetid) 
	|| !IsPlayerAroundOfPlayer(playerid, targetid) 
	|| playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	format:g_small_string("Вы шепчете %s: %s", 
		GetPlayerCurrentName(targetid), 
		text
	);
	
	SendSplitMessage(playerid, COLOR_FADE1, g_small_string);
	
	format:g_small_string("%s шепчет Вам: %s", 
		GetPlayerCurrentName(playerid), 
		text
	);
	
	SendSplitMessage(targetid, COLOR_FADE2, g_small_string); 
	
	SendRPMessage(ACTION_AME, playerid, "Шепчет");
	return 1;
}

CMD:ame(playerid, params[])
{	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /ame [Текст]");
		return 1;
	}
	
	pformat:("> %s %s", 
		GetPlayerCurrentName(playerid),
		params
	);
	
	psend:(playerid, C_PURPLE);
	
	params[0] = toupper(params[0]);
	SendRPMessage(ACTION_AME, playerid, params);
	
	return 1;
}

CMD:setdesc(playerid, params[])
{
	if (!isnull(character_data[playerid][c_desc]))
	{
		clean:<character_data[playerid][c_desc]>;
		Update:character_string(playerid, "c_desc", "");
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы убрали прошлое описание Вашего персонажа.");
		return 1;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /setdesc [описание персонажа]");
		return 1;
	}
	
	strcat(character_data[playerid][c_desc], params, MAX_PLAYER_DESC);
	SetCharacterDescCreatedTime(playerid, gettime());
	
	Update:character_string(playerid, "c_desc", params);
	Update:character_string(playerid, "c_desc_created_date", "NOW()", false);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно установили описание персонажа. " #cGRAY "(/setdesc - убрать, /desc - для просмотра)");
	
	format:g_small_string(ADMIN_MESSAGE " %s[%d] установил описание персонажа (/desc): %s",
		GetPlayerCurrentName(playerid),
		playerid,
		params
	);

	SendAdminMessage(C_GOLD, g_small_string);
	return 1;
}

CMD:desc(playerid, params[])
{
	new targetid,	
		day,
		month,
		year,
		hour,
		minute;
	
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /desc [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLoggedForCMD(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (isnull(GetCharacterDesc(targetid)))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У данного персонажа отсутствует описание.");
		return 1;
	}
	
	format:g_string("\
		" #DEFAULT " Описание персонажа - " #cPROJECT "%s" #cWHITE "\n\n",
		GetPlayerCurrentName(targetid)
	);
	
	if (strlen(GetCharacterDesc(targetid)) >= (MAX_PLAYER_DESC / 2))
	{	
		new str_desc_1 		[	MAX_PLAYER_DESC / 2		],
			str_desc_2		[	MAX_PLAYER_DESC / 2		];
		
		strmid(str_desc_1, GetCharacterDesc(targetid), 0, (MAX_PLAYER_DESC / 2));
		strmid(str_desc_2, GetCharacterDesc(targetid), (MAX_PLAYER_DESC / 2), MAX_PLAYER_DESC);
		format:g_string("%s" #cPROJECT "%s..\n..%s", g_string, str_desc_1, str_desc_2);
	}
	else 
	{
		format:g_string("%s" #cPROJECT "%s", g_string, GetCharacterDesc(targetid));
	}
	
	gmtime(GetCharacterDescCreatedTime(playerid), year, month, day, hour, minute);
	
	format:g_string("%s" #cWHITE "\n\nДата создания: " #DATE_FORMAT "",
		g_string,
		hour,
		minute,
		day,
		month,
		year
	);
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", g_string, "Закрыть", "");
	return 1;
}

CMD:action(playerid)
{
	ShowPlayerActionList(playerid, D_ACTION);
	return 1;
}

CMD:cc(playerid, params[]) 
{
	for(new i; i < MAX_PLAYER_NAME; i++)
	{
		SendClientMessage(playerid, C_WHITE, " ");
	}
	
	return 1;
}

// Chat - Commands - End

// Other
CMD:eject(playerid, params[])
{
	new targetid;
	
	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы должны находиться на месте водителя транспорта.");
		return 1;
	}
	
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /eject [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLoggedForCMD(targetid) || GetPlayerVehicleID(playerid) != GetPlayerVehicleID(targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	RemovePlayerFromVehicle(targetid);
	
	pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " выкинул Вас из транспорта.",
		GetPlayerCurrentName(playerid)
	);
	
	psend:(targetid, C_WHITE);
	
	pformat:("" #SUCCESS " Вы выкинули из транспорта " #cPROJECT "%s" #cWHITE ".",
		GetPlayerCurrentName(targetid)
	);
	
	psend:(playerid, C_WHITE);
	
	return 1;
}

CMD:pay(playerid, params[])
{
	new targetid,
		value;
		
	if (sscanf(params, "ui", targetid, value))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /pay [ID игрока] [сумма]");
		return 1;
	}
	
	if (!IsPlayerLoggedForCMD(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (!(0 < value < 100_000))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Передаваемая сумма не должна быть меньше " #cGREEN "$1" #cWHITE " и больше " #cGREEN "$100.000" #cWHITE ".");
		return 1;
	}
	
	if (!GivePlayerCash(playerid, -value))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас нет такого количества средств на руках.");
		return 1;
	}
	
	GivePlayerCash(targetid, value);
	
	format:g_small_string("Передал деньги %s.", 
		GetPlayerCurrentName(targetid) 
	);
	
	SendRPMessage(ACTION_AME, playerid, g_small_string);
	
	pformat:("" #SUCCESS " Вы передали деньги " #cPROJECT "%s" #cWHITE " в размере " #cGREEN "$%i" #cWHITE ".",
		GetPlayerCurrentName(targetid),
		value
	);
	
	psend:(playerid, C_WHITE);
	
	pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " передал Вам деньги в размере " #cGREEN "$%i" #cWHITE ".",
		GetPlayerCurrentName(playerid),
		value
	);
	
	psend:(targetid, C_WHITE);
	
	format:g_small_string("~y~%s[%i][IP:%s] gave money %s[%i][IP:%s].",
		GetPlayerCurrentName(playerid),
		playerid,
		GetUserIp(playerid),
		GetPlayerCurrentName(targetid),
		targetid,
		GetUserIp(targetid)
	);
	
	return 1;
}

CMD:knock(playerid)
{
	new index;
	
	for (; index < sizeof house_data; index++)
	{
		if (house_data[index][h_id] == 0)
		{
			continue;
		}
		
		if (GetPlayerVirtualWorld(playerid) == house_data[index][h_world] 
		&& IsPlayerInRangeOfPoint(playerid, 
			FACTOR_TELEPORT_RADIUS, 
			house_data[index][h_pos][0], 
			house_data[index][h_pos][1], 
			house_data[index][h_pos][2]) 
		)
		{
			SendClientMessage(playerid, C_WHITE, !DEFAULT " Вы постучали в дверь.");
			SendRPMessage(ACTION_AME, playerid, "Постучал в дверь");
			format:g_small_string("Кто-то постучал в дверь %s.",
				IsHouseType(index) == TYPE_APARTAMENT ? ("квартиры") : ("дома")
			);
			
			SendHouseMessage(index, C_PURPLE, g_small_string);
			return 1;
		}
	}
	
	index = 0;
	
	for (; index < sizeof premise_data; index++)
	{
		if (premise_data[index][pr_id] == 0)
		{
			continue;
		}
		
		if (GetPlayerVirtualWorld(playerid) == premise_data[index][pr_world] 
		&& IsPlayerInRangeOfPoint(playerid, 
			FACTOR_TELEPORT_RADIUS, 
			premise_data[index][pr_pos][0], 
			premise_data[index][pr_pos][1], 
			premise_data[index][pr_pos][2]) 
		)
		{
			SendClientMessage(playerid, C_WHITE, !DEFAULT " Вы постучали в дверь.");
			SendRPMessage(ACTION_AME, playerid, "Постучал в дверь");
			SendPremiseMessage(index, C_PURPLE, "Кто-то постучал в дверь помещения.");
			return 1;
		}
	}
	
	return 1;
}

CMD:invite(playerid, params[])
{
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /invite [ID игрока]");
		return 1;
	}
	
	InvitePlayer(playerid, params, false);
	return 1;
}

InvitePlayer(playerid, params[], bool: is_dialog)
{
	new targetid = strval(params);
	
	new bool: is_player_incorrect = false,
		bool: is_player_arranged = false;
	
	// Проверяем на доступность игрока (онлайн, ID, находится ли около игрока)
	if (isnull(params) 
	|| !IsInt(params) 
	|| !IsPlayerLogged(targetid)
	|| playerid == targetid 
	|| !IsPlayerAroundOfPlayer(playerid, targetid))
	{
		is_player_incorrect = true;
	}
	
	// Проверяем на трудоустройство в бизнесе, крайме, фракции
	if (IsFractionMember(targetid))
	{
		is_player_arranged = true;
	}
	
	if (IsFractionMember(playerid)) // Если принимаем во фракцию
	{
		if (is_player_incorrect)
		{
			if (is_dialog)
			{
				ShowFractionStaffInvite(playerid, "Неверный ID игрока.");
			}
			else
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
			}
			
			return 0;
		}
		
		if (is_player_arranged)
		{
			if (is_dialog)
			{
				ShowFractionStaffInvite(playerid, "Данный игрок уже находится в компании или организации.");
			}
			else
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
			}
			
			return 0;
		}
		
		if (!InvitePlayerToFraction(playerid, targetid, false))
		{
			if (is_dialog)
			{
				ShowFractionStaffInvite(playerid, "У Вас отсутствует доступ к данному действию.");
			}
			else
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
			}
			
			return 0;
		}
		
		SetPVarInt(playerid, "Fraction:IsDialogInvite", _: is_dialog);
		return 1;
	}
	/*
	else 
	if (CheckCrimeAccess(playerid)) // Если принимаем в крайм
    {
		if (is_player_incorrect)
        {
            if (is_dialog)
            {
                ShowCrimeStaffInvite(playerid, "Вы указали некорректного игрока.");
            }
            else
            {
                SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
            }
           
            return 0;
        }
       
        if (is_player_arranged)
        {
            if (is_dialog)
            {
                ShowCrimeStaffInvite(playerid, "Игрок находиться в организации.");
            }
            else
            {
				pformat:("" #ERROR " Игрок находиться в организации.");
				psend:(playerid, C_WHITE);
            }
           
            return 0;
        }
		
		if (!InvitePlayerToCrime(playerid, targetid))
		{
			if (is_dialog)
            {
                ShowCrimeStaffInvite(playerid, "У Вас нет доступа для совершения данного действия.");
            }
            else
            {
                SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
            }
           
            return 0;
		}
	}
	*/
	return 1;
}

CMD:uninvite(playerid, params[])
{
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /uninvite [ID игрока]");
		return 1;
	}
	
	UninvitePlayer(playerid, params, false);
	return 1;
}

UninvitePlayer(playerid, params[], bool: is_dialog)
{
	new targetid = strval(params);
	
	new bool: is_player_incorrect = false;
		
	if (isnull(params) 
	|| !IsInt(params) 
	|| !IsPlayerLogged(targetid) 
	|| playerid == targetid)
	{
		is_player_incorrect = true;
		return 0;
	}
	
	if (IsFractionMember(playerid))
	{
		if (is_player_incorrect)
		{
			if (is_dialog)
			{
				ShowFractionStaffUninvite(playerid, "Неверный ID игрока.");
			}
			else
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
			}
			
			return 0;
		}
		
		if (GetFractionMember(playerid) != GetFractionMember(targetid))
		{
			if (is_dialog)
			{
				ShowFractionStaffUninvite(playerid, "Данный игрок не находится в Вашей организации.");
			}
			else
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
			}
			
			return 0;
		}
		
		if (!UninvitePlayerFromFraction(playerid, targetid, false))
		{
			if (is_dialog)
			{
				ShowFractionStaffUninvite(playerid, "У Вас отсутствует доступ к данному действию.");
			}
			else
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
			}
			
			return 0;
		}
		
		SetPVarInt(playerid, "Fraction:IsDialogUninvite", _: is_dialog);
		return 1;
	}
	
	return 1;
}

CMD:blind(playerid)
{
	if (!GetPVarInt(playerid, "Player:Blinded"))
	{
		ShowBlind(playerid, true);
		SetPVarInt(playerid, "Player:Blinded", 1);
	}
	else 
	{
		ShowBlind(playerid, false);
		SetPVarInt( playerid, "Player:Blinded", 0);
		GameTextForPlayer(playerid, "Unblind", 2000, 5 );
	}
	
	return 1;
}

CMD:showid(playerid, params[])
{
	new targetid;
	
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /showid [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLoggedForCMD(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	ShowPlayerPass(playerid, targetid);
	return 1;
}

CMD:charity(playerid, params[]) 
{
	new money;
	
	if (sscanf(params, "d", money))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /charity [сумма]");
		return 1;
	}
	
	if (!(0 < money <= GetCharacterMoney(playerid)))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
		return 1;
	}
	
	GivePlayerCash(playerid, -money);
	
	pformat:(#SUCCESS " Вы успешно потратили " #cGREEN "$%d" #cWHITE " с помощью данной команды.", money);
	psend:(playerid, C_WHITE);
	return 1;	
}

CMD:frisk(playerid, params[])
{
	new targetid;
		
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /frisk [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLoggedForCMD(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if ((IsFractionMember(playerid, FRACTION_PD) || IsFractionMember(playerid, FRACTION_SD) || IsFractionMember(playerid, FRACTION_NP))
	&& CheckFractionDuty(playerid))
	{
		ShowInventoryItems(targetid, playerid);
		return 1;
	}
	
	SetPVarInt(targetid, "Player:FriskTargetId", playerid);
	
	format:g_string("" #DEFAULT " Предложение\n\n\
		" #cPROJECT "%s" #cWHITE " хочет Вас обыскать.\n\
		Вы принимаете его предложение?",
		GetPlayerCurrentName(playerid)
	);
	
	ShowPlayerDialog(targetid, D_FRISK, DIALOG_STYLE_MSGBOX, " ", 
		g_string,
		"Да", "Нет"
	);
	
	return 1;
}

CMD:time(playerid)
{
	new time;
	
	new year, 
		month, 
		day, 
		hour, 
		minute, 
		second;
		
	getdate(year, month, day);
	gettime(hour, minute, second);
	
	format:g_string("" #DEFAULT " Информация о времени и сроках\n\n\
		Время: " #cPROJECT "%02d:%02d" #cWHITE "\n\
		Дата: " #cPROJECT "%02d.%02d.%d" #cWHITE "\n\
		До заработной платы: " #cPROJECT "%d минут" #cWHITE,
		hour, minute, 
		day, month, year,
		MAX_PAYDAY - character_data[playerid][c_payday]
	);
	
	if (IsPlayerMuted(playerid))
	{
		time = floatround((user_data[playerid][u_mute] - gettime()) / 60);
		format:g_string("%s\nДо снятия блокировки чата: " #cPROJECT "%d минут" #cWHITE, 
			g_string,
			time <= 0 ? 1 : time
		);
	}
	
	if (IsCharacterArrested(playerid))
	{
		time = floatround((character_data[playerid][c_arrest_time] - gettime()) / 60);
		format:g_string("%s\nДо отбытия срока в %s: " #cPROJECT "%d минут" #cWHITE,
			g_string,
			GetCharacterArrestType(playerid) == TYPE_ARREST_ISOLATE ? ("КПЗ") : ("городской тюрьме"),
			time <= 0 ? 1 : time
		);
	}
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", g_string, "Закрыть", "");
	return 1;
}

CMD:donate(playerid)
{
	ShowPlayerDonate(playerid);
	return 1;
}

CMD:vobject(playerid)
{
	if (donate_object[playerid][d_object_id] != INVALID_OBJECT_ID)
	{
		if (IsValidDynamicObject(donate_object[playerid][d_object_id]))
		{
			DestroyDynamicObject(donate_object[playerid][d_object_id]);
			donate_object[playerid][d_object_id] = INVALID_OBJECT_ID;
		}
		
		if (IsValidDynamic3DTextLabel(donate_object[playerid][d_text_id]))
		{
			DestroyDynamic3DTextLabel(donate_object[playerid][d_text_id]);
		}
		
		donate_object[playerid][d_text_id] = Text3D: INVALID_3DTEXT_ID;
		
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Прошлый объект был удалён.");
		return 1;
	}
	
	ShowPlayerDonateObjects(playerid);
	return 1;
}

CMD:helpup(playerid, params[])
{
	if (GetCharacterDeath(playerid) != TYPE_DEATH_NONE)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	new targetid;
		
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /helpup [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLoggedForCMD(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (GetCharacterDeath(targetid) != TYPE_DEATH_INJURED)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Использовать данную команду можно только на игроке в первой стадии.");
		return 1;
	}
	
	HealthPlayer(targetid, true);
	
	pformat:(#SUCCESS " Вы подняли " #cPROJECT "%s" #cWHITE ".", GetPlayerCurrentName(targetid));
	psend:(playerid, C_WHITE);
	
	format:g_small_string("Поднял%s %s", EndWordSex(playerid), GetPlayerCurrentName(targetid));

	SendRPMessage(ACTION_AME, playerid, g_small_string);
	
	pformat:(#SUCCESS " Вас поднял " #cPROJECT "%s" #cWHITE ".", GetPlayerCurrentName(playerid));
	psend:(targetid, C_WHITE);
	return 1;
}

CMD:nameon(playerid, params[])
{
	if (GetUserSettings(playerid, SET_VISIBLE_NAMES) == 0)
	{
		SetUserSettings(playerid, SET_VISIBLE_NAMES, 1);
		pformat:("" #SUCCESS " Вы успешно включили отображение ник-неймов.");
		psend:(playerid, C_WHITE);

		ApplyUserSettings(playerid);
		Update:user_settings(playerid);
	}

	return 1;
}

CMD:nameoff(playerid, params[])
{
	if (GetUserSettings(playerid, SET_VISIBLE_NAMES) == 1)
	{
		SetUserSettings(playerid, SET_VISIBLE_NAMES, 0);
		pformat:("" #SUCCESS " Вы успешно отключили отображение ник-неймов.");
		psend:(playerid, C_WHITE);

		ApplyUserSettings(playerid);
		Update:user_settings(playerid);
	}

	return 1;
}