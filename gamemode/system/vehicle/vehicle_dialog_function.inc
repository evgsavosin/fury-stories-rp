/*!
	@brief Форматированные функции для диалогов
	@author Found (evg.savosin)
	@date 11.01.2019
*/

// Window
ShowVehicleMenuWindow(playerid, vehicleid)
{
	format:g_string(" %s [переднее водительское]\t" #cGRAY "/window l\n \ 
		 " #cWHITE "%s [переднее пассажирское]\t" #cGRAY "/window r\n \
		 " #cWHITE "%s [заднее левое пассажирское]\t" #cGRAY "/window rl\n \
		 " #cWHITE "%s [заднее правое пассажирское]\t" #cGRAY "/window rr",
		vehicle_data[vehicleid][v_window][0] ? ("" #cPROJECT "Открыть" #cWHITE "") : ("" #cGRAY "Закрыть" #cWHITE ""),
		vehicle_data[vehicleid][v_window][1] ? ("" #cPROJECT "Открыть" #cWHITE "") : ("" #cGRAY "Закрыть" #cWHITE ""),
		vehicle_data[vehicleid][v_window][2] ? ("" #cPROJECT "Открыть" #cWHITE "") : ("" #cGRAY "Закрыть" #cWHITE ""),
		vehicle_data[vehicleid][v_window][3] ? ("" #cPROJECT "Открыть" #cWHITE "") : ("" #cGRAY "Закрыть" #cWHITE "")
	);
	
	ShowPlayerDialog(playerid, D_CAR + 4, DIALOG_STYLE_TABLIST, " ",
		g_string,
		 "Выбрать", "Назад" 
	);
}

// Sell
ShowVehicleSellPlayer(playerid, error[] = "")
{
	format:g_string("" #DEFAULT " Продажа транспорта\n\n\
		Продать транспорт можно только игроку.\n\
		Введите ID игрока, которому Вы хотите продать транспорт:%s\
		" #cRED "%s",
		!isnull(error) ? ("\n\n") : (""),
		error
	);
	
	return ShowPlayerDialog(playerid, D_CAR + 5, DIALOG_STYLE_INPUT, " ", g_string, "Выбрать", "Закрыть");
}

ShowVehicleSellSumm(playerid, vehicleid, error[] = "")
{
	format:g_string("" #DEFAULT " Продажа транспорта\n\n\
		Введите сумму за которую Вы хотите продать транспорт " #cPROJECT "%s" #cWHITE ":\n\n\
		" #cGRAY "Минимальная цена продажи: " #cGREEN "$%i" #cGRAY ".\n\
		" #cGRAY "Максимальная цена продажи: " #cGREEN "$%i" #cGRAY ".%s\
		" #cRED "%s",
		GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name),
		GetMinSaleVehiclePrice(vehicleid),
		GetMaxSaleVehiclePrice(vehicleid),
		!isnull(error) ? ("\n\n") : (""),
		error
	);
	
	return ShowPlayerDialog(playerid, D_CAR + 6, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
}

// Swap
ShowVehicleSellSwap(playerid, error[] = "")
{
	format:g_string("" #DEFAULT " Обмен транспорта\n\n\
		Введите ID игрока, с котором Вы хотите обменяться транспортом:%s\
		" #cRED "%s",
		!isnull(error) ? ("\n\n") : (""),
		error
	);
	
	ShowPlayerDialog(playerid, D_CAR + 9, DIALOG_STYLE_INPUT, " ", g_string, "Выбрать", "Закрыть");
}

ShowVehicleBreakRent(playerid, vehicleid)
{
	format:g_string("" #DEFAULT " Разорвать договор аренды\n\n\
	Ваш транспорт " #cPROJECT "%s" #cWHITE " был арендован в транспортном агенстве.\n\
	У Вас имеется возможность разорвать договор аренды преждевременно, но без компенсации.\n\n\
	Вы действительно хотите разорвать договор об аренде транспорта?",
		GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name)
	);
	
	ShowPlayerDialog(playerid, D_CAR + 15, DIALOG_STYLE_MSGBOX, " ", g_string, "Да", "Нет");
}