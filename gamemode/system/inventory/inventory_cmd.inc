/*!
	@brief Команды для системы инвентаря
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

CMD:inv(playerid)
{	
	ShowInventory(playerid, GetUserSettings(playerid, SET_INVENTORY));
	return 1;
}

CMD:undress(playerid)
{
	if (IsFractionMember(playerid) && GetFractionMemberSkin(playerid))
	{
		SendClientMessage(playerid, C_WHITE, #ERROR " Прежде, чем снять одежду, необходимо уйти с дежурства.");
		return 1;
	}
	
	if (ResetPlayerSkin(playerid) == character_data[playerid][c_skin])
	{
		return 1;
	}
	
	ShowPlayerDialog(playerid, D_INV + 10, DIALOG_STYLE_MSGBOX, " ", 
		"" #DEFAULT " Снять одежду\n\nВы действительно хотите снять одежду с персонажа?",
		"Да", "Нет"
	);
	
	return 1;
}

CMD:boombox(playerid)
{
	for (new i; i < sizeof drop_data; i++)
	{
		if (drop_data[i][drop_item_id] == 0 
		|| !IsPlayerInDynamicArea(playerid, drop_data[i][drop_area]))
		{
			continue;
		}
		
		ShowMusicMenu(playerid, MUSIC_TYPE_BOOMBOX, i);
		
		return 1;
	}
	
	SendClientMessage(playerid, C_WHITE, !#ERROR " Для использования данной команды необходимо находиться рядом с бумбоксом.");
	return 1;
}

CMD:remsmoke(playerid)
{
	if (!IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ATTACH_SMOKE))
	{	
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не используете сигарету в данный момент.");
		return 1;
	}
	
	RemovePlayerAttachedObject(playerid, SLOT_ATTACH_SMOKE);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы выбросили окурок.");
	return 1;
}

CMD:channel(playerid, params[]) 
{
	new index,
		itindex,
		channel,
		radio_type;
	
	if ((index = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_RADIO, _, true)) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас отсутствует рация.");
		return 1;
	}
	
	if ((itindex = GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id))) == INVALID_PARAM)
	{
		return 1;
	}
	
	radio_type = item_list[itindex][it_param_1];
	
	if (sscanf(params, "i", channel))
	{
		SendClientMessage(playerid, C_WHITE, (
			radio_type == INV_FUNC_RADIO_HIGH ? 
			("" #DEFAULT " Введите: /channel [номер канала (0 - 999)]") 
			: ("" #DEFAULT " Введите: /channel [номер канала (0 - 333)]"))
		);
		
		return 1;
	}
	
	if (radio_type == INV_FUNC_RADIO_HIGH 
	&& !(0 <= channel <= 999))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы выбрали некорректный канал. Используйте номер канала от " #cPROJECT "0 до 999" #cWHITE ".");
		return 1;
	}
	else if (radio_type == INV_FUNC_RADIO_LOW
	&& !(0 <= channel <= 333))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы выбрали некорректный канал. Используйте номер канала от " #cPROJECT "0 до 333" #cWHITE ".");
		return 1;
	}

	switch(channel)
	{
		case 900:
		{
			if (!IsFractionMember(playerid, FRACTION_GOVERNMENT))
			{
				SendClientMessage(playerid, C_WHITE, #ERROR " Данный канал зашифрован.");
				return 1;
			}
		}
		
		case 911:
		{
			if (!IsFractionMember(playerid, FRACTION_PD))
			{
				SendClientMessage(playerid, C_WHITE, #ERROR " Данный канал зашифрован.");
				return 1;
			}
		}
		
		case 999:
		{
			if (!IsFractionMember(playerid, FRACTION_SD))
			{
				SendClientMessage(playerid, C_WHITE, #ERROR " Данный канал зашифрован.");
				return 1;
			}
		}
		
		case 991:
		{
			if (!IsFractionMember(playerid, FRACTION_FD))
			{
				SendClientMessage(playerid, C_WHITE, #ERROR " Данный канал зашифрован.");
				return 1;
			}
		}
		
		case 933:
		{
			if (!IsFractionMember(playerid, FRACTION_NP))
			{
				SendClientMessage(playerid, C_WHITE, #ERROR " Данный канал зашифрован.");
				return 1;
			}
			
			return 1;
		}	
	}
	
	if (IsFractionMember(playerid))
	{
		if (!CheckFractionAccess(playerid, fr_perm_radio))
		{
			SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
			return 1;
		}
	}
	
	pformat:("" #DEFAULT " Вы успешно переключили канал рации на " #cPROJECT "%i" #cWHITE ".", channel);
	psend:(playerid, C_WHITE);

	SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1, channel);
	Update:item_data(playerid, index, TYPE_INV_PLAYER);
	return 1;
}

CMD:slot(playerid, params[]) 
{	
	new slot,
		index;
	
	if ((index = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_RADIO, _, true)) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас отсутствует рация.");
		return 1;
	}
	
	if (sscanf(params, "i", slot))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /slot [номер канала (1 - 99)]");
		
		return 1;
	}
	
	if (!(1 <= slot <= 99))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы выбрали некорректный канал. Используйте номер канала от " #cPROJECT "1 до 999" #cWHITE ".");
		return 1;
	}
	
	pformat:("" #DEFAULT " Вы успешно переключили слот рации на " #cPROJECT "%i" #cWHITE ".", slot);
	psend:(playerid, C_WHITE);

	SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_2, slot);
	Update:item_data(playerid, index, TYPE_INV_PLAYER);
	return 1;
}

CMD:r(playerid, params[])
{
	new index;
	
	if ((index = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_RADIO, _, true)) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас отсутствует рация.");
		return 1;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /r [текст]");
		return 1;
	}
	
	if (GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1) == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не настроили рацию. " #cGRAY "(/channel, /slot - настройка)");
		return 1;
	}
	
	format:g_small_string("" #RADIO_MESSAGE " %s: %s", 
		GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1),
		1,
		GetPlayerCurrentName(playerid), 
		params
	);
	
	SendRadioMessage(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1), _, g_small_string);
		
	format:g_small_string("%s говорит: %s",
		GetPlayerCurrentName(playerid),
		params
	);
	
	ProxDetector(10.0, playerid, g_small_string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, true, true);
	return 1;
}

CMD:rr(playerid, params[])
{
	new index;
	
	if ((index = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_RADIO, _, true)) == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас отсутствует рация.");
		return 1;
	}
	
	if (isnull(params))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /rr [текст]");
		return 1;
	}
	
	if (GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1) == 0 
	|| GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_2) == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не настроили рацию. " #cGRAY "(/channel, /slot - настройка)");
		return 1;
	}
	
	format:g_small_string("" #RADIO_MESSAGE " %s: %s", 
		GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1),
		GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_2),
		GetPlayerCurrentName(playerid), 
		params
	);
	
	SendRadioMessage(
		GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1), 
		GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_2), 
		g_small_string 
	);
		
	format:g_small_string("%s говорит: %s",
		GetPlayerCurrentName(playerid),
		params
	);
	
	ProxDetector(10.0, playerid, g_small_string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, true, true);
	return 1;
}