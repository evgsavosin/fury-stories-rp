/*!
	@brief Функция загрузки сайтов из базы данных
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

function OnSiteLoad()
{
	new rows;
		
	cache_get_row_count(rows);
	
	for (new i; i < rows; i++)
	{	
		/// Integer
		cache_get_value_name_int(i, "s_id", site_data[i][s_id]);
		cache_get_value_name_int(i, "s_character_id", site_data[i][s_character_id]);
		cache_get_value_name_int(i, "s_template", site_data[i][s_template]);
		cache_get_value_name_int(i, "s_color", site_data[i][s_color]);
		cache_get_value_name_int(i, "s_is_darknet", site_data[i][s_is_darknet]);
		cache_get_value_name_int(i, "s_rent_time", site_data[i][s_rent_time]);
		cache_get_value_name_int(i, "s_created_time", site_data[i][s_created_time]);
		
		/// String
		cache_get_value_name(i, "s_address", site_data[i][s_address], MAX_SITE_ADDRESS);
		cache_get_value_name(i, "s_name", site_data[i][s_name], MAX_SITE_NAME);
		cache_get_value_name(i, "s_slogan", site_data[i][s_slogan], 32);
		cache_get_value_name(i, "s_description", site_data[i][s_description], 128);
		
		cache_get_value_name(i, "s_name_page_1", site_data[i][s_name_page_1], MAX_SITE_PAGE_NAME);
		cache_get_value_name(i, "s_name_page_2", site_data[i][s_name_page_2], MAX_SITE_PAGE_NAME);
		cache_get_value_name(i, "s_name_page_3", site_data[i][s_name_page_3], MAX_SITE_PAGE_NAME);
		cache_get_value_name(i, "s_name_page_4", site_data[i][s_name_page_4], MAX_SITE_PAGE_NAME);
		
		cache_get_value_name(i, "s_desc_page_1", site_data[i][s_desc_page_1], MAX_SITE_PAGE_DESC);
		cache_get_value_name(i, "s_desc_page_2", site_data[i][s_desc_page_2], MAX_SITE_PAGE_DESC);
		cache_get_value_name(i, "s_desc_page_3", site_data[i][s_desc_page_3], MAX_SITE_PAGE_DESC);
		cache_get_value_name(i, "s_desc_page_4", site_data[i][s_desc_page_4], MAX_SITE_PAGE_DESC);
	}
	
	printf("[OnSiteLoad]: Sites have been loaded. All - %i.", rows);
	return 1;
}

Load:character_sites(playerid)
{
	for (new index; index < sizeof site_data; index++)
	{
		if (site_data[index][s_character_id] != GetCharacterId(playerid))
		{
			continue;
		}
		
		GiveSiteOwner(playerid, index);
		
		printf("[Load:character_sites]: Site [ID:%d] has been loaded for player %s.",
			site_data[index][s_id],
			GetCharacterName(playerid)
		);
	}
}