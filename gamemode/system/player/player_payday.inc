/*!
	@brief Система PayDay
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018

*/

function OnPlayerPayDay(playerid)
{
	new time = gettime(),
		salary,
		salary_additional,
		vip = GetUserVip(playerid);
		
	new bool: is_salary = true;
	
	// Рабочий капитал
	if (character_data[playerid][c_capital_end_time] > 0)
	{
		if (time > character_data[playerid][c_capital_end_time])
		{
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Рабочий капитал больше не активен. Для его продления отправьте повторно заявку на сайте.");
			
			character_data[playerid][c_capital_value] = 0;
			character_data[playerid][c_capital_end_time] = 0;
			
			Update:character_int(playerid, "c_capital_value", 0);
			Update:character_string(playerid, "c_capital_end_date", "FROM_UNIXTIME(0)", false);
		}
		else
		{
			salary += character_data[playerid][c_capital_value];
		}
	}
	
	// Зарплата в организации
	if (IsFractionMember(playerid))
	{
		new index = GetFractionMember(playerid),
			rindex = GetFractionMemberRank(playerid);
		
		if (rindex != INVALID_PARAM)
		{
			salary += fraction_rank_data[index][rindex][fr_salary];
		}
	}
	else 
	{
		salary += MAX_CHARACTER_BENEFIT;
		is_salary = false;
	}
	
	// Увеличение зарплаты VIP
	if (is_salary)
	{
		switch (vip)
		{
			case VIP_STARTER:
			{
				salary_additional = floatround(salary * 0.05);
			}
			
			case VIP_DEFAULT:
			{
				salary_additional = floatround(salary * 0.15);
			}
			
			case VIP_ADVANCED:
			{
				salary_additional = floatround(salary * 0.25);
			}
			
			case VIP_PRO:
			{
				salary_additional = floatround(salary * 0.40);
			}
		}
	}
	
	salary += salary_additional;
	
	// Начисляем на дебетовую карту
	GiveDebitCardMoney(playerid, salary);
	
	// ---------------------------------------------------------------------------
	
	new hour,
		minute;
	
	gettime(hour, minute, _);

    pformat:("" #SUCCESS " Вы отыграли ровно час. Текущее время: %02d:%02d",
        hour, minute
    );
	
	psend:(playerid, C_WHITE);
				
	if (is_salary)
	{
		pformat:(#SUCCESS " Заработная плата: " #cGREEN "$%d" #cWHITE ".", 
			salary
		);
		
		psend:(playerid, C_WHITE);
	}
	else
	{
		pformat:(#SUCCESS " Пособия по безработице: " #cGREEN "$%d" #cWHITE ".",
			salary
		);
		
		psend:(playerid, C_WHITE);
	}
	
	
	pformat:(#SUCCESS " Баланс дебетовой карты №%i: " #cGREEN "$%i" #cWHITE ".",
		GetCharacterCardNumber(playerid),
		GetCharacterCardBalance(playerid)
	);
	
	psend:(playerid, C_WHITE);
	
	if (GetCharacterCardStart(playerid) > 0)
	{
		pformat:(#SUCCESS " Баланс дебетовой карты «Start»: " #cGREEN "$%i" #cWHITE ".",
			GetCharacterCardStart(playerid)
		);
		
		psend:(playerid, C_WHITE);
	}
	
	
	if (IsCreditCardExists(playerid))
	{
		pformat:(#SUCCESS " Баланс кредитной карты №%i: " #cGREEN "$%i" #cWHITE ".",
			GetCreditCardNumber(playerid),
			GetCreditCardBalance(playerid)
		);
		
		psend:(playerid, C_WHITE);
	}
	
	if (vip != 0)
	{
		new vip_end_time = user_data[playerid][u_vip_time] + (60 * 60 * 24 * 30);
		
		pformat:(#SUCCESS " VIP аккаунт: " #cGOLD "%s" #cWHITE ".", 
			GetUserVipText(playerid)
		);
		
		psend:(playerid, C_WHITE);
		
		if (vip != VIP_PRO)
		{
			if (time > vip_end_time && user_data[playerid][u_vip_time]) 
			{
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Действие VIP аккаунта закончилось.");
				
				user_data[playerid][u_vip] = 0;
				user_data[playerid][u_vip_time] = 0;
				
				Update:user_int(playerid, "u_vip", 0);
				Update:user_string(playerid, "u_vip_date", "FROM_UNIXTIME(0)", false);
			}
			
			if (user_data[playerid][u_vip] > 0)
			{
				pformat:(#SUCCESS " Осталось дней: " #cPROJECT "%d" #cWHITE ".", 
					floatround((vip_end_time - time) / (60 * 60 * 24))
				);
				
				psend:(playerid, C_WHITE);
			}
		}
	}
	
	return 1;
}