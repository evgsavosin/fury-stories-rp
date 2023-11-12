/*!
	@brief Приложение Fuber для системы телефона
	@author Found (evg.savosin)
	@date 28.08.2019
*/

// Clear
Clear:fuber_order_pvar(playerid)
{
	DeletePVar(playerid, "Fuber:PosX");
	DeletePVar(playerid, "Fuber:PosY");
	DeletePVar(playerid, "Fuber:PosZ");
	DeletePVar(playerid, "Fuber:SelectMap");
	DeletePVar(playerid, "Fuber:PosExists");
	DeletePVar(playerid, "Fuber:Wish");
}

// Public functions
_Phone_OnGameModeInit()
{
	for (new i; i < sizeof fuber_orders; i++)
	{
		Clear:fuber_order(i);
	}
}

_Phone_OnPlayerClickMap(playerid, Float: fX, Float: fY, Float: fZ)
{
	if (!GetPVarInt(playerid, "Fuber:SelectMap"))
	{
		return 1;
	}
	
	SetPVarFloat(playerid, "Fuber:PosX", fX);
	SetPVarFloat(playerid, "Fuber:PosY", fY);
	SetPVarFloat(playerid, "Fuber:PosZ", fZ);
	SetPVarInt(playerid, "Fuber:PosExists", true);
	DeletePVar(playerid, "Fuber:SelectMap");
	DeletePVar(playerid, "Admin:MapTeleportIgnore");
	
	// Курсор телефона
	ShowPhoneCursor(playerid, true);
	
	ShowFuberPassengerOrderDialog(playerid, D_PHONE_APP_FUBER + 2);
	
	SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы успешно проложили маршрут поездки.");
	return 1;
}

_Phone_OnPlayerEnterDynamicArea(playerid, areaid)
{
	if (areaid == fuber_driver_start_area[playerid] 
	&& GetFuberDriverVehicleId(playerid) == GetPlayerVehicleID(playerid))
	{	
		new order_index = GetFuberDriverOrderIndex(playerid),
			passenger_id = fuber_orders[order_index][fub_passenger_id],
			status = fuber_orders[order_index][fub_status];
			
		if (status == FUB_ORDER_WAY)
		{
			new balance = GetFuberDriverBalance(playerid);
			
			// Пополняем баланс водителя
			SetFuberDriverBalance(playerid, balance + GetFuberOrderFullCost(order_index) + FUBER_BONUS_COST);
			
			// Обнуляем заказ у водителя и пассажира
			SetFuberDriverOrderIndex(playerid, INVALID_PARAM);
			SetFuberPassengerOrderIndex(passenger_id, INVALID_PARAM);
			
			// Обнуляем метки
			ResetDriverOrderNavigation(playerid);
			
			// Добавляем поездки
			Create:fuber_trip(order_index);
			
			// Удаляем заказ
			Clear:fuber_order(order_index);
			
			SendClientMessage(playerid, C_YELLOW, !#FUBER_MESSAGE " Вы прибыли на место назначения. Поездка завершена.");
			SendClientMessage(passenger_id, C_YELLOW, !#FUBER_MESSAGE " Поездка была завершена. Оставить отзыв о поездке вы можете в приложении.");
		}
	}
	
	return 1;
}

_Phone_OnPlayerStateChange(playerid, newstate, oldstate)
{	
	if (oldstate == PLAYER_STATE_ONFOOT 
	&& newstate == PLAYER_STATE_PASSENGER)
	{
		if (HasFuberPassengerOrder(playerid))
		{
			new order_index = GetFuberPassengerOrderIndex(playerid),
				driver_id = fuber_orders[order_index][fub_driver_id];

			if (driver_id != INVALID_PLAYER_ID && GetFuberDriverVehicleId(driver_id) == GetPlayerVehicleID(driver_id))
			{
				new first_name	[MAX_PLAYER_NAME];
				
				// Статус
				fuber_orders[order_index][fub_status] = FUB_ORDER_WAY;
				
				if (fuber_driver_start_area[driver_id] != INVALID_STREAMER_ID)
				{
					ResetDriverOrderNavigation(driver_id, true);
				}
				
				// Чекпоинт
				SetDriverOrderNavigation(driver_id, 
					fuber_orders[order_index][fub_end_pos_x], 
					fuber_orders[order_index][fub_end_pos_y], 
					fuber_orders[order_index][fub_end_pos_z]
				);
				
				// Имя водителя
				GetFuberDriverFirstName(driver_id, first_name);
				
				new cost = fuber_orders[order_index][fub_cost];
				
				if (!PayFuberOrderByPaymentMethod(playerid, -cost))
				{
					fuber_orders[order_index][fub_cost] = floatround(fuber_orders[order_index][fub_cost] / 1.5);
					
					new reputation = GetFuberReputation(playerid);

					if (reputation > MIN_FUBER_REPUTATION)
					{
						SetFuberReputation(playerid, reputation - 1); 
						
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
						SendClientMessage(playerid, C_YELLOW, !#FUBER_MESSAGE " Ваша репутация в приложении Fuber была понижена. Приоритет будущих заказов снижен.");
					}
				}
				else 
				{
					new reputation = GetFuberReputation(playerid);
					
					if (reputation < MAX_FUBER_REPUTATION)
					{
						SetFuberReputation(playerid, GetFuberReputation(playerid) + 1);
						SendClientMessage(playerid, C_YELLOW, !#FUBER_MESSAGE " Ваша репутация в приложении Fuber была повышена. Приоритет будущих заказов повышен.");
					}
				}
				
				SendClientMessage(driver_id, C_YELLOW, !#FUBER_MESSAGE " Доставьте клиента до места назначения.");
				
				pformat:(#FUBER_MESSAGE " За рулем водитель %s. Приятной поездки!",
					first_name
				);
				
				psend:(playerid, C_YELLOW);
			}
		}
	}
	
	return 1;
}

_Phone_OnPlayerEnterCheckpoint(playerid)
{
	if (IsPlayerInDynamicArea(playerid, fuber_driver_start_area[playerid]))
	{
		ArrivedFuberDriver(playerid);
	}
	
	return 1;
}	

_Phone_OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	
	if (HasFuberPassengerOrder(playerid))
	{
		new order_index = GetFuberPassengerOrderIndex(playerid),
			driver_id = fuber_orders[order_index][fub_driver_id];
		
		if (driver_id != INVALID_PLAYER_ID)
		{
			PayFuberOrderByPaymentMethod(playerid, fuber_orders[order_index][fub_cost]);
			
			SendClientMessage(playerid, C_WHITE, !#ERROR " Заказ в Fuber был отменён, так как пассажир не в сети.");
			SetFuberDriverOrderIndex(driver_id, INVALID_PARAM);
		}
		
		Clear:fuber_order(order_index);
	}
	else if (HasFuberDriverOrder(playerid))
	{
		new order_index = GetFuberDriverOrderIndex(playerid),
			passenger_id = fuber_orders[order_index][fub_passenger_id];
		
		if (passenger_id != INVALID_PLAYER_ID)
		{
			if (PayFuberOrderByPaymentMethod(passenger_id, fuber_orders[order_index][fub_cost]))
			{
				SendClientMessage(playerid, C_WHITE, #SUCCESS " Средства, отданные за поездку, были возвращены.");
			}
			
			SendClientMessage(playerid, C_WHITE, !#ERROR " Заказ в Fuber был отменён, так как водитель не в сети.");
			SetFuberDriverOrderIndex(passenger_id, INVALID_PARAM);
		}
		
		Clear:fuber_order(order_index);
	}
	
	return 1;
}

function PAY:set_fuber_method_payment(playerid, status, type)
{
	SetFuberMethodPayment(playerid, type);
	ShowFuberPassengerDialog(playerid, D_PHONE_APP_FUBER + 1);
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно изменили метод оплаты.");
	return 1;
}

// Functions
ArrivedFuberDriver(playerid)
{
	new first_name	[MAX_PLAYER_NAME],
		order_index = GetFuberDriverOrderIndex(playerid),
		passenger_id = fuber_orders[order_index][fub_passenger_id];
		
	// Статус
	fuber_orders[order_index][fub_status] = FUB_ORDER_ARRIVED;
	
	// Имя водителя
	GetFuberDriverFirstName(playerid, first_name);
	
	SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы прибыли на место назначения, ожидайте клиента.");
	
	pformat:(#FUBER_MESSAGE " Водитель %s прибыл и ожидает Вас.",
		first_name
	);
	
	psend:(passenger_id, C_YELLOW);
	
	ResetDriverOrderNavigation(playerid);
}

PayFuberOrderByPaymentMethod(playerid, cost)
{
	new method_payment = GetFuberMethodPayment(playerid),
		bool: paid = false;
	
	if (method_payment == TYPE_PAY_MONEY)
	{
		if (GivePlayerCash(playerid, cost))
		{
			paid = true;
		}
	}
	else if (method_payment == TYPE_PAY_CARD)
	{
		if (GiveDebitCardMoney(playerid, cost))
		{
			paid = true;
		}
	}
	else if (method_payment == TYPE_PAY_CREDIT)
	{
		if (GiveCreditCardMoney(playerid, cost))
		{
			paid = true;
		}
	}
	
	return paid;
}

SetDriverOrderNavigation(playerid, Float: x, Float: y, Float: z)
{
	SetPlayerCheckpoint(playerid, 
		x,
		y,
		z,
		6.0
	);
	
	fuber_driver_start_area[playerid] = CreateDynamicCircle(
		x,
		y,
		50.0,
		_,
		_,
		playerid
	);
}

ResetDriverOrderNavigation(playerid, bool: disable_checkpoint = true)
{
	DestroyDynamicArea(fuber_driver_start_area[playerid]);
	fuber_driver_start_area[playerid] = INVALID_STREAMER_ID;
	
	if (disable_checkpoint)
	{
		DisablePlayerCheckpoint(playerid);
	}
}

AcceptFuberOrder(playerid, index)
{
	new Float: x,
		Float: y,
		Float: z;
		
	GetPlayerPos(playerid, x, y, z);
	
	new distance,
		time,
		first_name	[MAX_PLAYER_NAME],
		passenger_id = fuber_orders[index][fub_passenger_id];
	
	new time_text 	[32];
	
	// Дистанция
	distance = floatround(GetDistanceBetweenPoints(
		x,
		y,
		z,
		fuber_orders[index][fub_start_pos_x], 
		fuber_orders[index][fub_start_pos_y], 
		fuber_orders[index][fub_start_pos_z]
	));
	
	// Вреия
	time = CalculateApproximateTime(distance);
	
	// Меняем статус
	fuber_orders[index][fub_status] = FUB_ORDER_AWAITING;
	fuber_orders[index][fub_driver_id] = playerid;
	
	// Получаем имя водителя
	GetFuberDriverFirstName(playerid, first_name);
	
	// Устанавливаем
	SetFuberDriverOrderIndex(playerid, index);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы приняли заказ. На GPS навигаторе была отмечена точка посадки клиента.");
	
	if (time == 0)
	{
		strcat(time_text, "скоро приедет");
	}
	else
	{
		format:time_text("приедет примерно через %d мин", time);
	}
	
	pformat:(#FUBER_MESSAGE " На Ваш заказ был назначен водитель %s, который %s.",
		first_name,
		time_text
	);
	
	psend:(passenger_id, C_YELLOW);
	
	// Чекпоинт
	SetDriverOrderNavigation(
		playerid, 
		fuber_orders[index][fub_start_pos_x], 
		fuber_orders[index][fub_start_pos_y],
		fuber_orders[index][fub_start_pos_z]
	);
}

Update:fuber_order(playerid)
{
	new order_index = GetFuberPassengerOrderIndex(playerid);
	
	if (!GetPVarInt(playerid, "Fuber:PosExists"))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вам необходимо указать место доставки.");
		return;
	}
	
	if (HasFuberPassengerOrder(playerid))
	{
		if (fuber_orders[order_index][fub_status] > FUB_ORDER_SEARCH)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете отредактировать заказ, так как его уже взял водитель.");
			return;
		}
	}
	
	// Место доставки
	new Float: start_x,
		Float: start_y,
		Float: start_z,
		Float: x = GetPVarFloat(playerid, "Fuber:PosX"),
		Float: y = GetPVarFloat(playerid, "Fuber:PosY"),
		Float: z = GetPVarFloat(playerid, "Fuber:PosZ"),
		Float: distance;
	
	GetPlayerPos(playerid, start_x, start_y, start_z);
	
	// Пожелание
	new wish	[MAX_FUBER_WISH_LENGTH];
	
	GetPVarString(playerid, "Fuber:Wish", wish, sizeof wish);
	
	SendClientMessage(playerid, C_WHITE, !HasFuberPassengerOrder(playerid) ? 
		(SUCCESS " Вы успешно оформили заказ, ожидайте.")
		: (SUCCESS " Вы успешно отредактировали заказ.")
	);
	
	new bool: is_update = HasFuberPassengerOrder(playerid);
	
	order_index = UpdateFuberOrder(playerid, 
		x, 
		y, 
		z, 
		wish
	);
	
	if (!is_update)
	{
		foreach (new driver : Player)
		{
			distance = GetPlayerDistanceFromPoint(driver, start_x, start_y, start_z);
			
			if (!IsPlayerLogged(driver) || floatcmp(distance, 100.0) == 1)
			{
				continue;
			}
			
			if (!HasFuberDriverVehicle(driver) || HasFuberDriverOrder(driver))
			{
				continue;
			}
			
			pformat:(#FUBER_MESSAGE " На Вас был назначен заказ на расстоянии %0.1fm.",
				distance
			);
			
			psend:(driver, C_YELLOW);
			
			AcceptFuberOrder(driver, order_index);
			break;
		}
	}
	
	if (!order_index)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вам не удалось оформить заказ, повторите позднее.");
		return;
	}
}

UpdateFuberOrder(playerid, Float: end_pos_x, Float: end_pos_y, Float: end_pos_z, wish[MAX_FUBER_WISH_LENGTH])
{
	new Float: start_pos[3],
		cost,
		order_index = HasFuberPassengerOrder(playerid) ? GetFuberPassengerOrderIndex(playerid) : 0;
	
	for (new i = order_index; i < sizeof fuber_orders; i++)
	{
		if ((!HasFuberPassengerOrder(playerid) && fuber_orders[i][fub_passenger_id] == INVALID_PLAYER_ID)
		|| HasFuberPassengerOrder(playerid) && fuber_orders[i][fub_passenger_id] == playerid)
		{
			GetPlayerPos(playerid, start_pos[0], start_pos[1], start_pos[2]);
			
			cost = CalculateFuberCost(
				start_pos[0],
				start_pos[1],
				start_pos[2],
				end_pos_x,
				end_pos_y,
				end_pos_z
			);
			
			if (cost == 0)
			{
				break;
			}
			
			clean:<fuber_orders[i][fub_wish]>;
			strcat(fuber_orders[i][fub_wish], wish, MAX_FUBER_WISH_LENGTH);
			fuber_orders[i][fub_passenger_id] = playerid;
			fuber_orders[i][fub_cost] = cost;
			
			fuber_orders[i][fub_start_pos_x] = start_pos[0];
			fuber_orders[i][fub_start_pos_y] = start_pos[1];
			fuber_orders[i][fub_start_pos_z] = start_pos[2];
			
			fuber_orders[i][fub_end_pos_x] = end_pos_x;
			fuber_orders[i][fub_end_pos_y] = end_pos_y;
			fuber_orders[i][fub_end_pos_z] = end_pos_z;
			
			// Passenger data
			fuber_passenger_order_index[playerid] = i;
			
			return i;
		}
	}
	
	return 0;
}

Remove:fuber_order_by_passenger_id(playerid)
{
	Clear:fuber_passenger(playerid);
	
	for (new i, driver_id; i < sizeof fuber_orders; i++)
	{
		if (fuber_orders[i][fub_passenger_id] == playerid)
		{
			if ((driver_id = fuber_orders[i][fub_driver_id]) != INVALID_PLAYER_ID)
			{
				SetFuberDriverOrderIndex(driver_id, INVALID_PARAM);
			}
		
			Clear:fuber_order(i);
			
			return 1;
		}
	}
	
	return 0;
}

GetFuberOrdersCount()
{
	new count;
	
	for (new i; i < sizeof fuber_orders; i++)
	{
		if (fuber_orders[i][fub_passenger_id] != INVALID_PLAYER_ID)
		{
			count++;
		}
	}
	
	return count;
}

GetFuberDriversOnline()
{
	new count;
	
	foreach (new playerid : Player)
	{
		if (fuber_driver_order_index[playerid] != INVALID_VEHICLE_ID)
		{
			count++;
		}
	}
	
	return count;
}

CalculateFuberCost(Float: start_x, Float: start_y, Float: start_z, Float: end_x, Float: end_y, Float: end_z)
{
	new cost,
		distance = floatround(GetDistanceBetweenPoints(
			start_x, 
			start_y, 
			start_z, 
			end_x, 
			end_y, 
			end_z
		));
	
	// Если дистанция настолько мала, то отказываем в заказе
	if (distance < (FUBER_PER_FIFTY_COST * 2))
	{
		return 0;
	}

	if (_: end_x == _: 0.0 && _: end_y == _: 0.0 && _: end_z == _: 0.0)
	{
		return FUBER_BASE_COST;
	}
	
	// За каждые FUBER_PER_FIFTY_COST метров цена возрастает на $2
	cost += floatround(distance / FUBER_PER_FIFTY_COST) * 2;
	
	// Если водителей не так мало на количество заказов большое, то повышаем цену
	cost += CalculateApproximatePrice();
	
	return cost;
}

CalculateApproximatePrice()
{
	new orders = GetFuberOrdersCount(),
		drivers = GetFuberDriversOnline();
		
	return FUBER_BASE_COST + floatround(orders / (drivers * 2), floatround_floor);
}

CalculateApproximateTime(distance)
{
	new time = floatround(distance / (FUBER_AVERAGE_SPEED * 2));
	return time < 0 ? 0 : time;
}

GetFuberDriverFirstName(playerid, first_name[])
{
	new name 		[MAX_PLAYER_NAME],
		tmp			[1];
	
	strcat(name, GetPlayerCurrentName(playerid), sizeof name);
	sscanf(name, "s[24]s[24]", first_name, tmp);
}

GetFuberDriverReputationText(playerid, text[], len)
{
	new reputation = GetFuberDriverReputation(playerid);
	
	switch (reputation)
	{
		case -10 .. -5:
		{
			strcat(text, #cRED "Негативная" #cWHITE, len);
		}
		
		case 0:
		{
			strcat(text, #cGRAY "Нейтральная" #cWHITE, len);
		}
		
		case 5 .. 10:
		{
			strcat(text, #cGREEN "Положительная" #cWHITE, len);
		}
	}
}

IsFuberValidVehicle(modelid)
{
	switch (modelid)
	{
		case 420, 438:
		{
			return 1;
		}
	}
	
	return 0;
}

CheckFuberValidOwnVehicles(playerid)
{
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		if (!IsFuberValidVehicle(player_vehicle[playerid][pv_model][i]))
		{
			continue;
		}
		
		return 1;
	}
	
	return 0;
}

HasFuberDriverBan(playerid)
{
	return (GetFuberReputation(playerid) <= -5 && character_data[playerid][c_fuber_reputation_time] + (24 * 60 * 60) > gettime());
}

// Dialogs
ShowFuberDriverDialog(playerid, const dialogid)
{
	if (!CheckFuberValidOwnVehicles(playerid))
	{
		ShowPlayerDialog(playerid, D_PHONE_APP_FUBER + 5, DIALOG_STYLE_MSGBOX, "Fuber Driver", 
			"" #ERROR " Информация\n\n\
			Для того, чтобы использовать " #cPROJECT "Fuber Driver" #cWHITE ", Вам необходимо иметь\n\
			специализированный транспорт, который будет отвечать требованиям " #cPROJECT "Fuber" #cWHITE".\n\n\
			Арендовать транспорт можно у партнёра " #cPROJECT "Fuber" #cWHITE " — TA (Транспортное агенство).", 
			"Выйти", ""
		);
		
		return 1;
	}
	
	if (HasFuberPassengerOrder(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете использовать Fuber Driver, используя Fuber Passenger.");
		return 1;
	}

	new order_text 			[32],
		online_status_text	[32],
		reputation_text		[32];
	
	// На линии с транспорта
	if (HasFuberDriverVehicle(playerid))
	{
		strcat(online_status_text, #cGREEN "Да");
	}
	else 
	{
		strcat(online_status_text, #cRED "Нет");
	}
	
	if (HasFuberDriverOrder(playerid))
	{
		strcat(order_text, "Управление заказом\t");
	}
	else 
	{
		format:order_text("Найти заказ\t" #cPROJECT "%d" #cWHITE "", GetFuberOrdersCount());
	}
	
	// Репутация
	GetFuberDriverReputationText(playerid, reputation_text, sizeof reputation_text);
	
	format:g_string(" \
		%s\n \
		На линии\t%s" #cWHITE "\n \
		Баланс\t" #cGREEN "$%d" #cWHITE "\n \
		Репутация\t" #cPROJECT "%s" #cWHITE "\n \
		Мои поездки\t",
		order_text,
		online_status_text,
		GetFuberDriverBalance(playerid),
		reputation_text
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, "Fuber Driver", g_string, "Далее", "Назад");
	
	return 1;
}

ShowFuberDriverOrderDialog(playerid, const dialogid, index)
{
	new start_zone_name	[64],
		end_zone_name	[64];
	
	GetZoneName(
		fuber_orders[index][fub_start_pos_x],
		fuber_orders[index][fub_start_pos_y],
		start_zone_name,
		sizeof start_zone_name
	);
	
	GetZoneName(
		fuber_orders[index][fub_end_pos_x],
		fuber_orders[index][fub_end_pos_y],
		end_zone_name,
		sizeof end_zone_name
	);
	
	new action_text		[128];
	
	if (HasFuberDriverOrder(playerid))
	{
		strcat(action_text, "" #cGRAY "На месте" #cWHITE "\t\n \
			" #cRED "Завершить поездку\t"
		);
	}
	else 
	{
		strcat(action_text, "" #cPROJECT "Принять заказ" #cWHITE "\t");
	}
	
	format:g_string(" \
		Откуда\t" #cPROJECT "%s" #cWHITE "\n \
		Куда\t" #cPROJECT "%s" #cWHITE "\n \
		Цена\t" #cGREEN "$%d" #cWHITE "\n \
		Комментарий\t" #cPROJECT "%s" #cWHITE "\n \
		%s\
		",
		start_zone_name,
		end_zone_name,
		GetFuberOrderFullCost(index),
		fuber_orders[index][fub_wish],
		action_text
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, "Fuber Driver", g_string, "Выбрать", "Назад");
	
	return 1;
}

ShowFuberPassengerDialog(playerid, const dialogid)
{
	if (HasFuberDriverVehicle(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете использовать Fuber Passenger, используя Fuber Driver.");
		return 1;
	}
				
	new status_text	[32],
		order_index = GetFuberPassengerOrderIndex(playerid),
		method_payment = GetFuberMethodPayment(playerid);
	
	if (order_index != INVALID_PARAM)
	{
		format:status_text(#cGRAY "%s", 
			GetFuberOrderStatus(order_index)
		);
	}
	else 
	{
		format:status_text(#cGREEN "От $%d", 
			CalculateApproximatePrice()
		);
	}
	
	format:g_string(" %s\t%s" #cWHITE "\n \
		  Мои поездки\t\n \
		  Способ оплаты\t" #cPROJECT "%s" #cWHITE,
		HasFuberPassengerOrder(playerid) ? ("Управление заказом") : ("Заказать поездку"),
		status_text,
		GetPaymentTypeText(method_payment)
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_LIST, "Fuber", 
		g_string, 
		"Выбрать", "Назад"
	);
	
	return 1;
}

ShowFuberPassengerOrderDialog(playerid, const dialogid)
{
	new order_index = GetFuberPassengerOrderIndex(playerid);
	
	if (HasFuberPassengerOrder(playerid))
	{
		// Конечная позиция
		SetPVarFloat(playerid, "Fuber:PosX", fuber_orders[order_index][fub_end_pos_x]);
		SetPVarFloat(playerid, "Fuber:PosY", fuber_orders[order_index][fub_end_pos_y]);
		SetPVarFloat(playerid, "Fuber:PosZ", fuber_orders[order_index][fub_end_pos_z]);
		SetPVarInt(playerid, "Fuber:PosExists", true);
		
		// Пожелание
		SetPVarString(playerid, "Fuber:Wish", fuber_orders[order_index][fub_wish]);
	}

	new zone_text			[32],
		wish_text			[32];
	
	// Куда
	new Float: end_x = GetPVarFloat(playerid, "Fuber:PosX"),
		Float: end_y = GetPVarFloat(playerid, "Fuber:PosY"),
		Float: end_z = GetPVarFloat(playerid, "Fuber:PosZ");
	
	if (GetPVarInt(playerid, "Fuber:PosExists"))
	{
		GetZoneName(
			end_x,
			end_y,
			zone_text,
			sizeof zone_text
		);
		
		format:zone_text(#cPROJECT "%s", zone_text);
	}
	else 
	{
		strcat(zone_text, #cGRAY "Не указано");
	}
	
	// Пожелания
	new wish	[64];
	
	GetPVarString(playerid, "Fuber:Wish", wish, sizeof wish);

	if (!isnull(wish))
	{
		strcat(wish_text, #cPROJECT "Указано");
	}
	else 
	{
		strcat(wish_text, #cGRAY "Не указано");
	}
	
	// Итоговая стоимость
	new Float: start_x,
		Float: start_y,
		Float: start_z;
	
	GetPlayerPos(playerid, start_x, start_y, start_z);
	
	new cost = CalculateFuberCost(start_x, start_y, start_z, end_x, end_y, end_z);
	
	cost = cost == 0 ? FUBER_BASE_COST : cost;
	
	format:g_string(" \
		Куда\t%s\n \
		Комментарий\t%s\n \
		Итоговая стоимость:\t" #cGREEN "$%d\n \
		" #cGRAY "%s заказ\n \
		" #cRED "Отменить",
		zone_text,
		wish_text,
		cost,
		!HasFuberPassengerOrder(playerid) ? ("Оформить") : ("Отредактировать")
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, "Fuber", 
		g_string, 
		"Выбрать", "Назад"
	);
}

ShowFuberPassengerWishDialog(playerid, const dialogid, error[] = "")
{
	new wish_text [128];
	
	GetPVarString(playerid, "Fuber:Wish", wish_text, sizeof wish_text);
	
	format:g_string("\
		" #DEFAULT " Пожелание\n\n\
		%s%sВведите текст пожелания:%s",
		wish_text,
		isnull(wish_text) ? ("") : ("\n\n"),
		isnull(error) ? ("") : ("\n\n" cRED),
		error
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_INPUT, "Fuber", 
		g_string, 
		"Далее", "Назад"
	);
}

ShowFuberDriverOrders(playerid, const dialogid, action = ITEM_LIST_BEGIN)
{
	clean:<g_string>;
	
	new count,
		page;
		
	new start_zone_name	[64],
		end_zone_name	[64];
	
	if (action == ITEM_LIST_BEGIN)
	{
		SetPVarInt(playerid, "Fuber:Page", 0);
		page = 0;
	}
	else if (action == ITEM_LIST_CURRENT)
	{
		page = GetPVarInt(playerid, "Fuber:Page");
	}
	else if (action == ITEM_LIST_NEXT)
	{
		GivePVarInt(playerid, "Fuber:Page", 1);
		page = GetPVarInt(playerid, "Fuber:Page");
	}
	else if (action == ITEM_LIST_BACK)
	{
		TakePVarInt(playerid, "Fuber:Page", 1);
		page = GetPVarInt(playerid, "Fuber:Page");
	}
	
	format:g_string(#cPROJECT "Откуда\t" #cPROJECT "Куда\t" #cPROJECT "Цена поездки\n");
	
	for (new i = page * MAX_ITEM_LIST; i < sizeof fuber_orders; i++)
	{
		if (IsFuberOrderValid(i))
		{
			GetZoneName(
				fuber_orders[i][fub_start_pos_x],
				fuber_orders[i][fub_start_pos_y],
				start_zone_name,
				sizeof start_zone_name
			);
			
			GetZoneName(
				fuber_orders[i][fub_end_pos_x],
				fuber_orders[i][fub_end_pos_y],
				end_zone_name,
				sizeof end_zone_name
			);
			
			format:g_string("%s %s\t%s\t" #cGREEN "$%d" #cWHITE "\n", 
				g_string,
				start_zone_name,
				end_zone_name,
				GetFuberOrderFullCost(i)
			);
			
			g_dialog_select[playerid][count++] = i;
		
			if (count == MAX_ITEM_LIST)
			{
				break;
			}
		}
	}
	
	if (count == AC_DIALOG_ITEM_LIST)
	{
		strcat(g_big_string, "" #cGRAY "Вперед\t\t" #cWHITE ">>");
		g_dialog_select[playerid][count++] = ITEM_LIST_NEXT;
	}
	
	if (page > 0)
	{
		strcat(g_big_string, "\n" #cGRAY "Назад\t" #cWHITE "<<");
		g_dialog_select[playerid][count] = ITEM_LIST_BACK;
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, "Fuber Driver", 
		g_string, 
		"Далее", "Назад"
	);
}

ShowFuberTrips(playerid, const dialogid, bool: driver = false)
{	
	format:g_string("\
		SELECT *, IFNULL(UNIX_TIMESTAMP(fub_create_date), 0) AS fub_create_time \
		FROM " #__FUBER_TRIPS " \
		WHERE %s = %d \
		LIMIT 50",
		!driver ? ("fub_passenger_character_id") : ("fub_driver_character_id"),
		GetCharacterId(playerid)
	);
	
	mysql_tquery(db, g_string, "OnFuberShowTripList", "dd", playerid, dialogid);
}

function OnFuberShowTripList(playerid, const dialogid)
{	
	new server_tick = GetTickCount();
					
	if (GetPVarInt(playerid, "TimeMySQL:ShowFuberTripList") > server_tick)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
		return 1;
	}
					
	strglobalclear();

	new rows;

	cache_get_row_count(rows);

	strcat(g_big_string, #cPROJECT "Куда\t" #cPROJECT "Откуда\t" #cPROJECT "Дата\n");
	
	new id,
		create_time,
		hour,
		minute,
		day,
		month,
		year;
		
	new Float: start_x,
		Float: start_y,
		Float: end_x,
		Float: end_y;
	
	new start_zone_name		[32],
		end_zone_name		[32];
					
	for (new i; i < rows; i++)
	{
		// ID
		cache_get_value_name_int(i, "fub_id", id);
		cache_get_value_name_int(i, "fub_create_time", create_time);
		
		// Start pos
		cache_get_value_name_float(i, "fub_start_pos_x", start_x);
		cache_get_value_name_float(i, "fub_start_pos_y", start_y);
		GetZoneName(start_x, start_y, start_zone_name, sizeof start_zone_name);
		
		// End pos
		cache_get_value_name_float(i, "fub_end_pos_x", end_x);
		cache_get_value_name_float(i, "fub_end_pos_y", end_y);
		GetZoneName(end_x, end_y, end_zone_name, sizeof end_zone_name);
		
		gmtime(create_time, year, month, day, hour, minute);
		
		format:g_big_string("%s %s\t%s\t" #DATE_FORMAT "\n", 
			g_big_string,
			start_zone_name,
			end_zone_name,
			hour,
			minute,
			day,
			month,
			year
		);
		
		g_dialog_select[playerid][i] = id;
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "Выбрать", "Назад");
	SetPVarInt(playerid, "TimeMySQL:ShowFuberTripList", server_tick + 1000);
	return 1;
}

ShowFuberTripById(playerid, const dialogid, const id)
{
	format:g_string("\
		SELECT fub.*, \
			IFNULL(UNIX_TIMESTAMP(fub.fub_create_date), 0) AS fub_create_time, \
			IFNULL(c_driver.c_name, 'Неизвестно') AS fub_driver_name, \
			IFNULL(c_passenger.c_name, 'Неизвестно') AS fub_passenger_name \
		FROM " #__FUBER_TRIPS " fub \
		LEFT JOIN " #__CHARACTERS " c_driver ON c_driver.c_id = fub.fub_driver_character_id \
		LEFT JOIN " #__CHARACTERS " c_passenger ON c_passenger.c_id = fub.fub_passenger_character_id \
		WHERE fub.fub_id = %d \
		LIMIT 50",
		id
	);
	
	mysql_tquery(db, g_string, "OnFuberShowTripDataById", "dd", playerid, dialogid);
}

function OnFuberShowTripDataById(playerid, const dialogid)
{
	strglobalclear();

	new rows;

	cache_get_row_count(rows);
	
	if (rows == 0)
	{
		SendClientMessage(playerid, C_WHITE, #ERROR " Информация о данной поездке недоступна.");
		return 1;
	}
	
	new Float: start_x, 
		Float: start_y,
		Float: end_x,
		Float: end_y;
	
	new passenger_reputation,
		driver_reputation,
		driver_character_id,
		passenger_character_id,
		id,
		create_time,
		cost,
		hour,
		minute,
		day,
		month,
		year;
	
	new start_zone_name		[32],
		end_zone_name		[32];
		
	cache_get_value_name_float(0, "fub_start_pos_x", start_x);
	cache_get_value_name_float(0, "fub_start_pos_y", start_y);
	GetZoneName(start_x, start_y, start_zone_name, sizeof start_zone_name);
	
	cache_get_value_name_float(0, "fub_end_pos_x", end_x);
	cache_get_value_name_float(0, "fub_end_pos_y", end_y);
	GetZoneName(end_x, end_y, end_zone_name, sizeof end_zone_name);
	
	cache_get_value_name_int(0, "fub_id", id);
	cache_get_value_name_int(0, "fub_driver_character_id", driver_character_id);
	cache_get_value_name_int(0, "fub_passenger_character_id", passenger_character_id);
	cache_get_value_name_int(0, "fub_driver_reputation", driver_reputation);
	cache_get_value_name_int(0, "fub_passenger_reputation", passenger_reputation);
	
	SetPVarInt(playerid, "Fuber:TripId", id);
	SetPVarInt(playerid, "Fuber:TripDriverId", driver_character_id);
	SetPVarInt(playerid, "Fuber:TripPassengerId", passenger_character_id);
	SetPVarInt(playerid, "Fuber:TripDriverReputation", driver_reputation);
	SetPVarInt(playerid, "Fuber:TripPassengerReputation", passenger_reputation);
	
	cache_get_value_name_int(0, "fub_cost", cost);
	cache_get_value_name_int(0, "fub_create_time", create_time);
	
	gmtime(create_time, year, month, day, hour, minute);
	
	format:g_big_string("\
		" #DEFAULT " Информация о поездке\n\n\
		Откуда: " #cPROJECT "%s" #cWHITE "\n\
		Куда: " #cPROJECT "%s" #cWHITE "\n\
		Стоимость поездки: " #cGREEN "$%d" #cWHITE "\n\
		Дата поездки: " #DATE_FORMAT "\n\n\
		Отзыв о поездке можно оставить ниже, выбрав соответствующее действие.",
		start_zone_name,
		end_zone_name,
		cost,
		hour,
		minute,
		day,
		month,
		year
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Отзыв", "Назад");
	return 1;
}