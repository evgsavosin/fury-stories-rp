/*!
	@brief ������� ��������
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
	format:g_string("" #DEFAULT " ��������\n\n\
		�������� ������ �� ��������� �����.\n\
		���������� ���������: " #cGREEN "$%i" #cWHITE "\n\
		������: " #cGREEN "$%i" #cWHITE "\n\
		������� �����:\n\n\
		" #cGRAY "����������� ����� $1, ������������ $100.000.%s%s",
		GetCreditDifference(playerid),
		GetCreditCardBalance(playerid),
		!isnull(error_text) ? ("\n" #cRED "") : (""),
		error_text
	);
	
	ShowPlayerDialog(playerid, D_BANK + 18, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
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
	
	if (credit_data[playerid][credit_expense] > 0) // ���� ������ ������ ������
	{
		if (GetCreditDifference(playerid) != 0) // �� ��������
		{
			if (give_time < gettime())
			{
				new debt = AddDebtForCredit(character_data[playerid][c_credit_level]);
				
				pformat:(#ERROR " ��������! � ��� ��� �� �������� ������. ��������� ����� � �������: " #cGREEN "$%i",
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
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " ������� ����������� ����� �������� � ����������� ���������, � ����� ��������� � �������.");
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
		
				pformat:(#ERROR " ��������! ��� ���������� ��������� ��������� ����� ��: " #cPROJECT "" #DATE_FORMAT "",
					hour, minute,
					day, month, year
				);
				psend:(playerid, C_WHITE);
			}
		}
		else // ��������
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