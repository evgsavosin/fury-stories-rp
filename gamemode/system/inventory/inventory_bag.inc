/*!
	@brief Система сумок
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
	
	Переписать хранение ID с таблицы "bags" на таблицу "items", конкретно индентификатора предмета сумки
*/

Create:bag(id, index, type, bool: is_load = false)
{
	new bindex = GetFreeIndexForBag();
	
	if (bindex == INVALID_PARAM)
	{
		return;
	}
	
	Clear:bag_data(bindex);
	
	bag_data[bindex][bag_id] = GetInventoryEnumItem(id, index, type, inv_id);
	bag_data[bindex][bag_type] = GetItemIndexById(GetInventoryEnumItem(id, index, type, inv_item_id));
	
	if (is_load)
	{
		Load:inventory(bindex, TYPE_INV_BAG);
	
		printf("[Create:bag]: Bag with index %i has been loaded. (ID: %i)",
			bindex, 
			bag_data[bindex][bag_id]
		);
	}
	else 
	{
		printf("[Create:bag]: Bag with index %i has been created. (ID: %i)",
			bindex, 
			bag_data[bindex][bag_id]
		);
	}
}

Remove:bag(playerid, slot, item_remove = true, in_game = true)
{
	new bindex = GetBagIndexBySlot(playerid, slot, TYPE_INV_PLAYER);
	
	Remove:item_data(playerid, slot, TYPE_INV_PLAYER);
	
	RemovePlayerAttachedObject(playerid, SLOT_ATTACH_BAG);
	inventory_attach[playerid][SLOT_ATTACH_BAG] = INVALID_PARAM; 
	
	if (item_remove)
	{
		format:g_string("DELETE FROM " #__ITEMS " WHERE inv_owner_id = %i AND inv_owner_type = %i",
			bag_data[bindex][bag_id],
			TYPE_INV_BAG
		);
		
		mysql_pquery(db, g_string);
	}
	
	if (in_game)
	{
		Clear:bag_data(bindex);
	}
}

GetInventorySlotBag(const id, type) // определяем слот сумки у игрока и тд и тп
{
	new itindex;
		
	for (new i; i < MAX_INVENTORY_SLOTS; i++)
	{
		itindex = GetItemIndexById(GetInventoryEnumItem(id, i, type, inv_item_id));
		
		if (item_list[itindex][it_type] != INV_BAG)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

GetBagIndexBySlot(const id, index, type) // определяем индекс в массиве (MAX_BAGS) с помощью слота
{
	if (index == INVALID_PARAM)
	{
		return INVALID_PARAM;
	}
	
	new is_bag = item_list[GetItemIndexById(GetInventoryEnumItem(id, index, type, inv_item_id))][it_type] == INV_BAG;
		
	for (new i; i < MAX_BAGS; i++)
	{
		if (!GetBagId(i))
		{
			continue;
		}
			
		if (!is_bag || GetInventoryEnumItem(id, index, type, inv_id) != GetBagId(i))
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

GetBagIndexById(const id)
{
	for (new i; i < MAX_BAGS; i++)
	{
		if (!GetBagId(i))
		{
			continue;
		}
		
		printf("GetBagId(%d) = %d", i, GetBagId(i));
		if (GetBagId(i) != id)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

GetFreeIndexForBag()
{
	for (new i; i < MAX_BAGS; i++)
	{
		if (GetBagId(i))
		{
			continue;
		}
		
		return i; 
	}
	
	return INVALID_PARAM;
}

GetBagCountItems(bindex)
{
	new count,
		_: slots = item_list[bag_data[bindex][bag_type]][it_param_1];
		
	for (new i; i < slots; i++)
	{
		if (GetInventoryEnumItem(bindex, i, TYPE_INV_BAG, inv_item_id) == 0)
		{
			continue;
		}
		
		count++;
	}
	
	return count;
}
