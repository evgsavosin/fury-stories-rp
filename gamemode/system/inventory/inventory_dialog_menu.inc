/*!
	@brief Диалоговый инвентарь
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

/*!
	Открываем инвентарь на диалогах
	@param [in] playerid Игрок
	@param [in] additional_type Тип овнера
	@param [in] additional_id ID овнера
	@param [in] dialogid ID диалога
	@param [in] action_type Тип действия
*/

ShowInventoryDialog(playerid, additional_type = TYPE_INV_PLAYER, additional_id = INVALID_PARAM, dialogid = D_INV, action_type = INVALID_PARAM)
{
	strglobalclear();
	
	new str_param			[	128		],
		str_action			[	20		],
		i,
		item,
		param,
		avaible_count = 0,
		index = 0,
		bool: null = true;
		

	additional_id = (additional_id == INVALID_PARAM) ? playerid : additional_id;

	if (action_type == INV_ACTION_PUT)
	{
		strcat(str_action, "Положить предмет");
	}
	else if (action_type == INV_ACTION_TAKE)
	{
		strcat(str_action, "Взять предмет");
	}
	else 
	{
		strcat(str_action, "Инвентарь");
	}
	
	strcat(g_big_string, #cPROJECT "Название\t" #cPROJECT "Статус\t" #cPROJECT "Параметр\n");
	
	do
	{
		clean:<str_param>;
		
		if (!GetInventoryEnumItem(additional_id, i, additional_type, inv_item_id))
		{
			if (additional_type == TYPE_INV_PLAYER)
			{
				if (GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_use_slot)) 
				{
					inv_data[playerid][i][inv_use_slot] = 0;
				}
			}

			if (GetInventoryEnumItem(additional_id, i, additional_type, inv_param_1))
			{
				SetInventoryEnumItem(additional_id, i, additional_type, inv_param_1, 0);
			}
			
			continue;
		}
		
		item = GetItemIndexById(GetInventoryEnumItem(additional_id, i, additional_type, inv_item_id));
		param = GetInventoryEnumItem(additional_id, i, additional_type, inv_param_1);
		
		switch (item_list[item][it_type])
		{
			case INV_WEAPON_SMALL, INV_WEAPON_BIG :
			{
				if (param)
				{
					format:str_param("(" #cGRAY "%d пт." #cWHITE ")", param);
				}
			}
			
			case INV_SKIN :
			{
				format:str_param("(" #cGRAY "%d" #cWHITE ")", param);
			}
			
			case INV_AMMO :
			{
				if (param)
				{
					format:str_param("(" #cGRAY "%d пт." #cWHITE ")", param);
				}
			}	
			
			case INV_BAG :
			{
				index = GetBagIndexBySlot(additional_id, i, additional_type);
					
				if (action_type == INV_ACTION_PUT 
				&& GetInventoryEnumItem(additional_id, i, additional_type, inv_id) == GetBagId(index))
				{
					continue;
				}
				
				format:str_param("(" #cGRAY "%d/%d" #cWHITE ")",
					GetBagCountItems(index),
					item_list[item][it_param_1]
				);
			}
			
			case INV_DRUGS :
			{
				if (param)
				{
					format:str_param("(" #cGRAY "%d г." #cWHITE ")", param);
				}
			}
		}
		
		format:g_small_string(" " #cWHITE "%s %s\t%s\t%s\n",
			item_list[item][it_name],
			(IsItemWeaponBig(additional_id, i, additional_type) ? (" " #cWHITE "[" #cDARKRED "габаритный" #cWHITE "]") : ("")),
			(GetInventoryEnumItem(additional_id, i, additional_type, inv_use_slot) ? (#cPROJECT "Используется") : (" ")),
			isnull(str_param) ? ("") : str_param
		);

		strcat(g_big_string, g_small_string);
		
		null = false;
		
		inventory_list_id[playerid][avaible_count] = GetInventoryEnumItem(playerid, i, additional_type, inv_item_id);
		inventory_select_slot[playerid][avaible_count] = i;
		avaible_count++;
	}
	while (++i < MAX_INVENTORY_SLOTS);
	
	format:g_small_string("%s - Слотов " #cWHITE "[%i/%i]" #cGRAY "",
		str_action,
		avaible_count,
		MAX_INVENTORY_SLOTS
	);
	
	if (ResetPlayerSkin(playerid) != character_data[playerid][c_skin] 
	&& action_type != INV_ACTION_PUT && action_type != INV_ACTION_TAKE)
	{	
		strcat(g_big_string, "" #cPROJECT " Снять одежду\n");
		inventory_list_id[playerid][avaible_count] = sizeof item_list + character_data[playerid][c_skin];
		inventory_select_slot[playerid][avaible_count] = INVALID_PARAM;
		avaible_count++;
	}
	
	if (null)
	{
		inventory_list_id[playerid][avaible_count] = INVALID_PARAM;
		strcat(g_big_string, "  " #cGRAY "В инвентаре нет предметов");
	}
	
	return ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, g_small_string, g_big_string, "Выбрать", "Закрыть");
}
