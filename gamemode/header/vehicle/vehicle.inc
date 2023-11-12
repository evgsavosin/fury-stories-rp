/*!
	@brief Заголовок системы транспорта
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
*/

// Defines
#define DIALOG_BASICVEH_COLOR "\
	" #cGRAY "Выберите цвет:\n \
	" #cWHITE "Черный\n \
	Белый\n \
	{3b4e78}Темно-синий\n \
	{193826}Темно-зеленый\n \
	{9c8d70}Бежевый\n \
	{969591}Серый\
"

#define GetVehicleInterior(%0)			(vehicle_data[%0][v_tmp_int])
#define GetVehicleId(%0)				(vehicle_data[%0][v_id])
#define GetVehicleInfo(%0,%1)			(vehicle_info[%0-400][%1])
#define GetVehicleTypeBought(%0)		(vehicle_data[%0][v_buy_type])
#define GetVehicleRent(%0,%1)			(floatround(vehicle_info[%0-400][v_cost]*PERCENT_RENT_VEHICLE*%1))
#define GetVehicleCurrentHealth(%0)		(vehicle_data[%0][v_health])
#define GetVehicleFuel(%0)				(vehicle_data[%0][v_fuel])
#define IsVehiclePayCredit(%0)			(vehicle_data[%0][v_is_credit])
#define GetVehicleModel(%0)				(vehicle_data[%0][v_model])

// Constants
const MAX_VEHICLE_WINDOWS = 4;

// Тип владельца транспорта
enum
{
	TYPE_VEH_NONE,
	TYPE_VEH_PLAYER,
	TYPE_VEH_FRACTION
};

/// Тип удаления
enum 
{
	DELVEH_BY_PLAYER,
	DELVEH_BY_SERVER
};

enum E_VEHICLE_DATA
{
	v_id,		
	v_buy_type,
	v_owner_id,						/// Владелец
	v_owner_type,		
	v_number						[32],
	Float: v_fuel,					/// Топливо
	Float: v_mileage,				/// Пробег
	Float: v_pos_x,
	Float: v_pos_y,
	Float: v_pos_z,
	Float: v_pos_angle,
	Float: v_health,
	Float: v_state,
	v_model,
	v_color							[2],
	v_time,
	v_tmp_int,
	v_int,
	v_world,
	v_spawned,						/// Заспавнена машина или нет
	bool: v_is_credit,
	v_radio, // Радиостанция
	v_siren, // Сирена
	
	/// Params
	v_engine,
	v_lock,
	v_limit,
	v_alarm,
	v_boot,
	v_hood,
	v_light,
	v_obj,
	v_window						[MAX_VEHICLE_WINDOWS],
	
	v_del_timer,					/// Таймер удаления транспорта
	v_del_type,
	
	v_desc							[MAX_PLAYER_DESC],
	
	Text3D: v_callsign
};

enum E_PLAYER_VEHICLE_DATA
{
	pv_id,
	pv_model,
	pv_server_id,
	bool: pv_delete,
};

new vehicle_data					[MAX_VEHICLES][E_VEHICLE_DATA],
	player_vehicle					[MAX_PLAYERS][E_PLAYER_VEHICLE_DATA][MAX_PLAYER_VEHICLES];

// Functions
Clear:player_vehicle(playerid)
{
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		player_vehicle[playerid][pv_id][i] =
		player_vehicle[playerid][pv_model][i] =
		player_vehicle[playerid][pv_delete][i] =
		player_vehicle[playerid][pv_server_id][i] = 0;
	}
}

Clear:vehicle_data(vehicleid)
{
	Clear:vehicle_inv_data(vehicleid);
	Clear:veh_comp_inv_data(vehicleid);
	
	/// Integer 
	vehicle_data[vehicleid][v_id] = 
	vehicle_data[vehicleid][v_owner_id] = 
	vehicle_data[vehicleid][v_owner_type] = 
	vehicle_data[vehicleid][v_model] = 
	vehicle_data[vehicleid][v_color][0] = 
	vehicle_data[vehicleid][v_color][1] = 
	vehicle_data[vehicleid][v_time] = 
	vehicle_data[vehicleid][v_spawned] =
	vehicle_data[vehicleid][v_radio] = 
	vehicle_data[vehicleid][v_siren] = 
	vehicle_data[vehicleid][v_limit] = 0;
	
	vehicle_data[vehicleid][v_tmp_int] = 0;
	vehicle_data[vehicleid][v_del_type] = 
	vehicle_data[vehicleid][v_del_timer] = INVALID_PARAM;
	
	vehicle_data[vehicleid][v_lock] = 
	vehicle_data[vehicleid][v_boot] = 
	vehicle_data[vehicleid][v_hood] = 
	vehicle_data[vehicleid][v_light] = 
	vehicle_data[vehicleid][v_alarm] =
	vehicle_data[vehicleid][v_obj] = 
	vehicle_data[vehicleid][v_engine] = VEHICLE_PARAMS_OFF;
	
	for (new i; i < MAX_VEHICLE_WINDOWS; i++)
	{
		vehicle_data[vehicleid][v_window][i] = VEHICLE_PARAMS_ON;
	}
	
	/// String
	vehicle_data[vehicleid][v_desc][0] =
	vehicle_data[vehicleid][v_number][0] = EOS;
	
	/// Float
	vehicle_data[vehicleid][v_health] =
	vehicle_data[vehicleid][v_mileage] =
	vehicle_data[vehicleid][v_state] =
	vehicle_data[vehicleid][v_fuel] = 
	vehicle_data[vehicleid][v_pos_x] = 
	vehicle_data[vehicleid][v_pos_y] = 
	vehicle_data[vehicleid][v_pos_z] = 
	vehicle_data[vehicleid][v_pos_angle] = 0.0;
	
	/// Bool
	vehicle_data[vehicleid][v_is_credit] = false;
	
	// Text3D
	if (IsValidDynamic3DTextLabel(vehicle_data[vehicleid][v_callsign]))
	{
		DestroyDynamic3DTextLabel(vehicle_data[vehicleid][v_callsign]);
	}
	
	vehicle_data[vehicleid][v_callsign] = Text3D: INVALID_3DTEXT_ID;
	
	is_admin_vehicle{vehicleid} = 0;
}

Create:vehicle_data(buy_type, owner_type, owner_id, modelid, _: color[2], Float: pos[4], playerid = INVALID_PLAYER_ID, bool: is_credit = false, days = 7, number[] = "", int = 0, world = 0)
{
	new rent_time = (buy_type == TYPE_BUY_RENT) ? gettime() + (60 * 60 * 24 * days) : 0;
	
	format:g_big_string("INSERT INTO " #__VEHICLES " \
		(\
			v_buy_type, \
			v_owner_type, \
			v_owner_id, \
			v_spawned, \
			v_model, \
			v_color, \
			v_pos_x, \
			v_pos_y, \
			v_pos_z, \
			v_pos_angle, \
			v_fuel, \
			v_buy_time, \ 
			v_rent_time, \
			v_is_credit, \
			v_number, \
			v_int, \
			v_world \
		) VALUES (\
			%i, \
			%i, \
			%i, \
			%i, \
			%i, \
			'%i|%i', \
			%f, \
			%f, \
			%f, \
			%f, \
			%f, \
			%i, \
			%i, \
			%i, \
			'%q', \
			%i, \
			%i)",
		buy_type,
		owner_type,
		owner_id,
		0,
		modelid,
		color[0],
		color[1],
		pos[0],
		pos[1],
		pos[2],
		pos[3],
		GetVehicleInfo(modelid, v_max_fuel),
		gettime(),
		rent_time,
		is_credit,
		number,
		int,
		world
	);
	
	if (playerid != INVALID_PLAYER_ID)
	{
		mysql_tquery(db, g_big_string, "OnVehicleCreateForPlayer", "dd", playerid, modelid);
	}
	else 
	{
		mysql_tquery(db, g_big_string, "OnVehicleCreateForFraction");
	}
}

function OnVehicleCreateForFraction()
{
	new id = cache_insert_id();
	
	Load:vehicle_by_id(id);
	return 1;
}


function OnVehicleCreateForPlayer(playerid, modelid)
{
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		if (player_vehicle[playerid][pv_id][i] != 0)
		{
			continue;
		}
		
		player_vehicle[playerid][pv_server_id][i] = 0;
		player_vehicle[playerid][pv_id][i] = cache_insert_id();
		player_vehicle[playerid][pv_model][i] = modelid;
		
		break;
	}
	
	return 1;
}

Update:vehicle_data(vehicleid, playerid = INVALID_PLAYER_ID)
{
	if (playerid != INVALID_PLAYER_ID)
	{
		if (!IsUserAllowQuery(playerid))
		{
			return;
		}
	}

	format:g_big_string("\
		UPDATE " #__VEHICLES " \
		SET \
			v_spawned = %i, \
			v_mileage = %f, \
			v_fuel = %f, \
			v_health = %f, \
			v_pos_x = %f, \
			v_pos_y = %f, \
			v_pos_z = %f, \
			v_pos_angle = %f, \
			v_lock = %i, \
			v_number = '%q', \
			v_int = %d, \
			v_world = %d, \
			v_color = '%d|%d', \
			v_radio = %d, \
			v_siren = %d, \
			v_desc = '%q' \
		WHERE \
			v_id = %i \
		LIMIT 1",
		vehicle_data[vehicleid][v_spawned],
		vehicle_data[vehicleid][v_mileage],
		vehicle_data[vehicleid][v_fuel],
		vehicle_data[vehicleid][v_health],
		vehicle_data[vehicleid][v_pos_x],
		vehicle_data[vehicleid][v_pos_y],
		vehicle_data[vehicleid][v_pos_z],
		vehicle_data[vehicleid][v_pos_angle],
		vehicle_data[vehicleid][v_lock],
		vehicle_data[vehicleid][v_number],
		vehicle_data[vehicleid][v_int],
		vehicle_data[vehicleid][v_world],
		vehicle_data[vehicleid][v_color][0],
		vehicle_data[vehicleid][v_color][1],
		vehicle_data[vehicleid][v_radio],
		vehicle_data[vehicleid][v_siren],
		vehicle_data[vehicleid][v_desc],
		vehicle_data[vehicleid][v_id]
	);
	
	mysql_pquery(db, g_big_string, "OnVehicleUpdate", "d", playerid);
	
	if (playerid != INVALID_PLAYER_ID)
	{
		SetUserAllowQuery(playerid, false);
	}
}

function OnVehicleUpdate(playerid)
{
	if (playerid != INVALID_PLAYER_ID)
	{
		SetUserAllowQuery(playerid, true);
	}
	
	return 1;
}

Remove:vehicle_data(vehicleid)
{
	format:g_small_string("DELETE FROM " #__VEHICLES " WHERE v_id = %i LIMIT 1",
		vehicle_data[vehicleid][v_id]
	);
	
	mysql_tquery(db, g_small_string);
	
	DestroyVehicle(vehicleid);
	Clear:vehicle_data(vehicleid);
}