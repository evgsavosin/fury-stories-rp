/*!
	@brief ������� 911
	@author Found (evg.savosin)
	@date 05.01.2020
*/

GetFreeIndexForFractionCall()
{
	for (new i; i < MAX_FRACTION_CALLS; i++)
	{
		if (!fraction_call[i][c_exists])
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

SendFractionCallNotice(playerid, index)
{
	foreach (new i: Player)
	{
		if (!IsPlayerLogged(i))
		{
			continue;
		}
		
		if (!IsFractionMember(i, FRACTION_PD)
		&& !IsFractionMember(i, FRACTION_SD)
		&& !IsFractionMember(i, FRACTION_FD))
		{
			continue;
		}
		
		if (!CheckFractionDuty(i))
		{
			continue;
		}
		
		SendClientMessage(i, C_PROJECT, "===============911===============" );
		
		pformat:( "�������� ����� #%d: %010s", index + 1, fraction_call[index][c_text]);
		psend:(i, C_PROJECT);
		
		pformat:( "������ �������� ��: %s, ���. %d", 
			GetPlayerCurrentName(playerid), 
			fraction_call[index][c_phone]
		);
		
		psend:(i, C_PROJECT);
		
		pformat:( "�����: %s", fraction_call[index][c_zone]);
		psend:(i, C_PROJECT);
		
		SendClientMessage(i, C_PROJECT, "=================================" );
		
		PlayerPlaySound(i, 41603, 0, 0, 0);
	}

	return 1;
}

ShowFractionCalls(playerid, dialogid)
{
	new count;
	
	clean:<g_big_string>;
	strcat(g_big_string, #cPROJECT "����� ��������\t" #cPROJECT "��������\n");
	
	for (new i; i < MAX_FRACTION_CALLS; i++)
	{
		if (!fraction_call[i][c_exists])
		{
			continue;
		}
		
		format:g_big_string("%s %d\t%s\n", 
			g_big_string,
			fraction_call[i][c_phone],
			fraction_call[i][c_text]
		);
		
		g_dialog_select[playerid][count++] = i;
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "�������", "�������");
	return 1;
}

ShowFractionCallInformation(playerid, dialogid, index)
{
	format:g_big_string("\
		" #DEFAULT " ���������� �� ���������� ������ #%d\n\n\
		�������� ��������: " #cPROJECT "%s " #cWHITE "\n\
		�����: " #cPROJECT "%s" #cWHITE "\n\
		�������: " #cPROJECT "%d" #cWHITE "\n\
		���: " #cPROJECT "%s",
		index + 1,
		fraction_call[index][c_text],
		fraction_call[index][c_zone],
		fraction_call[index][c_phone],
		fraction_call[index][c_name]
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, " ", g_big_string, "��������", "�����");
}