/*!
	@brief Заголовок для приложения Fuber
	@author Found (evg.savosin)
	@date 28.08.2019
*/

// Defines
#define FUBER_BASE_COST					(40)
#define FUBER_PER_FIFTY_COST			(50)
#define FUBER_INCREASE_COST				(5)
#define FUBER_BONUS_COST				(10)
#define FUBER_INCREASE_LEVELS			(5)
#define FUBER_AVERAGE_SPEED				(60)
#define MAX_FUBER_WISH_LENGTH			128
#define MAX_FUBER_REPUTATION			5
#define MIN_FUBER_REPUTATION			-5

#define GetFuberDriverReputation(%0)	character_data[%0][c_fuber_reputation]
#define GetFuberDriverBalance(%0)		character_data[%0][c_fuber_balance]
#define GetFuberOrderStatus(%0)			fuber_order_status[fuber_orders[%0][fub_status]]
#define GetFuberMethodPayment(%0) 		character_data[%0][c_fuber_method_payment]
#define GetFuberOrderFullCost(%0)		fuber_orders[%0][fub_cost]
#define GetFuberDriverVehicleId(%0)		fuber_driver_vehicle_id[%0]
#define GetFuberDriverOrderIndex(%0)	fuber_driver_order_index[%0]
#define GetFuberPassengerOrderIndex(%0)	fuber_passenger_order_index[%0]
#define GetFuberReputation(%0) 			character_data[%0][c_fuber_reputation]

#define SetFuberDriverOrderIndex(%0,%1)	fuber_driver_order_index[%0]=%1
#define SetFuberPassengerOrderIndex(%0,%1) fuber_passenger_order_index[%0]=%1 
#define SetFuberDriverVehicleId(%0,%1)	fuber_driver_vehicle_id[%0]=%1
#define SetFuberMethodPayment(%0,%1) 	character_data[%0][c_fuber_method_payment]=%1;Update:character_int(%0,"c_fuber_method_payment",%1)
#define SetFuberDriverBalance(%0,%1) 	character_data[%0][c_fuber_balance]=%1;Update:character_int(%0,"c_fuber_balance",%1)
#define SetFuberReputation(%0,%1) 		character_data[%0][c_fuber_reputation]=%1;Update:character_int(%0,"c_fuber_reputation",%1)

#define HasFuberDriverVehicle(%0)		(fuber_driver_vehicle_id[%0] != INVALID_VEHICLE_ID)
#define HasFuberPassengerOrder(%0)		(fuber_passenger_order_index[%0] != INVALID_PARAM)
#define HasFuberDriverOrder(%0)			(fuber_driver_order_index[%0] != INVALID_PARAM)

#define IsFuberOrderValid(%0)			(fuber_orders[%0][fub_passenger_id] != INVALID_PLAYER_ID)

// Structures
enum
{
	FUB_ORDER_SEARCH = 0,
	FUB_ORDER_AWAITING,
	FUB_ORDER_ARRIVED,
	FUB_ORDER_WAY
};

new const fuber_order_status		[][] = 
{
	"Поиск водителя",
	"Водитель скоро приедет",
	"Водитель приехал и ожидает",
	"В пути"
};

enum E_FUBER_ORDER_DATA
{
	fub_status,
	fub_passenger_id,
	fub_driver_id,
	fub_wish						[MAX_FUBER_WISH_LENGTH],
	fub_cost,
	
	Float: fub_start_pos_x,
	Float: fub_start_pos_y,
	Float: fub_start_pos_z,
	
	Float: fub_end_pos_x,
	Float: fub_end_pos_y,
	Float: fub_end_pos_z
};

new fuber_orders					[MAX_FUBER_ORDERS][E_FUBER_ORDER_DATA],
	fuber_driver_order_index		[MAX_PLAYERS] = {INVALID_PARAM, ...},
	fuber_driver_vehicle_id			[MAX_VEHICLES] = {INVALID_VEHICLE_ID, ...},
	fuber_driver_start_area			[MAX_PLAYERS],
	fuber_passenger_order_index		[MAX_PLAYERS] = {INVALID_PARAM, ...};


Clear:player_fuber(playerid)
{
	Clear:fuber_driver(playerid);
	Clear:fuber_passenger(playerid);
}
	
Clear:fuber_driver(playerid)
{
	fuber_driver_start_area[playerid] = INVALID_STREAMER_ID;
	fuber_driver_vehicle_id[playerid] = INVALID_VEHICLE_ID;
	fuber_driver_order_index[playerid] = INVALID_PARAM;
}

Clear:fuber_passenger(playerid)
{
	fuber_passenger_order_index[playerid] = INVALID_PARAM;
}

Clear:fuber_order(index)
{
	// Int
	fuber_orders[index][fub_passenger_id] = 
	fuber_orders[index][fub_driver_id] = INVALID_PLAYER_ID;
	fuber_orders[index][fub_cost] = 0;
	fuber_orders[index][fub_status] = FUB_ORDER_SEARCH;
	
	// Float
	fuber_orders[index][fub_end_pos_x] = 
	fuber_orders[index][fub_end_pos_y] = 
	fuber_orders[index][fub_end_pos_z] =
	fuber_orders[index][fub_start_pos_x] = 
	fuber_orders[index][fub_start_pos_y] = 
	fuber_orders[index][fub_start_pos_z] = 0.0;
	
	// String
	fuber_orders[index][fub_wish][0] = EOS;
}

Create:fuber_trip(index)
{
	format:g_big_string("INSERT INTO " #__FUBER_TRIPS " (\
		fub_driver_character_id, \
		fub_passenger_character_id, \
		fub_start_pos_x, \
		fub_start_pos_y, \
		fub_start_pos_z, \
		fub_end_pos_x, \
		fub_end_pos_y, \
		fub_end_pos_z, \
		fub_cost, \
		fub_create_date \
		) VALUES (\
		  %d, \
		  %d, \
		  %f, \
		  %f, \
		  %f, \
		  %f, \
		  %f, \
		  %f, \
		  %d, \
		  NOW() \
		)",
		GetCharacterId(fuber_orders[index][fub_driver_id]), 
		GetCharacterId(fuber_orders[index][fub_passenger_id]), 
		fuber_orders[index][fub_start_pos_x], 
		fuber_orders[index][fub_start_pos_y], 
		fuber_orders[index][fub_start_pos_z], 
		fuber_orders[index][fub_end_pos_x], 
		fuber_orders[index][fub_end_pos_y], 
		fuber_orders[index][fub_end_pos_z],
		fuber_orders[index][fub_cost] 
	);
	
	mysql_pquery(db, g_big_string);
}