/*!
	@brief Файл с загрузкой криминальных систем
	@author Flavo
	@date 03.11.2019
*/

Load:crime_data()
{	
	format:g_string("SELECT cr.*, \
		c.c_name AS cr_leader_name \
		FROM " #__CRIMES " cr \
		LEFT JOIN " #__CRIMES_MEMBER " crm \
		ON crm.cr_crime_id = cr.cr_id AND crm.cr_leader = 1 \
		LEFT JOIN " #__CHARACTERS " c \
		ON c.c_id = crm.cr_character_id \
		GROUP BY cr.cr_id"
	);
		
	mysql_tquery(db, g_string, "OnCrimeLoad");
}

function OnCrimeLoad()
{
	new rows;
	
	cache_get_row_count(rows);

	if (rows == 0)
	{
		return 1;
	}
	
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "cr_id", crime_data[i][cr_id]);
		cache_get_value_name(i, "cr_name", crime_data[i][cr_name], MAX_CRIME_NAME);
		cache_get_value_name(i, "cr_leader_name", crime_data[i][cr_leader_name], MAX_PLAYER_NAME);
		cache_get_value_name_int(i, "cr_type_id", crime_data[i][cr_type_id]);
		cache_get_value_name_int(i, "cr_official", crime_data[i][cr_official]);
		cache_get_value_name_int(i, "cr_money", crime_data[i][cr_money]);
		cache_get_value_name_int(i, "cr_update_date", crime_data[i][cr_update_date]);
	}
	
	printf("[OnCrimeLoad]: Crime Fractions have been loaded. All - %d",
		rows
	);
	
	return 1;
}

Update:crime_counter()
{
	format:g_big_string("\
		UPDATE crimes cr \
		JOIN crimes_type crt ON crt.cr_id = cr.cr_type_id \
		SET cr.cr_money = \
			IF( \
				(cr.cr_money + crt.cr_money) > crt.cr_max_money, \
				crt.cr_max_money, \
				IF( \
					cr_official = 0, \
					(cr.cr_money + (crt.cr_money / 2)), \
					(cr.cr_money + crt.cr_money) \
				) \
			), \
		cr.cr_update_date = CURDATE() \
		WHERE \
		cr.cr_update_date + INTERVAL 3 DAY <= CURDATE()"
	);
	
	mysql_tquery(db, g_big_string);
}

Create:crime_data(playerid, index, max_money)
{
	format:g_string("INSERT \
		INTO " #__CRIMES " (cr_name, cr_type_id, cr_money) \
		VALUES ('%q', %d, %d)",
		crime_data[index][cr_name],
		crime_data[index][cr_type_id],
		max_money
	);
	
	mysql_tquery(db, g_string, "OnCrimeCreate", "ddd", playerid, index, max_money);
}

Destroy:crime_data(index)
{
	format:g_string("DELETE \
		FROM " #__CRIMES " \
		WHERE cr_id = %d",
		GetCrimeId(index)
	);
	
	mysql_tquery(db, g_string);
	
	Destroy:crime_member_to_all(index);
}

Destroy:crime_leader(index)
{
	format:g_string("DELETE \
		FROM " #__CRIMES_MEMBER " \
		WHERE cr_crime_id = %d AND cr_leader = 1",
		GetCrimeId(index)
	);
	
	mysql_tquery(db, g_string);
}

Destroy:crime_member_to_all(index)
{
	format:g_string("DELETE \
		FROM " #__CRIMES_MEMBER " \
		WHERE cr_crime_id = %d",
		GetCrimeId(index)
	);
	
	mysql_tquery(db, g_string);
}

Create:crime_leader(crime_index, index)
{
	format:g_string("INSERT \
		INTO " #__CRIMES_MEMBER " (cr_crime_id, cr_character_id, cr_leader) \
		VALUES (%d, %d, 1)",
		GetCrimeId(crime_index),
		index
	);
	
	mysql_tquery(db, g_string);
}

function OnCrimeCreate(playerid, index, max_money)
{
	crime_data[index][cr_id] = cache_insert_id();
	crime_data[index][cr_money] = max_money;
	
	pformat:(#SUCCESS " Фракция " #cPROJECT "%s (#%d)" #cWHITE " успешно создана!",
		crime_data[index][cr_name],
		crime_data[index][cr_id]
	);
	
	psend:(playerid, C_WHITE);
	
	ShowAdminCrimeList(playerid);
	
	printf("[OnCrimeCreate]: Fraction [ID:%d] has been created.",
		crime_data[index][cr_id]
	);
	
	return 1;
}

stock Update:crime_int(crime_index, column[], _: value)
{
    format:g_string("UPDATE " #__CRIMES " SET %s = %d WHERE cr_id = %d LIMIT 1",
        column,
        value,
        GetCrimeId(crime_index)
    );

    mysql_tquery(db, g_string);
}

stock Update:crime_string(crime_index, column[], const value[], bool: quotes = true)
{
    format:g_string("UPDATE " #__CRIMES " SET %s = %s%q%s WHERE cr_id = %d LIMIT 1",
        column,
        quotes ? ("'") : (""),
        value,
        quotes ? ("'") : (""),
        GetCrimeId(crime_index)
    );

    return mysql_tquery(db, g_string);
}

stock Update:crime_float(crime_index, column[], Float: value)
{
    format:g_string("UPDATE " #__CRIMES " SET %s = %f WHERE cr_id = %d LIMIT 1",
        column,
        value,
        GetCrimeId(crime_index)
    );

    return mysql_tquery(db, g_string);
}

Check:crime_leader_candidate(playerid, crime_index, string[])
{
	format:g_string("SELECT c.*, IFNULL(crm.cr_crime_id, 0) AS is_crime_member \
		FROM characters c \
		LEFT JOIN crimes_member crm \
		ON crm.cr_character_id = c.c_id \
		WHERE c_name = '%q'",
		string
	);
	
	mysql_tquery(db, g_string, "OnCrimeCandidateCheck", "dds", playerid, crime_index, string);
}

function OnCrimeCandidateCheck(playerid, crime_index, string[])
{
	new rows;
	
	cache_get_row_count(rows);
	
	if (rows == 0)
	{
		format:g_string("\
			" #DEFAULT " Настройка лидера\n\n\
			" #cWHITE "Введите имя и фамилию лидера криминальной организации в поле для ввода.\n\n\
			" #cGRAY "Примечание:\n\
			" #cPROJECT "* " #cWHITE"Максимальная длина текста - " #cPROJECT "%d" #cWHITE" символов.\n\
			" #cPROJECT "* " #cWHITE"Формат вводимого текста: " #cPROJECT "Имя_Фамилия" #cWHITE".\n\n\
			" #cRED "Данного игрока не существует или его имя было указано неверно.",
			MAX_PLAYER_NAME-4
		);

		ShowPlayerDialog(playerid, D_ADMIN_CRIME_EDIT_LEADER, DIALOG_STYLE_INPUT, " ",
			g_string,
			"Далее", "Назад"
		);
		
		return 1;
	}
	
	new is_crime_member;
		
	cache_get_value_name_int(0, "is_crime_member", is_crime_member);
	
	if (is_crime_member > 0 && is_crime_member != crime_data[crime_index][cr_id])
	{
		format:g_string("\
			" #DEFAULT " Настройка лидера\n\n\
			" #cWHITE "Введите имя и фамилию лидера криминальной организации в поле для ввода.\n\n\
			" #cGRAY "Примечание:\n\
			" #cPROJECT "* " #cWHITE"Максимальная длина текста - " #cPROJECT "%d" #cWHITE" символов.\n\
			" #cPROJECT "* " #cWHITE"Формат вводимого текста: " #cPROJECT "Имя_Фамилия" #cWHITE".\n\n\
			" #cRED "Игрок состоит в другой организации и не может быть назначен лидером.",
			MAX_PLAYER_NAME-4
		);

		ShowPlayerDialog(playerid, D_ADMIN_CRIME_EDIT_LEADER, DIALOG_STYLE_INPUT, " ",
			g_string,
			"Далее", "Назад"
		);
		
		return 1;
	}
	
	new character_id;
	
	cache_get_value_name_int(0, "c_id", character_id);
	
	new crmember_id = GetCrimeMemberIdToName(crime_data[crime_index][cr_leader_name]);
	
	if (crmember_id != INVALID_PARAM)
	{
		Clear:crmember_data(crmember_id);
		
		pformat:("" ERROR " Вас сняли с лидерства криминальной организации " #cPROJECT "%s" #cWHITE ".", crime_data[crime_index][cr_name]);
		psend:(crmember_id, C_WHITE);
	}
	
	crmember_id = GetCrimeMemberIdToName(string);
	
	Destroy:crime_leader(crime_index);
	Create:crime_leader(crime_index, character_id);
	
	clean:<crime_data[crime_index][cr_leader_name]>;
	strcat(crime_data[crime_index][cr_leader_name], string, MAX_PLAYER_NAME);
	
	Update:crime_string(crime_index, "cr_leader_name", crime_data[crime_index][cr_leader_name]);
	
	if (crmember_id != INVALID_PARAM)
	{
		Clear:crmember_data(crmember_id);
		
		Load:character_crime_member(crmember_id);
		
		pformat:("" SUCCESS " Вас назначили лидером криминальной организации " #cPROJECT "%s" #cWHITE ".", crime_data[crime_index][cr_name]);
		psend:(crmember_id, C_WHITE);
	}
	
	ShowAdminCrimeEdit(playerid, crime_index);
	
	return 1;
}

Update:crime_money(index, id)
{
	format:g_small_string("\
		UPDATE " #__CRIMES " \
		SET cr_money = %d \
		WHERE cr_id = %d",
		index,
		id
	);
	
	mysql_tquery(db, g_small_string);
}