/*!
	@brief Финансовые операции для системы домов
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

ShowHelpHouse(playerid, buy_type, pay_type = 0)
{
	clean:<g_big_string>;
	strcat(g_big_string, "" #SUCCESS " Уведомление\n\n");
	
	if (buy_type == TYPE_BUY_FULLY)
	{
		if (pay_type == TYPE_PAY_CREDIT)
		{
			strcat(g_big_string, "Вы успешно приобрели жилищное помещение с помощью кредитной карты.\n\
			Вы не сможете продать это помещение другому игроку, пока Ваш кредит будет активен.\n\
			Продажа жилья агенству направит часть средств на погашение кредитной задолжности.\n\n");
		}
		else 
		{
			strcat(g_big_string, "Вы успешно приобрели жилищное помещение.\n\n");
		}
		
		strcat(g_big_string, "Коммунальные услуги были продлены на " #cPROJECT "1" #cWHITE " день.\n\
			 Не допускайте задолжности коммунальных услуг, иначе часть Вашего имущества\n\
			 будет конфискована в пользу государства.\n\
			 Оплата происходит в онлайн-банке.\n\n"
		);
	}
	
	else if (buy_type == TYPE_BUY_RENT) 
	{
		strcat(g_big_string, "Вы успешно арендовали жилищное помещение.\n\
			 Не забывайте во время оплачивать арендную плату арендодателю.\n\
			 Сделать это можно в онлайн-банке.\n\n"
		);
	}
	
	strcat(g_big_string, "Управление:\n \
	Вызвать меню дома - " #cPROJECT "N или /hmenu" #cWHITE";\n \
	Список жилишных помещений - " #cPROJECT "/hlist" #cWHITE ";\n");
	strcat(g_big_string, "Изменить место появления персонажа можно в настройках.");
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", 
		g_big_string, 
		"Закрыть", "" 
	);
}

BuyHouse(playerid, index, buy_type)
{
	if (!buy_type)
	{
		return cmd_hmenu(playerid);
	}
	
	if (IsPlayerLodger(playerid))
	{	
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы уже являетесь сожителем. Для того, чтобы выселиться, используйте " #cPROJECT "/evict" #cWHITE ".");
		return cmd_hmenu(playerid);
	}
	
	if (IsCreditCardExists(playerid) && IsCreditCardUse(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_CREDIT_EXISTS);
		return cmd_hmenu(playerid);
	}
	
	if (!GetPlayerAvaibleHouse(playerid))
	{
		pformat:("" #ERROR " Вы не можете %s больше жилищных помещений.",
			buy_type == TYPE_BUY_RENT ? ("арендовать") : ("купить")
		);
		
		psend:(playerid, C_WHITE);
		return cmd_hmenu(playerid);
	}
	
	if (IsHouseBought(index))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный дом уже приобретен или арендован другим игроком.");
		return cmd_hmenu(playerid);
	}
	
	SetPVarInt(playerid, "House:BuyType", buy_type);
	SetPVarInt(playerid, "House:BuyIndex", index);
	
	MakePayment(playerid, (buy_type == TYPE_BUY_RENT ? GetHouseRent(index) : house_data[index][h_price]), "buy_house");
	
	return 1;
}

function PAY:buy_house(playerid, status, type)
{
	if (!status)
	{
		DeletePVar(playerid, "House:BuyType");
		DeletePVar(playerid, "House:BuyIndex");
		
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
		return cmd_hmenu(playerid);
	}

	new buy_type = GetPVarInt(playerid, "House:BuyType"),
		index = GetPVarInt(playerid, "House:BuyIndex");
	
	if (!GetPlayerAvaibleHouse(playerid))
	{
		DeletePVar(playerid, "House:BuyType");
		DeletePVar(playerid, "House:BuyIndex");
		
		pformat:("" #ERROR " Вы не можете %s больше жилищных помещений.",
			buy_type == TYPE_BUY_RENT ? ("арендовать") : ("купить")
		);
		
		psend:(playerid, C_WHITE);
		return cmd_hmenu(playerid);
	}
	
	house_data[index][h_character_id] = GetCharacterId(playerid);
	
	if (buy_type == TYPE_BUY_FULLY)
	{
		house_data[index][h_time] = gettime() + (60 * 60 * 24);
	}
	else if (buy_type == TYPE_BUY_RENT)
	{
		house_data[index][h_time] = gettime() + (60 * 60 * 24 * 7);
	}
	
	house_data[index][h_buy_type] = buy_type;
	house_data[index][h_debt] = 0;
	
	GiveHouseOwner(playerid, index);
	
	format:g_big_string(
		"UPDATE \
			" #__HOUSES " \
		SET \
			h_buy_type = %i, \
			h_character_id = %i, \
			h_time = %i, \
			h_buy_time = %i, \
			h_debt = 0, \
			h_money = 0 \
		WHERE \
			h_id = %i \
		LIMIT 1",
		buy_type,
		house_data[index][h_character_id],
		house_data[index][h_time],
		gettime(),
		GetHouseId(index)
	);
	
	mysql_tquery(db, g_big_string);
	
	Update:house(index);
	
	// очистка инвентарей с мебелью
	ShowHelpHouse(playerid, buy_type, type);
	
	Clear:house_pvar(playerid);
	
	return 1;
}

SellHouse(index)
{
	if (!IsHouseBought(index))
	{
		return 0;
	}
	
	new money,
		playerid = GetHouseOwnerIdByIndex(index),
		buy_type = GetHouseTypeBought(index);
	
	if (buy_type == TYPE_BUY_FULLY)
	{
		money = GetSaleHousePrice(index);
		
		if (playerid != INVALID_PLAYER_ID)
		{
			pformat:("" #DEFAULT " Ваш%s " #cPROJECT "#%i" #cWHITE " был%s продан%s государству. Средства в размере " #cGREEN "$%i" #cWHITE " возвращены на Вашу карту.",
				(IsHouseType(index) == TYPE_HOUSE) ? (" дом") : ("а квартира"),
				GetHouseId(index),
				(IsHouseType(index) == TYPE_HOUSE) ? ("") : ("а"),
				(IsHouseType(index) == TYPE_HOUSE) ? ("") : ("а"),
				money 
			);
			
			psend:(playerid, C_WHITE);
			
			if (IsCreditCardExists(playerid) && IsCreditCardUse(playerid))
			{
				new credit = GetCreditDifference(playerid);

				if ((money - credit) >= 0)
				{
					money -= credit;
				}
				else 
				{
					credit = abs((abs((money - credit)) - credit)); 
					money = 0;
				}
				
				GiveCreditCardMoney(playerid, credit);
				
				pformat:("" #DEFAULT " Часть средств (" #cGREEN "$%i" #cWHITE ") была направлена на выплату кредита в автоматическом порядке.",
					credit
				);
				
				psend:(playerid, C_WHITE);
			}
			
			if (money != 0)
			{
				GiveDebitCardMoney(
					playerid, 
					money
				);
			}
			
			if (IsPlayerRenovation(playerid))
			{
				SetRenovationMode(playerid, false);
			}
			
			RemoveHouseOwner(playerid, index);
			
			Clear:house_pvar(playerid);
		}
		else 
		{	
			format:g_string("UPDATE " #__CHARACTERS " SET c_refund = c_refund + %i WHERE c_id = %d LIMIT 1",
				money,
				house_data[index][h_character_id]
			);
			
			mysql_pquery(db, g_string);
		}
	}
	else if (buy_type == TYPE_BUY_RENT)
	{
		if (playerid != INVALID_PLAYER_ID)
		{
			pformat:("" #DEFAULT " Ваш договор с арендой %s " #cPROJECT "#%i" #cWHITE " истёк.",
				(IsHouseType(index) == TYPE_HOUSE) ? ("дома") : ("квартиры"),
				GetHouseId(index)
			);
			
			psend:(playerid, C_WHITE);
			
			if (IsPlayerRenovation(playerid))
			{
				SetRenovationMode(playerid, false);
			}
			
			RemoveHouseOwner(playerid, index);
				
			Clear:house_pvar(playerid);
		}
	}
	
	house_data[index][h_character_id] = 
	house_data[index][h_time] =
	house_data[index][h_lock] =
	house_data[index][h_debt] = 
	house_data[index][h_debt_count] = 
	house_data[index][h_money] =
	house_data[index][h_buy_type] = 0;
	house_data[index][h_is_credit] = false;
	
	format:g_big_string(
		"UPDATE \
			" #__HOUSES " \
		SET \
			h_buy_type = 0, \
			h_character_id = 0, \
			h_time = 0, \
			h_buy_time = 0, \
			h_money = 0, \
			h_debt = 0, \
			h_debt_count = 0, \
			h_is_credit = 0, \
			h_lock = 0 \
		WHERE \
			h_id = %i \
		LIMIT 1",
		GetHouseId(index)
	);
	
	mysql_pquery(db, g_big_string);
	
	ResetHouseLodgers(index, playerid != INVALID_PLAYER_ID);
	ResetHouseGarage(index);
	
	Update:house(index);
	return 1;
}

SellHouseToPlayer(playerid, index, targetid, money)
{
	if (!IsHouseBought(index))
	{
		return 0;
	}
	
	if (GetHouseTypeBought(index) == TYPE_BUY_RENT)
	{
		SendClientMessage(playerid, C_WHITE, !NOT_RENT_ACCESS);
		return 0;
	}
	
	if (IsHousePayCredit(index) 
	&& IsCreditCardExists(playerid) 
	&& IsCreditCardUse(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете продать данный дом игроку, так как он был оплачен с помощью активного кредита.");
		return 0;
	}
	
	if (IsPlayerLodger(targetid) || IsHouseAccess(TYPE_HOUSE_LODGER, targetid, index))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Для продажи имущества данному игроку, ему необходимо выселиться.");
		SendClientMessage(targetid, C_WHITE, !#ERROR " Для того, чтобы принять предложение, необходимо выселиться. " #cGRAY "(/evict)");
		return 0;
	}
	
	if (!GetPlayerAvaibleHouse(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок не может приобрести больше жилищных помещений.");
		SendClientMessage(targetid, C_WHITE, !#ERROR " Вы не можете приобрести больше жилищных помещений.");
		return 0;
	}
	
	if (GetHouseDebt(index) > 0)
	{
		SendClientMessage(targetid, C_WHITE, !#ERROR " У Вас имеется непогашенная задолжность.");
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
		(money + house_data[index][h_money])
	);
	
	RemoveHouseOwner(playerid, index);
	Clear:house_pvar(playerid);
	
	GivePlayerCash(
		targetid,
		-money 
	);
	
	ResetHouseLodgers(index, true);
	
	GiveHouseOwner(targetid, index);
	
	house_data[index][h_character_id] = GetCharacterId(targetid);
	house_data[index][h_time] = gettime() + (60 * 60 * 24);
	house_data[index][h_debt] = 
	house_data[index][h_debt_count] = 
	house_data[index][h_money] = 0;
	
	format:g_big_string(
		"UPDATE \
			" #__HOUSES " \
		SET \
			h_character_id = %i, \
			h_time = %i, \
			h_buy_time = %i, \
			h_money = 0, \
			h_debt = 0, \
			h_debt_count = 0 \
		WHERE \
			h_id = %i \
		LIMIT 1",
		house_data[index][h_character_id],
		house_data[index][h_time],
		gettime(),
		GetHouseId(index)
	);
	
	mysql_pquery(db, g_big_string);
	
	ShowHelpHouse(targetid, TYPE_BUY_FULLY);
	return 1;
}

ResetHousesCredit(playerid)
{
	new bool: exists;
	
	for (new i; i < MAX_PLAYER_HOUSES; i++)
	{
		if (player_house[playerid][i] == INVALID_PARAM)
		{
			continue; 
		}
		
		house_data[player_house[playerid][i]][h_is_credit] = false;
		exists = true;
	}
	
	if (exists)
	{
		format:g_string("UPDATE " #__HOUSES " SET h_is_credit = 0 WHERE h_character_id = %i",
			GetCharacterId(playerid),
			MAX_PLAYER_PREMISES
		);
		
		mysql_pquery(db, g_string);
	}
}

ResetHouseGarage(index)
{
	if (!house_data[index][hg_set_furn])
	{
		return;
	}
	
	Remove:all_furn_data(index, TYPE_REN_GARAGE);
	Create:static_furn(index, house_data[index][hg_int_type]);

	house_data[index][hg_set_furn] = !house_data[index][hg_set_furn];
	Update:garage_data(index);
}

ResetHouseLodgers(index, bool: by_owner)
{
	Remove:all_lodger(index);
	
	foreach (new playerid : Player)
	{
		if (lod_data[playerid][lod_house_index] != index)
		{
			continue;
		}
		
		Clear:lod_data(playerid);
		
		SendClientMessage(playerid, C_WHITE, by_owner ? 
			("" #DEFAULT " Вы были выселены. Жилищное помещение, в котором Вы проживали, продано самим владельцем.")
			: ("" #DEFAULT " Вы были выселены. Жилищное помещение, в котором Вы проживали, было автоматически продано.")
		);
	}
}

ResetHouseInterior(index)
{
	new room = house_settings[house_data[index][h_int_type]][hset_rooms];
		
	Clear:room_data(index, TYPE_REN_HOUSE);
	Remove:all_furn_data(index, TYPE_REN_HOUSE);
	Update:reset_room_data(index, TYPE_REN_HOUSE);
	
	for (new i; i < room; i++)
	{
		SetHouseInteriorMaterial(
			index, 
			i, 
			hint_roof_begin, 
			hint_roof_end, 
			TEXTURE_ROOF,
			0
		);

		SetHouseInteriorMaterial(
			index, 
			i, 
			hint_wall_begin, 
			hint_wall_end, 
			TEXTURE_WALL,
			0
		);

		SetHouseInteriorMaterial(
			index, 
			i, 
			hint_floor_begin, 
			hint_floor_end, 
			TEXTURE_FLOOR,
			0
		);
	}
	
	for (new i; i < sizeof furn_data; i++)
	{
		if (furn_data[i][f_id] == 0 
		|| (furn_data[i][f_owner_index] != index 
		|| furn_data[i][f_owner_type] != TYPE_REN_HOUSE))
		{
			continue;
		}
		
		if (furn_data[i][f_state])
		{
			DestroyDynamicObject(furn_data[i][f_object]);
		}
		
		Clear:furniture_data(i);
		Clear:furn_inv_data(i);
	}
	
	// Garage
	
	if (!GetHouseGarageExists(index))
	{
		return;
	}
	
	if (house_data[index][hg_set_furn])
	{
		Remove:all_furn_data(index, TYPE_REN_GARAGE);
		Create:static_furn(index, house_data[index][hg_int_type]);
		house_data[index][hg_set_furn] = false;
		Update:garage_data(index);
	}
}