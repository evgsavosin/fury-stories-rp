/*!
	@brief �������������� ������� ��� ������� ���������
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

ShowInventoryAddParam(playerid, param_number = 1, index)
{
	clean:<g_big_string>;
	
	switch (item_list[index][it_type])
	{
		case INV_WEAPON_BIG, INV_WEAPON_SMALL:
		{
			if (param_number == 1)
			{
				strcat(g_big_string, "\
					" #DEFAULT " ���������� ��������\n\n\
					������� ���������� ��������:"
				);
			}
			else if (param_number == 2)
			{
				strcat(g_big_string, "\
					" #DEFAULT " ����������� ������\n\n\
					" #cPROJECT "-1" #cWHITE " - ��������� (������ ��������/��������);\n\
					" #cPROJECT "0" #cWHITE " - �����������;\n\
					" #cPROJECT "1" #cWHITE " - ���������.\n\n\
					������� ��������: "
				);
			}
		}
		
		default:
		{
			format:g_big_string(#DEFAULT " �������� #%d\n\n\
				��������!\n\
				���� ��� �������� �� �������������� �������������.\n\
				�������� �������� ��������� ����� �������� � ������������ ������ ��������.\n\
				������� �������� � ��������� #%d:",
				param_number,
				param_number
			);
		}
	}
	
	new dialogid;
	
	if (param_number == 1)
	{
		dialogid = D_INV + 18;
	}
	else if (param_number == 2)
	{
		dialogid = D_INV + 19;
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
}

ShowInventoryItems(playerid, targetid)
{
	new itindex,
		text	[128];
	
	clean:<g_big_string>;
	format:g_big_string(#DEFAULT " �������� " #cPROJECT "%s" #cWHITE ":\n", 
		GetPlayerCurrentName(playerid)
	);
	
	for (new i; i < MAX_INVENTORY_SLOTS; i++)
	{
		if (!GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_id))
		{
			continue;
		}
		
		clean:<text>;
		
		itindex = GetItemIndexById(
			GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id)
		);
		
		GetInventoryItemValueFormat(
			itindex, 
			GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_param_1), 
			GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_param_2), 
			text,
			false,
			GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_id)
		);
		
		format:g_big_string("%s " #cPROJECT "%s" #cWHITE " - %s\n",
			g_big_string,
			item_list[itindex][it_name],
			text
		);
	}
	
	ShowPlayerDialog(targetid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", g_big_string, "�������", "");
}

ShowInventoryItemInformation(playerid, const slot)
{
	clean:<g_string>;
	
	new item;
	
	if ((item = GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id))) == INVALID_ITEM_ID)
	{
		return 1;
	}
	
	format:g_string("" #DEFAULT " ���������� � �������� - " #cPROJECT "%s" #cWHITE "\n\n��������: " #cPROJECT "%s" #cWHITE "\n",
		item_list[item][it_name],
		item_list[item][it_description]
	);
	
	switch(item_list[item][it_type])
	{
		case INV_WEAPON_SMALL, INV_WEAPON_BIG:
		{
			if (GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_1) != 0)
			{
				format:g_string("%s��������: " #cPROJECT "%i" #cWHITE ".",
					g_string,
					GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_1)
				);
			}
			
			if (GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_2) > 0) // Is Legal
			{
				format:g_string("%s%s�������� �����: " #cPROJECT "�%05d" #cWHITE ".",
					g_string,
					GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_1) != 0 ? ("\n") : (""),
					GetWeaponSerialNumber(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_id))
				);
			}
		}
		
		case INV_AMMO: 
		{
			if (GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_1) != 0)
			{
				format:g_string("%s�������� � ����������: " #cPROJECT "%i" #cWHITE ".",
					g_string,
					GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_1)
				);
				
				strcat(g_big_string, g_small_string);
			}
		}
		
		case INV_BAG: 
		{
			format:g_string("%s����������� �� " #cPROJECT "%i ��������(-��)" #cWHITE ".",
				g_string,
				item_list[item][it_param_1]
			);
		}
		
		case INV_PHONE:
		{
			new pindex = GetPhoneIndexBySlot(playerid, slot, TYPE_INV_PLAYER);
			
			format:g_string("%s����� ��������: " #cPROJECT "%i" #cWHITE ".\n\
			���� ��������: " #cPROJECT "%s" #cWHITE ".",
				g_string,
				phone_data[pindex][ph_number],
				panel_color_list[phone_data[pindex][ph_col_panel]][pc_color_name]
			);
		}
		
		case INV_SMOKE:
		{
			format:g_string("%s������� � ����� " #cPROJECT "%i" #cWHITE ".",
				g_string,
				GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_1)
			);
		}
		
		case INV_LIGHTER:
		{
			new value = GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_1);
			format:g_string("%s������� � �������: " #cPROJECT "%s" #cWHITE ".",
				g_string,
				(value >= 30 ? (#cGREEN " ������") : (
				value >= 15 ? (#cGRAY " �� ��������") : (
				value <= 0 ? (#cRED " ���������") : (""))))
			);
		}
		
		case INV_SKIN:
		{
			format:g_string("%s����� ������ " #cPROJECT "#%i" #cWHITE ".",
				g_string,
				GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_1)
			);
		}
		
		case INV_RADIO:
		{
			format:g_string("%s�����: " #cPROJECT "%i" #cWHITE ".\n����: " #cPROJECT "%i" #cWHITE ".",
				g_string,
				GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_1),
				GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_2)
			);
		}
		
		case INV_ATTACH:
		{
			if (item_list[item][it_param_1] == INV_FUNC_ARMOUR_LIGHT
			|| item_list[item][it_param_1] == INV_FUNC_ARMOUR_HEAVY)
			{
				new value = GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_2);
				format:g_string("%s���������: %s" #cWHITE ".",
					g_string,
					(value >= 80 ? ("" #cGREEN "� ������� ���������") : (
					value >= 40 ? ("" #cGRAY "�������") : (
					value < 40 ? ("" #cRED "�������") : (""))))
				);
			}
		}
		
		case INV_DRUGS:
		{
			if (GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_1) != 0)
			{
				format:g_string("%s���������� �����: " #cPROJECT "%i" #cWHITE ".",
					g_string,
					GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_1)
				);
			}
		}
	}
	
	SetPVarInt(playerid, "Inventory:TempSelect", slot);
	
	return ShowPlayerDialog(
		playerid, 
		D_INV + 2, 
		DIALOG_STYLE_MSGBOX, 
		" ", 
		g_string, 
		"�����", "" 
	);
}

UpdateInventory(playerid, index)
{
	if (IsInventoryTypeShow(playerid, TEXTDRAW_INVENTORY))
	{
		if (IsInventoryTextDrawShowed(playerid))
		{
			UpdateInventorySlotModel(playerid, index);
			UpdateInventorySelect(playerid, inventory_td_select[playerid], false, index);
		}
	}
	else
	{
		ShowInventoryDialog(playerid);
	}
}

ShowInventoryWeaponUse(playerid, index, itindex)
{
	new bool: is_weapon_cold = bool: IsWeaponCold(playerid, index);
				
	SetPVarInt(playerid, "Inventory:IsColdWeapon", _: is_weapon_cold);
			
	format:g_string(" ����� � ����\n%s%s%s",
		!is_weapon_cold ? (" ��������\n") : (""),
		!is_weapon_cold ? (" ���������\n") : (""),
		!GetItemStaticAttach(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id)) ? (" ���������� � ���������") : ("")
	);

	ShowPlayerDialog(playerid, D_INV + 6, DIALOG_STYLE_LIST, item_list[itindex][it_name],
		g_string,
		"�����", "�������"
	);	
}

ShowInventoryWeaponUnUse(playerid, index, itindex)
{
	ShowPlayerDialog(playerid, D_INV + 8, DIALOG_STYLE_LIST, item_list[itindex][it_name], 
		IsWeaponCold(playerid, index) ? (" ������ ������") : (" ������ ������\n ���������"),
		 "�������", "�������" 
	);
}

ShowInventoryDrugUse(playerid, itindex, values) // values == ���������� ��������� � �����
{
	format:g_small_string(" ����������%s%s",
		(values <= 1) ? (" ") : ("\n �����������"),
		(GetUserSettings(playerid, SET_INVENTORY) == 0) ? (" ") : ("\n ����������")
	);

	ShowPlayerDialog(playerid, D_INV_DRUG_USE, DIALOG_STYLE_LIST, item_list[itindex][it_name],
		g_small_string,
		"�������", "�������"
	);
}

ShowInventoryDrugSplit(playerid, index)
{
	format:g_string("" #DEFAULT " �����������\n\n\
		���������� � �������: " #cPROJECT "%i �����.\n\
		������� ���������� �����, ������� �� ������ �����������:",
		GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1)
	);

	ShowPlayerDialog(playerid, D_INV_DRUG_SPLIT, DIALOG_STYLE_INPUT, 
		item_list[GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id))][it_name],
		g_string,
		"�����", "�����"
	);
}

// �������� ������ ���� ���������
ShowInventoryItemList(playerid, action = ITEM_LIST_BEGIN, func_name[32] = "")
{
	clean:<g_big_string>;
	
	new page,
		count;
	
	if (action == ITEM_LIST_BEGIN)
	{
		if (!isnull(func_name))
		{
			clean:<g_small_string>;
			format:g_small_string("Inv_%s", func_name);
			SetPVarString(playerid, "Inventory:TempItemCallback", g_small_string);
		}
		
		SetPVarInt(playerid, "Inventory:Page", 0);
		page = 0;
	}
	else if (action == ITEM_LIST_CURRENT)
	{
		page = GetPVarInt(playerid, "Inventory:Page");
	}
	else if (action == ITEM_LIST_NEXT)
	{
		GivePVarInt(playerid, "Inventory:Page", 1);
		page = GetPVarInt(playerid, "Inventory:Page");
	}
	else if (action == ITEM_LIST_BACK)
	{
		TakePVarInt(playerid, "Inventory:Page", 1);
		page = GetPVarInt(playerid, "Inventory:Page");
	}
	
	for (new i = (page * MAX_ITEM_LIST) + 1; i < sizeof item_list; i++)
	{
		format:g_big_string("%s %s\n", 
			g_big_string, 
			GetInventoryItemName(i)
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

	ShowPlayerDialog(playerid, D_INV + 17, DIALOG_STYLE_TABLIST, " ", g_big_string, "�������", "�����");
}