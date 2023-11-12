/*!
	@brief Таймер для системы сайтов
	@author Found (evg.savosin)
	@date 16.12.2016, update 14.02.2018
*/

Timer:site_hour()
{
	for (new i; i < sizeof site_data; i++)
	{
		if (!GetSiteId(i))
		{
			continue;
		}
		
		if (site_data[i][s_rent_time] <= gettime())
		{
			Remove:site_data(GetPlayerIdByCharacterId(site_data[i][s_character_id]), i);
		}
	}
}