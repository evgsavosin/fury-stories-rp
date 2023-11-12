/*!
	@brief Меню для системы бизнесов
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

ShowBusinessList(playerid, dialogid = D_BUSINESS, bool: register = true)
{
	clean:<g_string>;
	
	new count,
		index;
	
	if (!register)
	{
		strcat(g_string, "" #cPROJECT "Название компании\t" #cPROJECT "Финансы\n");
	}
	
	if (register)
	{
		strcat(g_string, "" #cGRAY "Зарегистрировать компанию\t" #cGREEN "$" #CREATE_BUSINESS_COST "\n");
	}
	
	for (new i; i < MAX_PLAYER_BUSINESSES; i++)
	{
		if ((index = player_business[playerid][i]) == INVALID_PARAM)
		{
			continue;
		}
		
		if (!register)
		{
			format:g_string("%s %s\t" #cGREEN "$%i\n", 
				g_string, 
				business_data[index][b_name],
				business_data[index][b_profit]
			);
		}
		else 
		{
			format:g_string("%s %s\t\n", 
				g_string, 
				business_data[index][b_name]
			);
		}
		
		g_dialog_select[playerid][count] = index;
		count++;
	}
	
	return (count > 0 || register) ? ShowPlayerDialog(playerid, dialogid, !register ? DIALOG_STYLE_TABLIST_HEADERS : DIALOG_STYLE_TABLIST, " ", g_string, "Выбрать", "Закрыть") : 0;
}

ShowBusinessSettings(playerid, const index)
{
	new str_subtype		[	64	];
	
	if (business_data[index][b_subtype] == INVALID_PARAM)
	{
		strcat(str_subtype, "" #cGRAY "Отсутствует");
	}
	else 
	{
		format:str_subtype("" #cPROJECT "%s",
			GetBusinessSubtypeText(index)
		);
	}
	
	format:g_string(" \
		Деятельность\t%s" #cWHITE "\n \
		%s\t",
		str_subtype,
		business_data[index][b_subtype] != INVALID_PARAM ? ("Ассортимент") : ("")
	);
	
	ShowPlayerDialog(playerid, D_BUSINESS + 21, DIALOG_STYLE_TABLIST, " ", g_string, "Далее", "Назад");
}

ShowBusinessSettingsSubtypes(playerid, const index)
{
	clean:<g_string>;
	
	for (new i; i < MAX_BUSINESS_SUBTYPE; i++)
	{
		format:g_string("%s %s\n",
			g_string,
			business_subtype[business_data[index][b_type]][i][bst_name]
		);
	}

	ShowPlayerDialog(playerid, D_BUSINESS + 22, DIALOG_STYLE_LIST, " ", g_string, "Далее", "Назад");
}

ShowBusinessSettingsAssortment(playerid, const index)
{
	clean:<g_big_string>;
	
	new itindex,
		count;
	
	strcat(g_big_string, "" #cPROJECT "Имя\t" #cPROJECT "Стоимость\n\
	" #cGRAY "Добавить продукцию\n");
	
	for (new i; i < MAX_BUSINESS_ASSORT; i++)
	{
		if (bassort_data[index][i][ba_item_id] == 0 
		|| (itindex = GetItemIndexById(bassort_data[index][i][ba_item_id])) == INVALID_ITEM_ID)
		{
			continue;
		}
		
		format:g_big_string("%s %s\t" #cGREEN "$%i" #cWHITE "\n", 
			g_big_string,
			item_list[itindex][it_name],
			bassort_data[index][i][ba_cost]
		);
		
		g_dialog_select[playerid][count] = i;
		count++;
	}
	
	ShowPlayerDialog(playerid, D_BUSINESS + 23, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "Выбрать", "Назад");
}

ShowBusinessInformation(playerid, const index, dialogid)
{	
	if (!IsUserAllowQuery(playerid))
	{
		return;
	}
	
	format:g_string("\
		SELECT c.c_name AS owner_name \
		FROM " #__BUSINESSES " b \
		JOIN " #__CHARACTERS " c \
		ON b.b_character_id = c.c_id \
		WHERE b.b_id = %i",
		GetBusinessId(index)
	);
	
	mysql_tquery(db, g_string, "OnBusinessShowInformation", "iii", playerid, index, dialogid);
	
	SetUserAllowQuery(playerid, false);
}

function OnBusinessShowInformation(playerid, index, dialogid)
{
	SetUserAllowQuery(playerid, true);
	
	clean:<g_big_string>;
	
	new name	[MAX_PLAYER_NAME],
		rows,
		day,
		month,
		year,
		hour,
		minute;
	
	cache_get_row_count(rows);
	
	if (rows != 0)
	{
		cache_get_value_name(0, "owner_name", name);
	}
	
	if (isnull(name))
	{
		strcat(name, "Неизвестно");
	}
	
	gmtime(business_data[index][b_created_time], year, month, day, hour, minute);
	
	format:g_big_string("" #DEFAULT " Информация о компании #%d\n\n\
		Название: " #cPROJECT "%s" #cWHITE ".\n\
		Вид деятельности: " #cPROJECT "%s" #cWHITE ".\n\
		Дата регистрации: " #cPROJECT "" #DATE_FORMAT "" #cWHITE ".\n\
		Владелец: " #cPROJECT "%s" #cWHITE,
		GetBusinessId(index),
		GetBusinessName(index),
		GetBusinessTypeText(index),
		hour,
		minute,
		day,
		month,
		year,
		name
	);
	
	if (CheckBusinessAccess(TYPE_BUSINESS_OWNER, playerid, index))
	{
		format:g_big_string("%s\n\n\
			" #DEFAULT " Статистика о доходах:" #cWHITE "\n\
			Финансы: " #cGREEN "$%i" #cWHITE ".\n\
			Ежедневная прибыль: " #cGREEN "$%i" #cWHITE ".\n\
			Еженедельная прибыль: " #cGREEN "$%i" #cWHITE ".",
			g_big_string,
			business_data[index][b_profit],
			business_data[index][b_profit_daily],
			business_data[index][b_profit_weekly]
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Назад", "");
	return 1;
}

ShowBusinessMembers(playerid, const index)
{
	if (!IsUserAllowQuery(playerid))
	{
		return;
	}
	
	format:g_string("\
		SELECT bm.*, c.c_name, c.c_online \
		FROM " #__BMEMBERS " bm, " #__CHARACTERS " c \
		WHERE bm.bm_character_id = c.c_id AND bm_business_id = %i \
		LIMIT %i",
		GetBusinessId(index),
		MAX_BUSINESS_ITEM_LIST
	);
	
	mysql_tquery(db, g_string, "OnBusinessShowMembers", "ii", playerid, index);
	
	SetUserAllowQuery(playerid, false);
}

function OnBusinessShowMembers(playerid, const index)
{
	strglobalclear();
	
	Clear:bmember_select(playerid);
	
	new rows,
		i,
		online;
	
	cache_get_row_count(rows);
	SetPVarInt(playerid, "Business:CountMemberList", rows);
	
	strcat(g_big_string, "" #cPROJECT "Имя\t" #cPROJECT "Статус\n");

	for (; i < rows; i++)
	{
		if (i == MAX_BUSINESS_ITEM_LIST)
		{
			break;
		}
		
		cache_get_value_name_int(i, "c_online", online);
		cache_get_value_name(i, "c_name", g_small_string, MAX_PLAYER_NAME);
		cache_get_value_name_int(i, "bm_character_id", bmember_select[playerid][i][bs_character_id]);
		cache_get_value_name_int(i, "bm_perm_renovation", bmember_select[playerid][i][bs_perm][bm_perm_renovation]);
		cache_get_value_name_int(i, "bm_perm_lock", bmember_select[playerid][i][bs_perm][bm_perm_lock]);
		cache_get_value_name_int(i, "bm_perm_invite", bmember_select[playerid][i][bs_perm][bm_perm_invite]);
		cache_get_value_name_int(i, "bm_perm_uninvite", bmember_select[playerid][i][bs_perm][bm_perm_uninvite]);
		cache_get_value_name_int(i, "bm_perm_change", bmember_select[playerid][i][bs_perm][bm_perm_change]);
	
		GetWithoutUnderscore(g_small_string, bmember_select[playerid][i][bs_name]);
		
		format:g_big_string("%s %s\t%s" #cWHITE "\n",
			g_big_string,
			bmember_select[playerid][i][bs_name],
			(online ? ("" #cPROJECT "В сети") : ("" #cGRAY "Не в сети"))
		);
	}
	
	if (rows == 0)
	{
		strcat(g_big_string, "" #cGRAY " По данному запросу не найдено сотрудников\t");
		g_dialog_select[playerid][i] = ITEM_LIST_NONE;
	}
	
	ShowPlayerDialog(playerid, D_BUSINESS + 16, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "Далее", "Назад");
	
	SetUserAllowQuery(playerid, true);
	return 1;
}

ShowBusinessMemberSelected(playerid, index)
{
	format:g_big_string(" \
		" #cGRAY "Исключить из компании\t%s" #cWHITE "\n \
		Доступ к режиму ремонта\t%s" #cWHITE "\n \
		Доступ к дверям " #cGRAY "(/prlock)" #cWHITE "\t%s" #cWHITE "\n \
		Возможность принимать в компанию\t%s" #cWHITE "\n \
		Возможность исключать из компании\t%s" #cWHITE "\n \
		Изменять привилегии\t%s" #cWHITE "",
		bmember_select[playerid][index][bs_name],
		bmember_select[playerid][index][bs_perm][bm_perm_renovation] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет"),
		bmember_select[playerid][index][bs_perm][bm_perm_lock] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет"),
		bmember_select[playerid][index][bs_perm][bm_perm_invite] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет"),
		bmember_select[playerid][index][bs_perm][bm_perm_uninvite] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет"),
		bmember_select[playerid][index][bs_perm][bm_perm_change] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет")
	);
	
	ShowPlayerDialog(playerid, D_BUSINESS + 17, DIALOG_STYLE_TABLIST, bmember_select[playerid][index][bs_name], g_big_string, "Выбрать", "Назад");
}

ShowBusinessMemberChange(playerid, targetid)
{
	format:g_big_string(" \
		Доступ к режиму ремонта\t%s\n \
		Доступ к дверям " #cGRAY "(/prlock)" #cWHITE "\t%s\n \
		Возможность принимать в компанию\t%s\n \
		Возможность исключать из компании\t%s\n \
		Изменять привилегии\t%s",
		bmember_data[targetid][bm_perm][bm_perm_renovation] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет"),
		bmember_data[targetid][bm_perm][bm_perm_lock] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет"),
		bmember_data[targetid][bm_perm][bm_perm_invite] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет"),
		bmember_data[targetid][bm_perm][bm_perm_uninvite] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет"),
		bmember_data[targetid][bm_perm][bm_perm_change] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет")
	);
	
	ShowPlayerDialog(playerid, D_BUSINESS + 15, DIALOG_STYLE_TABLIST, " ", g_big_string, "Выбрать", "Назад");
}