/*!
	@brief Функции для системы сайтов
	@author Found (evg.savosin)
	@date 16.12.2016, update 14.02.2018
*/

Clear:site_pvar(playerid)
{
	SetPVarInt(playerid, "Site:Select", INVALID_PARAM);
	
	DeletePVar(playerid, "Site:Page");
}

Clear:site_edit_pvar(playerid)
{
	DeletePVar(playerid, "Site:EditAction");
	DeletePVar(playerid, "Site:EditColor");
	DeletePVar(playerid, "Site:EditDomain");
	DeletePVar(playerid, "Site:EditName");
	DeletePVar(playerid, "Site:EditSlogan");
	DeletePVar(playerid, "Site:EditDescription");
	DeletePVar(playerid, "Site:EditDarknet");
	DeletePVar(playerid, "Site:EditTemplate");
	
	DeletePVar(playerid, "Site:EditPageName[0]");
	DeletePVar(playerid, "Site:EditPageName[1]");
	DeletePVar(playerid, "Site:EditPageName[2]");
	DeletePVar(playerid, "Site:EditPageName[3]");
	
	DeletePVar(playerid, "Site:EditPageDesc[0]");
	DeletePVar(playerid, "Site:EditPageDesc[1]");
	DeletePVar(playerid, "Site:EditPageDesc[2]");
	DeletePVar(playerid, "Site:EditPageDesc[3]");
}

Site_OnGameModeInit()
{
	format:g_string("SELECT * FROM " #__SITES " LIMIT %i", MAX_SITES);
	mysql_tquery(db, g_string, "OnSiteLoad", "");
}

Site_OnPlayerClickPTD(playerid, PlayerText: playertextid)
{
	if (!GetPVarInt(playerid, "Site:States"))
	{
		return 1;
	}
	
	new index = GetPVarInt(playerid, "Site:Select");
	
	/// Адресная строка
	if (playertextid == ptd_address_line[playerid])
	{
		ShowBrowserCursor(playerid, false, true);
		
		ShowPlayerDialog(playerid, D_SITE, DIALOG_STYLE_INPUT, " ",
			"" #DEFAULT " Адресная строка\n\n\
			Введите ссылку в адресную строку для перехода на сайт:\n\n\
			" #cGRAY "Адрес должен быть в формате: www.domain.com",
			"Перейти", "Закрыть"
		);
	}
	
	// Template Url
	else if (playertextid == ptd_site_template_1[playerid][2]
	|| playertextid == ptd_site_template_2[playerid][5]
	|| playertextid == ptd_site_template_3[playerid][2]
	|| playertextid == ptd_dark_template_1[playerid][2])
	{
		ShowSitePageContent(playerid, index, s_name_page_1, s_desc_page_1);
	}
	
	else if (playertextid == ptd_site_template_1[playerid][3] 
	|| playertextid == ptd_site_template_2[playerid][4]
	|| playertextid == ptd_site_template_3[playerid][3] 
	|| playertextid == ptd_dark_template_1[playerid][3])
	{
		ShowSitePageContent(playerid, index, s_name_page_2, s_desc_page_2);
	}
	
	else if (playertextid == ptd_site_template_1[playerid][4]
	|| playertextid == ptd_site_template_2[playerid][3]
	|| playertextid == ptd_site_template_3[playerid][4] 
	|| playertextid == ptd_dark_template_1[playerid][4])
	{
		ShowSitePageContent(playerid, index, s_name_page_3, s_desc_page_3);
	}
	
	else if (playertextid == ptd_site_template_1[playerid][5] 
	|| playertextid == ptd_site_template_2[playerid][2]
	|| playertextid == ptd_site_template_3[playerid][5] 
	|| playertextid == ptd_dark_template_1[playerid][5])
	{
		ShowSitePageContent(playerid, index, s_name_page_4, s_desc_page_4);
	}
	
	return 1;
}

Site_OnPlayerClickTextDraw(playerid, Text: clickedid)
{
	if (!GetPVarInt(playerid, "Site:States"))
	{
		return 1;
	}
	
	if (clickedid == INVALID_TEXT_DRAW 
	|| clickedid == td_browser[2]) /// Exit
	{
		if (GetPVarInt(playerid, "Site:HideCursor"))
		{
			return 1;
		}
		
		ShowBrowser(playerid, false, false);
		cmd_phone(playerid);
	}
	else if (clickedid == td_browser[4]) /// Gog.com
	{
		UpdateBrowser(playerid, SITE_GOG, "www.gog.com", GetPVarInt(playerid, "Site:Select"));
	}
	else if (clickedid == td_browser[5]) /// Favorite Sites
	{
		if (!ShowSiteFavorites(playerid))
		{
			SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
		}
		else 
		{
			ShowBrowserCursor(playerid, false, true);
		}
	}
	
	/*!
		
		@brief GOG
	
	*/
	
	else if (clickedid == td_site_gog[2]) // Search
	{
		ShowBrowserCursor(playerid, false, true);
		ShowPlayerDialog(playerid, D_SITE + 44, DIALOG_STYLE_INPUT, "www.gog.com",
			"" #DEFAULT " Поиск\n\n\
			Введите ключевое слово на английском:",
			"Далее", "Закрыть"
		);
	}
	
	else if (clickedid == td_site_gog[5]) /// Arthouse
	{
		ShowBrowserCursor(playerid, false, true);
		ShowPlayerDialog(playerid, D_SITE + 22, DIALOG_STYLE_LIST, "www.arthouse.com",
			" Каталог жилья\n \
			Каталог коммерческих помещений",
			"Далее", "Закрыть"
		);
		
	}
	else if (clickedid == td_site_gog[13]) /// Adverts
	{
		ShowBrowserCursor(playerid, false, true);
		ShowPlayerDialog(playerid, D_SITE + 30, DIALOG_STYLE_LIST, "www.adverts.gog.com",
			" Категории объявлений\n \
			Мои объявления",
			"Далее", "Закрыть"
		);
		
	}
	else if (clickedid == td_site_gog[17]) /// Bank
	{
		ShowBrowserCursor(playerid, false, true);
		ShowBankMenu(playerid, TYPE_BANK_ONLINE);
	}
	else if (clickedid == td_site_gog[21]) /// LS Portal
	{
		ShowBrowserCursor(playerid, false, true);
		ShowPlayerDialog(playerid, D_SITE + 41, DIALOG_STYLE_LIST, "www.lsportal.com",
			" www.lscity.com\n \
			  www.san.com",
			"Далее", "Закрыть"
		);
	}
	else if (clickedid == td_site_gog[29]) /// Create Site (OVH)
	{
		ShowBrowserCursor(playerid, false, true);
		ShowSiteList(playerid, D_SITE + 5);
	}
	
	return 1;
}

// Site Functions

SiteGoToPage(playerid, address[])
{
	new absolute_address			[	 MAX_SITE_ADDRESS 	],
		index;
			
	GetAbsoluteWebsiteAddress(address, absolute_address);
	index = GetSiteIndexByDomain(absolute_address);
	
	if (!IsValidSiteString(absolute_address, MIN_SITE_ADDRESS, MAX_SITE_ADDRESS) 
	|| index == INVALID_PARAM)
	{
		return 0;
	}

	SetPVarInt(playerid, "Site:Select", index);
	UpdateBrowser(playerid, SITE_CUSTOM, address, index);
	
	ShowBrowserCursor(playerid, true, false);
	return 1;
}

ReplaceSiteDataPVar(playerid, index)
{
	site_data[index][s_color] = GetPVarInt(playerid, "Site:EditColor");
	site_data[index][s_template] = GetPVarInt(playerid, "Site:EditTemplate");
	
	GetPVarString(playerid, "Site:EditDomain", site_data[index][s_address], MAX_SITE_ADDRESS);
	GetPVarString(playerid, "Site:EditName", site_data[index][s_name], MAX_SITE_NAME);
	GetPVarString(playerid, "Site:EditSlogan", site_data[index][s_slogan], 32);
	GetPVarString(playerid, "Site:EditDescription", site_data[index][s_description], 128);
	
	GetPVarString(playerid, "Site:EditPageName[0]", site_data[index][s_name_page_1], MAX_SITE_PAGE_NAME);
	GetPVarString(playerid, "Site:EditPageName[1]", site_data[index][s_name_page_2], MAX_SITE_PAGE_NAME);
	GetPVarString(playerid, "Site:EditPageName[2]", site_data[index][s_name_page_3], MAX_SITE_PAGE_NAME);
	GetPVarString(playerid, "Site:EditPageName[3]", site_data[index][s_name_page_4], MAX_SITE_PAGE_NAME);
	
	GetPVarString(playerid, "Site:EditPageDesc[0]", site_data[index][s_desc_page_1], MAX_SITE_PAGE_DESC);
	GetPVarString(playerid, "Site:EditPageDesc[1]", site_data[index][s_desc_page_2], MAX_SITE_PAGE_DESC);
	GetPVarString(playerid, "Site:EditPageDesc[2]", site_data[index][s_desc_page_3], MAX_SITE_PAGE_DESC);
	GetPVarString(playerid, "Site:EditPageDesc[3]", site_data[index][s_desc_page_4], MAX_SITE_PAGE_DESC);

	site_data[index][s_is_darknet] = bool: GetPVarInt(playerid, "Site:EditDarknet");
}

PutSiteDataPVar(playerid, index)
{
	SetPVarInt(playerid, "Site:EditColor", site_data[index][s_color]);
	SetPVarInt(playerid, "Site:EditTemplate", site_data[index][s_template]);
	
	SetPVarString(playerid, "Site:EditDomain", site_data[index][s_address]);
	SetPVarString(playerid, "Site:EditName", site_data[index][s_name]);
	SetPVarString(playerid, "Site:EditSlogan", site_data[index][s_slogan]);
	SetPVarString(playerid, "Site:EditDescription", site_data[index][s_description]);
	
	SetPVarString(playerid, "Site:EditPageName[0]", site_data[index][s_name_page_1]);
	SetPVarString(playerid, "Site:EditPageName[1]", site_data[index][s_name_page_2]);
	SetPVarString(playerid, "Site:EditPageName[2]", site_data[index][s_name_page_3]);
	SetPVarString(playerid, "Site:EditPageName[3]", site_data[index][s_name_page_4]);
	
	SetPVarString(playerid, "Site:EditPageDesc[0]", site_data[index][s_desc_page_1]);
	SetPVarString(playerid, "Site:EditPageDesc[1]", site_data[index][s_desc_page_2]);
	SetPVarString(playerid, "Site:EditPageDesc[2]", site_data[index][s_desc_page_3]);
	SetPVarString(playerid, "Site:EditPageDesc[3]", site_data[index][s_desc_page_4]);
	
	SetPVarInt(playerid, "Site:EditDarknet", _: site_data[index][s_is_darknet]);
}

GetPlayerMaxSites(playerid)
{
	switch (user_data[playerid][u_vip])
	{
		case 1, 2: 
		{
			return MAX_PLAYER_SITES - 1;
		}
		
		case 3, 4:
		{
			return MAX_PLAYER_SITES;
		}
	}
	
	return MAX_PLAYER_SITES - 2;
}

GetPlayerAvaibleSites(playerid)
{
	return (GetPlayerMaxSites(playerid) - GetPlayerSitesCount(playerid)) <= 0 ? false : true;
}

GetPlayerSitesCount(playerid)
{
	new count;
		
	for (new i; i < MAX_PLAYER_SITES; i++)
	{
		if (player_site[playerid][i] == INVALID_PARAM)
		{
			continue;
		}
		
		count++;
	}
	
	return count;
}

GiveSiteOwner(playerid, index) // Выдаем овнера при авторизации
{
	for (new i; i < MAX_PLAYER_SITES; i++)
	{
		if (player_site[playerid][i] == INVALID_PARAM)
		{
			player_site[playerid][i] = index;
			
			break;
		}
	}
}

RemoveSiteOwner(playerid, index)
{
	for (new i; i < MAX_PLAYER_SITES; i++)
	{
		if (player_site[playerid][i] == index)
		{
			player_site[playerid][i] = INVALID_PARAM;
			
			break;
		}
	}
}

GetFreeIndexForSite()
{
	for (new i; i < sizeof site_data; i++)
	{
		if (GetSiteId(i) != 0)
		{
			continue;
		}
		
		printf("[GetFreeIndexForSite] = %d", i);
		return i; 
	}
	
	return INVALID_PARAM;
}

GetAbsoluteWebsiteAddress(input_address[], output_address[], len = sizeof(output_address))
{	
	output_address[0] = EOS;
	if (strfind(input_address, "www.") == 0)
	{
		strdel(input_address, 0, 4);
	}
	
	strcat(output_address, input_address, len);
}


GetSiteIndexByDomain(domain[])
{
	for (new i; i < sizeof site_data; i++)
	{
		if (site_data[i][s_id] == 0)
		{
			continue;
		}
		
		if (!strcmp(domain, site_data[i][s_address]))
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

IsValidSiteString(const text[], min, max)
{
	new len = strlen(text);
		
	if (!(min <= len <= max))
	{
		return 0;
	}
	
	while (len-- != 0)
	{
		switch(text[len])
		{	
			case 'а' .. 'я', 'А' .. 'Я', '/', '\n', '`', '~', '%', '^', '&', '[', ']', '{', '}', '|', ''' :
			{
				return 0;
			}
		}
	}
	
	return 1;
}

IsValidDomain(domain[])
{	
	for (new i; i < sizeof site_domains; i++)
	{
		if (!strcmp(site_domains[i], domain))
		{
			return 1;
		}
	}
	
	return 0;
}