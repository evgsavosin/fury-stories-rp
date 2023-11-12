/*!
	@brief Должности системы бизнесов
	@author Found (evg.savosin)
	@date 23.04.2018
*/

// Defines
#define GetBusinessMemberPerm(%0,%1)			(bmember_data[%0][bm_perm][%1])
#define GetBusinessMember(%0)					(bmember_data[%0][bm_business_index])
#define IsBusinessMember(%0)					(bmember_data[%0][bm_business_index] == INVALID_PARAM ? (IsBusinessOwner(%0) ? 1 : 0) : 1)

// Structures
enum 
{
	TYPE_BUSINESS_MEMBER,
	TYPE_BUSINESS_OWNER
};

// Привилегии 
enum
{
	bm_perm_renovation,
	bm_perm_lock,
	bm_perm_invite,
	bm_perm_uninvite,
	bm_perm_change,
	
	BMEMBER_SETTINGS
};

enum E_BUSINESS_MEMBER
{
	bm_business_index,
	bm_perm						[BMEMBER_SETTINGS],
};
	
enum E_BMEMBER_SELECT_DATA
{
	bs_name						[MAX_PLAYER_NAME],
	bs_character_id,
	bs_perm						[BMEMBER_SETTINGS],
};

new bmember_data				[	MAX_PLAYERS			][	E_BUSINESS_MEMBER		],
	bmember_select				[	MAX_PLAYERS			][	MAX_BUSINESS_ITEM_LIST	][	E_BMEMBER_SELECT_DATA	];
	
Clear:bmember_data(playerid)
{
	bmember_data[playerid][bm_business_index] = INVALID_PARAM;
	
	bmember_data[playerid][bm_perm][bm_perm_renovation] = 
	bmember_data[playerid][bm_perm][bm_perm_lock] = 
	bmember_data[playerid][bm_perm][bm_perm_invite] = 
	bmember_data[playerid][bm_perm][bm_perm_uninvite] = 
	bmember_data[playerid][bm_perm][bm_perm_change] = 0; 
}

Clear:bmember_select(playerid)
{
	for (new i; i < MAX_BUSINESS_ITEM_LIST; i++)
	{
		bmember_select[playerid][i][bs_name][0] = EOS; 
		bmember_select[playerid][i][bs_character_id] = 0; 
		
		for (new j; j < BMEMBER_SETTINGS; j++)
		{
			bmember_select[playerid][i][bs_perm][j] = 0;
		}
	}
}

Create:bmember_data(playerid, index)
{
	Clear:bmember_data(playerid);
	
	bmember_data[playerid][bm_business_index] = index;
	
	format:g_string("INSERT INTO " #__BMEMBERS " \
	(bm_business_id, bm_character_id) VALUES (%i, %i)",
		GetBusinessId(index),
		GetCharacterId(playerid)
	);
	
	mysql_tquery(db, g_string);
}

Update:bmember_data(playerid, index = INVALID_PARAM)
{
	if (index != INVALID_PARAM)
	{
		format:g_string(
			"UPDATE " #__BMEMBERS " \
			SET \
				bm_perm_renovation = %i, \
				bm_perm_lock = %i, \ 
				bm_perm_invite = %i, \
				bm_perm_uninvite = %i, \
				bm_perm_change = %i \
			WHERE \
				bm_character_id = %i \
			LIMIT 1",
			bmember_select[playerid][index][bs_perm][bm_perm_renovation],
			bmember_select[playerid][index][bs_perm][bm_perm_lock],
			bmember_select[playerid][index][bs_perm][bm_perm_invite],
			bmember_select[playerid][index][bs_perm][bm_perm_uninvite],
			bmember_select[playerid][index][bs_perm][bm_perm_change],
			bmember_select[playerid][index][bs_character_id]
		);
	}
	else 
	{
		format:g_string(
			"UPDATE " #__BMEMBERS " \
			SET \
				bm_perm_renovation = %i, \
				bm_perm_lock = %i, \ 
				bm_perm_invite = %i, \
				bm_perm_uninvite = %i, \
				bm_perm_change = %i \
			WHERE \
				bm_character_id = %i \
			LIMIT 1",
			bmember_data[playerid][bm_perm][bm_perm_renovation],
			bmember_data[playerid][bm_perm][bm_perm_lock],
			bmember_data[playerid][bm_perm][bm_perm_invite],
			bmember_data[playerid][bm_perm][bm_perm_uninvite],
			bmember_data[playerid][bm_perm][bm_perm_change],
			GetCharacterId(playerid)
		);
	}

	mysql_pquery(db, g_string);
}

Remove:bmember_data(account_id = INVALID_PARAM, playerid)
{
	if (account_id != INVALID_PARAM)
	{
		format:g_string("DELETE FROM " #__BMEMBERS " WHERE bm_character_id = %i LIMIT 1", 
			account_id
		);
		
		mysql_pquery(db, g_string);
	}
	
	if (playerid != INVALID_PLAYER_ID)
	{
		Clear:bmember_data(playerid);
		
		if (IsPlayerRenovation(playerid))
		{
			SetRenovationMode(playerid, false);
		}
	}
}