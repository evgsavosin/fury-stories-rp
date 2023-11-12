/*!
	@brief Заголовок для системы 911
	@author Found (evg.savosin)
	@date 05.02.2020
*/

// Constants
const MAX_FRACTION_CALLS = 50;

const MAX_FRACTION_CALL_TEXT = 32,
	  MAX_FRACTION_CALL_ZONE = 64,
	  MAX_FRACTION_CALL_POS = 3;

// Structures
enum E_FRACTION_CALL_DATA
{
	c_exists,
	c_name			[MAX_PLAYER_NAME],
	c_player_id,
	c_text			[MAX_FRACTION_CALL_TEXT],
	c_zone			[MAX_FRACTION_CALL_ZONE],
	Float: c_pos	[MAX_FRACTION_CALL_POS],
	c_phone
};

new fraction_call	[MAX_FRACTION_CALLS][E_FRACTION_CALL_DATA];

// Functions
Clear:fraction_call(index)
{
	fraction_call[index][c_exists] = false;
	fraction_call[index][c_zone][0] = 
	fraction_call[index][c_text][0] = 
	fraction_call[index][c_name][0] = EOS;
	fraction_call[index][c_player_id] = INVALID_PLAYER_ID;
	
	fraction_call[index][c_pos][0] =
	fraction_call[index][c_pos][1] =
	fraction_call[index][c_pos][2] = 0.0;
}

Create:fraction_call(index, playerid, text[])
{
	fraction_call[index][c_exists] = true;
	
	clean:<fraction_call[index][c_name]>;
	strcat(fraction_call[index][c_name], GetPlayerCurrentName(playerid), MAX_PLAYER_NAME);
	
	clean:<fraction_call[index][c_text]>;
	strcat(fraction_call[index][c_text], text, MAX_FRACTION_CALL_TEXT);
	
	new iindex = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_PHONE, _, true),
		pindex = GetPhoneIndexBySlot(playerid, iindex, TYPE_INV_PLAYER);
		
	fraction_call[index][c_phone] = GetPhoneNumber(pindex);
	
	new Float: x,
		Float: y,
		Float: z;
	
	GetPlayerPos(playerid, x, y, z);
	
	fraction_call[index][c_pos][0] = x;
	fraction_call[index][c_pos][1] = y;
	fraction_call[index][c_pos][2] = z;
	
	GetZoneName(
		x, 
		y, 
		fraction_call[index][c_zone], 
		MAX_FRACTION_CALL_ZONE
	);
}