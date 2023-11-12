/*!
	@brief Операции для системы помещений
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

ShowHelpPremise(playerid, buy_type, pay_type)
{
	clean:<g_big_string>;
	strcat(g_big_string, "" #SUCCESS " Уведомление\n\n");
	
	if (buy_type == TYPE_BUY_FULLY)
	{
		if (pay_type == TYPE_PAY_CREDIT)
		{
			strcat(g_big_string, "Вы успешно приобрели помещение с помощью кредитной карты.\n\
			Вы не сможете продать это помещение другому игроку, пока Ваш кредит будет активен.\n\
			Продажа жилья агенству направит часть средств на погашение кредитной задолжности.\n\n");
		}
		else 
		{
			strcat(g_big_string, "Вы успешно приобрели помещение.\n\n");
		}
		
		strcat(g_big_string, "Счета за электроэнергию оплачены на " #cPROJECT "1" #cWHITE " день.\n\
			 Не допускайте задолжности счетов данных услуг, иначе часть Вашего имущества\n\
			 будет конфискована в пользу государства.\n\
			 Оплата происходит в онлайн-банке.\n\n"
		);
	}
	
	else if (buy_type == TYPE_BUY_RENT) 
	{
		strcat(g_big_string, "Вы успешно арендовали помещение.\n\
			 Не забывайте во время оплачивать арендную плату арендодателю.\n\
			 Сделать это можно в онлайн-банке.\n\n"
		);
	}
	
	strcat(g_big_string, "Управление:\n \
	Вызвать меню помещения - " #cPROJECT "N" #cWHITE" или " #cPROJECT "/prmenu" #cWHITE";\n \
	Список жилишных помещений - " #cPROJECT "/prlist" #cWHITE ";\n");
	strcat(g_big_string, "Изменить место появления персонажа можно в настройках.");
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", 
		g_big_string, 
		"Закрыть", "" 
	);
}

BuyPremise(playerid, index, buy_type)
{
	if (!buy_type)
	{
		return cmd_prmenu(playerid);
	}
	
	if (!GetPlayerAvaiblePremise(playerid))
	{
		pformat:("" #ERROR " Вы не можете %s больше помещений.",
			buy_type == TYPE_BUY_RENT ? ("арендовать") : ("купить")
		);
		
		psend:(playerid, C_WHITE);
		return cmd_prmenu(playerid);
	}
	
	if (IsPremiseBought(index))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данное помещение уже приобретено или арендовано другим игроком.");
		return 1;
	}
	
	SetPVarInt(playerid, "Premise:BuyType", buy_type);
	SetPVarInt(playerid, "Premise:BuyIndex", index);
	
	MakePayment(playerid, (buy_type == TYPE_BUY_RENT ? GetPremiseRent(index) : premise_data[index][pr_price]), "buy_premise");
	
	return 1;
}

function PAY:buy_premise(playerid, status, type)
{
	if (!status)
	{
		DeletePVar(playerid, "Premise:BuyType");
		DeletePVar(playerid, "Premise:BuyIndex");
		
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
		return cmd_prmenu(playerid);
	}
	
	new buy_type = GetPVarInt(playerid, "Premise:BuyType"),
		index = GetPVarInt(playerid, "Premise:BuyIndex");
	
	if (!GetPlayerAvaiblePremise(playerid))
	{
		DeletePVar(playerid, "Premise:BuyType");
		DeletePVar(playerid, "Premise:BuyIndex");
		
		pformat:("" #ERROR " Вы не можете %s больше помещений.",
			buy_type == TYPE_BUY_RENT ? ("арендовать") : ("купить")
		);
		
		psend:(playerid, C_WHITE);
		return cmd_prmenu(playerid);
	}
	
	premise_data[index][pr_character_id] = GetCharacterId(playerid);
	
	if (buy_type == TYPE_BUY_FULLY)
	{
		premise_data[index][pr_time] = gettime() + (60 * 60 * 24);
	}
	else if (buy_type == TYPE_BUY_RENT)
	{
		premise_data[index][pr_time] = gettime() + (60 * 60 * 24 * 7);
	}
	
	premise_data[index][pr_buy_type] = buy_type;
	premise_data[index][pr_debt] = 0;
	
	GivePremiseOwner(playerid, index);
	
	format:g_big_string(
		"UPDATE \
			" #__PREMISES " \
		SET \
			pr_buy_type = %i, \
			pr_character_id = %i, \
			pr_time = %i, \
			pr_buy_time = %i, \
			pr_is_credit = %i, \
			pr_debt = 0, \
			pr_debt_count = 0, \
			pr_entrance = 0, \
			pr_profit = 0, \
			pr_assort_stock = 0, \
			pr_cash_pos_x = 0.0, \
			pr_cash_pos_y = 0.0, \
			pr_cash_pos_z = 0.0 \
		WHERE \
			pr_id = %i \
		LIMIT 1",
		buy_type,
		premise_data[index][pr_character_id],
		premise_data[index][pr_time],
		gettime(),
		(type == TYPE_PAY_CREDIT ? 1 : 0),
		GetPremiseId(index)
	);
	
	mysql_tquery(db, g_big_string);
	
	ShowHelpPremise(playerid, buy_type, type);
	
	Clear:premise_pvar(playerid);
	
	return 1;
}

SellPremise(index)
{
	if (!IsPremiseBought(index))
	{
		return 0;
	}
	
	new money,
		playerid = GetPremiseOwnerIdByIndex(index),
		buy_type = GetPremiseTypeBought(index);
	
	if (playerid != INVALID_PLAYER_ID)
	{
		if (IsPremiseTied(index))
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Чтобы продать данное помещение, необходимо его отвязать от компании.");
			return 0;
		}
	}
	else 
	{	
		new bindex = GetBusinessIndexById(premise_data[index][pr_business_id]);
		
		if (bindex != INVALID_PARAM)
		{
			PremiseUntie(index, bindex);
		}
	}
	
	if (buy_type == TYPE_BUY_FULLY)
	{
		money = GetSalePremisePrice(index);
		
		if (playerid != INVALID_PLAYER_ID)
		{
			pformat:("" #DEFAULT " Ваше помещение " #cPROJECT "#%i" #cWHITE " было продано агенству недвижимости. " #cGREEN "$%i" #cWHITE " возвращены на Вашу карту.",
				GetPremiseId(index),
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
					credit = abs(abs((money - credit)) - credit); 
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
			
			RemovePremiseOwner(playerid, index);
			
			Clear:premise_pvar(playerid);
		}
		else 
		{	
			format:g_string("UPDATE " #__CHARACTERS " SET c_refund = c_refund + %i WHERE c_id = %d LIMIT 1",
				money,
				premise_data[index][pr_character_id]
			);
			
			mysql_pquery(db, g_string);
		}
	}
	else if (buy_type == TYPE_BUY_RENT)
	{
		if (playerid != INVALID_PLAYER_ID)
		{
			pformat:("" #DEFAULT " Ваш договор с арендой помещения " #cPROJECT "#%i" #cWHITE " истёк.",
				GetPremiseId(index)
			);
			
			psend:(playerid, C_WHITE);
			
			if (IsPlayerRenovation(playerid))
			{
				SetRenovationMode(playerid, false);
			}
			
			RemovePremiseOwner(playerid, index);
			
			Clear:premise_pvar(playerid);
		}
	}
	
	premise_data[index][pr_lock] = 
	premise_data[index][pr_character_id] = 
	premise_data[index][pr_time] =
	premise_data[index][pr_debt] = 
	premise_data[index][pr_debt_count] = 
	premise_data[index][pr_buy_type] = 0;
	premise_data[index][pr_is_credit] = false;
	
	format:g_big_string(
		"UPDATE \
			" #__PREMISES " \
		SET \
			pr_buy_type = 0, \
			pr_character_id = 0, \
			pr_time = 0, \
			pr_buy_time = 0, \
			pr_debt = 0, \
			pr_debt_count = 0, \
			pr_entrance = 0, \
			pr_profit = 0, \
			pr_assort_stock = 0, \
			pr_cash_pos_x = 0.0, \
			pr_cash_pos_y = 0.0, \
			pr_cash_pos_z = 0.0, \
			pr_is_credit = 0, \
			pr_lock = 0 \
		WHERE \
			pr_id = %i \
		LIMIT 1",
		GetPremiseId(index)
	);
	
	mysql_pquery(db, g_big_string);
	return 1;
}

SellPremiseToPlayer(playerid, index, targetid, money)
{
	if (!IsPremiseBought(index))
	{
		return 0;
	}
	
	if (GetPremiseTypeBought(index) == TYPE_BUY_RENT)
	{
		SendClientMessage(playerid, C_WHITE, !NOT_RENT_ACCESS);
		return 0;
	}
	
	if (IsPremiseTied(index))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Чтобы продать данное помещение, необходимо его отвязать от компании.");
		return 0;
	}
	
	if (IsPremisePayCredit(index) 
	&& IsCreditCardExists(playerid) 
	&& IsCreditCardUse(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете продать данное помещение игроку, так как он был оплачен с помощью активного кредита.");
		return 0;
	}
	
	if (!GetPlayerAvaiblePremise(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок не может приобрести больше жилищных помещений.");
		SendClientMessage(targetid, C_WHITE, !#ERROR " Вы не можете приобрести больше жилищных помещений.");
		return 0;
	}
	
	if (GetPremiseDebt(index) > 0)
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
		money
	);
	
	RemovePremiseOwner(playerid, index);
	Clear:premise_pvar(playerid);
	
	GivePlayerCash(
		targetid,
		-money 
	);
	
	GivePremiseOwner(targetid, index);
	
	premise_data[index][pr_character_id] = GetCharacterId(targetid);
	premise_data[index][pr_time] = gettime() + (60 * 60 * 24);
	premise_data[index][pr_debt] = 
	premise_data[index][pr_debt_count] = 0;
	premise_data[index][pr_is_credit] = false;
	
	format:g_big_string(
		"UPDATE \
			" #__PREMISES " \
		SET \
			pr_character_id = %i, \
			pr_time = %i, \
			pr_buy_time = %i, \
			pr_debt = 0, \
			pr_debt_count = 0, \
			pr_is_credit = 0 \
		WHERE \
			pr_id = %i \
		LIMIT 1",
		premise_data[index][pr_character_id],
		premise_data[index][pr_time],
		gettime(),
		GetPremiseId(index)
	);
	
	mysql_pquery(db, g_big_string);
	
	ShowHelpPremise(targetid, TYPE_BUY_FULLY, TYPE_PAY_MONEY);
	return 1;
}

ResetPremisesCredit(playerid)
{
	new bool: exists;
	
	for (new i; i < MAX_PLAYER_PREMISES; i++)
	{
		if (player_premise[playerid][i] == INVALID_PARAM)
		{
			continue; 
		}
		
		premise_data[player_premise[playerid][i]][pr_is_credit] = false;
		exists = true;
	}
	
	if (exists)
	{
		format:g_string("UPDATE " #__PREMISES " SET pr_is_credit = 0 WHERE pr_character_id = %i",
			GetCharacterId(playerid),
			MAX_PLAYER_PREMISES
		);
		
		mysql_pquery(db, g_string);
	}
}

ResetPremiseInterior(index)
{
	new room = GetPremiseSettings(index, pset_rooms);
	
	Clear:room_data(index, TYPE_REN_PREMISE);
	Remove:all_furn_data(index, TYPE_REN_PREMISE);
	Update:reset_room_data(index, TYPE_REN_PREMISE);
	
	for (new i; i < room; i++)
	{
		SetPremiseInteriorMaterial(
			index, 
			i, 
			pint_roof_begin, 
			pint_roof_end, 
			TEXTURE_ROOF,
			0
		);

		SetPremiseInteriorMaterial(
			index, 
			i, 
			pint_wall_begin, 
			pint_wall_end, 
			TEXTURE_WALL,
			0
		);

		SetPremiseInteriorMaterial(
			index, 
			i, 
			pint_floor_begin, 
			pint_floor_end, 
			TEXTURE_FLOOR,
			0
		);
	}
	
	for (new i; i < sizeof furn_data; i++)
	{
		if (furn_data[i][f_id] == 0
		|| (furn_data[i][f_owner_index] != index 
		|| furn_data[i][f_owner_type] != TYPE_REN_PREMISE))
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
}