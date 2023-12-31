/*!
	@brief ������� ��� ������� ������
	@author Found (evg.savosin)
	@date 26.04.2017
*/

// Public function
Death_OnPlayerDisconnect(playerid)
{
	if (!user_login{playerid})
	{
		return 1;
	}
	
	if (IsValidDynamic3DTextLabel(death_data[playerid][d_text]))
	{
		DestroyDynamic3DTextLabel(death_data[playerid][d_text]);
	}
	
	return 1;
}

Death_OnPlayerDeath(playerid, killerid, reason)
{
	new death = GetCharacterDeath(playerid);

	if (death == TYPE_DEATH_NONE)
	{
		SetAdminLogForPlayer(playerid, reason, a_deathlog, killerid);
	}
	
	#pragma unused killerid
	#pragma unused reason
	
	if (!user_login{playerid} || death == TYPE_DEATH_DIED)
	{
		return 1;
	}
	
	GetPlayerPos(
		playerid, 
		character_data[playerid][c_pos][0], 
		character_data[playerid][c_pos][1], 
		character_data[playerid][c_pos][2] 
	);
		
	GetPlayerFacingAngle(playerid, character_data[playerid][c_pos][3]);
	
	character_data[playerid][c_world] = GetPlayerVirtualWorld(playerid);
	
	SetSpawnInfo(
		playerid, 
		264, 
		(character_data[playerid][c_fraction_skin] != 0) ? character_data[playerid][c_fraction_skin] : character_data[playerid][c_skin], 
		character_data[playerid][c_pos][0], 
		character_data[playerid][c_pos][1], 
		character_data[playerid][c_pos][2], 
		character_data[playerid][c_pos][3], 
		0, 
		0, 
		0, 
		0, 
		0, 
		0 
	);
	
	if (death == TYPE_DEATH_NONE)
	{
		HideInventoryWeapons(playerid);
	}
	
	death++;
	SetCharacterDeath(playerid, death);
	Update:character_int(playerid, "c_death", death);
	SetTimerEx("OnPlayerFixDeath", 300, false, "i", playerid); 
	return 1;
}

function OnPlayerFixDeath(playerid)
{
	if (floatcmp(GetCharacterHealth(playerid), 1.0) == -1) 
	{
		SetPlayerHealth(playerid, 1.0);
	}
	
	return 1;
}

Death_OnPlayerSpawn(playerid)
{	
	new death = GetCharacterDeath(playerid),
		count;

	if (death == TYPE_DEATH_NONE)
	{
		return 1;
	}
	
	count = GetPlayerDamageCount(playerid);
	
	SetPlayerVirtualWorld(playerid, character_data[playerid][c_world]);
	SetPlayerInterior(playerid, character_data[playerid][c_int]);
	
	Streamer_UpdateEx(
		playerid, 
		character_data[playerid][c_pos][0], 
		character_data[playerid][c_pos][1], 
		character_data[playerid][c_pos][2],
		character_data[playerid][c_world], 
		character_data[playerid][c_int], 
		STREAMER_TYPE_OBJECT, 
		(5000 + GetPlayerPing(playerid))
	);
	
	SetPlayerHealth(playerid, 100.0);
	Update:death(playerid);
	if (death == TYPE_DEATH_INJURED)
	{
		if (count)
		{
			pformat:("" #DEFAULT " ��� �������� ����� " #cPROJECT "%i ���%s" #cWHITE ". " #cGRAY "(/dm - ��������� �����������)",
				count,
				EndWordDamageCount(count)
			);
		}
		else 
		{
			pformat:("" #DEFAULT " ��� �������� �����.");
		}

	}
	else if (death == TYPE_DEATH_DIED)
	{
		if (count)
		{
			pformat:("" #DEFAULT " ��� �������� ����, ��� ���� ��� ����� " #cPROJECT "%i ���%s" #cWHITE ". " #cGRAY "(/dm - ��������� �����������)",
				count,
				EndWordDamageCount(count)
			);
		}
		else 
		{
			pformat:("" #DEFAULT " ��� �������� ����.");
		}
		
		#if defined __DEBUG == true
			death_data[playerid][d_timer] = 15;
		#else
			death_data[playerid][d_timer] = 60 * 3;
		#endif
	}
	
	psend:(playerid, C_WHITE);
	return 1;
}

Death_OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart) 
{
	#pragma unused bodypart
	#pragma unused amount
	#pragma unused weaponid
	#pragma unused issuerid
	
	if (GetCharacterDeath(playerid) == TYPE_DEATH_DIED)
	{
		SetPlayerHealth(playerid, 100.0);
	}
	
	return 1;
}

Death_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (!GetPVarInt(playerid, "Death:CKTrade"))
	{
		return 1;
	}
	
	new targetid = GetPVarInt(playerid, "Death:CKTargetId");
	
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
		
	if (PRESSED(KEY_YES))
	{
		ShowPlayerDialog(playerid, D_DEATH + 1, DIALOG_STYLE_MSGBOX, " ",
			"" #DEFAULT " ������������� �Character Kill�\n\n\
			��� ������� ������ \"��\" ��� �������� �������� ������ \"����\".\n\
			����������� ���� � �������� ���� ���� �������� �����������.\n\
			�������� ����� ��������� � ������� 15 ���� � ������� ��������� ������� �������.\n\
			� ��� ����� �������� ����������� �������� ���� ��������� �\n\
			���������� ������ � ������� ����������, �� ���, ��������� ����� ����.\n\n\
			�� ������������� ������� ������� " #cPROJECT "�CK�" #cWHITE "?",
			"��", "���"
		);
		
		return 0;
	}
	else if (PRESSED(KEY_NO))
	{
		pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " �������� ���� �����������.",
			GetPlayerCurrentName(playerid)
		);
		
		psend:(targetid, C_WHITE);
		
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " �� ��������� �����������.");
		
		DeletePVar(playerid, "Death:CKTrade");
		DeletePVar(playerid, "Death:CKTargetId");
		return 0;
	}
	
	return 1;
}

Death_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	#pragma unused ispassenger
	#pragma unused vehicleid
	
	new death = GetCharacterDeath(playerid);

	if (death != TYPE_DEATH_NONE)
	{
		FreezePlayer(playerid, 5000);
		SendClientMessage(playerid, C_WHITE, !#ERROR " �� �� ������ ������������ ���������.");
		return 1;
	}
	
	return 1;
}

// Other function
AddDamageForPlayer(playerid, Float: amount, weaponid, bodypart, issuerid)
{
	for (new i; i < MAX_DAMAGES; i++)
	{
		if (damage_data[playerid][i][dm_time] != 0)
		{
			continue;
		}
		
		damage_data[playerid][i][dm_amount] = amount;
		damage_data[playerid][i][dm_time] = gettime();
		damage_data[playerid][i][dm_body_part] = bodypart;
		damage_data[playerid][i][dm_weapon_id] = weaponid;
		
		if (issuerid == INVALID_PLAYER_ID)
		{
			return;
		}
		
		damage_data[playerid][i][dm_name] = GetCharacterName(issuerid);
		damage_data[playerid][i][dm_is_camera] = bool: GetPVarInt(issuerid, "Player:CorpseCamera");
		return;
	}
	
	for (new i; i < MAX_DAMAGES; i++)
	{
		if (i == (MAX_DAMAGES - 1))
		{
			damage_data[playerid][i][dm_amount] = amount;
			damage_data[playerid][i][dm_time] = gettime();
			damage_data[playerid][i][dm_body_part] = bodypart;
			damage_data[playerid][i][dm_weapon_id] = weaponid;
			
			if (issuerid == INVALID_PLAYER_ID)
			{
				continue;
			}
			
			damage_data[playerid][i][dm_name] = GetCharacterName(issuerid);
			damage_data[playerid][i][dm_is_camera] = bool: GetPVarInt(issuerid, "Player:CorpseCamera");
		}
		else 
		{
			damage_data[playerid][i][dm_amount] = damage_data[playerid][i + 1][dm_amount];
			damage_data[playerid][i][dm_time] = damage_data[playerid][i + 1][dm_time];
			damage_data[playerid][i][dm_body_part] = damage_data[playerid][i + 1][dm_body_part];
			damage_data[playerid][i][dm_weapon_id] = damage_data[playerid][i + 1][dm_weapon_id];
			damage_data[playerid][i][dm_is_camera] = damage_data[playerid][i + 1][dm_is_camera];
			damage_data[playerid][i][dm_name] = damage_data[playerid][i + 1][dm_name];
		}
	}
}

GetPlayerDamageCount(playerid)
{
	new count;
	
	for (new i; i < MAX_DAMAGES; i++)
	{
		if (damage_data[playerid][i][dm_time] == 0)
		{
			continue;
		}
		
		count++;
	}
	
	return count;
}

GetDeathStringTime(time, dest[32])
{	
	clean:<dest>;
	time = gettime() - time;
	if (time < 0 || time == gettime() || time > 2592000) 
	{
	    strcat(dest, "����������");
	    return 1;
	}
	
	if (time < 60)
	{
		format:dest("%i ���. �����", time);
	}
	else if (time >= 60 && time < 3600)
	{
		format:dest((time >= 120) ? ("%i �����(-�) �����") : ("%i ������ �����"), time / 60);
	}
	else if (time >= 3600)
	{
		format:dest((time >= 7200) ? ("%i ����(-��) �����") : ("%i ��� �����"), time / 3600);
	}

	return 1;
}

GetDeathBodyPart(part, dest[32])
{
	dest[0] = EOS;
	
	switch(part)
	{
		case 3 : 
		{
			strcat(dest, "����");
		}
		
		case 4 : 
		{
			strcat(dest, "���");
		}
		
		case 5 : 
		{
			strcat(dest, "����� ����");
		}
		
		case 6 : 
		{
			strcat(dest, "������ ����");
		}
		
		case 7 : 
		{
			strcat(dest, "����� ����");
		}
		
		case 8 : 
		{
			strcat(dest, "������ ����");
		}
		
		case 9 : 
		{
			strcat(dest, "������");
		}
		
		default : 
		{
			strcat(dest, "����������");
		}
	}
}

ApplyDeathAnimation(playerid, death)
{
	if (death == TYPE_DEATH_NONE)
	{
		ClearAnimations(playerid);
	}
	else if (death == TYPE_DEATH_INJURED)
	{
		ApplyAnimation(playerid, "SWEET", "null", 4.0, 0, 0, 0, 1, 0, 1);
		ApplyAnimation(playerid, "WUZI", "CS_Dead_Guy", 4.1, 0, 1, 1, 1, 0);
	}
	else if (death == TYPE_DEATH_DIED)	
	{
		ApplyAnimation(playerid, "SWEET", "null", 4.0, 0, 0, 0, 1, 0, 1);
		ApplyAnimation(playerid, "PED", "FLOOR_hit_f", 4.1, 0, 1, 1, 1, 0);
	}
}

Update:death(playerid, bool: is_help = false)
{
	new death = GetCharacterDeath(playerid);
	
	ApplyDeathAnimation(playerid, death);
	
	if (death == TYPE_DEATH_INJURED)
	{
		format:g_small_string("�������� ����� - " #cPROJECT "/dm %i",
			playerid
		);
	}
	else if (death == TYPE_DEATH_DIED)
	{
		format:g_small_string("�������� ����� - " #cPROJECT "/dm %i",
			playerid
		);
	}
	
	if (death != TYPE_DEATH_NONE)
	{
		if (IsValidDynamic3DTextLabel(death_data[playerid][d_text]))
		{
			UpdateDynamic3DTextLabelText(
				death_data[playerid][d_text], 
				C_WHITE, 
				g_small_string 
			);
		}
		else 
		{
			death_data[playerid][d_text] = CreateDynamic3DTextLabel(
				g_small_string, 
				C_WHITE, 
				0.0, 
				0.0, 
				0.0, 
				10.0, 
				playerid, 
				_ 
			);
		}
	}
	else 
	{
		if (IsValidDynamic3DTextLabel(death_data[playerid][d_text]))
		{
			DestroyDynamic3DTextLabel(death_data[playerid][d_text]);
		}
		
		Clear:death_data(playerid, is_help);
	}
	
	return 1;
}