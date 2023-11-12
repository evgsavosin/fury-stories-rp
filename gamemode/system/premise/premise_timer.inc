/*!
	@brief Таймер для системы помещений
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

Timer:premise()
{		
	for (new i, electric, index; i < sizeof premise_data; i++)
	{
		if (!IsPremiseBought(i))
		{
			continue;
		}
		
		// Аренда/Счета за электроэнергию
		if (premise_data[i][pr_time] < gettime())
		{	
			if (GetPremiseTypeBought(i) == TYPE_BUY_FULLY)
			{
				if (premise_data[i][pr_debt] == 0)
				{
					premise_data[i][pr_debt_count]++;
					if (premise_data[i][pr_debt_count] == 2)
					{
						SellPremise(i);
						continue;
					}
					
					Update:premise_int(i, "pr_debt_count", premise_data[i][pr_debt_count], true);
				}
				
				electric = GetPremiseElectric(i);
				premise_data[i][pr_debt] += AddDebtForProperty(electric) ;
				if (GetPremiseDebtInPercent(i) >= 10.0)
				{
					SellPremise(i);
				}
				else
				{
					Update:premise_int(i, "pr_debt", premise_data[i][pr_debt], true);
				}
			}
			else 
			{
				SellPremise(i);
			}
		}
		
		// Доход
		if (IsPremiseTied(i) && IsPremiseCashExists(i))
		{
			index = GetBusinessIndexById(premise_data[i][pr_business_id]);
			
			if (index == INVALID_PARAM)
			{
				printf("[Timer:premise]: Business (ID:%i) doesn't exists at the server.",
					premise_data[i][pr_business_id]
				);
				
				continue;
			}
			
			GiveBusinessProfit(index, 
				premise_data[i][pr_assort_stock] <= 50 ? 0 : floatround(GetPremiseMinProfit(i) / (24 * 7), floatround_ceil) // Минимальный заработок
				+ GetPremiseProfit(i) // За посетителей + Товар
			);
			
			premise_data[i][pr_profit] = 0;
			Update:premise_int(i, "pr_profit", 0);
			Clear:premise_visitors(i);
		}
	}
	
	return 1;
}

Timer:player_premise(playerid)
{
	if (GetPVarInt(playerid, "Player:PremiseEntranceIndex"))
	{
		if (GetPVarInt(playerid, "Player:PremiseEntranceTime") <= GetTickCount())
		{
			DeletePVar(playerid, "Player:PremiseEntranceIndex");
			DeletePVar(playerid, "Player:PremiseEntranceTime");
		}
	}
}