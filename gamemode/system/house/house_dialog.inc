/*!
	@brief ������� ������� �����
	@author Found (evg.savosin)
	@date 16.12.2016, update 21.03.2018
*/

House_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{	
	
		/*!
			@brief ������� ��� ����
		*/
		
		case D_HOUSE - 1 :
		{
			cmd_hmenu(playerid);
			return 1;
		}
		
		case D_HOUSE :
		{
			if (!response)
			{
				DeletePVar(playerid, "House:SelectPickup");
				return 1;
			}
			
			new index = GetPVarInt(playerid, "House:SelectPickup"),
				type = house_data[index][h_int_type];
			
			if (GetPlayerVirtualWorld(playerid) != house_data[index][h_world] 
			|| !IsPlayerInRangeOfPoint(playerid, 
			FACTOR_TELEPORT_RADIUS, 
			house_data[index][h_pos][0], 
			house_data[index][h_pos][1], 
			house_data[index][h_pos][2]))
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " �� ������ ���������� ����� � �������� ����������.");
				DeletePVar(playerid, "House:SelectPickup");
				return 1;
			}
			
			if (house_data[index][h_lock])
			{
				SendClientMessage(playerid, C_WHITE, !ERROR_DOOR_CLOSED);
				GameTextForPlayer(playerid, "~r~~w~CLOSED", 2000, 4);
				DeletePVar(playerid, "House:SelectPickup");
				return 1;
			}
			
			Move:player(playerid, 
				house_settings[type][hset_pos][0], 
				house_settings[type][hset_pos][1], 
				house_settings[type][hset_pos][2], 
				house_data[index][h_id], 
				INT_HOUSE,
				true,
				house_settings[type][hset_pos][3]
			);	
			
			DeletePVar(playerid, "House:SelectPickup");
		}
		
		case D_HOUSE + 1 :
		{
			if (!response)
			{
				Clear:house_pvar(playerid);
				return 1;
			}
			
			new index = GetPVarInt(playerid, "House:Select"),
				garage_type = house_data[index][hg_int_type];
			
			if (listitem == 0)
			{
				ShowHouseInformation(playerid, index, D_HOUSE - 1, true, "�����");
				return 1;
			}
			
			if (GetPVarInt(playerid, "House:IsOwner"))
			{
				if (listitem == 1)
				{
					ShowHouseControl(playerid, index);
					// ����������
				}
				else if (listitem == 2)
				{
					if (!CheckHouseAccess(TYPE_HOUSE_OWNER, playerid, index))
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
						HouseMenu(playerid, false);
						return 1;
					}
					
					if (GetHouseTypeBought(index) == TYPE_BUY_RENT)
					{
						SendClientMessage(playerid, C_WHITE, !NOT_RENT_ACCESS);
						HouseMenu(playerid, false);
						return 1;
					}
					
					ShowLodgerList(playerid, index);
				}
				else if (listitem == 3)
				{
					if (!CheckHouseAccess(TYPE_HOUSE_LODGER, playerid, index, lod_perm_renovation))
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
						HouseMenu(playerid, false);
						return 1;
					}
					
					new renovation = !IsPlayerRenovation(playerid) ? true : false;
					
					SetRenovationMode(
						playerid, 
						renovation, 
						TYPE_REN_HOUSE, 
						index, 
						GetHouseId(index),
						house_settings[house_data[index][h_int_type]][hset_furnitures]
					);
					
					if (renovation)
					{
						SendClientMessage(playerid, C_WHITE, !HELP_RENOVATION);
						ShowRenovationMenu(playerid);
					}
					else 
					{
						cmd_hmenu(playerid);
					}
				}
				else if (listitem == 4)
				{
					if (!CheckHouseAccess(TYPE_HOUSE_LODGER, playerid, index, lod_perm_safe))
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
						HouseMenu(playerid, false);
						return 1;
					}
					
					ShowHouseSafe(playerid, index);
					// safe
				}
				else if (listitem == 5)
				{
					Move:player(playerid, 
						hgarage_settings[garage_type][hgset_alt_pos][0], 
						hgarage_settings[garage_type][hgset_alt_pos][1], 
						hgarage_settings[garage_type][hgset_alt_pos][2], 
						house_data[index][h_id], 
						INT_GARAGE,
						true,
						hgarage_settings[garage_type][hgset_alt_pos][3]
					);
				}
			}
			else 
			{
				SetPVarInt(playerid, "House:TypeBuy", 0);
				
				if (listitem == 1)
				{
					format:g_string("" #DEFAULT " ������������\n\n\
					�� ���������� ��������� �������� ���������, ������� ������ ������������� ���������.\n\
					� �������� ��� ���������� ��������:\n  - \
					���������� ��������� �� " #cPROJECT "%i" #cWHITE " � ��������� �� ����.\n  - \
					����� �������\n    - \
					����������� ������\n    - \
					��������� �������\n  - \
					������������ �������� � ������\n\n\
					�� ������������� ������� %s " #cPROJECT "#%i" #cWHITE " �� " #cGREEN "$%i" #cWHITE "?",
						house_settings[house_data[index][h_int_type]][hset_lodgers],
						(IsHouseType(index) == TYPE_APARTAMENT) ? ("��������") : ("����"),
						GetHouseId(index),
						house_data[index][h_price]
					);
					
					ShowPlayerDialog(playerid, D_HOUSE + 2, DIALOG_STYLE_MSGBOX, " ", 
						g_string, 
						"��", "���" 
					);
					
					SetPVarInt(playerid, "House:BuyType", TYPE_BUY_FULLY);
				}
				else if (listitem == 2)
				{
					format:g_string("" #DEFAULT " ������\n\n\
					����������� ������� ����� �������� ��������� �� ������������ ���� �� ������� �����.\n\
					������ ��������� ������� ������������ ���������:\n  - \
					�� ��������� ������ ������������ �����.\n  - \
					�� �� ������� ��������� � ���� ��������.\n  - \
					����� ������� ���������.\n  - \ 
					������������ �������� ������ ����������.\n\n\
					" #cWHITE "�� ������������� ������ %s " #cPROJECT "#%i" #cWHITE " �� " #cGREEN "$%i" #cWHITE "/������?",
						(IsHouseType(index) == TYPE_APARTAMENT) ? ("��������") : ("����"),
						GetHouseId(index),
						GetHouseRent(index)
					);
					
					ShowPlayerDialog(playerid, D_HOUSE + 2, DIALOG_STYLE_MSGBOX, " ", 
						g_string, 
						"��", "���" 
					);
					
					SetPVarInt(playerid, "House:BuyType", TYPE_BUY_RENT);
				}
			}
		}
		
		case D_HOUSE + 2 : // ������� ����
		{
			if (!response)
			{
				cmd_hmenu(playerid);
				return 1;
			}
			
			BuyHouse(playerid, GetPVarInt(playerid, "House:Select"), GetPVarInt(playerid, "House:BuyType"));
		}
		
		case D_HOUSE + 3 :
		{
			if (!response)
			{
				cmd_hmenu(playerid);
				return 1;
			}
			
			new index = GetPVarInt(playerid, "House:Select");
			
			if (listitem == 0)
			{
				HouseLock(playerid, index);
				
				ShowHouseControl(playerid, index);
			}
			else if (listitem == 1)
			{
				if (!CheckHouseAccess(TYPE_HOUSE_OWNER, playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowHouseControl(playerid, index);
					return 1;
				}
					
				if (GetHouseTypeBought(index) == TYPE_BUY_RENT)
				{
					ShowPlayerDialog(playerid, D_HOUSE + 11, DIALOG_STYLE_MSGBOX, " ", 
						"" #DEFAULT " ����������� ������\n\n\
						�� ������������� ������������� ����������� ������?\n\
						����������� �� ����� ������.", 
						"��", "���" 
					);
				}	
				else 
				{
					format:g_string("" #DEFAULT " ������� ���\n\n\
					�� ������������� ������������� ������� " #cPROJECT "%s" #cWHITE "?\n\
					� ������ ����� ����������� � ����� �� �����, �� �������� " #cGREEN "$%i" #cWHITE ".",
						(IsHouseType(index) == TYPE_HOUSE) ? ("����") : ("��������"),
						GetSaleHousePrice(index)
					);
					
					ShowPlayerDialog(playerid, D_HOUSE + 11, DIALOG_STYLE_MSGBOX, " ", g_string, "��", "���");
				}
			}
			else if (listitem == 2)
			{
				if (GetHouseTypeBought(index) == TYPE_BUY_RENT)
				{
					SendClientMessage(playerid, C_WHITE, !NOT_RENT_ACCESS);
					ShowHouseControl(playerid, index);
					return 1;
				}
				
				if (!CheckHouseAccess(TYPE_HOUSE_OWNER, playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowHouseControl(playerid, index);
					return 1;
				}
				
				ShowHouseDialogSell_Player(playerid);
			}
		}
		
		case D_HOUSE + 4 :
		{
			if (!response)
			{
				cmd_hmenu(playerid);
				DeletePVar(playerid, "Lodger:Select");
				return 1;
			}
			
			new index = GetPVarInt(playerid, "House:Select");
			
			if (GetHouseTypeBought(index) == TYPE_BUY_RENT)
			{
				SendClientMessage(playerid, C_WHITE, !NOT_RENT_ACCESS);
				return 1;
			}	
			
			if (!CheckHouseAccess(TYPE_HOUSE_OWNER, playerid, index))
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
				return 1;
			}
			
			if (listitem == 0)
			{
				if (!IsUserAllowQuery(playerid))
				{
					return 1;
				}
	
				format:g_string("SELECT COUNT(lod_house_id) as lodgers_count FROM " #__HLODGER " WHERE lod_house_id = %i",
					GetHouseId(index)
				);
				
				mysql_tquery(db, g_string, "OnHouseCheckLodgers", "ii", playerid, index);
				
				SetUserAllowQuery(playerid, false);
				return 1;
			}
			
			listitem--;
			if (!lodger_select[playerid][listitem ][ls_character_id])
			{
				ShowLodgerList(playerid, index);
				return 1;
			}
			
			SetPVarInt(playerid, "Lodger:Select", listitem);
			ShowLodgerSelected(playerid, listitem);
		}
		
		case D_HOUSE + 5 :
		{
			new index = GetPVarInt(playerid, "House:Select");
			
			if (!response)
			{
				ShowLodgerList(playerid, index);
				return 1;
			}
			
			if (!CheckHouseAccess(TYPE_HOUSE_OWNER, playerid, index))
			{
				return SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
			}
			
			new targetid;
				
			if (isnull(inputtext) || !IsInt(inputtext) || !IsPlayerLogged(targetid = strval(inputtext)) || 
			targetid == playerid)
			{
				ShowPlayerDialog(playerid, D_HOUSE + 5, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " ����������\n\n\
					������� ID ������, �������� �� ������ ��������� � ����:\n\n\
					" #cRED "�� ����� �������� ID ������.",
					"�����", "�����"
				);
				
				return 1;
			}
			
			if (!IsPlayerAroundOfPlayer(playerid, targetid))
			{
				ShowPlayerDialog(playerid, D_HOUSE + 5, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " ����������\n\n\
					������� ID ������, �������� �� ������ ��������� � ����:\n\n\
					" #cRED "������ ����� ��������� ������� ������ �� ���.",
					"�����", "�����"
				);
				
				return 1;
			}
			
			new hindex = GetPlayerHouse(targetid);

			if (lod_data[targetid][lod_house_index] != INVALID_PARAM || hindex != INVALID_PARAM)
			{
				ShowPlayerDialog(playerid, D_HOUSE + 5, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " ����������\n\n\
					������� ID ������, �������� �� ������ ��������� � ����:\n\n\
					" #cRED "������ ����� ��� ���-�� ���������.",
					"�����", "�����"
				);
				
				return 1;
			}
			
			pformat:("" #SUCCESS " �� ��������� ����������� � ���������� " #cPROJECT "%s" #cWHITE ".",
				GetPlayerCurrentName(targetid)
			);
			
			psend:(playerid, C_WHITE);
			
			cmd_hmenu(playerid);
			// -
			
			format:g_string("" #DEFAULT " �����������\n\n\
				" #cPROJECT "%s" #cWHITE " ���������� ��� ����������� � ��� �������� ���������.\n\
				�� ���������� �����������?", GetPlayerCurrentName(playerid) 
			);
			
			ShowPlayerDialog(targetid, D_HOUSE + 6, DIALOG_STYLE_MSGBOX, " ", 
				g_string,
				"��", "���"
			);
			
			SetPVarInt(targetid, "House:OwnerId", playerid);
			SetPVarInt(targetid, "House:OwnerSelect", index);
		}
		
		case D_HOUSE + 6 :
		{
			new ownerid = GetPVarInt(playerid, "House:OwnerId"),
				index = GetPVarInt(playerid, "House:OwnerSelect");
				
			if (response)
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " ������ ���� �����������.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
				
				SendClientMessage(ownerid, C_WHITE, !#DEFAULT " ��� ��������� ������� �������� � ����, ��������� � " #cGRAY "��������" #cWHITE " � �������� ������� ��������.");
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� �����������.");
				
				Create:lod_data(playerid, index);
			}
			else 
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " �������� ���� �����������.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " �� ��������� �����������.");
			}
			
			DeletePVar(playerid, "House:OwnerId");
			DeletePVar(playerid, "House:OwnerSelect");
		}
		
		case D_HOUSE + 7 :
		{
			new index = GetPVarInt(playerid, "House:Select");
			
			if (!response)
			{
				ShowLodgerList(playerid, index);
				return 1;
			}
				
			if (!CheckHouseAccess(TYPE_HOUSE_OWNER, playerid, index))
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
				return 1;
			}
			
			new lindex = GetPVarInt(playerid, "Lodger:Select"),
				account_id = lodger_select[playerid][lindex][ls_character_id],
				targetid = GetPlayerIdByCharacterId(account_id);
			
			if (listitem == 0)
			{
				Remove:lod_data(account_id, targetid);
			
				if (targetid != INVALID_PLAYER_ID) // online
				{	
					pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " ������� ��� �� ��������� ���������.",
						GetPlayerCurrentName(playerid)
					);
					
					psend:(targetid, C_WHITE);
				}
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� �������� ������� ������ �� ������ ��������� ���������.");
			
				return 1;
			}
			
			listitem--;

			lodger_select[playerid][lindex][ls_perm][listitem] = !lodger_select[playerid][lindex][ls_perm][listitem];
			
			if (targetid != INVALID_PLAYER_ID)
			{
				lod_data[targetid][lod_perm][listitem] = lodger_select[playerid][lindex][ls_perm][listitem];
			}
			
			if (!IsUserAllowQuery(playerid))
			{
				return 1;
			}
			
			format:g_string(
				"UPDATE " #__HLODGER " \
				SET \
					lod_perm_safe = %i, \
					lod_perm_renovation = %i, \ 
					lod_perm_inventory = %i, \
					lod_perm_garage = %i \
				WHERE \
					lod_character_id = %i \
				LIMIT 1",
				lodger_select[playerid][lindex][ls_perm][lod_perm_safe],
				lodger_select[playerid][lindex][ls_perm][lod_perm_renovation],
				lodger_select[playerid][lindex][ls_perm][lod_perm_inventory],
				lodger_select[playerid][lindex][ls_perm][lod_perm_garage],
				account_id
			);
			
			mysql_pquery(db, g_string, "OnHouseLodgerUpdate", "d", playerid);
			
			SetUserAllowQuery(playerid, false);
			
			ShowLodgerSelected(playerid, lindex);
		}
		
		case D_HOUSE + 8 :
		{
			if (!response)
			{
				Clear:house_pvar(playerid);
				return 1;
			}
			
			if (!IsPlayerRenovation(playerid))
			{
				Clear:house_pvar(playerid);
				SendClientMessage(playerid, C_WHITE, !NOT_RENOVATION_MODE);
				return 1;
			}
			
			new index = GetPVarInt(playerid, "House:Select");
			
			if (listitem == 0) // hmenu
			{
				cmd_hmenu(playerid);
			}
			else if (listitem == 1) // furniture
			{
				ShowFurnMenu(playerid, ITEM_LIST_BEGIN, D_FURN);
			}
			else if (listitem == 2) // retexture
			{
				ShowRoomList(playerid, index, D_HOUSE + 9, TYPE_REN_HOUSE);
			}
		}
		
		case D_HOUSE + 9 :
		{
			if (!response)
			{
				ShowRenovationMenu(playerid);
				return 1;
			}
			
			new index = GetPVarInt(playerid, "House:Select");
			
			if (!CheckHouseAccess(TYPE_HOUSE_LODGER, playerid, index, lod_perm_renovation))
			{
				return 1;
			}
				
			SetPVarInt(playerid, "House:Room", listitem);
			
			format:g_small_string("" #DEFAULT " ���� #%d",
				listitem + 1
			);
			
			ShowPlayerDialog(playerid, D_HOUSE + 10, DIALOG_STYLE_LIST, g_small_string, 
				" �������������� �������\n \
				�������������� ����\n \
				�������������� ����",
				"�����", "�����"
			);
		}
		
		case D_HOUSE + 10 :
		{
			new index = GetPVarInt(playerid, "House:Select");
				
			if (!response)
			{
				ShowRoomList(playerid, index, D_HOUSE + 9, TYPE_REN_HOUSE);
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
		
		case D_HOUSE + 11 :
		{
			new index = GetPVarInt(playerid, "House:Select");
				
			if (response)
			{
				SellHouse(index);
			}
			else
			{
				ShowHouseControl(playerid, index);
			}
		}
		
		case D_HOUSE + 12 :
		{
			if (!response)
			{
				return cmd_hmenu(playerid);
			}
			
			new index = GetPVarInt(playerid, "House:Select");
			
			if (listitem == 0)
			{
				ShowHouseSafe(playerid, index);	
			}
			else if (listitem == 1) // give 
			{
				ShowPlayerDialog(playerid, D_HOUSE + 13, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " ���� - ����� �����\n\n\
					������� �����, ������� �� ������ ����� �� ����:",
					"�����", "�����" 
				);
			}
			else if (listitem == 2)
			{
				ShowPlayerDialog(playerid, D_HOUSE + 14, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " ���� - �������� �����\n\n\
					������� �����, ������� �� ������ �������� � ����:",
					"�����", "�����" 
				);
			}
		}
		
		case D_HOUSE + 13 :
		{
			new index = GetPVarInt(playerid, "House:Select"),
				money;
				
			if (!response)
			{
				ShowHouseSafe(playerid, index);
				return 1;
			}
				
			if (isnull(inputtext) || !IsInt(inputtext) 
			|| !(0 < (money = strval(inputtext)) <= house_data[index][h_money]))
			{
				ShowPlayerDialog(playerid, D_HOUSE + 13, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " ���� - ����� �����\n\n\
					������� �����, ������� �� ������ ����� �� ����:\n\n\
					" #cRED "�� ����� �������� �����.",
					"�����", "�����" 
				);
				
				return 1;
			}
			
			GivePlayerCash(playerid, money);
			house_data[index][h_money] -= money;
			Update:house_int(index, "h_money", house_data[index][h_money]);
			
			pformat:("" #SUCCESS " �� ������� ����� ����� � ������� " #cGREEN "$%i" #cWHITE " �� �����.",
				money
			);
			
			psend:(playerid, C_WHITE);
			
			ShowHouseSafe(playerid, index);
		}
		
		case D_HOUSE + 14 :
		{
			new index = GetPVarInt(playerid, "House:Select"),
				money;
				
			if (!response)
			{
				ShowHouseSafe(playerid, index);
				return 1;
			}
				
			if (isnull(inputtext) || !IsInt(inputtext) 
			|| !(0 < (money = strval(inputtext)) <= GetCharacterMoney(playerid)))
			{
				ShowPlayerDialog(playerid, D_HOUSE + 14, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " ���� - �������� �����\n\n\
					������� �����, ������� �� ������ �������� � ����:\n\n\
					" #cRED "�� ����� �������� �����.",
					"�����", "�����" 
				);
				
				return 1;
			}
			
			GivePlayerCash(playerid, -money);
			house_data[index][h_money] += money;
			Update:house_int(index, "h_money", house_data[index][h_money]);
			
			pformat:("" #SUCCESS " �� ������� �������� ����� � ������� " #cGREEN "$%i" #cWHITE " � ����.",
				money
			);
			
			psend:(playerid, C_WHITE);
			
			ShowHouseSafe(playerid, index);
		}
		
		case D_HOUSE + 15 :
		{
			new index = GetPVarInt(playerid, "House:Select"),
				targetid;
				
			if (!response)
			{
				cmd_hmenu(playerid);
				return 1;
			}
			
			if (isnull(inputtext) 
			|| !IsInt(inputtext) 
			|| !IsPlayerLogged(targetid = strval(inputtext)) 
			|| targetid == playerid)
			{
				ShowHouseDialogSell_Player(playerid, "�� ����� �������� ID ������.");
				return 1;
			}
			
			if (!IsPlayerAroundOfPlayer(playerid, targetid))
			{
				ShowHouseDialogSell_Player(playerid, "������ ����� ��������� ������� ������ �� ���.");
				return 1;
			}
			
			ShowHouseDialogSell_Summ(playerid, index);
			SetPVarInt(playerid, "House:TargetId", targetid);
		}
		
		case D_HOUSE + 16 :
		{
			new index = GetPVarInt(playerid, "House:Select"),
				targetid = GetPVarInt(playerid, "House:TargetId"),
				money = strval(inputtext);
				
			if (!response)
			{
				ShowHouseDialogSell_Player(playerid);
				return 1;
			}
			
			if (isnull(inputtext) 
			|| !IsInt(inputtext) 
			|| !(GetMinSaleHousePrice(index) <= money <= GetMaxSaleHousePrice(index)))
			{
				ShowHouseDialogSell_Summ(playerid, index);
				return 1;
			}
			
			if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid))
			{
				ShowHouseDialogSell_Summ(playerid, index, "����� ��������� ������ �� ��� ���� ��� ��� � ����.");
				return 1;
			}
		
			pformat:("" #SUCCESS " �� ��������� ����������� � ������� %s " #cPROJECT "%s" #cWHITE ".",
				(IsHouseType(index) == TYPE_APARTAMENT) ? ("��������") : ("����"),
				GetPlayerCurrentName(targetid)
			);
			
			psend:(playerid, C_WHITE);
			
			// -
			
			format:g_string("" #DEFAULT " �����������\n\n\
				" #cPROJECT "%s" #cWHITE " ���������� ��� ������ %s �� " #cGREEN "$%i" #cWHITE ".\n\
				�� ���������� �����������?",
				GetPlayerCurrentName(playerid),
				(IsHouseType(index) == TYPE_APARTAMENT) ? ("��������") : ("���"),
				money
			);
			
			ShowPlayerDialog(targetid, D_HOUSE + 17, DIALOG_STYLE_MSGBOX, " ", 
				g_string,
				"��", "���"
			);
			
			SetPVarInt(targetid, "House:OwnerId", playerid);
			SetPVarInt(targetid, "House:OwnerSelect", index);
			SetPVarInt(targetid, "House:Price", money);
		}
		
		case D_HOUSE + 17 :
		{
			new ownerid = GetPVarInt(playerid, "House:OwnerId"),
				index = GetPVarInt(playerid, "House:OwnerSelect"),
				price = GetPVarInt(playerid, "House:Price");
				
			if (response) // �����
			{
				if (SellHouseToPlayer(ownerid, index, playerid, price))
				{
					pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " ������ ���� �����������.",
						GetPlayerCurrentName(playerid)
					);
					
					psend:(ownerid, C_WHITE);
					
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ������� �����������.");
				}
			}
			else // ���������
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " �������� ���� �����������.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " �� ��������� �����������.");
			}
			
			DeletePVar(playerid, "House:OwnerId");
			DeletePVar(playerid, "House:OwnerSelect");
			DeletePVar(playerid, "House:Price");
		}
		
		case D_HOUSE + 18 :
		{
			ShowLodgerList(playerid, GetPVarInt(playerid, "House:Select"));
		}
		
		/*!
			@brief ������� ��� ������
		*/
		
		case D_GARAGE :
		{
			if (!response)
			{
				Clear:house_pvar(playerid);
				
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Garage:Select");
			
			if (!CheckHouseAccess(TYPE_HOUSE_LODGER, playerid, index, lod_perm_garage))
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
				return 1;
			}
			
			if (listitem == 0)
			{
				format:g_string(" %s " #cWHITE "�����\t" #cGRAY "/glock" #cWHITE "\n", 
					house_data[index][hg_lock] ? ("" #cPROJECT "�������") : ("" #cGRAY "�������")
				);
				
				ShowPlayerDialog(playerid, D_GARAGE + 1, DIALOG_STYLE_TABLIST, " ", g_string, "�������", "�����");
			}
			else if (listitem == 1)
			{	
				cmd_clist(playerid);
			}
			else if (listitem == 2)
			{
				if (!house_data[index][hg_set_furn])
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " ������ ����� ����������, ��������� ����������� ������������ ���������.");
				}
				
				new renovation = !IsPlayerRenovation(playerid) ? true : false;
					
				SetRenovationMode(
					playerid, 
					renovation, 
					TYPE_REN_GARAGE, 
					index, 
					GetHouseId(index), 
					hgarage_settings[house_data[index][hg_int_type]][hgset_furnitures] 
				);
				
				if (renovation)
				{
					SendClientMessage(playerid, C_WHITE, !HELP_RENOVATION);
					ShowRenovationMenu(playerid);
				}
				else 
				{
					GarageMenu(playerid);
				}
			}
			else if (listitem == 3) // ���������
			{
				if (!CheckHouseAccess(TYPE_HOUSE_OWNER, playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					return 1;
				}
				
				ShowGarageSettings(playerid, index, D_GARAGE + 2);
			}
		}
		
		case D_GARAGE + 1 :
		{
			if (!response)
			{
				GarageMenu(playerid, false);
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Garage:Select");
			
			if (!CheckHouseAccess(TYPE_HOUSE_LODGER, playerid, index, lod_perm_garage))
			{
				return 1;
			}
			
			if (listitem == 0)
			{
				GarageLock(playerid, index);
				
				format:g_string(" %s �����" #cWHITE "", 
					house_data[index][hg_lock] ? ("" #cPROJECT "�������") : ("" #cGRAY "�������")
				);
				
				ShowPlayerDialog(playerid, D_GARAGE + 1, DIALOG_STYLE_LIST, " ", g_string, "�������", "�����");
				
				return 1;
			}
		}
		
		case D_GARAGE + 2 :
		{
			if (!response)
			{
				GarageMenu(playerid, false);
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Garage:Select");
			
			if (listitem == 0) // ��������� ���������
			{
				if (GetHouseTypeBought(index) == TYPE_BUY_RENT)
				{
					SendClientMessage(playerid, C_WHITE, !NOT_RENT_ACCESS);
					return 1;
				}
			
				if (house_data[index][hg_set_furn])
				{
					ShowPlayerDialog(playerid, D_GARAGE + 3, DIALOG_STYLE_MSGBOX, " ", 
						"" #DEFAULT " ������������ ��������\n\n\
						��� ���������� ������������ ��� ����� ��������� ������� " #cPROJECT "��������" #cWHITE ".\n\
						�� ������������� ������ ��������? ",
						"��", "���" 
					);
				}
				else 
				{
					ShowPlayerDialog(playerid, D_GARAGE + 3, DIALOG_STYLE_MSGBOX, " ", 
						"" #DEFAULT " ������������ ��������\n\n\
						�� ��������� ������������ ��������, � ������� ������� �� ������� ��������� �������� ���, ��� �� ������ ���.\n\
						� ��� ������� ����� �� ������� ������������ ���������� ���������.\n\
						�� ������������� ������ ��������? ",
						"��", "���" 
					);
				}
			}
		}
		
		case D_GARAGE + 3 :
		{
			new index = GetPVarInt(playerid, "Garage:Select"),
				server_tick = GetTickCount();
	
			if (GetPVarInt(playerid, "TimeOut:GarageSetFurn") > server_tick)
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
				return 1;
			}
			
			if (response)
			{
				if (house_data[index][hg_set_furn])
				{
					Remove:all_furn_data(index, TYPE_REN_GARAGE);
					Create:static_furn(index, house_data[index][hg_int_type]);
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� ��������� ������������ ��������.");
				}
				else 
				{
					Destroy:static_furn(index);
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� �������� ������������ ��������.");
				}
				
				house_data[index][hg_set_furn] = !house_data[index][hg_set_furn];
				Update:garage_data(index);
			}
			else 
			{
				ShowGarageSettings(playerid, index, D_GARAGE + 2);
			}
			
			SetPVarInt(playerid, "TimeOut:GarageSetFurn", server_tick + 60_000);
		}
		
		case D_GARAGE + 4 :
		{
			if (!response)
			{
				return 1;
			}
			
			if (listitem == 0)
			{
				cmd_gmenu(playerid);
			}
			else if (listitem == 1)
			{
				ShowFurnMenu(playerid, ITEM_LIST_BEGIN, D_FURN);
			}
		}
	}
	
	return 1;
}

function OnHouseCheckLodgers(playerid, index)
{
	SetUserAllowQuery(playerid, true);
	
	new lodgers_count;
	
	cache_get_value_name_int(0, "lodgers_count", lodgers_count);
	
	if (lodgers_count >= house_settings[house_data[index][h_int_type]][hset_lodgers])
	{
		ShowPlayerDialog(playerid, D_HOUSE + 18, DIALOG_STYLE_MSGBOX, " ", 
			"" #ERROR " ����������\n\n\
			�� �� ������ ��������� � ���� ������ ���������.",
			"�����", ""
		);
		
		return 1;
	}
	
	ShowPlayerDialog(playerid, D_HOUSE + 5, DIALOG_STYLE_INPUT, " ", 
		"" #DEFAULT " ����������\n\n\
		������� ID ������, �������� �� ������ ��������� � ����:",
		"�����", "�����"
	);
	
	return 1;
}

function OnHouseLodgerUpdate(playerid)
{
	SetUserAllowQuery(playerid, true);
	return 1;
}