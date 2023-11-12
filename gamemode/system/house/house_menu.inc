/*!
	@brief Меню для системы домов
	@author Found (evg.savosin)
	@date 16.12.2016, update 21.03.2018
*/

ShowHouseList(playerid, const dialogid, btn_1[] = "Выбрать", btn_2[] = "Закрыть", show_type = 0)
{
	clean:<g_string>;
	
	new count = 0,
		str_zone			[	64	];
	
	
	if (show_type == 0)
	{
		strcat(g_string, "" #cPROJECT "#\t" #cPROJECT "Тип\n");
	}
	
	else if (show_type == 1)
	{
		strcat(g_string, "" #cPROJECT "#\t" #cPROJECT "Тип\t" #cPROJECT "Плата\n");
	}
	
	else if (show_type == 2)
	{
		strcat(g_string, "" #cPROJECT "#\t" #cPROJECT "Тип\t" #cPROJECT "Задолжность\n");
	}
	
	
	for (new i, index; i < MAX_PLAYER_HOUSES; i++)
	{
		if ((index = player_house[playerid][i]) == INVALID_PARAM)
		{
			continue;
		}
		
		GetHouseStreetZone(index, str_zone, sizeof str_zone);
		
		if (show_type == 0)
		{
			format:g_string("%s %s #%i, %s\t[%s" #cWHITE "]\n",
				g_string,
				IsHouseType(index) == TYPE_HOUSE ? ("House") : ("Apart."),
				GetHouseId(index),			
				str_zone,
				house_data[index][h_buy_type] == TYPE_BUY_FULLY ? ("" #cPROJECT "куплен") : ("" #cGRAY "арендован")
			);
			
			printf("house_data[%i][h_buy_type] == %i, %s", 
				index, 
				TYPE_BUY_FULLY,
				house_data[index][h_buy_type] == TYPE_BUY_FULLY ? ("" #cPROJECT "buy") : ("" #cGRAY "rent")
			);
		}
		
		else if (show_type == 1)
		{
			format:g_string("%s %s #%i, %s\t[%s" #cWHITE "]\t" #cGREEN "$%i\n",
				g_string,
				IsHouseType(index) == TYPE_HOUSE ? ("House") : ("Apart."),
				GetHouseId(index),			
				str_zone,
				house_data[index][h_buy_type] == TYPE_BUY_FULLY ? ("" #cPROJECT "куплен") : ("" #cGRAY "арендован"),
				house_data[index][h_buy_type] == TYPE_BUY_FULLY ? GetHouseCommunal(index) : GetHouseRent(index)
			);
		}
		
		else if (show_type == 2)
		{
			format:g_string("%s %s #%i, %s\t[%s" #cWHITE "]\t" #cRED "$%i\n",
				g_string,
				IsHouseType(index) == TYPE_HOUSE ? ("House") : ("Apart."),
				GetHouseId(index),			
				str_zone,
				house_data[index][h_buy_type] == TYPE_BUY_FULLY ? ("" #cPROJECT "куплен") : ("" #cGRAY "арендован"),
				GetHouseDebt(index)
			);
		}
		
		g_dialog_select[playerid][count++] = index;
	}
	
	return count ? ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ", g_string, btn_1, btn_2) : 0;
}

ShowHouseSafe(playerid, const index)
{
	format:g_string("\
		" #cGRAY "В сейфе: " #cGREEN "$%i" #cWHITE "\n \
		Взять сумму\n \
		Положить сумму", 
		house_data[index][h_money] 
	);
	
	ShowPlayerDialog(playerid, D_HOUSE + 12, DIALOG_STYLE_LIST, " ", g_string, "Выбрать", "Назад");
}

ShowHouseInformation(playerid, const index, dialogid, bool: is_owner, btn_1[], btn_2[] = "")
{	
	new zone_name			[	28	],
		lodgers = house_settings[house_data[index][h_int_type]][hset_lodgers];
		
	clean:<g_big_string>;
	
	format:g_small_string("" #DEFAULT " Информация о " #cWHITE "%s #%d\n\n",
		(IsHouseType(index) == TYPE_APARTAMENT) ? ("квартире") : ("доме"),
		house_data[index][h_id]
	);
	
	strcat(g_big_string, g_small_string);
	
	if (IsHouseType(index) == TYPE_HOUSE)
	{
		GetZoneName(
			house_data[index][h_pos][0], 
			house_data[index][h_pos][1], 
			zone_name, 
			sizeof zone_name 
		);
	}
	else 
	{
		new hindex = GetHostelIndexByHouse(index);
		
		if (hindex != INVALID_PARAM)
		{
			GetZoneName(
				hostel_data[hindex][hos_pos][0], 
				hostel_data[hindex][hos_pos][1], 
				zone_name, 
				sizeof zone_name 
			);
		}
		else 
		{
			strcat(zone_name, "Undefined", sizeof zone_name);
		}
	}
	
	format:g_small_string("Месторасположение: " #cPROJECT "%s" #cWHITE ".\n", 
		zone_name
	);
	
	strcat(g_big_string, g_small_string);
	
	if (house_data[index][h_character_id] == 0)
	{	
		format:g_small_string("Рыночная стоимость: " #cGREEN "$%i" #cWHITE ".\n", 
			house_data[index][h_price]  
		);
		
		strcat(g_big_string, g_small_string);
	}
	
	format:g_small_string("Интерьер: " #cPROJECT "%s" #cWHITE ".\n", 
		house_settings[house_data[index][h_int_type]][hset_name]
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("Коммунальные услуги: " #cGREEN "$%i" #cWHITE "/неделя.\n", 
		GetHouseCommunal(index)
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("Аренда: " #cGREEN "$%i" #cWHITE "/неделя.\n", 
		GetHouseRent(index)
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("Сожителей до: " #cPROJECT "%i" #cWHITE " %s.\n", 
		lodgers,
		lodgers == 1 ? ("персонажа") : ("персонажей")
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("Мебели до: " #cPROJECT "%i" #cWHITE " объектов.\n", 
		house_settings[house_data[index][h_int_type]][hset_furnitures]
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("Гараж: %s" #cWHITE "", 
		GetHouseGarageExists(index) ? ("" #cPROJECT "имеется") : ("отсутствует")
	);
	
	strcat(g_big_string, g_small_string);
	
	if (house_data[index][h_character_id] && is_owner)
	{
		new day,
			month,
			year,
			hour,
			minute;
		
		gmtime(house_data[index][h_time], year, month, day, hour, minute);
		if (house_data[index][h_buy_type] == TYPE_BUY_RENT)
		{
			strcat(g_big_string, "\nАренда оплачена до:");
		}
		else if (house_data[index][h_buy_type] == TYPE_BUY_FULLY)
		{
			strcat(g_big_string, "\nКоммунальные услуги оплачены до:");
		}
		
		format:g_small_string(" " #cPROJECT "" #DATE_FORMAT "" #cWHITE "", 
			hour,
			minute,
			day,
			month,
			year
		);
		
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("\nДвери: %s" #cWHITE "", 
			(house_data[index][h_lock]) ? ("" #cGRAY "Закрыты") : ("" #cPROJECT "Открыты")
		);
		
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("\nЗадолжность: %s", 
			(!house_data[index][h_debt]) ? ("не имеется") : ("")
		);
		
		strcat(g_big_string, g_small_string);
		
		if (house_data[index][h_debt])
		{
			format:g_small_string(" " #cGREEN "$%i" #cWHITE " составляет " #cPROJECT "%0.2f%%" #cWHITE " от полной стоимости", 
				house_data[index][h_debt],
				GetHouseDebtInPercent(index)
			);
			
			strcat(g_big_string, g_small_string);
		}
	}
	
	return ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, " ", g_big_string, btn_1, btn_2);
}

ShowHouseControl(playerid, const index)
{
	format:g_string(" \
		%s" #cWHITE " двери\t" #cGRAY "/hlock" #cWHITE "\n \
		%s\n \
		%s\
	",
		(house_data[index][h_lock]) ? ("" #cPROJECT "Открыть") : ("" #cGRAY "Закрыть"),
		GetHouseTypeBought(index) == TYPE_BUY_FULLY ? ("Продать") : ("Расторгнуть арендный договор"),
		GetHouseTypeBought(index) == TYPE_BUY_FULLY ? ("Продать игроку") : ("")
	);
	
	ShowPlayerDialog(playerid, D_HOUSE + 3, DIALOG_STYLE_TABLIST, " ",
		g_string,
		"Далее", "Назад" 
	);
}