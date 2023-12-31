/*!
	@brief ������� ��� ������� ���������
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

CMD:prlist(playerid)
{
	if (!ShowPremiseList(playerid, INVALID_DIALOG_ID, "�������", "", 0))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_PREMISE);
	}
	
	return 1;
}

CMD:prmenu(playerid)
{
	PremiseMenu(playerid);
	return 1;
}

PremiseMenu(playerid, show_message = true)
{
	clean:<g_small_string>;
	
	new world = GetPlayerVirtualWorld(playerid),
		index = GetPremiseIndexById(world),
		bindex = INVALID_PARAM;
	
	if (!IsPlayerInPremise(playerid, index, world) || !IsValidPremise(world))
	{
		if (show_message)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " ��� ������������� ������ �������, �� ������ ���������� � ���������.");
		}
		
		return 0;
	}
	
	SetPVarInt(playerid, "Premise:Select", index);
	SetPVarInt(playerid, "Premise:IsOwner", 0);
	
	if (!IsPremiseBought(index))
	{
		format:g_string(
			" ���������� � ���������\n \
			���������� �� " #cGREEN "$%d\n \
			���������� �� " #cGREEN "$%d" #cWHITE "/������",
			premise_data[index][pr_price],
			GetPremiseRent(index) 
		);
		
		ShowPlayerDialog(playerid, D_PREMISE + 1, DIALOG_STYLE_LIST, 
			" ",
			g_string,
			"�����", "�������"
		);
		
		return 1;
	}
	
	if (!CheckPremiseAccess(TYPE_PREMISE_MEMBER, playerid, index))
	{
		if (show_message)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " ������ ��������� �� �������� ����� �������������� ���� � ��� ��� ������� � ����.");
		}
		
		return 0;
	}

	SetPVarInt(playerid, "Premise:IsOwner", 1);
	
	if (IsPremiseTied(index))
	{
		bindex = GetBusinessIndexById(premise_data[index][pr_business_id]);
		if (bindex != INVALID_PARAM)
		{
			strcat(g_small_string, business_data[bindex][b_name], MAX_BUSINESS_NAME);
		}
	}
	
	format:g_string(
		" ���������� � ���������\t\n \
		 ���������� ����������\t\n \
		 ���������� ���������\t" #cPROJECT "%s\n \
		 ����� �������\t%s",
		 g_small_string,
		(IsPlayerRenovation(playerid)) ? ("" #cPROJECT "�������") : ("" #cGRAY "��������")
	);
	
	ShowPlayerDialog(playerid, D_PREMISE + 1, DIALOG_STYLE_TABLIST, 
		" ",
		g_string,
		"�����", "�������"
	);
	
	return 1;
}

PremiseRenovation(playerid) // @cmd: /ren
{
	new renovation = IsPlayerRenovation(playerid);
		
	if (!renovation)
	{
		SendClientMessage(playerid, C_WHITE, !NOT_RENOVATION_MODE);
		
		return 0;
	}
	
	new world = GetPlayerVirtualWorld(playerid),
		index = GetPremiseIndexById(world);
		
	if (!IsPlayerInPremise(playerid, index, world) || !IsValidPremise(world))
	{
		if (renovation)
		{
			SetRenovationMode(playerid, false, TYPE_REN_PREMISE, index);
		}
		
		SendClientMessage(playerid, C_WHITE, !#ERROR " ��� ������������� ������ ������� �� ������ ���������� � ����� ���������.");
	
		return 0;
	}
	
	if (GetRenovationType(playerid) != TYPE_REN_PREMISE
	&& GetRenovationId(playerid) != world)
	{
		return 0;
	}
	
	SetPVarInt(playerid, "Premise:Select", index);
	SetPVarInt(playerid, "Premise:IsOwner", 0);
	
	ShowPlayerDialog(playerid, D_PREMISE + 9, DIALOG_STYLE_TABLIST, " ", 
		" ������� ���� ���������\t" #cGRAY "/prmenu\n \
		����������� ������\n \
		��������� �������",
		"�����", "�������"
	);
	
	return 1;
}

CMD:prlock(playerid)
{
	PremiseLock(playerid);
	return 1;
}