/*!
	@brief Серверные пикапы
	@author Found (evg.savosin)
	@date 16.12.2016
*/

// Constants
const MAX_ENTRY_NAME = 64,
	  MAX_EXIT_NAME = 32,
	  MAX_ENTER_POS = 4;

// Structures
enum E_ENTER_DATA 
{
	e_entry_name					[MAX_ENTRY_NAME],
	e_exit_name						[MAX_EXIT_NAME],
	Float: e_entry_pos				[MAX_ENTER_POS],
	e_entry_int,
	e_entry_world,
	Float: e_exit_pos				[MAX_ENTER_POS],
	e_exit_int,
	e_exit_world
}

new const enter_list				[		][	E_ENTER_DATA	] =
{
	{"Автосалон «Grotti»", "Выход", 
		{1380.2137, 1460.4408, 2171.8208, 92.6726}, INT_OTHER, WORLD_OTHER + 1, 
		{1114.0680, -922.5804, 43.3906, 176.9366}, 0, 0 
	},
	
	{"Автосалон «Grotti»", "Выход", 
		{1380.2336, 1463.6936, 2171.8208, 92.6726}, INT_OTHER, WORLD_OTHER + 1, 
		{1117.3232, -922.5692, 43.3906, 176.9366}, 0, 0 
	},
	
	{"Мотосалон «Legendary Motorcycle»", "Выход", 
		{482.6950, 1342.3087, 2514.7893, 267.8041}, INT_OTHER, WORLD_OTHER + 2, 
		{2131.7515, -1151.2361, 24.0690, 3.6617}, 0, 0 
	},
	
	{"Веломагазин «Mr.Grant's Bike Shed»", "Выход", 
		{1943.6735, 1934.4807, 3272.2026, 269.6841}, INT_OTHER, WORLD_OTHER + 3, 
		{2139.4226, -1191.9657, 23.9922, 271.5715}, 0, 0 
	},
	
	{"Транспортное агенство", "Выход", 
		{833.7428, 2548.8691, 2610.9063, 176.1882}, INT_OTHER, WORLD_OTHER + 4, 
		{1830.2181, -1172.0491, 24.2656, 180.4534}, 0, 0 
	},
	
	{"Банк Лос-Сантоса", "Выход", 
		{-646.4005, 2706.2766, 2501.5398, 272.7942}, INT_OTHER, WORLD_OTHER + 5, 
		{1571.4259, -1336.3350, 16.4844, 318.3499}, 0, 0 
	},
	
	{"Бизнес агенство", "Выход", 
		{385.8360, 1075.7019, 1103.5758, 272.9625}, INT_OTHER, WORLD_OTHER + 6, 
		{1473.3180, -1263.9617, 14.5625, 93.4911}, 0, 0 
	},
	
	{"Центр лицензирования", "Выход", 
		{243.6289, 1852.1804, 1503.9016, 359.9250}, INT_OTHER, WORLD_OTHER + 7, 
		{1809.8837, -1166.3527, 24.2266, 171.7548}, 0, 0 
	},
	
	{"Оружейный магазин", "Выход", 
		{-1504.4309, 97.9461, 3201.9858, 272.9625}, INT_OTHER, WORLD_AMMUNATION, 
		{1368.7234, -1279.8346, 13.5469, 87.1303}, 0, 0 
	},
	
	/// LSPD - Headquarters
	{"Los Santos Police Department", "Выход", 
		{-337.1004, 2513.4690, 1504.4490, 357.7037}, INT_OTHER, WORLD_PD_HEADQUARTERS, 
		{1555.5004, -1675.4457, 16.1953, 88.9079}, 0, 0 
	},
	
	{"Дверь", "Дверь", // к камерам
		{-723.3824, 2534.0193, 1501.4010, 0.5470}, INT_OTHER, WORLD_PD_HEADQUARTERS, 
		{-325.3830, 2523.5588, 1504.4490, 89.5345}, INT_OTHER, WORLD_PD_HEADQUARTERS
	},
	
	{"Лифт", "Лифт", // первый - второй этаж
		{1060.0964, 1409.7311, 1504.2689, 89.5346}, INT_OTHER, WORLD_PD_HEADQUARTERS, 
		{-331.0851, 2529.6577, 1504.4490, 355.8471}, INT_OTHER, WORLD_PD_HEADQUARTERS
	},
	
	{"Лифт", "Лифт", // первый - нулевой
		{-115.1623, 1118.5803, 1604.0436, 274.5714}, INT_OTHER, WORLD_PD_HEADQUARTERS, 
		{-343.1849, 2529.6599, 1504.4490, 359.9437}, INT_OTHER, WORLD_PD_HEADQUARTERS
	},
	
	{"Дверь", "Дверь", // к конференц. залу
		{1076.7849, 1887.7170, 1504.2687, 98.0416}, INT_OTHER, WORLD_PD_HEADQUARTERS, 
		{1073.5496, 1390.2377, 1504.2689, 358.3773}, INT_OTHER, WORLD_PD_HEADQUARTERS
	},
	
	{"Дверь", "Дверь", // гараж
		{1912.2114,246.8875,2786.2532,185.5010}, INT_OTHER, WORLD_PD_HEADQUARTERS, 
		{-722.3141, 2539.4531, 1501.4010, 181.6554}, INT_OTHER, WORLD_PD_HEADQUARTERS
	},
	
	/// LSPD - 64 Saints
	{"Los Santos Police Department", "Выход", 
		{1091.3815, 1939.3986, 1504.2787, 57.2143}, INT_OTHER, WORLD_PD_64_SAINTS, 
		{2763.0400, -1448.0881, 31.1719, 131.4749}, 0, 0 
	},
	
	{"Дверь", "Дверь", 
		{1076.2743, 1939.3268, 1504.2787, 271.5363}, INT_OTHER, WORLD_PD_64_SAINTS, 
		{1075.4232, 2439.5039, 1504.2792, 90.1379}, INT_OTHER, WORLD_PD_64_SAINTS
	},
	
	{"Дверь", "Дверь", // гараж
		{1912.3300, 247.0147, 2786.2532, 179.9764}, INT_OTHER, WORLD_PD_64_SAINTS, 
		{1065.0920, 2452.3022, 1500.7565, 184.4288}, INT_OTHER, WORLD_PD_64_SAINTS
	},
	

	/// LSPD - 96 Verona
	{"Los Santos Police Department", "Выход", 
		{898.3086, 889.5090, 1503.8021, 87.6782}, INT_OTHER, WORLD_PD_96_VERONA, 
		{1009.9449, -1597.7904, 15.1765, 358.0874}, 0, 0 
	},

	{"Дверь", "Дверь", 
		{1382.5408, 899.5448, 1503.8021, 0.3275}, INT_OTHER, WORLD_PD_96_VERONA, 
		{883.5386, 905.0562, 1503.8021, 178.5691}, INT_OTHER, WORLD_PD_96_VERONA
	},
	
	{"Дверь", "Дверь", // гараж
		{1912.2114, 246.8875, 2786.2532, 185.5010}, INT_OTHER, WORLD_PD_96_VERONA, 
		{1385.6017, 902.4413, 1503.8021, 86.8083}, INT_OTHER, WORLD_PD_96_VERONA
	},
	
	/// Los Santos County Sheriff's Department - Blueberry
	{"Los Santos County Sheriff's Department", "Выход", 
		{353.6264, 2306.9590, 1504.3427, 3.5635}, INT_OTHER, WORLD_SD_BLUEBERRY, 
		{311.9312, -176.5795, 2.0558, 90.1146}, 0, 0 
	},
	
	{"Los Santos County Sheriff's Department", "Выход", 
		{376.5670, 2318.4075, 1504.3427, 92.5509}, INT_OTHER, WORLD_SD_BLUEBERRY, 
		{319.0999, -199.2349, 1.5781,185.8784}, 0, 0 
	},
	
	{"Los Santos County Sheriff's Department", "Выход", 
		{330.1279, 2319.3662, 1504.3427, 275.8527}, INT_OTHER, WORLD_SD_BLUEBERRY, 
		{317.6564, -154.0728, 1.5781, 358.0171}, 0, 0 
	},
	
	{"Дверь", "Дверь", 
		{366.8527, 2968.7778, 1500.9039, 0.3600}, INT_OTHER, WORLD_SD_BLUEBERRY, 
		{368.1190, 2325.0059, 1504.3407, 176.5484}, INT_OTHER, WORLD_SD_BLUEBERRY
	},
	
	{"Дверь", "Дверь", // гараж
		{1912.2114,246.8875,2786.2532,185.5010}, INT_OTHER, WORLD_SD_BLUEBERRY, 
		{1821.9009, 1391.4354, 3124.9934, 269.2258}, INT_OTHER, WORLD_SD_BLUEBERRY
	},
	
	/// Los Santos County Sheriff's Department - Los Santos
	{"Los Santos County Sheriff's Department", "Выход", 
		{-354.8371, 809.2133, 2000.9688, 277.3491}, INT_OTHER, WORLD_SD_LOSSANTOS, 
		{2402.5212, -1950.4762, 13.5707, 277.3726}, 0, 0 
	},
	
	{"Дверь", "Дверь", 
		{2377.5854, 546.7365, 2500.9688, 357.5867}, INT_OTHER, WORLD_SD_LOSSANTOS, 
		{-339.9889, 804.2255, 2000.9688, 352.5499}, INT_OTHER, WORLD_SD_LOSSANTOS
	},
	
	{"Дверь", "Дверь", 
		{-177.2724, 737.1098, 1901.6416, 270.1425}, INT_OTHER, WORLD_SD_LOSSANTOS, 
		{-339.9989, 813.5360, 2000.9688, 170.8382}, INT_OTHER, WORLD_SD_LOSSANTOS
	},
	
	{"Лифт", "Лифт", 
		{1836.7583, 1391.4119, 3124.9934, 91.2508}, INT_OTHER, WORLD_SD_LOSSANTOS, 
		{-349.5937, 789.3700, 2000.9688, 1.3234}, INT_OTHER, WORLD_SD_LOSSANTOS
	},
	
	{"Дверь", "Дверь", // гараж
		{1821.6306,1391.5322,3124.9934,270.7925}, INT_OTHER, WORLD_SD_LOSSANTOS, 
		{1912.2859, 246.8614, 2786.2532, 177.1147}, INT_OTHER, WORLD_SD_LOSSANTOS
	},
	
	/// San Andreas News
	{"San Andreas News", "Выход", 
		{13.5890, -13.1048, 3007.6582, 86.8875}, INT_OTHER, WORLD_SAN, 
		{1675.5294, -1633.2526, 14.2266, 272.0928}, 0, 0 
	},
	
	{"Лифт", "Лифт", 
		{-28.0290, -16.8988, 3007.6511, 93.8278}, INT_OTHER, WORLD_SAN, 
		{0.6887, -18.8359, 3007.6418, 273.5892}, INT_OTHER, WORLD_SAN
	},
	
	{"Дверь", "Дверь", 
		{-65.3777, -226.3172, 3182.4495, 356.6233}, INT_OTHER, WORLD_SAN, 
		{-37.6592, -25.7236, 3007.5723, 356.9366}, INT_OTHER, WORLD_SAN
	},
	
	/// National Park Service
	{"National Park Service", "Выход", 
		{175.8497, 1414.4241, 1504.0613, 354.7666}, INT_OTHER, WORLD_NPS, 
		{-2049.1563, -2367.1230, 30.6099, 226.4159}, 0, 0 
	},
	
	{"Дверь", "Дверь", 
		{-11.3270, 2025.2249, 1504.0242, 357.2499}, INT_OTHER, WORLD_NPS, 
		{190.0168, 1411.6841, 1508.0090, 274.2158}, INT_OTHER, WORLD_NPS
	},
	
	{"Дверь", "Дверь", // вход в камеры
		{205.6524, 2222.1853, 2368.6855, 1.9500}, INT_OTHER, WORLD_NPS, 
		{194.7538, 1422.8959, 1504.0613, 180.8651}, INT_OTHER, WORLD_NPS
	},
	
	{"National Park Service", "Дверь", // вход с черного входа
		{194.7538, 1422.8959, 1504.0613, 180.8651}, INT_OTHER, WORLD_NPS, 
		{-2051.8135, -2347.6711, 30.6250, 47.6971}, 0, 0 
	},
	
	/// Prison
	{"Twin Towers Correctional Facility", "Выход", 
		{-1679.7427, 2013.1841, 2599.8535, 229.7222}, INT_OTHER, WORLD_PRISON, 
		{1797.3578, -1578.9579, 14.0850, 280.1693}, 0, 0 
	},
	
	{"Дверь", "Дверь", 
		{-1552.8959, 1991.3568, 1144.6448, 269.5158}, INT_OTHER, WORLD_PRISON, 
		{-1666.7133, 1991.9200, 2603.2654, 92.8643}, INT_OTHER, WORLD_PRISON
	},
	
	{"Дверь", "Дверь", 
		{-1537.5586, 1991.4830, 1140.3594, 271.7092}, INT_OTHER, WORLD_PRISON, 
		{-1927.8605, 1993.0045, 1115.5806, 92.4808}, INT_OTHER, WORLD_PRISON
	},
	
	{"Дверь", "Дверь", 
		{-1944.5135, 1993.0940, 1115.5806, 269.8292}, INT_OTHER, WORLD_PRISON, 
		{-1660.6633, 1984.3373, 2599.8726, 357.5399}, INT_OTHER, WORLD_PRISON
	},
	
	{"Twin Towers Correctional Facility", "Выход", 
		{-1930.0687, 1991.2993, 1115.5806, 1.9500}, INT_OTHER, WORLD_PRISON, 
		{1772.5463, -1548.5426, 9.9133, 43.9604}, 0, 0 
	},
	
	/// Los Santos Government
	{"Los Santos City Hall", "Выход", 
		{1973.8256, 1336.3777, 2515.5623, 1.6367}, INT_OTHER, WORLD_CITYHALL, 
		{1479.4354, -1772.3387, 18.7958, 0.1167}, 0, 0 
	},
	
	{"Los Santos City Hall", "Выход", 
		{1970.8019, 1336.4213, 2515.5623, 358.8166}, INT_OTHER, WORLD_CITYHALL, 
		{1482.6913, -1772.3053, 18.7958, 4.1901}, 0, 0 
	},
	
	{"Лифт", "Лифт", 
		{1970.9227, 1881.7009, 2518.9971, 358.8400}, INT_OTHER, WORLD_CITYHALL, 
		{1972.2347, 1386.4741, 2518.9971, 178.9382}, INT_OTHER, WORLD_CITYHALL
	},
	
	/// The Court of Los Santos
	{"The Court of Los Santos", "Выход", 
		{-1227.7729, 2898.9260, 1210.1230, 93.1310}, INT_OTHER, WORLD_COURT, 
		{1467.2834, -1009.8451, 26.8438, 183.7085}, 0, 0 
	},
	
	{"The Court of Los Santos", "Выход", 
		{-1227.8420, 2895.9819, 1210.1230, 89.3710}, INT_OTHER, WORLD_COURT, 
		{1456.9241, -1009.6751, 26.8438, 170.5249}, 0, 0 
	},
	
	{"Дверь", "Дверь", 
		{-1279.8872, 2273.5366, 1210.4133, 177.1050}, INT_OTHER, WORLD_COURT, 
		{-1265.1696, 2905.5305, 1210.4133, 269.8295}, INT_OTHER, WORLD_COURT
	},
	
	{"Дверь", "Дверь", 
		{-1271.2117, 2292.8433, 1210.4133, 182.7451}, INT_OTHER, WORLD_COURT, 
		{-1264.9550, 2897.2266, 1210.4133, 266.3827}, INT_OTHER, WORLD_COURT
	},
	
	/// Hospital
	{"All Saints General Hospital", "Выход", 
		{-262.0419, 821.2703, 1503.8716, 357.5633}, INT_OTHER, WORLD_HOSPITAL, 
		{1172.1543, -1321.6952, 15.3994, 268.2391}, 0, 0 
	},
	
	{"All Saints General Hospital", "Выход", 
		{-264.6501, 821.2750, 1503.8716, 1.9734}, INT_OTHER, WORLD_HOSPITAL, 
		{1172.1466, -1325.1702, 15.4070, 270.1191}, 0, 0 
	},
	
	{"Дверь", "Дверь", 
		{1515.8812, 1239.3480, 1501.2975, 359.4433}, INT_OTHER, WORLD_HOSPITAL, 
		{-262.6527, 830.9563, 1503.8716, 177.1283}, INT_OTHER, WORLD_HOSPITAL
	},
	
	/// LSFD - Headquarters
	{"Los Santos Fire Department", "Выход", 
		{180.7399, 1758.4290, 1504.0741, 87.7808}, INT_OTHER, WORLD_FD_HEADQUARTERS, 
		{676.5770, -1358.0787, 15.3109, 92.1911}, 0, 0 
	},
	
	{"Los Santos Fire Department", "Выход", 
		{180.7514, 1754.0754, 1504.0741, 86.8407}, INT_OTHER, WORLD_FD_HEADQUARTERS, 
		{676.5969, -1348.4359, 15.3109, 88.1179}, 0, 0 
	},
	
	{"Los Santos Fire Department", "Выход", 
		{675.2163, 1759.8262, 1504.0741, 91.2509}, INT_OTHER, WORLD_FD_HEADQUARTERS, 
		{719.3922, -1357.8090, 13.5738, 283.9530}, 0, 0 
	},
	
	{"Дверь", "Дверь", 
		{174.2320, 1751.4449, 1504.0741, 357.5632}, INT_OTHER, WORLD_FD_HEADQUARTERS, 
		{174.0443, 2250.5342, 1504.0741, 179.9484}, INT_OTHER, WORLD_FD_HEADQUARTERS
	},
	
	{"Дверь", "Дверь", 
		{651.2319, 1750.9911, 1504.0741, 189.9285}, INT_OTHER, WORLD_FD_HEADQUARTERS, 
		{157.2417, 1767.4817, 1504.0751, 248.2090}, INT_OTHER, WORLD_FD_HEADQUARTERS
	},
	
	{"Дверь", "Дверь", 
		{155.6331, 1756.1208, 1504.0741, 267.9492}, INT_OTHER, WORLD_FD_HEADQUARTERS, 
		{655.6837, 1760.6814, 1504.0741, 269.5392}, INT_OTHER, WORLD_FD_HEADQUARTERS
	},

	// Other
	{"Боулинг-клуб", "Выход", 
		{1365.4835, -6.4101, 1000.8930, 268.5525}, INT_OTHER, WORLD_BOWLING, 
		{1284.4285, -1585.5303, 13.5469, 313.0838}, 0, 0 
	},
	
	{"Торговый Центр", "Выход", 
		{1569.5099, 970.9589, 1009.6140, 1.6133}, INT_OTHER, WORLD_MALL, 
		{1567.9160, -1898.0970, 13.5608, 0.2951}, 0, 0 
	},

	{"Студия звукозаписи", "Выход", 
		{2212.3889, -285.0728, 2084.0779, 3.8066}, INT_OTHER, WORLD_VINYL_COUNTDOWN, 
		{816.1714, -1386.0625, 13.5967, 178.8356}, 0, 0 
	},
	
	{"Ломбард", "Выход", 
		{2063.8838, 1332.5051, 2610.8892, 357.5632}, INT_OTHER, WORLD_PAWNSHOP, 
		{1984.2722, -1762.0350, 13.5469, 359.6450}, 0, 0 
	},
	
	{"Прачечная", "Выход", 
		{2703.2302, -1093.0313, 2101.0859, 222.8286}, INT_OTHER, WORLD_LAUNDRY_1, 
		{2174.5540, -1741.8240, 13.5507, 221.6129}, 0, 0 
	},
	
	{"Портовый склад", "Выход", 
		{-23.5350, 2279.5156, 2509.0359, 356.3567}, INT_OTHER, WORLD_PORT_STOCK, 
		{2354.1294, -2288.0442, 17.4219, 229.4557}, 0, 0 
	},

	// Swimming Pool
	{"Плавательный бассейн", "Выход", 
		{3494.0496, 2064.3088, 2.0812, 176.7917}, INT_OTHER, WORLD_SWIMMING_POOL, 
		{941.1686, -1717.8074, 13.9699, 90.3252}, 0, 0 
	},
	
	{"Дверь", "Дверь", 
		{3464.3184, 2041.1052, 8.5112, 181.4917}, INT_OTHER, WORLD_SWIMMING_POOL, 
		{3464.4412, 2041.1606, 2.0812, 179.0083}, INT_OTHER, WORLD_SWIMMING_POOL
	},
	
	{"Дверь", "Дверь", 
		{3464.3433, 2032.3365, 8.5112, 355.9966}, INT_OTHER, WORLD_SWIMMING_POOL, 
		{3464.2937, 2032.2223, 2.0812, 358.5033}, INT_OTHER, WORLD_SWIMMING_POOL
	}
};

Enters_OnGameModeInit()
{
	new bool: is_interior;
	
	for (new i; i < sizeof enter_list; i++)
	{
		is_interior = enter_list[i][e_entry_int] != 0;
		if (is_interior)
		{
			strcat(enter_list[i][e_exit_name], #cPROJECT "\nH", MAX_ENTRY_NAME);
		}
		
		CreatePickupWith3DTextLabel(
			enter_list[i][e_exit_name], 
			is_interior ? INVALID_PARAM : PICKUP_MODEL, 
			enter_list[i][e_entry_pos][0], 
			enter_list[i][e_entry_pos][1], 
			enter_list[i][e_entry_pos][2], 
			enter_list[i][e_entry_world], 
			enter_list[i][e_entry_int]
		);
		
		is_interior = enter_list[i][e_exit_int] != 0;
		if (is_interior)
		{
			strcat(enter_list[i][e_entry_name], #cPROJECT "\nH", MAX_EXIT_NAME);
		}
		
		CreatePickupWith3DTextLabel(
			enter_list[i][e_entry_name], 
			is_interior ? INVALID_PARAM : PICKUP_MODEL, 
			enter_list[i][e_exit_pos][0], 
			enter_list[i][e_exit_pos][1], 
			enter_list[i][e_exit_pos][2], 
			enter_list[i][e_exit_world], 
			enter_list[i][e_exit_int]
		);
	}
}

function Enters_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{
		for (new i, world = GetPlayerVirtualWorld(playerid); i < sizeof enter_list; i++)
		{
			if (world == enter_list[i][e_entry_world]
			&& IsPlayerInRangeOfPoint(playerid, 
				FACTOR_TELEPORT_RADIUS, 
				enter_list[i][e_entry_pos][0], 
				enter_list[i][e_entry_pos][1], 
				enter_list[i][e_entry_pos][2]) 
			)
			{	
				// в инт
				Move:player(playerid, 
					enter_list[i][e_exit_pos][0], 
					enter_list[i][e_exit_pos][1], 
					enter_list[i][e_exit_pos][2],
					enter_list[i][e_exit_world], 
					enter_list[i][e_exit_int],
					true,
					enter_list[i][e_exit_pos][3]
				);
				
				return 0;
			}
			else if (world == enter_list[i][e_exit_world]
			&& IsPlayerInRangeOfPoint(playerid, 
				FACTOR_TELEPORT_RADIUS, 
				enter_list[i][e_exit_pos][0], 
				enter_list[i][e_exit_pos][1], 
				enter_list[i][e_exit_pos][2]) 
			)
			{
				// из инта
				Move:player(playerid, 
					enter_list[i][e_entry_pos][0], 
					enter_list[i][e_entry_pos][1], 
					enter_list[i][e_entry_pos][2],
					enter_list[i][e_entry_world], 
					enter_list[i][e_entry_int],
					true,
					enter_list[i][e_entry_pos][3]
				);
				
				return 0;
			}
		}
	}
	
	return 1;
}