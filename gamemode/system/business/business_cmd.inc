/*!
	@brief ������� ��� ������� ��������
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

CMD:bleave(playerid)
{
	if (!IsBusinessMember(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " �� �� ��������� ���������� �����-���� ��������.");
		return 1;
	}
	
	Remove:bmember_data(GetCharacterId(playerid), playerid);
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� �������� ��������.");
	return 1;
}

CMD:bmenu(playerid)
{
	if (bmember_data[playerid][bm_business_index] != INVALID_PARAM)
	{
		SetPVarInt(playerid, "Business:Select", bmember_data[playerid][bm_business_index]);
		ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "�����", "�����");
	}
	else 
	{
		if (GetPlayerBusinessesCount(playerid) == 0)
		{
			SendClientMessage(playerid, C_WHITE, !PLAYER_NO_BUSINESS);
			return 1;
		}
		
		ShowBusinessList(playerid, D_BUSINESS + 6, false);
	}

	return 1;
}