/*!
	@brief Система администрирования
	@author Found (evg.savosin)
	@date 16.12.2016
		
	Максимальное количество уровней: 5;
*/

// Defines	
#define GetAdminLevel(%0)		(admin_data[%0][a_level])
#define GetAdminPerm(%0,%1)		(admin_data[%0][a_perm][%1])

#define SetAdminPerm(%0,%1,%2)	(admin_data[%0][a_perm][%1]=%2)

#define IsAdminLogged(%0)		(admin_login{%0})
#define IsPlayerDeveloper(%0)	(CheckAdminAccess(%0, ADMIN_LEAD, ap_developer))	

// Constants
const MAX_ADMIN_LOGS = 50;

// Structures & Variables
enum 
{
	ADMIN_NONE,
	ADMIN_TRAINEE, // Стажер
	ADMIN_JUNIOR, // Младший
	ADMIN_NORMAL, // Обычный
	ADMIN_SENIOR, // Старший
	ADMIN_LEAD // Ведущий
};

enum E_ADMIN_PERMISSIONS
{
	ap_developer, // Привилегия разработчика;
	ap_manage_admins, // Управление администраторами;
	ap_manage_helpers,
	ap_property,
	ap_manage_fraction,
	ap_manage_crime,
	ap_capital
};

enum E_ADMIN_DATA
{
	a_level,
	a_ip						[	MAX_PLAYER_IP	 		],
	a_perm						[	E_ADMIN_PERMISSIONS	 	]
};

enum
{
	alog_user_name				[MAX_PLAYER_NAME],
	alog_character_name			[MAX_PLAYER_NAME],
	alog_killer_name			[MAX_PLAYER_NAME],
	alog_reason,
	alog_time_hour,
	alog_time_minute,
	alog_time_second,
	
	a_deathlog,
	a_dislog,
	
	LOG_SETTINGS
};

enum E_ADMIN_LOGS
{
	alog_death					[LOG_SETTINGS],
	alog_disconnect				[LOG_SETTINGS]
};


new admin_data					[	MAX_PLAYERS][	E_ADMIN_DATA	],
	admin_login					[	MAX_PLAYERS char	],
	is_admin_vehicle			[	MAX_VEHICLES char],
	
	Menu: admin_menu,
	
	admin_logs					[MAX_ADMIN_LOGS][E_ADMIN_LOGS];

// Function	
Clear:admin_data(playerid)
{	
	admin_login{playerid} = 0;
	ShowAdminLog(playerid, false);
	
	/// Clear permissions
	for (new E_ADMIN_PERMISSIONS: i; i < E_ADMIN_PERMISSIONS; i++)
	{
		SetAdminPerm(playerid, i, 0);
	}
	
	/// Integer
	admin_data[playerid][a_level] = 0;
	
	/// String
	admin_data[playerid][a_ip][0] = EOS;
}

stock Update:admin_int(playerid, column[], _: value)
{
	format:g_string("UPDATE " #__ADMINS " SET %s = %d WHERE a_user_id = %d LIMIT 1",
		column,
		value,
		GetUserId(playerid)
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:admin_string(playerid, column[], const value[])
{
	format:g_string("UPDATE " #__ADMINS " SET %s = '%q' WHERE a_user_id = %d LIMIT 1",
		column,
		value,
		GetUserId(playerid)
	);
	
	return mysql_tquery(db, g_string);
}