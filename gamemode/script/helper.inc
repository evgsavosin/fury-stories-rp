/*!
	@brief Система Помощника
	@author Found (evg.savosin)
	@date 19.04.2018
*/

// Functions
SendHelperMessage(color, text[], bool: is_split = false)
{
	foreach (new playerid : Player)
	{
		if (IsPlayerGameAdmin(playerid) 
		|| (IsPlayerHelper(playerid) && IsHelperLogged(playerid)))
		{	
			if (is_split)
			{
				SendSplitMessage(playerid, color, text);
			}
			else
			{
				SendClientMessage(playerid, color, text);
			}
		}
	}
}

SendMessageToAsk(playerid, const text[]) 
{
	format:g_small_string("" #ADMIN_MESSAGE " Вопрос %s[%i]: %s",
		GetPlayerCurrentName(playerid),
		playerid, 
		text
	);

	SendHelperMessage(
		C_YELLOW, 
		g_small_string 
	);
	
	pformat:("" #DEFAULT " Текст: " #cGRAY"%s", text);
	psend:(playerid, C_WHITE);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно отправили вопрос помощникам.");
}

// Commands
CMD:hduty(playerid)
{
	if (!IsPlayerHelper(playerid))
	{
		return 0;
	}
	
	if (IsHelperLogged(playerid))
	{
		format:g_small_string("" #HELPER_MESSAGE " %s[%d] покинул дежурство. [IP: %s]",
			GetUserName(playerid),
			playerid,
			GetUserIp(playerid)
		);
		
		SendHelperMessage(C_DARKORANGE, g_small_string);
		
		helper_login{playerid} = 0;
		
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы покинули дежурство. Для возвращения используйте " #cPROJECT "/hduty" #cWHITE ".");
	}
	else 
	{
		helper_login{playerid} = 1;
		
		format:g_small_string("" HELPER_MESSAGE " %s[%d] вышел на дежурство. [IP: %s]",
			GetUserName(playerid),
			playerid,
			GetUserIp(playerid)
		);
	
		SendHelperMessage(C_DARKORANGE, g_small_string);
	}
	
	return 1;
}

CMD:h(playerid, params[])
{
	if (!CheckAdminAccess(playerid, ADMIN_TRAINEE) 
	&& (!IsPlayerHelper(playerid) || !IsHelperLogged(playerid)))
	{
		return 0;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /h [текст]");
		return 1;
	}
	
	format:g_small_string("" HELPER_MESSAGE " %s[%d]: %s",
		GetUserName(playerid),
		playerid,
		params
	);
	
	SendHelperMessage(C_DARKORANGE, g_small_string, true);
	
	return 1;
}