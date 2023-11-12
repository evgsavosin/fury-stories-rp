/*!
	@brief Файл с загрузкой участников криминальных систем
	@author Flavo
	@date 03.11.2019
*/

Load:character_crime_member(playerid)
{
	format:g_string("\
		SELECT crm.* \
		FROM " #__CRIMES_MEMBER " crm \
		JOIN " #__CHARACTERS " c ON c.c_id = crm.cr_character_id \
		WHERE crm.cr_character_id = %d",
		character_data[playerid][c_id]
	);

	mysql_tquery(db, g_string, "OnCrimeMemberLoad", "d", playerid);
}

function OnCrimeMemberLoad(playerid)
{
    new rows,
        crime_id;

    cache_get_row_count(rows);
	
	Clear:crmember_data(playerid);
	
    if (!rows)
    {	
        return 1;
    }
	
	cache_get_value_name_int(0, "cr_id", crmember_data[playerid][cr_id]);
	
	cache_get_value_name_int(0, "cr_leader", crmember_data[playerid][cr_leader]);
	
	cache_get_value_name_int(0, "cr_perm_invite", crmember_data[playerid][cr_perm][cr_perm_invite]);
	cache_get_value_name_int(0, "cr_perm_uninvite", crmember_data[playerid][cr_perm][cr_perm_uninvite]);
	cache_get_value_name_int(0, "cr_perm_buy", crmember_data[playerid][cr_perm][cr_perm_buy]);
	cache_get_value_name_int(0, "cr_perm_manage", crmember_data[playerid][cr_perm][cr_perm_manage]);
	
    cache_get_value_name_int(0, "cr_crime_id", crime_id);

    GiveCrimeMember(playerid, crime_id);

    printf("[OnCrimeMemberLoad]: The Player %d become a member crime %d.",
        GetCharacterId(playerid),
        crime_id
    );

    return 1;
}

GiveCrimeMember(playerid, crime_id)
{
    for (new i; i < sizeof crime_data; i++)
    {
        if (crime_data[i][cr_id] != crime_id)
        {
            continue;
        }

        crmember_data[playerid][cr_crime_index] = i;
    }
}

Create:crime_member(playerid, crime_index)
{
	format:g_string("\
		INSERT \
		INTO " #__CRIMES_MEMBER " (cr_crime_id, cr_character_id) \
		VALUES (%d, %d)",
		crime_data[crime_index][cr_id],
		character_data[playerid][c_id]
	);
	
	mysql_tquery(db, g_string);
}

Destroy:crmember_to_select(playerid, crime_member_index)
{
	format:g_string("\
		DELETE \
		FROM " #__CRIMES_MEMBER " \
		WHERE cr_crime_id = %d AND cr_character_id = %d",
		crmember_select[playerid][crime_member_index][cr_crime_id],
		crmember_select[playerid][crime_member_index][cr_character_id]
	);
	
	mysql_tquery(db, g_string);
}

Destroy:crmember_to_id(targetid)
{
	format:g_string("\
		DELETE \
		FROM " #__CRIMES_MEMBER " \
		WHERE cr_crime_id = %d AND cr_character_id = %d",
		crime_data[GetCrimeMember(targetid)][cr_id],
		character_data[targetid][c_id]
	);
	
	mysql_tquery(db, g_string);
}

Update:crmember_perm(crime_id, crm_character_id, const column[] = "", _: value)
{
	format:g_string("\
		UPDATE " #__CRIMES_MEMBER " \
		SET %s = %d \
		WHERE cr_crime_id = %d AND cr_character_id = %d",
		column,
		value,
		crime_id,
		crm_character_id
	);
	
	mysql_tquery(db, g_string);
}