/*!
	@brief �������� ��������� ��� ������
	@author Found (evg.savosin)
	@date 16.12.2016, update 16.01.2018
*/

// Defines
#define GetUserVipText(%0)			donate_vip[GetUserVip(%0)]

// Structures

// ������ VIP
enum 
{
	VIP_STARTER = 1,
	VIP_DEFAULT,
	VIP_ADVANCED,
	VIP_PRO
}

// ������ ������ 
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

// ID ���������
enum 
{ 
	ITEM_BRASSKNUCKLE = 113, // ������
	ITEM_KATANA = 7, // ������
	ITEM_PISTOL = 8, // ��������
	ITEM_SMALL_PP = 13, // �������������� ��
	
	ITEM_ARMOUR = 109, // ������ ����������
	ITEM_KNIFE = 88, // ��� ���������
	ITEM_SILENCE_PISTOL = 9, // �������� � ����������
	ITEM_AUTOPISTOL = 14, // ������������������ ��������
	ITEM_PP = 15 // ��
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
	{"�����������"},
	{"���������"},
	{"�����������"},
	{"�����������"},
	{"����������������"}
};

new const donate_objects		[][E_DONATE_OBJECT] =
{
	{11712, "��������� �����"},
	{19918, "׸���� ����"},
	{19167, "����� ������"},
	{11245, "���� ���"},
	{2614, "��� ����� ���"},
	{1255, "�����"},
	{1281, "���� � ������"},
	{3039, "�����"},
	{1665, "����������"},
	{2619, "������ ��� ����"},
	{19470, "�������� 'FOR SALE'"},
	{2896, "����"},
	{2712, "������"},
	{2060, "�����"},
	{19315, "�����"},
	{1917, "���������"},
	{19836, "������ �����"},
	{1369, "���������� ������"},
	{18728, "���������� �����"},
	{2773, "���������� ��� ���������"}
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