/*!
	@brief Файл с диалогами для криминальных систем
	@author Flavo
	@date 05.11.2019
*/

Crime_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		/// CMD:crmenu
		case D_CRIME:
		{
			if (!response)
			{
				return 1;
			}
			
			new crime_index = GetCrimeMember(playerid);
			
			if (listitem == 0) // CMD:crmenu -> Информация
			{
				ShowCrimeInformation(playerid, crime_index); // D_CRIME_DATA
				return 1;
			}
			
			if (listitem == 1) // CMD:crmenu -> Участники
			{
				ShowCrimeMember(playerid); // D_CRIME_MEMBER
				return 1;
			}
			
			if (listitem == 2) // CMD:crmenu -> Заказать товар
			{
				if (!CheckCrimeAccess(playerid, INVALID_PARAM, true) // Проверка на лидера
				&& !CheckCrimeAccess(playerid, cr_perm_manage, false)
				&& !CheckCrimeAccess(playerid, cr_perm_buy, false)
				)
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					
					ShowCrimeList(playerid);
					return 1;
				}
				
				ShowCrimeBuy(playerid); // D_CRIME_BUY
				return 1;
			}
		}
		
		case D_CRIME_DATA:
		{
			ShowCrimeList(playerid);
		}
		
		case D_CRIME_MEMBER:
		{
			if (!response)
			{
				ShowCrimeList(playerid);
				return 1;
			}
			
			new crime_index = GetCrimeMember(playerid);
			
			if (listitem == 0) // D_CRIME_INVITE
			{
				
				if (!CheckCrimeAccess(playerid, INVALID_PARAM, true)
				&& !CheckCrimeAccess(playerid, cr_perm_manage, false)
				&& !CheckCrimeAccess(playerid, cr_perm_invite, false)
				)
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					
					ShowCrimeMember(playerid);
					return 1;
				}
			
				ShowCrimeStaffInvite(playerid);
				return 1;
			}
			
			if (listitem == 1) // D_CRIME_UNINVITE
			{
				if (!CheckCrimeAccess(playerid, INVALID_PARAM, true)
				&& !CheckCrimeAccess(playerid, cr_perm_manage, false)
				&& !CheckCrimeAccess(playerid, cr_perm_uninvite, false)
				)
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					
					ShowCrimeMember(playerid);
					return 1;
				}
				
				ShowCrimeStaffUninvite(playerid); 
				return 1;
			}
			
			if (listitem == 2) // D_CRIME_PERM
			{
				if (!CheckCrimeAccess(playerid, INVALID_PARAM, true)
				&& !CheckCrimeAccess(playerid, cr_perm_manage, false)
				)
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					
					ShowCrimeMember(playerid);
					return 1;
				}
				
				ShowCrimeStaffPerm(playerid);
				return 1;
			}
			
			if (listitem == 3) // D_CRIME_MEMBER_LIST
			{
				ShowCrimeMemberList(playerid, crime_index, CRIME_LIST_BEGIN); 
				return 1;
			}
		}
		
		case D_CRIME_INVITE:
		{
			if (!response)
			{
				ShowCrimeMember(playerid);
				return 1;
			}
			
			InvitePlayerToCrime(playerid, inputtext, true);
		}
		
		case D_CRIME_INVITE_PLAYER:
		{
			new crime_index = GetPVarInt(playerid, "Crime:MemberIndex"),
				crime_member_index = GetPVarInt(playerid, "Crime:MemberId");
		
			if (!response)
			{
				pformat:("" #ERROR " Игрок отказался от Вашего предложения.");
				psend:(crime_member_index, C_WHITE);
				
				return 1;
			}
			
			Clear:crmember_data(playerid);
			
			Create:crime_member(playerid, crime_index);
			
			crmember_data[playerid][cr_crime_index] = crime_index;
			
			for (new i; i < sizeof crmember_data; i++)
			{
				if (crmember_data[i][cr_crime_index] != crime_index)
				{
					continue;
				}
				
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " принял " #cPROJECT "%s" #cWHITE " в организацию.",
					character_data[crime_member_index][c_name],
					character_data[playerid][c_name]
				);
				psend:(i, C_WHITE);
			}
		}
		
		case D_CRIME_UNINVITE:
		{
			if (!response)
			{
				ShowCrimeMember(playerid);
				return 1;
			}
			
			new targetid = strval(inputtext),
				crime_index = GetCrimeMember(playerid);
		
			if (isnull(inputtext)
			|| !IsInt(inputtext)
			|| !IsPlayerLogged(targetid)
			|| playerid == targetid
			|| crmember_data[targetid][cr_leader]
			|| crmember_data[targetid][cr_crime_index] != crmember_data[playerid][cr_crime_index]
			)
			{
				ShowCrimeStaffUninvite(playerid, "Вы указали некорректного игрока.");
				return 1;
			}
			
			Destroy:crmember_to_id(targetid);
			
			Clear:crmember_data(targetid);
			
			pformat:("\
				" #ERROR " Вы были исключены из криминальной организации " #cPROJECT "%s " #cWHITE ". " #cGRAY "(Кем: %s)",
				GetCrimeName(playerid),
				character_data[playerid][c_name]
			);
			psend:(targetid ,C_WHITE);
			
			for (new i; i < sizeof crmember_data; i++)
			{
				if (crmember_data[i][cr_crime_index] != crime_index)
				{
					continue;
				}
				
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " исключил " #cPROJECT "%s" #cWHITE " из организации.",
					character_data[playerid][c_name],
					character_data[targetid][c_name]
				);
				psend:(i, C_WHITE);
			}
			
			ShowCrimeMember(playerid);
		}
		
		case D_CRIME_PERM:
		{
			if (!response)
			{
				ShowCrimeMember(playerid);
				return 1;
			}
			
			new targetid = strval(inputtext);
		
			if (isnull(inputtext)
			|| !IsInt(inputtext)
			|| !IsPlayerLogged(targetid)
			|| playerid == targetid
			|| crmember_data[targetid][cr_leader]
			|| crmember_data[targetid][cr_crime_index] != crmember_data[playerid][cr_crime_index]
			)
			{
				ShowCrimeStaffPerm(playerid, "Вы указали некорректного игрока.");
				return 1;
			}
			
			SetPVarInt(playerid, "Crime:StaffEditPerm", targetid); 
			ShowCrimeStaffPermEdit(playerid, targetid); 				// D_CRIME_EDIT_PERM
		}
		
		case D_CRIME_EDIT_PERM:
		{
			new targetid = GetPVarInt(playerid, "Crime:StaffEditPerm");
			
			if (!IsPlayerLogged(targetid))
			{
				pformat:("" #ERROR " Выбраный игрок вышел из игры.");
				psend:(playerid, C_WHITE);
				
				ShowCrimeMember(playerid);
				return 1;
			}
			
			if (!response)
			{
				DeletePVar(playerid, "Crime:StaffEditPerm");
			
				ShowCrimeMember(playerid);
				return 1;
			}
			
			new crime_id = crime_data[GetCrimeMember(targetid)][cr_id],
				crm_character_id = character_data[targetid][c_id];
			
			if (listitem == 0)
			{
				if (crmember_data[targetid][cr_perm][cr_perm_invite] < 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_invite", 1);
					
					crmember_data[targetid][cr_perm][cr_perm_invite] = 1;
					
					ShowCrimeStaffPermEdit(playerid, targetid);
					return 1;
				}
				
				if (crmember_data[targetid][cr_perm][cr_perm_invite] == 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_invite", 0);
					
					crmember_data[targetid][cr_perm][cr_perm_invite] = 0;
					
					ShowCrimeStaffPermEdit(playerid, targetid);
					return 1;
				}
			}
			
			if (listitem == 1)
			{
				if (crmember_data[targetid][cr_perm][cr_perm_uninvite] < 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_uninvite", 1);
					
					crmember_data[targetid][cr_perm][cr_perm_uninvite] = 1;
					
					ShowCrimeStaffPermEdit(playerid, targetid);
					return 1;
				}
				
				if (crmember_data[targetid][cr_perm][cr_perm_uninvite] == 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_uninvite", 0);
					
					crmember_data[targetid][cr_perm][cr_perm_uninvite] = 0;
					
					ShowCrimeStaffPermEdit(playerid, targetid);
					return 1;
				}
			}
			
			if (listitem == 2)
			{
				if (crmember_data[targetid][cr_perm][cr_perm_buy] < 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_buy", 1);
					
					crmember_data[targetid][cr_perm][cr_perm_buy] = 1;
					
					ShowCrimeStaffPermEdit(playerid, targetid);
					return 1;
				}
				
				if (crmember_data[targetid][cr_perm][cr_perm_buy] == 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_buy", 0);
					
					crmember_data[targetid][cr_perm][cr_perm_buy] = 0;
					
					ShowCrimeStaffPermEdit(playerid, targetid);
					return 1;
				}
			}
			
			if (listitem == 3)
			{
				if (crmember_data[targetid][cr_perm][cr_perm_manage] < 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_manage", 1);
					
					crmember_data[targetid][cr_perm][cr_perm_manage] = 1;
					
					ShowCrimeStaffPermEdit(playerid, targetid);
					return 1;
				}
				
				if (crmember_data[targetid][cr_perm][cr_perm_manage] == 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_manage", 0);
					
					crmember_data[targetid][cr_perm][cr_perm_manage] = 0;
					
					ShowCrimeStaffPermEdit(playerid, targetid);
					return 1;
				}
			}
		}
		
		case D_CRIME_MEMBER_LIST:
		{
			if (!response)
			{
				ShowCrimeMember(playerid);
				return 1;
			}
			
			new crime_index = GetCrimeMember(playerid);
			
			if (crmember_select[playerid][listitem][cr_character_id] == CRIME_LIST_NEXT)
			{
				ShowCrimeMemberList(playerid, crime_index, CRIME_LIST_NEXT);
				return 1;
			}
			
			if (crmember_select[playerid][listitem][cr_character_id] == CRIME_LIST_BACK)
			{
				ShowCrimeMemberList(playerid, crime_index, CRIME_LIST_BACK);
				return 1;
			}
			
			
			
			if (crmember_select[playerid][listitem][cr_character_id] == GetCharacterId(playerid))
			{
				ShowCrimeMemberList(playerid, crime_index, CRIME_LIST_CURRENT);
				
				pformat:("" #ERROR " Вы не можете выбрать своего персонажа.");
				psend:(playerid, C_WHITE);
				
				return 1;
			}
			
			if (crmember_select[playerid][listitem][cr_leader])
			{
				ShowCrimeMemberList(playerid, crime_index, CRIME_LIST_CURRENT);
				
				pformat:("" #ERROR " Вы не можете выбрать лидера.");
				psend:(playerid, C_WHITE);
				
				return 1;
			}
			
			SetPVarInt(playerid, "Crime:MemberSelect", listitem);
			ShowCrimeMemberEdit(playerid, listitem); // D_CRIME_MEMBER_EDIT
		}
		
		case D_CRIME_MEMBER_EDIT:
		{
			new crime_index = GetCrimeMember(playerid);
		
			if (!response)
			{
				DeletePVar(playerid, "Crime:MemberSelect");
				
				ShowCrimeMemberList(playerid, crime_index, CRIME_LIST_CURRENT);
				
				return 1;
			}
			
			new crime_member_index = GetPVarInt(playerid, "Crime:MemberSelect"),
				crm_character_id = crmember_select[playerid][crime_member_index][cr_character_id],
				crime_id = crime_data[crime_index][cr_id],
				crime_member_id = GetCrimeMemberIdToSelect(playerid, crime_member_index);
			
			if (listitem == 0)
			{
				if (!CheckCrimeAccess(playerid, INVALID_PARAM, true)
				&& !CheckCrimeAccess(playerid, cr_perm_manage, false)
				&& !CheckCrimeAccess(playerid, cr_perm_uninvite, false)
				)
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					
					ShowCrimeMemberEdit(playerid, crime_member_index);
					return 1;
				}
				
				Destroy:crmember_to_select(playerid, crime_member_index);
				
				for (new i; i < sizeof character_data; i++)
				{
					if (character_data[i][c_id] != crmember_select[playerid][crime_member_index][cr_character_id])
					{
						continue;
					}
					
					Clear:crmember_data(i);
					
					pformat:("\
						" #ERROR " Вы были исключены из криминальной организации " #cPROJECT "%s " #cWHITE ". " #cGRAY "(Кем: %s)",
						GetCrimeName(playerid),
						character_data[playerid][c_name]
					);
					psend:(i ,C_WHITE);
				}
				
				for (new i; i < sizeof crmember_data; i++)
				{
					if (crmember_data[i][cr_crime_index] != crime_index)
					{
						continue;
					}
					
					pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " исключил " #cPROJECT "%s" #cWHITE " из организации.",
						character_data[playerid][c_name],
						crmember_select[playerid][crime_member_index][cr_name]
					);
					psend:(i, C_WHITE);
				}
				
				ShowCrimeMemberList(playerid, crime_index, CRIME_LIST_CURRENT);
				
				return 1;
			}
			
			if (listitem == 1)
			{
				if (!CheckCrimeAccess(playerid, INVALID_PARAM, true)
				&& !CheckCrimeAccess(playerid, cr_perm_manage, false)
				)
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					
					ShowCrimeMemberEdit(playerid, crime_member_index);
					return 1;
				}
				
				if (crmember_select[playerid][crime_member_index][cr_perm][cr_perm_invite] < 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_invite", 1);
					
					if (crime_member_id != INVALID_PARAM)
					{
						crmember_data[crime_member_id][cr_perm][cr_perm_invite] = 1;
					}
					
					crmember_select[playerid][crime_member_index][cr_perm][cr_perm_invite] = 1;
					
					ShowCrimeMemberEdit(playerid, crime_member_index);
					return 1;
				}
				
				if (crmember_select[playerid][crime_member_index][cr_perm][cr_perm_invite] == 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_invite", 0);
					
					if (crime_member_id != INVALID_PARAM)
					{
						crmember_data[crime_member_id][cr_perm][cr_perm_invite] = 0;
					}
					
					crmember_select[playerid][crime_member_index][cr_perm][cr_perm_invite] = 0;
					
					ShowCrimeMemberEdit(playerid, crime_member_index);
					return 1;
				}
			}
			
			if (listitem == 2)
			{
				if (!CheckCrimeAccess(playerid, INVALID_PARAM, true)
				&& !CheckCrimeAccess(playerid, cr_perm_manage, false)
				)
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					
					ShowCrimeMemberEdit(playerid, crime_member_index);
					return 1;
				}
				
				if (crmember_select[playerid][crime_member_index][cr_perm][cr_perm_uninvite] < 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_uninvite", 1);
					
					if (crime_member_id != INVALID_PARAM)
					{
						crmember_data[crime_member_id][cr_perm][cr_perm_uninvite] = 1;
					}
					
					crmember_select[playerid][crime_member_index][cr_perm][cr_perm_uninvite] = 1;
					
					ShowCrimeMemberEdit(playerid, crime_member_index);
					return 1;
				}
				
				if (crmember_select[playerid][crime_member_index][cr_perm][cr_perm_uninvite] == 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_uninvite", 0);
					
					if (crime_member_id != INVALID_PARAM)
					{
						crmember_data[crime_member_id][cr_perm][cr_perm_uninvite] = 0;
					}
					
					crmember_select[playerid][crime_member_index][cr_perm][cr_perm_uninvite] = 0;
					
					ShowCrimeMemberEdit(playerid, crime_member_index);
					return 1;
				}
			}
			
			if (listitem == 3)
			{
				if (!CheckCrimeAccess(playerid, INVALID_PARAM, true)
				&& !CheckCrimeAccess(playerid, cr_perm_manage, false)
				)
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					
					ShowCrimeMemberEdit(playerid, crime_member_index);
					return 1;
				}
				
				if (crmember_select[playerid][crime_member_index][cr_perm][cr_perm_buy] < 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_buy", 1);
					
					if (crime_member_id != INVALID_PARAM)
					{
						crmember_data[crime_member_id][cr_perm][cr_perm_buy] = 1;
					}
					
					crmember_select[playerid][crime_member_index][cr_perm][cr_perm_buy] = 1;
					
					ShowCrimeMemberEdit(playerid, crime_member_index);
					return 1;
				}
				
				if (crmember_select[playerid][crime_member_index][cr_perm][cr_perm_buy] == 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_buy", 0);
					
					if (crime_member_id != INVALID_PARAM)
					{
						crmember_data[crime_member_id][cr_perm][cr_perm_buy] = 0;
					}
					
					crmember_select[playerid][crime_member_index][cr_perm][cr_perm_buy] = 0;
					
					ShowCrimeMemberEdit(playerid, crime_member_index);
					return 1;
				}		
			}
			
			if (listitem == 4)
			{
				if (!CheckCrimeAccess(playerid, INVALID_PARAM, true)
				)
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					
					ShowCrimeMemberEdit(playerid, crime_member_index);
					return 1;
				}
				
				if (crmember_select[playerid][crime_member_index][cr_perm][cr_perm_manage] < 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_manage", 1);
					
					if (crime_member_id != INVALID_PARAM)
					{
						crmember_data[crime_member_id][cr_perm][cr_perm_manage] = 1;
					}
					
					crmember_select[playerid][crime_member_index][cr_perm][cr_perm_manage] = 1;
					
					ShowCrimeMemberEdit(playerid, crime_member_index);
					return 1;
				}
				
				if (crmember_select[playerid][crime_member_index][cr_perm][cr_perm_manage] == 1)
				{
					Update:crmember_perm(crime_id, crm_character_id, "cr_perm_manage", 0);
					
					if (crime_member_id != INVALID_PARAM)
					{
						crmember_data[crime_member_id][cr_perm][cr_perm_manage] = 0;
					}
					
					crmember_select[playerid][crime_member_index][cr_perm][cr_perm_manage] = 0;
					
					ShowCrimeMemberEdit(playerid, crime_member_index);
					return 1;
				}		
			}
		}
		
		case D_CRIME_BUY:
		{
			if (!response)
			{
				ShowCrimeList(playerid);
				return 1;
			}
			
			new crime_index = GetCrimeMember(playerid);
			
			if (listitem == 0) // CMD: crmenu -> Заказать товар -> Информация
			{
				ShowCrimeBuyInformation(playerid); // D_CRIME_BUY_INFORMATION
				return 1;
			}
			
			if (listitem == 1) // CMD: crmenu -> Заказать товар -> Узнать местоположение товара
			{
				new crime_character_id = character_data[playerid][c_id],
					storage_id_exist = GetCrimeBuyStorageIndexByPlayer(crime_index, crime_character_id);
				
				if (storage_id_exist == INVALID_PARAM)
				{
					pformat:("" #ERROR " У Вас нет активных заказов.");
					psend:(playerid, C_WHITE);
					
					ShowCrimeBuy(playerid);
					return 1;
				}
				
				new storage_location_exist = crbuy_storage[crime_index][storage_id_exist][cr_buy_location_index];
				
				if (storage_location_exist == INVALID_PARAM)
				{
					storage_location_exist = GetCrimBuyFreeLocationIndex();
				
					if (storage_location_exist == INVALID_PARAM)
					{
						pformat:("" #ERROR " Все локации получения товара заняты. Подождите пока одна из локаций освободится.");
						psend:(playerid, C_WHITE);
						
						ShowCrimeBuy(playerid);
						return 1;
					}
					
					crbuy_storage[crime_index][storage_id_exist][cr_buy_location_index] = storage_location_exist;
					
					crbuy_location[storage_location_exist][cr_loc_status] = true;
				}
				
				new Float: x = crbuy_location[storage_location_exist][cr_loc_x],
					Float: y = crbuy_location[storage_location_exist][cr_loc_y],
					Float: z = crbuy_location[storage_location_exist][cr_loc_z];
				
				SetPlayerCheckpoint(playerid, x, y, z, 2);
				
				pformat:("" #SUCCESS " Чекпоинт успешно установлен. Проследуйте на точку получения товара.");
				psend:(playerid, C_WHITE);
				
				if (crbuy_storage[crime_index][storage_id_exist][cr_buy_timer] == INVALID_PARAM) //!crbuy_storage[crime_index][storage_id_exist][cr_buy_3d_label])
				{
					crbuy_storage[crime_index][storage_id_exist][cr_buy_3d_label] = CreateDynamic3DTextLabel("N", C_WHITE, x, y, z, 10.0);
				}
				
				if (crbuy_storage[crime_index][storage_id_exist][cr_buy_timer] == INVALID_PARAM)
				{
					crbuy_storage[crime_index][storage_id_exist][cr_buy_timer] = 
						SetTimerEx("OnCrimeStorageTimerPast", MAX_CRIME_STORAGE_TIMER, false, "iiii", playerid, crime_index, storage_id_exist, storage_location_exist)
					;
					
					pformat:("" #SUCCESS " У Вас есть " #cPROJECT "%d" #cWHITE " минут чтобы забрать товар пока он не пропал.", GetCrimeTimerForMinute(MAX_CRIME_STORAGE_TIMER));
					psend:(playerid, C_WHITE);
				}
				
				return 1;
			}
			
			if (listitem == 2) // CMD: crmenu -> Заказать товар -> Оружейный арсенал
			{	
				SetPVarInt(playerid, "Crime:BuyDialogSelect", D_CRIME_BUY_WEAPON);
				SetPVarInt(playerid, "Crime:BuyCategorySelect", CR_BUY_CAT_WEAPON);
				
				ShowCrimeBuyList(playerid, D_CRIME_BUY_WEAPON, CR_BUY_CAT_WEAPON); // D_CRIME_BUY_WEAPON
				return 1;
			}
			
			if (listitem == 3) // CMD: crmenu -> Заказать товар -> Боеприпасы
			{
				SetPVarInt(playerid, "Crime:BuyDialogSelect", D_CRIME_BUY_AMMO);
				SetPVarInt(playerid, "Crime:BuyCategorySelect", CR_BUY_CAT_AMMO);
				
				ShowCrimeBuyList(playerid, D_CRIME_BUY_AMMO, CR_BUY_CAT_AMMO); // D_CRIME_BUY_AMMO
				return 1;
			}
			
			if (listitem == 4) // CMD: crmenu -> Заказать товар -> Наркотические вещества
			{
				SetPVarInt(playerid, "Crime:BuyDialogSelect", D_CRIME_BUY_DRUGS);
				SetPVarInt(playerid, "Crime:BuyCategorySelect", CR_BUY_CAT_DRUGS);
			
				ShowCrimeBuyList(playerid, D_CRIME_BUY_DRUGS, CR_BUY_CAT_DRUGS); // D_CRIME_BUY_DRUGS
				return 1;
			}
		}
		
		case D_CRIME_BUY_INFORMATION:
		{
			ShowCrimeBuy(playerid);
		}
		
		case D_CRIME_BUY_WEAPON:
		{
			if (!response)
			{
				DeletePVar(playerid, "Crime:BuyDialogSelect");
				DeletePVar(playerid, "Crime:BuyCategorySelect");
			
				ShowCrimeBuy(playerid);
				return 1;
			}
			
			listitem += GetCrimeBuyIndexToCategory(CR_BUY_CAT_WEAPON);
			
			SetPVarInt(playerid, "Crime:BuySelect", listitem);
			ShowCrimeBuyConfirm(playerid, listitem); // D_CRIME_BUY_CONFIRM
		}
		
		case D_CRIME_BUY_AMMO:
		{
			if (!response)
			{
				DeletePVar(playerid, "Crime:BuyDialogSelect");
				DeletePVar(playerid, "Crime:BuyCategorySelect");
			
				ShowCrimeBuy(playerid);
				return 1;
			}
			
			listitem += GetCrimeBuyIndexToCategory(CR_BUY_CAT_AMMO);
			
			SetPVarInt(playerid, "Crime:BuySelect", listitem);
			ShowCrimeBuyConfirm(playerid, listitem);
		}
		
		case D_CRIME_BUY_DRUGS:
		{
			if (!response)
			{
				DeletePVar(playerid, "Crime:BuyDialogSelect");
				DeletePVar(playerid, "Crime:BuyCategorySelect");
			
				ShowCrimeBuy(playerid);
				return 1;
			}
			
			listitem += GetCrimeBuyIndexToCategory(CR_BUY_CAT_DRUGS);
			
			SetPVarInt(playerid, "Crime:BuySelect", listitem);
			ShowCrimeBuyConfirm(playerid, listitem);
		}
		
		case D_CRIME_BUY_CONFIRM:
		{
			new crdialog = GetPVarInt(playerid, "Crime:BuyDialogSelect"),
				crcategory = GetPVarInt(playerid, "Crime:BuyCategorySelect"),
				crime_index = GetCrimeMember(playerid),
				crbuyselect = GetPVarInt(playerid, "Crime:BuySelect"),
				critemid = GetItemIndexById(crbuy_data[crbuyselect][cr_buy_item_id]),
				crime_character_id = character_data[playerid][c_id],
				storage_id_exist = GetCrimeBuyStorageIndexByPlayer(crime_index, crime_character_id);
		
			if (!response)
			{
				DeletePVar(playerid, "Crime:BuySelect");
			
				ShowCrimeBuyList(playerid, crdialog, crcategory);
				return 1;
			}
			
			if (crbuy_data[crbuyselect][cr_buy_access_type] > crime_data[crime_index][cr_type_id] // Проверка на доступ к товару по типу фракции
			|| crime_data[crime_index][cr_money] < crbuy_data[crbuyselect][cr_buy_count] // Проверка на наличие средств для покупки товара
			)
			{
				DeletePVar(playerid, "Crime:BuySelect");
				
				pformat:("" #ERROR " Недоступно для данного типа организации либо не хватает средств.");
				psend:(playerid, C_WHITE);
			
				ShowCrimeBuyList(playerid, crdialog, crcategory);
				return 1;
			}
			
			if (storage_id_exist == INVALID_PARAM)
			{
				storage_id_exist = GetCrimeBuyStorageFreeIndex(crime_index);
			
				if (storage_id_exist == INVALID_PARAM)
				{
					pformat:("" #ERROR " Превышен лимит закупок для фракции. Подождите пока участники Вашей организации заберут свой товар.");
					psend:(playerid, C_WHITE);
				
					DeletePVar(playerid, "Crime:BuySelect");
			
					ShowCrimeBuyList(playerid, crdialog, crcategory);
					return 1;
				}
				
				crbuy_storage[crime_index][storage_id_exist][cr_buy_customer_id] = crime_character_id;
			}
			
			if (crbuy_storage[crime_index][storage_id_exist][cr_buy_location_index] != INVALID_PARAM)
			{
				pformat:("" #ERROR " Невозможно сделать новый заказ. Товар с прошлого заказа не был подобран.");
				psend:(playerid, C_WHITE);
				
				DeletePVar(playerid, "Crime:BuySelect");
				
				ShowCrimeBuyList(playerid, crdialog, crcategory);
				return 1;
			}
			
			crbuy_storage[crime_index][storage_id_exist][cr_buy_item_storage][crbuyselect] += 1;
			
			new count = crime_data[crime_index][cr_money] - crbuy_data[crbuyselect][cr_buy_count],
				id = crime_data[crime_index][cr_id];
			
			Update:crime_money(count, id);
			
			crime_data[crime_index][cr_money] = count;
			
			pformat:("\
				" #SUCCESS " Вы успешно приобрели " #cPROJECT "%s" #cWHITE ", товар добавлен на точку подбора.",
				GetInventoryItemName(critemid)
			);
			psend:(playerid, C_WHITE);
			
			DeletePVar(playerid, "Crime:BuySelect");
			
			ShowCrimeBuyList(playerid, crdialog, crcategory);
		}
		
		case D_CRIME_BUY_STORAGE:
		{
			if (!response)
			{
				return 1;
			}
			
			new crime_index = GetCrimeMember(playerid),
				crime_character_id = character_data[playerid][c_id],
				storage_id_exist = GetCrimeBuyStorageIndexByPlayer(crime_index, crime_character_id),
				id = INVALID_PARAM,
				storage_product_index = INVALID_PARAM;
				
			
			for (new i, access; i < MAX_CRIME_BUY; i++)
			{
				if (crbuy_storage[crime_index][storage_id_exist][cr_buy_item_storage][i] > 0)
				{
					if (access != listitem)
					{
						access++;
						
						continue;
					}
					
					storage_product_index = i;
					
					id = crbuy_data[i][cr_buy_item_id];
					
					break;
				}
			}
			
			SetPVarInt(playerid, "Crime:StorageItemListIndex", id);
			SetPVarInt(playerid, "Crime:StorageProductIndex", storage_product_index);
			
			ShowCrimeBuyStorageConfirm(playerid, GetItemIndexById(id)); // D_CRIME_BUY_STORAGE_CONFIRM
		}
		
		case D_CRIME_BUY_STORAGE_CONFIRM:
		{
			new crime_index = GetCrimeMember(playerid),
				crime_character_id = character_data[playerid][c_id],
				storage_id_exist = GetCrimeBuyStorageIndexByPlayer(crime_index, crime_character_id);
				
			
			if (!response)
			{
				DeletePVar(playerid, "Crime:StorageItemListIndex");
				DeletePVar(playerid, "Crime:StorageProductIndex");
			
				ShowCrimeBuyStorage(playerid, crime_index, storage_id_exist);
				return 1;
			}
			
			new storage_location_exist = crbuy_storage[crime_index][storage_id_exist][cr_buy_location_index],
				id = GetPVarInt(playerid, "Crime:StorageItemListIndex"),
				storage_product_index = GetPVarInt(playerid, "Crime:StorageProductIndex"),
				product_status = GetItemIndexById(id),
				product_exist = INVALID_PARAM;
			
			
			product_status = GiveInventoryItem(playerid, id, crbuy_data[storage_product_index][cr_buy_value], TYPE_INV_PLAYER);
			
			
			if (product_status == INVALID_PARAM)
			{
				pformat:("" #ERROR " Не хватает места в инвентаре.");
				psend:(playerid, C_WHITE);
				
				DeletePVar(playerid, "Crime:StorageItemListIndex");
				DeletePVar(playerid, "Crime:StorageProductIndex");
				
				return 1;
			}
			
			crbuy_storage[crime_index][storage_id_exist][cr_buy_item_storage][storage_product_index] -= 1;
			
			if (crbuy_storage[crime_index][storage_id_exist][cr_buy_item_storage][storage_product_index] > 0)
			{
				DeletePVar(playerid, "Crime:StorageItemListIndex");
				DeletePVar(playerid, "Crime:StorageProductIndex");
				
				ShowCrimeBuyStorage(playerid, crime_index, storage_id_exist);
				return 1;
			}
			
			for (new i; i < MAX_CRIME_BUY; i++)
			{
				if (crbuy_storage[crime_index][storage_id_exist][cr_buy_item_storage][i] > 0)
				{
					product_exist = i;
				
					break;
				}
			}
			
			if (product_exist > INVALID_PARAM)
			{
				DeletePVar(playerid, "Crime:StorageItemListIndex");
				DeletePVar(playerid, "Crime:StorageProductIndex");
				
				ShowCrimeBuyStorage(playerid, crime_index, storage_id_exist);
				return 1;
			}
			
			KillTimer(crbuy_storage[crime_index][storage_id_exist][cr_buy_timer]);
			
			crbuy_location[storage_location_exist][cr_loc_status] = false;
			
			DestroyDynamic3DTextLabel(crbuy_storage[crime_index][storage_id_exist][cr_buy_3d_label]);
			
			DisablePlayerCheckpoint(playerid);
			
			DeletePVar(playerid, "Crime:StorageItemListIndex");
			DeletePVar(playerid, "Crime:StorageProductIndex");
			
			Clear:crbuy_storage(crime_index);
			//Clear:crbuy_storage_to_player(crime_index, storage_id_exist);
		}
	}
	
	return 1;
}