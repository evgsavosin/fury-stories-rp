/*!
	@brief Файл с командами криминальных систем
	@author Flavo
	@date 03.11.2019
*/

ShowCrimeList(playerid) // CMD: crmenu
{	
	clean:<g_small_string>;
	strcat(g_small_string, "\
		Информация\n\
		Участники\n\
		Заказать товар"
	);
	
	ShowPlayerDialog(playerid, D_CRIME, DIALOG_STYLE_LIST, GetCrimeName(playerid),
		g_small_string,
		"Далее", "Закрыть"
	);
}

ShowCrimeInformation(playerid, index) // CMD: crmenu -> Информация
{
	if (!IsUserAllowQuery(playerid))
	{
		return;
	}
	
	format:g_string("\
		SELECT COUNT(cr_id) AS members_count \
		FROM " #__CRIMES_MEMBER " \
		WHERE cr_crime_id = %d",
		crime_data[index][cr_id]
	);
	
	mysql_tquery(db, g_string, "OnCrimeMemberCount", "ii", playerid, index);
	
	SetUserAllowQuery(playerid, false);
}

function OnCrimeMemberCount(playerid, index)
{
	SetUserAllowQuery(playerid, true);
	
	new rows;
	
	cache_get_row_count(rows);
	
	if (!rows)
	{
		return 0;
	}
	
	new count,
		type = crime_data[index][cr_type_id] - 1;
	
	cache_get_value_name_int(0, "members_count", count);
	
	format:g_string("" #DEFAULT " Информация\n\n\
		" #cWHITE "Название организации:" #cPROJECT " %s\n\
		" #cWHITE "Тип организации: " #cPROJECT " %s\n\
		" #cWHITE "Лидер организации:" #cPROJECT " %s\n\
		" #cWHITE "Количество участников:" #cPROJECT " %d\n\
		" #cWHITE "Официальная:" #cPROJECT " %s\n\
		" #cWHITE "Средства организации:" #cGREEN " $%d",
		GetCrimeName(playerid),
		crtype_data[type][cr_name],
		crime_data[index][cr_leader_name],
		count,
		crime_data[index][cr_official] ? ("Да") : ("Нет"),
		crime_data[index][cr_money]
	);
	
	ShowPlayerDialog(playerid, D_CRIME_DATA, DIALOG_STYLE_MSGBOX, " ",
		g_string,
		"Закрыть", ""
	);

	return 1;
}

ShowCrimeMember(playerid) // CMD: crmenu -> Участники
{
	clean:<g_string>;
	strcat(g_string, #cWHITE "Принять в организацию\t" #cGRAY "/crinvite\n\
		" #cWHITE "Исключить из организации\t" #cGRAY "\n\
		" #cWHITE "Изменить привилегии\n\
		" #cWHITE "Список всех участников"
	);
	
	ShowPlayerDialog(playerid, D_CRIME_MEMBER, DIALOG_STYLE_TABLIST , " ",
		g_string,
		"Далее", "Назад"
	);
}

ShowCrimeStaffUninvite(playerid, error[] = "") // CMD: crmenu -> Участники -> Исключить из организации
{
	format:g_string("" #DEFAULT " Исключить из организации\n\n\
		Введите ID игрока, которого Вы хотите исключить из организации:%s%s",
		!isnull(error) ? ("\n\n" #cRED) : (""), 
		error 
	);
		
	ShowPlayerDialog(playerid, D_CRIME_UNINVITE, DIALOG_STYLE_INPUT, " ",
		g_string,
		"Далее", "Назад"
	);
}

ShowCrimeStaffPerm(playerid, error[] = "") // CMD: crmenu -> Участники -> Изменить привилегии
{
	format:g_string("" #DEFAULT " Изменить привилегии\n\n\
		Введите ID игрока, привилегии которого Вы хотите изменить:%s%s",
		!isnull(error) ? ("\n\n" #cRED) : (""), 
		error 
	);
		
	ShowPlayerDialog(playerid, D_CRIME_PERM, DIALOG_STYLE_INPUT, " ",
		g_string,
		"Далее", "Назад"
	);
}

ShowCrimeStaffPermEdit(playerid, targetid) // CMD: crmenu -> Участники -> Изменить привилегии
{
	format:g_string(" \
		" #cWHITE "Возможность принимать в организацию\t%s\n \
		" #cWHITE "Возможность исключать из организации\t%s\n \
		" #cWHITE "Возможность заказывать товар\t%s\n \
		" #cWHITE "Возможность изменять привилегии\t%s",
		crmember_data[targetid][cr_perm][cr_perm_invite] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет"),
		crmember_data[targetid][cr_perm][cr_perm_uninvite] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет"),
		crmember_data[targetid][cr_perm][cr_perm_buy] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет"),
		crmember_data[targetid][cr_perm][cr_perm_manage] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет")
	);
	
	ShowPlayerDialog(playerid, D_CRIME_EDIT_PERM, DIALOG_STYLE_TABLIST, " ",
		g_string,
		"Выбрать", "Отмена"
	);
}

ShowCrimeMemberList(playerid, const index, action = CRIME_LIST_BEGIN) // CMD: crmenu -> Участники -> Список участников
{
	new page;
	
	if (action == CRIME_LIST_BEGIN)
	{
		SetPVarInt(playerid, "Crime:MemberPage", 0);
		page = 0;
	}
	else if (action == CRIME_LIST_CURRENT)
	{
		page = GetPVarInt(playerid, "Crime:MemberPage");
	}
	else if (action == CRIME_LIST_NEXT)
	{
		GivePVarInt(playerid, "Crime:MemberPage", 1);
		page = GetPVarInt(playerid, "Crime:MemberPage");
	}
	else if (action == CRIME_LIST_BACK)
	{
		TakePVarInt(playerid, "Crime:MemberPage", 1);
		page = GetPVarInt(playerid, "Crime:MemberPage");
	}

	format:g_string("\
		SELECT crm.*, c.c_name, c.c_online \
		FROM " #__CRIMES_MEMBER " crm, " #__CHARACTERS " c \
		WHERE crm.cr_character_id = c.c_id AND cr_crime_id = %d \
		LIMIT %d, %d",
		GetCrimeId(index),
		page * MAX_CRIME_MEMBER_LIST,
		MAX_CRIME_MEMBER_LIST + 1
	);
	
	mysql_tquery(db, g_string, "OnCrimeShowMembers", "ddd", playerid, index, page);
}

function OnCrimeShowMembers(playerid, const index, page)
{
	strglobalclear();
	
	Clear:crmember_select(playerid);
	
	new rows,
		online,
		i;
	
	cache_get_row_count(rows);
	
	if (!rows)
	{
		ShowCrimeMemberList(playerid, index, CRIME_LIST_BACK);
		
		return 1;
	}
	
	strcat(g_big_string, "" #cPROJECT " Имя\t" #cPROJECT "Статус\n");

	for (; i < rows; i++)
	{
		if (i == MAX_CRIME_MEMBER_LIST)
		{
			break;
		}
		
		clean:<g_small_string>;
		
		cache_get_value_name_int(i, "c_online", online);
		cache_get_value_name(i, "c_name", g_small_string, MAX_PLAYER_NAME);
		cache_get_value_name_int(i, "cr_crime_id", crmember_select[playerid][i][cr_crime_id]);
		cache_get_value_name_int(i, "cr_character_id", crmember_select[playerid][i][cr_character_id]);
		cache_get_value_name_int(i, "cr_leader", crmember_select[playerid][i][cr_leader]);
		cache_get_value_name_int(i, "cr_perm_invite", crmember_select[playerid][i][cr_perm][cr_perm_invite]);
		cache_get_value_name_int(i, "cr_perm_uninvite", crmember_select[playerid][i][cr_perm][cr_perm_uninvite]);
		cache_get_value_name_int(i, "cr_perm_buy", crmember_select[playerid][i][cr_perm][cr_perm_buy]);
		cache_get_value_name_int(i, "cr_perm_manage", crmember_select[playerid][i][cr_perm][cr_perm_manage]);
	
		GetWithoutUnderscore(g_small_string, crmember_select[playerid][i][cr_name]);
		
		format:g_big_string("%s %s\t%s" #cWHITE "\n",
			g_big_string,
			crmember_select[playerid][i][cr_name],
			(online ? ("" #cPROJECT "В сети") : ("" #cGRAY "Не в сети"))
		);
	}
	
	if (i == MAX_CRIME_MEMBER_LIST && rows > MAX_CRIME_MEMBER_LIST)
	{
		strcat(g_big_string, "" #cGRAY "Вперед\t" #cWHITE ">>");
		crmember_select[playerid][i++][cr_character_id] = CRIME_LIST_NEXT;
	}
	
	if (page > 0)
	{
		strcat(g_big_string, "\n" #cGRAY "Назад\t" #cWHITE "<<");
		crmember_select[playerid][i][cr_character_id] = CRIME_LIST_BACK;
	}
	
	ShowPlayerDialog(playerid, D_CRIME_MEMBER_LIST, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"Далее", "Назад"
	);
	
	return 1;
}

ShowCrimeStaffInvite(playerid, error[] = "") // CMD: crmenu -> Участники -> Принять в организацию
{
	format:g_string("" #DEFAULT " Принять в организацию\n\n\
		Введите ID игрока, которого Вы хотите принять в организацию:\n\n\
		" #cGRAY "Игрок должен находиться неподалеку от Вас.%s%s",
		!isnull(error) ? ("\n\n" #cRED) : (""), 
		error 
	);
	
	ShowPlayerDialog(playerid, D_CRIME_INVITE, DIALOG_STYLE_INPUT, " ",
		g_string,
		"Далее", "Назад"
	);
}

ShowCrimeMemberEdit(playerid, index) // CMD: crmenu -> Список участников -> Выбранный участник
{
	format:g_string(" \
		" #cGRAY "Исключить из организации\t" #cGRAY "%s\n \
		" #cWHITE "Возможность принимать в организацию\t%s\n \
		" #cWHITE "Возможность исключать из организации\t%s\n \
		" #cWHITE "Возможность заказывать товар\t%s\n \
		" #cWHITE "Возможность изменять привилегии\t%s",
		crmember_select[playerid][index][cr_name],
		crmember_select[playerid][index][cr_perm][cr_perm_invite] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет"),
		crmember_select[playerid][index][cr_perm][cr_perm_uninvite] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет"),
		crmember_select[playerid][index][cr_perm][cr_perm_buy] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет"),
		crmember_select[playerid][index][cr_perm][cr_perm_manage] ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет")
	);
	
	ShowPlayerDialog(playerid, D_CRIME_MEMBER_EDIT, DIALOG_STYLE_TABLIST, " ",
		g_string,
		"Выбрать", "Назад"
	);
}

ShowCrimeBuy(playerid) // CMD: crmenu -> Заказать товар
{
	clean:<g_string>;
	strcat(g_string, " \
		" #cGRAY "Информация\n \
		" #cGRAY "Узнать местоположение товара \n \
		" #cWHITE "Оружейный арсенал\n \
		" #cWHITE "Боеприпасы\n \
		" #cWHITE "Наркотические вещества"
	);
	
	ShowPlayerDialog(playerid, D_CRIME_BUY, DIALOG_STYLE_LIST, " ",
		g_string,
		"Далее", "Назад"
	);
}

ShowCrimeBuyInformation(playerid) // CMD: crmenu -> Заказать товар -> Информация
{
	format:g_big_string("\
		" #DEFAULT " Информация\n\n\
		" #cWHITE "Доступ к заказу определенного товара зависит от типа организации.\n\
		" #cWHITE "Закупки осуществляются на средства организации, которые автоматически\n\
		" #cWHITE "начисляются каждые " #cPROJECT "3" #cWHITE " дня.\n\
		" #cWHITE "Пачка наркотиков содержит " #cPROJECT "%d" #cWHITE " грамм.\n\
		" #cWHITE "Количество патронов коробке равно стандартной обойме оружия.\n\n\
		" #cPROJECT "%s:\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\n\
		" #cPROJECT "%s:\n\
		" #cWHITE "— Все товары предыдущего типа\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\n\
		" #cPROJECT "%s:\n\ 
		" #cWHITE "— Все товары предыдущих типов\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\n\
		" #cPROJECT "%s:\n\
		" #cWHITE "— Все товары предыдущих типов\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s\n\
		" #cWHITE "— %s",
		CR_BUY_DRUGS_GRAMM,
		crtype_data[0][cr_name],
		GetInventoryItemName(7),
		GetInventoryItemName(10),
		GetInventoryItemName(17),
		crtype_data[1][cr_name],
		GetInventoryItemName(8),
		GetInventoryItemName(13),
		GetInventoryItemName(19),
		GetInventoryItemName(21),
		GetInventoryItemName(113), // marijuana
		crtype_data[2][cr_name],
		GetInventoryItemName(9),
		GetInventoryItemName(12),
		GetInventoryItemName(14),
		GetInventoryItemName(20),
		GetInventoryItemName(22),
		GetInventoryItemName(114), // lsd
		crtype_data[3][cr_name],
		GetInventoryItemName(11),
		GetInventoryItemName(15),
		GetInventoryItemName(16),
		GetInventoryItemName(18),
		GetInventoryItemName(23),
		GetInventoryItemName(24),
		GetInventoryItemName(115) // cocaine
	);
	
	ShowPlayerDialog(playerid, D_CRIME_BUY_INFORMATION, DIALOG_STYLE_MSGBOX, " ",
		g_big_string,
		"Закрыть", ""
	);
}

ShowCrimeBuyList(playerid, const dialogid, const category) // CMD: crmenu -> Заказать товар -> Одна из категорий товаров
{ 
	clean:<g_big_string>;
	strcat(g_big_string, #cPROJECT " Название\t" #cPROJECT "Цена\n");
	
	for (new i, id; i < sizeof crbuy_data; i++)
	{
		if (crbuy_data[i][cr_buy_cat] != category
		|| crbuy_data[i][cr_buy_access_type] > crime_data[GetCrimeMember(playerid)][cr_type_id]
		)
		{
			continue;
		}
		
		id = GetItemIndexById(crbuy_data[i][cr_buy_item_id]);
		
		format:g_big_string("\
			%s\n " #cWHITE "%s\t" cGREEN "$%d",
			g_big_string,
			item_list[id][it_name],
			crbuy_data[i][cr_buy_count]
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"Выбрать", "Назад"
	);
}

ShowCrimeBuyConfirm(playerid, index) // CMD: crmenu -> Заказать товар -> Оружейный арсенал -> Выбранный товар
{
	new id = GetItemIndexById(crbuy_data[index][cr_buy_item_id]),
		crime_id = GetCrimeMember(playerid);

	format:g_string("\
		" #DEFAULT " Подтверждение покупки\n\n\
		" #cWHITE "Вы действительно хотите приобрести " #cPROJECT "%s" #cWHITE " за " #cGREEN "$%d" #cWHITE "?\n\
		" #cWHITE "Средства фракции: " #cGREEN "$%d",
		item_list[id][it_name],
		crbuy_data[index][cr_buy_count],
		crime_data[crime_id][cr_money]
	);
	
	ShowPlayerDialog(playerid, D_CRIME_BUY_CONFIRM, DIALOG_STYLE_MSGBOX, " ",
		g_string,
		"Далее", "Отмена"
	);
}

ShowCrimeBuyStorage(playerid, index, slot) // При нажатии на горячую клавишу на месте подбора крайм товаров
{
	clean:<g_big_string>;
	strcat(g_big_string, "" #cPROJECT "Название\t" #cPROJECT "Количество\n");

	for (new i, id; i < MAX_CRIME_BUY; i++)
	{
		if (crbuy_storage[index][slot][cr_buy_item_storage][i] == 0)
		{
			continue;
		}
		
		id = GetItemIndexById(crbuy_data[i][cr_buy_item_id]);
		
		format:g_big_string("%s\n" #cWHITE "%s\t" #cGRAY "%d",
			g_big_string,
			item_list[id][it_name],
			crbuy_storage[index][slot][cr_buy_item_storage][i]
		);
	}

	ShowPlayerDialog(playerid, D_CRIME_BUY_STORAGE, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"Выбрать", "Назад"
	);
}

ShowCrimeBuyStorageConfirm(playerid, item_index) // При выборе предмета на месте подбора крайм товара
{
	format:g_string("\
		" #DEFAULT " Подтверждение\n\n\
		Вы действительно хотите подобрать " #cPROJECT "%s" #cWHITE "?",
		item_list[item_index][it_name]
	);
	
	ShowPlayerDialog(playerid, D_CRIME_BUY_STORAGE_CONFIRM, DIALOG_STYLE_MSGBOX, " ",
		g_string,
		"Далее", "Отмена"
	);
}