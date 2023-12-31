/*!
	@brief ������� ��� ������� �������
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

ShowFractionInformation(playerid, index, dialogid = D_FRACTION + 1)
{
	new str_budget	[MAX_FRACTION_BUDGET];
	
	GetFractionBudgetFormat(fraction_data[index][fr_budget], str_budget);
	
	format:g_big_string(#DEFAULT " ���������� �� �����������\n\n\
		��������: " #cPROJECT "%s" #cWHITE "\n\
		����������� ��������: " #cPROJECT "%s" #cWHITE "\n\
		��� ��������������: " #cPROJECT "%s" #cWHITE "\n\
		������: " #cPROJECT "%s" #cWHITE "",
		GetFractionName(index),
		GetFractionAltName(index),
		fraction_data[index][fr_type_budget] == FRAC_BUDGET_GOV ? ("���������������") : ("������������"),
		str_budget
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, " ", g_big_string, "�����", "");
}

ShowFractionUnitInformation(playerid, index, uindex, dialogid)
{	
	format:g_big_string(#DEFAULT " ���������� � �������������\n\n\
		��������: " #cPROJECT "%s" #cWHITE "\n\
		����������� ��������: " #cPROJECT "%s" #cWHITE "\n\
		�����: " #cPROJECT "%s" #cWHITE "",
		fraction_unit_data[index][uindex][fr_name],
		fraction_unit_data[index][uindex][fr_alt_name],
		fraction_unit_data[index][uindex][fr_leader_name]
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, " ", g_big_string, "�����", "");
}

ShowFractionObjectList(playerid, dialogid, index, action = ITEM_LIST_BEGIN, text[] = #cGRAY "�������� ������\t" #cWHITE "\n")
{
	if (!IsUserAllowQuery(playerid))
	{
		return;
	}
	
	new page;
	
	if (action == ITEM_LIST_BEGIN)
	{
		SetPVarInt(playerid, "Fraction:ObjectPage", 0);
		page = 0;
	}
	else if (action == ITEM_LIST_CURRENT)
	{
		page = GetPVarInt(playerid, "Fraction:ObjectPage");
	}
	else if (action == ITEM_LIST_NEXT)
	{
		GivePVarInt(playerid, "Fraction:ObjectPage", 1);
		page = GetPVarInt(playerid, "Fraction:ObjectPage");
	}
	else if (action == ITEM_LIST_BACK)
	{
		TakePVarInt(playerid, "Fraction:ObjectPage", 1);
		page = GetPVarInt(playerid, "Fraction:ObjectPage");
	}
	
	format:g_string("SELECT * FROM " #__FRACTIONS_OBJECT " WHERE fo_fraction_id = %d LIMIT %d, %d", 
		fraction_data[index][fr_id],
		page * MAX_ITEM_LIST,
		MAX_ITEM_LIST
	);

	mysql_tquery(db, g_string, "OnFractionShowObjectList", "dddds", playerid, dialogid, index, page, text);
	
	SetUserAllowQuery(playerid, false);
}

function OnFractionShowObjectList(playerid, dialogid, index, page, text[])
{
	SetUserAllowQuery(playerid, true);
	
	new rows;
	
	cache_get_row_count(rows);
	
	clean:<g_big_string>;
	strcat(g_big_string, #cPROJECT "��������\t" #cPROJECT "ID �������\n");
	
	if (!isnull(text))
	{
		strcat(g_big_string, text);
	}
	
	new count;
	
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "fo_id", fraction_item_select[playerid][i][fr_id]);
		cache_get_value_name_int(i, "fo_object_id", fraction_item_select[playerid][i][fr_object_id]);
		cache_get_value_name(i, "fo_name", fraction_item_select[playerid][i][fr_name], 32);
		
		format:g_big_string("%s %s\t%d\n",
			g_big_string,
			fraction_item_select[playerid][i][fr_name],
			fraction_item_select[playerid][i][fr_object_id]
		);
		
		if (count++ == MAX_ITEM_LIST)
		{
			break;
		}
	}
	
	if (count == MAX_ITEM_LIST)
	{
		strcat(g_big_string, "" #cGRAY "������\t\t" #cWHITE ">>");
		fraction_item_select[playerid][count++][fr_id] = ITEM_LIST_NEXT;
	}
	
	if (page > 0)
	{
		strcat(g_big_string, "\n" #cGRAY "�����\t" #cWHITE "<<");
		fraction_item_select[playerid][count][fr_id] = ITEM_LIST_BACK;
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "�������", "�������");
	
	return 1;
}

ShowFractionAttachList(playerid, dialogid, index, action = ITEM_LIST_BEGIN, text[] = #cGRAY "�������� �����\t" #cWHITE "\n")
{
	if (!IsUserAllowQuery(playerid))
	{
		return;
	}
	
	new page;
	
	if (action == ITEM_LIST_BEGIN)
	{
		SetPVarInt(playerid, "Fraction:ObjectPage", 0);
		page = 0;
	}
	else if (action == ITEM_LIST_CURRENT)
	{
		page = GetPVarInt(playerid, "Fraction:ObjectPage");
	}
	else if (action == ITEM_LIST_NEXT)
	{
		GivePVarInt(playerid, "Fraction:ObjectPage", 1);
		page = GetPVarInt(playerid, "Fraction:ObjectPage");
	}
	else if (action == ITEM_LIST_BACK)
	{
		TakePVarInt(playerid, "Fraction:ObjectPage", 1);
		page = GetPVarInt(playerid, "Fraction:ObjectPage");
	}
	
	format:g_string("SELECT * FROM " #__FRACTIONS_ATTACH " WHERE fr_fraction_id = %d LIMIT %d, %d", 
		fraction_data[index][fr_id],
		page * MAX_ITEM_LIST,
		MAX_ITEM_LIST
	);

	mysql_tquery(db, g_string, "OnFractionShowAttachList", "dddds", playerid, dialogid, index, page, text);
	
	SetUserAllowQuery(playerid, false);
}

function OnFractionShowAttachList(playerid, dialogid, index, page, text[])
{
	SetUserAllowQuery(playerid, true);
	
	new rows;
	
	cache_get_row_count(rows);
	
	clean:<g_big_string>;
	strcat(g_big_string, #cPROJECT "��������\t" #cPROJECT "ID �������\n");
	
	if (!isnull(text))
	{
		strcat(g_big_string, text);
	}
	
	new count;
	
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "fr_id", fraction_item_select[playerid][i][fr_id]);
		cache_get_value_name_int(i, "fr_object_id", fraction_item_select[playerid][i][fr_object_id]);
		cache_get_value_name(i, "fr_name", fraction_item_select[playerid][i][fr_name], 32);
		
		format:g_big_string("%s %s\t%d\n",
			g_big_string,
			fraction_item_select[playerid][i][fr_name],
			fraction_item_select[playerid][i][fr_object_id]
		);
		
		if (count++ == MAX_ITEM_LIST)
		{
			break;
		}
	}
	
	if (count == MAX_ITEM_LIST)
	{
		strcat(g_big_string, "" #cGRAY "������\t\t" #cWHITE ">>");
		fraction_item_select[playerid][count++][fr_id] = ITEM_LIST_NEXT;
	}
	
	if (page > 0)
	{
		strcat(g_big_string, "\n" #cGRAY "�����\t" #cWHITE "<<");
		fraction_item_select[playerid][count][fr_id] = ITEM_LIST_BACK;
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "�������", "�������");
	
	return 1;
}

ShowFractionItemList(playerid, dialogid, index, action = ITEM_LIST_BEGIN)
{
	if (!IsUserAllowQuery(playerid))
	{
		return;
	}
	
	new page;
	
	if (action == ITEM_LIST_BEGIN)
	{
		SetPVarInt(playerid, "Fraction:ObjectPage", 0);
		page = 0;
	}
	else if (action == ITEM_LIST_CURRENT)
	{
		page = GetPVarInt(playerid, "Fraction:ObjectPage");
	}
	else if (action == ITEM_LIST_NEXT)
	{
		GivePVarInt(playerid, "Fraction:ObjectPage", 1);
		page = GetPVarInt(playerid, "Fraction:ObjectPage");
	}
	else if (action == ITEM_LIST_BACK)
	{
		TakePVarInt(playerid, "Fraction:ObjectPage", 1);
		page = GetPVarInt(playerid, "Fraction:ObjectPage");
	}
	
	format:g_string("SELECT * FROM " #__FRACTIONS_ITEM " WHERE fr_fraction_id = %d LIMIT %d, %d", 
		fraction_data[index][fr_id],
		page * MAX_ITEM_LIST,
		MAX_ITEM_LIST
	);

	mysql_tquery(db, g_string, "OnFractionShowItemList", "dddd", playerid, dialogid, index, page);
	
	SetUserAllowQuery(playerid, false);
}

function OnFractionShowItemList(playerid, dialogid, index, page)
{
	SetUserAllowQuery(playerid, true);

	new rows;
	
	cache_get_row_count(rows);
	
	clean:<g_big_string>;
	
	if (dialogid != D_FRACTION + 50)
	{
		strcat(g_big_string, #cGRAY "�������� �������\n");
	}
	
	new i,
		itindex;
		
	new str_item_params	[128];
	
	for (; i < rows; i++)
	{
		clean:<str_item_params>;
		
		cache_get_value_name_int(i, "fr_id", fraction_item_select[playerid][i][fr_id]);
		cache_get_value_name_int(i, "fr_item_id", fraction_item_select[playerid][i][fr_object_id]);
		cache_get_value_name_int(i, "fr_item_param_1", fraction_item_select[playerid][i][fr_item_param_1]);
		cache_get_value_name_int(i, "fr_item_param_2", fraction_item_select[playerid][i][fr_item_param_2]);
		
		itindex = GetItemIndexById(fraction_item_select[playerid][i][fr_object_id]);
		if (itindex == INVALID_PARAM)
		{
			continue;
		}
		
		GetInventoryItemValueFormat(
			itindex,
			fraction_item_select[playerid][i][fr_item_param_1],
			fraction_item_select[playerid][i][fr_item_param_2],
			str_item_params,
			true
		);
		
		format:g_big_string("%s %s\t%s\n",
			g_big_string,
			GetInventoryItemName(itindex),
			str_item_params
		);
		
		if (i == MAX_ITEM_LIST)
		{
			break;
		}
	}
	
	if (i++ == MAX_ITEM_LIST)
	{
		strcat(g_big_string, "" #cGRAY "������\t\t" #cWHITE ">>");
		fraction_item_select[playerid][i++][fr_id] = ITEM_LIST_NEXT;
	}
	
	if (page > 0)
	{
		strcat(g_big_string, "\n" #cGRAY "�����\t" #cWHITE "<<");
		fraction_item_select[playerid][i][fr_id] = ITEM_LIST_BACK;
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, " ", g_big_string, "�������", "�������");
	
	return 1;
}

ShowFractionStaff(playerid)
{
	ShowPlayerDialog(playerid, D_FRACTION + 2, DIALOG_STYLE_TABLIST_HEADERS, " ",
		"" #cPROJECT "��������\t" #cPROJECT "�������\n \
		������� � �����������\t" #cGRAY "/finvite\n \
		������� �� �����������\t" #cGRAY "/funinvite\n \
		�������� ����\t" #cGRAY "/setrank\n \
		�������� �������������\t" #cGRAY "/setunit\n \
		������ ���� �����������\t" #cGRAY "/fmembers",
		"�����", "�����"
	);
}

ShowFractionStaffInvite(playerid, error[] = "")
{
	format:g_string("\
		" #DEFAULT " ������� � �����������\n\
		\n\
		������� ID ������, �������� �� ������ ������� � �����������:\n\n\
		" #cGRAY "����� ������ ��������� ���������� �� ���.%s%s",
		!isnull(error) ? ("\n" #cRED) : (""),
		error
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 3, DIALOG_STYLE_INPUT, " ",
		g_string,
		"�����", "�����"
	);
}

ShowFractionStaffUninvite(playerid, error[] = "")
{
	format:g_string("\
		" #DEFAULT " ������� �� �����������\n\
		\n\
		������� ID ������, �������� �� ������ ������� �� �����������:%s%s",
		!isnull(error) ? ("\n\n" #cRED) : (""),
		error
	);
		
	ShowPlayerDialog(playerid, D_FRACTION + 5, DIALOG_STYLE_INPUT, " ",
		g_string,
		"�����", "�����"
	);
}

ShowFractionStaffSetRank(playerid, error[] = "")
{
	format:g_string("\
		" #DEFAULT " �������� ����\n\
		\n\
		������� ID ������, ��� �������� �� ������ �������� ����:%s%s",
		!isnull(error) ? ("\n\n" #cRED) : (""),
		error
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 6, DIALOG_STYLE_INPUT, " ",
		g_string,
		"�����", "�����"
	);
}

ShowFractionStaffSetUnit(playerid, error[] = "")
{
	format:g_string("\
		" #DEFAULT " �������� �������������\n\
		\n\
		������� ID ������, ��� �������� �� ������ �������� �������������:%s%s",
		!isnull(error) ? ("\n\n" #cRED) : (""),
		error
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 8, DIALOG_STYLE_INPUT, " ",
		g_string,
		"�����", "�����"
	);
}

ShowFractionRanks(playerid, const dialogid, index, text[] = #cGRAY "�������� ����:\n")
{
	new count;
	
	clean:<g_big_string>;
	strcat(g_big_string, text);
	
	for (new i; i < MAX_FRACTION_RANKS; i++)
	{
		if (fraction_rank_data[index][i][fr_id] == 0)
		{
			continue;
		}
		
		format:g_big_string("%s %s\n", 
			g_big_string,
			fraction_rank_data[index][i][fr_name]
		);
		
		g_dialog_select[playerid][count++] = i; 
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", g_big_string, "�������", "�����");
}

ShowFractionUnits(playerid, const dialogid, index, text[] = #cGRAY "�������� �������������:\n")
{
	new count;
	
	clean:<g_big_string>;
	strcat(g_big_string, text);
	
	for (new i; i < MAX_FRACTION_UNITS; i++)
	{
		if (fraction_unit_data[index][i][fr_id] == 0)
		{
			continue;
		}
		
		format:g_big_string("%s %s\n", 
			g_big_string,
			fraction_unit_data[index][i][fr_name]
		);
		
		g_dialog_select[playerid][count++] = i; 
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, " ", g_big_string, "�������", "�����");
	
	return count;
}

ShowFractionMembers(playerid, dialogid, index, action = ITEM_LIST_BEGIN)
{
	new page;
	
	if (action == ITEM_LIST_BEGIN)
	{
		SetPVarInt(playerid, "Fraction:MemberPage", 0);
		page = 0;
	}
	else if (action == ITEM_LIST_CURRENT)
	{
		page = GetPVarInt(playerid, "Fraction:MemberPage");
	}
	else if (action == ITEM_LIST_NEXT)
	{
		GivePVarInt(playerid, "Fraction:MemberPage", 1);
		page = GetPVarInt(playerid, "Fraction:MemberPage");
	}
	else if (action == ITEM_LIST_BACK)
	{
		TakePVarInt(playerid, "Fraction:MemberPage", 1);
		page = GetPVarInt(playerid, "Fraction:MemberPage");
	}
	
	format:g_string("SELECT * FROM " #__CHARACTERS " WHERE c_fraction_id = %d LIMIT %d, %d", 
		GetFractionId(index),
		page * MAX_ITEM_LIST,
		MAX_ITEM_LIST
	);
	
	mysql_tquery(db, g_string, "OnFractionShowMembers", "dddd", playerid, dialogid, page, index);
}

function OnFractionShowMembers(playerid, dialogid, page, index)
{
	new rows;
	
	cache_get_row_count(rows);
	
	clean:<g_big_string>;
	strcat(g_big_string, #cPROJECT "���\t" #cPROJECT "����\t" #cPROJECT "�������������\t" #cPROJECT "������\n");
	
	new count,
		rindex,
		uindex;
		
	new str_rank		[MAX_FRACTION_RANK_NAME],
		str_unit		[MAX_FRACTION_NAME];
	
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "c_id", fraction_member_select[playerid][i][fr_id]);
		cache_get_value_name(i, "c_name", fraction_member_select[playerid][i][fr_name], MAX_PLAYER_NAME);
		cache_get_value_name_int(i, "c_online", fraction_member_select[playerid][i][fr_status]);
		
		// ����
		cache_get_value_name_int(i, "c_fraction_rank_id", fraction_member_select[playerid][i][fr_rank_index]);
		fraction_member_select[playerid][i][fr_rank_index] = rindex = GetFractionRankById(index, fraction_member_select[playerid][i][fr_rank_index]);
		
		clean:<str_rank>;
		if (rindex != INVALID_PARAM)
		{
			format:str_rank(#cPROJECT "%s", fraction_rank_data[index][rindex][fr_name]);
		}
		else 
		{
			strcat(str_rank, #cGRAY "���");
		}
		
		// �������������
		cache_get_value_name_int(i, "c_fraction_unit_id", fraction_member_select[playerid][i][fr_unit_index]);
		fraction_member_select[playerid][i][fr_unit_index] = uindex = GetFractionUnitById(index, fraction_member_select[playerid][i][fr_unit_index]);
		
		clean:<str_unit>;
		if (uindex != INVALID_PARAM)
		{
			format:str_unit(#cPROJECT "%s", fraction_unit_data[index][uindex][fr_name]);
		}
		else 
		{
			strcat(str_unit, #cGRAY "���");
		}
		
		format:g_big_string("%s %s\t%s\t%s\t%s\n",
			g_big_string,
			fraction_member_select[playerid][i][fr_name],
			str_rank,
			str_unit,
			fraction_member_select[playerid][i][fr_status] ? (#cPROJECT "� ����") : (#cGRAY "�� � ����")
		);
		
		g_dialog_select[playerid][count++] = i;
		
		if (count == MAX_ITEM_LIST)
		{
			break;
		}
	}
	
	if (count == MAX_ITEM_LIST)
	{
		strcat(g_big_string, "" #cGRAY "������\t\t" #cWHITE ">>");
		g_dialog_select[playerid][count++] = ITEM_LIST_NEXT;
	}
	
	if (page > 0)
	{
		strcat(g_big_string, "\n" #cGRAY "�����\t" #cWHITE "<<");
		g_dialog_select[playerid][count] = ITEM_LIST_BACK;
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "�������", "�����");

	return 1;
}

ShowFractionMemberSelect(playerid, index)
{
	new findex = GetFractionMember(playerid),
		uindex = fraction_member_select[playerid][index][fr_unit_index],
		rindex = fraction_member_select[playerid][index][fr_rank_index];
	
	new str_rank	[MAX_FRACTION_RANK_NAME],
		str_unit	[MAX_FRACTION_UNIT_NAME];
	
	clean:<str_rank>;
	if (rindex != INVALID_PARAM)
	{
		format:str_rank(#cPROJECT "%s", fraction_rank_data[findex][rindex][fr_name]);
	}
	else 
	{
		strcat(str_rank, #cGRAY "���");
	}
	
	clean:<str_unit>;
	if (uindex != INVALID_PARAM)
	{
		format:str_unit(#cPROJECT "%s", fraction_unit_data[findex][uindex][fr_name]);
	}
	else 
	{
		strcat(str_unit, #cGRAY "���");
	}

	clean:<g_big_string>;
	format:g_big_string("\
		" #cGRAY "�������\t" #cPROJECT "%s" #cWHITE "\n \
		�������� ����\t" #cPROJECT "%s" #cWHITE "\n \
		�������� �������������\t" #cPROJECT "%s",
		fraction_member_select[playerid][index][fr_name],
		str_rank,
		str_unit
	);

	ShowPlayerDialog(playerid, D_FRACTION + 11, DIALOG_STYLE_TABLIST, " ", g_big_string, "�������", "�����");
}

ShowFractionVehicles(playerid, dialogid, action = ITEM_LIST_BEGIN)
{
	clean:<g_big_string>;
	strcat(g_big_string, "" #cPROJECT "��������\t" #cPROJECT "������\n\
	" #cGRAY "�������� ���������\n");
	
	new index = GetFractionMember(playerid),
		id = GetFractionIdByIndex(index), 
		count,
		page;
	
	if (id == 0)
	{
		return;
	}
	
	if (action == ITEM_LIST_BEGIN)
	{
		SetPVarInt(playerid, "Fraction:VehiclePage", 0);
		page = 0;
	}
	else if (action == ITEM_LIST_CURRENT)
	{
		page = GetPVarInt(playerid, "Fraction:VehiclePage");
	}
	else if (action == ITEM_LIST_NEXT)
	{
		GivePVarInt(playerid, "Fraction:VehiclePage", 1);
		page = GetPVarInt(playerid, "Fraction:VehiclePage");
	}
	else if (action == ITEM_LIST_BACK)
	{
		TakePVarInt(playerid, "Fraction:VehiclePage", 1);
		page = GetPVarInt(playerid, "Fraction:VehiclePage");
	}
	
	for (new i, j, v = GetVehiclePoolSize(); i < v; i++)
	{
		if (vehicle_data[i][v_owner_type] == TYPE_VEH_FRACTION
		&& vehicle_data[i][v_owner_id] == id)
		{
			if (j != (page * MAX_ITEM_LIST))
			{
				j++;
				continue;
			}
			
			format:g_big_string("%s %s\t%d\n", 
				g_big_string, 
				GetVehicleInfo(vehicle_data[i][v_model], v_name),
				vehicle_data[i][v_model]
			);
			
			g_dialog_select[playerid][count++] = i;
			
			if (count == MAX_ITEM_LIST)
			{
				break;
			}
		}
	}
	
	if (count == MAX_ITEM_LIST)
	{
		strcat(g_big_string, "" #cGRAY "������\t\t" #cWHITE ">>");
		g_dialog_select[playerid][count++] = ITEM_LIST_NEXT;
	}
	
	if (page > 0)
	{
		strcat(g_big_string, "\n" #cGRAY "�����\t" #cWHITE "<<");
		g_dialog_select[playerid][count] = ITEM_LIST_BACK;
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "�������", "�����");
}

ShowFractionVehicleAddModel(playerid, error[] = "")
{
	format:g_string("\
		" #DEFAULT " ���������� ����������\n\n\
		������� " #cPROJECT "ID ������" #cWHITE " ����������:\n\n\
		" #cGRAY "������ ���������� ����� ���� �� 400 �� 611.\n\
		������� ���� ��� ����� ���������� ������ ���� ������������.%s%s",
		isnull(error) ? ("") : (cRED "\n\n"),
		error
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 19, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

ShowFractionVehicleAddColor(playerid, error[] = "")
{
	format:g_string("\
		" #DEFAULT " ���������� ����������\n\n\
		������� ����� ������� " #cPROJECT "���� 1 � ���� 2" #cWHITE " ��� ����������:\n\n\
		" #cGRAY "�������� ����� ����� ���� ������ �� 1 � �� 255.%s%s",
		isnull(error) ? ("") : (cRED "\n\n"),
		error
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 20, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

ShowFractionVehicleAddNumber(playerid, error[] = "")
{
	format:g_string("\
		" #DEFAULT " ���������� ����������\n\n\
		������� ����� ����������:\n\n\
		" #cGRAY "����� ������ ��������� ������ ��������� ����� � �����.\n\
		������� ���� ������ ���� �������.\n\
		����������� ����� ����� - 4 �������, ������������ - 8.%s%s",
		isnull(error) ? ("") : (cRED "\n\n"),
		error
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 21, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

ShowFractionSettingsAddRank(playerid, error[] = "")
{
	format:g_string("\
		" #DEFAULT " ���������� �����\n\n\
		������� �������� �������� �����:\n\n\
		" #cGRAY "����� ����� �� ������ ��������� %d �������.%s%s",
		MAX_FRACTION_RANK_NAME,
		isnull(error) ? ("") : (cRED "\n\n"),
		error
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 25, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

ShowFractionSettingsEditRank(playerid, findex, index)
{
	format:g_big_string("" #cPROJECT "��������\t" #cPROJECT "��������\n \
		��������\t" #cPROJECT "%s\n \
		���������� �����\t" #cGREEN "$%d\n \
		����������� ��������� �� �������\t%s\n \
		����������� ��������� �� �������\t%s\n \
		��������� �����\t%s\n \
		��������� �������������\t%s\n \
		������ � ������� �������� �������\t%s\n \
		������������ ������� �����\t%s\n \
		������ � �������� " #cGRAY "(/object)" #cWHITE "\t%s\n \
		������ � ������������ �������� " #cGRAY "(/attach)" #cWHITE "\t%s\n \
		������������� ����������\t%s\n \
		������������� ��������� ������\t%s\n \
		������ � ���������\t%s\n \
		������ � ������\t%s\n \
		������� ��������� �� ����������� �����\t%s\n \
		�������������\n \
		" #cRED "������� ����",
		fraction_rank_data[findex][index][fr_name],
		fraction_rank_data[findex][index][fr_salary],
		fraction_rank_data[findex][index][fr_perm_invite] ? (#cPROJECT "��") : (#cGRAY "���"),
		fraction_rank_data[findex][index][fr_perm_uninvite] ? (#cPROJECT "��") : (#cGRAY "���"),
		fraction_rank_data[findex][index][fr_perm_set_rank] ? (#cPROJECT "��") : (#cGRAY "���"),
		fraction_rank_data[findex][index][fr_perm_set_unit] ? (#cPROJECT "��") : (#cGRAY "���"),
		fraction_rank_data[findex][index][fr_perm_manage] ? (#cPROJECT "��") : (#cGRAY "���"),
		fraction_rank_data[findex][index][fr_perm_radio] ? (#cPROJECT "��") : (#cGRAY "���"),
		fraction_rank_data[findex][index][fr_perm_object] ? (#cPROJECT "��") : (#cGRAY "���"),
		fraction_rank_data[findex][index][fr_perm_attach] ? (#cPROJECT "��") : (#cGRAY "���"),
		fraction_rank_data[findex][index][fr_perm_vehicle] ? (#cPROJECT "��") : (#cGRAY "���"),
		fraction_rank_data[findex][index][fr_perm_clothes] ? (#cPROJECT "��") : (#cGRAY "���"),
		fraction_rank_data[findex][index][fr_perm_items] ? (#cPROJECT "��") : (#cGRAY "���"),
		fraction_rank_data[findex][index][fr_perm_weapon] ? (#cPROJECT "��") : (#cGRAY "���"),
		fraction_rank_data[findex][index][fr_perm_spawn_vehicle] ? (#cPROJECT "��") : (#cGRAY "���")
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 26, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "�����", "�����");
}

ShowFractionEditRankCustom(playerid, findex)
{
	new fraction_id = GetFractionIdByIndex(findex);
	
	switch (fraction_id)
	{
		default:
		{
			ShowPlayerDialog(playerid, D_FRACTION + 30, DIALOG_STYLE_MSGBOX, " ",
				"" #ERROR " �������������� ���������\n\n\
				��� ����� ����������� ����������� �������������� ���������.",
				"�����", ""
			);
		}
	}
}

ShowFractionEditRankName(playerid, error[] = "")
{
	format:g_string("\
		" #DEFAULT " �������� ��������\n\n\
		������� ����� �������� �����:\n\n\
		" #cGRAY "����� ����� �� ������ ��������� %d �������.%s%s",
		MAX_FRACTION_RANK_NAME,
		isnull(error) ? ("") : (cRED "\n\n"),
		error
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 27, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

ShowFractionEditRankSalary(playerid, index, error[] = "")
{
	format:g_string("\
		" #DEFAULT " �������� ���������� �����\n\n\
		����������� � ������������ ���������� ����� ������������ ��������.\n\
		����������� ���������� �����: " #cGREEN "$%d" #cWHITE "\n\
		������������ ���������� �����: " #cGREEN "$%d" #cWHITE "\n\n\
		������� ���������� ����� ��� ������� �����:%s%s",
		GetFractionMinSalary(index),
		GetFractionMaxSalary(index),
		isnull(error) ? ("") : (cRED "\n\n"),
		error
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 28, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

ShowFractionAddUnit(playerid, error[] = "")
{
	format:g_string("\
		" #DEFAULT " ���������� �������������\n\n\
		������� �������� �������� �������������:\n\n\
		" #cGRAY "����� ������������� �� ������ ��������� %d �������.%s%s",
		MAX_FRACTION_NAME,
		isnull(error) ? ("") : (cRED "\n\n"),
		error
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 32, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

ShowFractionAddUnitAltName(playerid, error[] = "")
{
	format:g_string("\
		" #DEFAULT " ���������� �������������\n\n\
		������� ����������� �������� �������� �������������:\n\n\
		" #cGRAY "����� ������������� �� ������ ��������� %d �������.%s%s",
		MAX_FRACTION_ALT_NAME,
		isnull(error) ? ("") : (cRED "\n\n"),
		error
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 33, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

ShowFractionEditUnit(playerid, findex, index)
{
	new bool: is_spawn_exists = fraction_unit_data[findex][index][fr_pos_x] == 0.0 && fraction_unit_data[findex][index][fr_pos_y] == 0.0;
	
	new str_leader	[64];
	
	if (isnull(fraction_unit_data[findex][index][fr_leader_name]))
	{
		strcat(str_leader, #cGRAY "�����������");
	}
	else 
	{
		format:str_leader(#cPROJECT "%s", fraction_unit_data[findex][index][fr_leader_name]);
	}
	
	clean:<g_big_string>;
	format:g_big_string("\
		" #cPROJECT "��������\t" #cPROJECT "��������\n \
		�������� �������������\t" #cPROJECT "%s" #cWHITE "\n \
		����������� �������� �������������\t" #cPROJECT "%s" #cWHITE "\n \
		�����\t" #cPROJECT "%s\n \
		������\t\n \
		����� ���������\t%s\n \
		" #cRED "������� �������������",
		fraction_unit_data[findex][index][fr_name],
		fraction_unit_data[findex][index][fr_alt_name],
		str_leader,
		!is_spawn_exists ? (#cPROJECT "�����������") : (#cGRAY "�� �����������")
	);

	ShowPlayerDialog(playerid, D_FRACTION + 34, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "�������", "�����");
}

ShowFractionEditUnitName(playerid, error[] = "")
{
	format:g_string("\
		" #DEFAULT " �������� ��������\n\n\
		������� ����� �������� �������������:\n\n\
		" #cGRAY "����� ������������� �� ������ ��������� %d �������.%s%s",
		MAX_FRACTION_NAME,
		isnull(error) ? ("") : (cRED "\n\n"),
		error
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 35, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

ShowFractionEditUnitAltName(playerid, error[] = "")
{
	format:g_string("\
		" #DEFAULT " �������� ����������� ��������\n\n\
		������� ����� ����������� �������� �������������:\n\n\
		" #cGRAY "����� ������������� �� ������ ��������� %d �������.%s%s",
		MAX_FRACTION_NAME,
		isnull(error) ? ("") : (cRED "\n\n"),
		error
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 36, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

ShowFractionEditUnitLeader(playerid, findex, index, error[] = "")
{
	new str_leader_name 	[MAX_PLAYER_NAME];
		
	if (isnull(fraction_unit_data[findex][index][fr_leader_name]))
	{
		strcat(str_leader_name, #cGRAY "�����������");
	}
	else
	{
		strcat(str_leader_name, fraction_unit_data[findex][index][fr_leader_name]);
	}
		
	format:g_string("\
		" #DEFAULT " �����\n\n\
		������� �����: " #cPROJECT "%s" #cWHITE "\n\
		" #cWHITE "������� ��� � ������� �������� ������ �������������:\n\n\
		" #cGRAY "������������ ����� ������ - " #cPROJECT "%d" #cWHITE" ��������.\n\
		������ ��������� ������: " #cPROJECT "���_�������" #cWHITE".\n\
		��� ����, ����� ������ ����� ������, ��������� ������ ������.%s%s",
		str_leader_name,
		MAX_PLAYER_NAME - 4,
		isnull(error) ? ("") : ("\n\n" #cRED),
		error
	);

	ShowPlayerDialog(playerid, D_FRACTION + 37, DIALOG_STYLE_INPUT, " ",
		g_string,
		"�����", "�����"
	);
}

ShowFractionUnitSkins(playerid, findex, index)
{
	clean:<g_big_string>;
	strcat(g_big_string, #cGRAY "�������� ������\n");
	
	new count;
	for (new i; i < MAX_FRACTION_SKINS; i++)
	{
		if (fraction_unit_data[findex][index][fr_skins][i] == 0)
		{
			continue;
		}
		
		format:g_big_string("%s ������ #%d\n", 
			g_big_string,
			fraction_unit_data[findex][index][fr_skins][i]
		);
		
		g_dialog_select[playerid][count++] = i;
	}
	
	ShowPlayerDialog(playerid, D_FRACTION + 38, DIALOG_STYLE_LIST, " ", g_big_string, "�����", "�����");
}

ShowFractionUnitSkinsAdd(playerid, error[] = "")
{
	format:g_string("\
		" #DEFAULT " ���������� ������\n\n\
		������� " #cPROJECT "ID �����" #cWHITE ":\n\n\
		" #cGRAY "�������� ����� ���� �� 1 �� 311.%s%s",
		isnull(error) ? ("") : (cRED "\n\n"),
		error
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 39, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

ShowFractionUnitSpawn(playerid, findex, index)
{
	new bool: is_spawn_exists = fraction_unit_data[findex][index][fr_pos_x] == 0.0 && fraction_unit_data[findex][index][fr_pos_y] == 0.0;
	
	format:g_string("\
		" #DEFAULT " ���������� ����� ���������\n\n\
		����� ���������: %s" #cWHITE "\n\n\
		����� ������ '�����', �� ���������� ����� ����� ���������.\n\
		���������� �������� ����� ��������� ����� ����� �� ������� ������� ���������.",
		is_spawn_exists ? (#cGRAY "�� �����������") : (#cPROJECT "�����������")
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 41, DIALOG_STYLE_MSGBOX, " ", g_string, "�����", "�����");
}

ShowFractionJoinRank(playerid, index)
{
	new rindex = GetFractionRankById(index, fraction_data[index][fr_join_rank_id]);
				
	clean:<g_small_string>;
	if (rindex != INVALID_PARAM)
	{
		format:g_small_string(#cGRAY "������� ����: %s\n", fraction_rank_data[index][rindex][fr_name]);
	}
	else 
	{
		strcat(g_small_string, #cGRAY "������� ����: �����������\n");
	}
	
	ShowFractionRanks(playerid, D_FRACTION + 43, index, g_small_string);
}