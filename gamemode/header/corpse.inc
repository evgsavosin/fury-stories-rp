/*!
	@brief Заголовок системы смерти (Трупы)
	@author Found (evg.savosin)
	@date 27.04.2018
*/

// Defines
#define GetCorpseReasonText(%0)		(corpse_reason[corpse_data[%0][corp_reason]])

// Structures & Variables
enum 
{
	TYPE_CORP_NONE,
	TYPE_CORP_TEMP,
	TYPE_CORP_DB
}

enum 
{
	STATE_CORP_DEFAULT,
	STATE_CORP_BURY,
	STATE_CORP_COAL,
	STATE_CORP_ACID
}

enum 
{
	REASON_CORP_NONE,
	REASON_CORP_FIST,
	REASON_CORP_COLD,
	REASON_CORP_WEAPON,
}

enum E_CORPSE_DATA
{
	corp_id,
	corp_type,
	corp_state,
	corp_reason,
	corp_weapon_id,
	corp_character_name				[	MAX_PLAYER_NAME		],
	corp_skin,
	Float: corp_pos					[	4	],
	corp_world,
	corp_int,
	corp_attack_name_fist			[	MAX_PLAYER_NAME		],
	corp_attack_name_cold			[	MAX_PLAYER_NAME		],
	corp_camera_name				[	MAX_PLAYER_NAME		],
	corp_created_time,
	
	corp_fire_object,
	bool: corp_poured_gas,
	
	corp_object,
	corp_actor,
	Text3D: corp_text,
	
	bool: corp_used,
}

new const corpse_reason				[	][	] =
{
	{"Неизвестно"},
	{"Безоружное нападение"},
	{"Нападение холодным оружием"},
	{"Нападение огнестрельным оружием"}
}; 

new corpse_data						[	MAX_CORPSES		][	E_CORPSE_DATA	],
	corpse_camera_zones				[		2		],
	corpse_dirt_zone;


// Functions
Clear:corpse_data(index)
{
	/// Integer
	corpse_data[index][corp_created_time] =
	corpse_data[index][corp_id] =
	corpse_data[index][corp_skin] = 
	corpse_data[index][corp_reason] = 
	corpse_data[index][corp_int] = 
	corpse_data[index][corp_weapon_id] = 
	corpse_data[index][corp_state] = 
	corpse_data[index][corp_world] = 0;
	corpse_data[index][corp_type] = TYPE_CORP_NONE;
	corpse_data[index][corp_fire_object] =
	corpse_data[index][corp_object] = INVALID_OBJECT_ID;
	corpse_data[index][corp_actor] = INVALID_ACTOR_ID;
	corpse_data[index][corp_text] = Text3D: INVALID_3DTEXT_ID;
	
	/// Float 
	corpse_data[index][corp_pos][0] =
	corpse_data[index][corp_pos][1] =
	corpse_data[index][corp_pos][2] =
	corpse_data[index][corp_pos][3] = 0.0;
	
	/// String
	corpse_data[index][corp_attack_name_fist][0] =
	corpse_data[index][corp_attack_name_cold][0] =
	corpse_data[index][corp_camera_name][0] =
	corpse_data[index][corp_character_name][0] = EOS;
	
	/// Bool
	corpse_data[index][corp_used] = 
	corpse_data[index][corp_poured_gas] = false;
}

Update:corpse_int(index, column[], _: value, bool: is_pquery = false)
{
	if (corpse_data[index][corp_type] != TYPE_CORP_DB)
	{
		return 0;
	}
	
	clean:<g_string>;
	
	format:g_string("UPDATE " #__CORPSES " SET %s = %i WHERE corp_id = %i LIMIT 1",
		column,
		value,
		corpse_data[index][corp_id]
	);
	
	return !is_pquery ? mysql_tquery(db, g_string) : mysql_pquery(db, g_string);
}

Create:corpse_data(playerid, type)
{	
	new index = GetFreeIndexForCorpse();
	
	if (index == INVALID_PARAM)
	{
		index = GetCorpseOldTimeIndex();
		Remove:corpse_data(index);
	}
	else 
	{
		Clear:corpse_data(index);
	}

	corpse_data[index][corp_weapon_id] = character_data[playerid][c_attack_weapon_id];
	
	switch(corpse_data[index][corp_weapon_id])
	{
		case 0 :
		{
			corpse_data[index][corp_reason] = REASON_CORP_FIST; 
		}
		
		case 1 .. 15 :
		{
			corpse_data[index][corp_reason] = REASON_CORP_COLD; 
		}
		
		default :
		{
			corpse_data[index][corp_reason] = REASON_CORP_WEAPON;
		}
	}
	
	if (!isnull(character_data[playerid][c_attack_name_camera]))
	{
		strcat(corpse_data[index][corp_camera_name], character_data[playerid][c_attack_name_camera], MAX_PLAYER_NAME);
	}
	
	GetPlayerPos(playerid, 
		corpse_data[index][corp_pos][0],
		corpse_data[index][corp_pos][1],
		corpse_data[index][corp_pos][2]
	);
	
	GetPlayerFacingAngle(playerid, corpse_data[index][corp_pos][3]);
	
	corpse_data[index][corp_type] = type;
	corpse_data[index][corp_created_time] = gettime();
	corpse_data[index][corp_skin] = GetCharacterSkin(playerid);
	corpse_data[index][corp_int] = GetCharacterInt(playerid);
	corpse_data[index][corp_world] = GetPlayerVirtualWorld(playerid);
	
	strcat(corpse_data[index][corp_character_name], GetCharacterName(playerid), MAX_PLAYER_NAME);
	strcat(corpse_data[index][corp_attack_name_fist], character_data[playerid][c_attack_name_fist], MAX_PLAYER_NAME);
	strcat(corpse_data[index][corp_attack_name_cold], character_data[playerid][c_attack_name_cold], MAX_PLAYER_NAME);
	
	if (type == TYPE_CORP_DB)
	{
		format:g_big_string("INSERT INTO " #__CORPSES " \
			(\
				corp_state, \
				corp_reason, \
				corp_weapon_id, \
				corp_character_name, \
				corp_skin, \
				corp_pos_x, \
				corp_pos_y, \
				corp_pos_z, \
				corp_pos_angle, \
				corp_created_time, \
				corp_attack_name_fist, \
				corp_attack_name_cold, \
				corp_camera_name, \
				corp_poured_gas \
			) VALUES (\
				%i, \
				%i, \
				%i, \
				'%q', \
				%i, \
				%f, \
				%f, \
				%f, \
				%f, \
				%i, \
				'%q', \
				'%q', \
				'%q', \
				%i\
			)",
			STATE_CORP_DEFAULT,
			corpse_data[index][corp_reason],
			corpse_data[index][corp_weapon_id],
			corpse_data[index][corp_character_name],
			corpse_data[index][corp_skin],
			corpse_data[index][corp_pos][0],
			corpse_data[index][corp_pos][1],
			corpse_data[index][corp_pos][2],
			corpse_data[index][corp_pos][3],
			corpse_data[index][corp_created_time],
			corpse_data[index][corp_attack_name_fist],
			corpse_data[index][corp_attack_name_cold],
			corpse_data[index][corp_camera_name],
			corpse_data[index][corp_poured_gas]
		);
		
		mysql_tquery(db, g_big_string, "OnCorpseCreate", "i", index);
	}
	
	Create:corpse(index);
	
	// Clear 
	clean:<character_data[playerid][c_attack_name_cold]>;
	Update:character_string(playerid, "c_attack_name_cold", "");
	
	clean:<character_data[playerid][c_attack_name_fist]>;
	Update:character_string(playerid, "c_attack_name_fist", "");
}

function OnCorpseCreate(index)
{
	corpse_data[index][corp_id] = cache_insert_id();
	Create:corpse(index);
	printf("[OnCorpseCreate]: Corpse (ID:%i) has been created.", corpse_data[index][corp_id]);
	return 1;
}

Remove:corpse_data(index)
{
	Destroy:corpse(index, true);
	
	if (corpse_data[index][corp_type] != TYPE_CORP_DB)
	{
		format:g_string("DELETE FROM " #__CORPSES " WHERE corp_id = %i", 
			corpse_data[index][corp_id]
		);
		
		mysql_pquery(db, g_string);
	}
	
	Clear:corpse_data(index);
}