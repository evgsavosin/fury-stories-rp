/*!
	@brief Основной файл для создания билда
	@author Found (evg.savosin)
	@date 16.12.2016, update 16.01.2018

	Информация о игровом моде:
	Плагины:
		MySQL R41-4;
		Streamer v2.9.4;
		CrashDetect 4.19.4;
		SSCANF 2.8.3;
		Profiler 2.15.3;
*/

// Disable constant correctly
#pragma warning push
#pragma warning disable 239
#pragma warning disable 214

// Environment list
#define DEV                                         (0) // Local server (very small players, debug mode)
#define TEST                                        (1) // Test server (small players)
#define PROD                                        (3) // Production server

// Environment 
#define __ENV                                       DEV // 'dev', 'test', 'prod'

// Debug
#if __ENV == DEV
    #define __DEBUG
#endif

// Settings for fixes.inc
#define FIX_GetPlayerColour 						(0)
#define FIX_OnVehicleMod							(0)
#define FIX_CreatePlayerTextDraw_2					(0)
#define FIX_PlayerTextDrawSetString_2				(0)
#define FIX_TextDrawCreate_2						(0)
#define FIX_TextDrawSetString_2						(0)

#include <a_samp>

// Settings
#if defined MAX_VEHICLES
	#undef MAX_VEHICLES
#endif
#define MAX_VEHICLES								(1999)

#if defined MAX_PLAYERS
	#undef MAX_PLAYERS
#endif
#if __ENV == DEV
	#define MAX_PLAYERS								(5)
#elseif __ENV == TEST
    #define MAX_PLAYERS								(50)
#else
	#define MAX_PLAYERS								(300)
#endif

// Fixed tag
#if defined INVALID_TEXT_DRAW
	#undef INVALID_TEXT_DRAW
#endif
#define INVALID_TEXT_DRAW							(Text: 0xFFFF)

#define	INVALID_PTD									(PlayerText: 0xFFFF)

// Includes
#include <fixes>
#include <crashdetect>
#include <a_mysql>
#include <sscanf2>
#include <streamer>
#include <zcmd>
#include <foreach>
//#include <profiler>
#include <Pawn.RakNet>
#include <TOTP>

// Custom libraries
#include "core\custom\mdialog.inc"
#include "core\custom\3DMenu.inc"

// Core
#include "core\config.inc"
#include "core\constant.inc"
#include "core\macro.inc"
#include "core\var.inc"
#include "core\array.inc"
#include "core\object.inc"
#include "core\remove_object.inc"
#include "core\server.inc"
#include "core\db.inc"
#include "core\blanks.inc"
#include "core\dialogs.inc"

// Header
#include "header\player\user.inc"
#include "header\player\character.inc"
#include "header\player\player.inc"
#include "header\player\credit.inc"
#include "header\player\license.inc"
#include "header\player\armour.inc"
#include "header\player\action.inc"
#include "header\player\donate.inc"

#include "header\admin\admin.inc"
#include "header\admin\alog.inc"

#include "header\vehicle\vehicle_list.inc"
#include "header\vehicle\vehicle.inc"

#include "header\inventory\item_list.inc"
#include "header\inventory\inventory.inc"
#include "header\inventory\bag.inc"

#include "header\texture_list.inc"
#include "header\renovation.inc"

#include "header\house\interior.inc"
#include "header\house\house.inc"
#include "header\house\lodger.inc"
#include "header\house\garage.inc"
#include "header\house\hostel.inc"

#include "header\premise\premise.inc"
#include "header\premise\pinterior.inc"
#include "header\premise\pprofit.inc"

#include "header\business\business.inc"
#include "header\business\btype.inc"
#include "header\business\bmember.inc"
#include "header\business\bassort.inc"

#include "header\room.inc"

#include "header\phone\phone.inc"
#include "header\phone\contacts.inc"
#include "header\phone\call.inc"
// App\Fuber
#include "header\phone\fuber.inc"

#include "header\fraction\fraction.inc"
#include "header\fraction\frank.inc"
#include "header\fraction\funit.inc"
#include "header\fraction\fobject.inc"
#include "header\fraction\fstrobe.inc"
#include "header\fraction\fdoor.inc"
#include "header\fraction\fstock.inc"
#include "header\fraction\fduty.inc"
#include "header\fraction\fgarage.inc"
#include "header\fraction\fcalls.inc"
#include "header\fraction\fcamera.inc"
#include "header\fraction\fprison.inc"
#include "header\fraction\fnews.inc"

#include "header\furniture\furniture_list.inc"
#include "header\furniture\furniture.inc"

#include "header\site\site.inc"
#include "header\site\adverts.inc"
#include "header\site\estate.inc"

#include "header\death.inc"

#include "header\corpse.inc"

#include "header\computer\computer.inc"

#include "header\crime\crime.inc"
#include "header\crime\crtype.inc"
#include "header\crime\crmember.inc"
#include "header\crime\crbuy.inc"

// Core
#include "core\textdraw.inc"

#include "core\anticheat\header\ac_header.inc"
#include "core\anticheat\header\ac_list.inc"
#include "core\anticheat\header\ac_raknet.inc"
#include "core\anticheat\header\ac_data.inc"
#include "core\native_function.inc"
#include "core\anticheat\ac_native_function.inc"
#include "core\function.inc"
#include "core\dialog_values.inc"

#include "core\anticheat\ac_function.inc"
#include "core\anticheat\ac_incoming_packet.inc"
#include "core\anticheat\ac_incoming_rpc.inc"
#include "core\anticheat\ac_outgoing_rpc.inc"
#include "core\anticheat\ac_dialog.inc"
#include "core\anticheat\ac_menu_control.inc"

// Anticheat list
#include "core\anticheat\list\ac_special_action.inc"
#include "core\anticheat\list\ac_onfoot_rvanka.inc"
#include "core\anticheat\list\ac_driver_rvanka.inc"
#include "core\anticheat\list\ac_unoccupied_rvanka.inc"
#include "core\anticheat\list\ac_onfoot_flyhack.inc"
#include "core\anticheat\list\ac_invisible_surf.inc"
#include "core\anticheat\list\ac_onfoot_teleport.inc"
#include "core\anticheat\list\ac_car_to_player.inc"
#include "core\anticheat\list\ac_driver_teleport.inc"
#include "core\anticheat\list\ac_car_slapper.inc"
#include "core\anticheat\list\ac_onfoot_airbreak.inc"
#include "core\anticheat\list\ac_driver_airbreak.inc"
#include "core\anticheat\list\ac_driver_enter.inc"
#include "core\anticheat\list\ac_passenger_enter.inc"
#include "core\anticheat\list\ac_driver_fast_enter.inc"
#include "core\anticheat\list\ac_passenger_fast_enter.inc"
#include "core\anticheat\list\ac_weapon_hack.inc"
#include "core\anticheat\list\ac_driver_speedhack.inc"
#include "core\anticheat\list\ac_trailer_teleport.inc"

// Script
#if defined __DEBUG
	#include "script\test.inc"
#endif

#include "script\commands.inc"
#include "script\gps.inc"
#include "script\enters.inc"
#include "script\payment.inc"
#include "script\vehicle_shop.inc"
#include "script\rent.inc"
#include "script\recycling_vehicle.inc"
#include "script\bank.inc"
#include "script\helper.inc"
#include "script\licenses.inc"
#include "script\music.inc"
#include "script\gas.inc"
#include "script\funicular.inc"
#include "script\gun_shop.inc"
#include "script\weather.inc"
#include "script\police_reception.inc"
#include "script\autoservice.inc"
#include "script\connection.inc"

// System
#include "system\timer.inc"

// Admin
#include "system\admin\admin_function.inc"
#include "system\admin\admin_dialog.inc"
#include "system\admin\admin_menu.inc"
#include "system\admin\admin_log.inc"
#include "system\admin\admin_cmd.inc"

// Player
#include "system\player\player_function.inc"
#include "system\player\player_anim.inc"
#include "system\player\player_login.inc"
#include "system\player\player_camera.inc"
#include "system\player\player_dialog.inc"
#include "system\player\player_proxdetector.inc"
#include "system\player\player_chat.inc"
#include "system\player\player_payday.inc"
#include "system\player\player_spawn.inc"
#include "system\player\player_load.inc"
#include "system\player\player_settings.inc"
#include "system\player\player_credit.inc"
#include "system\player\player_license.inc"
#include "system\player\player_damage.inc"
#include "system\player\player_timer.inc"
#include "system\player\player_action.inc"
#include "system\player\player_donate.inc"
#include "system\player\player_menu.inc"

// Inventory
#include "system\inventory\inventory_textdraw.inc"
#include "system\inventory\inventory_dialog_menu.inc"
#include "system\inventory\inventory_load.inc"
#include "system\inventory\inventory_function.inc"
#include "system\inventory\inventory_dialog.inc"
#include "system\inventory\inventory_attach.inc"
#include "system\inventory\inventory_bag.inc"
#include "system\inventory\inventory_menu.inc"
#include "system\inventory\inventory_cmd.inc"

// Renovation
#include "system\renovation\renovation_function.inc"
#include "system\renovation\renovation_room.inc"
#include "system\renovation\renovation_dialog.inc"

// Furniture
#include "system\furniture\furniture_function.inc"
#include "system\furniture\furniture_dialog.inc"
#include "system\furniture\furniture_load.inc"
#include "system\furniture\furniture_cmd.inc"

// House
#include "system\house\house_function.inc"
#include "system\house\house_dialog.inc"
#include "system\house\house_dialog_function.inc"
#include "system\house\house_load.inc"
#include "system\house\house_cmd.inc"
#include "system\house\house_hostel.inc"
#include "system\house\house_lodger.inc"
#include "system\house\house_interior.inc"
#include "system\house\house_operations.inc"
#include "system\house\house_garage.inc"
#include "system\house\house_timer.inc"
#include "system\house\house_menu.inc"

// Premise
#include "system\premise\premise_function.inc"
#include "system\premise\premise_dialog.inc"
#include "system\premise\premise_load.inc"
#include "system\premise\premise_interior.inc"
#include "system\premise\premise_operations.inc"
#include "system\premise\premise_menu.inc"
#include "system\premise\premise_buy.inc"
#include "system\premise\premise_profit.inc"
#include "system\premise\premise_timer.inc"
#include "system\premise\premise_cmd.inc"

// Business
#include "system\business\business_function.inc"
#include "system\business\business_dialog.inc"
#include "system\business\business_load.inc"
#include "system\business\business_member.inc"
#include "system\business\business_menu.inc"
#include "system\business\business_assort.inc"
#include "system\business\business_timer.inc"
#include "system\business\business_cmd.inc"

// Phone\App
#include "system\phone\app\fuber\_phone_function.inc"
#include "system\phone\app\fuber\_phone_dialog.inc"
#include "system\phone\app\fuber\_phone_cmd.inc"

// Phone
#include "system\phone\phone_function.inc"
#include "system\phone\phone_load.inc"
#include "system\phone\phone_menu.inc"
#include "system\phone\phone_dialog.inc"
#include "system\phone\phone_interface.inc" // < error
#include "system\phone\phone_timer.inc"
#include "system\phone\app\phone_app_anogram.inc"
#include "system\phone\phone_cmd.inc"

// Vehicle
#include "system\vehicle\vehicle_function.inc"
#include "system\vehicle\vehicle_speedometer.inc"
#include "system\vehicle\vehicle_load.inc"
#include "system\vehicle\vehicle_operations.inc"
#include "system\vehicle\vehicle_dialog.inc"
#include "system\vehicle\vehicle_dialog_function.inc"
#include "system\vehicle\vehicle_params.inc"
#include "system\vehicle\vehicle_timer.inc"
#include "system\vehicle\vehicle_menu.inc"
#include "system\vehicle\vehicle_cmd.inc"
#include "system\vehicle\vehicle_key_alarm.inc"

// Site
#include "system\site\site_function.inc"
#include "system\site\site_dialog.inc"
#include "system\site\site_menu.inc"
#include "system\site\site_interface.inc"
#include "system\site\site_load.inc"
#include "system\site\site_timer.inc"
#include "system\site\site_estate.inc"
#include "system\site\site_adverts.inc"
#include "system\site\site_bank.inc"

// Death
#include "system\death\death_function.inc"
#include "system\death\death_dialog.inc"
#include "system\death\death_timer.inc"
#include "system\death\death_cmd.inc"

// Corpse
#include "system\corpse\corpse_function.inc"
#include "system\corpse\corpse_dialog.inc"
#include "system\corpse\corpse_load.inc"
#include "system\corpse\corpse_camera_zone.inc"
#include "system\corpse\corpse_dirt_zone.inc"
#include "system\corpse\corpse_timer.inc"
#include "system\corpse\corpse_cmd.inc"

// Fraction
//#include "system\fraction\fraction_tmp.inc"
#include "system\fraction\fraction_function.inc"
#include "system\fraction\fraction_dialog.inc"
#include "system\fraction\fraction_load.inc"
#include "system\fraction\fraction_rank.inc"
#include "system\fraction\fraction_unit.inc"
#include "system\fraction\fraction_object.inc"
#include "system\fraction\fraction_menu.inc"
#include "system\fraction\fraction_strobe.inc"
#include "system\fraction\fraction_door.inc"
#include "system\fraction\fraction_duty.inc"
#include "system\fraction\fraction_stock.inc"
#include "system\fraction\fraction_garage.inc"
#include "system\fraction\fraction_call.inc"
#include "system\fraction\fraction_prison.inc"
#include "system\fraction\fraction_cmd.inc"
#include "system\fraction\fraction_timer.inc"

// Fraction\List
#include "system\fraction\list\fraction_government.inc"
#include "system\fraction\list\fraction_pd.inc"
#include "system\fraction\list\fraction_sd.inc"
#include "system\fraction\list\fraction_fd.inc"
#include "system\fraction\list\fraction_news.inc"

// Computer
#include "system\computer\computer_function.inc"
#include "system\computer\computer_textdraw.inc"

// Crime
#include "system\crime\crime_load.inc"
#include "system\crime\crime_type.inc"
#include "system\crime\crime_member.inc"
#include "system\crime\crime_function.inc"
#include "system\crime\crime_dialog.inc"
#include "system\crime\crime_menu.inc"
#include "system\crime\crime_cmd.inc"

/// Base publics & function by SA:MP Team
#include "base.pwn"
