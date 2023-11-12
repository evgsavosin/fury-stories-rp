/*!
	@brief Raknet - Incoming RPC (Client)
	@author Found (evg.savosin)
	@date 12.05.2019
*/

IRPC:RPC_Spawn(playerid, BitStream: bs)
{
	ac_player_data[playerid][ac_is_death] = false;
	
	AntiCheatDumpPlayerPos(playerid, 
		ac_player_data[playerid][spawn_pos_x], 
		ac_player_data[playerid][spawn_pos_y],
		ac_player_data[playerid][spawn_pos_z]
	);
	
	AntiCheatTimeout(playerid, AC_ONFOOT_FLYHACK);
	AntiCheatTimeout(playerid, AC_ONFOOT_AIRBREAK);
	AntiCheatTimeout(playerid, AC_DRIVER_AIRBREAK);
    return 1;
}

IRPC:RPC_Death(playerid, BitStream: bs)
{	
	if (ac_player_data[playerid][ac_is_death])
	{
		AntiCheatDetect(playerid, AC_FAKE_DEATH);
		return 1;
	}

	ac_player_data[playerid][ac_is_moved] =
	ac_player_data[playerid][ac_is_set_pos] = false;
	
	ac_player_data[playerid][ac_is_death] = true;
	
	AntiCheatTimeout(playerid, AC_ONFOOT_AIRBREAK);
	AntiCheatTimeout(playerid, AC_DRIVER_AIRBREAK);
	return 1;
}

IRPC:RPC_EnterVehicle(playerid, BitStream: bs)
{
	new vehicleid,
		ispassenger,
		Float: distance,
		Float: enter_distance,
		tmp,
		doors;
	
	BS_ReadInt16(bs, vehicleid);
	BS_ReadInt8(bs, ispassenger);
    
	if (!(0 < vehicleid < MAX_VEHICLES))
	{
		AntiCheatDetect(playerid, AC_RAKNET_HACK);
		return 1;
	}
	
    GetVehicleParamsEx(
		vehicleid, 
		tmp, 
		tmp, 
		tmp,
		doors,
		tmp, 
		tmp, 
		tmp
	);
	
	distance = GetVehicleDistanceFromPoint(
		vehicleid, 
		ac_player_data[playerid][ac_pos_x],
		ac_player_data[playerid][ac_pos_y],
		ac_player_data[playerid][ac_pos_z]
	);
	
	enter_distance = GetVehicleEnterDistance(vehicleid);
	
	if (floatcmp(distance, enter_distance) == 1
	|| (doors == VEHICLE_PARAMS_ON && !ispassenger))
	{	
		if (doors == VEHICLE_PARAMS_ON)
		{
			ClearAnimations(playerid);
		}
		
		return 0;
	}
	
	ac_player_data[playerid][ac_enter_vehicle_id] = vehicleid;
	ac_player_data[playerid][ac_enter_tick] = ac_player_data[playerid][ac_tick];

	AntiCheatDumpPlayerVehicleData(playerid, INVALID_VEHICLE_ID, INVALID_PARAM);
	return 1;
}

IRPC:RPC_ExitVehicle(playerid, BitStream: bs)
{	
	new vehicleid;
	
	BS_ReadInt16(bs, vehicleid);
    
	if (!(0 < vehicleid < MAX_VEHICLES))
	{
		AntiCheatDetect(playerid, AC_RAKNET_HACK);
		return 1;
	}
	
	AntiCheatTimeout(playerid, AC_ONFOOT_AIRBREAK);
	return 1;
}

IRPC:RPC_EditAttachedObject(playerid, BitStream: bs)
{
	new response,
		index,
		model;
		
	BS_ReadInt32(bs, response);
	BS_ReadInt32(bs, index);
	BS_ReadInt32(bs, model);
	
	if (!(0 <= index < MAX_ATTACH_SLOTS))
	{
		AntiCheatDetect(playerid, AC_RAKNET_HACK);
		return 1;
	}
	
	if (ac_player_data[playerid][ac_attach_id][index] == INVALID_OBJECT_ID 
	|| ac_player_data[playerid][ac_attach_id][index] != model)
	{
		AntiCheatDetect(playerid, AC_ATTACH_CRASHER);
		return 1;
	}
	
	return 1;
}