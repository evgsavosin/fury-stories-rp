/*!
	@brief Диалоги для системы трупов
	@author Found (evg.savosin)
	@date 26.04.2017
*/

Corpse_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	
	if (dialogid == D_CORPSE)
	{
		if (!response)
		{
			DeletePVar(playerid, "Corpse:Select");
			DeletePVar(playerid, "Player:ShovelExists");
			return 1;
		}
		
		new index = GetPVarInt(playerid, "Corpse:Select");
		
		if (listitem == 0)
		{
			if (corpse_data[index][corp_type] == STATE_CORP_BURY && !GetPVarInt(playerid, "Player:ShovelExists"))
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Для того, чтобы просмотреть информацию о закопанном трупе, необходимо использовать лопату.");
				return 1;
			}
			
			ShowCorpseInformation(playerid, index);
		}	
		else if (listitem == 1)
		{
			if (corpse_data[index][corp_state] != STATE_CORP_DEFAULT)
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACTION);
				return 1;
			}
			
			if (corpse_data[index][corp_used])
			{
				SendClientMessage(playerid, C_WHITE, !CORPSE_USED);
				return 1;
			}
			
			if (GetPVarInt(playerid, "Player:ShovelExists"))
			{
				if (!GetPVarInt(playerid, "Player:CorpseDirt"))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Для того, чтобы закопать труп, необходимо находиться за городом.");
					return 1;
				}
				
				TogglePlayerControllable(playerid, false);
				TogglePlayerAnimResetDisable(playerid, false);
				
				ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant_Loop", 4.1, 1, 1, 1, 0, 0, 1, true);
				SetPVarInt(playerid, "Player:CorpseDigs", true);
				SetPVarInt(playerid, "Player:CorpseDigsIndex", index);
				SetPVarInt(playerid, "Player:CorpseDigsTimer", 
					SetTimerEx("OnPlayerDigs", 1000 * 20, false, "ii", playerid, index)
				);
				
				corpse_data[index][corp_used] = true;
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы закапываете труп, подождите... " #cGRAY "(Время: 4 минуты | Отменить действие: /canceldigs)");
			}
			else 
			{
				ShowPlayerDialog(playerid, D_CORPSE + 2, DIALOG_STYLE_MSGBOX, " ",
					"" #DEFAULT " Убрать труп\n\n\
					Дальнейшее расследование станет недоступны.\n\
					Вы действительно хотите убрать труп?", 
					"Да", "Нет"
				);
			}
		}
	}
	else if (dialogid == D_CORPSE + 1)
	{
		new params					[	4	];
		valstr(params, (GetPVarInt(playerid, "Corpse:Select") + 1));
		cmd_corpse(playerid, params);
	}
	else if (dialogid == D_CORPSE + 2)
	{
		Remove:corpse_data(GetPVarInt(playerid, "Corpse:Select"));
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно убрали труп.");
	}
	
	return 1;
}

function OnPlayerDigs(playerid, index)
{
	DeletePVar(playerid, "Player:CorpseDigs");
	DeletePVar(playerid, "Player:CorpseDigsTimer");
	DeletePVar(playerid, "Player:CorpseDigsIndex");
	
	TogglePlayerControllable(playerid, true);
	TogglePlayerAnimResetDisable(playerid, true);
	
	ClearAnimationsEx(playerid);
	
	Recreate:corpse(index, STATE_CORP_BURY);
	corpse_data[index][corp_used] = false;
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно закопали труп.");
	return 1;
}