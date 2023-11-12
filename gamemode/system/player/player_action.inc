/*!
	@brief Описание местности персонажем
	@author Found (evg.savosin)
	@date 26.04.2017
*/

ShowPlayerActionList(playerid, const dialogid, targetid = INVALID_PARAM)
{
	new count;
	
	if (targetid == INVALID_PARAM)
	{
		clean:<g_string>;
		strcat(g_string, #cGRAY "Добавить описание\n");
	}
	
	for (new i; i < MAX_ACTIONS; i++)
	{
		if (character_action[playerid][i][c_text_id] == Text3D: INVALID_3DTEXT_ID)
		{
			continue;
		}
		
		format:g_string("%s %s\n", g_string, character_action[playerid][i][c_text]);
		g_dialog_select[playerid][count++] = i;
	}
	
	new title	[MAX_PLAYER_NAME];
	
	if (targetid != INVALID_PARAM)
	{
		strcat(title, GetPlayerCurrentName(playerid));
	}
	else 
	{
		strcat(title, " ");
	}
	
	ShowPlayerDialog(targetid == INVALID_PARAM ? playerid : targetid, dialogid, DIALOG_STYLE_LIST, title, g_string, "Выбрать", "Закрыть");
}