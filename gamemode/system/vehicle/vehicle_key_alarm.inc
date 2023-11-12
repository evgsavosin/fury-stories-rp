/*!
	@brief Система сигнализации
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.01.2018
*/

// Действие при клике
ActionVehicleKeyAlarm(playerid, vehicleid, action)
{ 
	if (GetPVarInt(playerid, "KeyAlarm:Progress") != 0)
	{
		return 1;
	}
	
	OnVehicleKeyAlarmAction(playerid, vehicleid, action);
	return 1;
}

function OnVehicleKeyAlarmAction(playerid, vehicleid, action)
{
	new progress = GetPVarInt(playerid, "KeyAlarm:Progress");
	
	if (progress == 0)
	{
		if (PlayerText: action == PTD_KA_ICON_ENGINE) // Управление двигателем
		{
			CheckVehicleEngine(playerid, vehicleid);
		}
		else if (PlayerText: action == PTD_KA_ICON_LOCK) // Управление замком
		{
			CheckVehicleLock(playerid, vehicleid);
		}
		else if (PlayerText: action == PTD_KA_ICON_BOOT_1) // Управление багажником 
		{
			CheckVehicleBoot(vehicleid);
			return 1;
		}
	}
	
	if (progress < 4)
	{
		GivePVarInt(playerid, "KeyAlarm:Progress", 1);
		
		CheckVehicleLight(playerid, vehicleid, ((progress % 2) == 0) ? VEHICLE_PARAMS_ON : VEHICLE_PARAMS_OFF);
		BeginVehicleKeyAlarmActionTimer(playerid, 150, vehicleid, action);
		return 1;
	}
	
	SetPVarInt(playerid, "KeyAlarm:Progress", 0);
	return 1;
}

BeginVehicleKeyAlarmActionTimer(playerid, time, vehicleid, action)
{
	SetTimerEx("OnVehicleKeyAlarmAction", time, false, "ddd", playerid, vehicleid, action);
}

// Выход на ESC
DisableVehicleKeyAlarm(playerid)
{
	if (!IsKeyAlarmShowed(playerid))
	{
		return 1;
	}
	
	ShowKeyAlarm(playerid, false);
	return 1;
}