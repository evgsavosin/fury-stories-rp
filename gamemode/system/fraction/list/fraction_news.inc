/*!
	@brief ������� ��� ��������
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

News_OnGameModeInit()
{
	Clear:fraction_news_ether_data();
}

News_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		case D_NEWS_ETHER:
		{
			if (!response)
			{
				cmd_fmenu(playerid);
				return 1;
			}
			
			//new index = GetFractionMember(playerid);
			
			if (listitem == 0) // ������/��������� ����
			{
				new vehicleid = GetPlayerVehicleID(playerid);
				
				if (fraction_news_ether_data[fr_player_id] == INVALID_PLAYER_ID)
				{
					if (!IsPlayerInRangeOfPoint(playerid, 100.0, NEWS_STUDIO_POS) || vehicleid != 0 && vehicle_data[vehicleid][v_model] != 488 && vehicle_data[vehicleid][v_model] != 582)
					{
						SendClientMessage(playerid, C_WHITE, !#ERROR " �� ������ ��������� � ������ ��� � ������������������ ����������.");
						return 1;
					}
					
					SetPVarInt(playerid, "News:Ether", true);
					
					fraction_news_ether_data[fr_player_id] = playerid;
					
					/*format:g_small_string(#FRACTION_MESSAGE " %s �����%s ������� � ������ �����.",
						GetPlayerCurrentName(playerid),
						EndWordSex(playerid)
					);
					
					SendFractionMessage(index, g_small_string);*/
					
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " �� ������ ������� � ������ �����. " #cGRAY "(/e - ��� �������� ��������� � ������ �����)");
					return 1;
				}
				else if (fraction_news_ether_data[fr_player_id] == playerid)
				{
					fraction_news_ether_data[fr_player_id] = INVALID_PLAYER_ID;
					
					/*format:g_small_string(#FRACTION_MESSAGE " %s ��������%s ������� � ������ �����.",
						GetPlayerCurrentName(playerid),
						EndWordSex(playerid)
					);
					
					SendFractionMessage(index, g_small_string);*/
					
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " �� ��������� ������� � ������ �����.");
					
					foreach (new i : Player)
					{
						DeletePVar(i, "News:Ether");
					}
					
					return 1;
				}
				
				ShowFractionNewsEtherMenu(playerid);
			}
			else if (listitem == 1) // ���������� � ����
			{
				if (fraction_news_ether_data[fr_player_id] == INVALID_PLAYER_ID)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " ������ ���� �� ��� �����.");
					return 1;
				}
				
				ShowFractionNewsEtherInvite(playerid);
			}
			else if (listitem == 2) // ����������� �� �����
			{
				if (fraction_news_ether_data[fr_player_id] == INVALID_PLAYER_ID)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " ������ ���� �� ��� �����.");
					return 1;
				}
				
				ShowFractionNewsEtherUninvite(playerid);
			}
		}
		
		case D_NEWS_ETHER_INVITE:
		{
			if (!response)
			{
				ShowFractionNewsEtherMenu(playerid);
				return 1;
			}
			
			new targetid = strval(inputtext);
			
			if (isnull(inputtext) || !IsPlayerLogged(targetid) || playerid == targetid || !IsPlayerAroundOfPlayer(playerid, targetid))
			{
				ShowFractionNewsEtherInvite(playerid, "����� ������������ �����.");
				return 1;
			}
			
			SetPVarInt(targetid, "News:SenderId", playerid);
			
			format:g_string(#DEFAULT " ����������� � ������ ����\n\n\
				" #cPROJECT "%s" #cWHITE " ���������� ��� � ������ ����.\n\
				�� ���������� �����������?",
				GetPlayerCurrentName(playerid)
			);
			
			ShowPlayerDialog(targetid, D_NEWS_ETHER_INVITE_ACCEPT, DIALOG_STYLE_MSGBOX, " ", g_string, "��", "���");
		}
		
		case D_NEWS_ETHER_INVITE_ACCEPT:
		{
			new sender_id = GetPVarInt(playerid, "News:SenderId");
			
			if (response)
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " ������ ���� �����������.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(sender_id, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� �����������. " #cGRAY "(/e - ��� �������� ��������� � ������ �����)");
			}
			else 
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " �������� ���� �����������.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(sender_id, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " �� ��������� �����������.");
			}
			
			SetPVarInt(playerid, "News:Ether", response);
			DeletePVar(playerid, "News:SenderId");
		}
		
		case D_NEWS_ETHER_UNINVITE:
		{
			if (!response)
			{
				ShowFractionNewsEtherMenu(playerid);
				return 1;
			}
			
			new targetid = strval(inputtext);
			
			if (isnull(inputtext) || !IsPlayerLogged(targetid) || playerid == targetid)
			{
				ShowFractionNewsEtherUninvite(playerid, "����� ������������ �����.");
				return 1;
			}
			
			pformat:(#SUCCESS " �� ������� ������� � ����� " #cPROJECT "%s" #cWHITE ".", targetid);
			psend:(playerid, C_WHITE);
			
			pformat:(#SUCCESS " " #cPROJECT "%s" #cWHITE " ������ ��� � �����.", playerid);
			psend:(playerid, C_WHITE);
			
			DeletePVar(playerid, "News:Ether");
		}
	}
	
	return 1;
}

ShowFractionNewsEtherInvite(playerid, error[] = "")
{
	format:g_string(#DEFAULT " ���������� � ����\n\n\
		������� ID ������, �������� ������ ���������� � ������ ����:\n\n\
		" #cGRAY "����� ������ ��������� ����� � ����.%s%s",
		isnull(error) ? ("") : (cRED),
		error
	);
	
	ShowPlayerDialog(playerid, D_NEWS_ETHER_INVITE, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

ShowFractionNewsEtherUninvite(playerid, error[] = "")
{
	format:g_string(#DEFAULT " ������� � �����\n\n\
		������� ID ������, �������� ������ ������� � �����:\n\n\
		" #cGRAY "����� ������ ��������� ����� � ����.%s%s",
		isnull(error) ? ("") : (cRED),
		error
	);
	
	ShowPlayerDialog(playerid, D_NEWS_ETHER_UNINVITE, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

ShowFractionNewsEtherMenu(playerid)
{
	clean:<g_small_string>;

	new ether_player_id = fraction_news_ether_data[fr_player_id];
	
	if (ether_player_id == INVALID_PLAYER_ID)
	{
		strcat(g_small_string, "������ ����"); 
	}
	else if (ether_player_id == playerid)
	{
		strcat(g_small_string, "��������� ����");
	}
	else 
	{
		format:g_small_string("���� ���� " #cPROJECT "%s",
			GetPlayerCurrentName(ether_player_id)
		);
	}
	
	format:g_string(" %s\n \
		���������� � ����\n \
		������� � �����",
		g_small_string
	);
	
	ShowPlayerDialog(playerid, D_NEWS_ETHER, DIALOG_STYLE_LIST, " ", g_string, "�����", "�����");
}

CMD:e(playerid, params[])
{
	if (!IsFractionMember(playerid, FRACTION_NEWS))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (fraction_news_ether_data[fr_player_id] == INVALID_PLAYER_ID)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " ������ ���� �� ��� �����.");
		return 1;
	}
	
	if (!GetPVarInt(playerid, "News:Ether"))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " �� �� ���������� � ������ �����.");
		return 1;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " �������: /e [�����]");
		return 1;
	}
	
	new findex = GetFractionMember(playerid);
	
	new vehicleid,
		index;
	
	foreach (new i : Player)
	{
		if (!IsPlayerLogged(i))
		{
			continue;
		}

		if ((vehicleid = GetPlayerVehicleID(i)) != 0 && !vehicle_data[vehicleid][v_radio])
		{
			continue;
		}
		
		if ((index = GetInventoryDefaultPhone(i)) == INVALID_PARAM || !phone_data[index][ph_radio])
		{
			continue;
		}
		
		format:g_small_string("���� %s > %s: %s",
			fraction_data[findex][fr_alt_name],
			GetPlayerCurrentName(playerid),
			params
		);
		
		SendSplitMessage(playerid, 0x5D83F5FF, g_small_string);
	}
	
	return 1;
}