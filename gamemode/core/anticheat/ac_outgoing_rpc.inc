/*!
	@brief Raknet - Outgoing RPC (Server)
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ORPC:RPC_AttachTrailerToVeh(playerid, BitStream: bs)
{
	if (!(0 <= playerid < MAX_PLAYERS))
	{
		return 0;
	}
	
	new vehicleid;
	
	BS_ReadInt16(bs, vehicleid);
	
	ac_veh_data[vehicleid][ac_attach_to_vehicleid] = vehicleid;
	return 1;
}

ORPC:RPC_DetachTrailerFromVeh(playerid, BitStream: bs)
{
	if (!(0 <= playerid < MAX_PLAYERS))
	{
		return 0;
	}
	
	new vehicleid;
	
	BS_ReadInt16(bs, vehicleid);
	
	ac_veh_data[vehicleid][ac_attach_to_vehicleid] = INVALID_VEHICLE_ID;
	return 1;
}

ORPC:RPC_SetPlayerAttachedObj(playerid, BitStream: bs)
{
	if (!(0 <= playerid < MAX_PLAYERS))
	{
		return 0;
	}
	
	new tmp,
		index,
		bool: create,
		model;
	
	BS_ReadInt16(bs, tmp);
	BS_ReadInt32(bs, index);
	BS_ReadBool(bs, create);
	BS_ReadInt32(bs, model);
	
	if (create)
	{
		ac_player_data[playerid][ac_attach_id][index] = model;
	}
	else 
	{
		ac_player_data[playerid][ac_attach_id][index] = INVALID_OBJECT_ID;
	}
	
	return 1;
}

ORPC:RPC_TogglePlayerSpectati(playerid, BitStream: bs)
{
	if (!(0 <= playerid < MAX_PLAYERS))
	{
		return 0;
	}
	
	new toggle;
	
	BS_ReadInt8(bs, toggle);
	
	ac_player_data[playerid][ac_is_spectated] = bool: toggle;
	return 1;
}

ORPC:RPC_SetPlayerPos(playerid, BitStream: bs)
{
	if (!(0 <= playerid < MAX_PLAYERS))
	{
		return 0;
	}
	
	BS_ReadFloat(bs, ac_player_data[playerid][ac_pos_x]);
	BS_ReadFloat(bs, ac_player_data[playerid][ac_pos_y]);
	BS_ReadFloat(bs, ac_player_data[playerid][ac_pos_z]);
	
	AntiCheatDumpPlayerPos(
		playerid, 
		ac_player_data[playerid][ac_pos_x], 
		ac_player_data[playerid][ac_pos_y], 
		ac_player_data[playerid][ac_pos_z]
	);
	
	AntiCheatTimeout(playerid, AC_ONFOOT_TELEPORT);
	
	return 1;
}	

ORPC:RPC_SetPlayerPosFindZ(playerid, BitStream: bs)
{
	if (!(0 <= playerid < MAX_PLAYERS))
	{
		return 0;
	}
	
	BS_ReadFloat(bs, ac_player_data[playerid][ac_pos_x]);
	BS_ReadFloat(bs, ac_player_data[playerid][ac_pos_y]);
	BS_ReadFloat(bs, ac_player_data[playerid][ac_pos_z]);
	
	AntiCheatDumpPlayerPos(
		playerid, 
		ac_player_data[playerid][ac_pos_x], 
		ac_player_data[playerid][ac_pos_y], 
		ac_player_data[playerid][ac_pos_z]
	);
	
	return 1;
}

ORPC:RPC_SetSpawnInfo(playerid, BitStream: bs)
{
	if (!(0 <= playerid < MAX_PLAYERS))
	{
		return 0;
	}
	
	new tmp,
		Float: x,
		Float: y,
		Float: z;
		
	BS_ReadValue(
		bs, 
		PR_INT8, tmp, 
		PR_INT32, tmp, 
		PR_INT8, tmp, 
		PR_FLOAT, x, 
		PR_FLOAT, y, 
		PR_FLOAT, z
	);
	
	ac_player_data[playerid][spawn_pos_x] = x;
	ac_player_data[playerid][spawn_pos_y] = y;
	ac_player_data[playerid][spawn_pos_z] = z;
	return 1;
}

ORPC:RPC_RemoveFromVehicle(playerid, BitStream: bs)
{
	if (!(0 <= playerid < MAX_PLAYERS))
	{
		return 0;
	}
	
	ac_player_data[playerid][ac_is_remove_from_vehicle] = true;
	
	AntiCheatTimeout(playerid, NOP_REMOVE_FROM_VEHICLE);
	AntiCheatTimeout(playerid, AC_ONFOOT_AIRBREAK);
	AntiCheatTimeout(playerid, AC_DRIVER_AIRBREAK);
	return 1;
}

ORPC:RPC_PutPlayerInVehicle(playerid, BitStream: bs)
{
	if (!(0 <= playerid < MAX_PLAYERS))
	{
		return 0;
	}
	
	new vehicleid,
		seatid;
	
	BS_ReadInt16(bs, vehicleid);
	BS_ReadInt8(bs, seatid);
	
	ac_player_data[playerid][ac_enter_vehicle_id] = INVALID_VEHICLE_ID;
	ac_player_data[playerid][ac_enter_tick] = 0;
	ac_player_data[playerid][ac_is_put_in_car] = true;
	
	AntiCheatDumpPlayerVehicleData(playerid, vehicleid, INVALID_PARAM);
	
	AntiCheatTimeout(playerid, (seatid == 0 ? AC_DRIVER_FAST_ENTER : AC_PASSENGER_FAST_ENTER));
	AntiCheatTimeout(playerid, AC_ONFOOT_AIRBREAK);
	AntiCheatTimeout(playerid, AC_DRIVER_AIRBREAK);
	return 1;
}

ORPC:RPC_SetVehiclePos(playerid, BitStream: bs)
{
	if (!(0 <= playerid < MAX_PLAYERS))
	{
		return 0;
	}
	
	AntiCheatTimeout(playerid, AC_ONFOOT_AIRBREAK);
	AntiCheatTimeout(playerid, AC_DRIVER_AIRBREAK);
	return 1;
}

ORPC:RPC_GivePlayerWeapon(playerid, BitStream: bs)
{
	if (!(0 <= playerid < MAX_PLAYERS))
	{
		return 0;
	}
	
	new weaponid,
		ammo,
		slot;
		
	BS_ReadUint16(bs, weaponid);
	BS_ReadUint32(bs, ammo);
	
	slot = GetWeaponSlot(weaponid);
	printf("PRE RPC_GivePlayerWeapon [%i %i %i %i]", playerid, weaponid, ammo, ammo / 65536);
	ammo = ammo / 65536;
	
	if(ammo < -32768) 
	{
		ammo = -32768;
	}
	else if(ammo > 32767) 
	{
		ammo = 32767;
	}

	printf("PAST RPC_GivePlayerWeapon [%i %i %i]", playerid, weaponid, ammo);
	if ((0 <= weaponid <= 15) || (44 <= weaponid <= 46) || weaponid == 40)
	{
		ac_player_data[playerid][ac_ammo][slot] = 1;
	}
	else 
	{
		ac_player_data[playerid][ac_ammo][slot] += ammo;
	}
	
	ac_player_data[playerid][ac_weapon_id][slot] = weaponid;
	AntiCheatTimeout(playerid, AC_WEAPON_HACK);
	return 1;
}

ORPC:RPC_SetWeaponAmmo(playerid, BitStream: bs)
{
	if (!(0 <= playerid < MAX_PLAYERS))
	{
		return 0;
	}
	
	new weaponid,
		ammo,
		slot;
		
	BS_ReadUint8(bs, weaponid);
	BS_ReadUint16(bs, ammo);
	
	slot = GetWeaponSlot(weaponid);

	if ((0 <= weaponid <= 15) || (44 <= weaponid <= 46) || weaponid == 40)
	{
		ac_player_data[playerid][ac_ammo][slot] = 1;
	}
	else 
	{
		ac_player_data[playerid][ac_ammo][slot] = ammo;
	}
	
	ac_player_data[playerid][ac_weapon_id][slot] = weaponid;
	
	AntiCheatTimeout(playerid, AC_WEAPON_HACK);
	return 1;
}

ORPC:RPC_ResetPlayerWeapons(playerid, BitStream: bs)
{
	if (!(0 <= playerid < MAX_PLAYERS))
	{
		return 0;
	}
	
	for (new i = MAX_WEAPON_SLOTS - 1; i >= 0; i--)
	{
		ac_player_data[playerid][ac_weapon_id][i] = 
		ac_player_data[playerid][ac_ammo][i] = 0;
	}
	
	AntiCheatTimeout(playerid, AC_WEAPON_HACK);
	return 1;
}

ORPC:RPC_SetPlayerArmedWeapon(playerid, BitStream: bs)
{
	if (!(0 <= playerid < MAX_PLAYERS))
	{
		return 0;
	}
	
	AntiCheatTimeout(playerid, AC_WEAPON_HACK);
	return 1;
}