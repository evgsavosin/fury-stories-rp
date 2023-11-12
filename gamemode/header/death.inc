/*!
	@brief Заголовок системы смерти
	@author Found (evg.savosin)
	@date 27.04.2018
*/

// Structures & Variables
enum 
{
	TYPE_DEATH_NONE,
	TYPE_DEATH_INJURED,
	TYPE_DEATH_DIED
}

enum E_DEATH_DATA
{
	d_timer,
	Text3D: d_text
}

enum E_DAMAGE_DATA
{
	dm_body_part,
	dm_weapon_id,
	dm_time,
	dm_name					[	MAX_PLAYER_NAME		],
	Float: dm_amount,
	bool: dm_is_camera
}

new death_data				[	MAX_PLAYERS		][	E_DEATH_DATA	],
	damage_data				[	MAX_PLAYERS		][	MAX_DAMAGES		][	E_DAMAGE_DATA	];
	
	
// Function
Clear:death_data(playerid, bool: is_help = false)
{
	death_data[playerid][d_timer] = 0;
	death_data[playerid][d_text] = Text3D: INVALID_3DTEXT_ID;
	
	if (!is_help)
	{
		for (new i; i < MAX_DAMAGES; i++)
		{
			damage_data[playerid][i][dm_name][0] = EOS;
			
			damage_data[playerid][i][dm_body_part] =
			damage_data[playerid][i][dm_weapon_id] =
			damage_data[playerid][i][dm_time] = 0;
			
			damage_data[playerid][i][dm_amount] = 0.0;
			
			damage_data[playerid][i][dm_is_camera] = false;
		}
	}
}