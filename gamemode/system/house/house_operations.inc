/*!
	@brief ���������� �������� ��� ������� �����
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

ShowHelpHouse(playerid, buy_type, pay_type = 0)
{
	clean:<g_big_string>;
	strcat(g_big_string, "" #SUCCESS " �����������\n\n");
	
	if (buy_type == TYPE_BUY_FULLY)
	{
		if (pay_type == TYPE_PAY_CREDIT)
		{
			strcat(g_big_string, "�� ������� ��������� �������� ��������� � ������� ��������� �����.\n\
			�� �� ������� ������� ��� ��������� ������� ������, ���� ��� ������ ����� �������.\n\
			������� ����� �������� �������� ����� ������� �� ��������� ��������� �����������.\n\n");
		}
		else 
		{
			strcat(g_big_string, "�� ������� ��������� �������� ���������.\n\n");
		}
		
		strcat(g_big_string, "������������ ������ ���� �������� �� " #cPROJECT "1" #cWHITE " ����.\n\
			 �� ���������� ����������� ������������ �����, ����� ����� ������ ���������\n\
			 ����� ������������ � ������ �����������.\n\
			 ������ ���������� � ������-�����.\n\n"
		);
	}
	
	else if (buy_type == TYPE_BUY_RENT) 
	{
		strcat(g_big_string, "�� ������� ���������� �������� ���������.\n\
			 �� ��������� �� ����� ���������� �������� ����� ������������.\n\
			 ������� ��� ����� � ������-�����.\n\n"
		);
	}
	
	strcat(g_big_string, "����������:\n \
	������� ���� ���� - " #cPROJECT "N ��� /hmenu" #cWHITE";\n \
	������ �������� ��������� - " #cPROJECT "/hlist" #cWHITE ";\n");
	strcat(g_big_string, "�������� ����� ��������� ��������� ����� � ����������.");
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", 
		g_big_string, 
		"�������", "" 
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
		SendClientMessage(playerid, C_WHITE, !#ERROR " �� ��� ��������� ���������. ��� ����, ����� ����������, ����������� " #cPROJECT "/evict" #cWHITE ".");
		return cmd_hmenu(playerid);
	}
	
	if (IsCreditCardExists(playerid) && IsCreditCardUse(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_CREDIT_EXISTS);
		return cmd_hmenu(playerid);
	}
	
	if (!GetPlayerAvaibleHouse(playerid))
	{
		pformat:("" #ERROR " �� �� ������ %s ������ �������� ���������.",
			buy_type == TYPE_BUY_RENT ? ("����������") : ("������")
		);
		
		psend:(playerid, C_WHITE);
		return cmd_hmenu(playerid);
	}
	
	if (IsHouseBought(index))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " ������ ��� ��� ���������� ��� ��������� ������ �������.");
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
		
		pformat:("" #ERROR " �� �� ������ %s ������ �������� ���������.",
			buy_type == TYPE_BUY_RENT ? ("����������") : ("������")
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
	
	// ������� ���������� � �������
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
			pformat:("" #DEFAULT " ���%s " #cPROJECT "#%i" #cWHITE " ���%s ������%s �����������. �������� � ������� " #cGREEN "$%i" #cWHITE " ���������� �� ���� �����.",
				(IsHouseType(index) == TYPE_HOUSE) ? (" ���") : ("� ��������"),
				GetHouseId(index),
				(IsHouseType(index) == TYPE_HOUSE) ? ("") : ("�"),
				(IsHouseType(index) == TYPE_HOUSE) ? ("") : ("�"),
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
				
				pformat:("" #DEFAULT " ����� ������� (" #cGREEN "$%i" #cWHITE ") ���� ���������� �� ������� ������� � �������������� �������.",
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
			pformat:("" #DEFAULT " ��� ������� � ������� %s " #cPROJECT "#%i" #cWHITE " ����.",
				(IsHouseType(index) == TYPE_HOUSE) ? ("����") : ("��������"),
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
		SendClientMessage(playerid, C_WHITE, !#ERROR " �� �� ������ ������� ������ ��� ������, ��� ��� �� ��� ������� � ������� ��������� �������.");
		return 0;
	}
	
	if (IsPlayerLodger(targetid) || IsHouseAccess(TYPE_HOUSE_LODGER, targetid, index))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " ��� ������� ��������� ������� ������, ��� ���������� ����������.");
		SendClientMessage(targetid, C_WHITE, !#ERROR " ��� ����, ����� ������� �����������, ���������� ����������. " #cGRAY "(/evict)");
		return 0;
	}
	
	if (!GetPlayerAvaibleHouse(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " ������ ����� �� ����� ���������� ������ �������� ���������.");
		SendClientMessage(targetid, C_WHITE, !#ERROR " �� �� ������ ���������� ������ �������� ���������.");
		return 0;
	}
	
	if (GetHouseDebt(index) > 0)
	{
		SendClientMessage(targetid, C_WHITE, !#ERROR " � ��� ������� ������������ �����������.");
		return 0;
	}
	
	if (!CheckSummForPay(targetid, money))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " � ������� ������ ������������ �������.");
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
			("" #DEFAULT " �� ���� ��������. �������� ���������, � ������� �� ���������, ������� ����� ����������.")
			: ("" #DEFAULT " �� ���� ��������. �������� ���������, � ������� �� ���������, ���� ������������� �������.")
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