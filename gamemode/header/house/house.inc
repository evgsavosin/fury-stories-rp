/*!
	@brief Заголовок для системы домов
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

// Defines
#define GetHouseId(%0)					(house_data[%0][h_id])
#define GetHouseCommunal(%0)			(floatround(house_data[%0][h_price]*PERCENT_COMMUNAL_HOUSE))
#define GetHousePrice(%0)				(house_data[%0][h_price])
#define GetHouseDebt(%0)				(house_data[%0][h_debt])
#define GetHouseRent(%0)				(floatround(house_data[%0][h_price]*PERCENT_RENT_HOUSE))
#define GetHouseGarageExists(%0)		(house_data[%0][hg_int_type])
#define GetHouseTypeBought(%0)			(house_data[%0][h_buy_type])

#define IsHouseType(%0)					(house_data[%0][h_interior] == 0 ? TYPE_HOUSE : TYPE_APARTAMENT)
#define IsHouseBought(%0)				(house_data[%0][h_character_id] != 0)
#define IsHousePayCredit(%0)			(house_data[%0][h_is_credit])

// Structures
enum 
{
	TYPE_HOUSE_OWNER = 0,
	TYPE_HOUSE_LODGER
};

enum
{
	TYPE_HOUSE,
	TYPE_APARTAMENT
};

enum E_HOUSE_DATA 
{
	h_id, 
	h_character_id, // Айди в бд аккаунта игрока
	h_buy_type, // rent or fully
	Float: h_pos 								[	4 	], 
	h_world, 
	h_interior, 
	h_price, 
	h_int_type, // тип интерьера
	h_lock, 
	h_money, 
	h_time, // До какого оплачен дом - UNIX. 
	h_debt, // задолжность
	h_debt_count, // сколько раз можно задолжать
	Text3D: h_text, 
	h_pickup,
	bool: h_is_credit,

	// garage
	hg_int_type,
	Float: hg_veh_pos							[	4	],
	Float: hg_addveh_pos						[	4	],
	Float: hg_pos								[	4	],
	Text3D: hg_text,
	hg_lock,
	hg_set_furn
};

new house_data			[	MAX_HOUSES	][	E_HOUSE_DATA	],

	player_house		[	MAX_PLAYERS		][		MAX_PLAYER_HOUSES		];
	

Clear:house_data(index)
{
	Clear:garage_data(index);
	
	// Integer
	house_data[index][h_id] =
	house_data[index][h_character_id] =
	house_data[index][h_buy_type] =
	house_data[index][h_world] =
	house_data[index][h_interior] =
	house_data[index][h_price] =
	house_data[index][h_int_type] =
	house_data[index][h_lock] =
	house_data[index][h_money] =
	house_data[index][h_debt] =
	house_data[index][h_debt_count] =
	house_data[index][h_time] =
	house_data[index][h_pickup] = 0;
	
	house_data[index][h_text] = Text3D: INVALID_3DTEXT_ID;
	

	// Float
	house_data[index][h_pos][0] =
	house_data[index][h_pos][1] =
	house_data[index][h_pos][2] =
	house_data[index][h_pos][3] = 0;
	
	// Bool
	house_data[index][h_is_credit] = false;
}

Clear:player_house(playerid)
{
	player_house[playerid][0] =
	player_house[playerid][1] =
	player_house[playerid][2] = INVALID_PARAM;
}

Create:house_data(index, playerid = INVALID_PLAYER_ID)
{
	clean:<g_big_string>;
	format:g_big_string("\
		INSERT INTO " #__HOUSES " \
		(h_price, h_int_type, h_lock, h_pos_x, h_pos_y, h_pos_z, h_pos_angle, h_world, h_interior) \
			VALUES \
		(%i, %i, %i, %f, %f, %f, %f, %i, %i)", 
		house_data[index][h_price],
		house_data[index][h_int_type],
		house_data[index][h_lock],
		house_data[index][h_pos][0],
		house_data[index][h_pos][1],
		house_data[index][h_pos][2],
		house_data[index][h_pos][3],
		house_data[index][h_world],
		house_data[index][h_interior]
	);

	mysql_tquery(db, g_big_string, "OnHouseCreate", "ii", index, playerid);

	return 1;
}

stock Update:house_int(index, column[], _: value, bool: is_pquery = false)
{
	clean:<g_string>;
	
	format:g_string("UPDATE `"#__HOUSES"` SET `%s` = %d WHERE `h_id` = %d LIMIT 1",
		column,
		value,
		house_data[index][h_id]
	);
	
	return !is_pquery ? mysql_tquery(db, g_string) : mysql_pquery(db, g_string);
}

stock Update:house_string(index, column[], value[])
{
	format:g_string("UPDATE `"#__HOUSES"` SET `%s` = '%q' WHERE `h_id` = %d LIMIT 1",
		column,
		value,
		house_data[index][h_id]
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:house_float(index, column[], Float: value)
{
	format:g_string("UPDATE `"#__HOUSES"` SET `%s` = %f WHERE `h_id` = %d LIMIT 1",
		column,
		value,
		house_data[index][h_id]
	);
	
	return mysql_tquery(db, g_string);
}