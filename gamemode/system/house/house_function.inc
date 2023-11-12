/*!
	@brief Функции системы домов
	@author Found (evg.savosin)
	@date 16.12.2016, update 21.03.2018
*/

// Publics 
Clear:house_pvar(playerid)
{
	DeletePVar(playerid, "House:Select");
	DeletePVar(playerid, "House:IsOwner");
	DeletePVar(playerid, "House:BuyType");
	DeletePVar(playerid, "House:BuyIndex");
	
	DeletePVar(playerid, "Lodger:Select");
	
	DeletePVar(playerid, "Garage:Select");
}

House_OnGameModeInit()
{
	HouseInteriorStaticObjects();
	HouseInteriorText3D();
	
	mysql_tquery(db, "SELECT * FROM " #__HOUSES "", "OnHouseLoad", "");
	
	return 1;
}

House_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{	
		for (new index, type, world; index < sizeof house_data; index++)
		{
			if (GetHouseId(index) == 0)
			{
				continue;
			}
			
			type = house_data[index][h_int_type];
			world = GetCharacterWorld(playerid);
			
			if (world == house_data[index][h_world] 
			&& IsPlayerInRangeOfPoint(playerid, 
			FACTOR_TELEPORT_RADIUS, 
			house_data[index][h_pos][0], 
			house_data[index][h_pos][1], 
			house_data[index][h_pos][2]))
			{	
				SetPVarInt(playerid, "House:SelectPickup", index);

				ShowHouseInformation(playerid, index, D_HOUSE, false, "Войти", "Закрыть");
				
				return 0;
			}
			
			else if (house_data[index][h_id] == world 
				&& IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, 
					house_settings[type][hset_pos][0], 
					house_settings[type][hset_pos][1], 
					house_settings[type][hset_pos][2])
			)
			{
				if (house_data[index][h_lock])
				{
					return GameTextForPlayer(playerid, "~w~CLOSED", 2000, 4);
				}
				
				Move:player(playerid, 
					house_data[index][h_pos][0], 
					house_data[index][h_pos][1], 
					house_data[index][h_pos][2], 
					house_data[index][h_world], 
					house_data[index][h_interior],
					true,
					house_data[index][h_pos][3]
				);	
				
				return 0;
			}
		}
	}
	
	if (PRESSED(KEY_NO))
	{
		if (HouseMenu(playerid, false))
		{
			printf("HouseMenu key block");
			return 0;
		}
		
		if (GarageMenu(playerid, false))
		{
			printf("GarageMenu key block");
			return 0;
		}
	}
	
	return 1;
}

// Functions

Create:house(index)
{
	strglobalclear();
	
	format:g_string("%s #%d", 
		(!house_data[index][h_interior]) ? ("Дом") : ("Квартира"),
		house_data[index][h_id]
	);
	
	house_data[index][h_text] = CreateDynamic3DTextLabel(
		g_string, 
		-1, 
		house_data[index][h_pos][0], 
		house_data[index][h_pos][1], 
		house_data[index][h_pos][2], 
		TEXT3D_DRAW_DISTANCE, 
		_, 
		_, 
		1, 
		house_data[index][h_world], 
		house_data[index][h_interior], 
		_, 
		TEXT3D_DRAW_DISTANCE
	);

	house_data[index][h_pickup] = CreateDynamicPickup(
		!house_data[index][h_character_id] ? (1273) : (1272), 
		1, 
		house_data[index][h_pos][0], 
		house_data[index][h_pos][1], 
		house_data[index][h_pos][2], 
		house_data[index][h_world], 
		house_data[index][h_interior], 
		-1, 
		PICKUP_DRAW_DISTANCE
	);
	
	Create:house_int_obj(index, house_data[index][h_int_type]);
}

Destroy:house(index)
{
	Destroy:house_int_obj(index);
	
	if (IsValidDynamicPickup(house_data[index][h_pickup]))
	{	
		DestroyDynamicPickup(house_data[index][h_pickup]);
	}

	if (IsValidDynamic3DTextLabel(house_data[index][h_text]))
	{	
		DestroyDynamic3DTextLabel(house_data[index][h_text]);
	}
}

Update:house(index)
{
	if (IsValidDynamicPickup(house_data[index][h_pickup]))
	{	
		DestroyDynamicPickup(house_data[index][h_pickup]);
	}
	
	house_data[index][h_pickup] = CreateDynamicPickup(
		!house_data[index][h_character_id] ? (1273) : (1272), 
		1, 
		house_data[index][h_pos][0], 
		house_data[index][h_pos][1], 
		house_data[index][h_pos][2], 
		house_data[index][h_world], 
		house_data[index][h_interior], 
		-1, 
		PICKUP_DRAW_DISTANCE
	);
}

HouseLock(playerid, index = INVALID_PARAM)
{
	new server_tick = GetTickCount();
	
	if (GetPVarInt(playerid, "House:LockTime") > server_tick)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
		return;
	}
	
	if (index == INVALID_PARAM)
	{
		index = GetHouseAroundOfPlayer(playerid);
			
		if (index == INVALID_PARAM)
		{
			return;
		}
	
		if (!CheckHouseAccess(TYPE_HOUSE_LODGER, playerid, index))
		{
			return;
		}
	}
	
	house_data[index][h_lock] = !house_data[index][h_lock];
	GameTextForPlayer(playerid, (house_data[index][h_lock]) ? ("~r~LOCKED") : ("~g~UNLOCKED"), 2000, 4);
	Update:house_int(index, "h_lock", house_data[index][h_lock]);
	
	SetPVarInt(playerid, "House:LockTime", server_tick + 1000);
}

/// Summ function 

function Float: GetHouseDebtInPercent(index)
{
	return Float: (house_data[index][h_debt] / house_data[index][h_price]) * 100.00; // процент задолжности от общей суммы
}

GetSaleHousePrice(index)
{
	return (house_data[index][h_price] - house_data[index][h_debt]) + house_data[index][h_money];
}

GetMaxSaleHousePrice(index)
{		
	return house_data[index][h_price] * 2;
}

GetMinSaleHousePrice(index)
{
	return floatround(0.1 * house_data[index][h_price]);
}

/// Summ function - end
SetHouseMark(playerid, index)
{	
	if (IsHouseType(index) == TYPE_HOUSE)
	{
		SetIncludeGPS(
			playerid, 
			house_data[index][h_pos][0], 
			house_data[index][h_pos][1], 
			house_data[index][h_pos][2]
		);
	}
	else 
	{
		new hindex;
		
		if ((hindex = GetHostelIndexByHouse(index)) != INVALID_PARAM)
		{
			SetIncludeGPS(
				playerid, 
				hostel_data[hindex][hos_pos][0], 
				hostel_data[hindex][hos_pos][1], 
				hostel_data[hindex][hos_pos][2]
			);
		}
	}
}

GetHouseStreetZone(index, zone[], len = sizeof(zone))
{	
	zone[0] = EOS;
	
	if (IsHouseType(index) == TYPE_HOUSE)
	{
		GetZoneName(
			house_data[index][h_pos][0], 
			house_data[index][h_pos][1], 
			zone, 
			len
		);
	}
	else 
	{
		new hindex;
		
		if ((hindex = GetHostelIndexByHouse(index)) != INVALID_PARAM)
		{
			GetZoneName(
				hostel_data[hindex][hos_pos][0], 
				hostel_data[hindex][hos_pos][1], 
				zone, 
				len
			);
		}
		else 
		{
			strcat(zone, "Undefined", len);
		}
	}
}

GetHouseAroundOfPlayer(playerid, Float: distance = 1.0, bool: in_house = true)
{
	new world = GetCharacterWorld(playerid);
			
	for (new i; i < sizeof house_data; i++)
	{
		if (world == house_data[i][h_world]
		&& GetPlayerDistanceFromPoint(playerid, 
			house_data[i][h_pos][0],
			house_data[i][h_pos][1],
			house_data[i][h_pos][2]
		) <= distance || (in_house && IsPlayerInHouse(playerid, i)))
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

IsPlayerInHouse(playerid, index, Float: distance = 50.0)
{
	if (index == INVALID_PARAM)
	{
		return 0;
	}
	
	if (GetCharacterInt(playerid) != INT_HOUSE)
	{
		return 0;
	}
	
	if (GetHouseId(index) != GetCharacterWorld(playerid))
	{
		return 0;
	}
	
	new type = house_data[index][h_int_type];
	
	return (GetPlayerDistanceFromPoint(playerid,
		house_settings[type][hset_pos][0],
		house_settings[type][hset_pos][1],
		house_settings[type][hset_pos][2]) <= distance);
}

IsValidHouse(const house_id)
{
	if (house_id == 0)
	{
		return 0;
	}
	
	for (new i; i < sizeof house_data; i++)
	{
		if (house_data[i][h_id] != house_id)
		{
			continue;
		}
		
		return 1;
	}
	
	return 0;
}

GetPlayerHouse(playerid, only_house = false, buy_fully = false)
{
	if (!only_house && lod_data[playerid][lod_house_index] != INVALID_PARAM)
	{
		return lod_data[playerid][lod_house_index];
	}
	
	for (new i; i < MAX_PLAYER_HOUSES; i++)
	{
		if (player_house[playerid][i] == INVALID_PARAM)
		{
			continue;
		}
		
		if (buy_fully && GetHouseTypeBought(player_house[playerid][i]) != TYPE_BUY_FULLY)
		{
			continue;
		}

		return player_house[playerid][i];
	}
	
	return INVALID_PARAM;
}

GetPlayerHousesCount(playerid)
{
	new houses_count;
		
	for (new i; i < MAX_PLAYER_HOUSES; i++)
	{
		if (player_house[playerid][i] == INVALID_PARAM)
		{
			continue;
		}

		houses_count++;
	}
	
	return houses_count;
}

GetPlayerMaxHouses(playerid)
{
	switch (user_data[playerid][u_vip])
	{
		case 2 .. 4:
		{
			return MAX_PLAYER_HOUSES;
		}
	}
	
	return MAX_PLAYER_HOUSES - 1;
}

GetPlayerAvaibleHouse(playerid)
{
	return (GetPlayerMaxHouses(playerid) - GetPlayerHousesCount(playerid)) <= 0 ? false : true;
}

GetHouseIndexById(house_id)
{
	if (0 >= house_id)
	{
		return INVALID_PARAM;
	}
	
	for (new i; i < sizeof house_data; i++)
	{
		if (house_data[i][h_id] != house_id)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

GiveHouseOwner(playerid, index) // Выдаем овнера при авторизации
{
	for (new i; i < MAX_PLAYER_HOUSES; i++)
	{
		if (player_house[playerid][i] != INVALID_PARAM)
		{
			continue;
		}
		
		player_house[playerid][i] = index;
		
		break;
	}
}

RemoveHouseOwner(playerid, index)
{
	for (new i; i < MAX_PLAYER_HOUSES; i++)
	{
		if (player_house[playerid][i] != index)
		{
			continue;
		}
		
		player_house[playerid][i] = INVALID_PARAM;
		
		break;
	}
}

GetHouseOwnerIdByIndex(index)
{
	foreach (new playerid : Player)
	{
		for (new i; i < MAX_PLAYER_HOUSES; i++)
		{
			if (player_house[playerid][i] == index)
			{
				return playerid;
			}
		}
	}
	
	return INVALID_PLAYER_ID;
}

IsHouseAccess(const type, playerid, const index)
{
	if (type == TYPE_HOUSE_LODGER)
	{
		return (lod_data[playerid][lod_house_index] == index);
	}
	else if (type == TYPE_HOUSE_OWNER)
	{
		for (new i; i < MAX_PLAYER_HOUSES; i++)
		{
			if (player_house[playerid][i] != index)
			{
				continue;
			}
			
			return 1;
		}
	}
	
	return 0;
}

CheckHouseAccess(type, playerid, index, perm = INVALID_PARAM)
{
	if (type == TYPE_HOUSE_LODGER)
	{	
		if (perm == INVALID_PARAM)
		{
			if (IsHouseAccess(TYPE_HOUSE_OWNER, playerid, index)
			|| IsHouseAccess(TYPE_HOUSE_LODGER, playerid, index))
			{
				return 1;
			}
		}
		else 
		{
			if (IsHouseAccess(TYPE_HOUSE_OWNER, playerid, index)
			|| (IsHouseAccess(TYPE_HOUSE_LODGER, playerid, index) 
			&& GetLodgerPerm(playerid, perm)))
			{
				return 1;
			}
		}
	}
	else if (type == TYPE_HOUSE_OWNER)
	{
		if (IsHouseAccess(TYPE_HOUSE_OWNER, playerid, index))
		{
			return 1;
		}
	}
	
	return 0;
}

SendHouseMessage(index, color, text[], Float: distance = 20.0)
{
	foreach (new playerid : Player)
	{
		if (!IsPlayerInHouse(playerid, index, distance))
		{
			continue;
		}
		
		SendSplitMessage(playerid, color, text);
	}
	
	return 1;
}

// Other functions

function OnHouseCreate(index, playerid)
{
	new room = house_settings[house_data[index][h_int_type]][hset_rooms];
		
	house_data[index][h_id] = cache_insert_id();
	
	Create:house(index);
	
	clean:<g_big_string>;
	strcat(g_big_string, "INSERT INTO " #__ROOMS " (r_owner_type, r_owner_id, r_number) \
	VALUES ");
	
	for (new i; i < room; i++)
	{
		format:g_small_string("(%i, %i, %i)", TYPE_REN_HOUSE, house_data[index][h_id], i);
		strcat(g_big_string, g_small_string);
		
		if (i != (room - 1))
		{
			strcat(g_big_string, ",");
		}
		
		SetHouseInteriorMaterial(index, i, 
			hint_roof_begin, 
			hint_roof_end, 
			TEXTURE_ROOF,
			hroom_data[index][i][r_roof] 
		);
		
		SetHouseInteriorMaterial(index, i, 
			hint_wall_begin, 
			hint_wall_end, 
			TEXTURE_WALL,
			hroom_data[index][i][r_wall] 
		);
		
		SetHouseInteriorMaterial(index, i, 
			hint_floor_begin, 
			hint_floor_end, 
			TEXTURE_FLOOR,
			hroom_data[index][i][r_floor] 
		);
	}
	
	mysql_tquery(db, g_big_string);
	
	if (playerid != INVALID_PLAYER_ID)
	{
		pformat:("" #DEFAULT " Дом с ID: " #cPROJECT "%i" #cWHITE ", успешно создан.", house_data[index][h_id]);
		psend:(playerid, C_WHITE);
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Установить гараж дому - " #cPROJECT "/addgarage" #cWHITE ".");
	}
		
	printf("[OnHouseCreate]: House [ID:%d] has been created.",
		house_data[index][h_id]
	);
	
	return 1;
}