/*!
	@brief Текстдравы телефона
	@author Found (evg.savosin)
	@date 25.11.2019
*/

// Defines
#define TD_PHONE_DESKTOP_ARRAY			(4)
#define TD_PHONE_ACTION_CALL			(2)
#define TD_PHONE_ITEM_LIST				(6)

#define PH_ITEM_BUTTON					(5)

// Structures
enum 
{
	PH_COLOR_BLACK,
	PH_COLOR_GREY,
	PH_COLOR_GOLD,
	PH_COLOR_PINK,
};

enum E_PHONE_COLOR
{
	pc_color_int,
	pc_color							[	7	],
	pc_color_name						[	13 	],
};

new const panel_color_list					[	][	E_PHONE_COLOR	] =
{
	{0x000000FF, "000000", "Черный"},
	{0x565656FF, "565656", "Серебряный"},
	{0x8a6518FF, "8a6518", "Золотой"},
	{0x7d4641FF, "7d4641", "Розовый"}
};

/// Тип action call
enum
{
	PH_INCOMING_CALL, // Входящий
	PH_OUTGOING_CALL, // Исходящий
	PH_ACTION_CALL
};

/// Начальный и конечный индекс в массиве item_list
enum 
{
	PH_ITEM_NAME_BEGIN = 0,
	PH_ITEM_NAME_END = 4,
};

enum 
{
	PH_ITEM_AVA_BEGIN = 2,
	PH_ITEM_AVA_END = 6,
};

/// Статичные элементы вверха
enum 
{
	PH_HEAD_START = 6,
	PH_HEAD_END = 10
};

/// Элементы кастомизации
enum 
{
	CLICK_PH_CALL = 4,
	CLICK_PH_SMS,
	CLICK_PH_WEB,
	CLICK_PH_APPS,
	CLICK_PH_BANK = 10
};

new Text: td_phone_static				[	16	 ],
	Text: td_phone_panel				[  12   ],
	Text: td_phone_head_time,
	Text: td_phone_breadcrumb,
	Text: td_phone_offline,
	
	Text: td_phone_desktop				[	17 	 ], /// Основная страница
	Text: td_phone_call					[	14	 ], /// Набор номера
	Text: td_phone_action_call			[	3	 ], /// Страница входящих/исходящих звонков
	Text: td_phone_item_list			[	7	 ], /// Контакты, беседы

	/// Основные элементы 
	PlayerText: ptd_phone_breadcrumb	[	MAX_PLAYERS		],
	PlayerText: ptd_phone_call_input	[	MAX_PLAYERS		],
	
	PlayerText: ptd_phone_desktop		[	MAX_PLAYERS		][	 TD_PHONE_DESKTOP_ARRAY ],
	PlayerText: ptd_phone_action_call	[	MAX_PLAYERS		][	 TD_PHONE_ACTION_CALL	],
	PlayerText: ptd_phone_item_list		[	MAX_PLAYERS		][ TD_PHONE_ITEM_LIST 	];

// Functions
TD_Global_Phone()
{
	/*!
		
		@brief Основные статичные элементы
	
	*/
	TD_Panel_Phone();
	
	td_phone_offline = TextDrawCreate(511.835693, 241.933334, "box"); // Offline Background 
	TextDrawLetterSize(td_phone_offline, 0.000000, 15.577008);
	TextDrawTextSize(td_phone_offline, 593.389892, 0.000000);
	TextDrawAlignment(td_phone_offline, 1);
	TextDrawColor(td_phone_offline, -1061109505);
	TextDrawUseBox(td_phone_offline, 1);
	TextDrawBoxColor(td_phone_offline, 0x1b1b1bFF);
	TextDrawSetShadow(td_phone_offline, 0);
	TextDrawSetOutline(td_phone_offline, 0);
	TextDrawBackgroundColor(td_phone_offline, 0x1b1b1bFF);
	TextDrawFont(td_phone_offline, 1);
	TextDrawSetProportional(td_phone_offline, 1);
	TextDrawSetShadow(td_phone_offline, 0);

	
	td_phone_static[0] = TextDrawCreate(511.835693, 241.933334, "box"); // Background 
	TextDrawLetterSize(td_phone_static[0], 0.000000, 15.577008);
	TextDrawTextSize(td_phone_static[0], 593.389892, 0.000000);
	TextDrawAlignment(td_phone_static[0], 1);
	TextDrawColor(td_phone_static[0], -1061109505);
	TextDrawUseBox(td_phone_static[0], 1);
	TextDrawBoxColor(td_phone_static[0], -908398081);
	TextDrawSetShadow(td_phone_static[0], 0);
	TextDrawSetOutline(td_phone_static[0], 0);
	TextDrawBackgroundColor(td_phone_static[0], 255);
	TextDrawFont(td_phone_static[0], 1);
	TextDrawSetProportional(td_phone_static[0], 1);
	TextDrawSetShadow(td_phone_static[0], 0);

	/// Вверх
	td_phone_static[1] = TextDrawCreate(511.835693, 241.933334, "box"); // Top Header 
	TextDrawLetterSize(td_phone_static[1], 0.000000, 0.706412);
	TextDrawTextSize(td_phone_static[1], 593.250185, 0.000000);
	TextDrawAlignment(td_phone_static[1], 1);
	TextDrawColor(td_phone_static[1], -2139062017);
	TextDrawUseBox(td_phone_static[1], 1);
	TextDrawBoxColor(td_phone_static[1], 2074607615);
	TextDrawSetShadow(td_phone_static[1], 0);
	TextDrawSetOutline(td_phone_static[1], 0);
	TextDrawBackgroundColor(td_phone_static[1], 255);
	TextDrawFont(td_phone_static[1], 1);
	TextDrawSetProportional(td_phone_static[1], 1);
	TextDrawSetShadow(td_phone_static[1], 0);
	
	/// Breadcrumb - Хлебные крошки
	td_phone_static[2] = TextDrawCreate(511.835693, 251.500005, "box"); // breadcrumb 
	TextDrawLetterSize(td_phone_static[2], 0.000000, 1.596416);
	TextDrawTextSize(td_phone_static[2], 593.250185, 0.000000);
	TextDrawAlignment(td_phone_static[2], 1);
	TextDrawColor(td_phone_static[2], -2139062017);
	TextDrawUseBox(td_phone_static[2], 1);
	TextDrawBoxColor(td_phone_static[2], 1502004479);
	TextDrawSetShadow(td_phone_static[2], 0);
	TextDrawSetOutline(td_phone_static[2], 0);
	TextDrawBackgroundColor(td_phone_static[2], 255);
	TextDrawFont(td_phone_static[2], 1);
	TextDrawSetProportional(td_phone_static[2], 1);
	TextDrawSetShadow(td_phone_static[2], 0);

	td_phone_static[3] = TextDrawCreate(569.116821, 219.083389, "LD_BEAT:chit"); // Bread 
	TextDrawLetterSize(td_phone_static[3], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_static[3], 3.279999, 3.879976);
	TextDrawAlignment(td_phone_static[3], 1);
	TextDrawColor(td_phone_static[3], 16711711);
	TextDrawSetShadow(td_phone_static[3], 0);
	TextDrawSetOutline(td_phone_static[3], 0);
	TextDrawBackgroundColor(td_phone_static[3], 255);
	TextDrawFont(td_phone_static[3], 4);
	TextDrawSetProportional(td_phone_static[3], 0);
	TextDrawSetShadow(td_phone_static[3], 0);

	td_phone_static[4] = TextDrawCreate(536.529602, 221.683319, "box"); // Bread 
	TextDrawLetterSize(td_phone_static[4], 0.000000, -0.095706);
	TextDrawTextSize(td_phone_static[4], 539.000000, 0.000000);
	TextDrawAlignment(td_phone_static[4], 1);
	TextDrawColor(td_phone_static[4], -206);
	TextDrawUseBox(td_phone_static[4], 1);
	TextDrawBoxColor(td_phone_static[4], -232);
	TextDrawSetShadow(td_phone_static[4], 0);
	TextDrawSetOutline(td_phone_static[4], 0);
	TextDrawBackgroundColor(td_phone_static[4], 40);
	TextDrawFont(td_phone_static[4], 1);
	TextDrawSetProportional(td_phone_static[4], 1);
	TextDrawSetShadow(td_phone_static[4], 0);

	td_phone_static[5] = TextDrawCreate(553.311950, 394.949554, "box"); // Bread 
	TextDrawLetterSize(td_phone_static[5], 0.000000, -0.305884);
	TextDrawTextSize(td_phone_static[5], 559.000000, 0.000000);
	TextDrawAlignment(td_phone_static[5], 1);
	TextDrawColor(td_phone_static[5], -1);
	TextDrawUseBox(td_phone_static[5], 1);
	TextDrawBoxColor(td_phone_static[5], -233);
	TextDrawSetShadow(td_phone_static[5], 0);
	TextDrawSetOutline(td_phone_static[5], 0);
	TextDrawBackgroundColor(td_phone_static[5], 255);
	TextDrawFont(td_phone_static[5], 1);
	TextDrawSetProportional(td_phone_static[5], 1);
	TextDrawSetShadow(td_phone_static[5], 0);

	td_phone_static[6] = TextDrawCreate(508.352844, 216.283416, "box"); // Grey Line 1 6
	TextDrawLetterSize(td_phone_static[6 ], 0.000000, 20.605564);
	TextDrawTextSize(td_phone_static[6 ], 505.000000, 0.000000);
	TextDrawAlignment(td_phone_static[6 ], 1);
	TextDrawColor(td_phone_static[6 ], -1);
	TextDrawUseBox(td_phone_static[6 ], 1);
	TextDrawBoxColor(td_phone_static[6 ], -2139062017);
	TextDrawSetShadow(td_phone_static[6 ], 0);
	TextDrawSetOutline(td_phone_static[6 ], 0);
	TextDrawBackgroundColor(td_phone_static[6 ], 255);
	TextDrawFont(td_phone_static[6 ], 1);
	TextDrawSetProportional(td_phone_static[6 ], 1);
	TextDrawSetShadow(td_phone_static[6 ], 0);

	td_phone_static[7] = TextDrawCreate(508.823486, 405.866790, "box"); // Grey Line 2 7
	TextDrawLetterSize(td_phone_static[7], 0.000000, -0.476797);
	TextDrawTextSize(td_phone_static[7], 597.197265, 0.000000);
	TextDrawAlignment(td_phone_static[7], 1);
	TextDrawColor(td_phone_static[7], -1);
	TextDrawUseBox(td_phone_static[7], 1);
	TextDrawBoxColor(td_phone_static[7], -2139062209);
	TextDrawSetShadow(td_phone_static[7], 0);
	TextDrawSetOutline(td_phone_static[7], 0);
	TextDrawBackgroundColor(td_phone_static[7], 255);
	TextDrawFont(td_phone_static[7], 1);
	TextDrawSetProportional(td_phone_static[7], 1);
	TextDrawSetShadow(td_phone_static[7], 0);
	
	td_phone_static[8] = TextDrawCreate(573.852905, 246.166580, "box"); // Head Battery 8
	TextDrawLetterSize(td_phone_static[8], 0.000000, -0.177824);
	TextDrawTextSize(td_phone_static[8], 575.199707, 0.000000);
	TextDrawAlignment(td_phone_static[8], 1);
	TextDrawColor(td_phone_static[8], -1);
	TextDrawUseBox(td_phone_static[8], 1);
	TextDrawBoxColor(td_phone_static[8], -1);
	TextDrawSetShadow(td_phone_static[8], 0);
	TextDrawSetOutline(td_phone_static[8], 0);
	TextDrawBackgroundColor(td_phone_static[8], 255);
	TextDrawFont(td_phone_static[8], 1);
	TextDrawSetProportional(td_phone_static[8], 1);
	TextDrawSetShadow(td_phone_static[8], 0);

	td_phone_static[9] = TextDrawCreate(570.487915, 245.116638, "box"); // Head Internet 1 10
	TextDrawLetterSize(td_phone_static[9], 0.000000, 0.023351);
	TextDrawTextSize(td_phone_static[9], 567.759399, 0.000000);
	TextDrawAlignment(td_phone_static[9], 1);
	TextDrawColor(td_phone_static[9], -1);
	TextDrawUseBox(td_phone_static[9], 1);
	TextDrawBoxColor(td_phone_static[9], -1);
	TextDrawSetShadow(td_phone_static[9], 0);
	TextDrawSetOutline(td_phone_static[9], 0);
	TextDrawBackgroundColor(td_phone_static[9], 255);
	TextDrawFont(td_phone_static[9], 1);
	TextDrawSetProportional(td_phone_static[9], 1);
	TextDrawSetShadow(td_phone_static[9], 0);
	
	td_phone_static[10] = TextDrawCreate(568.488403, 246.516723, "box"); // Head Internet 0 9
	TextDrawLetterSize(td_phone_static[10], 0.000000, -0.147648);
	TextDrawTextSize(td_phone_static[10], 565.759887, 0.000000);
	TextDrawAlignment(td_phone_static[10], 1);
	TextDrawColor(td_phone_static[10], -1);
	TextDrawUseBox(td_phone_static[10], 1);
	TextDrawBoxColor(td_phone_static[10], -1);
	TextDrawSetOutline(td_phone_static[10], 0);
	TextDrawBackgroundColor(td_phone_static[10], 255);
	TextDrawFont(td_phone_static[10], 1);
	TextDrawSetProportional(td_phone_static[10], 1);
	TextDrawSetShadow(td_phone_static[10], 0);

	td_phone_static[11] = TextDrawCreate(566.488891, 247.716796, "box"); // Head Internet 2  11
	TextDrawLetterSize(td_phone_static[11], 0.000000, -0.285647);
	TextDrawTextSize(td_phone_static[11], 563.760375, 0.000000);
	TextDrawAlignment(td_phone_static[11], 1);
	TextDrawColor(td_phone_static[11], -1);
	TextDrawUseBox(td_phone_static[11], 1);
	TextDrawBoxColor(td_phone_static[11], -1);
	TextDrawSetOutline(td_phone_static[11], 0);
	TextDrawBackgroundColor(td_phone_static[11], 255);
	TextDrawFont(td_phone_static[11], 1);
	TextDrawSetProportional(td_phone_static[11], 1);
	TextDrawSetShadow(td_phone_static[11], 0);

	td_phone_static[12] = TextDrawCreate(514.268981, 241.433380, "b"); // Head Bluetouch 12
	TextDrawLetterSize(td_phone_static[12], 0.128940, 0.771664);
	TextDrawAlignment(td_phone_static[12], 1);
	TextDrawColor(td_phone_static[12], -1);
	TextDrawSetOutline(td_phone_static[12], 0);
	TextDrawBackgroundColor(td_phone_static[12], 255);
	TextDrawFont(td_phone_static[12], 2);
	TextDrawSetProportional(td_phone_static[12], 1);
	TextDrawSetShadow(td_phone_static[12], 0);

	td_phone_static[13] = TextDrawCreate(546.253234, 222.282943, "box"); // Bread 
	TextDrawLetterSize(td_phone_static[13], 0.000000, -0.305884);
	TextDrawTextSize(td_phone_static[13], 562.500854, 0.000000);
	TextDrawAlignment(td_phone_static[13], 1);
	TextDrawColor(td_phone_static[13], -1);
	TextDrawUseBox(td_phone_static[13], 1);
	TextDrawBoxColor(td_phone_static[13], -225);
	TextDrawSetOutline(td_phone_static[13], 0);
	TextDrawBackgroundColor(td_phone_static[13], 255);
	TextDrawFont(td_phone_static[13], 1);
	TextDrawSetProportional(td_phone_static[13], 1);
	TextDrawSetShadow(td_phone_static[13], 0);
	
	td_phone_static[14] = TextDrawCreate(546.292785, 225.516708, "--------"); // Bread 
	TextDrawLetterSize(td_phone_static[14], 0.165176, 0.584999);
	TextDrawAlignment(td_phone_static[14], 1);
	TextDrawColor(td_phone_static[14], -112);
	TextDrawSetOutline(td_phone_static[14], 0);
	TextDrawBackgroundColor(td_phone_static[14], 255);
	TextDrawFont(td_phone_static[14], 2);
	TextDrawSetProportional(td_phone_static[14], 1);
	TextDrawSetShadow(td_phone_static[14], 0);

	td_phone_static[15] = TextDrawCreate(567.117309, 217.883316, "LD_BEAT:chit"); // Bread 
	TextDrawLetterSize(td_phone_static[15], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_static[15], 7.000000, 6.000000);
	TextDrawAlignment(td_phone_static[15], 1);
	TextDrawColor(td_phone_static[15], -220);
	TextDrawSetOutline(td_phone_static[15], 0);
	TextDrawBackgroundColor(td_phone_static[15], 255);
	TextDrawFont(td_phone_static[15], 4);
	TextDrawSetProportional(td_phone_static[15], 0);
	TextDrawSetShadow(td_phone_static[15], 0);
	
	/// Вверх
	td_phone_head_time = TextDrawCreate(579.551208, 242.016677, "17:15"); // Top Time 
	TextDrawLetterSize(td_phone_head_time, 0.119056, 0.643333);
	TextDrawAlignment(td_phone_head_time, 1);
	TextDrawColor(td_phone_head_time, -1);
	TextDrawSetOutline(td_phone_head_time, 0);
	TextDrawBackgroundColor(td_phone_head_time, 255);
	TextDrawFont(td_phone_head_time, 2);
	TextDrawSetProportional(td_phone_head_time, 1);
	TextDrawSetShadow(td_phone_head_time, 0);
	
	/*!
		
		@brief Элементы для страницы: Desktop
	
	*/
	
	/// Поисковая строка GOG
	td_phone_desktop[0] = TextDrawCreate(516.713500, 273.150024, "box"); // GOG Search Box 
	TextDrawLetterSize(td_phone_desktop[0], 0.000000, 1.105880);
	TextDrawTextSize(td_phone_desktop[0], 588.100463, 0.000000);
	TextDrawAlignment(td_phone_desktop[0], 1);
	TextDrawColor(td_phone_desktop[0], -1);
	TextDrawUseBox(td_phone_desktop[0], 1);
	TextDrawBoxColor(td_phone_desktop[0], -1);
	TextDrawSetOutline(td_phone_desktop[0], 0);
	TextDrawBackgroundColor(td_phone_desktop[0], 255);
	TextDrawFont(td_phone_desktop[0], 1);
	TextDrawSetProportional(td_phone_desktop[0], 1);
	TextDrawSetShadow(td_phone_desktop[0], 0);

	td_phone_desktop[1] = TextDrawCreate(520.536621, 274.150085, "G"); // Gog Icon
	TextDrawLetterSize(td_phone_desktop[1], 0.148230, 0.876666);
	TextDrawAlignment(td_phone_desktop[1], 2);
	TextDrawColor(td_phone_desktop[1], -1061109505);
	TextDrawSetOutline(td_phone_desktop[1], 0);
	TextDrawBackgroundColor(td_phone_desktop[1], 255);
	TextDrawFont(td_phone_desktop[1], 2);
	TextDrawSetProportional(td_phone_desktop[1], 1);
	TextDrawSetShadow(td_phone_desktop[1], 0);
	
	td_phone_desktop[2] = TextDrawCreate(579.041076, 272.616638, "O"); // GOG Search Button 1
	TextDrawLetterSize(td_phone_desktop[2], 0.158588, 0.800831);
	TextDrawAlignment(td_phone_desktop[2], 1);
	TextDrawColor(td_phone_desktop[2], -1061109505);
	TextDrawSetOutline(td_phone_desktop[2], 0);
	TextDrawBackgroundColor(td_phone_desktop[2], 255);
	TextDrawFont(td_phone_desktop[2], 1);
	TextDrawSetProportional(td_phone_desktop[2], 1);
	TextDrawSetShadow(td_phone_desktop[2], 0);
	
	td_phone_desktop[3] = TextDrawCreate(585.188049, 276.383209, "/"); // GOG Search Button 2
	TextDrawLetterSize(td_phone_desktop[3], -0.286588, 0.561662);
	TextDrawAlignment(td_phone_desktop[3], 1);
	TextDrawColor(td_phone_desktop[3], -1061109505);
	TextDrawSetOutline(td_phone_desktop[3], 0);
	TextDrawBackgroundColor(td_phone_desktop[3], 255);
	TextDrawFont(td_phone_desktop[3], 1);
	TextDrawSetProportional(td_phone_desktop[3], 1);
	TextDrawSetShadow(td_phone_desktop[3], 0);
	
	/// Иконки для доступа к call, sms, web, apps
	
	td_phone_desktop[4] = TextDrawCreate(517.705871, 353.066040, "LD_SPAC:white"); // Call 
	TextDrawLetterSize(td_phone_desktop[4], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_desktop[4], 12.000000, 13.000000);
	TextDrawAlignment(td_phone_desktop[4], 1);
	TextDrawColor(td_phone_desktop[4], -1665415169);
	TextDrawSetOutline(td_phone_desktop[4], 0);
	TextDrawBackgroundColor(td_phone_desktop[4], 255);
	TextDrawFont(td_phone_desktop[4], 4);
	TextDrawSetProportional(td_phone_desktop[4], 0);
	TextDrawSetShadow(td_phone_desktop[4], 0);
	TextDrawSetSelectable(td_phone_desktop[4], true);

	td_phone_desktop[5] = TextDrawCreate(536.901184, 353.066040, "LD_SPAC:white"); // SMS 
	TextDrawLetterSize(td_phone_desktop[5], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_desktop[5], 12.000000, 13.000000);
	TextDrawAlignment(td_phone_desktop[5], 1);
	TextDrawColor(td_phone_desktop[5], -1667315713);
	TextDrawSetOutline(td_phone_desktop[5], 0);
	TextDrawBackgroundColor(td_phone_desktop[5], 255);
	TextDrawFont(td_phone_desktop[5], 4);
	TextDrawSetProportional(td_phone_desktop[5], 0);
	TextDrawSetShadow(td_phone_desktop[5], 0);
	TextDrawSetSelectable(td_phone_desktop[5], true);

	td_phone_desktop[6] = TextDrawCreate(555.296691, 352.766021, "LD_SPAC:white"); // WEB 
	TextDrawLetterSize(td_phone_desktop[6], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_desktop[6], 12.000000, 13.000000);
	TextDrawAlignment(td_phone_desktop[6], 1);
	TextDrawColor(td_phone_desktop[6], -1599434241);
	TextDrawSetOutline(td_phone_desktop[6], 0);
	TextDrawBackgroundColor(td_phone_desktop[6], 255);
	TextDrawFont(td_phone_desktop[6], 4);
	TextDrawSetProportional(td_phone_desktop[6], 0);
	TextDrawSetShadow(td_phone_desktop[6], 0);
	TextDrawSetSelectable(td_phone_desktop[6], true);

	td_phone_desktop[7] = TextDrawCreate(573.892150, 352.766021, "LD_SPAC:white"); // APPS 
	TextDrawLetterSize(td_phone_desktop[7], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_desktop[7], 12.000000, 13.000000);
	TextDrawAlignment(td_phone_desktop[7], 1);
	TextDrawColor(td_phone_desktop[7], -1666529281);
	TextDrawSetOutline(td_phone_desktop[7], 0);
	TextDrawBackgroundColor(td_phone_desktop[7], 255);
	TextDrawFont(td_phone_desktop[7], 4);
	TextDrawSetProportional(td_phone_desktop[7], 0);
	TextDrawSetShadow(td_phone_desktop[7], 0);
	TextDrawSetSelectable(td_phone_desktop[7], true);
	
	/// Время и дата

	td_phone_desktop[8] = TextDrawCreate(530.800292, 288.066650, "17~n~15"); // Time 
	TextDrawLetterSize(td_phone_desktop[8], 0.371293, 2.113329);
	TextDrawAlignment(td_phone_desktop[8], 2);
	TextDrawColor(td_phone_desktop[8], -1917649409);
	TextDrawSetOutline(td_phone_desktop[8], 0);
	TextDrawBackgroundColor(td_phone_desktop[8], 255);
	TextDrawFont(td_phone_desktop[8], 2);
	TextDrawSetProportional(td_phone_desktop[8], 1);
	TextDrawSetShadow(td_phone_desktop[8], 0);
	
	td_phone_desktop[9] = TextDrawCreate(531.474609, 328.316558, "23 Tuesday"); // Date 
	TextDrawLetterSize(td_phone_desktop[9], 0.102117, 0.759998);
	TextDrawAlignment(td_phone_desktop[9], 2);
	TextDrawColor(td_phone_desktop[9], -1917649409);
	TextDrawSetOutline(td_phone_desktop[9], 0);
	TextDrawBackgroundColor(td_phone_desktop[9], 255);
	TextDrawFont(td_phone_desktop[9], 2);
	TextDrawSetProportional(td_phone_desktop[9], 1);
	TextDrawSetShadow(td_phone_desktop[9], 0);
	
	/// Виджет контактов
	
	td_phone_desktop[10] = TextDrawCreate(554.622314, 326.049407, "LD_SPAC:white"); // Click widget contacts
	TextDrawLetterSize(td_phone_desktop[10], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_desktop[10], 35.000000, 9.000000);
	TextDrawAlignment(td_phone_desktop[10], 1);
	TextDrawColor(td_phone_desktop[10], 290108217);
	TextDrawSetShadow(td_phone_desktop[10], 0);
	TextDrawSetOutline(td_phone_desktop[10], 0);
	TextDrawBackgroundColor(td_phone_desktop[10], 255);
	TextDrawFont(td_phone_desktop[10], 4);
	TextDrawSetProportional(td_phone_desktop[10], 0);
	TextDrawSetShadow(td_phone_desktop[10], 0);
	TextDrawSetSelectable(td_phone_desktop[10], true);

	td_phone_desktop[11] = TextDrawCreate(554.634826, 289.883209, "Contacts:"); // 
	TextDrawLetterSize(td_phone_desktop[11], 0.137881, 0.888331);
	TextDrawAlignment(td_phone_desktop[11], 1);
	TextDrawColor(td_phone_desktop[11], -1917649409);
	TextDrawSetShadow(td_phone_desktop[11], 0);
	TextDrawSetOutline(td_phone_desktop[11], 0);
	TextDrawBackgroundColor(td_phone_desktop[11], 255);
	TextDrawFont(td_phone_desktop[11], 2);
	TextDrawSetProportional(td_phone_desktop[11], 1);
	TextDrawSetShadow(td_phone_desktop[11], 0);

	td_phone_desktop[12] = TextDrawCreate(552.434631, 298.150115, "LD_BEAT:chit"); // ava1 
	TextDrawLetterSize(td_phone_desktop[12], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_desktop[12], 12.029977, 14.000000);
	TextDrawAlignment(td_phone_desktop[12], 1);
	TextDrawColor(td_phone_desktop[12], -1);
	TextDrawSetShadow(td_phone_desktop[12], 0);
	TextDrawSetOutline(td_phone_desktop[12], 0);
	TextDrawBackgroundColor(td_phone_desktop[12], 255);
	TextDrawFont(td_phone_desktop[12], 4);
	TextDrawSetProportional(td_phone_desktop[12], 0);
	TextDrawSetShadow(td_phone_desktop[12], 0);

	td_phone_desktop[13] = TextDrawCreate(560.565673, 326.899719, "CONTACTS"); // text-btn 
	TextDrawLetterSize(td_phone_desktop[13], 0.108232, 0.707496);
	TextDrawAlignment(td_phone_desktop[13], 1);
	TextDrawColor(td_phone_desktop[13], -1);
	TextDrawSetShadow(td_phone_desktop[13], 0);
	TextDrawSetOutline(td_phone_desktop[13], 0);
	TextDrawBackgroundColor(td_phone_desktop[13], 255);
	TextDrawFont(td_phone_desktop[13], 2);
	TextDrawSetProportional(td_phone_desktop[13], 1);
	TextDrawSetShadow(td_phone_desktop[13], 0);

	td_phone_desktop[14] = TextDrawCreate(564.587707, 300.683807, "hdhedsrjsjtklyhmnv"); // c-name 
	TextDrawLetterSize(td_phone_desktop[14], 0.032940, 0.643332);
	TextDrawAlignment(td_phone_desktop[14], 1);
	TextDrawColor(td_phone_desktop[14], -2139062017);
	TextDrawSetShadow(td_phone_desktop[14], 0);
	TextDrawSetOutline(td_phone_desktop[14], 0);
	TextDrawBackgroundColor(td_phone_desktop[14], 255);
	TextDrawFont(td_phone_desktop[14], 2);
	TextDrawSetProportional(td_phone_desktop[14], 1);
	TextDrawSetShadow(td_phone_desktop[14], 0);

	td_phone_desktop[15] = TextDrawCreate(552.434631, 310.350830, "LD_BEAT:chit"); // ava2
	TextDrawLetterSize(td_phone_desktop[15], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_desktop[15], 12.029977, 14.000000);
	TextDrawAlignment(td_phone_desktop[15], 1);
	TextDrawColor(td_phone_desktop[15], -1);
	TextDrawSetShadow(td_phone_desktop[15], 0);
	TextDrawSetOutline(td_phone_desktop[15], 0);
	TextDrawBackgroundColor(td_phone_desktop[15], 255);
	TextDrawFont(td_phone_desktop[15], 4);
	TextDrawSetProportional(td_phone_desktop[15], 0);
	TextDrawSetShadow(td_phone_desktop[15], 0);

	td_phone_desktop[16] = TextDrawCreate(565.058288, 312.933868, "hdfjhdfyhedhejhnerhntrj"); // c-name-2 
	TextDrawLetterSize(td_phone_desktop[16], 0.032940, 0.643332);
	TextDrawAlignment(td_phone_desktop[16], 1);
	TextDrawColor(td_phone_desktop[16], -2139062017);
	TextDrawSetShadow(td_phone_desktop[16], 0);
	TextDrawSetOutline(td_phone_desktop[16], 0);
	TextDrawBackgroundColor(td_phone_desktop[16], 255);
	TextDrawFont(td_phone_desktop[16], 2);
	TextDrawSetProportional(td_phone_desktop[16], 1);
	TextDrawSetShadow(td_phone_desktop[16], 0);
	
	/*!
		
		@brief Элементы для страницы: Action Call
	
	*/
	
	td_phone_action_call[0] = TextDrawCreate(532.289916, 364.732513, "ACCEPT"); // 
	TextDrawLetterSize(td_phone_action_call[0], 0.128939, 0.877496);
	TextDrawTextSize(td_phone_action_call[0], 8.000000, 37.000000);
	TextDrawAlignment(td_phone_action_call[0], 2);
	TextDrawColor(td_phone_action_call[0], -1);
	TextDrawUseBox(td_phone_action_call[0], 1);
	TextDrawBoxColor(td_phone_action_call[0], 1772577535);
	TextDrawSetOutline(td_phone_action_call[0], 0);
	TextDrawBackgroundColor(td_phone_action_call[0], 255);
	TextDrawFont(td_phone_action_call[0], 2);
	TextDrawSetProportional(td_phone_action_call[0], 1);
	TextDrawSetShadow(td_phone_action_call[0], 0);
	TextDrawSetSelectable(td_phone_action_call[0], true);

	td_phone_action_call[1] = TextDrawCreate(573.379882, 364.732513, "DECLINE"); // 
	TextDrawLetterSize(td_phone_action_call[1], 0.128939, 0.877496);
	TextDrawTextSize(td_phone_action_call[1], 8.000000, 37.000000);
	TextDrawAlignment(td_phone_action_call[1], 2);
	TextDrawColor(td_phone_action_call[1], -1);
	TextDrawUseBox(td_phone_action_call[1], 1);
	TextDrawBoxColor(td_phone_action_call[1], -1486724353);
	TextDrawSetOutline(td_phone_action_call[1], 0);
	TextDrawBackgroundColor(td_phone_action_call[1], 255);
	TextDrawFont(td_phone_action_call[1], 2);
	TextDrawSetProportional(td_phone_action_call[1], 1);
	TextDrawSetShadow(td_phone_action_call[1], 0);
	TextDrawSetSelectable(td_phone_action_call[1], true);

	td_phone_action_call[2] = TextDrawCreate(527.573059, 294.401184, "LD_BEAT:chit"); // avatar 
	TextDrawLetterSize(td_phone_action_call[2], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_action_call[2], 49.000000, 60.000000);
	TextDrawAlignment(td_phone_action_call[2], 1);
	TextDrawColor(td_phone_action_call[2], 18);
	TextDrawSetOutline(td_phone_action_call[2], 0);
	TextDrawBackgroundColor(td_phone_action_call[2], 255);
	TextDrawFont(td_phone_action_call[2], 4);
	TextDrawSetProportional(td_phone_action_call[2], 0);
	TextDrawSetShadow(td_phone_action_call[2], 0);
	
	
	/*!
		
		@brief Элементы для страницы: Item List (contacts, call log)
	
	*/
	
	td_phone_item_list[0] = TextDrawCreate(586.952697, 269.034088, "LD_BEAT:up"); // UP 
	TextDrawLetterSize(td_phone_item_list[0], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_item_list[0], 7.000000, 9.000000);
	TextDrawAlignment(td_phone_item_list[0], 1);
	TextDrawColor(td_phone_item_list[0], 1433712482);
	TextDrawSetOutline(td_phone_item_list[0], 0);
	TextDrawBackgroundColor(td_phone_item_list[0], 255);
	TextDrawFont(td_phone_item_list[0], 4);
	TextDrawSetProportional(td_phone_item_list[0], 0);
	TextDrawSetShadow(td_phone_item_list[0], 0);
	TextDrawSetSelectable(td_phone_item_list[0], true);

	td_phone_item_list[1] = TextDrawCreate(587.423278, 371.117401, "LD_BEAT:down"); // DOWN 
	TextDrawLetterSize(td_phone_item_list[1], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_item_list[1], 7.000000, 9.000000);
	TextDrawAlignment(td_phone_item_list[1], 1);
	TextDrawColor(td_phone_item_list[1], 1433712482);
	TextDrawSetOutline(td_phone_item_list[1], 0);
	TextDrawBackgroundColor(td_phone_item_list[1], 255);
	TextDrawFont(td_phone_item_list[1], 4);
	TextDrawSetProportional(td_phone_item_list[1], 0);
	TextDrawSetShadow(td_phone_item_list[1], 0);
	TextDrawSetSelectable(td_phone_item_list[1], true);

	td_phone_item_list[2] = TextDrawCreate(511.917663, 269.301971, "LD_BEAT:chit"); // ava1 
	TextDrawLetterSize(td_phone_item_list[2], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_item_list[2], 18.210027, 22.000000);
	TextDrawAlignment(td_phone_item_list[2], 1);
	TextDrawColor(td_phone_item_list[2], 1433712482);
	TextDrawSetOutline(td_phone_item_list[2], 0);
	TextDrawBackgroundColor(td_phone_item_list[2], 255);
	TextDrawFont(td_phone_item_list[2], 4);
	TextDrawSetProportional(td_phone_item_list[2], 0);
	TextDrawSetShadow(td_phone_item_list[2], 0);

	td_phone_item_list[3] = TextDrawCreate(511.917663, 288.803161, "LD_BEAT:chit"); // ava2 
	TextDrawLetterSize(td_phone_item_list[3], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_item_list[3], 18.210027, 22.000000);
	TextDrawAlignment(td_phone_item_list[3], 1);
	TextDrawColor(td_phone_item_list[3], 1433712482);
	TextDrawSetOutline(td_phone_item_list[3], 0);
	TextDrawBackgroundColor(td_phone_item_list[3], 255);
	TextDrawFont(td_phone_item_list[3], 4);
	TextDrawSetProportional(td_phone_item_list[3], 0);
	TextDrawSetShadow(td_phone_item_list[3], 0);

	td_phone_item_list[4] = TextDrawCreate(511.447082, 308.204345, "LD_BEAT:chit"); // ava3 
	TextDrawLetterSize(td_phone_item_list[4], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_item_list[4], 18.210027, 22.000000);
	TextDrawAlignment(td_phone_item_list[4], 1);
	TextDrawColor(td_phone_item_list[4], 1433712482);
	TextDrawSetOutline(td_phone_item_list[4], 0);
	TextDrawBackgroundColor(td_phone_item_list[4], 255);
	TextDrawFont(td_phone_item_list[4], 4);
	TextDrawSetProportional(td_phone_item_list[4], 0);
	TextDrawSetShadow(td_phone_item_list[4], 0);

	td_phone_item_list[5] = TextDrawCreate(511.447082, 326.905487, "LD_BEAT:chit"); // ava4 
	TextDrawLetterSize(td_phone_item_list[5], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_item_list[5], 18.210027, 22.000000);
	TextDrawAlignment(td_phone_item_list[5], 1);
	TextDrawColor(td_phone_item_list[5], 1433712482);
	TextDrawSetOutline(td_phone_item_list[5], 0);
	TextDrawBackgroundColor(td_phone_item_list[5], 255);
	TextDrawFont(td_phone_item_list[5], 4);
	TextDrawSetProportional(td_phone_item_list[5], 0);
	TextDrawSetShadow(td_phone_item_list[5], 0);

	td_phone_item_list[6] = TextDrawCreate(511.447082, 345.806640, "LD_BEAT:chit"); // ava5 
	TextDrawLetterSize(td_phone_item_list[6], 0.000000, 0.000000);
	TextDrawTextSize(td_phone_item_list[6], 18.210027, 22.000000);
	TextDrawAlignment(td_phone_item_list[6], 1);
	TextDrawColor(td_phone_item_list[6], 1433712482);
	TextDrawSetOutline(td_phone_item_list[6], 0);
	TextDrawBackgroundColor(td_phone_item_list[6], 255);
	TextDrawFont(td_phone_item_list[6], 4);
	TextDrawSetProportional(td_phone_item_list[6], 0);
	TextDrawSetShadow(td_phone_item_list[6], 0);
	
	/*!
		
		@brief Элементы для страницы: Call 
	
	*/
	
	td_phone_call[0] = TextDrawCreate(511.835754, 305.365325, "box"); // cback-numbers 
	TextDrawLetterSize(td_phone_call[0], 0.000000, 8.474000);
	TextDrawTextSize(td_phone_call[0], 593.271240, 0.000000);
	TextDrawAlignment(td_phone_call[0], 1);
	TextDrawColor(td_phone_call[0], -2139062017);
	TextDrawUseBox(td_phone_call[0], 1);
	TextDrawBoxColor(td_phone_call[0], 1433712415);
	TextDrawSetOutline(td_phone_call[0], 0);
	TextDrawBackgroundColor(td_phone_call[0], 255);
	TextDrawFont(td_phone_call[0], 1);
	TextDrawSetProportional(td_phone_call[0], 1);
	TextDrawSetShadow(td_phone_call[0], 0);
	
	td_phone_call[1] = TextDrawCreate(528.152160, 357.935424, "0"); // 
	TextDrawLetterSize(td_phone_call[1], 0.238115, 1.296663);
	TextDrawTextSize(td_phone_call[1], 12.000000, 8.539999);
	TextDrawAlignment(td_phone_call[1], 2);
	TextDrawColor(td_phone_call[1], 1433712639);
	TextDrawSetShadow(td_phone_call[1], 0);
	TextDrawSetOutline(td_phone_call[1], 0);
	TextDrawBackgroundColor(td_phone_call[1], 255);
	TextDrawFont(td_phone_call[1], 2);
	TextDrawSetProportional(td_phone_call[1], 1);
	TextDrawSetShadow(td_phone_call[1], 0);
	TextDrawSetSelectable(td_phone_call[1], true);
	
	td_phone_call[2] = TextDrawCreate(528.252136, 308.832427, "1"); // 
	TextDrawLetterSize(td_phone_call[2], 0.238115, 1.296663);
	TextDrawTextSize(td_phone_call[2], 12.000000, 8.539999);
	TextDrawAlignment(td_phone_call[2], 2);
	TextDrawColor(td_phone_call[2], 1433712639);
	TextDrawSetShadow(td_phone_call[2], 0);
	TextDrawSetOutline(td_phone_call[2], 0);
	TextDrawBackgroundColor(td_phone_call[2], 255);
	TextDrawFont(td_phone_call[2], 2);
	TextDrawSetProportional(td_phone_call[2], 1);
	TextDrawSetShadow(td_phone_call[2], 0);
	TextDrawSetSelectable(td_phone_call[2], true);
	
	td_phone_call[3] = TextDrawCreate(553.445983, 308.832427, "2"); // 
	TextDrawLetterSize(td_phone_call[3], 0.238115, 1.296663);
	TextDrawTextSize(td_phone_call[3], 12.000000, 8.539999);
	TextDrawAlignment(td_phone_call[3], 2);
	TextDrawColor(td_phone_call[3], 1433712639);
	TextDrawSetShadow(td_phone_call[3], 0);
	TextDrawSetOutline(td_phone_call[3], 0);
	TextDrawBackgroundColor(td_phone_call[3], 255);
	TextDrawFont(td_phone_call[3], 2);
	TextDrawSetProportional(td_phone_call[3], 1);
	TextDrawSetShadow(td_phone_call[3], 0);
	TextDrawSetSelectable(td_phone_call[3], true);
	
	td_phone_call[4] = TextDrawCreate(577.240173, 308.832427, "3"); // 
	TextDrawLetterSize(td_phone_call[4], 0.238115, 1.296663);
	TextDrawTextSize(td_phone_call[4], 12.000000, 8.539999);
	TextDrawAlignment(td_phone_call[4], 2);
	TextDrawColor(td_phone_call[4], 1433712639);
	TextDrawSetShadow(td_phone_call[4], 0);
	TextDrawSetOutline(td_phone_call[4], 0);
	TextDrawBackgroundColor(td_phone_call[4], 255);
	TextDrawFont(td_phone_call[4], 2);
	TextDrawSetProportional(td_phone_call[4], 1);
	TextDrawSetShadow(td_phone_call[4], 0);
	TextDrawSetSelectable(td_phone_call[4], true);
	
	td_phone_call[5] = TextDrawCreate(528.252136, 325.233428, "4"); // 
	TextDrawLetterSize(td_phone_call[5], 0.238115, 1.296663);
	TextDrawTextSize(td_phone_call[5], 12.000000, 8.539999);
	TextDrawAlignment(td_phone_call[5], 2);
	TextDrawColor(td_phone_call[5], 1433712639);
	TextDrawSetShadow(td_phone_call[5], 0);
	TextDrawSetOutline(td_phone_call[5], 0);
	TextDrawBackgroundColor(td_phone_call[5], 255);
	TextDrawFont(td_phone_call[5], 2);
	TextDrawSetProportional(td_phone_call[5], 1);
	TextDrawSetShadow(td_phone_call[5], 0);
	TextDrawSetSelectable(td_phone_call[5], true);

	td_phone_call[6] = TextDrawCreate(553.445983, 325.133422, "5"); // 
	TextDrawLetterSize(td_phone_call[6], 0.238115, 1.296663);
	TextDrawTextSize(td_phone_call[6], 12.000000, 8.539999);
	TextDrawAlignment(td_phone_call[6], 2);
	TextDrawColor(td_phone_call[6], 1433712639);
	TextDrawSetShadow(td_phone_call[6], 0);
	TextDrawSetOutline(td_phone_call[6], 0);
	TextDrawBackgroundColor(td_phone_call[6], 255);
	TextDrawFont(td_phone_call[6], 2);
	TextDrawSetProportional(td_phone_call[6], 1);
	TextDrawSetShadow(td_phone_call[6], 0);
	TextDrawSetSelectable(td_phone_call[6], true);
	
	td_phone_call[7] = TextDrawCreate(577.240173, 325.133422, "6"); // 
	TextDrawLetterSize(td_phone_call[7], 0.238115, 1.296663);
	TextDrawTextSize(td_phone_call[7], 12.000000, 8.539999);
	TextDrawAlignment(td_phone_call[7], 2);
	TextDrawColor(td_phone_call[7], 1433712639);
	TextDrawSetShadow(td_phone_call[7], 0);
	TextDrawSetOutline(td_phone_call[7], 0);
	TextDrawBackgroundColor(td_phone_call[7], 255);
	TextDrawFont(td_phone_call[7], 2);
	TextDrawSetProportional(td_phone_call[7], 1);
	TextDrawSetShadow(td_phone_call[7], 0);
	TextDrawSetSelectable(td_phone_call[7], true);

	td_phone_call[8] = TextDrawCreate(528.252136, 341.534423, "7"); // 
	TextDrawLetterSize(td_phone_call[8], 0.238115, 1.296663);
	TextDrawTextSize(td_phone_call[8], 12.000000, 8.539999);
	TextDrawAlignment(td_phone_call[8], 2);
	TextDrawColor(td_phone_call[8], 1433712639);
	TextDrawSetShadow(td_phone_call[8], 0);
	TextDrawSetOutline(td_phone_call[8], 0);
	TextDrawBackgroundColor(td_phone_call[8], 255);
	TextDrawFont(td_phone_call[8], 2);
	TextDrawSetProportional(td_phone_call[8], 1);
	TextDrawSetShadow(td_phone_call[8], 0);
	TextDrawSetSelectable(td_phone_call[8], true);

	td_phone_call[9] = TextDrawCreate(553.445983, 341.534423, "8"); // 
	TextDrawLetterSize(td_phone_call[9], 0.238115, 1.296663);
	TextDrawTextSize(td_phone_call[9], 12.000000, 8.539999);
	TextDrawAlignment(td_phone_call[9], 2);
	TextDrawColor(td_phone_call[9], 1433712639);
	TextDrawSetShadow(td_phone_call[9], 0);
	TextDrawSetOutline(td_phone_call[9], 0);
	TextDrawBackgroundColor(td_phone_call[9], 255);
	TextDrawFont(td_phone_call[9], 2);
	TextDrawSetProportional(td_phone_call[9], 1);
	TextDrawSetShadow(td_phone_call[9], 0);
	TextDrawSetSelectable(td_phone_call[9], true);

	td_phone_call[10] = TextDrawCreate(577.240173, 341.534423, "9"); // 
	TextDrawLetterSize(td_phone_call[10], 0.238115, 1.296663);
	TextDrawTextSize(td_phone_call[10], 12.000000, 8.539999);
	TextDrawAlignment(td_phone_call[10], 2);
	TextDrawColor(td_phone_call[10], 1433712639);
	TextDrawSetShadow(td_phone_call[10], 0);
	TextDrawSetOutline(td_phone_call[10], 0);
	TextDrawBackgroundColor(td_phone_call[10], 255);
	TextDrawFont(td_phone_call[10], 2);
	TextDrawSetProportional(td_phone_call[10], 1);
	TextDrawSetShadow(td_phone_call[10], 0);
	TextDrawSetSelectable(td_phone_call[10], true);

	td_phone_call[11] = TextDrawCreate(564.701232, 359.718505, "C"); // 
	TextDrawLetterSize(td_phone_call[11], 0.159058, 1.016664);
	TextDrawTextSize(td_phone_call[11], 8.539999, 32.000000);
	TextDrawAlignment(td_phone_call[11], 2);
	TextDrawColor(td_phone_call[11], -1);
	TextDrawUseBox(td_phone_call[11], 1);
	TextDrawBoxColor(td_phone_call[11], 8257654);
	TextDrawSetShadow(td_phone_call[11], 0);
	TextDrawSetOutline(td_phone_call[11], 0);
	TextDrawBackgroundColor(td_phone_call[11], 255);
	TextDrawFont(td_phone_call[11], 2);
	TextDrawSetProportional(td_phone_call[11], 1);
	TextDrawSetShadow(td_phone_call[11], 0);
	TextDrawSetSelectable(td_phone_call[11], true);

	td_phone_call[12] = TextDrawCreate(544.379760, 270.00000, "ADD TO CONTACTS"); // 
	TextDrawLetterSize(td_phone_call[12], 0.101176, 0.695831);
	TextDrawTextSize(td_phone_call[12], 8.500000, 63.000000);
	TextDrawAlignment(td_phone_call[12], 2);
	TextDrawColor(td_phone_call[12], -2139062017);
	TextDrawUseBox(td_phone_call[12], 1);
	TextDrawBoxColor(td_phone_call[12], -167);
	TextDrawSetShadow(td_phone_call[12], 0);
	TextDrawSetOutline(td_phone_call[12], 0);
	TextDrawBackgroundColor(td_phone_call[12], 255);
	TextDrawFont(td_phone_call[12], 2);
	TextDrawSetProportional(td_phone_call[12], 1);
	TextDrawSetShadow(td_phone_call[12], 0);
	TextDrawSetSelectable(td_phone_call[12], true);

	td_phone_call[13] = TextDrawCreate(585.961853, 270.00000, "CLEAR"); // 
	TextDrawLetterSize(td_phone_call[13], 0.101176, 0.695831);
	TextDrawTextSize(td_phone_call[13], 8.500000, 15.000000);
	TextDrawAlignment(td_phone_call[13], 2);
	TextDrawColor(td_phone_call[13], -1);
	TextDrawUseBox(td_phone_call[13], 1);
	TextDrawBoxColor(td_phone_call[13], -2139062148);
	TextDrawSetShadow(td_phone_call[13], 0);
	TextDrawSetOutline(td_phone_call[13], 0);
	TextDrawBackgroundColor(td_phone_call[13], 255);
	TextDrawFont(td_phone_call[13], 2);
	TextDrawSetProportional(td_phone_call[13], 1);
	TextDrawSetShadow(td_phone_call[13], 0);
	TextDrawSetSelectable(td_phone_call[13], true);
	
	td_phone_breadcrumb = TextDrawCreate(517.328735, 254.500091, "<"); // btn-last 
	TextDrawLetterSize(td_phone_breadcrumb, 0.195291, 0.865000);
	TextDrawTextSize(td_phone_breadcrumb, 8.699829, 10.701665);
	TextDrawAlignment(td_phone_breadcrumb, 2);
	TextDrawColor(td_phone_breadcrumb, -1);
	TextDrawSetOutline(td_phone_breadcrumb, 0);
	TextDrawBackgroundColor(td_phone_breadcrumb, 255);
	TextDrawFont(td_phone_breadcrumb, 1);
	TextDrawSetProportional(td_phone_breadcrumb, 1);
	TextDrawSetShadow(td_phone_breadcrumb, 0);
	TextDrawSetSelectable(td_phone_breadcrumb, true);
}

TD_Panel_Phone()
{
	for (new i, j; i < sizeof panel_color_list; i++, j += 3)
	{
		td_phone_panel[j] = TextDrawCreate(508.746917, 216.316360, "box"); // Panel 
		TextDrawLetterSize(td_phone_panel[j], 0.000000, 20.588228);
		TextDrawTextSize(td_phone_panel[j], 597.000000, 0.000000);
		TextDrawAlignment(td_phone_panel[j], 1);
		TextDrawColor(td_phone_panel[j], -1);
		TextDrawUseBox(td_phone_panel[j], 1);
		TextDrawBoxColor(td_phone_panel[j], panel_color_list[i][pc_color_int]);
		TextDrawSetOutline(td_phone_panel[j], 0);
		TextDrawBackgroundColor(td_phone_panel[0], panel_color_list[i][pc_color_int]);
		TextDrawFont(td_phone_panel[j], 1);
		TextDrawSetProportional(td_phone_panel[j], 1);
		TextDrawSetShadow(td_phone_panel[j], 0);
		
		td_phone_panel[j + 1] = TextDrawCreate(600.688232, 355.666656, "box"); // Panel 
		TextDrawLetterSize(td_phone_panel[j + 1], 0.000000, 1.247056);
		TextDrawTextSize(td_phone_panel[j + 1], 598.000000, 0.000000);
		TextDrawAlignment(td_phone_panel[j + 1], 1);
		TextDrawColor(td_phone_panel[j + 1], -1);
		TextDrawUseBox(td_phone_panel[j + 1], 1);
		TextDrawBoxColor(td_phone_panel[j + 1], panel_color_list[i][pc_color_int]);
		TextDrawSetOutline(td_phone_panel[j + 1], 0);
		TextDrawBackgroundColor(td_phone_panel[j + 1], panel_color_list[i][pc_color_int]);
		TextDrawFont(td_phone_panel[j + 1], 1);
		TextDrawSetProportional(td_phone_panel[j + 1], 1);
		TextDrawSetShadow(td_phone_panel[j + 1], 0);

		td_phone_panel[j + 2] = TextDrawCreate(601.629394, 251.249984, "box"); // Panel 
		TextDrawLetterSize(td_phone_panel[j + 2], 0.000000, 2.188230);
		TextDrawTextSize(td_phone_panel[j + 2], 597.000000, 0.000000);
		TextDrawAlignment(td_phone_panel[j + 2], 1);
		TextDrawColor(td_phone_panel[j + 2], -1);
		TextDrawUseBox(td_phone_panel[j + 2], 1);
		TextDrawBoxColor(td_phone_panel[j + 2], panel_color_list[i][pc_color_int]);
		TextDrawSetOutline(td_phone_panel[j + 2], 0);
		TextDrawBackgroundColor(td_phone_panel[j + 2], panel_color_list[i][pc_color_int]);
		TextDrawFont(td_phone_panel[j + 2], 1);
		TextDrawSetProportional(td_phone_panel[j + 2], 1);
		TextDrawSetShadow(td_phone_panel[j + 2], 0);
	}
}

TD_Player_Phone(playerid)
{
	/*!
		
		@brief Основные элементы
	
	*/

	ptd_phone_breadcrumb[playerid] = CreatePlayerTextDraw(playerid, 552.669250, 255.233551, "ESMOND WHEELER"); // breadcrumb-title 
	PlayerTextDrawLetterSize(playerid, ptd_phone_breadcrumb[playerid], 0.127527, 0.750832);
	PlayerTextDrawAlignment(playerid, ptd_phone_breadcrumb[playerid], 2);
	PlayerTextDrawColor(playerid, ptd_phone_breadcrumb[playerid], -1);
	PlayerTextDrawSetOutline(playerid, ptd_phone_breadcrumb[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_phone_breadcrumb[playerid], 255);
	PlayerTextDrawFont(playerid, ptd_phone_breadcrumb[playerid], 2);
	PlayerTextDrawSetProportional(playerid, ptd_phone_breadcrumb[playerid], 1);
	PlayerTextDrawSetShadow(playerid, ptd_phone_breadcrumb[playerid], 0);
	
	/*!
		
		@brief Элементы для страницы: Desktop
	
	*/
	
	/// Текст к иконкам call, sms, web, apps
	ptd_phone_desktop[playerid][0] = CreatePlayerTextDraw(playerid, 524.004516, 366.949615, "CALL"); // 
	PlayerTextDrawLetterSize(playerid, ptd_phone_desktop[playerid][0], 0.111997, 0.754163);
	PlayerTextDrawAlignment(playerid, ptd_phone_desktop[playerid][0], 2);
	PlayerTextDrawColor(playerid, ptd_phone_desktop[playerid][0], 1433843711);
	PlayerTextDrawSetOutline(playerid, ptd_phone_desktop[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_phone_desktop[playerid][0], 255);
	PlayerTextDrawFont(playerid, ptd_phone_desktop[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, ptd_phone_desktop[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, ptd_phone_desktop[playerid][0], 0);

	ptd_phone_desktop[playerid][1] = CreatePlayerTextDraw(playerid, 542.899902, 366.949615, "SMS"); // 
	PlayerTextDrawLetterSize(playerid, ptd_phone_desktop[playerid][1], 0.111997, 0.754163);
	PlayerTextDrawAlignment(playerid, ptd_phone_desktop[playerid][1], 2);
	PlayerTextDrawColor(playerid, ptd_phone_desktop[playerid][1], 1433843711);
	PlayerTextDrawSetOutline(playerid, ptd_phone_desktop[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_phone_desktop[playerid][1], 255);
	PlayerTextDrawFont(playerid, ptd_phone_desktop[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, ptd_phone_desktop[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, ptd_phone_desktop[playerid][1], 0);

	ptd_phone_desktop[playerid][2] = CreatePlayerTextDraw(playerid, 561.501098, 366.916259, "WEB"); // 
	PlayerTextDrawLetterSize(playerid, ptd_phone_desktop[playerid][2], 0.111997, 0.754163);
	PlayerTextDrawAlignment(playerid, ptd_phone_desktop[playerid][2], 2);
	PlayerTextDrawColor(playerid, ptd_phone_desktop[playerid][2], 1433843711);
	PlayerTextDrawSetOutline(playerid, ptd_phone_desktop[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_phone_desktop[playerid][2], 255);
	PlayerTextDrawFont(playerid, ptd_phone_desktop[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, ptd_phone_desktop[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, ptd_phone_desktop[playerid][2], 0);

	ptd_phone_desktop[playerid][3] = CreatePlayerTextDraw(playerid, 580.015075, 366.399444, "Apps"); // 
	PlayerTextDrawLetterSize(playerid,ptd_phone_desktop[playerid][3], 0.111997, 0.754163);
	PlayerTextDrawAlignment(playerid,ptd_phone_desktop[playerid][3], 2);
	PlayerTextDrawColor(playerid,ptd_phone_desktop[playerid][3], 1433843711);
	PlayerTextDrawSetOutline(playerid,ptd_phone_desktop[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid,ptd_phone_desktop[playerid][3], 255);
	PlayerTextDrawFont(playerid,ptd_phone_desktop[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid,ptd_phone_desktop[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid,ptd_phone_desktop[playerid][3], 0);
	
	/*!
		
		@brief Элементы для страницы: Action Call
	
	*/
	
	ptd_phone_action_call[playerid][0] = CreatePlayerTextDraw(playerid, 552.631408, 270.0000, "111-333"); // number 
	PlayerTextDrawLetterSize(playerid, ptd_phone_action_call[playerid][0], 0.128939, 0.847495);
	PlayerTextDrawTextSize(playerid, ptd_phone_action_call[playerid][0], 0.000000, 81.000000);
	PlayerTextDrawAlignment(playerid, ptd_phone_action_call[playerid][0], 2);
	PlayerTextDrawColor(playerid, ptd_phone_action_call[playerid][0], 1433712639);
	PlayerTextDrawUseBox(playerid, ptd_phone_action_call[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, ptd_phone_action_call[playerid][0], 24);
	PlayerTextDrawSetOutline(playerid, ptd_phone_action_call[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_phone_action_call[playerid][0], 255);
	PlayerTextDrawFont(playerid, ptd_phone_action_call[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, ptd_phone_action_call[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, ptd_phone_action_call[playerid][0], 0);

	ptd_phone_action_call[playerid][1] = CreatePlayerTextDraw(playerid, 553.580688, 288.550384, "Incoming Call"); // status 
	PlayerTextDrawLetterSize(playerid, ptd_phone_action_call[playerid][1], 0.116232, 0.794996);
	PlayerTextDrawAlignment(playerid, ptd_phone_action_call[playerid][1], 2);
	PlayerTextDrawColor(playerid, ptd_phone_action_call[playerid][1], -2139062052);
	PlayerTextDrawSetOutline(playerid, ptd_phone_action_call[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_phone_action_call[playerid][1], 255);
	PlayerTextDrawFont(playerid, ptd_phone_action_call[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, ptd_phone_action_call[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, ptd_phone_action_call[playerid][1], 0);
	
	/*!
		
		@brief Элементы для страницы: Item List (contacts, call log)
	
	*/
	
	ptd_phone_item_list[playerid][0] = CreatePlayerTextDraw(playerid, 530.722290, 273.735473, "Esmond Wheeler"); // name1 
	PlayerTextDrawLetterSize(playerid, ptd_phone_item_list[playerid][0], 0.111997, 0.701665);
	PlayerTextDrawTextSize(playerid, ptd_phone_item_list[playerid][0], 577.000000, 7.730831);
	PlayerTextDrawAlignment(playerid, ptd_phone_item_list[playerid][0], 1);
	PlayerTextDrawColor(playerid, ptd_phone_item_list[playerid][0], 1433712639);
	PlayerTextDrawSetOutline(playerid, ptd_phone_item_list[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_phone_item_list[playerid][0], 255);
	PlayerTextDrawFont(playerid, ptd_phone_item_list[playerid][0], 2);
	PlayerTextDrawSetProportional(playerid, ptd_phone_item_list[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, ptd_phone_item_list[playerid][0], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_phone_item_list[playerid][0], true);

	ptd_phone_item_list[playerid][1] = CreatePlayerTextDraw(playerid, 530.722290, 293.336669, "Esmond Wheeler"); // name2 
	PlayerTextDrawLetterSize(playerid, ptd_phone_item_list[playerid][1], 0.111997, 0.701665);
	PlayerTextDrawTextSize(playerid, ptd_phone_item_list[playerid][1], 577.000000, 7.730831);
	PlayerTextDrawAlignment(playerid, ptd_phone_item_list[playerid][1], 1);
	PlayerTextDrawColor(playerid, ptd_phone_item_list[playerid][1], 1433712639);
	PlayerTextDrawSetOutline(playerid, ptd_phone_item_list[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_phone_item_list[playerid][1], 255);
	PlayerTextDrawFont(playerid, ptd_phone_item_list[playerid][1], 2);
	PlayerTextDrawSetProportional(playerid, ptd_phone_item_list[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, ptd_phone_item_list[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_phone_item_list[playerid][1], true);

	ptd_phone_item_list[playerid][2] = CreatePlayerTextDraw(playerid, 530.722290, 311.737792, "Esmond Wheeler"); // name3 
	PlayerTextDrawLetterSize(playerid, ptd_phone_item_list[playerid][2], 0.111997, 0.701665);
	PlayerTextDrawTextSize(playerid, ptd_phone_item_list[playerid][2], 577.000000, 7.730831);
	PlayerTextDrawAlignment(playerid, ptd_phone_item_list[playerid][2], 1);
	PlayerTextDrawColor(playerid, ptd_phone_item_list[playerid][2], 1433712639);
	PlayerTextDrawSetOutline(playerid, ptd_phone_item_list[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_phone_item_list[playerid][2], 255);
	PlayerTextDrawFont(playerid, ptd_phone_item_list[playerid][2], 2);
	PlayerTextDrawSetProportional(playerid, ptd_phone_item_list[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, ptd_phone_item_list[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_phone_item_list[playerid][2], true);

	ptd_phone_item_list[playerid][3] = CreatePlayerTextDraw(playerid, 530.722290, 330.538940, "Esmond Wheeler"); // name4 
	PlayerTextDrawLetterSize(playerid, ptd_phone_item_list[playerid][3], 0.111997, 0.701665);
	PlayerTextDrawTextSize(playerid, ptd_phone_item_list[playerid][3], 577.000000, 7.730831);
	PlayerTextDrawAlignment(playerid, ptd_phone_item_list[playerid][3], 1);
	PlayerTextDrawColor(playerid, ptd_phone_item_list[playerid][3], 1433712639);
	PlayerTextDrawSetOutline(playerid, ptd_phone_item_list[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_phone_item_list[playerid][3], 255);
	PlayerTextDrawFont(playerid, ptd_phone_item_list[playerid][3], 2);
	PlayerTextDrawSetProportional(playerid, ptd_phone_item_list[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, ptd_phone_item_list[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_phone_item_list[playerid][3], true);

	ptd_phone_item_list[playerid][4] = CreatePlayerTextDraw(playerid, 530.722290, 351.040191, "Esmond Wheeler"); // name5 
	PlayerTextDrawLetterSize(playerid, ptd_phone_item_list[playerid][4], 0.111997, 0.701665);
	PlayerTextDrawTextSize(playerid, ptd_phone_item_list[playerid][4], 577.000000, 7.730831);
	PlayerTextDrawAlignment(playerid, ptd_phone_item_list[playerid][4], 1);
	PlayerTextDrawColor(playerid, ptd_phone_item_list[playerid][4], 1433712639);
	PlayerTextDrawSetOutline(playerid, ptd_phone_item_list[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_phone_item_list[playerid][4], 255);
	PlayerTextDrawFont(playerid, ptd_phone_item_list[playerid][4], 2);
	PlayerTextDrawSetProportional(playerid, ptd_phone_item_list[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, ptd_phone_item_list[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_phone_item_list[playerid][4], true);
		
	ptd_phone_item_list[playerid][5] = CreatePlayerTextDraw(playerid, 512.993652, 374.156433, "Add Contact"); // 
	PlayerTextDrawLetterSize(playerid, ptd_phone_item_list[playerid][5], 0.149174, 0.870832);
	PlayerTextDrawTextSize(playerid, ptd_phone_item_list[playerid][5], 581.699829, 20.701665);
	PlayerTextDrawAlignment(playerid, ptd_phone_item_list[playerid][5], 1);
	PlayerTextDrawColor(playerid, ptd_phone_item_list[playerid][5], -2139062017);
	PlayerTextDrawUseBox(playerid, ptd_phone_item_list[playerid][5], 0);
	//PlayerTextDrawBoxColor(playerid, ptd_phone_item_list[playerid][5], 20);
	PlayerTextDrawSetOutline(playerid, ptd_phone_item_list[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_phone_item_list[playerid][5], 255);
	PlayerTextDrawFont(playerid, ptd_phone_item_list[playerid][5], 2);
	PlayerTextDrawSetProportional(playerid, ptd_phone_item_list[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, ptd_phone_item_list[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_phone_item_list[playerid][5], true);
	
	/*!
		
		@brief Элементы для страницы: Call
	
	*/
	
	ptd_phone_call_input[playerid] = CreatePlayerTextDraw(playerid, 554.093200, 281.799499, "_"); // 
	PlayerTextDrawLetterSize(playerid, ptd_phone_call_input[playerid], 0.197646, 1.121664);
	PlayerTextDrawAlignment(playerid, ptd_phone_call_input[playerid], 2);
	PlayerTextDrawColor(playerid, ptd_phone_call_input[playerid], 1433712639);
	PlayerTextDrawSetOutline(playerid, ptd_phone_call_input[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_phone_call_input[playerid], 255);
	PlayerTextDrawFont(playerid, ptd_phone_call_input[playerid], 2);
	PlayerTextDrawSetProportional(playerid, ptd_phone_call_input[playerid], 1);
	PlayerTextDrawSetShadow(playerid, ptd_phone_call_input[playerid], 0);
}

TD_UpdatePhoneDate()
{
	new hour,
		minute;
	
	gettime(hour, minute, _);
	
	format:g_small_string("%02d:%02d", hour, minute);
	TextDrawSetString(td_phone_head_time, g_small_string);
	
	format:g_small_string("%02d~n~%02d", hour, minute);
	TextDrawSetString(td_phone_desktop[8], g_small_string); 
	
	GetNameOfWeekday(g_small_string);
	TextDrawSetString(td_phone_desktop[9], g_small_string);
}

TD_SetPhoneBreadcrumb(playerid, bool: states, title[] = "none", bool: btn = false)
{
	if (states)
	{
		if (btn)
		{
			TextDrawShowForPlayer(playerid, td_phone_breadcrumb);
		}
		
		TextDrawShowForPlayer(playerid, td_phone_static[2]);
		PlayerTextDrawShow(playerid, ptd_phone_breadcrumb[playerid]);
		PlayerTextDrawSetString(playerid, ptd_phone_breadcrumb[playerid], title);
	}
	else 
	{
		TextDrawHideForPlayer(playerid, td_phone_static[2]);
		PlayerTextDrawHide(playerid, ptd_phone_breadcrumb[playerid]);
		TextDrawHideForPlayer(playerid, td_phone_breadcrumb);
	}
}

TD_SetPhonePanel(playerid, bool: states, type)
{
	new index = type * 3;
	if (states)
	{
		TextDrawShowForPlayer(playerid, td_phone_panel[index]);
		TextDrawShowForPlayer(playerid, td_phone_panel[index + 1]);
		TextDrawShowForPlayer(playerid, td_phone_panel[index + 2]);
	}
	else 
	{
		TextDrawHideForPlayer(playerid, td_phone_panel[index]);
		TextDrawHideForPlayer(playerid, td_phone_panel[index + 1]);
		TextDrawHideForPlayer(playerid, td_phone_panel[index + 2]);
	}
}