/*
    Load user and character data
*/

function OnUserLoad(playerid)
{
	new rows;
	
	cache_get_row_count(rows);
	
	if (!rows)
	{
		Kick(playerid);
		return 1;
	}
	
	// Integer
	cache_get_value_name_int(0, "u_warn", user_data[playerid][u_warn]);
	cache_get_value_name_int(0, "u_register_time", user_data[playerid][u_register_time]);
	cache_get_value_name_int(0, "u_last_time", user_data[playerid][u_last_time]);
	cache_get_value_name_int(0, "u_cash_action", user_data[playerid][u_cash_action]);
	cache_get_value_name_int(0, "u_helper", user_data[playerid][u_helper]);
	cache_get_value_name_int(0, "u_vip", user_data[playerid][u_vip]);
	cache_get_value_name_int(0, "u_vip_time", user_data[playerid][u_vip_time]);
	
	// String
	cache_get_value_name(0, "u_email", user_data[playerid][u_email], MAX_PLAYER_EMAIL);
	cache_get_value_name(0, "u_reg_ip", user_data[playerid][u_reg_ip], MAX_PLAYER_IP);
	cache_get_value_name(0, "u_last_ip", user_data[playerid][u_last_ip], MAX_PLAYER_IP);
	
	// Настройки
	Load:user_settings(playerid);
	
	printf("[OnUserLoad]: User %s(%d)[%d] has been logged. IP: %s", 
		user_data[playerid][u_name],
		user_data[playerid][u_id],
		playerid,
		GetUserIp(playerid)
	);
	
	return 1;
}

Load:character(playerid)
{	
	new name	[MAX_PLAYER_NAME],
		result;
	
	// Character name
	cache_get_value_name(0, "c_name", character_data[playerid][c_name], MAX_PLAYER_NAME);
	
	// Get name with out underscore
	GetWithoutUnderscore(character_data[playerid][c_name], name);
	strcat(character_data[playerid][c_rpname], name, MAX_PLAYER_NAME);
	
	// Replcae name and check 
	result = ReplacePlayerName(playerid, TYPE_IC);
	
	if (strcmp(user_data[playerid][u_name], character_data[playerid][c_name]) != 0 && result != 1)
	{
		printf("[Load:character]: Player (ID: %d) not logged and has been kicked. (%d, %d)",
			playerid,
			strcmp(user_data[playerid][u_name], character_data[playerid][c_name]),
			result
		);
		
		Kick(playerid);
		return 1;
	}
	
	// Integer
	cache_get_value_name_int(0, "c_id", character_data[playerid][c_id]);
	cache_get_value_name_int(0, "c_sex", character_data[playerid][c_sex]);
	cache_get_value_name_int(0, "c_skin", character_data[playerid][c_skin]);
	cache_get_value_name_int(0, "c_money", character_data[playerid][c_money]);
	cache_get_value_name_int(0, "c_bank", character_data[playerid][c_bank]);
	cache_get_value_name_int(0, "c_card", character_data[playerid][c_card]);
	cache_get_value_name_int(0, "c_credit_level", character_data[playerid][c_credit_level]);
	cache_get_value_name_int(0, "c_world", character_data[playerid][c_world]); 
	cache_get_value_name_int(0, "c_int", character_data[playerid][c_int]);
	cache_get_value_name_int(0, "c_role", character_data[playerid][c_role]); 
	cache_get_value_name_int(0, "c_race", character_data[playerid][c_race]); 
	cache_get_value_name_int(0, "c_age", character_data[playerid][c_age]);
	cache_get_value_name_int(0, "c_last_time", character_data[playerid][c_last_time]); 
	cache_get_value_name_int(0, "c_register_time", character_data[playerid][c_register_time]); 
	cache_get_value_name_int(0, "c_desc_created_time", character_data[playerid][c_desc_created_time]);
	cache_get_value_name_int(0, "c_death", character_data[playerid][c_death]);
	cache_get_value_name_int(0, "c_buy_weapon_count", character_data[playerid][c_buy_weapon_count]);
	cache_get_value_name_int(0, "c_start_capital", character_data[playerid][c_start_capital]);
	cache_get_value_name_int(0, "c_start_pack_buy_time", character_data[playerid][c_start_pack_buy_time]);
	cache_get_value_name_int(0, "c_capital_value", character_data[playerid][c_capital_value]);
	cache_get_value_name_int(0, "c_capital_end_time", character_data[playerid][c_capital_end_time]);
	
	cache_get_value_name_int(0, "c_payday", character_data[playerid][c_payday]);
	
	cache_get_value_name_int(0, "c_fuber_balance", character_data[playerid][c_fuber_balance]);
	cache_get_value_name_int(0, "c_fuber_reputation", character_data[playerid][c_fuber_reputation]);
	cache_get_value_name_int(0, "c_fuber_method_payment", character_data[playerid][c_fuber_method_payment]);
	
	cache_get_value_name_int(0, "c_arrest_type", character_data[playerid][c_arrest_type]);
	cache_get_value_name_int(0, "c_arrest_camera", character_data[playerid][c_arrest_camera]);
	cache_get_value_name_int(0, "c_arrest_time", character_data[playerid][c_arrest_time]);
	
	
	// Float
	cache_get_value_name_float(0, "c_health", character_data[playerid][c_health]);
	cache_get_value_name_float(0, "c_pos_x", character_data[playerid][c_pos][0]);
	cache_get_value_name_float(0, "c_pos_y", character_data[playerid][c_pos][1]);
	cache_get_value_name_float(0, "c_pos_z", character_data[playerid][c_pos][2]);
	cache_get_value_name_float(0, "c_pos_angle", character_data[playerid][c_pos][3]);
	
	// String
	cache_get_value_name(0, "c_desc", character_data[playerid][c_desc], MAX_PLAYER_DESC);
	cache_get_value_name(0, "c_attack_name_fist", character_data[playerid][c_attack_name_fist], MAX_PLAYER_NAME);
	cache_get_value_name(0, "c_attack_name_cold", character_data[playerid][c_attack_name_cold], MAX_PLAYER_NAME); 
	cache_get_value_name(0, "c_attack_name_camera", character_data[playerid][c_attack_name_camera], MAX_PLAYER_NAME);
	cache_get_value_name(0, "c_suspect", character_data[playerid][c_suspect], MAX_CHARACTER_SUSPECT);
	
	if (!isnull(character_data[playerid][c_attack_name_fist])
	|| !isnull(character_data[playerid][c_attack_name_cold]))
	{
		SetPVarInt(playerid, "Player:AttackNameTime", gettime());
	}
	
	// Player is auth
	user_login{playerid} = true; 
	
	// Load property
	Load:character_property(playerid);

	// Set character loaded flag
	SetCharacterLoaded(playerid, true);
	
    // Callback
    CallLocalFunction("OnCharacterAfterLoad", "d", playerid);

	// Log
	printf("[Load:character]: Character %s(%d)[%d] has been loaded. IP: %s", 
		character_data[playerid][c_name],
		character_data[playerid][c_id],
		playerid,
		GetUserIp(playerid)
	);
	
	return 1;
}

Load:character_property(playerid)
{		
	/*
		
		Single 
	
	*/
	
	// Load settings
	Load:character_settings(playerid);
	
	// Load credit
	Load:character_credit(playerid);
	
	// Load licenses
	Load:character_license(playerid);
	
	// Load houses
	Load:character_houses(playerid);
	
	// Load premises
	Load:character_premise(playerid);
	
	// Load sites
	Load:character_sites(playerid);
	
	// Load and return refund money (House, premises)
	Load:character_refund(playerid);
	
	// Load businesses
	Load:character_business(playerid);
	
	// Load fraction
	Load:character_fraction(playerid);
	
	// Load crime
	Load:character_crime_member(playerid);
	
	/*
		
		Multi with query
	
	*/
	
	// Load lodger
	if (!GetPlayerHousesCount(playerid))
	{
		Load:character_lodger(playerid);
	}
	
	// Load business member
	Load:character_business_member(playerid);
	
	// Load inventory items
	Load:inventory(playerid, TYPE_INV_PLAYER);
	
	// Load player vehicle
	Load:vehicle(playerid, TYPE_VEH_PLAYER, true);
}

Load:character_refund(playerid)
{
	new refund,
		diff,
		credit;
	
	cache_get_value_name_int(0, "c_refund", refund);
	
	if (refund == 0)
	{
		return;
	}
	
	Update:character_int(playerid, "c_refund", 0);
	
	if (IsCreditCardExists(playerid) 
	&& IsCreditCardUse(playerid))
	{
		if (refund >= (diff = GetCreditDifference(playerid)))
		{
			refund -= diff;
			GiveCreditCardMoney(playerid, diff);
			credit = diff;
		}
		else
		{
			GiveCreditCardMoney(playerid, refund);
			refund = 0;
			credit = refund;
		}
	}
	
	if (refund != 0)
	{
		GiveDebitCardMoney(playerid, refund);
		
		pformat:("" #SUCCESS " Ваше имущество было продано в связи с задолжностями. Средства в размере " #cGREEN "$%i" #cWHITE " были возвращены на карту.",
			refund
		);
		
		psend:(playerid, C_WHITE);
	}
	
	if (credit == 0)
	{
		return; 
	}
	
	pformat:("" #DEFAULT " Часть средств (" #cGREEN "$%i" #cWHITE ") была направлена на выплату кредита в автоматическом порядке.",
		credit
	);
	
	psend:(playerid, C_WHITE);
}

function OnPlayerBeforeSpawn(playerid)
{	
	if (!user_login{playerid})
	{
		return;
	}
	
    new in_interior = GetCharacterInt(playerid) != 0 || GetCharacterWorld(playerid) != 0;

	new Float: x,
		Float: y,
		Float: z,
		Float: angle;
		
	GetSpawnInfo(playerid, x, y, z, angle);
	SetSpawnInfo(
		playerid, 
		264,
		character_data[playerid][c_fraction_skin] > 0 ? character_data[playerid][c_fraction_skin] : character_data[playerid][c_skin],
		x, 
		y, 
		z,
		angle,
		0, 
		0, 
		0, 
		0, 
		0, 
		0 
	);
	
	SetPlayerScore(playerid, 1);
	
	// Устанавливаем цвет фракции
	if (IsFractionMember(playerid) && IsFractionMemberOnDuty(playerid))
	{
		new findex = GetFractionMember(playerid);
		
		SetPlayerColor(
			playerid,
			fraction_data[findex][fr_color]
		);
	}
	
	// Обновляем статус онлайна
	Update:user_int(playerid, "u_online", 1);
	Update:character_int(playerid, "c_online", 1);
	
	// Обновляем погоду
	Update:player_weather(playerid);

	if (!in_interior)
	{		
		DeletePVar(playerid, "Player:InInterior");
		Streamer_SetVisibleItems(
			STREAMER_TYPE_OBJECT, 
			GetUserSettings(playerid, SET_VISIBLE_OBJECT),
			playerid
		);
	}
	else
	{
		SetPVarInt(playerid, "Player:InInterior", true);
		Streamer_SetVisibleItems(STREAMER_TYPE_OBJECT, MAX_VISIBLE_OBJECTS_ALL);
	}

    TogglePlayerSpectating(playerid, false); 
	
	// Hello message
    if (!HasPlayerRelogin(playerid))
    { 
        if (user_data[playerid][u_last_time] > 0)
        {
            pformat:(#DEFAULT " C возвращением, " #cPROJECT "%s" #cWHITE ".", GetUserName(playerid));
        }
        else 
        {
            pformat:(#DEFAULT " Добро пожаловать, " #cPROJECT "%s" #cWHITE ".", GetPlayerCurrentName(playerid));
        }
        
        psend:(playerid, C_WHITE);
	
        // Информация о VIP аккаунте
        if (GetUserVip(playerid) >= VIP_STARTER)
        {
            pformat:(#SUCCESS " У Вас действует VIP аккаунт: " #cGOLD "%s" #cWHITE ".", 
                GetUserVipText(playerid)
            );
            
            psend:(playerid, C_WHITE);
        }
    }

    // Check
    Check:credit(playerid);

    CallLocalFunction("OnPlayerAfterSpawn", "d", playerid);
}
