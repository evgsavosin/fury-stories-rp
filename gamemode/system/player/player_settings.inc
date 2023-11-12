/*!
	@brief Настройки аккаунта и персонажа
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

// Load
Load:user_settings(playerid)
{
	cache_get_value_name_int(0, "set_inventory", user_data[playerid][u_settings][SET_INVENTORY]);
	cache_get_value_name_int(0, "set_visible_object", user_data[playerid][u_settings][SET_VISIBLE_OBJECT]);
	cache_get_value_name_int(0, "set_visible_pickup", user_data[playerid][u_settings][SET_VISIBLE_PICKUP]);
	cache_get_value_name_int(0, "set_b_message", user_data[playerid][u_settings][SET_B_MESSAGE]);
	cache_get_value_name_int(0, "set_pm_message", user_data[playerid][u_settings][SET_PM_MESSAGE]);
	cache_get_value_name_int(0, "set_admin_message", user_data[playerid][u_settings][SET_ADMIN_MESSAGE]);
	cache_get_value_name_int(0, "set_logo", user_data[playerid][u_settings][SET_LOGO]);
	cache_get_value_name_int(0, "set_visible_names", user_data[playerid][u_settings][SET_VISIBLE_NAMES]);
	cache_get_value_name(0, "set_google_auth", user_data[playerid][u_settings][SET_GOOGLE_AUTH], MAX_GOOGLE_AUTH);
	
	ApplyUserSettings(playerid);
}

Load:character_settings(playerid)
{
	cache_get_value_name_int(0, "set_spawn", character_data[playerid][c_settings][SET_SPAWN]);
	cache_get_value_name_int(0, "set_spawn_street", character_data[playerid][c_settings][SET_SPAWN_STREET]);
	cache_get_value_name_int(0, "set_walk", character_data[playerid][c_settings][SET_WALK]);
	cache_get_value_name_int(0, "set_talk", character_data[playerid][c_settings][SET_TALK]);
	cache_get_value_name_int(0, "set_greetings", character_data[playerid][c_settings][SET_GREETINGS]);
	cache_get_value_name_int(0, "set_style", character_data[playerid][c_settings][SET_STYLE]);
	
	SetPlayerFightingStyle(playerid, 
		GetCharacterFightStyle(playerid)
	);
}

// Настройка аккаунта
ShowUserSettings(playerid)
{
	clean:<g_string>;
	
	new visible_object = user_data[playerid][u_settings][SET_VISIBLE_OBJECT],
		str_visible_obj		[8];
		
	if (visible_object == MAX_VISIBLE_OBJECTS)
	{
		strcat(str_visible_obj, "Высокая");
	}
	else if (visible_object == (MAX_VISIBLE_OBJECTS / 2))
	{
		strcat(str_visible_obj, "Низкая");
	}
	else if (visible_object < MAX_VISIBLE_OBJECTS)
	{
		strcat(str_visible_obj, "Средняя");
	}
	
	format:g_big_string("\
		" #cPROJECT "Настройка\t" #cPROJECT "Значение\n \
		Инвентарь\t" #cGRAY "%s" #cWHITE "\n \
		Прорисовка объектов\t" #cGRAY "%s" #cWHITE "\n \
		Отображение пикапов\t%s" #cWHITE "\n \
		Отображение действий администраторов\t" #cGRAY "%s" #cWHITE "\n \
		Отображение личных сообщений " #cGRAY "(/pm, /pmon, /pmoff)\t%s" #cWHITE "\n \
		Отображение OOC чата " #cGRAY "(/b, /bon, /boff)\t%s" #cWHITE "\n \
		Отображение логотипа\t%s" #cWHITE "\n \
		Отображение ник-неймов" #cGRAY "(/nameon, /nameoff)\t%s" #cWHITE "\n \
		Приоритет вывода информации " #cGRAY "(/stats и тд.)\t" #cGRAY "%s" #cWHITE "\n \
		Безопасность\t%s",
		(GetUserSettings(playerid, SET_INVENTORY) == 0) ? ("Текстдрав") : ("Диалог"),
		str_visible_obj,
		(GetUserSettings(playerid, SET_VISIBLE_PICKUP) == 1) ? ("" #cPROJECT "Включено") : ("" #cGRAY "Отключено"),
		(GetUserSettings(playerid, SET_ADMIN_MESSAGE) == 1) ? ("Глобально") : ("Локально"),
		(GetUserSettings(playerid, SET_PM_MESSAGE) == 1) ? ("" #cPROJECT "Включено") : ("" #cGRAY "Выключено"),
		(GetUserSettings(playerid, SET_B_MESSAGE) == 1) ? ("" #cPROJECT "Включено") : ("" #cGRAY "Выключено"),
		(GetUserSettings(playerid, SET_LOGO) == 1) ? ("" #cPROJECT "Включено") : ("" #cGRAY "Выключено"),
		(GetUserSettings(playerid, SET_VISIBLE_NAMES) == 1) ? ("" #cPROJECT "Включено") : ("" #cGRAY "Выключено"),
		(GetUserSettings(playerid, SET_DESIGN) == 1) ? ("Диалог") : ("Чат"),
		isnull(user_data[playerid][u_settings][SET_GOOGLE_AUTH]) ? (#cRED "Низкая") : (#cPROJECT "Высокая")
	);
	
	ShowPlayerDialog(playerid, D_SETTINGS, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "Изменить", "Назад");
	return 1;
}

ApplyUserSettings(playerid)
{		
	/// Отображение объектов
	Streamer_SetVisibleItems(
		STREAMER_TYPE_OBJECT, 
		user_data[playerid][u_settings][SET_VISIBLE_OBJECT],
		playerid
	);
	
	Streamer_Update(playerid, STREAMER_TYPE_OBJECT);
	
	/// Отображение пикапов
	Streamer_SetVisibleItems(
		STREAMER_TYPE_PICKUP, 
		(user_data[playerid][u_settings][SET_VISIBLE_PICKUP]) ? 4096 : 0,
		playerid
	);
	
	Streamer_Update(playerid, STREAMER_TYPE_PICKUP);
	
	/// Логотип
	ShowPlayerLogo(playerid, bool: GetUserSettings(playerid, SET_LOGO));
	
	/// Отображение ников
	ShowPlayerNames(playerid, bool: GetUserSettings(playerid, SET_VISIBLE_NAMES));
}

ShowUserSecurity(playerid)
{
	new str_google_auth	[32];
	
	if (!isnull(user_data[playerid][u_settings][SET_GOOGLE_AUTH]))
	{
		strcat(str_google_auth, #cPROJECT "Подключена");
	}
	else 
	{
		strcat(str_google_auth, #cGRAY "Не подключена");
	}
	
	format:g_string("" #cPROJECT "Название\t" #cPROJECT "Статус\n \
		Двухфакторная аутентификация\t%s",
		str_google_auth
	);
		
	ShowPlayerDialog(playerid, D_SETTINGS + 3, DIALOG_STYLE_TABLIST_HEADERS, " ", g_string, "Далее", "Назад");
	return 1;
}

ShowUserConnectGoogleAuth(playerid, error[] = "")
{
	new google_auth	[MAX_GOOGLE_AUTH];
			
	GenerateBase32String(google_auth, sizeof google_auth);
	SetPVarString(playerid, "Player:GoogleAuth", google_auth);
					
	format:g_string(#DEFAULT " Двухфакторная аутентификация\n\n\
		Для использования аутентификации, необходимо установить приложение,\n\
		которое генерирует коды. Например, Authy, Google Authenticator или\n\
		браузерное расширение Authenticator.\n\n\
		После того, как Вы это сделаете, необходимо будет ввести секретный код в приложение,\n\
		а уже сгенерированный код из приложения подставить в поле ниже.\n\
		Секретный код: " #cPROJECT "%s" #cWHITE "\n\n\
		Введите сгенерированный код из приложения:%s%s",
		google_auth,
		isnull(error) ? ("") : ("\n\n" #cRED),
		error
	);
	
	ShowPlayerDialog(playerid, D_SETTINGS + 9, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
}

ShowUserDisableGoogleAuth(playerid, error[] = "")
{
	format:g_string(#DEFAULT " Двухфакторная аутентификация\n\n\
		Для отключения защиты, необходимо ввести секретный код из приложения.\n\
		Введите сгенерированный код из приложения:%s%s",
		isnull(error) ? ("") : ("\n\n" #cRED),
		error
	);
		
	ShowPlayerDialog(playerid, D_SETTINGS + 10, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
}

// Настройка персонажа
ShowAccountSettings(playerid)
{
	new str_walk				[		32		],
		str_talk				[		32		],
		str_spawn				[		32 		],
		str_greetings			[		32 		],
		str_fighting_style		[		32		];
	
	/// Тип походки
	if (GetCharacterSettings(playerid, SET_WALK) == 0)
	{
		strcat(str_walk, "Стандартный");
	}
	else
	{
		format:str_walk("Тип %i", GetCharacterSettings(playerid, SET_WALK));
	}
	
	/// Тип разговора
	if (GetCharacterSettings(playerid, SET_TALK) == 0)
	{
		strcat(str_talk, "Отсутствует");
	}
	else
	{
		format:str_talk("Тип %i", GetCharacterSettings(playerid, SET_TALK));
	}
	
	/// Тип приветствия
	if (GetCharacterSettings(playerid, SET_GREETINGS) == 0)
	{
		strcat(str_greetings, "Стандартный");
	}
	else
	{
		format:str_greetings("Тип %i", GetCharacterSettings(playerid, SET_GREETINGS));
	}
	
	/// Стиль боя
	if (GetCharacterSettings(playerid, SET_STYLE) == 0)
	{
		strcat(str_fighting_style, "Стандартный");
	}	
	else
	{
		format:str_fighting_style("Тип %i", GetCharacterSettings(playerid, SET_STYLE));
	}
	
	if (GetCharacterSettings(playerid, SET_SPAWN) == SPAWN_STREET)
	{
		new spawn_street = GetCharacterSettings(playerid, SET_SPAWN_STREET);
		strcat(str_spawn, character_spawn_street_info[spawn_street][spawn_street_name]);
	}
	else 
	{
		strcat(str_spawn, character_spawn_info[GetCharacterSettings(playerid, SET_SPAWN)]);
	}
	
	format:g_string("\
		" #cPROJECT "Настройка\t" #cPROJECT "Значение\n \
		Место появления\t" #cGRAY "%s" #cWHITE "\n \
		Тип походки\t" #cGRAY "%s" #cWHITE "\n \
		Тип жестикуляции\t" #cGRAY "%s" #cWHITE "\n \
		Тип приветствия\t" #cGRAY "%s" #cWHITE "\n \
		Стиль боя\t" #cGRAY "%s" #cWHITE "\n",
		str_spawn,
		str_walk,
		str_talk,
		str_greetings,
		str_fighting_style
	);
	
	ShowPlayerDialog(playerid, D_SETTINGS + 2, DIALOG_STYLE_TABLIST_HEADERS, " ", g_string, "Изменить", "Назад");
	return 1;
}

ShowPlayerSettingsSpawn(playerid)
{	
	clean:<g_string>;
	
	for (new i; i < sizeof character_spawn_info; i++)
	{
		format:g_string("%s %s\n",
			g_string,
			character_spawn_info[i]
		);
	}
	
	ShowPlayerDialog(playerid, D_SETTINGS + 4, DIALOG_STYLE_LIST, " ", g_string, "Далее", "Назад");
}

ShowPlayerSettingsSpawnStreet(playerid)
{	
	clean:<g_string>;
	
	for (new i; i < sizeof character_spawn_street_info; i++)
	{
		format:g_string("%s %s\n",
			g_string,
			character_spawn_street_info[i][spawn_street_name]
		);
	}
	
	ShowPlayerDialog(playerid, D_SETTINGS + 5, DIALOG_STYLE_LIST, " ", g_string, "Далее", "Назад");
}

ShowPlayerSettingsWalk(playerid)
{
	clean:<g_string>;
	
	for (new i; i < sizeof character_walk_anim; i++)
	{	
		if (i == 0)
		{
			strcat(g_string, " Стандартная\n");
		}
		else
		{
			format:g_string("%s Тип %i\n",
				g_string,
				i
			);
		}
	}
	
	ShowPlayerDialog(playerid, D_SETTINGS + 6, DIALOG_STYLE_LIST, " ", g_string, "Далее", "Назад");
}

ShowPlayerSettingsTalk(playerid)
{
	clean:<g_string>;
	
	for (new i; i < sizeof character_talk_anim; i++)
	{	
		if (i == 0)
		{
			strcat(g_string, " Отсутствует\n");
		}
		else
		{
			format:g_string("%s Тип %i\n",
				g_string,
				i
			);
		}
	}
	
	ShowPlayerDialog(playerid, D_SETTINGS + 7, DIALOG_STYLE_LIST, " ", g_string, "Далее", "Назад");
}

ShowPlayerSettingsGreetings(playerid)
{
	clean:<g_string>;

	for (new i; i < sizeof character_greetings_anim; i++)
	{	
		if (i == 0)
		{
			strcat(g_string, " Стандартная\n");
		}
		else
		{
			format:g_string("%s Тип %i\n",
				g_string,
				i
			);
		}
	}
	
	ShowPlayerDialog(playerid, D_SETTINGS + 8, DIALOG_STYLE_LIST, " ", g_string, "Далее", "Назад");
}

ShowPlayerSettingsFightingStyle(playerid)
{
	clean:<g_string>;

	for (new i; i < sizeof character_fighting_style; i++)
	{	
		if (i == 0)
		{
			strcat(g_string, " Стандартная\n");
		}
		else
		{
			format:g_string("%s Стиль %i\n",
				g_string,
				i
			);
		}
	}
	
	ShowPlayerDialog(playerid, D_SETTINGS + 11, DIALOG_STYLE_LIST, " ", g_string, "Далее", "Назад");
}

ShowPlayerNames(playerid, bool: states)
{
	foreach (new i : Player)
	{
		ShowPlayerNameTagForPlayer(playerid, i, states);
	}
}