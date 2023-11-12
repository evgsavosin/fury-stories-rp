/*!
	@brief Меню для системы администрирования
	@author Found (evg.savosin)
	@date 16.12.2016, update 08.03.2018
	
*/

ShowAdminEditHouse(playerid, dialogid = D_ADMIN + 8)
{
	new index = GetPVarInt(playerid, "Admin:HouseSelect");
	format:g_small_string("Редактирование дома #%d", index);
	
	format:g_string(" \
		Информация\t\n \
		Установить вход на этом месте\t\n \
		Установить интерьер\t%s[%i]\n \
		Установить цену\t" #cGREEN "$%i\n \
		Установить аренду/ком. услуги\t\n \
		Обнулить задолжности\t\n \
	    Продать",
		GetHouseSettings(index, hset_name),
		house_data[index][h_int_type],
		GetHousePrice(index)
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, g_small_string, 
		g_string,
		"Далее", "Закрыть"
	);
}

ShowAdminEditHouseTime(playerid, dialogid, bool: success = false, bool: error = false)
{
	new index = GetPVarInt(playerid, "Admin:HouseSelect"),
		day,
		month,
		year,
		hour,
		minute,
		second;
	
	gmtime(house_data[index][h_time], year, month, day, hour, minute, second);
	
	format:g_string("" #DEFAULT " Установить аренду/ком. услуги\n\n\
	Продлены до: " #cPROJECT "" #DATE_FORMAT_S "" #cWHITE "\n\
	Введите количество дней на которое Вы хотите изменить аренду:\n\n\
	" #cGRAY "К примеру, если прибавить дни, то пишите просто число.\n\
	Если отнять, то необходимо писать с минусом.\n\
	%s\n\
	%s",
		hour,
		minute,
		second,
		day,
		month,
		year,
		success ? ("" #cGREEN "Вы успешно изменили дату аренды/ком. услуг. Для выхода используйте \"Назад\".") : (""),
		error ? ("" #cRED "Вы ввели неверное количество дней.") : ("")
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_string, "Применить", "Назад");
}

ShowAdminEditPremise(playerid, dialogid = D_ADMIN + 17)
{
	new index = GetPVarInt(playerid, "Admin:PremiseSelect");
	format:g_small_string("Редактирование помещения #%d", index);
	
	format:g_string(" \
		Информация\t\n \
		Установить вход на этом месте\t\n \
		Установить интерьер\t%s[%i]\n \
		Установить цену\t" #cGREEN "$%i\n \
		Установить аренду/ком. услуги\t\n \
		Обнулить задолжности\t\n \
	    Продать",
		GetPremiseSettings(index, pset_name),
		premise_data[index][pr_int_type],
		GetPremisePrice(index)
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, g_small_string, 
		g_string,
		"Далее", "Закрыть"
	);
}

ShowAdminEditPremiseTime(playerid, dialogid, bool: success = false, bool: error = false)
{
	new index = GetPVarInt(playerid, "Admin:PremiseSelect"),
		day,
		month,
		year,
		hour,
		minute,
		second;
	
	gmtime(premise_data[index][pr_time], year, month, day, hour, minute, second);
	
	format:g_string("" #DEFAULT " Установить аренду/ком. услуги\n\n\
	Продлены до: " #cPROJECT "" #DATE_FORMAT_S "" #cWHITE "\n\
	Введите количество дней на которое Вы хотите изменить аренду:\n\n\
	" #cGRAY "К примеру, если прибавить дни, то пишите просто число.\n\
	Если отнять, то необходимо писать с минусом.\n\
	%s\n\
	%s",
		hour,
		minute,
		second,
		day,
		month,
		year,
		success ? ("" #cGREEN "Вы успешно изменили дату аренды/ком. услуг. Для выхода используйте \"Назад\".") : (""),
		error ? ("" #cRED "Вы ввели неверное количество дней.") : ("")
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_string, "Применить", "Назад");
}

ShowAdminHouseInteriors(playerid, dialogid)
{
	clean:<g_big_string>;
	
	for (new i = 1; i < sizeof house_settings; i++)
	{
		format:g_big_string("%s %s [%i]\n",
			g_big_string,
			house_settings[i][hset_name],
			i
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", g_big_string, "Выбрать", "Закрыть");
}

ShowAdminHostelInteriors(playerid, dialogid)
{
	clean:<g_big_string>;
	
	for (new i = 1, type; i < sizeof hostel_settings; i++)
	{
		type = hostel_settings[i][hos_set_type];
		format:g_big_string("%s %s [%i]\n",
			g_big_string,
			type == TYPE_HOSTEL_LOW ? ("Низкий класс") : (
				type == TYPE_HOSTEL_MEDIUM ? ("Средний класс") : ("Высокий класс")
			),
			i
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", g_big_string, "Выбрать", "Закрыть");
}

ShowAdminPremiseInteriors(playerid, dialogid)
{
	clean:<g_big_string>;
	
	for (new i = 1; i < sizeof premise_settings; i++)
	{
		format:g_big_string("%s %s [%i]\n",
			g_big_string,
			premise_settings[i][pset_name],
			i
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", g_big_string, "Выбрать", "Закрыть");
}

/// Manage fraction
ShowAdminFractionList(playerid, dialogid = D_ADMIN + 23, bool: create_item = true)
{
	format:g_big_string(#cPROJECT "Название\t" #cPROJECT "Лидер\n");
	
	if (create_item)
	{
		strcat(g_big_string, #cGRAY "Создать фракцию" #cWHITE "\n");
	}
	
	for (new i; i < sizeof fraction_data; i++)
	{
		if (fraction_data[i][fr_id] == 0)
		{
			continue;
		}
		
		format:g_big_string("%s %s (#%d)\t%s\n", 
			g_big_string,
			fraction_data[i][fr_name],
			fraction_data[i][fr_id],
			fraction_data[i][fr_leader_name]
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ", 
		g_big_string,
		"Далее", "Закрыть"
	);
}

// Создание фракции
ShowAdminFractionCreate(playerid, const dialogid, error[] = "")
{
	if (dialogid == D_ADMIN + 24)
	{
		format:g_string(#DEFAULT " Создание фракции\n\n\
			Введите название будущей фракции:%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, 
			" ", 
			g_string,
			"Далее", "Назад"
		);
	}
	else if (dialogid == D_ADMIN + 25)
	{
		format:g_string(#DEFAULT " Создание фракции\n\n\
			Введите сокращенное название фракции (аббревиатуру):%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, 
			" ", 
			g_string,
			"Далее", "Назад"
		);
	}
	else if (dialogid == D_ADMIN + 26)
	{
		format:g_string(#DEFAULT " Создание фракции\n\n\
			Укажите цвет фракции в формате " #cGRAY "0xFF" #cWHITE "FFFFFF:%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, 
			" ", 
			g_string,
			"Далее", "Назад"
		);
	}
	else if (dialogid == D_ADMIN + 27)
	{
		new name 		[32],
			alt_name	[32],
			color		[16];
		
		GetPVarString(playerid, "Admin:FractionName", name, sizeof name);
		GetPVarString(playerid, "Admin:FractionShortName", alt_name, sizeof alt_name);
		GetPVarString(playerid, "Admin:FractionColor", color, sizeof color);
		
		format:g_string(#DEFAULT " Создание фракции\n\n\
			Название: " #cPROJECT "%s" #cWHITE "\n\
			Сокращенное название: " #cPROJECT "%s" #cWHITE "\n\
			Цвет: " #cPROJECT "%s" #cWHITE "\n\n\
			Вы действительно желаете создать данную фракцию?",
			name,
			alt_name,
			color
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, 
			" ", 
			g_string,
			"Далее", "Назад"
		);
	}
}

// Редактирование фракции
ShowAdminFractionEdit(playerid, const dialogid, index, error[] = "")
{
	if (dialogid == D_ADMIN + 28)
	{
		new str_budget			[MAX_FRACTION_BUDGET],
			str_leader_name		[MAX_PLAYER_NAME];
			
		if (isnull(fraction_data[index][fr_leader_name]))
		{
			strcat(str_leader_name, #cGRAY "Отсутствует", MAX_PLAYER_NAME);
		}
		else 
		{
			strcat(str_leader_name, fraction_data[index][fr_leader_name], MAX_PLAYER_NAME);
		}
		
		GetFractionBudgetFormat(fraction_data[index][fr_budget], str_budget);
		
		format:g_big_string(" \
			" #cPROJECT "Свойство\t" #cPROJECT "Значение" #cWHITE "\n \
			Название фракции\t" #cPROJECT "%s" #cWHITE "\n \
			Сокращенное название фракции\t" #cPROJECT "%s" #cWHITE "\n \
			Цвет\t%06x" #cWHITE "\n \
			Доступные объекты\t" #cGRAY "/object" #cWHITE "\n \
			Доступные прикреплённые объекты\t" #cGRAY "/attach" #cWHITE "\n \
			Тип финансирования бюджета\t" #cPROJECT "%s" #cWHITE "\n \
			Бюджет\t" #cPROJECT "%s" #cWHITE "\n \
			Доступные предметы на складе\n \
			Лидер\t" #cPROJECT "%s" #cWHITE "\n \
			" #cRED "Удалить фракцию",
			fraction_data[index][fr_name],
			fraction_data[index][fr_alt_name],
			fraction_data[index][fr_color],
			fraction_data[index][fr_type_budget] == FRAC_BUDGET_GOV ? ("Государственный") : ("Коммерческий"),
			str_budget,
			str_leader_name
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "Далее", "Назад");
	}
	else if (dialogid == D_ADMIN + 29)
	{
		format:g_big_string("\
			" #DEFAULT " Название фракции\n\n\
			Текущее название: " #cPROJECT "%s" #cWHITE "\n\
			Введите новое название:%s%s",
			fraction_data[index][fr_name],
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
	}
	else if (dialogid == D_ADMIN + 30)
	{
		format:g_big_string("\
			" #DEFAULT " Сокращенное название фракции\n\n\
			Текущее название: " #cPROJECT "%s" #cWHITE "\n\
			Введите новое название:%s%s",
			fraction_data[index][fr_alt_name],
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
	}
	else if (dialogid == D_ADMIN + 31)
	{
		format:g_big_string("\
			" #DEFAULT " Цвет фракции\n\n\
			Текущий цвет: " #cPROJECT "%06x" #cWHITE "\n\
			Введите новый цвет в формате " #cGRAY "FFFFFF" #cWHITE ":%s%s",
			fraction_data[index][fr_color],
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
	}
	else if (dialogid == D_ADMIN + 32)
	{
		ShowFractionObjectList(playerid, dialogid, index);
	}
	else if (dialogid == D_ADMIN + 38)
	{
		ShowFractionAttachList(playerid, dialogid, index);
	}
	else if (dialogid == D_ADMIN + 44)
	{
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", #cGRAY "\
			Выберите тип финансирования:\n \
			Государственный\t" #cGRAY "Правительство регулирует бюджет\n \
			Коммерческий\t" #cGRAY "Бюджет регулируется администрацией", 
			"Далее", "Назад"
		);
	}
	else if (dialogid == D_ADMIN + 45)
	{
		new str_budget	[16];
		
		// Бюджет
		GetFractionBudgetFormat(fraction_data[index][fr_budget], str_budget);
		
		format:g_big_string("\
			" #DEFAULT " Бюджет\n\n\
			Текущий бюджет фракции: " #cGREEN "%s" #cWHITE "\n\
			Укажите новый бюджет в формате " #cGRAY "0,000 (до запятой - млрд., после - млн.)" #cWHITE ":\n\n\
			" #cGRAY "Бюджет не должен быть выше $99.999 млрд. или ниже $0.000 млрд.%s%s",
			str_budget,
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
	}
	else if (dialogid == D_ADMIN + 46)
	{
		ShowFractionItemList(playerid, dialogid, index);
	}
	else if (dialogid == D_ADMIN + 49)
	{
		format:g_big_string("\
			" #ERROR " Удаление фракции\n\n\
			Вы действительно желаете удалить " #cPROJECT "%s" #cWHITE "?",
			fraction_data[index][fr_name]
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Далее", "Назад");
	}
	else if (dialogid == D_ADMIN + 50)
	{
		new str_leader_name 	[MAX_PLAYER_NAME];
		
		if (isnull(fraction_data[index][fr_leader_name]))
		{
			strcat(str_leader_name, #cGRAY "Отсутствует");
		}
		else
		{
			strcat(str_leader_name, fraction_data[index][fr_leader_name]);
		}
			
		format:g_string("\
			" #DEFAULT " Лидер\n\n\
			Текущий лидер: " #cPROJECT "%s" #cWHITE "\n\
			" #cWHITE "Введите имя и фамилию будущего лидера фракции:\n\n\
			" #cGRAY "Максимальная длина текста - " #cPROJECT "%d" #cWHITE" символов.\n\
			Формат вводимого текста: " #cPROJECT "Имя_Фамилия" #cWHITE".\n\
			Для того, чтобы просто снять лидера, отправьте пустую строку.%s%s",
			str_leader_name,
			MAX_PLAYER_NAME - 4,
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);

		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ",
			g_string,
			"Далее", "Назад"
		);
	}
}

// Редактирование объекта
ShowAdminFractionObjectEdit(playerid, const dialogid, index = INVALID_PARAM, error[] = "")
{
	if (dialogid == D_ADMIN + 33)
	{
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", " \
			Изменить название\n \
			Изменить ID объекта\n \
			" #cRED "Удалить объект",
			"Выбрать", "Назад"
		);
	}
	else if (dialogid == D_ADMIN + 34)
	{
		format:g_big_string("\
			" #DEFAULT " Название объекта\n\n\
			Текущее название: " #cPROJECT "%s" #cWHITE "\n\
			Введите новое название:%s%s",
			fraction_item_select[playerid][index][fr_name],
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
	}
	else if (dialogid == D_ADMIN + 35)
	{
		format:g_big_string("\
			" #DEFAULT " ID объекта\n\n\
			Текущий ID объекта: " #cPROJECT "%d" #cWHITE "\n\
			Введите новый ID объекта:%s%s",
			fraction_item_select[playerid][index][fr_object_id],
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
	}
	else if (dialogid == D_ADMIN + 36)
	{
		format:g_big_string("\
			" #DEFAULT " Добавить объект\n\n\
			Введите ID объекта:%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
	}
	else if (dialogid == D_ADMIN + 37)
	{
		format:g_big_string("\
			" #DEFAULT " Добавить объект\n\n\
			Введите имя объекта:%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
	}
}

// Редактирование аттача
ShowAdminFractionAttachEdit(playerid, const dialogid, index = INVALID_PARAM, error[] = "")
{
	if (dialogid == D_ADMIN + 39)
	{
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", " \
			Изменить название\n \
			Изменить ID аттача\n \
			" #cRED "Удалить объект",
			"Выбрать", "Назад"
		);
	}
	else if (dialogid == D_ADMIN + 40)
	{
		format:g_big_string("\
			" #DEFAULT " Название аттача\n\n\
			Текущее название: " #cPROJECT "%s" #cWHITE "\n\
			Введите новое название:%s%s",
			fraction_item_select[playerid][index][fr_name],
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
	}
	else if (dialogid == D_ADMIN + 41)
	{
		format:g_big_string("\
			" #DEFAULT " ID аттача\n\n\
			Текущий ID аттача: " #cPROJECT "%d" #cWHITE "\n\
			Введите новый ID аттача:%s%s",
			fraction_item_select[playerid][index][fr_object_id],
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
	}
	else if (dialogid == D_ADMIN + 42)
	{
		format:g_big_string("\
			" #DEFAULT " Добавить аттач\n\n\
			Введите ID аттача:%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
	}
	else if (dialogid == D_ADMIN + 43)
	{
		printf("%d dialogid D_ADMIN + 43 call", dialogid);
		format:g_big_string("\
			" #DEFAULT " Добавить аттач\n\n\
			Введите имя аттача:%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
	}
}

ShowAdminCrimeEditName(playerid) // CMD:crmanage -> Редактирование -> Изменить название
{
	format:g_string("\
		" #DEFAULT " Настройка названия.\n\n\
		" #cWHITE "Введите название криминальной организации в поле для ввода.\n\n\
		" #cGRAY " Примечание:\n\
		" #cPROJECT "* " #cWHITE "Максимальная длина текста - " #cPROJECT "%d" #cWHITE " символ.",
		MAX_CRIME_NAME-1
	);
	
	ShowPlayerDialog(playerid, D_ADMIN_CRIME_EDIT_NAME, DIALOG_STYLE_INPUT, " ",
		g_string,
		"Далее", "Назад"
	);
	
	return 1;
}

ShowAdminCrimeEditStatus(playerid) // CMD:crmanage -> Редактирование -> Изменить статус
{
	clean:<g_string>;

	strcat(g_string, #cPROJECT " Статус фракции" #cWHITE "\n \
		Одобренный\n \
		Официальный"
	);

	ShowPlayerDialog(playerid, D_ADMIN_CRIME_EDIT_STATUS, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_string,
		"Далее", "Назад"
	);
	
	return 1;
}

ShowAdminCrimeType(playerid, const dialogid) // CMD:crmanage <-> Тип фракции
{
	clean:<g_string>;
	
	strcat(g_string, #cGRAY " Выберите тип фракции" #cWHITE "\n");
	
	for (new i; i < MAX_CRIME_TYPE; i++)
	{
		if (crtype_data[i][cr_id] == 0)
		{
			continue;
		}
		
		format:g_string("%s%s \n",
			g_string,
			crtype_data[i][cr_name]
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ",
		g_string,
		"Далее", "Назад"
	);
}

ShowAdminCrimeEditLeader(playerid) // CMD:crmanage -> Редактирование -> Назначить лидера
{
	format:g_string("\
		" #DEFAULT " Настройка лидера\n\n\
		" #cWHITE "Введите имя и фамилию лидера криминальной организации в поле для ввода.\n\n\
		" #cGRAY "Примечание:\n\
		" #cPROJECT "* " #cWHITE"Максимальная длина текста - " #cPROJECT "%d" #cWHITE" символов.\n\
		" #cPROJECT "* " #cWHITE"Формат вводимого текста: " #cPROJECT "Имя_Фамилия" #cWHITE".",
		MAX_PLAYER_NAME-4
	);

	ShowPlayerDialog(playerid, D_ADMIN_CRIME_EDIT_LEADER, DIALOG_STYLE_INPUT, " ",
		g_string,
		"Далее", "Назад"
	);
}

ShowAdminCrimeDeleteLeader(playerid, index) // CMD:crmanage -> Редактирование -> Снять лидера
{
	format:g_small_string("\
		" #ERROR " Вы действительно хотите удалить лидера фракции " #cPROJECT "%s" #cWHITE " - " #cPROJECT "%s" #cWHITE "?",
		crime_data[index][cr_name],
		crime_data[index][cr_leader_name]
	);
	
	ShowPlayerDialog(playerid, D_ADMIN_CRIME_DELETE_LEADER, DIALOG_STYLE_MSGBOX, " ",
		g_small_string,
		"Далее", "Отмена"
	);
}

ShowAdminCrimeEditConfirm(playerid, index) // CMD:crmanage -> Редактирование -> Удалить фракцию
{
	format:g_string("\
		" #ERROR " Вы действительно хотите удалить фракцию " #cPROJECT "%s" #cWHITE "?",
		crime_data[index][cr_name]
	);
	
	ShowPlayerDialog(playerid, D_ADMIN_CRIME_CONFIRM, DIALOG_STYLE_MSGBOX, " ",
		g_string,
		"Далее", "Отмена"
	);
}

ShowAdminCrimeList(playerid) // CMD:crmanage
{
	clean:<g_big_string>;
	
	strcat(g_big_string, #cPROJECT "Название\t" #cPROJECT "Официальная\t" #cPROJECT "Лидер\n\
	" #cGRAY "Создать фракцию" #cGRAY "\n");
	
	for (new i; i < sizeof crime_data; i++)
	{
		if (crime_data[i][cr_id] == 0)
		{
			continue;
		}
		
		format:g_big_string("%s %s (#%d)\t%s\t" #cPROJECT "%s" #cWHITE "\n",
			g_big_string,
			crime_data[i][cr_name],
			crime_data[i][cr_id],
			crime_data[i][cr_official] ? ("Да") : ("Нет"),
			crime_data[i][cr_leader_name]
		);
	}
	
	ShowPlayerDialog(playerid, D_ADMIN_CRIME, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"Далее", "Закрыть"
	);
}

ShowAdminCrimeCreate(playerid) // CMD:crmanage -> Создать фракцию
{	
	strglobalclear();
	
	GetPVarString(playerid, "Admin:CrimeCreateName", g_small_string, sizeof g_small_string);
	GetPVarString(playerid, "Admin:CrimeCreateType", g_string, sizeof g_string);
	
	format:g_big_string("\
		" #cPROJECT "Свойство\t" #cPROJECT "Значение" #cWHITE "\n \
		Название\t" #cPROJECT "%s" #cWHITE "\n \
		Тип\t" #cPROJECT "%s" #cWHITE "\n \
		" #cGRAY "Создать",
		g_small_string,
		g_string
	);
	
	ShowPlayerDialog(playerid, D_ADMIN_CRIME_CREATE, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"Далее", "Назад"
	);
}

ShowAdminCrimeCreateName(playerid) // CMD:crmanage -> Создать фракцию -> Название
{
	format:g_big_string("\
		" #DEFAULT " Настройка названия.\n\n\
		" #cWHITE "Введите название криминальной организации в поле для ввода.\n\n\
		" #cGRAY " Примечание:\n\
		" #cPROJECT "* " #cWHITE "Максимальная длина текста - " #cPROJECT "%d" #cWHITE " символ.",
		MAX_CRIME_NAME-1
	);

	ShowPlayerDialog(playerid, D_ADMIN_CRIME_CREATE_NAME, DIALOG_STYLE_INPUT, " ",
		g_big_string,
		"Далее", "Назад"
	);
}

ShowAdminCrimeEdit(playerid, index) // CMD:crmanage -> Редактирование фракции по нажатию на нее
{
	format:g_big_string("\
		" #cPROJECT " Свойство\t" #cPROJECT "Значение\n \
		" #cWHITE "Изменить название\t" #cPROJECT "%s\n \
		" #cWHITE "Изменить статус\t" #cPROJECT "%s\n \
		" #cWHITE "Изменить тип\t" #cPROJECT "%s\n \
		" #cWHITE "Назначить лидера\t" #cPROJECT "%s\n \
		" #cWHITE "Снять лидера\n \
		" #cRED "Удалить фракцию",
		crime_data[index][cr_name],
		crime_data[index][cr_official] ? ("Официальный") : ("Одобренный"),
		GetCrimeTypeName(index),
		crime_data[index][cr_leader_name]
	);
	
	ShowPlayerDialog(playerid, D_ADMIN_CRIME_EDIT, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"Далее", "Назад"
	);
	
	return 1;
}

ShowAdminDisconnectionLog(playerid)
{
	clean:<g_big_string>;
	strcat(g_big_string, "" #cPROJECT "Имя аккаунта\t" #cPROJECT "Имя персонажа\t" #cPROJECT "Причина\t" #cPROJECT "Время\n" #cWHITE ""
	);
	
	for (new i, end_i; i < MAX_ADMIN_LOGS; i++)
	{
		if (isnull(admin_logs[i][alog_disconnect][alog_user_name]) || end_i >= 1)
		{
			break;
		}
		
		if ((i + 2) < MAX_ADMIN_LOGS)
		{
			if (isnull(admin_logs[i + 1][alog_disconnect][alog_user_name]))
			{
				end_i++;
			}
		}
		
		format:g_big_string("%s %s\t%s\t%s\t%s%d:%s%d:%s%d\n",
			g_big_string,
			admin_logs[i][alog_disconnect][alog_user_name],
			admin_logs[i][alog_disconnect][alog_character_name],
			(admin_logs[i][alog_disconnect][alog_reason] == 0) ? ("Вылетел") : ((admin_logs[i][alog_disconnect][alog_reason] == 1) ? ("Вышел") : ("Отсоединен сервером")),
			(admin_logs[i][alog_disconnect][alog_time_hour] > 9) ? ("") : ("0"),
			admin_logs[i][alog_disconnect][alog_time_hour],
			(admin_logs[i][alog_disconnect][alog_time_minute] > 9) ? ("") : ("0"),
			admin_logs[i][alog_disconnect][alog_time_minute],
			(admin_logs[i][alog_disconnect][alog_time_second] > 9) ? ("") : ("0"),
			admin_logs[i][alog_disconnect][alog_time_second]
		);
	}
	
	ShowPlayerDialog(playerid, D_ADMIN_DISLOG, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"Отмена", ""
	);
}

ShowAdminDeathLog(playerid)
{
	clean:<g_big_string>;
	strcat(g_big_string, "" #cPROJECT "Имя персонажа\t" #cPROJECT "Причина смерти\t" #cPROJECT "Имя убийцы\t" #cPROJECT "Время\n" #cWHITE ""
	);
	
	for (new i, end_i; i < MAX_ADMIN_LOGS; i++)
	{
		if (isnull(admin_logs[i][alog_death][alog_user_name]) || end_i >= 1)
		{
			break;
		}
		
		if ((i + 2) < MAX_ADMIN_LOGS)
		{
			if (isnull(admin_logs[i + 1][alog_death][alog_user_name]))
			{
				end_i++;
			}
		}
		
		format:g_small_string("%s", admin_logs[i][alog_death][alog_killer_name]);
		
		format:g_big_string("%s %s\t%s\t%s\t%s%d:%s%d:%s%d\n",
			g_big_string,
			admin_logs[i][alog_death][alog_character_name],
			ShowPlayerDeathReason(admin_logs[i][alog_death][alog_reason]),
			(isnull(admin_logs[i][alog_death][alog_killer_name])) ? ("~") : (g_small_string),
			(admin_logs[i][alog_death][alog_time_hour] > 9) ? ("") : ("0"),
			admin_logs[i][alog_death][alog_time_hour],
			(admin_logs[i][alog_death][alog_time_minute] > 9) ? ("") : ("0"),
			admin_logs[i][alog_death][alog_time_minute],
			(admin_logs[i][alog_death][alog_time_second] > 9) ? ("") : ("0"),
			admin_logs[i][alog_death][alog_time_second]
		);
	}
	
	ShowPlayerDialog(playerid, D_ADMIN_DISLOG, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"Отмена", ""
	);
}