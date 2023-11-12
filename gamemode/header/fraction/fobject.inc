/*!
	@brief Заголовок системы объектов для системы фракций
	@author Found (evg.savosin)
	@date 05.02.2020
*/

// Defines
#define GetFractionObject(%0,%1)			fraction_object[%0][%1][fr_object_id]
#define GetFractionText(%0,%1)				fraction_object[%0][%1][fr_text_id]

// Constants
const MAX_FRACTION_OBJECTS = 300;

const Float: MAX_FRACTION_OBJECT_EDIT_DIST = 130.0;

// Structures
enum E_FRACTION_OBJECT_DATA
{
	fr_object_id,
	Text3D: fr_text_id
};

new fraction_object		[MAX_FRACTIONS][MAX_FRACTION_OBJECTS][E_FRACTION_OBJECT_DATA];

// Functions
Clear:fraction_object_all()
{
	for (new j; j < MAX_FRACTIONS; j++)
	{
		for (new i; i < MAX_FRACTION_OBJECTS; i++)
		{
			Clear:fraction_object(j, i);
		}
	}
}

Clear:fraction_object(findex, index)
{
	fraction_object[findex][index][fr_object_id] = INVALID_OBJECT_ID;
	fraction_object[findex][index][fr_text_id] = Text3D: INVALID_3DTEXT_ID;
}

Create:fraction_object(playerid, findex, index, object_id)
{			
	new Float: x,
		Float: y,
		Float: z;
		
	GetPlayerPos(playerid, x, y, z);
	
	fraction_object[findex][index][fr_object_id] = CreateDynamicObject( 
		object_id, 
		x + 2.0,
		y,
		z,
		0.0,
		0.0,
		0.0,
		GetCharacterWorld(playerid),
		-1,
		-1,
		150
	);
	
	Streamer_UpdateEx(playerid, x, y, z);
}

Destroy:fraction_object(findex, index)
{
	if (IsValidDynamicObject(fraction_object[findex][index][fr_object_id]))
	{
		DestroyDynamicObject(fraction_object[findex][index][fr_object_id]);
	}

	if (IsValidDynamic3DTextLabel(fraction_object[findex][index][fr_text_id]))
	{
		DestroyDynamic3DTextLabel( 
			fraction_object[findex][index][fr_text_id]
		);
	}
	
	Clear:fraction_object(findex, index);
}