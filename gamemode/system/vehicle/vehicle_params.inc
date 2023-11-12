/*!
	@brief Параметры транспорта
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.01.2018
*/

CheckVehicleLock(playerid, vehicleid)
{
	CheckVehicleParams(vehicleid);
	vehicle_data[vehicleid][v_lock] = vehicle_data[vehicleid][v_lock] == VEHICLE_PARAMS_ON 
		? VEHICLE_PARAMS_OFF : VEHICLE_PARAMS_ON;
	SetVehicleParams(vehicleid);
	
	GameTextForPlayer(playerid, (vehicle_data[vehicleid][v_lock] == VEHICLE_PARAMS_OFF) ? ("DOORS ~g~UNLOCKED") : ("DOORS ~r~LOCKED"), 2000, 4);
	
	return 1;
}

CheckVehicleLight(playerid, vehicleid, value = INVALID_PARAM) 
{
	CheckVehicleParams(vehicleid);
	
	if (value == INVALID_PARAM)
	{
		vehicle_data[vehicleid][v_light] = vehicle_data[vehicleid][v_light] == VEHICLE_PARAMS_ON 
			? VEHICLE_PARAMS_OFF : VEHICLE_PARAMS_ON; 
			
		GameTextForPlayer(playerid, (vehicle_data[vehicleid][v_light] == VEHICLE_PARAMS_OFF) ? ("LIGHTS ~r~OFF") : ("LIGHTS ~g~ON"), 2000, 4);
	}
	else 
	{
		vehicle_data[vehicleid][v_light] = value; 
	}
		
	SetVehicleParams(vehicleid);
	return 1;
}

CheckVehicleEngine(playerid, vehicleid) 
{
	new type;
	
	CheckVehicleParams(vehicleid);
	
	if (vehicle_data[vehicleid][v_engine] != VEHICLE_PARAMS_ON)
	{
		type = vehicle_data[vehicleid][v_owner_type];
	
		if (type != TYPE_VEH_NONE)
		{
			if (type == TYPE_VEH_PLAYER)
			{
				if (!IsVehicleAccess(playerid, vehicleid))
				{
					SendClientMessage(playerid, C_WHITE, !VEHICLE_NO_ACCESS);
					return 1;
				}
			}
			else if (type == TYPE_VEH_FRACTION)
			{
				new fraction_id = GetFractionMemberId(playerid);
				if (vehicle_data[vehicleid][v_owner_id] != fraction_id 
				|| !CheckFractionAccess(playerid, fr_perm_vehicle))
				{
					SendClientMessage(playerid, C_WHITE, !VEHICLE_NO_ACCESS);
					return 1;
				}
			}
		}
		
		if (vehicle_data[vehicleid][v_fuel] <= 0.0)
		{	
			SendClientMessage(playerid, C_WHITE, !#ERROR " В данном транспорте закончилось топливо.");
			return 1;
		}
		
		if (vehicle_data[vehicleid][v_health] <= 400.0)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Двигатель не в состоянии завестись.");
			return 1;
		}
	}
	
	vehicle_data[vehicleid][v_engine] = vehicle_data[vehicleid][v_engine] == VEHICLE_PARAMS_ON 
		? VEHICLE_PARAMS_OFF : VEHICLE_PARAMS_ON;
		
	SetVehicleParams(vehicleid);
	
	GameTextForPlayer(playerid, (vehicle_data[vehicleid][v_engine] == VEHICLE_PARAMS_OFF) ? ("ENGINE ~r~OFF") : ("ENGINE ~g~ON"), 2000, 4);
	return 1;
}	

CheckVehicleHood(vehicleid) 
{
	CheckVehicleParams(vehicleid);
	vehicle_data[vehicleid][v_hood] = vehicle_data[vehicleid][v_hood] == VEHICLE_PARAMS_ON 
		? VEHICLE_PARAMS_OFF : VEHICLE_PARAMS_ON;
	SetVehicleParams(vehicleid);

	return 1;
}

CheckVehicleBoot(vehicleid) 
{
	CheckVehicleParams(vehicleid);
	vehicle_data[vehicleid][v_boot] = vehicle_data[vehicleid][v_boot] == VEHICLE_PARAMS_ON 
		? VEHICLE_PARAMS_OFF : VEHICLE_PARAMS_ON;
	SetVehicleParams(vehicleid);
	
	return 1;
}

CheckVehicleLimit(vehicleid) 
{
	vehicle_data[vehicleid][v_limit] = vehicle_data[vehicleid][v_limit] == VEHICLE_PARAMS_ON 
		? VEHICLE_PARAMS_OFF : VEHICLE_PARAMS_ON;
	
	return 1;
}

ResetVehicleParams(vehicleid)
{
	vehicle_data[vehicleid][v_engine] =
	vehicle_data[vehicleid][v_light] =
	vehicle_data[vehicleid][v_alarm] =
	vehicle_data[vehicleid][v_lock] =
	vehicle_data[vehicleid][v_hood] =
	vehicle_data[vehicleid][v_boot] =
	vehicle_data[vehicleid][v_obj] = VEHICLE_PARAMS_OFF;
	
	vehicle_data[vehicleid][v_window][0] =
	vehicle_data[vehicleid][v_window][1] =
	vehicle_data[vehicleid][v_window][2] =
	vehicle_data[vehicleid][v_window][3] = 0;
}

SetVehicleParams(vehicleid) 
{
	SetVehicleParamsEx(vehicleid, 
		vehicle_data[vehicleid][v_engine], 
		vehicle_data[vehicleid][v_light], 
		vehicle_data[vehicleid][v_alarm], 
		vehicle_data[vehicleid][v_lock], 
		vehicle_data[vehicleid][v_hood], 
		vehicle_data[vehicleid][v_boot], 
		vehicle_data[vehicleid][v_obj] 
	);
	
	SetVehicleParamsCarWindows(vehicleid, 
		vehicle_data[vehicleid][v_window][0], 
		vehicle_data[vehicleid][v_window][1], 
		vehicle_data[vehicleid][v_window][2], 
		vehicle_data[vehicleid][v_window][3] 
	);	

	return 1;	
}

CheckVehicleParams(vehicleid) 
{
	GetVehicleParamsEx(vehicleid, 
		vehicle_data[vehicleid][v_engine], 
		vehicle_data[vehicleid][v_light], 
		vehicle_data[vehicleid][v_alarm], 
		vehicle_data[vehicleid][v_lock], 
		vehicle_data[vehicleid][v_hood], 
		vehicle_data[vehicleid][v_boot], 
		vehicle_data[vehicleid][v_obj] 
	);
	
	GetVehicleParamsCarWindows(vehicleid, 
		vehicle_data[vehicleid][v_window][0], 
		vehicle_data[vehicleid][v_window][1], 
		vehicle_data[vehicleid][v_window][2], 
		vehicle_data[vehicleid][v_window][3] 
	);	
	
	return 1;
}