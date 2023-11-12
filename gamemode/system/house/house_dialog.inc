/*!
	@brief Диалоги системы домов
	@author Found (evg.savosin)
	@date 16.12.2016, update 21.03.2018
*/

House_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{	
	
		/*!
			@brief Диалоги для дома
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
				SendClientMessage(playerid, C_WHITE, !#ERROR " Вы должны находиться рядом с жилищным помещением.");
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
				ShowHouseInformation(playerid, index, D_HOUSE - 1, true, "Назад");
				return 1;
			}
			
			if (GetPVarInt(playerid, "House:IsOwner"))
			{
				if (listitem == 1)
				{
					ShowHouseControl(playerid, index);
					// управление
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
					format:g_string("" #DEFAULT " Приобретение\n\n\
					Вы полноценно покупаете жилищное помещение, которым можете распоряжаться самолично.\n\
					С покупкой Вам становится доступно:\n  - \
					Подселение сожильцов до " #cPROJECT "%i" #cWHITE " и настройка их прав.\n  - \
					Режим ремонта\n    - \
					Расстановка мебели\n    - \
					Изменение текстур\n  - \
					Кастомизация объектов в гараже\n\n\
					Вы подтверждаете покупку %s " #cPROJECT "#%i" #cWHITE " за " #cGREEN "$%i" #cWHITE "?",
						house_settings[house_data[index][h_int_type]][hset_lodgers],
						(IsHouseType(index) == TYPE_APARTAMENT) ? ("квартиры") : ("дома"),
						GetHouseId(index),
						house_data[index][h_price]
					);
					
					ShowPlayerDialog(playerid, D_HOUSE + 2, DIALOG_STYLE_MSGBOX, " ", 
						g_string, 
						"Да", "Нет" 
					);
					
					SetPVarInt(playerid, "House:BuyType", TYPE_BUY_FULLY);
				}
				else if (listitem == 2)
				{
					format:g_string("" #DEFAULT " Аренда\n\n\
					Экономичный вариант снять жилищное помещение на определенный срок за меньшую сумму.\n\
					Однако некоторые функции претерпевают изменения:\n  - \
					Не требуется оплата коммунальных услуг.\n  - \
					Вы не сможете подселить к себе сожильца.\n  - \
					Режим ремонта ограничен.\n  - \ 
					Кастомизация объектов гаража недоступна.\n\n\
					" #cWHITE "Вы подтверждаете аренду %s " #cPROJECT "#%i" #cWHITE " за " #cGREEN "$%i" #cWHITE "/неделя?",
						(IsHouseType(index) == TYPE_APARTAMENT) ? ("квартиры") : ("дома"),
						GetHouseId(index),
						GetHouseRent(index)
					);
					
					ShowPlayerDialog(playerid, D_HOUSE + 2, DIALOG_STYLE_MSGBOX, " ", 
						g_string, 
						"Да", "Нет" 
					);
					
					SetPVarInt(playerid, "House:BuyType", TYPE_BUY_RENT);
				}
			}
		}
		
		case D_HOUSE + 2 : // покупка дома
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
						"" #DEFAULT " Расторгнуть аренду\n\n\
						Вы действительно подтверждаете расторжение аренды?\n\
						Компенсация не будет выдана.", 
						"Да", "Нет" 
					);
				}	
				else 
				{
					format:g_string("" #DEFAULT " Продать дом\n\n\
					Вы действительно подтверждаете продажу " #cPROJECT "%s" #cWHITE "?\n\
					С учетом Вашей задолжности и суммы из сейфа, Вы получите " #cGREEN "$%i" #cWHITE ".",
						(IsHouseType(index) == TYPE_HOUSE) ? ("дома") : ("квартиры"),
						GetSaleHousePrice(index)
					);
					
					ShowPlayerDialog(playerid, D_HOUSE + 11, DIALOG_STYLE_MSGBOX, " ", g_string, "Да", "Нет");
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
					"" #DEFAULT " Подселение\n\n\
					Введите ID игрока, которого Вы хотите подселить к себе:\n\n\
					" #cRED "Вы ввели неверный ID игрока.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			if (!IsPlayerAroundOfPlayer(playerid, targetid))
			{
				ShowPlayerDialog(playerid, D_HOUSE + 5, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Подселение\n\n\
					Введите ID игрока, которого Вы хотите подселить к себе:\n\n\
					" #cRED "Данный игрок находится слишком далеко от Вас.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			new hindex = GetPlayerHouse(targetid);

			if (lod_data[targetid][lod_house_index] != INVALID_PARAM || hindex != INVALID_PARAM)
			{
				ShowPlayerDialog(playerid, D_HOUSE + 5, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Подселение\n\n\
					Введите ID игрока, которого Вы хотите подселить к себе:\n\n\
					" #cRED "Данный игрок уже где-то проживает.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			pformat:("" #SUCCESS " Вы отправили предложение о подселении " #cPROJECT "%s" #cWHITE ".",
				GetPlayerCurrentName(targetid)
			);
			
			psend:(playerid, C_WHITE);
			
			cmd_hmenu(playerid);
			// -
			
			format:g_string("" #DEFAULT " Предложение\n\n\
				" #cPROJECT "%s" #cWHITE " предлагает Вам подселиться в его жилищное помещение.\n\
				Вы принимаете предложение?", GetPlayerCurrentName(playerid) 
			);
			
			ShowPlayerDialog(targetid, D_HOUSE + 6, DIALOG_STYLE_MSGBOX, " ", 
				g_string,
				"Да", "Нет"
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
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " принял Ваше предложение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
				
				SendClientMessage(ownerid, C_WHITE, !#DEFAULT " Для настройки доступа сожителя к дому, перейдите в " #cGRAY "Сожители" #cWHITE " и выберите нужного сожителя.");
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы приняли предложение.");
				
				Create:lod_data(playerid, index);
			}
			else 
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " отклонил Ваше предложение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы отклонили предложение.");
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
					pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " выселил Вас из жилищного помещения.",
						GetPlayerCurrentName(playerid)
					);
					
					psend:(targetid, C_WHITE);
				}
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно выселили данного игрока из своего жилищного помещения.");
			
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
			
			format:g_small_string("" #DEFAULT " Зона #%d",
				listitem + 1
			);
			
			ShowPlayerDialog(playerid, D_HOUSE + 10, DIALOG_STYLE_LIST, g_small_string, 
				" Редактирование потолка\n \
				Редактирование стен\n \
				Редактирование пола",
				"Далее", "Назад"
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
					"" #DEFAULT " Сейф - взять сумму\n\n\
					Введите сумму, которую Вы хотите взять из сейф:",
					"Далее", "Назад" 
				);
			}
			else if (listitem == 2)
			{
				ShowPlayerDialog(playerid, D_HOUSE + 14, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Сейф - положить сумму\n\n\
					Введите сумму, которую Вы хотите положить в сейф:",
					"Далее", "Назад" 
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
					"" #DEFAULT " Сейф - взять сумму\n\n\
					Введите сумму, которую Вы хотите взять из сейф:\n\n\
					" #cRED "Вы ввели неверную сумму.",
					"Далее", "Назад" 
				);
				
				return 1;
			}
			
			GivePlayerCash(playerid, money);
			house_data[index][h_money] -= money;
			Update:house_int(index, "h_money", house_data[index][h_money]);
			
			pformat:("" #SUCCESS " Вы успешно взяли сумму в размере " #cGREEN "$%i" #cWHITE " из сейфа.",
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
					"" #DEFAULT " Сейф - положить сумму\n\n\
					Введите сумму, которую Вы хотите положить в сейф:\n\n\
					" #cRED "Вы ввели неверную сумму.",
					"Далее", "Назад" 
				);
				
				return 1;
			}
			
			GivePlayerCash(playerid, -money);
			house_data[index][h_money] += money;
			Update:house_int(index, "h_money", house_data[index][h_money]);
			
			pformat:("" #SUCCESS " Вы успешно положили сумму в размере " #cGREEN "$%i" #cWHITE " в сейф.",
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
				ShowHouseDialogSell_Player(playerid, "Вы ввели неверный ID игрока.");
				return 1;
			}
			
			if (!IsPlayerAroundOfPlayer(playerid, targetid))
			{
				ShowHouseDialogSell_Player(playerid, "Данный игрок находится слишком далеко от Вас.");
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
				ShowHouseDialogSell_Summ(playerid, index, "Игрок находится далеко от Вас либо его нет в сети.");
				return 1;
			}
		
			pformat:("" #SUCCESS " Вы отправили предложение о продаже %s " #cPROJECT "%s" #cWHITE ".",
				(IsHouseType(index) == TYPE_APARTAMENT) ? ("квартиры") : ("дома"),
				GetPlayerCurrentName(targetid)
			);
			
			psend:(playerid, C_WHITE);
			
			// -
			
			format:g_string("" #DEFAULT " Предложение\n\n\
				" #cPROJECT "%s" #cWHITE " предлагает Вам купить %s за " #cGREEN "$%i" #cWHITE ".\n\
				Вы принимаете предложение?",
				GetPlayerCurrentName(playerid),
				(IsHouseType(index) == TYPE_APARTAMENT) ? ("квартиру") : ("дом"),
				money
			);
			
			ShowPlayerDialog(targetid, D_HOUSE + 17, DIALOG_STYLE_MSGBOX, " ", 
				g_string,
				"Да", "Нет"
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
				
			if (response) // Купил
			{
				if (SellHouseToPlayer(ownerid, index, playerid, price))
				{
					pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " принял Ваше предложение.",
						GetPlayerCurrentName(playerid)
					);
					
					psend:(ownerid, C_WHITE);
					
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы приняли предложение.");
				}
			}
			else // Отказался
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " отклонил Ваше предложение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы отклонили предложение.");
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
			@brief Диалоги для гаража
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
				format:g_string(" %s " #cWHITE "двери\t" #cGRAY "/glock" #cWHITE "\n", 
					house_data[index][hg_lock] ? ("" #cPROJECT "Открыть") : ("" #cGRAY "Закрыть")
				);
				
				ShowPlayerDialog(playerid, D_GARAGE + 1, DIALOG_STYLE_TABLIST, " ", g_string, "Выбрать", "Назад");
			}
			else if (listitem == 1)
			{	
				cmd_clist(playerid);
			}
			else if (listitem == 2)
			{
				if (!house_data[index][hg_set_furn])
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Данный пункт недоступен, поскольку возможность кастомизации отключена.");
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
			else if (listitem == 3) // настройки
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
				
				format:g_string(" %s дверь" #cWHITE "", 
					house_data[index][hg_lock] ? ("" #cPROJECT "Открыть") : ("" #cGRAY "Закрыть")
				);
				
				ShowPlayerDialog(playerid, D_GARAGE + 1, DIALOG_STYLE_LIST, " ", g_string, "Выбрать", "Назад");
				
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
			
			if (listitem == 0) // настройка фурнитуры
			{
				if (GetHouseTypeBought(index) == TYPE_BUY_RENT)
				{
					SendClientMessage(playerid, C_WHITE, !NOT_RENT_ACCESS);
					return 1;
				}
			
				if (house_data[index][hg_set_furn])
				{
					ShowPlayerDialog(playerid, D_GARAGE + 3, DIALOG_STYLE_MSGBOX, " ", 
						"" #DEFAULT " Кастомизация объектов\n\n\
						При отключении кастомизации все ранее купленные объекты " #cPROJECT "УДАЛЯТСЯ" #cWHITE ".\n\
						Вы подтверждаете данное действие? ",
						"Да", "Нет" 
					);
				}
				else 
				{
					ShowPlayerDialog(playerid, D_GARAGE + 3, DIALOG_STYLE_MSGBOX, " ", 
						"" #DEFAULT " Кастомизация объектов\n\n\
						Вы включаете кастомизацию объектов, с помощью которой Вы сможете настроить интерьер так, как он удобен Вам.\n\
						У Вас имеется право на возврат стандартного оформления интерьера.\n\
						Вы подтверждаете данное действие? ",
						"Да", "Нет" 
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
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы отключили кастомизацию объектов.");
				}
				else 
				{
					Destroy:static_furn(index);
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы включили кастомизацию объектов.");
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
			"" #ERROR " Подселение\n\n\
			Вы не можете подселить к себе больше сожителей.",
			"Назад", ""
		);
		
		return 1;
	}
	
	ShowPlayerDialog(playerid, D_HOUSE + 5, DIALOG_STYLE_INPUT, " ", 
		"" #DEFAULT " Подселение\n\n\
		Введите ID игрока, которого Вы хотите подселить к себе:",
		"Далее", "Назад"
	);
	
	return 1;
}

function OnHouseLodgerUpdate(playerid)
{
	SetUserAllowQuery(playerid, true);
	return 1;
}