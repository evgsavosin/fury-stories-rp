/*!
	@brief Таймер для системы трупов
	@author Found (evg.savosin)
	@date 26.04.2017
*/

Timer:corpse()
{
	for (new i; i < sizeof corpse_data; i++)
	{
		if (corpse_data[i][corp_type] == TYPE_CORP_TEMP 
		&& corpse_data[i][corp_created_time] <= (gettime() - (60 * 60 * 2)))
		{
			Remove:corpse_data(i);
		}
	}
}