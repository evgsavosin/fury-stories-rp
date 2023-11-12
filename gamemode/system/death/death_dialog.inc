/*!
	@brief Диалоги для системы смерти
	@author Found (evg.savosin)
	@date 26.04.2017
*/

Death_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	#pragma unused listitem
	
	if (dialogid == D_DEATH)
	{
		if (response)
		{	
			KillPlayer(playerid);
		}
	}
	else if (dialogid == D_DEATH + 1)
	{
		if (response)
		{
			KillPlayerCharacter(playerid, GetPVarInt(playerid, "Death:CKTargetId"));
		}
		else 
		{
			SendClientMessage(playerid, C_WHITE, !HELP_TRADE);
		}
	}

	return 1;
}