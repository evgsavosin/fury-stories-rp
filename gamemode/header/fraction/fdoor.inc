/*!
	@brief Заголовок системы дверей для системы фракций
	@author Found (evg.savosin)
	@date 05.02.2020
*/

// Constants
const MAX_FRACTION_DOORS = 50;
const MAX_FRACTION_DOOR_POS = 6;

// Structures
enum
{
	DOOR_DEFAULT,
	DOOR_PRISON
};

enum E_FRACTION_DOOR_DATA
{
	fr_object_id,
	Float: fr_begin_pos	[MAX_FRACTION_DOOR_POS],
	Float: fr_end_pos	[MAX_FRACTION_DOOR_POS],
	bool: fr_status,
	Float: fr_radius,
	fr_type
};

new fraction_door		[MAX_FRACTIONS][MAX_FRACTION_DOORS][E_FRACTION_DOOR_DATA];

// Functions
Create:fraction_door(findex, object_id, Float: radius, Float: x1, Float: y1, Float: z1, Float: rx1, Float: ry1, Float: rz1, Float: x2, Float: y2, Float: z2, Float: rx2, Float: ry2, Float: rz2, type = DOOR_DEFAULT)
{	
	for (new i; i < MAX_FRACTION_DOORS; i++)
	{
		if (fraction_door[findex][i][fr_object_id] == 0)
		{
			fraction_door[findex][i][fr_object_id] = object_id;
			fraction_door[findex][i][fr_radius] = radius;
			fraction_door[findex][i][fr_status] = false;
			
			fraction_door[findex][i][fr_begin_pos][0] = x1;
			fraction_door[findex][i][fr_begin_pos][1] = y1;
			fraction_door[findex][i][fr_begin_pos][2] = z1;
			fraction_door[findex][i][fr_begin_pos][3] = rx1;
			fraction_door[findex][i][fr_begin_pos][4] = ry1;
			fraction_door[findex][i][fr_begin_pos][5] = rz1;
			
			fraction_door[findex][i][fr_end_pos][0] = x2;
			fraction_door[findex][i][fr_end_pos][1] = y2;
			fraction_door[findex][i][fr_end_pos][2] = z2;
			fraction_door[findex][i][fr_end_pos][3] = rx2;
			fraction_door[findex][i][fr_end_pos][4] = ry2;
			fraction_door[findex][i][fr_end_pos][5] = rz2;
			
			fraction_door[findex][i][fr_type] = type;
			break;
		}
	}
}