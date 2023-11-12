/*!
	@brief Основной файл с функциями для системы транспорта
	@author Found (evg.savosin)
	@date 16.12.2016
*/

Clear:vehicle_pvar(playerid)
{
	DeletePVar(playerid, "Vehicle:Select");
	DeletePVar(playerid, "Vehicle:UseClist");
}

Vehicle_OnGameModeInit()
{
	clean:<g_string>;
	
	format:g_string("DELETE FROM " #__VEHICLES " WHERE v_buy_type = %i AND v_rent_time <= %i",
		TYPE_BUY_RENT,
		gettime()
	);
	
	mysql_tquery(db, g_string);
	
	return 1;
}

Vehicle_OnPlayerConnect(playerid)
{
	player_speedometer[playerid] = INVALID_PARAM;
	
	return 1;
}

function Vehicle_OnPlayerDeath(playerid, killerid, reason) 
{	
	return 1; 
}

Vehicle_OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	
	if (player_speedometer[playerid] != INVALID_PARAM)
	{
		KillTimer(player_speedometer[playerid]);
		player_speedometer[playerid] = INVALID_PARAM;
	}
	
	for (new i = 1, j = GetVehiclePoolSize(); i <= j; i++)
	{
		if (!IsOwnerVehicle(playerid, i))
		{
			continue;
		}
		
		Destroy:vehicle_data(playerid, i, 60000 * 5, DELVEH_BY_SERVER);
	}
	
	return 1;
}

Vehicle_OnVehicleSpawn(vehicleid)
{
	SetVehiclePos(
		vehicleid,
		vehicle_data[vehicleid][v_pos_x],
		vehicle_data[vehicleid][v_pos_y],
		vehicle_data[vehicleid][v_pos_z]
	);
	
	SetTimerEx("OnVehicleSpawnAngleSet", 1000, false, "d", vehicleid);
	
	LinkVehicleToInterior(vehicleid, vehicle_data[vehicleid][v_int]);
	SetVehicleVirtualWorld(vehicleid, vehicle_data[vehicleid][v_world]);
	SetVehicleHealth(vehicleid, vehicle_data[vehicleid][v_health]);
	ChangeVehicleColor(vehicleid, vehicle_data[vehicleid][v_color][0], vehicle_data[vehicleid][v_color][1]);
	
	ResetVehicleParams(vehicleid);
	return 1;
}

function OnVehicleSpawnAngleSet(vehicleid)
{
	SetVehicleZAngle(vehicleid, vehicle_data[vehicleid][v_pos_angle]);
	return 1;
}

Vehicle_OnPlayerKeyStateChange(playerid, newkeys, oldkeys) 
{
	new player_state = GetPlayerState(playerid);
	
	if (player_state == PLAYER_STATE_ONFOOT || player_state == PLAYER_STATE_DRIVER)
	{
		if (PRESSED(KEY_NO))
		{
			new vehicleid = GetVehicleAroundOfPlayer(playerid);
			
			if (vehicleid == 0)
			{
				return 1;
			}
			
			SetPVarInt(playerid, "Vehicle:Select", vehicleid);
			ShowVehicleMenu(playerid, vehicleid);
			return 0;
		}
		
		if (player_state == PLAYER_STATE_DRIVER)
		{
			new vehicleid = GetPlayerVehicleID(playerid);
			
			if (IsBikeVehicle(vehicleid))
			{
				return 1;
			}
			
			if (PRESSED(KEY_SUBMISSION)) 
			{
				CheckVehicleEngine(playerid, vehicleid);
			}
			
			if (PRESSED(KEY_ACTION)) 
			{
				CheckVehicleLight(playerid, vehicleid);
			}
		}
	}

	return 1;
}

Vehicle_OnPlayerClickTextDraw(playerid, Text: clickedid) 
{
	if (clickedid == INVALID_TEXT_DRAW)
	{
		DisableVehicleKeyAlarm(playerid);
	}
	
	return 1;
}

Vehicle_OnPlayerClickPTD(playerid, PlayerText: playertextid)
{
	new vehicleid = GetPVarInt(playerid, "KeyAlarm:VehicleId");
	
	if (vehicleid != 0)
	{
		for (new PlayerText: i = PTD_KA_START; i < PTD_KA_END; i++)
		{
			if (playertextid == ptd_key_alarm[playerid][i])
			{
				ActionVehicleKeyAlarm(playerid, vehicleid, _: i);
				return 1;
			}
		}
	}
	
	return 1;
}

Vehicle_OnVehicleMod(playerid, vehicleid, componentid)
{
	Kick(playerid);
	
	RemoveVehicleComponent(vehicleid, componentid);
	return 1;
}

function Vehicle_OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	Kick(playerid);
	
	ChangeVehiclePaintjob(vehicleid, 3);
	return 1;
}

Vehicle_OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	#pragma unused color1
	#pragma unused color2
	
	Kick(playerid);
	
	ChangeVehicleColor(vehicleid, vehicle_data[vehicleid][v_color][0], vehicle_data[vehicleid][v_color][1]);
	return 1;
}

Destroy:vehicle_data(playerid, vehicleid, time = 60000 * 3, type = INVALID_PARAM)
{
	if (vehicle_data[vehicleid][v_del_timer] != INVALID_PARAM)
	{
		return;
	}
	
	if (time != INVALID_PARAM)
	{
		vehicle_data[vehicleid][v_del_type] = type;
		vehicle_data[vehicleid][v_del_timer] = SetTimerEx(
			"OnVehicleDestroy", 
			time, 
			false, 
			"ii",
			playerid,
			vehicleid 
		);
	}
	else 
	{
		OnVehicleDestroy(playerid, vehicleid);
	}
}

function OnVehicleDestroy(playerid, vehicleid)
{
	if (playerid != INVALID_PLAYER_ID)
	{
		RemoveVehicleOwner(playerid, vehicleid);
	}
	
	DestroyVehicle(vehicleid, false);
	
	if (playerid != INVALID_PLAYER_ID 
	&& GetCharacterId(playerid) == vehicle_data[vehicleid][v_owner_id])
	{
		pformat:("" #SUCCESS " Транспорт " #cPROJECT "%s" #cWHITE " был убран.",
			GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name)
		);
		
		psend:(playerid, C_WHITE);
	}
	
	vehicle_data[vehicleid][v_spawned] = false;
	Update:vehicle_data(vehicleid);
	Clear:vehicle_data(vehicleid);
	return 1;
}

/*function Float: GetVehicleDebtInPercent(vehicleid)
{
	return Float: (
		vehicle_data[vehicleid][v_debt] * 100)
		/ GetVehicleInfo(vehicle_data[vehicleid][v_model], v_cost); // процент задолжности от общей суммы
}*/

function Float: GetVehicleFuelRate(modelid)
{	
	return Float: (45000.0 *(GetVehicleInfo(modelid, v_fuel_rate) 
	* (GetVehicleInfo(modelid, v_max_fuel) * 0.025)));
}

GetPlayerVehiclesCount(playerid)
{
	new vehicles_count;
		
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		if (player_vehicle[playerid][pv_id][i] == 0)
		{
			continue;
		}
		
		vehicles_count++;
	}
	
	return vehicles_count;
}

GetPlayerMaxVehicles(playerid)
{
	switch (user_data[playerid][u_vip])
	{
		case VIP_DEFAULT, VIP_ADVANCED:
		{
			return MAX_PLAYER_VEHICLES - 1;
		}
		
		case VIP_PRO:
		{
			return MAX_PLAYER_VEHICLES;
		}
	}
	
	return MAX_PLAYER_VEHICLES - 2;
}

GetPlayerAvaibleVehicle(playerid)
{
	return (GetPlayerMaxVehicles(playerid) - GetPlayerVehiclesCount(playerid)) <= 0 ? false : true;
}

SetVehicleOwner(playerid, id, model, vehicleid = 0)
{
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		if (player_vehicle[playerid][pv_id][i] != 0)
		{
			continue;
		}

		player_vehicle[playerid][pv_id][i] = id;
		player_vehicle[playerid][pv_model][i] = model;
		player_vehicle[playerid][pv_server_id][i] = vehicleid;
		break;
	}
	
	if (vehicleid == 0)
	{
		return;
	}
	
	vehicle_data[vehicleid][v_owner_id] = GetCharacterId(playerid);
}

GiveVehicleOwner(playerid, id, vehicleid)
{
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		if (player_vehicle[playerid][pv_id][i] != id)
		{
			continue;
		}
		
		player_vehicle[playerid][pv_server_id][i] = vehicleid;
		break;
	}
}

RemoveVehicleOwner(playerid, vehicleid, bool: fully = false)
{
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		if (player_vehicle[playerid][pv_server_id][i] == vehicleid)
		{	
			player_vehicle[playerid][pv_server_id][i] = 0;
			player_vehicle[playerid][pv_delete][i] = false;
			
			if (fully)
			{
				player_vehicle[playerid][pv_id][i] = 
				player_vehicle[playerid][pv_model][i] = 0;
			}
			
			break;
		}
	}
}

IsOwnerVehicle(playerid, vehicleid)
{
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		if (player_vehicle[playerid][pv_server_id][i] == vehicleid)
		{
			return 1;
		}
	}
	
	return 0;
}

IsVehicleAccess(playerid, vehicleid)
{
	new access;
	
	if (vehicle_data[vehicleid][v_owner_type] == TYPE_VEH_PLAYER)
	{
		access = IsOwnerVehicle(playerid, vehicleid);
		
		if (!access && GetPVarInt(playerid, "Vehicle:Trust") != 0)
		{
			access = (GetPVarInt(playerid, "Vehicle:Trust") == vehicle_data[vehicleid][v_owner_id]);
		}
	}
	else if (vehicle_data[vehicleid][v_owner_type] == TYPE_VEH_FRACTION && IsFractionMember(playerid))
	{
		access = (vehicle_data[vehicleid][v_owner_id] == GetFractionMemberId(playerid));
	}
	
	return access;
}

GetVehicleAroundOfPlayer(playerid, bool: is_inside = true, Float: distance = 2.0)
{
	new Float: x,
		Float: y,
		Float: z,
		vehicleid = is_inside && GetPlayerState(playerid) == PLAYER_STATE_DRIVER ? GetPlayerVehicleID(playerid) : 0;
	
	if (vehicleid == 0)
	{
		for (new i = 1, j = GetVehiclePoolSize(); i <= j; i++)
		{
			GetVehicleComponentPos(i, false, x, y, z);
			if (GetPlayerDistanceFromPoint(playerid, x, y, z) <= 0.8)
			{
				return i;
			}
			
			GetVehicleComponentPos(i, true, x, y, z);
			if (GetPlayerDistanceFromPoint(playerid, x, y, z) <= 0.8)
			{
				return i;
			}
			
			GetVehiclePos(i, x, y, z);
			if (GetPlayerDistanceFromPoint(playerid, x, y, z) <= distance)
			{
				return i;
			}
		}
	}
	
	return vehicleid;
}

stock IsPlayerAroundVehicle(playerid, vehicleid, Float: distance = 2.0)
{
	new Float: x,
		Float: y,
		Float: z;
		
	GetVehiclePos(vehicleid, x, y, z);

	if (GetPlayerDistanceFromPoint(playerid, x, y, z) > distance)
	{
		return 0;
	}
	
	return 1;
}

GetCountSpawnedVehicle(playerid)
{
	new count;
	
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		if (player_vehicle[playerid][pv_server_id][i] == 0)
		{
			continue;
		}
		
		count++;
	}
	
	return count;
}

stock GetPlayerVehicle(playerid)
{
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		if (player_vehicle[playerid][pv_server_id][i] == INVALID_PARAM)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

GetPlayerVehicleIndexByServerId(playerid, vehicleid)
{
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		if (player_vehicle[playerid][pv_server_id][i] != vehicleid)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

SetVehiclePark(vehicleid, playerid)
{
	GetVehiclePos(vehicleid, 
		vehicle_data[vehicleid][v_pos_x], 
		vehicle_data[vehicleid][v_pos_y], 
		vehicle_data[vehicleid][v_pos_z] 
	);
	
	GetVehicleZAngle(vehicleid, vehicle_data[vehicleid][v_pos_angle]);
	
	vehicle_data[vehicleid][v_int] = GetVehicleInterior(vehicleid);
	vehicle_data[vehicleid][v_world] = GetVehicleVirtualWorld(vehicleid);
	
	Update:vehicle_data(vehicleid, playerid);
}

VehicleLock(playerid)
{	
	new vehicleid = GetVehicleAroundOfPlayer(playerid);
		
	if (!vehicleid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_AROUND_CAR);
		return 0;
	}
	
	if (!IsVehicleAccess(playerid, vehicleid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_THIS_CAR);
		return 0;
	}
	
	CheckVehicleLock(playerid, vehicleid);
	Update:vehicle_data(vehicleid, playerid);
	
	return 1;
}

VehicleFill(vehicleid, Float: fuel, bool: is_full = false)
{
	if (is_full)
	{
		vehicle_data[vehicleid][v_fuel] = GetVehicleInfo(vehicle_data[vehicleid][v_model], v_max_fuel);
	}
	else 
	{
		if ((GetVehicleFuel(vehicleid) + fuel) >= GetVehicleInfo(vehicle_data[vehicleid][v_model], v_max_fuel))
		{
			return 0;
		}
		
		vehicle_data[vehicleid][v_fuel] += fuel;
	}
	
	if (GetVehicleId(vehicleid) != 0)
	{
		Update:vehicle_data(vehicleid);
	}
	
	return 1;
}

Move:vehicle(vehicleid, Float: x, Float: y, Float: z, worldid = 0, int = 0, use_angle = false, Float: angle = 0.0)
{		
	SetVehicleVirtualWorld(vehicleid, worldid);
	LinkVehicleToInterior(vehicleid, int);
	SetVehiclePos(vehicleid, 
		x, y, z
	);
				
	if (use_angle)
	{
		SetVehicleZAngle(vehicleid, angle);
	}
	
	foreach (new playerid : Player)
	{
		if (vehicleid != 0 && GetPlayerVehicleID(playerid) == vehicleid)
		{
			Move:player(playerid, 0.0, 0.0, 0.0, worldid, int, _, _, false);
		}
	}
	
	return 1;
}

GetMinSaleVehiclePrice(vehicleid)
{
	return floatround(0.1 * GetVehicleInfo(vehicle_data[vehicleid][v_model], v_cost));
}

GetMaxSaleVehiclePrice(vehicleid)
{		
	return GetVehicleInfo(vehicle_data[vehicleid][v_model], v_cost) * 2;
}

GivePlayerVehicle(playerid, buy_type, modelid, _: color[2], Float: pos[4], bool: is_credit = false, days = 7)
{
	Create:vehicle_data(
		buy_type, 
		TYPE_VEH_PLAYER, 
		GetCharacterId(playerid), 
		modelid, 
		color, 
		pos,
		playerid,
		is_credit,
		days
	);
}

IsVehicleOpenWindows(vehicleid)
{	
	for (new i; i < MAX_VEHICLE_WINDOWS; i++)
	{
		if (vehicle_data[vehicleid][v_window][i] == 0)
		{
			return 0;
		}
	}
	
	return 1;
}

IsVehicleOccupied(vehicleid)
{
	foreach (new playerid : Player)
	{
		if (IsPlayerInVehicle(playerid, vehicleid))
		{
			return 1;
		}
	}
	
	return 0;
}

SendVehicleMessage(vehicleid, text[])
{
	foreach (new playerid : Player)
	{
		if (!IsPlayerLogged(playerid))
		{
			continue;
		}
			
		if (IsPlayerInVehicle(playerid, vehicleid) || GetPVarInt(playerid, "Admin:ShowVehicleMessage" ) == vehicleid)
		{
			SendSplitMessage(playerid, COLOR_FADE1, text);
		}
	}
}