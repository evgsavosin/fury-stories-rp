/*!
	@brief Заголовок для системы телефонов
	@author Found (evg.savosin)
	@date 16.12.2016, update 26.01.2018
*/

// Defines
#define GetPhoneId(%0)						phone_data[%0][ph_id]
#define GetPhoneNumber(%0)					phone_data[%0][ph_number]
#define IsPhoneShowed(%0)					GetPVarInt(%0,"Phone:States")
#define GetPhoneShowedIndex(%0)				GetPVarInt(%0,"Phone:Select")

#define DIALOG_PHONE_NUMBER 				"\
	" #ERROR " Ошибка\n\n\
	Вы ввели неверный номер.\n\
	Вводимый номер должен быть в формате XXXXXX или XXX.\n\n\
	" #cGRAY "911 - экстренная служба;\n\
	777 - новостная студия;\
"

#define DIALOG_PHONE_NUMBER_EXISTS 			"\
	" #ERROR " Ошибка\n\n\
	Вводимый номер уже записан в ваших контактах.\
"

#define DIALOG_PHONE_APPS					" \
	Settings\n \
	GOG Maps\n \
	Fuber\n \
	Fuber Driver\n \
	Radio\
"

// Constants
const MAX_PHONE_ANOGRAM_NAME = 64,
	  MAX_PHONE_ANOGRAM_CONTACTS = 50;

// Structures
enum 
{
	NUMBER_TYPE_INCORRECTLY,
	NUMBER_TYPE_PHONE,
	NUMBER_TYPE_SPECIAL
};

/// Тип сообщения
enum
{
	TYPE_PH_OUTGOING, /// Исходящее
	TYPE_PH_INCOMING /// Входящие
};

/// Страницы
enum
{
	PH_PAGE_INVALID = INVALID_PARAM,
	PH_PAGE_DESKTOP,
	PH_PAGE_CONTACTS,
	PH_PAGE_CALL,
	PH_PAGE_INCOMING_CALL,
	PH_PAGE_OUTGOING_CALL,
	PH_PAGE_SMS
};

enum E_PHONE_MUSIC
{
	pm_id, 
	pm_name							[	16	],
};

new const phone_music				[		][	E_PHONE_MUSIC	] =
{
	{0, "Без звука"},
	{23000, "Мелодия 1"},
	{31204, "Мелодия 2"},  
	{19600, "Мелодия 3"}, 
	{20804, "Мелодия 4"}
};

enum E_PHONE_DATA
{
	ph_id,
	ph_col_panel, /// цвет корпуса
	ph_music, /// звук мелоди
	bool: ph_status, /// 0 - off | 1 - on
	ph_number, /// номер
	ph_paid_time, /// проплачено до
	ph_player_id,
	ph_call_index, /// кто вызывает
	ph_call_timer,
	ph_anogram_name						[MAX_PHONE_ANOGRAM_NAME],
	ph_radio
};
 
new phone_data							[MAX_PHONES][E_PHONE_DATA],
	phone_call_number					[MAX_PLAYERS][MAX_NUMBER_LENGTH];

	
Clear:phone_data(index)
{
	phone_data[index][ph_anogram_name][0] = EOS; 
	phone_data[index][ph_id] = 
	phone_data[index][ph_col_panel] = 
	phone_data[index][ph_paid_time] = 
	phone_data[index][ph_music] =
	phone_data[index][ph_radio] =
	phone_data[index][ph_number] = 0;
	phone_data[index][ph_status] = true;
	phone_data[index][ph_player_id] = INVALID_PLAYER_ID; 
	phone_data[index][ph_call_timer] = 
	phone_data[index][ph_call_index] = INVALID_PARAM;
	
	for (new i; i < MAX_CONTACTS; i++)
	{
		Clear:contact_data(index, i);
	}
}

Create:phone_data(const id, index, type, panel)
{	
	new number = (random(999_999 - 100_000) + 100_000),
		paid_time = gettime() + (60 * 60 * 24 * 7);
	
	format:g_string("INSERT INTO " #__PHONES " (\
		ph_col_panel, \
		ph_number, \
		ph_created_time, \
		ph_paid_time \
		) VALUES (\
		  %i, \
		  %i, \
		  %i, \
		  %i \
		)",
		panel,
		number,
		gettime(),
		paid_time
	);
	
	mysql_tquery(db, g_string, "OnPhoneCreate", "iiiiii", id, index, type, panel, number, paid_time);
}

function OnPhoneCreate(const id, index, type, panel, number, paid_time)
{	
	new phone_index = GetFreeIndexForPhone(),
		phone_db_id = cache_insert_id();
	
	if (phone_index == INVALID_PARAM)
	{
		printf("[OnPhoneCreate]: Error slot [%i, %i, %i]", id, index, type);
		return 1;
	}

	Clear:phone_data(phone_index);
	
	phone_data[phone_index][ph_id] = phone_db_id;
	phone_data[phone_index][ph_col_panel] = panel;
	phone_data[phone_index][ph_number] = number;
	phone_data[phone_index][ph_status] = true;
	phone_data[phone_index][ph_paid_time] = paid_time;
	
	if (type == TYPE_INV_PLAYER)
	{
		phone_data[phone_index][ph_player_id] = id;
	}
	
	SetInventoryEnumItem(id, index, type, inv_param_1, phone_db_id);
	Create:item_data(id, index, type);
	return 1;
}

Recreate:phone_data(const id, index, type, db_id)
{
	printf("[Recreate:phone_data] %d", db_id);
	new phone_index = GetPhoneIndexById(db_id);
	
	format:g_string("INSERT INTO " #__PHONES " (\
		ph_id, \
		ph_col_panel, \
		ph_number, \
		ph_status, \
		ph_created_time \
		) VALUES (\
		  %i, \
		  %i, \
		  %i, \
		  %i, \
		  %i \
		)",
		db_id,
		phone_data[phone_index][ph_col_panel],
		phone_data[phone_index][ph_number],
		phone_data[phone_index][ph_status],
		gettime()
	);
	
	mysql_tquery(db, g_string);
	
	if (type == TYPE_INV_PLAYER)
	{
		phone_data[phone_index][ph_player_id] = id;
	}
	
	SetInventoryEnumItem(id, index, type, inv_param_1, db_id);
	Create:item_data(id, index, type);
}

Update:phone_data(playerid, const index)
{	
	if (playerid != INVALID_PLAYER_ID)
	{
		if (!IsUserAllowQuery(playerid))
		{
			return;
		}
	}
	
	format:g_string("UPDATE " #__PHONES " \ 
		SET \
			ph_col_panel = %i, \
			ph_number = %i, \
			ph_status = %i, \
			ph_music = %i, \
			ph_paid_time = %i, \
			ph_anogram_name = '%q' \
		WHERE \
			ph_id = %i \
		LIMIT 1",
		phone_data[index][ph_col_panel],
		phone_data[index][ph_number],
		phone_data[index][ph_status],
		phone_data[index][ph_music],
		phone_data[index][ph_paid_time],
		phone_data[index][ph_anogram_name],
		GetPhoneId(index)
	);
	
	mysql_tquery(db, g_string, "OnPhoneDataUpdate", "d", playerid);
	
	if (playerid != INVALID_PLAYER_ID)
	{
		SetUserAllowQuery(playerid, false);
	}
}

function OnPhoneDataUpdate(playerid)
{
	if (playerid != INVALID_PLAYER_ID)
	{
		SetUserAllowQuery(playerid, true);
	}
	
	return 1;
}

Remove:phone_data(id, slot, type, fully = true, in_game = true)
{
	new index = GetPhoneIndexBySlot(id, slot, type);
	
	if (index == INVALID_PARAM)
	{
		printf("[ERROR]: Remove phone function, index is invalid param. (Slot: %i)",
			slot
		);
		
		return 0;
	}
	
	format:g_string("\
		DELETE i, p \
		FROM \
			" #__ITEMS " i \
		LEFT JOIN \
			" #__PHONES " p \
			ON (i.inv_param_1 = p.ph_id) \
		WHERE i.inv_id = %i",
		GetInventoryEnumItem(id, slot, type, inv_id)
	);
	
	mysql_pquery(db, g_string);	
	
	if (type == TYPE_INV_PLAYER)
	{
		if (IsPhoneShowed(id))
		{
			ShowPhoneTextDraw(id, false);
		}
		
		phone_data[index][ph_player_id] = INVALID_PLAYER_ID;
	}
	
	if (fully)
	{
		format:g_string("\
			DELETE c, m \
			FROM \
				" #__CONTACTS " c \
			LEFT JOIN \
				" #__MESSAGES " m \
				ON (c.pc_phone_id = m.pm_id) \
			WHERE c.pc_phone_id = %i",
			GetInventoryEnumItem(id, slot, type, inv_param_1)
		);
		
		mysql_tquery(db, g_string);
	}
	
	if (in_game)
	{
		Clear:phone_data(index);
	}
	
	return 1;
}