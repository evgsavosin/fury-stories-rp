/*!
	@brief Файл системы транспорта с операциями
	@author Found (evg.savosin)
	@date 16.12.2016
*/

ShowHelpVehicle(playerid, buy_type)
{
	clean:<g_big_string>;
	
	strcat(g_big_string, "" #DEFAULT " Информация\n\n");
	if (buy_type == TYPE_BUY_FULLY)
	{
		strcat(g_big_string, "Вы успешно приобрели транспортное средство.\n\
			 Получить номера можно будет в полицейском участке.\n\
			 Не забывайте, что каждый месяц, Вам необходимо уплачивать государственные пошлины.\n\
			 Сделать это можно в онлайн-банке.\n\n"
		);
	}
	else if (buy_type == TYPE_BUY_RENT) 
	{
		strcat(g_big_string, "Вы успешно арендовали транспортное средство.\n\n");
	}
	
	strcat(g_big_string, "Управление:\n \
	Вызвать меню транспорта - " #cPROJECT "N или /cmenu" #cWHITE ";\n \
	Список транспорта - " #cPROJECT "/clist" #cWHITE ";");
	
	ShowPlayerDialog(playerid, 
		INVALID_DIALOG_ID, 
		DIALOG_STYLE_MSGBOX, 
		" ", 
		g_big_string, 
		"Закрыть", "" 
	);
}

SwapVehicleToPlayer(playerid, const vehicleid, targetid, const target_vehicleid)
{
	clean:<g_string>;
	
	new index;
				
	if (!IsOwnerVehicle(playerid, vehicleid) || !IsOwnerVehicle(targetid, target_vehicleid))
	{
		return 0;
	}
	
	if (IsVehiclePayCredit(vehicleid) 
	&& IsCreditCardExists(playerid) 
	&& IsCreditCardUse(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете продать данный транспорт игроку, так как он был оплачен с помощью активного кредита.");
		return 0;
	}
	
	if (IsVehiclePayCredit(target_vehicleid) 
	&& IsCreditCardExists(targetid) 
	&& IsCreditCardUse(targetid))
	{
		SendClientMessage(targetid, C_WHITE, !#ERROR " Вы не можете продать данный транспорт игроку, так как он был оплачен с помощью активного кредита.");
		return 0;
	}
	
	if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
	{
		SendClientMessage(playerid, C_WHITE, !VEHICLE_RENT_ACCESS);
		return 0;
	}
	
	if (GetVehicleTypeBought(target_vehicleid) == TYPE_BUY_RENT)
	{
		SendClientMessage(targetid, C_WHITE, !VEHICLE_RENT_ACCESS);
		return 0;
	}
	
	index = GetPlayerVehicleIndexByServerId(playerid, vehicleid);
	if (index == INVALID_PARAM || player_vehicle[playerid][pv_delete][index])
	{
		SendClientMessage(targetid, C_WHITE, !#ERROR " У данного игрока убран транспорт. Повторите попытку обмена позже.");
		SendClientMessage(playerid, C_WHITE, !#ERROR " Убранный транспорт не может участвовать в обмене.");
		return 0;
	}
	
	index = GetPlayerVehicleIndexByServerId(targetid, target_vehicleid);
	if (index == INVALID_PARAM || player_vehicle[targetid][pv_delete][index])
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У данного игрока убран транспорт. Повторите попытку обмена позже.");
		SendClientMessage(targetid, C_WHITE, !#ERROR " Убранный транспорт не может участвовать в обмене.");
		return 0;
	}
	
	if (!GetPlayerAvaibleVehicle(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок не может приобрести больше транспортного средства.");
		SendClientMessage(targetid, C_WHITE, !#ERROR " Вы не можете приобрести больше транспортного средства.");
		return 0;
	}
	
	if (!GetPlayerAvaibleVehicle(playerid))
	{
		SendClientMessage(targetid, C_WHITE, !#ERROR " Данный игрок не может приобрести больше транспортного средства.");
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете приобрести больше транспортного средства.");
		return 0;
	}
	
	RemoveVehicleOwner(playerid, vehicleid, true);
	RemoveVehicleOwner(targetid, target_vehicleid, true);
	
	SetVehicleOwner(playerid, GetVehicleId(target_vehicleid), vehicle_data[target_vehicleid][v_model], target_vehicleid);
	SetVehicleOwner(targetid, GetVehicleId(vehicleid), vehicle_data[vehicleid][v_model], vehicleid);

	format:g_string("\
		UPDATE " #__VEHICLES " \
			SET \
			v_owner_id = %i, \
			v_buy_time = %i \
		WHERE \
			v_id = %i \
		LIMIT 1",
		vehicle_data[vehicleid][v_owner_id],
		gettime(),
		GetVehicleId(vehicleid)
	);
	
	mysql_tquery(db, g_string);
	
	format:g_string("\
		UPDATE " #__VEHICLES " \
			SET \
			v_owner_id = %i, \
			v_buy_time = %i \
		WHERE \
			v_id = %i \
		LIMIT 1",
		vehicle_data[target_vehicleid][v_owner_id],
		gettime(),
		GetVehicleId(target_vehicleid)
	);
	
	mysql_tquery(db, g_string);
	
	return 1;
}

SellVehicleToPlayer(playerid, const vehicleid, targetid, const money)
{
	clean:<g_string>;
	
	if (!IsOwnerVehicle(playerid, vehicleid))
	{
		return 0;
	}

	if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
	{
		SendClientMessage(playerid, C_WHITE, !VEHICLE_RENT_ACCESS);
		return 1;
	}
	
	if (IsVehiclePayCredit(vehicleid) 
	&& IsCreditCardExists(playerid) 
	&& IsCreditCardUse(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете продать данный транспорт игроку, так как он был оплачен с помощью активного кредита.");
		return 0;
	}
	
	new index = GetPlayerVehicleIndexByServerId(playerid, vehicleid);
	if (index == INVALID_PARAM || player_vehicle[playerid][pv_delete][index])
	{
		SendClientMessage(targetid, C_WHITE, !#ERROR " У данного игрока убран транспорт. Повторите попытку обмена позже.");
		SendClientMessage(playerid, C_WHITE, !#ERROR " Убранный транспорт не может участвовать в продаже.");
		return 0;
	}
	
	if (!GetPlayerAvaibleVehicle(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок не может приобрести больше транспортного средства.");
		SendClientMessage(targetid, C_WHITE, !#ERROR " Вы не можете приобрести больше транспортного средства.");
		return 0;
	}
	
	if (!CheckSummForPay(targetid, money))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У данного игрока недостаточно средств.");
		SendClientMessage(targetid, C_WHITE, !ERROR_PAY);
		return 0;
	}
	
	GivePlayerCash(
		playerid, 
		money
	);
	
	RemoveVehicleOwner(playerid, vehicleid, true);
	Clear:vehicle_pvar(playerid);
	
	GivePlayerCash(
		targetid, 
		-money
	);
	
	SetVehicleOwner(targetid, GetVehicleId(vehicleid), vehicle_data[vehicleid][v_model], vehicleid);
	
	format:g_string("\
		UPDATE " #__VEHICLES " \
			SET \
			v_owner_id = %i, \
			v_buy_time = %i \
		WHERE \
			v_id = %i \
		LIMIT 1",
		vehicle_data[vehicleid][v_owner_id],
		gettime(),
		GetVehicleId(vehicleid)
	);
	
	mysql_tquery(db, g_string);
	
	if (GetCountSpawnedVehicle(targetid) > MAX_SPAWNED_VEHICLES)
	{
		Destroy:vehicle_data(targetid, vehicleid, INVALID_PARAM);
		SendClientMessage(targetid, C_WHITE, !#DEFAULT " Транспорт был помещен в слот. Для вызова, используйте " #cPROJECT "/clist" #cWHITE ".");
	}
	
	ShowHelpVehicle(targetid, TYPE_BUY_FULLY);
	
	return 1;
}

SellVehicle(playerid, vehicleid, recycling = true)
{
	new modelid = vehicle_data[vehicleid][v_model],
		money = GetRecycleSumm(modelid);
	
	if (!IsOwnerVehicle(playerid, vehicleid))
	{
		return;
	}
	
	if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
	{
		if (recycling)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете утилизировать арендованный транспорт.");
		}
		
		return;
	}
	
	if (!IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, RECYCLE_LS_POS) 
	&& !IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, RECYCLE_RC_POS))
	{
		if (recycling)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Утилизация транспорта возможно только в определенном месте.");
		}
		
		return;
	}
	
	if (IsCreditCardExists(playerid) && IsCreditCardUse(playerid))
	{
		new credit = GetCreditDifference(playerid);

		if ((money - credit) >= 0)
		{
			money -= credit;
		}
		else 
		{
			credit = abs(abs((money - credit)) - credit); 
			money = 0;
		}
		
		GiveCreditCardMoney(playerid, credit);
		
		pformat:("" #DEFAULT " Часть средств (" #cGREEN "$%i" #cWHITE ") была направлена на выплату кредита в автоматическом порядке.",
			credit
		);
		
		psend:(playerid, C_WHITE);
	}

	if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_START_CAPITAL)
	{
		character_data[playerid][c_start_capital] += money;
		Update:character_int(playerid, "c_start_capital", character_data[playerid][c_start_capital]);
	}
	else
	{
		GivePlayerCash(playerid, money);
	}
	
	RemoveVehicleOwner(playerid, vehicleid, true);
	
	Remove:vehicle_data(vehicleid);
	
	pformat:("" #SUCCESS " Вы успешно утилизировали " #cPROJECT "%s" #cWHITE " за " #cGREEN "$%i" #cWHITE ".", 
		GetVehicleInfo(modelid, v_name),
		money
	);
	
	psend:(playerid, C_WHITE);
}

BreakRentVehicle(playerid, vehicleid)
{
	new modelid = vehicle_data[vehicleid][v_model];
	
	if (!IsOwnerVehicle(playerid, vehicleid))
	{
		return;
	}
	
	if (GetVehicleTypeBought(vehicleid) != TYPE_BUY_RENT)
	{
		return;
	}
	
	RemoveVehicleOwner(playerid, vehicleid, true);
	
	Remove:vehicle_data(vehicleid);
	
	pformat:(#SUCCESS " Вы успешно разорвали договор об аренде " #cPROJECT "%s" #cWHITE ".", 
		GetVehicleInfo(modelid, v_name)
	);
	
	psend:(playerid, C_WHITE);
}

ResetVehiclesCredit(playerid)
{
	new bool: exists,
		vehicleid;
	
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		if ((vehicleid = player_vehicle[playerid][pv_server_id][i]) == 0)
		{
			continue; 
		}
		
		vehicle_data[vehicleid][v_is_credit] = false;
		exists = true;
	}
	
	if (exists)
	{
		format:g_string("UPDATE " #__VEHICLES " SET v_is_credit = 0 WHERE v_owner_id = %i AND v_owner_type = %i LIMIT %i",
			GetCharacterId(playerid),
			TYPE_VEH_PLAYER,
			MAX_PLAYER_PREMISES
		);
		
		mysql_pquery(db, g_string);
	}
}