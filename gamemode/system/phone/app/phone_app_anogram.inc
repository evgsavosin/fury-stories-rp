/*!
	@brief Приложение "Anogram"
	@author Found (evg.savosin)
	@date 01.11.2019
*/

ShowPhoneAnogram(playerid, index, error[] = "")
{
	if (isnull(phone_data[index][ph_anogram_name]))
	{
		format:g_string("" #DEFAULT " Anogram\n\
			\n\
			Добро пожаловать в приложение.\n\
			" #cPROJECT "Anogram" #cWHITE " - это бесплатный анонимный мессенджер,\n\
			защищённый сквозным шифрованием. Это обеспечивает максимальную сохранность Ваших данных.\n\
			\n\
			Перед тем, как Вы начнете пользоваться данным приложением,\n\
			необходимо ввести Ваш логин в нём.\n\
			\n\
			Введите логин:%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, D_PHONE_APP_ANOGRAM + 6, DIALOG_STYLE_INPUT, " ",
			g_string,
			"Далее", "Назад"
		);
	}
	else 
	{
		format:g_string(#cPROJECT "%s\n \
			Мои беседы\n \
			Настройки",
			phone_data[index][ph_anogram_name]
		);
		
		ShowPlayerDialog(playerid, D_PHONE_APP_ANOGRAM, DIALOG_STYLE_LIST, "Anogram",
			g_string,
			"Выбрать", "Закрыть"
		);
	}
}

ShowPhoneAnogramDialogs(playerid, index)
{
	format:g_string("\
		SELECT an.ph_to_phone_id, \
			   ph.ph_anogram_name \
		FROM " #__PHONES_ANOGRAM " an \
		JOIN " #__PHONES " ph \
			ON ph.ph_id = an.ph_to_phone_id  \
		WHERE (an.ph_phone_id = %d AND an.ph_from_phone_id = %d) \
		GROUP BY an.ph_to_phone_id",
		GetPhoneId(index),
		GetPhoneId(index)
	);
	
	mysql_tquery(db, g_string, "OnPhoneShowAnogramDialogs", "i", playerid);
}

function OnPhoneShowAnogramDialogs(playerid)
{
	clean:<g_big_string>;
	
	new rows,
		name	[MAX_PHONE_ANOGRAM_NAME],
		id;
	
	cache_get_row_count(rows);
	
	for (new i; i < rows; i++)
	{
		if (i >= MAX_PHONE_ANOGRAM_CONTACTS)
		{
			break;
		}
		
		cache_get_value_name(i, "ph_anogram_name", name, MAX_PHONE_ANOGRAM_NAME);
		cache_get_value_name_int(i, "ph_to_phone_id", id);
		
		format:g_big_string("%s %s\n", g_big_string, name);
		g_dialog_select[playerid][i] = id;
	}
	
	ShowPlayerDialog(playerid, D_PHONE_APP_ANOGRAM + 1, DIALOG_STYLE_LIST, " ", g_big_string, "Далее", "Назад");
	return 1;
}

ShowPhoneAnogramMessages(playerid, from_phone_id, to_phone_id)
{
	format:g_string("\
		SELECT an.ph_text, \
			   ph.ph_anogram_name \
		FROM " #__PHONES_ANOGRAM " an \
		JOIN " #__PHONES " ph \
			ON ph.ph_id = an.ph_from_phone_id \
		WHERE an.ph_phone_id = %d \
			AND ( \
				(an.ph_from_phone_id = %d AND an.ph_to_phone_id = %d) \
				OR (an.ph_from_phone_id = %d AND an.ph_to_phone_id = %d) \
			) \
		ORDER BY an.ph_date ASC",
		from_phone_id,
		from_phone_id,
		to_phone_id,
		to_phone_id,
		from_phone_id
	);
	
	mysql_tquery(db, g_string, "OPhoneAnogramnShowMessages", "i", playerid);
}

function OPhoneAnogramnShowMessages(playerid)
{
	clean:<g_big_string>;
	
	new rows,
		name	[MAX_PHONE_ANOGRAM_NAME],
		id;
	
	cache_get_row_count(rows);
	
	for (new i; i < rows; i++)
	{
		if (i >= MAX_PHONE_ANOGRAM_CONTACTS)
		{
			break;
		}
		
		cache_get_value_name(i, "ph_anogram_name", name, MAX_PHONE_ANOGRAM_NAME);
		cache_get_value_name_int(i, "ph_to_phone_id", id);
		
		format:g_big_string("%s %s\n", g_big_string, name);
		g_dialog_select[playerid][i] = id;
	}
	
	ShowPlayerDialog(playerid, D_PHONE_APP_ANOGRAM + 2, DIALOG_STYLE_INPUT, " ", g_big_string, "Далее", "Назад");
	return 1;
}

ShowPhoneAnogramSettings(playerid)
{
	ShowPlayerDialog(playerid, D_PHONE_APP_ANOGRAM + 3, DIALOG_STYLE_LIST, "Anogram",
		" Изменить логин\n\
		  Очистить переписку",
		"Выбрать", "Закрыть"
	);
}

ShowPhoneAnogramChangeLogin(playerid, index, error[] = "")
{
	format:g_string("\
		" #DEFAULT " Смена логина\n\n\
		Текущий логин: " #cPROJECT "%s" #cWHITE "\n\
		Введите новый логин:\n\n\
		" #cGRAY "Минимальная длина - 4 символа, а максимальна - 32.%s%s",
		phone_data[index][ph_anogram_name],
		isnull(error) ? ("") : ("\n\n" #cRED),
		error
	);
	
	ShowPlayerDialog(playerid, D_PHONE_APP_ANOGRAM + 4, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
}

Create:anogram_message(playerid, from_phone_id, to_phone_id, const text[])
{
	format:g_string("(%d, %d, %d, '%q', NOW()),",
		from_phone_id, from_phone_id, to_phone_id, text
	);
	
	format:g_big_string("INSERT INTO " #__PHONES_ANOGRAM " \
	(ph_phone_id, ph_from_phone_id, ph_to_phone_id, ph_text, ph_date) \
	VALUES \
	%s (%d, %d, %d, '%q', NOW())",
		g_string,
		
		to_phone_id, 
		from_phone_id, 
		to_phone_id, 
		text
	);
	
	mysql_tquery(db, g_big_string, "OnPhoneAnogramMessageCreate", "ddd", playerid, from_phone_id, to_phone_id);
}

function OnPhoneAnogramMessageCreate(playerid, from_phone_id, to_phone_id)
{
	ShowPhoneAnogramMessages(playerid, from_phone_id, to_phone_id);
	return 1;
}

Remove:all_anogram_message(const phone_id)
{
	format:g_string("DELETE FROM " #__PHONES_ANOGRAM " WHERE ph_phone_id = %d",
		phone_id
	);
	
	mysql_tquery(db, g_string);
}