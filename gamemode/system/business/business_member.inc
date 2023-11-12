/*!
	@brief Система участников бизнес компании
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

Load:character_business_member(playerid)
{
	format:g_string("SELECT * FROM " #__BMEMBERS " WHERE bm_character_id = %i LIMIT 1",
		GetCharacterId(playerid)
	);
	
	mysql_tquery(db, g_string, "OnBusinessMemberLoad", "i", playerid);
}

function OnBusinessMemberLoad(playerid)
{
	new rows,
		business_id;
	
	cache_get_row_count(rows);
	
	if (!rows)
	{
		return 1;
	}
	
	cache_get_value_name_int(0, "bm_perm_renovation", bmember_data[playerid][bm_perm][bm_perm_renovation]);
	cache_get_value_name_int(0, "bm_perm_lock", bmember_data[playerid][bm_perm][bm_perm_lock]);
	cache_get_value_name_int(0, "bm_perm_invite", bmember_data[playerid][bm_perm][bm_perm_invite]);
	cache_get_value_name_int(0, "bm_perm_uninvite", bmember_data[playerid][bm_perm][bm_perm_uninvite]);
	cache_get_value_name_int(0, "bm_perm_change", bmember_data[playerid][bm_perm][bm_perm_change]);
	cache_get_value_name_int(0, "bm_business_id", business_id);
	
	GiveBusinessMember(playerid, business_id);
	
	printf("[OnBusinessMemberLoad]: The Player %d become a member business %d.",
		GetCharacterId(playerid),
		business_id
	);
	
	
	return 1;
}

GiveBusinessMember(playerid, business_id)
{
	for (new i; i < sizeof business_data; i++)
	{
		if (business_data[i][b_id] != business_id)
		{
			continue;
		}
		
		bmember_data[playerid][bm_business_index] = i;
	}
}
