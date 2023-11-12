/*!
	@brief Файл с основной конфигурацией
	@author Found (evg.savosin)
	@date 16.12.2016
		
	Данная конфигурация содержит все самые необходимые
	параметры для изменения работоспособности игрового мода
*/

/// Base
#define __TIMEZONE							(3)

#if defined __DEBUG
	#define __RESTART_DELAY					(1)
#else 
	#define __RESTART_DELAY					(120) 
#endif

#define __VERSION							"FS 2.0 RC"
#define __AC_VERSION						"FuryAC 1.3"


#define __PROJECT_SITE					    "fury-rp.ru"
#define __PROJECT_NAME                      "Fury Role Play"

#if __ENV == DEV
    #define __SERVER_NAME					" | Development"
#elseif __ENV == TEST
    #define __SERVER_NAME                   " | Nemesis"    
#else
    #define __SERVER_NAME                   ""
#endif 

/// Tables
#define __USERS								"users"
#define __USETTINGS							"users_settings"
#define __CHARACTERS						"characters"
#define __CSETTINGS							"characters_settings"
#define __CKILL								"characters_kill"
#define __ADMINS							"admins"
#define __FRACTIONS							"fractions"
#define __FRACTIONS_RANK					"fractions_rank"
#define __FRACTIONS_UNIT					"fractions_unit"
#define __FRACTIONS_OBJECT					"fractions_object"
#define __FRACTIONS_ATTACH					"fractions_attach"
#define __FRACTIONS_ITEM					"fractions_item"
#define __HOUSES							"houses"
#define __HLODGER							"houses_lodger"
#define __HGARAGE							"houses_garage"
#define __PREMISES							"premises"
#define __ROOMS								"rooms"
#define __VEHICLES							"vehicles"
#define __BANS								"bans"
#define __HOSTELS							"hostels"
#define __IPBANS							"ipbans"
#define __ITEMS								"items"
#define __FURN								"furnitures"
#define __PHONES							"phones"
#define __CONTACTS							"phones_contact"
#define __CONVERSATIONS						"phones_conversation"
#define __MESSAGES							"phones_message"
#define __PHONES_ANOGRAM					"phones_anogram"
#define __SITES								"sites"
#define __SFAVORITE							"sites_favorite"
#define __ADVERTS							"adverts"
#define __CREDITS							"credits"
#define __LICENSES							"licenses"
#define __BUSINESSES						"businesses"
#define __BMEMBERS							"businesses_member"
#define __BASSORT							"businesses_assort"
#define __MUSIC								"music"
#define __CORPSES							"corpses"
#define __FUBER_TRIPS						"fuber_trips"
#define __DONATE							"donate"
#define __DONATE_ITEM						"donate_item"
#define __CRIMES							"crimes"
#define __CRIMES_MEMBER						"crimes_member"

#define __HASH_METHOD						"SHA2(MD5('_fs_%q'), 384)"

#define DATE_FORMAT							"%02d:%02d %02d.%02d.%04d"
#define DATE_FORMAT_S						"%02d:%02d:%02d %02d.%02d.%04d"

#define UNIXTIME_END						2114380800

/// Other
#define COST_RETEXTURE						(50)

#define PERCENT_RENT_HOUSE					0.07
#define PERCENT_RENT_VEHICLE				0.01
#define PERCENT_COMMUNAL_HOUSE				0.01

#define PERCENT_RENT_PREMISE				0.07
#define PERCENT_ELECTRIC_PREMISE			0.02
#define PERCENT_MIN_PROFIT_PREMISE			0.8

#define FACTOR_TELEPORT_RADIUS				1.3
#define FACTOR_TRADE_RADIUS					4.0
#define FACTOR_AFK_PAYDAY					(45) // Пропуск PayDay для игрока простоявшего минут

#define PICKUP_DRAW_DISTANCE				50.0 
#define PICKUP_MODEL						(19902)
#define TEXT3D_DRAW_DISTANCE				5.0

/// Position
#define POS_SPAWN							1574.5708, -1280.3445, 17.4922
#define POS_DEMORGAN						3958.6768, -942.3129, 3.8427

/// World and interiors
#define INT_HOUSE							(2)
#define INT_HOSTEL							(3)
#define INT_GARAGE							(4)
#define INT_PREMISE							(5)
#define INT_OTHER							(6)

#define WORLD_HOSTEL						(100_000)
#define WORLD_OTHER							(150_000)

/// Colors
#define C_PURPLE							(0xC2A2DAFF)
#define C_LIGHTRED          				(0xFF6347AA)
#define C_LIGHTGREEN 						(0x9ACD32AA)
#define C_YELLOW                			(0xFFFF00AA)
#define C_DARKYELLOW                   		(0xFFCC00AA)
#define C_GRAY 								(0xAFAFAFAA)
#define C_DARKGRAY              			(0x989898FF)
#define C_GREEN 							(0x5dbb5dFF)
#define C_PINK 								(0xE75480FF)
#define C_PROJECT 							(0x65d1d3FF) 
#define C_DARKRED							(0x8c2a2aff)
#define C_RED								(0xcf4e4eAA)
#define C_WHITE 							(0xFFFFFFFF)
#define C_GOLD 								(0xFFCC00FF)
#define C_LIGHTBLUE 						(0x5c90c5FF)
#define C_BLUE                  			(0x4682B4FF)
#define C_ORANGE                			(0xFF9945FF)
#define C_DARKORANGE             			(0xDEB047FF)
#define C_OPACITY_GRAY						(0xD0D0D0AA)
#define C_TEAM_DEFAULT						(0xFFFFFF00)

#define C_TD_BACKGROUND_FIRST				(0x1A2125FF)
#define C_TD_BACKGROUND_SECOND				(0x252E34FF)


#define COLOR_FADE1            				(0xE6E6E6E6)
#define COLOR_FADE2             			(0xC8C8C8C8)
#define COLOR_FADE3             			(0xAAAAAAAA)
#define COLOR_FADE4             			(0x8C8C8C8C)
#define COLOR_FADE5             			(0x6E6E6E6E)
 
#define cLIGHTRED          					"{FF6347}"
#define cLIGHTGREEN							"{9ACD32}"
#define cPURPLE								"{C2A2DA}"
#define cYELLOW                 			"{FFFF00}"
#define cGRAY                   			"{AFAFAF}"
#define cPINK                   			"{E75480}"
#define cWHITE                  			"{FFFFFF}"
#define cDARKYELLOW                   		"{FFCC00}"
#define cDARKGRAY              	 			"{989898}"
#define cLIGHTBLUE 							"{33CCFF}"
#define cBLUE                 				"{4682B4}"
#define cPROJECT                  			"{65d1d3}"
#define cRED								"{cf4e4e}"
#define cDARKRED							"{8c2a2a}"
#define cGREEN                				"{5dbb5d}"
#define cORANGE								"{FF9945}"
#define cDARKORANGE             			"{DEB047}"
#define cGOLD 								"{FFCC00}"

#define CI_DIALOG_CAPTION                   "{65d1d3}"
#define CI_DIALOG_INFO                      "{ffffff}"
#define CI_DIALOG_DELETE                    "{AA3333}"

/// Chat prefixes
#define ERROR 								"" #cRED "*" #cWHITE ""
#define SUCCESS								"" #cGREEN "*" #cWHITE ""
#define DEFAULT								"" #cGRAY "*" #cWHITE ""

#define HELPER_MESSAGE						"H >"
#define ADMIN_MESSAGE						"A >"
#define AC_MESSAGE							"FuryAC >"
#define SMS_MESSAGE							"SMS >"
#define PHONE_MESSAGE						"Телефон >"
#define ETHER_MESSAGE						"Эфир >"
#define FUBER_MESSAGE						"Fuber >"
#define VEHICLE_MESSAGE						"Транспорт >"
#define STREET_MESSAGE						"Улица >"
#define RADIO_MESSAGE						"CH: %i, S: %i >"
#define FRACTION_MESSAGE					"F >"
#define DEPARTMENT_MESSAGE					"D >"
				