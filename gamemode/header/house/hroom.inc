/*!
	@brief Заголовок для системы кастомизации
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

// Structures
new hroom_data						[	sizeof house_data 	][	MAX_ROOMS	][ E_ROOM_DATA 	];

new const hroom_coord				[][	E_ROOM_COORD	] = 
{
	{1, 1, {-2714.1694, -1508.7211, 2602.0522}},
	{1, 2, {-2711.6748, -1516.2886, 2602.0522}}
};
	
	
Update:room_data(house_index, room_index)
{
	format:g_string("UPDATE " #__ROOMS " \
		SET \
			r_roof = %i, \
			r_floor = %i, \
			r_wall = %i \
		WHERE \
			r_owner_id = %i AND \
			r_owner_type = %i AND \
			r_number = %i",
		hroom_data[house_index][room_index][r_roof],
		hroom_data[house_index][room_index][r_floor],
		hroom_data[house_index][room_index][r_wall],
		GetHouseId(house_index),
		TYPE_REN_HOUSE,
		room_index
	);
	
	mysql_tquery(db, g_string);
	
	return 1;
}