/*!
	@brief Контрольное меню
	@author Found (evg.savosin)
	@date 12.05.2019
*/

ShowAntiCheatMenu(playerid, action = AC_ITEM_LIST_BEGIN)
{
	if (!IsAntiCheatAdmin(playerid))
	{
		return;
	}
	
	clean:<g_big_string>;
	
	new count,
		page;
	
	if (action == AC_ITEM_LIST_BEGIN)
	{
		SetPVarInt(playerid, "AntiCheat:Page", 0);
		page = 0;
	}
	else if (action == AC_ITEM_LIST_CURRENT)
	{
		page = GetPVarInt(playerid, "AntiCheat:Page");
	}
	else if (action == AC_ITEM_LIST_NEXT)
	{
		GivePVarInt(playerid, "AntiCheat:Page", 1);
		page = GetPVarInt(playerid, "AntiCheat:Page");
	}
	else if (action == AC_ITEM_LIST_BACK)
	{
		TakePVarInt(playerid, "AntiCheat:Page", 1);
		page = GetPVarInt(playerid, "AntiCheat:Page");
	}
	
	format:g_big_string(#cPROJECT "Название античита\t" #cPROJECT "Статус\n");
	for (new i = page * AC_DIALOG_ITEM_LIST; i < MAX_ANTICHEAT_LIST; i++)
	{
		format:g_big_string("%s%s\t%s\n", 
			g_big_string, 
			GetAntiCheatData(i, ac_name), 
			!GetAntiCheatData(i, ac_is_nop) ? GetAntiCheatPunishText(i) : ("-")
		);
		
		g_dialog_select[playerid][count++] = i;
		
		if (count == AC_DIALOG_ITEM_LIST)
		{
			break;
		}
	}
	
	if (count == AC_DIALOG_ITEM_LIST)
	{
		strcat(g_big_string, "" #cGRAY "Вперед\t\t" #cWHITE ">>");
		g_dialog_select[playerid][count++] = AC_ITEM_LIST_NEXT;
	}
	
	if (page > 0)
	{
		strcat(g_big_string, "\n" #cGRAY "Назад\t" #cWHITE "<<");
		g_dialog_select[playerid][count] = AC_ITEM_LIST_BACK;
	}
	
	ShowPlayerDialog(playerid, AC_DIALOG, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "Далее", "Назад");
}



