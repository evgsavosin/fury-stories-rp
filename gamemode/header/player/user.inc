/*!
	@brief Основной заголовок для системы глобального аккаунта
	@author Found (evg.savosin)
	@date 16.12.2016, update 16.01.2018
*/

// Defines
#define GetUserId(%0)					(user_data[%0][u_id])
#define GetUserName(%0)					(user_data[%0][u_name])
#define GetUserIp(%0)					(user_data[%0][u_ip])
#define GetUserVip(%0)					(user_data[%0][u_vip])
#define GetUserWarn(%0)					(user_data[%0][u_warn])
#define GetUserSettings(%0,%1)			(user_data[%0][u_settings][%1])
#define GetUserVipEndDayCount(%0) 		floatround((((user_data[%0][u_vip_time]+(60*60*24*30))-gettime())/(60 * 60 * 24)))

#define SetUserSettings(%0,%1,%2)		(user_data[%0][u_settings][%1]=%2)
#define ClearUserSettings(%0,%1)		(user_data[%0][u_settings][%1][0]=EOS)

#define IsUserLogged(%0)                user_login{%0}
#define IsUserAllowQuery(%0)			user_allow_query{%0}
#define SetUserAllowQuery(%0,%1)		user_allow_query{%0}=%1

#define IsUserVip(%0)					(user_data[%0][u_vip] > 0)

// Constants
const MAX_GOOGLE_AUTH = 17;

const MAX_USER_WARNS = 5;

// Structures
enum E_USER_SETTINGS /// Настройки аккаунта
{
	SET_INVENTORY, // тип инвентаря
	SET_VISIBLE_OBJECT, // прорисовка объектов
	SET_VISIBLE_PICKUP, // отображение пикапов
	SET_ADMIN_MESSAGE, // сообщения администратора
	SET_PM_MESSAGE, // личные сообщения
	SET_B_MESSAGE, // /b сообщения
	SET_DESIGN, /// оформление
	SET_LOGO, // логотип
	SET_VISIBLE_NAMES, // отображение ников
	
	// Безопасность
	SET_GOOGLE_AUTH				[MAX_GOOGLE_AUTH], // гугл-аутентификатор
};

enum
{
	USER_ACTIVE = 0,
	USER_RETEST,
	USER_DISABLED
}

enum E_USER_DATA 
{
	u_id,
	u_name						[MAX_PLAYER_NAME],
	u_email						[MAX_PLAYER_EMAIL],
	u_mute,
	u_warn,
	u_register_time,
	u_last_time,
	u_reg_ip					[MAX_PLAYER_IP],
	u_last_ip					[MAX_PLAYER_IP],
	u_ip						[MAX_PLAYER_IP],
	u_cash_action, /// unix дата последних денежных действий,
	u_helper,
	u_settings					[E_USER_SETTINGS],
	u_vip,
	u_vip_time
};

new user_data					[MAX_PLAYERS][E_USER_DATA],
	user_login					[MAX_PLAYERS char],
	user_allow_query			[MAX_PLAYERS char];

Clear:user_data(playerid, bool: is_relogin = false)
{	
	user_login{playerid} = false;
	user_allow_query{playerid} = true;

    if (is_relogin)
    {
        return;
    }
    
    Clear:user_settings(playerid);

	/// Integer
	user_data[playerid][u_id] =
	user_data[playerid][u_mute] =
	user_data[playerid][u_warn] = 
	user_data[playerid][u_cash_action] =
	user_data[playerid][u_register_time] =
	user_data[playerid][u_vip] =
	user_data[playerid][u_vip_time] =
	user_data[playerid][u_last_time] = 0;
	
	/// String
    user_data[playerid][u_name][0] = 
	user_data[playerid][u_email][0] = 
	user_data[playerid][u_reg_ip][0] = 
	user_data[playerid][u_last_ip][0] = 
	user_data[playerid][u_ip][0] = EOS;
	
	/// Float
}

stock Update:user_int(playerid, column[], _: value)
{
	format:g_string("UPDATE " #__USERS " SET %s = %i WHERE u_id = %i LIMIT 1",
		column,
		value,
		GetUserId(playerid)
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:user_string(playerid, column[], const value[], bool: quotes = true)
{
	format:g_string("UPDATE " #__USERS " SET %s = %s%q%s WHERE u_id = %i LIMIT 1",
		column,
		quotes ? ("'") : (""),
		value,
		quotes ? ("'") : (""),
		GetUserId(playerid)
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:user_float(playerid, column[], Float: value)
{
	format:g_string("UPDATE " #__USERS " SET %s = %f WHERE u_id = %i LIMIT 1",
		column,
		value,
		GetUserId(playerid)
	);
	
	return mysql_tquery(db, g_string);
}

Clear:user_settings(playerid)
{
	SetUserSettings(playerid, SET_VISIBLE_OBJECT, MAX_VISIBLE_OBJECTS);
	SetUserSettings(playerid, SET_B_MESSAGE, 1);
	SetUserSettings(playerid, SET_LOGO, 1);
	SetUserSettings(playerid, SET_VISIBLE_NAMES, 1);
	SetUserSettings(playerid, SET_PM_MESSAGE, 1);
	SetUserSettings(playerid, SET_ADMIN_MESSAGE, 1);
	SetUserSettings(playerid, SET_DESIGN, 1);
	SetUserSettings(playerid, SET_VISIBLE_PICKUP, 1);
	SetUserSettings(playerid, SET_INVENTORY, 0);
	
	ClearUserSettings(playerid, SET_GOOGLE_AUTH);
}

Update:user_settings(playerid)
{
	if (!IsUserAllowQuery(playerid))
	{
		return;
	}
	
	format:g_string("\
		UPDATE " #__USETTINGS " \
		SET \
			set_inventory = %d, \
			set_visible_object = %d, \
			set_visible_pickup = %d, \
			set_admin_message = %d, \
			set_pm_message = %d, \
			set_b_message = %d, \
			set_design = %d, \
			set_google_auth = '%q', \
			set_logo = %d, \
			set_visible_names = %d \
		WHERE \
			set_user_id = %d \
		LIMIT 1",
		GetUserSettings(playerid, SET_INVENTORY),
		GetUserSettings(playerid, SET_VISIBLE_OBJECT),
		GetUserSettings(playerid, SET_VISIBLE_PICKUP),
		GetUserSettings(playerid, SET_ADMIN_MESSAGE),
		GetUserSettings(playerid, SET_PM_MESSAGE),
		GetUserSettings(playerid, SET_B_MESSAGE),
		GetUserSettings(playerid, SET_DESIGN),
		GetUserSettings(playerid, SET_GOOGLE_AUTH),
		GetUserSettings(playerid, SET_LOGO),
		GetUserSettings(playerid, SET_VISIBLE_NAMES),
		GetUserId(playerid)
	);
	
	mysql_tquery(db, g_string, "OnUserSettingsUpdate", "d", playerid);
	
	SetUserAllowQuery(playerid, false);
}

function OnUserSettingsUpdate(playerid)
{
	SetUserAllowQuery(playerid, true);
	return 1;
}