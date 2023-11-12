/*!
	@brief Сайл с командами криминальных систем
	@author Flavo
	@date 03.11.2019
*/

CMD:crmenu(playerid, params[])
{
	if (!CheckCrimeAccess(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	ShowCrimeList(playerid);
	return 1;
}

CMD:crinvite(playerid, params[])
{
	if (!CheckCrimeAccess(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}

	if (isnull(params) || !IsInt(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " ¬ведите: /invite [ID игрока]");
		return 1;
	}
	
	InvitePlayerToCrime(playerid, params, false);
	return 1;
}