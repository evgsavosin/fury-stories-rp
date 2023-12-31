/*!
	@brief ���� ��� ������� �����������������
	@author Found (evg.savosin)
	@date 16.12.2016, update 08.03.2018
	
*/

ShowAdminEditHouse(playerid, dialogid = D_ADMIN + 8)
{
	new index = GetPVarInt(playerid, "Admin:HouseSelect");
	format:g_small_string("�������������� ���� #%d", index);
	
	format:g_string(" \
		����������\t\n \
		���������� ���� �� ���� �����\t\n \
		���������� ��������\t%s[%i]\n \
		���������� ����\t" #cGREEN "$%i\n \
		���������� ������/���. ������\t\n \
		�������� �����������\t\n \
	    �������",
		GetHouseSettings(index, hset_name),
		house_data[index][h_int_type],
		GetHousePrice(index)
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, g_small_string, 
		g_string,
		"�����", "�������"
	);
}

ShowAdminEditHouseTime(playerid, dialogid, bool: success = false, bool: error = false)
{
	new index = GetPVarInt(playerid, "Admin:HouseSelect"),
		day,
		month,
		year,
		hour,
		minute,
		second;
	
	gmtime(house_data[index][h_time], year, month, day, hour, minute, second);
	
	format:g_string("" #DEFAULT " ���������� ������/���. ������\n\n\
	�������� ��: " #cPROJECT "" #DATE_FORMAT_S "" #cWHITE "\n\
	������� ���������� ���� �� ������� �� ������ �������� ������:\n\n\
	" #cGRAY "� �������, ���� ��������� ���, �� ������ ������ �����.\n\
	���� ������, �� ���������� ������ � �������.\n\
	%s\n\
	%s",
		hour,
		minute,
		second,
		day,
		month,
		year,
		success ? ("" #cGREEN "�� ������� �������� ���� ������/���. �����. ��� ������ ����������� \"�����\".") : (""),
		error ? ("" #cRED "�� ����� �������� ���������� ����.") : ("")
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_string, "���������", "�����");
}

ShowAdminEditPremise(playerid, dialogid = D_ADMIN + 17)
{
	new index = GetPVarInt(playerid, "Admin:PremiseSelect");
	format:g_small_string("�������������� ��������� #%d", index);
	
	format:g_string(" \
		����������\t\n \
		���������� ���� �� ���� �����\t\n \
		���������� ��������\t%s[%i]\n \
		���������� ����\t" #cGREEN "$%i\n \
		���������� ������/���. ������\t\n \
		�������� �����������\t\n \
	    �������",
		GetPremiseSettings(index, pset_name),
		premise_data[index][pr_int_type],
		GetPremisePrice(index)
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, g_small_string, 
		g_string,
		"�����", "�������"
	);
}

ShowAdminEditPremiseTime(playerid, dialogid, bool: success = false, bool: error = false)
{
	new index = GetPVarInt(playerid, "Admin:PremiseSelect"),
		day,
		month,
		year,
		hour,
		minute,
		second;
	
	gmtime(premise_data[index][pr_time], year, month, day, hour, minute, second);
	
	format:g_string("" #DEFAULT " ���������� ������/���. ������\n\n\
	�������� ��: " #cPROJECT "" #DATE_FORMAT_S "" #cWHITE "\n\
	������� ���������� ���� �� ������� �� ������ �������� ������:\n\n\
	" #cGRAY "� �������, ���� ��������� ���, �� ������ ������ �����.\n\
	���� ������, �� ���������� ������ � �������.\n\
	%s\n\
	%s",
		hour,
		minute,
		second,
		day,
		month,
		year,
		success ? ("" #cGREEN "�� ������� �������� ���� ������/���. �����. ��� ������ ����������� \"�����\".") : (""),
		error ? ("" #cRED "�� ����� �������� ���������� ����.") : ("")
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_string, "���������", "�����");
}

ShowAdminHouseInteriors(playerid, dialogid)
{
	clean:<g_big_string>;
	
	for (new i = 1; i < sizeof house_settings; i++)
	{
		format:g_big_string("%s %s [%i]\n",
			g_big_string,
			house_settings[i][hset_name],
			i
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", g_big_string, "�������", "�������");
}

ShowAdminHostelInteriors(playerid, dialogid)
{
	clean:<g_big_string>;
	
	for (new i = 1, type; i < sizeof hostel_settings; i++)
	{
		type = hostel_settings[i][hos_set_type];
		format:g_big_string("%s %s [%i]\n",
			g_big_string,
			type == TYPE_HOSTEL_LOW ? ("������ �����") : (
				type == TYPE_HOSTEL_MEDIUM ? ("������� �����") : ("������� �����")
			),
			i
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", g_big_string, "�������", "�������");
}

ShowAdminPremiseInteriors(playerid, dialogid)
{
	clean:<g_big_string>;
	
	for (new i = 1; i < sizeof premise_settings; i++)
	{
		format:g_big_string("%s %s [%i]\n",
			g_big_string,
			premise_settings[i][pset_name],
			i
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", g_big_string, "�������", "�������");
}

/// Manage fraction
ShowAdminFractionList(playerid, dialogid = D_ADMIN + 23, bool: create_item = true)
{
	format:g_big_string(#cPROJECT "��������\t" #cPROJECT "�����\n");
	
	if (create_item)
	{
		strcat(g_big_string, #cGRAY "������� �������" #cWHITE "\n");
	}
	
	for (new i; i < sizeof fraction_data; i++)
	{
		if (fraction_data[i][fr_id] == 0)
		{
			continue;
		}
		
		format:g_big_string("%s %s (#%d)\t%s\n", 
			g_big_string,
			fraction_data[i][fr_name],
			fraction_data[i][fr_id],
			fraction_data[i][fr_leader_name]
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ", 
		g_big_string,
		"�����", "�������"
	);
}

// �������� �������
ShowAdminFractionCreate(playerid, const dialogid, error[] = "")
{
	if (dialogid == D_ADMIN + 24)
	{
		format:g_string(#DEFAULT " �������� �������\n\n\
			������� �������� ������� �������:%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, 
			" ", 
			g_string,
			"�����", "�����"
		);
	}
	else if (dialogid == D_ADMIN + 25)
	{
		format:g_string(#DEFAULT " �������� �������\n\n\
			������� ����������� �������� ������� (������������):%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, 
			" ", 
			g_string,
			"�����", "�����"
		);
	}
	else if (dialogid == D_ADMIN + 26)
	{
		format:g_string(#DEFAULT " �������� �������\n\n\
			������� ���� ������� � ������� " #cGRAY "0xFF" #cWHITE "FFFFFF:%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, 
			" ", 
			g_string,
			"�����", "�����"
		);
	}
	else if (dialogid == D_ADMIN + 27)
	{
		new name 		[32],
			alt_name	[32],
			color		[16];
		
		GetPVarString(playerid, "Admin:FractionName", name, sizeof name);
		GetPVarString(playerid, "Admin:FractionShortName", alt_name, sizeof alt_name);
		GetPVarString(playerid, "Admin:FractionColor", color, sizeof color);
		
		format:g_string(#DEFAULT " �������� �������\n\n\
			��������: " #cPROJECT "%s" #cWHITE "\n\
			����������� ��������: " #cPROJECT "%s" #cWHITE "\n\
			����: " #cPROJECT "%s" #cWHITE "\n\n\
			�� ������������� ������� ������� ������ �������?",
			name,
			alt_name,
			color
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, 
			" ", 
			g_string,
			"�����", "�����"
		);
	}
}

// �������������� �������
ShowAdminFractionEdit(playerid, const dialogid, index, error[] = "")
{
	if (dialogid == D_ADMIN + 28)
	{
		new str_budget			[MAX_FRACTION_BUDGET],
			str_leader_name		[MAX_PLAYER_NAME];
			
		if (isnull(fraction_data[index][fr_leader_name]))
		{
			strcat(str_leader_name, #cGRAY "�����������", MAX_PLAYER_NAME);
		}
		else 
		{
			strcat(str_leader_name, fraction_data[index][fr_leader_name], MAX_PLAYER_NAME);
		}
		
		GetFractionBudgetFormat(fraction_data[index][fr_budget], str_budget);
		
		format:g_big_string(" \
			" #cPROJECT "��������\t" #cPROJECT "��������" #cWHITE "\n \
			�������� �������\t" #cPROJECT "%s" #cWHITE "\n \
			����������� �������� �������\t" #cPROJECT "%s" #cWHITE "\n \
			����\t%06x" #cWHITE "\n \
			��������� �������\t" #cGRAY "/object" #cWHITE "\n \
			��������� ������������ �������\t" #cGRAY "/attach" #cWHITE "\n \
			��� �������������� �������\t" #cPROJECT "%s" #cWHITE "\n \
			������\t" #cPROJECT "%s" #cWHITE "\n \
			��������� �������� �� ������\n \
			�����\t" #cPROJECT "%s" #cWHITE "\n \
			" #cRED "������� �������",
			fraction_data[index][fr_name],
			fraction_data[index][fr_alt_name],
			fraction_data[index][fr_color],
			fraction_data[index][fr_type_budget] == FRAC_BUDGET_GOV ? ("���������������") : ("������������"),
			str_budget,
			str_leader_name
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "�����", "�����");
	}
	else if (dialogid == D_ADMIN + 29)
	{
		format:g_big_string("\
			" #DEFAULT " �������� �������\n\n\
			������� ��������: " #cPROJECT "%s" #cWHITE "\n\
			������� ����� ��������:%s%s",
			fraction_data[index][fr_name],
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
	}
	else if (dialogid == D_ADMIN + 30)
	{
		format:g_big_string("\
			" #DEFAULT " ����������� �������� �������\n\n\
			������� ��������: " #cPROJECT "%s" #cWHITE "\n\
			������� ����� ��������:%s%s",
			fraction_data[index][fr_alt_name],
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
	}
	else if (dialogid == D_ADMIN + 31)
	{
		format:g_big_string("\
			" #DEFAULT " ���� �������\n\n\
			������� ����: " #cPROJECT "%06x" #cWHITE "\n\
			������� ����� ���� � ������� " #cGRAY "FFFFFF" #cWHITE ":%s%s",
			fraction_data[index][fr_color],
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
	}
	else if (dialogid == D_ADMIN + 32)
	{
		ShowFractionObjectList(playerid, dialogid, index);
	}
	else if (dialogid == D_ADMIN + 38)
	{
		ShowFractionAttachList(playerid, dialogid, index);
	}
	else if (dialogid == D_ADMIN + 44)
	{
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", #cGRAY "\
			�������� ��� ��������������:\n \
			���������������\t" #cGRAY "������������� ���������� ������\n \
			������������\t" #cGRAY "������ ������������ ��������������", 
			"�����", "�����"
		);
	}
	else if (dialogid == D_ADMIN + 45)
	{
		new str_budget	[16];
		
		// ������
		GetFractionBudgetFormat(fraction_data[index][fr_budget], str_budget);
		
		format:g_big_string("\
			" #DEFAULT " ������\n\n\
			������� ������ �������: " #cGREEN "%s" #cWHITE "\n\
			������� ����� ������ � ������� " #cGRAY "0,000 (�� ������� - ����., ����� - ���.)" #cWHITE ":\n\n\
			" #cGRAY "������ �� ������ ���� ���� $99.999 ����. ��� ���� $0.000 ����.%s%s",
			str_budget,
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
	}
	else if (dialogid == D_ADMIN + 46)
	{
		ShowFractionItemList(playerid, dialogid, index);
	}
	else if (dialogid == D_ADMIN + 49)
	{
		format:g_big_string("\
			" #ERROR " �������� �������\n\n\
			�� ������������� ������� ������� " #cPROJECT "%s" #cWHITE "?",
			fraction_data[index][fr_name]
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, " ", g_big_string, "�����", "�����");
	}
	else if (dialogid == D_ADMIN + 50)
	{
		new str_leader_name 	[MAX_PLAYER_NAME];
		
		if (isnull(fraction_data[index][fr_leader_name]))
		{
			strcat(str_leader_name, #cGRAY "�����������");
		}
		else
		{
			strcat(str_leader_name, fraction_data[index][fr_leader_name]);
		}
			
		format:g_string("\
			" #DEFAULT " �����\n\n\
			������� �����: " #cPROJECT "%s" #cWHITE "\n\
			" #cWHITE "������� ��� � ������� �������� ������ �������:\n\n\
			" #cGRAY "������������ ����� ������ - " #cPROJECT "%d" #cWHITE" ��������.\n\
			������ ��������� ������: " #cPROJECT "���_�������" #cWHITE".\n\
			��� ����, ����� ������ ����� ������, ��������� ������ ������.%s%s",
			str_leader_name,
			MAX_PLAYER_NAME - 4,
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);

		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ",
			g_string,
			"�����", "�����"
		);
	}
}

// �������������� �������
ShowAdminFractionObjectEdit(playerid, const dialogid, index = INVALID_PARAM, error[] = "")
{
	if (dialogid == D_ADMIN + 33)
	{
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", " \
			�������� ��������\n \
			�������� ID �������\n \
			" #cRED "������� ������",
			"�������", "�����"
		);
	}
	else if (dialogid == D_ADMIN + 34)
	{
		format:g_big_string("\
			" #DEFAULT " �������� �������\n\n\
			������� ��������: " #cPROJECT "%s" #cWHITE "\n\
			������� ����� ��������:%s%s",
			fraction_item_select[playerid][index][fr_name],
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
	}
	else if (dialogid == D_ADMIN + 35)
	{
		format:g_big_string("\
			" #DEFAULT " ID �������\n\n\
			������� ID �������: " #cPROJECT "%d" #cWHITE "\n\
			������� ����� ID �������:%s%s",
			fraction_item_select[playerid][index][fr_object_id],
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
	}
	else if (dialogid == D_ADMIN + 36)
	{
		format:g_big_string("\
			" #DEFAULT " �������� ������\n\n\
			������� ID �������:%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
	}
	else if (dialogid == D_ADMIN + 37)
	{
		format:g_big_string("\
			" #DEFAULT " �������� ������\n\n\
			������� ��� �������:%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
	}
}

// �������������� ������
ShowAdminFractionAttachEdit(playerid, const dialogid, index = INVALID_PARAM, error[] = "")
{
	if (dialogid == D_ADMIN + 39)
	{
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", " \
			�������� ��������\n \
			�������� ID ������\n \
			" #cRED "������� ������",
			"�������", "�����"
		);
	}
	else if (dialogid == D_ADMIN + 40)
	{
		format:g_big_string("\
			" #DEFAULT " �������� ������\n\n\
			������� ��������: " #cPROJECT "%s" #cWHITE "\n\
			������� ����� ��������:%s%s",
			fraction_item_select[playerid][index][fr_name],
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
	}
	else if (dialogid == D_ADMIN + 41)
	{
		format:g_big_string("\
			" #DEFAULT " ID ������\n\n\
			������� ID ������: " #cPROJECT "%d" #cWHITE "\n\
			������� ����� ID ������:%s%s",
			fraction_item_select[playerid][index][fr_object_id],
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
	}
	else if (dialogid == D_ADMIN + 42)
	{
		format:g_big_string("\
			" #DEFAULT " �������� �����\n\n\
			������� ID ������:%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
	}
	else if (dialogid == D_ADMIN + 43)
	{
		printf("%d dialogid D_ADMIN + 43 call", dialogid);
		format:g_big_string("\
			" #DEFAULT " �������� �����\n\n\
			������� ��� ������:%s%s",
			isnull(error) ? ("") : ("\n\n" #cRED),
			error
		);
		
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
	}
}

ShowAdminCrimeEditName(playerid) // CMD:crmanage -> �������������� -> �������� ��������
{
	format:g_string("\
		" #DEFAULT " ��������� ��������.\n\n\
		" #cWHITE "������� �������� ������������ ����������� � ���� ��� �����.\n\n\
		" #cGRAY " ����������:\n\
		" #cPROJECT "* " #cWHITE "������������ ����� ������ - " #cPROJECT "%d" #cWHITE " ������.",
		MAX_CRIME_NAME-1
	);
	
	ShowPlayerDialog(playerid, D_ADMIN_CRIME_EDIT_NAME, DIALOG_STYLE_INPUT, " ",
		g_string,
		"�����", "�����"
	);
	
	return 1;
}

ShowAdminCrimeEditStatus(playerid) // CMD:crmanage -> �������������� -> �������� ������
{
	clean:<g_string>;

	strcat(g_string, #cPROJECT " ������ �������" #cWHITE "\n \
		����������\n \
		�����������"
	);

	ShowPlayerDialog(playerid, D_ADMIN_CRIME_EDIT_STATUS, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_string,
		"�����", "�����"
	);
	
	return 1;
}

ShowAdminCrimeType(playerid, const dialogid) // CMD:crmanage <-> ��� �������
{
	clean:<g_string>;
	
	strcat(g_string, #cGRAY " �������� ��� �������" #cWHITE "\n");
	
	for (new i; i < MAX_CRIME_TYPE; i++)
	{
		if (crtype_data[i][cr_id] == 0)
		{
			continue;
		}
		
		format:g_string("%s%s \n",
			g_string,
			crtype_data[i][cr_name]
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ",
		g_string,
		"�����", "�����"
	);
}

ShowAdminCrimeEditLeader(playerid) // CMD:crmanage -> �������������� -> ��������� ������
{
	format:g_string("\
		" #DEFAULT " ��������� ������\n\n\
		" #cWHITE "������� ��� � ������� ������ ������������ ����������� � ���� ��� �����.\n\n\
		" #cGRAY "����������:\n\
		" #cPROJECT "* " #cWHITE"������������ ����� ������ - " #cPROJECT "%d" #cWHITE" ��������.\n\
		" #cPROJECT "* " #cWHITE"������ ��������� ������: " #cPROJECT "���_�������" #cWHITE".",
		MAX_PLAYER_NAME-4
	);

	ShowPlayerDialog(playerid, D_ADMIN_CRIME_EDIT_LEADER, DIALOG_STYLE_INPUT, " ",
		g_string,
		"�����", "�����"
	);
}

ShowAdminCrimeDeleteLeader(playerid, index) // CMD:crmanage -> �������������� -> ����� ������
{
	format:g_small_string("\
		" #ERROR " �� ������������� ������ ������� ������ ������� " #cPROJECT "%s" #cWHITE " - " #cPROJECT "%s" #cWHITE "?",
		crime_data[index][cr_name],
		crime_data[index][cr_leader_name]
	);
	
	ShowPlayerDialog(playerid, D_ADMIN_CRIME_DELETE_LEADER, DIALOG_STYLE_MSGBOX, " ",
		g_small_string,
		"�����", "������"
	);
}

ShowAdminCrimeEditConfirm(playerid, index) // CMD:crmanage -> �������������� -> ������� �������
{
	format:g_string("\
		" #ERROR " �� ������������� ������ ������� ������� " #cPROJECT "%s" #cWHITE "?",
		crime_data[index][cr_name]
	);
	
	ShowPlayerDialog(playerid, D_ADMIN_CRIME_CONFIRM, DIALOG_STYLE_MSGBOX, " ",
		g_string,
		"�����", "������"
	);
}

ShowAdminCrimeList(playerid) // CMD:crmanage
{
	clean:<g_big_string>;
	
	strcat(g_big_string, #cPROJECT "��������\t" #cPROJECT "�����������\t" #cPROJECT "�����\n\
	" #cGRAY "������� �������" #cGRAY "\n");
	
	for (new i; i < sizeof crime_data; i++)
	{
		if (crime_data[i][cr_id] == 0)
		{
			continue;
		}
		
		format:g_big_string("%s %s (#%d)\t%s\t" #cPROJECT "%s" #cWHITE "\n",
			g_big_string,
			crime_data[i][cr_name],
			crime_data[i][cr_id],
			crime_data[i][cr_official] ? ("��") : ("���"),
			crime_data[i][cr_leader_name]
		);
	}
	
	ShowPlayerDialog(playerid, D_ADMIN_CRIME, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"�����", "�������"
	);
}

ShowAdminCrimeCreate(playerid) // CMD:crmanage -> ������� �������
{	
	strglobalclear();
	
	GetPVarString(playerid, "Admin:CrimeCreateName", g_small_string, sizeof g_small_string);
	GetPVarString(playerid, "Admin:CrimeCreateType", g_string, sizeof g_string);
	
	format:g_big_string("\
		" #cPROJECT "��������\t" #cPROJECT "��������" #cWHITE "\n \
		��������\t" #cPROJECT "%s" #cWHITE "\n \
		���\t" #cPROJECT "%s" #cWHITE "\n \
		" #cGRAY "�������",
		g_small_string,
		g_string
	);
	
	ShowPlayerDialog(playerid, D_ADMIN_CRIME_CREATE, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"�����", "�����"
	);
}

ShowAdminCrimeCreateName(playerid) // CMD:crmanage -> ������� ������� -> ��������
{
	format:g_big_string("\
		" #DEFAULT " ��������� ��������.\n\n\
		" #cWHITE "������� �������� ������������ ����������� � ���� ��� �����.\n\n\
		" #cGRAY " ����������:\n\
		" #cPROJECT "* " #cWHITE "������������ ����� ������ - " #cPROJECT "%d" #cWHITE " ������.",
		MAX_CRIME_NAME-1
	);

	ShowPlayerDialog(playerid, D_ADMIN_CRIME_CREATE_NAME, DIALOG_STYLE_INPUT, " ",
		g_big_string,
		"�����", "�����"
	);
}

ShowAdminCrimeEdit(playerid, index) // CMD:crmanage -> �������������� ������� �� ������� �� ���
{
	format:g_big_string("\
		" #cPROJECT " ��������\t" #cPROJECT "��������\n \
		" #cWHITE "�������� ��������\t" #cPROJECT "%s\n \
		" #cWHITE "�������� ������\t" #cPROJECT "%s\n \
		" #cWHITE "�������� ���\t" #cPROJECT "%s\n \
		" #cWHITE "��������� ������\t" #cPROJECT "%s\n \
		" #cWHITE "����� ������\n \
		" #cRED "������� �������",
		crime_data[index][cr_name],
		crime_data[index][cr_official] ? ("�����������") : ("����������"),
		GetCrimeTypeName(index),
		crime_data[index][cr_leader_name]
	);
	
	ShowPlayerDialog(playerid, D_ADMIN_CRIME_EDIT, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"�����", "�����"
	);
	
	return 1;
}

ShowAdminDisconnectionLog(playerid)
{
	clean:<g_big_string>;
	strcat(g_big_string, "" #cPROJECT "��� ��������\t" #cPROJECT "��� ���������\t" #cPROJECT "�������\t" #cPROJECT "�����\n" #cWHITE ""
	);
	
	for (new i, end_i; i < MAX_ADMIN_LOGS; i++)
	{
		if (isnull(admin_logs[i][alog_disconnect][alog_user_name]) || end_i >= 1)
		{
			break;
		}
		
		if ((i + 2) < MAX_ADMIN_LOGS)
		{
			if (isnull(admin_logs[i + 1][alog_disconnect][alog_user_name]))
			{
				end_i++;
			}
		}
		
		format:g_big_string("%s %s\t%s\t%s\t%s%d:%s%d:%s%d\n",
			g_big_string,
			admin_logs[i][alog_disconnect][alog_user_name],
			admin_logs[i][alog_disconnect][alog_character_name],
			(admin_logs[i][alog_disconnect][alog_reason] == 0) ? ("�������") : ((admin_logs[i][alog_disconnect][alog_reason] == 1) ? ("�����") : ("���������� ��������")),
			(admin_logs[i][alog_disconnect][alog_time_hour] > 9) ? ("") : ("0"),
			admin_logs[i][alog_disconnect][alog_time_hour],
			(admin_logs[i][alog_disconnect][alog_time_minute] > 9) ? ("") : ("0"),
			admin_logs[i][alog_disconnect][alog_time_minute],
			(admin_logs[i][alog_disconnect][alog_time_second] > 9) ? ("") : ("0"),
			admin_logs[i][alog_disconnect][alog_time_second]
		);
	}
	
	ShowPlayerDialog(playerid, D_ADMIN_DISLOG, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"������", ""
	);
}

ShowAdminDeathLog(playerid)
{
	clean:<g_big_string>;
	strcat(g_big_string, "" #cPROJECT "��� ���������\t" #cPROJECT "������� ������\t" #cPROJECT "��� ������\t" #cPROJECT "�����\n" #cWHITE ""
	);
	
	for (new i, end_i; i < MAX_ADMIN_LOGS; i++)
	{
		if (isnull(admin_logs[i][alog_death][alog_user_name]) || end_i >= 1)
		{
			break;
		}
		
		if ((i + 2) < MAX_ADMIN_LOGS)
		{
			if (isnull(admin_logs[i + 1][alog_death][alog_user_name]))
			{
				end_i++;
			}
		}
		
		format:g_small_string("%s", admin_logs[i][alog_death][alog_killer_name]);
		
		format:g_big_string("%s %s\t%s\t%s\t%s%d:%s%d:%s%d\n",
			g_big_string,
			admin_logs[i][alog_death][alog_character_name],
			ShowPlayerDeathReason(admin_logs[i][alog_death][alog_reason]),
			(isnull(admin_logs[i][alog_death][alog_killer_name])) ? ("~") : (g_small_string),
			(admin_logs[i][alog_death][alog_time_hour] > 9) ? ("") : ("0"),
			admin_logs[i][alog_death][alog_time_hour],
			(admin_logs[i][alog_death][alog_time_minute] > 9) ? ("") : ("0"),
			admin_logs[i][alog_death][alog_time_minute],
			(admin_logs[i][alog_death][alog_time_second] > 9) ? ("") : ("0"),
			admin_logs[i][alog_death][alog_time_second]
		);
	}
	
	ShowPlayerDialog(playerid, D_ADMIN_DISLOG, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"������", ""
	);
}