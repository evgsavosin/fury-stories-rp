/*!
	@brief ������� ��� ������� �����
	@author Found (evg.savosin)
	@date 16.12.2016, update 25.03.2018
*/

/*!
	@brief ������� ��� ����
*/

CMD:hlist(playerid)
{
	if (!ShowHouseList(playerid, INVALID_DIALOG_ID, "�������", "", 0))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_HOUSE);
	}
	
	return 1;
}

CMD:hmenu(playerid)
{
	HouseMenu(playerid);
	return 1;
}

HouseMenu(playerid, show_message = true)
{
	Clear:house_pvar(playerid);
	
	new world = GetCharacterWorld(playerid),
		index = GetHouseIndexById(world);
	
	if (!IsPlayerInHouse(playerid, index) || !IsValidHouse(world))
	{
		if (show_message)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " ��� ������������� ������ ������� �� ������ ���������� � �������� ���������.");
		}
		
		return 0;
	}
	
	SetPVarInt(playerid, "House:Select", index);
	SetPVarInt(playerid, "House:IsOwner", 0);
	
	if (!IsHouseBought(index))
	{
		format:g_string(
			" ���������� � %s\n \
			���������� �� " #cGREEN "$%d\n \
			���������� �� " #cGREEN "$%d" #cWHITE "/������",
			(house_data[index][h_interior]) ? ("��������") : ("����"),
			house_data[index][h_price],
			GetHouseRent(index) 
		);
		
		ShowPlayerDialog(playerid, D_HOUSE + 1, DIALOG_STYLE_LIST, 
			" ",
			g_string,
			"�����", "�������"
		);
		
		return 1;
	}
	
	if (!CheckHouseAccess(TYPE_HOUSE_LODGER, playerid, index))
	{
		if (show_message)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " ������ ��� �� �������� ����� �������������� ���� � ��� ��� ������� � ����.");
		}
		
		return 0;
	}

	SetPVarInt(playerid, "House:IsOwner", 1);
	
	format:g_string(
		" ���������� � %s\n \
		 ���������� %s\n \
		 ��������\n \
		 ����� �������\t%s\n \
		 ����\
		 %s",
		(house_data[index][h_interior]) ? ("��������") : ("����"),
		(house_data[index][h_interior]) ? ("���������") : ("�����"),
		(IsPlayerRenovation(playerid)) ? ("" #cPROJECT "�������") : ("" #cGRAY "��������"),
		(GetHouseGarageExists(index)) ? ("\n ����� � �����") : ("")
	);
	
	ShowPlayerDialog(playerid, D_HOUSE + 1, DIALOG_STYLE_TABLIST, 
		" ",
		g_string,
		"�����", "�������"
	);
	return 1;
}

CMD:hlock(playerid)
{
	HouseLock(playerid);
	return 1;
}

/*!
	@brief ������� ��� ������
*/

CMD:gmenu(playerid)
{
	GarageMenu(playerid);
	return 1;
}

GarageMenu(playerid, show_message = true)
{
	Clear:house_pvar(playerid);
	
	new world = GetCharacterWorld(playerid),
		index = GetHouseIndexById(world);
		
	if (!IsPlayerInGarage(playerid, index, world) || !IsValidHouse(world))
	{
		if (show_message)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " ��� ������������� ������ �������, �� ������ ���������� � ����� ������.");
		}
		
		return 0;
	}

	if (!CheckHouseAccess(TYPE_HOUSE_LODGER, playerid, index, lod_perm_garage))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " ������ ����� �� �������� ����� �������������� ���� � ��� ��� ������� � ����.");
		
		return 0;
	}
	
	SetPVarInt(playerid, "Garage:Select", index);
	
	format:g_string(
		"���������� �������\n\
		 ������ ���������\t" #cGRAY "/carlist\n\
		 ����� �������\t%s\n\
		 ���������",
		(IsPlayerRenovation(playerid)) ? ("" #cPROJECT "�������") : ("" #cGRAY "��������")
	);
	
	ShowPlayerDialog(playerid, D_GARAGE, DIALOG_STYLE_TABLIST, 
		" ",
		g_string,
		"�����", "�������"
	);
	
	return 1;
}

HouseRenovation(playerid) // @cmd: /ren
{
	new renovation = IsPlayerRenovation(playerid);
		
	if (!renovation)
	{
		SendClientMessage(playerid, C_WHITE, !NOT_RENOVATION_MODE);
		
		return 0;
	}
	
	new world = GetPlayerVirtualWorld(playerid),
		index = GetHouseIndexById(world);
		
	if (!IsPlayerInHouse(playerid, index) || !IsValidHouse(world))
	{
		if (renovation)
		{
			SetRenovationMode(playerid, false, TYPE_REN_HOUSE, index);
		}
		
		SendClientMessage(playerid, C_WHITE, !#ERROR " ��� ������������� ������ ������� �� ������ ���������� � ����� �������� ���������.");
	
		return 0;
	}
	
	if (GetRenovationType(playerid) != TYPE_REN_HOUSE 
	&& GetRenovationId(playerid) != world)
	{
		return 0;
	}
	
	SetPVarInt(playerid, "House:Select", index);
	SetPVarInt(playerid, "House:IsOwner", 0);
	
	ShowPlayerDialog(playerid, D_HOUSE + 8, DIALOG_STYLE_TABLIST, " ", 
		" ������� ���� ����\t" #cGRAY "/hmenu\n \
		����������� ������\n \
		��������� �������",
		"�����", "�������"
	);
	
	return 1;
}

GarageRenovation(playerid)
{
	new renovation = IsPlayerRenovation(playerid);
		
	if (!renovation)
	{
		SendClientMessage(playerid, C_WHITE, !NOT_RENOVATION_MODE);
		
		return 0;
	}
	
	new world = GetPlayerVirtualWorld(playerid),
		index = GetHouseIndexById(world);
		
	if (!IsPlayerInGarage(playerid, index, world) || !IsValidHouse(world))
	{
		if (renovation)
		{
			SetRenovationMode(playerid, false, TYPE_REN_GARAGE, index);
		}
		
		SendClientMessage(playerid, C_WHITE, !#ERROR " ��� ������������� ������ �������, �� ������ ���������� � ����� ������.");
	
		return 0;
	}
	
	SetPVarInt(playerid, "Garage:Select", index);
	
	ShowPlayerDialog(playerid, D_GARAGE + 4, DIALOG_STYLE_TABLIST, " ", 
		" ������� ���� ������\t" #cGRAY "/gmenu\n \
		����������� ������",
		"�����", "�������"
	);
	
	return 1;
}

CMD:glock(playerid)
{
	GarageLock(playerid);
	return 1;
}

CMD:evict(playerid)
{
	if (!IsPlayerLodger(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " �� �� ��������� ���������.");
		return 1;
	}
	
	Remove:lod_data(GetCharacterId(playerid), playerid);
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� ���������� �� ��������� ���������.");
	return 1;
}
