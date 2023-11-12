/*!
	@brief Перехват нативных функций
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
	
	Синтаксис:
	
	n_*(...)
*/

// Common functions
stock n_Kick(playerid)
{
	SetPVarInt(playerid, "Player:IsKicked", true);
	SetTimerEx("OnPlayerDelayKick", 300, false, "i", playerid);
	return 1;
}

function OnPlayerDelayKick(playerid)
{
	return Kick(playerid);
}

#if defined ALS_Kick
    #undef Kick
#else
    #define _ALS_Kick
#endif

#define Kick n_Kick  

// Player functions
stock n_ShowPlayerDialog(playerid, dialogid, style, caption[], info[], button1[], button2[])
{	
	player_dialog_id[playerid] = dialogid;
	return ShowPlayerDialog(playerid, dialogid, style, caption, info, button1, button2);
}

#if defined ALS_ShowPlayerDialog
    #undef ShowPlayerDialog
#else
    #define _ALS_ShowPlayerDialog
#endif

#if defined ShowPlayerDialog
	#undef ShowPlayerDialog
#endif
#define ShowPlayerDialog n_ShowPlayerDialog


stock n_SetPlayerHealth(playerid, Float: health)
{
	character_data[playerid][c_health] = health;
	return SetPlayerHealth(playerid, health);
}

#if defined ALS_SetPlayerHealth
    #undef SetPlayerHealth
#else
    #define _ALS_SetPlayerHealth
#endif

#define SetPlayerHealth n_SetPlayerHealth  


stock n_SetPlayerInterior(playerid, interiorid)
{
	character_data[playerid][c_int] = interiorid;
	return SetPlayerInterior(playerid, interiorid);
}

#if defined ALS_SetPlayerInterior || defined SetPlayerInterior
    #undef SetPlayerInterior
#else
    #define _ALS_SetPlayerInterior
#endif

#define SetPlayerInterior n_SetPlayerInterior

stock n_SetPlayerVirtualWorld(playerid, worldid)
{
	character_data[playerid][c_world] = worldid;
	return SetPlayerVirtualWorld(playerid, worldid);
}

#if defined ALS_SetPlayerVirtualWorld
    #undef SetPlayerVirtualWorld
#else
    #define _ALS_SetPlayerVirtualWorld
#endif

#define SetPlayerVirtualWorld n_SetPlayerVirtualWorld


// Vehicle functions

stock n_CreateVehicle(modelid, Float: x, Float: y, Float: z, Float: angle, color1, color2, respawn_delay, addsiren = 0, is_clear = true)
{
	new vehicleid = CreateVehicle(modelid, Float: x, Float: y, Float: z, Float: angle, color1, color2, respawn_delay, addsiren);
	
	if (is_clear)
	{
		Clear:vehicle_data(vehicleid);
		
		vehicle_data[vehicleid][v_pos_x] = x;
		vehicle_data[vehicleid][v_pos_y] = y;
		vehicle_data[vehicleid][v_pos_z] = z;
		vehicle_data[vehicleid][v_pos_angle] = angle;
		
		vehicle_data[vehicleid][v_model] = modelid;
		vehicle_data[vehicleid][v_fuel] = 100.0; 
		vehicle_data[vehicleid][v_health] = 1000.0;
		vehicle_data[vehicleid][v_color][0] = color1;
		vehicle_data[vehicleid][v_color][1] = color2;
		vehicle_data[vehicleid][v_owner_type] = TYPE_VEH_NONE;
		
		is_admin_vehicle{vehicleid} = false;
		
		SetVehicleParams(vehicleid);
	}
	
	return vehicleid;
}

#if defined ALS_CreateVehicle
    #undef CreateVehicle
#else
    #define _ALS_CreateVehicle
#endif

#define CreateVehicle n_CreateVehicle


stock n_DestroyVehicle(vehicleid, bool: is_clear = true)
{
	if (is_clear)
	{
		Clear:vehicle_data(vehicleid);
	}
	
	return DestroyVehicle(vehicleid);
}

#if defined ALS_DestroyVehicle
    #undef DestroyVehicle
#else
    #define _ALS_DestroyVehicle
#endif

#define DestroyVehicle n_DestroyVehicle


stock n_LinkVehicleToInterior(vehicleid, interiorid)
{
	vehicle_data[vehicleid][v_tmp_int] = interiorid;
	LinkVehicleToInterior(vehicleid, interiorid);
}

#if defined ALS_LinkVehicleToInterior
    #undef LinkVehicleToInterior
#else
    #define _ALS_LinkVehicleToInterior
#endif

#define LinkVehicleToInterior n_LinkVehicleToInterior


stock n_SetVehicleHealth(vehicleid, Float: health)
{
	vehicle_data[vehicleid][v_health] = health;
	return SetVehicleHealth(vehicleid, Float: health);
}

#if defined ALS_SetVehicleHealth
    #undef SetVehicleHealth
#else
    #define _ALS_SetVehicleHealth
#endif

#define SetVehicleHealth n_SetVehicleHealth


stock n_Dialog_Open(playerid, const function[], style, caption[], const info[], const button1[], const button2[])
{
    new color_caption   [MDIALOG_MAX_CAPTION_SIZE];

    format(color_caption, sizeof(color_caption), #CI_DIALOG_CAPTION "%s", caption);
    return Dialog_Open(playerid, function, style, color_caption, info, button1, button2);
}

#if defined ALS_Dialog_Open
    #undef Dialog_Open
#else
    #define _ALS_Dialog_Open
#endif

#define Dialog_Open n_Dialog_Open