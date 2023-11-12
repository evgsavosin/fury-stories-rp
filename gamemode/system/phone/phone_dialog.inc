/*!
	@brief Диалоги для системы телефона
	@author Found (evg.savosin)
	@date 16.12.2016, update 30.01.2018
*/

Phone_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	// Include
	_Phone_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	
	// Other code
	switch(dialogid)
	{
		case D_PHONE - 1 :
		{
			if (!response)
			{
				return 1;
			}
			
			if (listitem == 0)
			{
				new server_tick = GetTickCount(),
					index = GetPVarInt(playerid, "Phone:Select");
				
				if (GetPVarInt(playerid, "TimeOut:Phone") > server_tick)
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
					return 1;
				}
				
				phone_data[index][ph_status] = !phone_data[index][ph_status];
				
				ShowPhoneTextDraw(playerid, false, _, _, false, _, true);
				ShowPhoneTextDraw(playerid, true, PH_PAGE_DESKTOP, index);

				SetPVarInt(playerid, "TimeOut:Phone", server_tick + 1000);
			}
		}
		
		case D_PHONE :
		{
			if (!response)
			{
				return 1;
			}
			
			if (GetPVarInt(playerid, !"Inventory:States")
			|| GetPVarInt(playerid, !"Site:States"))
			{
				SendClientMessage(playerid, C_WHITE, !ERROR_INTERFACE);
				return 1;
			}
			
			if (IsPhoneShowed(playerid))
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас уже используется телефон. Для выхода используйте " #cPROJECT "ESC" #cWHITE ".");
				return 1;
			}
			
			new index = g_dialog_select[playerid][listitem];
			
			if (phone_data[index][ph_call_index] != INVALID_PARAM)
			{
				if (!ShowPhoneTextDraw(playerid, true, PH_PAGE_INCOMING_CALL, index, _, phone_data[index][ph_call_index]))
				{
					SendClientMessage(playerid, C_WHITE, !ERROR_INTERFACE);
				}
			}
			else 
			{
				if (!ShowPhoneTextDraw(playerid, true, PH_PAGE_DESKTOP, index))
				{
					SendClientMessage(playerid, C_WHITE, !ERROR_INTERFACE);
				}
			}
		}
		
		case D_PHONE + 1 :
		{
			if (!response) // удалить
			{
				return 1;
			}
			
			new index = GetPVarInt(playerid, !"Phone:Select"),
				number = GetPVarInt(playerid, !"Phone:ConversationNumber"),
				name 		[	MAX_PLAYER_NAME	+ 1];
			
			GetItemListNameOfContact(index, number, name);
			
			format:g_string("" #DEFAULT " Удалить беседу\n\n\
				Вы действительно собираетесь удалить беседу с " #cPROJECT "%i" #cWHITE "?", 
				name
			);
			
			ShowPlayerDialog(playerid, D_PHONE + 2, DIALOG_STYLE_MSGBOX, " ",
				g_string,
				"Да", "Нет"
			);
		}
		
		case D_PHONE + 2 :
		{
			if (response)
			{
				new index = GetPVarInt(playerid, !"Phone:Select"),
					number = GetPVarInt(playerid, !"Phone:ConversationNumber");
					
				format:g_string("\
					DELETE c, m \
					FROM \
						" #__CONVERSATIONS " c \
					LEFT JOIN \
						" #__MESSAGES " m \
						ON (c.pc_to_number = m.pm_to_number AND pm_type = %i \ 
						OR c.pc_to_number = m.pm_from_number AND pm_type = %i) \
					WHERE c.pc_from_number = %i AND c.pc_to_number = %i",
					TYPE_PH_OUTGOING,
					TYPE_PH_INCOMING,
					GetPhoneNumber(index),
					number
				);
				
				mysql_tquery(db, g_string);
				
				GetItemListNameOfContact(index, number, g_string);
				
				pformat:("" #SUCCESS " Вы успешно удалили беседу с " #cPROJECT "%s" #cWHITE ".", 
					g_string
				);
				
				psend:(playerid, C_WHITE);
				
				UpdatePhone(playerid, PH_PAGE_SMS, index);
			}
		}
		
		case D_PHONE + 3 :
		{
			if (!response)
			{	
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowPlayerDialog(playerid, D_PHONE + 10, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Написать сообщение\n\n\
					Введите номер, на который Вы хотите отправить сообщение:",
					"Далее", "Отмена"
				);
			}
			else
			{
				ShowPlayerDialog(playerid, D_PHONE + 4, DIALOG_STYLE_MSGBOX, " ",
					"" #DEFAULT " Удалить все переписки\n\n\
					Внимание! Вы действительно хотите удалить все беседы?\n\n\
					" #cGRAY "Вы не сможете восстановить удаленные диалоги.",
					"Да", "Нет"
				);
			}
		}
		
		case D_PHONE + 4 :
		{
			if (!response)
			{
				return 1;
			}
			
			new index = GetPVarInt(playerid, !"Phone:Select");
				
			format:g_string("\
				DELETE c, m \
				FROM \
					" #__CONVERSATIONS " c \
				LEFT JOIN \
					" #__MESSAGES " m \
					ON (c.pc_to_number = m.pm_to_number AND pm_type = %i \ 
					OR c.pc_to_number = m.pm_from_number AND pm_type = %i) \
				WHERE c.pc_from_number = %i",
				TYPE_PH_OUTGOING,
				TYPE_PH_INCOMING,
				GetPhoneNumber(index)
			);
			
			mysql_tquery(db, g_string, "OnPhoneDeleteConversations", "ii", playerid, index);
		}
		
		case D_PHONE + 5 :
		{
			if (!response)
			{
				return 1;
			}
			
			new index = GetPVarInt(playerid, !"Phone:Select");
			
			if (isnull(inputtext) 
			|| !IsValidPhoneContactName(inputtext, 3, MAX_PLAYER_NAME))
			{
				ShowPlayerDialog(playerid, D_PHONE + 5, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Добавить новый контакт\n\n\
					Введите название контакта:\n\n\
					" #cRED "Название должно быть написано на латинских буквах и цифрах.\n\
					Минимальная длина 3 символа, максимальная 24.",
					"Далее", "Назад"
				);
	
				return 1;
			}
			
			Create:contact(
				playerid, 
				index, 
				GetPVarInt(playerid, !"Phone:AddNumber"), 
				inputtext 
			);
			
			DeletePVar(playerid, !"Phone:AddNumber");
		}
		
		case D_PHONE + 6 :
		{
			if (!response)
			{
				return 1;
			}
			
			new phone_index = GetPVarInt(playerid, "Phone:Select"),
				index = GetPVarInt(playerid, "Phone:ContactSelect");
			
			if (listitem == 0) /// Информация
			{
				ShowPhoneContactInformation(playerid, phone_index, index);
			}
			
			else if (listitem == 1) /// Позвонить
			{
				if (!PhoneCall(playerid, phone_index, contact_data[phone_index][index][pc_number]))
				{
					ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", DIALOG_PHONE_NUMBER, "Закрыть", "");
					return 1;
				}
			}
			
			else if (listitem == 2) /// Отправить смс
			{
				ShowPlayerDialog(playerid, D_PHONE + 8, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Отправить сообщение\n\n\
					Введите сообщение, которое Вы хотите отправить:",
					"Далее", "Назад"
				);
			}
			
			else if (listitem == 3) /// Переименовать
			{
				ShowPlayerDialog(playerid, D_PHONE + 9, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Переименовать контакт\n\n\
					Введите новое название:",
					"Далее", "Назад"
				);
			}
			
			else if (listitem == 4) /// Удалить
			{
				format:g_string("" #DEFAULT " Удалить контакт\n\n\
					Вы действительно хотите удалить " #cPROJECT "%s" #cWHITE " из своих контактов?",
					contact_data[phone_index][index][pc_name]
				);
				
				ShowPlayerDialog(playerid, D_PHONE + 7, DIALOG_STYLE_MSGBOX, " ", g_string, "Да", "Нет");
			}
		}
		
		case D_PHONE + 7 :
		{
			new phone_index = GetPVarInt(playerid, "Phone:Select"),
				index = GetPVarInt(playerid, "Phone:ContactSelect");
				
			if (response)
			{
				format:g_string("DELETE FROM " #__CONTACTS " \
					WHERE pc_number = %i AND pc_phone_id = %i \
					LIMIT 1",
					contact_data[phone_index][index][pc_number],
					GetPhoneId(phone_index)
				);
				
				mysql_pquery(db, g_string);
				
				
				pformat:("" #SUCCESS " Вы успешно удалили " #cPROJECT "%s" #cWHITE " из контактов.",
					contact_data[phone_index][index][pc_name]
				);
				
				psend:(playerid, C_WHITE);
				
				Clear:contact_data(phone_index, index);
				
				UpdatePhonePageContacts(playerid, GetPVarInt(playerid, "Phone:ItemPage"), phone_index);
			}
			else 
			{
				ShowPhoneContactMenu(playerid, index);
			}
		}
		
		case D_PHONE + 8 :
		{
			new index = GetPVarInt(playerid, "Phone:ContactSelect");
				
			if (!response)
			{
				ShowPhoneContactMenu(playerid, index);
				return 1;
			}
			
			format:g_small_string("%i %s", index + 1, inputtext);
			SendSMS(playerid, g_small_string, GetPVarInt(playerid, "Phone:Select"));
			ShowPhoneContactMenu(playerid, index);
		}
		
		case D_PHONE + 9 :
		{
			if (!IsUserAllowQuery(playerid))
			{
				return 1;
			}
			
			new phone_index = GetPVarInt(playerid, "Phone:Select"),
				index = GetPVarInt(playerid, "Phone:ContactSelect");
				
			if (!response)
			{
				ShowPhoneContactMenu(playerid, index);
				return 1;
			}
			
			if (isnull(inputtext) 
			|| !IsValidPhoneContactName(inputtext, 3, MAX_PLAYER_NAME))
			{
				ShowPlayerDialog(playerid, D_PHONE + 9, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Переименовать контакт\n\n\
					Введите новое название:\n\n\
					" #cRED "Название должно быть написано на латинских буквах и цифрах.\n\
					Минимальная длина 3 символа, максимальная 24.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			pformat:("" #SUCCESS " Вы успешно переименовали контакт " #cPROJECT "%s" #cWHITE ". Новое имя: " #cPROJECT "%s" #cWHITE ".",
				contact_data[phone_index][index][pc_name],
				inputtext
			);
			
			psend:(playerid, C_WHITE);
			
			contact_data[phone_index][index][pc_name][0] = EOS;
			strcat(contact_data[phone_index][index][pc_name], inputtext, MAX_PLAYER_NAME);
			
			format:g_string("UPDATE " #__CONTACTS " SET pc_name = '%q' WHERE pc_number = %i LIMIT 1",
				inputtext,
				contact_data[phone_index][index][pc_name]
			);
			
			mysql_tquery(db, g_string, "OnPhoneContactUpdate", "d", playerid);
			
			SetUserAllowQuery(playerid, false);
			
			ShowPhoneContactMenu(playerid, index);
			
			UpdatePhone(playerid, PH_PAGE_CONTACTS, phone_index);
		}
		
		case D_PHONE + 10 :
		{
			if (!response)
			{
				return 1;
			}
			
			new number = strval(inputtext);
			
			if (isnull(inputtext) || !IsInt(inputtext) || !(100_000 <= number <= 999_999))
			{
				ShowPlayerDialog(playerid, D_PHONE + 10, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Написать сообщение\n\n\
					Введите номер, на который Вы хотите отправить сообщение:\n\n\
					" #cRED "Вы ввели неверный номер. Вводимый номер должен быть в формате XXXXXX.",
					"Далее", "Отмена"
				);
				
				return 1;
			}
			
			SetPVarInt(playerid, "Phone:SendMessageNumber", number);
			
			ShowPlayerDialog(playerid, D_PHONE + 11, DIALOG_STYLE_INPUT, " ", 
				"" #DEFAULT " Отправить сообщение\n\n\
				Введите сообщение, которое Вы хотите отправить:",
				"Далее", "Назад"
			);
		}
		
		case D_PHONE + 11 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_PHONE + 11, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Написать сообщение\n\n\
					Введите номер, на который Вы хотите отправить сообщение:",
					"Далее", "Отмена"
				);
				
				return 1;
			}
			
			format:g_small_string("%i %s", GetPVarInt(playerid, "Phone:SendMessageNumber"), inputtext);
			SendSMS(playerid, g_small_string, GetPVarInt(playerid, "Phone:Select"));
			
			DeletePVar(playerid, "Phone:SendMessageNumber");
		}
		
		case D_PHONE + 12 :
		{
			if (!response)
			{
				return 1;
			}
			
			//new index = GetPVarInt(playerid, "Phone:Select");
			
			switch(listitem)
			{
				case 0: /// Settings
				{
					ShowPlayerDialog(playerid, D_PHONE + 13, DIALOG_STYLE_LIST, " ",
						" Изменить мелодию вызова",
						"Далее", "Закрыть"
					);
				}
				
				case 1: /// GOG Maps
				{
					cmd_gps(playerid);
				}
				
				case 2: /// Fuber
				{
					ShowFuberPassengerDialog(playerid, D_PHONE_APP_FUBER + 1);
				}
				
				case 3: /// Fuber Driver
				{
					ShowFuberDriverDialog(playerid, D_PHONE_APP_FUBER + 6);
				}
				
				case 4: /// Radio
				{
					ShowPlayerDialog(playerid, D_PHONE + 17, DIALOG_STYLE_MSGBOX, " ", #DEFAULT " Radio\n\n\
						Данное приложение позволяет прослушивать прямые эфиры.\n\
						Ваши действия:", 
						"Вкл", "Выкл"
					);
				}
			}
		}
		
		case D_PHONE + 13 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_PHONE + 12, DIALOG_STYLE_LIST, "Apps", DIALOG_PHONE_APPS, "Выбрать", "Закрыть");
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowPhoneMusicList(playerid, D_PHONE + 14);
			}
		}
		
		case D_PHONE + 14 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_PHONE + 13, DIALOG_STYLE_LIST, " ",
					" Изменить мелодию вызова",
					"Далее", "Закрыть"
				);
				
				return 1;
			}
			
			SetPVarInt(playerid, "Phone:MusicId", listitem);
			
			PhonePlayMusic(playerid, listitem);
			
			ShowPlayerDialog(playerid, D_PHONE + 15, DIALOG_STYLE_MSGBOX, " ", 
				"" #DEFAULT " Установить мелодию вызова\n\n\
				Данная мелодия автоматически проигрывается в данный момент.\n\
				Желаете установить её?",
				"Да", "Нет"
			);
		}
	
		case D_PHONE + 15 :
		{
			if (!response)
			{
				PhonePlayMusic(playerid, 0);
				ShowPhoneMusicList(playerid, D_PHONE + 14);
				return 1;
			}
			
			new phone_index = GetPVarInt(playerid, "Phone:Select");
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно установили новую мелодию на вызов.");
			PhonePlayMusic(playerid, 0);
			
			phone_data[phone_index][ph_music] = GetPVarInt(playerid, "Phone:MusicId");
			
			Update:phone_data(playerid, phone_index);
			
			DeletePVar(playerid, "Phone:MusicId");
		}
		
		/*
		
			@brief 911 System
		
		*/
		
		case D_PHONE + 16:
		{
			if (!response)
			{
				return 1;
			}
			
			if (isnull(inputtext) || strlen(inputtext) > MAX_FRACTION_CALL_TEXT)
			{
				ShowPlayerDialog(playerid, D_PHONE + 16, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Служба 911\n\n\
					Опишите коротко ситуацию:\n\n\
					" #cRED "Вы ввели некорректный текст.",
					"Далее", "Закрыть"
				);
				
				return 1;
			}
			
			new index = GetFreeIndexForFractionCall();
			
			if (index == INVALID_PARAM)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Превышен лимит вызовов на линии.");
				return 1;
			}
			
			Create:fraction_call(index, playerid, inputtext);
			SendFractionCallNotice(playerid, index);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Ваш вызов в экстренную службу зарегистрирован. Пожалуйста, ожидайте.");
		}
		
		case D_PHONE + 17:
		{
			new index = GetPVarInt(playerid, "Phone:Select");
			
			phone_data[index][ph_radio] = response;
			SendClientMessage(playerid, C_WHITE, phone_data[index][ph_radio] ? (#DEFAULT " Вы успешно включили радио.") : (#DEFAULT " Вы успешно выключили радио."));
			
			Update:phone_data(playerid, index);
		}
		
		/*
		
			@brief Anogram
		
		*/
		
		case D_PHONE_APP_ANOGRAM:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_PHONE + 12, DIALOG_STYLE_LIST, "Apps", DIALOG_PHONE_APPS, "Выбрать", "Закрыть");
				return 1;
			}
			
			new phone_index = GetPVarInt(playerid, "Phone:Select");
			
			if (listitem == 0)
			{
				ShowPhoneAnogramDialogs(playerid, phone_index);
			}
			else if (listitem == 1)
			{
				ShowPhoneAnogramSettings(playerid);
			}
		}
		
		case D_PHONE_APP_ANOGRAM + 1:
		{
			new phone_index = GetPVarInt(playerid, "Phone:Select");
			
			if (!response)
			{
				ShowPhoneAnogram(playerid, phone_index);
				return 1;
			}
			
			new to_phone_id = g_dialog_select[playerid][listitem];
			
			SetPVarInt(playerid, "Phone:AnogramToPhoneId", to_phone_id);
			ShowPhoneAnogramMessages(playerid, GetPhoneId(phone_index), to_phone_id);
		}
		
		case D_PHONE_APP_ANOGRAM + 2:
		{
			new phone_index = GetPVarInt(playerid, "Phone:Select");
			
			if (!response)
			{
				ShowPhoneAnogram(playerid, phone_index);
				return 1;
			}
			
			if (isnull(inputtext))
			{
				return 1;
			}
			
			new to_phone_id = GetPVarInt(playerid, "Phone:AnogramToPhoneId");
			
			DeletePVar(playerid, "Phone:AnogramToPhoneId");
			
			Create:anogram_message(
				playerid, 
				GetPhoneId(phone_index), 
				to_phone_id, 
				inputtext
			);
		}
		
		case D_PHONE_APP_ANOGRAM + 3:
		{
			new phone_index = GetPVarInt(playerid, "Phone:Select");
			
			if (!response)
			{
				ShowPhoneAnogram(playerid, phone_index);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowPhoneAnogramChangeLogin(playerid, phone_index);
			}
			else if (listitem == 1)
			{
				ShowPlayerDialog(playerid, D_PHONE_APP_ANOGRAM + 5, DIALOG_STYLE_MSGBOX, " ",
					"" #DEFAULT "Очистка сообщений\n\n\
					Вы действительно желаете очистить сообщения?",
					"Да", "Нет"
				);
			}
		}
		
		case D_PHONE_APP_ANOGRAM + 4:
		{
			new phone_index = GetPVarInt(playerid, "Phone:Select");
			
			if (!response)
			{
				ShowPhoneAnogramSettings(playerid);
				return 1;
			}
			
			new len = strlen(inputtext);
			
			if (isnull(inputtext) || !(4 <= len <= 32))
			{
				ShowPhoneAnogramChangeLogin(playerid, 
					phone_index, 
					"Вы ввели некорректный логин."
				);
				
				return 1;
			}

			Check:anogram_login(playerid, phone_index, inputtext);
		}
		
		case D_PHONE_APP_ANOGRAM + 5:
		{
			new phone_index = GetPVarInt(playerid, "Phone:Select");
			
			if (response)
			{
				Remove:all_anogram_message(phone_index);
				SendClientMessage(playerid, C_WHITE, #SUCCESS " Все сообщения были очищены.");
			}
			
			ShowPhoneAnogramSettings(playerid);
		}
		
		case D_PHONE_APP_ANOGRAM + 6:
		{
			new phone_index = GetPVarInt(playerid, "Phone:Select");
			
			if (!response)
			{
				return 1;
			}
			
			if (!response)
			{
				ShowPlayerDialog(playerid, D_PHONE + 12, DIALOG_STYLE_LIST, "Apps", DIALOG_PHONE_APPS, "Выбрать", "Закрыть");
				return 1;
			}
			
			new len = strlen(inputtext);
			
			if (isnull(inputtext) || !(4 <= len <= 32))
			{
				ShowPhoneAnogram(playerid, 
					phone_index, 
					"Вы ввели некорректный логин."
				);
				
				return 1;
			}
			
			Check:anogram_login(playerid, phone_index, inputtext);
		}
	}
	
	return 1;
}

function OnPhoneDeleteConversations(playerid, index)
{
	UpdatePhone(playerid, PH_PAGE_SMS, index);
	return 1;
}

Check:anogram_login(playerid, phone_index, inputtext[])
{
	format:g_string("\
		SELECT \
			IF(COUNT(ph_id) > 0, 1, 0) AS is_exists \
		FROM " #__PHONES " \
		WHERE ph_anogram_name = '%q' \
		LIMIT 1", 
		inputtext
	);
	
	mysql_tquery(db, g_string, "OnPhoneCheckAnogramLogin", "dds", playerid, phone_index, inputtext);
}

function OnPhoneCheckAnogramLogin(playerid, index, login[])
{
	new is_exists;
	
	cache_get_value_name_int(0, "is_exists", is_exists);
	
	if (is_exists)
	{
		ShowPhoneAnogramChangeLogin(playerid, index, 
			"Данный логин уже занят."
		);
	}
	else
	{	
		if (isnull(phone_data[index][ph_anogram_name]))
		{
			ShowPhoneAnogram(playerid, index);
		}
		else 
		{
			ShowPhoneAnogramSettings(playerid);
		}
		
		clean:<phone_data[index][ph_anogram_name]>;
		strcat(phone_data[index][ph_anogram_name], login, MAX_PHONE_ANOGRAM_NAME);
		
		Update:phone_data(playerid, index);
	
	}
	
	return 1;
}

function OnPhoneContactUpdate(playerid)
{
	SetUserAllowQuery(playerid, true);
	return 1;
}