/*!
	@brief ������� ��� ������������ ������
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

CMD:jail(playerid, params[]) 
{
	if (!IsFractionMember(playerid, FRACTION_SD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
		
	new targetid,
		time;
		
	if (sscanf(params, "ud", targetid, time))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " �������: /jail [ID ������] [���������� �����]");
		return 1;
	}
	
	if (GetCharacterWorld(playerid) != WORLD_PRISON)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " ��� ������������� ������ �������, ��� ���������� ���������� ������ ������.");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (IsCharacterJailed(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " ������ ����� ��� ��������� � ��������� ������.");
		return 1;
	}
		
	if (!(0 < time < 1000))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " ���� � ��������� ������ ����� ���� �� 1 ������ �� 60 �����.");
		return 1;
	}
	
	new follow_id = GetPVarInt(targetid, "Player:Follow");
	
	if (follow_id != INVALID_PLAYER_ID) 
	{
		SetPVarInt(follow_id, "Player:Lead", INVALID_PLAYER_ID);
		SetPVarInt(targetid, "Player:Follow", INVALID_PLAYER_ID);
	}
	
	if (GetPVarInt(targetid, "Player:Cuff")) 
	{
		DeletePVar(targetid, "Player:Cuff");
		RemovePlayerAttachedObject(playerid, SLOT_ATTACH_TEMP);
		SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
		TogglePlayerControllable(targetid, true);	
	}	
	
	ImprisonPlayerToJail(targetid, time);
	
	pformat:(#DEFAULT " �� ���� �������� � ��������� ������ " #cPROJECT "%s" #cWHITE " �� " #cPROJECT "%d" #cWHITE " ���.", GetPlayerCurrentName(playerid), time);
	psend:(targetid, C_WHITE );
		
	pformat:(#SUCCESS " �� ������� ��������� � ��������� ������ " #cPROJECT "%s" #cWHITE " �� " #cPROJECT "%d" #cWHITE " ���.",GetPlayerCurrentName(targetid), time);
	psend:(playerid, C_WHITE);
	return 1;
}

CMD:setjail( playerid, params[] )
{
	if (!IsFractionMember(playerid, FRACTION_SD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
		
	new targetid,
		time;
		
	if (sscanf(params, "ud", targetid, time))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " �������: /setjail [ID ������] [���������� �����]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
		
	if (!(0 < time < 1000))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " ���� � ��������� ������ ����� ���� �� 1 ������ �� 60 �����.");
		return 1;
	}
	
	character_data[targetid][c_arrest_time] = time != 0 ? (gettime() + (time * 60)) : 0;
	format:g_small_string("FROM_UNIXTIME(%d)", character_data[targetid][c_arrest_time]);
	Update:character_string(targetid, "c_arrest_date", g_small_string, false);
	
	pformat:(#DEFAULT " ��� ���� ���������� ��� ������� " #cPROJECT "%s" #cWHITE " �� " #cPROJECT "%d" #cWHITE " ���.", GetPlayerCurrentName(playerid), time);
	psend:(targetid, C_WHITE );
		
	pformat:(#SUCCESS " �� ������� �������� ���� ���������� � ������ " #cPROJECT "%s" #cWHITE " �� " #cPROJECT "%d" #cWHITE " ���.",GetPlayerCurrentName(targetid), time);
	psend:(playerid, C_WHITE);
	return 1;
}

CMD:unjail( playerid, params[] )
{
	if (!IsFractionMember(playerid, FRACTION_SD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
		
	new targetid;
		
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " �������: /unjail [ID ������]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (!IsCharacterJailed(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " ������ ����� �� ��������� � ��������� ������.");
		return 1;
	}
	
	ResetPlayerArrest(targetid);
	
	pformat:(#SUCCESS " �� ��������� " #cPROJECT "%s" #cWHITE " �� ��������� ������.", GetPlayerCurrentName(targetid));
	psend:(playerid, C_WHITE);
	
	pformat:(#DEFAULT " " #cPROJECT "%s" #cWHITE " �������� ��� �� ��������� ������.", GetPlayerCurrentName(playerid));
	psend:(targetid, C_WHITE );
	return 1;
}