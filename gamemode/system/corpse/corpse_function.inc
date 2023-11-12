/*!
	@brief Система трупов
	@author Found (evg.savosin)
	@date 27.04.2018
*/

// Public function
Corpse_OnGameModeInit()
{
	CorpseCameraAreas();
	CorpseDirtArea();
	
	for (new i; i < MAX_CORPSES; i++)
	{
		Clear:corpse_data(i);
	}

	// Mysql Query
	format:g_string("DELETE FROM " #__CORPSES " WHERE corp_created_time <= %i", 
		gettime() - (60 * 60 * 24 * 30)
	);
	
	mysql_pquery(db, g_string);
	
	format:g_string("SELECT * FROM " #__CORPSES " LIMIT %i", MAX_CORPSES);
	mysql_tquery(db, g_string, "OnCorpseLoad", "");
}

Corpse_OnPlayerDisconnect(playerid)
{
	if (GetPVarInt(playerid, "Player:CorpseDigs"))
	{
		new timer = GetPVarInt(playerid, "Player:CorpseDigsTimer"),
			index = GetPVarInt(playerid, "Player:CorpseDigsIndex");
			
		KillTimer(timer);
		
		corpse_data[index][corp_used] = false;
	}
	
	if (GetPVarInt(playerid, "Player:CorpsePourAcid"))
	{
		new timer = GetPVarInt(playerid, "Player:CorpsePourAcidTimer"),
			index = GetPVarInt(playerid, "Player:CorpsePourAcidIndex");
			
		KillTimer(timer);
		
		corpse_data[index][corp_used] = false;
	}
	
	if (GetPVarInt(playerid, "Player:CorpsePourGas"))
	{
		new timer = GetPVarInt(playerid, "Player:CorpsePourGasTimer"),
			index = GetPVarInt(playerid, "Player:CorpsePourGasIndex");
			
		KillTimer(timer);
		
		corpse_data[index][corp_used] = false;
	}
}

Corpse_OnPlayerEnterDynamicArea(playerid, areaid) 
{
	CorpseCameraAreasPlayerEnter(playerid, areaid);
	CorpseDirtAreaPlayerEnter(playerid, areaid);
}

Corpse_OnPlayerLeaveDynamicArea(playerid, areaid) 
{
	CorpseCameraAreasPlayerLeave(playerid, areaid);
	CorpseDirtAreaPlayerLeave(playerid, areaid);
}


// Other function 
ShowCorpseInformation(playerid, index)
{
	if (corpse_data[index][corp_state] == STATE_CORP_COAL)
	{
		new name		[	MAX_PLAYER_NAME		];
		
		GetWithoutUnderscore(corpse_data[index][corp_character_name], name);
			
		format:g_big_string("" #DEFAULT " Информация о трупе #%i\n\n\
			Имя: " #cPROJECT "%s" #cWHITE "\n\n\
			" #cRED "ТРУП СОЖЖЕН, ОСТАЛЬНАЯ ИНФОРМАЦИЯ НЕДОСТУПНА",
			name,
			index + 1
		);
	}
	else
	{
		new approximately_time = GetCorpseApproximatelyDeathTime(corpse_data[index][corp_created_time]),
		
			year,
			month,
			day,
			hour,
			minute,
			
			cyear,
			cmonth,
			cday,
			chour,
			cminute,
			csecond,
			
			windex,
			itindex = INVALID_ITEM_ID,
			street_name							[		64			],
			name								[	MAX_PLAYER_NAME	],
			
			str_case							[		128	 		],
			str_biological						[		128 		],
			str_blood							[		128 		],
			str_camera 							[		128 		],
			str_gas								[		128			];
		
		
		windex = GetItemWeaponIndexByParam(corpse_data[index][corp_weapon_id]);
		printf("windex: %i, corp_weapon_id: %i", windex, corpse_data[index][corp_weapon_id]);
		if (windex != INVALID_ITEM_ID)
		{
			itindex = GetItemIndexById(item_list[windex][it_param_2]);
		}	
		
		GetZoneName(
			corpse_data[index][corp_pos][0], 
			corpse_data[index][corp_pos][1], 
			street_name, 
			sizeof street_name 
		);
		
		gmtime(approximately_time, year, month, day, hour, minute, _);
		gmtime(corpse_data[index][corp_created_time], cyear, cmonth, cday, chour, cminute, csecond);
		
		if (itindex != INVALID_ITEM_ID)
		{
			format:str_case("Гильзы оружейного калибра " #cPROJECT "%s" #cWHITE ".", 
				item_list[itindex][it_name]
			);
		}
		
		if (corpse_data[index][corp_state] != STATE_CORP_ACID)
		{
			if (!isnull(corpse_data[index][corp_attack_name_fist]))
			{
				format:str_biological("Фрагменты биологической ткани под ногтями. " #cGRAY "(%s)" #cWHITE "",
					corpse_data[index][corp_attack_name_fist]
				);
			}
			
			if (!isnull(corpse_data[index][corp_attack_name_cold]))
			{
				format:str_blood("Фрагменты крови на одежде. " #cGRAY "(%s)" #cWHITE "",
					corpse_data[index][corp_attack_name_cold]
				);
			}
		}
		
		if (corpse_data[index][corp_poured_gas])
		{
			format:str_gas("Присутствие следов горючей смеси.");
		}
		
		if (!isnull(corpse_data[index][corp_camera_name]))
		{
			format:str_camera("[%02d:" #DATE_FORMAT "]: Los Santos, %s. " #cGRAY "(%s)" #cWHITE "",
				chour, cminute, csecond, cday, cmonth, cyear,
				street_name,
				corpse_data[index][corp_camera_name]
			);
		}
		else
		{
			strcat(str_camera, "Отсутствуют"); 
		}
	
		GetWithoutUnderscore(corpse_data[index][corp_character_name], name);
		
		format:g_big_string("" #DEFAULT " Информация о трупе #%i\n\n\
			Имя: " #cPROJECT "%s" #cWHITE ".\n\
			Причина смерти: " #cPROJECT "%s" #cWHITE ".\n\
			Предполагаемая дата смерти: " #cPROJECT "" #DATE_FORMAT "" #cWHITE ".\n\n\
			" #DEFAULT " Улики:\n\
			%s%s\
			%s%s\
			%s%s\
			%s%s\n\
			Записи с камер видеонаблюдения:\n\
			%s",
			index + 1,
			name,
			GetCorpseReasonText(index),
			hour, minute, day, month, year,
			str_case, !isnull(str_case) ? ("\n") : (""),
			str_biological, !isnull(str_biological) ? ("\n") : (""),
			str_blood, !isnull(str_blood) ? ("\n") : (""),
			str_gas, !isnull(str_gas) ? ("\n") : (""),
			str_camera
		);
	}
	
	ShowPlayerDialog(playerid, D_CORPSE + 1, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Назад", "");
}

GetCorpseApproximatelyDeathTime(time)
{
	new current_time = gettime();
	
	time -= current_time;

	if (time <= (60 * 60 * 24 * 7)) // 1 неделя
	{
		return ((time + (60 * 60)) + current_time) - 100;
	}
	else if (time <= (60 * 60 * 24 * 7 * 2)) // 2 неделя
	{
		return ((time + (60 * 60 * 24)) + current_time) - 200;
	}
	else if (time <= (60 * 60 * 24 * 7 * 3)) // 3 неделя
	{
		return ((time + (60 * 60 * 24 * 2)) + current_time) - 300;
	}
	
	return time + current_time;
}

GetCorpseOldTimeIndex()
{
	new time,
		index;
		
	for (new i; i < MAX_CORPSES; i++)
	{
		time = corpse_data[i][corp_created_time];
		
		for (new j; j < MAX_CORPSES; j++)
		{
			if (corpse_data[j][corp_created_time] < time)
			{
				time = corpse_data[j][corp_created_time];
				index = j;
			}
			
			j++;
		}
	}
	
	return index;
}

GetFreeIndexForCorpse()
{
	for (new i; i < MAX_CORPSES; i++)
	{
		if (corpse_data[i][corp_type] == TYPE_CORP_NONE)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

Create:corpse(index)
{	
	if (corpse_data[index][corp_state] == STATE_CORP_DEFAULT)
	{
		corpse_data[index][corp_actor] = CreateDynamicActor(
			corpse_data[index][corp_skin],
			corpse_data[index][corp_pos][0],
			corpse_data[index][corp_pos][1],
			corpse_data[index][corp_pos][2],
			corpse_data[index][corp_pos][3] ,
			_,
			_,
			corpse_data[index][corp_world],
			corpse_data[index][corp_int],
			_,
			100.0
		);
		
		ApplyDynamicActorAnimation(corpse_data[index][corp_actor], "PED", "FLOOR_hit_f", 4.1, 0, 1, 1, 1, 0);
	}
	
	
	if (corpse_data[index][corp_state] == STATE_CORP_DEFAULT
	|| corpse_data[index][corp_state] == STATE_CORP_ACID)
	{
		format:g_small_string("Труп - " #cPROJECT "/corpse %i", index + 1);
	
		if (corpse_data[index][corp_reason] != REASON_CORP_FIST)
		{
			corpse_data[index][corp_object] = CreateDynamicObject(
				19477,
				corpse_data[index][corp_pos][0],
				corpse_data[index][corp_pos][1],
				corpse_data[index][corp_pos][2] - 1.0,
				0.0,
				90.0,
				0.0,
				corpse_data[index][corp_world],
				corpse_data[index][corp_int]
			);
			
			SetDynamicObjectMaterial(corpse_data[index][corp_object], 0, 14612, "ab_abattoir_box", "ab_bloodfloor", 0x00000000);
		}
	}
	else if (corpse_data[index][corp_state] == STATE_CORP_BURY)
	{
		format:g_small_string("Труп - " #cPROJECT "/corpse %i", index + 1);
		
		corpse_data[index][corp_object] = CreateDynamicObject(
			854, 
			corpse_data[index][corp_pos][0],
			corpse_data[index][corp_pos][1],
			corpse_data[index][corp_pos][2] - 0.9,
			0.0,
			0.0,
			0.0,
			corpse_data[index][corp_world],
			corpse_data[index][corp_int]
		); 
		
		SetDynamicObjectMaterial(corpse_data[index][corp_object], 0, 17075, "cuntwlandwest", "cw2_mounttrailblank", 0x00000000);
	}
	else if (corpse_data[index][corp_state] == STATE_CORP_COAL)
	{
		format:g_small_string("Труп - " #cPROJECT "/corpse %i", index + 1);
		
		corpse_data[index][corp_object] = CreateDynamicObject(
			2907, 
			corpse_data[index][corp_pos][0],
			corpse_data[index][corp_pos][1],
			corpse_data[index][corp_pos][2] - 1.0,
			0.0,
			0.0,
			90.0,
			corpse_data[index][corp_world],
			corpse_data[index][corp_int]
		); 
		
		SetDynamicObjectMaterial(corpse_data[index][corp_object], 0, 19882, "marcossteak2", "cj_steak", 0x00000000);
	}
	
	corpse_data[index][corp_text] = CreateDynamic3DTextLabel(
		g_small_string, 
		C_WHITE, 
		corpse_data[index][corp_pos][0],
		corpse_data[index][corp_pos][1],
		corpse_data[index][corp_pos][2],
		1.5, 
		_, 
		_,
		_,
		corpse_data[index][corp_world],
		corpse_data[index][corp_int]
	);
}

Destroy:corpse(index, bool: is_save = false)
{
	if (IsValidDynamicActor(corpse_data[index][corp_actor]))
	{
		DestroyDynamicActor(corpse_data[index][corp_actor]);
	}
	
	if (IsValidDynamic3DTextLabel(corpse_data[index][corp_text]))
	{
		DestroyDynamic3DTextLabel(corpse_data[index][corp_text]);
	}
	
	if (IsValidDynamicObject(corpse_data[index][corp_object]))
	{
		DestroyDynamicObject(corpse_data[index][corp_object]);
	}
	
	if (!is_save)
	{
		Clear:corpse_data(index);
	}
}

Recreate:corpse(index, type)
{
	corpse_data[index][corp_state] = type;
	Update:corpse_int(index, "corp_state", type);
	Destroy:corpse(index, true);
	Create:corpse(index);
}

Create:corpse_fire(index)
{
	if (!corpse_data[index][corp_poured_gas])
	{
		return 0;
	}
	
	corpse_data[index][corp_poured_gas] = false;
	corpse_data[index][corp_used] = true;
	
	corpse_data[index][corp_fire_object] = CreateDynamicObject(
		18688, 
		corpse_data[index][corp_pos][0],
		corpse_data[index][corp_pos][1],
		corpse_data[index][corp_pos][2] - 2.34,
		0.0,
		0.0,
		0.0,
		corpse_data[index][corp_world],
		corpse_data[index][corp_int]
	);

	SetTimerEx("OnCorpseFireOut", 1000 * 20, false, "i", index);
	return 1;
}

function OnCorpseFireOut(index)
{
	if (IsValidDynamicObject(corpse_data[index][corp_fire_object]))
	{
		DestroyDynamicObject(corpse_data[index][corp_fire_object]);
	}
	
	Recreate:corpse(index, STATE_CORP_COAL);
	return 1;
}