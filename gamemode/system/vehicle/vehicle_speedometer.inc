/*!
	@brief Файл с системой спидометра, расчета миляжа и бензина для системы т/с
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

function Vehicle_OnPlayerStateChange(playerid, newstate, oldstate) 
{
	new vehicleid = GetPlayerVehicleID(playerid),
		vehicle_name [MAX_SPEEDOMETER_VEHICLE_NAME];
	
	if (newstate == PLAYER_STATE_DRIVER)
	{		
		if (!vehicleid)
		{
			return 1;
		}
		
		SendClientMessage(playerid, C_WHITE, !"" DEFAULT " Управление транспортом - " #cPROJECT "N или /cmenu" #cWHITE " | Управление окнами - " #cPROJECT "/window [l | r | rl | rr]" #cWHITE ".");
		
		if (IsAirVehicle(vehicleid) || IsBoatVehicle(vehicleid))
		{
			return 1;
		}
		
		if (IsBikeVehicle(vehicleid) || GetVehicleModel(vehicleid) == 538)
		{
			vehicle_data[vehicleid][v_engine] = VEHICLE_PARAMS_ON;
			SetVehicleParams(vehicleid);
		}
		else 
		{
			if (vehicle_data[vehicleid][v_model] != 0)
			{
				player_speedometer[playerid] = SetTimerEx(
					"OnVehicleSpeedometerUpdate", 
					400, 
					true, 
					"ii", 
					playerid, 
					vehicleid 
				);
			
				ShowSpeedometer(playerid, true);
				
				GetVehicleNameForSpeedometer(
					GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name), 
					vehicle_name
				);
				
				PlayerTextDrawSetString(playerid, ptd_speedometer[playerid][7], 
					vehicle_name
				);
			}
		}
	}

	if (oldstate == PLAYER_STATE_DRIVER)
	{
		if (IsBikeVehicle(vehicleid))
		{
			vehicle_data[vehicleid][v_engine] = VEHICLE_PARAMS_OFF;
			SetVehicleParams(vehicleid);
		}
		else 
		{
			ShowSpeedometer(playerid, false);
			KillTimer(player_speedometer[playerid]);
			player_speedometer[playerid] = INVALID_PARAM;
		}
	}
	
	return 1;
}

function OnVehicleSpeedometerUpdate(playerid, vehicleid)
{
	if (vehicle_data[vehicleid][v_model] == 0)
	{
		KillTimer(player_speedometer[playerid]);
		ShowSpeedometer(playerid, false);
		return 1;
	}
	
	new Float: vel_x,
		Float: vel_y,
		Float: vel_z;
		
	GetVehicleVelocity(vehicleid, vel_x, vel_y, vel_z);
	
	new Float: speed = GetVehicleSpeed(vehicleid);
		
	vehicle_data[vehicleid][v_mileage] += speed / 45000.0;
	vehicle_data[vehicleid][v_fuel] -= speed / GetVehicleFuelRate(vehicle_data[vehicleid][v_model]);
	
	if (!GetPVarInt(playerid, "Speedometer:States"))
	{
		return 1;
	}
	
	// Скорость
	format:g_small_string("%i", floatround(speed));
	PlayerTextDrawSetString(playerid, ptd_speedometer[playerid][0], g_small_string);
	
	UpdateSpeedBar(playerid, speed, 150.0);
	
	// Пробег
	format:g_small_string("%0.2f MP", vehicle_data[vehicleid][v_mileage]);
	PlayerTextDrawSetString(playerid, ptd_speedometer[playerid][2], g_small_string);
	
	// Топливо
	format:g_small_string("%0.2f GAL.", vehicle_data[vehicleid][v_fuel]);
	PlayerTextDrawSetString(playerid, ptd_speedometer[playerid][1], g_small_string);
	
	
	// Engine
	PlayerTextDrawBoxColor(playerid, ptd_speedometer[playerid][3], 
		(vehicle_data[vehicleid][v_engine] == 1) ? C_PROJECT : -2139062241 
	);
	
	PlayerTextDrawShow(playerid, ptd_speedometer[playerid][3]);
	
	// Light 
	PlayerTextDrawBoxColor(playerid, ptd_speedometer[playerid][4], 
		(vehicle_data[vehicleid][v_light] == 1) ? C_PROJECT : -2139062241 
	);
	
	PlayerTextDrawShow(playerid, ptd_speedometer[playerid][4]);
	
	// Lock
	PlayerTextDrawBoxColor(playerid, ptd_speedometer[playerid][5], 
		(vehicle_data[vehicleid][v_lock] == 1) ? C_PROJECT : -2139062241 
	);
	
	PlayerTextDrawShow(playerid, ptd_speedometer[playerid][5]);
	
	// Limit 
	PlayerTextDrawBoxColor(playerid, ptd_speedometer[playerid][6], 
		(vehicle_data[vehicleid][v_limit] == 1) ? C_PROJECT : -2139062241 
	);
	
	PlayerTextDrawShow(playerid, ptd_speedometer[playerid][6]);
		
	return 1;
}

UpdateSpeedBar(playerid, Float: speed, Float: max_speed)
{
	new Float: width = TextDrawBackgroundCalculated(519.0, 610.0, speed, max_speed),
		color = C_PROJECT;
		
	PlayerTextDrawTextSize(playerid, ptd_speedometer[playerid][0], width, 0.000000);
	
	if (floatround(max_speed / 2.0) < floatround(speed))
	{
		color = 0x8c842aff;
	}
	
	if (floatround(max_speed / 1.22) < floatround(speed))
	{
		color = C_DARKRED;
	}
	
	PlayerTextDrawBoxColor(playerid, ptd_speedometer[playerid][0], color);
	PlayerTextDrawShow(playerid, ptd_speedometer[playerid][0]);
}

// Получить имя транспорта для спидометра в обрезанном виде
GetVehicleNameForSpeedometer(name[], dest[MAX_SPEEDOMETER_VEHICLE_NAME])
{
	new length = strlen(name);
	
	if (length <= (MAX_SPEEDOMETER_VEHICLE_NAME - 3))
	{
		strcat(dest, name);
		return;
	}
	
	strmid(dest, name, 0, MAX_SPEEDOMETER_VEHICLE_NAME - 3);
	strcat(dest, "...");
}
