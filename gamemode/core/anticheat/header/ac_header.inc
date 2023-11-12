/*!
	@brief Античит (FuryAC) - Заголовок
	@author Found (evg.savosin)
	@date 12.05.2019
*/

// Define
#define isnan(%0)						%0!=%0		

#define IsAntiCheatAdmin(%0)			CheckAdminAccess(%0,ADMIN_JUNIOR)	
#define IsAntiCheatValidCode(%0)		(0<=%0<MAX_ANTICHEAT_LIST)

#define IsPlayerSpectated(%0)			ac_player_data[%0][ac_is_spectated]


#define GetAntiCheatData(%0,%1)			anticheat_list[%0][%1]
#define SetAntiCheatData(%0,%1,%2)		anticheat_list[%0][%1]=%2

#define CheckAntiCheatTimeout(%0,%1) 	(ac_player_data[%0][ac_tick] > (ac_player_data[%0][ac_timeout_tick][%1] + ac_player_data[%0][ac_ping]))

#define GetAntiCheatPunishText(%0)		anticheat_punish_list[GetAntiCheatData(%0,ac_type_punish)]

// List 
#define ID_PLAYER_SYNC: 				a_207
#define ID_MARKERS_SYNC: 				b_208
#define ID_UNOCCUPIED_SYNC: 			c_209
#define ID_TRAILER_SYNC: 				d_210
#define ID_PASSENGER_SYNC: 				e_211
#define ID_SPECTATOR_SYNC: 				f_212
#define ID_AIM_SYNC: 					c_203
#define ID_VEHICLE_SYNC: 				x_200
#define ID_RCON_COMMAND: 				z_201
#define ID_RCON_RESPONCE: 				y_202
#define ID_WEAPONS_UPDATE: 				u_204
#define ID_STATS_UPDATE: 				i_205
#define ID_BULLET_SYNC: 				p_206

// Settings
#define __AC_REPORTING_ALL				(2)
#define __AC_REPORTING_WARNING			(1)
#define __AC_REPORTING_OFF				(0)

#if !defined INVALID_PARAM
	#define INVALID_PARAM				(-1)
#endif

#if !defined __AC_DEBUG
	#define __AC_DEBUG					__AC_REPORTING_WARNING
#endif

#if !defined AC_MESSAGE
	#define AC_MESSAGE 					"// FuryAC >"
#endif

#if !defined __AC_VERSION
	#define __AC_VERSION				"FuryAC 1.0"
#endif

#define AC_DIALOG						D_ANTICHEAT


// Constants 

// Задержка уведомления в секундах
const AC_WARNING_TIMEOUT = 4;

// Количество античитов на одной странице
const AC_DIALOG_ITEM_LIST = 18;

// Количество сохраняемых позиций
const AC_POSITION_COUNT = 3;

// Invalid RPC ID
const INVALID_RPC_ID = 0;

// Предупреждения
const AC_WARNING_WEAPON_HACK = 2;
const AC_DIFF_AMMO_HACK = 3;