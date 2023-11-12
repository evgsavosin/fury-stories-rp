/*!
	@brief Таймер для системы транспорта
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.01.2018
*/

Timer:vehicle_second()
{
	for (new i = 1, j = GetVehiclePoolSize(); i <= j; i++)
	{
		if (vehicle_data[i][v_model] == 0 
		|| vehicle_data[i][v_model] == 538
		|| IsBikeVehicle(i))
		{
			continue;
		}
		
		if (vehicle_data[i][v_fuel] <= 0.0)
		{	
			vehicle_data[i][v_fuel] = 0.0;
			vehicle_data[i][v_engine] = VEHICLE_PARAMS_OFF;
			SetVehicleParams(i);
		}
		
		GetVehicleHealth(i, vehicle_data[i][v_health]);
		if (vehicle_data[i][v_health] <= 400.0)
		{	
			vehicle_data[i][v_engine] = VEHICLE_PARAMS_OFF;
			SetVehicleParams(i);
			SetVehicleHealth(i, 400.0);
		}
	}
}

Timer:vehicle_minute()
{
	TD_UpdateKeyAlarmTime();
}