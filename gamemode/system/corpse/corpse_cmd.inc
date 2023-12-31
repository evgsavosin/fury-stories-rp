/*!
	@brief ������� ��� ������� ������
	@author Found (evg.savosin)
	@date 26.04.2017
*/

CMD:corpse(playerid, params[])
{
	new index;
	
	if (sscanf(params, "i", index))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " �������: /corpse [ID �����]");
		return 1;
	}
	
	index--;
	
	if (!(0 <= (index) <= MAX_CORPSES) || corpse_data[index][corp_type] == TYPE_CORP_NONE)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " �� ������� �������� ID �����.");
		return 1;
	}
	
	if (!IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS,
	corpse_data[index][corp_pos][0], 
	corpse_data[index][corp_pos][1], 
	corpse_data[index][corp_pos][2]) 
	|| GetCharacterInt(playerid) != corpse_data[index][corp_int]
	|| GetPlayerVirtualWorld(playerid) != corpse_data[index][corp_world])
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " �� ������ ���������� ����� � ������.");
		return 1;
	}
	
	new item = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_WEAPON_BIG, WEAPON_SHOVEL, true),
		name		[	MAX_PLAYER_NAME		];
	
	SetPVarInt(playerid, "Corpse:Select", index);
	SetPVarInt(playerid, "Player:ShovelExists", (item != INVALID_PLAYER_ID));
	
	GetWithoutUnderscore(corpse_data[index][corp_character_name], name);
	
	format:g_string(" ��������� ������\n%s",
		item != INVALID_PARAM && corpse_data[index][corp_state] != STATE_CORP_BURY ? (" " #cGRAY "�������� ���� � ������� ������") : ("")
	);
	
	ShowPlayerDialog(playerid, D_CORPSE, DIALOG_STYLE_LIST, name,
		g_string,
		"�������", "�������"
	);
	
	return 1;
}

CMD:canceldigs(playerid)
{
	if (!GetPVarInt(playerid, "Player:CorpseDigs"))
	{
		return 1;
	}
	
	new timer = GetPVarInt(playerid, "Player:CorpseDigsTimer"),
		index = GetPVarInt(playerid, "Player:CorpseDigsIndex");
		
	KillTimer(timer);
	
	corpse_data[index][corp_used] = false;
	
	DeletePVar(playerid, "Player:CorpseDigs");
	DeletePVar(playerid, "Player:CorpseDigsTimer");
	DeletePVar(playerid, "Player:CorpseDigsIndex");
	
	TogglePlayerControllable(playerid, true);
	ClearAnimationsEx(playerid);
	return 1;
}

CMD:cancelgas(playerid)
{	
	if (!GetPVarInt(playerid, "Player:CorpsePourGas"))
	{
		return 1;
	}
	
	new timer = GetPVarInt(playerid, "Player:CorpsePourGasTimer"),
		index = GetPVarInt(playerid, "Player:CorpsePourGasIndex");
		
	KillTimer(timer);
	
	corpse_data[index][corp_used] = false;
	
	RemovePlayerAttachedObject(playerid, SLOT_ATTACH_TEMP);
						
	DeletePVar(playerid, "Player:CorpsePourGas");
	DeletePVar(playerid, "Player:CorpsePourGasTimer");
	DeletePVar(playerid, "Player:CorpsePourGasIndex");
	
	TogglePlayerControllable(playerid, true);
	ClearAnimationsEx(playerid);
	return 1;
}

CMD:cancelchemical(playerid)
{
	if (!GetPVarInt(playerid, "Player:CorpsePourAcid"))
	{
		return 1;
	}
	
	new timer = GetPVarInt(playerid, "Player:CorpsePourAcidTimer"),
		index = GetPVarInt(playerid, "Player:CorpsePourAcidIndex");
		
	KillTimer(timer);
	
	corpse_data[index][corp_used] = false;
	
	DeletePVar(playerid, "Player:CorpsePourAcid");
	DeletePVar(playerid, "Player:CorpsePourAcidTimer");
	DeletePVar(playerid, "Player:CorpsePourAcidIndex");
	
	TogglePlayerControllable(playerid, true);
	ClearAnimationsEx(playerid);
	return 1;
}