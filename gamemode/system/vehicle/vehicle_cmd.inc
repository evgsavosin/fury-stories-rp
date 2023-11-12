/*!
	@brief Файл с командами для системы транспорта
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

CMD:clist(playerid)
{
	Clear:vehicle_pvar(playerid);
	
	if (!ShowVehicleList(playerid, D_CAR))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CAR);
	}
	
	return 1;
}

CMD:cmenu(playerid)
{
	Clear:vehicle_pvar(playerid);
	
	new vehicleid = GetVehicleAroundOfPlayer(playerid);
	
	if (!vehicleid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_AROUND_CAR);
		return 1;
	}
	
	SetPVarInt(playerid, "Vehicle:Select", vehicleid);
	ShowVehicleMenu(playerid, vehicleid);
	
	return 1;
}

CMD:park(playerid)
{
	if (GetPlayerVehiclesCount(playerid) == 0)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CAR);
		return 1;
	}
	
	new vehicleid = GetPlayerVehicleID(playerid);
	
	if (!vehicleid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_AROUND_CAR);
		return 1;
	}
	
	if (!IsOwnerVehicle(playerid, vehicleid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_THIS_CAR);
		return 1;
	}
	
	SetVehiclePark(vehicleid, playerid);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно припарковали свое транспортное средство.");
	return 1;
}

CMD:unrentcar(playerid)
{
	if (!GetPlayerVehiclesCount(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CAR);
		return 1;
	}
	
	new vehicleid = GetVehicleAroundOfPlayer(playerid);
	
	if (!vehicleid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_AROUND_CAR);
		return 1;
	}
	
	if (!IsOwnerVehicle(playerid, vehicleid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_THIS_CAR);
		return 1;
	}
	
	if (GetVehicleTypeBought(vehicleid) != TYPE_BUY_RENT)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный транспорт не является арендованным.");
		return 1;
	}
	
	SetPVarInt(playerid, "Vehicle:Select", vehicleid);	
	ShowVehicleBreakRent(playerid, vehicleid);
	return 1;
}

CMD:sellcar(playerid)
{
	if (!GetPlayerVehiclesCount(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CAR);
		return 1;
	}
	
	new vehicleid = GetVehicleAroundOfPlayer(playerid);
	
	if (!vehicleid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_AROUND_CAR);
		return 1;
	}
	
	if (!IsOwnerVehicle(playerid, vehicleid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_THIS_CAR);
		return 1;
	}
	
	if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
	{
		SendClientMessage(playerid, C_WHITE, !VEHICLE_RENT_ACCESS);
		return 1;
	}
	
	SetPVarInt(playerid, "Vehicle:Select", vehicleid);	
	ShowVehicleSellPlayer(playerid);
	return 1;
}

CMD:swapcar(playerid)
{
	if (!GetPlayerVehiclesCount(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CAR);
		return 1;
	}
	
	new vehicleid = GetVehicleAroundOfPlayer(playerid);
	
	if (!vehicleid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_AROUND_CAR);
		return 1;
	}
	
	if (!IsOwnerVehicle(playerid, vehicleid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_THIS_CAR);
		return 1;
	}
	
	if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
	{
		SendClientMessage(playerid, C_WHITE, !VEHICLE_RENT_ACCESS);
		return 1;
	}
	
	ShowVehicleList(playerid, D_CAR + 8);
	return 1;
}

CMD:trustcar(playerid)
{
	if (!GetPlayerVehiclesCount(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CAR);
		return 1;
	}
	
	new vehicleid = GetVehicleAroundOfPlayer(playerid);
	
	if (!vehicleid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_AROUND_CAR);
		return 1;
	}
	
	if (!IsOwnerVehicle(playerid, vehicleid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_THIS_CAR);
		return 1;
	}
	
	if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
	{
		SendClientMessage(playerid, C_WHITE, !VEHICLE_RENT_ACCESS);
		return 1;
	}
	
	SetPVarInt(playerid, "Vehicle:Select", vehicleid);
	ShowPlayerDialog(playerid, D_CAR + 12, DIALOG_STYLE_INPUT, " ", 
		"" #DEFAULT " Доверенность\n\n\
		Вы можете предоставить доступ к временному управлению Вашим транспортом.\n\
		Введите ID игрока, которому Вы хотите доверить Ваш транспорт:", 
		"Выбрать", "Закрыть" 
	);
	return 1;
}

CMD:taketrustcar(playerid)
{
	if (!GetPlayerVehiclesCount(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CAR);
		return 1;
	}
	
	foreach (new i : Player)
	{
		if (GetPVarInt(i, "Vehicle:Trust") == GetCharacterId(playerid))
		{
			DeletePVar(i, "Vehicle:Trust");
		}
	}
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно забрали доступ к Вашему транспорту у других игроков.");
	return 1;
}

CMD:hood(playerid)
{
	new vehicleid = GetVehicleAroundOfPlayer(playerid);
	
	if (!vehicleid)
	{
		return SendClientMessage(playerid, C_WHITE, !PLAYER_AROUND_CAR);
	}
	
	if (vehicle_data[vehicleid][v_hood] != VEHICLE_PARAMS_ON)
	{
		if (!IsVehicleAccess(playerid, vehicleid))
		{
			return SendClientMessage(playerid, C_WHITE, !PLAYER_NO_THIS_CAR);
		}
	}
	
	new Float: x,
		Float: y,
		Float: z;
		
	GetVehicleComponentPos(vehicleid, false, x, y, z);
	
	if (GetPlayerDistanceFromPoint(playerid, x, y, z) > 3.0)
	{
		return 1;
	}
	
	CheckVehicleHood(vehicleid);
	
	return 1;
}

CMD:boot(playerid)
{
	new vehicleid = GetVehicleAroundOfPlayer(playerid);
	
	if (!vehicleid)
	{
		return SendClientMessage(playerid, C_WHITE, !PLAYER_AROUND_CAR);
	}
	
	if (vehicle_data[vehicleid][v_boot] != VEHICLE_PARAMS_ON)
	{
		if (!IsVehicleAccess(playerid, vehicleid))
		{
			return SendClientMessage(playerid, C_WHITE, !PLAYER_NO_THIS_CAR);
		}
	}
	
	new Float: x,
		Float: y,
		Float: z;
		
	GetVehicleComponentPos(vehicleid, true, x, y, z);
	
	if (GetPlayerDistanceFromPoint(playerid, x, y, z) > 3.5)
	{
		return 1;
	}
		
	CheckVehicleBoot(vehicleid);
	return 1;
}

CMD:en(playerid)
{
	new vehicleid = GetPlayerVehicleID(playerid),
		player_state = GetPlayerState(playerid);
	
	if (IsBikeVehicle(vehicleid))
	{
		return 1;
	}
	
	if (vehicleid == 0 || player_state != PLAYER_STATE_DRIVER)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы должны находиться на месте водителя транспорта.");
		return 1;
	}
	
	CheckVehicleEngine(playerid, vehicleid);
	return 1;
}

CMD:window(playerid, params[])
{
	if (!IsPlayerInAnyVehicle(playerid))
	{
		return SendClientMessage(playerid, C_WHITE, !#ERROR " Вы должны находиться за рулем транспорта.");
	}
	
	new vehicleid = GetPlayerVehicleID(playerid),
		seat = GetPlayerVehicleSeat(playerid);
		
	if (!vehicleid || seat == 128 || seat > 3)
	{
		return 1;
	}
	
	if (isnull(params))
	{
		vehicle_data[vehicleid][v_window][seat] = !vehicle_data[vehicleid][v_window][seat];
	}
	else if (!isnull(params) && seat == 0)
	{
		if (!strcmp(params, "l", true))
		{
			vehicle_data[vehicleid][v_window][0] = !vehicle_data[vehicleid][v_window][0];
		}
		else if (!strcmp(params, "r", true))
		{
			vehicle_data[vehicleid][v_window][1] = !vehicle_data[vehicleid][v_window][1];
		}
		else if (!strcmp(params, "rl", true))
		{
			vehicle_data[vehicleid][v_window][2] = !vehicle_data[vehicleid][v_window][2];
		}
		else if (!strcmp(params, "rr", true))
		{
			vehicle_data[vehicleid][v_window][3] = !vehicle_data[vehicleid][v_window][3];
		}
		else
		{
			return SendClientMessage(playerid, C_WHITE, !#DEFAULT " " #DEFAULT " Введите: /window [l - переднее левое | r - переднее правое | rl - заднее левое | rr - заднее правое]");
		}

	}
	
	SetVehicleParams(vehicleid);
	
	return 1;
}

CMD:clock(playerid)
{
	VehicleLock(playerid);
	return 1;
}

CMD:setcdesc(playerid, params[])
{
	new vehicleid;
	if ((vehicleid = GetVehicleAroundOfPlayer(playerid)) == 0)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_AROUND_CAR);
		return 1;
	}
	
	if (!IsOwnerVehicle(playerid, vehicleid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_THIS_CAR);
		return 1;
	}
	
	if (!isnull(vehicle_data[vehicleid][v_desc]))
	{
		clean:<vehicle_data[vehicleid][v_desc]>;
		Update:vehicle_data(vehicleid, playerid);

		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы убрали прошлое описание Вашего транспорта.");
		return 1;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /setcdesc [описание транспорта]");
		return 1;
	}
	
	strcat(vehicle_data[vehicleid][v_desc], params, MAX_PLAYER_DESC);

	Update:vehicle_data(vehicleid, playerid);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно установили описание транспорта. " #cGRAY "(/setcdesc - убрать, /cdesc - для просмотра)");
	return 1;
}

CMD:cdesc(playerid, params[])
{
	new vehicleid;
	if ((vehicleid = GetVehicleAroundOfPlayer(playerid)) == 0)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_AROUND_CAR);
		return 1;
	}

	if (isnull(vehicle_data[vehicleid][v_desc]))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У данного транспорта отсутствует описание.");
		return 1;
	}
	
	format:g_string("\
		" #DEFAULT " Описание транспорта - " #cPROJECT "%s" #cWHITE "\n\n",
		GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name)
	);
	
	if (strlen(vehicle_data[vehicleid][v_desc]) >= (MAX_PLAYER_DESC / 2))
	{	
		new str_desc_1 		[	MAX_PLAYER_DESC / 2		],
			str_desc_2		[	MAX_PLAYER_DESC / 2		];
		
		strmid(str_desc_1, vehicle_data[vehicleid][v_desc], 0, (MAX_PLAYER_DESC / 2));
		strmid(str_desc_2, vehicle_data[vehicleid][v_desc], ((MAX_PLAYER_DESC / 2) - 1), MAX_PLAYER_DESC + 1);
		format:g_string("%s" #cPROJECT "%s..\n..%s", g_string, str_desc_1, str_desc_2);
	}
	else 
	{
		format:g_string("%s" #cPROJECT "%s", g_string, vehicle_data[vehicleid][v_desc]);
	}
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", g_string, "Закрыть", "");
	return 1;
}

CMD:ckey(playerid)
{
	new count = ShowVehicleAroundOfPlayerList(playerid, D_CAR + 14, 1);
	
	if (count == 1)
	{
		new vehicleid = g_dialog_select[playerid][0];
		ShowKeyAlarm(playerid, true, vehicleid);
	}
	else if (count == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Не найден транспорт в радиусе.");
	}
	
	return 1;
}

CMD:cdetails(playerid)
{
	Clear:vehicle_pvar(playerid);
	
	new vehicleid = GetVehicleAroundOfPlayer(playerid);
	
	if (!vehicleid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_AROUND_CAR);
		return 1;
	}

	if (IsBikeVehicle(vehicleid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACTION);
		return 1;
	}
	
	if (!IsOwnerVehicle(playerid, vehicleid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_THIS_CAR);
		return 1;
	}
	
	ShowPlayerDialog(playerid, D_CAR + 13, DIALOG_STYLE_LIST, " ", " \
		Снять передний бампер\n \
		Снять задний бампер", 
		"Далее", "Закрыть"
	);
	
	return 1;
}