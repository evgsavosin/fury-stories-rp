/*!
	@brief Система кредитов
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

Load:character_credit(playerid)
{
	new is_exists_credit;
	
	cache_get_value_name_int(0, "is_exists_credit", is_exists_credit);
		
	if (is_exists_credit != 0)
	{
		cache_get_value_name_int(0, "credit_card", credit_data[playerid][credit_card]);
		cache_get_value_name_int(0, "credit_expense", credit_data[playerid][credit_expense]);
		cache_get_value_name_int(0, "credit_limit", credit_data[playerid][credit_limit]);
		cache_get_value_name_int(0, "credit_give_time", credit_data[playerid][credit_give_time]);
	}
}

ShowRepayPlayerCredit(playerid, error_text[] = "")
{
	format:g_string("" #DEFAULT " Операции\n\n\
		Погасить кредит на кредитной карте.\n\
		Необходимо выплатить: " #cGREEN "$%i" #cWHITE "\n\
		Баланс: " #cGREEN "$%i" #cWHITE "\n\
		Введите сумму:\n\n\
		" #cGRAY "Минимальная сумма $1, максимальная $100.000.%s%s",
		GetCreditDifference(playerid),
		GetCreditCardBalance(playerid),
		!isnull(error_text) ? ("\n" #cRED "") : (""),
		error_text
	);
	
	ShowPlayerDialog(playerid, D_BANK + 18, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
}

ResetPlayerCredit(playerid, fully = false)
{
	ResetPremisesCredit(playerid);
	ResetHousesCredit(playerid);
	ResetVehiclesCredit(playerid);
	
	if (fully)
	{
		credit_data[playerid][credit_expense] =
		credit_data[playerid][credit_card] = 
		credit_data[playerid][credit_limit] = 
		credit_data[playerid][credit_give_time] = 0;
		Remove:credit_data(playerid);
	}
	else 
	{
		credit_data[playerid][credit_give_time] = gettime();
		Update:credit_data(playerid);
	}
}

GiveCreditCardMoney(const playerid, money)
{	
	if (!(0 <= (credit_data[playerid][credit_card] + money) <= credit_data[playerid][credit_limit]))
	{
		return 0;
	}
	
	if (money < 0)
	{
		credit_data[playerid][credit_expense] += money;
	}
	
	credit_data[playerid][credit_card] += money;
	Update:credit_data(playerid);
	return 1;
}

Check:credit(playerid)
{
	if (!IsCreditCardExists(playerid))
	{
		return;
	}
	
	new give_time = GetCreditDateSuccess(credit_data[playerid][credit_give_time]);
	
	if (credit_data[playerid][credit_expense] > 0) // Если прошло больше месяца
	{
		if (GetCreditDifference(playerid) != 0) // Не выплачен
		{
			if (give_time < gettime())
			{
				new debt = AddDebtForCredit(character_data[playerid][c_credit_level]);
				
				pformat:(#ERROR " Внимание! У Вас был не выплачен кредит. Начислено пение в размере: " #cGREEN "$%i",
					debt
				);
				
				psend:(playerid, C_WHITE);
				
				if (floatround(credit_data[playerid][credit_limit] / credit_data[playerid][credit_limit]) > 0.7)
				{
					new value;
					
					if ((value = GetPlayerHouse(playerid, true, true)) != INVALID_PARAM)
					{
						SellHouse(value);
					}
				}
				else 
				{
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " Наличие задолжности может привести к конфискации имущества, а также проблемам с законом.");
				}
				
				if (character_data[playerid][c_credit_level] > 0)
				{
					character_data[playerid][c_credit_level] -= 1;
				}
				
				credit_data[playerid][credit_limit] += debt;
				ResetPlayerCredit(playerid);
			}
			else
			{
				new year,
					month,
					day,
					hour,
					minute;
					
				gmtime(give_time, year, month, day, hour, minute);
		
				pformat:(#ERROR " Внимание! Вам необходимо пополнить кредитную карту до: " #cPROJECT "" #DATE_FORMAT "",
					hour, minute,
					day, month, year
				);
				psend:(playerid, C_WHITE);
			}
		}
		else // Выплачен
		{
			if (character_data[playerid][c_credit_level] < 3)
			{
				character_data[playerid][c_credit_level] += 1;
			}
			
			credit_data[playerid][credit_expense] = 0;
			ResetPlayerCredit(playerid);
		}
	}
}