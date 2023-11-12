/*!
	@brief Функции
	@author Found (evg.savosin)
	@date 12.05.2019
*/

// Public functions
public OnGameModeInit()
{
	print("[AC_OnGameModeInit]: " #__AC_VERSION " initialized...");
	
	#if defined AC_OnGameModeInit
		return AC_OnGameModeInit();
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif

#define	OnGameModeInit	AC_OnGameModeInit
#if defined AC_OnGameModeInit
	forward AC_OnGameModeInit();
#endif


public OnPlayerConnect(playerid)
{
	Clear:anticheat(playerid);
	
	#if defined AC_OnPlayerConnect
		return AC_OnPlayerConnect(playerid);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define	OnPlayerConnect	AC_OnPlayerConnect
#if defined AC_OnPlayerConnect
	forward AC_OnPlayerConnect(playerid);
#endif


public OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart)
{
	if (amount < 0.0 || issuerid != INVALID_PLAYER_ID 
	&& !(0 <= issuerid < MAX_PLAYERS) || !(3 <= bodypart <= 9) 
	|| !IsValidDamageReason(weaponid))
	{
		AntiCheatDetect(playerid, AC_WEAPON_CRASHER);
		AntiCheatDebug(
			playerid, 
			AC_WEAPON_CRASHER, 
			"[TakeDamage] PLAYERID", 
			float(playerid)
		);
	}

	#if defined AC_OnPlayerTakeDamage
		return AC_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerTakeDamage
    #undef OnPlayerTakeDamage
#else
    #define _ALS_OnPlayerTakeDamage
#endif

#define	OnPlayerTakeDamage	AC_OnPlayerTakeDamage
#if defined AC_OnPlayerTakeDamage
	forward AC_OnPlayerTakeDamage(playerid, issuerid, Float:amount, weaponid, bodypart);
#endif


public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
	if (amount < 0.0 || !(0 <= damagedid < MAX_PLAYERS) 
	|| !(3 <= bodypart <= 9) || !IsValidWeapon(weaponid))
	{
		AntiCheatDetect(playerid, AC_WEAPON_CRASHER);
		AntiCheatDebug(
			playerid, 
			AC_WEAPON_CRASHER, 
			"[GiveDamage] PLAYERID", 
			float(playerid)
		);
	}
			
	#if defined AC_OnPlayerGiveDamage
		return AC_OnPlayerGiveDamage(playerid, issuerid, Float:amount, weaponid, bodypart);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerGiveDamage
    #undef OnPlayerGiveDamage
#else
    #define _ALS_OnPlayerTakeDamage
#endif

#define	OnPlayerGiveDamage	AC_OnPlayerGiveDamage
#if defined AC_OnPlayerGiveDamage
	forward AC_OnPlayerGiveDamage(playerid, issuerid, Float:amount, weaponid, bodypart);
#endif


public OnPlayerStateChange(playerid, newstate, oldstate)
{	
	if (!IsPlayerLogged(playerid))
	{
		return 1;
	}
	
	// NOP TogglePlayerSpectating
	if (newstate == PLAYER_STATE_SPECTATING && !IsPlayerSpectated(playerid))
	{
		AntiCheatDetect(playerid, NOP_PLAYER_SPECTATE);
	}
	
	// Restricted use weapon driver
	if (newstate == PLAYER_STATE_DRIVER)
	{
		SetPlayerArmedWeapon(playerid, 0);
	}
	else if ((oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
	&& newstate == PLAYER_STATE_ONFOOT)
	{
		AntiCheatTimeout(playerid, AC_ONFOOT_AIRBREAK);
	}
	
	#if defined AC_OnPlayerStateChange
		return AC_OnPlayerStateChange(playerid, newstate, oldstate);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerStateChange
    #undef OnPlayerStateChange
#else
    #define _ALS_OnPlayerStateChange
#endif

#define	OnPlayerStateChange	AC_OnPlayerStateChange
#if defined AC_OnPlayerStateChange
	forward AC_OnPlayerStateChange(playerid, newstate, oldstate);
#endif

public OnPlayerSpawn(playerid)
{
	if (ac_player_data[playerid][ac_weapon_id][0] == WEAPON_BRASSKNUCKLE)
	{
		AntiCheatTimeout(playerid, AC_WEAPON_HACK);
	}
	
	#if defined AC_OnPlayerSpawn
		return AC_OnPlayerSpawn(playerid);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerSpawn
    #undef OnPlayerSpawn
#else
    #define _ALS_OnPlayerSpawn
#endif

#define	OnPlayerSpawn	AC_OnPlayerSpawn
#if defined AC_OnPlayerSpawn
	forward AC_OnPlayerSpawn(playerid);
#endif


public OnPlayerUpdate(playerid)
{	
	// Ђктуальный тик
	ac_player_data[playerid][ac_tick] = GetTickCount();
	
	// 
	for (new i; i < MAX_ANTICHEAT_LIST; i++)
	{
		if (GetAntiCheatData(i, ac_logic_warning_count) != 0 
		&& ac_player_data[playerid][ac_detect_count][i] > 0
		&& ac_player_data[playerid][ac_detect_tick][i] >= ac_player_data[playerid][ac_tick] + (GetAntiCheatData(i, ac_logic_warning_count) * 500))
		{
			ac_player_data[playerid][ac_detect_count][i] -= 1;
		}
	}
	
	#if defined AC_OnPlayerUpdate
		AC_OnPlayerUpdate(playerid);
	#endif
	
	return 1;
}
#if defined _ALS_OnPlayerUpdate
    #undef OnPlayerUpdate
#else
    #define _ALS_OnPlayerUpdate
#endif

#define	OnPlayerUpdate	AC_OnPlayerUpdate
#if defined AC_OnPlayerUpdate
	forward AC_OnPlayerUpdate(playerid);
#endif

/*
	@brief Timer (1s)
*/

Timer:anticheat(playerid)
{
	ac_player_data[playerid][ac_ping] = GetPlayerPing(playerid);
}

// AntiCheat functions
AntiCheatDetect(playerid, const code) 
{
	if (!IsAntiCheatValidCode(code))
	{
		return 1;
	}
	
	if (IsAntiCheatAdmin(playerid))
	{
		return 1;
	}
	
	new type = GetAntiCheatData(code, ac_type_punish),
		tick = ac_player_data[playerid][ac_tick];
		
	if (type == AC_PUNISH_IGNORE)
	{
		return 1;
	}

	if (ac_player_data[playerid][ac_detect_flood_tick] > tick)
	{
		return 1;
	}

	ac_player_data[playerid][ac_detect_flood_tick] = tick + (1000 * AC_WARNING_TIMEOUT);
	
	ac_player_data[playerid][ac_detect_tick][code] = tick;
	if (++ac_player_data[playerid][ac_detect_count][code] < GetAntiCheatData(code, ac_logic_warning_count))
	{
		return 1;
	}
	
	ac_player_data[playerid][ac_detect_count][code] = 0;
	
	if (type == AC_PUNISH_WARNING)
	{
		format:g_small_string(#AC_MESSAGE " %s[%d] (%s) подозревается в читерстве. (%s | #%d)",
			GetCharacterName(playerid),
			playerid,
			GetUserName(playerid),
			GetAntiCheatData(code, ac_name),
			code
		);

		SendAdminMessage(C_RED, g_small_string);
		return 1;
	}
	else if (type == AC_PUNISH_KICK)
	{
		KickWithDialog(
			playerid, 
			ANTICHEAT_ID, 
			GetAntiCheatData(code, ac_name),
			code
		);
		
		return 0;
	}
	
	return 1;
}

AntiCheatTimeout(playerid, const code, custom_tick = 0)
{
	if (!IsAntiCheatValidCode(code))
	{
		return;
	}
	
	ac_player_data[playerid][ac_timeout_tick][code] = (GetTickCount() + (custom_tick == 0 ? GetAntiCheatData(code, ac_timeout_tick) : custom_tick));
}

// Format: (playerid, code, "Name", value, ..., "Name-n", value-n)
AntiCheatDebug(playerid, const code, {Float, _}: ...)
{
	if (!IsAntiCheatValidCode(code))
	{
		return;
	}
	
	if (IsPlayerKicked(playerid))
	{
		return;
	}
	
	new type = GetAntiCheatData(code, ac_type_punish);
	
	if (type == AC_PUNISH_IGNORE)
	{
		return;
	}
	
	if (ac_player_data[playerid][ac_debug_flood_tick] > ac_player_data[playerid][ac_tick])
	{
		return;
	}

	ac_player_data[playerid][ac_debug_flood_tick] = ac_player_data[playerid][ac_tick] + (1000 * AC_WARNING_TIMEOUT);
	
	const static_args = 2;
	
	new args = numargs(),
		arg,
		str_name	[64],
		string		[128];
	
	format:string(#AC_MESSAGE " 0x%02d: ", code);
	for (new i = static_args; i < args; i++)
	{
		if (((i - static_args) % 2) == 0) // String
		{	
			for (new j = 0;;)
			{	
				if ((arg = getarg(i, j)) == EOS)
				{
					break;
				}
				
				str_name[j++] = arg;
			}
		}
		else // Integer, float
		{
			arg = getarg(i);

			format:string("%s%s[%0.2f] ", 
				string,
				str_name,
				arg
			);
			
			clean:<str_name>;
		}
	}
	
	SendAdminMessage(C_RED, string, false, ADMIN_LEAD);
}

// Other functions
GetAntiCheatSpeed(playerid)
{
	new Float: vel_x,
		Float: vel_y,
		Float: vel_z,
		vehicleid = GetPlayerVehicleID(playerid);

    if(vehicleid > 0)
	{
		GetVehicleVelocity(vehicleid, vel_x, vel_y, vel_z);
	}
	else
	{
		GetPlayerVelocity(playerid, vel_x, vel_y, vel_z);
    }
	
	return floatround(VectorSize(vel_x, vel_y, vel_z) * 100.0);
}

Float: GetVehicleEnterDistance(vehicleid)
{
	new modelid = GetVehicleModel(vehicleid);
	
	switch (modelid)
	{
	    case 592: 
		{
			return 40.0;
		}
		
	    case 553: 
		{
			return 30.0;
		}
		
	    case 570, 537, 538: 
		{
			return 100.0;
		}
	}
	
	return 20.0;
}

IsValidDamageReason(weaponid)
{
	return (0 <= weaponid <= WEAPON_MOLTOV || WEAPON_COLT45 <= weaponid <= WEAPON_PARACHUTE || WEAPON_VEHICLE <= weaponid <= WEAPON_COLLISION);
}

IsValidWeapon(weaponid) 
{
	return (0 <= weaponid <= WEAPON_MOLTOV || WEAPON_COLT45 <= weaponid <= WEAPON_PARACHUTE);
}

IsBulletWeapon(weaponid)
{
	return (weaponid == WEAPON_MINIGUN || WEAPON_COLT45 <= weaponid <= WEAPON_SNIPER);
}

AntiCheatDumpPlayerData(playerid, Float: position[])
{
	// Position
	ac_player_data[playerid][ac_pos_x] = position[0];
	ac_player_data[playerid][ac_pos_y] = position[1];
	ac_player_data[playerid][ac_pos_z] = position[2];
}

AntiCheatDumpPlayerPos(playerid, Float: x, Float: y, Float: z)
{
	new counter = ac_player_data[playerid][ac_dump_pos_count] == INVALID_PARAM ? 0 : ac_player_data[playerid][ac_dump_pos_count];
	
	ac_player_pos[playerid][counter][0] = x;
	ac_player_pos[playerid][counter][1] = y;
	ac_player_pos[playerid][counter][2] = z;
	
	ac_player_data[playerid][ac_dump_pos_count] = (counter >= AC_POSITION_COUNT) ? 0 : ac_player_data[playerid][ac_dump_pos_count]++;
	ac_player_data[playerid][ac_is_set_pos] = true;
}

AntiCheatDumpPlayerVehicleData(playerid, vehicleid, seatid)
{
	ac_player_data[playerid][ac_vehicle_id] = vehicleid;
	ac_player_data[playerid][ac_vehicle_seat_id] = seatid;
}

// Check functions 
CheckAntiCheatVehicleEnter(playerid, vehicleid)
{
	if (!(1 <= vehicleid <= MAX_VEHICLES) 
	|| ac_player_data[playerid][ac_vehicle_id] != INVALID_VEHICLE_ID)
	{
		return 1;
	}
	
	new bool: is_cheat = false;

	#if __AC_DEBUG >= __AC_REPORTING_ALL
		printf("CheckAntiCheatVehicleEnter: [%i %i %i %i]",
			ac_player_data[playerid][ac_enter_vehicle_id],
			vehicleid,
			ac_player_data[playerid][ac_tick],
			ac_player_data[playerid][ac_enter_tick] + 350
		);
	#endif 
	
	if (!ac_player_data[playerid][ac_is_put_in_car] 
	&& !IsBoatVehicle(vehicleid) 
	&& !IsTrainVehicle(vehicleid)
	&& (ac_player_data[playerid][ac_enter_vehicle_id] != vehicleid
	|| ac_player_data[playerid][ac_tick] <= ac_player_data[playerid][ac_enter_tick] + 350))
	{
		AntiCheatDebug(playerid, 
			AC_DRIVER_ENTER, 
			"[01]PLAYERID", 
			float(playerid),
			"VEHICLEID", 
			float(vehicleid),
			"TICK",
			(ac_player_data[playerid][ac_tick] - ac_player_data[playerid][ac_enter_tick])
		);
		
		is_cheat = true;
	}

	ac_player_data[playerid][ac_enter_vehicle_id] = INVALID_VEHICLE_ID;
	ac_player_data[playerid][ac_enter_tick] = 0;
	ac_player_data[playerid][ac_is_put_in_car] = false;
	
	return _: !is_cheat;
}

CheckAntiCheatVehicleFastEnter(playerid, vehicleid, seatid)
{
	new bool: is_cheat = false;
	
	if (ac_player_data[playerid][ac_vehicle_id] != INVALID_VEHICLE_ID
	&& ac_player_data[playerid][ac_vehicle_id] != vehicleid)
	{
		AntiCheatDebug(
			playerid, 
			AC_DRIVER_ENTER, 
			"[01]PLAYERID", 
			float(playerid),
			"OLD_VEHICLEID",
			ac_player_data[playerid][ac_vehicle_id],
			"NEW_VEHICLEID", 
			float(vehicleid)
		);
		
		is_cheat = true;
	}
	else if (ac_player_data[playerid][ac_vehicle_id] == vehicleid
	&& ac_player_data[playerid][ac_vehicle_seat_id] != seatid
	&& seatid != 0x3F)
	{
		AntiCheatDebug(
			playerid, 
			AC_DRIVER_ENTER, 
			"[02]PLAYERID", 
			float(playerid),
			"OLD_SEATID", 
			float(ac_player_data[playerid][ac_vehicle_seat_id]),
			"NEW_SEATID",
			float(seatid)
		);
		
		is_cheat = true;
	}
	
	return _: !is_cheat;
}

CheckRemovePlayerFromVehicle(playerid)
{
	if (CheckAntiCheatTimeout(playerid, NOP_REMOVE_FROM_VEHICLE) 
	&& ac_player_data[playerid][ac_is_remove_from_vehicle])
	{
		AntiCheatDetect(playerid, NOP_REMOVE_FROM_VEHICLE);
	}
}