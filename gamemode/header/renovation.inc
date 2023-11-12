/*!
	@brief Заголовок системы реновации
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
*/

#define GetRenovationId(%0)				(ren_data[%0][ren_id])
#define GetRenovationIndex(%0)			(ren_data[%0][ren_index])
#define GetRenovationType(%0)			(ren_data[%0][ren_type])
#define GetRenovationMaxFurn(%0)		(ren_data[%0][ren_max_furn])

#define IsPlayerRenovation(%0)			(ren_data[%0][ren_type] != TYPE_REN_NONE && ren_data[%0][ren_index] != INVALID_PARAM)

enum 
{
	TYPE_MULTI = 0,
	TYPE_SINGLE
}

enum 
{
	TYPE_REN_NONE = 0,
	TYPE_REN_HOUSE,
	TYPE_REN_GARAGE,
	TYPE_REN_PREMISE
}

enum E_REN_DATA
{
	ren_id,
	ren_index,
	ren_type, 
	Text3D: ren_text			[	2 	],
	ren_max_furn,
}

new ren_data					[	MAX_PLAYERS	][	E_REN_DATA	];
	
	
Clear:ren_data(playerid)
{	
	ren_data[playerid][ren_max_furn] = 0;
	ren_data[playerid][ren_id] = 0;
	ren_data[playerid][ren_index] = INVALID_PARAM;
	ren_data[playerid][ren_type] = TYPE_REN_NONE;
	
	if (ren_data[playerid][ren_text][0] == ren_data[playerid][ren_text][1])
	{
		if (IsValidDynamic3DTextLabel(ren_data[playerid][ren_text][0]))
		{
			DestroyDynamic3DTextLabel(ren_data[playerid][ren_text][0]);
		}
	}
	else 
	{
		for (new Text3D: i = ren_data[playerid][ren_text][0]; i <= ren_data[playerid][ren_text][1]; i++)
		{
			if (IsValidDynamic3DTextLabel(i))
			{
				DestroyDynamic3DTextLabel(i);
			}
		}
	}
	
	ren_data[playerid][ren_text][1] =
	ren_data[playerid][ren_text][0] = Text3D: INVALID_3DTEXT_ID;
}

