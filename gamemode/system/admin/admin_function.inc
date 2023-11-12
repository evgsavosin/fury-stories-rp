/*!
	@brief Функции для системы администрирования
	@author Found (evg.savosin)
	@date 16.12.2016, update 08.03.2018
	
*/

Admin_OnGameModeInit()
{
	admin_menu = CreateMenu("Admin", 0, 5.0, 160.0, 50.0);
 	SetMenuColumnHeader(admin_menu, 0, "Menu");
	AddMenuItem(admin_menu, 0, "Next");
	AddMenuItem(admin_menu, 0, "Update");
	AddMenuItem(admin_menu, 0, "Back");
	AddMenuItem(admin_menu, 0, "Stats");
	AddMenuItem(admin_menu, 0, "Sessions");
	AddMenuItem(admin_menu, 0, "Items");
	AddMenuItem(admin_menu, 0, "Quit");
}

Admin_OnPlayerDeath(playerid, killerid, reason)
{
	foreach (new i : Player)
	{
		if (IsPlayerGameAdmin(i))
		{
			SendDeathMessageToPlayer(i, killerid, playerid, reason);
		}
	}
}

Admin_OnPlayerSelectedMenuRow(playerid, row) 
{
    if (GetPlayerMenu(playerid) == admin_menu)
	{
        new specid = GetPVarInt(playerid, "Admin:SpectateId"),
			vehicleid;
			
		ShowMenuForPlayer(admin_menu, playerid);
		
        switch(row) 
		{
			case 0:
			{
				if (GetPVarInt(playerid, "Admin:SpectateId") >= GetPlayerPoolSize())
				{
					SetPVarInt(playerid, "Admin:SpectateId", 0);
				}
				else
				{
					GivePVarInt(playerid, "Admin:SpectateId", 1);
				}
						
				for (new i = GetPVarInt(playerid, "Admin:SpectateId"), j = GetPlayerPoolSize(); i <= j; i++)
				{
					if (!IsPlayerLogged(i) || (i == playerid))
					{
						GameTextForPlayer(playerid, "~r~INCORRECT PLAYER", 1500, 4);
						continue;
					}
					
					SetPVarInt(playerid, "Admin:SpectateId", i);
					SetPlayerInterior(playerid, GetPlayerInterior(i));
					SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(i));
					
					if (!IsPlayerInAnyVehicle(i)) 
					{
						PlayerSpectatePlayer(playerid, i);
					}
					else
					{
						vehicleid =  GetPlayerVehicleID(i);
						SetPVarInt(playerid, "Admin:ShowVehicleMessage", vehicleid);
						PlayerSpectateVehicle(playerid, vehicleid);
					}
					
					break;
				}
			}
			
			case 1:
			{		
				if (!IsPlayerLogged(specid) || (specid == playerid))
				{
					AdminStopSpectate(playerid);
					return 1;
				}

				SetPlayerInterior(playerid, GetPlayerInterior(specid));
				SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(specid));
				
				if (!IsPlayerInAnyVehicle(specid)) 
				{
					PlayerSpectatePlayer(playerid, specid);
				}
				else 
				{
					vehicleid = GetPlayerVehicleID(specid);
					SetPVarInt(playerid, "Admin:ShowVehicleMessage", vehicleid);
					PlayerSpectateVehicle(playerid, vehicleid);
				}
			}
			
			case 2:
			{
				if (GetPVarInt(playerid, "Admin:SpectateId") <= 0)
				{
					SetPVarInt(playerid, "Admin:SpectateId", GetPlayerPoolSize());
				}
				else 
				{
					TakePVarInt(playerid, "Admin:SpectateId", 1);
				}
					
				for (new i = GetPVarInt(playerid, "Admin:SpectateId"); i >= 0; i--)
				{
					if (!IsPlayerLogged(i) || (i == playerid))
					{
						GameTextForPlayer(playerid, "~r~INCORRECT PLAYER", 1500, 4);
						continue;
					}
					
					SetPVarInt(playerid, "Admin:SpectateId", i);
					
					SetPlayerInterior(playerid, GetPlayerInterior(i));
					SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(i));
					
					if (!IsPlayerInAnyVehicle(i)) 
					{
						PlayerSpectatePlayer(playerid, i);
					}
					else
					{
						vehicleid = GetPlayerVehicleID(i);
						SetPVarInt(playerid, "Admin:ShowVehicleMessage", vehicleid);
						PlayerSpectateVehicle(playerid, vehicleid);
					}
					
					break;
				}
			}
			
			case 3: 
			{
			   	ShowPlayerStats(specid, playerid, true);
			}
			
			case 4: 
			{
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " В разработке");
			}
			
			case 5: 
			{
				format:g_small_string("%d", specid);
				cmd_afrisk(playerid, g_small_string);
			}
			
			case 6: 
			{
				AdminStopSpectate(playerid);
			}
       }
   }
	
    return 1;
}

Admin_OnPlayerExitedMenu(playerid) 
{
    ShowMenuForPlayer(GetPlayerMenu(playerid), playerid);
	
	return 1;
}

Admin_OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE))
	{
		return 1;
	}
	
	SetPlayerPos(playerid, fX, fY, fZ + 0.5);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	return 1;
}

function OnAdminLogin(playerid)
{
	new rows,
		str_ip		[	32	];
	
	cache_get_row_count(rows);
	
	if (rows == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не являетесь администратором.");
		return 1;
	}
	
	cache_get_value_name(0, "a_ip", str_ip, sizeof str_ip);
	cache_get_value_name_int(0, "a_level", admin_data[playerid][a_level]);
	
	clean:<admin_data[playerid][a_ip]>;
	if (isnull(str_ip))
	{
		Update:admin_string(playerid, "a_ip", GetUserIp(playerid));
		strcat(admin_data[playerid][a_ip], GetUserIp(playerid), MAX_PLAYER_IP);
	}
	else 
	{
		strcat(admin_data[playerid][a_ip], str_ip, MAX_PLAYER_IP);
	}
	
	// Load
	Load:admin_permissions(playerid);
	
	admin_login{playerid} = 1;
	
	ReplacePlayerName(playerid, TYPE_OOC);
	
	if (IsPlayerDeveloper(playerid))
	{
		format:g_small_string("" #ADMIN_MESSAGE " %s[%d] авторизовался как администратор.",
			GetUserName(playerid),
			playerid,
			GetUserIp(playerid)
		);
	}
	else 
	{
		format:g_small_string("" #ADMIN_MESSAGE " %s[%d] авторизовался как администратор. [IP: %s]",
			GetUserName(playerid),
			playerid,
			GetUserIp(playerid)
		);
	}
	
	SendAdminMessage(C_GREEN, g_small_string);
	
	// Admin log
	ShowAdminLog(playerid, true);
	
	printf("[OnAdminLogin]: Admin %s(%d)[%d] has been logged as level %d.",
		GetPlayerCurrentName(playerid),
		GetUserId(playerid),
		playerid,
		GetAdminLevel(playerid)
	);
	
	return 1;
}

SendMessageToReport(playerid, const text[]) 
{
	format:g_small_string("" #ADMIN_MESSAGE " Жалоба %s[%i]: %s",
		GetPlayerCurrentName(playerid),
		playerid, 
		text
	);

	SendAdminMessage(
		IsUserVip(playerid) ? C_PROJECT : C_YELLOW, 
		g_small_string 
	);
	
	pformat:("" #DEFAULT " Текст: " #cGRAY"%s", text);
	psend:(playerid, C_WHITE);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно отправили сообщение администрации.");
}

SendAdminMessage(color, text[], bool: is_split = false, level = ADMIN_TRAINEE)
{
	foreach (new playerid : Player)
	{
		if (IsPlayerGameAdmin(playerid, level))
		{	
			if (is_split)
			{
				SendSplitMessage(playerid, color, text);
			}
			else 
			{
				SendClientMessage(playerid, color, text);
			}
		}
	}
	
	return 1;
}

SendGlobalAdminMessage(text[], playerid = INVALID_PLAYER_ID, pd_text[] = "") 
{
	foreach (new i : Player)
	{
		if (!IsPlayerLogged(i))
		{
			continue;
		}
		
		if (GetUserSettings(i, SET_ADMIN_MESSAGE) || IsAdminLogged(i))
		{
			SendClientMessage(i, C_LIGHTRED, text);
		}
	}
	
	if (playerid != INVALID_PLAYER_ID)
	{
		ProxDetector(30.0, playerid, pd_text, COLOR_FADE3, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, COLOR_FADE5, _, _, true);
	}
}

IsPlayerGameAdmin(playerid, level = ADMIN_TRAINEE, logged = true)
{
	if (admin_data[playerid][a_level] < level)
	{
		return 0;
	}
	
	if (logged && !IsAdminLogged(playerid))
	{
		return 0;
	}
	
	return 1;
}

CheckAdminAccess(playerid, _: level, E_ADMIN_PERMISSIONS: perm = E_ADMIN_PERMISSIONS: INVALID_PARAM)
{
	if (perm == E_ADMIN_PERMISSIONS: INVALID_PARAM)
	{
		if (!IsPlayerGameAdmin(playerid, level))
		{
			return 0;
		}
	}
	else 
	{
		if (!IsPlayerGameAdmin(playerid, level) 
		|| !GetAdminPerm(playerid, perm))
		{
			return 0;
		}
	}
	
	return 1;
}

AdminStartSpectate(playerid, targetid)
{
	if (!GetPVarInt(playerid, "Admin:SpectateMode"))
	{
		new Float: x,
			Float: y,
			Float: z,
			Float: angle;
			
		GetPlayerPos(playerid, x, y, z);
		GetPlayerFacingAngle(playerid, angle);
		
		SetPVarFloat(playerid, "Admin:PosX", x);
		SetPVarFloat(playerid, "Admin:PosY", y);
		SetPVarFloat(playerid, "Admin:PosZ", z);
		SetPVarFloat(playerid, "Admin:PosAngle", angle);
		SetPVarInt(playerid, "Admin:World", GetPlayerVirtualWorld(playerid));
		SetPVarInt(playerid, "Admin:Interior", GetPlayerInterior(playerid));
		SetPVarInt(playerid, "Admin:SpectateId", targetid);
		SetPVarInt(playerid, "Admin:SpectateMode", true);
		
		ShowMenuForPlayer(admin_menu, playerid);
	
		TogglePlayerSpectating(playerid, true);
	}
	
	SetPlayerInterior(playerid, GetPlayerInterior(targetid));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));
	
	new vehicleid = GetPlayerVehicleID(targetid);
	if (vehicleid == 0) 
	{
		PlayerSpectatePlayer(playerid, targetid);
	}
	else 
	{
		SetPVarInt(playerid, "Admin:ShowVehicleMessage", vehicleid);
		PlayerSpectateVehicle(playerid, vehicleid);
	}
}

AdminStopSpectate(playerid)
{
	new Float: x,
		Float: y,
		Float: z,
		Float: angle;
		
	GetSpawnInfo(playerid, x, y, z, angle);	
	SetSpawnInfo(playerid, 264, character_data[playerid][c_skin], x, y, z, angle, 0, 0, 0, 0, 0, 0);
	
	DeletePVar(playerid, "Admin:PosX");
	DeletePVar(playerid, "Admin:PosY");
	DeletePVar(playerid, "Admin:PosZ");
	DeletePVar(playerid, "Admin:PosAngle");
	DeletePVar(playerid, "Admin:World");
	DeletePVar(playerid, "Admin:Interior");
	DeletePVar(playerid, "Admin:ShowVehicleMessage");
	SetPVarInt(playerid, "Admin:SpectateId", INVALID_PLAYER_ID);
	DeletePVar(playerid, "Admin:SpectateMode");
	
	HideMenuForPlayer(admin_menu, playerid);
	TogglePlayerSpectating(playerid, 0);
}

Load:admin_permissions(playerid)
{
	cache_get_value_name_int(0, "ap_developer", admin_data[playerid][a_perm][ap_developer]);
	cache_get_value_name_int(0, "ap_manage_admins", admin_data[playerid][a_perm][ap_manage_admins]);
	cache_get_value_name_int(0, "ap_manage_helpers", admin_data[playerid][a_perm][ap_manage_helpers]);
	cache_get_value_name_int(0, "ap_property", admin_data[playerid][a_perm][ap_property]);
	cache_get_value_name_int(0, "ap_manage_fraction", admin_data[playerid][a_perm][ap_manage_fraction]);
	cache_get_value_name_int(0, "ap_manage_crime", admin_data[playerid][a_perm][ap_manage_crime]);
	cache_get_value_name_int(0, "ap_capital", admin_data[playerid][a_perm][ap_capital]);
}

function INV:admin_faction_add_item(playerid, item_id, param_1, param_2)
{
	new findex = GetPVarInt(playerid, "Admin:FractionSelect");
	
	Create:fraction_item(
		GetFractionId(findex),
		item_id,
		param_1,
		param_2
	);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно добавили предмет к данной фракции.");
	
	ShowAdminFractionEdit(playerid, D_ADMIN + 46, findex);
	return 1;
}

GetCrimeEmptySlot()
{
	for (new i; i < sizeof crime_data; i++)
	{
		if (crime_data[i][cr_id] != 0)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

IsValidLenghtCrimeLeader(playerid, const dialogid, inputtext[], error[] = "")
{
	new len = strlen(inputtext);

	if (!(0 < len < MAX_PLAYER_NAME - 4)) 
	{
		format:g_string("\
			" #DEFAULT " Настройка лидера\n\n\
			" #cWHITE "Введите имя и фамилию лидера криминальной организации в поле для ввода.\n\n\
			" #cGRAY "Примечание:\n\
			" #cPROJECT "* " #cWHITE"Максимальная длина текста - " #cPROJECT "%d" #cWHITE" символов.\n\
			" #cPROJECT "* " #cWHITE"Формат вводимого текста: " #cPROJECT "Имя_Фамилия" #cWHITE".%s%s",
			MAX_PLAYER_NAME-4,
			!isnull(error) ? ("\n\n" #cRED) : (""), 
			error 
		);
	
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ",
			g_string,
			"Далее", "Назад"
		);
		
		return 0;
	}
	
	return 1;
}

IsValidCrimeLeaderName(playerid, const dialogid, inputtext[], error[] = "")
{
	new len = strlen(inputtext);

	for (new i; i < len; i++)
	{
		switch (inputtext[i])
		{
			case 'А'..'Я', 'а'..'я':
			{
				format:g_string("\
					" #DEFAULT " Настройка лидера\n\n\
					" #cWHITE "Введите имя и фамилию лидера криминальной организации в поле для ввода.\n\n\
					" #cGRAY "Примечание:\n\
					" #cPROJECT "* " #cWHITE"Максимальная длина текста - " #cPROJECT "%d" #cWHITE" символов.\n\
					" #cPROJECT "* " #cWHITE"Формат вводимого текста: " #cPROJECT "Имя_Фамилия" #cWHITE".%s%s",
					MAX_PLAYER_NAME-4,
					!isnull(error) ? ("\n\n" #cRED) : (""), 
					error
				);
				
				ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ",
					g_string,
					"Далее", "Назад"
				);
				
				return 0;
			}
			
			default:
			{
				continue;
			}
		}
	}
	
	return 1;
}

IsCrimeNameTwin(playerid, const dialogid, inputtext[], error[] = "")
{
	for (new i; i < MAX_CRIMES; i++)
	{
		if ((strcmp(crime_data[i][cr_name], inputtext, true)) != 0)
		{
			continue;
		}
		
		format:g_string("\
			" #DEFAULT " Настройка названия\n\n\
			" #cWHITE "Введите название криминальной организации в поле для ввода.\n\n\
			" #cGRAY "Примечание:\n\
			" #cPROJECT "* " #cWHITE"Максимальная длина текста - " #cPROJECT "%d" #cWHITE" символ.%s%s",
			MAX_CRIME_NAME-1,
			!isnull(error) ? ("\n\n" #cRED) : (""), 
			error
		);
	
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ",
			g_string,
			"Далее", "Назад"
		);

		return 0;
	}
	
	return 1;
}

IsValidCrimeName(playerid, const dialogid, inputtext[], error[] = "")
{
	new len = strlen(inputtext);

	for (new i; i < len; i++)
	{
		switch (inputtext[i])
		{
			case 'А'..'Я', 'а'..'я':
			{
				format:g_string("\
					" #DEFAULT " Настройка названия\n\n\
					" #cWHITE "Введите название криминальной организации в поле для ввода.\n\n\
					" #cGRAY "Примечание:\n\
					" #cPROJECT "* " #cWHITE"Максимальная длина текста - " #cPROJECT "%d" #cWHITE" символ.%s%s",
					MAX_CRIME_NAME-1,
					!isnull(error) ? ("\n\n" #cRED) : (""), 
					error
				);
				
				ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ",
					g_string,
					"Далее", "Назад"
				);
				
				return 0;
			}
			
			default:
			{
				continue;
			}
		}
	}
	
	return 1;
}

IsValidLenghtCrimeName(playerid, const dialogid, inputtext[], error[] = "")
{
	new len = strlen(inputtext);

	if (!(0 < len < MAX_CRIME_NAME)) 
	{
		format:g_string("\
			" #DEFAULT " Настройка названия\n\n\
			" #cWHITE "Введите название криминальной организации в поле для ввода.\n\n\
			" #cGRAY "Примечание:\n\
			" #cPROJECT "* " #cWHITE"Максимальная длина текста - " #cPROJECT "%d" #cWHITE" символ.%s%s",
			MAX_CRIME_NAME-1,
			!isnull(error) ? ("\n\n" #cRED) : (""), 
			error 
		);
	
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ",
			g_string,
			"Далее", "Назад"
		);
		
		return 0;
	}
	
	return 1;
}

ShowPlayerDeathReason(reason)
{
	clean:<g_string>;

	switch(reason)
	{
		case 0:
		{
			strcat(g_string, "Fist");
		}
		
		case 1:
		{
			strcat(g_string, "Brass Knuckles");
		}
		
		case 2:
		{
			strcat(g_string, "Golf Club");
		}
		
		case 3:
		{
			strcat(g_string, "Nitestick");
		}
		
		case 4:
		{
			strcat(g_string, "Knife");
		}
		
		case 5:
		{
			strcat(g_string, "Bat");
		}
		
		case 6:
		{
			strcat(g_string, "Shovel");
		}
		
		case 7:
		{
			strcat(g_string, "Poolstick");
		}
		
		case 8:
		{
			strcat(g_string, "Katana");
		}
		
		case 9:
		{
			strcat(g_string, "Chainsaw");
		}
		
		case 10:
		{
			strcat(g_string, "Dildo");
		}
		
		case 11:
		{
			strcat(g_string, "Dildo 2");
		}
		
		case 12:
		{
			strcat(g_string, "Vibrator");
		}
		
		case 13:
		{
			strcat(g_string, "Vibrator 2");
		}
		
		case 14:
		{
			strcat(g_string, "Flower");
		}
		
		case 15:
		{
			strcat(g_string, "Cane");
		}
		
		case 16:
		{
			strcat(g_string, "Grenade");
		}
		
		case 17:
		{
			strcat(g_string, "Teargas");
		}
		
		case 18:
		{
			strcat(g_string, "Moltov");
		}
		
		case 22:
		{
			strcat(g_string, "Colt 45");
		}
		
		case 23:
		{
			strcat(g_string, "Silenced");
		}
		
		case 24:
		{
			strcat(g_string, "Deagle");
		}
		
		case 25:
		{
			strcat(g_string, "Shotgun");
		}
		
		case 26:
		{
			strcat(g_string, "Sawedoff");
		}
		
		case 27:
		{
			strcat(g_string, "Shotgspa");
		}
		
		case 28:
		{
			strcat(g_string, "Uzi");
		}
		
		case 29:
		{
			strcat(g_string, "Mp5");
		}
		
		case 30:
		{
			strcat(g_string, "AK47");
		}
		
		case 31:
		{
			strcat(g_string, "M4");
		}
		
		case 32:
		{
			strcat(g_string, "Tec9");
		}
		
		case 33:
		{
			strcat(g_string, "Rifle");
		}
		
		case 34:
		{
			strcat(g_string, "Sniper");
		}
		
		case 35:
		{
			strcat(g_string, "Rocketlauncher");
		}
		
		case 36:
		{
			strcat(g_string, "Heatseeker");
		}
		
		case 37:
		{
			strcat(g_string, "Flamethrower");
		}
		
		case 38:
		{
			strcat(g_string, "Minigun");
		}
		
		case 39:
		{
			strcat(g_string, "Satchel");
		}
		
		case 40:
		{
			strcat(g_string, "Bomb");
		}
		
		case 41:
		{
			strcat(g_string, "Spraycan");
		}
		
		case 42:
		{
			strcat(g_string, "Fireextinguisher");
		}
		
		case 49:
		{
			strcat(g_string, "Столкновение с транспортом");
		}
		
		case 50:
		{
			strcat(g_string, "Лопасти верт./Задавлен т.с.");
		}
		
		case 51:
		{
			strcat(g_string, "Взрыв");
		}
		
		case 53:
		{
			strcat(g_string, "Утопление");
		}
		
		case 54:
		{
			strcat(g_string, "Падение с высоты");
		}
		
		default:
		{
			strcat(g_string, "Не определена");
		}
	}
	
	return g_string;
}
