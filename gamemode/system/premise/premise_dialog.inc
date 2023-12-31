/*!
	@brief ������� ��� ������� ���������
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

Premise_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{	
		case D_PREMISE - 1 :
		{
			cmd_prmenu(playerid);
			return 1;
		}
		
		case D_PREMISE :
		{
			if (!response)
			{
				DeletePVar(playerid, "Premise:SelectPickup");
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Premise:SelectPickup"),
				type = premise_data[index][pr_int_type],
				server_tick = GetTickCount();
			
			if (GetPlayerVirtualWorld(playerid) != premise_data[index][pr_world] 
			|| !IsPlayerInRangeOfPoint(playerid, 
			FACTOR_TELEPORT_RADIUS, 
			premise_data[index][pr_pos][0], 
			premise_data[index][pr_pos][1], 
			premise_data[index][pr_pos][2]))
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " �� ���������� ������� ������ �� ���������.");
				DeletePVar(playerid, "Premise:SelectPickup");
				return 1;
			}
			
			if (premise_data[index][pr_lock])
			{
				SendClientMessage(playerid, C_WHITE, !ERROR_DOOR_CLOSED);
				GameTextForPlayer(playerid, "~r~~w~CLOSED", 2000, 4);
				DeletePVar(playerid, "Premise:SelectPickup");
				return 1;
			}
			
			if (IsPremiseTied(index)) // ���� �������� ������
			{
				if (!IsPremiseOwnerAccess(playerid, index))
				{
					if (GetPremiseEntrance(index) != 0 
					&& !CheckPremiseAccess(TYPE_PREMISE_MEMBER, playerid, index))
					{
						if (GetPVarInt(playerid, "Player:PremiseEntranceIndex") != index)
						{
							if (!GivePlayerCash(playerid, -GetPremiseEntrance(index)))
							{
								SendClientMessage(playerid, C_WHITE, !ERROR_PAY);
								DeletePVar(playerid, "Premise:SelectPickup");
								return 1;
							}
							
							GivePremiseProfit(index, GetPremiseEntrance(index));
						}
						
						SetPVarInt(playerid, "Player:PremiseEntranceIndex", index);
						SetPVarInt(playerid, "Player:PremiseEntranceTime", server_tick + 1000 * 60 * 30);
					}
				
					GivePremiseProfitByVisitor(index, playerid); // ������� �� ���������
				}
			}
			
			Move:player(playerid, 
				premise_settings[type][pset_pos][0], 
				premise_settings[type][pset_pos][1], 
				premise_settings[type][pset_pos][2], 
				premise_data[index][pr_id], 
				INT_PREMISE,
				true,
				premise_settings[type][pset_pos][3]
			);	
			
			DeletePVar(playerid, "Premise:SelectPickup");
		}
		
		case D_PREMISE + 1 :
		{
			if (!response)
			{
				return 1;
			}

			new index = GetPVarInt(playerid, "Premise:Select");
			
			if (listitem == 0)
			{
				ShowPremiseInformation(playerid, index, D_PREMISE - 1, true, "�����");
				return 1;
			}
			
			if (GetPVarInt(playerid, "Premise:IsOwner"))
			{
				if (!CheckPremiseAccess(TYPE_PREMISE_MEMBER, playerid, index)) 
				{
					return 1;
				}
				
				if (listitem == 1) // ���������� ����������
				{
					ShowPremiseControl(playerid, index);
					// ����������
				}
				else if (listitem == 2) // ���������� ���������
				{
					if (!CheckPremiseAccess(TYPE_PREMISE_OWNER, playerid, index)
					|| !IsPremiseTied(index))
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
						PremiseMenu(playerid, false);
						return 1;
					}
					
					ShowPremiseBusinessMenu(playerid, index);
				}
				else if (listitem == 3) // ����� �������
				{
					if (!CheckPremiseAccess(TYPE_PREMISE_MEMBER, playerid, index, bm_perm_renovation))
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
						PremiseMenu(playerid, false);
						return 1;
					}
				
					new renovation = !IsPlayerRenovation(playerid) ? true : false;
					
					SetRenovationMode(
						playerid, 
						renovation, 
						TYPE_REN_PREMISE, 
						index, 
						GetPremiseId(index),
						GetPremiseSettings(index, pset_furnitures)
					);
					
					if (renovation)
					{
						SendClientMessage(playerid, C_WHITE, !HELP_RENOVATION);
						ShowRenovationMenu(playerid);
					}
					else 
					{
						cmd_prmenu(playerid);
					}
				}
			}
			else 
			{
				SetPVarInt(playerid, "Premise:TypeBuy", 0);
				
				if (listitem == 1)
				{
					format:g_string("" #DEFAULT " ������������\n\n\
					�� ���������� ��������� ���������, ������� c������ ������������� ���������.\n\
					� �������� ��� ���������� ��������:\n  - \
					�������� ��������\n  - \
					����� �������\n    - \
					����������� ������\n    - \
					��������� �������.\n\n\
					�� ������������� ������� ��������� " #cPROJECT "#%i" cWHITE " �� " #cGREEN "$%i" #cWHITE "?",
						GetPremiseId(index),
						premise_data[index][pr_price]
					);
					
					ShowPlayerDialog(playerid, D_PREMISE + 2, DIALOG_STYLE_MSGBOX, " ", 
						g_string, 
						"��", "���" 
					);
					
					SetPVarInt(playerid, "Premise:BuyType", TYPE_BUY_FULLY);
				}
				else if (listitem == 2)
				{
					format:g_string("" #DEFAULT " ������\n\n\
					������� ������� ����� � ������ ��������� �� ������������ ����.\n\
					� �������� ��� ���������� ��������:\n  - \
					�������� ��������\n  - \
					" #cGRAY "������������ ����� �������" #cWHITE "\n    - \
					����������� ������\n    - \
					��������� �������.\n\n\
					" #cWHITE "�� ������������� ������ ��������� " #cPROJECT "#%i" cWHITE " �� " #cGREEN "$%i" #cWHITE "/������?",
						GetPremiseId(index),
						GetPremiseRent(index)
					);
					
					ShowPlayerDialog(playerid, D_PREMISE + 2, DIALOG_STYLE_MSGBOX, " ", 
						g_string, 
						"��", "���" 
					);
					
					SetPVarInt(playerid, "Premise:BuyType", TYPE_BUY_RENT);
				}
			}
		}
		
		case D_PREMISE + 2 :
		{
			if (!response)
			{
				cmd_prmenu(playerid);
				return 1;
			}

			BuyPremise(playerid, GetPVarInt(playerid, "Premise:Select"), GetPVarInt(playerid, "Premise:BuyType"));
		}
		
		case D_PREMISE + 3 :
		{
			if (!response)
			{
				cmd_prmenu(playerid);
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Premise:Select");
			
			if (listitem == 0) // �����
			{
				PremiseLock(playerid, index);
				ShowPremiseControl(playerid, index);
			}
			else if (listitem == 1) // �������� ��������
			{
				if (!CheckPremiseAccess(TYPE_PREMISE_OWNER, playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowPremiseControl(playerid, index);
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_PREMISE + 4, DIALOG_STYLE_INPUT, " ",
					DIALOG_PREMISE_NAME,
					"�����", "�����"
				);
			}
			
			else if (listitem == 2) // ������� ��������
			{
				if (!CheckPremiseAccess(TYPE_PREMISE_OWNER, playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowPremiseControl(playerid, index);
					return 1;
				}
				
				format:g_string("" #DEFAULT " ������� �����������\n\n\
				�� ������������� ������������� ������� " #cPROJECT "���������" #cWHITE " �����������?\n\
				� ������ ����� ����������� � ����� �� �����, �� �������� " #cGREEN "$%i" #cWHITE ".",
					GetSalePremisePrice(index)
				);
				
				ShowPlayerDialog(playerid, D_PREMISE + 5, DIALOG_STYLE_MSGBOX, " ", g_string, "��", "���");
			}
			
			else if (listitem == 3) // ������� ������
			{
				if (GetPremiseTypeBought(index) == TYPE_BUY_RENT)
				{
					SendClientMessage(playerid, C_WHITE, !NOT_RENT_ACCESS);
					ShowPremiseControl(playerid, index);
					return 1;
				}
			
				if (!CheckPremiseAccess(TYPE_PREMISE_OWNER, playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowPremiseControl(playerid, index);
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_PREMISE + 6, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " ������� ��������� ������\n\n\
					������� ID ������, �������� �� ������ ������� ���������:",
					"�����", "�����"
				);
			}
		}
		
		case D_PREMISE + 4 :
		{
			new index = GetPVarInt(playerid, "Premise:Select");
			
			if (!response)
			{
				ShowPremiseControl(playerid, index);
				return 1;
			}
			
			if (!IsValidPremiseNameString(inputtext))
			{
				ShowPlayerDialog(playerid, D_PREMISE + 4, DIALOG_STYLE_INPUT, " ",
					DIALOG_PREMISE_NAME,
					"�����", "�����"
				);
				
				return 1;
			}
			
			new server_tick = GetTickCount();
	
			if (GetPVarInt(playerid, "Premise:NameTime") > server_tick)
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
				ShowPremiseControl(playerid, index);
				return 1;
			}
			
			premise_data[index][pr_name][0] = EOS;
			strcat(premise_data[index][pr_name], inputtext, MAX_PREMISE_NAME);
			Update:premise_string(index, "pr_name", inputtext);
			Update:premise_text(index);
			ShowPremiseControl(playerid, index);
			
			SetPVarInt(playerid, "Premise:NameTime", server_tick + 1000);
		}
		
		case D_PREMISE + 5 :
		{
			new index = GetPVarInt(playerid, "Premise:Select");
			
			if (response)
			{
				SellPremise(index);
			}
			else 
			{
				ShowPremiseControl(playerid, index);
			}
		}
		
		case D_PREMISE + 6 :
		{
			new index = GetPVarInt(playerid, "Premise:Select"),
				targetid = strval(inputtext);
				
			if (!response)
			{
				cmd_prmenu(playerid);
				return 1;
			}
			
			if (!targetid || !IsPlayerLogged(targetid) || targetid == playerid)
			{
				ShowPlayerDialog(playerid, D_PREMISE + 6, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " ������� ��������� ������\n\n\
					������� ID ������, �������� �� ������ ������� ���������:\n\n\
					" #cRED "�� ����� �������� ID ������.",
					"�����", "�����"
				);
				
				return 1;
			}
			
			if (!IsPlayerAroundOfPlayer(playerid, targetid))
			{
				ShowPlayerDialog(playerid, D_PREMISE + 6, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " ������� ��������� ������\n\n\
					������� ID ������, �������� �� ������ ������� ���������:\n\n\
					" #cRED "������ ����� ��������� ������� ������ �� ���.",
					"�����", "�����"
				);
				
				return 1;
			}

			format:g_string("" #DEFAULT " ������� ��������� ������\n\n\
				������� ����� �� ������� �� ������ ������� ��������� " #cPROJECT "%s" #cWHITE ":\n\n\
				" #cGRAY "����������� ���� �������: " #cGREEN "$%i" #cGRAY ".\n\
				" #cGRAY "������������ ���� �������: " #cGREEN "$%i" #cGRAY ".",
				GetPlayerCurrentName(targetid),
				GetMinSalePremisePrice(index),
				GetMaxSalePremisePrice(index)
			);
			
			ShowPlayerDialog(playerid, D_PREMISE + 7, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
			
			SetPVarInt(playerid, "Premise:TargetId", targetid);
		}
		
		case D_PREMISE + 7 :
		{
			new index = GetPVarInt(playerid, "Premise:Select"),
				targetid = GetPVarInt(playerid, "Premise:TargetId"),
				money;
				
			if (!response)
			{
				ShowPlayerDialog(playerid, D_PREMISE + 6, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " ������� ��������� ������\n\n\
					������� ID ������, �������� �� ������ ������� ���������:",
					"�����", "�����"
				);
				
				return 1;
			}
			
			if (isnull(inputtext) || !IsInt(inputtext) 
			|| !(GetMinSalePremisePrice(index) <= (money = strval(inputtext)) <= GetMaxSalePremisePrice(index)))
			{
				format:g_string("" #DEFAULT " ������� ��������� ������\n\n\
					������� ����� �� ������� �� ������ ������� ��������� " #cPROJECT "%s" #cWHITE ":\n\n\
					" #cGRAY "����������� ���� �������: " #cGREEN "$%i" #cGRAY ".\n\
					" #cGRAY "������������ ���� �������: " #cGREEN "$%i" #cGRAY ".\n\
					" #cRED "�� ����� �������� �����.",
					GetPlayerCurrentName(targetid),
					GetMinSalePremisePrice(index),
					GetMaxSalePremisePrice(index)
				);
				
				ShowPlayerDialog(playerid, D_PREMISE + 7, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
				
				return 1;
			}
			
			if (!IsPlayerLogged(playerid) || !IsPlayerAroundOfPlayer(playerid, targetid))
			{
				format:g_string("" #DEFAULT " ������� ��������� ������\n\n\
					������� ����� �� ������� �� ������ ������� ��������� " #cPROJECT "%s" #cWHITE ":\n\n\
					" #cGRAY "����������� ���� �������: " #cGREEN "$%i" #cGRAY ".\n\
					" #cGRAY "������������ ���� �������: " #cGREEN "$%i" #cGRAY ".\n\
					" #cRED "����� ��������� ������ �� ��� ���� ��� ��� � ����.",
					GetPlayerCurrentName(targetid),
					GetMinSalePremisePrice(index),
					GetMaxSalePremisePrice(index)
				);
				
				ShowPlayerDialog(playerid, D_PREMISE + 7, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
				
				return 1;
			}
		
			pformat:("" #SUCCESS " �� ��������� ����������� � ������� ��������� " #cPROJECT "%s" #cWHITE ".",
				GetPlayerCurrentName(targetid)
			);
			
			psend:(playerid, C_WHITE);
			
			// -
			
			format:g_string("" #DEFAULT " �����������\n\n\
				" #cPROJECT "%s" #cWHITE " ���������� ��� ������ ��������� �� " #cGREEN "$%i" #cWHITE ".\n\
				�� ���������� �����������?",
				GetPlayerCurrentName(playerid),
				money
			);
			
			ShowPlayerDialog(targetid, D_PREMISE + 8, DIALOG_STYLE_MSGBOX, " ", 
				g_string,
				"��", "���"
			);
			
			SetPVarInt(targetid, "Premise:OwnerId", playerid);
			SetPVarInt(targetid, "Premise:OwnerSelect", index);
			SetPVarInt(targetid, "Premise:Price", money);
		}
		
		case D_PREMISE + 8 :
		{
			new ownerid = GetPVarInt(playerid, "Premise:OwnerId"),
				index = GetPVarInt(playerid, "Premise:OwnerSelect"),
				price = GetPVarInt(playerid, "Premise:Price");
				
			if (response)
			{
				if (SellPremiseToPlayer(ownerid, index, playerid, price))
				{
					pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " ������ ���� �����������.",
						GetPlayerCurrentName(playerid)
					);
					
					psend:(ownerid, C_WHITE);
					
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� �����������.");
				}
				// ������
			}
			else 
			{
				// ����������
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " �������� ���� �����������.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " �� ��������� �����������.");
			}
			
			DeletePVar(playerid, "Premise:OwnerId");
			DeletePVar(playerid, "Premise:OwnerSelect");
			DeletePVar(playerid, "Premise:Price");
		}
		
		case D_PREMISE + 9 :
		{
			if (!response)
			{
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Premise:Select");
			
			if (listitem == 0)
			{
				PremiseMenu(playerid, false);
			}
			else if (listitem == 1)
			{
				ShowFurnMenu(playerid, ITEM_LIST_BEGIN, D_FURN);
			}
			else if (listitem == 2)
			{
				ShowRoomList(playerid, index, D_PREMISE + 10, TYPE_REN_PREMISE);
			}
		}
		
		case D_PREMISE + 10 :
		{
			if (!response)
			{
				ShowRenovationMenu(playerid);
				return 1;
			}
				
			SetPVarInt(playerid, "Premise:Room", listitem);
			
			format:g_small_string("" #DEFAULT " ���� #%d",
				listitem + 1
			);
			
			ShowPlayerDialog(playerid, D_PREMISE + 11, DIALOG_STYLE_LIST, g_small_string, 
				" �������������� �������\n \
				�������������� ����\n \
				�������������� ����",
				"�����", "�����"
			);
		}
		
		case D_PREMISE + 11 :
		{
			new index = GetPVarInt(playerid, "Premise:Select");
			
			if (!response)
			{
				ShowRoomList(playerid, index, D_PREMISE + 10, TYPE_REN_PREMISE);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowTextureList(playerid, true, TEXTURE_ROOF);
			}
			else if (listitem == 1)
			{
				ShowTextureList(playerid, true, TEXTURE_WALL);
			}
			else if (listitem == 2)
			{
				ShowTextureList(playerid, true, TEXTURE_FLOOR);
			}
		}
		
		case D_PREMISE + 12 :
		{
			new index = GetPVarInt(playerid, "Premise:Select");
			
			if (!response)
			{
				cmd_prmenu(playerid);
				return 1;
			}
			
			if (listitem == 0) // �������� ������
			{
				format:g_string(#DEFAULT " �������� ������\n\n\
					�� ������: " #cPROJECT "%d" #cWHITE " ��.\n\
					������������ ����� �� ������: %d ��\n\
					" #cGREEN"$1" #cWHITE " = " #cPROJECT "1 ��." #cWHITE "\n\n\
					������� ���������� ������ ������ ��� ������:",
					premise_data[index][pr_assort_stock],
					MAX_ASSORT_STOCK
				);
				
				ShowPlayerDialog(playerid, D_PREMISE + 16, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
			}
			else if (listitem == 1) // ����� �� ����
			{
				if (GetPremiseEntrance(index) != 0)
				{
					premise_data[index][pr_entrance] = 0;
					Update:premise_int(index, "pr_entrance", 0);
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� ������ ����� �� ����.");
				}
				else 
				{
					new bindex = GetBusinessIndexById(GetPremiseBusinessId(index));
					
					if (business_data[bindex][b_subtype] == INVALID_PARAM)
					{
						SendClientMessage(playerid, C_WHITE, #ERROR " � ��� �� ��������� ��� ������������.");
						return 1;
					}
					
					if (!GetBusinessSubtypeEntrance(bindex))
					{
						SendClientMessage(playerid, C_WHITE, !#ERROR " ������ ��� ������������ �� ��������������� ������� �������� �����.");
						ShowPremiseBusinessMenu(playerid, index);
						return 1;
					}
					
					ShowPlayerDialog(playerid, D_PREMISE + 14, DIALOG_STYLE_INPUT, " ",
						"" #DEFAULT " ����� �� ����\n\n\
						������� �����, ������� �� ������ ������� � �����������:\n\n\
						" #cGRAY "����������� �����: " #cGREEN "$1" #cGRAY ".\n\
						" #cGRAY "������������ �����: " #cGREEN "$50" #cGRAY ".",
						"�����", "�����"
					);
				}
			}
			else if (listitem == 2) // 
			{
				if (IsPremiseCashExists(index))
				{
					Destroy:premise_cash_text(index);
					Clear:premise_cash(index);
					Update:premise_cash(index);
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� ������ �����.");
					ShowPremiseBusinessMenu(playerid, index);
				}
				else 
				{
					ShowPlayerDialog(playerid, D_PREMISE + 13, DIALOG_STYLE_MSGBOX, " ",
						"" #DEFAULT " ���������� �����\n\n\
						�� ������������� ������� ���������� ����� � ������ �����?",
						"��", "���"
					);
				}
			}
		}
		
		case D_PREMISE + 13 :
		{
			new index = GetPVarInt(playerid, "Premise:Select");
			
			if (!response)
			{
				ShowPremiseBusinessMenu(playerid, index);
				return 1;
			}
			
			new Float: x,
				Float: y,
				Float: z;
				
			GetPlayerPos(playerid, x, y, z);
			
			premise_data[index][pr_cash_pos][0] = x;
			premise_data[index][pr_cash_pos][1] = y;
			premise_data[index][pr_cash_pos][2] = z;
			
			Create:premise_cash_text(index);
			
			Update:premise_cash(index);
			ShowPremiseBusinessMenu(playerid, index);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� ���������� ����� � ������ �����.");
		}
		
		case D_PREMISE + 14 :
		{	
			new index = GetPVarInt(playerid, "Premise:Select");
			
			if (!response)
			{
				return 1;
			}
			
			new value = strval(inputtext);
			
			if (!(1 <= value <= 50))
			{	
				ShowPlayerDialog(playerid, D_PREMISE + 14, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " ����� �� ����\n\n\
					������� �����, ������� �� ������ ������� � �����������:\n\n\
					" #cGRAY "����������� �����: " #cGREEN "$1" #cGRAY ".\n\
					" #cGRAY "������������ �����: " #cGREEN "$50" #cGRAY ".\n\
					" #cRED "�� ����� �������� �����.",
					"�����", "�����"
				);
				
				return 1;
			}
			
			premise_data[index][pr_entrance] = value;
			Update:premise_int(index, "pr_entrance", value);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� ���������� ����� �� ����.");
			ShowPremiseBusinessMenu(playerid, index);
		}
		
		case D_PREMISE + 15 :
		{
			new index = GetPVarInt(playerid, "PremiseAssort:Index"),	
				prindex = GetPVarInt(playerid, "Premise:BuySelect"),
				bindex = GetPVarInt(playerid, "Premise:BusinessSelect"),
				asindex;
			
			if (!response)
			{
				DeletePVar(playerid, "PremiseAssort:Index");
				return 1;
			}
			
			asindex = GetAssortListIndex(
				business_data[bindex][b_type], 
				business_data[bindex][b_subtype], 
				bassort_data[bindex][index][ba_item_id], 
				bassort_data[bindex][index][ba_item_param] 
			);
			
			if (asindex == INVALID_PARAM)
			{
				printf("[Premise_OnDialogResponse:D_PREMISE+15]: Assort item doesn't exists. (ITEMID:%i)",
					bassort_data[bindex][index][ba_item_id]
				);
				
				DeletePVar(playerid, "PremiseAssort:Index");
				return 1;
			}
			
			if (!IsInventorySlotFreeExists(playerid))
			{
				SendClientMessage(playerid, C_WHITE, !ERROR_NO_SLOTS);
				DeletePVar(playerid, "PremiseAssort:Index");
				return 1;
			}
			
			if ((premise_data[prindex][pr_assort_stock] - business_assort_list[asindex][bi_count]) <= 0)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " �� ������ ����������� ������.");
				DeletePVar(playerid, "PremiseAssort:Index");
				return 1;
			}
			
			SetPVarInt(playerid, "PremiseAssort:Count", business_assort_list[asindex][bi_count]);
			
			MakePayment(playerid, bassort_data[bindex][index][ba_cost], "buy_item");
		}
		
		case D_PREMISE + 16: 
		{
			new index = GetPVarInt(playerid, "Premise:Select");
		
			if (!response)
			{
				ShowPremiseBusinessMenu(playerid, index);
				return 1;
			}
			
			new assort_stock = strval(inputtext);
			
			if (!(0 < assort_stock <= MAX_ASSORT_STOCK) || ((assort_stock + premise_data[index][pr_assort_stock]) > MAX_ASSORT_STOCK))
			{
				format:g_string(#DEFAULT " �������� ������\n\n\
					�� ������: " #cPROJECT "%d" #cWHITE " ��.\n\
					������������ ����� �� ������: %d ��\n\
					" #cGREEN"$1" #cWHITE " = " #cPROJECT "1 ��." #cWHITE "\n\n\
					������� ���������� ������ ������ ��� ������:\n\n\
					" #cRED "�� ����� �������� ���������� ������ ������.",
					premise_data[index][pr_assort_stock],
					MAX_ASSORT_STOCK
				);
				
				ShowPlayerDialog(playerid, D_PREMISE + 16, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
				return 1;
			}
			
			if (!GivePlayerCash(playerid, -assort_stock))
			{	
				format:g_string(#DEFAULT " �������� ������\n\n\
					�� ������: " #cPROJECT "%d" #cWHITE " ��.\n\
					������������ ����� �� ������: %d ��\n\
					" #cGREEN"$1" #cWHITE " = " #cPROJECT "1 ��." #cWHITE "\n\n\
					������� ���������� ������ ������ ��� ������:\n\n\
					" #cRED "� ��� ����������� ��������.",
					premise_data[index][pr_assort_stock],
					MAX_ASSORT_STOCK
				);
				
				ShowPlayerDialog(playerid, D_PREMISE + 16, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
				return 1;
			}
			
			premise_data[index][pr_assort_stock] += assort_stock;
			Update:premise_int(index, "pr_assort_stock", premise_data[index][pr_assort_stock]);
			
			pformat:(#SUCCESS " �� ������� �������� ������ � ���������� " #cPROJECT "%d ��." #cWHITE " �� ����� " #cGREEN "$%d" #cWHITE".",
				assort_stock,
				assort_stock
			);
			
			psend:(playerid, C_WHITE);
			
			ShowPremiseBusinessMenu(playerid, index);
		}
	}
	
	return 1;
}