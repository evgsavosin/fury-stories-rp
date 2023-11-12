/*!
	@brief Функции для системы помещений
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

// Public function
Clear:premise_pvar(playerid)
{
	DeletePVar(playerid, "Premise:Select");
	DeletePVar(playerid, "Premise:IsOwner");
	DeletePVar(playerid, "Premise:BuyType");
	DeletePVar(playerid, "Premise:BuyIndex");
}

Premise_OnGameModeInit()
{
	PremiseInteriorText3D();
	PremiseInteriorStaticObjects();
	
	mysql_tquery(db, "SELECT * FROM " #__PREMISES "", "OnPremiseLoad", "");
}

Premise_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{	
		for (new i, type, world; i < sizeof premise_data; i++)
		{
			if (GetPremiseId(i) == 0)
			{
				continue;
			}
			
			type = premise_data[i][pr_int_type];
			world = GetPlayerVirtualWorld(playerid); 
			
			if (world == premise_data[i][pr_world] 
			&& IsPlayerInRangeOfPoint(playerid, 
			FACTOR_TELEPORT_RADIUS, 
			premise_data[i][pr_pos][0], 
			premise_data[i][pr_pos][1], 
			premise_data[i][pr_pos][2]))
			{	
				SetPVarInt(playerid, "Premise:SelectPickup", i);

				ShowPremiseInformation(playerid, i, D_PREMISE, false, "Войти", "Закрыть");
				
				return 0;
			}
			else if (premise_data[i][pr_id] == world 
			&& IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, 
			premise_settings[type][pset_pos][0], 
			premise_settings[type][pset_pos][1], 
			premise_settings[type][pset_pos][2]))
			{
				if (premise_data[i][pr_lock])
				{
					GameTextForPlayer(playerid, "~r~~w~CLOSED", 2000, 4);
					return 1;
				}
				
				Move:player(playerid, 
					premise_data[i][pr_pos][0], 
					premise_data[i][pr_pos][1], 
					premise_data[i][pr_pos][2], 
					premise_data[i][pr_world], 
					premise_data[i][pr_interior],
					true,
					premise_data[i][pr_pos][3]
				);	
				
				return 0;
			}
		}
	}

	if (PRESSED(KEY_NO))
	{
		if (PremiseMenu(playerid, false))
		{
			printf("PremiseMenu key block");
			return 0;
		}
	}
	
	return 1;
}

// Other function
IsPremiseOwnerAccess(playerid, index)
{
	for (new i; i < MAX_PLAYER_PREMISES; i++)
	{
		if (player_premise[playerid][i] == index)
		{
			return 1;
		}
	}
	
	return 0;
}

CheckPremiseAccess(type, playerid, index, perm = INVALID_PARAM)
{
	if (type == TYPE_PREMISE_MEMBER)
	{
		if (IsPremiseOwnerAccess(playerid, index))
		{
			return 1;
		}
		
		if (!IsPremiseTied(index))
		{
			return 0;
		}
		
		new bindex = GetBusinessIndexById(GetPremiseBusinessId(index));
		
		if (bindex == INVALID_PARAM)
		{
			return 0;
		}
		
		return CheckBusinessAccess(type, playerid, bindex, perm);
	}
	else if (type == TYPE_PREMISE_OWNER)
	{
		return IsPremiseOwnerAccess(playerid, index);
	}
	
	return 1;
}

PremiseTie(index, bindex)
{
	premise_data[index][pr_business_id] = GetBusinessId(bindex);
	Update:premise_business(index);
}

PremiseUntie(index, bindex)
{	
	if (!IsPremiseTied(index))
	{
		return;
	}
	
	GiveBusinessProfit(bindex, GetPremiseProfit(index));
	
	Destroy:premise_cash_text(index);
	Update:premise_cash(index);
	
	Clear:premise_business(index);
	Update:premise_business(index);
	
	bindex = GetBusinessIndexById(premise_data[index][pr_business_id]);
	Remove:all_bassort_data(bindex);
	
	Clear:premise_visitors(index);
}

GivePremiseProfit(index, profit)
{
	if (premise_data[index][pr_profit] + profit <= 0)
	{
		return 0;
	}
	
	premise_data[index][pr_profit] += profit;
	Update:premise_int(index, "pr_profit", premise_data[index][pr_profit]);
	return 1;
}

GivePremiseAssortStock(index, assort_stock)
{
	if (premise_data[index][pr_assort_stock] + assort_stock <= 0)
	{
		return 0;
	}
	
	premise_data[index][pr_assort_stock] += assort_stock;
	Update:premise_int(index, "pr_assort_stock", premise_data[index][pr_assort_stock]);
	return 1;
}

SetPremiseMark(playerid, index)
{	
	SetIncludeGPS(
		playerid, 
		premise_data[index][pr_pos][0], 
		premise_data[index][pr_pos][1], 
		premise_data[index][pr_pos][2]
	);
}

GetPremiseStreetZone(index, zone[], len = sizeof(zone))
{	
	zone[0] = EOS;
	
	GetZoneName(
		premise_data[index][pr_pos][0], 
		premise_data[index][pr_pos][1], 
		zone, 
		len
	);
}

GivePremiseOwner(playerid, index) 
{
	for (new i; i < MAX_PLAYER_PREMISES; i++)
	{
		if (player_premise[playerid][i] != INVALID_PARAM)
		{
			continue;
		}
		
		player_premise[playerid][i] = index;
		
		break;
	}
}

RemovePremiseOwner(playerid, index)
{
	for (new i; i < MAX_PLAYER_PREMISES; i++)
	{
		if (player_premise[playerid][i] != index)
		{
			continue;
		}
		
		player_premise[playerid][i] = INVALID_PARAM;
		
		break;
	}
}

GetPlayerPremise(playerid)
{
	for (new i; i < sizeof premise_data; i++)
	{
		if (!CheckPremiseAccess(TYPE_PREMISE_MEMBER, playerid, i))
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}


GetPlayerPremisesCount(playerid)
{
	new count;
	
	for (new i; i < MAX_PLAYER_PREMISES; i++)
	{
		if (player_premise[playerid][i] != INVALID_PARAM)
		{
			count++;
		}
	}
	
	return count;
}

GetPlayerMaxPremises(playerid)
{
	#pragma unused playerid
	
	return MAX_PLAYER_PREMISES;
}

GetPlayerAvaiblePremise(playerid)
{
	return (GetPlayerMaxPremises(playerid) - GetPlayerPremisesCount(playerid)) <= 0 ? false : true;
}

GetPremiseIndexById(premise_id)
{
	if (0 >= premise_id)
	{
		return INVALID_PARAM;
	}
	
	for (new i; i < sizeof premise_data; i++)
	{
		if (premise_data[i][pr_id] != premise_id)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

GetPremiseAroundOfPlayer(playerid, in_premise = true)
{
	new world = GetPlayerVirtualWorld(playerid);
		
	for (new i; i < sizeof premise_data; i++)
	{
		if (in_premise)
		{
			if (GetPlayerDistanceFromPoint(playerid, 
				premise_data[i][pr_pos][0],
				premise_data[i][pr_pos][1],
				premise_data[i][pr_pos][2]
			) <= 1.0 || IsPlayerInPremise(playerid, i, world))
			{
				return i;
			}
		}
		else 
		{
			if (GetPlayerDistanceFromPoint(playerid, 
				premise_data[i][pr_pos][0],
				premise_data[i][pr_pos][1],
				premise_data[i][pr_pos][2]
			) <= 1.0)
			{
				return i;
			}
		}
	}
	
	return INVALID_PARAM;
}

IsPlayerInPremise(playerid, index, world, Float: distance = 50.0)
{
	if (index == INVALID_PARAM || world == 0 
	|| GetPlayerInterior(playerid) != INT_PREMISE)
	{
		return 0;
	}
	
	new type = premise_data[index][pr_int_type];
	
	return (GetPlayerDistanceFromPoint(playerid,
		premise_settings[type][pset_pos][0],
		premise_settings[type][pset_pos][1],
		premise_settings[type][pset_pos][2]) <= distance);
}

IsValidPremise(const premise_id)
{
	if (premise_id == 0)
	{
		return 0;
	}
	
	for (new i; i < sizeof premise_data; i++)
	{
		if (premise_data[i][pr_id] != premise_id)
		{
			continue;
		}
		
		return 1;
	}
	
	return 0;
}

IsValidPremiseNameString(const text[])
{
	new len = strlen(text);
		
	if (!(0 <= len <= MAX_PREMISE_NAME))
	{
		return 0;
	}
	
	while (len-- != 0)
	{
		switch(text[len])
		{	
			case 'а' .. 'я', 'А' .. 'Я', '\n', '`', '~', '%', '^', '&', '[', ']', '{', '}', '|' :
			{
				return 0;
			}
		}
	}
	
	return 1;
}

GetPremiseOwnerIdByIndex(index)
{
	foreach (new playerid : Player)
	{
		for (new i; i < MAX_PLAYER_PREMISES; i++)
		{
			if (player_premise[playerid][i] == index)
			{
				return playerid;
			}
		}
	}
	
	return INVALID_PLAYER_ID;
}

SendPremiseMessage(index, color, const text[])
{
	foreach (new playerid : Player)
	{
		if (!IsPlayerInPremise(playerid, index, GetPremiseId(index), 20.0))
		{
			continue;
		}
		
		SendClientMessage(playerid, color, text);
	}
	
	return 1;
}

PremiseLock(playerid, index = INVALID_PARAM)
{	
	new server_tick = GetTickCount();
	
	if (GetPVarInt(playerid, "Premise:LockTime") > server_tick)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
		return;
	}
	
	if (index == INVALID_PARAM)
	{
		index = GetPremiseAroundOfPlayer(playerid, false);
			
		if (index == INVALID_PARAM)
		{
			return;
		}
		
		if (!CheckPremiseAccess(TYPE_PREMISE_MEMBER, playerid, index, bm_perm_lock))
		{
			return;
		}
	}
	
	premise_data[index][pr_lock] = !premise_data[index][pr_lock];
	GameTextForPlayer(playerid, (premise_data[index][pr_lock]) ? ("~r~LOCKED") : ("~g~UNLOCKED"), 2000, 4);
	Update:premise_int(index, "pr_lock", premise_data[index][pr_lock]);
	
	SetPVarInt(playerid, "Premise:LockTime", server_tick + 1000);
}

// Summ function
function Float: GetPremiseDebtInPercent(index)
{
	return Float: float(premise_data[index][pr_debt] * 100) / premise_data[index][pr_price]; // процент задолжности от общей суммы
}

GetSalePremisePrice(index)
{
	return premise_data[index][pr_price] - premise_data[index][pr_debt];
}

GetMaxSalePremisePrice(index)
{		
	return premise_data[index][pr_price] * 2;
}

GetMinSalePremisePrice(index)
{
	return floatround(0.1 * premise_data[index][pr_price]);
}

/// Prefix function
Create:premise(index)
{
	strglobalclear();
	
	format:g_string("%s\n#%d", 
		premise_data[index][pr_name],
		premise_data[index][pr_id]
	);
	
	premise_data[index][pr_text] = CreateDynamic3DTextLabel(
		g_string, 
		-1, 
		premise_data[index][pr_pos][0], 
		premise_data[index][pr_pos][1], 
		premise_data[index][pr_pos][2], 
		TEXT3D_DRAW_DISTANCE, 
		_, 
		_, 
		1, 
		premise_data[index][pr_world], 
		premise_data[index][pr_interior], 
		_, 
		TEXT3D_DRAW_DISTANCE
	);

	premise_data[index][pr_pickup] = CreateDynamicPickup(
		PICKUP_MODEL, 
		1, 
		premise_data[index][pr_pos][0], 
		premise_data[index][pr_pos][1], 
		premise_data[index][pr_pos][2], 
		premise_data[index][pr_world], 
		premise_data[index][pr_interior], 
		-1, 
		PICKUP_DRAW_DISTANCE
	);
	
	if (IsPremiseCashExists(index))
	{
		Create:premise_cash_text(index);
	}
	
	Create:premise_int_obj(index, premise_data[index][pr_int_type]);
}

Destroy:premise(index)
{
	Destroy:premise_int_obj(index);
	
	if (IsValidDynamicPickup(premise_data[index][pr_pickup]))
	{	
		DestroyDynamicPickup(premise_data[index][pr_pickup]);
	}

	if (IsValidDynamic3DTextLabel(premise_data[index][pr_text]))
	{	
		DestroyDynamic3DTextLabel(premise_data[index][pr_text]);
	}
	
	Destroy:premise_cash_text(index);
}

Create:premise_cash_text(index)
{
	premise_data[index][pr_cash_text] = CreateDynamic3DTextLabel(
		"Касса\n" #cPROJECT "H", 
		-1, 
		premise_data[index][pr_cash_pos][0], 
		premise_data[index][pr_cash_pos][1], 
		premise_data[index][pr_cash_pos][2], 
		TEXT3D_DRAW_DISTANCE, 
		_, 
		_, 
		1, 
		premise_data[index][pr_id], 
		INT_PREMISE, 
		_, 
		TEXT3D_DRAW_DISTANCE
	);
}

Destroy:premise_cash_text(index)
{
	if (IsValidDynamic3DTextLabel(premise_data[index][pr_cash_text]))
	{	
		DestroyDynamic3DTextLabel(premise_data[index][pr_cash_text]);
	}
	
	premise_data[index][pr_cash_text] = Text3D: INVALID_3DTEXT_ID;
}

Update:premise_text(index)
{
	if (IsValidDynamic3DTextLabel(premise_data[index][pr_text]))
	{	
		DestroyDynamic3DTextLabel(premise_data[index][pr_text]);
	}
	
	format:g_string("%s\n#%d", 
		premise_data[index][pr_name],
		premise_data[index][pr_id]
	);
	
	premise_data[index][pr_text] = CreateDynamic3DTextLabel(
		g_string, 
		-1, 
		premise_data[index][pr_pos][0], 
		premise_data[index][pr_pos][1], 
		premise_data[index][pr_pos][2], 
		TEXT3D_DRAW_DISTANCE, 
		_, 
		_, 
		1, 
		premise_data[index][pr_world], 
		premise_data[index][pr_interior], 
		_, 
		TEXT3D_DRAW_DISTANCE
	);
}

function OnPremiseCreate(index, playerid)
{
	new room = premise_settings[premise_data[index][pr_int_type]][pset_rooms];
		
	premise_data[index][pr_id] = cache_insert_id();
	
	Create:premise(index);
	
	clean:<g_big_string>;
	strcat(g_big_string, "INSERT INTO " #__ROOMS " (r_owner_type, r_owner_id, r_number) \
	VALUES");
	
	for (new i; i < room; i++)
	{
		format:g_small_string("(%i, %i, %i)", TYPE_REN_PREMISE, premise_data[index][pr_id], i);
		strcat(g_big_string, g_small_string);
		
		if (i != (room - 1))
		{
			strcat(g_big_string, ",");
		}
		
		SetPremiseInteriorMaterial(index, i, 
			pint_roof_begin, 
			pint_roof_end, 
			TEXTURE_ROOF,
			proom_data[index][i][r_roof] 
		);
		
		SetPremiseInteriorMaterial(index, i, 
			pint_wall_begin, 
			pint_wall_end, 
			TEXTURE_WALL,
			proom_data[index][i][r_wall] 
		);
		
		SetPremiseInteriorMaterial(index, i, 
			pint_floor_begin, 
			pint_floor_end, 
			TEXTURE_FLOOR,
			proom_data[index][i][r_floor] 
		);
	}
	
	mysql_tquery(db, g_big_string);
	
	if (playerid != INVALID_PLAYER_ID)
	{
		pformat:("" #DEFAULT " Помещение с ID: " #cPROJECT "%i" #cWHITE ", успешно создано.", premise_data[index][pr_id]);
		psend:(playerid, C_WHITE);
	}
		
	printf("[OnPremiseCreate]: Premise [ID:%d] has been created.",
		premise_data[index][pr_id]
	);
	
	return 1;
}
