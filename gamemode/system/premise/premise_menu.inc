/*!
	@brief Система меню для помещений
	@author Found (evg.savosin)
	@date 16.12.2016, update 01.04.2018
*/

ShowPremiseList(playerid, const dialogid, btn_1[] = "Выбрать", btn_2[] = "Закрыть", show_type = 0)
{
	clean:<g_string>;
	
	new count = 0,
		str_zone			[	64	],
		name				[	MAX_BUSINESS_NAME	],
		index,
		bindex = INVALID_PARAM;
	
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
	
	else if (show_type == 3)
	{
		strcat(g_string, "" #cPROJECT "#\t" #cPROJECT "Состояние\n");
	}
	
	for (new i; i < MAX_PLAYER_PREMISES; i++)
	{
		if ((index = player_premise[playerid][i]) == INVALID_PARAM)
		{
			continue;
		}
		
		GetPremiseStreetZone(index, str_zone, sizeof str_zone);
		
		if (show_type == 0)
		{
			format:g_string("%s Premise #%i, %s\t[%s" #cWHITE "]\n",
				g_string,
				GetPremiseId(index),			
				str_zone,
				premise_data[index][pr_buy_type] == TYPE_BUY_FULLY ? ("" #cPROJECT "куплен") : ("" #cGRAY "арендован")
			);
		}
		else if (show_type == 1)
		{
			format:g_string("%s Premise #%i, %s\t[%s" #cWHITE "]\t" #cGREEN "$%i\n",
				g_string,
				GetPremiseId(index),			
				str_zone,
				premise_data[index][pr_buy_type] == TYPE_BUY_FULLY ? ("" #cPROJECT "куплен") : ("" #cGRAY "арендован"),
				premise_data[index][pr_buy_type] == TYPE_BUY_FULLY ? GetPremiseElectric(i) : GetPremiseRent(i)
			);
		}
		else if (show_type == 2)
		{
			format:g_string("%s Premise #%i, %s\t[%s" #cWHITE "]\t" #cRED "$%i\n",
				g_string,
				GetPremiseId(index),			
				str_zone,
				premise_data[index][pr_buy_type] == TYPE_BUY_FULLY ? ("" #cPROJECT "куплен") : ("" #cGRAY "арендован"),
				GetPremiseDebt(index)
			);
		}
		else if (show_type == 3)
		{	
			clean:<name>;
			if (IsPremiseTied(index))
			{
				bindex = GetBusinessIndexById(premise_data[index][pr_business_id]);
				if (bindex == INVALID_PARAM)
				{
					strcat(name, "" #cGRAY "Не привязан");
				}
				else 
				{
					format:name("" #cPROJECT "%s", GetBusinessName(bindex));
				}				
			}
			else 
			{
				strcat(name, "" #cGRAY "Не привязан");
			}
			
			format:g_string("%s Premise #%i, %s\t[%s" #cWHITE "]\n",
				g_string,
				GetPremiseId(index),			
				str_zone,
				name
			);
		}
		
		g_dialog_select[playerid][count] = index;
		count++;
	}
	
	return count ? ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ", g_string, btn_1, btn_2) : 0;
}

ShowPremiseInformation(playerid, const index, dialogid, bool: is_owner, btn_1[], btn_2[] = "")
{	
	new zone_name			[	32	];
		
	clean:<g_big_string>;
	
	format:g_small_string("" #DEFAULT " Информация о помещении #%d\n\n",
		premise_data[index][pr_id]
	);
	
	strcat(g_big_string, g_small_string);
	
	
	if (!isnull(premise_data[index][pr_name]))
	{
		format:g_small_string("Название: " #cPROJECT "%s" #cWHITE ".\n", 
			premise_data[index][pr_name]
		);
		
		strcat(g_big_string, g_small_string);
	}
	
	format:g_small_string("Двери: %s" #cWHITE ".\n", 
		(premise_data[index][pr_lock]) ? ("" #cGRAY "Закрыты") : ("" #cPROJECT "Открыты")
	);
	
	strcat(g_big_string, g_small_string);
	
	GetZoneName(
		premise_data[index][pr_pos][0], 
		premise_data[index][pr_pos][1], 
		zone_name, 
		sizeof zone_name 
	);
	
	format:g_small_string("Месторасположение: " #cPROJECT "%s" #cWHITE ".\n", 
		zone_name
	);
	
	strcat(g_big_string, g_small_string);
	
	if (!IsPremiseBought(index) || is_owner)
	{	
		format:g_small_string("Рыночная стоимость: " #cGREEN "$%i" #cWHITE ".\n", 
			premise_data[index][pr_price]  
		);
		
		strcat(g_big_string, g_small_string);
	
		format:g_small_string("Плата за электроэнергию: " #cGREEN "$%i" #cWHITE "/неделя.\n", 
			premise_settings[premise_data[index][pr_int_type]][pset_electrocity]
		);
		
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("Аренда: " #cGREEN "$%i" #cWHITE "/неделя.\n", 
			GetPremiseRent(index)
		);
		
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("Мебели до: " #cPROJECT "%i" #cWHITE " объектов.", 
			premise_settings[premise_data[index][pr_int_type]][pset_furnitures]
		);
		
		strcat(g_big_string, g_small_string);
	}
	
	if (IsPremiseBought(index) && is_owner)
	{
		new day,
			month,
			year,
			hour,
			minute,
			second;
		
		gmtime(premise_data[index][pr_time], year, month, day, hour, minute, second);
		if (premise_data[index][pr_buy_type] == TYPE_BUY_RENT)
		{
			strcat(g_big_string, "\nАренда и электроэнергия оплачена до:");
		}
		else if (premise_data[index][pr_buy_type] == TYPE_BUY_FULLY)
		{
			strcat(g_big_string, "\nЭлектроэнергия оплачена до:");
		}
		
		format:g_small_string(" " #cPROJECT "" #DATE_FORMAT "" #cWHITE ".", 
			hour,
			minute,
			day,
			month,
			year
		);
		
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("\nЗадолжность: %s.", 
			(!premise_data[index][pr_debt]) ? ("не имеется") : ("")
		);
		
		strcat(g_big_string, g_small_string);
		
		if (premise_data[index][pr_debt])
		{
			format:g_small_string(" " #cGREEN "$%i" #cWHITE " составляет " #cPROJECT "%0.2f%%" #cWHITE " от полной стоимости.", 
				premise_data[index][pr_debt],
				GetPremiseDebtInPercent(index)
			);
			
			strcat(g_big_string, g_small_string);
		}
		
		if (IsPremiseTied(index))
		{
			format:g_string("\n\n\
			Доход за этот час: " #cGREEN "$%i" #cWHITE "\n\
			Продуктов на складе: " #cPROJECT "%i ед." #cWHITE "", 
				(premise_data[index][pr_assort_stock] <= 50 ? 0 : (GetPremiseMinProfit(index) / (24 * 7)) + GetPremiseProfit(index)),
				premise_data[index][pr_assort_stock]
			);
			
			strcat(g_big_string, g_string);
		}
	}
	
	if (IsPremiseTied(index) && GetPremiseEntrance(index) != 0)
	{
		format:g_small_string("Плата за вход: " #cGREEN "$%i" #cWHITE "", 
			premise_data[index][pr_entrance]
		);
		
		strcat(g_big_string, g_small_string);
	}
	
	return ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, " ", g_big_string, btn_1, btn_2);
}

ShowPremiseControl(playerid, const index)
{
	clean:<g_small_string>;
	
	if (isnull(premise_data[index][pr_name]))
	{
		strcat(g_small_string, "" #cGRAY "Отсутствует");
	}
	else 
	{
		format:g_small_string("" #cPROJECT "%s", premise_data[index][pr_name]);
	}
	
	format:g_string(" \
		%s" #cWHITE " двери\t\n \
		Изменить название\t%s\n \
		Продать\t\n \
		Продать игроку\t",
		(premise_data[index][pr_lock]) ? ("" #cPROJECT "Открыть") : ("" #cGRAY "Закрыть"),
		g_small_string
	);
	
	ShowPlayerDialog(playerid, D_PREMISE + 3, DIALOG_STYLE_TABLIST, " ",
		g_string,
		"Далее", "Назад" 
	);
}

ShowPremiseBusinessMenu(playerid, index)
{	
	new str_entrance	[	32	];
	
	if (GetPremiseEntrance(index) != 0)
	{
		format:str_entrance("" #cGREEN "$%i" #cWHITE "", GetPremiseEntrance(index));
	}
	
	format:g_string("\
		Заказать товары\n\
		Плата за вход\t%s\t\n\
		Касса\t%s" #cWHITE "",
		str_entrance,
		IsPremiseCashExists(index) ? ("" #cGRAY "Не установлено") : ("" #cPROJECT "Установлено")
	);
	
	ShowPlayerDialog(playerid, D_PREMISE + 12, DIALOG_STYLE_TABLIST, " ", g_string, "Далее", "Назад");
}