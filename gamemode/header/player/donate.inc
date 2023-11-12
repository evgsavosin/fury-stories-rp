/*!
	@brief Основной заголовок для доната
	@author Found (evg.savosin)
	@date 16.12.2016, update 16.01.2018
*/

// Defines
#define GetUserVipText(%0)			donate_vip[GetUserVip(%0)]

// Structures

// Список VIP
enum 
{
	VIP_STARTER = 1,
	VIP_DEFAULT,
	VIP_ADVANCED,
	VIP_PRO
}

// Список доната 
enum
{
	DONATE_CHANGE_CHARACTER_NAME = 1,
	DONATE_UNWARN,
	DONATE_CHANGE_VEHICLE_NUMBER,
	DONATE_CHANGE_PHONE_NUMBER,
	
	DONATE_WEAPON_CASE,
	DONATE_ARMY_CASE,
	
	DONATE_PACK_1,
	DONATE_PACK_2,
	DONATE_PACK_3,
	
	DONATE_VIP_STARTER,
	DONATE_VIP_DEFAULT,
	DONATE_VIP_ADVANCED,
	DONATE_VIP_PRO
}

// ID предметов
enum 
{ 
	ITEM_BRASSKNUCKLE = 113, // Кастет
	ITEM_KATANA = 7, // Катана
	ITEM_PISTOL = 8, // Пистолет
	ITEM_SMALL_PP = 13, // Малогабаритный пп
	
	ITEM_ARMOUR = 109, // Легкий бронежилет
	ITEM_KNIFE = 88, // Нож выживания
	ITEM_SILENCE_PISTOL = 9, // Пистолет с глушителем
	ITEM_AUTOPISTOL = 14, // Полуавтоматический пистолет
	ITEM_PP = 15 // ПП
}

new const donate_weapon_case 		[] =
{
	ITEM_BRASSKNUCKLE,
	ITEM_KATANA,
	ITEM_PISTOL,
	ITEM_SMALL_PP
};

new const donate_army_case 	[] =
{
	ITEM_ARMOUR,
	ITEM_KNIFE,
	ITEM_SILENCE_PISTOL,
	ITEM_AUTOPISTOL,
	ITEM_PP
};

enum E_DONATE_OBJECT
{
	d_object_id,
	d_name						[64]
}

new const donate_vip			[][] =
{
	{"Отсутствует"},
	{"Начальный"},
	{"Стандартный"},
	{"Продвинутый"},
	{"Профессиональный"}
};

new const donate_objects		[][E_DONATE_OBJECT] =
{
	{11712, "Церковный крест"},
	{19918, "Чёрный ящик"},
	{19167, "Карта города"},
	{11245, "Флаг США"},
	{2614, "Два флага США"},
	{1255, "Лежак"},
	{1281, "Стол с зонтом"},
	{3039, "Лавка"},
	{1665, "Пепельница"},
	{2619, "Мишень для тира"},
	{19470, "Табличка 'FOR SALE'"},
	{2896, "Гроб"},
	{2712, "Швабра"},
	{2060, "Мешок"},
	{19315, "Олень"},
	{1917, "Двигатель"},
	{19836, "Лужица крови"},
	{1369, "Инвалидное кресло"},
	{18728, "Сигнальный огонь"},
	{2773, "Ограждения для церемоний"}
};

enum E_DONATE_OBJECT_DATA
{
	Text3D: d_text_id,
	d_object_id,
}

new donate_object		[MAX_PLAYERS][E_DONATE_OBJECT_DATA];


Clear:donate(playerid)
{
	donate_object[playerid][d_text_id] = Text3D: INVALID_3DTEXT_ID;
	donate_object[playerid][d_object_id] = INVALID_OBJECT_ID;
}

Create:donate_item(playerid, item_id, bool: show_donate_menu = false)
{
	format:g_string("INSERT INTO " #__DONATE " (user_id, donate_item_id, create_date) VALUES (%d, %d, NOW())",
		GetUserId(playerid),
		item_id
	);

	mysql_tquery(db, g_string, "OnDonateItemCreate", "dd", playerid, _: show_donate_menu);
}

function OnDonateItemCreate(playerid, show_donate_menu)
{
	if (show_donate_menu)
	{
		ShowPlayerDonate(playerid);
	}
	
	return 1;
}

Remove:donate_item(playerid, item_id, callback[])
{
	format:g_string("DELETE FROM " #__DONATE " WHERE user_id = %d AND donate_item_id = %d LIMIT 1",
		GetUserId(playerid),
		item_id
	);
	
	mysql_tquery(db, g_string, callback, "dd", playerid, item_id);
}