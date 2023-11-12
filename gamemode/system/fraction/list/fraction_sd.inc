/*!
	@brief Системы для департамента шерифа
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

CMD:jail(playerid, params[]) 
{
	if (!IsFractionMember(playerid, FRACTION_SD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
		
	new targetid,
		time;
		
	if (sscanf(params, "ud", targetid, time))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /jail [ID игрока] [Количество минут]");
		return 1;
	}
	
	if (GetCharacterWorld(playerid) != WORLD_PRISON)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Для использования данной команды, Вам необходимо находиться внутри тюрьмы.");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (IsCharacterJailed(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок уже находится в городской тюрьме.");
		return 1;
	}
		
	if (!(0 < time < 1000))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Срок в городской тюрьме может быть от 1 минуты до 60 минут.");
		return 1;
	}
	
	new follow_id = GetPVarInt(targetid, "Player:Follow");
	
	if (follow_id != INVALID_PLAYER_ID) 
	{
		SetPVarInt(follow_id, "Player:Lead", INVALID_PLAYER_ID);
		SetPVarInt(targetid, "Player:Follow", INVALID_PLAYER_ID);
	}
	
	if (GetPVarInt(targetid, "Player:Cuff")) 
	{
		DeletePVar(targetid, "Player:Cuff");
		RemovePlayerAttachedObject(playerid, SLOT_ATTACH_TEMP);
		SetPlayerSpecialAction(targetid, SPECIAL_ACTION_NONE);
		TogglePlayerControllable(targetid, true);	
	}	
	
	ImprisonPlayerToJail(targetid, time);
	
	pformat:(#DEFAULT " Вы были помещены в городскую тюрьму " #cPROJECT "%s" #cWHITE " на " #cPROJECT "%d" #cWHITE " мин.", GetPlayerCurrentName(playerid), time);
	psend:(targetid, C_WHITE );
		
	pformat:(#SUCCESS " Вы успешно поместили в городскую тюрьму " #cPROJECT "%s" #cWHITE " на " #cPROJECT "%d" #cWHITE " мин.",GetPlayerCurrentName(targetid), time);
	psend:(playerid, C_WHITE);
	return 1;
}

CMD:setjail( playerid, params[] )
{
	if (!IsFractionMember(playerid, FRACTION_SD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
		
	new targetid,
		time;
		
	if (sscanf(params, "ud", targetid, time))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /setjail [ID игрока] [Количество минут]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
		
	if (!(0 < time < 1000))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Срок в городской тюрьме может быть от 1 минуты до 60 минут.");
		return 1;
	}
	
	character_data[targetid][c_arrest_time] = time != 0 ? (gettime() + (time * 60)) : 0;
	format:g_small_string("FROM_UNIXTIME(%d)", character_data[targetid][c_arrest_time]);
	Update:character_string(targetid, "c_arrest_date", g_small_string, false);
	
	pformat:(#DEFAULT " Ваш срок заключения был изменен " #cPROJECT "%s" #cWHITE " на " #cPROJECT "%d" #cWHITE " мин.", GetPlayerCurrentName(playerid), time);
	psend:(targetid, C_WHITE );
		
	pformat:(#SUCCESS " Вы успешно изменили срок заключения в тюрьме " #cPROJECT "%s" #cWHITE " на " #cPROJECT "%d" #cWHITE " мин.",GetPlayerCurrentName(targetid), time);
	psend:(playerid, C_WHITE);
	return 1;
}

CMD:unjail( playerid, params[] )
{
	if (!IsFractionMember(playerid, FRACTION_SD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
		
	new targetid;
		
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /unjail [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (!IsCharacterJailed(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный игрок не находится в городской тюрьме.");
		return 1;
	}
	
	ResetPlayerArrest(targetid);
	
	pformat:(#SUCCESS " Вы выпустили " #cPROJECT "%s" #cWHITE " из городской тюрьмы.", GetPlayerCurrentName(targetid));
	psend:(playerid, C_WHITE);
	
	pformat:(#DEFAULT " " #cPROJECT "%s" #cWHITE " выпустил Вас из городской тюрьмы.", GetPlayerCurrentName(playerid));
	psend:(targetid, C_WHITE );
	return 1;
}