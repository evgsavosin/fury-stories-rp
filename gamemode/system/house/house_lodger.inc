/*!
	@brief Сожители для системы домов
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

Load:character_lodger(playerid)
{
	new rows,
		house_id;
	
	cache_get_row_count(rows);
	
	if (rows == 0)
	{
		return 1;
	}
	
	cache_get_value_name_int(0, "lod_perm_safe", lod_data[playerid][lod_perm][lod_perm_safe]);
	cache_get_value_name_int(0, "lod_perm_renovation", lod_data[playerid][lod_perm][lod_perm_renovation]);
	cache_get_value_name_int(0, "lod_perm_inventory", lod_data[playerid][lod_perm][lod_perm_inventory]);
	cache_get_value_name_int(0, "lod_perm_garage", lod_data[playerid][lod_perm][lod_perm_garage]);
	cache_get_value_name_int(0, "lod_house_id", house_id);
	
	GivePlayerLodger(playerid, house_id);
	
	printf("[LODGER]: The Player %d become a lodger house %d.",
		GetCharacterId(playerid),
		house_id
	);
	
	return 1;
}

ShowLodgerSelected(playerid, index)
{	
	clean:<g_big_string>;
	
	format:g_small_string("" #cGRAY "Выселить\t%s\n" #cWHITE "", 
		lodger_select[playerid][index][ls_name] 
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("Доступ к сейфу\t%s\n" #cWHITE "", 
		(lodger_select[playerid][index][ls_perm][lod_perm_safe]) ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет")
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("Доступ к режиму ремонта\t%s\n" #cWHITE "", 
		(lodger_select[playerid][index][ls_perm][lod_perm_renovation]) ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет")		
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("Доступ к инвентарю\t%s\n" #cWHITE "", 
		(lodger_select[playerid][index][ls_perm][lod_perm_inventory]) ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет")		
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("Доступ к гаражу\t%s" #cWHITE "", 
		(lodger_select[playerid][index][ls_perm][lod_perm_garage]) ? ("" #cPROJECT "Да") : ("" #cGRAY "Нет")		
	);
	
	strcat(g_big_string, g_small_string);
	
	ShowPlayerDialog(playerid, D_HOUSE + 7, DIALOG_STYLE_TABLIST, lodger_select[playerid][index][ls_name], g_big_string, "Выбрать", "Назад");
}

ShowLodgerList(playerid, index)
{
	if (!IsUserAllowQuery(playerid))
	{
		return;
	}
			
	format:g_string(
		"SELECT l.*, c.c_name \
		FROM " #__HLODGER " l, " #__CHARACTERS " c \
		WHERE \
			l.lod_character_id = c.c_id AND l.lod_house_id = %i LIMIT %d",
		house_data[index][h_id],
		MAX_LODGERS
	);
	
	mysql_tquery(db, g_string, "OnLodgerShowList", "i", playerid);
	
	SetUserAllowQuery(playerid, false);
}

function OnLodgerShowList(playerid)
{
	strglobalclear();
	
	new rows,
		name			[	MAX_PLAYER_NAME		];
	
	cache_get_row_count(rows);
	Clear:lod_select(playerid);
	
	strcat(g_big_string, "" #cGRAY "Подселить игрока" #cWHITE "\n");
	
	for (new i; i < rows; i++)
	{
		cache_get_value_name(i, "c_name", name, MAX_PLAYER_NAME);
		
		GetWithoutUnderscore(name, lodger_select[playerid][i][ls_name]);

		format:g_small_string(" %s\n", lodger_select[playerid][i][ls_name]);
		strcat(g_big_string, g_small_string);
		
		cache_get_value_name_int(i, "lod_character_id", lodger_select[playerid][i][ls_character_id]);
		cache_get_value_name_int(i, "lod_perm_safe", lodger_select[playerid][i][ls_perm][lod_perm_safe]);
		cache_get_value_name_int(i, "lod_perm_renovation", lodger_select[playerid][i][ls_perm][lod_perm_renovation]);
		cache_get_value_name_int(i, "lod_perm_garage", lodger_select[playerid][i][ls_perm][lod_perm_garage]);
		
	}
	
	ShowPlayerDialog(playerid, D_HOUSE + 4, DIALOG_STYLE_LIST, " ", g_big_string, "Выбрать", "Назад");
	
	SetUserAllowQuery(playerid, true);
	return 1;
}

GivePlayerLodger(playerid, house_id)
{
	for (new index; index < sizeof house_data; index++)
	{
		if (house_data[index][h_id] != house_id)
		{
			continue;
		}
		
		lod_data[playerid][lod_house_index] = index;
	}
}

Create:lod_data(playerid, index)
{
	Clear:lod_data(playerid);
	
	lod_data[playerid][lod_house_index] = index;
	
	format:g_string("INSERT INTO " #__HLODGER " \
	(lod_house_id, lod_character_id) VALUES (%i, %i)",
		GetHouseId(index),
		GetCharacterId(playerid)
	);
	
	mysql_tquery(db, g_string);
	return 1;
}