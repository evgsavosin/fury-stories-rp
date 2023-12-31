/*!
	@brief ������������ ���� ������������ �������
	@author Flavo
	@date 05.12.2019
*/

// Macro
#define GetCrimeTimerForMinute(%0)					%0 / 60000

// Constants
const MAX_CRIME_CUSTOMER = 15;
const MAX_CRIME_BUY = 21;

// ����� �� ������ ������
const MAX_CRIME_STORAGE_TIMER = 1000 * 60 * 30; 

// ���-�� �������� � ����� ��� ������� ������
const CR_AMMO_COLT = 17; 
const CR_AMMO_DEAGLE = 7;
const CR_AMMO_SHOTGUNS = 20;
const CR_AMMO_MP5_UZI = 50;
const CR_AMMO_AK_RIFLE = 30;
const CR_AMMO_M4 = 50;

// ���-�� ����� ����� � ����� ��� ������� ������
const CR_BUY_DRUGS_GRAMM = 50;

const CR_BUY_EMPTY_VALUE = 0;

// Structures
enum
{
	CR_BUY_CAT_WEAPON = 1,
	CR_BUY_CAT_AMMO,
	CR_BUY_CAT_DRUGS,
	CR_BUY_CAT_OTHER
};

enum E_CRIME_BUY
{
	cr_buy_cat,
	cr_buy_item_id,
	cr_buy_access_type,
	cr_buy_count,
	cr_buy_value
};

enum E_CRIME_BUY_STORAGE
{
	cr_buy_location_index,
	cr_buy_customer_id,
	cr_buy_item_storage								[MAX_CRIME_BUY],
	cr_buy_timer,
	Text3D: cr_buy_3d_label
};

enum E_CRIME_BUY_LOCATION
{
	Float: cr_loc_x,
	Float: cr_loc_y,
	Float: cr_loc_z,
	bool: cr_loc_status
};

// Arrays
new crbuy_data[MAX_CRIME_BUY][E_CRIME_BUY] =				// !��������� ������ ������ ���� ���� �� ������, ������������� �� ���� ������(������, ��������� � �.�.)
{															// {���������, id � item_list, ��� �������(������, ������� � 1), ����, ����������}
	{CR_BUY_CAT_WEAPON, 8, 1, 300, CR_BUY_EMPTY_VALUE}, 						// colt45
	{CR_BUY_CAT_WEAPON, 9, 2, 550, CR_BUY_EMPTY_VALUE}, 						// silenced
	{CR_BUY_CAT_WEAPON, 10, 3, 900, CR_BUY_EMPTY_VALUE}, 						// deagle
	{CR_BUY_CAT_WEAPON, 11, 1, 800, CR_BUY_EMPTY_VALUE}, 						// shotgun
	{CR_BUY_CAT_WEAPON, 12, 4, 1750, CR_BUY_EMPTY_VALUE},						// shotgspa
	{CR_BUY_CAT_WEAPON, 13, 3, 700, CR_BUY_EMPTY_VALUE},						// uzi
	{CR_BUY_CAT_WEAPON, 14, 2, 690, CR_BUY_EMPTY_VALUE},						// tec9
	{CR_BUY_CAT_WEAPON, 15, 3, 1000, CR_BUY_EMPTY_VALUE},						// mp5
	{CR_BUY_CAT_WEAPON, 16, 4, 1800, CR_BUY_EMPTY_VALUE},						// ak47
	{CR_BUY_CAT_WEAPON, 17, 4, 2200, CR_BUY_EMPTY_VALUE},						// m4
	{CR_BUY_CAT_WEAPON, 18, 1, 1250, CR_BUY_EMPTY_VALUE}, 						// rifle
	{CR_BUY_CAT_WEAPON, 19, 4, 2700, CR_BUY_EMPTY_VALUE}, 						// sniper
	{CR_BUY_CAT_AMMO, 20, 2, 15, CR_AMMO_COLT}, 								// ������� 9mm (colt45, silenced)
	{CR_BUY_CAT_AMMO, 21, 3, 20, CR_AMMO_DEAGLE}, 								// ������� .44 magnum (deagle)
	{CR_BUY_CAT_AMMO, 22, 2, 25, CR_AMMO_SHOTGUNS}, 							// ������� 12mm (shotgun, shotgspa)
	{CR_BUY_CAT_AMMO, 23, 3, 30, CR_AMMO_MP5_UZI}, 								// ������� 9x19 (uzi, tec9, mp5)
	{CR_BUY_CAT_AMMO, 24, 4, 35, CR_AMMO_AK_RIFLE}, 							// ������� 7,62�39mm (ak47, rifle, sniper)
	{CR_BUY_CAT_AMMO, 25, 4, 40, CR_AMMO_M4}, 									// ������� 5,56x45 mm NATO (m4)
	{CR_BUY_CAT_DRUGS, 114, 2, 250, CR_BUY_DRUGS_GRAMM}, 						// ���������
	{CR_BUY_CAT_DRUGS, 115, 3, 350, CR_BUY_DRUGS_GRAMM}, 						// ���
	{CR_BUY_CAT_DRUGS, 116, 4, 500, CR_BUY_DRUGS_GRAMM} 						// ������
};

new crbuy_location[][E_CRIME_BUY_LOCATION] = 				// 4 ������� - ���� ��������� ���������(������������\�� ������������)
{
	{2011.3380, -1097.5848, 24.8225, false},				// n1 �������� � glen park
	{2337.3901, -1240.4122, 22.5000, false},				// n2 ��������� ������� ����� pig pen
	{2696.8845, -1109.8545, 69.5695, false},				// n3 ����� ���-������� �� ������ ������� ��
	{2812.6438, -1417.5109, 16.2500, false},				// n4 ��������� ����,���������� �� ������������ ���������
	{2607.6001, -2159.4045, -0.2188, false},				// n5 �������� ����� ����� �� ��������� � ��������
	{2878.2546, -2124.9199, 4.5413, false},					// n6 ����� �� ��������� �����. �������
	{2402.1206, -2560.9404, 13.6493, false},				// n7 ������ ���� �� ������� �� ������� � �����
	{2376.3677, -2015.8293, 14.8329, false},				// n8 ������� ����� ������ � �����
	{2079.2231, -2033.3358, 13.5469, false},				// n9 ������ �� ������ ����� �����
	{1599.3805, -1815.1167, 13.4252, false},				// n10 ������ � ������ �������� ����� ����� �.�
	{1295.1982, -983.8693, 32.6953, false},					// n11 ��������� ������� � ������
	{720.4148, -1163.8651, 16.5930, false},					// n12 ���������� ����� �������� ������� ����� �������
	{996.1149, -1432.6455, 13.5469, false},					// n13 ������ ����� ����� �� ������ ����� ������������
	{979.5785, -1255.6069, 16.9499, false},					// n14 ������ ����� � "��������" ��� � �����
	{2351.3625, -655.9492, 128.0547, false},				// n15 ����������� ������ �� ������� �-���������� ��
	{-261.5503, -2183.1885, 28.9719, false},				// n16 ������ � ������ �� �������
	{-576.1628, -504.6696, 25.5234, false},					// n17 ����� �������������� �� ����� ������
	{-57.3629, -224.0460, 5.4297, false},					// n18 ������ �� ������ ��������
	{165.5615, -301.0228, 1.5781, false},					// n19 ���������� �� ������ ��������
	{1323.7574, 206.1963, 19.5547, false},					// n20 ������ ���� ������ � �����������
	{2162.1689, -103.0247, 2.7500, false},					// n21 ������� �� ������ ���� � �������� ����
	{197.8168, -226.9544, 1.7786, false},					// n22 ����������� ������ ����� ������� ����� �� ������� � ������ ��������
	{2319.5488, -65.0127, 26.4844, false},					// n23 ���������� � ������� ����
	{2769.3003, -2528.3208, 13.6392, false}					// n24 ���������� � ����� ����� �������, � ������������ �����
};

new crbuy_storage[MAX_CRIMES][MAX_CRIME_CUSTOMER][E_CRIME_BUY_STORAGE];

// Functions
Clear:crbuy_storage_to_player(frac_index, pl_index)
{
	crbuy_storage[frac_index][pl_index][cr_buy_location_index] = INVALID_PARAM;
	crbuy_storage[frac_index][pl_index][cr_buy_customer_id] = 0;
	crbuy_storage[frac_index][pl_index][cr_buy_timer] = INVALID_PARAM;
	/*
	for (new i; i < MAX_CRIME_BUY; i++)
	{
		crbuy_storage[frac_index][pl_index][cr_buy_item_storage][i] = 0;
	}*/
}

Clear:crbuy_storage(index)
{
	for (new i; i < MAX_CRIME_CUSTOMER; i++)
	{
		crbuy_storage[index][i][cr_buy_location_index] = INVALID_PARAM;
		crbuy_storage[index][i][cr_buy_customer_id] = 
		crbuy_storage[index][i][cr_buy_item_storage][0] = EOS;
		crbuy_storage[index][i][cr_buy_timer] = INVALID_PARAM;
	}
	
	return 1;
}