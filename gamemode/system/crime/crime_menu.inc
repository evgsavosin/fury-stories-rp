/*!
	@brief ���� � ��������� ������������ ������
	@author Flavo
	@date 03.11.2019
*/

ShowCrimeList(playerid) // CMD: crmenu
{	
	clean:<g_small_string>;
	strcat(g_small_string, "\
		����������\n\
		���������\n\
		�������� �����"
	);
	
	ShowPlayerDialog(playerid, D_CRIME, DIALOG_STYLE_LIST, GetCrimeName(playerid),
		g_small_string,
		"�����", "�������"
	);
}

ShowCrimeInformation(playerid, index) // CMD: crmenu -> ����������
{
	if (!IsUserAllowQuery(playerid))
	{
		return;
	}
	
	format:g_string("\
		SELECT COUNT(cr_id) AS members_count \
		FROM " #__CRIMES_MEMBER " \
		WHERE cr_crime_id = %d",
		crime_data[index][cr_id]
	);
	
	mysql_tquery(db, g_string, "OnCrimeMemberCount", "ii", playerid, index);
	
	SetUserAllowQuery(playerid, false);
}

function OnCrimeMemberCount(playerid, index)
{
	SetUserAllowQuery(playerid, true);
	
	new rows;
	
	cache_get_row_count(rows);
	
	if (!rows)
	{
		return 0;
	}
	
	new count,
		type = crime_data[index][cr_type_id] - 1;
	
	cache_get_value_name_int(0, "members_count", count);
	
	format:g_string("" #DEFAULT " ����������\n\n\
		" #cWHITE "�������� �����������:" #cPROJECT " %s\n\
		" #cWHITE "��� �����������: " #cPROJECT " %s\n\
		" #cWHITE "����� �����������:" #cPROJECT " %s\n\
		" #cWHITE "���������� ����������:" #cPROJECT " %d\n\
		" #cWHITE "�����������:" #cPROJECT " %s\n\
		" #cWHITE "�������� �����������:" #cGREEN " $%d",
		GetCrimeName(playerid),
		crtype_data[type][cr_name],
		crime_data[index][cr_leader_name],
		count,
		crime_data[index][cr_official] ? ("��") : ("���"),
		crime_data[index][cr_money]
	);
	
	ShowPlayerDialog(playerid, D_CRIME_DATA, DIALOG_STYLE_MSGBOX, " ",
		g_string,
		"�������", ""
	);

	return 1;
}

ShowCrimeMember(playerid) // CMD: crmenu -> ���������
{
	clean:<g_string>;
	strcat(g_string, #cWHITE "������� � �����������\t" #cGRAY "/crinvite\n\
		" #cWHITE "��������� �� �����������\t" #cGRAY "\n\
		" #cWHITE "�������� ����������\n\
		" #cWHITE "������ ���� ����������"
	);
	
	ShowPlayerDialog(playerid, D_CRIME_MEMBER, DIALOG_STYLE_TABLIST , " ",
		g_string,
		"�����", "�����"
	);
}

ShowCrimeStaffUninvite(playerid, error[] = "") // CMD: crmenu -> ��������� -> ��������� �� �����������
{
	format:g_string("" #DEFAULT " ��������� �� �����������\n\n\
		������� ID ������, �������� �� ������ ��������� �� �����������:%s%s",
		!isnull(error) ? ("\n\n" #cRED) : (""), 
		error 
	);
		
	ShowPlayerDialog(playerid, D_CRIME_UNINVITE, DIALOG_STYLE_INPUT, " ",
		g_string,
		"�����", "�����"
	);
}

ShowCrimeStaffPerm(playerid, error[] = "") // CMD: crmenu -> ��������� -> �������� ����������
{
	format:g_string("" #DEFAULT " �������� ����������\n\n\
		������� ID ������, ���������� �������� �� ������ ��������:%s%s",
		!isnull(error) ? ("\n\n" #cRED) : (""), 
		error 
	);
		
	ShowPlayerDialog(playerid, D_CRIME_PERM, DIALOG_STYLE_INPUT, " ",
		g_string,
		"�����", "�����"
	);
}

ShowCrimeStaffPermEdit(playerid, targetid) // CMD: crmenu -> ��������� -> �������� ����������
{
	format:g_string(" \
		" #cWHITE "����������� ��������� � �����������\t%s\n \
		" #cWHITE "����������� ��������� �� �����������\t%s\n \
		" #cWHITE "����������� ���������� �����\t%s\n \
		" #cWHITE "����������� �������� ����������\t%s",
		crmember_data[targetid][cr_perm][cr_perm_invite] ? ("" #cPROJECT "��") : ("" #cGRAY "���"),
		crmember_data[targetid][cr_perm][cr_perm_uninvite] ? ("" #cPROJECT "��") : ("" #cGRAY "���"),
		crmember_data[targetid][cr_perm][cr_perm_buy] ? ("" #cPROJECT "��") : ("" #cGRAY "���"),
		crmember_data[targetid][cr_perm][cr_perm_manage] ? ("" #cPROJECT "��") : ("" #cGRAY "���")
	);
	
	ShowPlayerDialog(playerid, D_CRIME_EDIT_PERM, DIALOG_STYLE_TABLIST, " ",
		g_string,
		"�������", "������"
	);
}

ShowCrimeMemberList(playerid, const index, action = CRIME_LIST_BEGIN) // CMD: crmenu -> ��������� -> ������ ����������
{
	new page;
	
	if (action == CRIME_LIST_BEGIN)
	{
		SetPVarInt(playerid, "Crime:MemberPage", 0);
		page = 0;
	}
	else if (action == CRIME_LIST_CURRENT)
	{
		page = GetPVarInt(playerid, "Crime:MemberPage");
	}
	else if (action == CRIME_LIST_NEXT)
	{
		GivePVarInt(playerid, "Crime:MemberPage", 1);
		page = GetPVarInt(playerid, "Crime:MemberPage");
	}
	else if (action == CRIME_LIST_BACK)
	{
		TakePVarInt(playerid, "Crime:MemberPage", 1);
		page = GetPVarInt(playerid, "Crime:MemberPage");
	}

	format:g_string("\
		SELECT crm.*, c.c_name, c.c_online \
		FROM " #__CRIMES_MEMBER " crm, " #__CHARACTERS " c \
		WHERE crm.cr_character_id = c.c_id AND cr_crime_id = %d \
		LIMIT %d, %d",
		GetCrimeId(index),
		page * MAX_CRIME_MEMBER_LIST,
		MAX_CRIME_MEMBER_LIST + 1
	);
	
	mysql_tquery(db, g_string, "OnCrimeShowMembers", "ddd", playerid, index, page);
}

function OnCrimeShowMembers(playerid, const index, page)
{
	strglobalclear();
	
	Clear:crmember_select(playerid);
	
	new rows,
		online,
		i;
	
	cache_get_row_count(rows);
	
	if (!rows)
	{
		ShowCrimeMemberList(playerid, index, CRIME_LIST_BACK);
		
		return 1;
	}
	
	strcat(g_big_string, "" #cPROJECT " ���\t" #cPROJECT "������\n");

	for (; i < rows; i++)
	{
		if (i == MAX_CRIME_MEMBER_LIST)
		{
			break;
		}
		
		clean:<g_small_string>;
		
		cache_get_value_name_int(i, "c_online", online);
		cache_get_value_name(i, "c_name", g_small_string, MAX_PLAYER_NAME);
		cache_get_value_name_int(i, "cr_crime_id", crmember_select[playerid][i][cr_crime_id]);
		cache_get_value_name_int(i, "cr_character_id", crmember_select[playerid][i][cr_character_id]);
		cache_get_value_name_int(i, "cr_leader", crmember_select[playerid][i][cr_leader]);
		cache_get_value_name_int(i, "cr_perm_invite", crmember_select[playerid][i][cr_perm][cr_perm_invite]);
		cache_get_value_name_int(i, "cr_perm_uninvite", crmember_select[playerid][i][cr_perm][cr_perm_uninvite]);
		cache_get_value_name_int(i, "cr_perm_buy", crmember_select[playerid][i][cr_perm][cr_perm_buy]);
		cache_get_value_name_int(i, "cr_perm_manage", crmember_select[playerid][i][cr_perm][cr_perm_manage]);
	
		GetWithoutUnderscore(g_small_string, crmember_select[playerid][i][cr_name]);
		
		format:g_big_string("%s %s\t%s" #cWHITE "\n",
			g_big_string,
			crmember_select[playerid][i][cr_name],
			(online ? ("" #cPROJECT "� ����") : ("" #cGRAY "�� � ����"))
		);
	}
	
	if (i == MAX_CRIME_MEMBER_LIST && rows > MAX_CRIME_MEMBER_LIST)
	{
		strcat(g_big_string, "" #cGRAY "������\t" #cWHITE ">>");
		crmember_select[playerid][i++][cr_character_id] = CRIME_LIST_NEXT;
	}
	
	if (page > 0)
	{
		strcat(g_big_string, "\n" #cGRAY "�����\t" #cWHITE "<<");
		crmember_select[playerid][i][cr_character_id] = CRIME_LIST_BACK;
	}
	
	ShowPlayerDialog(playerid, D_CRIME_MEMBER_LIST, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"�����", "�����"
	);
	
	return 1;
}

ShowCrimeStaffInvite(playerid, error[] = "") // CMD: crmenu -> ��������� -> ������� � �����������
{
	format:g_string("" #DEFAULT " ������� � �����������\n\n\
		������� ID ������, �������� �� ������ ������� � �����������:\n\n\
		" #cGRAY "����� ������ ���������� ���������� �� ���.%s%s",
		!isnull(error) ? ("\n\n" #cRED) : (""), 
		error 
	);
	
	ShowPlayerDialog(playerid, D_CRIME_INVITE, DIALOG_STYLE_INPUT, " ",
		g_string,
		"�����", "�����"
	);
}

ShowCrimeMemberEdit(playerid, index) // CMD: crmenu -> ������ ���������� -> ��������� ��������
{
	format:g_string(" \
		" #cGRAY "��������� �� �����������\t" #cGRAY "%s\n \
		" #cWHITE "����������� ��������� � �����������\t%s\n \
		" #cWHITE "����������� ��������� �� �����������\t%s\n \
		" #cWHITE "����������� ���������� �����\t%s\n \
		" #cWHITE "����������� �������� ����������\t%s",
		crmember_select[playerid][index][cr_name],
		crmember_select[playerid][index][cr_perm][cr_perm_invite] ? ("" #cPROJECT "��") : ("" #cGRAY "���"),
		crmember_select[playerid][index][cr_perm][cr_perm_uninvite] ? ("" #cPROJECT "��") : ("" #cGRAY "���"),
		crmember_select[playerid][index][cr_perm][cr_perm_buy] ? ("" #cPROJECT "��") : ("" #cGRAY "���"),
		crmember_select[playerid][index][cr_perm][cr_perm_manage] ? ("" #cPROJECT "��") : ("" #cGRAY "���")
	);
	
	ShowPlayerDialog(playerid, D_CRIME_MEMBER_EDIT, DIALOG_STYLE_TABLIST, " ",
		g_string,
		"�������", "�����"
	);
}

ShowCrimeBuy(playerid) // CMD: crmenu -> �������� �����
{
	clean:<g_string>;
	strcat(g_string, " \
		" #cGRAY "����������\n \
		" #cGRAY "������ �������������� ������ \n \
		" #cWHITE "��������� �������\n \
		" #cWHITE "����������\n \
		" #cWHITE "������������� ��������"
	);
	
	ShowPlayerDialog(playerid, D_CRIME_BUY, DIALOG_STYLE_LIST, " ",
		g_string,
		"�����", "�����"
	);
}

ShowCrimeBuyInformation(playerid) // CMD: crmenu -> �������� ����� -> ����������
{
	format:g_big_string("\
		" #DEFAULT " ����������\n\n\
		" #cWHITE "������ � ������ ������������� ������ ������� �� ���� �����������.\n\
		" #cWHITE "������� �������������� �� �������� �����������, ������� �������������\n\
		" #cWHITE "����������� ������ " #cPROJECT "3" #cWHITE " ���.\n\
		" #cWHITE "����� ���������� �������� " #cPROJECT "%d" #cWHITE " �����.\n\
		" #cWHITE "���������� �������� ������� ����� ����������� ������ ������.\n\n\
		" #cPROJECT "%s:\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\n\
		" #cPROJECT "%s:\n\
		" #cWHITE "� ��� ������ ����������� ����\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\n\
		" #cPROJECT "%s:\n\ 
		" #cWHITE "� ��� ������ ���������� �����\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\n\
		" #cPROJECT "%s:\n\
		" #cWHITE "� ��� ������ ���������� �����\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s\n\
		" #cWHITE "� %s",
		CR_BUY_DRUGS_GRAMM,
		crtype_data[0][cr_name],
		GetInventoryItemName(7),
		GetInventoryItemName(10),
		GetInventoryItemName(17),
		crtype_data[1][cr_name],
		GetInventoryItemName(8),
		GetInventoryItemName(13),
		GetInventoryItemName(19),
		GetInventoryItemName(21),
		GetInventoryItemName(113), // marijuana
		crtype_data[2][cr_name],
		GetInventoryItemName(9),
		GetInventoryItemName(12),
		GetInventoryItemName(14),
		GetInventoryItemName(20),
		GetInventoryItemName(22),
		GetInventoryItemName(114), // lsd
		crtype_data[3][cr_name],
		GetInventoryItemName(11),
		GetInventoryItemName(15),
		GetInventoryItemName(16),
		GetInventoryItemName(18),
		GetInventoryItemName(23),
		GetInventoryItemName(24),
		GetInventoryItemName(115) // cocaine
	);
	
	ShowPlayerDialog(playerid, D_CRIME_BUY_INFORMATION, DIALOG_STYLE_MSGBOX, " ",
		g_big_string,
		"�������", ""
	);
}

ShowCrimeBuyList(playerid, const dialogid, const category) // CMD: crmenu -> �������� ����� -> ���� �� ��������� �������
{ 
	clean:<g_big_string>;
	strcat(g_big_string, #cPROJECT " ��������\t" #cPROJECT "����\n");
	
	for (new i, id; i < sizeof crbuy_data; i++)
	{
		if (crbuy_data[i][cr_buy_cat] != category
		|| crbuy_data[i][cr_buy_access_type] > crime_data[GetCrimeMember(playerid)][cr_type_id]
		)
		{
			continue;
		}
		
		id = GetItemIndexById(crbuy_data[i][cr_buy_item_id]);
		
		format:g_big_string("\
			%s\n " #cWHITE "%s\t" cGREEN "$%d",
			g_big_string,
			item_list[id][it_name],
			crbuy_data[i][cr_buy_count]
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"�������", "�����"
	);
}

ShowCrimeBuyConfirm(playerid, index) // CMD: crmenu -> �������� ����� -> ��������� ������� -> ��������� �����
{
	new id = GetItemIndexById(crbuy_data[index][cr_buy_item_id]),
		crime_id = GetCrimeMember(playerid);

	format:g_string("\
		" #DEFAULT " ������������� �������\n\n\
		" #cWHITE "�� ������������� ������ ���������� " #cPROJECT "%s" #cWHITE " �� " #cGREEN "$%d" #cWHITE "?\n\
		" #cWHITE "�������� �������: " #cGREEN "$%d",
		item_list[id][it_name],
		crbuy_data[index][cr_buy_count],
		crime_data[crime_id][cr_money]
	);
	
	ShowPlayerDialog(playerid, D_CRIME_BUY_CONFIRM, DIALOG_STYLE_MSGBOX, " ",
		g_string,
		"�����", "������"
	);
}

ShowCrimeBuyStorage(playerid, index, slot) // ��� ������� �� ������� ������� �� ����� ������� ����� �������
{
	clean:<g_big_string>;
	strcat(g_big_string, "" #cPROJECT "��������\t" #cPROJECT "����������\n");

	for (new i, id; i < MAX_CRIME_BUY; i++)
	{
		if (crbuy_storage[index][slot][cr_buy_item_storage][i] == 0)
		{
			continue;
		}
		
		id = GetItemIndexById(crbuy_data[i][cr_buy_item_id]);
		
		format:g_big_string("%s\n" #cWHITE "%s\t" #cGRAY "%d",
			g_big_string,
			item_list[id][it_name],
			crbuy_storage[index][slot][cr_buy_item_storage][i]
		);
	}

	ShowPlayerDialog(playerid, D_CRIME_BUY_STORAGE, DIALOG_STYLE_TABLIST_HEADERS, " ",
		g_big_string,
		"�������", "�����"
	);
}

ShowCrimeBuyStorageConfirm(playerid, item_index) // ��� ������ �������� �� ����� ������� ����� ������
{
	format:g_string("\
		" #DEFAULT " �������������\n\n\
		�� ������������� ������ ��������� " #cPROJECT "%s" #cWHITE "?",
		item_list[item_index][it_name]
	);
	
	ShowPlayerDialog(playerid, D_CRIME_BUY_STORAGE_CONFIRM, DIALOG_STYLE_MSGBOX, " ",
		g_string,
		"�����", "������"
	);
}