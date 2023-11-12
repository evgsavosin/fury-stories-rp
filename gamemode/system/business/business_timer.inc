/*!
	@brief Таймер для системы бизнесов
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

Timer:business()
{
	for (new i, time = gettime(); i < sizeof business_data; i++)
	{
		if (GetBusinessId(i) == 0)
		{
			continue;
		}
		
		if (business_data[i][b_created_time] >= time + (60 * 60 * 24 * 3) && GetBusinessLinkPremiseCount(i) == 0)
		{
			Remove:business_data(INVALID_PLAYER_ID, i);
		}
	}
}