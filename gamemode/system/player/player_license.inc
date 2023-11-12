/*!
	@brief Система лицензий
	@author Found (evg.savosin)
	@date 26.04.2017
*/

Load:character_license(playerid)
{
	new rows;
	
	cache_get_row_count(rows);
	
	for (new i, E_LICENSES_INFO: type; i < rows; i++)
	{
		cache_get_value_name_int(i, "l_type_int", _: type);
		
		if (!(li_drive <= type <= li_weapon))
		{
			continue;
		}
		
		cache_get_value_name_int(i, "l_id", license_data[playerid][type][l_id]);
		cache_get_value_name_int(i, "l_gave_time", license_data[playerid][type][l_gave_time]);
		cache_get_value_name_int(i, "l_take_time", license_data[playerid][type][l_take_time]);
		
		cache_get_value_name(i, "l_gave_name", license_data[playerid][type][l_gave_name], MAX_PLAYER_NAME);
		cache_get_value_name(i, "l_take_name", license_data[playerid][type][l_take_name], MAX_PLAYER_NAME);
	}
}

GivePlayerLicense(playerid, E_LICENSES_INFO: type, name[] = "Centre of Licenses")
{
	new time = gettime();
	
	format:g_string("INSERT INTO " #__LICENSES " \
		(l_character_id, l_type, l_gave_date, l_gave_name) \
		VALUES \
		(%i, %i, NOW(), '%q')",
		GetCharacterId(playerid),
		_: type + 1,
		name
	);
	
	mysql_tquery(db, g_string, "OnPlayerLicenseCreate", "iisi", playerid, _: type, name, time);
}

function OnPlayerLicenseCreate(playerid, E_LICENSES_INFO: type, name[], time)
{
	license_data[playerid][type][l_id] = cache_insert_id();
	license_data[playerid][type][l_gave_time] = time;
	
	license_data[playerid][type][l_gave_name][0] = EOS;
	strcat(license_data[playerid][type][l_gave_name], name, MAX_PLAYER_NAME);
	
	return 1;
}