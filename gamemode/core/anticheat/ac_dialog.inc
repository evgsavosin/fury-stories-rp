/*!
	@brief Диалог
	@author Found (evg.savosin)
	@date 12.05.2019
*/

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{	
	if (dialogid == AC_DIALOG)
	{
		if (!response)
		{
			cmd_amenu(playerid);
			return 1;
		}
		
		new index = g_dialog_select[playerid][listitem];
		
		if (index == AC_ITEM_LIST_BACK || index == AC_ITEM_LIST_NEXT)
		{
			ShowAntiCheatMenu(playerid, index);
			return 1;
		}
		
		// Если не NOP
		if (!GetAntiCheatData(index, ac_is_nop))
		{
			new type = (GetAntiCheatData(index, ac_type_punish) + 1);

			type = (type >= MAX_ANTICHEAT_PUNISH_LIST) ? 0 : type;
			
			SetAntiCheatData(index, ac_type_punish, type);
		}
		
		ShowAntiCheatMenu(playerid, ITEM_LIST_CURRENT);
	}
	
	#if defined AC_OnDialogResponse
		return AC_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnDialogResponse
    #undef OnDialogResponse
#else
    #define _ALS_OnDialogResponse
#endif

#define	OnDialogResponse	AC_OnDialogResponse
#if defined AC_OnDialogResponse
	forward AC_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif