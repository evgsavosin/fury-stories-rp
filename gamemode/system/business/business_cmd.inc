/*!
	@brief Команды для системы бизнесов
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

CMD:bleave(playerid)
{
	if (!IsBusinessMember(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не являетесь участником какой-либо компании.");
		return 1;
	}
	
	Remove:bmember_data(GetCharacterId(playerid), playerid);
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно покинули компанию.");
	return 1;
}

CMD:bmenu(playerid)
{
	if (bmember_data[playerid][bm_business_index] != INVALID_PARAM)
	{
		SetPVarInt(playerid, "Business:Select", bmember_data[playerid][bm_business_index]);
		ShowPlayerDialog(playerid, D_BUSINESS + 7, DIALOG_STYLE_LIST, " ", DIALOG_BUSINESS_MANAGE, "Далее", "Назад");
	}
	else 
	{
		if (GetPlayerBusinessesCount(playerid) == 0)
		{
			SendClientMessage(playerid, C_WHITE, !PLAYER_NO_BUSINESS);
			return 1;
		}
		
		ShowBusinessList(playerid, D_BUSINESS + 6, false);
	}

	return 1;
}