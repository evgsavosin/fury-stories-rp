/*!
	@brief ���� ��� ������� �����
	@author Found (evg.savosin)
	@date 16.12.2016, update 21.03.2018
*/

ShowHouseList(playerid, const dialogid, btn_1[] = "�������", btn_2[] = "�������", show_type = 0)
{
	clean:<g_string>;
	
	new count = 0,
		str_zone			[	64	];
	
	
	if (show_type == 0)
	{
		strcat(g_string, "" #cPROJECT "#\t" #cPROJECT "���\n");
	}
	
	else if (show_type == 1)
	{
		strcat(g_string, "" #cPROJECT "#\t" #cPROJECT "���\t" #cPROJECT "�����\n");
	}
	
	else if (show_type == 2)
	{
		strcat(g_string, "" #cPROJECT "#\t" #cPROJECT "���\t" #cPROJECT "�����������\n");
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
				house_data[index][h_buy_type] == TYPE_BUY_FULLY ? ("" #cPROJECT "������") : ("" #cGRAY "���������")
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
				house_data[index][h_buy_type] == TYPE_BUY_FULLY ? ("" #cPROJECT "������") : ("" #cGRAY "���������"),
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
				house_data[index][h_buy_type] == TYPE_BUY_FULLY ? ("" #cPROJECT "������") : ("" #cGRAY "���������"),
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
		" #cGRAY "� �����: " #cGREEN "$%i" #cWHITE "\n \
		����� �����\n \
		�������� �����", 
		house_data[index][h_money] 
	);
	
	ShowPlayerDialog(playerid, D_HOUSE + 12, DIALOG_STYLE_LIST, " ", g_string, "�������", "�����");
}

ShowHouseInformation(playerid, const index, dialogid, bool: is_owner, btn_1[], btn_2[] = "")
{	
	new zone_name			[	28	],
		lodgers = house_settings[house_data[index][h_int_type]][hset_lodgers];
		
	clean:<g_big_string>;
	
	format:g_small_string("" #DEFAULT " ���������� � " #cWHITE "%s #%d\n\n",
		(IsHouseType(index) == TYPE_APARTAMENT) ? ("��������") : ("����"),
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
	
	format:g_small_string("�����������������: " #cPROJECT "%s" #cWHITE ".\n", 
		zone_name
	);
	
	strcat(g_big_string, g_small_string);
	
	if (house_data[index][h_character_id] == 0)
	{	
		format:g_small_string("�������� ���������: " #cGREEN "$%i" #cWHITE ".\n", 
			house_data[index][h_price]  
		);
		
		strcat(g_big_string, g_small_string);
	}
	
	format:g_small_string("��������: " #cPROJECT "%s" #cWHITE ".\n", 
		house_settings[house_data[index][h_int_type]][hset_name]
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("������������ ������: " #cGREEN "$%i" #cWHITE "/������.\n", 
		GetHouseCommunal(index)
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("������: " #cGREEN "$%i" #cWHITE "/������.\n", 
		GetHouseRent(index)
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("��������� ��: " #cPROJECT "%i" #cWHITE " %s.\n", 
		lodgers,
		lodgers == 1 ? ("���������") : ("����������")
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("������ ��: " #cPROJECT "%i" #cWHITE " ��������.\n", 
		house_settings[house_data[index][h_int_type]][hset_furnitures]
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("�����: %s" #cWHITE "", 
		GetHouseGarageExists(index) ? ("" #cPROJECT "�������") : ("�����������")
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
			strcat(g_big_string, "\n������ �������� ��:");
		}
		else if (house_data[index][h_buy_type] == TYPE_BUY_FULLY)
		{
			strcat(g_big_string, "\n������������ ������ �������� ��:");
		}
		
		format:g_small_string(" " #cPROJECT "" #DATE_FORMAT "" #cWHITE "", 
			hour,
			minute,
			day,
			month,
			year
		);
		
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("\n�����: %s" #cWHITE "", 
			(house_data[index][h_lock]) ? ("" #cGRAY "�������") : ("" #cPROJECT "�������")
		);
		
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("\n�����������: %s", 
			(!house_data[index][h_debt]) ? ("�� �������") : ("")
		);
		
		strcat(g_big_string, g_small_string);
		
		if (house_data[index][h_debt])
		{
			format:g_small_string(" " #cGREEN "$%i" #cWHITE " ���������� " #cPROJECT "%0.2f%%" #cWHITE " �� ������ ���������", 
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
		%s" #cWHITE " �����\t" #cGRAY "/hlock" #cWHITE "\n \
		%s\n \
		%s\
	",
		(house_data[index][h_lock]) ? ("" #cPROJECT "�������") : ("" #cGRAY "�������"),
		GetHouseTypeBought(index) == TYPE_BUY_FULLY ? ("�������") : ("����������� �������� �������"),
		GetHouseTypeBought(index) == TYPE_BUY_FULLY ? ("������� ������") : ("")
	);
	
	ShowPlayerDialog(playerid, D_HOUSE + 3, DIALOG_STYLE_TABLIST, " ",
		g_string,
		"�����", "�����" 
	);
}