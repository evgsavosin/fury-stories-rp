/*!
	@brief Команды для системы телефонов
	@author Found (evg.savosin)
	@date 16.12.2016, update 30.01.2018
*/

CMD:p(playerid)
{
	return cmd_phone(playerid);
}

CMD:phone(playerid) 
{	
	new index = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_PHONE, _, true);
	
	if (index == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас отсутствует по умолчанию телефон. Выбрать его можно в инвентаре.");
		return 1;
	}
	
	if (IsInventoryTextDrawShowed(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас уже используется телефон.");
		return 1;
	}
	
	ShowPhone(playerid, index);
	return 1;
}

CMD:pmenu(playerid)
{
	new index = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_PHONE, _, true);
	
	if (index == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас отсутствует по умолчанию телефон. Выбрать его можно в инвентаре.");
		return 1;
	}
	
	if (GetCharacterDeath(playerid) != TYPE_DEATH_NONE)
	{
		SendClientMessage(playerid, C_WHITE, !ERROR_USE_PHONE);
		return 1;
	}
	
	if (ShowPhoneMenu(playerid) == INVALID_PARAM)
	{
		return cmd_phone(playerid);
	}
	
	return 1;
}

CMD:c(playerid, params[])
{
	if (GetCharacterDeath(playerid) != TYPE_DEATH_NONE)
	{
		SendClientMessage(playerid, C_WHITE, !ERROR_USE_PHONE);
		return 1;
	}
		
	if (!IsPlayerCalling(playerid) || GetPVarInt(playerid, "Phone:CallTime") == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не разговариваете ни с кем по телефону.");
		return 1;
	}
	
	if (isnull(params))
	{	
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /c [текст вне разговорного телефона]");
		return 1;
	}
	
	format:g_small_string("%s говорит: %s", 
		GetPlayerCurrentName(playerid), 
		params
	);
	
	ProxDetector(20.0, playerid, g_small_string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
	return 1;
}

CMD:sms(playerid, params[])
{
	if (GetCharacterDeath(playerid) != TYPE_DEATH_NONE)
	{
		SendClientMessage(playerid, C_WHITE, !ERROR_USE_PHONE);
		return 1;
	}
	
	SendSMS(playerid, params, GetInventoryDefaultPhone(playerid));
	return 1;
}

SendSMS(playerid, params[], phone_index)
{
	new value,
		text							[	120		],
		server_tick = GetTickCount();
	
	if (GetPVarInt(playerid, "TimeOut:PhoneSendSms") > server_tick)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
		return 1;
	}
	
	if (phone_index == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !ERROR_ACTIVE_PHONE);
		return 1;
	}
	
	if (sscanf(params, "is[120]", value, text))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /sms [индекс контакта или номер] [сообщение]");
		return 1;
	}
	
	if ((1 <= value <= MAX_CONTACTS)) /// Если от 0 до (MAX_CONTACTS) то индекс контакта
	{
		value--;
		if (contact_data[phone_index][value][pc_number] == 0)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Контакт под данным индексом не найден.");
			return 1;
		}
		
		Create:message(playerid, contact_data[phone_index][value][pc_number], text, INVALID_PARAM);
		
		SetPVarInt(playerid, "TimeOut:PhoneSendSms", server_tick + 5000);
		
		return 1;
	}
	else if ((100_000 <= value <= 999_999)) /// Если 6 значное значение, то номер
	{
		if (value == GetPhoneNumber(phone_index))
		{
			goto SKIP_MESSAGE_SEND;
		}
		
		format:g_string(
			"SELECT COUNT(ph_id) AS phone_valid \
			FROM " #__PHONES " \
			WHERE ph_number = %i \
			LIMIT 1",
			value
		);
		
		mysql_tquery(db, g_string, "OnPhoneSendMessage", "iis", playerid, value, text);
		
		SetPVarInt(playerid, "TimeOut:PhoneSendSms", server_tick + 5000);
		return 1;
	}
	
	SKIP_MESSAGE_SEND:
	
	SendClientMessage(playerid, C_WHITE, !#ERROR " Вы ввели неверный номер или индекс контакта.");
	return 1;
}

function OnPhoneSendMessage(playerid, number, text[120])
{
	new is_valid;
	
	cache_get_value_name_int(0, "phone_valid", is_valid);
	
	if (is_valid == 0)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный номер не зарегистрирован в сети AT&T.");
		return 1;
	}
	
	Create:message(playerid, number, text, INVALID_PARAM);
	return 1;
}
