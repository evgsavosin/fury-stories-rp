/*!
	@brief Диалоги для системы помещений
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
				SendClientMessage(playerid, C_WHITE, !#ERROR " Вы находитесь слишком далеко от помещения.");
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
			
			if (IsPremiseTied(index)) // Если привязан бизнес
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
				
					GivePremiseProfitByVisitor(index, playerid); // Прибыль за посещение
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
				ShowPremiseInformation(playerid, index, D_PREMISE - 1, true, "Назад");
				return 1;
			}
			
			if (GetPVarInt(playerid, "Premise:IsOwner"))
			{
				if (!CheckPremiseAccess(TYPE_PREMISE_MEMBER, playerid, index)) 
				{
					return 1;
				}
				
				if (listitem == 1) // Управление помещением
				{
					ShowPremiseControl(playerid, index);
					// управление
				}
				else if (listitem == 2) // Управление компанией
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
				else if (listitem == 3) // Режим ремонта
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
					format:g_string("" #DEFAULT " Приобретение\n\n\
					Вы полноценно покупаете помещение, которым cможете распоряжаться самолично.\n\
					С покупкой Вам становится доступно:\n  - \
					Создание компании\n  - \
					Режим ремонта\n    - \
					Расстановка мебели\n    - \
					Изменение текстур.\n\n\
					Вы подтверждаете покупку помещения " #cPROJECT "#%i" cWHITE " за " #cGREEN "$%i" #cWHITE "?",
						GetPremiseId(index),
						premise_data[index][pr_price]
					);
					
					ShowPlayerDialog(playerid, D_PREMISE + 2, DIALOG_STYLE_MSGBOX, " ", 
						g_string, 
						"Да", "Нет" 
					);
					
					SetPVarInt(playerid, "Premise:BuyType", TYPE_BUY_FULLY);
				}
				else if (listitem == 2)
				{
					format:g_string("" #DEFAULT " Аренда\n\n\
					Быстрый вариант взять в аренду помещение на определенный срок.\n\
					С покупкой Вам становится доступно:\n  - \
					Создание компании\n  - \
					" #cGRAY "Ограниченный режим ремонта" #cWHITE "\n    - \
					Расстановка мебели\n    - \
					Изменение текстур.\n\n\
					" #cWHITE "Вы подтверждаете аренду помещения " #cPROJECT "#%i" cWHITE " за " #cGREEN "$%i" #cWHITE "/неделя?",
						GetPremiseId(index),
						GetPremiseRent(index)
					);
					
					ShowPlayerDialog(playerid, D_PREMISE + 2, DIALOG_STYLE_MSGBOX, " ", 
						g_string, 
						"Да", "Нет" 
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
			
			if (listitem == 0) // Двери
			{
				PremiseLock(playerid, index);
				ShowPremiseControl(playerid, index);
			}
			else if (listitem == 1) // Изменить название
			{
				if (!CheckPremiseAccess(TYPE_PREMISE_OWNER, playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowPremiseControl(playerid, index);
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_PREMISE + 4, DIALOG_STYLE_INPUT, " ",
					DIALOG_PREMISE_NAME,
					"Далее", "Назад"
				);
			}
			
			else if (listitem == 2) // Продать агенству
			{
				if (!CheckPremiseAccess(TYPE_PREMISE_OWNER, playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
					ShowPremiseControl(playerid, index);
					return 1;
				}
				
				format:g_string("" #DEFAULT " Продать государству\n\n\
				Вы действительно подтверждаете продажу " #cPROJECT "помещения" #cWHITE " государству?\n\
				С учетом Вашей задолжности и суммы из сейфа, Вы получите " #cGREEN "$%i" #cWHITE ".",
					GetSalePremisePrice(index)
				);
				
				ShowPlayerDialog(playerid, D_PREMISE + 5, DIALOG_STYLE_MSGBOX, " ", g_string, "Да", "Нет");
			}
			
			else if (listitem == 3) // Продать игроку
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
					"" #DEFAULT " Продажа помещения игроку\n\n\
					Введите ID игрока, которому Вы хотите продать имущество:",
					"Далее", "Назад"
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
					"Далее", "Назад"
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
					"" #DEFAULT " Продажа помещения игроку\n\n\
					Введите ID игрока, которому Вы хотите продать имущество:\n\n\
					" #cRED "Вы ввели неверный ID игрока.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			if (!IsPlayerAroundOfPlayer(playerid, targetid))
			{
				ShowPlayerDialog(playerid, D_PREMISE + 6, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Продажа помещения игроку\n\n\
					Введите ID игрока, которому Вы хотите продать имущество:\n\n\
					" #cRED "Данный игрок находится слишком далеко от Вас.",
					"Далее", "Назад"
				);
				
				return 1;
			}

			format:g_string("" #DEFAULT " Продажа помещения игроку\n\n\
				Введите сумму за которую Вы хотите продать имущество " #cPROJECT "%s" #cWHITE ":\n\n\
				" #cGRAY "Минимальная цена продажи: " #cGREEN "$%i" #cGRAY ".\n\
				" #cGRAY "Максимальная цена продажи: " #cGREEN "$%i" #cGRAY ".",
				GetPlayerCurrentName(targetid),
				GetMinSalePremisePrice(index),
				GetMaxSalePremisePrice(index)
			);
			
			ShowPlayerDialog(playerid, D_PREMISE + 7, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
			
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
					"" #DEFAULT " Продажа помещения игроку\n\n\
					Введите ID игрока, которому Вы хотите продать имущество:",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			if (isnull(inputtext) || !IsInt(inputtext) 
			|| !(GetMinSalePremisePrice(index) <= (money = strval(inputtext)) <= GetMaxSalePremisePrice(index)))
			{
				format:g_string("" #DEFAULT " Продажа помещения игроку\n\n\
					Введите сумму за которую Вы хотите продать имущество " #cPROJECT "%s" #cWHITE ":\n\n\
					" #cGRAY "Минимальная цена продажи: " #cGREEN "$%i" #cGRAY ".\n\
					" #cGRAY "Максимальная цена продажи: " #cGREEN "$%i" #cGRAY ".\n\
					" #cRED "Вы ввели неверную сумму.",
					GetPlayerCurrentName(targetid),
					GetMinSalePremisePrice(index),
					GetMaxSalePremisePrice(index)
				);
				
				ShowPlayerDialog(playerid, D_PREMISE + 7, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
				
				return 1;
			}
			
			if (!IsPlayerLogged(playerid) || !IsPlayerAroundOfPlayer(playerid, targetid))
			{
				format:g_string("" #DEFAULT " Продажа помещения игроку\n\n\
					Введите сумму за которую Вы хотите продать имущество " #cPROJECT "%s" #cWHITE ":\n\n\
					" #cGRAY "Минимальная цена продажи: " #cGREEN "$%i" #cGRAY ".\n\
					" #cGRAY "Максимальная цена продажи: " #cGREEN "$%i" #cGRAY ".\n\
					" #cRED "Игрок находится далеко от Вас либо его нет в сети.",
					GetPlayerCurrentName(targetid),
					GetMinSalePremisePrice(index),
					GetMaxSalePremisePrice(index)
				);
				
				ShowPlayerDialog(playerid, D_PREMISE + 7, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
				
				return 1;
			}
		
			pformat:("" #SUCCESS " Вы отправили предложение о продаже помещения " #cPROJECT "%s" #cWHITE ".",
				GetPlayerCurrentName(targetid)
			);
			
			psend:(playerid, C_WHITE);
			
			// -
			
			format:g_string("" #DEFAULT " Предложение\n\n\
				" #cPROJECT "%s" #cWHITE " предлагает Вам купить помещение за " #cGREEN "$%i" #cWHITE ".\n\
				Вы принимаете предложение?",
				GetPlayerCurrentName(playerid),
				money
			);
			
			ShowPlayerDialog(targetid, D_PREMISE + 8, DIALOG_STYLE_MSGBOX, " ", 
				g_string,
				"Да", "Нет"
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
					pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " принял Ваше предложение.",
						GetPlayerCurrentName(playerid)
					);
					
					psend:(ownerid, C_WHITE);
					
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы приняли предложение.");
				}
				// купила
			}
			else 
			{
				// отказалась
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " отклонил Ваше предложение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы отклонили предложение.");
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
			
			format:g_small_string("" #DEFAULT " Зона #%d",
				listitem + 1
			);
			
			ShowPlayerDialog(playerid, D_PREMISE + 11, DIALOG_STYLE_LIST, g_small_string, 
				" Редактирование потолка\n \
				Редактирование стен\n \
				Редактирование пола",
				"Далее", "Назад"
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
			
			if (listitem == 0) // Заказать товары
			{
				format:g_string(#DEFAULT " Заказать товары\n\n\
					На складе: " #cPROJECT "%d" #cWHITE " ед.\n\
					Максимальный объём на складе: %d ед\n\
					" #cGREEN"$1" #cWHITE " = " #cPROJECT "1 ед." #cWHITE "\n\n\
					Введите количество единиц товара для заказа:",
					premise_data[index][pr_assort_stock],
					MAX_ASSORT_STOCK
				);
				
				ShowPlayerDialog(playerid, D_PREMISE + 16, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
			}
			else if (listitem == 1) // Плата за вход
			{
				if (GetPremiseEntrance(index) != 0)
				{
					premise_data[index][pr_entrance] = 0;
					Update:premise_int(index, "pr_entrance", 0);
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно убрали плату за вход.");
				}
				else 
				{
					new bindex = GetBusinessIndexById(GetPremiseBusinessId(index));
					
					if (business_data[bindex][b_subtype] == INVALID_PARAM)
					{
						SendClientMessage(playerid, C_WHITE, #ERROR " У Вас не определен вид деятельности.");
						return 1;
					}
					
					if (!GetBusinessSubtypeEntrance(bindex))
					{
						SendClientMessage(playerid, C_WHITE, !#ERROR " Данный вид деятельности не предусматривает функции платного входа.");
						ShowPremiseBusinessMenu(playerid, index);
						return 1;
					}
					
					ShowPlayerDialog(playerid, D_PREMISE + 14, DIALOG_STYLE_INPUT, " ",
						"" #DEFAULT " Плата за вход\n\n\
						Введите сумму, которую Вы будете взымать с посетителей:\n\n\
						" #cGRAY "Минимальная сумма: " #cGREEN "$1" #cGRAY ".\n\
						" #cGRAY "Максимальная сумма: " #cGREEN "$50" #cGRAY ".",
						"Далее", "Назад"
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
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно убрали кассу.");
					ShowPremiseBusinessMenu(playerid, index);
				}
				else 
				{
					ShowPlayerDialog(playerid, D_PREMISE + 13, DIALOG_STYLE_MSGBOX, " ",
						"" #DEFAULT " Установить кассу\n\n\
						Вы действительно желаете установить кассу в данном месте?",
						"Да", "Нет"
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
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно установили кассу в данном месте.");
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
					"" #DEFAULT " Плата за вход\n\n\
					Введите сумму, которую Вы будете взымать с посетителей:\n\n\
					" #cGRAY "Минимальная сумма: " #cGREEN "$1" #cGRAY ".\n\
					" #cGRAY "Максимальная сумма: " #cGREEN "$50" #cGRAY ".\n\
					" #cRED "Вы ввели неверную сумму.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			premise_data[index][pr_entrance] = value;
			Update:premise_int(index, "pr_entrance", value);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно установили плату за вход.");
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
				SendClientMessage(playerid, C_WHITE, !#ERROR " На складе закончились товары.");
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
				format:g_string(#DEFAULT " Заказать товары\n\n\
					На складе: " #cPROJECT "%d" #cWHITE " ед.\n\
					Максимальный объём на складе: %d ед\n\
					" #cGREEN"$1" #cWHITE " = " #cPROJECT "1 ед." #cWHITE "\n\n\
					Введите количество единиц товара для заказа:\n\n\
					" #cRED "Вы ввели неверное количество единиц товара.",
					premise_data[index][pr_assort_stock],
					MAX_ASSORT_STOCK
				);
				
				ShowPlayerDialog(playerid, D_PREMISE + 16, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
				return 1;
			}
			
			if (!GivePlayerCash(playerid, -assort_stock))
			{	
				format:g_string(#DEFAULT " Заказать товары\n\n\
					На складе: " #cPROJECT "%d" #cWHITE " ед.\n\
					Максимальный объём на складе: %d ед\n\
					" #cGREEN"$1" #cWHITE " = " #cPROJECT "1 ед." #cWHITE "\n\n\
					Введите количество единиц товара для заказа:\n\n\
					" #cRED "У Вас отсутствуют средства.",
					premise_data[index][pr_assort_stock],
					MAX_ASSORT_STOCK
				);
				
				ShowPlayerDialog(playerid, D_PREMISE + 16, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
				return 1;
			}
			
			premise_data[index][pr_assort_stock] += assort_stock;
			Update:premise_int(index, "pr_assort_stock", premise_data[index][pr_assort_stock]);
			
			pformat:(#SUCCESS " Вы успешно заказали товары в количестве " #cPROJECT "%d ед." #cWHITE " на сумму " #cGREEN "$%d" #cWHITE".",
				assort_stock,
				assort_stock
			);
			
			psend:(playerid, C_WHITE);
			
			ShowPremiseBusinessMenu(playerid, index);
		}
	}
	
	return 1;
}