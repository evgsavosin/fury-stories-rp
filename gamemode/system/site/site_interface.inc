/*!
	@brief Интерфейс для системы сайтов
	@author Found (evg.savosin)
	@date 16.12.2016, update 14.02.2018
*/

ShowBrowserCursor(playerid, bool: states, forbid_cancel_select = false)
{
	SetPVarInt(playerid, "Site:HideCursor", forbid_cancel_select);
	
	if (states)
	{
		SelectTextDraw(playerid, C_GRAY);
	}
	else
	{
		CancelSelectTextDraw(playerid);
	}
}

ShowBrowser(playerid, bool: states, bool: cancel_select = true)
{
	if (states)
	{
		for (new i; i < sizeof td_browser; i++)
		{
			TextDrawShowForPlayer(playerid, td_browser[i]);
		}
		
		PlayerTextDrawShow(playerid, ptd_address_line[playerid]);
		
		ShowBrowserCursor(playerid, true);
		
		UpdateBrowser(playerid, SITE_GOG, "www.gog.com");
	}
	else 
	{
		for (new i; i < sizeof td_browser; i++)
		{
			TextDrawHideForPlayer(playerid, td_browser[i]);
		}
		
		PlayerTextDrawHide(playerid, ptd_address_line[playerid]);
		
		ShowSiteGOG(playerid, false);
		ShowSiteCustom(playerid, false);
		
		if (cancel_select)
		{
			ShowBrowserCursor(playerid, false);
		}
		
		Clear:site_pvar(playerid);
	}
	
	SetPVarInt(playerid, "Site:States", states);
}

UpdateBrowser(playerid, const page, domain[], index = INVALID_PARAM)
{	
	new oldpage = GetPVarInt(playerid, "Site:Page");
	
	/// Скрываем старую страницу, если есть
	if (oldpage != SITE_INVALID)
	{
		if (oldpage == SITE_GOG)
		{
			ShowSiteGOG(playerid, false);
		}
		
		else if (oldpage == SITE_CUSTOM)
		{
			ShowSiteCustom(playerid, false, index);
		}
	}
	
	/// Обновляем браузерную строку
	PlayerTextDrawSetString(playerid, ptd_address_line[playerid], domain);
	
	if (page == SITE_GOG)
	{
		ShowSiteGOG(playerid, true);
	}
	
	else if (page == SITE_CUSTOM)
	{
		if (index == INVALID_PARAM)
		{
			return;
		}
		
		ShowSiteCustom(playerid, true, index);
	}
	
	SetPVarInt(playerid, "Site:Page", page);
	
}

ShowSiteGOG(playerid, bool: states)
{
	if (states)
	{
		for (new i; i < sizeof td_site_gog; i++)
		{
			TextDrawShowForPlayer(playerid, td_site_gog[i]);
		}
	}
	else 
	{
		for (new i; i < sizeof td_site_gog; i++)
		{
			TextDrawHideForPlayer(playerid, td_site_gog[i]);
		}
	}
}

ShowSiteCustom(playerid, bool: states, index = INVALID_PARAM)
{
	if (!states && index == INVALID_PARAM)
	{
		ShowTemplateOne(playerid, states, index);
		ShowTemplateTwo(playerid, states, index);
		ShowTemplateThree(playerid, states, index);
		ShowTemplateDarknetOne(playerid, states, index);
		return;
	}
	
	switch(site_data[index][s_template])
	{
		case 1 :
		{
			ShowTemplateOne(playerid, states, index);
		}
		
		case 2 :
		{
			ShowTemplateTwo(playerid, states, index);
		}
		
		case 3 :
		{
			ShowTemplateThree(playerid, states, index);
		}
		
		case 4 :
		{
			ShowTemplateDarknetOne(playerid, states, index);
		}
	}
}

/// Первый шаблон
ShowTemplateOne(playerid, bool: states, index = INVALID_PARAM)
{
	if (states)
	{
		if (index == INVALID_PARAM)
		{
			return;
		}
		
		for (new i; i < TD_SITE_TEMPLATE_1; i++)
		{
			if (i < sizeof td_site_template_1)
			{
				TextDrawShowForPlayer(playerid, td_site_template_1[i]);
			}
			
			switch(i)
			{
				case 0, 9, 10 : /// Фон меню, блоков
				{
					PlayerTextDrawBoxColor(
						playerid, 
						ptd_site_template_1[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int]
					);
				}
				
				case 1 : /// Logo
				{
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_1[playerid][i], 
						site_data[index][s_name] 
					);
				}
				
				case 2 : /// Name Page 1
				{
					if (isnull(site_data[index][s_name_page_1]))
					{
						continue;
					}
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_1[playerid][i], 
						site_data[index][s_name_page_1] 
					);
				}
				
				case 3 : /// Name Page 2
				{
					if (isnull(site_data[index][s_name_page_2]))
					{
						continue;
					}
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_1[playerid][i], 
						site_data[index][s_name_page_2] 
					);
				}
				
				case 4 : /// Name Page 3
				{
					if (isnull(site_data[index][s_name_page_3]))
					{
						continue;
					}
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_1[playerid][i], 
						site_data[index][s_name_page_3] 
					);
				}
				
				case 5 : /// Name Page 4
				{
					if (isnull(site_data[index][s_name_page_4]))
					{
						continue;
					}
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_1[playerid][i], 
						site_data[index][s_name_page_4] 
					);
				}
				
				case 6 : /// Description
				{
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_1[playerid][i], 
						site_data[index][s_description] 
					);
				}
				
				case 7 : /// Copyrights
				{
					PlayerTextDrawColor(
						playerid, 
						ptd_site_template_1[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int] 
					);
					
					format:g_small_string("(c) 2019 %s. All Rights Reserved.",
						site_data[index][s_name]
					);
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_1[playerid][i], 
						g_small_string 
					);
				}
				
				case 8 : /// Slogan
				{
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_1[playerid][i], 
						site_data[index][s_slogan] 
					);
				}
			}
			
			PlayerTextDrawShow(playerid, ptd_site_template_1[playerid][i]);
		}
	}
	else 
	{
		for (new i; i < TD_SITE_TEMPLATE_1; i++)
		{
			if (i < sizeof td_site_template_1)
			{
				TextDrawHideForPlayer(playerid, td_site_template_1[i]);
			}
			
			PlayerTextDrawHide(playerid, ptd_site_template_1[playerid][i]);
		}
	}
}

/// Второй шаблон
ShowTemplateTwo(playerid, bool: states, index = INVALID_PARAM)
{
	if (states)
	{
		if (index == INVALID_PARAM)
		{
			return;
		}
		
		for (new i; i < TD_SITE_TEMPLATE_2; i++)
		{
			if (i < sizeof td_site_template_2)
			{
				TextDrawShowForPlayer(playerid, td_site_template_2[i]);
			}
			
			switch(i)
			{
				case 0 :
				{
					PlayerTextDrawBoxColor(
						playerid, 
						ptd_site_template_2[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int] 
					);
				}
				
				case 1 : /// Background-Menu, Логотип
				{
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_2[playerid][i], 
						site_data[index][s_name] 
					);
				}
				
				case 5 : /// Name Page 1
				{	
					if (isnull(site_data[index][s_name_page_1]))
					{
						continue;
					}
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_2[playerid][i], 
						site_data[index][s_name_page_1] 
					);
				}
				
				case 4 : /// Name Page 2
				{
					if (isnull(site_data[index][s_name_page_2]))
					{
						continue;
					}
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_2[playerid][i], 
						site_data[index][s_name_page_2] 
					);
				}
				
				case 3 : /// Name Page 3
				{
					if (isnull(site_data[index][s_name_page_3]))
					{
						continue;
					}
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_2[playerid][i], 
						site_data[index][s_name_page_3] 
					);
				}
				
				case 2 : /// Name Page 4
				{
					if (isnull(site_data[index][s_name_page_4]))
					{
						continue;
					}
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_2[playerid][i], 
						site_data[index][s_name_page_4] 
					);
				}
				
				case 6 : /// Description
				{
					PlayerTextDrawColor(
						playerid, 
						ptd_site_template_2[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int] 
					);
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_2[playerid][i], 
						site_data[index][s_description] 
					);
				}
				
				case 7 : /// Copyrights
				{
					PlayerTextDrawColor(
						playerid, 
						ptd_site_template_2[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int] 
					);
					
					format:g_small_string("(c) 2019 %s. All Rights Reserved.",
						site_data[index][s_name]
					);
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_2[playerid][i], 
						g_small_string
					);
				}
				
				case 8 : /// Slogan
				{
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_2[playerid][i], 
						site_data[index][s_slogan] 
					);
				}
				
				case 9, 10 : /// Date and Login
				{
					PlayerTextDrawColor(
						playerid, 
						ptd_site_template_2[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int] 
					);
				}
			}
			
			PlayerTextDrawShow(playerid, ptd_site_template_2[playerid][i]);
		}
	}
	else 
	{
		for (new i; i < TD_SITE_TEMPLATE_2; i++)
		{
			if (i < sizeof td_site_template_2)
			{
				TextDrawHideForPlayer(playerid, td_site_template_2[i]);
			}
			
			PlayerTextDrawHide(playerid, ptd_site_template_2[playerid][i]);
		}
	}
}

/// Третий шаблон
ShowTemplateThree(playerid, bool: states, index = INVALID_PARAM)
{
	if (states)
	{
		if (index == INVALID_PARAM)
		{
			return;
		}
		
		for (new i; i < TD_SITE_TEMPLATE_3; i++)
		{
			if (i < sizeof td_site_template_3)
			{
				TextDrawShowForPlayer(playerid, td_site_template_3[i]);
			}
			
			switch(i)
			{
				case 0 : /// Логотип
				{	
					PlayerTextDrawColor(
						playerid, 
						ptd_site_template_3[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int] 
					);
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_3[playerid][i], 
						site_data[index][s_name] 
					);
				}
				
				case 1 : /// Slogan
				{
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_3[playerid][i], 
						site_data[index][s_slogan] 
					);
				}
				
				case 2 : /// Name Page 1
				{	
					if (isnull(site_data[index][s_name_page_1]))
					{
						continue;
					}
					
					PlayerTextDrawColor(
						playerid, 
						ptd_site_template_3[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int] 
					);
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_3[playerid][i], 
						site_data[index][s_name_page_1] 
					);
				}
				
				case 3 : /// Name Page 2
				{
					if (isnull(site_data[index][s_name_page_2]))
					{
						continue;
					}
					
					PlayerTextDrawColor(
						playerid, 
						ptd_site_template_3[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int] 
					);
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_3[playerid][i], 
						site_data[index][s_name_page_2] 
					);
				}
				
				case 4 : /// Name Page 3
				{
					if (isnull(site_data[index][s_name_page_3]))
					{
						continue;
					}
					
					PlayerTextDrawColor(
						playerid, 
						ptd_site_template_3[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int] 
					);
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_3[playerid][i], 
						site_data[index][s_name_page_3] 
					);
				}
				
				case 5 : /// Name Page 4
				{
					if (isnull(site_data[index][s_name_page_4]))
					{
						continue;
					}
					
					PlayerTextDrawColor(
						playerid, 
						ptd_site_template_3[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int] 
					);
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_3[playerid][i], 
						site_data[index][s_name_page_4] 
					);
				}
				
				case 7 :
				{
					PlayerTextDrawColor(
						playerid, 
						ptd_site_template_3[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int] 
					);
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_3[playerid][i], 
						site_data[index][s_description] 
					);
				}
				
				case 6 :
				{
					PlayerTextDrawBoxColor(
						playerid, 
						ptd_site_template_3[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int]
					);
				}
				
				case 8 : /// Copyrights
				{
					format:g_small_string("(c) 2019 %s. All Rights Reserved.",
						site_data[index][s_name]
					);
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_site_template_3[playerid][i], 
						g_small_string
					);
				}
			}
			
			PlayerTextDrawShow(playerid, ptd_site_template_3[playerid][i]);
		}
	}
	else 
	{
		for (new i; i < TD_SITE_TEMPLATE_3; i++)
		{
			if (i < sizeof td_site_template_3)
			{
				TextDrawHideForPlayer(playerid, td_site_template_3[i]);
			}
			
			PlayerTextDrawHide(playerid, ptd_site_template_3[playerid][i]);
		}
	}
}


/// Первый шаблон (Darknet)
ShowTemplateDarknetOne(playerid, bool: states, index = INVALID_PARAM)
{
	if (states)
	{
		if (index == INVALID_PARAM)
		{
			return;
		}

		TextDrawShowForPlayer(playerid, td_browser_black);
		TextDrawShowForPlayer(playerid, td_browser_tor);
		TextDrawShowForPlayer(playerid, td_dark_template_1);
		
		for (new i; i < TD_DARK_TEMPLATE_1; i++)
		{	
			switch(i)
			{
				case 0 : /// Логотип
				{
					PlayerTextDrawSetString(
						playerid, 
						ptd_dark_template_1[playerid][i], 
						site_data[index][s_name] 
					);
				}
				
				case 1 : /// Слоган
				{
					PlayerTextDrawColor(
						playerid, 
						ptd_dark_template_1[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int] 
					);
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_dark_template_1[playerid][i], 
						site_data[index][s_slogan] 
					);
				}
				
				case 2 :  /// Name Page 1
				{
					if (isnull(site_data[index][s_name_page_1]))
					{
						continue;
					}
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_dark_template_1[playerid][i], 
						site_data[index][s_name_page_1] 
					);
				}
				
				case 3 :  /// Name Page 2
				{
					if (isnull(site_data[index][s_name_page_2]))
					{
						continue;
					}
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_dark_template_1[playerid][i], 
						site_data[index][s_name_page_2] 
					);
				}
				
				case 4 :  /// Name Page 3
				{
					if (isnull(site_data[index][s_name_page_3]))
					{
						continue;
					}
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_dark_template_1[playerid][i], 
						site_data[index][s_name_page_3] 
					);
				}
				
				case 5 :  /// Name Page 4
				{
					if (isnull(site_data[index][s_name_page_4]))
					{
						continue;
					}
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_dark_template_1[playerid][i], 
						site_data[index][s_name_page_4] 
					);
				}
				
				case 6 : /// Description
				{
					PlayerTextDrawColor(
						playerid, 
						ptd_dark_template_1[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int] 
					);
					
					PlayerTextDrawSetString(
						playerid, 
						ptd_dark_template_1[playerid][i], 
						site_data[index][s_description] 
					);
				}
				
				case 7 .. 10 :
				{
					PlayerTextDrawColor(
						playerid, 
						ptd_dark_template_1[playerid][i], 
						site_colors[site_data[index][s_color]][sc_color_int] 
					);
				}
			}
			
			PlayerTextDrawShow(playerid, ptd_dark_template_1[playerid][i]);
		}
	}
	else 
	{
		TextDrawHideForPlayer(playerid, td_browser_black);
		TextDrawHideForPlayer(playerid, td_browser_tor);
		TextDrawHideForPlayer(playerid, td_dark_template_1);
		
		for (new i; i < TD_DARK_TEMPLATE_1; i++)
		{
			PlayerTextDrawHide(playerid, ptd_dark_template_1[playerid][i]);
		}
	}
}