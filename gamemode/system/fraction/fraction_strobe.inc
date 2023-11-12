/*!
	@brief Система стробоскопов (/sl)
	@author Found (evg.savosin)
	@date 05.01.2020
*/

function OnFractionVehicleStrobeTimeout(vehicleid)
{
	new panels,
		doors,
		tires,
		lights;
			
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	UpdateVehicleDamageStatus(vehicleid, panels, doors, 0, tires);
	
	CheckVehicleLight(INVALID_PLAYER_ID, vehicleid, VEHICLE_PARAMS_OFF);
	
	strobelight_flash{vehicleid} = 0;
	
	if (strobelight_timer[vehicleid])
	{
		KillTimer(strobelight_timer[vehicleid]);
		strobelight_timer[vehicleid] = INVALID_PARAM;
	}
	
	if (strobelight_time_out[vehicleid])
	{
		KillTimer(strobelight_time_out[vehicleid]);
		strobelight_time_out[vehicleid] = INVALID_PARAM;
	}
	
	return 1;
}


function OnFractionVehicleStrobeLight(vehicleid)
{

	new panels,
		doors,
		tires,
		lights;
		
	GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	
	switch (strobelight_flash{vehicleid})
	{
		case 0: UpdateVehicleDamageStatus(vehicleid, panels, doors, 2, tires);
		case 1: UpdateVehicleDamageStatus(vehicleid, panels, doors, 5, tires);
		case 2: UpdateVehicleDamageStatus(vehicleid, panels, doors, 2, tires);
		case 3: UpdateVehicleDamageStatus(vehicleid, panels, doors, 4, tires);
		case 4: UpdateVehicleDamageStatus(vehicleid, panels, doors, 5, tires);
		case 5: UpdateVehicleDamageStatus(vehicleid, panels, doors, 4, tires);	
	}
	
	strobelight_flash{vehicleid}++;
	if( strobelight_flash{vehicleid} > 5 )
	{
		strobelight_flash{vehicleid} = 0;
	}

	return 1;
}

IsValidFractionStrobeVehicle( vehicleid )
{
	if (vehicle_data[vehicleid][v_owner_type] == TYPE_VEH_FRACTION)
	{
		switch (vehicle_data[vehicleid][v_owner_id])
		{
			case FRACTION_PD, FRACTION_FD, FRACTION_SD, FRACTION_HOSPITAL:
			{
				return 1;
			}
		}
	}
	
	return 0;
}