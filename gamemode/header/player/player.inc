/*!
	@brief Основной заголовок для системы игрока
	@author Found (evg.savosin)
	@date 16.12.2016, update 16.01.2018
	
	Здесь находятся макросы, константы, а также паттерны к диалогам.
*/

// Defines
#define DIALOG_IS_ONLINE 		"\
	" #ERROR " Авторизация\n\n\
	С данного аккаунта уже происходит игра на сервере.\n\
	Если это не Вы, то обратитесь на сайт - " #cPROJECT "" #__PROJECT_SITE "" #cWHITE ".\
"

#define DIALOG_RETEST 			"\
	" #ERROR " Авторизация\n\n\
	Ваш аккаунт был отправлен на повторное тестирование.\n\
	Пройти ретест можно на сайте - " #cPROJECT "" #__PROJECT_SITE "" #cWHITE ".\
"

#define DIALOG_DISABLED 		"\
	" #ERROR " Авторизация\n\n\
	Ваш аккаунт был отключён администрацией.\n\
	Свяжитесь с администрацией для подробностей - " #cPROJECT "" #__PROJECT_SITE "" #cWHITE ".\
"

#define DIALOG_REGISTER			"\
	" #DEFAULT " Авторизация\n\n\
	Добро пожаловать на " #cPROJECT "" #__PROJECT_NAME "" #cWHITE ".\n\
	Ваш аккаунт " #cGRAY "не зарегистрирован" #cWHITE " на сервере.\n\n\
	Для регистрации пройдите на сайт - " #cPROJECT "" #__PROJECT_SITE "" #cWHITE ".\
"

#define DIALOG_LOGIN			"\
	" #DEFAULT " Авторизация\n\n\
	Добро пожаловать на " #cPROJECT ""#__PROJECT_NAME"" #cWHITE ".\n\
	Ваш аккаунт " #cPROJECT "зарегистрирован" #cWHITE " на сервере.\n\n\
	Введите пароль ниже:\
"

#define DIALOG_GOOGLE_AUTH		"\
	" #DEFAULT " Двухфакторная аутентификация\n\n\
	Введите сгенерированный код из приложения:\
"

#define GetPlayerCurrentName(%0)		(player_temp_name[%0])
#define GetPlayerAfk(%0)				(player_afk[%0])

#define IsPlayerLogged(%0)				(IsPlayerConnected(%0) && user_login{%0} && user_data[%0][u_id] && character_data[%0][c_id])
#define IsPlayerLoggedForCMD(%0)		(%0 != INVALID_PLAYER_ID && user_login{%0} && user_data[%0][u_id] && character_data[%0][c_id])
#define IsPlayerLoggedforeach(%0)		(user_login{%0} && user_data[%0][u_id] && character_data[%0][c_id])
#define IsPlayerRegister(%0)			(user_data[%0][u_id] && IsPlayerConnected(%0))
#define IsPlayerAfk(%0)					((player_afk[%0] > 3) ? 1 : 0)
#define IsPlayerMuted(%0)				(user_data[%0][u_mute])
#define IsPlayerHelper(%0)				(user_data[%0][u_helper])
#define IsHelperLogged(%0)				(helper_login{%0})
#define IsPlayerLicenseExists(%0,%1)	(license_data[%0][%1][l_id] != 0)
#define IsPlayerKicked(%0)				(GetPVarInt(%0, "Player:IsKicked"))

// Structures
enum 
{
	TYPE_BAN_CHARACTER = 1,
	TYPE_BAN_USER
}

// Variables
new	player_temp_name					[MAX_PLAYERS][MAX_PLAYER_NAME],
	player_speedometer					[MAX_PLAYERS],
	player_afk							[MAX_PLAYERS],
	bool: player_spectate				[MAX_PLAYERS char],
	player_gps							[MAX_PLAYERS char],
	player_dialog_id					[MAX_PLAYERS],
	helper_login						[MAX_PLAYERS char];

	
// Functions
Clear:player_data(playerid, bool: is_relogin = false)
{
    Clear:user_data(playerid, is_relogin);
    Clear:admin_data(playerid);
	Clear:donate(playerid);
	Clear:character_data(playerid);
	Clear:lod_data(playerid);
	Clear:anticheat(playerid);
	Clear:inv_data(playerid);
	Clear:ren_data(playerid);
	Clear:call_data(playerid);
	Clear:credit_data(playerid);
	Clear:all_license_data(playerid);
	Clear:bmember_data(playerid);
	Clear:armour_data(playerid);
	Clear:death_data(playerid);
	
	Clear:player_vehicle(playerid);
	Clear:player_house(playerid);
	Clear:player_premise(playerid);
	Clear:player_site(playerid);
	Clear:player_business(playerid);
	Clear:player_fuber(playerid);
	
	Clear:site_fav_select(playerid);
	Clear:site_adv_select(playerid);
	
	// Other var
    if (!is_relogin)
    {
        player_temp_name[playerid][0] = EOS;
    }

    helper_login{playerid} = 0;
	player_afk[playerid] =
	player_spectate{playerid} = false;
	player_speedometer[playerid] = INVALID_PARAM;
	
	player_dialog_id[playerid] = INVALID_DIALOG_ID;
	
	// PVar
	SetPVarInt(playerid, "Player:Lead", INVALID_PLAYER_ID);
	SetPVarInt(playerid, "Player:Follow", INVALID_PLAYER_ID);
}