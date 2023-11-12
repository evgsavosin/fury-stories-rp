/*!
	@brief Система прибыли
	@author Found (evg.savosin)
	@date 16.12.2016, update 01.04.2018
*/

GivePremiseProfitByVisitor(index, playerid)
{
	if (!IsPremiseVisitorExists(playerid, index))
	{
		for (new i; i < MAX_PREMISE_VISITORS; i++)
		{
			if (premise_visitors[index][i][prv_character_id] == 0)
			{
				premise_visitors[index][i][prv_character_id] = GetCharacterId(playerid);
				
				premise_visitors[index][i][prv_ip][0] = EOS;
				strcat(premise_visitors[index][i][prv_ip], GetUserIp(playerid), MAX_PLAYER_IP);
				
				GivePremiseProfit(index, floatround(GetPremiseRent(index) * 0.02));
				
				return 1;
			}
		}
	}
	
	return 0;
}

IsPremiseVisitorExists(playerid, index)
{
	if (!GetPlayerPremisesCount(playerid))
	{
		for (new i; i < MAX_PREMISE_VISITORS; i++)
		{
			if (premise_visitors[index][i][prv_character_id] == GetCharacterId(playerid)
			|| !strcmp(premise_visitors[index][i][prv_ip], GetUserIp(playerid)))
			{
				return 1;
			}
		}
	}
		
	return 0;
}
