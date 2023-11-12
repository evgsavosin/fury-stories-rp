/*!
	@brief Система банка
	@author Found (evg.savosin)
	@date 17.03.2018
*/

// Defines
#define DIALOG_BANK_PAYMENTS		" \
  Перевести клиенту банка\n \
  Оплата счетов или аренды за жилищное помещение\n \
  Оплатить мобильные услуги\n \
  Оплата счетов или аренды за помещение\n \
  Оплата задолжностей за жилищное помещение\n \
  Оплата задолжностей за помещение\
"

// Structures
enum 
{
	TYPE_BANK_STATIC,
	TYPE_BANK_ONLINE,
	TYPE_BANK_ATM
};

enum E_CASHBOX_POS
{
	Float: cp_pos_x,
	Float: cp_pos_y,
	Float: cp_pos_z
}

new const bank_cashbox_pos	[][E_CASHBOX_POS] =
{
	{-628.3091, 2711.9871, 2501.5398},
	{-628.9048, 2708.8813, 2501.5398},
	{-628.9355, 2705.5466, 2501.5398},
	{-628.3397, 2701.8801, 2501.5398}
};

enum E_ATM_POS
{
	Float: cp_pos_x,
	Float: cp_pos_y,
	Float: cp_pos_z,
	Float: cp_pos_rx,
	Float: cp_pos_ry,
	Float: cp_pos_rz
}

new const bank_atm_pos		[][E_ATM_POS] =
{
	{941.662780, -1724.774169, 13.626879, 0.000000, 0.000000, -90.000000},
	{1675.914550, -1625.993652, 13.838749, 0.000000, 0.000000, 90.000000},
	{1367.296630, -1290.116577, 13.180178, 0.000000, 0.000000, -90.000000},
	{825.984069, -1385.395019, 13.276849, 0.000000, 0.000000, 0.000000},
	{1155.026489, -1463.090209, 15.436873, 0.000000, 0.000000, -68.099906},
	{1102.171508, -1461.925292, 15.416876, 0.000000, 0.000000, -270.000000},
	{1282.945556, -1583.938720, 13.193480, 0.000000, 0.000000, -225.000000},
	{1415.354125, -1693.640747, 13.196874, 0.000000, 0.000000, 71.000061},
	{478.320922, -1761.967407, 5.156656, 0.000000, 0.000000, 0.000000},
	{2069.107910, -1782.020629, 13.138464, 0.000000, 0.000000, 117.900024},
	{1893.2079, -2015.7617, 13.2, 0.000000, 0.000000, -90.000000},
	{1754.506225, -1942.994995, 13.226815, 0.000000, 0.000000, 0.000000},
	{1805.565185, -1167.340820, 23.378129, 0.000000, 0.000000, -13.500005},
	{2334.293945, 44.796360, 26.104389, 0.000000, 0.000000, -270.000000},
	{1302.693847, 303.285217, 19.164682, 0.000000, 0.000000, 65.500000},
	{273.176696, -179.045791, 1.198124, 0.000000, 0.000000, 90.000000},
	{-2135.567626, -2431.506835, 30.218755, 0.000000, 0.000000, 142.100006},
	{1566.083740, -1898.051879, 13.200232, 0.000000, 0.000000, -180.000000}
};


Bank_OnGameModeInit()
{
	// Кассы банка
	for (new i; i < sizeof bank_cashbox_pos; i++)
	{
		CreatePickupWith3DTextLabel("" #cPROJECT "H", 
			INVALID_PARAM, 
			bank_cashbox_pos[i][cp_pos_x], 
			bank_cashbox_pos[i][cp_pos_y], 
			bank_cashbox_pos[i][cp_pos_z],
			WORLD_OTHER + 5, 
			INT_OTHER 
		);
	}
	
	// Банкоматы
	for (new i; i < sizeof bank_atm_pos; i++)
	{
		CreatePickupWith3DTextLabel("" #cPROJECT "H", 
			INVALID_PARAM, 
			bank_atm_pos[i][cp_pos_x], 
			bank_atm_pos[i][cp_pos_y], 
			bank_atm_pos[i][cp_pos_z]
		);
		
		CreateDynamicObject(19324,
			bank_atm_pos[i][cp_pos_x], 
			bank_atm_pos[i][cp_pos_y], 
			bank_atm_pos[i][cp_pos_z], 
			bank_atm_pos[i][cp_pos_rx], 
			bank_atm_pos[i][cp_pos_ry], 
			bank_atm_pos[i][cp_pos_rz], 
			-1, 
			-1, 
			-1, 
			300.00, 
			300.00
		); 
	}
}

Bank_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{
		// Cashbox
		for (new i; i < sizeof bank_cashbox_pos; i++)
		{
			if (!IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS,
			bank_cashbox_pos[i][cp_pos_x],
			bank_cashbox_pos[i][cp_pos_y],
			bank_cashbox_pos[i][cp_pos_z]))
			{
				continue;
			}
			
			SetPVarInt(playerid, "Bank:CashBoxIndex", i);
			ShowBankMenu(playerid, TYPE_BANK_STATIC);
			return 0;
		}
		
		// ATM
		for (new i; i < sizeof bank_atm_pos; i++)
		{
			if (!IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS,
			bank_atm_pos[i][cp_pos_x],
			bank_atm_pos[i][cp_pos_y],
			bank_atm_pos[i][cp_pos_z]))
			{
				continue;
			}
			
			SetPVarInt(playerid, "Bank:CashBoxIndex", i);
			ShowBankMenu(playerid, TYPE_BANK_ATM);
			return 0;
		}
	}
	
	return 1;
}

Bank_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case D_BANK :
		{
			if (!response)
			{
				if (GetPVarInt(playerid, "Bank:Type") == TYPE_BANK_ONLINE)
				{
					ShowBrowserCursor(playerid, true, false); 
				}
				
				DeletePVar(playerid, "Bank:Type");
				return 1;
			}
			
			if (listitem == 0) // Information
			{
				strglobalclear();
				
				new str_credit_card	[512],
					str_start_card	[128];
				
				if (IsCreditCardExists(playerid))
				{
					new success_date = GetCreditDateSuccess(credit_data[playerid][credit_give_time]),
						give_day,
						give_month,
						give_year,
						give_hour,
						give_minute,
						took_day,
						took_month,
						took_year,
						took_hour,
						took_minute;
					
					gmtime(credit_data[playerid][credit_give_time], give_year, give_month, give_day, give_hour, give_minute, _);
					
					if (success_date >= gettime())
					{
						gmtime(success_date, took_year, took_month, took_day, took_hour, took_minute, _);
						
						format:g_small_string("" #cPROJECT "" #DATE_FORMAT "" #cWHITE "",
							took_hour, took_minute, took_day, took_month, took_year 
						);
					}
					else
					{
						clean:<g_small_string>;
						strcat(g_small_string, "" #cRED "Неограничено" #cWHITE "");
					}
					
					format:str_credit_card("Кредитная карта [" #cPROJECT "№%i" #cWHITE "]: " #cGREEN "$%i" #cWHITE "\n\n\
						" #DEFAULT " Информация о кредите\n\n\
						Лимит средств: " #cGREEN "$%i" #cWHITE "\n\
						Дата оформления: " #cPROJECT "" #DATE_FORMAT "" #cWHITE "\n\
						Погасить до: %s\n\n",
						GetCreditCardNumber(playerid),
						GetCreditCardBalance(playerid),
						credit_data[playerid][credit_limit],
						give_hour, give_minute, give_day, give_month, give_year,
						g_small_string
					);
				}
				
				if (IsCharacterCardStartExists(playerid))
				{
					format:str_start_card("Дебетовая карта " #cPROJECT "«Start»" #cWHITE ": " #cGREEN "%d" #cWHITE,
						GetCharacterCardStart(playerid)
					);
				}
				
				format:g_big_string("\
					" #DEFAULT " Информация\n\n\
					Кредитная история: " #cGRAY "%s" #cWHITE "\n\ 
					Дебетовая карта [" #cPROJECT "№%i" #cWHITE "]: " #cGREEN "$%i" #cWHITE "\n\
					Банковский счет: " #cGREEN "$%i" #cWHITE "\n\
					%s%s%s", 
					credit_level_info[character_data[playerid][c_credit_level]][cl_reputation_text],
					GetCharacterCardNumber(playerid),
					GetCharacterCardBalance(playerid),
					GetCharacterBank(playerid),
					str_credit_card,
					isnull(str_credit_card) ? ("") : ("\n"),
					str_start_card
				);
				
				ShowPlayerDialog(playerid, D_BANK + 1, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Закрыть", "");
			}
			else if (listitem == 1) // Operations
			{	
				ShowBankOperations(playerid);
			}
			else if (listitem == 2) // Payments
			{
				ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
					DIALOG_BANK_PAYMENTS,
					"Далее", "Назад"
				);
			}
			else if (listitem == 3) // Credit
			{
				ShowPlayerDialog(playerid, D_BANK + 9, DIALOG_STYLE_MSGBOX, " ",
					DIALOG_CREDIT_INFO,
					"Далее", "Назад"
				);
			}
			else if (listitem == 4)
			{
				if (IsCreditCardExists(playerid)
				&& IsCreditCardUse(playerid))
				{
					ShowBankMenu(playerid, GetPVarInt(playerid, "Bank:Type"));
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " Нельзя расторгнуть активный кредитный договор.");
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_BANK + 17, DIALOG_STYLE_MSGBOX, " ",
					DIALOG_CREDIT_DISSOLVE,
					"Да", "Нет"
				);
			}
		}
		
		case D_BANK + 1:
		{
			ShowBankMenu(playerid, GetPVarInt(playerid, "Bank:Type"));
		}
		
		case D_BANK + 2:
		{
			if (!response)
			{
				ShowBankMenu(playerid, GetPVarInt(playerid, "Bank:Type"));
				return 1;
			}
			
			new type = GetPVarInt(playerid, "Bank:Type");

			if (type == TYPE_BANK_ONLINE)
			{
				if (listitem == 2)
				{
					if (IsCreditCardExists(playerid))
					{
						ShowRepayPlayerCredit(playerid);
					}
					else 
					{
						ShowRepayPlayerStartCard(playerid);
					}
					
					return 1;
				}
				else if (listitem == 3)
				{
					ShowRepayPlayerStartCard(playerid);
					return 1;
				}
			}

			if (type == TYPE_BANK_STATIC)
			{
				if (listitem == 5)
				{
					if (IsCreditCardExists(playerid))
					{
						ShowRepayPlayerCredit(playerid);
					}
					else 
					{
						ShowRepayPlayerStartCard(playerid);
					}
					
					return 1;
				}
				else if (listitem == 6)
				{
					ShowRepayPlayerStartCard(playerid);
					return 1;
				}
			}

			if (type == TYPE_BANK_ATM)
			{
				if (listitem == 4)
				{
					if (IsCreditCardExists(playerid))
					{
						ShowRepayPlayerCredit(playerid);
					}
					else 
					{
						ShowRepayPlayerStartCard(playerid);
					}
					
					return 1;
				}
				else if (listitem == 5)
				{
					ShowRepayPlayerStartCard(playerid);
					return 1;
				}
			}
			
			SetPVarInt(playerid, "Bank:OperationListItem", listitem);
			ShowBankOperationInput(playerid);
		}
		
		case D_BANK + 3:
		{
			if (!response)
			{
				DeletePVar(playerid, "Bank:OperationListItem");
				ShowBankOperations(playerid);
				return 1;
			}
			
			listitem = GetPVarInt(playerid, "Bank:OperationListItem");
			
			new value = strval(inputtext),
				type = GetPVarInt(playerid, "Bank:Type"),
				bool: is_error = false;
			
			if (value == 0 || !CheckInputSumm(value))
			{
				is_error = true;
			}
			
			if (type == TYPE_BANK_ONLINE)
			{	
				if (listitem == 0)
				{
					if (is_error || !CheckCardSummForPay(playerid, value))
					{
						ShowBankOperationInput(playerid, true);
						return 1;
					}
					
					GiveDebitCardMoney(playerid, -value);
					GivePlayerBank(playerid, value);
					
					pformat:("" #SUCCESS " Вы успешно перевели средства с карты " #cPROJECT "(№%i)" #cWHITE " на счет в размере " #cGREEN "$%i" #cWHITE ".",
						GetCharacterCardNumber(playerid),
						value
					);
				}
				else 
				{
					if (is_error || !CheckBankSummForPay(playerid, value))
					{
						ShowBankOperationInput(playerid, true);
						return 1;
					}
					
					GiveDebitCardMoney(playerid, value);
					GivePlayerBank(playerid, -value);
					
					pformat:("" #SUCCESS " Вы успешно перевели средства со счёта на карту " #cPROJECT "(№%i)" #cWHITE " в размере " #cGREEN "$%i" #cWHITE ".",
						GetCharacterCardNumber(playerid),
						value
					);
				}
				
				psend:(playerid, C_WHITE);
			}
			else if (type == TYPE_BANK_STATIC)
			{	
				if (listitem == 0)
				{
					if (is_error || !CheckSummForPay(playerid, value))
					{
						ShowBankOperationInput(playerid, true);
						return 1;
					}
					
					GivePlayerCash(playerid, -value);
					GivePlayerBank(playerid, value);
					
					pformat:("" #SUCCESS " Вы успешно внесли наличные на счет в размере " #cGREEN "$%i" #cWHITE ".",
						value
					);
				}
				else if (listitem == 1)
				{
					if (is_error || !CheckBankSummForPay(playerid, value))
					{
						ShowBankOperationInput(playerid, true);
						return 1;
					}
					
					GivePlayerCash(playerid, value);
					GivePlayerBank(playerid, -value);
					
					pformat:("" #SUCCESS " Вы успешно сняли деньги со счета в размере " #cGREEN "$%i" #cWHITE ".",
						value
					);
				}
				else if (listitem == 2)
				{
					if (is_error || !CheckCardSummForPay(playerid, value))
					{
						ShowBankOperationInput(playerid, true);
						return 1;
					}
					
					GiveDebitCardMoney(playerid, -value);
					GivePlayerBank(playerid, value);
					
					pformat:("" #SUCCESS " Вы успешно перевели средства с карты " #cPROJECT "(№%i)" #cWHITE " на счет в размере " #cGREEN "$%i" #cWHITE ".",
						GetCharacterCardNumber(playerid),
						value
					);
				}
				else if (listitem == 3)
				{
					if (is_error || !CheckBankSummForPay(playerid, value))
					{
						ShowBankOperationInput(playerid, true);
						return 1;
					}
					
					GiveDebitCardMoney(playerid, value);
					GivePlayerBank(playerid, -value);
					
					pformat:("" #SUCCESS " Вы успешно перевели средства со счёта на карту " #cPROJECT "(№%i)" #cWHITE " в размере " #cGREEN "$%i" #cWHITE ".",
						GetCharacterCardNumber(playerid),
						value
					);
				}
				else if (listitem == 4)
				{
					if (is_error || !CheckCardSummForPay(playerid, value))
					{
						ShowBankOperationInput(playerid, true);
						return 1;
					}
					
					GivePlayerCash(playerid, value);
					GiveDebitCardMoney(playerid, -value);
					
					pformat:("" #SUCCESS " Вы успешно сняли деньги с карты " #cPROJECT "(№%i)" #cWHITE " в размере " #cGREEN "$%i" #cWHITE ".",
						GetCharacterCardNumber(playerid),
						value
					);
				}
				
				psend:(playerid, C_WHITE);
				
				ApplyAnimationEx(playerid, "PED", "ATM", 4.1, 0, 1, 1, 0, 0, 1);
			}
			else if (type == TYPE_BANK_ATM)
			{
				if (listitem == 0)
				{
					if (is_error || !CheckCardSummForPay(playerid, value))
					{
						ShowBankOperationInput(playerid, true);
						return 1;
					}
					
					GiveDebitCardMoney(playerid, -value);
					GivePlayerBank(playerid, value);
					
					pformat:("" #SUCCESS " Вы успешно перевели средства с карты " #cPROJECT "(№%i)" #cWHITE " на счет в размере " #cGREEN "$%i" #cWHITE ".",
						GetCharacterCardNumber(playerid),
						value
					);
				}
				else if (listitem == 1)
				{
					if (is_error || !CheckBankSummForPay(playerid, value))
					{
						ShowBankOperationInput(playerid, true);
						return 1;
					}
					
					GiveDebitCardMoney(playerid, value);
					GivePlayerBank(playerid, -value);
					
					pformat:("" #SUCCESS " Вы успешно перевели средства со счёта на карту " #cPROJECT "(№%i)" #cWHITE " в размере " #cGREEN "$%i" #cWHITE ".",
						GetCharacterCardNumber(playerid),
						value
					);
				}
				else if (listitem == 2)
				{
					if (is_error || !CheckSummForPay(playerid, value))
					{
						ShowBankOperationInput(playerid, true);
						return 1;
					}
					
					GivePlayerCash(playerid, -value);
					GiveDebitCardMoney(playerid, value);
					
					pformat:("" #SUCCESS " Вы успешно внесли наличные на карту " #cPROJECT "(№%i)" #cWHITE " в размере " #cGREEN "$%i" #cWHITE ".",
						GetCharacterCardNumber(playerid),
						value
					);
				}
				else if (listitem == 3)
				{
					if (is_error || !CheckCardSummForPay(playerid, value))
					{
						ShowBankOperationInput(playerid, true);
						return 1;
					}
					
					GivePlayerCash(playerid, value);
					GiveDebitCardMoney(playerid, -value);
					
					pformat:("" #SUCCESS " Вы успешно сняли деньги с карты " #cPROJECT "(№%i)" #cWHITE " в размере " #cGREEN "$%i" #cWHITE ".",
						GetCharacterCardNumber(playerid),
						value
					);
				}
				
				psend:(playerid, C_WHITE);
				
				ApplyAnimationEx(playerid, "PED", "ATM", 4.1, 0, 1, 1, 0, 0, 1);
			}
			
			ShowBankOperations(playerid);
		}

		case D_BANK + 4:
		{
			if (!response)
			{
				ShowBankMenu(playerid, GetPVarInt(playerid, "Bank:Type"));
				return 1;
			}
			
			switch(listitem)
			{
				case 0 : // Перевод
				{
					ShowPlayerDialog(playerid, D_BANK + 5, DIALOG_STYLE_INPUT, " ",
						"" #DEFAULT " Перевести клиенту банка\n\n\
						Введите номер карты, на которую Вы хотите перечислить средства:\n\n\
						" #cGRAY "Номер карты должен быть в формате: XXXXXXXX.",
						"Далее", "Назад"
					);
				}
				
				case 1 : // Оплата аренды дома
				{
					if (!ShowHouseList(playerid, D_BANK + 7, _, "Назад", 1))
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_HOUSE);
						ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
						  DIALOG_BANK_PAYMENTS,
						  "Далее", "Назад"
						);
						
						return 1;
					}
				}
				
				case 2 : // Оплатить счета за мобильные услуги
				{
					if (!ShowPhoneList(playerid, D_BANK + 8, _, "Назад"))
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_PHONE);
						ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
						  DIALOG_BANK_PAYMENTS,
						  "Далее", "Назад"
						);
						
						return 1;
					}
				}
				
				case 3 : // Оплатить счета за аренду помещений и электроэнергию
				{
					if (!ShowPremiseList(playerid, D_BANK + 14, _, "Назад", 1))
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_PREMISE);
						ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
						  DIALOG_BANK_PAYMENTS,
						  "Далее", "Назад"
						);
						
						return 1;
					}
				}
				
				case 4 : // Задолжность за дом 
				{
					if (!ShowHouseList(playerid, D_BANK + 12, _, "Назад", 2))
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_HOUSE);
						ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
						  DIALOG_BANK_PAYMENTS,
						  "Далее", "Назад"
						);
						
						return 1;
					}
				}
				
				case 5 : // Задолжность за помещение
				{
					if (!ShowPremiseList(playerid, D_BANK + 15, _, "Назад", 2))
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_PREMISE);
						ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
						  DIALOG_BANK_PAYMENTS,
						  "Далее", "Назад"
						);
						
						return 1;
					}
				}
			}
		}
		
		case D_BANK + 5:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
				  DIALOG_BANK_PAYMENTS,
				  "Далее", "Назад"
				);
				
				return 1;
			}
			
			new number = strval(inputtext);
			
			if (isnull(inputtext) || !IsInt(inputtext) 
			|| !(10000000 <= number <= 99999999)
			|| !(IsValidPlayerDebitCard(number)))
			{
				ShowPlayerDialog(playerid, D_BANK + 5, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Перевести клиенту банка\n\n\
					Введите номер карты, на которую Вы хотите перечислить средства:\n\n\
					" #cRED "Номер карты должен быть в формате: XXXXXXXX.\n\
					Вы ввели неверный номер карты либо игрок с данной картой находится не в сети.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			SetPVarInt(playerid, "Bank:CardNumber", number);
			
			ShowPlayerDialog(playerid, D_BANK + 6, DIALOG_STYLE_INPUT, " ",
				"" #DEFAULT " Перевести клиенту банка\n\n\
				Введите сумму, которую Вы желаете перевести:\n\n\
				" #cGRAY "Минимальная сумма $1, максимальная $100.000.",
				"Далее", "Назад"
			);
		}
		
		case D_BANK + 6:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BANK + 5, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Перевести клиенту банка\n\n\
					Введите номер карты, на которую Вы хотите перечислить средства:\n\n\
					" #cGRAY "Номер карты должен быть в формате: XXXXXXXX.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			new number = GetPVarInt(playerid, "Bank:CardNumber"),
				value = strval(inputtext);
			
			if (value == 0 || !CheckInputSumm(value))
			{
				ShowPlayerDialog(playerid, D_BANK + 6, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Перевести клиенту банка\n\n\
					Введите сумму, которую Вы желаете перевести:\n\n\
					" #cRED "Минимальная сумма $1, максимальная $100.000.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			new targetid = GetPlayerIdByDebitCard(number);
			if (targetid == INVALID_PLAYER_ID)
			{
				ShowPlayerDialog(playerid, D_BANK + 5, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Перевести клиенту банка\n\n\
					Введите номер карты, на которую Вы хотите перечислить средства:\n\n\
					" #cRED "Игрок с данной картой находится не в сети.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			if (!GiveDebitCardMoney(playerid, -value))
			{
				ShowPlayerDialog(playerid, D_BANK + 6, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Перевести клиенту банка\n\n\
					Введите сумму, которую Вы желаете перевести:\n\
					" #cRED "Минимальная сумма $1, максимальная $100.000.\n\n\
					У Вас недостаточно средств на карте.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			GiveDebitCardMoney(targetid, value);
			ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
			  DIALOG_BANK_PAYMENTS,
			  "Далее", "Назад"
			);
			
			format:g_small_string("" #SMS_MESSAGE " От Los Santos Bank: Зачисление средств на карту (%i) от (%i) - %s в размере $%i.", 
				GetCharacterCardNumber(targetid),
				GetCharacterCardNumber(playerid),
				GetPlayerCurrentName(playerid),
				value
			);
			
			SendSplitMessage(targetid, C_DARKYELLOW, g_small_string);
			
			SendRPMessage(ACTION_AME, targetid, "Вибрирует телефон");
			
			format:g_small_string("" #SMS_MESSAGE " От Los Santos Bank: Перевод средств с карты (%i) на (%i) - %s в размере $%i.", 
				GetCharacterCardNumber(playerid),
				GetCharacterCardNumber(targetid),
				GetPlayerCurrentName(targetid),
				value
			);
			
			SendSplitMessage(playerid, C_DARKYELLOW, g_small_string);
		}
		
		case D_BANK + 7:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
				  DIALOG_BANK_PAYMENTS,
				  "Далее", "Назад"
				);
				
				return 1;
			}
			
			new index = g_dialog_select[playerid][listitem],
				day,
				month,
				year,
				hour,
				minute,
				type_buy = house_data[index][h_buy_type];
			
			gmtime(house_data[index][h_time], year, month, day, hour, minute);
			
			if (house_data[index][h_time] >= GetMaxTimeForProperty())
			{
				pformat:("" #ERROR " Вы не можете совершить оплату, у Вас уже %s " #cPROJECT "" #DATE_FORMAT "" #cWHITE ".", 
					type_buy == TYPE_BUY_FULLY ? ("коммунальные услуги оплачены до:") : ("аренда оплачена до:"),
					hour,
					minute,
					day,
					month,
					year
				);
				
				psend:(playerid, C_WHITE);
			}
			else 
			{
				if (!GiveDebitCardMoney(playerid, type_buy == TYPE_BUY_FULLY ? -GetHouseCommunal(index) : -GetHouseRent(index)))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
				}
				else 
				{
					house_data[index][h_time] += (60 * 60 * 24 * 7);
					
					gmtime(house_data[index][h_time], _, month, day, hour, minute);
					
					pformat:("" #SUCCESS " %s" #cPROJECT " " #DATE_FORMAT "" #cWHITE ".", 
						type_buy == TYPE_BUY_FULLY ? ("Коммунальные услуги были успешно оплачены до:") : ("Аренда была успешно оплачена до:"),
						hour,
						minute,
						day,
						month,
						year
					);
					
					psend:(playerid, C_WHITE);
					
					Update:house_int(index, "h_time", house_data[index][h_time]);
				}
			}
			
			ShowHouseList(playerid, D_BANK + 7, _, "Назад", 1);
		}
		
		case D_BANK + 8:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
				  DIALOG_BANK_PAYMENTS,
				  "Далее", "Назад"
				);
				
				return 1;
			}
			
			new index = g_dialog_select[playerid][listitem],
				day,
				month,
				year,
				hour,
				minute;
		
			gmtime(phone_data[index][ph_paid_time], year, month, day, hour, minute);
			
			if (phone_data[index][ph_paid_time] >= gettime() + (60 * 60 * 24 * 7 * 2))
			{
				pformat:("" #ERROR " Вы не можете совершить оплату, у Вас уже оплачено до: " #cPROJECT "" #DATE_FORMAT "" #cWHITE ".", 
					hour,
					minute,
					day,
					month,
					year
				);
				
				psend:(playerid, C_WHITE);
			}
			else 
			{
				if (!GiveDebitCardMoney(playerid, -60))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
				}
				else
				{
					if (phone_data[index][ph_paid_time] == 0)
					{
						phone_data[index][ph_paid_time] = gettime();
					}
					
					phone_data[index][ph_paid_time] += (60 * 60 * 24 * 7);
					
					gmtime(phone_data[index][ph_paid_time], year, month, day, hour, minute);
					
					pformat:("" #SUCCESS " Вы успешно продлили мобильный тариф до: " #cPROJECT "" #DATE_FORMAT "" #cWHITE ".", 
						hour,
						minute,
						day,
						month,
						year
					);
					
					psend:(playerid, C_WHITE);
					
					Update:phone_data(playerid, index);
				}
			}
			
			ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
			  DIALOG_BANK_PAYMENTS,
			  "Далее", "Назад"
			);	
		}
		
		case D_BANK + 9:
		{
			if (IsCreditCardExists(playerid))
			{
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " У Вас уже оформлен кредит.");
			}
			else
			{
				if (response)
				{
					ShowBankCredit(playerid);
					return 1;
				}
			}
			
			ShowBankMenu(playerid, GetPVarInt(playerid, "Bank:Type"));
		}
		
		case D_BANK + 10:
		{
			if (!response)
			{	
				ShowPlayerDialog(playerid, D_BANK + 9, DIALOG_STYLE_MSGBOX, " ",
				 DIALOG_CREDIT_INFO,
				  "Далее", "Назад"
				);
				
				return 1;
			}
						
			if (!IsAvaibleCreditLimit(playerid, listitem))
			{
				ShowBankCredit(playerid);
				return 1;
			}
			
			new value = credit_level_info[listitem][cl_limit_sum];
			if (!GivePlayerCash(playerid, -GetCreditPledge(value)))
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
				ShowBankCredit(playerid);
				return 1;
			}
			
			format:g_string("\
				" #DEFAULT " Оформить кредитную карту\n\n\
				Вы успешно оформили кредит на сумму " #cGREEN "$%i" #cWHITE ".\n\n\
				Оплата кредита происходит в банке в меню " #cGRAY "Операции" #cWHITE ".",
				value
			);
			
			ShowPlayerDialog(playerid, D_BANK + 11, DIALOG_STYLE_MSGBOX, " ", g_string, "Назад", "");
			
			credit_data[playerid][credit_card] = value;
			credit_data[playerid][credit_limit] = value;
			credit_data[playerid][credit_give_time] = gettime();
			
			Update:credit_data(playerid);
		}
		
		case D_BANK + 11:
		{
			ShowBankMenu(playerid, GetPVarInt(playerid, "Bank:Type"));
		}
		
		case D_BANK + 12:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
				  DIALOG_BANK_PAYMENTS,
				  "Далее", "Назад"
				);
				
				return 1;
			}
			
			new index = g_dialog_select[playerid][listitem];
			
			SetPVarInt(playerid, "Bank:SelectDebtHouse", index);
			
			if (house_data[index][h_debt] == 0)
			{
				if (!ShowHouseList(playerid, D_BANK + 12, _, "Назад", 2))
				{
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " Задолжность у данного жилищного помещения отсутствует.");
					ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
					  DIALOG_BANK_PAYMENTS,
					  "Далее", "Назад"
					);
					
					return 1;
				}
			}
			
			format:g_string("" #DEFAULT " Оплата задолжности за жилищное помещение\n\n\
				Задолжность за %s #%i составляет " #cGREEN "$%i" #cWHITE " (" #cPROJECT "%0.2f%%" #cWHITE " от полной стоимости).\n\
				Помните, что своевременная оплата позволяет сохранить Ваши средства и Ваше имущество.\n\
				Вы желаете погасить данную сумму?", 
				(IsHouseType(index) == TYPE_HOUSE) ? ("дом") : ("квартиру"),
				GetHouseId(index),
				GetHouseDebt(index),
				CallLocalFunction("GetHouseDebtInPercent", "d", index)
			);
			
			ShowPlayerDialog(playerid, D_BANK + 13, DIALOG_STYLE_MSGBOX, " ", g_string, "Далее", "Отмена");
		}
		
		case D_BANK + 13:
		{
			if (!response)
			{
				DeletePVar(playerid, "Bank:SelectDebtHouse");
				
				if (!ShowHouseList(playerid, D_BANK + 12, _, "Назад", 2))
				{
					ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
					  DIALOG_BANK_PAYMENTS,
					  "Далее", "Назад"
					);
					
					return 1;
				}
				
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Bank:SelectDebtHouse");
			
			if (!GiveDebitCardMoney(playerid, -GetHouseDebt(index)))
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
				if (!ShowHouseList(playerid, D_BANK + 12, _, "Назад", 2))
				{
					ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
					  DIALOG_BANK_PAYMENTS,
					  "Далее", "Назад"
					);
					
					return 1;
				}
				
				return 1;
			}
			
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы успешно оплатили задолжность.");
			house_data[index][h_debt] = 0;
			Update:house_int(index, "h_debt", 0);
			
			if (!ShowHouseList(playerid, D_BANK + 12, _, "Назад", 2))
			{
				ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
				  DIALOG_BANK_PAYMENTS,
				  "Далее", "Назад"
				);
				
				return 1;
			}
		}
		
		case D_BANK + 14:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
				  DIALOG_BANK_PAYMENTS,
				  "Далее", "Назад"
				);
				
				return 1;
			}
			
			new index = g_dialog_select[playerid][listitem],
				day,
				month,
				year,
				hour,
				minute,
				type_buy = premise_data[index][pr_buy_type];
			
			gmtime(premise_data[index][pr_time], year, month, day, hour, minute);
			
			if (premise_data[index][pr_time] >= GetMaxTimeForProperty())
			{
				pformat:("" #ERROR " Вы не можете совершить оплату, у Вас уже %s" #cPROJECT "" #DATE_FORMAT "" #cWHITE ".", 
					type_buy == TYPE_BUY_FULLY ? ("счета за электроэнергию оплачены до:") : ("аренда оплачена до:"),
					hour,
					minute,
					day,
					month,
					year
				);
				
				psend:(playerid, C_WHITE);
			}
			else 
			{
				if (!GiveDebitCardMoney(playerid, type_buy == TYPE_BUY_FULLY ? -GetPremiseCommunal(index) : -GetPremiseRent(index)))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
				}
				else 
				{
					premise_data[index][pr_time] += (60 * 60 * 24 * 7);
					
					gmtime(premise_data[index][pr_time], year, month, day, hour, minute);
					
					pformat:("" #SUCCESS " %s" #cPROJECT "" #DATE_FORMAT "" #cWHITE ".", 
						type_buy == TYPE_BUY_FULLY ? ("Счета за электроэнергию были успешно оплачены до:") : ("Аренда была успешно оплачена до:"),
						hour,
						minute,
						day,
						month,
						year
					);
					
					psend:(playerid, C_WHITE);
					
					Update:premise_int(index, "pr_time", premise_data[index][pr_time]);
				}
			}
			
			ShowPremiseList(playerid, D_BANK + 14, _, "Назад", 1);
		}
		
		case D_BANK + 15:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
				  DIALOG_BANK_PAYMENTS,
				  "Далее", "Назад"
				);
				
				return 1;
			}
			
			new index = g_dialog_select[playerid][listitem];
			
			SetPVarInt(playerid, "Bank:SelectDebtPremise", index);
			
			if (premise_data[index][pr_debt] == 0)
			{
				if (!ShowPremiseList(playerid, D_BANK + 15, _, "Назад", 2))
				{
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " Задолжность у данного помещения отсутствует.");
					ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
					  DIALOG_BANK_PAYMENTS,
					  "Далее", "Назад"
					);
					
					return 1;
				}
			}
			
			format:g_string("" #DEFAULT " Оплата задолжности за помещение\n\n\
				Задолжность за помещение #%i составляет " #cGREEN "$%i" #cWHITE " (" #cPROJECT "%0.2f%%" #cWHITE " от полной стоимости).\n\
				Помните, что своевременная оплата позволяет сохранить Ваши средства и Ваше имущество.\n\
				Вы желаете погасить данную сумму?", 
				GetPremiseId(index),
				GetPremiseDebt(index),
				CallLocalFunction("GetPremiseDebtInPercent", "d", index)
			);
			
			ShowPlayerDialog(playerid, D_BANK + 16, DIALOG_STYLE_MSGBOX, " ", g_string, "Далее", "Отмена");
		}
		
		case D_BANK + 16:
		{
			if (!response)
			{
				DeletePVar(playerid, "Bank:SelectDebtPremise");
				
				if (!ShowPremiseList(playerid, D_BANK + 15, _, "Назад", 2))
				{
					ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
					  DIALOG_BANK_PAYMENTS,
					  "Далее", "Назад"
					);
					
					return 1;
				}
				
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Bank:SelectDebtPremise");
			
			if (!GiveDebitCardMoney(playerid, -GetPremiseDebt(index)))
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
				if (!ShowHouseList(playerid, D_BANK + 15, _, "Назад", 2))
				{
					ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
					  DIALOG_BANK_PAYMENTS,
					  "Далее", "Назад"
					);
					
					return 1;
				}
				
				return 1;
			}
			
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы успешно оплатили задолжность.");
			premise_data[index][pr_debt] = 0;
			Update:premise_int(index, "pr_debt", 0);
			
			if (!ShowPremiseList(playerid, D_BANK + 15, _, "Назад", 2))
			{
				ShowPlayerDialog(playerid, D_BANK + 4, DIALOG_STYLE_LIST, " ", 
				  DIALOG_BANK_PAYMENTS,
				  "Далее", "Назад"
				);
				
				return 1;
			}
		}
		
		case D_BANK + 17:
		{
			if (response)
			{
				ResetPlayerCredit(playerid, true);
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно расторгнули кредитный договор.");
			}
			
			ShowBankMenu(playerid, GetPVarInt(playerid, "Bank:Type"));
		}
		
		case D_BANK + 18:
		{
			if (!response)
			{
				ShowBankOperations(playerid);
				return 1;
			}
			
			new value = strval(inputtext);
			
			if (isnull(inputtext) || !CheckInputSumm(value))
			{
				ShowRepayPlayerCredit(playerid, "Вы ввели неверную сумму.");
				return 1;
			}
			
			if ((value + credit_data[playerid][credit_card]) > credit_data[playerid][credit_limit])
			{
				ShowRepayPlayerCredit(playerid, "Введенная сумма должна быть равна сумме, которую необходимо погасить.");
				return 1;
			}
			
			if (!GiveDebitCardMoney(playerid, -value))
			{
				ShowRepayPlayerCredit(playerid, "Недостаточно средств на дебетовой карте.");
				return 1;
			}
			
			GiveCreditCardMoney(playerid, value);
			
			new credit_diff = credit_data[playerid][credit_limit] - GetCreditCardBalance(playerid);
			
			if (credit_diff != 0)
			{
				pformat:("" #SUCCESS " Вы успешно погасили часть средств " #cGREEN "$%i" #cWHITE ". Осталось: " #cGREEN "$%i" #cWHITE ".",
					value,
					GetCreditCardBalance(playerid)
				);
				
				psend:(playerid, C_WHITE);
			}
			else 
			{
				pformat:("" #SUCCESS " Вы успешно погасили кредит " #cGREEN "$%i" #cWHITE ". Списание средств произойдет через 3 недели, после начала использования.",
					value
				);
				
				psend:(playerid, C_WHITE);
			}
			
			ShowBankOperations(playerid);
		}
		
		case D_BANK + 19:
		{
			if (!response)
			{
				ShowBankOperations(playerid);
				return 1;
			}
			
			new value = strval(inputtext);
			
			if (isnull(inputtext) || !CheckInputSumm(value))
			{
				ShowRepayPlayerStartCard(playerid, "Вы ввели неверную сумму.");
				return 1;
			}
			
			if (!GiveDebitCardMoney(playerid, -value))
			{
				ShowRepayPlayerStartCard(playerid, "Недостаточно средств на дебетовой карте.");
				return 1;
			}
			
			character_data[playerid][c_start_capital] += value;
			Update:character_int(playerid, "c_start_capital", character_data[playerid][c_start_capital]);
			
			pformat:(#SUCCESS " Вы успешно пополнили карту «Start» на сумму " #cGREEN "$%d" #cWHITE ".", value);
			psend:(playerid, C_WHITE);
			
			ShowBankOperations(playerid);
		}
	}
	
	return 1;
}

ShowBankCredit(playerid)
{
	clean:<g_string>;
	strcat(g_string, #cPROJECT "Сумма\t" #cPROJECT "#\n");
	
	for (new i; i < sizeof credit_level_info; i++)
	{
		format:g_string("%s" #cGREEN "$%i\t[%s" #cWHITE "]\n",
			g_string,
			credit_level_info[i][cl_limit_sum],
			IsAvaibleCreditLimit(playerid, i) ? ("" #cPROJECT "доступно") : ("" #cGRAY "недоступно")
		);
	}
	
	ShowPlayerDialog(playerid, D_BANK + 10, DIALOG_STYLE_TABLIST_HEADERS, " ", g_string, "Выбрать", "Назад");
}

ShowBankMenu(playerid, type)
{	
	clean:<g_string>;
	
	SetPVarInt(playerid, "Bank:Type", type);
	
	if (type == TYPE_BANK_ONLINE)
	{
		ShowBrowserCursor(playerid, false, true); 
	}
	
	strcat(g_string, " Информация о счетах\n \
		Операции\n \
		Платежи и переводы" 
	);
	
	if (type == TYPE_BANK_STATIC)
	{
		strcat(g_string, "\n Оформить кредитную карту");
		
		if (IsCreditCardExists(playerid)
		&& !IsCreditCardUse(playerid))
		{
			strcat(g_string, "\n Расторгнуть кредитный договор");
		}
	}
	
	ShowPlayerDialog(playerid, D_BANK, DIALOG_STYLE_LIST, 
		type == TYPE_BANK_ONLINE ? ("www.lsbank.com") : (" "), 
		g_string, 
		"Выбрать", "Закрыть" 
	);
}

ShowBankOperations(playerid)
{
	clean:<g_string>;
	
	new type = GetPVarInt(playerid, "Bank:Type"),
		str_credit_card			[64],
		str_start_card			[64];
	
	if (IsCreditCardExists(playerid))
	{
		strcat(str_credit_card, " Пополнить кредитную карту");
	}
	
	if (IsCharacterCardStartExists(playerid))
	{
		strcat(str_start_card, " Пополнить дебетовую карту «Start»");
	}
	
	if (type == TYPE_BANK_ONLINE)
	{
		format:g_string(" \
			Перевести с карты на счёт\n \
			Перевести со счёта на карту\n%s%s%s",
			str_credit_card,
			isnull(str_credit_card) ? ("") : ("\n"),
			str_start_card
		);
	}
	else if (type == TYPE_BANK_ATM)
	{
		format:g_string(" \
			Перевести с карты на счёт\n \
			Перевести со счёта на карту\n \
			Внести наличные на карту\n \
			Снять деньги с карты\n%s%s%s",
			str_credit_card,
			isnull(str_credit_card) ? ("") : ("\n"),
			str_start_card
		);
	}
	else if (type == TYPE_BANK_STATIC)
	{
		format:g_string(" \
			Внести наличные на счёт\n \
			Снять деньги со счета\n \
			Перевести с карты на счёт\n \
			Перевести со счёта на карту\n \
			Снять деньги с карты\n%s%s%s",
			str_credit_card,
			isnull(str_credit_card) ? ("") : ("\n"),
			str_start_card 
		);
	}
	
	ShowPlayerDialog(playerid, D_BANK + 2, DIALOG_STYLE_LIST, 
		type == TYPE_BANK_ONLINE ? ("www.lsbank.com") : (" "), 
		g_string, 
		"Выбрать", "Назад" 
	);
}

ShowBankOperationInput(playerid, bool: error = false)
{
	clean:<g_string>;
	new type = GetPVarInt(playerid, "Bank:Type"),
		listitem = GetPVarInt(playerid, "Bank:OperationListItem");
	
	if (type == TYPE_BANK_ONLINE)
	{
		if (listitem == 0)
		{
			format:g_string("" #DEFAULT " Операции\n\n\
				Перевод с дебетовой карты на банковский счёт.\n\
				Дебетовая карта [" #cPROJECT "№%i" #cWHITE "]: " #cGREEN "$%i" #cWHITE "\n\
				Банковский счет: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму:\n\n\
				" #cGRAY "Минимальная сумма $1, максимальная $100.000.%s",
				GetCharacterCardNumber(playerid),
				GetCharacterCardBalance(playerid),
				GetCharacterBank(playerid),
				error ? ("\n" #cRED "Недостаточно средств.") : ("")
			);
		}
		else
		{
			format:g_string("" #DEFAULT " Операции\n\n\
				Перевод с банковского счета на дебетовую карту.\n\
				Дебетовая карта [" #cPROJECT "№%i" #cWHITE "]: " #cGREEN "$%i" #cWHITE "\n\
				Банковский счет: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму:\n\n\
				" #cGRAY "Минимальная сумма $1, максимальная $100.000.%s",
				GetCharacterCardNumber(playerid),
				GetCharacterCardBalance(playerid),
				GetCharacterBank(playerid),
				error ? ("\n" #cRED "Недостаточно средств.") : ("")
			);
		}
	}
	else if (type == TYPE_BANK_ATM)
	{
		if (listitem == 0)
		{
			format:g_string("" #DEFAULT " Операции\n\n\
				Перевод с дебетовой карты на банковский счёт.\n\
				Дебетовая карта [" #cPROJECT "№%i" #cWHITE "]: " #cGREEN "$%i" #cWHITE "\n\
				Банковский счет: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму:\n\n\
				" #cGRAY "Минимальная сумма $1, максимальная $100.000.%s",
				GetCharacterCardNumber(playerid),
				GetCharacterCardBalance(playerid),
				GetCharacterBank(playerid),
				error ? ("\n" #cRED "Недостаточно средств.") : ("")
			);
		}
		else if (listitem == 1)
		{
			format:g_string("" #DEFAULT " Операции\n\n\
				Перевод с банковского счета на дебетовую карту.\n\
				Дебетовая карта [" #cPROJECT "№%i" #cWHITE "]: " #cGREEN "$%i" #cWHITE "\n\
				Банковский счет: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму:\n\n\
				" #cGRAY "Минимальная сумма $1, максимальная $100.000.%s",
				GetCharacterCardNumber(playerid),
				GetCharacterCardBalance(playerid),
				GetCharacterBank(playerid),
				error ? ("\n" #cRED "Недостаточно средств.") : ("")
			);
		}
		else if (listitem == 2)
		{
			format:g_string("" #DEFAULT " Операции\n\n\
				Внести наличные на карту.\n\
				Наличные: " #cGREEN "$%i" #cWHITE "\n\
				Дебетовая карта [" #cPROJECT "№%i" #cWHITE "]: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму:\n\n\
				" #cGRAY "Минимальная сумма $1, максимальная $100.000.%s",
				GetCharacterMoney(playerid),
				GetCharacterCardNumber(playerid),
				GetCharacterCardBalance(playerid),
				error ? ("\n" #cRED "Недостаточно средств.") : ("")
			);
		}
		else if (listitem == 3)
		{
			format:g_string("" #DEFAULT " Операции\n\n\
				Снять деньги с карты.\n\
				Наличные: " #cGREEN "$%i" #cWHITE "\n\
				Дебетовая карта [" #cPROJECT "№%i" #cWHITE "]: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму:\n\n\
				" #cGRAY "Минимальная сумма $1, максимальная $100.000.%s",
				GetCharacterMoney(playerid),
				GetCharacterCardNumber(playerid),
				GetCharacterCardBalance(playerid),
				error ? ("\n" #cRED "Недостаточно средств.") : ("")
			);
		}
	}
	else if (type == TYPE_BANK_STATIC)
	{
		if (listitem == 0)
		{
			format:g_string("" #DEFAULT " Операции\n\n\
				Внести наличные на банковский счёт.\n\
				Наличные: " #cGREEN "$%i" #cWHITE "\n\
				Банковский счет: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму:\n\n\
				" #cGRAY "Минимальная сумма $1, максимальная $100.000.%s",
				GetCharacterMoney(playerid),
				GetCharacterBank(playerid),
				error ? ("\n" #cRED "Недостаточно средств.") : ("")
			);
		}
		else if (listitem == 1)
		{
			format:g_string("" #DEFAULT " Операции\n\n\
				Снять деньги с банковского счёта.\n\
				Наличные: " #cGREEN "$%i" #cWHITE "\n\
				Банковский счет: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму:\n\n\
				" #cGRAY "Минимальная сумма $1, максимальная $100.000.%s",
				GetCharacterMoney(playerid),
				GetCharacterBank(playerid),
				error ? ("\n" #cRED "Недостаточно средств.") : ("")
			);
		}
		else if (listitem == 2)
		{
			format:g_string("" #DEFAULT " Операции\n\n\
				Перевод с дебетовой карты на банковский счёт.\n\
				Дебетовая карта [" #cPROJECT "№%i" #cWHITE "]: " #cGREEN "$%i" #cWHITE "\n\
				Банковский счет: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму:\n\n\
				" #cGRAY "Минимальная сумма $1, максимальная $100.000.%s",
				GetCharacterCardNumber(playerid),
				GetCharacterCardBalance(playerid),
				GetCharacterBank(playerid),
				error ? ("\n" #cRED "Недостаточно средств.") : ("")
			);
		}
		else if (listitem == 3)
		{
			format:g_string("" #DEFAULT " Операции\n\n\
				Перевод с банковского счета на дебетовую карту.\n\
				Дебетовая карта [" #cPROJECT "№%i" #cWHITE "]: " #cGREEN "$%i" #cWHITE "\n\
				Банковский счет: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму:\n\n\
				" #cGRAY "Минимальная сумма $1, максимальная $100.000.%s",
				GetCharacterCardNumber(playerid),
				GetCharacterCardBalance(playerid),
				GetCharacterBank(playerid),
				error ? ("\n" #cRED "Недостаточно средств.") : ("")
			);
		}
		else if (listitem == 4)
		{
			format:g_string("" #DEFAULT " Операции\n\n\
				Снять деньги с карты.\n\
				Наличные: " #cGREEN "$%i" #cWHITE "\n\
				Дебетовая карта [" #cPROJECT "№%i" #cWHITE "]: " #cGREEN "$%i" #cWHITE "\n\
				Введите сумму:\n\n\
				" #cGRAY "Минимальная сумма $1, максимальная $100.000.%s",
				GetCharacterMoney(playerid),
				GetCharacterCardNumber(playerid),
				GetCharacterCardBalance(playerid),
				error ? ("\n" #cRED "Недостаточно средств.") : ("")
			);
		}
	}
	
	ShowPlayerDialog(playerid, D_BANK + 3, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
}

ShowRepayPlayerStartCard(playerid, error[] = "")
{
	format:g_string("" #DEFAULT " Операции\n\n\
		Пополнение карты «Start» с помощью дебетовой карты.\n\
		Дебетовая карта [" #cPROJECT "№%i" #cWHITE "]: " #cGREEN "$%i" #cWHITE "\n\
		Карта «Start»: " #cGREEN "$%i" #cWHITE "\n\
		Введите сумму:\n\n\
		" #cGRAY "Минимальная сумма $1, максимальная $100.000.%s",
		GetCharacterCardNumber(playerid),
		GetCharacterCardBalance(playerid),
		GetCharacterCardStart(playerid),
		!isnull(error) ? ("\n" #cRED "Недостаточно средств.") : ("")
	);
	
	ShowPlayerDialog(playerid, D_BANK + 19, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
}