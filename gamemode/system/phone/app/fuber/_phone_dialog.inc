/*!
	@brief Диалоги для приложений
	@author Found (evg.savosin)
	@date 28.08.2019
*/

_Phone_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case D_PHONE_APP_FUBER + 1:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_PHONE + 12, DIALOG_STYLE_LIST, "Apps", DIALOG_PHONE_APPS, "Выбрать", "Закрыть");
				return 1;
			}
			
			if (listitem == 0) // Заказ
			{
				ShowFuberPassengerOrderDialog(playerid, D_PHONE_APP_FUBER + 2);
			}
			else if (listitem == 1) // Мои поездки
			{
				ShowFuberTrips(playerid, D_PHONE_APP_FUBER + 10);
				SetPVarInt(playerid, "Fuber:TripDriverDialog", false);
			}
			else if (listitem == 2) // Способ оплаты
			{
				MakePayment(playerid, 0, "set_fuber_method_payment", "Способ оплаты");
			}
		}
		
		case D_PHONE_APP_FUBER + 2:
		{
			if (response)
			{
				if (listitem == 0) // Куда
				{
					SetPVarInt(playerid, "Fuber:SelectMap", true);
					SetPVarInt(playerid, "Phone:HideCursor", true);
					
					ShowPlayerDialog(playerid, D_PHONE_APP_FUBER + 3, DIALOG_STYLE_MSGBOX, "Fuber", "\
						"#DEFAULT " Проложить маршрут поездки\n\n\
						Необходимо поставить отметку на карте, куда именно Вы хотели бы поехать.\n\n\
						Нажмите " #cPROJECT "«ESC»" #cWHITE ", затем перейдите в раздел " #cPROJECT "«Карта / Map»" #cWHITE " и поставьте метку.",
						"Назад", "(ESC)"
					);
					
					return 1;
				}
				else if (listitem == 1) // Пожелание
				{
					ShowFuberPassengerWishDialog(playerid, D_PHONE_APP_FUBER + 4);
					return 1;
				}
				else if (listitem == 2) // Итоговая стоимость
				{
					ShowFuberPassengerOrderDialog(playerid, D_PHONE_APP_FUBER + 2);
					return 1;
				}
				else if (listitem == 3)// Оформить заказ
				{	
					Update:fuber_order(playerid);
				}
				else // Отмена заказа
				{
					Clear:fuber_order_pvar(playerid);
					
					if (HasFuberPassengerOrder(playerid))
					{
						new order_index = GetFuberPassengerOrderIndex(playerid),
							driver_id = fuber_orders[order_index][fub_driver_id];
						
						SendClientMessage(driver_id, C_YELLOW, !#FUBER_MESSAGE " Клиент отменил заказ.");
						ResetDriverOrderNavigation(playerid);
						
						Remove:fuber_order_by_passenger_id(playerid);
					}
					
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно отменили заказ.");
				}
			}
			
			ShowFuberPassengerDialog(playerid, D_PHONE_APP_FUBER + 1);
		}
		
		case D_PHONE_APP_FUBER + 3: 
		{
			if (response)
			{
				DeletePVar(playerid, "Phone:HideCursor");
				DeletePVar(playerid, "Fuber:SelectMap");
				ShowFuberPassengerOrderDialog(playerid, D_PHONE_APP_FUBER + 2);
			}
			else 
			{
				SetPVarInt(playerid, "Admin:MapTeleportIgnore", true);
				SendClientMessage(playerid, C_WHITE, #DEFAULT " Перейдите в меню паузы или используйте " #cPROJECT "/cancelfuber" #cWHITE", чтобы отменить действие.");
			}
		}
		
		case D_PHONE_APP_FUBER + 4:
		{
			if (!response)
			{
				ShowFuberPassengerOrderDialog(playerid, D_PHONE_APP_FUBER + 2);
				return 1;
			}
			
			if (isnull(inputtext))
			{
				ShowFuberPassengerWishDialog(playerid, D_PHONE_APP_FUBER + 4,
					"Вы ввели неверное значение."
				);
				
				return 1;
			}
			
			SetPVarString(playerid, "Fuber:Wish", inputtext);
			SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы успешно отредактировали комментарий.");
			
			ShowFuberPassengerOrderDialog(playerid, D_PHONE_APP_FUBER + 2);
		}
		
		case D_PHONE_APP_FUBER + 6:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_PHONE + 12, DIALOG_STYLE_LIST, "Apps", DIALOG_PHONE_APPS, "Выбрать", "Закрыть");
				return 1;
			}

			new order_index = GetFuberDriverOrderIndex(playerid);
			
			if (listitem == 0) // Найти заказ
			{ 
				if (!HasFuberDriverVehicle(playerid))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Для начала работы, сперва необходимо выйти на линию.");
				}
				else 
				{
					if (!HasFuberDriverOrder(playerid))
					{
						ShowFuberDriverOrders(playerid, D_PHONE_APP_FUBER + 7);
					}
					else 
					{
						ShowFuberDriverOrderDialog(playerid, D_PHONE_APP_FUBER + 9, order_index);
					}
					
					return 1;
				}
			}
			else if (listitem == 1) // На линии 
			{
				if (HasFuberDriverOrder(playerid))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Завершите поездку, прежде чем уйти с с линии.");
				}
				else 
				{
					new vehicleid = GetPlayerVehicleID(playerid),
						modelid = GetVehicleModel(vehicleid);
					
					if (!IsFuberValidVehicle(modelid))
					{
						SendClientMessage(playerid, C_WHITE, !#ERROR " Данный транспорт не подходит для таксования. Для подробной информации, используйте - " #cPROJECT "/job" #cWHITE ".");
					}
					else 
					{
						if (HasFuberDriverVehicle(playerid))
						{
							SetFuberDriverVehicleId(playerid, INVALID_VEHICLE_ID);
							SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно ушли с линии.");
						}
						else 
						{
							if (HasFuberDriverBan(playerid))
							{
								pformat:(#ERROR " Вы были заблокированы на день, за низкую репутацию. Блокировка спадет через %d часов.",
									(character_data[playerid][c_fuber_reputation_time] + (24 * 60 * 60)) - gettime()
								);
								
								psend:(playerid, C_WHITE);
							}
							else 
							{
								SetFuberDriverVehicleId(playerid, vehicleid);
								SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно вышли на линию.");
							}
						}
					}
				}
			}
			else if (listitem == 2) // Баланс
			{
				new balance = GetFuberDriverBalance(playerid);
			
				if (balance > 0)
				{
					GiveDebitCardMoney(playerid, 
						balance
					);
					
					SetFuberDriverBalance(playerid, 0);
					
					format:g_small_string(#SMS_MESSAGE " От Los Santos Bank: Зачисление средств на карту (%d) от Fuber - в размере $%d.", 
						GetCharacterCardNumber(playerid),
						balance
					);
					
					SendSplitMessage(playerid, C_DARKYELLOW, g_small_string);
				}
				else 
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Вывод средств невозможен, так как Ваш баланс равен нулю.");
				}
			}
			else if (listitem == 4) // Мои поездки
			{
				SetPVarInt(playerid, "Fuber:TripDriverDialog", true);
				ShowFuberTrips(playerid, D_PHONE_APP_FUBER + 10, true);
			}
			
			ShowFuberDriverDialog(playerid, D_PHONE_APP_FUBER + 6);
		}
		
		case D_PHONE_APP_FUBER + 7:
		{
			if (!response)
			{
				ShowFuberDriverDialog(playerid, D_PHONE_APP_FUBER + 6);
				return 1;
			}
			
			new index = g_dialog_select[playerid][listitem];
		
			if (index == ITEM_LIST_BACK || index == ITEM_LIST_NEXT)
			{
				ShowFuberDriverOrders(playerid, index);
				return 1;
			}
			
			SetPVarInt(playerid, "Fuber:SelectDriverOrder", index);
			ShowFuberDriverOrderDialog(playerid, D_PHONE_APP_FUBER + 8, index);
		}
		
		case D_PHONE_APP_FUBER + 8:
		{
			if (response)
			{
				new index = GetPVarInt(playerid, "Fuber:SelectDriverOrder");
				
				if (listitem == 4)
				{
					AcceptFuberOrder(playerid, index);
				}
				else 
				{
					ShowFuberDriverOrderDialog(playerid, D_PHONE_APP_FUBER + 8, index);
				}
				
				DeletePVar(playerid, "Fuber:SelectDriverOrder");
			}
			else
			{
				DeletePVar(playerid, "Fuber:SelectDriverOrder");
				ShowFuberDriverOrders(playerid, D_PHONE_APP_FUBER + 7, ITEM_LIST_CURRENT);
			}
		}
		
		case D_PHONE_APP_FUBER + 9:
		{
			if (response)
			{
				new order_index = GetFuberDriverOrderIndex(playerid);
				
				if (listitem == 5)
				{
					new first_name	[MAX_PLAYER_NAME];
					
					// Статус
					fuber_orders[order_index][fub_status] = FUB_ORDER_SEARCH;
					
					GetFuberDriverFirstName(playerid, first_name);
					
					pformat:(#FUBER_MESSAGE " Водитель %s отказался от Вашего заказа. Идёт поиск водителя...",
						first_name
					);
					
					psend:(fuber_orders[order_index][fub_passenger_id], C_YELLOW);
				}
				else if (listitem == 4)
				{	
					if (IsPlayerInDynamicArea(playerid, fuber_driver_start_area[playerid]))
					{
						ArrivedFuberDriver(playerid);
					}
					else
					{
						SendClientMessage(playerid, C_WHITE, !#ERROR " Вы слишком далеко находитесь от места вызова.");
					}
				}
				else 
				{
					ShowFuberDriverOrderDialog(playerid, D_PHONE_APP_FUBER + 9, order_index);
				}
			}
			else 
			{
				ShowFuberDriverDialog(playerid, D_PHONE_APP_FUBER + 6);
			}
		}
		
		case D_PHONE_APP_FUBER + 10:
		{
			if (!response)
			{
				if (GetPVarInt(playerid, "Fuber:TripDriverDialog"))
				{
					ShowFuberDriverDialog(playerid, D_PHONE_APP_FUBER + 6);
				}
				else 
				{
					ShowFuberPassengerDialog(playerid, D_PHONE_APP_FUBER + 1);
				}
				
				return 1;
			}
			
			new id = g_dialog_select[playerid][listitem];
			
			ShowFuberTripById(playerid, D_PHONE_APP_FUBER + 11, id);
		}
		
		case D_PHONE_APP_FUBER + 11:
		{
			if (response) // Отзыв
			{
				ShowPlayerDialog(playerid, D_PHONE_APP_FUBER + 12, DIALOG_STYLE_LIST, " ", #cGRAY "Понравилась ли Вам поездка?" #cWHITE "\n \
					Да\n \
					Нет",
					"Выбрать", "Назад"
				);
			}
			else // Назад
			{
				ShowFuberTrips(playerid, D_PHONE_APP_FUBER + 10);
				
				DeletePVar(playerid, "Fuber:TripId");
				DeletePVar(playerid, "Fuber:TripDriverId");
				DeletePVar(playerid, "Fuber:TripPassengerId");
			}
		}
		
		case D_PHONE_APP_FUBER + 12:
		{
			if (response)
			{
				if (listitem == 0)
				{
					ShowPlayerDialog(playerid, D_PHONE_APP_FUBER + 12, DIALOG_STYLE_LIST, " ", #cGRAY "Понравилась ли Вам поездка?" #cWHITE "\n \
						Да\n \
						Нет",
						"Выбрать", "Назад"
					);
					
					return 1;
				}
				
				new trip_id = GetPVarInt(playerid, "Fuber:TripId"),
					driver_character_id = GetPVarInt(playerid, "Fuber:TripDriverId"),
					passenger_character_id = GetPVarInt(playerid, "Fuber:TripPassengerId"),
					reputation = listitem == 1 ? 1 : -1,
					passenger_reputation = GetPVarInt(playerid, "Fuber:TripDriverReputation"),
					driver_reputation = GetPVarInt(playerid, "Fuber:TripPassengerReputation");
				
				if ((driver_character_id == GetCharacterId(playerid) && driver_reputation)
				|| (passenger_character_id == GetCharacterId(playerid) && passenger_reputation))
				{
					ShowFuberTripById(playerid, D_PHONE_APP_FUBER + 11, 
						GetPVarInt(playerid, "Fuber:TripId")
					);
					
					SendClientMessage(playerid, C_WHITE, #ERROR " Вы уже оставляли отзыв.");
					return 1;
				}
					
				new bool: changed = false,
					current_reputation;
					
				foreach (new i : Player)
				{
					if (!IsPlayerLogged(i))
					{
						continue;
					}
					
					if (i == playerid)
					{
						continue;
					}
					
					if (GetCharacterId(i) == driver_character_id
					|| GetCharacterId(i) == passenger_character_id)
					{
						current_reputation = GetFuberReputation(i) + reputation;
						
						if (current_reputation > MAX_FUBER_REPUTATION)
						{
							current_reputation = MAX_FUBER_REPUTATION;
						}
						else
						{
							current_reputation = MIN_FUBER_REPUTATION;
						}
						
						SetFuberReputation(i, current_reputation);
						
						changed = true;
						break;
					}
				}
				
				if (!changed)
				{
					format:g_string("UPDATE " #__CHARACTERS " \
						SET c_fuber_reputation = IF(c_fuber_reputation > %s" #MAX_FUBER_REPUTATION ", c_fuber_reputation, c_fuber_reputation %s 1)  \
						WHERE c_id = %d \
						LIMIT 1",
						reputation > 0 ? ("") : ("-"),
						reputation > 0 ? ("+") : ("-"),
						GetCharacterId(playerid) == passenger_character_id ? driver_character_id : passenger_character_id
					);
					
					mysql_tquery(db, g_string);
				}
				
				format:g_string("UPDATE " #__FUBER_TRIPS " SET fub_%s_reputation = 1 WHERE fub_id = %d",
					GetCharacterId(playerid) == passenger_character_id ? ("passenger") : ("driver"),
					trip_id
				);
				
				mysql_tquery(db, g_string);
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно оставили отзыв о поездке.");
			}
			
			ShowFuberTripById(playerid, D_PHONE_APP_FUBER + 11, 
				GetPVarInt(playerid, "Fuber:TripId")
			);
		}
	}
	
	return 1;
}