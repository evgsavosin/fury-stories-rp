/*!
	@brief Таймер для системы домов
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

Timer:house()
{		
	for (new i, communal; i < sizeof house_data; i++)
	{
		if (!IsHouseBought(i))
		{
			continue;
		}
		
		if (house_data[i][h_time] < gettime())
		{	
			if (GetHouseTypeBought(i) == TYPE_BUY_FULLY)
			{
				if (house_data[i][h_debt] == 0)
				{
					house_data[i][h_debt_count]++;
					if (house_data[i][h_debt_count] == 2)
					{
						SellHouse(i);
						continue;
					}
					
					Update:house_int(i, "h_debt_count", house_data[i][h_debt_count], true);
				}
				
				communal = GetHouseCommunal(i);
				house_data[i][h_debt] += AddDebtForProperty(communal) ;
				if (GetHouseDebtInPercent(i) >= 10.0)
				{
					SellHouse(i);
				}
				else
				{
					Update:house_int(i, "h_debt", house_data[i][h_debt], true);
				}
			}
			else 
			{
				SellHouse(i);
			}
		}
	}
	
	return 1;
}