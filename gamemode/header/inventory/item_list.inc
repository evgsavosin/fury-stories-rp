/*!
	@brief ������ ��������� � ������� ���������
	@author Found (evg.savosin)
	@date 16.12.2016, update 07.02.2018
	
*/

// Defines
#define GetInventoryItemId(%0)		item_list[%0][it_id]	
#define GetInventoryItemName(%0)	item_list[%0][it_name]	

// Structures
// ���� ���������
enum 
{
	INV_NONE = 0,
	INV_SKIN, // 1 
	INV_WEAPON_SMALL, // 2
	INV_WEAPON_BIG, // 3
	INV_EAT, // 4 
	INV_DRINK, // 5 
	INV_ATTACH, // 6 
	INV_AMMO, // 7
	INV_BAG, // 8 �����
	INV_PHONE, // 9 
	INV_OBJECT, // 10
	INV_HEALTH, // 11
	INV_REPAIR, // 12
	INV_SMOKE, // 13
	INV_RADIO, // 14
	INV_FUEL, // 15
	INV_CHEMICAL, // 16
	INV_LIGHTER, // 17
	INV_DRUGS // 18
};

// �������������� ������� � ���������
enum 
{
	INV_FUNC_HIDDEN_NAME = -1000,
	INV_FUNC_SOUND,
	INV_FUNC_SINGLE_SMOKE,
	INV_FUNC_RADIO_LOW,
	INV_FUNC_RADIO_HIGH,
	INV_FUNC_ARMOUR_LIGHT,
	INV_FUNC_ARMOUR_HEAVY,
	INV_FUNC_KNIFE,
	INV_FUNC_MARIJUANA,
	INV_FUNC_LSD,
	INV_FUNC_COCAINE
};

enum E_ITEM_DATA
{
	it_id,
	it_type,
	
	it_name						[	64		],
	it_model,
	
	Float: it_draw_x,
	Float: it_draw_y,
	Float: it_draw_z,
	Float: it_draw_zoom,
	
	it_param_1,
	it_param_2,
	
	it_description				[	256		],
	
	bool: it_is_glove_exists,
};

new const item_list				[		][		E_ITEM_DATA 	] = 
{
	{0, INV_NONE, "�����", 19374, 0.0, 0.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM, "", false}, // �����
	
	
	{1, INV_SKIN, "������", 0, 0.0, 0.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"������������ ������� �������, ����������� ������������ �������.", false},

	
	{2, INV_WEAPON_BIG, "������ ��� ������", 333, 0.0, -30.0, 0.0, 1.5, WEAPON_GOLFCLUB, INVALID_PARAM, 
		"���������� ������ � ���� ����� � �������� ������ ��� ���� � �����.", false},
		
	{3, INV_WEAPON_BIG, "��������� �������", 334, 0.0, -30.0, 0.0, 1.5, WEAPON_NITESTICK, INVALID_PARAM, 
		"������������� ������, ������� ������������ ������������ ������������������ �������.", false},
		
	{5, INV_WEAPON_BIG, "����������� ����", 336, 0.0, -30.0, 0.0, 1.5, WEAPON_BAT, INVALID_PARAM, 
		"���������� ������, ������� ������ � ��������� ���������� ����� �������� ������ �������� ���.", false},
		
	{6, INV_WEAPON_BIG, "������", 337, 0.0, -30.0, 0.0, 1.5, WEAPON_SHOVEL, INVALID_PARAM, 
		"������ ���������� ��� ������ � �������.", false},
		
	{7, INV_WEAPON_BIG, "������", 339, 0.0, -30.0, 0.0, 1.5, WEAPON_KATANA, INVALID_PARAM, 
		"������� �������� �����.", false},
		
	{8, INV_WEAPON_SMALL, "�������������� ��������", 346, 0.0, -30.0, 0.0, 1.5, WEAPON_COLT45, 20,
		"������������ ��������.\n\
		��������� ��� ���������: " #cPROJECT "M1911, Beretta M9, Glock 17, HK VP9, ��,\nSmith & Wesson Model CS45, Kimber Classic" #cWHITE ".", true},
		
	{9, INV_WEAPON_SMALL, "�������������� �������� � ����������", 347, 0.0, -30.0, 0.0, 1.5, WEAPON_SILENCED, 20,
		"������������ �������� � ����������.\n\
		��������� ��� ���������: " #cPROJECT "M1911, Beretta M9, Glock 17, HK VP9, ��,\nSmith & Wesson Model CS45, Kimber Classic" #cWHITE ".", true},
		
	{10, INV_WEAPON_SMALL, "������� ��������", 348, 0.0, -30.0, 0.0, 1.5, WEAPON_DEAGLE, 21,
		"������� ������������ ��������.\n\
		��������� ��� ���������: " #cPROJECT "Desert Eagle, Combat Magnum" #cWHITE ".", true},
	
	{11, INV_WEAPON_BIG, "��������", 349, 0.0, -30.0, 0.0, 1.5, WEAPON_SHOTGUN, 22,
		"��������������� ������������� ������.\n\
		��������� ��� ���������: " #cPROJECT "Remington 1100, Remington 870, Benelli Nova" #cWHITE ".", false},
		
	{12, INV_WEAPON_BIG, "��������� ��������", 351, 0.0, -30.0, 0.0, 1.5, WEAPON_SHOTGSPA, 22,
		"�������������� ��������������� ������������� ������.\n\
		��������� ��� ���������: " #cPROJECT "SPAS-12" #cWHITE ".", false},
		
	{13, INV_WEAPON_SMALL, "�������������� ��", 352, 0.0, -30.0, 0.0, 1.5, WEAPON_UZI, 23,
		"����������� �������������� ��������-������.\n\
		��������� ��� ���������: " #cPROJECT "Micro UZI" #cWHITE ".", true},
		
	{14, INV_WEAPON_SMALL, "������������������ ��������", 372, 0.0, -30.0, 0.0, 1.5, WEAPON_TEC9, 23,
		"�������������� ��������-�������, ������������� � ������ � 1980-� �����.\n\
		��������� ��� ���������: " #cPROJECT "TEC-9" #cWHITE ".", true},	
		
	{15, INV_WEAPON_BIG, "��", 353, 0.0, -30.0, 0.0, 1.5, WEAPON_MP5, 23,
		"��������-�������.\n\
		��������� ��� ���������: " #cPROJECT "HK MP5, HK MP7" #cWHITE ".", false},
	
	{16, INV_WEAPON_BIG, "������� �����������", 355, 0.0, -30.0, 0.0, 1.5, WEAPON_AK47, 24,
		"�������, �������� �� ���������� � ����.\n\
		��������� ��� ���������: " #cPROJECT "���, ��-74, �����, ���" #cWHITE ".", false},
		
	{17, INV_WEAPON_BIG, "AR-15", 356, 0.0, -30.0, 0.0, 1.5, WEAPON_M4, 25,
		"������������ ������������������ �������� ��� ������.\n\
		��������� ��� ���������: " #cPROJECT "M4A1, HK416" #cWHITE ".", false},
	
	{18, INV_WEAPON_BIG, "��������", 357, 0.0, -30.0, 0.0, 1.5, WEAPON_RIFLE, 24,
		"�������� ���������� ������.\n\
		��������� ��� ���������: " #cPROJECT "M14, M1 Garand" #cWHITE ".", false},
	
	{19, INV_WEAPON_BIG, "����������� ��������", 358, 0.0, -30.0, 0.0, 1.5, WEAPON_SNIPER, 24,
		"�������� ���������� ������.\n\
		��������� ��� ���������: " #cPROJECT "Barrett M98B, M2010, M110,\nBor, ���, AS50, Remington 700, M24" #cWHITE ".", false},
	
	
	{20, INV_AMMO, "������� 9 mm", 2037, 30.0, 30.0, 0.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"������� ������� 9 mm, ������� ����������� � ����������.", true},
	
	{21, INV_AMMO, "������� .44 Magnum", 2037, 30.0, 30.0, 0.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"������� ������� .44 Magnum, ������� ����������� � ������� ����������.", true},
		
	{22, INV_AMMO, "������� 12 mm", 2043, -90.0, 0.0, 0.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"������� ������� 12 mm, ������� ����������� � ����������.", true},
		
	{23, INV_AMMO, "������� 9x19 mm", 2040, -10.0, 0.0, 30.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"������� ������� 9x19 mm, ������� ����������� � ����������-���������.", true},
		
	{24, INV_AMMO, "������� 7,62�39 mm", 2040, -10.0, 0.0, 30.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"������� ������� 7,62�39 mm, ������� ����������� � �������� �����������, ���������, ����������� ���������.", true},
	
	{25, INV_AMMO, "������� 5,56x45 mm NATO", 2040, -10.0, 0.0, 30.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"������� ������� 5,56x45 mm NATO, ������� ����������� � �������������� ��������.", true},
	
	
	{26, INV_PHONE, "��������", 18874, 90.0, 180.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"��������� �������, ����������� ����������������� ���������� ������������� ����������.\n\
		��������� ��� ���������: "#cPROJECT "Iphone X, Samsung Galaxy S9, SONY Experia XZ" #cWHITE ".", true},

		
	{27, INV_BAG, "���������� �����", 11745, -30.0, 0.0, 90.0, 1.0, (5), INVALID_PARAM,
		"������� ��� �������� ��������� ���������.", false},
	
	{28, INV_BAG, "�������� �����", 19559, -30.0, 0.0, 90.0, 1.0, (8), INVALID_PARAM,
		"������� ��� �������� ��������� ���������.", false},

	{29, INV_BAG, "�������� �����", 2663, -16.0, 0.0, -55.0, 1.0, (2), INVALID_PARAM,
		"������� ��� �������� ��������� ���������.", false},
	
	{30, INV_BAG, "�������", 19624, -16.0, 0.0, -55.0, 1.0, (6), INVALID_PARAM,
		"������� ��� �������� ��������� ���������.", false},
		

	{31, INV_EAT, "���������", 2768, 0.0, 0.0, 0.0, 1.0, 5, INVALID_PARAM,
		"��� ��������, ��������� �� �������� ������� �������.", true},
		
	{32, INV_EAT, "����", 2769, 0.0, 0.0, -140.0, 0.75, 2, INVALID_PARAM,
		"������������ ����� ������������ �����.", true},
		
	{33, INV_EAT, "������", 19576, -35.0, 15.0, -70.0, 0.7, 1, INVALID_PARAM,
		"���� ������, ������� ������������� � ���� � ������ ����.", true},
		
	{34, INV_EAT, "��������", 19574, -35.0, 15.0, -70.0, 0.7, 1, INVALID_PARAM,
		"���� ���������, ������� ������������� � ���� � ������ ����.", true},
		
	{35, INV_EAT, "�����", 19578, -35.0, 15.0, -70.0, 0.7, 1, INVALID_PARAM,
		"���� ������������ ������������ ��������, ������� ������������ � ����������� �������.", true},
		
	{36, INV_EAT, "������", 19847, 30.0, -45.0, 90.0, 1.0, 5, INVALID_PARAM,
		"����� �� ������������� ����� ������ ����.", true},
		
	{37, INV_EAT, "���-���", 19346, -45.0, 0.0, 150.0, 1.5, 2, INVALID_PARAM,
		"������� � ������������� �������� � ��������.", true},
		
	{38, INV_EAT, "��������", 2355, -30.0, -30.0, 180.0, 0.6, 10, INVALID_PARAM,
		"����� �� ������� ��������.", true},
		
	{39, INV_EAT, "�����", 2220, -30.0, -30.0, 180.0, 0.6, 10, INVALID_PARAM,
		"����������� ������������ ����� � ���� ������� �������� ������.", true},
		
	{40, INV_EAT, "����� ����� ����� � �������", 2221, -50.0, 0.0, 90.0, 0.7, 5, INVALID_PARAM,
		"����� �� ������� � ������ � ����������� � ����.", true},
		
	{41, INV_EAT, "������� ����� ����� � �������", 2223, -50.0, 0.0, 90.0, 0.7, 8, INVALID_PARAM,
		"������������� ������� � ������ ����.", true},
	
	{42, INV_EAT, "������� ����� ����� � �������", 2222, -50.0, 0.0, 90.0, 0.7, 10, INVALID_PARAM,
		"��������� ����� �������� � ������ ����.", true},
		
	
	{43, INV_DRINK, "������ � ����", 19835, -40.0, 0.0, 170.0, 0.7, 5, INVALID_PARAM,
		"��������� ���� �� ������������ ����� � �������� ����������.", true},
	
	{44, INV_DRINK, "��������� � ������� �Sprunk�", 1546, 0.0, 0.0, 260.0, 0.8, 5, INVALID_PARAM,
		"�������������� ������������ ������� � �������� ����������.", true},
		
	{45, INV_DRINK, "��������� � ������� �Burger Shot�", 2647, 0.0, 0.0, 260.0, 0.8, 5, INVALID_PARAM,
		"�������������� ������������ ������� � �������� ����������.", true},
	
	{46, INV_DRINK, "�������� ���", 19564, 0.0, 0.0, 30.0, 1.0, 5, INVALID_PARAM,
		"��� ������� �� �����.", true},
		
	{47, INV_DRINK, "������������ ���", 19563, 0.0, 0.0, 30.0, 1.0, 5, INVALID_PARAM,
		"��� ������� �� ����������.", true},
		
	{48, INV_DRINK, "��������� � ����� �Sprunk�", 2601, 0.0, 0.0, -70.0, 0.7, 5, INVALID_PARAM,
		"�������������� ������������ ������� � �������� �����.", true},
	
	{49, INV_DRINK, "����", 2958, 0.0, 0.0, 30.0, 0.9, 15, INVALID_PARAM,
		"�������� ���������������� �������.", true},
		
	{50, INV_DRINK, "������� ����", 1544, 0.0, 0.0, 30.0, 0.9, 15, INVALID_PARAM,
		"�������� ���������������� �������.", true},
		
	{51, INV_DRINK, "���", 1950, 0.0, 0.0, 30.0, 0.9, 15, INVALID_PARAM,
		"���������������� �������.", true},
		
	{52, INV_DRINK, "�����", 1668, 0.0, 0.0, 30.0, 0.9, 25, INVALID_PARAM,
		"������� ����������� �������", true},
		
	{53, INV_DRINK, "�����", 1669, 0.0, 0.0, 30.0, 0.9, 25, INVALID_PARAM,
		"������� ����������� �������.", true},
		
	{54, INV_DRINK, "������", 1520, 0.0, 0.0, 30.0, 0.9, 25, INVALID_PARAM,
		"������� ����������� �������.", true},
		
	{55, INV_DRINK, "������", 19820, 0.0, 0.0, 30.0, 0.9, 25, INVALID_PARAM,
		"������� ����������� �������.", true},
	
	{56, INV_DRINK, "������", 19821, 0.0, 0.0, 30.0, 0.9, 25, INVALID_PARAM,
		"������� ����������� �������.", true},
	
	{57, INV_DRINK, "�����", 19823, 0.0, 0.0, 30.0, 0.9, 25, INVALID_PARAM,
		"������� ����������� �������.", true},
	
	{58, INV_DRINK, "������� ����", 19822, 0.0, 0.0, 30.0, 0.9, 20, INVALID_PARAM,
		"����������� �������.", true},
		
	{59, INV_DRINK, "����� ����", 19824, 0.0, 0.0, 30.0, 0.9, 20, INVALID_PARAM,
		"����������� �������.", true},
	
	{60, INV_DRINK, "����� ����", 1667, 0.0, 0.0, 30.0, 0.9, 15, INVALID_PARAM,
		"����������� �������.", true},
		
	{61, INV_DRINK, "����� �������", 19819, 0.0, 0.0, 30.0, 0.9, 15, INVALID_PARAM,
		"����������� �������.", true},
	
	{62, INV_DRINK, "����� �����������", 19818, 0.0, 0.0, 30.0, 0.9, 15, INVALID_PARAM,
		"����������� �������.", true}, 
		
	{63, INV_DRINK, "��������", 1666, 0.0, 0.0, 30.0, 0.9, 15, INVALID_PARAM,
		"����������� �������.", true}, 

	
	{64, INV_ATTACH, "�����", INVALID_PARAM, 220.0, 90.0, 0.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"�������� ����, ��������� �� �������� ���������.", true},
	
	{65, INV_ATTACH, "�������", INVALID_PARAM, 60.0, 180.0, 180.0, 0.8, INVALID_PARAM, INVALID_PARAM,
		"�������� ���� � ���� �������.", true},
	
	{66, INV_ATTACH, "�����", INVALID_PARAM, 120.0, 40.0, 80.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"�������� ���� � ��������� ������� ��������.", true},
	
	{67, INV_ATTACH, "����", INVALID_PARAM, 10.0, 0.0, 90.0, 0.65, INVALID_PARAM, INVALID_PARAM,
		"���������.", true},
	
	{68, INV_ATTACH, "������ �� ����", INVALID_PARAM, -45.0, 45.0, 170.0, 0.8, INVALID_PARAM, INVALID_PARAM,
		"�������� �����, ������� ��������� ����� ����.", true},
		
	{69, INV_ATTACH, "�����", INVALID_PARAM, -10.0, -90.0, 30.0, 0.8, INVALID_PARAM, INVALID_PARAM,
		"�������� ����, ���������� �� �����.", true},
		
	{70, INV_ATTACH, "������������ ����", INVALID_PARAM, -10.0, 0.0, 30.0, 0.5, INVALID_PARAM, INVALID_PARAM,
		"����, ������������ �������, ������� �������� ��������� �������� ����� � ������� �����.", true},
		
	{71, INV_ATTACH, "�������������", INVALID_PARAM, 0.0, 45.0, 180.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"������������� ������ � ����������������� ����������������.", false},
		
	{72, INV_ATTACH, "��������", INVALID_PARAM, 0.0, 45.0, 180.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"���������� ��� ������������� ������������� �������� ����������.", true},
		
	{73, INV_ATTACH, "����������� ����", INVALID_PARAM, -10.0, 0.0, 30.0, 0.5, INVALID_PARAM, INVALID_PARAM,
		"����, � ������� ��� ������� ������� ������������ ������������� ��������� ������������ ����������.", true},
		
	
	{74, INV_ATTACH, "������", 19773, 0.0, 0.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"����� ��� ������� ������� �������������� ������.", true},
		
	{75, INV_ATTACH, "���������", 19878, -60.0, 180.0, 160.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"�����, ��������� �� ������, ������� �������� ��������� ���� �����, \n\
		������������� �� ����� ���������� ��������.", false},
		
	{76, INV_ATTACH, "�������", 18641, 0.0, 90.0, 0.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"��������� ������� �������� ����� ��� ��������������� �������������.", true},
		
	{77, INV_ATTACH, "�������", 2916, -50.0, 0.0, 0.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"���������� ������ ��� ���������� ���������� ����������.", false},
		
	{78, INV_ATTACH, "������������� ���", 2114, -60.0, 180.0, 160.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"���������� ������ ��� ���������� ���������� ����������.", false},
		
	{79, INV_ATTACH, "������������� �������", 2711, 60.0, 60.0, -90.0, 0.6, INVALID_PARAM, INVALID_PARAM,
		"���������� ��� ��������� ����������.", true},
		
	{80, INV_ATTACH, "������", 18632, 0.0, 360.0, 0.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"���������� � ���� ������� ������ ��� ����� ����.", false},
		
	{81, INV_ATTACH, "������� ����", 19627, 90.0, 0.0, 0.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"���������� � ���� ������� ������ ��� ����� ����.", true},
		
	{82, INV_ATTACH, "�������", 18635, 0.0, 0.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"������� � �����������.", true},
		
	{83, INV_ATTACH, "��������� ����", 18633, 90.0, -90.0, 0.0, 1.3, INVALID_PARAM, INVALID_PARAM,
		"���� ��� ������� �����.", true},
		
	{84, INV_ATTACH, "�������", 19631, 260.0, 90.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"������ ������� ����������.", false},
		
	{85, INV_ATTACH, "������", 19622, 0.0, 0.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"���������� ��� ������� ������.", false},
		
	{86, INV_ATTACH, "��������", 18644, 0.0, 0.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"������ ��������� ����������, ��������������� ��� ������������ � \n������������ �������� ������� � �������.", true},
		
	{87, INV_ATTACH, "������", 18890, 0.0, 0.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"�������������������� ����������.", false},
		
	{88, INV_ATTACH, "��� ���������", 335, 90.0, 0.0, -200.0, 1.0, INV_FUNC_KNIFE, INVALID_PARAM,
		"�������, ��� ������� ���������� ������������� ��� � ������� ������ �������.", true},
		
	{89, INV_ATTACH, "�����", 18638, 0.0, 90.0, 230.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"������ ����������� �����.", false},
		
	{90, INV_ATTACH, "������ �����", 19801, 0.0, 0.0, 180.0, 0.7, INV_FUNC_HIDDEN_NAME, INVALID_PARAM,
		"��������� ������ �����.", true}, // @INV_FUNC_HIDDEN_NAME
		
	{91, INV_ATTACH, "����������", 19472, 90.0, 120.0, 0.0, 1.0, INV_FUNC_HIDDEN_NAME, INVALID_PARAM,
		"�������� �������������� ������ ������� �������.", true}, // @INV_FUNC_HIDDEN_NAME
	
	
	{92, INV_REPAIR, "���� � �������������", 19921, 260.0, 180.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"������� ���� � ������� ���������� ��� �������� �������������� \n\
		������� ��������������.", false},
		
	{93, INV_HEALTH, "����� � ������", 11748, 90.0, 220.0, 0.0, 0.8, INVALID_PARAM, INVALID_PARAM,
		"����� ��� ��������� ���.", true},
		
		
	{94, INV_SMOKE, "�������� �Red Sticks�", 19896, 90.0, 220.0, 0.0, 0.5, INVALID_PARAM, INVALID_PARAM,
		"������� ����� � ����������.", true},
	
	{95, INV_SMOKE, "�������� �C/K�", 19897, 90.0, 220.0, 0.0, 0.5, INVALID_PARAM, INVALID_PARAM,
		"����� ����� � ����������.", true},
		
	{96, INV_SMOKE, "��������� ������", 3044, -320.0, -70.0, 0.0, 0.3, INV_FUNC_SINGLE_SMOKE, INVALID_PARAM,
		"������� �� ������� ������.", true},
		
		
	{97, INV_OBJECT, "������� �����", 19831, -20.0, 0.0, 220.0, 1.2, INVALID_PARAM, INVALID_PARAM,
		"��������� ��� ������������� ���� �� �����, ����.", false},
		
	{98, INV_OBJECT, "������������� �����", 1481, -20.0, 0.0, 220.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"��������� ��� ������������� ���� �� �����, ����.", false},
		
		
	{99, INV_ATTACH, "������ �������", 2102, -20.0, 0.0, 220.0, 1.0, INV_FUNC_SOUND, INVALID_PARAM,
		"��� ����������� �����������.", true},
		
	{100, INV_ATTACH, "������� �������", 2226, -20.0, 0.0, 220.0, 1.0, INV_FUNC_SOUND, INVALID_PARAM,
		"��� ����������� �����������.", true},
	
	
	{101, INV_ATTACH, "�������������", INVALID_PARAM, 60.0, -20.0, 0.0, 0.5, INVALID_PARAM, INVALID_PARAM,
		"�������, ����������� � ����������� ��������.", true},
		
		
	{102, INV_ATTACH, "����� ��� ������� ���", INVALID_PARAM, 10.0, 0.0, -110.0, 0.7, INV_FUNC_HIDDEN_NAME, INVALID_PARAM,
		"�������, ����������� � ����������� ��������.", true},
	
	{103, INV_ATTACH, "����", INVALID_PARAM, 60.0, -20.0, 0.0, 0.5, INV_FUNC_HIDDEN_NAME, INVALID_PARAM,
		"������� ����� ������ ���������� ������� ������.", true},
	
	
	{104, INV_RADIO, "�����", 2967, 260.0, 30.0, 180.0, 0.8, INV_FUNC_RADIO_LOW, INVALID_PARAM,
		"���������� �����-���������� ����������.", true},
		
	{105, INV_RADIO, "���������� �����", 19942, 0.0, 0.0, 200.0, 0.8, INV_FUNC_RADIO_HIGH, INVALID_PARAM,
		"���������� ���������� �����-���������� ����������.", true},
		
		
	{106, INV_ATTACH, "�������", 19893, -10.0, 0.0, -160.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"���������� ������������ ���������.", false},
		
		
	{107, INV_BAG, "�����", 3026, 180.0, 0.0, 0.0, 1.0, (4), INVALID_PARAM,
		"������������������ ����� ��� �������� ���������.", false},
		
		
	{108, INV_FUEL, "��������", 1650, 0.0, 0.0, 30.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"�������� � ��������� ��������� �� 5 ������.", false},
		
		
	{109, INV_ATTACH, "˸���� ����������", 373, -90.0, 200.0, 310.0, 1.8, INV_FUNC_ARMOUR_LIGHT, INVALID_PARAM,
		"������� �������������� ������ ��������, �������������� ������ ������� ����� ��������.", false},
	
	{110, INV_ATTACH, "������� ����������", 19515, 0.0, -90.0, 0.0, 0.9, INV_FUNC_ARMOUR_HEAVY, INVALID_PARAM,
		"������� �������������� ������ ��������, �������������� ������ ������� ����� ��������.", false},
		
		
	{111, INV_CHEMICAL, "���������� �������", 19570, -10.0, -10.0, 0.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"���������� ���������� �����, ��������� �� ������ ������������� ������������ ��������.", false},
		
		
	{112, INV_LIGHTER, "���������", 19995, 90.0, 0.0, 10.0, 0.8, INVALID_PARAM, INVALID_PARAM,
		"���������� ��� ��������� ����.", false},
		
		
	{113, INV_WEAPON_SMALL, "������", 331, 90.0, 0.0, 10.0, 0.8, WEAPON_BRASSKNUCKLE, INVALID_PARAM,
		"���������� ������-������������� ������ ��� ��������� ��� �� ������� ���������.", false},
		
		
	{114, INV_DRUGS, "���������", 3027, 90.0, 0.0, 10.0, 0.8, INV_FUNC_MARIJUANA, INVALID_PARAM,
		"����� � ���������� �������.", false},
		
	{115, INV_DRUGS, "���", 2709, 90.0, 0.0, 10.0, 0.8, INV_FUNC_LSD, INVALID_PARAM,
		"������� � ����������.", false},
	
	{116, INV_DRUGS, "������", 1575, 90.0, 0.0, 10.0, 0.8, INV_FUNC_COCAINE, INVALID_PARAM,
		"����� � ����� ��������.", false}, 
		
		
	{117, INV_WEAPON_SMALL, "����������� ���������", 365, 0.0, -30.0, 0.0, 1.5, WEAPON_SPRAYCAN, INVALID_PARAM,
		"���������� ��� ���������� ������ ������� ��� ������, ����������� ��������������� � ����.", true},
	
	{118, INV_WEAPON_SMALL, "�����������", 367, 0.0, -30.0, 0.0, 1.5, WEAPON_CAMERA, INVALID_PARAM,
		"���������� ��� ����������� ����������� �����������.", true},
		
	{119, INV_WEAPON_SMALL, "�������", 367, 0.0, -30.0, 0.0, 1.5, WEAPON_PARACHUTE, INVALID_PARAM,
		"���������� ������ ��� ���������� �������� �������� � �������.", true}
};
