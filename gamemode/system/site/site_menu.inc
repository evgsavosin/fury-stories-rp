/*!
	@brief Динамичные диалоги для системы сайтов
	@author Found (evg.savosin)
	@date 16.12.2016, update 14.02.2018
*/

ShowSiteList(playerid, dialogid)
{
	clean:<g_big_string>;
	
	new count = 0,
		index;

	strcat(g_big_string, "" #cGRAY "Создать сайт\t\n" #cWHITE "");
	for (new i; i < MAX_PLAYER_SITES; i++)
	{
		if ((index = player_site[playerid][i]) == INVALID_PARAM)
		{
			continue;
		}
		
		format:g_big_string("%s %s%s\t%s\n",
			g_big_string,
			site_data[index][s_name],
			(site_data[index][s_rent_time] < gettime() + (60 * 60 * 24 * 3)) ? (" [" #cDARKRED "требует оплаты" #cWHITE "]") : (""),
			site_data[index][s_address]
		);
		
		g_dialog_select[playerid][count] = index;
		count++;
	}   
	
	return ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, " ", g_big_string, "Выбрать", "Закрыть");
}

ShowSiteInformation(playerid, dialogid, const index)
{
	clean:<g_big_string>;
	
	new day,
		month,
		year,
		hour,
		minute;
	
	gmtime(site_data[index][s_created_time], year, month, day, hour, minute, _);
	
	format:g_big_string("\
		" #DEFAULT " Информация о сайте\n\n\
		Адрес: " #cPROJECT "%s" #cWHITE "\n\
		Название: " #cPROJECT "%s" #cWHITE "\n\
		Слоган: " #cPROJECT "%s" #cWHITE "\n\
		Цвет дизайна: {%s}%s" #cWHITE "\n\
		Дата создания: " #cPROJECT "" #DATE_FORMAT "" #cWHITE ".\n",
		site_data[index][s_address],
		site_data[index][s_name],
		site_data[index][s_slogan],
		site_colors[site_data[index][s_color]][sc_color],
		site_colors[site_data[index][s_color]][sc_color_name],
		hour, minute, day, month, year
	);
	
	gmtime(site_data[index][s_rent_time], year, month, day, hour, minute);
	
	format:g_big_string("\
		%sХостинг арендован до: " #cPROJECT "" #DATE_FORMAT "" #cWHITE ".\n\
		Onionland Tor Hidden Service: %s" #cWHITE ".\n\
		",
		g_big_string,
		hour, minute, day, month, year,
		site_data[index][s_is_darknet] ? ("" #cPROJECT "Установлен") : ("" #cGRAY "Не установлен")
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Назад", "");
}

ShowSitePageContent(playerid, index, E_SITE_DATA: name_page, E_SITE_DATA: s_desc_page)
{
	clean:<g_big_string>;
	
	format:g_big_string(
		"" #DEFAULT " > " #cPROJECT "%s" #cWHITE "\n\
		Содержание:\n\n\
		%s",
		site_data[index][name_page],
		site_data[index][s_desc_page]
	);
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Закрыть", "");
}

ShowSiteFavorites(playerid)
{
	new server_tick = GetTickCount();
	
	if (GetPVarInt(playerid, "TimeMySQL:ShowFavSite") > server_tick)
	{
		return 0;
	}
	
	format:g_string("\
		SELECT sf_id, sf_address, sf_name \
		FROM " #__SFAVORITE " \
		WHERE sf_character_id = %i \
		ORDER BY sf_created_time ASC \
		LIMIT %i",
		GetCharacterId(playerid),
		MAX_SITE_FAVORITES
	);
	
	mysql_tquery(db, g_string, "OnSiteShowFavorites", "i", playerid);
	
	SetPVarInt(playerid, "TimeMySQL:ShowFavSite", server_tick + 1000);
	return 1;
}

function OnSiteShowFavorites(playerid)
{
	clean:<g_big_string>;
	
	new rows;

	cache_get_row_count(rows);
	
	SetPVarInt(playerid, "Site:CountFavorites", rows);
	
	strcat(g_big_string, "" #cGRAY "Добавить сайт\n" #cWHITE "");
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "sf_id", site_fav_select[playerid][i][sf_id]);
		cache_get_value_name(
			i, 
			"sf_address", 
			site_fav_select[playerid][i][sf_address], 
			MAX_SITE_ADDRESS 
		);
		
		cache_get_value_name(
			i, 
			"sf_name", 
			site_fav_select[playerid][i][sf_name], 
			MAX_SITE_NAME
		);
		
		format:g_big_string("%s %s\t%s",
			g_big_string,
			site_fav_select[playerid][i][sf_name],
			site_fav_select[playerid][i][sf_address]
		);
	}
	
	ShowPlayerDialog(playerid, D_SITE + 1, DIALOG_STYLE_LIST, " ", g_big_string, "Выбрать", "Закрыть");
	return 1;
}

ShowSiteFavoriteSelected(playerid, index)
{
	format:g_string("%s\n\
	" #cPROJECT "www.%s\n\
	" #cGRAY "Перейти\t" #cWHITE ">>\n\
	" #cGRAY "Удалить из закладок\t" #cWHITE "X",
		site_fav_select[playerid][index][sf_name],
		site_fav_select[playerid][index][sf_address]
	);
	
	ShowPlayerDialog(playerid, D_SITE + 2, DIALOG_STYLE_TABLIST, "" #DEFAULT " Закладки", g_string, "Выбрать", "Назад");
}

ShowSiteDialogMenuEdit(playerid)
{
	new str_address				[	MAX_SITE_ADDRESS	],
		str_template			[	32	],
		str_color				[	32	],
		str_name				[	MAX_SITE_NAME 	],
		str_slogan				[	32		],
		str_description			[	32		],
		str_action				[	32		],
		action = GetPVarInt(playerid, "Site:EditAction"),
		color = GetPVarInt(playerid, "Site:EditColor"),
		template = GetPVarInt(playerid, "Site:EditTemplate"),
		bool: is_completed = true;
		
	if (action == 0)
	{
		return;
	}
	
	/// Address
	clean:<g_string>;
	GetPVarString(playerid, "Site:EditDomain", g_string, sizeof g_string);
	if (isnull(g_string))
	{
		strcat(str_address, "" #cGRAY "Не указано");
		is_completed = false;
	}
	else
	{
		format:str_address("" #cPROJECT "%s", g_string);
	}
	
	if (template == 0)
	{
		strcat(str_template, "" #cGRAY "Не указано");
		is_completed = false;
	}
	else
	{
		format:str_template("" #cPROJECT "Дизайн #%i", template) ;
	}
	
	/// Color
	if (color == INVALID_PARAM)
	{
		strcat(str_color, "" #cGRAY "Не указано");
		is_completed = false;
	}
	else
	{
		format:str_color("{%s}%s", 
			site_colors[color][sc_color],
			site_colors[color][sc_color_name] 
		);
	}
	
	/// Name
	clean:<g_string>;
	GetPVarString(playerid, "Site:EditName", g_string, sizeof g_string);
	if (isnull(g_string))
	{
		strcat(str_name, "" #cGRAY "Не указано");
		is_completed = false;
	}
	else
	{
		format:str_name("" #cPROJECT "%s", g_string);
	}
	
	/// Slogan
	clean:<g_string>;
	GetPVarString(playerid, "Site:EditSlogan", g_string, sizeof g_string);
	if (isnull(g_string))
	{
		strcat(str_slogan, "" #cGRAY "Не указано");
	}
	else
	{
		format:str_slogan("" #cPROJECT "%s", g_string);
	}
	
	/// Description
	clean:<g_string>;
	GetPVarString(playerid, "Site:EditDescription", g_string, sizeof g_string);
	if (isnull(g_string))
	{
		strcat(str_description, "" #cGRAY "Не указано");
		is_completed = false;
	}
	else 
	{
		strcat(str_description, "" #cPROJECT "Указано");
	}
	
	if (is_completed)
	{
		if (action == SITE_ACTION_CREATE)
		{
			strcat(str_action, "" #cGRAY "Создать сайт");
		}
		else if (action == SITE_ACTION_EDIT)
		{
			strcat(str_action, "" #cGRAY "Отредактировать сайт");
		}
	}
	
	format:g_big_string(" \
	   " #cWHITE "Тип шаблона\t%s\n \
	   " #cWHITE "Цвет дизайна\t%s\n \
	   " #cWHITE "Название\t%s\n \
	   " #cWHITE "Слоган\t%s\n \
	   " #cWHITE "Описание\t%s\n \
	   " #cWHITE "Настройка страниц\n \
		%s",
		str_template,
		str_color,
		str_name,
		str_slogan,
		str_description,
		str_action
	);
	
	ShowPlayerDialog(playerid, D_SITE + 7, DIALOG_STYLE_TABLIST, str_address,
		g_big_string,
		"Выбрать", "Назад"
	);
}

ShowSiteDialogAddressEdit(playerid, bool: show_error = false)
{
	clean:<g_big_string>;
	clean:<g_string>;
	
	strcat(g_big_string, "" #DEFAULT " Домен\n\n\
	Домен - это адрес созданного сайта, который имеет собственное уникальное имя,\n\
	по которому пользователи смогут зайти на сам ресурс.\n\
	Перед созданием сайта, Вам необходимо выбрать свободное доменное имя.\n\n\
	" #cGRAY "Домен нужно вводить в формате: example.com\n\
	Доступные домены для регистрации:\n");
	
	for (new i; i < sizeof site_domains; i++)
	{
		if (i == sizeof site_domains - 1)
		{
			format:g_big_string("%s.%s;", g_big_string, site_domains[i]);
		}
		else
		{
			format:g_big_string("%s.%s, ", g_big_string, site_domains[i]);
		}
	}
	
	strcat(g_big_string, "\n\n" #cWHITE "Введите будущий домен сайта:");
	
	if (show_error)
	{
		strcat(g_big_string, "\n\n" #cRED "Домен содержит неверные символы или Вы выбрали неверное доменное имя.");
	}
	
	ShowPlayerDialog(playerid, D_SITE + 6, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
}

ShowSiteDialogTemplates(playerid)
{
	clean:<g_big_string>;
	
	for (new i; i < sizeof site_templates; i++)
	{
		format:g_big_string("%s %s\t" #cWHITE "%s\n",
			g_big_string,
			site_templates[i][st_name],
			_: site_templates[i][st_darknet] == _: GetPVarInt(playerid, "Site:EditDarknet") ? ("[" #cGREEN "доступно" #cWHITE "]") : ("[" #cRED "недоступно" #cWHITE "]")
		);
	}
	
	ShowPlayerDialog(playerid, D_SITE + 8, DIALOG_STYLE_TABLIST, " ", g_big_string, "Далее", "Назад");
}

ShowSiteDialogColors(playerid)
{
	clean:<g_big_string>;
	
	for (new i; i < sizeof site_colors; i++)
	{
		format:g_big_string("%s {%s}%s\n",
			g_big_string,
			site_colors[i][sc_color],
			site_colors[i][sc_color_name]
		);
	}
	
	ShowPlayerDialog(playerid, D_SITE + 9, DIALOG_STYLE_LIST, " ", g_big_string, "Далее", "Назад");
}

ShowSiteDialogDescription(playerid, bool: show_error = false)
{
	clean:<g_big_string>;
	clean:<g_string>;
	
	GetPVarString(playerid, "Site:EditDescription", g_string, sizeof g_string);
	
	format:g_big_string("" #DEFAULT " Описание\n\n\
		Описание сайта выводится на главную страницу.\n\
		Введите текст:\n\n\
		" #cGRAY "Текущее описание:" #cWHITE "\n\
		%s\n\%s\ 
		%sТекст должен содержать только латинские буквы и цифры.\n\
		Длина текста не должна быть меньше 10 символов и больше, чем 128 символов.", 
		g_string,
		isnull(g_string) ? ("") : ("\n"),
		show_error ? (cRED) : (cGRAY)
	);
	
	ShowPlayerDialog(playerid, D_SITE + 12, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
}

ShowSiteDialogPages(playerid)
{
	clean:<g_big_string>;
	
	new str_page_name		[	4 	][	64	],
		str_page_desc		[	4	][	64	];
	
	for (new i; i < 4; i++)
	{
		clean:<g_string>;
		format:g_small_string("Site:EditPageName[%i]", i);
		GetPVarString(playerid, g_small_string, g_string, sizeof g_string);
		if (isnull(g_string))
		{
			strcat(str_page_name[i], "" #cGRAY "Не указано");
		}
		else
		{
			format(str_page_name[i], MAX_SITE_PAGE_NAME, "" #cPROJECT "%s", g_string);
		}
		
		clean:<g_string>;
		format:g_small_string("Site:EditPageDesc[%i]", i);
		GetPVarString(playerid, g_small_string, g_string, sizeof g_string);
		if (isnull(g_string))
		{
			strcat(str_page_desc[i], "" #cGRAY "Не указано");
		}
		else
		{
			strcat(str_page_desc[i], "" #cPROJECT "Указано");
		}
	}
	
	format:g_big_string(" \
		" #cPROJECT "#\t" #cPROJECT "Название\t" #cPROJECT "Контент\n \
		Страница #1\t%s\t%s\n \
		Страница #2\t%s\t%s\n \
		Страница #3\t%s\t%s\n \
		Страница #4\t%s\t%s", 
		str_page_name[0], str_page_desc[0],
		str_page_name[1], str_page_desc[1],
		str_page_name[2], str_page_desc[2],
		str_page_name[3], str_page_desc[3]
	);
	
	ShowPlayerDialog(playerid, D_SITE + 14, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "Выбрать", "Назад");
}

ShowSiteDialogPageName(playerid, index, bool: is_error = false)
{
	clean:<g_string>;
	format:g_small_string("Site:EditPageName[%i]", index);
	GetPVarString(playerid, g_small_string, g_string, sizeof g_string);
	
	format:g_big_string("" #DEFAULT " Редактировать название\n\n\
		Название страницы отображается в меню сайта как пункт. Вы можете сделать данный пункт\n\
		в меню неактивным, для этого ничего не вводите и нажмите \"Далее\".\n\
		Введите текст:\n\n\
		" #cGRAY "Текущее название:\n\
		" #cWHITE "%s\n\n\
		%sТекст должен содержать только латинские буквы и цифры.\n\
		Длина текста не должна превышать больше 16 символов.",
		g_string,
		is_error ? (cRED) : (cGRAY)
	);
	
	ShowPlayerDialog(playerid, D_SITE + 16, DIALOG_STYLE_INPUT, " ",
		g_big_string,
		"Далее", "Назад"
	);
}

ShowSiteDialogPageDesc(playerid, index, bool: is_error = false)
{
	format:g_small_string("Site:EditPageDesc[%i]", index);
	GetPVarString(playerid, g_small_string, g_string, sizeof g_string);
	
	format:g_big_string("" #DEFAULT " Редактирование контента\n\n\
		Вы редактируете контент на странице.\n\ 
		" #HELP_TEXT_EDITOR "\n\
		Введите текст:\n\n\
		" #cGRAY "Текущий контент:" #cWHITE "%s\n\n\
		%sМаксимальное количество символов в строке не должно превышать 128,\n\ 
		а полный текст не должен быть больше %i символов.",
		g_string,
		is_error ? (cRED) : (cGRAY),
		MAX_SITE_PAGE_DESC
	);
	
	ShowPlayerDialog(playerid, D_SITE + 17, DIALOG_STYLE_INPUT, " ",
		g_big_string,
		"Ввод", "Очистить"
	);
}