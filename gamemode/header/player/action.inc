/*!
	@brief Заголовок для системы описания (/action)
	@author Found (evg.savosin)
	@date 16.12.2016, update 16.01.2018
*/

// Defines
#define IsValidAction(%0,%1)		(character_action[%0][%1][c_text_id] != Text3D: INVALID_3DTEXT_ID)

// Constants
const MAX_ACTIONS = 3,
	  MAX_ACTION_TEXT = 128;

// Structures & Variables
enum E_CHARACTER_ACTION
{
	c_text							[MAX_ACTION_TEXT],
	Text3D: c_text_id
};

new character_action				[MAX_PLAYERS][MAX_ACTIONS][E_CHARACTER_ACTION];

// Functions
Clear:character_actions(playerid)
{
	for (new i; i < MAX_ACTIONS; i++)
	{
		character_action[playerid][i][c_text][0] = EOS;
		character_action[playerid][i][c_text_id] = Text3D: INVALID_3DTEXT_ID;
	}
}

Clear:character_action(playerid, index)
{
	character_action[playerid][index][c_text][0] = EOS;
	character_action[playerid][index][c_text_id] = Text3D: INVALID_3DTEXT_ID;
}

Create:action(playerid, text[MAX_ACTION_TEXT], Text3D: text_id)
{
	for (new i; i < MAX_ACTIONS; i++)
	{
		if (!IsValidAction(playerid, i))
		{
			character_action[playerid][i][c_text] = text;
			character_action[playerid][i][c_text_id] = text_id;
			break;
		}
	}
}