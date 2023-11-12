/*!
	@brief Диалоги для системы игрока
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

Player_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (!(D_LOGIN <= dialogid <= D_LOGIN + 4) && !IsPlayerLogged(playerid))
	{
		printf("[Player_OnDialogResponse]: Player (ID: %d) not logged and has been kicked.",
			playerid
		);
		
		Kick(playerid);
		return 1;
	}
	
	switch (dialogid)
	{
		/*!
			
			@brief D_LOGIN
		
		*/
		
		case D_LOGIN:
		{
			if (!response)
			{
				Kick(playerid);
				return 1;
			}
			
			if (isnull(inputtext) || !IsValidPassword(inputtext))
			{
				ShowPlayerDialog(playerid, D_LOGIN, DIALOG_STYLE_PASSWORD, " ", DIALOG_LOGIN, "Далее", "Закрыть");
				return 1;
			}
			
			Load:check_player_login(playerid, inputtext);
		}
	
	    case D_LOGIN + 1:
		{
			if (!response)
			{
				Kick(playerid);
				return 1;
			}
			
			if (user_login{playerid})
			{
				Kick(playerid);
				return 1;
			}
			
			new account_id = character_select[playerid][listitem][cs_id],
				status = character_select[playerid][listitem][cs_status],
				bool: is_banned = character_select[playerid][listitem][cs_is_banned];
			
			if (status != STATUS_ACCEPT)
			{
				ShowUserCharacterList(playerid);
				SendClientMessage(playerid, C_WHITE, !#ERROR " Выбранный персонаж должен быть активирован.");
				return 1;
			}
			
			if (is_banned)
			{
				ShowCharacterBanInformation(playerid, listitem);
				return 1;
			}
			
			// Загружаем полностью глобальный аккаунт с настройками
			format:g_big_string("\
				SELECT \
					IFNULL(UNIX_TIMESTAMP(u.u_register_date), 0) AS u_register_time, \
					IFNULL(UNIX_TIMESTAMP(u.u_last_date), 0) AS u_last_time, \
					IFNULL(UNIX_TIMESTAMP(u.u_vip_date), 0) AS u_vip_time, \
					u.*, u_set.* \
				FROM " #__USERS " AS u \
				LEFT JOIN " #__USETTINGS " AS u_set \
				ON \
					u.u_id = u_set.set_user_id \
				WHERE \
					u.u_id = %i AND u.u_online = 0",
				user_data[playerid][u_id]
			);
			
			mysql_tquery(db, g_big_string, "OnUserLoad", "d", playerid);

			// Загружаем персонажа (Настройки, кредит)
			format:g_big_string("\
				SELECT \
					c.*, \
					IFNULL(UNIX_TIMESTAMP(c.c_last_date), 0) AS c_last_time, \
					IFNULL(UNIX_TIMESTAMP(c.c_register_date), 0) AS c_register_time, \
					IFNULL(UNIX_TIMESTAMP(c.c_desc_created_date), 0) AS c_desc_created_time, \
					IFNULL(UNIX_TIMESTAMP(c.c_fuber_reputation_date), 0) AS c_fuber_reputation_time, \
					IFNULL(UNIX_TIMESTAMP(c.c_start_pack_buy_date), 0) AS c_start_pack_buy_time, \
					IFNULL(UNIX_TIMESTAMP(c.c_capital_end_date), 0) AS c_capital_end_time, \
					IFNULL(UNIX_TIMESTAMP(c.c_arrest_date), 0) AS c_arrest_time, \
					c_set.*, \
					credit.*, IFNULL(credit.credit_character_id, 0) AS is_exists_credit, \
					license.*, \
					license.l_type - 1 AS l_type_int, \
					IFNULL(UNIX_TIMESTAMP(license.l_gave_date), 0) AS l_gave_time, \
					IFNULL(UNIX_TIMESTAMP(license.l_take_date), 0) AS l_take_time, lodger.* \
				FROM " #__CHARACTERS " AS c \
				JOIN " #__CSETTINGS " AS c_set \
				ON \
					c.c_id = c_set.set_character_id \
				LEFT JOIN " #__CREDITS " AS credit \
				ON \
					c.c_id = credit.credit_character_id \
				LEFT JOIN " #__LICENSES " AS license \
				ON \
					c.c_id = license.l_character_id \
				LEFT JOIN " #__HLODGER " AS lodger \
				ON \
					c.c_id = lodger.lod_character_id \
				WHERE \
					c.c_id = %i AND c.c_online = 0", 
				account_id
			);
			
			mysql_tquery(db, g_big_string, "OnCharacterLoad", "d", playerid);
		}
	
		case D_LOGIN + 2:
		{
			ShowUserCharacterList(playerid);
		}
		
		case D_LOGIN + 3:
		{
			if (!response)
			{
				Kick(playerid);
				return 1;
			}
			
			new code = GoogleAuthenticatorCode(
				GetUserSettings(playerid, SET_GOOGLE_AUTH), 
				gettime()
			);
			
			if (isnull(inputtext) || strval(inputtext) != code)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Неверно введён сгенерированный код из приложения.");
				Kick(playerid);
				return 1;
			}
			
			ShowUserCharacterList(playerid);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно прошли двухфакторную аутентификацию.");
		}
		
		case D_LOGIN + 4:
		{
			if (!response)
			{
				Kick(playerid);
				return 1;
			}
			
			ShowUserCharacterList(playerid);
		}
		
		/*!
			
			@brief D_SETTINGS
		
		*/
		
		case D_SETTINGS:
		{
			if (!response)
			{
				Dialog_Show(playerid, Dialog:PLAYER_MENU_SETTINGS);
				return 1;
			}
			
			switch(listitem) // Инвентарь
			{
				case 0:
				{
					SetUserSettings(playerid, SET_INVENTORY, !GetUserSettings(playerid, SET_INVENTORY));
				}
				
				case 1: // Прорисовка объектов
				{
					ShowPlayerDialog(playerid, D_SETTINGS + 1, DIALOG_STYLE_LIST, " ", 
						"" #cGRAY "Выберите прорисовку:" #cWHITE "\n \
							Высокая\n \
							Средняя\n \
							Низкая\n",
						"Выбрать", "Назад"
					);
					
					return 1;
				}
				
				case 2: // Отображение пикапов
				{
					SetUserSettings(playerid, SET_VISIBLE_PICKUP, !GetUserSettings(playerid, SET_VISIBLE_PICKUP));
				}
				
				case 3: // Действия администрации
				{
					SetUserSettings(playerid, SET_ADMIN_MESSAGE, !GetUserSettings(playerid, SET_ADMIN_MESSAGE));
				}
				
				case 4: // pm
				{
					SetUserSettings(playerid, SET_PM_MESSAGE, !GetUserSettings(playerid, SET_PM_MESSAGE));
				}
				
				case 5: // b
				{
					SetUserSettings(playerid, SET_B_MESSAGE, !GetUserSettings(playerid, SET_B_MESSAGE));
				}
				
				case 6: // логотип
				{
					SetUserSettings(playerid, SET_LOGO, !GetUserSettings(playerid, SET_LOGO));
				}
				
				case 7: // отображение ник-неймов
				{
					SetUserSettings(playerid, SET_VISIBLE_NAMES, !GetUserSettings(playerid, SET_VISIBLE_NAMES));
				}
				
				case 8: // приоритет оформления
				{
					SetUserSettings(playerid, SET_DESIGN, !GetUserSettings(playerid, SET_DESIGN));
				}
				
				case 9: // Безопасность
				{
					ShowUserSecurity(playerid);
					return 1;
				}
			}
			
			ShowUserSettings(playerid);
			ApplyUserSettings(playerid);
			Update:user_settings(playerid);
		}
		
		case D_SETTINGS + 1:
		{
			if (!response)
			{
				ShowUserSettings(playerid);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowPlayerDialog(playerid, D_SETTINGS + 1, DIALOG_STYLE_LIST, " ", 
					"" #cGRAY "Выберите прорисовку:" #cWHITE "\n \
						Высокая\n \
						Средняя\n \
						Низкая\n",
					"Выбрать", "Назад"
				);
				return 1;
			}
			
			if (listitem == 1)
			{
				user_data[playerid][u_settings][SET_VISIBLE_OBJECT] = MAX_VISIBLE_OBJECTS;
			}
			else if (listitem == 2)
			{
				user_data[playerid][u_settings][SET_VISIBLE_OBJECT] = 450;
			}
			else if (listitem == 3)
			{
				user_data[playerid][u_settings][SET_VISIBLE_OBJECT] = 300;
			}
			
			ShowUserSettings(playerid);
			ApplyUserSettings(playerid);
			Update:user_settings(playerid);
		}
		
		case D_SETTINGS + 2:
		{
			if (!response)
			{
				Dialog_Show(playerid, Dialog:PLAYER_MENU_SETTINGS);
				return 1;
			}
			
			if (listitem == 0) // Место появления
			{
				ShowPlayerSettingsSpawn(playerid);
			}
			else if (listitem == 1) // Тип походки
			{
				ShowPlayerSettingsWalk(playerid);
			}
			else if (listitem == 2) // Тип разговора
			{
				ShowPlayerSettingsTalk(playerid);
			}
			else if (listitem == 3) // Тип приветствия
			{
				ShowPlayerSettingsGreetings(playerid);
			}
			else if (listitem == 4) // Стиль боя
			{
				if (!IsUserVip(playerid))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Смена стиля боя доступна только для VIP аккаунтов.");
					return 1;
				}
			
				ShowPlayerSettingsFightingStyle(playerid);
			}
		}
		 
		case D_SETTINGS + 3: // Безопасность
		{
			if (!response)
			{
				ShowUserSettings(playerid);
				return 1;
			}
			
			if (listitem == 0)
			{
				if (isnull(user_data[playerid][u_settings][SET_GOOGLE_AUTH]))
				{
					ShowUserConnectGoogleAuth(playerid);
				}
				else 
				{
					ShowUserDisableGoogleAuth(playerid);
				}
			}
		}
		
		case D_SETTINGS + 4:
		{
			if (!response)
			{
				ShowAccountSettings(playerid);
				return 1;
			}
			

			if (listitem == 0) // Улица
			{
				ShowPlayerSettingsSpawnStreet(playerid);
			}
			else if (listitem == 1) // Жилищное помещение
			{
				new hindex = GetPlayerHouse(playerid);
				
				if (hindex == INVALID_PARAM)
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_HOUSE);
					ShowAccountSettings(playerid);
					return 1;
				}
			}
			else if (listitem == 2) // Помещение
			{
				new pindex = GetPlayerPremise(playerid);
				
				if (pindex == INVALID_PARAM)
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_PREMISE);
					ShowAccountSettings(playerid);
					return 1;
				}
			}
			else if (listitem == 3) // Организация
			{
				if (!IsFractionMember(playerid))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FRACTION);
					ShowAccountSettings(playerid);
					return 1;
				}
			}
			
			SetCharacterSettings(playerid, SET_SPAWN, listitem);
			ShowAccountSettings(playerid);
			Update:character_settings(playerid);
		}
		
		case D_SETTINGS + 5: 
		{
			if (!response)
			{
				Dialog_Show(playerid, Dialog:PLAYER_MENU_SETTINGS);
				return 1;
			}
			
			SetCharacterSettings(playerid, SET_SPAWN, 0);
			SetCharacterSettings(playerid, SET_SPAWN_STREET, listitem);
			ShowAccountSettings(playerid);
			Update:character_settings(playerid);
		}
		
		case D_SETTINGS + 6:
		{
			if (!response || !(0 <= listitem < sizeof character_walk_anim))
			{
				ShowAccountSettings(playerid);
				return 1;
			}
			
			SetCharacterSettings(playerid, SET_WALK, listitem);
			ShowAccountSettings(playerid);
			Update:character_settings(playerid);
		}
		
		case D_SETTINGS + 7:
		{
			if (!response || !(0 <= listitem < sizeof character_talk_anim))
			{
				ShowAccountSettings(playerid);
				return 1;
			}
			
			SetCharacterSettings(playerid, SET_TALK, listitem);
			ShowAccountSettings(playerid);
			Update:character_settings(playerid);
		}
		
		case D_SETTINGS + 8: // Анимация приветствия
		{
			if (!response || !(0 <= listitem < sizeof character_greetings_anim))
			{
				ShowAccountSettings(playerid);
				return 1;
			}
			
			SetCharacterSettings(playerid, SET_GREETINGS, listitem);
			ShowAccountSettings(playerid);
			Update:character_settings(playerid);
		}
		
		case D_SETTINGS + 9: // Безопасность: Двухфакторная аутентификация - подключение
		{
			if (!response)
			{
				ShowUserSecurity(playerid);
				return 1;
			}
			
			new google_auth 	[MAX_GOOGLE_AUTH],
				code;
			
			GetPVarString(playerid, "Player:GoogleAuth", google_auth, sizeof google_auth);
			code = GoogleAuthenticatorCode(google_auth, gettime());
			
			if (isnull(inputtext) || strval(inputtext) != code)
			{
				ShowUserConnectGoogleAuth(playerid, 
					"Неверно введён код из приложения."
				);
				
				return 1;
			}
			
			DeletePVar(playerid, "Player:GoogleAuth");
			ClearUserSettings(playerid, SET_GOOGLE_AUTH);
			
			strcat(
				GetUserSettings(playerid, SET_GOOGLE_AUTH),
				google_auth,
				MAX_GOOGLE_AUTH
			);
			
			ShowUserSecurity(playerid);
			Update:user_settings(playerid);
		}
		
		case D_SETTINGS + 10: // Безопаснось: Двухфакторная аутентификация - отключения
		{
			if (!response)
			{
				ShowUserSecurity(playerid);
				return 1;
			}
			
			new code = GoogleAuthenticatorCode(
				GetUserSettings(playerid, SET_GOOGLE_AUTH), 
				gettime()
			);
			
			if (isnull(inputtext) || strval(inputtext) != code)
			{
				ShowUserConnectGoogleAuth(playerid, 
					"Неверно введён код из приложения."
				);
				
				return 1;
			}
			
			ClearUserSettings(playerid, SET_GOOGLE_AUTH);
			ShowUserSecurity(playerid);
			Update:user_settings(playerid);
		}
		
		case D_SETTINGS + 11: // Смена стиля боя
		{
			if (!response)
			{
				ShowAccountSettings(playerid);
				return 1;
			}
			
			if (!IsUserVip(playerid))
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
				return 1;
			}
			
			SetCharacterSettings(playerid, SET_STYLE, listitem);
			SetPlayerFightingStyle(playerid, 
				GetCharacterFightStyle(playerid)
			);
			
			ShowAccountSettings(playerid);
			Update:character_settings(playerid);
		}
		
		/*
		
			@brief Описание (/action)
			
		*/
		
		case D_ACTION:
		{
			if (!response)
			{
				return 1;
			}
			
			if ((listitem--) == 0)
			{
				new count = 0;
				
				for (new i; i < MAX_ACTIONS; i++)
				{
					if (IsValidAction(playerid, i))
					{
						count++;
					}
				}
				
				if (count >= MAX_ACTIONS)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Вы уже создали максимальное количество описаний.");
					cmd_action(playerid);
					return 1;
				}
				
				ShowPlayerDialog(playerid, D_ACTION + 1, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Добавить описание\n\n\
					Введите текст:",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			new index = g_dialog_select[playerid][listitem];
			
			SetPVarInt(playerid, "Player:SelectAction", index);
			
			ShowPlayerDialog(playerid, D_ACTION + 2, DIALOG_STYLE_MSGBOX, " ",
				"" #DEFAULT " Удаление описания\n\n\
				Вы действительно желаете удалить описание?",
				"Да", "Нет"
			);
		}
		
		case D_ACTION + 1:
		{
			if (response)
			{
				if (isnull(inputtext))
				{
					ShowPlayerDialog(playerid, D_ACTION + 1, DIALOG_STYLE_INPUT, " ", 
						"" #DEFAULT " Добавить описание\n\n\
						Введите текст:\n\n\
						" #cRED "Вы не ввели текст.",
						"Далее", "Назад"
					);
					
					return 1;
				}
				
				new Float: x,
					Float: y,
					Float: z;
				
				GetPlayerPos(playerid, x, y, z);
				
				format:g_string("%s\n(( %s[%i] ))",
					inputtext,
					GetPlayerCurrentName(playerid),
					playerid
				);
				
				new text [MAX_ACTION_TEXT];
				
				strcat(text, inputtext, MAX_ACTION_TEXT);
				
				Create:action(
					playerid, 
					text,
					CreateDynamic3DTextLabel(
						g_string,
						C_PURPLE,
						x,
						y,
						z,
						10.0,
						_,
						_,
						_,
						GetCharacterInt(playerid),
						GetPlayerVirtualWorld(playerid)
					)
				);
				
				format:g_small_string(ADMIN_MESSAGE " %s[%d] установил описание (/action): %s",
					GetPlayerCurrentName(playerid),
					playerid,
					inputtext
				);

				SendAdminMessage(C_GOLD, g_small_string);
			}
			
			cmd_action(playerid);
		}
		
		case D_ACTION + 2:
		{
			if (response)
			{
				new index = GetPVarInt(playerid, "Player:SelectAction");
				
				if (IsValidDynamic3DTextLabel(character_action[playerid][index][c_text_id]))
				{
					DestroyDynamic3DTextLabel(
						character_action[playerid][index][c_text_id]
					);
				}
				
				Clear:character_action(playerid, index);
			}
			
			DeletePVar(playerid, "Player:SelectAction");
			cmd_action(playerid);
		}
		
		case D_FRISK:
		{
			new targetid = GetPVarInt(playerid, "Player:FriskTargetId");
			
			if (response)
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " принял Ваше предложение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(targetid, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы приняли предложение.");
				ShowInventoryItems(playerid, targetid);
			}
			else 
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " отклонил Ваше предложение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(targetid, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы отклонили предложение.");
			}
			
			DeletePVar(targetid, "Player:FriskTargetId");
		}
	}	
	
	return 1;
}