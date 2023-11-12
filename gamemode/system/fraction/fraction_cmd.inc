/*!
	@brief Команды для системы фракции
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

CMD:fmenu(playerid)
{
	if (!CheckFractionAccess(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	new index = GetFractionMember(playerid);
	
	if (index == INVALID_PARAM)
	{
		return 1;
	}
	
	clean:<g_string>;
	strcat(g_string, " \
		Информация\n \
		Сотрудники\n \
		Подразделения\n \
		Транспорт\n \
		Настройки"
	);
	
	new fraction_id = GetFractionMemberId(playerid);
	
	switch (fraction_id)
	{
		case FRACTION_NEWS:
		{
			strcat(g_string, "\n Управление эфиром\n");
		}
		
		case FRACTION_GOVERNMENT:
		{
			strcat(g_string, "\n Экономика штата\n");
		}
	}
	
	ShowPlayerDialog(playerid, D_FRACTION, DIALOG_STYLE_TABLIST, 
		fraction_data[index][fr_name],
		g_string,
		"Выбрать", "Назад"
	);
	
	return 1;
}

CMD:finvite(playerid, params[])
{	
	InviteFractionPlayer(playerid, params, false);
	return 1;
}

InviteFractionPlayer(playerid, params[], bool: is_dialog)
{
	if (!IsFractionMember(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не состоите в организации.");
		return 0;
	}
	
	new targetid;
	
	if (sscanf(params, "u", targetid))
	{
		if (is_dialog)
		{
			ShowFractionStaffInvite(playerid, "Вы не ввели ID игрока.");
		}
		else 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /finvite [ID игрока]");
		}
		
		return 0;
	}
	
	// Проверяем на доступность игрока (онлайн, ID, находится ли около игрока)
	if (!IsPlayerLogged(targetid)
	|| playerid == targetid 
	|| !IsPlayerAroundOfPlayer(playerid, targetid))
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
	
	// Проверяем на трудоустройство в бизнесе, крайме, фракции
	if (IsFractionMember(targetid))
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
	
	// Принимаем во фракцию
	if (!InvitePlayerToFraction(playerid, targetid, is_dialog))
	{
		if (is_dialog)
		{
			ShowFractionStaffInvite(playerid, "Вы не имеете полномочий для выполнения данного действия.");
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

CMD:funinvite(playerid, params[])
{	
	UninviteFractionPlayer(playerid, params, false);
	return 1;
}

UninviteFractionPlayer(playerid, params[], bool: is_dialog)
{
	if (!IsFractionMember(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не состоите в организации.");
		return 0;
	}
	
	new targetid;
	
	if (sscanf(params, "u", targetid))
	{
		if (is_dialog)
		{
			ShowFractionStaffInvite(playerid, "Вы не ввели ID игрока.");
		}
		else 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /funinvite [ID игрока]");
		}
		
		return 0;
	}
		
	if (!IsPlayerLogged(targetid) 
	|| playerid == targetid)
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
	
	new fraction_id = GetFractionMemberId(playerid);
	
	if (!IsFractionMember(targetid, fraction_id))
	{
		if (is_dialog)
		{
			ShowFractionStaffUninvite(playerid, "Данный игрок не находится в вашей организации.");
		}
		else
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR" Данный игрок не находится в вашей организации.");
		}
		
		return 0;
	}
	
		
	if (!UninvitePlayerFromFraction(playerid, targetid, is_dialog))
	{
		if (is_dialog)
		{
			ShowFractionStaffUninvite(playerid, "Вы не имеете полномочий для выполнения данного действия.");
		}
		else
		{
			SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		}
		
		return 0;
	}
	
	return 1;
}

CMD:setrank(playerid, params[])
{
	SetRank(playerid, params, false);
	return 1;
}

SetRank(playerid, params[], bool: is_dialog)
{
	if (!IsFractionMember(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не состоите в организации.");
		return 0;
	}
	
	new targetid;
	
	if (sscanf(params, "u", targetid))
	{
		if (is_dialog)
		{
			ShowFractionStaffInvite(playerid, "Вы не ввели ID игрока.");
		}
		else 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /setrank [ID игрока]");
		}
		
		return 0;
	}
		
	if (!IsPlayerLogged(targetid))
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
	
	new fraction_id = GetFractionMemberId(playerid);
	
	if (!IsFractionMember(targetid, fraction_id))
	{
		if (is_dialog)
		{
			ShowFractionStaffUninvite(playerid, "Данный игрок не находится в вашей организации.");
		}
		else
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR" Данный игрок не находится в вашей организации.");
		}
		
		return 0;
	}
	
	// Игрок 2 не состоит во фракции, или игрок 1 не обладает нужным доступом
	if (!SetPlayerFractionRank(playerid, targetid, is_dialog))
	{
		if (is_dialog)
		{
			ShowFractionStaffSetRank(playerid, "У Вас отсутствуют полномочия для выполнения данной операции.");
		}
		else
		{
			SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		}
		
		return 0;
	}
	
	return 1;
}

CMD:setunit(playerid, params[])
{
	SetUnit(playerid, params, false);
	return 1;
}

SetUnit(playerid, params[], bool: is_dialog)
{
	if (!IsFractionMember(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не состоите в организации.");
		return 0;
	}
	
	new targetid;
	
	if (sscanf(params, "u", targetid))
	{
		if (is_dialog)
		{
			ShowFractionStaffInvite(playerid, "Вы не ввели ID игрока.");
		}
		else 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /setunit [ID игрока]");
		}
		
		return 0;
	}
		
	if (!IsPlayerLogged(targetid))
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
	
	new fraction_id = GetFractionMemberId(playerid);
	
	if (!IsFractionMember(targetid, fraction_id))
	{
		if (is_dialog)
		{
			ShowFractionStaffUninvite(playerid, "Данный игрок не находится в вашей организации.");
		}
		else
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR" Данный игрок не находится в вашей организации.");
		}
		
		return 0;
	}
	
	// Игрок 2 не состоит во фракции, или игрок 1 не обладает нужным доступом
	if (!SetPlayerFractionUnit(playerid, targetid, is_dialog))
	{	
		if (is_dialog)
		{
			ShowFractionStaffSetUnit(playerid, "Вы не имеете полномочий для выполнения данного действия.");
		}
		else
		{
			SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		}
		
		return 0;
	}
	
	return 1;
}

CMD:fmembers(playerid)
{
	if (!IsFractionMember(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	ShowFractionMembers(
		playerid, 
		D_FRACTION + 10, 
		GetFractionMember(playerid)
	);
				
	return 1;
}

CMD:fpark(playerid)
{
	if (!IsFractionMember(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	new vehicleid = GetPlayerVehicleID(playerid);
	
	if (!vehicleid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_AROUND_CAR);
		return 1;
	}
	
	if (vehicle_data[vehicleid][v_owner_type] == TYPE_VEH_FRACTION
	&& !IsFractionMember(playerid, vehicle_data[vehicleid][v_owner_id]))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	SetVehiclePark(vehicleid, playerid);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно припарковали транспортное средства.");
	return 1;
}


CMD:f(playerid, params[])
{
	if (IsPlayerMuted(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_MUTED);
		return 1;
	}
	
	if (!IsFractionMember(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /f [текст]");
		return 1;
	}
	
	format:g_small_string(#FRACTION_MESSAGE " %s[%d]: %s",
		GetPlayerCurrentName(playerid),
		playerid,
		params
	);
	
	SendFractionMessage(
		GetFractionMember(playerid), 
		g_small_string
	);
				
	return 1;
}

CMD:object(playerid)
{
	if (!IsFractionMember(playerid) || !CheckFractionAccess(playerid, fr_perm_object))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}

	new index = GetFractionMember(playerid);
	ShowFractionObjectList(playerid, D_FRACTION + 44, index, _, "");
	return 1;
}

CMD:dobject( playerid, params[])
{
	if (!IsFractionMember(playerid) || !CheckFractionAccess(playerid, fr_perm_object))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
	
	if (isnull(params)) 
	{
		ShowPlayerDialog(playerid, D_FRACTION + 45, DIALOG_STYLE_LIST, " ", 
			" Удаление по ID: " #cPROJECT "/dobject [ID объекта]" #cWHITE "\n \
			Удалить объект по клику",
			"Выбрать", "Закрыть"
		);
		
		return 1;
	}
	
	new index = strval(params),
		findex = GetFractionMember(playerid);

	index--;
	
	if (!(0 <= index < MAX_FRACTION_OBJECTS) || GetFractionObject(findex, index) == INVALID_OBJECT_ID)
	{
		SendClientMessage( playerid, C_WHITE, #ERROR " Вы ввели неверный ID объекта.");
		return 1;
	}
	
	Destroy:fraction_object(findex, index);
	
	pformat:(#SUCCESS " Вы успешно удалили объект с ID: " #cPROJECT "%d", index + 1);
	psend:(playerid, C_WHITE);
	return 1;
}

CMD:attach(playerid)
{
	if (!IsFractionMember(playerid) || !CheckFractionAccess(playerid, fr_perm_attach))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}

	new index = GetFractionMember(playerid);
	ShowFractionAttachList(playerid, D_FRACTION + 46, index, _, #cGRAY "Удалить все объекты\n");
	return 1;
}

CMD:sl(playerid)
{
	return cmd_strobelight(playerid);
}
	
CMD:strobelight(playerid)
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD)
	&& !IsFractionMember(playerid, FRACTION_FD)
	&& !IsFractionMember(playerid, FRACTION_HOSPITAL)
	&& !IsFractionMember(playerid, FRACTION_NP))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	new vehicleid;
	
	if (!(vehicleid = GetPlayerVehicleID(playerid)))
	{
		SendClientMessage( playerid, C_WHITE, !#ERROR " Для использован команды, Вам необходимо находиться в транспорте." );
		return 1;
	}
	
	if (!IsValidFractionStrobeVehicle(vehicleid))
	{
		SendClientMessage( playerid, C_WHITE, !#ERROR " Вы не можете использовать данную команду в данном транспорте." );
		return 1;
	}
	
	if( strobelight_timer[vehicleid] == INVALID_PARAM)
	{
		strobelight_timer[vehicleid] = SetTimerEx("OnFractionVehicleStrobeLight", 250, true, "d", vehicleid);	
		CheckVehicleLight(playerid, vehicleid, VEHICLE_PARAMS_ON);
		
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы включили стробоскопы." );
	}
	else
	{	
		OnFractionVehicleStrobeTimeout(vehicleid);
		
		SendClientMessage(playerid, C_WHITE, #DEFAULT " Вы выключили стробоскопы." );
	}
	
	return 1;
}

CMD:color(playerid, params[])
{
	if (!IsFractionMember(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	new color;
	
	if (sscanf(params, "d", color) || (color < 0 || color > 1))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /color [0 - снять, 1 - установить]");
		return 1;
	}
	
	if (color == 0) 
	{
		SetPlayerColor(playerid, C_TEAM_DEFAULT);
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Цвет ника установлен по умолчанию." );
	}
	else
	{
		new findex = GetFractionMember(playerid);
		
		SetPlayerColor(
			playerid,
			fraction_data[findex][fr_color]
		);
		
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Установлен фракционный цвет ника." );
	}	
	
	return 1;
}

CMD:mdc(playerid)
{	
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	ShowPlayerDialog(playerid, D_FRACTION + 51, DIALOG_STYLE_TABLIST_HEADERS, " ",
		"" #cPROJECT "Функция\t" #cPROJECT "Команда\n \
		Информация о человеке\n \
		Информация о транспорте\n \
		Информация о доме\n \
		Информация о помещении\n \
		Активные вызовы\t" #cGRAY "/accept",
		"Далее", "Закрыть"
	);
	
	return 1;
}

CMD:m(playerid, params[])
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD)
	&& !IsFractionMember(playerid, FRACTION_NP))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}

	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
	
	new vehicleid = GetVehicleAroundOfPlayer(playerid);

	if (IsBikeVehicle(vehicleid))
	{
		SendClientMessage( playerid, C_WHITE, !PLAYER_NO_ACCESS );
		return 1;
	}
	
	if (vehicle_data[vehicleid][v_owner_id] != GetFractionMemberId(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы находитесь не рядом или не в служебном транспорте.");
		return 1;
	}
	
	if (!IsPlayerInAnyVehicle(playerid) && vehicle_data[vehicleid][v_lock] != VEHICLE_PARAMS_OFF)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Транспорт должен быть открыт.");
		return 1;
	}
	
	if (isnull(params) || strlen(params) > 128)
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /m [текст]");
		return 1;
	}
	
	new findex = GetFractionMember(playerid),
		rank_name	[MAX_FRACTION_RANK_NAME];
	
	GetFractionRankName(playerid, rank_name);
	
	format:g_small_string("[Мегафон %s] %s %s: %s", 
		fraction_data[findex][fr_alt_name], 
		rank_name,
		GetPlayerCurrentName(playerid), 
		params
	);
	
	ProxDetector(60.0, playerid, g_small_string, C_YELLOW, C_YELLOW, C_YELLOW, C_YELLOW, C_YELLOW);
	return 1;
}

CMD:callsign(playerid, params[]) 
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD)
	&& !IsFractionMember(playerid, FRACTION_NP)
	&& !IsFractionMember(playerid, FRACTION_FD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}

	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}

	if (!IsPlayerInAnyVehicle(playerid) || GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (isnull(params) || strlen(params) > 64)
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /callsign [текст]");
		return 1;
	}
	
	new vehicleid = GetPlayerVehicleID(playerid);
	
	if (IsBikeVehicle(vehicleid))
	{
		SendClientMessage( playerid, C_WHITE, !PLAYER_NO_ACCESS );
		return 1;
	}
	
	if (vehicle_data[vehicleid][v_owner_id] != GetFractionMemberId(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы находитесь не в служебном транспорте.");
		return 1;
	}
		
	if (IsValidDynamic3DTextLabel(vehicle_data[vehicleid][v_callsign]))
	{
		SendClientMessage( playerid, C_WHITE, !#DEFAULT " На этом транспорте уже установлена маркировка. " #cGRAY "(/dcallsign для удаления)");
		return 1;
	}
	
	new findex = GetFractionMember(playerid);
		
	vehicle_data[vehicleid][v_callsign] = CreateDynamic3DTextLabel(params, C_WHITE, -1.0, -2.8, 0.0, 30.0, INVALID_PLAYER_ID, vehicleid);
	
	format:g_small_string(#FRACTION_MESSAGE " %s установил маркировку (#%d) %s.",
		GetPlayerCurrentName(playerid),
		vehicleid,
		params
	);
	
	SendFractionMessage(findex, g_small_string);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно установили маркировку. " #cGRAY "(/dcallsign для удаления)");
	return 1;
}

CMD:dcallsign(playerid, params[])
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD)
	&& !IsFractionMember(playerid, FRACTION_NP)
	&& !IsFractionMember(playerid, FRACTION_FD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
		
	new vehicleid = GetPlayerVehicleID(playerid);
	
	if (!vehicleid)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Для удаления маркировки Вы должны находится в транспорте.");
		return 1;
	}
		
	if (vehicle_data[vehicleid][v_owner_id] != GetFractionMemberId(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы находитесь не в служебном транспорте.");
		return 1;
	}
		
	if (!IsValidDynamic3DTextLabel(vehicle_data[vehicleid][v_callsign]))
	{
		SendClientMessage( playerid, C_WHITE, !#DEFAULT " На этом транспорте не установлена маркировка.");
		return 1;
	}

	DestroyDynamic3DTextLabel(vehicle_data[vehicleid][v_callsign]);
	vehicle_data[vehicleid][v_callsign] = Text3D: INVALID_3DTEXT_ID;
	
	new findex = GetFractionMember(playerid);
	
	format:g_small_string(#FRACTION_MESSAGE " %s удалил маркировку с транспорта #%d.",
		GetPlayerCurrentName(playerid),
		vehicleid
	);
	
	SendFractionMessage(findex, g_small_string);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно удалили маркировку.");
	return 1;
}

CMD:cuff( playerid, params[] ) 
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD)
	&& !IsFractionMember(playerid, FRACTION_NP))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
	
	new targetid;
	
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /cuff [ID игрока]");
		return 1;
	}
		
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	 
	if (GetPVarInt(targetid, "Player:Cuff")) 
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок уже в наручниках.");
		return 1;
	}
	
	SetPlayerSpecialAction(targetid, SPECIAL_ACTION_CUFFED);
	SetPlayerAttachedObject(targetid, SLOT_ATTACH_TEMP, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
	SetPVarInt(targetid, "Player:Cuff", true);
	
	format:g_small_string("Надел%s наручники на %s", 
		EndWordSex(playerid), 
		GetPlayerCurrentName(targetid)
	);
	
	SendRPMessage(ACTION_AME, playerid, g_small_string);
	
	pformat:(#DEFAULT "" #cPROJECT " %s" #cWHITE " надел на Вас наручники.", 
		GetPlayerCurrentName(playerid)
	);
	
	psend:(targetid, C_WHITE);
	return 1;
}

CMD:uncuff( playerid, params[] ) 
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD)
	&& !IsFractionMember(playerid, FRACTION_NP))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
	
	new targetid;
	
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /uncuff [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
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
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок уже в наручниках.");
		return 1;
	}
	
	RemovePlayerAttachedObject(targetid, SLOT_ATTACH_TEMP);
	SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
	
	DeletePVar(targetid, "Player:Cuff");
	
	format:g_small_string("Снял%s наручники на %s", 
		EndWordSex(playerid), 
		GetPlayerCurrentName(targetid)
	);
	
	SendRPMessage(ACTION_AME, playerid, g_small_string);
	
	pformat:(#DEFAULT "" #cPROJECT "%s" #cWHITE " снял с Вас наручники.", 
		GetPlayerCurrentName(playerid)
	);
	
	psend:(targetid, C_WHITE);
	return 1;
}

CMD:hale(playerid, params[]) 
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD)
	&& !IsFractionMember(playerid, FRACTION_NP))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
		
	if (GetPVarInt(playerid, "Player:Lead") != INVALID_PLAYER_ID)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы уже ведёте за собой кого-то.");
		return 1;
	}
	
	new targetid;
	
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /hale [ID игрока]");
		return 1;
	}
	
	if (!GetPVarInt(targetid, "Player:Cuff")) 
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок должен быть в наручниках.");
		return 1;
	}
		
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
			
	SetPVarInt(playerid, "Player:Lead", targetid);
	SetPVarInt(targetid, "Player:Follow", playerid);
	
	pformat:(#SUCCESS " Вы успешно заставили " #cPROJECT "%s" #cWHITE " идти за Вами. " #cGRAY "(/unhale - отпустить)", 
		GetPlayerCurrentName(targetid)
	);
	
	psend:(playerid, C_WHITE);

	pformat:(#SUCCESS "" #cPROJECT "%s" #cWHITE " заставил%s Вас идти за %s.", 
		GetPlayerCurrentName(playerid), 
		EndWordSex(playerid), 
		GetCharacterSex(playerid) == 1 ? ("ней") : ("ним") 
	);
	
	psend:(targetid, C_WHITE);
	
	TogglePlayerControllable(playerid, true);
	return 1;
}

CMD:unhale(playerid, params[]) 
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD)
	&& !IsFractionMember(playerid, FRACTION_NP))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}

	new targetid;
	
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /unhale [ID игрока]");
		return 1;
	}
	
	if (GetPVarInt(playerid, "Player:Lead") != targetid)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок идёт не за Вами.");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	SetPVarInt(playerid, "Player:Lead", INVALID_PLAYER_ID);
	SetPVarInt(targetid, "Player:Follow", INVALID_PLAYER_ID);
	
	TogglePlayerControllable(targetid, true);
	
	pformat:(#SUCCESS " Вы прекратили вести за собой " #cPROJECT "%s" #cWHITE ".", 
		GetPlayerCurrentName(targetid)
	);
	
	psend:(playerid, C_WHITE);
	
	pformat:(#SUCCESS " Вы прекратили идти за " #cPROJECT "%s" #cWHITE ".", 
		GetPlayerCurrentName(playerid)
	);
	
	psend:(targetid, C_WHITE );
	return 1;
}

CMD:put(playerid, params[])
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD)
	&& !IsFractionMember(playerid, FRACTION_NP))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
		
	if (IsPlayerInAnyVehicle(playerid))
	{
		SendClientMessage( playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	new targetid,
		vehicleid = GetVehicleAroundOfPlayer(playerid, false, 5.0);
	
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /put [ID игрока]");
		return 1;
	}
		
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
		
	if (vehicleid == 0 
	|| vehicle_data[vehicleid][v_owner_type] != TYPE_VEH_FRACTION 
	|| vehicle_data[vehicleid][v_owner_id] != GetFractionMemberId(playerid))
	{
		SendClientMessage( playerid, C_WHITE, !#ERROR " Вы должны находиться рядом со служебным транспортом.");
		return 1;
	}
	
	new Float: x,
		Float: y,
		Float: z;
		
	GetVehiclePos(vehicleid, x, y, z);
	
	if (!PutPlayerInVehicle(targetid, vehicleid, 2) && PutPlayerInVehicle(targetid, vehicleid, 3))
	{
		SendClientMessage(playerid, C_WHITE, #ERROR " Вы не можете посадить игрока в данный транспорт.");
		return 1;
	}
	
	return 1;
}

CMD:su(playerid, params[]) 
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
	
	new targetid,
		reason		[64];
		
	if (sscanf(params, "us[64]", targetid, reason))
	{
		SendClientMessage(playerid, C_WHITE, #DEFAULT " Введите: /su [ID игрока] [Причина]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || targetid == playerid)
	{	
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}

	if (!isnull(character_data[playerid][c_suspect]))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок уже находится в розыске.");
		return 1;
	}
	
	if (!(3 < strlen(reason) < MAX_CHARACTER_SUSPECT))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Укажите корректно причину розыска.");
		return 1;
	}
	
	clean:<character_data[targetid][c_suspect]>;
	strcat(character_data[targetid][c_suspect], reason, MAX_CHARACTER_SUSPECT);
	
	Update:character_string(targetid, "c_suspect", reason);
	
	pformat:(#SUCCESS " Вы объявили в розыск " #cPROJECT "%s" #cWHITE " c причиной " #cPROJECT "%s" #cWHITE ".", 
		GetPlayerCurrentName(targetid),
		reason
	);
	
	psend:(playerid, C_WHITE);
	return 1;
}

CMD:unsu(playerid, params[]) 
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
	
	new targetid;
		
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, #DEFAULT " Введите: /unsu [ID игрока]");
		return 1;
	}
	
	clean:<character_data[playerid][c_suspect]>;
	Update:character_string(playerid, "c_suspect", "");
	
	pformat:(#SUCCESS " Вы сняли розыск с " #cPROJECT "%s" #cWHITE ".", 
		GetPlayerCurrentName(targetid)
	);
	
	psend:(playerid, C_WHITE);
	return 1;
}

CMD:arrest(playerid, params[]) 
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD)
	&& !IsFractionMember(playerid, FRACTION_NP))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
		
	new targetid,
		time;
		
	if (sscanf(params, "ud", targetid, time))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /arrest [ID игрока] [Количество минут]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (IsCharacterArrested(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок уже находится в КПЗ.");
		return 1;
	}
		
	if (!(0 < time < 60))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Срок в КПЗ может быть от 1 минуты до 60 минут.");
		return 1;
	}

	new bool: is_exists = false;
		
	for (new i; i < sizeof fraction_camera; i++)
	{
		if (fraction_camera[i][fr_type] == TYPE_ARREST_ISOLATE 
		&& IsPlayerInRangeOfPoint(playerid, 7.0, fraction_camera[i][fr_pos_camera_entry][0], fraction_camera[i][fr_pos_camera_entry][1], fraction_camera[i][fr_pos_camera_entry][2]))
		{
			character_data[targetid][c_arrest_time] = gettime() + (time * 60);
			character_data[targetid][c_arrest_camera] = i;
			character_data[targetid][c_arrest_type] = TYPE_ARREST_ISOLATE;
		
			SetPlayerPos(
				targetid, 
				fraction_camera[i][fr_pos_camera][0],
				fraction_camera[i][fr_pos_camera][1],
				fraction_camera[i][fr_pos_camera][2]
			);
			
			SetPlayerFacingAngle(targetid, fraction_camera[i][fr_pos_camera][3]);
			
			is_exists = true;
			break;
		}
	}
	
	if (!is_exists)
	{
		SendClientMessage(playerid, C_WHITE, #ERROR " Вы находитесь не около КПЗ.");
		return 1;
	}
	
	new follow_id = GetPVarInt(targetid, "Player:Follow");
	
	if (follow_id != INVALID_PLAYER_ID) 
	{
		SetPVarInt(follow_id, "Player:Lead", INVALID_PLAYER_ID);
		SetPVarInt(targetid, "Player:Follow", INVALID_PLAYER_ID);
	}
	
	if (GetPVarInt(targetid, "Player:Cuff")) 
	{
		DeletePVar(targetid, "Player:Cuff");
		RemovePlayerAttachedObject(playerid, SLOT_ATTACH_TEMP);
		SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
		TogglePlayerControllable(targetid, true);	
	}	
	
	format:g_small_string("FROM_UNIXTIME(%d)", character_data[targetid][c_arrest_time]);
	Update:character_string(targetid, "c_arrest_date", g_small_string, false);
	Update:character_int(targetid, "c_arrest_type", TYPE_ARREST_ISOLATE);
	Update:character_int(targetid, "c_arrest_camera", character_data[targetid][c_arrest_camera]);
	
	pformat:(#DEFAULT " Вы были помещены в КПЗ " #cPROJECT "%s" #cWHITE " на " #cPROJECT "%d" #cWHITE " мин.", GetPlayerCurrentName(playerid), time);
	psend:(targetid, C_WHITE );
		
	pformat:(#SUCCESS " Вы успешно поместили в КПЗ " #cPROJECT "%s" #cWHITE " на " #cPROJECT "%d" #cWHITE " мин.",GetPlayerCurrentName(targetid), time);
	psend:(playerid, C_WHITE);
	return 1;
}

CMD:unarrest( playerid, params[] )
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD)
	&& !IsFractionMember(playerid, FRACTION_NP))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
		
	new targetid;
		
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /unarrest [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (!IsCharacterArrested(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок не находится в КПЗ.");
		return 1;
	}
	
	ResetPlayerArrest(targetid);
	
	pformat:(#SUCCESS " Вы выпустили " #cPROJECT "%s" #cWHITE " из КПЗ.", GetPlayerCurrentName(targetid));
	psend:(playerid, C_WHITE);
	
	pformat:(#DEFAULT " " #cPROJECT "%s" #cWHITE " выпустил Вас из КПЗ.", GetPlayerCurrentName(playerid));
	psend:(targetid, C_WHITE );
	return 1;
}

CMD:accept(playerid, params[])
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD)
	&& !IsFractionMember(playerid, FRACTION_FD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
	
	ShowFractionCalls(playerid, D_FRACTION + 52);
	return 1;
}

CMD:taser(playerid)
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
	
	if (IsPlayerInAnyVehicle(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Для использования данного действия, Вы должны находится вне транспорта.");
		return 1;
	}
	
	new taser = GetPVarInt(playerid, "Player:Taser");
	
	if (taser)
	{
		RemovePlayerWeapon(playerid, WEAPON_SILENCED);
		GiveInventoryWeapons(playerid);
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы убрали тазер.");
	}
	else 
	{
		HideInventoryWeapons(playerid, false);
		GivePlayerWeapon(playerid, WEAPON_SILENCED, 2);
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы достали тазер.");
	}
	
	SetPVarInt(playerid, "Player:Taser", !taser);
	return 1;
}

CMD:frepair(playerid)
{
	if (!IsFractionMember(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
	
	new vehicleid = GetPlayerVehicleID(playerid);
	
	if (vehicleid == 0 
	|| vehicle_data[vehicleid][v_owner_type] != TYPE_VEH_FRACTION 
	|| vehicle_data[vehicleid][v_owner_id] != GetFractionMemberId(playerid))
	{
		SendClientMessage( playerid, C_WHITE, !#ERROR " Вы должны находиться рядом со служебным транспортом.");
		return 1;
	}
	
	if (!IsPlayerInRangeOfPoint(playerid, FRACTION_REPAIR_POS) || GetCharacterInt(playerid) != INT_OTHER)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Для использования данной команды Вы должны находится в гараже организации.");
		return 1;
	}
	
	VehicleFill(vehicleid, 0.0, true);
	RepairVehicle(vehicleid);
	vehicle_data[vehicleid][v_health] = 1000.0;
	SetVehicleHealth(vehicleid, vehicle_data[vehicleid][v_health]);
	Update:vehicle_data(vehicleid, playerid);

	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно отремонтировали и заправили транспортное средство.");
	return 1;
}

CMD:dep(playerid, params[])
{
	return cmd_d(playerid, params);
}

CMD:d(playerid, params[])
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD)
	&& !IsFractionMember(playerid, FRACTION_NP)
	&& !IsFractionMember(playerid, FRACTION_FD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /d(ep) [Текст]");
		return 1;
	}
	
	new findex = GetFractionMember(playerid),
		rank_name	[MAX_FRACTION_RANK_NAME];
	
	GetFractionRankName(playerid, rank_name);
	
	for (new i; i < MAX_FRACTIONS; i++)
	{
		switch (fraction_data[i][fr_id])
		{
			case FRACTION_PD, FRACTION_SD, FRACTION_NP, FRACTION_FD:
			{
				format:g_small_string(#DEPARTMENT_MESSAGE " (%s) %s %s: %s",
					fraction_data[findex][fr_alt_name], 
					rank_name,
					GetPlayerCurrentName(playerid), 
					params
				);
				
				SendFractionMessage(
					GetFractionIndexById(fraction_data[i][fr_id]),
					g_small_string,
					C_PROJECT
				);
			}
		}
	}
	
	return 1;
}

CMD:ram(playerid, params[]) 
{
	if (!IsFractionMember(playerid, FRACTION_PD)
	&& !IsFractionMember(playerid, FRACTION_SD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
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
			SendClientMessage(playerid, C_WHITE, !DEFAULT " Выбили дверь жилищного помещения.");
			SendRPMessage(ACTION_AME, playerid, "Выбил дверь");
			format:g_small_string("Дверь %s была выбита.",
				IsHouseType(index) == TYPE_APARTAMENT ? ("квартиры") : ("дома")
			);
			
			SendHouseMessage(index, C_PURPLE, g_small_string);
			
			house_data[index][h_lock] = false;
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
			SendClientMessage(playerid, C_WHITE, !DEFAULT " Выбили дверь помещения.");
			SendRPMessage(ACTION_AME, playerid, "Выбил дверь");
			SendPremiseMessage(index, C_PURPLE, "Дверь помещения была выбита.");
			
			premise_data[index][pr_lock] = false;
			return 1;
		}
	}
	
	return 1;
}

CMD:heal(playerid, params[])
{
	if (!IsFractionMember(playerid, FRACTION_FD)
	&& !IsFractionMember(playerid, FRACTION_HOSPITAL))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
	
	new targetid;
	
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /heal [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (GetCharacterDeath(targetid) == TYPE_DEATH_DIED)
	{
		SendClientMessage(playerid, C_WHITE, #ERROR " Данный игрок умер и его нельзя вылечить.");
		return 1;
	}

	SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы использовали сумку с медикаментами.");
	
	format:g_small_string("Использовал%s сумку с медикаментами", EndWordSex(playerid));
	SendRPMessage(ACTION_AME, playerid, g_small_string);
	
	ApplyAnimation(playerid, "MEDIC", "CPR", 4.0, 0, 1, 1, 0, 0, 1);
	
	if (GetCharacterHealth(targetid) + 50.0 < 100.0 ) 
	{
		SetPlayerHealth(targetid, GetCharacterHealth(targetid) + 50.0 );
	}
	else 
	{
		SetPlayerHealth(targetid, 100.0);
	}
	
	HealthPlayer(targetid);
	return 1;
}