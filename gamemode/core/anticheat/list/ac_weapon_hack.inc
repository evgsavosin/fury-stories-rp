/*!
	@brief Античит: Weapon Hack
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ID_PLAYER_SYNC:AC_WEAPON_HACK(playerid, data[PR_OnFootSync])
{
	if (!CheckAntiCheatTimeout(playerid, AC_WEAPON_HACK))
	{
		return 1;
	}
	
	new bool: is_cheat = false,
		weaponid = data[PR_weaponId],
		ammo,
		slot = GetWeaponSlot(weaponid);
	
	if (slot == INVALID_PARAM)
	{
		return 1;
	}
	
	ammo = GetPlayerAmmo(playerid);
	
	if (weaponid != ac_player_data[playerid][ac_weapon_id][slot])
	{
		AntiCheatDebug(playerid, 
			AC_WEAPON_HACK, 
			"[03]PLAYERID", 
			float(playerid),
			"PLAYER_WEAPON",
			float(weaponid),
			"SERVER_WEAPON",
			float(ac_player_data[playerid][ac_weapon_id][slot]),
			"SLOT",
			float(slot)
		);
		
		is_cheat = true;
	}
	
	if (!is_cheat 
	&& !(0 <= weaponid <= WEAPON_CANE) 
	&& !(44 <= weaponid <= WEAPON_PARACHUTE) 
	&& weaponid != WEAPON_BOMB)
	{	
		if (ac_player_data[playerid][ac_ammo][slot] < ammo)
		{
			if (++ac_player_data[playerid][ac_weapon_warning][slot] > AC_WARNING_WEAPON_HACK)
			{
				AntiCheatDebug(playerid, 
					AC_WEAPON_HACK, 
					"[04]PLAYERID", 
					float(playerid),
					"PLAYER_AMMO",
					float(ammo),
					"SERVER_AMMO",
					float(ac_player_data[playerid][ac_ammo][slot]),
					"SLOT",
					float(slot)
				);
				
				is_cheat = true;
			}
		}
		else 
		{
			ac_player_data[playerid][ac_weapon_warning][slot] = 0;
		}
	}
	
	if (is_cheat)
	{
		AntiCheatDetect(playerid, AC_WEAPON_HACK);
		return 0;
	}
	
	return 1;
}

ID_VEHICLE_SYNC:AC_WEAPON_HACK(playerid, data[PR_InCarSync])
{
	if (!CheckAntiCheatTimeout(playerid, AC_WEAPON_HACK))
	{
		return 1;
	}
	
	if (!ac_player_data[playerid][ac_is_in_car])
	{
		AntiCheatTimeout(playerid, AC_WEAPON_HACK);
		return 1;
	}
	
	return (data[PR_weaponId] != 0 && data[PR_weaponId] != WEAPON_BRASSKNUCKLE) ? AntiCheatDetect(playerid, AC_WEAPON_HACK) : 1;
}

ID_PASSENGER_SYNC:AC_WEAPON_HACK(playerid, data[PR_PassengerSync])
{
	if (!CheckAntiCheatTimeout(playerid, AC_WEAPON_HACK))
	{
		return 1;
	}
	
	new bool: is_cheat = false,
		weaponid = data[PR_weaponId],
		slot = GetWeaponSlot(weaponid);
	
	if (slot == INVALID_PARAM)
	{
		return 1;
	}
	
	if (weaponid != ac_player_data[playerid][ac_weapon_id][slot])
	{
		AntiCheatDebug(playerid, 
			AC_WEAPON_HACK, 
			"[07]PLAYERID", 
			float(playerid),
			"PLAYER_WEAPON",
			float(weaponid),
			"SERVER_WEAPON",
			float(ac_player_data[playerid][ac_weapon_id][slot]),
			"SLOT",
			float(slot)
		);
		
		is_cheat = true;
	}

	if (is_cheat)
	{
		AntiCheatDetect(playerid, AC_WEAPON_HACK);
		return 0;
	}
	
	return 1;
}

ID_BULLET_SYNC:AC_WEAPON_HACK(playerid, data[PR_BulletSync])
{
	new bool: is_cheat = false,
		weaponid = data[PR_weaponId],
		ammo,
		slot = GetWeaponSlot(weaponid);

	if (weaponid != ac_player_data[playerid][ac_weapon_id][slot])
	{
		AntiCheatDebug(playerid, 
			AC_WEAPON_HACK, 
			"[05]PLAYERID", 
			float(playerid),
			"PLAYER_WEAPON",
			float(weaponid),
			"SERVER_WEAPON",
			float(ac_player_data[playerid][ac_weapon_id][slot]),
			"SLOT",
			float(slot)
		);
		
		is_cheat = true;
	}
	
	if (!is_cheat)
	{
		ammo = ac_player_data[playerid][ac_ammo][slot] - 1;
		
		if (ammo <= INVALID_PARAM)
		{
			AntiCheatDebug(playerid, 
				AC_WEAPON_HACK, 
				"[06]PLAYERID", 
				float(playerid),
				"PLAYER_AMMO",
				float(ammo),
				"SERVER_AMMO",
				float(ac_player_data[playerid][ac_ammo][slot]),
				"SLOT",
				float(slot)
			);
			
			is_cheat = true;
		}
		else
		{
			ac_player_data[playerid][ac_ammo][slot] = ammo;
			is_cheat = !OnInventoryUpdateWeaponData(playerid, weaponid, ammo);
			AntiCheatTimeout(playerid, AC_WEAPON_HACK, 500);
		}
	}
	
	if (is_cheat)
	{
		AntiCheatDetect(playerid, AC_WEAPON_HACK);
		return 0;
	}
	
	return 1;
}