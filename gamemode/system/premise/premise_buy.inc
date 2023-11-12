/*!
	@brief Система покупки
	@author Found (evg.savosin)
	@date 16.12.2016, update 01.04.2018
*/

// Public function
PrBuy_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{
		new world = GetPlayerVirtualWorld(playerid),
			index = GetPremiseIndexById(world);
	
		if (!IsPlayerInPremise(playerid, index, world) || !IsValidPremise(world))
		{
			return 1;
		}
		
		if (IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS,
		premise_data[index][pr_cash_pos][0],
		premise_data[index][pr_cash_pos][1],
		premise_data[index][pr_cash_pos][2]))
		{
			ShowPremiseAssort(playerid, true, index);
			return 0;
		}
	}
	
	return 1;
}

PrBuy_OnPlayerClickTextDraw(playerid, Text: clickedid)
{	
	if (!GetPVarInt(playerid, "PremiseAssort:States"))
	{
		return 1;
	}
	
	if (clickedid == INVALID_TEXT_DRAW)
	{
		ShowPremiseAssort(playerid, false);
	}
	else if (clickedid == td_select_menu[1]) // next
	{
		UpdatePremiseAssort(playerid, GetPVarInt(playerid, "PremiseAssort:Page") + 1);
	}
	else if (clickedid == td_select_menu[2]) // last 
	{
		UpdatePremiseAssort(playerid, GetPVarInt(playerid, "PremiseAssort:Page") - 1);
	}
	
	return 1;
}

PrBuy_OnPlayerClickPTD(playerid, PlayerText: playertextid)
{
	if (!GetPVarInt(playerid, "PremiseAssort:States"))
	{
		return 1;
	}
		
	new bindex = GetPVarInt(playerid, "Premise:BusinessSelect"),
		index,
		itindex;
		
	for (new i; i < TD_SELECT_MENU_ARRAY; i++)
	{
		if (playertextid == ptd_select_menu[playerid][i])
		{
			index = g_td_select[playerid][i];
			if ((itindex = GetItemIndexById(bassort_data[bindex][index][ba_item_id])) == INVALID_ITEM_ID)
			{
				continue;
			}
			
			SetPVarInt(playerid, "PremiseAssort:Index", index);
			
			format:g_string("\
				" #DEFAULT " Покупка\n\n\
				Название: " #cPROJECT "%s" #cWHITE "\n\
				Описание: " #cPROJECT "%s" #cWHITE "\n\
				Цена: " #cGREEN "$%i" #cWHITE "\n\n\
				Вы действительно желаете приобрести данный товар?",
				item_list[itindex][it_name],
				item_list[itindex][it_description],
				bassort_data[bindex][index][ba_cost]
			);
			
			ShowPlayerDialog(playerid, D_PREMISE + 15, DIALOG_STYLE_MSGBOX, " ", g_string, "Купить", "Отмена");
			break;
		}
	}
	
	return 1;
}

function PAY:buy_item(playerid, status)
{
	new prindex = GetPVarInt(playerid, "Premise:BuySelect"),
		bindex = GetPVarInt(playerid, "Premise:BusinessSelect"),
		index = GetPVarInt(playerid, "PremiseAssort:Index"),
		itindex = GetItemIndexById(bassort_data[bindex][index][ba_item_id]);
	
	if (!IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS,
	premise_data[prindex][pr_cash_pos][0],
	premise_data[prindex][pr_cash_pos][1],
	premise_data[prindex][pr_cash_pos][2]))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы должны находиться на месте покупки.");
		return 1;
	}
		
	if (!status)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
		return 1;
	}
	
	GivePremiseAssortStock(prindex, -GetPVarInt(playerid, "PremiseAssort:Count"));
	
	GiveInventoryItem(playerid, bassort_data[bindex][index][ba_item_id], bassort_data[bindex][index][ba_item_param]);
	
	pformat:("" #SUCCESS " Вы успешно приобрели предмет " #cPROJECT "%s" #cWHITE ".",
		item_list[itindex][it_name]
	);
	psend:(playerid, C_WHITE);
	return 1;
}

// Other function 
ShowPremiseAssort(playerid, states, index = INVALID_PARAM)
{
	if (!ShowSelectMenu(playerid, states, "Shop"))
	{
		SendClientMessage(playerid, C_WHITE, !ERROR_INTERFACE);
		return;
	}
	
	if (states)
	{	
		SetPVarInt(playerid, "PremiseAssort:Page", 0);
		SetPVarInt(playerid, "Premise:BuySelect", index);
		SetPVarInt(playerid, "Premise:BusinessSelect", GetBusinessIndexById(premise_data[index][pr_business_id]));
		
		SelectTextDraw(playerid, C_GRAY);
		
		UpdatePremiseAssort(playerid, 0);
	}
	else 
	{	
		for (new i; i < TD_SELECT_MENU_ARRAY; i++)
		{
			g_td_select[playerid][i] = INVALID_PARAM;
		}
		
		DeletePVar(playerid, "PremiseAssort:Page");
		DeletePVar(playerid, "PremiseAssort:Count");
		DeletePVar(playerid, "Premise:BuySelect");
	}
	
	SetPVarInt(playerid, "PremiseAssort:States", states);
}

UpdatePremiseAssort(playerid, page)
{	
	new bindex = GetPVarInt(playerid, "Premise:BusinessSelect");
		
	if (!(0 <= page <= GetPremiseAssortMaxPage(bindex)))
	{
		return;
	}
	
	new itindex,
		count;
	
	SetPVarInt(playerid, "PremiseAssort:Page", page);
	
	for (new i; i < TD_SELECT_MENU_ARRAY; i++)
	{	
		PlayerTextDrawHide(playerid, ptd_select_menu[playerid][i]);
		g_td_select[playerid][i] = INVALID_PARAM;
	}
	
	for (new i, j; i < MAX_BUSINESS_ASSORT; i++)
	{
		if (count == TD_SELECT_MENU_ARRAY)
		{
			break;
		}
		
		if (bassort_data[bindex][i][ba_item_id] == 0)
		{
			continue;
		}
		
		if ((itindex = GetItemIndexById(bassort_data[bindex][i][ba_item_id])) == INVALID_ITEM_ID)
		{
			continue;
		}
		
		if (j != (page * TD_SELECT_MENU_ARRAY))
		{
			j++;
			continue;
		}
		
		PlayerTextDrawSetPreviewModel(
			playerid, 
			ptd_select_menu[playerid][count], 
			(item_list[itindex][it_model] <= 0 ? bassort_data[bindex][i][ba_item_param] : item_list[itindex][it_model])
		);
		
		PlayerTextDrawSetPreviewRot(
			playerid, 
			ptd_select_menu[playerid][count], 
			item_list[itindex][it_draw_x], 
			item_list[itindex][it_draw_y], 
			item_list[itindex][it_draw_z], 
			item_list[itindex][it_draw_zoom]
		);
		
		PlayerTextDrawShow(playerid, ptd_select_menu[playerid][count]);
		
		g_td_select[playerid][count] = i;
		
		count++;
	}
}

GetPremiseAssortMaxPage(bindex)
{
	new count;
	
	for (new i; i < MAX_BUSINESS_ASSORT; i++)
	{
		if (bassort_data[bindex][i][ba_item_id] == 0)
		{
			continue;
		}
		
		count++;
	}
	
	return floatround((count / TD_SELECT_MENU_ARRAY));
}