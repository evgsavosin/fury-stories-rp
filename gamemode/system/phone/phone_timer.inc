/*!
	@brief Таймер для системы телефонов
	@author Found (evg.savosin)
	@date 16.12.2016, update 04.02.2018
*/

Timer:phone()
{
	TD_UpdatePhoneDate();
	
	for (new i; i < sizeof phone_data; i++)
	{
		if (phone_data[i][ph_paid_time] == 0)
		{
			continue;
		}
		
		if (phone_data[i][ph_paid_time] < gettime())
		{
			phone_data[i][ph_paid_time] = 0;
			Update:phone_data(INVALID_PLAYER_ID, i);
			
			if (phone_data[i][ph_player_id] != INVALID_PLAYER_ID)
			{
				SendClientMessage(phone_data[i][ph_player_id], C_DARKYELLOW, "" #SMS_MESSAGE " От AT&T: Обслуживание сотовой связи приостановлено. Пополните баланс.");
			}
		}
	}
}