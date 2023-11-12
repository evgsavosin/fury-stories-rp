/*!
	@brief Файл с функциями криминальных систем
	@author Flavo
	@date 03.11.2019
*/

Crime_OnGameModeInit()
{
	Update:crime_counter();
	Load:crime_data();
	Load:crtype_data();
	
	for (new i; i < MAX_CRIMES; i++)
	{
		Clear:crbuy_storage(i);
	}
}

Crime_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_NO))
	{
		if (!CheckCrimeAccess(playerid))
		{
			return 1;
		}

		new crime_index = GetCrimeMember(playerid),
			storage_id_exist;
			
		for (new i; i < MAX_CRIME_CUSTOMER; i++)
		{
			if (crbuy_storage[crime_index][i][cr_buy_customer_id] != character_data[playerid][c_id])
			{
				continue;
			}
			
			storage_id_exist = i;
			break;
		}
			
		new	storage_location_exist = crbuy_storage[crime_index][storage_id_exist][cr_buy_location_index];

		if (crbuy_storage[crime_index][storage_id_exist][cr_buy_customer_id] != character_data[playerid][c_id] || storage_id_exist == INVALID_PARAM)
		{
			return 1;
		}

		new Float: x = crbuy_location[storage_location_exist][cr_loc_x],
			Float: y = crbuy_location[storage_location_exist][cr_loc_y],
			Float: z = crbuy_location[storage_location_exist][cr_loc_z];
			
		if (!IsPlayerInRangeOfPoint(playerid, 5, x, y, z))
		{
			pformat:("" #ERROR " Вы находитесь слишком далеко от точки получения товара.");
			psend:(playerid, C_WHITE);
			
			return 1;
		}
		
		ShowCrimeBuyStorage(playerid, crime_index, storage_id_exist);
		return 0;
	}
	return 1;
}

CheckCrimeAccess(playerid, perm = INVALID_PARAM, bool: only_leader = false) 
{ 
	// Если не член криминальной организации 
	if (GetCrimeMember(playerid) == INVALID_PARAM) 
	{ 
		return 0; 
	} 

	// Если только проверяем на лидера 
	if (only_leader) 
	{ 
		return IsCrimeLeader(playerid); 
	}

	// Если сравнение идет по привилегии, то проверяем эту привилегию 
	if ((perm != INVALID_PARAM && !GetCrimeMemberPerm(playerid, perm)) && !IsCrimeLeader(playerid)) 
	{ 
		return 0; 
	} 

	return 1; 
}

ClearCrimeData()
{
	for (new i; i < sizeof crime_data; i++)
	{
		Clear:crime_data(i);
	}
}

ClearCrimeMemberDataToIndex(index)
{
	for (new i; i < sizeof crmember_data; i++)
	{
		if (crmember_data[i][cr_crime_index] != index)
		{
			continue;
		}
		
		Clear:crmember_data(i);
	}
	
	return 1;
}

GetCrimeLeaderId(index)
{
	for (new i; i < sizeof crmember_data; i++)
	{
		if (crmember_data[i][cr_leader] && crmember_data[i][cr_crime_index] == index)
		{
			return i;
		}
		
		continue;
	}
	
	return INVALID_PARAM;
}

GetCrimeMemberIdToName(string[])
{
	for (new i; i < sizeof character_data; i++)
	{
		if (strcmp(string, character_data[i][c_name], true) != 0)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

GetCrimeMemberIdToSelect(playerid, crime_member_index)
{
	for (new i; i < sizeof character_data; i++)
	{
		if (character_data[i][c_id] != crmember_select[playerid][crime_member_index][cr_character_id])
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

GetCrimeBuyIndexToCategory(category)
{
	for (new i; i < sizeof crbuy_data; i++)
	{
		if (crbuy_data[i][cr_buy_cat] != category)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

GetCrimeBuyStorageIndexByPlayer(index, id)
{
	for (new i; i < MAX_CRIME_CUSTOMER; i++)
	{
		if (crbuy_storage[index][i][cr_buy_customer_id] != id)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

GetCrimeBuyStorageFreeIndex(index)
{
	for (new i; i < MAX_CRIME_CUSTOMER; i++)
	{
		if (crbuy_storage[index][i][cr_buy_customer_id] != 0)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

GetCrimBuyFreeLocationIndex()
{
	for (new i; i < sizeof crbuy_location; i++)
	{
		if (crbuy_location[i][cr_loc_status] == true)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

function OnCrimeStorageTimerPast(playerid, crime_text_3d, crime_index, storage_id_exist, storage_location_exist)
{	
	KillTimer(crbuy_storage[crime_index][storage_id_exist][cr_buy_timer]);

	crbuy_location[storage_location_exist][cr_loc_status] = false;
	
	DestroyDynamic3DTextLabel(crbuy_storage[crime_index][storage_id_exist][cr_buy_3d_label]);
	
	new targetid = INVALID_PARAM;
	
	for (new i; i < sizeof character_data; i++)
	{
		if (character_data[i][c_id] == crbuy_storage[crime_index][storage_id_exist][cr_buy_customer_id])
		{
			targetid = i;
		}
	}
	
	if(targetid != INVALID_PARAM)
	{
		pformat:("" #ERROR " Вы не успели забрать свой заказ, товар безвозвратно удален.");
		psend:(targetid, C_WHITE);
		
		DisablePlayerCheckpoint(targetid);
	}
		
	Clear:crbuy_storage_to_player(crime_index, storage_id_exist);
	
	return 1;
}

InvitePlayerToCrime(playerid, params[], bool: is_dialog)
{
	// Проверяем на лидерство или наличие привилегий
	if (!CheckCrimeAccess(playerid, INVALID_PARAM, true)
	&& !CheckCrimeAccess(playerid, cr_perm_manage, false)
	&& !CheckCrimeAccess(playerid, cr_perm_invite, false)
	)
	{
		if (is_dialog)
		{
			ShowCrimeStaffInvite(playerid, "У Вас нет доступа для совершения данного действия.");
		}
		else
		{
			SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		}
	   
		return 0;
	}

	new targetid = strval(params);
	
	// Проверяем на доступность игрока (онлайн, ID, находится ли около игрока)
	if (isnull(params)
	|| !IsInt(params)
	|| !IsPlayerLogged(targetid)
	|| playerid == targetid 
	|| !IsPlayerAroundOfPlayer(playerid, targetid))
	{
		if (is_dialog)
		{
			ShowCrimeStaffInvite(playerid, "Вы указали некорректного игрока.");
		}
		else
		{
			SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		}
	   
		return 0;
	}
	
	// Проверяем на трудоустройство в фракции, крайме
	if (IsFractionMember(targetid) || CheckCrimeAccess(targetid))
	{
		if (is_dialog)
		{
			ShowCrimeStaffInvite(playerid, "Игрок находиться в организации.");
		}
		else
		{
			pformat:("" #ERROR " Игрок находиться в организации.");
			psend:(playerid, C_WHITE);
		}
	   
		return 0;
	}
	
	new index = GetCrimeMember(playerid);
   
    pformat:("" #SUCCESS " Вы отправили приглашение " #cPROJECT "%s" #cWHITE ".",
        GetPlayerCurrentName(targetid)
    );
    psend:(playerid, C_WHITE);
   
    SetPVarInt(targetid, "Crime:MemberId", playerid);
    SetPVarInt(targetid, "Crime:MemberIndex", index);
   
    format:g_string("" #DEFAULT " Приглашение\n\n\
        Приглашение от " #cPROJECT "%s" #cWHITE ".\n\
        Вас приглашают стать участником криминальной организации " #cPROJECT "%s" #cWHITE ".\n\
        Вы принимаете приглашение?",
        GetPlayerCurrentName(playerid),
        GetCrimeName(playerid)
    );
   
    ShowPlayerDialog(targetid, D_CRIME_INVITE_PLAYER, DIALOG_STYLE_MSGBOX, " ",
		g_string,
		"Да", "Нет"
	);

    return 1;
}

// Наркотики
ShowPlayerDrugEffect(playerid, param)
{
	new Float: health;

	if (param == INV_FUNC_MARIJUANA) // ЭФФЕКТ МАРИХУАНЫ
	{
		if (!character_data[playerid][c_drugs_effect][drug_effect_minute_timer])
		{
			character_data[playerid][c_drugs_effect][drug_effect_minute_timer] = 15; // длительность эффекта в минутах
			
			health = GetCharacterHealth(playerid) + 50; // единоразовая прибавка к здоровью
			
			if (health > 100)
			{
				health = 100 - GetCharacterHealth(playerid);
			
				SetCharacterHealth(playerid, health);
			}
			
			SetCharacterHealth(playerid, health);
		}
	
		SetPlayerTime(playerid, 0, 0);
		SetPlayerWeather(playerid, 124);
		
		SetPlayerDrunkLevel(playerid, 2100);
		
		return 1;
	}
	
	if (param == INV_FUNC_LSD) // ЭФФЕКТ ЛСД
	{
		if (!character_data[playerid][c_drugs_effect][drug_effect_minute_timer])
		{
			character_data[playerid][c_drugs_effect][drug_effect_minute_timer] = 25;
		}
	
		health = GetCharacterHealth(playerid) + 1;
			
		if (health < 100 && character_data[playerid][c_drugs_effect][drug_effect_second_timer] >= 9) // Ограничение на прибавку к здоровью раз в 10 секунд
		{
			SetCharacterHealth(playerid, health);
			
			character_data[playerid][c_drugs_effect][drug_effect_second_timer] = 0;
		}
	
		SetPlayerTime(playerid, 3, 0);
		SetPlayerWeather(playerid, 253);
		
		SetPlayerDrunkLevel(playerid, 2100);
	
		return 1;
	}
	
	if (param == INV_FUNC_COCAINE) // ЭФФЕКТ КОКАИНА
	{
		if (!character_data[playerid][c_drugs_effect][drug_effect_minute_timer])
		{
			character_data[playerid][c_drugs_effect][drug_effect_minute_timer] = 20;
			character_data[playerid][c_drugs_effect][drug_effect_second_timer] = 5;
		}
		
		health = GetCharacterHealth(playerid) + 1;
			
		if (health < 100 && character_data[playerid][c_drugs_effect][drug_effect_second_timer] >= 4) // Ограничение на прибавку к здоровью раз в 5 секунд
		{
			SetCharacterHealth(playerid, health);
			
			character_data[playerid][c_drugs_effect][drug_effect_second_timer] = 0;
		}
		
		SetPlayerTime(playerid, 16, 0);
		SetPlayerWeather(playerid, 188);
	
		return 1;
	}
	
	return 0;
}