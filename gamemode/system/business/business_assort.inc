/*!
	@brief Операции для системы бизнесов
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/


Assort_OnPlayerClickTextDraw(playerid, Text: clickedid)
{
	if (clickedid == INVALID_TEXT_DRAW)
	{
		if (GetPVarInt(playerid, "BusinessAssort:States"))
		{
			new bindex = GetPVarInt(playerid, "Business:Select"),
				type = business_data[bindex][b_type],
				subtype = business_data[bindex][b_subtype];
		
			if (type == 0 && subtype == 2)
			{
				AssortmentAddForBusiness(playerid, bindex);
			}
			else
			{
				ShowBusinessSettingsAssortment(playerid, bindex);
			}
			
			ShowBusinessAddAssort(playerid, false);
		}
	}
	else if (clickedid == td_select_menu[1]) // next
	{
		UpdateBusinessAddAssort(playerid, GetPVarInt(playerid, "BusinessAssort:Index") + TD_SELECT_MENU_ARRAY);
	}
	else if (clickedid == td_select_menu[2]) // last 
	{
		UpdateBusinessAddAssort(playerid, GetPVarInt(playerid, "BusinessAssort:Index") - TD_SELECT_MENU_ARRAY);
	}
	
	return 1;
}

Assort_OnPlayerClickPTD(playerid, PlayerText: playertextid)
{
	if (!GetPVarInt(playerid, "BusinessAssort:States"))
	{
		return 1;
	}
		
	new index,
		itindex;
		
	for (new i; i < TD_SELECT_MENU_ARRAY; i++)
	{
		if (playertextid == ptd_select_menu[playerid][i])
		{
			index = g_td_select[playerid][i];
			itindex = GetItemIndexById(business_assort_list[index][bi_item_id]);
			
			SetPVarInt(playerid, "BusinessAssort:AddIndex", index);
			
			format:g_string("\
				" #DEFAULT " Добавить товар в ассортимент\n\n\
				Название: " #cPROJECT "%s" #cWHITE "\n\
				Начальная цена: " #cGREEN "$%i" #cWHITE "\n\
				Вы действительно желаете добавить данный товар в ассортимент?",
				item_list[itindex][it_name],
				business_assort_list[index][bi_cost]
			);
			
			ShowPlayerDialog(playerid, D_BUSINESS + 25, DIALOG_STYLE_MSGBOX, " ", g_string, "Добавить", "Закрыть");
			break;
		}
	}
	
	return 1;
}

AssortmentAddForBusiness(playerid, const index)
{
	new type = business_data[index][b_type],
		subtype = business_data[index][b_subtype];
		
	if (type == 0 && subtype == 2)
	{
		ShowPlayerDialog(playerid, D_BUSINESS + 24, DIALOG_STYLE_LIST, " ",
			" Одежда\n \
			  Шапки\n \
			  Банданы\n \
			  Кепки\n \
			  Очки\n \
			  Платки на лицо\n \
			  Шляпы\n \
			  Механические часы",
			  "Далее", "Назад"
		);
		
		return 1;
	}
	
	ShowBusinessAddAssort(playerid, true, INVALID_PARAM, business_data[index][b_type], business_data[index][b_subtype]);
	
	return 1;
}

ShowBusinessAddAssort(playerid, states, item_id = INVALID_PARAM, type = INVALID_PARAM, subtype = INVALID_PARAM)
{
	new begin_index,
		end_index;
	
	if (!ShowSelectMenu(playerid, states, "Add Products"))
	{
		SendClientMessage(playerid, C_WHITE, !ERROR_INTERFACE);
		return;
	}
	
	if (states)
	{	
		GetBusinessAddAssortEnds(item_id, type, subtype, begin_index, end_index);
		
		SetPVarInt(playerid, "BusinessAssort:Index", begin_index);
		SetPVarInt(playerid, "BusinessAssort:BeginIndex", begin_index);
		SetPVarInt(playerid, "BusinessAssort:EndIndex", end_index);
		
		SelectTextDraw(playerid, C_GRAY);
		
		UpdateBusinessAddAssort(playerid, begin_index);
	}
	else 
	{	
		for (new i; i < TD_SELECT_MENU_ARRAY; i++)
		{
			g_td_select[playerid][i] = INVALID_PARAM;
		}
		
		DeletePVar(playerid, "BusinessAssort:Index");
		DeletePVar(playerid, "BusinessAssort:BeginIndex");
		DeletePVar(playerid, "BusinessAssort:EndIndex");
	}
	
	SetPVarInt(playerid, "BusinessAssort:States", states);
}

UpdateBusinessAddAssort(playerid, index)
{	
	new begin_index = GetPVarInt(playerid, "BusinessAssort:BeginIndex"),
		end_index = GetPVarInt(playerid, "BusinessAssort:EndIndex"),
		itindex;
		
	if (!(begin_index <= index <= end_index))
	{
		return;
	}
	
	SetPVarInt(playerid, "BusinessAssort:Index", index);
	
	for (new i; i < TD_SELECT_MENU_ARRAY; i++)
	{
		if (i + index > end_index ||
		(itindex = GetItemIndexById(business_assort_list[i + index][bi_item_id])) == INVALID_ITEM_ID)
		{
			PlayerTextDrawHide(playerid, ptd_select_menu[playerid][i]);
			g_td_select[playerid][i] = INVALID_PARAM;
			continue;
		}
		
		PlayerTextDrawSetPreviewModel(
			playerid, 
			ptd_select_menu[playerid][i], 
			(item_list[itindex][it_model] <= 0 ? business_assort_list[i + index][bi_item_param] : item_list[itindex][it_model])
		);
		
		PlayerTextDrawSetPreviewRot(
			playerid, 
			ptd_select_menu[playerid][i], 
			item_list[itindex][it_draw_x], 
			item_list[itindex][it_draw_y], 
			item_list[itindex][it_draw_z], 
			item_list[itindex][it_draw_zoom] 
		);
		
		PlayerTextDrawShow(playerid, ptd_select_menu[playerid][i]);
		
		g_td_select[playerid][i] = i + index;
	}
}

GetBusinessAddAssortEnds(item_id = INVALID_PARAM, type, subtype, &begin_index, &end_index)
{
	for (new i; i < sizeof business_assort_list; i++)
	{
		if (business_assort_list[i][bi_type] != type 
		|| business_assort_list[i][bi_subtype] != subtype)
		{
			continue;
		}
		
		if (item_id != INVALID_PARAM 
		&& business_assort_list[i][bi_item_id] != item_id)
		{
			continue;
		}
		
		if (!begin_index)
		{
			begin_index = i;
		}
		
		end_index = i;
	}
}

GetFreeIndexForBusinessAssort(index)
{
	for (new i; i < MAX_BUSINESS_ASSORT; i++)
	{
		if (bassort_data[index][i][ba_item_id] == 0)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

GetBusinessAssortSimilar(bindex, item_id, item_param)
{
	for (new i; i < MAX_BUSINESS_ASSORT; i++)
	{
		if (bassort_data[bindex][i][ba_item_id] == item_id
		&& bassort_data[bindex][i][ba_item_param] == item_param)
		{
			return 1;
		}
	}
	
	return 0;
}

GetMinBusinessAssortPrice(type, subtype, item_id)
{
	for (new i; i < sizeof business_assort_list; i++)
	{
		if (business_assort_list[i][bi_type] == type 
		&& business_assort_list[i][bi_subtype] == subtype 
		&& business_assort_list[i][bi_item_id] == item_id)
		{
			return floatround(business_assort_list[i][bi_cost] - (business_assort_list[i][bi_cost] * 0.7));
		}
	}
	
	return 0;
}

GetMaxBusinessAssortPrice(type, subtype, item_id)
{
	for (new i; i < sizeof business_assort_list; i++)
	{
		if (business_assort_list[i][bi_type] == type 
		&& business_assort_list[i][bi_subtype] == subtype 
		&& business_assort_list[i][bi_item_id] == item_id)
		{
			return floatround(business_assort_list[i][bi_cost] + (business_assort_list[i][bi_cost] * 0.7));
		}
	}
	
	return 0;
}

GetAssortListIndex(type, subtype, item_id, item_param)
{
	for (new i; i < sizeof business_assort_list; i++)
	{
		if (business_assort_list[i][bi_type] == type
		&& business_assort_list[i][bi_subtype] == subtype
		&& business_assort_list[i][bi_item_id] == item_id
		&& business_assort_list[i][bi_item_param] == item_param)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}