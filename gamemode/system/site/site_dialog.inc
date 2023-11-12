/*!
	@brief Диалоги для системы сайтов
	@author Found (evg.savosin)
	@date 16.12.2016, update 14.02.2018
*/

function Site_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case D_SITE :
		{
			if (!response)
			{
				ShowBrowserCursor(playerid, true, false);
				return 1;
			}
			
			/// Если вдруг не открыт браузер вовсе
			if (!IsSiteShowed(playerid))
			{
				return 1;
			}
			
			if (isnull(inputtext))
			{
				ShowPlayerDialog(playerid, D_SITE, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Адресная строка\n\n\
					Введите ссылку в адресную строку для перехода на сайт:\n\n\
					" #cGRAY "Адрес должен быть в формате: www.example.com\n\
					" #cRED "Введите адрес сайта.",
					"Перейти", "Закрыть"
				);
				
				return 1;
			}
			
			if (!SiteGoToPage(playerid, inputtext))
			{
				ShowPlayerDialog(playerid, D_SITE, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Адресная строка\n\n\
					Введите ссылку в адресную строку для перехода на сайт:\n\n\
					" #cGRAY "Адрес должен быть в формате: www.example.com\n\
					" #cRED "Не удается получить доступ к сайту, Вы ввели неверный адрес.",
					"Перейти", "Закрыть"
				);
				
				return 1;
			}
		}
		
		case D_SITE + 1 :
		{
			if (!response)
			{
				ShowBrowserCursor(playerid, true, false);
				return 1;
			}
			
			if (listitem == 0)
			{
				if (GetPVarInt(playerid, "Site:CountFavorites") >= MAX_SITE_FAVORITES)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете добавить больше 20 сайтов в закладки.");
					if (!ShowSiteFavorites(playerid))
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
					}
				}
				else 
				{
					ShowPlayerDialog(playerid, D_SITE + 4, DIALOG_STYLE_INPUT, " ", 
						"" #DEFAULT " Добавить сайт в закладки\n\n\
						Введите адрес сайта, который Вы хотите добавить в закладки:\n\n\
						" #cGRAY "Адрес должен быть в формате: www.example.com",
						"Далее", "Назад" 
					);
				}
				
				return 1;
			}
			
			listitem--;
			SetPVarInt(playerid, "Site:FavSelect", listitem);
			
			ShowSiteFavoriteSelected(playerid, listitem);
		}
		
		case D_SITE + 2 :
		{
			if (!response)
			{
				if (!ShowSiteFavorites(playerid))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
				}
				
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Site:FavSelect");
			
			if ((0 <= listitem <= 2))
			{
				if (!SiteGoToPage(playerid, site_fav_select[playerid][index][sf_address]))
				{
					ShowSiteFavoriteSelected(playerid, index);
					
					return 1;
				}
			}
			
			else if (listitem == 3)
			{
				format:g_string("DELETE FROM " #__SFAVORITE " WHERE sf_id = %i",
					site_fav_select[playerid][index][sf_id]
				);
				
				mysql_tquery(db, g_string);
				
				pformat:("" #SUCCESS " Вы успешно удалили веб-сайт " #cPROJECT "%s (www.%s)" #cWHITE " из закладок.",
					site_fav_select[playerid][index][sf_name],
					site_fav_select[playerid][index][sf_address]
				);
				
				psend:(playerid, C_WHITE);
				
				if (!ShowSiteFavorites(playerid))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
				}
			}
			
			Clear:site_fav_select(playerid);
		}
		
		case D_SITE + 3 :
		{
			if (!ShowSiteFavorites(playerid))
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
			}
		}
		
		case D_SITE + 4 :
		{
			if (!response)
			{
				if (!ShowSiteFavorites(playerid))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
				}
				
				return 1;
			}

			if (isnull(inputtext))
			{
				ShowPlayerDialog(playerid, D_SITE + 4, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Добавить сайт в закладки\n\n\
					Введите адрес сайта, который Вы хотите добавить в закладки:\n\n\
					" #cGRAY "Адрес должен быть в формате: www.example.com\n\
					" #cRED "Введите адрес сайта.",
					"Далее", "Назад" 
				);
				
				return 1;
			}
			
			if (!SiteGoToPage(playerid, inputtext))
			{
				ShowPlayerDialog(playerid, D_SITE + 4, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Добавить сайт в закладки\n\n\
					Введите адрес сайта, который Вы хотите добавить в закладки:\n\n\
					" #cGRAY "Адрес должен быть в формате: www.example.com\n\
					" #cRED "Не удается получить доступ к сайту, Вы ввели неверный адрес.",
					"Далее", "Назад" 
				);
				
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Site:Select");
			
			pformat:("" #SUCCESS " Вы успешно добавили веб-сайт " #cPROJECT "%s (www.%s)" #cWHITE " в закладки.",
				site_data[index][s_name],
				site_data[index][s_address]
			);
			
			psend:(playerid, C_WHITE);
			
			format:g_string("INSERT INTO " #__SFAVORITE " (sf_character_id, sf_address, sf_name, sf_created_time) \
			VALUES (%i, '%q', '%q', %i)", 
				GetCharacterId(playerid),
				site_data[index][s_address],
				site_data[index][s_name],
				gettime()
			);
			
			mysql_tquery(db, g_string);
		}
		
		case D_SITE + 5 :
		{
			if (!response)
			{
				ShowBrowserCursor(playerid, true, false);
				return 1;
			}
			
			if (listitem == 0) /// Create site
			{
				if (!GetPlayerAvaibleSites(playerid))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете больше создать сайтов.");
					ShowBrowserCursor(playerid, true, false);
					return 1;
				}
				
				if (GetFreeIndexForSite() == INVALID_PARAM)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Превышен лимит на сайты, Вы не можете создать сайт.");
					ShowBrowserCursor(playerid, true, false);
					return 1;
				}
				
				Clear:site_edit_pvar(playerid);
				
				SetPVarInt(playerid, "Site:EditAction", SITE_ACTION_CREATE);

				ShowSiteDialogAddressEdit(playerid);
				return 1;
			}
			
			listitem--;
			
			SetPVarInt(playerid, "Site:EditSelect", g_dialog_select[playerid][listitem]);
			ShowPlayerDialog(playerid, D_SITE + 19, DIALOG_STYLE_LIST, " ", DIALOG_SITE_MANAGE, "Выбрать", "Назад");
		}
		
		case D_SITE + 6 :
		{
			if (!response)
			{
				ShowSiteList(playerid, D_SITE + 5);
				return 1;
			}
			
			new name				[		32				],
				domain				[		7				];
			
			if (isnull(inputtext) 
			|| !IsValidSiteString(inputtext, MIN_SITE_ADDRESS, MAX_SITE_ADDRESS) 
			|| sscanf(inputtext, "p<.>s[32]s[7]", name, domain)
			|| !IsValidSiteString(name, MIN_SITE_ADDRESS, MAX_SITE_ADDRESS) 
			|| !IsValidDomain(domain) 
			|| GetSiteIndexByDomain(inputtext) != INVALID_PARAM)
			{
				ShowSiteDialogAddressEdit(playerid, true);
				return 1;
			}
			
			if (!strcmp("onion", domain, true))
			{
				SetPVarInt(playerid, "Site:EditDarknet", true);
			}
			
			strtolower(inputtext);
			
			SetPVarString(playerid, "Site:EditDomain", inputtext);
			ShowSiteDialogMenuEdit(playerid);
		}
		
		case D_SITE + 7 :
		{
			new action = GetPVarInt(playerid, "Site:EditAction");
			
			if (action == SITE_ACTION_NONE)
			{
				return 1;
			}
			
			if (!response)
			{
				if (action == SITE_ACTION_CREATE)
				{
					ShowSiteDialogAddressEdit(playerid);
				}
				else
				{
					ShowSiteList(playerid, D_SITE + 5);
				}
				
				return 1;
			}
			
			switch (listitem)
			{
				case 0 : // Template
				{
					ShowSiteDialogTemplates(playerid);
				}
				
				case 1 : // Color
				{
					ShowSiteDialogColors(playerid);
				}
				
				case 2 : // Name
				{
					ShowPlayerDialog(playerid, D_SITE + 10, DIALOG_STYLE_INPUT, " ",
						"" #DEFAULT " Название\n\n\
						Название сайта будет отображаться на главной странице.\n\
						Введите текст:\n\n\
						" #cGRAY "Текст должен содержать только латинские буквы и цифры.\n\
						Длина текста не должна быть меньше 3 символов и больше, чем 32 символа.",
						"Далее", "Назад"
					);
				}
				
				case 3 : // Slogan
				{
					ShowPlayerDialog(playerid, D_SITE + 11, DIALOG_STYLE_INPUT, " ",
						"" #DEFAULT " Слоган\n\n\
						Слоган будет отображаться под названием сайта.\n\
						Введите текст:\n\n\
						" #cGRAY "Это необязательное поле, Вы можете не указывать его, нажав \"Далее\".\n\
						Текст должен содержать только латинские буквы и цифры.",
						"Далее", "Назад"
					);
				}
				
				case 4 : // Description
				{
					ShowSiteDialogDescription(playerid);
				}
				
				case 5 : // Page Settings
				{
					ShowSiteDialogPages(playerid);
				}
				
				case 6 : // Action
				{
					if (action == SITE_ACTION_CREATE) /// Insert
					{
						ShowPlayerDialog(playerid, D_SITE + 18, DIALOG_STYLE_MSGBOX, " ", 
							"" #DEFAULT " Создать сайт\n\n\
							Вы действительно желаете создать сайт?\n\
							" #cWHITE "Вы оплачиваете услуги за создание сайта и за недельную аренду.\n\
							Итоговая стоимость создания сайта " #cGREEN "$345" #cWHITE ".",
							"Создать", "Назад"
						);
					}
					else /// Update
					{
						new index = GetPVarInt(playerid, "Site:EditSelect");
						
						Update:site_data(playerid, index);
						
						pformat:("" #SUCCESS " Вы успешно обновили сайт " #cPROJECT "%s(%s)" #cWHITE ".",
							site_data[index][s_name],
							site_data[index][s_address]
						);
						
						psend:(playerid, C_WHITE);
						
						ShowSiteList(playerid, D_SITE + 5);
					}
				}
			}
		}
		
		case D_SITE + 8 :
		{
			if (GetPVarInt(playerid, "Site:EditAction") == SITE_ACTION_NONE)
			{
				return 1;
			}
			
			if (response)
			{
				if ((site_templates[listitem][st_darknet] && !GetPVarInt(playerid, "Site:EditDarknet")) 
				|| (!site_templates[listitem][st_darknet] && GetPVarInt(playerid, "Site:EditDarknet")))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Данный шаблон предназначен для других сайтов.");
					ShowSiteDialogTemplates(playerid);
					return 1;
				}
				
				SetPVarInt(playerid, "Site:EditTemplate", listitem + 1);
			}
			
			ShowSiteDialogMenuEdit(playerid);
		}
		
		case D_SITE + 9 :
		{
			if (GetPVarInt(playerid, "Site:EditAction") == SITE_ACTION_NONE)
			{
				return 1;
			}
			
			if (response)
			{
				SetPVarInt(playerid, "Site:EditColor", listitem);
			}
			
			ShowSiteDialogMenuEdit(playerid);
		}
		
		case D_SITE + 10 :
		{
			if (GetPVarInt(playerid, "Site:EditAction") == SITE_ACTION_NONE)
			{
				return 1;
			}
			
			if (response)
			{
				if (isnull(inputtext) || !IsValidSiteString(inputtext, 3, 32))
				{
					ShowPlayerDialog(playerid, D_SITE + 10, DIALOG_STYLE_INPUT, " ",
						"" #DEFAULT " Название\n\n\
						Название сайта будет отображаться на главной странице.\n\
						Введите текст:\n\n\
						" #cRED "Текст должен содержать только латинские буквы и цифры.\n\
						Длина текста не должна быть меньше 3 символов и больше, чем 32 символа.",
						"Далее", "Назад"
					);
					
					return 1;
				}
				
				SetPVarString(playerid, "Site:EditName", inputtext);
			}
			
			ShowSiteDialogMenuEdit(playerid);
		}
		
		case D_SITE + 11 :
		{
			if (GetPVarInt(playerid, "Site:EditAction") == SITE_ACTION_NONE)
			{
				return 1;
			}
			
			if (response)
			{
				if (!IsValidSiteString(inputtext, 0, 32))
				{
					ShowPlayerDialog(playerid, D_SITE + 11, DIALOG_STYLE_INPUT, " ",
						"" #DEFAULT " Слоган\n\n\
						Слоган будет отображаться под названием сайта.\n\
						Введите текст:\n\n\
						" #cGRAY "Это необязательное поле, Вы можете не указывать его, нажав \"Далее\".\n\
						" #cRED "Текст должен содержать только латинские буквы и цифры.",
						"Далее", "Назад"
					);
					
					return 1;
				}
				
				SetPVarString(playerid, "Site:EditSlogan", inputtext);
			}
			
			ShowSiteDialogMenuEdit(playerid);
		}
		
		case D_SITE + 12 :
		{
			if (GetPVarInt(playerid, "Site:EditAction") == SITE_ACTION_NONE)
			{
				return 1;
			}
			
			if (response)
			{
				if (isnull(inputtext) 
				|| !IsValidSiteString(inputtext, 10, 128))
				{
					ShowSiteDialogDescription(playerid, true);
					
					return 1;
				}
				
				SetPVarString(playerid, "Site:EditDescription", inputtext);
			}
			
			ShowSiteDialogMenuEdit(playerid);
		}
		
		case D_SITE + 13 :
		{
			if (GetPVarInt(playerid, "Site:EditAction") == SITE_ACTION_NONE)
			{
				return 1;
			}
			
			if (!response)
			{
				ShowSiteDialogMenuEdit(playerid);
				return 1;
			}
			
			ShowSiteDialogPages(playerid);
		}
		
		case D_SITE + 14 :
		{
			if (GetPVarInt(playerid, "Site:EditAction") == SITE_ACTION_NONE)
			{
				return 1;
			}
			
			if (!response)
			{
				ShowSiteDialogMenuEdit(playerid);
				return 1;
			}
			
			SetPVarInt(playerid, "Site:EditPageSelect", listitem);
			ShowPlayerDialog(playerid, D_SITE + 15, DIALOG_STYLE_LIST, " ",
				" Редактировать название\n \
				  Редактировать контент",
				"Далее", "Назад" 
			);
		}
		
		case D_SITE + 15 :
		{
			if (GetPVarInt(playerid, "Site:EditAction") == SITE_ACTION_NONE)
			{
				return 1;
			}
			
			if (!response)
			{
				ShowSiteDialogPages(playerid);
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Site:EditPageSelect");
			
			if (listitem == 0) // Edit name
			{
				ShowSiteDialogPageName(playerid, index);
			}
			else // Edit content
			{
				ShowSiteDialogPageDesc(playerid, index);
			}
		}
		
		case D_SITE + 16 :
		{
			if (GetPVarInt(playerid, "Site:EditAction") == SITE_ACTION_NONE)
			{
				return 1;
			}
			
			if (response)
			{
				new index = GetPVarInt(playerid, "Site:EditPageSelect");
				
				if (!IsValidSiteString(inputtext, 0, 16))
				{
					ShowSiteDialogPageName(playerid, index, true);
					
					return 1;
				}
				
				format:g_small_string("Site:EditPageName[%i]", index);
				SetPVarString(playerid, g_small_string, inputtext);
			}
			
			ShowPlayerDialog(playerid, D_SITE + 15, DIALOG_STYLE_LIST, " ",
				" Редактировать название\n \
				  Редактировать контент",
				"Далее", "Назад" 
			);
		}
		
		case D_SITE + 17 :
		{
			if (GetPVarInt(playerid, "Site:EditAction") == SITE_ACTION_NONE)
			{
				return 1;
			}
			
			clean:<g_string>;
			clean:<g_small_string>;
			
			new index = GetPVarInt(playerid, "Site:EditPageSelect");
			
			if (response) // Input
			{
				if (isnull(inputtext)) // Saved
				{
					ShowPlayerDialog(playerid, D_SITE + 15, DIALOG_STYLE_LIST, " ",
						" Редактировать название\n \
						  Редактировать контент",
						"Далее", "Назад" 
					);
					
					return 1;
				}
				
				format:g_small_string("Site:EditPageDesc[%i]", index);
				GetPVarString(playerid, g_small_string, g_string, sizeof g_string);
				if (strlen(g_string) > MAX_SITE_PAGE_DESC)
				{
					ShowSiteDialogPageDesc(playerid, index, true);
					return 1;
				}
				
				format:g_string("%s\n%s", g_string, inputtext);
				format:g_small_string("Site:EditPageDesc[%i]", index);
				SetPVarString(playerid, g_small_string, g_string);
				ShowSiteDialogPageDesc(playerid, index);
			}
			else // Clear
			{
				format:g_small_string("Site:EditPageDesc[%i]", index);
				GetPVarString(playerid, g_small_string, g_string, sizeof g_string);
				if (!isnull(g_string))
				{
					for (new i = strlen(g_string) - 1; i >= 0; i--)
					{
						if (g_string[i] == '\n')
						{
							g_string[i] = EOS;
							
							format:g_small_string("Site:EditPageDesc[%i]", index);
							SetPVarString(playerid, g_small_string, g_string);
							break;
						}
					}
					
					ShowSiteDialogPageDesc(playerid, index);
				}
				else 
				{
					ShowPlayerDialog(playerid, D_SITE + 15, DIALOG_STYLE_LIST, " ",
						" Редактировать название\n \
						  Редактировать контент",
						"Далее", "Назад" 
					);
				}	
			}
		}
		
		case D_SITE + 18 :
		{
			if (!response)
			{
				ShowSiteDialogMenuEdit(playerid);
				return 1;
			}
			
			new index = GetFreeIndexForSite();
						
			if (index == INVALID_PARAM)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Превышен лимит сайтов, Вы не можете создать сайт.");
				return 1;
			}
			
			ShowBrowserCursor(playerid, true, false);
			
			Create:site_data(playerid, index);
		}
		
		case D_SITE + 19 :
		{
			if (!response)
			{
				ShowSiteList(playerid, D_SITE + 5);
				DeletePVar(playerid, "Site:EditSelect");
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Site:EditSelect");
			
			if (listitem == 0) // Информация
			{
				ShowSiteInformation(playerid, D_SITE + 20, index);
			}
			else if (listitem == 1) // Управление
			{
				Clear:site_edit_pvar(playerid);
				
				SetPVarInt(playerid, "Site:EditAction", SITE_ACTION_EDIT);
				
				PutSiteDataPVar(playerid, index);
				ShowSiteDialogMenuEdit(playerid);
			}
			else if (listitem == 2) // Оплата сайта
			{
				new day,
					month,
					year,
					hour,
					minute;
			
				gmtime(site_data[index][s_rent_time], year, month, day, hour, minute);
				
				if (site_data[index][s_rent_time] >= gettime() + (60 * 60 * 24 * 7 * 2))
				{
					pformat:("" #ERROR " Вы не можете совершить оплату, у Вас уже оплачено до: " #cPROJECT "" #DATE_FORMAT "" #cWHITE ".", 
						hour,
						minute,
						day,
						month,
						year
					);
					
					psend:(playerid, C_WHITE);
				}
				else 
				{
					if (!GiveDebitCardMoney(playerid, -80))
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
					}
					else
					{
						site_data[index][s_rent_time] = gettime() + (60 * 60 * 24 * 30);
						
						gmtime(site_data[index][s_rent_time], year, month, day, hour, minute);
						
						pformat:("" #SUCCESS " Вы успешно продлили услуги хостинга до: " #cPROJECT "" #DATE_FORMAT "" #cWHITE ".", 
							hour,
							minute,
							day,
							month,
							year
						);
						
						psend:(playerid, C_WHITE);
						
						Update:site_data(playerid, index);
					}
				}
				
				ShowPlayerDialog(playerid, D_SITE + 19, DIALOG_STYLE_LIST, " ", DIALOG_SITE_MANAGE, "Выбрать", "Назад");
			}
			else if (listitem == 3) // Перейти на сайт
			{
				SiteGoToPage(playerid, site_data[index][s_address]);
			}
			else if (listitem == 4) // Удалить 
			{
				ShowPlayerDialog(playerid, D_SITE + 21, DIALOG_STYLE_MSGBOX, " ", 
					"" #DEFAULT " Удалить сайт\n\n\
					Вы действительно желаете удалить сайт?\n\n\
					" #cGRAY "Адрес сайта станет доступен всем, а содержимое сайта удалится.", 
					"Далее", "Отмена" 
				);
			}
		}
		
		case D_SITE + 20 :
		{
			return ShowPlayerDialog(playerid, D_SITE + 19, DIALOG_STYLE_LIST, " ", DIALOG_SITE_MANAGE, "Выбрать", "Назад");
		}
		
		case D_SITE + 21 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_SITE + 19, DIALOG_STYLE_LIST, " ", DIALOG_SITE_MANAGE, "Выбрать", "Назад");
				return 1;
			}
			
			Remove:site_data(playerid, GetPVarInt(playerid, "Site:EditSelect"));
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно удалили сайт.");
			
			ShowSiteList(playerid, D_SITE + 5);
		}
		
		
		// GOG 
		
		case D_SITE + 22 :
		{
			if (!response)
			{
				ShowBrowserCursor(playerid, true, false);
				return 1;
			}
			
			if (listitem == 0) // Houses
			{
				ShowPlayerDialog(playerid, D_SITE + 23, DIALOG_STYLE_LIST, "www.estateagency.com/houses", DIALOG_SITE_HOUSE, "Далее", "Назад");
				SetPVarInt(playerid, "Site:EstateType", TYPE_ESTATE_HOUSE);
			}
			
			else if (listitem == 1) // Premises
			{
				ShowPlayerDialog(playerid, D_SITE + 23, DIALOG_STYLE_LIST, "www.estateagency.com/premises", DIALOG_SITE_PREMISE, "Далее", "Назад");
				SetPVarInt(playerid, "Site:EstateType", TYPE_ESTATE_PREMISE);
			}
		}
		
		case D_SITE + 23 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_SITE + 22, DIALOG_STYLE_LIST, "www.estateagency.com",
					" Каталог жилья\n \
					Каталог коммерческих помещений",
					"Далее", "Закрыть"
				);
				
				DeletePVar(playerid, "Site:EstatePage");
				DeletePVar(playerid, "Site:EstatePrice[0]");
				DeletePVar(playerid, "Site:EstatePrice[1]");
				DeletePVar(playerid, "Site:EstatePriceRent[0]");
				DeletePVar(playerid, "Site:EstatePriceRent[1]");
				DeletePVar(playerid, "Site:EstateZone");
				DeletePVar(playerid, "Site:EstateType");
				DeletePVar(playerid, "Site:EstateIndex");
				return 1;
			}
			
			new type = GetPVarInt(playerid, "Site:EstateType");
			
			SetPVarInt(playerid, "Site:EstateZone", false);
			SetPVarInt(playerid, "Site:EstatePrice[0]", INVALID_PARAM);
			SetPVarInt(playerid, "Site:EstatePrice[1]", INVALID_PARAM);
			SetPVarInt(playerid, "Site:EstatePriceRent[0]", INVALID_PARAM);
			SetPVarInt(playerid, "Site:EstatePriceRent[1]", INVALID_PARAM);
			
			if (listitem == 0) /// Список
			{
				if (!ShowSiteEstateList(playerid, type, D_SITE + 24, 0))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " По вашему запросу ничего не найдено.");
					ShowPlayerDialog(playerid, D_SITE + 23, DIALOG_STYLE_LIST, 
						(type == TYPE_ESTATE_HOUSE ? ("www.estateagency.com/houses") : ("www.estateagency.com/premises")), 
						(type == TYPE_ESTATE_HOUSE ? (DIALOG_SITE_HOUSE) : (DIALOG_SITE_PREMISE)), 
						"Далее", "Назад"
					);
					return 1;
				}
			}
			else if (listitem == 1) /// В этом районе
			{
				SetPVarInt(playerid, "Site:EstateZone", true);
				
				if (!ShowSiteEstateList(playerid, type, D_SITE + 24, 0, true))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " По вашему запросу ничего не найдено.");
					ShowPlayerDialog(playerid, D_SITE + 23, DIALOG_STYLE_LIST, 
						(type == TYPE_ESTATE_HOUSE ? ("www.estateagency.com/houses") : ("www.estateagency.com/premises")), 
						(type == TYPE_ESTATE_HOUSE ? (DIALOG_SITE_HOUSE) : (DIALOG_SITE_PREMISE)), 
						"Далее", "Назад"
					);
					return 1;
				}
			}
			else if (listitem == 2) /// По цене покупки
			{
				ShowPlayerDialog(playerid, D_SITE + 26, DIALOG_STYLE_INPUT, 
					(type == TYPE_ESTATE_HOUSE ? ("www.estateagency.com/houses"): ("www.estateagency.com/premises")),
					"" #DEFAULT " Указать ценовую категорию\n\n\
					Укажите диапазон ценевой категории:\n\n\
					" #cGRAY "Пример: 10000-30000",
					"Далее", "Назад"
				);
			}
			else if (listitem == 3) /// По цене аренды
			{
				ShowPlayerDialog(playerid, D_SITE + 27, DIALOG_STYLE_INPUT, 
					(type == TYPE_ESTATE_HOUSE ? ("www.estateagency.com/houses"): ("www.estateagency.com/premises")),
					"" #DEFAULT " Указать ценовую категорию аренды\n\n\
					Укажите диапазон ценевой категории аренды:\n\n\
					" #cGRAY "Пример: 10000-30000",
					"Далее", "Назад"
				);
			}
			else if (listitem == 4) /// По номеру
			{
				ShowPlayerDialog(playerid, D_SITE + 28, DIALOG_STYLE_INPUT, 
					(type == TYPE_ESTATE_HOUSE ? ("www.estateagency.com/houses"): ("www.estateagency.com/premises")),
					(type == TYPE_ESTATE_HOUSE ? 
					("" #DEFAULT " Указать номер жилья\n\nУкажите номер жилья (ID):") : 
					("" #DEFAULT " Указать номер помещения\n\nУкажите номер помещения (ID):")),
					"Далее", "Назад"
				);
			}
		}
		
		case D_SITE + 24 :
		{
			new type = GetPVarInt(playerid, "Site:EstateType");
			
			if (!response)
			{
				ShowPlayerDialog(playerid, D_SITE + 23, DIALOG_STYLE_LIST, 
					(type == TYPE_ESTATE_HOUSE ? ("www.estateagency.com/houses"): ("www.estateagency.com/premises")),
					(type == TYPE_ESTATE_HOUSE ? (DIALOG_SITE_HOUSE) : (DIALOG_SITE_PREMISE)), 
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			new page = GetPVarInt(playerid, "Site:EstatePage"),
				index = g_dialog_select[playerid][listitem];
				
			if (index == ITEM_LIST_NEXT)
			{
				ShowSiteEstateList(
					playerid, 
					type,
					D_SITE + 24, 
					page + 1, 
					bool: GetPVarInt(playerid, "Site:EstateZone"),
					GetPVarInt(playerid, "Site:EstatePrice[0]"),
					GetPVarInt(playerid, "Site:EstatePrice[1]"),
					GetPVarInt(playerid, "Site:EstatePriceRent[0]"),
					GetPVarInt(playerid, "Site:EstatePriceRent[1]")
				);
				
				return 1;
			}
			else if (index == ITEM_LIST_BACK)
			{
				ShowSiteEstateList(
					playerid, 
					type,
					D_SITE + 24, 
					page - 1, 
					bool: GetPVarInt(playerid, "Site:EstateZone"),
					GetPVarInt(playerid, "Site:EstatePrice[0]"),
					GetPVarInt(playerid, "Site:EstatePrice[1]"),
					GetPVarInt(playerid, "Site:EstatePriceRent[0]"),
					GetPVarInt(playerid, "Site:EstatePriceRent[1]")
				);
				
				return 1;
			}
			
			SetPVarInt(playerid, "Site:EstateIndex", index);
			
			if (type == TYPE_ESTATE_HOUSE)
			{
				ShowHouseInformation(playerid, index, D_SITE + 25, false, "Найти", "Назад");
			}
			else 
			{
				ShowPremiseInformation(playerid, index, D_SITE + 25, false, "Найти", "Назад");
			}
		}
		
		case D_SITE + 25 :
		{
			new type = GetPVarInt(playerid, "Site:EstateType"),
				index = GetPVarInt(playerid, "Site:EstateIndex");
			
			if (response)
			{
				if (type == TYPE_ESTATE_HOUSE)
				{
					SetHouseMark(playerid, index);
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Выбранное жилищное помещение отмечено на карте. " #cGRAY "(/gps - отмена)");
				}
				else 
				{
					SetPremiseMark(playerid, index);
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Выбранное помещение отмечено на карте. " #cGRAY "(/gps - отмена)");
				}
			}
			
			ShowSiteEstateList(
				playerid, 
				type,
				D_SITE + 24, 
				GetPVarInt(playerid, "Site:EstatePage"), 
				bool: GetPVarInt(playerid, "Site:EstateZone"),
				GetPVarInt(playerid, "Site:EstatePrice[0]"),
				GetPVarInt(playerid, "Site:EstatePrice[1]"),
				GetPVarInt(playerid, "Site:EstatePriceRent[0]"),
				GetPVarInt(playerid, "Site:EstatePriceRent[1]")
			);
		}
		
		case D_SITE + 26 :
		{
			new type = GetPVarInt(playerid, "Site:EstateType");
			
			if (!response)
			{
				ShowPlayerDialog(playerid, D_SITE + 23, DIALOG_STYLE_LIST, 
					(type == TYPE_ESTATE_HOUSE ? ("www.estateagency.com/houses"): ("www.estateagency.com/premises")),
					(type == TYPE_ESTATE_HOUSE ? (DIALOG_SITE_HOUSE) : (DIALOG_SITE_PREMISE)), 
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			new price 	[	2 	];
			
			if (sscanf(inputtext, "p<->a<i>[2]", price)
			|| !ShowSiteEstateList(playerid, type, D_SITE + 24, 0, false, price[0], price[1], _, _))
			{	
				ShowPlayerDialog(playerid, D_SITE + 26, DIALOG_STYLE_INPUT, "www.estateagency.com/houses",
					"" #DEFAULT " Указать ценовую категорию\n\n\
					Укажите диапазон ценевой категории:\n\n\
					" #cRED "Пример: 10000-30000\n\
					По вашему запросу ничего не найдено.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			SetPVarInt(playerid, "Site:EstatePrice[0]", price[0]);
			SetPVarInt(playerid, "Site:EstatePrice[1]", price[1]);
		}
		
		case D_SITE + 27 :
		{
			new type = GetPVarInt(playerid, "Site:EstateType");
			
			if (!response)
			{
				ShowPlayerDialog(playerid, D_SITE + 23, DIALOG_STYLE_LIST, 
					(type == TYPE_ESTATE_HOUSE ? ("www.estateagency.com/houses") : ("www.estateagency.com/premises")), 
					(type == TYPE_ESTATE_HOUSE ? (DIALOG_SITE_HOUSE) : (DIALOG_SITE_PREMISE)), 
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			new price 	[	2 	];
			
			if (isnull(inputtext) || sscanf(inputtext, "p<->a<i>[2]", price)
			|| !ShowSiteEstateList(playerid, type, D_SITE + 24, 0, false, _, _, price[0], price[1]))
			{	
				ShowPlayerDialog(playerid, D_SITE + 27, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Указать ценовую категорию аренды\n\n\
					Укажите диапазон ценевой категории аренды:\n\
					" #cRED "Пример: 10000-30000\n\n\
					По вашему запросу ничего не найдено.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			SetPVarInt(playerid, "Site:EstatePriceRent[0]", price[0]);
			SetPVarInt(playerid, "Site:EstatePriceRent[1]", price[1]);
		}
		
		case D_SITE + 28 :
		{
			new type = GetPVarInt(playerid, "Site:EstateType");
			
			if (!response)
			{
				ShowPlayerDialog(playerid, D_SITE + 23, DIALOG_STYLE_LIST, 
					(type == TYPE_ESTATE_HOUSE ? ("www.estateagency.com/houses"): ("www.estateagency.com/premises")),
					(type == TYPE_ESTATE_HOUSE ? (DIALOG_SITE_HOUSE) : (DIALOG_SITE_PREMISE)), 
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			new index;
			
			if (type == TYPE_ESTATE_HOUSE)
			{
				if ((index = GetHouseIndexById(strval(inputtext))) == INVALID_PARAM)
				{
					ShowPlayerDialog(playerid, D_SITE + 28, DIALOG_STYLE_INPUT, 
						"www.estateagency.com/houses",
						"" #DEFAULT " Указать номер жилья\n\n\
						Укажите номер жилья (ID):\n\n\
						" #cRED "Вы ввели неверный ID жилья.",
						"Далее", "Назад"
					);
					
					return 1;
				}
			}
			else
			{
				if ((index = GetPremiseIndexById(strval(inputtext))) == INVALID_PARAM)
				{
					ShowPlayerDialog(playerid, D_SITE + 28, DIALOG_STYLE_INPUT, 
						"www.estateagency.com/premises",
						"" #DEFAULT " Указать номер помещения\n\n\
						Укажите номер помещения (ID):\n\n\
						" #cRED "Вы ввели неверный ID помещения.",
						"Далее", "Назад"
					);
					
					return 1;
				}
			}

			SetPVarInt(playerid, "Site:EstateIndex", index);
			
			if (type == TYPE_ESTATE_HOUSE)
			{
				ShowHouseInformation(playerid, index, D_SITE + 29, false, "Найти", "Назад");
			}
			else 
			{
				ShowPremiseInformation(playerid, index, D_SITE + 29, false, "Найти", "Назад");
			}
		}
		
		case D_SITE + 29 :
		{
			new type = GetPVarInt(playerid, "Site:EstateType"),
				index = GetPVarInt(playerid, "Site:EstateIndex");
			
			if (response)
			{
				if (type == TYPE_ESTATE_HOUSE)
				{
					SetHouseMark(playerid, index);
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Выбранное жилищное помещение отмечено на карте. " #cGRAY "(/gps - отмена)");
				}
				else 
				{
					SetPremiseMark(playerid, index);
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Выбранное помещение отмечено на карте. " #cGRAY "(/gps - отмена)");
				}
			}
			
			ShowPlayerDialog(playerid, D_SITE + 23, DIALOG_STYLE_LIST, 
				(type == TYPE_ESTATE_HOUSE ? ("www.estateagency.com/houses") : ("www.estateagency.com/premises")), 
				(type == TYPE_ESTATE_HOUSE ? (DIALOG_SITE_HOUSE) : (DIALOG_SITE_PREMISE)), 
				"Далее", "Назад"
			);
		}
		
		case D_SITE + 30 :
		{
			if (!response)
			{
				ShowBrowserCursor(playerid, true, false);
				
				Clear:advert_pvar(playerid);
				return 1;
			}
			/*
					ShowPlayerDialog(playerid, D_SITE + 30, DIALOG_STYLE_LIST, "www.adverts.gog.com",
			" Категории объявления\n \
					Мои объявления",
			"Далее", "Закрыть"
		);
			*/
			if (listitem == 0) /// Cat
			{
				ShowPlayerDialog(playerid, D_SITE + 37, DIALOG_STYLE_LIST, "www.adverts.gog.com", DIALOG_ADVERT_CAT, "Далее", "Назад");
			}
			
			else if (listitem == 1) // Mya ads
			{
				ShowSiteAdvertList(playerid, D_SITE + 31);
			}
		}
		
		case D_SITE + 31 :
		{
			if (!response)
			{			
				ShowPlayerDialog(playerid, D_SITE + 30, DIALOG_STYLE_LIST, "www.adverts.gog.com",
					" Категории объявления\n \
							Мои объявления",
					"Далее", "Закрыть"
				);
				
				DeletePVar(playerid, "Site:AdvSelect");
				DeletePVar(playerid, "Site:CountAdverts");
				
				return 1;
			}
			
			if (listitem == 0) // Add
			{
				if (GetPVarInt(playerid, "Site:CountAdverts") >= MAX_ADVERTS)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете разместить на сайте больше 20 объявлений.");
					ShowSiteAdvertList(playerid, D_SITE + 31);
				}
				else
				{
					ShowPlayerDialog(playerid, D_SITE + 33, DIALOG_STYLE_LIST, "www.adverts.gog.com", DIALOG_ADVERT_CAT, "Выбрать", "Назад");
				}
				
				return 1;
			}
			
			listitem--;
			SetPVarInt(playerid, "Site:AdvSelect", listitem);
			ShowSiteAdvertInformation(playerid, listitem, D_SITE + 32, "Удалить", "Назад");
		}
		
		case D_SITE + 32 : 
		{
			if (!response)
			{
				ShowSiteAdvertList(playerid, D_SITE + 31);
				return 1;
			}
			
			format:g_string("DELETE FROM " #__ADVERTS " WHERE ad_id = %i",
				site_adv_select[playerid][GetPVarInt(playerid, "Site:AdvSelect")][ad_id]
			);
			
			mysql_tquery(db, g_string);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно удалили объявление с сайта.");
			ShowSiteAdvertList(playerid, D_SITE + 31);
		}
		
		case D_SITE + 33 :
		{
			if (!response)
			{
				ShowSiteAdvertList(playerid, D_SITE + 31);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowPlayerDialog(playerid, D_SITE + 33, DIALOG_STYLE_LIST, "www.adverts.gog.com", DIALOG_ADVERT_CAT, "Выбрать", "Назад");
				return 1;
			}
			
			listitem--;
			SetPVarInt(playerid, "Site:AdvCat", listitem);
			
			if (listitem != 3)
			{
				ShowPlayerDialog(playerid, D_SITE + 34, DIALOG_STYLE_LIST, "www.adverts.gog.com", DIALOG_ADVERT_TYPE, "Выбрать", "Назад");
			}
			else
			{
				SetPVarInt(playerid, "Site:AdvType", 0);
				ShowPlayerDialog(playerid, D_SITE + 35, DIALOG_STYLE_INPUT, "www.adverts.gog.com",
					"" #DEFAULT " Разместить объявление\n\n\
					Введите текст объявления:\n\n\
					" #cGRAY "Максимальная текста длина 128 символов.",
					"Далее", "Назад"
				);
			}
		}
		
		case D_SITE + 34 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_SITE + 33, DIALOG_STYLE_LIST, "www.adverts.gog.com", DIALOG_ADVERT_CAT, "Выбрать", "Назад");
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowPlayerDialog(playerid, D_SITE + 34, DIALOG_STYLE_LIST, "www.adverts.gog.com", DIALOG_ADVERT_TYPE, "Выбрать", "Назад");
				return 1;
			}
			
			SetPVarInt(playerid, "Site:AdvType", listitem);
			ShowPlayerDialog(playerid, D_SITE + 35, DIALOG_STYLE_INPUT, "www.adverts.gog.com",
				"" #DEFAULT " Разместить объявление\n\n\
				Введите текст объявления:\n\n\
				" #cGRAY "Максимальная текста длина 128 символов.",
				"Далее", "Назад"
			);
		}
		
		case D_SITE + 35 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_SITE + 34, DIALOG_STYLE_LIST, "www.adverts.gog.com", DIALOG_ADVERT_TYPE, "Выбрать", "Назад");
				return 1;
			}
			
			new cat = GetPVarInt(playerid, "Site:AdvCat");
			
			if (isnull(inputtext) || strlen(inputtext) >= 128)
			{
				ShowPlayerDialog(playerid, D_SITE + 35, DIALOG_STYLE_INPUT, "www.adverts.gog.com",
					"" #DEFAULT " Разместить объявление\n\n\
					Введите текст объявления:\n\n\
					" #cRED "Максимальная длина текста 128 символов.\n\
					Вы ввели некорректный текст.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			SetPVarString(playerid, "Site:AdvText", inputtext);
			
			if (cat != 3)
			{
				ShowPlayerDialog(playerid, D_SITE + 36, DIALOG_STYLE_INPUT, "www.adverts.gog.com",
					"" #DEFAULT " Разместить объявление\n\n\
					Введите стоимость имущества:\n\n\
					" #cGRAY "0 - договорная цена.",
					"Далее", "Назад"
				);
			}
			else 
			{	
				SetPVarInt(playerid, "Site:AdvPrice", 0);
				if (!Create:advert_data(playerid))
				{
					SendClientMessage(playerid, C_WHITE, !ERROR_ACTIVE_PHONE);
				}
				else 
				{
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно разместили объявление на " #cPROJECT "www.adverts.gog.com" #cWHITE".");
					ShowSiteAdvertList(playerid, D_SITE + 31);
				}
			}
		}
		
		case D_SITE + 36 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_SITE + 35, DIALOG_STYLE_INPUT, "www.adverts.gog.com",
					"" #DEFAULT " Разместить объявление\n\n\
					Введите текст объявления:\n\n\
					" #cGRAY "Максимальная текста длина 128 символов.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			new price = strval(inputtext);
			
			if (isnull(inputtext) || !(0 <= price <= 99_999_999_999))
			{	
				ShowPlayerDialog(playerid, D_SITE + 36, DIALOG_STYLE_INPUT, "www.adverts.gog.com",
					"" #DEFAULT " Разместить объявление\n\n\
					Введите стоимость имущества:\n\n\
					" #cGRAY "0 - договорная цена.\n\
					" #cRED "Вы ввели неверное значение.",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			SetPVarInt(playerid, "Site:AdvPrice", price);
			
			if (!Create:advert_data(playerid))
			{
				SendClientMessage(playerid, C_WHITE, !ERROR_ACTIVE_PHONE);
			}
			else 
			{
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно разместили объявление на " #cPROJECT "www.adverts.gog.com" #cWHITE".");
				ShowSiteAdvertList(playerid, D_SITE + 31);
			}
		}
		
		case D_SITE + 37 :
		{
			if (!response)
			{
				DeletePVar(playerid, "Site:AdvCatSelect");
				DeletePVar(playerid, "Site:AdvTypeSelect");
				DeletePVar(playerid, "Site:AdvPage");
				
				ShowPlayerDialog(playerid, D_SITE + 30, DIALOG_STYLE_LIST, "www.adverts.gog.com",
					" Категории объявления\n \
					Мои объявления",
					"Далее", "Закрыть"
				);
				
				return 1;
			}

			if (listitem == 0)
			{
				ShowPlayerDialog(playerid, D_SITE + 37, DIALOG_STYLE_LIST, "www.adverts.gog.com", DIALOG_ADVERT_CAT, "Далее", "Назад");
				return 1;
			}
			
			listitem--;
			SetPVarInt(playerid, "Site:AdvCatSelect", listitem);
			if (listitem != 3)
			{
				ShowPlayerDialog(playerid, D_SITE + 38, DIALOG_STYLE_LIST, "www.adverts.gog.com", DIALOG_ADVERT_TYPE, "Далее", "Назад");
			}
			else
			{
				SetPVarInt(playerid, "Site:AdvTypeSelect", 0);
				
				ShowSiteAdvertList(
					playerid, 
					D_SITE + 39, 
					0, 
					GetPVarInt(playerid, "Site:AdvCatSelect"), 
					0 
				);
			}
		}
		
		case D_SITE + 38 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_SITE + 37, DIALOG_STYLE_LIST, "www.adverts.gog.com", DIALOG_ADVERT_CAT, "Далее", "Назад");
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowPlayerDialog(playerid, D_SITE + 38, DIALOG_STYLE_LIST, "www.adverts.gog.com", DIALOG_ADVERT_TYPE, "Далее", "Назад");
				return 1;
			}
			
			SetPVarInt(playerid, "Site:AdvTypeSelect", listitem);
			
			ShowSiteAdvertList(
				playerid, 
				D_SITE + 39, 
				0, 
				GetPVarInt(playerid, "Site:AdvCatSelect"), 
				listitem 
			);
		}
		
		case D_SITE + 39 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_SITE + 38, DIALOG_STYLE_LIST, "www.adverts.gog.com", DIALOG_ADVERT_TYPE, "Далее", "Назад");
				return 1;
			}
			
			if (site_adv_select[playerid][listitem][ad_id] == ITEM_LIST_NEXT)
			{
				ShowSiteAdvertList(
					playerid, 
					D_SITE + 39, 
					GetPVarInt(playerid, "Site:AdvPage") + 1, 
					GetPVarInt(playerid, "Site:AdvCatSelect"), 
					GetPVarInt(playerid, "Site:AdvTypeSelect")
				);
				
				return 1;
			}
			
			else if (site_adv_select[playerid][listitem][ad_id] == ITEM_LIST_BACK)
			{
				ShowSiteAdvertList(
					playerid, 
					D_SITE + 39, 
					GetPVarInt(playerid, "Site:AdvPage") - 1, 
					GetPVarInt(playerid, "Site:AdvCatSelect"), 
					GetPVarInt(playerid, "Site:AdvTypeSelect") 
				);
				
				return 1;
			}
			
			else if (site_adv_select[playerid][listitem][ad_id] == ITEM_LIST_NONE)
			{
				ShowPlayerDialog(playerid, D_SITE + 38, DIALOG_STYLE_LIST, "www.adverts.gog.com", DIALOG_ADVERT_TYPE, "Далее", "Назад");
				return 1;
			}
			
			ShowSiteAdvertInformation(playerid, listitem, D_SITE + 40);
		}
		
		case D_SITE + 40 :
		{
			ShowSiteAdvertList(
				playerid, 
				D_SITE + 39, 
				GetPVarInt(playerid, "Site:AdvPage"), 
				GetPVarInt(playerid, "Site:AdvCatSelect"), 
				GetPVarInt(playerid, "Site:AdvTypeSelect")
			);
		}
		
		
		/*
		
			@brief LS Portal
		
		*/
		
		
		case D_SITE + 41 :
		{
			if (!response)
			{
				ShowBrowserCursor(playerid, true, false);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowPlayerDialog(playerid, D_SITE + 42, DIALOG_STYLE_LIST, 
					"www.lscity.com",
					" Указы\n \
					  Законадательные Акты\n \
					  Приказы\n \
					  Положения",
					"Далее", "Назад"
				);
			}
			else if (listitem == 1)
			{
				ShowPlayerDialog(playerid, D_SITE + 43, DIALOG_STYLE_LIST, 
					"www.san.com",
					" Новостная лента",
					"Далее", "Назад"
				);
			}
		}
		
		case D_SITE + 42:
		{
			if (response)
			{
				ShowBrowserCursor(playerid, true, false);
				return 1;
			}
			
			ShowPlayerDialog(playerid, D_SITE + 42, DIALOG_STYLE_LIST, 
				"www.lscity.com",
				" Указы\n \
				  Законадательные Акты\n \
				  Приказы\n \
				  Положения",
				"Далее", "Назад"
			);
			
			SendClientMessage(playerid, C_WHITE, !#ERROR " Информация отсутствует.");
		}
		
		case D_SITE + 43:
		{
			if (!response)
			{
				ShowBrowserCursor(playerid, true, false);
				return 1;
			}
			
			ShowPlayerDialog(playerid, D_SITE + 43, DIALOG_STYLE_LIST, 
				"www.san.com",
				" Новостная лента",
				"Далее", "Назад"
			);
			
			SendClientMessage(playerid, C_WHITE, !#ERROR " Информация отсутствует.");
		}
		
		case D_SITE + 44:
		{
			if (!response)
			{
				ShowBrowserCursor(playerid, true, false);
				return 1;
			}
			
			if (isnull(inputtext) || !IsValidSiteString(inputtext, MIN_SITE_ADDRESS, MAX_SITE_ADDRESS))
			{
				ShowPlayerDialog(playerid, D_SITE + 44, DIALOG_STYLE_INPUT, "www.gog.com",
					"" #DEFAULT " Поиск\n\n\
					Введите ключевое слово на английском:\n\n\
					" #cRED "Вы введи некорректное слово.",
					"Далее", "Закрыть"
				);
				
				return 1;
			}
			
			clean:<g_big_string>;
			
			new count;
			for (new i; i < MAX_SITES; i++)
			{
				if (site_data[i][s_id] == 0)
				{
					continue;
				}
				
				if (strfind(site_data[i][s_name], inputtext, true) != -1
				|| strfind(site_data[i][s_slogan], inputtext, true) != -1
				|| strfind(site_data[i][s_description], inputtext, true) != -1)
				{
					if (count >= 50)
					{
						break;
					}
					
					format:g_big_string("%s %s (%s) - %s\n", 
						g_big_string,
						site_data[i][s_name],
						site_data[i][s_address],
						site_data[i][s_description]
					);
					
					g_dialog_select[playerid][count++] = i;
				}
			}
			
			if (!count)
			{
				g_dialog_select[playerid][0] = INVALID_PARAM;
				strcat(g_big_string, " " #cGRAY "По вашему результату ничего не найдено");
			}
			
			ShowPlayerDialog(playerid, D_SITE + 45, DIALOG_STYLE_LIST, " ", g_big_string, "Выбрать", "Закрыть");
		}
		
		case D_SITE + 45:
		{
			new index = g_dialog_select[playerid][listitem];
			
			if (!response || index == INVALID_PARAM)
			{
				ShowBrowserCursor(playerid, false, true);
				ShowPlayerDialog(playerid, D_SITE + 44, DIALOG_STYLE_INPUT, "www.gog.com",
					"" #DEFAULT " Поиск\n\n\
					Введите ключевое слово на английском:",
					"Далее", "Закрыть"
				);
				
				return 1;
			}
			
			SiteGoToPage(playerid, site_data[index][s_address]);
		}
	}
	
	return 1;
}