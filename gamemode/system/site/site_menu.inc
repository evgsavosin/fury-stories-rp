/*!
	@brief ���������� ������� ��� ������� ������
	@author Found (evg.savosin)
	@date 16.12.2016, update 14.02.2018
*/

ShowSiteList(playerid, dialogid)
{
	clean:<g_big_string>;
	
	new count = 0,
		index;

	strcat(g_big_string, "" #cGRAY "������� ����\t\n" #cWHITE "");
	for (new i; i < MAX_PLAYER_SITES; i++)
	{
		if ((index = player_site[playerid][i]) == INVALID_PARAM)
		{
			continue;
		}
		
		format:g_big_string("%s %s%s\t%s\n",
			g_big_string,
			site_data[index][s_name],
			(site_data[index][s_rent_time] < gettime() + (60 * 60 * 24 * 3)) ? (" [" #cDARKRED "������� ������" #cWHITE "]") : (""),
			site_data[index][s_address]
		);
		
		g_dialog_select[playerid][count] = index;
		count++;
	}   
	
	return ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, " ", g_big_string, "�������", "�������");
}

ShowSiteInformation(playerid, dialogid, const index)
{
	clean:<g_big_string>;
	
	new day,
		month,
		year,
		hour,
		minute;
	
	gmtime(site_data[index][s_created_time], year, month, day, hour, minute, _);
	
	format:g_big_string("\
		" #DEFAULT " ���������� � �����\n\n\
		�����: " #cPROJECT "%s" #cWHITE "\n\
		��������: " #cPROJECT "%s" #cWHITE "\n\
		������: " #cPROJECT "%s" #cWHITE "\n\
		���� �������: {%s}%s" #cWHITE "\n\
		���� ��������: " #cPROJECT "" #DATE_FORMAT "" #cWHITE ".\n",
		site_data[index][s_address],
		site_data[index][s_name],
		site_data[index][s_slogan],
		site_colors[site_data[index][s_color]][sc_color],
		site_colors[site_data[index][s_color]][sc_color_name],
		hour, minute, day, month, year
	);
	
	gmtime(site_data[index][s_rent_time], year, month, day, hour, minute);
	
	format:g_big_string("\
		%s������� ��������� ��: " #cPROJECT "" #DATE_FORMAT "" #cWHITE ".\n\
		Onionland Tor Hidden Service: %s" #cWHITE ".\n\
		",
		g_big_string,
		hour, minute, day, month, year,
		site_data[index][s_is_darknet] ? ("" #cPROJECT "����������") : ("" #cGRAY "�� ����������")
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, " ", g_big_string, "�����", "");
}

ShowSitePageContent(playerid, index, E_SITE_DATA: name_page, E_SITE_DATA: s_desc_page)
{
	clean:<g_big_string>;
	
	format:g_big_string(
		"" #DEFAULT " > " #cPROJECT "%s" #cWHITE "\n\
		����������:\n\n\
		%s",
		site_data[index][name_page],
		site_data[index][s_desc_page]
	);
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", g_big_string, "�������", "");
}

ShowSiteFavorites(playerid)
{
	new server_tick = GetTickCount();
	
	if (GetPVarInt(playerid, "TimeMySQL:ShowFavSite") > server_tick)
	{
		return 0;
	}
	
	format:g_string("\
		SELECT sf_id, sf_address, sf_name \
		FROM " #__SFAVORITE " \
		WHERE sf_character_id = %i \
		ORDER BY sf_created_time ASC \
		LIMIT %i",
		GetCharacterId(playerid),
		MAX_SITE_FAVORITES
	);
	
	mysql_tquery(db, g_string, "OnSiteShowFavorites", "i", playerid);
	
	SetPVarInt(playerid, "TimeMySQL:ShowFavSite", server_tick + 1000);
	return 1;
}

function OnSiteShowFavorites(playerid)
{
	clean:<g_big_string>;
	
	new rows;

	cache_get_row_count(rows);
	
	SetPVarInt(playerid, "Site:CountFavorites", rows);
	
	strcat(g_big_string, "" #cGRAY "�������� ����\n" #cWHITE "");
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "sf_id", site_fav_select[playerid][i][sf_id]);
		cache_get_value_name(
			i, 
			"sf_address", 
			site_fav_select[playerid][i][sf_address], 
			MAX_SITE_ADDRESS 
		);
		
		cache_get_value_name(
			i, 
			"sf_name", 
			site_fav_select[playerid][i][sf_name], 
			MAX_SITE_NAME
		);
		
		format:g_big_string("%s %s\t%s",
			g_big_string,
			site_fav_select[playerid][i][sf_name],
			site_fav_select[playerid][i][sf_address]
		);
	}
	
	ShowPlayerDialog(playerid, D_SITE + 1, DIALOG_STYLE_LIST, " ", g_big_string, "�������", "�������");
	return 1;
}

ShowSiteFavoriteSelected(playerid, index)
{
	format:g_string("%s\n\
	" #cPROJECT "www.%s\n\
	" #cGRAY "�������\t" #cWHITE ">>\n\
	" #cGRAY "������� �� ��������\t" #cWHITE "X",
		site_fav_select[playerid][index][sf_name],
		site_fav_select[playerid][index][sf_address]
	);
	
	ShowPlayerDialog(playerid, D_SITE + 2, DIALOG_STYLE_TABLIST, "" #DEFAULT " ��������", g_string, "�������", "�����");
}

ShowSiteDialogMenuEdit(playerid)
{
	new str_address				[	MAX_SITE_ADDRESS	],
		str_template			[	32	],
		str_color				[	32	],
		str_name				[	MAX_SITE_NAME 	],
		str_slogan				[	32		],
		str_description			[	32		],
		str_action				[	32		],
		action = GetPVarInt(playerid, "Site:EditAction"),
		color = GetPVarInt(playerid, "Site:EditColor"),
		template = GetPVarInt(playerid, "Site:EditTemplate"),
		bool: is_completed = true;
		
	if (action == 0)
	{
		return;
	}
	
	/// Address
	clean:<g_string>;
	GetPVarString(playerid, "Site:EditDomain", g_string, sizeof g_string);
	if (isnull(g_string))
	{
		strcat(str_address, "" #cGRAY "�� �������");
		is_completed = false;
	}
	else
	{
		format:str_address("" #cPROJECT "%s", g_string);
	}
	
	if (template == 0)
	{
		strcat(str_template, "" #cGRAY "�� �������");
		is_completed = false;
	}
	else
	{
		format:str_template("" #cPROJECT "������ #%i", template) ;
	}
	
	/// Color
	if (color == INVALID_PARAM)
	{
		strcat(str_color, "" #cGRAY "�� �������");
		is_completed = false;
	}
	else
	{
		format:str_color("{%s}%s", 
			site_colors[color][sc_color],
			site_colors[color][sc_color_name] 
		);
	}
	
	/// Name
	clean:<g_string>;
	GetPVarString(playerid, "Site:EditName", g_string, sizeof g_string);
	if (isnull(g_string))
	{
		strcat(str_name, "" #cGRAY "�� �������");
		is_completed = false;
	}
	else
	{
		format:str_name("" #cPROJECT "%s", g_string);
	}
	
	/// Slogan
	clean:<g_string>;
	GetPVarString(playerid, "Site:EditSlogan", g_string, sizeof g_string);
	if (isnull(g_string))
	{
		strcat(str_slogan, "" #cGRAY "�� �������");
	}
	else
	{
		format:str_slogan("" #cPROJECT "%s", g_string);
	}
	
	/// Description
	clean:<g_string>;
	GetPVarString(playerid, "Site:EditDescription", g_string, sizeof g_string);
	if (isnull(g_string))
	{
		strcat(str_description, "" #cGRAY "�� �������");
		is_completed = false;
	}
	else 
	{
		strcat(str_description, "" #cPROJECT "�������");
	}
	
	if (is_completed)
	{
		if (action == SITE_ACTION_CREATE)
		{
			strcat(str_action, "" #cGRAY "������� ����");
		}
		else if (action == SITE_ACTION_EDIT)
		{
			strcat(str_action, "" #cGRAY "��������������� ����");
		}
	}
	
	format:g_big_string(" \
	   " #cWHITE "��� �������\t%s\n \
	   " #cWHITE "���� �������\t%s\n \
	   " #cWHITE "��������\t%s\n \
	   " #cWHITE "������\t%s\n \
	   " #cWHITE "��������\t%s\n \
	   " #cWHITE "��������� �������\n \
		%s",
		str_template,
		str_color,
		str_name,
		str_slogan,
		str_description,
		str_action
	);
	
	ShowPlayerDialog(playerid, D_SITE + 7, DIALOG_STYLE_TABLIST, str_address,
		g_big_string,
		"�������", "�����"
	);
}

ShowSiteDialogAddressEdit(playerid, bool: show_error = false)
{
	clean:<g_big_string>;
	clean:<g_string>;
	
	strcat(g_big_string, "" #DEFAULT " �����\n\n\
	����� - ��� ����� ���������� �����, ������� ����� ����������� ���������� ���,\n\
	�� �������� ������������ ������ ����� �� ��� ������.\n\
	����� ��������� �����, ��� ���������� ������� ��������� �������� ���.\n\n\
	" #cGRAY "����� ����� ������� � �������: example.com\n\
	��������� ������ ��� �����������:\n");
	
	for (new i; i < sizeof site_domains; i++)
	{
		if (i == sizeof site_domains - 1)
		{
			format:g_big_string("%s.%s;", g_big_string, site_domains[i]);
		}
		else
		{
			format:g_big_string("%s.%s, ", g_big_string, site_domains[i]);
		}
	}
	
	strcat(g_big_string, "\n\n" #cWHITE "������� ������� ����� �����:");
	
	if (show_error)
	{
		strcat(g_big_string, "\n\n" #cRED "����� �������� �������� ������� ��� �� ������� �������� �������� ���.");
	}
	
	ShowPlayerDialog(playerid, D_SITE + 6, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
}

ShowSiteDialogTemplates(playerid)
{
	clean:<g_big_string>;
	
	for (new i; i < sizeof site_templates; i++)
	{
		format:g_big_string("%s %s\t" #cWHITE "%s\n",
			g_big_string,
			site_templates[i][st_name],
			_: site_templates[i][st_darknet] == _: GetPVarInt(playerid, "Site:EditDarknet") ? ("[" #cGREEN "��������" #cWHITE "]") : ("[" #cRED "����������" #cWHITE "]")
		);
	}
	
	ShowPlayerDialog(playerid, D_SITE + 8, DIALOG_STYLE_TABLIST, " ", g_big_string, "�����", "�����");
}

ShowSiteDialogColors(playerid)
{
	clean:<g_big_string>;
	
	for (new i; i < sizeof site_colors; i++)
	{
		format:g_big_string("%s {%s}%s\n",
			g_big_string,
			site_colors[i][sc_color],
			site_colors[i][sc_color_name]
		);
	}
	
	ShowPlayerDialog(playerid, D_SITE + 9, DIALOG_STYLE_LIST, " ", g_big_string, "�����", "�����");
}

ShowSiteDialogDescription(playerid, bool: show_error = false)
{
	clean:<g_big_string>;
	clean:<g_string>;
	
	GetPVarString(playerid, "Site:EditDescription", g_string, sizeof g_string);
	
	format:g_big_string("" #DEFAULT " ��������\n\n\
		�������� ����� ��������� �� ������� ��������.\n\
		������� �����:\n\n\
		" #cGRAY "������� ��������:" #cWHITE "\n\
		%s\n\%s\ 
		%s����� ������ ��������� ������ ��������� ����� � �����.\n\
		����� ������ �� ������ ���� ������ 10 �������� � ������, ��� 128 ��������.", 
		g_string,
		isnull(g_string) ? ("") : ("\n"),
		show_error ? (cRED) : (cGRAY)
	);
	
	ShowPlayerDialog(playerid, D_SITE + 12, DIALOG_STYLE_INPUT, " ", g_big_string, "�����", "�����");
}

ShowSiteDialogPages(playerid)
{
	clean:<g_big_string>;
	
	new str_page_name		[	4 	][	64	],
		str_page_desc		[	4	][	64	];
	
	for (new i; i < 4; i++)
	{
		clean:<g_string>;
		format:g_small_string("Site:EditPageName[%i]", i);
		GetPVarString(playerid, g_small_string, g_string, sizeof g_string);
		if (isnull(g_string))
		{
			strcat(str_page_name[i], "" #cGRAY "�� �������");
		}
		else
		{
			format(str_page_name[i], MAX_SITE_PAGE_NAME, "" #cPROJECT "%s", g_string);
		}
		
		clean:<g_string>;
		format:g_small_string("Site:EditPageDesc[%i]", i);
		GetPVarString(playerid, g_small_string, g_string, sizeof g_string);
		if (isnull(g_string))
		{
			strcat(str_page_desc[i], "" #cGRAY "�� �������");
		}
		else
		{
			strcat(str_page_desc[i], "" #cPROJECT "�������");
		}
	}
	
	format:g_big_string(" \
		" #cPROJECT "#\t" #cPROJECT "��������\t" #cPROJECT "�������\n \
		�������� #1\t%s\t%s\n \
		�������� #2\t%s\t%s\n \
		�������� #3\t%s\t%s\n \
		�������� #4\t%s\t%s", 
		str_page_name[0], str_page_desc[0],
		str_page_name[1], str_page_desc[1],
		str_page_name[2], str_page_desc[2],
		str_page_name[3], str_page_desc[3]
	);
	
	ShowPlayerDialog(playerid, D_SITE + 14, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "�������", "�����");
}

ShowSiteDialogPageName(playerid, index, bool: is_error = false)
{
	clean:<g_string>;
	format:g_small_string("Site:EditPageName[%i]", index);
	GetPVarString(playerid, g_small_string, g_string, sizeof g_string);
	
	format:g_big_string("" #DEFAULT " ������������� ��������\n\n\
		�������� �������� ������������ � ���� ����� ��� �����. �� ������ ������� ������ �����\n\
		� ���� ����������, ��� ����� ������ �� ������� � ������� \"�����\".\n\
		������� �����:\n\n\
		" #cGRAY "������� ��������:\n\
		" #cWHITE "%s\n\n\
		%s����� ������ ��������� ������ ��������� ����� � �����.\n\
		����� ������ �� ������ ��������� ������ 16 ��������.",
		g_string,
		is_error ? (cRED) : (cGRAY)
	);
	
	ShowPlayerDialog(playerid, D_SITE + 16, DIALOG_STYLE_INPUT, " ",
		g_big_string,
		"�����", "�����"
	);
}

ShowSiteDialogPageDesc(playerid, index, bool: is_error = false)
{
	format:g_small_string("Site:EditPageDesc[%i]", index);
	GetPVarString(playerid, g_small_string, g_string, sizeof g_string);
	
	format:g_big_string("" #DEFAULT " �������������� ��������\n\n\
		�� ������������ ������� �� ��������.\n\ 
		" #HELP_TEXT_EDITOR "\n\
		������� �����:\n\n\
		" #cGRAY "������� �������:" #cWHITE "%s\n\n\
		%s������������ ���������� �������� � ������ �� ������ ��������� 128,\n\ 
		� ������ ����� �� ������ ���� ������ %i ��������.",
		g_string,
		is_error ? (cRED) : (cGRAY),
		MAX_SITE_PAGE_DESC
	);
	
	ShowPlayerDialog(playerid, D_SITE + 17, DIALOG_STYLE_INPUT, " ",
		g_big_string,
		"����", "��������"
	);
}