/*!
	@brief Глобальные переменные и енуменаторы
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
*/

/*!
	
	STRUCTURES / Структуры
	
*/

enum // SendRPMessage(type, playerid, const action[]);
{
	ACTION_ME = 0,
	ACTION_DO,
	ACTION_AME,
};

enum 
{
	TYPE_CHOOSE_REG = 1,
	TYPE_CHOOSE_CUPBOARD
};

enum
{
	TYPE_IC,
	TYPE_OOC,
	TYPE_HIDDEN
};

/// Тип покупки
enum 
{
	TYPE_BUY_RENT = 1, // взял в аренду
	TYPE_BUY_FULLY = 2, // купил полностью
	TYPE_BUY_START_CAPITAL = 3 // купил за стартовый капитал
};


/// Для динамичных диалогов
enum
{
	ITEM_LIST_NEXT = INVALID_PARAM - 2,
	ITEM_LIST_BACK,
	ITEM_LIST_BEGIN,
	ITEM_LIST_CURRENT,
	ITEM_LIST_NONE
};

/*!
	
	VARIABLES / Переменные
	
*/

/// Динамичные диалоги
new	g_td_select					[MAX_PLAYERS][6];

/// Строковые переменные
new g_small_string				[256],
	g_string					[512],
	g_big_string				[2048 ];
	

/// Соединение с базой данных
new MySQL: db;
	

/// Остальное
new g_hour,
	g_minute,
	g_second;
	
new timer_second_tick;

// Задержка старта
new g_delay = __RESTART_DELAY;