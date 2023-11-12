/*!
	@brief Заголовок для системы бизнесов
	@author Found (evg.savosin)
	@date 23.04.2018
*/

// Defines
#define DIALOG_BUSINESS_MENU 	" \
Информация\n \
Закрыть компанию\
"

#define DIALOG_BUSINESS_MANAGE	" \
Информация\n \
Помещения\n \
Персонал\n \
Настройки\n \
Финансы\
"

#define DIALOG_BUSINESS_STAFF 	" \
Принять в компанию \n \
Исключить из компании \n \
Изменить привилегии\n \
Список всех сотрудников\
"

#define CREATE_BUSINESS_POS						395.1547, 1075.6742, 1103.5356

#define CREATE_BUSINESS_COST					1000

#define GetBusinessId(%0)						business_data[%0][b_id]
#define GetBusinessName(%0)						business_data[%0][b_name]
#define GetBusinessProfit(%0)					business_data[%0][b_profit]

// Structures
enum E_BUSINESS_DATA
{
	b_id,
	b_character_id,
	b_name					[	MAX_BUSINESS_NAME	],
	b_type,
	b_subtype,
	
	b_profit,
	b_profit_daily,
	b_profit_weekly,
	b_created_time
};

new business_data			[	MAX_BUSINESSES 		][		E_BUSINESS_DATA				],
	
	player_business			[	MAX_PLAYERS			][		MAX_PLAYER_BUSINESSES		];
	
	

Clear:business_data(index)
{
	/// Integer
	business_data[index][b_id] = 
	business_data[index][b_character_id] = 
	business_data[index][b_type] = 
	business_data[index][b_profit] = 
	business_data[index][b_profit_daily] = 
	business_data[index][b_profit_weekly] = 
	business_data[index][b_created_time] = 0;
	
	business_data[index][b_subtype] = INVALID_PARAM;
	
	/// String
	business_data[index][b_name][0] = EOS; 
}

Clear:player_business(playerid)
{
	player_business[playerid][0] = 
	player_business[playerid][1] = INVALID_PARAM;
}

stock Update:business_int(index, column[], _: value, bool: is_pquery = false)
{
	clean:<g_string>;
	
	format:g_string("UPDATE `"#__BUSINESSES"` SET `%s` = %d WHERE `b_id` = %d LIMIT 1",
		column,
		value,
		GetBusinessId(index)
	);
	
	return !is_pquery ? mysql_tquery(db, g_string) : mysql_pquery(db, g_string);
}

Create:business_data(playerid, index, type, name[])
{
	format:g_string("\
		INSERT INTO " #__BUSINESSES " \
			(b_character_id, b_name, b_type, b_created_time) \
		VALUES \
			(%i, '%q', %i, %i)",
		GetCharacterId(playerid),
		name,
		type,
		gettime()
	);
	
	mysql_tquery(db, g_string, "OnBusinessCreate", "iiis", playerid, index, type, name);
}

function OnBusinessCreate(playerid, index, type, name[])
{	
	business_data[index][b_id] = cache_insert_id();
	strcat(business_data[index][b_name], name, MAX_BUSINESS_NAME);
	business_data[index][b_character_id] = GetCharacterId(playerid);
	business_data[index][b_type] = type;
	business_data[index][b_subtype] = INVALID_PARAM;
	business_data[index][b_created_time] = gettime();
	
	GiveBusinessOwner(playerid, index);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно создали компанию. Привяжите её к помещению в течение 3 дней.");
	SendClientMessage(playerid, C_WHITE, !#DEFAULT " Для того, чтобы открыть список компаний, используйте " #cPROJECT "/bmenu" #cWHITE ".");
	return 1;
}