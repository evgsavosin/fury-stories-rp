/*!
	@brief ������� ���� ��� ���������
	@author Found (evg.savosin)
	@date 16.12.2016, update 01.04.2018
*/

ShowPremiseList(playerid, const dialogid, btn_1[] = "�������", btn_2[] = "�������", show_type = 0)
{
	clean:<g_string>;
	
	new count = 0,
		str_zone			[	64	],
		name				[	MAX_BUSINESS_NAME	],
		index,
		bindex = INVALID_PARAM;
	
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
	
	else if (show_type == 3)
	{
		strcat(g_string, "" #cPROJECT "#\t" #cPROJECT "���������\n");
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
				premise_data[index][pr_buy_type] == TYPE_BUY_FULLY ? ("" #cPROJECT "������") : ("" #cGRAY "���������")
			);
		}
		else if (show_type == 1)
		{
			format:g_string("%s Premise #%i, %s\t[%s" #cWHITE "]\t" #cGREEN "$%i\n",
				g_string,
				GetPremiseId(index),			
				str_zone,
				premise_data[index][pr_buy_type] == TYPE_BUY_FULLY ? ("" #cPROJECT "������") : ("" #cGRAY "���������"),
				premise_data[index][pr_buy_type] == TYPE_BUY_FULLY ? GetPremiseElectric(i) : GetPremiseRent(i)
			);
		}
		else if (show_type == 2)
		{
			format:g_string("%s Premise #%i, %s\t[%s" #cWHITE "]\t" #cRED "$%i\n",
				g_string,
				GetPremiseId(index),			
				str_zone,
				premise_data[index][pr_buy_type] == TYPE_BUY_FULLY ? ("" #cPROJECT "������") : ("" #cGRAY "���������"),
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
					strcat(name, "" #cGRAY "�� ��������");
				}
				else 
				{
					format:name("" #cPROJECT "%s", GetBusinessName(bindex));
				}				
			}
			else 
			{
				strcat(name, "" #cGRAY "�� ��������");
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
	
	format:g_small_string("" #DEFAULT " ���������� � ��������� #%d\n\n",
		premise_data[index][pr_id]
	);
	
	strcat(g_big_string, g_small_string);
	
	
	if (!isnull(premise_data[index][pr_name]))
	{
		format:g_small_string("��������: " #cPROJECT "%s" #cWHITE ".\n", 
			premise_data[index][pr_name]
		);
		
		strcat(g_big_string, g_small_string);
	}
	
	format:g_small_string("�����: %s" #cWHITE ".\n", 
		(premise_data[index][pr_lock]) ? ("" #cGRAY "�������") : ("" #cPROJECT "�������")
	);
	
	strcat(g_big_string, g_small_string);
	
	GetZoneName(
		premise_data[index][pr_pos][0], 
		premise_data[index][pr_pos][1], 
		zone_name, 
		sizeof zone_name 
	);
	
	format:g_small_string("�����������������: " #cPROJECT "%s" #cWHITE ".\n", 
		zone_name
	);
	
	strcat(g_big_string, g_small_string);
	
	if (!IsPremiseBought(index) || is_owner)
	{	
		format:g_small_string("�������� ���������: " #cGREEN "$%i" #cWHITE ".\n", 
			premise_data[index][pr_price]  
		);
		
		strcat(g_big_string, g_small_string);
	
		format:g_small_string("����� �� ��������������: " #cGREEN "$%i" #cWHITE "/������.\n", 
			premise_settings[premise_data[index][pr_int_type]][pset_electrocity]
		);
		
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("������: " #cGREEN "$%i" #cWHITE "/������.\n", 
			GetPremiseRent(index)
		);
		
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("������ ��: " #cPROJECT "%i" #cWHITE " ��������.", 
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
			strcat(g_big_string, "\n������ � �������������� �������� ��:");
		}
		else if (premise_data[index][pr_buy_type] == TYPE_BUY_FULLY)
		{
			strcat(g_big_string, "\n�������������� �������� ��:");
		}
		
		format:g_small_string(" " #cPROJECT "" #DATE_FORMAT "" #cWHITE ".", 
			hour,
			minute,
			day,
			month,
			year
		);
		
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("\n�����������: %s.", 
			(!premise_data[index][pr_debt]) ? ("�� �������") : ("")
		);
		
		strcat(g_big_string, g_small_string);
		
		if (premise_data[index][pr_debt])
		{
			format:g_small_string(" " #cGREEN "$%i" #cWHITE " ���������� " #cPROJECT "%0.2f%%" #cWHITE " �� ������ ���������.", 
				premise_data[index][pr_debt],
				GetPremiseDebtInPercent(index)
			);
			
			strcat(g_big_string, g_small_string);
		}
		
		if (IsPremiseTied(index))
		{
			format:g_string("\n\n\
			����� �� ���� ���: " #cGREEN "$%i" #cWHITE "\n\
			��������� �� ������: " #cPROJECT "%i ��." #cWHITE "", 
				(premise_data[index][pr_assort_stock] <= 50 ? 0 : (GetPremiseMinProfit(index) / (24 * 7)) + GetPremiseProfit(index)),
				premise_data[index][pr_assort_stock]
			);
			
			strcat(g_big_string, g_string);
		}
	}
	
	if (IsPremiseTied(index) && GetPremiseEntrance(index) != 0)
	{
		format:g_small_string("����� �� ����: " #cGREEN "$%i" #cWHITE "", 
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
		strcat(g_small_string, "" #cGRAY "�����������");
	}
	else 
	{
		format:g_small_string("" #cPROJECT "%s", premise_data[index][pr_name]);
	}
	
	format:g_string(" \
		%s" #cWHITE " �����\t\n \
		�������� ��������\t%s\n \
		�������\t\n \
		������� ������\t",
		(premise_data[index][pr_lock]) ? ("" #cPROJECT "�������") : ("" #cGRAY "�������"),
		g_small_string
	);
	
	ShowPlayerDialog(playerid, D_PREMISE + 3, DIALOG_STYLE_TABLIST, " ",
		g_string,
		"�����", "�����" 
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
		�������� ������\n\
		����� �� ����\t%s\t\n\
		�����\t%s" #cWHITE "",
		str_entrance,
		IsPremiseCashExists(index) ? ("" #cGRAY "�� �����������") : ("" #cPROJECT "�����������")
	);
	
	ShowPlayerDialog(playerid, D_PREMISE + 12, DIALOG_STYLE_TABLIST, " ", g_string, "�����", "�����");
}