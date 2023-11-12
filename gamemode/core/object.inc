/*!
	@brief ־בתוךעû ס סונגונא
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
*/

#if defined STREAMER_OBJECT_SD
	#undef STREAMER_OBJECT_SD
#endif 

#define STREAMER_OBJECT_SD					(300.0)

// Virtual worlds for interiors
enum 
{
	WORLD_PD_HEADQUARTERS = WORLD_OTHER,
	WORLD_PD_64_SAINTS,
	WORLD_PD_96_VERONA,
	WORLD_HOSPITAL,
	WORLD_SD_BLUEBERRY,
	WORLD_SD_LOSSANTOS,
	WORLD_SAN,
	WORLD_NPS,
	WORLD_PRISON,
	WORLD_CITYHALL,
	WORLD_COURT,
	
	WORLD_BOWLING,
	WORLD_SWIMMING_POOL,
	WORLD_MALL,
	WORLD_VINYL_COUNTDOWN,
	WORLD_PAWNSHOP,
	WORLD_LAUNDRY_1,
	WORLD_AMMUNATION,
	WORLD_PORT_STOCK,
	
	WORLD_FD_HEADQUARTERS,
}

Include_ServerObjects()
{
	new tmpobjid,
		start_object_id,
		end_object_id;
	
	#include "object\exterior\fixes.pwn"
	
	/*!
	
		@brief Exterior
		
	*/
	
	#include "object\exterior\unity.pwn"
	#include "object\exterior\downtown.pwn"
	#include "object\exterior\moll.pwn"
	#include "object\exterior\idlewood_pizza.pwn"
	#include "object\exterior\idlewood_lane.pwn"
	#include "object\exterior\east_los_santos.pwn"
	//#include "object\exterior\all_saints_square.pwn"
	#include "object\exterior\chinatown.pwn"
	#include "object\exterior\las_colinas.pwn"
	#include "object\exterior\el_corona.pwn"
	#include "object\exterior\glen_park.pwn"
	#include "object\exterior\little_armenia.pwn"
	#include "object\exterior\little_italy.pwn"
	#include "object\exterior\grotti.pwn"
	#include "object\exterior\recycle.pwn"
	#include "object\exterior\liverpool_park.pwn"
	#include "object\exterior\west.pwn"
	#include "object\exterior\market.pwn"
	#include "object\exterior\east_market.pwn"
	//#include "object\exterior\harbor.pwn"
	#include "object\exterior\autoservice.pwn"
	#include "object\exterior\russian.pwn"
	
	/// Fire Department
	//#include "object\exterior\fd\fd_downtown.pwn"
	#include "object\exterior\fd\fd_headquarters.pwn"
	
	/// Police Department
	#include "object\exterior\pd\pd_64_saints.pwn"
	#include "object\exterior\pd\pd_96_verona.pwn"
	#include "object\exterior\pd\pd_headquarters.pwn"
	
	/// Sheriffs Department
	#include "object\exterior\sd\sd_lossantos.pwn"
	#include "object\exterior\sd\sd_blueberry.pwn"
	
	/// National Park 
	#include "object\exterior\npl\npl_office.pwn"
	#include "object\exterior\npl\npl_forest.pwn"
	
	/// Prison
	#include "object\exterior\prison\prison.pwn"
	
	/// Other
	#include "object\exterior\departure_los_santos.pwn"
	#include "object\exterior\vehicle_mode.pwn"
	#include "object\exterior\other.pwn"
	
	/*!
	
		@brief Interior
		
	*/
	
	#include "object\interior\hostel\low_yan_1.pwn"
	#include "object\interior\hostel\low_dima_2.pwn"
	#include "object\interior\hostel\low_gaby_3.pwn"
	
	#include "object\interior\vehshop_grotti.pwn"
	#include "object\interior\vehshop_lm.pwn"
	#include "object\interior\vehshop_bike_shed.pwn"
	#include "object\interior\rent.pwn"
	#include "object\interior\bank.pwn"
	#include "object\interior\business_agency.pwn"
	#include "object\interior\centre_of_licenses.pwn"
	
	#include "object\interior\bowling.pwn"
	#include "object\interior\swimming_pool.pwn"
	#include "object\interior\mall.pwn"
	#include "object\interior\vinyl_countdown.pwn"
	#include "object\interior\pawnshop.pwn"
	#include "object\interior\ammunation.pwn"
	#include "object\interior\laundry\laundry_1.pwn"
	
	/// Los Santos Government 
	#include "object\interior\ch\ch.pwn"
	
	/// The Court of Los Santos
	#include "object\interior\court\court.pwn"
	
	/// Los Santos Fire Department
	#include "object\interior\fd\int_fd_headquarters.pwn"
	
	/// Los Santos Police Department
	#include "object\interior\pd\int_pd_headquarters.pwn"
	#include "object\interior\pd\int_pd_64_saints.pwn"
	#include "object\interior\pd\int_pd_96_verona.pwn"
	
	/// Los Santos County Sheriff's Department 
	#include "object\interior\sd\int_sd_blueberry.pwn"
	#include "object\interior\sd\int_sd_lossantos.pwn"
	
	/// SAN 
	#include "object\interior\san\san.pwn"
	
	/// National Park Service 
	#include "object\interior\npl\npl.pwn"
	
	/// Hospital 
	#include "object\interior\hospital\hospital.pwn"
	
	/// Prison 
	#include "object\interior\prison\int_prison.pwn"
	
	/// Other
	#include "object\interior\stock.pwn"
	
	// Garage
	#include "object\interior\garage.pwn"
}

// Functions
UpdateObjectData(start_object_id, end_object_id, world, int = INT_OTHER)
{
	for (new i = start_object_id; i < end_object_id; i++)
	{
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, i, E_STREAMER_INTERIOR_ID, int);
		Streamer_SetIntData(STREAMER_TYPE_OBJECT, i, E_STREAMER_WORLD_ID, world);
	}
}