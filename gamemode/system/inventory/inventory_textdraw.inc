/*!
	@brief Инвентарь на текстдравах
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

/*!
	Открываем инвентарь на текстдравах
	@param [in] playerid Игрок
	@param [bool] states Показать/Скрыть
	@param [in] additional_type Тип овнера
	@param [string] additional_name Имя овнера
	@param [in] additional_id ID овнера
	@param [in] additional_slots Количество слотов
	@param [bool] cancel_select Отмена селекта текстдравов
*/

ShowInventoryTextdraw(playerid, bool: states, additional_type = TYPE_INV_PLAYER, additional_name[] = "", 
additional_id = INVALID_PARAM, additional_slots = MAX_INVENTORY_SLOTS, bool: cancel_select = true)
{
	new i = 0;
	
	additional_id = (additional_id == INVALID_PARAM) ? playerid : additional_id;
	
	if (states)
	{
		if (additional_type != TYPE_INV_PLAYER)
		{
			PlayerTextDrawSetString(playerid, td_inv_header[playerid], additional_name);
			PlayerTextDrawShow(playerid, td_inv_header[playerid]);
			TextDrawShowForPlayer(playerid, td_inventory[1]);
		}
		
		PlayerTextDrawShow(playerid, td_inv_button[playerid]);
		
		while (i < sizeof td_inventory)
		{
			if (i != 1 && i != 9 && i != 10)
			{
				TextDrawShowForPlayer(playerid, td_inventory[i]);
			}
			
			if (i < TD_INVENTORY_SLOTS)
			{
				if (additional_type != TYPE_INV_PLAYER && i < additional_slots)
				{
					UpdateInventorySelect(playerid, td_inv_addslot[playerid][i], false, i, additional_id, additional_type);
					UpdateInventorySlotModel(playerid, i, additional_type, additional_id);
				}
			
				UpdateInventorySelect(playerid, td_inv_slot[playerid][i], false, i);
				UpdateInventorySlotModel(playerid, i);
			}
			
			i++;
		}
		
		SelectTextDraw(playerid, C_GRAY);
	}
	else 
	{
		PlayerTextDrawHide(playerid, td_inv_header[playerid]);
		PlayerTextDrawHide(playerid, td_inv_button[playerid]);
		
		while (i < sizeof td_inventory)
		{
			TextDrawHideForPlayer(playerid, td_inventory[i]);
			
			if (i < TD_INVENTORY_SLOTS)
			{
				PlayerTextDrawHide(playerid, td_inv_addslot[playerid][i]);
				PlayerTextDrawHide(playerid, td_inv_slot[playerid][i]);
			}
			
			i++;
		}
		
		if (cancel_select)
		{
			CancelSelectTextDraw(playerid);
		}
	}
	
	inventory_td_select[playerid] = INVALID_PTD;
	SetPVarInt(playerid, "Inventory:Select", INVALID_PARAM);
	SetPVarInt(playerid, "Inventory:AddSelect", INVALID_PARAM);
	SetPVarInt(playerid, !"Inventory:States", states);
	return 1;
}

ShowAdditionalTextdraw(playerid, states, additional_type = TYPE_INV_PLAYER, additional_name[] = "", id = INVALID_PARAM, additional_slots = MAX_INVENTORY_SLOTS)
{
	new i = 0;
		
	if (states)
	{
		PlayerTextDrawSetString(playerid, td_inv_header[playerid], additional_name);
		PlayerTextDrawShow(playerid, td_inv_header[playerid]);
		TextDrawShowForPlayer(playerid, td_inventory[1]);
		
		while (i < additional_slots)
		{
			UpdateInventorySelect(playerid, td_inv_addslot[playerid][i], false, i, id, additional_type);
			UpdateInventorySlotModel(playerid, i, additional_type, id);
			i++;
		}
	}
	else 
	{
		while (i < additional_slots)
		{
			PlayerTextDrawHide(playerid, td_inv_addslot[playerid][i]);
			i++;
		}
		
		TextDrawHideForPlayer(playerid, td_inventory[1]);
		PlayerTextDrawHide(playerid, td_inv_header[playerid]);
		TextDrawHideForPlayer(playerid, td_inventory[9]);
		TextDrawHideForPlayer(playerid, td_inventory[10]);
	}
	
	return 1;
}

GetBackgroundSlot(type)
{
	switch(type)
	{
		case ACTIVE_SLOT :
		{
			return C_PROJECT;
		}
		
		case WEAPON_BIG_SLOT :
		{
			return C_DARKRED;
		}
	}
	
	return 70;
}

SetTextInventoryButton(playerid, selectable, type_slot, slot, id = INVALID_PARAM, type = INVALID_PARAM)
{
	id = (id == INVALID_PARAM) ? playerid : id;
	type = (type == INVALID_PARAM) ? TYPE_INV_PLAYER : type;
	
	new item = GetItemIndexById(GetInventoryEnumItem(id, slot, type, inv_item_id));

	if (selectable)
	{
		if (type_slot == ACTIVE_SLOT)
		{	
			if (type == TYPE_INV_PLAYER && item_list[item][it_type] == INV_BAG)
			{
				PlayerTextDrawSetString(playerid, td_inv_button[playerid], "Edit");
			}
			else 
			{
				PlayerTextDrawSetString(playerid, td_inv_button[playerid], "Unuse");
			}
		}
		else if (type_slot == DEFAULT_SLOT || type_slot == WEAPON_BIG_SLOT)
		{
			if (type == TYPE_INV_VEHICLE)
			{
				PlayerTextDrawSetString(playerid, td_inv_button[playerid], "(Un)Att");
			}
			else 
			{
				PlayerTextDrawSetString(playerid, td_inv_button[playerid], "Use");
			}
		}
	}
	else 
	{
		PlayerTextDrawSetString(playerid, td_inv_button[playerid], "(Un)Use");
	}
}

UpdateInventorySelect(playerid, PlayerText: textdraw, selectable, slot, id = INVALID_PARAM, type = INVALID_PARAM)
{	
	id = (id == INVALID_PARAM) ? playerid : id;
	type = (type == INVALID_PARAM) ? TYPE_INV_PLAYER : type;
	
	new type_slot = GetInventoryTypeSlot(id, slot, type);
		
	if (selectable)
	{
		PlayerTextDrawHide(playerid, textdraw);
		PlayerTextDrawBackgroundColor(playerid, textdraw, 150);
		PlayerTextDrawShow(playerid, textdraw);
		
		inventory_td_select[playerid] = textdraw;
	}
	else 
	{	
		PlayerTextDrawHide(playerid, textdraw);
		PlayerTextDrawBackgroundColor(playerid, textdraw, GetBackgroundSlot(type_slot));
		PlayerTextDrawShow(playerid, textdraw);
		
		inventory_td_select[playerid] = INVALID_PTD;
		
		SetPVarInt(playerid, "Inventory:Select", INVALID_PARAM);
		SetPVarInt(playerid, "Inventory:AddSelect", INVALID_PARAM);
	}
	
	SetTextInventoryButton(playerid, selectable, type_slot, slot, id, type);
}

UpdateInventorySlotModel(playerid, slot, type = TYPE_INV_PLAYER, id = INVALID_PARAM)
{
	new item,
		color,
		model,
		PlayerText: textdraw;
	
	id = (id == INVALID_PARAM) ? playerid : id;
	textdraw = (type == TYPE_INV_PLAYER) ? td_inv_slot[playerid][slot] : td_inv_addslot[playerid][slot];
	item = GetItemIndexById(GetInventoryEnumItem(id, slot, type, inv_item_id));
	color = GetBackgroundSlot(GetInventoryTypeSlot(id, slot, type));
	model = GetItemModel(id, slot, type);
	
	PlayerTextDrawHide(playerid, textdraw);
	PlayerTextDrawSetPreviewModel(playerid, textdraw, model);
	PlayerTextDrawSetPreviewRot(
		playerid, 
		textdraw, 
		item_list[item][it_draw_x], 
		item_list[item][it_draw_y], 
		item_list[item][it_draw_z], 
		item_list[item][it_draw_zoom] 
	);
	
	PlayerTextDrawBackgroundColor(playerid, textdraw, color);
	PlayerTextDrawShow(playerid, textdraw);
}

MoveDataInventorySlot(playerid, oldslot, newslot, id = INVALID_PARAM, type = TYPE_INV_PLAYER)
{
	new E_INVENTORY_DATA: i;
		
	id = (id == INVALID_PARAM) ? playerid : id;
	
	while (i < E_INVENTORY_DATA)
	{
		SetInventoryEnumItem(id, newslot, type, E_INVENTORY_DATA: i, 
			GetInventoryEnumItem(id, oldslot, type, E_INVENTORY_DATA: i) 
		);
		
		i++;
	}
	
	Update:item_data(id, oldslot, type, _, newslot, _);
	
	// Обновление привязки аттача к слоту предмета
	if (type == TYPE_INV_VEHICLE)
	{
		InventoryVehicleUpdateAttach(id, oldslot, newslot);
	}
	
	Clear:inv_data_slot(id, oldslot, type);
	
	UpdateInventorySlotModel(playerid, newslot, type, id);
	UpdateInventorySlotModel(playerid, oldslot, type, id);
}