/*!
	@brief Заголовок для системы гаражей
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

// Defines 
#define GetGarageSettings(%0,%1)			hgarage_settings[house_data[%0][hg_int_type]][%1]

// Structures
enum E_GARAGE_SETTINGS
{
	Float: hgset_pos							[	4	],
	Float: hgset_veh_pos						[	4	],
	Float: hgset_addveh_pos						[	4 	],
	Float: hgset_alt_pos						[	4	],
	hgset_furnitures
}
	
new const hgarage_settings							[	][	E_GARAGE_SETTINGS] =
{
	{
		{0.0, 0.0, 0.0, 0.0}, 
		{0.0, 0.0, 0.0, 0.0}, 
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		0
	}, // none
	
	{
		{-1573.7805, -1771.3600, 2500.9688, 182.5768}, 
		{-1573.6849, -1774.5985, 2500.6748, 360.000},
		{0.0, 0.0, 0.0, 0.0},
		{-1566.8309, -1781.6766, 2503.2654, 90.9376},
		50
	},
	
	{
		{-511.3641, 1802.1500, 1237.8551, 85.9705},
		{-515.1633, 1801.9343, 1237.5604, 270.3474},
		{0.0, 0.0, 0.0, 0.0},
		{-521.4144, 1805.1182, 1237.8551, 269.9871},
		70
	},
	
	{
		{1261.4353, -18.2565, 1000.9197, 271.8268},
		{1263.6591, -20.9642, 1000.6612, 89.8004},
		{1263.6871, -12.8559, 1000.6612, 89.8004},
		{1270.8080, -16.7009, 1000.9197, 98.5752},
		80
	}
};
	
new hgarage_static_furn							[	sizeof house_data	][2];

Clear:garage_data(index)
{
	house_data[index][hg_int_type] =
	house_data[index][hg_lock] =
	house_data[index][hg_set_furn] = 0;
	
	house_data[index][hg_text] = Text3D: INVALID_3DTEXT_ID;
	
	house_data[index][hg_veh_pos][0] =
	house_data[index][hg_veh_pos][1] =
	house_data[index][hg_veh_pos][2] =
	house_data[index][hg_veh_pos][3] =
	
	house_data[index][hg_addveh_pos][0] =
	house_data[index][hg_addveh_pos][1] =
	house_data[index][hg_addveh_pos][2] =
	house_data[index][hg_addveh_pos][3] =
	
	house_data[index][hg_pos][0] =
	house_data[index][hg_pos][1] =
	house_data[index][hg_pos][2] =
	house_data[index][hg_pos][3] = 0.0;
}

Create:garage_data(index, playerid)
{
	clean:<g_big_string>;
	
	format:g_big_string("\
		INSERT INTO " #__HGARAGE "\ 
		(g_type, g_house_id, g_pos_x, g_pos_y, g_pos_z, g_pos_angle, \ 
		g_veh_pos_x, g_veh_pos_y, g_veh_pos_z, g_veh_pos_angle, \
		g_addveh_pos_x, g_addveh_pos_y, g_addveh_pos_z, g_addveh_pos_angle, g_lock, g_set_furn) \
		VALUES \
		(%i, %i, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %i, %i)", 
		house_data[index][hg_int_type],
		house_data[index][h_id],
		house_data[index][hg_pos][0],
		house_data[index][hg_pos][1],
		house_data[index][hg_pos][2],
		house_data[index][hg_pos][3],
		house_data[index][hg_veh_pos][0],
		house_data[index][hg_veh_pos][1],
		house_data[index][hg_veh_pos][2],
		house_data[index][hg_veh_pos][3],
		house_data[index][hg_addveh_pos][0],
		house_data[index][hg_addveh_pos][1],
		house_data[index][hg_addveh_pos][2],
		house_data[index][hg_addveh_pos][3],
		0,
		0
	);

	mysql_tquery(db, g_big_string, "OnGarageCreate", "ii", index, playerid);
	return 1;
}

function OnGarageCreate(index, playerid)
{
	Create:garage(index);
	
	pformat:("" #DEFAULT " Гараж для дома с ID: " #cPROJECT "%i" #cWHITE ", успешно создан.", 
		house_data[index][h_id] 
	);
	
	psend:(playerid, C_WHITE);
	
	printf("[GARAGES]: Garage [ID:%d] has been created by %s.",
		house_data[index][h_id],
		GetCharacterName(playerid)
	);
	
	return 1;
}

Update:garage_data(index)
{
	format:g_string("\
		UPDATE " #__HGARAGE " \
		SET \
			g_pos_x = %f, \
			g_pos_y = %f, \
			g_pos_z = %f, \
			g_pos_angle = %f, \
			g_veh_pos_x = %f, \
			g_veh_pos_y = %f, \
			g_veh_pos_z = %f, \
			g_veh_pos_angle = %f, \
			g_lock = %i, \
			g_set_furn = %i \
		WHERE \
			g_house_id = %i \
		LIMIT 1",
		house_data[index][hg_pos][0],
		house_data[index][hg_pos][1],
		house_data[index][hg_pos][2],
		house_data[index][hg_pos][3],
		house_data[index][hg_veh_pos][0],
		house_data[index][hg_veh_pos][1],
		house_data[index][hg_veh_pos][2],
		house_data[index][hg_veh_pos][3],
		house_data[index][hg_lock],
		house_data[index][hg_set_furn],
		house_data[index][h_id]
	);
	
	mysql_tquery(db, g_string);
	
	return 1;
}

Remove:garage_data(index, playerid)
{
	format:g_string("DELETE FROM "  #__HGARAGE  " WHERE `g_house_id` = %i LIMIT 1",
		GetHouseId(index)
	);
	
	mysql_tquery(db, g_string, "OnGarageDelete", "ii", index, playerid);
}

function OnGarageDelete(index, playerid)
{
	pformat:("" #SUCCESS " Вы успешно удалили гараж для дома с ID: " #cPROJECT "%i" #cWHITE ".", 
		GetHouseId(index)
	);
	
	psend:(playerid, C_WHITE);
	
	printf("[GARAGES]: Garage [ID:%d] has been deleted by %s.",
		GetHouseId(index),
		GetUserName(playerid)
	);	
	
	Destroy:garage(index);
	
	Clear:garage_data(index);
	return 1;
}
