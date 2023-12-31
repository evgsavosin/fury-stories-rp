/*!
	@brief ������� ��� ������� ���������
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

CMD:inv(playerid)
{	
	ShowInventory(playerid, GetUserSettings(playerid, SET_INVENTORY));
	return 1;
}

CMD:undress(playerid)
{
	if (IsFractionMember(playerid) && GetFractionMemberSkin(playerid))
	{
		SendClientMessage(playerid, C_WHITE, #ERROR " ������, ��� ����� ������, ���������� ���� � ���������.");
		return 1;
	}
	
	if (ResetPlayerSkin(playerid) == character_data[playerid][c_skin])
	{
		return 1;
	}
	
	ShowPlayerDialog(playerid, D_INV + 10, DIALOG_STYLE_MSGBOX, " ", 
		"" #DEFAULT " ����� ������\n\n�� ������������� ������ ����� ������ � ���������?",
		"��", "���"
	);
	
	return 1;
}

CMD:boombox(playerid)
{
	for (new i; i < sizeof drop_data; i++)
	{
		if (drop_data[i][drop_item_id] == 0 
		|| !IsPlayerInDynamicArea(playerid, drop_data[i][drop_area]))
		{
			continue;
		}
		
		ShowMusicMenu(playerid, MUSIC_TYPE_BOOMBOX, i);
		
		return 1;
	}
	
	SendClientMessage(playerid, C_WHITE, !#ERROR " ��� ������������� ������ ������� ���������� ���������� ����� � ���������.");
	return 1;
}

CMD:remsmoke(playerid)
{
	if (!IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ATTACH_SMOKE))
	{	
		SendClientMessage(playerid, C_WHITE, !#ERROR " �� �� ����������� �������� � ������ ������.");
		return 1;
	}
	
	RemovePlayerAttachedObject(playerid, SLOT_ATTACH_SMOKE);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ��������� ������.");
	return 1;
}

CMD:channel(playerid, params[]) 
{
	new index,
		itindex,
		channel,
		radio_type;
	
	if ((index = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_RADIO, _, true)) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " � ��� ����������� �����.");
		return 1;
	}
	
	if ((itindex = GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id))) == INVALID_PARAM)
	{
		return 1;
	}
	
	radio_type = item_list[itindex][it_param_1];
	
	if (sscanf(params, "i", channel))
	{
		SendClientMessage(playerid, C_WHITE, (
			radio_type == INV_FUNC_RADIO_HIGH ? 
			("" #DEFAULT " �������: /channel [����� ������ (0 - 999)]") 
			: ("" #DEFAULT " �������: /channel [����� ������ (0 - 333)]"))
		);
		
		return 1;
	}
	
	if (radio_type == INV_FUNC_RADIO_HIGH 
	&& !(0 <= channel <= 999))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " �� ������� ������������ �����. ����������� ����� ������ �� " #cPROJECT "0 �� 999" #cWHITE ".");
		return 1;
	}
	else if (radio_type == INV_FUNC_RADIO_LOW
	&& !(0 <= channel <= 333))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " �� ������� ������������ �����. ����������� ����� ������ �� " #cPROJECT "0 �� 333" #cWHITE ".");
		return 1;
	}

	switch(channel)
	{
		case 900:
		{
			if (!IsFractionMember(playerid, FRACTION_GOVERNMENT))
			{
				SendClientMessage(playerid, C_WHITE, #ERROR " ������ ����� ����������.");
				return 1;
			}
		}
		
		case 911:
		{
			if (!IsFractionMember(playerid, FRACTION_PD))
			{
				SendClientMessage(playerid, C_WHITE, #ERROR " ������ ����� ����������.");
				return 1;
			}
		}
		
		case 999:
		{
			if (!IsFractionMember(playerid, FRACTION_SD))
			{
				SendClientMessage(playerid, C_WHITE, #ERROR " ������ ����� ����������.");
				return 1;
			}
		}
		
		case 991:
		{
			if (!IsFractionMember(playerid, FRACTION_FD))
			{
				SendClientMessage(playerid, C_WHITE, #ERROR " ������ ����� ����������.");
				return 1;
			}
		}
		
		case 933:
		{
			if (!IsFractionMember(playerid, FRACTION_NP))
			{
				SendClientMessage(playerid, C_WHITE, #ERROR " ������ ����� ����������.");
				return 1;
			}
			
			return 1;
		}	
	}
	
	if (IsFractionMember(playerid))
	{
		if (!CheckFractionAccess(playerid, fr_perm_radio))
		{
			SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
			return 1;
		}
	}
	
	pformat:("" #DEFAULT " �� ������� ����������� ����� ����� �� " #cPROJECT "%i" #cWHITE ".", channel);
	psend:(playerid, C_WHITE);

	SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1, channel);
	Update:item_data(playerid, index, TYPE_INV_PLAYER);
	return 1;
}

CMD:slot(playerid, params[]) 
{	
	new slot,
		index;
	
	if ((index = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_RADIO, _, true)) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " � ��� ����������� �����.");
		return 1;
	}
	
	if (sscanf(params, "i", slot))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " �������: /slot [����� ������ (1 - 99)]");
		
		return 1;
	}
	
	if (!(1 <= slot <= 99))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " �� ������� ������������ �����. ����������� ����� ������ �� " #cPROJECT "1 �� 999" #cWHITE ".");
		return 1;
	}
	
	pformat:("" #DEFAULT " �� ������� ����������� ���� ����� �� " #cPROJECT "%i" #cWHITE ".", slot);
	psend:(playerid, C_WHITE);

	SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_2, slot);
	Update:item_data(playerid, index, TYPE_INV_PLAYER);
	return 1;
}

CMD:r(playerid, params[])
{
	new index;
	
	if ((index = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_RADIO, _, true)) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " � ��� ����������� �����.");
		return 1;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " �������: /r [�����]");
		return 1;
	}
	
	if (GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1) == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " �� �� ��������� �����. " #cGRAY "(/channel, /slot - ���������)");
		return 1;
	}
	
	format:g_small_string("" #RADIO_MESSAGE " %s: %s", 
		GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1),
		1,
		GetPlayerCurrentName(playerid), 
		params
	);
	
	SendRadioMessage(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1), _, g_small_string);
		
	format:g_small_string("%s �������: %s",
		GetPlayerCurrentName(playerid),
		params
	);
	
	ProxDetector(10.0, playerid, g_small_string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, true, true);
	return 1;
}

CMD:rr(playerid, params[])
{
	new index;
	
	if ((index = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_RADIO, _, true)) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " � ��� ����������� �����.");
		return 1;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " �������: /rr [�����]");
		return 1;
	}
	
	if (GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1) == 0 
	|| GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_2) == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " �� �� ��������� �����. " #cGRAY "(/channel, /slot - ���������)");
		return 1;
	}
	
	format:g_small_string("" #RADIO_MESSAGE " %s: %s", 
		GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1),
		GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_2),
		GetPlayerCurrentName(playerid), 
		params
	);
	
	SendRadioMessage(
		GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1), 
		GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_2), 
		g_small_string 
	);
		
	format:g_small_string("%s �������: %s",
		GetPlayerCurrentName(playerid),
		params
	);
	
	ProxDetector(10.0, playerid, g_small_string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, true, true);
	return 1;
}