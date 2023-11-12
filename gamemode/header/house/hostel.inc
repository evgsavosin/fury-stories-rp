/*!
	@brief Заголовок для системы подъездов
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

// Типы подъездов
enum 
{
	TYPE_HOSTEL_NONE,
	TYPE_HOSTEL_LOW,
	TYPE_HOSTEL_MEDIUM,
	TYPE_HOSTEL_HIGH
}

enum E_HOSTEL_DATA
{
	hos_id,
	hos_int_type,
	Float: hos_pos								[	4 	],
	hos_pickup,
	Text3D: hos_text,
}

enum E_HOSTEL_SETTINGS // Настройки падиков
{
	hos_set_type,
	Float: hos_set_pos							[	4	],
	hos_set_houses
}

enum E_HOSTEL_HOUSE_POS
{
	hos_hp_id,
	Float: hos_hp_pos							[	4	]
}

// Подъезды
new const hostel_settings						[	][	E_HOSTEL_SETTINGS] = 
{
	{TYPE_HOSTEL_NONE, {0.0, 0.0, 0.0, 0.0}, 0}, // None
	
	{TYPE_HOSTEL_LOW, {2869.0208, 2894.2285, 2001.4849, 357.8765}, 11}, // Подъезд [Yan]
	{TYPE_HOSTEL_LOW, {-369.0622, 1754.5933, 3284.0159, 263.8988}, 12}, // Подъезд [Dima]
	{TYPE_HOSTEL_LOW, {8.8916, 2714.8457, 2273.8041, 89.9977}, 8} // Подъезд [Gaby]
};

new const hostel_house_pos						[	][	E_HOSTEL_HOUSE_POS] = // Позиции домов при создании
{
	{1, {2873.7151, 2898.8154, 2001.4849, 88.8891}},
	{1, {2867.7090, 2898.7788, 2001.4849, 270.9140}},
	{1, {2867.7075, 2909.5984, 2001.4849, 269.3708}},
	{1, {2872.0979, 2914.3586, 2001.4849, 182.9134}},
	{1, {2873.5991, 2911.4858, 2001.4849, 88.9360}},
	{1, {2872.4607, 2890.6433, 2004.9828, 359.3453}},
	{1, {2867.7146, 2893.1873, 2004.9828, 269.4178}},
	{1, {2867.7024, 2901.2893, 2004.9828, 272.2378}},
	{1, {2873.5625, 2897.8142, 2004.9828, 92.4063}},
	{1, {2867.6733, 2910.1050, 2004.9828, 271.6346}},
	{1, {2873.0474, 2912.4209, 2004.9828, 92.0929}},
	
	{2, {-367.5143, 1757.3022, 3284.0159, 179.6346}},
	{2, {-363.7169, 1757.4269, 3284.0159, 175.8744}},
	{2, {-360.8328, 1756.4934, 3284.0159, 93.4670}},
	{2, {-362.8098, 1746.8436, 3284.0159, 268.9354}},
	{2, {-360.4153, 1744.1150, 3284.0159, 359.8029}},
	{2, {-356.1369, 1744.2126, 3284.0159, 357.1278}},
	{2, {-356.0206, 1744.1201, 3287.5159, 0.7428}},
	{2, {-360.4241, 1744.1787, 3287.5159, 352.5960}},
	{2, {-362.8094, 1746.7910, 3287.5159, 267.6819}},
	{2, {-360.7762, 1756.4819, 3287.5159, 87.2236}},
	{2, {-363.6457, 1757.3025, 3287.5159, 174.0177}},
	{2, {-367.5298, 1757.4614, 3287.5159, 178.0910}},

	{3, {1.6553, 2716.7410, 2273.8041, 181.0567}},
	{3, {-0.8203, 2714.2266, 2273.8041, 269.8993}},
	{3, {-0.7122, 2704.4377, 2273.8041, 270.6710}},
	{3, {1.8319, 2701.6899, 2273.8041, 357.3201}},
	{3, {4.5798, 2706.9312, 2273.8041, 88.3323}},
	{3, {15.6461, 2709.3704, 2277.2948, 91.0073}},
	{3, {15.5137, 2703.8284, 2277.2948, 90.8623}},
	{3, {12.9128, 2701.7854, 2277.2948, 359.5131}}
};

new hostel_data 						[	MAX_HOSTELS		][	E_HOSTEL_DATA	];
	
	
Clear:hostel_data(index)
{
	hostel_data[index][hos_id] =
	hostel_data[index][hos_int_type] =
	hostel_data[index][hos_pickup] = 0;

	hostel_data[index][hos_pos][0] =
	hostel_data[index][hos_pos][1] = 
	hostel_data[index][hos_pos][2] =
	hostel_data[index][hos_pos][3] = 0.0;
	
	hostel_data[index][hos_text] = Text3D: INVALID_3DTEXT_ID;

}

Create:hostel_data(index, playerid, price)
{
	clean:<g_string>;
	
	format:g_string("INSERT INTO " #__HOSTELS " \
							(hos_int_type, hos_pos_x, hos_pos_y, hos_pos_z, hos_pos_angle) \
								VALUES \
							(%i, %f, %f, %f, %f)",
		hostel_data[index][hos_int_type],
		hostel_data[index][hos_pos][0],
		hostel_data[index][hos_pos][1],
		hostel_data[index][hos_pos][2],
		hostel_data[index][hos_pos][3]
	);
	
	mysql_tquery(db, g_string, "OnHostelCreate", "iii", index, playerid, price);
}

function OnHostelCreate(index, playerid, price)
{
	hostel_data[index][hos_id] = cache_insert_id();
	
	CreateHousesInHostel(index, price);
	Create:hostel(index);
	
	pformat:("" #SUCCESS " Подъезд с ID: " #cPROJECT "%i" #cWHITE ", успешно создан.", 
		hostel_data[index][hos_id] 
	);
	
	psend:(playerid, C_WHITE);
	
	printf("[HOSTELS]: Hostel [ID:%d] has been created by %s.",
		hostel_data[index][hos_id],
		GetCharacterName(playerid)
	);
	
	return 1;
}

Remove:hostel_delete(index, playerid)
{
	clean:<g_string>;
	
	format:g_string("DELETE FROM "  #__HOSTELS  " WHERE `hos_id` = %i LIMIT 1",
		hostel_data[index][hos_id]
	);
	
	mysql_tquery(db, g_string, "OnHostelDelete", "ii", index, playerid);
}

function OnHostelDelete(index, playerid)
{
	if (!cache_affected_rows())
	{
		return SendClientMessage(playerid, C_WHITE, !#ERROR " Неверный ID подъезда.");
	}
	
	pformat:("" #SUCCESS " Вы успешно удалили подъезд с ID: " #cPROJECT "%i" #cWHITE ".", 
		hostel_data[index][hos_id] 
	);
	
	psend:(playerid, C_WHITE);
	
	printf("[OnHostelDelete]: Hostel [ID:%d] has been deleted by %s.",
		hostel_data[index][hos_id],
		GetUserName(playerid)
	);	
	
	format:g_small_string("DELETE FROM "  #__HOUSES " WHERE h_world = %i",
		hostel_data[index][hos_id]
	);
	
	mysql_tquery(db, g_string);
	
	Destroy:hostel(index);
	Clear:hostel_data(index);

	return 1;
}