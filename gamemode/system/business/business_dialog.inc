/*!
	@brief Диалоги для системы бизнесов
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
					SendClientMessage(playerid, C_WHITE, !#ERROR " Вы уже являетесь участником компании. Для того, чтобы покинуть компанию, используйте " #cPROJECT "/bleave" #cWHITE ".");
					return 1;
				}
				
				if (!GetPlayerAvaibleBusiness(playerid))
				{
					SendClientMessage(playerid, C_WHITE, #ERROR " Вы не можете открыть больше компаний.");
					return 1;
				}
				
				if (GetPlayerPremisesCount(playerid) == 0)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас отсутствуют помещения.");
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_BUSINESS + 1, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Зарегистрировать компанию\n\n\
					Введите название будущей компании:\n\n\
					" #cGRAY "Название должно быть написано на латинских буквах и цифрах.\n\
					Длина названия не должна быть меньше 3 символов и больше, чем 32 символа",
					"Далее", "Назад" 
				);
				
				return 1;
			}
			
			listitem--;
			
			SetPVarInt(playerid, "Business:Select", g_dialog_select[playerid][listitem]);
			
			ShowPlayerDialog(playerid, D_BUSINESS + 3, DIALOG_STYLE_LIST, " ", 
				DIALOG_BUSINESS_MENU,
				"Далее", "Назад"
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
					"" #DEFAULT " Зарегистрировать компанию\n\n\
					Введите название будущей компании:\n\n\
					" #cRED "Название должно быть написано на латинских буквах и цифрах.\n\
					Длина названия не должна быть меньше 3 символов и больше, чем 32 символа",
					"Далее", "Назад" 
				);
				
				return 1;
			}
			
			SetPVarString(playerid, "Business:CreateName", inputtext);
			ShowPlayerDialog(playerid, D_BUSINESS + 2, DIALOG_STYLE_TABLIST_HEADERS, 
				" ", 
				DIALOG_BUSINESS_TYPE, 
				"Выбрать", "Назад" 
			);
		}
		
		case D_BUSINESS + 2 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 1, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Зарегистрировать компанию\n\n\
					Введите название будущей компании:\n\n\
					" #cGRAY "Название должно быть написано на латинских буквах и цифрах.\n\
					Длина названия не должна быть меньше 3 символов и больше, чем 32 символа",
					"Далее", "Назад" 
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
				SendClientMessage(playerid, C_WHITE, !#ERROR " Для того, чтобы создать компанию, необходимо иметь в наличии помещения.");
				DeletePVar(playerid, "Business:CreateName");
				return 1;
			}
			
			new index = GetFreeIndexForBusiness();
			
			if (index == INVALID_PARAM)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Превышен лимит компаний, Вы не можете создать компанию.");
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
			
			if (listitem == 0) // Информация
			{
				ShowBusinessInformation(playerid, index, D_BUSINESS + 4);
			}
			else // Закрыть компанию
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 5, DIALOG_STYLE_MSGBOX, " ", 
					"" #DEFAULT " Закрыть компанию\n\n\
					Вы действительно желаете закрыть компанию?",
					"Далее", "Назад"
				);
			}
		}
		
		case D_BUSINESS + 4 :
		{
			ShowPlayerDialog(playerid, D_BUSINESS + 3, DIALOG_STYLE_LIST, " ", 
				DIALOG_BUSINESS_MENU,
				"Далее", "Назад"
			);
		}
		
		case D_BUSINESS + 5 :
		{
			if (response)
			{
				Remove:business_data(playerid, GetPVarInt(playerid, "Business:Select"));
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно закрыли компанию.");
				
				ShowBusinessList(playerid);
			}
			else 
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 3, DIALOG_STYLE_LIST, " ", 
					DIALOG_BUSINESS_MENU,
					"Далее", "Назад"
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
			ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "Далее", "Назад");
		}
		
		case D_BUSINESS + 7 :
		{
			if (!response)
			{
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Business:Select");
			
			if (listitem == 0) /// Информация
			{
				ShowBusinessInformation(playerid, index, D_BUSINESS + 8);
			}
			else if (listitem == 1) /// Помещения
			{	
				if (!CheckBusinessAccess(TYPE_BUSINESS_OWNER, playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					cmd_bmenu(playerid);
					return 1;
				}
				
				ShowPremiseList(playerid, D_BUSINESS + 9, _, "Назад", 3);
			}
			else if (listitem == 2) /// Персонал
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
					DIALOG_BUSINESS_STAFF,
					"Выбрать", "Назад" 
				);
			}
			else if (listitem == 3) /// Настройки
			{
				if (!CheckBusinessAccess(TYPE_BUSINESS_OWNER, playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					cmd_bmenu(playerid);
					return 1;
				}
				
				if (business_data[index][b_type] == (sizeof business_type - 1))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Данный тип компании не подразумевает использование данного раздела.");
					return 1;
				}
				
				ShowBusinessSettings(playerid, index);
			}
			else if (listitem == 4) /// Финансы
			{
				if (!CheckBusinessAccess(TYPE_BUSINESS_OWNER, playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					cmd_bmenu(playerid);
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_BUSINESS + 18, DIALOG_STYLE_LIST, " ", 
					" Перевести средства компании на карту\n \
					Положить средства на счет компании",
					"Далее", "Назад"
				);
			}
		}
		
		case D_BUSINESS + 8 :
		{
			ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "Далее", "Назад");
		}
		
		case D_BUSINESS + 9 :
		{
			if (!response)
			{
				DeletePVar(playerid, "Time:PremiseUntie");
				ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "Далее", "Назад");
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Business:Select"),
				prindex = g_dialog_select[playerid][listitem],
				server_tick = GetTickCount();
			
			if (GetPVarInt(playerid, "Time:PremiseUntie") > server_tick)
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
				ShowPremiseList(playerid, D_BUSINESS + 9, _, "Назад", 3);
				return 1;
			}
			
			if (!IsPremiseTied(prindex))
			{
				PremiseTie(prindex, index);
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно привязали помещение к компании.");
			}
			else 
			{
				PremiseUntie(prindex, index);
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно отвязали помещение от компании.");
			}
			
			ShowPremiseList(playerid, D_BUSINESS + 9, _, "Назад", 3);
			SetPVarInt(playerid, "Time:PremiseUntie", server_tick + 5000);
		}
		
		case D_BUSINESS + 10 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "Далее", "Назад");
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Business:Select");
			
			if (listitem == 0) /// Принять
			{
				if (!CheckBusinessAccess(TYPE_BUSINESS_MEMBER, playerid, index, bm_perm_invite))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
						DIALOG_BUSINESS_STAFF,
						"Выбрать", "Назад" 
					);
					
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_BUSINESS + 11, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Принять в компанию\n\n\
					Введите ID игрока, которого Вы хотите принять в компанию:\n\n\
					" #cGRAY "Игрок должен находится неподалеку от Вас.",
					"Далее", "Назад"
				);
			}
			else if (listitem == 1) /// Исключить
			{
				if (!CheckBusinessAccess(TYPE_BUSINESS_MEMBER, playerid, index, bm_perm_uninvite))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
						DIALOG_BUSINESS_STAFF,
						"Выбрать", "Назад" 
					);
					
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_BUSINESS + 13, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Исключить из компании\n\n\
					Введите ID игрока, которого Вы хотите исключить из компанию:",
					"Далее", "Назад"
				);
			}
			else if (listitem == 2) // Изменить привилегии
			{
				if (!CheckBusinessAccess(TYPE_BUSINESS_MEMBER, playerid, index, bm_perm_change))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
						DIALOG_BUSINESS_STAFF,
						"Выбрать", "Назад" 
					);
					
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_BUSINESS + 14, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Изменить привилегии\n\n\
					Введите ID игрока, у которого Вы хотите изменить привилегии:",
					"Далее", "Назад"
				);
			}
			else if (listitem == 3) // Список всех сотрудников
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
					"Выбрать", "Назад" 
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
					"" #DEFAULT " Принять в компанию\n\n\
					Введите ID игрока, которого Вы хотите принять в компанию:\n\n\
					" #cGRAY "Игрок должен находится неподалеку от Вас.\n\
					" #cRED "Вы ввели неверный ID игрока.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			if (IsBusinessMember(targetid))
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 11, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Принять в компанию\n\n\
					Введите ID игрока, которого Вы хотите принять в компанию:\n\n\
					" #cGRAY "Игрок должен находится неподалеку от Вас.\n\
					" #cRED "Данный игрок уже состоит в компании.",
					"Далее", "Назад"
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
					SendClientMessage(playerid, C_WHITE, !#ERROR " Игрок, выславший предложение, вышел с сервера.");
					return 1;
				}
				
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " принял Ваше приглашение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
				
				SendClientMessage(ownerid, C_WHITE, !#DEFAULT " Для настройки доступа перейдите в " #cGRAY "Персонал" #cWHITE ".");
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы приняли приглашение.");
				
				Create:bmember_data(playerid, index);
				
				format:g_small_string("// \"%s\" > %s вступил в компанию по приглашению от %s.",
					GetBusinessName(index),
					GetPlayerCurrentName(playerid),
					GetPlayerCurrentName(ownerid)
				);
				
				SendBusinessMessage(index, C_PROJECT, g_small_string);
			}
			else 
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " отклонил Ваше приглашение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы отклонили приглашение.");
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
					"Выбрать", "Назад" 
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
					"" #DEFAULT " Исключить из компании\n\n\
					Введите ID игрока, которого Вы хотите исключить из компанию:\n\
					" #cRED "Вы ввели неверный ID игрока.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			if (index != GetBusinessMember(targetid))
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 13, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Исключить из компании\n\n\
					Введите ID игрока, которого Вы хотите исключить из компанию:\n\n\
					" #cRED "Данный игрок не состоит в Вашей компании.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			Remove:bmember_data(GetCharacterId(targetid), targetid);
			
			pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " уволил Вас из компании " #cPROJECT "%s" #cWHITE ".",
				GetPlayerCurrentName(playerid),
				GetBusinessName(index)
			);
			
			psend:(targetid, C_WHITE);
			
			format:g_small_string("// \"%s\" > %s уволил из компании %s.",
				GetBusinessName(index),
				GetPlayerCurrentName(playerid),
				GetPlayerCurrentName(targetid)
			);
			
			SendBusinessMessage(index, C_PROJECT, g_small_string);
			
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы успешно исключили игрока из компании.");
		}
		
		case D_BUSINESS + 14 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
					DIALOG_BUSINESS_STAFF,
					"Выбрать", "Назад" 
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
					"" #DEFAULT " Изменить привилегии\n\n\
					Введите ID игрока, у которого Вы хотите изменить привилегии:\n\n\
					" #cRED "Вы ввели неверный ID игрока.",
					"Далее", "Назад"
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
					"Выбрать", "Назад" 
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
					"Выбрать", "Назад" 
				);
				
				DeletePVar(playerid, "Business:MemberListPage");
				DeletePVar(playerid, "Business:CountMemberList");
				return 1;
			}
			
			if (bmember_select[playerid][listitem][bs_character_id] == GetCharacterId(playerid))
			{
				ShowBusinessMembers(playerid, index);
				pformat:("" #ERROR " Вы не можете выбрать своего персонажа.");
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
					pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " исключил Вас из компании " #cPROJECT "%s" #cWHITE ".",
						GetPlayerCurrentName(playerid),
						GetBusinessName(index)
					);
					
					psend:(targetid, C_WHITE);
					
					format:g_small_string("// \"%s\" > %s исключил из компании %s.",
						GetBusinessName(index),
						GetPlayerCurrentName(playerid),
						GetPlayerCurrentName(targetid)
					);
					
					SendBusinessMessage(index, C_PROJECT, g_small_string);
				}
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы успешно исключили игрока из компании.");
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
				ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "Далее", "Назад");
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Business:Select");
			
			if (listitem == 0)
			{
				format:g_string("" #DEFAULT " Перевести средства компании на карту\n\n\
				Средства компании: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму, которую Вы хотите снять на карту:",
					GetBusinessProfit(index)
				);
				
				ShowPlayerDialog(playerid, D_BUSINESS + 19, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
			}
			else
			{
				format:g_string("" #DEFAULT " Положить средства на счет компании\n\n\
				Средства компании: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму, которую Вы хотите положить на счет компании:",
					GetBusinessProfit(index)
				);
				
				ShowPlayerDialog(playerid, D_BUSINESS + 20, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
			}
			
		}
		
		case D_BUSINESS + 19 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 18, DIALOG_STYLE_LIST, " ", 
					" Перевести средства компании на карту\n \
					Положить средства на счет компании",
					"Далее", "Назад"
				);
			
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Business:Select"),
				value = strval(inputtext);
			
			if (!(0 < value <= GetBusinessProfit(index)))
			{
				format:g_string("" #DEFAULT " Перевести средства компании на карту\n\n\
				Средства компании: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму, которую Вы хотите снять на карту:\n\n\
				" #cRED "Вы ввели неверную сумму.",
					GetBusinessProfit(index)
				);
				
				ShowPlayerDialog(playerid, D_BUSINESS + 19, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
				return 1;
			}
			
			GiveDebitCardMoney(playerid, value);
			business_data[index][b_profit] -= value;
			Update:business_int(index, "b_profit", business_data[index][b_profit]);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно перевели средства компании на карту.");
			
			ShowPlayerDialog(playerid, D_BUSINESS + 18, DIALOG_STYLE_LIST, " ", 
				" Перевести средства компании на карту\n \
				Положить средства на счет компании",
				"Далее", "Назад"
			);
		}
		
		case D_BUSINESS + 20 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 18, DIALOG_STYLE_LIST, " ", 
					" Перевести средства компании на карту\n \
					Положить средства на счет компании",
					"Далее", "Назад"
				);
			
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Business:Select"),
				value = strval(inputtext);
			
			if (!(0 < value <= GetCharacterCardBalance(playerid)))
			{
				format:g_string("" #DEFAULT " Положить средства на счет компании\n\n\
				Средства компании: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму, которую Вы хотите положить на счет:\n\n\
				" #cRED "Вы ввели неверную сумму.",
					GetBusinessProfit(index)
				);
				
				ShowPlayerDialog(playerid, D_BUSINESS + 20, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
				return 1;
			}
			
			GiveDebitCardMoney(playerid, -value);
			business_data[index][b_profit] += value;
			Update:business_int(index, "b_profit", business_data[index][b_profit]);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно положили средства на счет компании.");
			
			ShowPlayerDialog(playerid, D_BUSINESS + 18, DIALOG_STYLE_LIST, " ", 
				" Перевести средства компании на карту\n \
				Положить средства на счет компании",
				"Далее", "Назад"
			);
		}
		
		case D_BUSINESS + 21 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "Далее", "Назад");
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
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно изменили деятельность. Старая продукция была полностью обнулена.");
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
					SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас уже заполнен ассортимент.");
					return 1;
				}
				
				AssortmentAddForBusiness(playerid, index);
				return 1;
			}
			
			listitem--;
			SetPVarInt(playerid, "BusinessAssort:Select", g_dialog_select[playerid][listitem]);
			ShowPlayerDialog(playerid, D_BUSINESS + 26, DIALOG_STYLE_LIST, " ", 
				" Изменить цену\n \
				  Удалить продукцию",
				"Далее", "Назад" 
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
				SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас уже находится данный предмет в ассортименте.");
				DeletePVar(playerid, "BusinessAssort:AddIndex");
				return 1;
			}
			
			Create:bassort_data(bindex, index);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно добавили данный товар в ассортименты.");
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
					" #DEFAULT " Изменить цену\n\n\
					Введите новую цену за товар:\n\n\
					" #cGRAY "Минимальная цена: " #cGREEN "$%i" #cGRAY ".\n\
					Максимальная цена: " #cGREEN "$%i" #cGRAY ".",
					GetMinBusinessAssortPrice(business_data[bindex][b_type], business_data[bindex][b_subtype], bassort_data[bindex][index][ba_item_id]),
					GetMaxBusinessAssortPrice(business_data[bindex][b_type], business_data[bindex][b_subtype], bassort_data[bindex][index][ba_item_id])
				);
					
					
				ShowPlayerDialog(playerid, D_BUSINESS + 27, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
			}
			else 
			{
				
				Remove:bassort_data(bindex, index);
				ShowBusinessSettingsAssortment(playerid, bindex);
				SendClientMessage(playerid, C_WHITE, !#ERROR " Вы успешно удалили данный товар из ассортимента.");
			}
		}
		
		case D_BUSINESS + 27 :
		{	
			new bindex = GetPVarInt(playerid, "Business:Select"),
				index = GetPVarInt(playerid, "BusinessAssort:Select"); 
			
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BUSINESS + 26, DIALOG_STYLE_LIST, " ", 
					" Изменить цену\n \
					  Удалить продукцию",
					"Далее", "Назад" 
				);
				return 1;
			}
			
			new value = strval(inputtext),
				item_id = bassort_data[bindex][index][ba_item_id];
			
			if (isnull(inputtext) 
			|| !(GetMinBusinessAssortPrice(business_data[bindex][b_type], business_data[bindex][b_subtype], item_id) <= value <= GetMaxBusinessAssortPrice(business_data[bindex][b_type], business_data[bindex][b_subtype], item_id)))
			{
				format:g_string("\
					" #DEFAULT " Изменить цену\n\n\
					Введите новую цену за товар:\n\n\
					" #cGRAY "Минимальная цена: " #cGREEN "$%i" #cGRAY ".\n\
					Максимальная цена: " #cGREEN "$%i" #cGRAY ".\n\
					" #cRED "Вы ввели неверную цену за товар.",
					GetMinBusinessAssortPrice(business_data[bindex][b_type], business_data[bindex][b_subtype], item_id),
					GetMaxBusinessAssortPrice(business_data[bindex][b_type], business_data[bindex][b_subtype], item_id)
				);
					
					
				ShowPlayerDialog(playerid, D_BUSINESS + 27, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
				return 1;
			}
			
			bassort_data[bindex][index][ba_cost] = value;
			Update:bassort_int(bindex, index, "ba_cost", value);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно обновили цену.");
			ShowPlayerDialog(playerid, D_BUSINESS + 26, DIALOG_STYLE_LIST, " ", 
				" Изменить цену\n \
				  Удалить продукцию",
				"Далее", "Назад" 
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
		ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "Далее", "Назад");
		SendClientMessage(playerid, C_WHITE, !#ERROR " Превышен максимальный лимит персонала.");
		return 1;
	}

	pformat:("" #SUCCESS " Вы отправили приглашение " #cPROJECT "%s" #cWHITE ".",
		GetPlayerCurrentName(targetid)
	);
	
	psend:(playerid, C_WHITE);
	
	ShowPlayerDialog(playerid, D_BUSINESS + 10, DIALOG_STYLE_LIST, " ",
		DIALOG_BUSINESS_STAFF,
		"Выбрать", "Назад" 
	);
	
	SetPVarInt(targetid, "Business:OwnerId", playerid);
	SetPVarInt(targetid, "Business:OwnerSelect", index);
	
	format:g_string("" #DEFAULT " Приглашение\n\n\
		Приглашение от " #cPROJECT "%s" #cWHITE ".\n\
		Вас приглашают стать сотрудником компании " #cPROJECT "%s" #cWHITE ".\n\
		Вы принимаете приглашение?",
		GetPlayerCurrentName(playerid),
		GetBusinessName(index)
	);
	
	ShowPlayerDialog(targetid, D_BUSINESS + 12, DIALOG_STYLE_MSGBOX, " ", g_string, "Да", "Нет");
	return 1;
}