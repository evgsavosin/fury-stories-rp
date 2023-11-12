/*!
	@brief Команды для системы фурнитуры
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

CMD:fs(playerid)
{
	if (!IsPlayerRenovation(playerid))
	{
		return 1;
	}
	
	SetPVarInt(playerid, "Furn:SelectObject", 1);
	SelectObject(playerid);
	return 1;
}