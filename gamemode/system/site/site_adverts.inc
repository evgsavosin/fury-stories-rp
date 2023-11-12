/*!
	@brief Объявления (GOG - advers.gog.com)
	@author Found (evg.savosin)
	@date 16.12.2016, update 12.03.2018
*/

Clear:advert_pvar(playerid)
{
	DeletePVar(playerid, "Site:AdvCat");
	DeletePVar(playerid, "Site:AdvType");
	DeletePVar(playerid, "Site:AdvPrice");
	DeletePVar(playerid, "Site:AdvText");
}

ShowSiteAdvertInformation(playerid, index, dialogid, btn_1[] = "Назад", btn_2[] = "")
{
	clean:<g_small_string>;
	clean:<g_big_string>;
	
	new month,
		day,
		hour,
		minute;
		
	gmtime(site_adv_select[playerid][index][ad_created_time], _, month, day, hour, minute, _);
	
	if (site_adv_select[playerid][index][ad_type] != 0)
	{
		if (site_adv_select[playerid][index][ad_price] != 0)
		{
			format:g_small_string("Цена: " #cGREEN "$%i" #cWHITE ".", site_adv_select[playerid][index][ad_price]);
		}
		else 
		{
			strcat(g_small_string, "Цена: " #cGRAY "Договорная" #cWHITE ".");
		}
	}
	
	format:g_big_string("" #DEFAULT " Информация об объявлении\n\n\
		Категория: " #cPROJECT "%s" #cWHITE "\n\
		Тип: " #cGRAY "%s" #cWHITE "\n\
		Содержимое:\n\
		" #cPROJECT "%s" #cWHITE "\n\n\
		%s\n\
		Дата размещения: " #cPROJECT "%02d/%02d %02d:%02d" #cWHITE ".\n\
		Телефон для связи: " #cPROJECT "%i" #cWHITE ".",
		site_adv_cat[site_adv_select[playerid][index][ad_category]],
		site_adv_select[playerid][index][ad_type] != 0 ? (site_adv_type[site_adv_select[playerid][index][ad_type]]) : ("Отсутствует"),
		site_adv_select[playerid][index][ad_text],
		g_small_string,
		month, day, hour, minute,
		site_adv_select[playerid][index][ad_number]
	);
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, " ", g_big_string, btn_1, btn_2);
	return 1;
}

ShowSiteAdvertList(playerid, dialogid = D_SITE + 31, page = 0, cat = INVALID_PARAM, type = INVALID_PARAM)
{
	if (dialogid == D_SITE + 31)
	{
		format:g_string("SELECT * FROM " #__ADVERTS " WHERE ad_character_id = %i LIMIT %i",
			GetCharacterId(playerid),
			MAX_ADVERTS
		);
	}
	else 
	{
		SetPVarInt(playerid, "Site:AdvPage", page);
		
		format:g_string("SELECT * \
			FROM " #__ADVERTS " \
			WHERE ad_type = %i AND ad_category = %i \
			LIMIT %i, %i",
			type, 
			cat,
			page * MAX_ADVERTS,
			MAX_ADVERTS
		);
	}
	
	mysql_tquery(db, g_string, "OnSiteShowAdvertList", "iii", playerid, dialogid, page);
}

function OnSiteShowAdvertList(playerid, dialogid, page)
{
	clean:<g_big_string>;
	
	new rows,
		i,
		title 			[		34		],
		price			[		16		];

	cache_get_row_count(rows);
	
	SetPVarInt(playerid, "Site:CountAdverts", rows);
	
	strcat(g_big_string, "" #cPROJECT "Заголовок\t" #cPROJECT "#\n");
	
	if (dialogid == D_SITE + 31)
	{
		strcat(g_big_string, "" #cGRAY "Разместить объявление\t\n" #cWHITE "");
	}
	
	for (; i < rows; i++)
	{
		if (i == MAX_ADVERTS)
		{
			break;
		}
		
		cache_get_value_name_int(i, "ad_id", site_adv_select[playerid][i][ad_id]);
		cache_get_value_name_int(i, "ad_number", site_adv_select[playerid][i][ad_number]);
		cache_get_value_name_int(i, "ad_created_time", site_adv_select[playerid][i][ad_created_time]);
		cache_get_value_name_int(i, "ad_price", site_adv_select[playerid][i][ad_price]);
		cache_get_value_name_int(i, "ad_category", site_adv_select[playerid][i][ad_category]);
		
		cache_get_value_name(
			i, 
			"ad_text", 
			site_adv_select[playerid][i][ad_text], 
			128 
		);
		
		strmid(title, site_adv_select[playerid][i][ad_text], 0, 30);
		strcat(title, "...");
		
		clean:<price>;
		if (site_adv_select[playerid][i][ad_price] != 0)
		{
			format:price("$%i", site_adv_select[playerid][i][ad_price]);
		}
		
		format:g_big_string("%s " #cGRAY "%s" #cWHITE " %s\t" #cGREEN "%s\n",
			g_big_string,
			site_adv_type[site_adv_select[playerid][i][ad_type]],
			title,
			price
		);
	}
	
	if (dialogid != D_SITE + 31)
	{
		if (rows == MAX_ADVERTS + 1)
		{
			strcat(g_big_string, "" #cGRAY "Вперед\t>>");
			site_adv_select[playerid][i++][ad_id] = ITEM_LIST_NEXT;
		}
		
		if (page != 0)
		{
			strcat(g_big_string, "\n" #cGRAY "Назад\t<<");
			site_adv_select[playerid][i][ad_id] = ITEM_LIST_BACK;
		}
	}
	
	if (rows == 0 && page == 0)
	{
		strcat(g_big_string, "" #cGRAY " По данному запросу не найдено объявлений\t");
		site_adv_select[playerid][i][ad_id] = ITEM_LIST_NONE;
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, "www.adverts.gog.com", g_big_string, "Выбрать", "Назад");
	return 1;
}

Create:advert_data(playerid)
{
	new index = GetInventoryDefaultPhone(playerid);
	if (index == INVALID_PARAM)
	{
		return 0;
	}
	
	new number = GetPhoneNumber(index);
	
	clean:<g_small_string>;
	GetPVarString(playerid, "Site:AdvText", g_small_string, sizeof g_small_string);
	
	format:g_string("\
		INSERT INTO " #__ADVERTS " \
			(ad_character_id, ad_number, ad_category, ad_type, ad_price, ad_text, ad_created_time) \
		VALUES \
			(%i, %i, %i, %i, %i, '%q', %i)",
		GetCharacterId(playerid),
		number,
		GetPVarInt(playerid, "Site:AdvCat"),
		GetPVarInt(playerid, "Site:AdvType"),
		GetPVarInt(playerid, "Site:AdvPrice"),
		g_small_string,
		gettime()
	);
	
	mysql_tquery(db, g_string);
	return 1;
}