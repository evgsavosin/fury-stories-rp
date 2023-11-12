
#define RECOLOR_COST			200
#define REPAIR_COST				100
#define AUTOSERVICE_POSITION	1698.5277, -1464.1857, 13.3205

Autoservice_OnGameModeInit()
{
	CreatePickupWith3DTextLabel("ALT", INVALID_PARAM, AUTOSERVICE_POSITION);
}

function Autoservice_OnPlayerKSC(playerid, newkeys, oldkeys) 
{
	if (PRESSED(KEY_FIRE) && IsPlayerInAnyVehicle(playerid) && GetPlayerVehicleSeat(playerid) == 0)
	{
		if (IsPlayerInRangeOfPoint(playerid, 3.5, AUTOSERVICE_POSITION))
		{
			new vehicleid = GetPlayerVehicleID(playerid);
		
			SetPVarInt(playerid, "Autoservice:VehicleId", vehicleid);
			
			if (IsBikeVehicle(vehicleid))
			{
				SendClientMessage(playerid, C_WHITE, !"" #ERROR " Недоступно для этого транспорта.");
				return 1;
			}
		
			ShowPlayerDialog(playerid, D_AUTOSERVICE, DIALOG_STYLE_LIST, "Станция технического обслуживания", " \
				Покрасочные работы\n \
				Ремонт", 
				"Выбрать", "Закрыть"
			);
			
			return 0;
		}
	}

	return 1;
}

Autoservice_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == D_AUTOSERVICE)
	{
		if (!response)
		{
			DeletePVar(playerid, "Autoservice:VehicleId");
			return 1;
		}
		
		if (listitem == 0)
		{
			ShowPlayerDialog(playerid, D_AUTOSERVICE + 2, DIALOG_STYLE_INPUT, " ",
				"" #DEFAULT " Покрасочные работы\n\n\
				Стоимость покраски составит: " #cGREEN "$200" #cWHITE "\n\
				Укажите через запятую значения цвета от 0 до 255:\n\n\
				" #cGRAY "Пример: 0, 0",
				"Да", "Нет"
			);
		}
		else if (listitem == 1)
		{
			ShowPlayerDialog(playerid, D_AUTOSERVICE + 1, DIALOG_STYLE_MSGBOX, " ",
				"" #DEFAULT " Ремонт\n\n\
				Починка транспорта стоит: " #cGREEN "$100" #cWHITE "\n\
				Вы хотите продолжить?",
				"Да", "Нет"
			);
		}
	}
	else if (dialogid == D_AUTOSERVICE + 1)
	{
		if (!response)
		{
			ShowPlayerDialog(playerid, D_AUTOSERVICE, DIALOG_STYLE_LIST, "Станция технического обслуживания", " \
				Покрасочные работы\n \
				Ремонт", 
				"Выбрать", "Закрыть"
			);
			
			return 1;
		}
		
		if (!GivePlayerCash(playerid, -REPAIR_COST))
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Недостаточно средств.");
			return 1;
		}
		
		new vehicleid = GetPVarInt(playerid, "Autoservice:VehicleId");
		RepairVehicle(vehicleid);
		
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно починили транспорт.");
		
		DeletePVar(playerid, "Autoservice:VehicleId");
	}
	else if (dialogid == D_AUTOSERVICE + 2)
	{
		if (!response)
		{
			ShowPlayerDialog(playerid, D_AUTOSERVICE, DIALOG_STYLE_LIST, "Станция технического обслуживания", " \
				Покрасочные работы\n \
				Ремонт", 
				"Выбрать", "Закрыть"
			);
			
			return 1;
		}
		
		new vehicleid = GetPVarInt(playerid, "Autoservice:VehicleId");
		
		new color1,
			color2;
			
		if (sscanf(inputtext, "p<,>dd", color1, color2)
		|| !(0 <= color1 <= 255) || !(0 <= color2 <= 255))
		{
			ShowPlayerDialog(playerid, D_AUTOSERVICE + 2, DIALOG_STYLE_INPUT, " ",
				"" #DEFAULT " Покрасочные работы\n\n\
				Стоимость покраски составит: " #cGREEN "$200" #cWHITE "\n\
				Укажите через запятую значения цвета от 0 до 255:\n\n\
				" #cGRAY "Пример: 0, 0\n\
				" #cRED "Вы неверно указали цвет.",
				"Да", "Нет"
			);
			
			return 1;
		}
		
		if (!GivePlayerCash(playerid, -RECOLOR_COST))
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Недостаточно средств.");
			return 1;
		}
		
		vehicle_data[vehicleid][v_color][0] = color1;
		vehicle_data[vehicleid][v_color][1] = color2;
		ChangeVehicleColor(vehicleid, vehicle_data[vehicleid][v_color][0], vehicle_data[vehicleid][v_color][1]);
		Update:vehicle_data(vehicleid, playerid);
		
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно перекрасили транспорт.");
	}
	
	return 1;
}