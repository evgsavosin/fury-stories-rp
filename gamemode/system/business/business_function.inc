/*!
	@brief Функции для системы бизнесов
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

// Public function
Bus_OnGameModeInit()
{
	CreatePickupWith3DTextLabel("" #cPROJECT "H", INVALID_PARAM, CREATE_BUSINESS_POS);
	
	mysql_tquery(db, "SELECT * FROM " #__BUSINESSES "", "OnBusinessLoad", "");
}

Bus_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{
		if (IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, CREATE_BUSINESS_POS))
		{
			ShowBusinessList(playerid);
			return 0;
		}
	}
	
	return 1;
}

// Other function
GiveBusinessProfit(index, profit)
{
	if (business_data[index][b_profit] + profit <= 0)
	{
		return 0;
	}
	
	business_data[index][b_profit] += profit;
	Update:business_int(index, "b_profit", business_data[index][b_profit]);
	return 1;
}

GetFreeIndexForBusiness()
{
	for (new i; i < sizeof business_data; i++)
	{
		if (GetBusinessId(i) == 0)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

GetBusinessIndexById(const id)
{
	for (new i; i < MAX_BUSINESSES; i++)
	{
		if (GetBusinessId(i) == id)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

GetPlayerBusinessesCount(playerid)
{
	new count;
	
	for (new i; i < MAX_PLAYER_BUSINESSES; i++)
	{
		if (player_business[playerid][i] != INVALID_PARAM)
		{
			count++;
		}
	}
	
	return count;
}

GetBusinessAssortCount(const index)
{
	new count;
	
	for (new i; i < MAX_BUSINESS_ASSORT; i++)
	{
		if (bassort_data[index][i][ba_item_id] != 0)
		{
			count++;
		}
	}
	
	return count;
}

GetBusinessLinkPremiseCount(index)
{
	new count;
	
	for (new i; i < sizeof premise_data; i++)
	{
		if (premise_data[i][pr_business_id] == GetBusinessId(index))
		{
			count++;
		}
	}
	
	return count;
}

IsBusinessAccess(const type, playerid, const index)
{
	if (type == TYPE_BUSINESS_MEMBER)
	{
		return (GetBusinessMember(playerid) == index);
	}
	else if (type == TYPE_BUSINESS_OWNER)
	{
		for (new i; i < MAX_PLAYER_BUSINESSES; i++)
		{
			if (player_business[playerid][i] != index)
			{
				continue;
			}
			
			return 1;
		}
	}
	
	return 0;
}

CheckBusinessAccess(type, playerid, index, perm = INVALID_PARAM)
{
	if (type == TYPE_BUSINESS_MEMBER)
	{	
		if (perm == INVALID_PARAM)
		{
			if (IsBusinessAccess(TYPE_BUSINESS_OWNER, playerid, index)
			|| IsBusinessAccess(TYPE_BUSINESS_MEMBER, playerid, index))
			{
				return 1;
			}
		}
		else 
		{
			if (IsBusinessAccess(TYPE_BUSINESS_OWNER, playerid, index)
			|| (IsBusinessAccess(TYPE_BUSINESS_MEMBER, playerid, index) 
			&& GetBusinessMemberPerm(playerid, perm)))
			{
				return 1;
			}
		}
	}
	else if (type == TYPE_BUSINESS_OWNER)
	{
		if (IsBusinessAccess(TYPE_BUSINESS_OWNER, playerid, index))
		{
			return 1;
		}
	}
	
	return 0;
}

IsValidBusinessNameString(const text[])
{
	new len = strlen(text);
		
	if (!(3 <= len <= MAX_BUSINESS_NAME))
	{
		return 0;
	}
	
	while (len-- != 0)
	{
		switch(text[len])
		{	
			case 'а' .. 'я', 'А' .. 'Я', '/', '\n', '`', '~', '%', '^', '&', '[', ']', '{', '}', '|', ''' :
			{
				return 0;
			}
		}
	}
	
	return 1;
}

GiveBusinessOwner(playerid, index) 
{
	for (new i; i < MAX_PLAYER_BUSINESSES; i++)
	{
		if (player_business[playerid][i] != INVALID_PARAM)
		{
			continue;
		}
		
		player_business[playerid][i] = index;
		
		break;
	}
}

IsBusinessOwner(playerid, index = INVALID_PARAM)
{
	for (new i; i < MAX_PLAYER_BUSINESSES; i++)
	{
		if (index != INVALID_PARAM)
		{
			if (player_business[playerid][i] == index)
			{
				return 1;
			}
		}
		else 
		{
			if (player_business[playerid][i] != INVALID_PARAM)
			{
				return 1;
			}
		}
	}
	
	return 0;
}

RemoveBusinessOwner(playerid, index)
{
	for (new i; i < MAX_PLAYER_BUSINESSES; i++)
	{
		if (player_business[playerid][i] != index)
		{
			continue;
		}
		
		player_business[playerid][i] = INVALID_PARAM;
		
		break;
	}
}

GetPlayerMaxBusinesses(playerid)
{
	if (GetUserVip(playerid) >= VIP_STARTER)
	{
		return MAX_PLAYER_BUSINESSES;
	}
	
	return MAX_PLAYER_BUSINESSES - 1;
}

GetPlayerAvaibleBusiness(playerid)
{
	return (GetPlayerMaxBusinesses(playerid) - GetPlayerBusinessesCount(playerid)) <= 0 ? false : true;
}

SendBusinessMessage(bindex, color, const text[])
{
	foreach (new playerid : Player)
	{
		if (GetBusinessMember(playerid) == bindex)
		{	
			SendClientMessage(playerid, color, text);
		}
	}
}

Remove:business_data(playerid, index)
{
	for (new i; i < sizeof premise_data; i++)
	{
		if (premise_data[i][pr_business_id] == GetBusinessId(index))
		{
			PremiseUntie(i, index);
		}
	}
	
	format:g_string("DELETE FROM " #__BMEMBERS " WHERE bm_business_id = %i", 
		GetBusinessId(index)
	);
	
	mysql_pquery(db, g_string);
	
	foreach (new i : Player)
	{
		if (GetBusinessMember(i) != index)
		{
			continue;
		}
		
		Remove:bmember_data(INVALID_PARAM, playerid);
	}
	
	if (playerid != INVALID_PLAYER_ID)
	{
		GiveDebitCardMoney(playerid, business_data[index][b_profit]);
		RemoveBusinessOwner(playerid, index);
	}
	else 
	{
		format:g_string("UPDATE " #__CHARACTERS " SET c_bank = c_bank + %i WHERE c_id = %i LIMIT 1",
			business_data[index][b_profit],
			business_data[index][b_character_id]
		);
		
		mysql_pquery(db, g_string);
	}
	
	format:g_string("DELETE FROM " #__BUSINESSES " WHERE b_id = %i", GetBusinessId(index));
	mysql_pquery(db, g_string);
	
	Clear:business_data(index);
}