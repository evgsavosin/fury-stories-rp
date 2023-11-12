/*!
	@brief Системы для новостей
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

News_OnGameModeInit()
{
	Clear:fraction_news_ether_data();
}

News_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		case D_NEWS_ETHER:
		{
			if (!response)
			{
				cmd_fmenu(playerid);
				return 1;
			}
			
			//new index = GetFractionMember(playerid);
			
			if (listitem == 0) // Начать/Завершить эфир
			{
				new vehicleid = GetPlayerVehicleID(playerid);
				
				if (fraction_news_ether_data[fr_player_id] == INVALID_PLAYER_ID)
				{
					if (!IsPlayerInRangeOfPoint(playerid, 100.0, NEWS_STUDIO_POS) || vehicleid != 0 && vehicle_data[vehicleid][v_model] != 488 && vehicle_data[vehicleid][v_model] != 582)
					{
						SendClientMessage(playerid, C_WHITE, !#ERROR " Вы должны находится в студии или в специализированном транспорте.");
						return 1;
					}
					
					SetPVarInt(playerid, "News:Ether", true);
					
					fraction_news_ether_data[fr_player_id] = playerid;
					
					/*format:g_small_string(#FRACTION_MESSAGE " %s начал%s вещание в прямом эфире.",
						GetPlayerCurrentName(playerid),
						EndWordSex(playerid)
					);
					
					SendFractionMessage(index, g_small_string);*/
					
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы начали вещание в прямом эфире. " #cGRAY "(/e - для отправки сообщения в прямом эфире)");
					return 1;
				}
				else if (fraction_news_ether_data[fr_player_id] == playerid)
				{
					fraction_news_ether_data[fr_player_id] = INVALID_PLAYER_ID;
					
					/*format:g_small_string(#FRACTION_MESSAGE " %s завершил%s вещание в прямом эфире.",
						GetPlayerCurrentName(playerid),
						EndWordSex(playerid)
					);
					
					SendFractionMessage(index, g_small_string);*/
					
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы завершили вещание в прямом эфире.");
					
					foreach (new i : Player)
					{
						DeletePVar(i, "News:Ether");
					}
					
					return 1;
				}
				
				ShowFractionNewsEtherMenu(playerid);
			}
			else if (listitem == 1) // Пригласить в эфир
			{
				if (fraction_news_ether_data[fr_player_id] == INVALID_PLAYER_ID)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Прямой эфир не был начат.");
					return 1;
				}
				
				ShowFractionNewsEtherInvite(playerid);
			}
			else if (listitem == 2) // Отсоединить от эфира
			{
				if (fraction_news_ether_data[fr_player_id] == INVALID_PLAYER_ID)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Прямой эфир не был начат.");
					return 1;
				}
				
				ShowFractionNewsEtherUninvite(playerid);
			}
		}
		
		case D_NEWS_ETHER_INVITE:
		{
			if (!response)
			{
				ShowFractionNewsEtherMenu(playerid);
				return 1;
			}
			
			new targetid = strval(inputtext);
			
			if (isnull(inputtext) || !IsPlayerLogged(targetid) || playerid == targetid || !IsPlayerAroundOfPlayer(playerid, targetid))
			{
				ShowFractionNewsEtherInvite(playerid, "Введён некорректный игрок.");
				return 1;
			}
			
			SetPVarInt(targetid, "News:SenderId", playerid);
			
			format:g_string(#DEFAULT " Приглашение в прямой эфир\n\n\
				" #cPROJECT "%s" #cWHITE " приглашает Вас в прямой эфир.\n\
				Вы принимаете приглашение?",
				GetPlayerCurrentName(playerid)
			);
			
			ShowPlayerDialog(targetid, D_NEWS_ETHER_INVITE_ACCEPT, DIALOG_STYLE_MSGBOX, " ", g_string, "Да", "Нет");
		}
		
		case D_NEWS_ETHER_INVITE_ACCEPT:
		{
			new sender_id = GetPVarInt(playerid, "News:SenderId");
			
			if (response)
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " принял Ваше предложение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(sender_id, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы приняли предложение. " #cGRAY "(/e - для отправки сообщения в прямом эфире)");
			}
			else 
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " отклонил Ваше предложение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(sender_id, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы отклонили предложение.");
			}
			
			SetPVarInt(playerid, "News:Ether", response);
			DeletePVar(playerid, "News:SenderId");
		}
		
		case D_NEWS_ETHER_UNINVITE:
		{
			if (!response)
			{
				ShowFractionNewsEtherMenu(playerid);
				return 1;
			}
			
			new targetid = strval(inputtext);
			
			if (isnull(inputtext) || !IsPlayerLogged(targetid) || playerid == targetid)
			{
				ShowFractionNewsEtherUninvite(playerid, "Введён некорректный игрок.");
				return 1;
			}
			
			pformat:(#SUCCESS " Вы успешно выгнали с эфира " #cPROJECT "%s" #cWHITE ".", targetid);
			psend:(playerid, C_WHITE);
			
			pformat:(#SUCCESS " " #cPROJECT "%s" #cWHITE " выгнал Вас с эфира.", playerid);
			psend:(playerid, C_WHITE);
			
			DeletePVar(playerid, "News:Ether");
		}
	}
	
	return 1;
}

ShowFractionNewsEtherInvite(playerid, error[] = "")
{
	format:g_string(#DEFAULT " Пригласить в эфир\n\n\
		Введите ID игрока, которого хотите пригласить в прямой эфир:\n\n\
		" #cGRAY "Игрок должен находится рядом с Вами.%s%s",
		isnull(error) ? ("") : (cRED),
		error
	);
	
	ShowPlayerDialog(playerid, D_NEWS_ETHER_INVITE, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
}

ShowFractionNewsEtherUninvite(playerid, error[] = "")
{
	format:g_string(#DEFAULT " Выгнать с эфира\n\n\
		Введите ID игрока, которого хотите выгнать с эфира:\n\n\
		" #cGRAY "Игрок должен находится рядом с Вами.%s%s",
		isnull(error) ? ("") : (cRED),
		error
	);
	
	ShowPlayerDialog(playerid, D_NEWS_ETHER_UNINVITE, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
}

ShowFractionNewsEtherMenu(playerid)
{
	clean:<g_small_string>;

	new ether_player_id = fraction_news_ether_data[fr_player_id];
	
	if (ether_player_id == INVALID_PLAYER_ID)
	{
		strcat(g_small_string, "Начать эфир"); 
	}
	else if (ether_player_id == playerid)
	{
		strcat(g_small_string, "Завершить эфир");
	}
	else 
	{
		format:g_small_string("Эфир ведёт " #cPROJECT "%s",
			GetPlayerCurrentName(ether_player_id)
		);
	}
	
	format:g_string(" %s\n \
		Пригласить в эфир\n \
		Выгнать с эфира",
		g_small_string
	);
	
	ShowPlayerDialog(playerid, D_NEWS_ETHER, DIALOG_STYLE_LIST, " ", g_string, "Далее", "Назад");
}

CMD:e(playerid, params[])
{
	if (!IsFractionMember(playerid, FRACTION_NEWS))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (fraction_news_ether_data[fr_player_id] == INVALID_PLAYER_ID)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Прямой эфир не был начат.");
		return 1;
	}
	
	if (!GetPVarInt(playerid, "News:Ether"))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не находитесь в прямом эфире.");
		return 1;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /e [Текст]");
		return 1;
	}
	
	new findex = GetFractionMember(playerid);
	
	new vehicleid,
		index;
	
	foreach (new i : Player)
	{
		if (!IsPlayerLogged(i))
		{
			continue;
		}

		if ((vehicleid = GetPlayerVehicleID(i)) != 0 && !vehicle_data[vehicleid][v_radio])
		{
			continue;
		}
		
		if ((index = GetInventoryDefaultPhone(i)) == INVALID_PARAM || !phone_data[index][ph_radio])
		{
			continue;
		}
		
		format:g_small_string("Эфир %s > %s: %s",
			fraction_data[findex][fr_alt_name],
			GetPlayerCurrentName(playerid),
			params
		);
		
		SendSplitMessage(playerid, 0x5D83F5FF, g_small_string);
	}
	
	return 1;
}