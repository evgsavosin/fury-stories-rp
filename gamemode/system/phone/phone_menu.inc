/*!
	@brief Динамичные диалоги для системы телефона
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.01.2018
*/
					
ShowPhoneList(playerid, dialogid = D_PHONE, btn_1[] = "Выбрать", btn_2[] = "Закрыть")
{
	clean:<g_big_string>;
	
	new count,
		index,
		hour,
		minute,
		second,
		day,
		month,
		year,
		str_paid_time		[	64 	];
	
	strcat(g_big_string, "" #cPROJECT "#\t" #cPROJECT "Номер\t" #cPROJECT "Статус\t" #cPROJECT "Тариф оплачен до\n");
	for (new i; i < MAX_INVENTORY_SLOTS; i++)
	{
		if ((index = GetPhoneIndexBySlot(playerid, i, TYPE_INV_PLAYER)) == INVALID_PARAM)
		{
			continue;
		}
		
		if (phone_data[index][ph_paid_time] != 0)
		{
			gmtime(phone_data[index][ph_paid_time], year, month, day, hour, minute, second);
			format:str_paid_time("" #DATE_FORMAT "",
				hour,
				minute,
				day,
				month,
				year
			);
		}
		else 
		{
			clean:<str_paid_time>;
			strcat(str_paid_time, "" #cDARKRED "Требует оплаты");
		}
		
		format:g_big_string("%s " #cWHITE "%s телефон%s%s\t" #cPROJECT "%i\t%s\t%s\n",
			g_big_string,
			panel_color_list[phone_data[index][ph_col_panel]][pc_color_name],
			GetInventoryDefaultPhone(playerid) == index ? (" [" #cGRAY "по умолчанию" #cWHITE "]") : (""),
			phone_data[index][ph_call_index] != INVALID_PARAM ? (" [" #cDARKRED "вызывает" #cWHITE "]") : (""),
			phone_data[index][ph_number],
			(!phone_data[index][ph_status]) ? ("" #cGRAY "Выключен") : ("" #cPROJECT "Включен"),
			str_paid_time
		);
		
		g_dialog_select[playerid][count] = index;
		count++;
	}
	
	return count ? ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, btn_1, btn_2) : 0;
}

ShowPhoneMenu(playerid)
{
	new index = GetPVarInt(playerid, "Phone:Select");
	
	if (index == INVALID_PARAM)
	{
		return INVALID_PARAM;
	}
	
	format:g_small_string(" %s" #cWHITE " телефон",
		phone_data[index][ph_status] ? ("" #cGRAY "Выключить") : ("" #cPROJECT "Включить")
	);
	
	return ShowPlayerDialog(playerid, D_PHONE - 1, DIALOG_STYLE_LIST, " ", g_small_string, "Выбрать", "Закрыть");
}

ShowPhoneConversation(playerid, const index, const number)
{
	format:g_big_string("\
		SELECT pm_from_number, pm_to_number, pm_text, pm_created_time \
		FROM " #__MESSAGES " \
		WHERE (pm_from_number = %i AND pm_to_number = %i AND pm_type = %i) \
		OR (pm_from_number = %i AND pm_to_number = %i AND pm_type = %i) \
		ORDER BY pm_created_time ASC \
		LIMIT 25",
		GetPhoneNumber(index),
		number,
		TYPE_PH_OUTGOING,
		number,
		GetPhoneNumber(index),
		TYPE_PH_INCOMING
	);
	
	mysql_pquery(db, g_big_string, "OnPhoneShowConversation", "iii", playerid, index, number);
}

function OnPhoneShowConversation(playerid, index, number)
{
	strglobalclear();
	
	new rows,
		from_number,
		time,
		year,
		month,
		day,
		hour,
		minute,
		second,
		name 		[	MAX_PLAYER_NAME	],
		text		[		120			];
	
	cache_get_row_count(rows);
	
	name[0] = EOS;
	
	GetItemListNameOfContact(index, number, name);
	format:g_big_string("" #DEFAULT " Беседа с " #cPROJECT "%s" #cWHITE ":\n\n", name);
	
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "pm_created_time", time);
		cache_get_value_name_int(i, "pm_from_number", from_number);
		cache_get_value_name(i, "pm_text", text);
		
		name[0] = EOS;
		
		if (from_number == GetPhoneNumber(index))
		{
			strcat(name, GetPlayerCurrentName(playerid));
		}
		else 
		{
			GetItemListNameOfContact(index, from_number, name);
		}
		
		gmtime(time, year, month, day, hour, minute, second);
		
		format:g_big_string("%s - " #cGRAY "[%02d/%02d/%04d %02d:%02d:%02d]" #cWHITE " %s: %s\n", 
			g_big_string,
			day,
			month,
			year,
			hour,
			minute,
			second,
			name,
			text
		);
	}
	
	SetPVarInt(playerid, "Phone:ConversationNumber", number);
	ShowPlayerDialog(playerid, D_PHONE + 1, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Удалить", "Назад");
	
	return 1;
}

ShowPhoneContactMenu(playerid, index)
{
	SetPVarInt(playerid, "Phone:ContactSelect", index);
	
	format:g_string(" Информация о контакте\n \
		  Позвонить\t" #cGRAY "/call %i\n \
		  Отправить сообщение\t" #cGRAY "/sms %\n \
		  Переименовать\n \
		  Удалить из контактов",
		index,
		index
	);
	
	ShowPlayerDialog(playerid, D_PHONE + 6, DIALOG_STYLE_TABLIST, " ", g_string, "Выбрать", "Закрыть");
}

ShowPhoneContactInformation(playerid, phone_index, index)
{
	new year,
		month,
		day,
		hour,
		minute;
	
	gmtime(contact_data[phone_index][index][pc_created_time], year, month, day, hour, minute, _);
	
	format:g_string("\
		" #DEFAULT " Информация о контакте\n\n\
		Индекс: " #cPROJECT "%i" #cWHITE "\n\
		Имя: " #cPROJECT "%s" #cWHITE "\n\
		Номер: " #cPROJECT "%i" #cWHITE "\n\
		Дата добавления: " #cPROJECT "%02d/%02d/%04d %02d:%02d" #cWHITE "",
		index + 1,
		contact_data[phone_index][index][pc_name],
		contact_data[phone_index][index][pc_number],
		day, month, year, hour, minute
	);
	
	ShowPlayerDialog(playerid, D_PHONE + 8, DIALOG_STYLE_MSGBOX, " ",
		g_string, 
		"Удалить", "Назад"
	);
}

ShowPhoneMusicList(playerid, const dialogid)
{
	clean:<g_big_string>;
	
	for (new i; i < sizeof phone_music; i++)
	{
		format:g_big_string("%s %s\n",
			g_big_string,
			phone_music[i][pm_name] 
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", g_big_string, "Выбрать", "Назад");
}