/*!
	@brief Диалоги для системы фракций
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

Fraction_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{	
	switch (dialogid)
	{
		case D_FRACTION:
		{
			if (!response)
			{
				return 1;
			}
			
			new index = GetFractionMember(playerid),
				fraction_id = GetFractionMemberId(playerid);
			
			switch (listitem)
			{
				case 0: // Информация
				{
					ShowFractionInformation(playerid, index);
				}
				
				case 1: // Сотрудники
				{
					ShowFractionStaff(playerid);
				}
				
				case 2: // Подразделения
				{
					if (!CheckFractionAccess(playerid, fr_perm_set_rank))
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
						cmd_fmenu(playerid);
						return 1;
					}
				
					if (!ShowFractionUnits(playerid, D_FRACTION + 14, index, ""))
					{
						ShowPlayerDialog(playerid, D_FRACTION + 1, DIALOG_STYLE_MSGBOX, " ",
							"" #ERROR " Подразделения\n\n\
							Список подразделений отсутствует.",
							"Назад", ""
						);
					}
				}
				
				case 3: // Транспорт
				{
					ShowPlayerDialog(playerid, FRACTION_VEHICLE_DIALOG);
				}
				
				case 4: // Настройка
				{
					ShowPlayerDialog(playerid, FRACTION_SETTINGS_DIALOG);
				}
			}
			
			if (fraction_id == FRACTION_NEWS)
			{
				if (listitem == 5) // Управление эфиром
				{
					ShowFractionNewsEtherMenu(playerid);
				}
			}
		}
		
		case D_FRACTION + 1: // Информация
		{
			return cmd_fmenu(playerid);
		}
		
		case D_FRACTION + 2: // Сотрудники
		{
			if (!response)
			{
				cmd_fmenu(playerid);
				return 1;
			}

			if (listitem == 0) // Принять
			{
				if (!CheckFractionAccess(playerid, fr_perm_invite))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowFractionStaff(playerid);
					return 1;
				}
				
				ShowFractionStaffInvite(playerid);
			}
			else if (listitem == 1) // Уволить
			{
				if (!CheckFractionAccess(playerid, fr_perm_uninvite))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowFractionStaff(playerid);
					return 1;
				}
				
				ShowFractionStaffUninvite(playerid);
			}
			else if (listitem == 2) // Изменить ранг
			{
				if (!CheckFractionAccess(playerid, fr_perm_uninvite))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowFractionStaff(playerid);
					return 1;
				}
				
				ShowFractionStaffSetRank(playerid);
			}
			else if (listitem == 3) // Изменить подразделение
			{
				if (!CheckFractionAccess(playerid, fr_perm_uninvite))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowFractionStaff(playerid);
					return 1;
				}
				
				ShowFractionStaffSetUnit(playerid);
			}
			else if (listitem == 4) // Список всех сотрудников
			{	
				ShowFractionMembers(
					playerid, 
					D_FRACTION + 10, 
					GetFractionMember(playerid)
				);
			}
		}
		
		case D_FRACTION + 3: // Сотрудники: Принять игрока
		{
			if (!response)
			{
				ShowFractionStaff(playerid);
				return 1;
			}
			
			InviteFractionPlayer(playerid, inputtext, true);
		}
		
		case D_FRACTION + 4: // Сотрудники: Принять игрока -> Подтверждение
		{
			new memberid = GetPVarInt(playerid, "Fraction:InviteMemberId"),
				index = GetPVarInt(playerid, "Fraction:InviteMemberFractionIndex");
			
			if (response)
			{
				if (!IsPlayerLogged(memberid))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Игрок, выславший предложение, вышел с сервера.");
					return 1;
				}
				
				pformat:(#SUCCESS " " #cPROJECT "%s" #cWHITE " принял Ваше приглашение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(memberid, C_WHITE);
				
				// Подсказки
				SendClientMessage(memberid, C_WHITE, !#SUCCESS " Для установки ранга и подразделения перейдите в " #cGRAY "Сотрудники" #cWHITE ".");
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы приняли приглашение.");
				
				// Обновление данных
				character_data[playerid][c_fraction_index] = index;
				Update:character_int(playerid, "c_fraction_id", GetFractionId(index));
				
				if (fraction_data[index][fr_join_rank_id] != 0)
				{
					new rindex = GetFractionRankById(index, fraction_data[index][fr_join_rank_id]);
					character_data[playerid][c_fraction_rank_index] = rindex;
					Update:character_int(playerid, "c_fraction_rank_id", fraction_data[index][fr_join_rank_id]);
				}
				
				// Фракционное сообщение
				format:g_small_string(#FRACTION_MESSAGE " %s вступил в организацию по приглашению от %s.",
					GetPlayerCurrentName(playerid),
					GetPlayerCurrentName(memberid)
				);
				
				SendFractionMessage(index, g_small_string);
			}
			else 
			{
				pformat:(#ERROR " " #cPROJECT "%s" #cWHITE " отклонил Ваше приглашение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(memberid, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#ERROR " Вы отклонили приглашение.");
			}
			
			DeletePVar(playerid, "Fraction:InviteMemberId");
			DeletePVar(playerid, "Fraction:InviteMemberFractionIndex");
		}
		
		case D_FRACTION + 5: // Сотрудники: Уволить игрока
		{
			if (!response)
			{
				ShowFractionStaff(playerid);
				return 1;
			}
			
			UninviteFractionPlayer(playerid, inputtext, true);
		}
		
		case D_FRACTION + 6: // Сотрудники: Изменить ранг
		{
			if (!response)
			{
				ShowFractionStaff(playerid);
				return 1;
			}
			
			SetRank(playerid, inputtext, true);
		}
		
		case D_FRACTION + 7: // Сотрудники: Изменить ранг -> Выбор ранга
		{
			new bool: is_dialog = bool: GetPVarInt(playerid, "Fraction:IsDialogSetRank"),
				index = GetFractionMember(playerid);
			
			if (!response)
			{
				if (is_dialog)
				{
					ShowFractionStaffSetRank(playerid);
				}
				
				DeletePVar(playerid, "Fraction:IsDialogSetRank");
				return 1;
			}

			new	targetid = GetPVarInt(playerid, "Fraction:TargetId");
			
			if (listitem == 0)
			{
				ShowFractionRanks(playerid, dialogid, index);
				return 1;
			}
			
			listitem--;
			
			new rindex = g_dialog_select[playerid][listitem],
				rank_id = GetFractionRankId(playerid, rindex);
	
			character_data[targetid][c_fraction_rank_index] = rindex;
			Update:character_int(targetid, "c_fraction_rank_id", rank_id);
			
			new rank_name	[MAX_FRACTION_RANK_NAME];
	
			GetFractionRankName(targetid, rank_name);
			
			pformat:(#DEFAULT " " #cPROJECT "%s" #cWHITE " изменил ваш ранг на " #cPROJECT "%s" #cWHITE ".",
				GetPlayerCurrentName(playerid),
				rank_name
			);
			
			psend:(targetid, C_WHITE);
			
			pformat:(#SUCCESS " Вы успешно изменили ранг " #cPROJECT "%s" #cWHITE " на " #cPROJECT "%s" #cWHITE ".",
				GetPlayerCurrentName(targetid),
				rank_name
			);
			
			psend:(playerid, C_WHITE);
			
			if (is_dialog)
			{
				ShowFractionStaff(playerid);
			}
		}
		
		case D_FRACTION + 8: // Сотрудники: Изменить подразделение
		{
			if (!response)
			{
				ShowFractionStaff(playerid);
				return 1;
			}
			
			SetUnit(playerid, inputtext, true);
		}
		
		case D_FRACTION + 9: // Сотрудники: Изменить подразделение -> Выбор подразделения
		{
			new bool: is_dialog = bool: GetPVarInt(playerid, "Fraction:IsDialogSetUnit");
			
			if (!response)
			{
				if (is_dialog)
				{
					ShowFractionStaffSetUnit(playerid);
				}
				
				DeletePVar(playerid, "Fraction:IsDialogSetUnit");
				return 1;
			}

			new	index = GetFractionMember(playerid),
				targetid = GetPVarInt(playerid, "Fraction:TargetId");
			
			if (listitem == 0)
			{
				ShowFractionUnits(playerid, dialogid, index);
				return 1;
			}
			
			listitem--;
			
			new uindex = g_dialog_select[playerid][listitem],
				unit_id = GetFractionUnitId(playerid, uindex);
			
			character_data[targetid][c_fraction_unit_index] = uindex;
			Update:character_int(targetid, "c_fraction_unit_id", unit_id);
			
			pformat:(#DEFAULT " " #cPROJECT "%s" #cWHITE " изменил ваше подразделение на " #cPROJECT "%s" #cWHITE ".",
				GetPlayerCurrentName(playerid),
				GetFractionUnitName(targetid, uindex)
			);
			
			psend:(targetid, C_WHITE);
			
			pformat:(#SUCCESS " Вы успешно изменили подразделение " #cPROJECT "%s" #cWHITE " на " #cPROJECT "%s" #cWHITE ".",
				GetPlayerCurrentName(targetid),
				GetFractionUnitName(targetid, uindex)
			);
			
			psend:(playerid, C_WHITE);
			
			if (is_dialog)
			{
				ShowFractionStaff(playerid);
			}
		}
		
		case D_FRACTION + 10: // Сотрудники: Список всех сотрудников
		{
			if (!response)
			{
				ShowFractionStaff(playerid);
				return 1;
			}
			
			new index = GetFractionMember(playerid),
				action = g_dialog_select[playerid][listitem];
			
			if (action == ITEM_LIST_NEXT || action == ITEM_LIST_BACK)
			{
				ShowFractionMembers(
					playerid, 
					dialogid, 
					index, 
					action
				);
				
				return 1;
			}
			
			SetPVarInt(playerid, "Fraction:SelectMemberIndex", action);
			
			ShowFractionMemberSelect(playerid, action);
		}
		
		case D_FRACTION + 11: // Сотрудники: Список всех сотрудников > Управление сотрудником
		{
			if (response)
			{
				new index = GetPVarInt(playerid, "Fraction:SelectMemberIndex"),
					findex = GetFractionMember(playerid),
					targetid = GetPlayerIdByCharacterId(fraction_member_select[playerid][index][fr_id]);
				
				if (listitem == 0) // Уволить
				{
					if (CheckFractionAccess(playerid, fr_perm_uninvite)
					&& fraction_data[findex][fr_leader_id] != fraction_member_select[playerid][index][fr_id])
					{
						if (targetid == INVALID_PLAYER_ID)
						{
							format:g_string("UPDATE " #__CHARACTERS " \
								SET \
									c_fraction_id = 0, \
									c_fraction_rank_id = 0, \
									c_fraction_unit_id = 0 \
								WHERE c_id = %d",
								fraction_member_select[playerid][index][fr_id]
							);
							
							mysql_tquery(db, g_string);
						}
						else
						{
							UninvitePlayerFromFraction(playerid, targetid, true);
						}
					}
					else 
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					}
				}
				else if (listitem == 1) // Изменить ранг
				{	
					if (CheckFractionAccess(playerid, fr_perm_set_rank))
					{
						if (targetid == INVALID_PLAYER_ID)
						{
							ShowFractionRanks(
								playerid, 
								D_FRACTION + 12,
								GetFractionMember(playerid)
							);
						}
						else
						{
							SetPlayerFractionRank(playerid, targetid, true);
						}
						
						return 1;
					}
					else
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					}
				}
				else if (listitem == 2) // Изменить подразделение
				{
					if (CheckFractionAccess(playerid, fr_perm_set_unit))
					{
						if (targetid == INVALID_PLAYER_ID)
						{
							ShowFractionUnits(
								playerid, 
								D_FRACTION + 13,
								GetFractionMember(playerid)
							);
						}
						else
						{
							SetPlayerFractionUnit(playerid, targetid, true);
						}
						
						return 1;
					}
					else 
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					}
				}
			}
			
			ShowFractionMembers(
				playerid, 
				D_FRACTION + 10, 
				GetFractionMember(playerid), 
				ITEM_LIST_CURRENT
			);
		}
		
		case D_FRACTION + 12: // Сотрудники: Список всех сотрудников > Управление сотрудником > Изменить ранг
		{
			new mindex = GetPVarInt(playerid, "Fraction:SelectMemberIndex");
			
			if (response)
			{
				new	index = GetFractionMember(playerid);
				
				if (listitem == 0)
				{
					ShowFractionRanks(playerid, dialogid, index);
					return 1;
				}
				
				listitem--;
				
				new rindex = g_dialog_select[playerid][listitem],
					rank_id = GetFractionRankId(playerid, rindex);
		
				format:g_string("UPDATE " #__CHARACTERS " SET c_fraction_rank_id = %d WHERE c_id = %d",
					rank_id,
					fraction_member_select[playerid][mindex][fr_id]
				);
				
				mysql_tquery(db, g_string);
				
				new rank_name	[MAX_FRACTION_RANK_NAME];
	
				GetFractionRankName(playerid, rank_name);
			
				pformat:(#SUCCESS " Вы успешно изменили ранг " #cPROJECT "%s" #cWHITE " на " #cPROJECT "%s" #cWHITE ".",
					fraction_member_select[playerid][mindex][fr_name],
					rank_name
				);
				
				psend:(playerid, C_WHITE);
			}
			
			ShowFractionMemberSelect(playerid, mindex);
		}
		
		case D_FRACTION + 13: // Сотрудники: Список всех сотрудников > Управление сотрудником > Изменить подразделение
		{
			new mindex = GetPVarInt(playerid, "Fraction:SelectMemberIndex");
			
			if (response)
			{
				new	index = GetFractionMember(playerid);
				
				if (listitem == 0)
				{
					ShowFractionUnits(playerid, dialogid, index);
					return 1;
				}
				
				listitem--;
				
				format:g_string("UPDATE " #__CHARACTERS " SET c_fraction_unit_id = %d WHERE c_id = %d",
					fraction_unit_data[index][listitem][fr_id],
					fraction_member_select[playerid][mindex][fr_id]
				);
				
				mysql_tquery(db, g_string);
				
				pformat:(#SUCCESS " Вы успешно изменили подразделение " #cPROJECT "%s" #cWHITE " на " #cPROJECT "%s" #cWHITE ".",
					fraction_member_select[playerid][mindex][fr_name],
					GetFractionUnitName(playerid, listitem)
				);
				
				psend:(playerid, C_WHITE);
			}
			
			ShowFractionMemberSelect(playerid, mindex);
		}
		
		case D_FRACTION + 14: // Подразделения: Выбор подразделения
		{
			if (!response)
			{
				cmd_fmenu(playerid);
				return 1;
			}
			
			new index = GetFractionMember(playerid);
			ShowFractionUnitInformation(playerid, index, listitem, D_FRACTION + 15);
		}
		
		case D_FRACTION + 15: 
		{
			cmd_fmenu(playerid);
			return 1;
		}
		
		case D_FRACTION + 16: // Транспорт
		{
			if (!response)
			{
				cmd_fmenu(playerid);
				return 1;
			}
			
			if (listitem == 0) // Список транспорта
			{
				if (GetFractionLeader(playerid) == INVALID_PARAM)
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowPlayerDialog(playerid, FRACTION_VEHICLE_DIALOG);
					return 1;
				}
			
				ShowFractionVehicles(playerid, D_FRACTION + 17);
			}
			else if (listitem == 1) // Вернуть транспорт на парковочные места
			{
				if (!CheckFractionAccess(playerid, fr_perm_spawn_vehicle))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowPlayerDialog(playerid, FRACTION_VEHICLE_DIALOG);
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_FRACTION + 22, DIALOG_STYLE_MSGBOX, " ",
					"" #DEFAULT " Вернуть транспорт на парковычные места\n\n\
					Вы действительно хотите вернуть весь неиспользуемый транспорт на парковочные места?",
					"Да", "Нет"
				);
			}
		}
		
		case D_FRACTION + 17:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, FRACTION_VEHICLE_DIALOG);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowFractionVehicleAddModel(playerid);
				return 1;
			}
			
			listitem--;
			
			new action = g_dialog_select[playerid][listitem];
			
			if (action == ITEM_LIST_NEXT || action == ITEM_LIST_BACK)
			{
				ShowFractionVehicles(playerid, dialogid, action);
				return 1;
			}
			
			action = g_dialog_select[playerid][listitem];
			
			SetPVarInt(playerid, "Fraction:VehicleId", action);
			
			format:g_string(" "cRED "Удалить транспорт\n \
				%s" #cWHITE " сирену",
				vehicle_data[action][v_siren] ? (#cGRAY "Снять") : (#cPROJECT "Установить")
			);
			
			ShowPlayerDialog(playerid, D_FRACTION + 18, DIALOG_STYLE_LIST, " ", g_string, "Далае", "Назад");
		}
		
		case D_FRACTION + 18:
		{
			if (response)
			{
				new vehicleid = GetPVarInt(playerid, "Fraction:VehicleId");
				
				if (listitem == 0) // Удалить транспорт
				{
					Remove:vehicle_data(vehicleid);
					SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы успешно удалили транспорт организации.");
				}
				else if (listitem == 1) // Установить сирену
				{
					new server_tick = GetTickCount();
	
					if (GetPVarInt(playerid, "Fraction:SirenTime") > server_tick)
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
						return 0;
					}
					
					new id = vehicle_data[vehicleid][v_id];

					vehicle_data[vehicleid][v_siren] = !vehicle_data[vehicleid][v_siren];
					OnVehicleDestroy(INVALID_PLAYER_ID, vehicleid);
					Load:vehicle_by_id(id);
					
					SetPVarInt(playerid, "Fraction:SirenTime", server_tick + 1000);
				}
			}
			
			ShowFractionVehicles(playerid, D_FRACTION + 17, ITEM_LIST_CURRENT);
		}
		
		case D_FRACTION + 19:
		{
			if (!response)
			{
				ShowFractionVehicles(playerid, D_FRACTION + 17, ITEM_LIST_CURRENT);
				return 1;
			}
			
			new model = strval(inputtext);
			
			if (!(400 <= model <= 611))
			{
				ShowFractionVehicleAddModel(playerid, "Вы указали некорректный ID модели.");
				return 1;
			}
			
			SetPVarInt(playerid, "Fraction:VehicleAddModel", model);
			
			ShowFractionVehicleAddColor(playerid);
		}
		
		case D_FRACTION + 20:
		{
			if (!response)
			{
				ShowFractionVehicleAddModel(playerid);
				DeletePVar(playerid, "Fraction:VehicleAddModel");
				return 1;
			}
			
			new color1,
				color2;
				
			if (sscanf(inputtext, "p<,>dd", color1, color2))
			{
				ShowFractionVehicleAddColor(playerid, "Вы указали некорректное значение.");
				return 1;
			}
			
			if (!(0 <= color1 <= 255))
			{
				ShowFractionVehicleAddColor(playerid, "Вы указали неверный цвет 1.");
				return 1;
			}
			
			if (!(0 <= color2 <= 255))
			{
				ShowFractionVehicleAddColor(playerid, "Вы указали неверный цвет 2.");
				return 1;
			}
			
			SetPVarInt(playerid, "Fraction:VehicleAddColor1", color1);
			SetPVarInt(playerid, "Fraction:VehicleAddColor2", color2);
			
			ShowFractionVehicleAddNumber(playerid);
		}
		
		case D_FRACTION + 21:
		{
			if (!response)
			{
				ShowFractionVehicleAddColor(playerid);
				DeletePVar(playerid, "Fraction:VehicleAddColor1");
				DeletePVar(playerid, "Fraction:VehicleAddColor2");
				return 1;
			}
			
			if (isnull(inputtext) || !IsValidVehicleNumber(inputtext))
			{
				ShowFractionVehicleAddNumber(playerid, "Вы ввели некорректный номер.");
				return 1;
			}
			
			new fraction_id = GetFractionMemberId(playerid),
				model = GetPVarInt(playerid, "Fraction:VehicleAddModel"),
				color[2];
				
			new Float: pos[4];
			
			GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
			GetPlayerFacingAngle(playerid, pos[3]);
			
			color[0] = GetPVarInt(playerid, "Fraction:VehicleAddColor1");
			color[1] = GetPVarInt(playerid, "Fraction:VehicleAddColor2");
			
			Create:vehicle_data(
				TYPE_BUY_FULLY, 
				TYPE_VEH_FRACTION, 
				fraction_id, 
				model, 
				color, 
				pos,
				INVALID_PLAYER_ID,
				false,
				0,
				inputtext,
				GetCharacterInt(playerid),
				GetCharacterWorld(playerid)
			);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Транспорт для организации успешно создан.");
			ShowFractionVehicles(playerid, D_FRACTION + 17, ITEM_LIST_CURRENT);
			
			DeletePVar(playerid, "Fraction:VehicleAddColor1");
			DeletePVar(playerid, "Fraction:VehicleAddColor2");
			DeletePVar(playerid, "Fraction:VehicleAddModel");
		}
		
		case D_FRACTION + 22:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, FRACTION_VEHICLE_DIALOG);
				return 1;
			}
			
			new id = GetFractionMemberId(playerid);
			
			for (new i = 1, j = GetVehiclePoolSize(); i <= j; i++)
			{
				if (vehicle_data[i][v_owner_type] == TYPE_VEH_FRACTION
				&& vehicle_data[i][v_owner_id] == id
				&& !IsVehicleOccupied(i))
				{
					SetVehicleToRespawn(i);
				}
			}
			
			format:g_small_string(#FRACTION_MESSAGE " %s вернул неиспользуемый транспорт на парковочные места.",
				GetPlayerCurrentName(playerid)
			);
			
			SendFractionMessage(
				GetFractionMember(playerid), 
				g_small_string
			);
			
			ShowPlayerDialog(playerid, FRACTION_VEHICLE_DIALOG);
		}
		
		case D_FRACTION + 23: // Настройка
		{
			if (!response)
			{
				cmd_fmenu(playerid);
				return 1;
			}
			
			if (!CheckFractionAccess(playerid, fr_perm_manage))
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
				cmd_fmenu(playerid);
				return 1;
			}
			
			new index = GetFractionMember(playerid);
			
			if (listitem == 0) // Список рангов 
			{
				ShowFractionRanks(playerid, D_FRACTION + 24, index, #cGRAY "Добавить ранг\n");
			}
			else if (listitem == 1) // Список подразделений
			{
				ShowFractionUnits(playerid, D_FRACTION + 31, index, #cGRAY "Добавить подразделение\n");
			}
			else if (listitem == 2) // Ранг по умолчанию
			{
				ShowFractionJoinRank(playerid, index);
			}
		}
		
		case D_FRACTION + 24: // Настройка: Список рангов
		{
			new findex = GetFractionMember(playerid);
			
			if (!response)
			{
				ShowPlayerDialog(playerid, FRACTION_SETTINGS_DIALOG);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowFractionSettingsAddRank(playerid);
				return 1;
			}
			
			listitem--;
			
			new rindex = g_dialog_select[playerid][listitem];
			SetPVarInt(playerid, "Fraction:SelectRank", rindex);
			ShowFractionSettingsEditRank(playerid, findex, rindex);
		}
		
		case D_FRACTION + 25: // Настройка: Список рангов -> Добавление ранга
		{
			new findex = GetFractionMember(playerid);
			
			if (response)
			{
				if (isnull(inputtext))
				{
					ShowFractionSettingsAddRank(playerid, "Некорректное название ранга.");
					return 1;
				}
				
				if (strlen(inputtext) > MAX_FRACTION_RANK_NAME)
				{
					ShowFractionSettingsAddRank(playerid, "Превышен лимит символов на название.");
					return 1;
				}
				
				new index = GetFreeIndexForFractionRank(findex);

				if (index != INVALID_PARAM)
				{
					fraction_rank_data[findex][index][fr_id] = true;
					
					clean:<fraction_rank_data[findex][index][fr_name]>;
					strcat(fraction_rank_data[findex][index][fr_name], inputtext, MAX_FRACTION_RANK_NAME);
					fraction_rank_data[findex][index][fr_salary] = GetFractionMinSalary(findex);
		
					Create:fraction_rank_data(playerid, findex, index);
				}
				else 
				{
					ShowFractionSettingsAddRank(playerid, "Превышен лимит на создание рангов.");
				}
			}
			
			ShowFractionRanks(playerid, D_FRACTION + 24, findex, #cGRAY "Добавить ранг\n");
		}
		
		case D_FRACTION + 26: // Настройка: Список рангов -> Управление рангом
		{
			new findex = GetFractionMember(playerid),
				index = GetPVarInt(playerid, "Fraction:SelectRank");
			
			if (!response)
			{
				ShowFractionRanks(playerid, D_FRACTION + 24, findex, #cGRAY "Добавить ранг\n");
				return 1;
			}
			
			new value;

			if (listitem == 0) // Название
			{
				ShowFractionEditRankName(playerid);
				return 1;
			}
			else if (listitem == 1) // Заработная плата
			{
				ShowFractionEditRankSalary(playerid, findex);
				return 1;
			}
			else if (listitem == 2) // Возможность принимать во фракцию
			{
				value = fraction_rank_data[findex][index][fr_perm_invite] = !fraction_rank_data[findex][index][fr_perm_invite];
				Update:fraction_rank_int(findex, index, "fr_perm_invite", value);
			}
			else if (listitem == 3) // Возможность увольнять из фракции
			{
				value = fraction_rank_data[findex][index][fr_perm_uninvite] = !fraction_rank_data[findex][index][fr_perm_uninvite];
				Update:fraction_rank_int(findex, index, "fr_perm_uninvite", value);
			}
			else if (listitem == 4) // Изменение ранга
			{
				value = fraction_rank_data[findex][index][fr_perm_set_rank] = !fraction_rank_data[findex][index][fr_perm_set_rank];
				Update:fraction_rank_int(findex, index, "fr_perm_set_rank", value);
			}
			else if (listitem == 5) // Изменение подразделения
			{
				value = fraction_rank_data[findex][index][fr_perm_set_unit] = !fraction_rank_data[findex][index][fr_perm_set_unit];
				Update:fraction_rank_int(findex, index, "fr_perm_set_unit", value);
			}
			else if (listitem == 6) // Доступ к разделу настроек фракции
			{
				value = fraction_rank_data[findex][index][fr_perm_manage] = !fraction_rank_data[findex][index][fr_perm_manage];
				Update:fraction_rank_int(findex, index, "fr_perm_manage", value);
			}
			else if (listitem == 7) // Использовать частоты рации
			{
				value = fraction_rank_data[findex][index][fr_perm_radio] = !fraction_rank_data[findex][index][fr_perm_radio];
				Update:fraction_rank_int(findex, index, "fr_perm_radio", value);
			}
			else if (listitem == 8) // Доступ к объектам
			{
				value = fraction_rank_data[findex][index][fr_perm_object] = !fraction_rank_data[findex][index][fr_perm_object];
				Update:fraction_rank_int(findex, index, "fr_perm_object", value);
			}
			else if (listitem == 9) // Доступ к прикреплённым объектам
			{
				value = fraction_rank_data[findex][index][fr_perm_attach] = !fraction_rank_data[findex][index][fr_perm_attach];
				Update:fraction_rank_int(findex, index, "fr_perm_attach", value);
			}
			else if (listitem == 10) // Использование транспорта
			{
				value = fraction_rank_data[findex][index][fr_perm_vehicle] = !fraction_rank_data[findex][index][fr_perm_vehicle];
				Update:fraction_rank_int(findex, index, "fr_perm_vehicle", value);
			}
			else if (listitem == 11) // Использование служебной одежды
			{
				value = fraction_rank_data[findex][index][fr_perm_clothes] = !fraction_rank_data[findex][index][fr_perm_clothes];
				Update:fraction_rank_int(findex, index, "fr_perm_clothes", value);
			}
			else if (listitem == 12) // Доступ к предметам
			{
				value = fraction_rank_data[findex][index][fr_perm_items] = !fraction_rank_data[findex][index][fr_perm_items];
				Update:fraction_rank_int(findex, index, "fr_perm_items", value);
			}
			else if (listitem == 13) // Доступ к оружию
			{
				value = fraction_rank_data[findex][index][fr_perm_weapon] = !fraction_rank_data[findex][index][fr_perm_weapon];
				Update:fraction_rank_int(findex, index, "fr_perm_weapon", value);
			}
			else if (listitem == 14) // Вернуть транспорт на парковочное место
			{
				value = fraction_rank_data[findex][index][fr_perm_spawn_vehicle] = !fraction_rank_data[findex][index][fr_perm_spawn_vehicle];
				Update:fraction_rank_int(findex, index, "fr_perm_spawn_vehicle", value);
			}
			else if (listitem == 15) // Дополнительно
			{
				ShowFractionEditRankCustom(playerid, findex);
				return 1;
			}
			else if (listitem == 16) // Удалить ранг
			{
				ShowPlayerDialog(playerid, D_FRACTION + 29, DIALOG_STYLE_MSGBOX, " ",
					""#ERROR" Удаление ранга\n\n\
					Вы действительно хотите удалить данный ранг?",
					"Да", "Нет"
				);
				
				return 1;
			}
			
			ShowFractionSettingsEditRank(playerid, findex, index);
		}
		
		case D_FRACTION + 27: // Настройка: Список рангов -> Управление рангом -> Изменение названия
		{
			new findex = GetFractionMember(playerid),
				index = GetPVarInt(playerid, "Fraction:SelectRank");
				
			if (response)
			{
				if (isnull(inputtext))
				{
					ShowFractionSettingsAddRank(playerid, "Некорректное название ранга.");
					return 1;
				}
				
				if (strlen(inputtext) > MAX_FRACTION_RANK_NAME)
				{
					ShowFractionSettingsAddRank(playerid, "Превышен лимит символов на название.");
					return 1;
				}
				
				clean:<fraction_rank_data[findex][index][fr_name]>;
				strcat(fraction_rank_data[findex][index][fr_name], inputtext, MAX_FRACTION_RANK_NAME);
				Update:fraction_rank_string(findex, index, "fr_name", inputtext);
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно изменили имя для данного ранга.");
			}
			
			ShowFractionSettingsEditRank(playerid, findex, index);
		}
		
		case D_FRACTION + 28: // Настройка: Список рангов -> Управление рангом -> Изменение зарплаты
		{
			new findex = GetFractionMember(playerid),
				index = GetPVarInt(playerid, "Fraction:SelectRank");
				
			if (response)
			{
				new salary = strval(inputtext);
				
				if (!(GetFractionMinSalary(findex) <= salary <= GetFractionMaxSalary(findex)))
				{
					ShowFractionEditRankSalary(playerid, findex, "Вы указали неверное значение.");
					return 1;
				}
				
				fraction_rank_data[findex][index][fr_salary] = salary;
				Update:fraction_rank_int(findex, index, "fr_salary", salary);
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно изменили зарплату для данного ранга.");
			}
			
			ShowFractionSettingsEditRank(playerid, findex, index);
		}
		
		case D_FRACTION + 29: // Настройка: Список рангов -> Управление рангом -> Удаление ранга
		{
			new findex = GetFractionMember(playerid),
				index = GetPVarInt(playerid, "Fraction:SelectRank");
				
			if (!response)
			{
				ShowFractionSettingsEditRank(playerid, findex, index);
				return 1;
			}
			
			Remove:fraction_rank_data(findex, index);
			
			ShowFractionRanks(playerid, D_FRACTION + 24, findex, #cGRAY "Добавить ранг\n");
			SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы успешно удалили ранг.");
		}
		
		case D_FRACTION + 30: // Настройка: Список рангов -> Управление рангом -> Дополнительные доступы
		{
			new findex = GetFractionMember(playerid),
				index = GetPVarInt(playerid, "Fraction:SelectRank");
				
			ShowFractionSettingsEditRank(playerid, findex, index);
		}
		
		case D_FRACTION + 31: // Настройка: Список подразделений
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, FRACTION_SETTINGS_DIALOG);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowFractionAddUnit(playerid);
				return 1;
			}
			
			listitem--;
			
			new findex = GetFractionMember(playerid),
				uindex = g_dialog_select[playerid][listitem];
			
			SetPVarInt(playerid, "Fraction:SelectUnit", uindex);
			ShowFractionEditUnit(playerid, findex, uindex);
		}
		
		case D_FRACTION + 32: // Настройка: Список подразделений -> Добавление подразделения (название)
		{
			new index = GetFractionMember(playerid);
			
			if (!response)
			{
				ShowFractionUnits(playerid, D_FRACTION + 31, index, #cGRAY "Добавить подразделение\n");
				return 1;
			}
			
			if (isnull(inputtext))
			{
				ShowFractionAddUnit(playerid, "Некорректное название подразделения.");
				return 1;
			}
			
			if (strlen(inputtext) > MAX_FRACTION_NAME)
			{
				ShowFractionAddUnit(playerid, "Превышен лимит символов на название.");
				return 1;
			}
			
			SetPVarString(playerid, "Fraction:AddUnitName", inputtext);
			ShowFractionAddUnitAltName(playerid);
		}
		
		case D_FRACTION + 33: // Настройка: Список подразделений -> Добавление подразделения (сокращенное название)
		{
			new findex = GetFractionMember(playerid);
			if (response)
			{
				if (isnull(inputtext))
				{
					ShowFractionAddUnitAltName(playerid, "Некорректное название подразделения.");
					return 1;
				}
				
				if (strlen(inputtext) > MAX_FRACTION_ALT_NAME)
				{
					ShowFractionAddUnitAltName(playerid, "Превышен лимит символов на название.");
					return 1;
				}
				
				new index = GetFreeIndexForFractionUnit(findex);
				
				if (index != INVALID_PARAM)
				{
					fraction_unit_data[findex][index][fr_id] = true;
					
					clean:<g_small_string>;
					GetPVarString(playerid, "Fraction:AddUnitName", g_small_string, sizeof g_small_string);
					
					clean:<fraction_unit_data[findex][index][fr_name]>;
					strcat(fraction_unit_data[findex][index][fr_name], g_small_string, MAX_FRACTION_NAME);
					
					clean:<fraction_unit_data[findex][index][fr_alt_name]>;
					strcat(fraction_unit_data[findex][index][fr_alt_name], inputtext, MAX_FRACTION_ALT_NAME);
		
					Create:fraction_unit_data(playerid, findex, index);
				}
				else 
				{
					ShowFractionAddUnit(playerid, "Превышен лимит на создание подразделений.");
				}
			}
			
			ShowFractionUnits(playerid, D_FRACTION + 31, findex, #cGRAY "Добавить подразделение\n");
		}
		
		case D_FRACTION + 34: // Настройка: Список подразделений -> Управление подразделением
		{
			new findex = GetFractionMember(playerid),
				index = GetPVarInt(playerid, "Fraction:SelectUnit");
			
			if (!response)
			{
				ShowFractionUnits(playerid, D_FRACTION + 31, findex, #cGRAY "Добавить подразделение\n");
				return 1;
			}
			
			if (listitem == 0) // Название подразделения
			{
				ShowFractionEditUnitName(playerid);
			}
			else if (listitem == 1) // Сокращенное название подразделение
			{
				ShowFractionEditUnitAltName(playerid);
			}
			else if (listitem == 2) // Лидер
			{
				ShowFractionEditUnitLeader(playerid, findex, index);
			}
			else if (listitem == 3) // Одежда 
			{
				ShowFractionUnitSkins(playerid, findex, index);
			}
			else if (listitem == 4) // Место появления
			{
				ShowFractionUnitSpawn(playerid, findex, index);
			}
			else if (listitem == 5) // Удалить подразделение
			{
				ShowPlayerDialog(playerid, D_FRACTION + 42, DIALOG_STYLE_MSGBOX, " ",
					"" #DEFAULT " Удаление подразделения\n\n\
					Вы действительно хотите удалить данное подразделение?",
					"Да", "Нет"
				);
			}
		}
		
		case D_FRACTION + 35: // Настройка: Список подразделений -> Управление подразделением -> Изменить название
		{
			new findex = GetFractionMember(playerid),
				index = GetPVarInt(playerid, "Fraction:SelectUnit");
				
			if (response)
			{	
				if (isnull(inputtext))
				{
					ShowFractionEditUnitName(playerid, "Некорректное название подразделения.");
					return 1;
				}
				
				if (strlen(inputtext) > MAX_FRACTION_NAME)
				{
					ShowFractionEditUnitName(playerid, "Превышен лимит символов на название.");
					return 1;
				}
				
				clean:<fraction_unit_data[findex][index][fr_name]>;
				strcat(fraction_unit_data[findex][index][fr_name], inputtext, MAX_FRACTION_NAME);
				Update:fraction_unit_string(findex, index, "fr_name", fraction_unit_data[findex][index][fr_name]);
			
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно изменили имя подразделения.");
			}
			
			ShowFractionEditUnit(playerid, findex, index);
		}
		
		case D_FRACTION + 36: // Настройка: Список подразделений -> Управление подразделением -> Изменить сокращенное название
		{
			new findex = GetFractionMember(playerid),
				index = GetPVarInt(playerid, "Fraction:SelectUnit");
				
			if (response)
			{	
				if (isnull(inputtext))
				{
					ShowFractionEditUnitName(playerid, "Некорректное название подразделения.");
					return 1;
				}
				
				if (strlen(inputtext) > MAX_FRACTION_ALT_NAME)
				{
					ShowFractionEditUnitName(playerid, "Превышен лимит символов на название.");
					return 1;
				}
				
				clean:<fraction_unit_data[findex][index][fr_alt_name]>;
				strcat(fraction_unit_data[findex][index][fr_alt_name], inputtext, MAX_FRACTION_ALT_NAME);
				Update:fraction_unit_string(findex, index, "fr_alt_name", fraction_unit_data[findex][index][fr_alt_name]);
			
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно изменили сокращенное имя подразделения.");
			}
			
			ShowFractionEditUnit(playerid, findex, index);
		}
		
		case D_FRACTION + 37:
		{
			new findex = GetFractionMember(playerid),
				index = GetPVarInt(playerid, "Fraction:SelectUnit");
				
			if (response)
			{
				if (isnull(inputtext))
				{
					if (fraction_unit_data[findex][index][fr_leader_id] == 0)
					{
						ShowFractionEditUnitLeader(playerid, findex, index, "У данного подразделения отсутствует лидер.");
						return 1;
					}
					
					new bool: exists = false;
					
					foreach (new i : Player)
					{
						if (!IsPlayerLogged(playerid))
						{
							continue;
						}
						
						if (character_data[i][c_fraction_unit_leader_index] == index)
						{
							character_data[i][c_fraction_unit_leader_index] = 0;
		
							Update:fraction_unit_int(findex, index, "fr_leader_id", 0);
							exists = true;
							
							break;
						}
					}
					
					if (!exists)
					{
						format:g_string("\
							UPDATE " #__CHARACTERS " \
							SET \
								c_fraction_unit_id = 0 \
							WHERE c_id = %d",
							fraction_data[index][fr_leader_id]
						);
					}
					
					Update:fraction_int(index, "fr_leader_id", 0);
					
					fraction_unit_data[findex][index][fr_leader_id] = 0;
					clean:<fraction_unit_data[findex][index][fr_leader_name]>;
					
					SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы успешно сняли лидера фракции.");
					
					format:g_small_string(#FRACTION_MESSAGE " %s снял лидера с подразделения %s.",
						GetPlayerCurrentName(playerid),
						fraction_unit_data[findex][index][fr_name]
					);
					
					SendFractionMessage(findex, g_small_string);
					return 1;
				}

				Check:fraction_unit_leader(playerid, findex, index, inputtext);
			}
			
			ShowFractionEditUnit(playerid, findex, index);
		}
		
		case D_FRACTION + 38:
		{
			new findex = GetFractionMember(playerid),
				index = GetPVarInt(playerid, "Fraction:SelectUnit");
				
			if (!response)
			{
				ShowFractionEditUnit(playerid, findex, index);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowFractionUnitSkinsAdd(playerid);
				return 1;
			}
			
			listitem--;
			
			new skin = g_dialog_select[playerid][listitem];
			
			SetPVarInt(playerid, "Fraction:SelectSkin", skin);
			ShowPlayerDialog(playerid, D_FRACTION + 40, DIALOG_STYLE_LIST, " ", " Удалить одежду", "Далее", "Назад");
		}
		
		case D_FRACTION + 39:
		{
			new findex = GetFractionMember(playerid),
				index = GetPVarInt(playerid, "Fraction:SelectUnit");
				
			if (response)
			{
				new skin = strval(inputtext);
				
				if (!(1 <= skin <= 311) || skin == 74)
				{
					ShowFractionUnitSkinsAdd(playerid, "Некорректное значение.");
					return 1;
				}
				
				new sindex = GetFreeIndexForUnitSkin(findex, index);
				
				if (sindex != INVALID_PARAM)
				{
					fraction_unit_data[findex][index][fr_skins][sindex] = skin; 
					Update:fraction_unit_skins(findex, index);
					
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно добавили новую одежду для данного подразделения.");
					
				}
				else 
				{
					ShowFractionUnitSkinsAdd(playerid, "Превышен лимит на одежду.");
				}
			}
			
			ShowFractionUnitSkins(playerid, findex, index);
		}
		
		case D_FRACTION + 40:
		{
			new findex = GetFractionMember(playerid),
				index = GetPVarInt(playerid, "Fraction:SelectUnit"),
				sindex = GetPVarInt(playerid, "Fraction:SelectSkin");
			
			if (response)
			{
				if (listitem == 0)
				{
					fraction_unit_data[findex][index][fr_skins][sindex] = 0; 
					Update:fraction_unit_skins(findex, index);
					
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно удалили одежду для данного подразделения.");
				}
			}
			
			ShowFractionUnitSkins(playerid, findex, index);
		}
		
		case D_FRACTION + 41:
		{
			new findex = GetFractionMember(playerid),
				index = GetPVarInt(playerid, "Fraction:SelectUnit");
			
			if (!response)
			{
				ShowFractionEditUnit(playerid, findex, index);
				return 1;
			}
			
			new Float: x,
				Float: y,
				Float: z,
				Float: angle;
				
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			
			fraction_unit_data[findex][index][fr_pos_x] = x;
			fraction_unit_data[findex][index][fr_pos_y] = y;
			fraction_unit_data[findex][index][fr_pos_z] = z;
			fraction_unit_data[findex][index][fr_pos_angle] = angle;
			
			Update:fraction_unit_float(findex, index, "fr_pos_x", x);
			Update:fraction_unit_float(findex, index, "fr_pos_y", y);
			Update:fraction_unit_float(findex, index, "fr_pos_z", z);
			Update:fraction_unit_float(findex, index, "fr_pos_angle", angle);
			
			fraction_unit_data[findex][index][fr_int] = GetCharacterInt(playerid);
			fraction_unit_data[findex][index][fr_world] = GetCharacterWorld(playerid);
	
			Update:fraction_unit_int(findex, index, "fr_int", GetCharacterInt(playerid));
			Update:fraction_unit_int(findex, index, "fr_world", GetCharacterWorld(playerid));
			
			SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы успешно установили место появление.");
			ShowFractionEditUnit(playerid, findex, index);
		}
		
		case D_FRACTION + 42:
		{
			new findex = GetFractionMember(playerid),
				index = GetPVarInt(playerid, "Fraction:SelectUnit");
				
			if (!response)
			{
				ShowFractionEditUnit(playerid, findex, index);
				return 1;
			}
			
			Remove:fraction_unit_data(findex, index);
			
			SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы успешно удалили подразделение.");
			ShowFractionUnits(playerid, D_FRACTION + 31, findex, #cGRAY "Добавить подразделение\n");
		}
		
		case D_FRACTION + 43:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, FRACTION_SETTINGS_DIALOG);
				return 1;
			}
			
			new index = GetFractionMember(playerid);
			
			if (listitem == 0)
			{
				ShowFractionJoinRank(playerid, index);
				return 1;
			}
			
			listitem--;
			
			new rindex = g_dialog_select[playerid][listitem];
			
			fraction_data[index][fr_join_rank_id] = fraction_rank_data[index][rindex][fr_id];
			Update:fraction_int(index, "fr_join_rank_id", fraction_rank_data[index][rindex][fr_id]);
			SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы успешно установили ранг по умолчанию.");
			ShowPlayerDialog(playerid, FRACTION_SETTINGS_DIALOG);
		}
		
		
		/*
			@brief Система объектов 
		*/
		
		
		case D_FRACTION + 44: // Список объектов (/object)
		{
			if (!response)
			{
				return 1;
			}
			
			new action = fraction_item_select[playerid][listitem][fr_id];
			
			if (action == ITEM_LIST_NEXT || action == ITEM_LIST_BACK)
			{
				new index = GetFractionMember(playerid);
				ShowFractionObjectList(playerid, D_FRACTION + 44, index, action, "");
				return 1;
			}
			
			new findex = GetFractionMember(playerid),
				index = GetFreeIndexForFractionObject(findex),
				model = fraction_item_select[playerid][listitem][fr_object_id];
			
			if (index != INVALID_PARAM)
			{
				Create:fraction_object(playerid, findex, index, model);
				
				EditDynamicObject(
					playerid, 
					GetFractionObject(findex, index)
				);
				
				SetPVarInt(playerid, "Fraction:ObjectMode", 1);
				SetPVarInt(playerid, "Fraction:ObjectIndex", index);
			}
			else 
			{
				SendClientMessage(playerid, C_WHITE, #ERROR " Лимит объектов на организацию превышен.");
			}
			
		}
		
		case D_FRACTION + 45: // Удаление объектов (/dobject)
		{
			if( !response )
			{
				return 1;
			}
			
			if (listitem == 0)
			{
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Для удаления объекта используйте - " #cPROJECT "/dobject [ID объекта]");
				return 1;
			}
			else if (listitem == 1)
			{
				SetPVarInt(playerid, "Fraction:ObjectSelect", true);
				SelectObject(playerid);
				
				SendClientMessage(playerid, C_WHITE, #DEFAULT " Выберите объект для удаления с помощью курсора.");
				return 1;
			}
		}
		
		/*
		
			@brief Система аттачей
		
		*/
		
		case D_FRACTION + 46: // Список аттачей (/attach)
		{
			if (!response)
			{
				return 1;
			}
			
			new action = fraction_item_select[playerid][listitem][fr_id];
			
			if (action == ITEM_LIST_NEXT || action == ITEM_LIST_BACK)
			{
				new index = GetFractionMember(playerid);
				ShowFractionAttachList(playerid, dialogid, index, action, #cGRAY "Удалить все объекты\n");
				return 1;
			}
				
			if (listitem == 0)
			{		
				RemovePlayerAttachedObject(playerid, SLOT_ATTACH_FACTION_1); 
				RemovePlayerAttachedObject(playerid, SLOT_ATTACH_FACTION_2); 
				RemovePlayerAttachedObject(playerid, SLOT_ATTACH_FACTION_3);
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно очистили список прикреплённых объектов.");
				return 1;
			}
			
			SetPVarInt(playerid, "Fraction:AttachObjectId", fraction_item_select[playerid][listitem][fr_object_id]);
			ShowPlayerDialog(playerid, D_FRACTION + 47, DIALOG_STYLE_LIST, " ", FRACTION_BONE_DIALOG, "Выбрать", "Назад");
		}
		
		case D_FRACTION + 47:
		{
			if (!response)
			{
				DeletePVar(playerid, "Fraction:AttachObjectId");
				cmd_attach(playerid);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowPlayerDialog(playerid, D_FRACTION + 47, DIALOG_STYLE_LIST, " ", FRACTION_BONE_DIALOG, "Выбрать", "Назад");
				return 1;
			}
			
			new object_id = GetPVarInt(playerid, "Fraction:AttachObjectId"),
				bool: is_exists = false;
			
			for (new i = SLOT_ATTACH_FACTION_1; i <= SLOT_ATTACH_FACTION_3; i++)
			{
				if (!IsPlayerAttachedObjectSlotUsed(playerid, i))
				{
					SetPVarInt(playerid, "Fraction:AttachMode", true);
					
					SetPlayerAttachedObject(playerid, i, object_id, listitem);
					EditAttachedObject(playerid, i);
					
					is_exists = true;
					break;
				}
			}
			
			if (!is_exists)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете прикрепить больше объектов, так как слоты заняты.");
				return 1;
			}
		}
		
		/*
		
			@brief Дежурство и выбор скина
		
		*/
		
		case D_FRACTION + 48: // Заступление на дежурство
		{
			if (!response)
			{
				return 1;
			}
			
			if (listitem == 0) // В рабочей форме
			{
				new findex = GetFractionMember(playerid),
					uindex = GetFractionMemberUnit(playerid);
				
				if (uindex == INVALID_PARAM)
				{
					SendClientMessage(playerid, C_WHITE, #ERROR " Вы не состоите в подразделении.");
					return 1;
				}
				
				ShowFractionSkinList(playerid, true, findex, uindex);
			}
			else if (listitem == 1) // В гражданской форме
			{
				FractionMemberDuty(playerid, true);
			}
		}
		
		case D_FRACTION + 49: // Уход с дежурства
		{
			if (!response)
			{
				return 1;
			}
			
			FractionMemberDuty(playerid, false);
		}
		
		/*
		
			@brief Склад
		
		*/
		
		case D_FRACTION + 50:
		{
			if (!response)
			{
				return 1;
			}
			
			new findex = GetFractionMember(playerid),
				id = fraction_item_select[playerid][listitem][fr_id];
			
			if (id == ITEM_LIST_NEXT || id == ITEM_LIST_BACK)
			{
				ShowFractionItemList(playerid, dialogid, findex, id);
				return 1;
			}
			
			if (GiveInventoryItem(
				playerid, 
				fraction_item_select[playerid][listitem][fr_object_id],
				fraction_item_select[playerid][listitem][fr_item_param_1],
				fraction_item_select[playerid][listitem][fr_item_param_2]
			) == INVALID_PARAM)
			{
				SendClientMessage(playerid, C_WHITE, !ERROR_NO_SLOTS);
				return 1;
			}
			
			SendRPMessage(ACTION_AME, playerid, 
				character_data[playerid][c_sex] == 0 ? ("Взял снаряжение") : ("Взяла снаряжение")
			);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно получили предмет.");
		}
		
		/*
		
			@brief MDC
			
		*/
		
		case D_FRACTION + 51:
		{
			if (!response)
			{
				return 1;
			}
			
			if (listitem == 0) // Информация о человеке
			{
				ShowPlayerDialog(playerid, D_FRACTION + 55, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Информация о человеке\n\n\
					Введите имя человека:",
					"Далее", "Назад"
				);
			}
			else if (listitem == 1) // Информация о транспорте
			{
				ShowPlayerDialog(playerid, D_FRACTION + 57, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Информация о транспорте\n\n\
					Введите номер транспорта:",
					"Далее", "Назад"
				);
			}
			else if (listitem == 2) // Информация о доме
			{
				ShowPlayerDialog(playerid, D_FRACTION + 57, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Информация о доме\n\n\
					Введите номер дома:",
					"Далее", "Назад"
				);
			}
			else if (listitem == 3) // Информация о помещении
			{
				ShowPlayerDialog(playerid, D_FRACTION + 57, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Информация о помещении\n\n\
					Введите номер помещения:",
					"Далее", "Назад"
				);
			}
			else if (listitem == 4) // Активные вызовы
			{
				ShowFractionCalls(playerid, D_FRACTION + 52);
			}
		}
		
		case D_FRACTION + 52:
		{
			if (!response)
			{
				cmd_mdc(playerid);
				return 1;
			}
			
			new index = g_dialog_select[playerid][listitem];
			
			SetPVarInt(playerid, "Fraction:SelectCall", index);
			ShowFractionCallInformation(playerid, D_FRACTION + 53, index);
		}
		
		case D_FRACTION + 53:
		{
			if (!response)
			{
				ShowFractionCalls(playerid, D_FRACTION + 52);
				return 1;
			}
			
			ShowPlayerDialog(playerid, D_FRACTION + 54, DIALOG_STYLE_LIST, " ", " \
				Принять вызов\n \
				Аннулировать вызов",
				"Выбрать", "Назад"
			);
		}
		
		case D_FRACTION + 54:
		{
			new index = GetPVarInt(playerid, "Fraction:SelectCall"),
				findex = GetFractionMember(playerid);
			
			if (!response)
			{
				ShowFractionCallInformation(playerid, D_FRACTION + 53, index);
				return 1;
			}
			
			new targetid = fraction_call[index][c_player_id];
			
			if (listitem == 0) // Принять вызов
			{
				if (IsPlayerLogged(targetid))
				{
					SendClientMessage(targetid, C_WHITE, !#SUCCESS " Ваш вызов в 911 успешно подтвержден, ожидайте на месте.");
				}
				
				SetIncludeGPS(
					playerid, 
					fraction_call[index][c_pos][0], 
					fraction_call[index][c_pos][1], 
					fraction_call[index][c_pos][2]
				);
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно приняли вызов.");
				
				format:g_small_string(#FRACTION_MESSAGE " %s принял%s вызов в 911 (#%d).",
					GetPlayerCurrentName(playerid),
					EndWordSex(playerid),
					index
				);
				
				SendFractionMessage(findex, g_small_string);
			}
			else if (listitem == 1) // Аннулировать вызов
			{
				if (IsPlayerLogged(targetid))
				{
					SendClientMessage(targetid, C_WHITE, #SUCCESS " Ваш вызов в 911 был аннулирован.");
				}
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно аннулировали вызов.");
				
				format:g_small_string(#FRACTION_MESSAGE " %s аннулировал%s вызов в 911 (#%d).",
					GetPlayerCurrentName(playerid),
					EndWordSex(playerid),
					index
				);
				
				SendFractionMessage(findex, g_small_string);
			}
			
			Clear:fraction_call(index);
		}
		
		case D_FRACTION + 55:
		{
			if (!response)
			{
				cmd_mdc(playerid);
				return 1;
			}
			
			if (!IsUserAllowQuery(playerid))
			{
				return 1;
			}
	
			format:g_string("SELECT * FROM " #__CHARACTERS " WHERE c_name LIKE '%q' LIMIT 1",
				inputtext
			);
			
			mysql_tquery(db, g_string, "OnFractionCharacterSearch", "dd", playerid, inputtext);
			
			SetUserAllowQuery(playerid, false);
		}
		
		case D_FRACTION + 56:
		{
			cmd_mdc(playerid);
		}
		
		case D_FRACTION + 57:
		{
			/*format:g_string("SELECT c.* \
				FROM " #__VEHICLES " \
				LEFT JOIN " #__CHARACTERS "
				WHERE v_number LIKE '%q' LIMIT 1",
				inputtext
			);
			
			mysql_tquery(db, g_string, "OnFractionVehicleSearch", "dd", playerid, inputtext);*/
			
			SendClientMessage(playerid, C_WHITE, "В разработке.");
		}
		
		/*
			
			@brief Тюрьма (компьютер)
			
		*/
		
		case D_FRACTION + 58:
		{
			if (!response)
			{
				return 1;
			}
			
			if (!IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, PRISON_MENU_POS))
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Вы находитесь на большом расстоянии от пульта управления.");
				return 1;
			}

			SetFractionCameraStateDoor(
				GetFractionMember(playerid)
			);
			
			SendRPMessage(ACTION_AME, playerid, 
				character_data[playerid][c_sex] == 0 ? ("Нажал на пульт управления") : ("Нажала на пульт управления")
			);
			
			ShowPrisonMenu(playerid);
		}
	}
	
	return 1;
}

function OnFractionCharacterSearch(playerid, name[])
{	
	SetUserAllowQuery(playerid, true);
	
	new rows;
	
	cache_get_row_count(rows);
	
	if (rows == 0)
	{
		ShowPlayerDialog(playerid, D_FRACTION + 55, DIALOG_STYLE_INPUT, " ",
			"" #DEFAULT " Информация о человеке\n\n\
			Введите имя человека:\n\n\
			" #cRED "Данный человек не найден в базе данных.",
			"Далее", "Назад"
		);
		
		return 1;
	}
	
	new first_name 	[MAX_PLAYER_NAME],
		last_name  	[MAX_PLAYER_NAME],
		str_suspect [128];
		
	new race,
		age;
		
	clean:<g_small_string>;
	cache_get_value_name(0, "c_name", g_small_string, MAX_PLAYER_NAME);
	sscanf(g_small_string, "p<_>s[24]s[24]", first_name, last_name);
	
	cache_get_value_name_int(0, "c_race", race);
	cache_get_value_name_int(0, "c_age", age);
	
	clean:<g_small_string>;
	cache_get_value_name(0, "c_suspect", g_small_string, MAX_PLAYER_NAME);
	
	if (!isnull(g_small_string))
	{
		format:str_suspect(#cPROJECT "%s", g_small_string);
	}
	else 
	{
		strcat(str_suspect, #cGRAY "Нет");
	}
	
	clean:<g_string>;
	format:g_string("\
		" #DEFAULT " Информация о человеке\n\n\
		Имя: " #cPROJECT "%s" #cWHITE "\n\
		Фамилия: " #cPROJECT "%s" #cWHITE "\n\
		Раса: " #cPROJECT "%s" #cWHITE "\n\
		Возраст: " #cPROJECT "%d лет" #cWHITE "\n\
		Розыск: " #cPROJECT "%s" #cWHITE "",
		first_name,
		last_name,
		character_race_info[race],
		age,
		str_suspect
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 56, DIALOG_STYLE_MSGBOX, " ", g_string, "Назад", "");
	return 1;
}

Check:fraction_unit_leader(playerid, findex, index, name[])
{
	format:g_string("SELECT COUNT(c_id) as character_exists, c_id AS character_id FROM " #__CHARACTERS " WHERE c_name = '%q' AND c_fraction_id = %d", 
		name, 
		GetFractionId(findex)
	);
	
	mysql_tquery(db, g_string, "OnFractionUnitLeaderCheck", "ddds", playerid, findex, index, name);
}

function OnFractionUnitLeaderCheck(playerid, findex, index, name[])
{
	new is_exists,
		character_id;
	
	cache_get_value_name_int(0, "character_exists", is_exists);
	cache_get_value_name_int(0, "character_id", character_id);
	
	if (!is_exists)
	{
		ShowFractionEditUnitLeader(playerid, D_ADMIN + 50, index, "Вы ввели неверное имя персонажа.");
		return 1;
	}
	
	is_exists = false;
				
	foreach (new i : Player)
	{
		if (!IsPlayerLogged(i))
		{
			continue;
		}
		
		if (character_data[i][c_id] == character_id
		&& GetFractionMember(i) == findex)
		{
			character_data[i][c_fraction_unit_leader_index] = index;
			
			Update:character_int(i, "c_fraction_unit_id", fraction_unit_data[findex][index][fr_id]);
			is_exists = true;
		
			break;
		}
	}
	
	fraction_unit_data[findex][index][fr_leader_id] = character_id;
	clean:<fraction_unit_data[findex][index][fr_leader_name]>;
	strcat(fraction_unit_data[findex][index][fr_leader_name], name, MAX_PLAYER_NAME);
	
	if (!is_exists)
	{
		format:g_string("\
			UPDATE " #__CHARACTERS " \
			SET \
				c_fraction_unit_id = 0 \
			WHERE c_id = %d AND c_fraction_id = %d",
			GetFractionId(findex),
			character_id,
			GetFractionId(findex)
		);
		
		mysql_tquery(db, g_string);
	}
	
	Update:fraction_int(findex, "fr_leader_id", character_id);
	
	pformat:(#SUCCESS " Вы успешно назначили " #cPROJECT "%s" #cWHITE " лидером подразделения.", name);
	psend:(playerid, C_WHITE);
	
	format:g_small_string(#FRACTION_MESSAGE " %s назначил лидером подразделения %s.",
		GetPlayerCurrentName(playerid),
		name
	);
	
	SendFractionMessage(findex, g_small_string);
	
	ShowFractionEditUnit(playerid, findex, index);
	return 1;
}