/*!
	@brief Заголовок для сожителей
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

// Defines
#define GetLodgerPerm(%0,%1)			(lod_data[%0][lod_perm][%1])
#define IsPlayerLodger(%0)				(lod_data[%0][lod_house_index] != INVALID_PARAM ? 1 : 0)

#define	LODGER_SETTINGS				(	4	)

// Structures
enum 
{
	lod_perm_safe,
	lod_perm_renovation,
	lod_perm_inventory,
	lod_perm_garage
}	

enum E_LODGER_DATA
{	
	lod_house_index,
	lod_perm				[	LODGER_SETTINGS		],
};

enum E_LOD_SELECT_DATA
{
	ls_name					[	MAX_PLAYER_NAME		],
	ls_character_id,
	ls_perm					[	LODGER_SETTINGS 	],
};

new lod_data				[	MAX_PLAYERS		][	E_LODGER_DATA	],
	lodger_select			[	MAX_PLAYERS		][	MAX_LODGERS	][	E_LOD_SELECT_DATA	];

Clear:lod_data(playerid)
{
	lod_data[playerid][lod_house_index] = INVALID_PARAM;
	
	for (new i; i < LODGER_SETTINGS; i++)
	{
		lod_data[playerid][lod_perm][i] = 0;
	}
}

Clear:lod_select(playerid)
{
	for (new index; index < MAX_LODGERS; index++)
	{
		lodger_select[playerid][index][ls_name][0] = EOS; 
		lodger_select[playerid][index][ls_character_id] = 0; 
		
		for (new i; i < LODGER_SETTINGS; i++)
		{
			lodger_select[playerid][index][ls_perm][i] = 0;
		}
	}
}

Remove:lod_data(account_id, playerid = INVALID_PLAYER_ID)
{
	format:g_string("DELETE FROM " #__HLODGER " WHERE lod_character_id = %i LIMIT 1", 
		account_id
	);
	
	mysql_tquery(db, g_string);			
	
	if (playerid != INVALID_PLAYER_ID)
	{
		Clear:lod_data(playerid);

		if (IsPlayerRenovation(playerid))
		{
			SetRenovationMode(playerid, false);
		}
	}
}

Remove:all_lodger(house_id)
{
	format:g_string("DELETE FROM " #__HLODGER " WHERE lod_house_id = %i", 
		house_id
	);
				
	mysql_tquery(db, g_string);
}