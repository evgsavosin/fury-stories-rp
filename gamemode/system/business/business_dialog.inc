/*!
	@brief ������� ��� ������� ��������
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

Bus_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case D_BUSINESS :
		{
			if (!response)
			{
				return 1;
			}
			
			if (listitem == 0)
			{
				if (bmember_data[playerid][bm_business_index] != INVALID_PARAM)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " �� ��� ��������� ���������� ��������. ��� ����, ����� �������� ��������, ����������� " #cPROJECT "/bleave" #cWHITE ".");
					return 1;
				}
				
				if (!GetPlayerAvaibleBusiness(playerid))
				{
					SendClientMessage(playerid, C_WHITE, #ERROR " �� �� ������ ������� ������ ��������.");
					return 1;
				}
				
				if (GetPlayerPremisesCount(playerid) == 0)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " � ��� ����������� ���������.");
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_BUSINESS + 1, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " ���������������� ��������\n\n\
					������� �������� ������� ��������:\n\n\
					" #cGRAY "�������� ������ ���� �������� �� ��������� ������ � ������.\n\
					����� �������� �� ������ ���� ������ 3 �������� � ������, ��� 32 �������",
					"�����", "�����" 
				);
				
				return 1;
			}
			
			listitem--;
			
			SetPVarInt(playerid, "Business:Select", g_dialog_select[playerid][listitem]);
			
			ShowPlayerDialog(playerid, D_BUSINESS + 3, DIALOG_STYLE_LIST, " ", 
				DIALOG_BUSINESS_MENU,
				"�����", "�����"
			);
		}
		
		case D_BUSINESS + 1 :
		{
			if (!response)
			{
				ShowBusinessList(playerid);
				return 1;
			}
			
			if (!IsValidBusinessNameString(inputtext))
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 1, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " ���������������� ��������\n\n\
					������� �������� ������� ��������:\n\n\
					" #cRED "�������� ������ ���� �������� �� ��������� ������ � ������.\n\
					����� �������� �� ������ ���� ������ 3 �������� � ������, ��� 32 �������",
					"�����", "�����" 
				);
				
				return 1;
			}
			
			SetPVarString(playerid, "Business:CreateName", inputtext);
			ShowPlayerDialog(playerid, D_BUSINESS + 2, DIALOG_STYLE_TABLIST_HEADERS, 
				" ", 
				DIALOG_BUSINESS_TYPE, 
				"�������", "�����" 
			);
		}
		
		case D_BUSINESS + 2 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 1, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " ���������������� ��������\n\n\
					������� �������� ������� ��������:\n\n\
					" #cGRAY "�������� ������ ���� �������� �� ��������� ������ � ������.\n\
					����� �������� �� ������ ���� ������ 3 �������� � ������, ��� 32 �������",
					"�����", "�����" 
				);
				
				return 1;
			}
			
			if (!CheckSummForPay(playerid, CREATE_BUSINESS_COST))
			{
				SendClientMessage(playerid, C_WHITE, !ERROR_PAY);
				DeletePVar(playerid, "Business:CreateName");
				return 1;
			}
			
			if (!GetPlayerPremisesCount(playerid))
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " ��� ����, ����� ������� ��������, ���������� ����� � ������� ���������.");
				DeletePVar(playerid, "Business:CreateName");
				return 1;
			}
			
			new index = GetFreeIndexForBusiness();
			
			if (index == INVALID_PARAM)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " �������� ����� ��������, �� �� ������ ������� ��������.");
				DeletePVar(playerid, "Business:CreateName");
				return 1;
			}
			
			GivePlayerCash(playerid, -CREATE_BUSINESS_COST);
			
			clean:<g_small_string>;
			GetPVarString(playerid, "Business:CreateName", g_small_string, sizeof g_small_string);
			Create:business_data(playerid, index, listitem, g_small_string);
			
			DeletePVar(playerid, "Business:CreateName");
		}
		
		case D_BUSINESS + 3 :
		{
			if (!response)
			{
				ShowBusinessList(playerid);
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Business:Select");
			
			if (listitem == 0) // ����������
			{
				ShowBusinessInformation(playerid, index, D_BUSINESS + 4);
			}
			else // ������� ��������
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 5, DIALOG_STYLE_MSGBOX, " ", 
					"" #DEFAULT " ������� ��������\n\n\
					�� ������������� ������� ������� ��������?",
					"�����", "�����"
				);
			}
		}
		
		case D_BUSINESS + 4 :
		{
			ShowPlayerDialog(playerid, D_BUSINESS + 3, DIALOG_STYLE_LIST, " ", 
				DIALOG_BUSINESS_MENU,
				"�����", "�����"
			);
		}
		
		case D_BUSINESS + 5 :
		{
			if (response)
			{
				Remove:business_data(playerid, GetPVarInt(playerid, "Business:Select"));
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� ������� ��������.");
				
				ShowBusinessList(playerid);
			}
			else 
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 3, DIALOG_STYLE_LIST, " ", 
					DIALOG_BUSINESS_MENU,
					"�����", "�����"
				);
			}
		}
		
		case D_BUSINESS + 6 :
		{
			if (!response)
			{	
				DeletePVar(playerid, "Business:Select");
				return 1;
			}
			
			SetPVarInt(playerid, "Business:Select", g_dialog_select[playerid][listitem]);
			ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "�����", "�����");
		}
		
		case D_BUSINESS + 7 :
		{
			if (!response)
			{
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Business:Select");
			
			if (listitem == 0) /// ����������
			{
				ShowBusinessInformation(playerid, index, D_BUSINESS + 8);
			}
			else if (listitem == 1) /// ���������
			{	
				if (!CheckBusinessAccess(TYPE_BUSINESS_OWNER, playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					cmd_bmenu(playerid);
					return 1;
				}
				
				ShowPremiseList(playerid, D_BUSINESS + 9, _, "�����", 3);
			}
			else if (listitem == 2) /// ��������
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
					DIALOG_BUSINESS_STAFF,
					"�������", "�����" 
				);
			}
			else if (listitem == 3) /// ���������
			{
				if (!CheckBusinessAccess(TYPE_BUSINESS_OWNER, playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					cmd_bmenu(playerid);
					return 1;
				}
				
				if (business_data[index][b_type] == (sizeof business_type - 1))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " ������ ��� �������� �� ������������� ������������� ������� �������.");
					return 1;
				}
				
				ShowBusinessSettings(playerid, index);
			}
			else if (listitem == 4) /// �������
			{
				if (!CheckBusinessAccess(TYPE_BUSINESS_OWNER, playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					cmd_bmenu(playerid);
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_BUSINESS + 18, DIALOG_STYLE_LIST, " ", 
					" ��������� �������� �������� �� �����\n \
					�������� �������� �� ���� ��������",
					"�����", "�����"
				);
			}
		}
		
		case D_BUSINESS + 8 :
		{
			ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "�����", "�����");
		}
		
		case D_BUSINESS + 9 :
		{
			if (!response)
			{
				DeletePVar(playerid, "Time:PremiseUntie");
				ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "�����", "�����");
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Business:Select"),
				prindex = g_dialog_select[playerid][listitem],
				server_tick = GetTickCount();
			
			if (GetPVarInt(playerid, "Time:PremiseUntie") > server_tick)
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
				ShowPremiseList(playerid, D_BUSINESS + 9, _, "�����", 3);
				return 1;
			}
			
			if (!IsPremiseTied(prindex))
			{
				PremiseTie(prindex, index);
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� ��������� ��������� � ��������.");
			}
			else 
			{
				PremiseUntie(prindex, index);
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� �������� ��������� �� ��������.");
			}
			
			ShowPremiseList(playerid, D_BUSINESS + 9, _, "�����", 3);
			SetPVarInt(playerid, "Time:PremiseUntie", server_tick + 5000);
		}
		
		case D_BUSINESS + 10 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "�����", "�����");
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Business:Select");
			
			if (listitem == 0) /// �������
			{
				if (!CheckBusinessAccess(TYPE_BUSINESS_MEMBER, playerid, index, bm_perm_invite))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
						DIALOG_BUSINESS_STAFF,
						"�������", "�����" 
					);
					
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_BUSINESS + 11, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " ������� � ��������\n\n\
					������� ID ������, �������� �� ������ ������� � ��������:\n\n\
					" #cGRAY "����� ������ ��������� ���������� �� ���.",
					"�����", "�����"
				);
			}
			else if (listitem == 1) /// ���������
			{
				if (!CheckBusinessAccess(TYPE_BUSINESS_MEMBER, playerid, index, bm_perm_uninvite))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
						DIALOG_BUSINESS_STAFF,
						"�������", "�����" 
					);
					
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_BUSINESS + 13, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " ��������� �� ��������\n\n\
					������� ID ������, �������� �� ������ ��������� �� ��������:",
					"�����", "�����"
				);
			}
			else if (listitem == 2) // �������� ����������
			{
				if (!CheckBusinessAccess(TYPE_BUSINESS_MEMBER, playerid, index, bm_perm_change))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
						DIALOG_BUSINESS_STAFF,
						"�������", "�����" 
					);
					
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_BUSINESS + 14, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " �������� ����������\n\n\
					������� ID ������, � �������� �� ������ �������� ����������:",
					"�����", "�����"
				);
			}
			else if (listitem == 3) // ������ ���� �����������
			{
				ShowBusinessMembers(playerid, GetPVarInt(playerid, "Business:Select"));	
			}
		}
		
		case D_BUSINESS + 11 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
					DIALOG_BUSINESS_STAFF,
					"�������", "�����" 
				);
				
				return 1;
			}
			
			new targetid = strval(inputtext),
				index = GetPVarInt(playerid, "Business:Select");
				
			if (isnull(inputtext) || !IsInt(inputtext) 
			|| !IsPlayerLogged(targetid)
			|| playerid == targetid 
			|| !IsPlayerAroundOfPlayer(playerid, targetid))
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 11, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " ������� � ��������\n\n\
					������� ID ������, �������� �� ������ ������� � ��������:\n\n\
					" #cGRAY "����� ������ ��������� ���������� �� ���.\n\
					" #cRED "�� ����� �������� ID ������.",
					"�����", "�����"
				);
				
				return 1;
			}
			
			if (IsBusinessMember(targetid))
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 11, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " ������� � ��������\n\n\
					������� ID ������, �������� �� ������ ������� � ��������:\n\n\
					" #cGRAY "����� ������ ��������� ���������� �� ���.\n\
					" #cRED "������ ����� ��� ������� � ��������.",
					"�����", "�����"
				);
				
				return 1;
			}
			
			if (!IsUserAllowQuery(playerid))
			{
				return 1;
			}
			
			format:g_string("SELECT COUNT(bm_character_id) as members_count FROM " #__BMEMBERS " WHERE bm_business_id = %i",
				GetBusinessId(index)
			);
			
			mysql_tquery(db, g_string, "OnBusinessCheckMembers", "iii", playerid, targetid, index);
		
			SetUserAllowQuery(playerid, false);
		}
		
		case D_BUSINESS + 12 :
		{
			new index = GetPVarInt(playerid, "Business:OwnerSelect"),
				ownerid = GetPVarInt(playerid, "Business:OwnerId");
				
			if (response)
			{
				if (!IsPlayerLogged(ownerid))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " �����, ��������� �����������, ����� � �������.");
					return 1;
				}
				
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " ������ ���� �����������.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
				
				SendClientMessage(ownerid, C_WHITE, !#DEFAULT " ��� ��������� ������� ��������� � " #cGRAY "��������" #cWHITE ".");
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " �� ������� �����������.");
				
				Create:bmember_data(playerid, index);
				
				format:g_small_string("// \"%s\" > %s ������� � �������� �� ����������� �� %s.",
					GetBusinessName(index),
					GetPlayerCurrentName(playerid),
					GetPlayerCurrentName(ownerid)
				);
				
				SendBusinessMessage(index, C_PROJECT, g_small_string);
			}
			else 
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " �������� ���� �����������.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " �� ��������� �����������.");
			}
			
			DeletePVar(playerid, "Business:OwnerSelect");
			DeletePVar(playerid, "Business:OwnerId");
		}
		
		case D_BUSINESS + 13 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
					DIALOG_BUSINESS_STAFF,
					"�������", "�����" 
				);
				
				return 1;
			}
			
			new targetid,
				index = GetPVarInt(playerid, "Business:Select");
				
			if (isnull(inputtext) || !IsInt(inputtext) 
			|| !IsPlayerLogged(targetid = strval(inputtext)) 
			|| playerid == targetid)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 13, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " ��������� �� ��������\n\n\
					������� ID ������, �������� �� ������ ��������� �� ��������:\n\
					" #cRED "�� ����� �������� ID ������.",
					"�����", "�����"
				);
				
				return 1;
			}
			
			if (index != GetBusinessMember(targetid))
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 13, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " ��������� �� ��������\n\n\
					������� ID ������, �������� �� ������ ��������� �� ��������:\n\n\
					" #cRED "������ ����� �� ������� � ����� ��������.",
					"�����", "�����"
				);
				
				return 1;
			}
			
			Remove:bmember_data(GetCharacterId(targetid), targetid);
			
			pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " ������ ��� �� �������� " #cPROJECT "%s" #cWHITE ".",
				GetPlayerCurrentName(playerid),
				GetBusinessName(index)
			);
			
			psend:(targetid, C_WHITE);
			
			format:g_small_string("// \"%s\" > %s ������ �� �������� %s.",
				GetBusinessName(index),
				GetPlayerCurrentName(playerid),
				GetPlayerCurrentName(targetid)
			);
			
			SendBusinessMessage(index, C_PROJECT, g_small_string);
			
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " �� ������� ��������� ������ �� ��������.");
		}
		
		case D_BUSINESS + 14 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
					DIALOG_BUSINESS_STAFF,
					"�������", "�����" 
				);
				
				return 1;
			}
			
			new targetid,
				index = GetPVarInt(playerid, "Business:Select");
				
			if (isnull(inputtext) || !IsInt(inputtext) 
			|| !IsPlayerLogged(targetid = strval(inputtext))
			|| playerid == targetid 
			|| GetBusinessMember(targetid) != index)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 14, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " �������� ����������\n\n\
					������� ID ������, � �������� �� ������ �������� ����������:\n\n\
					" #cRED "�� ����� �������� ID ������.",
					"�����", "�����"
				);
				
				return 1;
			}
			
			SetPVarInt(playerid, "Business:TargetId", targetid);
			ShowBusinessMemberChange(playerid, targetid);
		}
		
		case D_BUSINESS + 15 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
					DIALOG_BUSINESS_STAFF,
					"�������", "�����" 
				);
				
				DeletePVar(playerid, "Business:TargetId"); 
				return 1;
			}
			
			new targetid = GetPVarInt(playerid, "Business:TargetId");
			
			bmember_data[targetid][bm_perm][listitem] = !bmember_data[targetid][bm_perm][listitem];
			
			Update:bmember_data(targetid);
			
			ShowBusinessMemberChange(playerid, targetid);
		}
		
		case D_BUSINESS + 16 :
		{
			new index = GetPVarInt(playerid, "Business:Select");
			
			if (!response || GetPVarInt(playerid, "Business:CountMemberList") == 0)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
					DIALOG_BUSINESS_STAFF,
					"�������", "�����" 
				);
				
				DeletePVar(playerid, "Business:MemberListPage");
				DeletePVar(playerid, "Business:CountMemberList");
				return 1;
			}
			
			if (bmember_select[playerid][listitem][bs_character_id] == GetCharacterId(playerid))
			{
				ShowBusinessMembers(playerid, index);
				pformat:("" #ERROR " �� �� ������ ������� ������ ���������.");
				psend:(playerid, C_WHITE);
				return 1;
			}
			
			SetPVarInt(playerid, "Business:MemberSelect", listitem);
			ShowBusinessMemberSelected(playerid, listitem);
		}
		
		case D_BUSINESS + 17 :
		{
			new index = GetPVarInt(playerid, "Business:Select");
				
			if (!response)
			{
				ShowBusinessMembers(playerid, index);
				return 1;
			}
			
			new mindex = GetPVarInt(playerid, "Business:MemberSelect"),
				account_id = bmember_select[playerid][mindex][bs_character_id],
				targetid = GetPlayerIdByCharacterId(account_id);
		
			if (listitem == 0)
			{
				if (!CheckBusinessAccess(TYPE_BUSINESS_MEMBER, playerid, index, bm_perm_uninvite))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowBusinessMembers(playerid, GetPVarInt(playerid, "Business:Select"));
					return 1;
				}
				
				Remove:bmember_data(account_id, targetid);
				
				if (targetid != INVALID_PLAYER_ID) // online
				{	
					pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " �������� ��� �� �������� " #cPROJECT "%s" #cWHITE ".",
						GetPlayerCurrentName(playerid),
						GetBusinessName(index)
					);
					
					psend:(targetid, C_WHITE);
					
					format:g_small_string("// \"%s\" > %s �������� �� �������� %s.",
						GetBusinessName(index),
						GetPlayerCurrentName(playerid),
						GetPlayerCurrentName(targetid)
					);
					
					SendBusinessMessage(index, C_PROJECT, g_small_string);
				}
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " �� ������� ��������� ������ �� ��������.");
				ShowBusinessMembers(playerid, index);
				return 1;
			}
			
			if (!CheckBusinessAccess(TYPE_BUSINESS_MEMBER, playerid, index, bm_perm_change))
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
				ShowBusinessMemberSelected(playerid, listitem);
				return 1;
			}
			
			listitem--;
			bmember_select[playerid][mindex][bs_perm][listitem] = !bmember_select[playerid][mindex][bs_perm][listitem];
			
			if (targetid != INVALID_PLAYER_ID)
			{
				bmember_data[targetid][bm_perm][listitem] = bmember_select[playerid][mindex][bs_perm][listitem];
			}
			
			Update:bmember_data(playerid, mindex);
			
			ShowBusinessMemberSelected(playerid, mindex);
		}
		
		case D_BUSINESS + 18 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "�����", "�����");
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Business:Select");
			
			if (listitem == 0)
			{
				format:g_string("" #DEFAULT " ��������� �������� �������� �� �����\n\n\
				�������� ��������: " #cGREEN "$%i" #cWHITE "\n\
				������� �����, ������� �� ������ ����� �� �����:",
					GetBusinessProfit(index)
				);
				
				ShowPlayerDialog(playerid, D_BUSINESS + 19, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
			}
			else
			{
				format:g_string("" #DEFAULT " �������� �������� �� ���� ��������\n\n\
				�������� ��������: " #cGREEN "$%i" #cWHITE "\n\
				������� �����, ������� �� ������ �������� �� ���� ��������:",
					GetBusinessProfit(index)
				);
				
				ShowPlayerDialog(playerid, D_BUSINESS + 20, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
			}
			
		}
		
		case D_BUSINESS + 19 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 18, DIALOG_STYLE_LIST, " ", 
					" ��������� �������� �������� �� �����\n \
					�������� �������� �� ���� ��������",
					"�����", "�����"
				);
			
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Business:Select"),
				value = strval(inputtext);
			
			if (!(0 < value <= GetBusinessProfit(index)))
			{
				format:g_string("" #DEFAULT " ��������� �������� �������� �� �����\n\n\
				�������� ��������: " #cGREEN "$%i" #cWHITE "\n\
				������� �����, ������� �� ������ ����� �� �����:\n\n\
				" #cRED "�� ����� �������� �����.",
					GetBusinessProfit(index)
				);
				
				ShowPlayerDialog(playerid, D_BUSINESS + 19, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
				return 1;
			}
			
			GiveDebitCardMoney(playerid, value);
			business_data[index][b_profit] -= value;
			Update:business_int(index, "b_profit", business_data[index][b_profit]);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� �������� �������� �������� �� �����.");
			
			ShowPlayerDialog(playerid, D_BUSINESS + 18, DIALOG_STYLE_LIST, " ", 
				" ��������� �������� �������� �� �����\n \
				�������� �������� �� ���� ��������",
				"�����", "�����"
			);
		}
		
		case D_BUSINESS + 20 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 18, DIALOG_STYLE_LIST, " ", 
					" ��������� �������� �������� �� �����\n \
					�������� �������� �� ���� ��������",
					"�����", "�����"
				);
			
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Business:Select"),
				value = strval(inputtext);
			
			if (!(0 < value <= GetCharacterCardBalance(playerid)))
			{
				format:g_string("" #DEFAULT " �������� �������� �� ���� ��������\n\n\
				�������� ��������: " #cGREEN "$%i" #cWHITE "\n\
				������� �����, ������� �� ������ �������� �� ����:\n\n\
				" #cRED "�� ����� �������� �����.",
					GetBusinessProfit(index)
				);
				
				ShowPlayerDialog(playerid, D_BUSINESS + 20, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
				return 1;
			}
			
			GiveDebitCardMoney(playerid, -value);
			business_data[index][b_profit] += value;
			Update:business_int(index, "b_profit", business_data[index][b_profit]);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� �������� �������� �� ���� ��������.");
			
			ShowPlayerDialog(playerid, D_BUSINESS + 18, DIALOG_STYLE_LIST, " ", 
				" ��������� �������� �������� �� �����\n \
				�������� �������� �� ���� ��������",
				"�����", "�����"
			);
		}
		
		case D_BUSINESS + 21 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "�����", "�����");
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Business:Select");
			
			if (listitem == 0)
			{
				ShowBusinessSettingsSubtypes(playerid, index);
			}
			else if (listitem == 1)
			{
				ShowBusinessSettingsAssortment(playerid, index);
			}
		}
		
		case D_BUSINESS + 22 :
		{
			new index = GetPVarInt(playerid, "Business:Select");
			
			if (!response)
			{
				ShowBusinessSettings(playerid, index);
				return 1;
			}
			
			business_data[index][b_subtype] = listitem;
			Update:business_int(index, "b_subtype", listitem);
			Remove:all_bassort_data(index);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� �������� ������������. ������ ��������� ���� ��������� ��������.");
			ShowBusinessSettings(playerid, index);
		}
		
		case D_BUSINESS + 23 :
		{
			new index = GetPVarInt(playerid, "Business:Select");
			
			if (!response)
			{
				ShowBusinessSettings(playerid, index);
				return 1;
			}
			
			if (listitem == 0)
			{
				if (GetBusinessAssortCount(index) >= GetBusinessSubtypeSlots(index))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " � ��� ��� �������� �����������.");
					return 1;
				}
				
				AssortmentAddForBusiness(playerid, index);
				return 1;
			}
			
			listitem--;
			SetPVarInt(playerid, "BusinessAssort:Select", g_dialog_select[playerid][listitem]);
			ShowPlayerDialog(playerid, D_BUSINESS + 26, DIALOG_STYLE_LIST, " ", 
				" �������� ����\n \
				  ������� ���������",
				"�����", "�����" 
			);
		}
		
		case D_BUSINESS + 24 :
		{
			new index = GetPVarInt(playerid, "Business:Select"),
				item_id;
			
			if (!response)
			{
				ShowBusinessSettingsAssortment(playerid, index);
				return 1;
			}
			
			if (listitem == 0)
			{
				item_id = 1;
			}
			else
			{
				item_id = listitem + 63;
			}
			
			ShowBusinessAddAssort(playerid, true, item_id, business_data[index][b_type], business_data[index][b_subtype]);
		}
		
		case D_BUSINESS + 25 :
		{
			if (!response)
			{
				DeletePVar(playerid, "BusinessAssort:AddIndex");
				return 1;
			}
			
			new bindex = GetPVarInt(playerid, "Business:Select"),
				index = GetPVarInt(playerid, "BusinessAssort:AddIndex");
				
			if (GetBusinessAssortSimilar(bindex, 
			business_assort_list[index][bi_item_id], 
			business_assort_list[index][bi_item_param]))
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " � ��� ��� ��������� ������ ������� � ������������.");
				DeletePVar(playerid, "BusinessAssort:AddIndex");
				return 1;
			}
			
			Create:bassort_data(bindex, index);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� �������� ������ ����� � ������������.");
		}
		
		case D_BUSINESS + 26 :
		{
			new bindex = GetPVarInt(playerid, "Business:Select"),
				index = GetPVarInt(playerid, "BusinessAssort:Select");
			
			if (!response)
			{
				ShowBusinessSettingsAssortment(playerid, bindex);
				return 1;
			}
			
			if (listitem == 0)
			{
				format:g_string("\
					" #DEFAULT " �������� ����\n\n\
					������� ����� ���� �� �����:\n\n\
					" #cGRAY "����������� ����: " #cGREEN "$%i" #cGRAY ".\n\
					������������ ����: " #cGREEN "$%i" #cGRAY ".",
					GetMinBusinessAssortPrice(business_data[bindex][b_type], business_data[bindex][b_subtype], bassort_data[bindex][index][ba_item_id]),
					GetMaxBusinessAssortPrice(business_data[bindex][b_type], business_data[bindex][b_subtype], bassort_data[bindex][index][ba_item_id])
				);
					
					
				ShowPlayerDialog(playerid, D_BUSINESS + 27, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
			}
			else 
			{
				
				Remove:bassort_data(bindex, index);
				ShowBusinessSettingsAssortment(playerid, bindex);
				SendClientMessage(playerid, C_WHITE, !#ERROR " �� ������� ������� ������ ����� �� ������������.");
			}
		}
		
		case D_BUSINESS + 27 :
		{	
			new bindex = GetPVarInt(playerid, "Business:Select"),
				index = GetPVarInt(playerid, "BusinessAssort:Select"); 
			
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 26, DIALOG_STYLE_LIST, " ", 
					" �������� ����\n \
					  ������� ���������",
					"�����", "�����" 
				);
				return 1;
			}
			
			new value = strval(inputtext),
				item_id = bassort_data[bindex][index][ba_item_id];
			
			if (isnull(inputtext) 
			|| !(GetMinBusinessAssortPrice(business_data[bindex][b_type], business_data[bindex][b_subtype], item_id) <= value <= GetMaxBusinessAssortPrice(business_data[bindex][b_type], business_data[bindex][b_subtype], item_id)))
			{
				format:g_string("\
					" #DEFAULT " �������� ����\n\n\
					������� ����� ���� �� �����:\n\n\
					" #cGRAY "����������� ����: " #cGREEN "$%i" #cGRAY ".\n\
					������������ ����: " #cGREEN "$%i" #cGRAY ".\n\
					" #cRED "�� ����� �������� ���� �� �����.",
					GetMinBusinessAssortPrice(business_data[bindex][b_type], business_data[bindex][b_subtype], item_id),
					GetMaxBusinessAssortPrice(business_data[bindex][b_type], business_data[bindex][b_subtype], item_id)
				);
					
					
				ShowPlayerDialog(playerid, D_BUSINESS + 27, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
				return 1;
			}
			
			bassort_data[bindex][index][ba_cost] = value;
			Update:bassort_int(bindex, index, "ba_cost", value);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� �������� ����.");
			ShowPlayerDialog(playerid, D_BUSINESS + 26, DIALOG_STYLE_LIST, " ", 
				" �������� ����\n \
				  ������� ���������",
				"�����", "�����" 
			);
		}
	}
	
	return 1;
}

function OnBusinessCheckMembers(playerid, targetid, index)
{
	SetUserAllowQuery(playerid, true);
	
	new count;
	
	cache_get_value_name_int(0, "members_count", count);
	
	if (count >= MAX_BUSINESS_MEMBERS)
	{
		ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "�����", "�����");
		SendClientMessage(playerid, C_WHITE, !#ERROR " �������� ������������ ����� ���������.");
		return 1;
	}

	pformat:("" #SUCCESS " �� ��������� ����������� " #cPROJECT "%s" #cWHITE ".",
		GetPlayerCurrentName(targetid)
	);
	
	psend:(playerid, C_WHITE);
	
	ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
		DIALOG_BUSINESS_STAFF,
		"�������", "�����" 
	);
	
	SetPVarInt(targetid, "Business:OwnerId", playerid);
	SetPVarInt(targetid, "Business:OwnerSelect", index);
	
	format:g_string("" #DEFAULT " �����������\n\n\
		����������� �� " #cPROJECT "%s" #cWHITE ".\n\
		��� ���������� ����� ����������� �������� " #cPROJECT "%s" #cWHITE ".\n\
		�� ���������� �����������?",
		GetPlayerCurrentName(playerid),
		GetBusinessName(index)
	);
	
	ShowPlayerDialog(targetid, D_BUSINESS + 12, DIALOG_STYLE_MSGBOX, " ", g_string, "��", "���");
	return 1;
}