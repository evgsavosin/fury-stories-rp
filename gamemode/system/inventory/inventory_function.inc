/*!
	@brief Функции для системы инвентаря
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/


// Public functions
Inv_OnGameModeInit()
{
	for (new i; i < sizeof drop_data; i++)
	{
		Clear:drop_data(i);
	}
}

Inv_OnPlayerDisconnect(playerid, reason)
{	
	#pragma unused reason
	if (user_login{playerid})
	{
		for (new i, itindex, type, index; i < MAX_INVENTORY_SLOTS; i++)
		{
			itindex = GetItemIndexById(GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id));
			type = item_list[itindex][it_type];
			
			if (type == INV_WEAPON_BIG || type == INV_WEAPON_SMALL) /// Сохраняем патроны и прочую информацию об оружии
			{
				Update:item_data(playerid, i, TYPE_INV_PLAYER, _, _, _, true);
			}
			else if (type == INV_BAG) /// Очищаем информацию о сумке
			{
				if ((index = GetBagIndexBySlot(playerid, i, TYPE_INV_PLAYER)) == INVALID_PARAM)
				{
					printf("[Inv_OnPlayerDisconnect]: Invalid Index bag of slot[%i] (ACCOUNT ID: %i)", i, GetCharacterId(playerid));
					continue;
				}
				
				Clear:bag_data(index);
			}
			else if (type == INV_PHONE) /// Очищаем информацию о телефоне
			{
				if ((index = GetPhoneIndexBySlot(playerid, i, TYPE_INV_PLAYER)) == INVALID_PARAM)
				{
					printf("[Inv_OnPlayerDisconnect]: Invalid index phone of slot[%i] (ACCOUNT ID: %i)", i, GetCharacterId(playerid));
					continue;
				}
				
				Clear:phone_data(index);
			}
			else if (type == INV_ATTACH) /// Сохраняем бронь
			{
				if (GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_param_2) != 0
				&& item_list[itindex][it_param_1] != INV_FUNC_ARMOUR_LIGHT 
				&& item_list[itindex][it_param_1] != INV_FUNC_ARMOUR_HEAVY)
				{
					continue;
				}
				
				Update:item_data(playerid, i, TYPE_INV_PLAYER, _, _, _, true);
			}
		}
	}
	
	return 1;
}

Inv_OnPlayerSpawn(playerid)
{
	// Сбрасываем скиллы
	SetPlayerSkillLevel(playerid, WEAPONSKILL_PISTOL, 0);
	SetPlayerSkillLevel(playerid, WEAPONSKILL_MICRO_UZI, 0);
	
	// Применяем предметы
	SetTimerEx("OnPlayerApplyUseItem", 1000, false, "i", playerid);
	return 1;
}

Inv_OnPlayerClickTextDraw(playerid, Text: clickedid) 
{
	new select = GetPVarInt(playerid, "Inventory:Select");
		
	// Действия с кнопками
	if (clickedid == INVALID_TEXT_DRAW && IsInventoryTextDrawShowed(playerid))
	{
		ShowInventoryTextdraw(playerid, false);
	}
	else if (td_inventory[4] == clickedid) // Информация
	{
		if (select == INVALID_PARAM)
		{
			SendClientMessage(playerid, C_WHITE, !ERROR_NOT_CHOOSE_ITEM);
			return 1;
		}
		
		return ShowInventoryItemInformation(playerid, select);
	}
	else if (td_inventory[5] == clickedid) // Передать
	{
		if (select == INVALID_PARAM)
		{
			SendClientMessage(playerid, C_WHITE, !ERROR_NOT_CHOOSE_ITEM);
			return 1;
		}
		
		ShowPlayerDialog(playerid, D_INV + 3, DIALOG_STYLE_INPUT, item_list[GetItemIndexById(GetInventoryEnumItem(playerid, select, TYPE_INV_PLAYER, inv_item_id))][it_name], 
			"" #DEFAULT " Передать предмет\n\n\
			Для того, чтобы передать предмет, введите ID игрока:\n\n\
			" #cGRAY "Данный игрок должен находиться рядом с Вами.", 
			"Далее", "Назад" 
		);
	}
	else if (td_inventory[6] == clickedid) // Выбросить
	{
		if (select == INVALID_PARAM)
		{
			SendClientMessage(playerid, C_WHITE, !ERROR_NOT_CHOOSE_ITEM);
			return 1;
		}
		
		format:g_string("" #DEFAULT " Выбросить предмет\n\n\
			Вы действительно собираетесь выбросить предмет " #cPROJECT "%s" #cWHITE "?",
			item_list[GetItemIndexById(GetInventoryEnumItem(playerid, select, TYPE_INV_PLAYER, inv_item_id))][it_name]
		);
		
		ShowPlayerDialog(playerid, D_INV + 5, DIALOG_STYLE_MSGBOX, item_list[GetItemIndexById(GetInventoryEnumItem(playerid, select, TYPE_INV_PLAYER, inv_item_id))][it_name], 
			g_string, 
			"Далее", "Назад" 
		);
	}
	else if (td_inventory[7] == clickedid) // Удалить
	{
		if (select == INVALID_PARAM)
		{
			SendClientMessage(playerid, C_WHITE, !ERROR_NOT_CHOOSE_ITEM);
			return 1;
		}
		
		format:g_string("" #DEFAULT " Удалить предмет\n\n\
			Вы действительно собираетесь удалить предмет " #cPROJECT "%s" #cGRAY "?",
			item_list[GetItemIndexById(GetInventoryEnumItem(playerid, select, TYPE_INV_PLAYER, inv_item_id))][it_name]
		);
		
		ShowPlayerDialog(playerid, D_INV + 4, DIALOG_STYLE_MSGBOX, item_list[GetItemIndexById(GetInventoryEnumItem(playerid, select, TYPE_INV_PLAYER, inv_item_id))][it_name], 
			g_string, 
			"Далее", "Назад" 
		);
	}
	else if (td_inventory[8] == clickedid) // Снять одежду
	{	
		if (ResetPlayerSkin(playerid) == character_data[playerid][c_skin])
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " На Вас нет одежды.");
			return 1;
		}
		
		SetPVarInt(playerid, "Inventory:TempSelect", select);
		cmd_undress(playerid);
	}
	
	return 1;
}

Inv_OnPlayerClickPlayerTextDraw(playerid, PlayerText: playertextid)
{
	new i,
		select = GetPVarInt(playerid, "Inventory:Select"),
		addselect = GetPVarInt(playerid, "Inventory:AddSelect"),
		id = GetPVarInt(playerid, "Inventory:Id"),
		type_inv = GetPVarInt(playerid, "Inventory:TypeInv");
	
	// Действия с инвентарем
	for (i = 0; i < MAX_INVENTORY_SLOTS; i++)
	{
		if (playertextid != td_inv_slot[playerid][i])
		{
			continue;
		}
		
		// Отжатие выделенной ячейки
		if (inventory_td_select[playerid] == playertextid 
		&& select == i && addselect == INVALID_PARAM)
		{
			UpdateInventorySelect(playerid, playertextid, false, i);
			break;
		}
		
		else if (addselect == INVALID_PARAM)
		{
			new is_selected = (inventory_td_select[playerid] != INVALID_PTD && select != INVALID_PARAM);
			if (GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id) == 0) // Перемещение ячейки
			{
				if (is_selected)
				{
					MoveDataInventorySlot(playerid, select, i);
					UpdateInventorySelect(playerid, playertextid, false, i);
					break;
				}
			}
			else // Выделение ячейки
			{
				if (is_selected)
				{
					UpdateInventorySelect(playerid, inventory_td_select[playerid], false, select);
					
					if (IsInventoryItemExistsByType(playerid, TYPE_INV_PLAYER, i, INV_DRUGS) 
					&& IsInventoryItemExistsByType(playerid, TYPE_INV_PLAYER, select, INV_DRUGS)
					)
					{
						new first_itindex = GetItemIndexById(GetInventoryEnumItem(playerid, select, TYPE_INV_PLAYER, inv_item_id)),
							second_itindex = GetItemIndexById(GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id));
							
						if (item_list[second_itindex][it_param_1] == item_list[first_itindex][it_param_1])
						{
							new value = GetInventoryEnumItem(playerid, select, TYPE_INV_PLAYER, inv_param_1);
							
							value += GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_param_1);
							
							SetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_param_1, value);
							
							RemoveInventoryItem(playerid, select);
							
							Update:item_data(playerid, i, TYPE_INV_PLAYER);
							
							UpdateInventorySelect(playerid, inventory_td_select[playerid], false, select);
							return 1;
						}
					}
				}
				
				UpdateInventorySelect(playerid, playertextid, true, i);
				SetPVarInt(playerid, "Inventory:Select", i);
				break;
			}
		}
		
		// Перемещение из additional inventory в player inv
		else if (inventory_td_select[playerid] != INVALID_PTD 
		&& addselect != INVALID_PARAM && select == INVALID_PARAM)
		{
			if (!GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id))
			{
				ActionDataInventorySlot(playerid, 
					INV_ACTION_TAKE, 
					addselect, 
					i, 
					id,
					type_inv
				);
				
				UpdateInventorySelect(playerid, playertextid, false, i);
				break;
			}
		}
	}
	
	if (id != INVALID_PARAM)
	{
		// Действия с дополнительным инвентарем
		for (i = 0; i < MAX_INVENTORY_SLOTS; i++)
		{
			if (playertextid != td_inv_addslot[playerid][i])
			{
				continue;
			}
			
			// Отжатие ячейки
			if (inventory_td_select[playerid] == playertextid 
			&& select == INVALID_PARAM && addselect == i)
			{
				UpdateInventorySelect(playerid, playertextid, false, i, id, type_inv);
			}
			
			else if (select == INVALID_PARAM)
			{
				new is_selected = (inventory_td_select[playerid] != INVALID_PTD && addselect != INVALID_PARAM);
				if (GetInventoryEnumItem(id, i, type_inv, inv_item_id) == 0) // Перемещение ячейки
				{
					if (is_selected)
					{
						MoveDataInventorySlot(playerid, addselect, i, id, type_inv);
						UpdateInventorySelect(playerid, playertextid, false, i, id, type_inv);
						break;
					}
				}
				else // Выделение ячейки
				{
					if (is_selected)
					{
						UpdateInventorySelect(playerid, inventory_td_select[playerid], false, addselect);
					}
					
					UpdateInventorySelect(playerid, playertextid, true, i, id, type_inv);
					SetPVarInt(playerid, "Inventory:AddSelect", i);
					break;
				}
			}
			
			// Перемещение из player inv в additional inv
			else if (inventory_td_select[playerid] != INVALID_PTD 
			&& select != INVALID_PARAM && addselect == INVALID_PARAM)
			{

				new itindex = GetItemIndexById(GetInventoryEnumItem(playerid, select, TYPE_INV_PLAYER, inv_item_id));
					
				if (type_inv == TYPE_INV_BAG && item_list[itindex][it_type] == INV_BAG)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете поместить предмет сумки в другую сумку.");
					break;
				}
				
				if (!GetInventoryEnumItem(id, i, type_inv, inv_item_id))
				{
					ActionDataInventorySlot(playerid, 
						INV_ACTION_PUT, 
						select, 
						i, 
						id,
						type_inv
					);
					
					UpdateInventorySelect(playerid, playertextid, false, i, id, type_inv);
					break;
				}
			}
		}
	}
	
	select = GetPVarInt(playerid, "Inventory:Select");
	addselect = GetPVarInt(playerid, "Inventory:AddSelect");
	
	if (playertextid == td_inv_button[playerid])
	{	
		if (select == INVALID_PARAM && addselect == INVALID_PARAM)
		{
			SendClientMessage(playerid, C_WHITE, !ERROR_NOT_CHOOSE_ITEM);
			return 1;
		}
		
		if (select != INVALID_PARAM && addselect == INVALID_PARAM)
		{
			if (!GetInventoryEnumItem(playerid, select, TYPE_INV_PLAYER, inv_use_slot))
			{
				if (!InventoryUseItem(playerid, select))
				{
					SendClientMessage(playerid, C_WHITE, !ERROR_NO_USE);
					return 1;
				}
			}
			else
			{
				InventoryUnuseItem(playerid, select, true, false);
			}
		}
		else if (select == INVALID_PARAM && addselect != INVALID_PARAM 
		&& type_inv == TYPE_INV_VEHICLE)
		{
			if (!GetVehicleSlotIsAttached(id, addselect))
			{
				if (!InventoryVehicleAttach(playerid, id, addselect))
				{
					SendClientMessage(playerid, C_WHITE, !ERROR_NO_USE);
					return 1;
				}
			}
			else
			{
				InventoryVehicleUnattach(playerid, id, addselect);
			}
		}
	}
	
	return 1;
}

Inv_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	#pragma unused oldkeys
	
	if (PRESSED(KEY_CTRL_BACK))
	{
		if (GetPVarInt(playerid, "Drop:Edit"))
		{
			return 1;
		}
		
		for (new i, itindex; i < sizeof drop_data; i++)
		{
			if (!IsPlayerInRangeOfPoint(playerid, 2.0, 
			drop_data[i][drop_pos_x], 
			drop_data[i][drop_pos_y],
			drop_data[i][drop_pos_z])
			|| IsPlayerInAnyVehicle(playerid))
			{
				continue;
			}
			
			if (drop_data[i][drop_item_id] == 0)
			{
				continue;
			}
			
			itindex = GetItemIndexById(drop_data[i][drop_item_id]);
			SetPVarInt(playerid, "Drop:Select", i);
			format:g_string("" #DEFAULT " Подобрать предмет\n\n\
				Вы действительно желаете подобрать предмет " #cPROJECT "%s" #cWHITE "?",
				item_list[itindex][it_name]
			);
			
			ShowPlayerDialog(playerid, D_INV + 16, DIALOG_STYLE_MSGBOX, " ", g_string, "Да", "Нет");
			return 0;
		}
	}
	else if (PRESSED(KEY_HANDBRAKE))
	{
		if (!GetPVarInt(playerid, "Inventory:UseDrinkIndex"))
		{
			return 1;
		}
			
		if (GetPVarInt(playerid, "Inventory:UseDrinkCount") != 5)
		{
			new index = GetPVarInt(playerid, "Inventory:UseDrinkIndex");
				
			GivePVarInt(playerid, "Inventory:UseDrinkCount", 1);
			
			ApplyAnimationEx(playerid, "VENDING", "VEND_Drink2_P", 2.0, 0, 0, 0, 0, 5000, 1, true);
			
			format:g_small_string("Пьет %s", 
				item_list[index][it_name]
			);
			
			SendRPMessage(ACTION_AME, playerid, g_small_string);
			
			GiveHealthPlayer(playerid, float(item_list[index][it_param_1]));
		}
		else
		{
			DeletePVar(playerid, "Inventory:UseDrinkIndex");
			DeletePVar(playerid, "Inventory:UseDrinkCount");
			
			ClearAnimationsEx(playerid);
			
			RemovePlayerAttachedObject(playerid, SLOT_ATTACH_DRINK);
		}
	}
	
	return 1;
}

function Inv_OnPlayerEditDynamicObject(playerid, objectid, response, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz)
{		
	if (GetPVarInt(playerid, "Drop:Edit"))
	{
		if (response == EDIT_RESPONSE_CANCEL)
		{
			DestroyDynamicObject(objectid);
			
			drop_data[GetPVarInt(playerid, "Drop:Index")][drop_object] = INVALID_OBJECT_ID;
		}
		else if (response == EDIT_RESPONSE_FINAL)
		{
			new i = GetPVarInt(playerid, "Drop:Index"),
				slot = GetPVarInt(playerid, "Drop:Slot"),
				item = GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id));
			
			drop_data[i][drop_item_id] = inv_data[playerid][slot][inv_item_id];
			drop_data[i][drop_item_param_1] = inv_data[playerid][slot][inv_param_1];
			drop_data[i][drop_item_param_2] = inv_data[playerid][slot][inv_param_2];
			
			drop_data[i][drop_pos_x] = x;
			drop_data[i][drop_pos_y] = y;
			drop_data[i][drop_pos_z] = z;
			drop_data[i][drop_character_id] = GetCharacterId(playerid);
			
			if (item_list[item][it_type] == INV_BAG)
			{
				format:g_small_string("%s\n" #cPROJECT "Подобрать - H\nДействия - Y",
					item_list[item][it_name]
				);
				
				drop_data[i][drop_item_param_1] = inv_data[playerid][slot][inv_id];
				drop_data[i][drop_use_inv] = true;
			}
			else 
			{
				if (item_list[item][it_type] == INV_ATTACH 
				&& item_list[item][it_param_1] == INV_FUNC_SOUND)
				{
					drop_data[i][drop_area] = CreateDynamicSphere(
						x, 
						y, 
						z, 
						30.0, 
						GetPlayerVirtualWorld(playerid), 
						GetPlayerInterior(playerid)
					);
					
					drop_data[i][drop_func] = INV_FUNC_SOUND;
				}
				
				format:g_small_string("%s\n" #cPROJECT "Подобрать - H",
					item_list[item][it_name]
				);
			}
			
			drop_data[i][drop_label] = CreateDynamic3DTextLabel(
				g_small_string, 
				C_WHITE, 
				x, 
				y, 
				z, 
				1.5 
			);
			
			if (!RemoveInventoryItem(playerid, slot, true, false))
			{
				if (IsValidDynamicObject(drop_data[i][drop_object]))
				{
					DestroyDynamicObject(drop_data[i][drop_object]);
				}
				
				if (IsValidDynamic3DTextLabel(drop_data[i][drop_label]))
				{
					DestroyDynamic3DTextLabel(drop_data[i][drop_label]);
				}	
				
				DeletePVar(playerid, "Drop:Edit");
				DeletePVar(playerid, "Drop:Index");
				DeletePVar(playerid, "Drop:Slot");
				Clear:drop_data(i);
				
				SendClientMessage(playerid, C_WHITE, !ERROR_SYSTEM);
				
				return 1;
			}
			
			pformat:("" #SUCCESS " Вы положили предмет " #cPROJECT "%s" #cWHITE". Для подбора, используйте " #cPROJECT "H" #cWHITE ".",
				item_list[item][it_name]
			);
			
			psend:(playerid, C_WHITE);

		}
		
		if (response == EDIT_RESPONSE_CANCEL || response == EDIT_RESPONSE_FINAL)
		{
			DeletePVar(playerid, "Drop:Edit");
			DeletePVar(playerid, "Drop:Index");
			DeletePVar(playerid, "Drop:Slot");
			
			ShowInventory(playerid, GetUserSettings(playerid, SET_INVENTORY));
		}
	}
	
	if (GetPVarInt(playerid, "VehicleAttach:Edit"))
	{
		new vehicleid = GetPVarInt(playerid, "VehicleAttach:Vehicle"),
			index = GetPlayerVehicleIndexByServerId(playerid, vehicleid);
		
		if (player_vehicle[playerid][pv_server_id][index] == 0 
		|| response == EDIT_RESPONSE_CANCEL)
		{
			new slot = GetPVarInt(playerid, "VehicleAttach:AttachSlot");
				
			DestroyDynamicObject(objectid);
			
			inventory_veh_attach[vehicleid][slot][a_slot] = 
			inventory_veh_attach[vehicleid][slot][a_object] = INVALID_PARAM;
		}
		else if (response == EDIT_RESPONSE_FINAL)
		{
			new Float: x_pos,
				Float: y_pos,
				Float: z_pos,
				Float: angle;
				
			GetVehiclePos(vehicleid, x_pos, y_pos, z_pos);
			GetVehicleZAngle(vehicleid, angle);
			
			x -= x_pos;
			y -= y_pos;
			z -= z_pos;
			
			x = x * floatcos(angle, degrees) + y * floatsin(angle, degrees);
			y = -x * floatsin(angle, degrees) + y * floatcos(angle, degrees);
			
			if (VectorSize(x, y, z) < 5.0)
			{
				if (IsDynamicObjectMoving(objectid))
				{
					StopDynamicObject(objectid);
				}
				
				AttachDynamicObjectToVehicle(
					objectid, 
					vehicleid, 
					x, 
					y, 
					z, 
					rx, 
					ry, 
					rz - angle 
				);
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно прикрепили предмет к транспорту.");
			}
		}
		
		if (response == EDIT_RESPONSE_CANCEL || response == EDIT_RESPONSE_FINAL)
		{
			DeletePVar(playerid, "VehicleAttach:Edit");
			DeletePVar(playerid, "VehicleAttach:Vehicle");
			DeletePVar(playerid, "VehicleAttach:Slot");
			DeletePVar(playerid, "VehicleAttach:AttachSlot");
		
			ShowInventory(playerid, GetUserSettings(playerid, SET_INVENTORY));
		}
	}

	return 1;
}

Inv_OnPlayerEnterDynamicArea(playerid, areaid)
{
	for (new i; i < sizeof drop_data; i++)
	{
		if (!IsValidDynamicArea(drop_data[i][drop_area]))
		{
			continue;
		}
		
		if (areaid == drop_data[i][drop_area])
		{
			if (isnull(drop_data[i][drop_boombox_url]))
			{
				continue;
			}
			
			PlayAudioStreamForPlayer(
				playerid, 
				drop_data[i][drop_boombox_url], 
				drop_data[i][drop_pos_x], 
				drop_data[i][drop_pos_y],
				drop_data[i][drop_pos_z], 
				15.0, 
				1
			);
			
			break;
		}
	}
	
	return 1;
}

Inv_OnPlayerLeaveDynamicArea(playerid, areaid)
{
	for (new i; i < sizeof drop_data; i++)
	{
		if (!IsValidDynamicArea(drop_data[i][drop_area]))
		{
			continue;
		}
		
		if (areaid == drop_data[i][drop_area])
		{
			StopAudioStreamForPlayer(playerid);
		}
	}
	
	return 1;
}

// Main function
function OnInventoryUpdateWeaponData(playerid, weaponid, ammo)
{
	new slot = GetInventorySlotByWeaponId(playerid, weaponid);
	
	if (slot == INVALID_PARAM 
	|| ammo == 0 && !GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_use_slot))
	{
		if (weaponid == WEAPON_SILENCED && GetPVarInt(playerid, "Player:Taser") && ammo < 3)
		{
			return 1;
		}
		
		return 0;
	}
	
	SetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_1, ammo);
	
	if (ammo == 0)
	{
		InventoryUnuseItem(playerid, slot, false, true);
	}
	
	return 1;
}

function OnPlayerApplyUseItem(playerid)
{
	new item,
		type,
		used,
		attach_slot = GetFreeAttachSlot(playerid),
		i = 0,
		bool: is_attach = false;
		
	do
	{
		if ((item = GetItemIndexById(GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id))) == INVALID_ITEM_ID)
		{
			continue;
		}
		
		type = item_list[item][it_type];
		if (type != INV_ATTACH 
		&& type != INV_WEAPON_SMALL 
		&& type != INV_WEAPON_BIG 
		&& type != INV_BAG)
		{
			continue;
		}
		
		used = GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_use_slot);
		if (used == TYPE_USE_DEFAULT)
		{
			if (type == INV_ATTACH)
			{
				if (attach_slot == INVALID_PARAM)
				{
					continue;
				}
				
				SetPVarInt(playerid, "Inventory:AttachType", DEFAULT_ATTACH);
				is_attach = true;
			}
			else if (type == INV_BAG)
			{
				SetPVarInt(playerid, "Inventory:AttachType", BAG_ATTACH);
				is_attach = true;
			}
			else if (type == INV_WEAPON_SMALL || type == INV_WEAPON_BIG)
			{
				GiveInventoryWeapon(playerid, i);
			}
		}
		else if (used == TYPE_USE_ATTACH)
		{
			if (type == INV_WEAPON_SMALL || type == INV_WEAPON_BIG)
			{
				if (attach_slot == INVALID_PARAM)
				{
					continue;
				}
				
				SetPVarInt(playerid, "Inventory:AttachType", DEFAULT_ATTACH);
				is_attach = true;
			}
		}
		
		if (is_attach)
		{
			OnInventoryAttachItem(
				playerid, 
				GetItemModel(playerid, i, TYPE_INV_PLAYER),
				inv_data[playerid][i][inv_bone],
				inv_data[playerid][i][inv_pos_x], 
				inv_data[playerid][i][inv_pos_y], 
				inv_data[playerid][i][inv_pos_z],
				inv_data[playerid][i][inv_rot_x], 
				inv_data[playerid][i][inv_rot_y], 
				inv_data[playerid][i][inv_rot_z],
				inv_data[playerid][i][inv_scale_x],
				inv_data[playerid][i][inv_scale_y],
				inv_data[playerid][i][inv_scale_z],
				i,
				INVALID_PARAM // not save
			);
			
			is_attach = false;
		}
	}
	while (++i < MAX_INVENTORY_SLOTS);
	
	return 1;
}

InventoryUseItem(playerid, index)
{
	new itindex = GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id)),
		type = item_list[itindex][it_type];
		
	if (itindex == INVALID_ITEM_ID)
	{
		return 0;
	}
	
	if (GetInventoryTypeItemCount(playerid, type, true) >= GetInventoryMaxTypeItems(type, true))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете использовать данный предмет, поскольку подобные уже используются Вами.");
		return 1;
	}
	
	SetPVarInt(playerid, "Inventory:TempSelect", index);
	
	switch(item_list[itindex][it_type])
	{
		case INV_SKIN :
		{
			if (ResetPlayerSkin(playerid) != character_data[playerid][c_skin])
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " На Вас уже надета одежда, снимите её, чтобы надеть новую.");
				return 1;
			}
			
			new skin_id = GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1);
				
			if (!IsValidSkin(skin_id, GetCharacterSex(playerid)))
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете надеть данную одежду.");
				return 1;
			}
			
			new Float: x,
				Float: y,
				Float: z,
				Float: angle;
				
			character_data[playerid][c_skin] = skin_id;
			
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			
			SetSpawnInfo(playerid, 264, character_data[playerid][c_skin], x, y, z, angle, 0, 0, 0, 0, 0, 0);
			SetPlayerSkin(playerid, character_data[playerid][c_skin]);
			
			Update:character_int(playerid, "c_skin", character_data[playerid][c_skin]);
		}
		
		case INV_WEAPON_BIG, INV_WEAPON_SMALL :
		{
			ShowInventoryWeaponUse(playerid, index, itindex);
			return 1; 
		}
		
		case INV_AMMO :
		{
			UpdateInventory(playerid, index);
			if (!GiveInventoryAmmo(playerid, index))
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Данный тип патрона не подходит к оружию или Вы не выбрали само оружие.");
				return 1;
			}
		}
		
		case INV_EAT : 
		{
			ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 2.0, 0, 0, 0, 0, 5000, 1);
			
			format:g_small_string("Съел%s %s", 
				EndWordSex(playerid),
				item_list[itindex][it_name]
			);
			
			SendRPMessage(ACTION_AME, playerid, g_small_string);
		}
		
		case INV_DRINK :
		{
			SetPVarInt(playerid, "Inventory:UseDrinkIndex", itindex);
			SetPVarInt(playerid, "Inventory:UseDrinkCount", 0);
			
			SetPlayerAttachedObject(
				playerid, 
				SLOT_ATTACH_DRINK, 
				item_list[itindex][it_model],
				5,
				0.126999,
				0.016998,
				-0.010999,
				5.099999,
				-175.499862,
				1.399999,
				1.000000,
				1.000000,
				1.000000
			);
		}
		
		case INV_ATTACH :
		{
			if (GetFreeAttachSlot(playerid) == INVALID_PARAM)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете прикрепить больше предметов на персонажа!");
				return 1;
			}
			
			AttachPlayerInventoryItem(playerid, index);
			return 1; 
		}
		
		case INV_BAG :
		{
			AttachPlayerInventoryItem(playerid, index, BAG_ATTACH);
			return 1;
		}
		
		case INV_PHONE :
		{	
			new slot = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_PHONE, _, true);
	
			if (slot == INVALID_PARAM)
			{
				SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_use_slot, true);
				Update:item_data(playerid, index, TYPE_INV_PLAYER);
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно активировали данный телефон в качестве основного. " #cGRAY "(/phone - вызвать телефон)");
				UpdateInventory(playerid, index);
			}
			else 
			{
				if (IsInventoryTextDrawShowed(playerid))
				{
					ShowInventoryTextdraw(playerid, false, _, _, _, _, false);
				}
				
				ShowPhone(playerid, index);
			}
			
			return 1;
		}
		
		case INV_SMOKE :
		{
			ShowPlayerDialog(playerid, D_INV + 13, DIALOG_STYLE_LIST, " ",
				" Прикрепить сигарету ко рту\n \
				  Прикрепить сигарету к левой руке\n \
				  Прикрепить сигарету к правой руке",
				"Далее", "Закрыть"
			);
			
			return 1;
		}
		
		case INV_HEALTH :
		{
			if (GetCharacterHealth(playerid) > 70.0)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Ваше здоровье не позволяет использовать бинт.");
				return 1;
			}
			
			new Float: x,
				Float: y,
				Float: z;
				
			GetPlayerPos(playerid, x, y, z);
			
			TogglePlayerControllable(playerid, false);
			TogglePlayerAnimResetDisable(playerid, false);
			
			ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant_Loop", 4.1, 1, 1, 1, 0, 0, 1, true);
			SetTimerEx("OnHealthPlayer", 9000, false, "iifff", playerid, index, x, y, z);
			
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы перевязываете себе раны, подождите...");
			SendRPMessage(ACTION_AME, playerid, "Перевязывает раны");
			UpdateInventory(playerid, index);
			return 1;
		}
		
		case INV_REPAIR :
		{
			new vehicleid;
			
			if (!(vehicleid = GetVehicleAroundOfPlayer(playerid)))
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_AROUND_CAR);
				return 1;
			}
			
			if (GetVehicleCurrentHealth(vehicleid) > 400.0)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Ваш транспорт в состоянии завестись.");
				return 1;
			}
			
			if (random(2) == 1)
			{
				SetVehicleHealth(vehicleid, 500.0);
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вам удалось починить транспорт.");
				
				format:g_small_string("Починил%s транспорт", 
					EndWordSex(playerid)
				);
				
				SendRPMessage(ACTION_AME, playerid, g_small_string);
			}
			else 
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Вам не удалось починить транспорт. Вы можете воспользоваться услугами СТО, позвонив по номеру.");
			}
		}
		
		case INV_FUEL :
		{
			new vehicleid;
			
			if ((vehicleid = GetVehicleAroundOfPlayer(playerid)))
			{
				if (!VehicleFill(vehicleid, 5.0))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Бак заправляемого транспорта полон.");
					return 1;
				}
			}
			else
			{
				for (new i; i < sizeof corpse_data; i++)
				{
					if (IsPlayerInRangeOfPoint(playerid, 
					FACTOR_TELEPORT_RADIUS, 
					corpse_data[i][corp_pos][0], 
					corpse_data[i][corp_pos][1], 
					corpse_data[i][corp_pos][2]) 
					&& corpse_data[i][corp_state] == STATE_CORP_DEFAULT)
					{
						TogglePlayerControllable(playerid, false);
						TogglePlayerAnimResetDisable(playerid, false);
						
						ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant_Loop", 4.1, 1, 1, 1, 0, 0, 1, true);
						
						SetPlayerAttachedObject(
							playerid, 
							SLOT_ATTACH_TEMP,  
							1650, 
							6,
							ATTACH_INV_FUEL
						);

						SetPVarInt(playerid, "Player:CorpsePourGas", true);
						SetPVarInt(playerid, "Player:CorpsePourGasIndex", index);
						SetPVarInt(playerid, "Player:CorpsePourGasTimer", 
							SetTimerEx("OnCorpsePourGas", 1000 * 30, false, "iii", playerid, index, i) 
						);
						
						UpdateInventory(playerid, index);
						
						SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы обливаете труп бензином, подождите... " #cGRAY "(Время: 2 минуты | Отменить действие: /cancelgas)");
						SendRPMessage(ACTION_AME, playerid, "Использует канистру");
						return 1;
					}
				}
				
				return 0;
			}
		}

		case INV_RADIO :
		{
			SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_use_slot, true);
			Update:item_data(playerid, index, TYPE_INV_PLAYER);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно активировали данную рацию в качестве основной. " #cGRAY "(/channel, /slot - настройки)");
			UpdateInventory(playerid, index);
			return 1;
		}
		
		case INV_CHEMICAL :
		{	
			for (new i; i < sizeof corpse_data; i++)
			{
				if (IsPlayerInRangeOfPoint(playerid, 
				FACTOR_TELEPORT_RADIUS, 
				corpse_data[i][corp_pos][0], 
				corpse_data[i][corp_pos][1], 
				corpse_data[i][corp_pos][2]) 
				&& corpse_data[i][corp_state] == STATE_CORP_DEFAULT)
				{
					if (corpse_data[i][corp_used])
					{
						SendClientMessage(playerid, C_WHITE, !CORPSE_USED);
						return 1;
					}
					
					TogglePlayerControllable(playerid, false);
					TogglePlayerAnimResetDisable(playerid, false);
					
					ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant_Loop", 4.1, 1, 1, 1, 0, 0, 1, true);
					
					SetPVarInt(playerid, "Player:CorpsePourAcid", true);
					SetPVarInt(playerid, "Player:CorpsePourAcidIndex", i);
					SetPVarInt(playerid, "Player:CorpsePourAcidTimer", 
						SetTimerEx("OnCorpsePourAcid", 1000 * 20, false, "iii", playerid, index, i) 
					);
					
					corpse_data[i][corp_used] = true;
					
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы скрываете улики с помощью химраствора, подождите... " #cGRAY "(Время: 2 минуты | Отменить действие: /cancelchemical)");
					SendRPMessage(ACTION_AME, playerid, "Использует химраствор");
					UpdateInventory(playerid, index);
					return 1;
				}
			}
			
			return 0;
		}
		
		case INV_LIGHTER :
		{
			for (new i; i < sizeof corpse_data; i++)
			{
				if (IsPlayerInRangeOfPoint(playerid, 
				FACTOR_TELEPORT_RADIUS, 
				corpse_data[i][corp_pos][0], 
				corpse_data[i][corp_pos][1], 
				corpse_data[i][corp_pos][2]))
				{	
					if (corpse_data[i][corp_used])
					{
						SendClientMessage(playerid, C_WHITE, !CORPSE_USED);
						return 1;
					}
					
					if ((GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1) - 1) <= 0)
					{
						SendClientMessage(playerid, C_WHITE, #ERROR " В зажигалке закончился газ.");
						return 1;
					}
					
					SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1, 
						GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1) - 1
					);
					
					Update:item_data(playerid, index, TYPE_INV_PLAYER);
					
					UpdateInventory(playerid, index);
					
					if (!Create:corpse_fire(i))
					{
						SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете поджечь труп без воспламеняющиеся жидкости.");
						return 1;
					}
					
					corpse_data[i][corp_used] = true;
				
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы использовали зажигалку");
					SendRPMessage(ACTION_AME, playerid, "Использует зажигалку");
					
					
					return 1;
				}
			}
			
			return 0;
		}
		
		case INV_DRUGS:
		{
			ShowInventoryDrugUse(playerid, itindex, GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1));
			return 1;
		}
		
		default :
		{
			return 0;
		}
	}
	
	pformat:("" #SUCCESS " Вы успешно использовали " #cPROJECT "%s" #cWHITE ".",
		item_list[itindex][it_name]
	);
	
	psend:(playerid, C_WHITE);
	
	RemoveInventoryItem(playerid, index);
	
	return 1;
}

function OnHealthPlayer(playerid, index)
{
	TogglePlayerControllable(playerid, true);
	TogglePlayerAnimResetDisable(playerid, true);
	
	ClearAnimationsEx(playerid);
	
	if (!CheckActionSlot(playerid, index, INV_HEALTH)
	|| !RemoveInventoryItem(playerid, index))
	{
		return 1;
	}
	
	SetPlayerHealth(playerid, 100.0);
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно использовали бинты.");
	return 1;
}

function OnCorpsePourAcid(playerid, index, cindex)
{
	DeletePVar(playerid, "Player:CorpsePourAcid");
	DeletePVar(playerid, "Player:CorpsePourAcidIndex");
	DeletePVar(playerid, "Player:CorpsePourAcidTimer");
	
	TogglePlayerControllable(playerid, true);
	TogglePlayerAnimResetDisable(playerid, true);
	
	ClearAnimationsEx(playerid);
	
	if (!IsPlayerInRangeOfPoint(playerid, 
	FACTOR_TELEPORT_RADIUS, 
	corpse_data[cindex][corp_pos][0], 
	corpse_data[cindex][corp_pos][1], 
	corpse_data[cindex][corp_pos][2]))
	{
		return 1;
	}
	
	if (!CheckActionSlot(playerid, index, INV_CHEMICAL)
	|| !RemoveInventoryItem(playerid, index))
	{
		return 1;
	}
	
	Recreate:corpse(index, STATE_CORP_ACID);
	corpse_data[cindex][corp_used] = false;
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно использовали химраствор для скрытия улик.");
	return 1;
}

function OnCorpsePourGas(playerid, index, cindex)
{
	DeletePVar(playerid, "Player:CorpsePourGas");
	DeletePVar(playerid, "Player:CorpsePourGasIndex");
	DeletePVar(playerid, "Player:CorpsePourGasTimer");
	
	TogglePlayerControllable(playerid, true);
	TogglePlayerAnimResetDisable(playerid, true);
	
	ClearAnimationsEx(playerid);
	
	RemovePlayerAttachedObject(playerid, SLOT_ATTACH_TEMP);
	
	if (!IsPlayerInRangeOfPoint(playerid, 
	FACTOR_TELEPORT_RADIUS, 
	corpse_data[cindex][corp_pos][0], 
	corpse_data[cindex][corp_pos][1], 
	corpse_data[cindex][corp_pos][2]))
	{
		return 1;
	}
	
	if (!CheckActionSlot(playerid, index, INV_FUEL)
	|| !RemoveInventoryItem(playerid, index))
	{
		return 1;
	}
	
	corpse_data[cindex][corp_poured_gas] = true;
	corpse_data[cindex][corp_used] = false;
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно облили труп бензином. Для того, чтобы поджечь, используйте зажигалку.");
	return 1;
}

InventoryUnuseItem(playerid, index, bool: is_save, bool: is_priority)
{
	new used;
		
	if (!(used = GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_use_slot)))
	{
		return 1;
	}
	
	new itindex = GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id));
	
	SetPVarInt(playerid, "Inventory:TempSelect", index);
	
	switch(item_list[itindex][it_type])
	{
		case INV_WEAPON_BIG, INV_WEAPON_SMALL :
		{
			if (used == TYPE_USE_ATTACH && IsAttachExists(playerid, index, TYPE_INV_PLAYER))
			{
				RemoveAttachItemBySlot(playerid, index);
			}
			else if (used == TYPE_USE_DEFAULT)
			{
				if (is_priority)
				{
					RemoveInventoryWeapon(playerid, index);	
				}
				else 
				{
					ShowInventoryWeaponUnUse(playerid, index, itindex);
				}
				
				return 1;
			}
		}
		
		case INV_ATTACH :
		{
			new param = item_list[itindex][it_param_1];
			
			if (param == INV_FUNC_HIDDEN_NAME)
			{
				ReplacePlayerName(playerid, IsAdminLogged(playerid) ? TYPE_OOC : TYPE_IC);
			}
			else if (param == INV_FUNC_ARMOUR_LIGHT || param == INV_FUNC_ARMOUR_HEAVY)
			{
				Clear:armour_data(playerid);
			}
			else if (param == INV_FUNC_KNIFE)
			{
				DeletePVar(playerid, "Player:UseKnife");
			}
			
			RemoveAttachItemBySlot(playerid, index);
		}
		
		case INV_BAG :
		{
			if (is_priority)
			{
				RemovePlayerAttachedObject(playerid, SLOT_ATTACH_BAG);

				inventory_attach[playerid][SLOT_ATTACH_BAG] = INVALID_PARAM;
			}
			else 
			{
				ShowPlayerDialog(playerid, D_INV + 12, DIALOG_STYLE_LIST, item_list[itindex][it_name], 
					" Изменить позицию\n \
					  Убрать сумку",
					 "Выбрать", "Закрыть" 
				);
				
				return 1;
			}
		}
		
		case INV_PHONE : 
		{
			if (!is_priority)
			{
				new slot = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_PHONE, _, true);
		
				if(slot == index)
				{
					itindex = GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id));
					ShowPlayerDialog(playerid, D_INV + 14, DIALOG_STYLE_LIST, item_list[itindex][it_name],
						" Воспользоваться\n " #cGRAY "Убрать по умолчанию",
						"Выбрать", "Закрыть"
					);
				}
				
				return 1;
			}
		}
	}
	
	SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_use_slot, false);
	
	if (is_save)
	{
		Update:item_data(playerid, index, TYPE_INV_PLAYER);
	}
	
	if (!is_priority)
	{
		pformat:("" #SUCCESS " Вы успешно убрали предмет " #cPROJECT "%s" #cWHITE ".",
			item_list[itindex][it_name]
		);
		
		psend:(playerid, C_WHITE);
		
		UpdateInventory(playerid, index);
	}
	
	return 1;
}

InventoryDropItem(playerid, slot)
{
	if (GetPVarInt(playerid, "Drop:Edit"))
	{
		return 0;
	}

	new i,
		Float: x,
		Float: y,
		Float: z,
		Float: angle;
	
	if (!GetPlayerPos(playerid, x, y, z))
	{
		return 0;
	}
	
	GetPlayerFacingAngle(playerid, angle);
	
	x += (0.5 * (floatsin(-angle, degrees)));
	y += (0.5 * (floatcos(-angle, degrees)));
	z -= 1.0;
	
	while (++i < sizeof drop_data)
	{
		if (drop_data[i][drop_item_id] != 0
		|| drop_data[i][drop_object] != INVALID_OBJECT_ID)
		{
			continue;
		}
		
		drop_data[i][drop_object] = CreateDynamicObject(
			GetItemDropObjectModel(playerid, slot), 
			x, 
			y, 
			z, 
			0.0, 
			0.0, 
			0.0,
			GetPlayerVirtualWorld(playerid),
			character_data[playerid][c_int],
			_,
			100
		);
		
		if (IsInventoryTypeShow(playerid, TEXTDRAW_INVENTORY) 
		&& IsInventoryTextDrawShowed(playerid))
		{
			ShowInventoryTextdraw(playerid, false);
		}
		
		SetPVarInt(playerid, "Drop:Index", i);
		SetPVarInt(playerid, "Drop:Slot", slot);
		SetPVarInt(playerid, "Drop:Edit", true);
		
		Streamer_Update(playerid);
		
		EditDynamicObject(playerid, drop_data[i][drop_object]);
		SendClientMessage(playerid, C_WHITE, !HELP_EDITOR);
		return 1;
	}

	return 0;
}

InventoryTakeItem(playerid, index)
{
	if (drop_data[index][drop_item_id] == 0)
	{
		return INVALID_PARAM;
	}
	
	if (playerid != INVALID_PLAYER_ID 
	&& !CheckInventoryFreeForItem(playerid, drop_data[index][drop_item_id]))
	{
		return INVALID_PARAM;
	}
	
	new itindex = GetItemIndexById(drop_data[index][drop_item_id]),
		sindex;
	
	if (playerid != INVALID_PLAYER_ID)
	{
		if (!GetPVarInt(playerid, "Drop:BagTake") 
		&& item_list[itindex][it_type] == INV_BAG)
		{	
			SetPVarInt(playerid, "Drop:TakeIndex", index);
			SetPVarInt(playerid, "Drop:Model", item_list[itindex][it_model]);
			
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " В данной сумке находятся предмет, необходимо прикрепить заранее её к персонажу.");
			ShowPlayerDialog(playerid, D_INV + 15, DIALOG_STYLE_LIST, " ", DIALOG_INV_BONE, "Выбрать", "Закрыть");
			return 1;
		}
	}
	
	if ((item_list[itindex][it_type] == INV_ATTACH 
	&& item_list[itindex][it_param_1] == INV_FUNC_SOUND)
	&& IsValidDynamicArea(drop_data[index][drop_area]))
	{
		if (playerid != INVALID_PLAYER_ID 
		&& GetPlayerIdByCharacterId(drop_data[index][drop_character_id]) != playerid)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Это бумбокс не принадлежит Вам.");
			return 1;
		}
		
		foreach (new i : Player)
		{
			if (IsPlayerInDynamicArea(i, drop_data[index][drop_area]))
			{
				StopAudioStreamForPlayer(i);
			}
		}
		
		DestroyDynamicArea(drop_data[index][drop_area]);
	}
	
	if (IsValidDynamic3DTextLabel(drop_data[index][drop_label]))
	{
		DestroyDynamic3DTextLabel(drop_data[index][drop_label]);
	}
	
	drop_data[index][drop_label] = Text3D: INVALID_3DTEXT_ID;
	
	if (IsValidDynamicObject(drop_data[index][drop_object]))
	{
		DestroyDynamicObject(drop_data[index][drop_object]);
	}
	
	if (playerid != INVALID_PLAYER_ID)
	{
		GiveInventoryItem(playerid, drop_data[index][drop_item_id], drop_data[index][drop_item_param_1], drop_data[index][drop_item_param_2]);
	}
	
	Clear:drop_data(index);
	
	return sindex;
}

ActionDataInventorySlot(playerid, action, oldslot, newslot = INVALID_PARAM, const id, type)
{
	new itindex,
		bool: is_exists = false,
		type_inv = (newslot == INVALID_PARAM) ? DIALOG_INVENTORY : TEXTDRAW_INVENTORY;

	if (type_inv == DIALOG_INVENTORY)
	{
		for (newslot = 0; newslot < MAX_INVENTORY_SLOTS; newslot++)
		{
			if (action == INV_ACTION_TAKE)
			{
				if (!inv_data[playerid][newslot][inv_item_id])
				{
					is_exists = true;
					break;
				}
			}
			else if (action == INV_ACTION_PUT)
			{
				if (type == TYPE_INV_VEHICLE)
				{
					if (GetVehicleInfo(vehicle_data[id][v_model], v_max_slots) <= newslot)
					{
						break;
					}
				}
				else if (type == TYPE_INV_FURN) 
				{
					if (furniture_list[furn_data[id][f_item_index]][fitem_slot] <= newslot)
					{
						break;
					}
				}
				else if (type == TYPE_INV_VEH_GLOVE)
				{
					if (GetVehicleInfo(vehicle_data[id][v_model], v_comp_max_slots) <= newslot)
					{
						break;
					}
				}
				else if (type == TYPE_INV_BAG)
				{
					itindex = GetItemIndexById(GetInventoryEnumItem(playerid, oldslot, TYPE_INV_PLAYER, inv_item_id));
					if (item_list[itindex][it_param_1] <= newslot)
					{
						break;
					}
				}
				
				if (GetInventoryEnumItem(id, newslot, type, inv_item_id) == 0)
				{
					is_exists = true;
					break;
				}
			}
		}
	}
	
	/// Если нет свободного слота и инвентарь на диалогах
	if (!is_exists && type_inv == DIALOG_INVENTORY)
	{
		SendClientMessage(playerid, C_WHITE, !ERROR_NO_USE);
		return 0;
	}

	if (action == INV_ACTION_TAKE)
	{	
		Clear:inv_data_slot(playerid, newslot, TYPE_INV_PLAYER);
		
		if (type == TYPE_INV_VEHICLE)
		{
			inv_data[playerid][newslot][inv_id] = vehicle_inv_data[id][oldslot][inv_id];
			inv_data[playerid][newslot][inv_item_id] = vehicle_inv_data[id][oldslot][inv_item_id];
			inv_data[playerid][newslot][inv_param_1] = vehicle_inv_data[id][oldslot][inv_param_1];
			inv_data[playerid][newslot][inv_param_2] = vehicle_inv_data[id][oldslot][inv_param_2];
			
			if (GetVehicleSlotIsAttached(id, oldslot))
			{
				InventoryVehicleUnattach(playerid, id, oldslot);
			}
			
		}
		else if (type == TYPE_INV_BAG)
		{
			inv_data[playerid][newslot][inv_id] = bag_inv_data[id][oldslot][inv_id];
			inv_data[playerid][newslot][inv_item_id] = bag_inv_data[id][oldslot][inv_item_id];
			inv_data[playerid][newslot][inv_param_1] = bag_inv_data[id][oldslot][inv_param_1];
			inv_data[playerid][newslot][inv_param_2] = bag_inv_data[id][oldslot][inv_param_2];
		}
		else if (type == TYPE_INV_FURN)
		{
			inv_data[playerid][newslot][inv_id] = furn_inv_data[id][oldslot][inv_id];
			inv_data[playerid][newslot][inv_item_id] = furn_inv_data[id][oldslot][inv_item_id];
			inv_data[playerid][newslot][inv_param_1] = furn_inv_data[id][oldslot][inv_param_1];
			inv_data[playerid][newslot][inv_param_2] = furn_inv_data[id][oldslot][inv_param_2];
		}
		else if (type == TYPE_INV_VEH_GLOVE)
		{
			inv_data[playerid][newslot][inv_id] = veh_comp_inv_data[id][oldslot][inv_id];
			inv_data[playerid][newslot][inv_item_id] = veh_comp_inv_data[id][oldslot][inv_item_id];
			inv_data[playerid][newslot][inv_param_1] = veh_comp_inv_data[id][oldslot][inv_param_1];
			inv_data[playerid][newslot][inv_param_2] = veh_comp_inv_data[id][oldslot][inv_param_2];
		}
		
		Update:item_data(id, oldslot, type, GetInventoryOwnerId(playerid, TYPE_INV_PLAYER), newslot, TYPE_INV_PLAYER);
		
		Clear:inv_data_slot(id, oldslot, type);
		
		if (type_inv == TEXTDRAW_INVENTORY)
		{
			UpdateInventorySlotModel(playerid, newslot, TYPE_INV_PLAYER);
			UpdateInventorySlotModel(playerid, oldslot, type, id);
		}
	}
	else if (action == INV_ACTION_PUT)
	{
		if (CheckInventoryServiceItem(playerid, oldslot) && type != TYPE_INV_VEH_GLOVE)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете передать служебный предмет.");
			return 1;
		}
			
		itindex = GetItemIndexById(GetInventoryEnumItem(playerid, oldslot, TYPE_INV_PLAYER, inv_item_id));
		
		Clear:inv_data_slot(id, newslot, type);
		
		if (type == TYPE_INV_VEHICLE)
		{
			vehicle_inv_data[id][newslot][inv_id] = inv_data[playerid][oldslot][inv_id];
			vehicle_inv_data[id][newslot][inv_item_id] = inv_data[playerid][oldslot][inv_item_id];
			vehicle_inv_data[id][newslot][inv_param_1] = inv_data[playerid][oldslot][inv_param_1];
			vehicle_inv_data[id][newslot][inv_param_2] = inv_data[playerid][oldslot][inv_param_2];
			
			/// Attach item
			if (GetPVarInt(playerid, "Inventory:VehicleAttach"))
			{
				if (!InventoryVehicleAttach(playerid, id, newslot))
				{
					SendClientMessage(playerid, C_WHITE, !ERROR_NO_USE);
					return 1;
				}
			}
		}
		else if (type == TYPE_INV_BAG)
		{
			bag_inv_data[id][newslot][inv_id] = inv_data[playerid][oldslot][inv_id];
			bag_inv_data[id][newslot][inv_item_id] = inv_data[playerid][oldslot][inv_item_id];
			bag_inv_data[id][newslot][inv_param_1] = inv_data[playerid][oldslot][inv_param_1];
			bag_inv_data[id][newslot][inv_param_2] = inv_data[playerid][oldslot][inv_param_2];
		}
		else if (type == TYPE_INV_FURN)
		{
			furn_inv_data[id][newslot][inv_id] = inv_data[playerid][oldslot][inv_id];
			furn_inv_data[id][newslot][inv_item_id] = inv_data[playerid][oldslot][inv_item_id];
			furn_inv_data[id][newslot][inv_param_1] = inv_data[playerid][oldslot][inv_param_1];
			furn_inv_data[id][newslot][inv_param_2] = inv_data[playerid][oldslot][inv_param_2];
		}
		else if (type == TYPE_INV_VEH_GLOVE)
		{
			veh_comp_inv_data[id][newslot][inv_id] = inv_data[playerid][oldslot][inv_id];
			veh_comp_inv_data[id][newslot][inv_item_id] = inv_data[playerid][oldslot][inv_item_id];
			veh_comp_inv_data[id][newslot][inv_param_1] = inv_data[playerid][oldslot][inv_param_1];
			veh_comp_inv_data[id][newslot][inv_param_2] = inv_data[playerid][oldslot][inv_param_2];
		}

		/// For special items
		if (item_list[itindex][it_type] == INV_PHONE)
		{
			new index = GetPhoneIndexById(inv_data[playerid][oldslot][inv_param_1]);
			phone_data[index][ph_player_id] = INVALID_PLAYER_ID;
		}
		
		// Slot back
		if (IsWeaponStaticAttach(item_list[itindex][it_param_1])
		&& IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ATTACH_BACK))
		{
			RemovePlayerAttachedObject(playerid, SLOT_ATTACH_BACK);
		}
		
		/// Other
		InventoryUnuseItem(playerid, oldslot, false, true);
		Update:item_data(playerid, oldslot, TYPE_INV_PLAYER, GetInventoryOwnerId(id, type), newslot, type);
		Clear:inv_data_slot(playerid, oldslot, TYPE_INV_PLAYER);
		
		if (type_inv == TEXTDRAW_INVENTORY)
		{
			UpdateInventorySlotModel(playerid, oldslot, TYPE_INV_PLAYER);
			UpdateInventorySlotModel(playerid, newslot, type, id);
		}
	}
	
	return 1;
}

// Other function

/// *Item
GetItemIndexById(_: item_id)
{
	for (new i; i < sizeof item_list; i++)
	{
		if (item_id == item_list[i][it_id])
		{
			return i;
		}
	}
	
	return INVALID_ITEM_ID;
}

GetItemWeaponIndexByParam(param_1)
{
	for (new i; i < sizeof item_list; i++)
	{
		if ((item_list[i][it_type] == INV_WEAPON_BIG || item_list[i][it_type] == INV_WEAPON_SMALL) 
			&& param_1 == item_list[i][it_param_1])
		{
			return i;
		}
	}
	
	return INVALID_ITEM_ID;
}

GetItemModel(const id, slot, type)
{
	new item = GetItemIndexById(GetInventoryEnumItem(id, slot, type, inv_item_id)),
		param;

	switch(item_list[item][it_type])
	{
		case INV_ATTACH, INV_SKIN :
		{
			if ((param = GetInventoryEnumItem(id, slot, type, inv_param_1)) != 0)
			{
				return param;
			}
		}
	}
	
	return item_list[item][it_model];
}

GetItemDropObjectModel(id, slot, type = TYPE_INV_PLAYER)
{
	new item = GetItemIndexById(GetInventoryEnumItem(id, slot, type, inv_item_id)),
		item_type = item_list[item][it_type];
		
	if (item_type == INV_SKIN)
	{
		return random(2) ? 2386 : 2384;
	}
	
	return GetItemModel(id, slot, type);
}

IsItemWeaponBig(id, slot, type)
{
	return item_list[GetItemIndexById(GetInventoryEnumItem(id, slot, type, inv_item_id))][it_type] == INV_WEAPON_BIG;
}

IsValidItem(playerid, slot, item_type, item_type_2 = INVALID_PARAM)
{	
	new item = GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id));
		
	if (!(INVALID_ITEM_ID < item < sizeof item_list))
	{
		return 0;
	}
	
	if (item == INVALID_ITEM_ID)
	{
		return 0;
	}
	
	if (item_type_2 == INVALID_PARAM)
	{
		if (item_list[item][it_type] != item_type)
		{
			return 0;
		}
	}
	else 
	{
		if (item_list[item][it_type] != item_type 
		&& item_list[item][it_type] != item_type_2)
		{
			return 0;
		}
	}
	
	return 1;
}

IsWeaponCold(playerid, slot)
{
	switch(item_list[GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id))][it_param_1])
	{
		case WEAPON_GOLFCLUB,
			 WEAPON_NITESTICK,
			 WEAPON_KNIFE,
			 WEAPON_BAT,
			 WEAPON_SHOVEL,
			 WEAPON_KATANA :
		{
			return 1;
		}
	}
	
	return 0;
}

IsItemExists(const id, index, type)
{
	if (index == INVALID_PARAM)
	{
		return 0;
	}
	
	if (!GetInventoryEnumItem(id, index, type, inv_item_id))
	{
		return 0;
	}
	
	return 1;
}

/// *Inventory
GetInventoryOwnerId(const id, type)
{
	if (type == TYPE_INV_PLAYER)
	{
		if (!IsPlayerLogged(id))
		{
			return INVALID_PARAM;
		}
		
		return GetCharacterId(id);
	}
	else if (type == TYPE_INV_VEHICLE || type == TYPE_INV_VEH_GLOVE)
	{
		if (!(0 < id <= GetVehiclePoolSize()))
		{
			return INVALID_PARAM;
		}
		
		return GetVehicleId(id);
	}
	else if (type == TYPE_INV_BAG)
	{
		if (!(0 <= id < MAX_BAGS))
		{
			return INVALID_PARAM;
		}
		
		return GetBagId(id);
	}
	else if (type == TYPE_INV_FURN)
	{
		if (!(0 <= id < MAX_FURN_OBJECTS))
		{
			return INVALID_PARAM;
		}
		
		return furn_data[id][f_id];
	}
	
	return INVALID_PARAM;
}

GetInventoryTypeSlot(id, slot, type = TYPE_INV_PLAYER)
{
	if (type == TYPE_INV_PLAYER)
	{
		if (inv_data[id][slot][inv_use_slot])
		{
			return ACTIVE_SLOT;
		}
	}

	if (IsItemWeaponBig(id, slot, type))
	{
		return WEAPON_BIG_SLOT;
	}
	
	return DEFAULT_SLOT;
}

/// --

GetInventoryIndexById(playerid, id)
{
	for (new i; i < MAX_INVENTORY_SLOTS; i++)
	{
		if (GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_id) == id)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

GetInventoryTypeItemCount(playerid, type, bool: is_use)
{
	new count;
		
	for (new i, itindex; i < MAX_INVENTORY_SLOTS; i++)
	{		
		if (is_use && !GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_use_slot))
		{
			continue;
		}
		
		itindex = GetItemIndexById(GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id));
		if (type == item_list[itindex][it_type])
		{
			count++;
		}
	}
	
	return count;
}

GetInventorySlotByWeaponId(playerid, weaponid)
{
	new item;
		
	for (new i; i < MAX_INVENTORY_SLOTS; i++)
	{
		if (!GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_use_slot))
		{
			continue;
		}
		
		item = GetItemIndexById(GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id));
		
		if (item == INVALID_ITEM_ID)
		{
			continue;
		}
		
		if (item_list[item][it_type] != INV_WEAPON_BIG 
		&& item_list[item][it_type] != INV_WEAPON_SMALL)
		{
			continue;
		}
		
		if (item_list[item][it_param_1] != weaponid)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

GetInventoryTypeItemExists(id, type = TYPE_INV_PLAYER, item_type, item_param_1 = INVALID_PARAM, bool: is_use = false)
{
	for (new i, itindex; i < MAX_INVENTORY_SLOTS; i++)
	{
		if (is_use && !GetInventoryEnumItem(id, i, type, inv_use_slot))
		{
			continue;
		}
		
		if ((itindex = GetItemIndexById(GetInventoryEnumItem(id, i, type, inv_item_id))) == INVALID_PARAM)
		{
			continue;
		}
		
		if (item_list[itindex][it_type] != item_type)
		{
			continue;
		}
		
		if (item_param_1 != INVALID_PARAM && item_list[itindex][it_param_1] != item_param_1)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

/// GiveInventory
GiveInventoryItem(playerid, _: item_id, _: item_param_1 = 0, _: item_param_2 = 0)
{
	new item = GetItemIndexById(item_id),
		type = item_list[item][it_type];
		
	if (!(0 < item < sizeof item_list))
	{
		return INVALID_PARAM;
	}
	
	// регулируем количество типовых предметов
	if (GetInventoryTypeItemCount(playerid, type, false) >= GetInventoryMaxTypeItems(type, false))
	{
		return INVALID_PARAM;
	}
	
	for (new i; i < MAX_INVENTORY_SLOTS; i++)
	{
		if (GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id))
		{
			continue;
		}
		
		Clear:inv_data_slot(playerid, i, TYPE_INV_PLAYER);
		
		inv_data[playerid][i][inv_item_id] = item_id;
		inv_data[playerid][i][inv_use_slot] = 0;
		
		if (item_list[item][it_type] == INV_PHONE) // Recreate phone (Transfer to player)
		{
			if (item_param_1 == 0)
			{
				Create:phone_data(playerid, i, TYPE_INV_PLAYER, item_param_2);
			}
			else
			{
				Recreate:phone_data(playerid, i, TYPE_INV_PLAYER, item_param_1);
			}
		}
		else if (item_list[item][it_type] == INV_BAG && item_param_1 != 0) // Recreate bag (Transfer to player)
		{
			Recreate:item_data(playerid, i, TYPE_INV_PLAYER, item_param_1);
		}
		else // Default
		{
			inv_data[playerid][i][inv_param_1] = item_param_1;
			inv_data[playerid][i][inv_param_2] = item_param_2;
			Create:item_data(playerid, i, TYPE_INV_PLAYER);
		}
		
		if (IsInventoryTextDrawShowed(playerid))
		{
			UpdateInventorySlotModel(playerid, i);
		}
		
		printf("[INVENTORY][LOG]: Item %d[Param: %d] has been added where inventory %s[%d].",
			item_id,
			item_param_1,
			GetCharacterName(playerid),
			GetCharacterId(playerid)
		);
		
		return i;
	}
	
	return INVALID_PARAM;
}

GiveInventoryWeapon(playerid, index, bool: is_use = false)
{
	new itindex;
	
	if ((itindex = GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id))) == INVALID_ITEM_ID)
	{
		return 0;
	}
	
	if (item_list[itindex][it_type] != INV_WEAPON_BIG 
	&& item_list[itindex][it_type] != INV_WEAPON_SMALL)
	{
		return 0;
	}
	
	if (is_use && !GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_use_slot))
	{
		return 0;
	}
	
	if (IsWeaponCold(playerid, index))
	{
		SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1, 1);
	}
	else 
	{
		if (GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1) <= 0)
		{
			SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1, 0);
		}
	}
	
	RemovePlayerWeapon(playerid, item_list[itindex][it_param_1]);
	GivePlayerWeapon(playerid, item_list[itindex][it_param_1], GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1));
	
	if (!GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_use_slot))
	{
		SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_use_slot, true);
		Update:item_data(playerid, index, TYPE_INV_PLAYER);
	}
	
	return 1;
}

GiveInventoryAmmo(playerid, slot)
{
	new item_ammo_id = GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id),
		item_weapon;
	
	for (new i; i < MAX_INVENTORY_SLOTS; i++)
	{
		if (!GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_use_slot))
		{
			continue;
		}
		
		item_weapon = GetItemIndexById(GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id));
		
		if (item_weapon == INVALID_ITEM_ID)
		{
			continue;
		}
		
		if (item_list[item_weapon][it_type] != INV_WEAPON_BIG 
		&& item_list[item_weapon][it_type] != INV_WEAPON_SMALL)
		{
			continue;
		}
		
		if (item_ammo_id != item_list[item_weapon][it_param_2])
		{
			continue;
		}
		
		SetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_param_1, 
			GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_param_1) 
			+ GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_1) 
		);
		
		SetPlayerAmmo(playerid, item_list[item_weapon][it_param_1], 
			GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_param_1) 
		);
		
		return 1;
	}
	
	return 0;
}

GiveInventoryAmmoForWeapon(playerid, slot_ammo, slot_weapon)
{
	new item_ammo = GetItemIndexById(GetInventoryEnumItem(playerid, slot_ammo, TYPE_INV_PLAYER, inv_item_id)),
		item_weapon = GetItemIndexById(GetInventoryEnumItem(playerid, slot_weapon, TYPE_INV_PLAYER, inv_item_id));
		
	if (item_ammo == INVALID_ITEM_ID || item_weapon == INVALID_ITEM_ID)
	{
		return 0;
	}
	
	if (item_list[item_weapon][it_type] != INV_WEAPON_BIG 
	&& item_list[item_weapon][it_type] != INV_WEAPON_SMALL)
	{
		return 0;
	}
	
	if (item_list[item_ammo][it_id] != item_list[item_weapon][it_param_2])
	{
		return 0;
	}
		
	SetInventoryEnumItem(playerid, slot_weapon, TYPE_INV_PLAYER, inv_param_1, 
		GetInventoryEnumItem(playerid, slot_weapon, TYPE_INV_PLAYER, inv_param_1) 
		+ GetInventoryEnumItem(playerid, slot_ammo, TYPE_INV_PLAYER, inv_param_1) 
	);
	
	SetPlayerAmmo(playerid, item_list[item_weapon][it_param_1], 
		GetInventoryEnumItem(playerid, slot_weapon, TYPE_INV_PLAYER, inv_param_1) 
	);
	
	RemoveInventoryItem(playerid, slot_ammo, true);
	
	return 1;
}

/// RemoveInventory
RemoveInventoryItem(playerid, _: index, bool: fully = true, bool: fully_in_game = true)
{
	if (!(0 <= index < MAX_INVENTORY_SLOTS) 
	|| GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id) == 0)
	{
		return 0;
	}	
	
	new itindex = GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id)),
		bool: is_deleted = false;
	
	switch(item_list[itindex][it_type])
	{
		case INV_BAG :
		{
			ShowAdditionalTextdraw(playerid, false);
			Remove:bag(playerid, index, fully, fully_in_game);
			is_deleted = true;
		}
		
		case INV_ATTACH :
		{
			InventoryUnuseItem(playerid, index, false, true);
		}
	
		case INV_WEAPON_SMALL, INV_WEAPON_BIG :
		{
			new used = GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_use_slot);
				
			if (used == TYPE_USE_DEFAULT)
			{
				RemoveInventoryWeapon(playerid, index, false);
				
			}
			else if (used == TYPE_USE_ATTACH && IsAttachExists(playerid, index, TYPE_INV_PLAYER))
			{
				RemoveAttachItemBySlot(playerid, index);
			}
			
			if (IsWeaponStaticAttach(item_list[itindex][it_param_1])
			&& IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ATTACH_BACK))
			{
				RemovePlayerAttachedObject(playerid, SLOT_ATTACH_BACK);
			}
		}
		
		case INV_PHONE :
		{
			Remove:phone_data(playerid, index, TYPE_INV_PLAYER, fully, fully_in_game);
		}
	}
	
	if (!is_deleted)
	{
		Remove:item_data(playerid, index, TYPE_INV_PLAYER);
	}
	
	printf("[INVENTORY][LOG]: Item %d - %s [Param: %d] has been removed where inventory %s[%d].",
		item_list[itindex][it_id],
		item_list[itindex][it_name],
		GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1),
		GetCharacterName(playerid),
		GetCharacterId(playerid)
	);
	
	Clear:inv_data_slot(playerid, index, TYPE_INV_PLAYER);
	
	UpdateInventory(playerid, index);
	
	return 1;
}

RemoveInventoryFractionWeapon(playerid)
{
	new itindex,
		param;
		
	for (new i; i < MAX_INVENTORY_SLOTS; i++)
	{
		itindex = GetItemIndexById(GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id));
		param = item_list[itindex][it_param_1]; // id оружия
		
		if (itindex == INVALID_ITEM_ID 
		|| (item_list[itindex][it_type] != INV_WEAPON_BIG 
		&& item_list[itindex][it_type] != INV_WEAPON_SMALL))
		{
			continue;
		}
		
		if (GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_param_2) != INVENTORY_FRACTION_ITEM)
		{
			continue;
		}
		
		RemovePlayerWeapon(playerid, param);
		RemoveInventoryItem(playerid, i);
	}
}

RemoveInventoryWeapon(playerid, index, bool: is_save = true, bool: is_use_slot = true)
{
	if (!GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_use_slot))
	{
		return 0;
	}
	
	new itindex = GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id)),
		param = item_list[itindex][it_param_1]; // id оружия
		
	if (itindex == INVALID_ITEM_ID 
	|| (item_list[itindex][it_type] != INV_WEAPON_BIG 
	&& item_list[itindex][it_type] != INV_WEAPON_SMALL))
	{
		return 0;
	}

	RemovePlayerWeapon(playerid, param);
	
	if (is_use_slot)
	{
		SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_use_slot, false);
	}
	
	if (is_save)
	{
		Update:item_data(playerid, index, TYPE_INV_PLAYER, _, _, _, true);
	}

	return 1;
}

/// Other
IsInventorySlotFreeExists(id, type = TYPE_INV_PLAYER)
{
	for (new i; i < MAX_INVENTORY_SLOTS; i++)
	{
		if (!GetInventoryEnumItem(id, i, type, inv_item_id))
		{
			return 1;
		}
	}
	
	return 0;
}

IsInventoryItemExistsByType(id, inv_type = TYPE_INV_PLAYER, index, type) 
{ 
	new item_id = GetInventoryEnumItem(id, index, inv_type, inv_item_id), 
	itindex = GetItemIndexById(item_id); 

	return (item_list[itindex][it_type] == type); 
}

GiveInventoryWeapons(playerid)
{
	for (new i; i < MAX_INVENTORY_SLOTS; i++)
	{
		GiveInventoryWeapon(playerid, i, true);
	}
}

HideInventoryWeapons(playerid, bool: is_use = true)
{
	for (new i; i < MAX_INVENTORY_SLOTS; i++)
	{
		RemoveInventoryWeapon(playerid, i, _, is_use);
	}
}

CheckInventoryFreeForItem(playerid, _: item_id)
{
	new item = GetItemIndexById(item_id),
		type = item_list[item][it_type];
		
	if (!(0 < item < sizeof item_list))
	{
		return 0;
	}
	
	if (GetInventoryTypeItemCount(playerid, type, false) >= GetInventoryMaxTypeItems(type, false))
	{
		return 0;
	}
	
	new count;
	
	for (new i; i < MAX_INVENTORY_SLOTS; i++)
	{
		if (GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_id) != 0)
		{
			count++;
		}
	}
	
	return count >= MAX_INVENTORY_SLOTS ? 0 : 1;
}

CheckActionSlot(playerid, slot, item_type, item_type_2 = INVALID_PARAM)
{
	if (!IsItemExists(playerid, slot, TYPE_INV_PLAYER) 
	|| !IsValidItem(playerid, slot, item_type, item_type_2))
	{
		if (GetPVarInt(playerid, "Inventory:States"))
		{
			UpdateInventorySlotModel(playerid, slot);
			UpdateInventorySelect(playerid, inventory_td_select[playerid], false, slot);
		}
		
		return 0;
	}
	
	return 1;
}

/// Show inventory
ShowInventory(playerid, type = TEXTDRAW_INVENTORY, bool: is_update_textdraw_inv = false)
{
	if (IsInterfaceActive(playerid) && !is_update_textdraw_inv)
	{
		SendClientMessage(playerid, C_WHITE, !ERROR_INTERFACE);
		return 1;
	}
	
	if (GetPVarInt(playerid, "Drop:Edit") 
	|| GetPVarInt(playerid, "VehicleAttach:Edit"))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете использовать инвентарь, поскольку Вы редактируете объект.");
		return 1;
	}
	
	if (GetCharacterDeath(playerid) != TYPE_DEATH_NONE)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACTION);
		return 1;
	}
	
	new i,
		v = GetVehiclePoolSize(),
		id = INVALID_PARAM,
		type_inv = TYPE_INV_PLAYER,
		show_slots = MAX_INVENTORY_SLOTS,
		Float: x,
		Float: y,
		Float: z,
		str_dialog_inv_name				[		64			],
		str_textdraw_inv_name			[		64 			],
		itindex,
		seat;
	
	for (i = 0; i < sizeof drop_data; i++)
	{
		if (drop_data[i][drop_item_id] == 0 
		|| !drop_data[i][drop_use_inv])
		{
			continue;
		}
		
		if (!IsPlayerInRangeOfPoint(playerid, 1.5, 
		drop_data[i][drop_pos_x], 
		drop_data[i][drop_pos_y],
		drop_data[i][drop_pos_z])
		|| IsPlayerInAnyVehicle(playerid))
		{
			continue;
		}
		
		itindex = GetItemIndexById(drop_data[i][drop_item_id]);
		id = GetBagIndexById(drop_data[i][drop_item_param_1]);
		type_inv = TYPE_INV_BAG;
		show_slots = item_list[itindex][it_param_1];
		
		format:str_dialog_inv_name("Взаимодействие с " #cPROJECT "%s", item_list[itindex][it_name]);
		str_textdraw_inv_name[0] = EOS;
		strcat(str_textdraw_inv_name, "Dropped Bag");
		break;
	}
	
	// Определяем инвентарь транспорта
	for (i = 1; i <= v; i++)
	{
		if (IsPlayerInVehicle(playerid, i))
		{
			seat = GetPlayerVehicleSeat(playerid);
			if (seat != 0 && seat != 1)
			{
				continue;
			}
			
			if (vehicle_data[i][v_owner_type] == TYPE_VEH_FRACTION)
			{
				new fraction_id = GetFractionMemberId(playerid);
				if (vehicle_data[i][v_owner_id] != fraction_id 
				|| !CheckFractionAccess(playerid, fr_perm_vehicle)
				|| !CheckFractionDuty(playerid))
				{
					continue;
				}
			}
			
			id = i;
			type_inv = TYPE_INV_VEH_GLOVE;
			str_dialog_inv_name[0] = EOS;
			show_slots = GetVehicleInfo(vehicle_data[i][v_model], v_comp_max_slots);
			strcat(str_dialog_inv_name, GetVehicleInfo(vehicle_data[i][v_model], v_name));
			
			format:str_dialog_inv_name("Взаимодействие с " #cPROJECT "%s" #cGRAY " (Бардачок)", 
				GetVehicleInfo(vehicle_data[i][v_model], v_name) 
			);
			
			format:str_textdraw_inv_name("%s", 
				GetVehicleInfo(vehicle_data[i][v_model], v_name) 
			);
			break;
		}
		else if (!IsPlayerInAnyVehicle(playerid))
		{
			if (GetPlayerVirtualWorld(playerid) != GetVehicleVirtualWorld(i))
			{
				continue;
			}
			
			if (!IsVehicleStreamedIn(i, playerid))
			{
				continue;
			}

			GetVehicleComponentPos(i, true, x, y, z);
			if (!IsPlayerInRangeOfPoint(playerid, 0.5, x, y, z))
			{
				continue;
			}
			
			if (vehicle_data[i][v_boot] != VEHICLE_PARAMS_ON)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Для использования багажника, необходимо его открыть. " #cGRAY "(/boot)");
				return 1;
			}
			
			id = i;
			type_inv = TYPE_INV_VEHICLE;
			str_dialog_inv_name[0] = EOS;
			show_slots = GetVehicleInfo(vehicle_data[i][v_model], v_max_slots);
			
			format:str_dialog_inv_name("Взаимодействие с " #cPROJECT "%s" #cGRAY " (Багажник)", 
				GetVehicleInfo(vehicle_data[i][v_model], v_name) 
			);
			
			format:str_textdraw_inv_name("%s", 
				GetVehicleInfo(vehicle_data[i][v_model], v_name) 
			);
			break;
		}
	}
	
	for (i = 0; i < MAX_FURN_OBJECTS; i++)
	{
		if (!IsPlayerInRangeOfPoint(playerid, 1.5, 
			furn_data[i][f_pos_x], 
			furn_data[i][f_pos_y],
			furn_data[i][f_pos_z])
		)
		{
			continue;
		}
		
		if (furniture_list[furn_data[i][f_item_index]][fitem_slot] == 0)
		{
			continue;
		}
		
		if (!CheckHouseAccess(TYPE_HOUSE_LODGER, playerid, furn_data[i][f_owner_index], lod_perm_inventory))
		{
			continue;
		}
		
		if (GetCharacterInt(playerid) != INT_HOUSE 
		&& GetCharacterWorld(playerid) != GetHouseId(furn_data[i][f_owner_index]))
		{
			continue;
		}
		
		id = i;
		type_inv = TYPE_INV_FURN;
		str_dialog_inv_name[0] = EOS;
		show_slots = furniture_list[furn_data[i][f_item_index]][fitem_slot];

		format:str_dialog_inv_name("Взаимодействие с " #cPROJECT "%s", 
			furniture_list[furn_data[i][f_item_index]][fitem_name]
		);
		
		format:str_textdraw_inv_name("Furniture #%i", 
			furn_data[i][f_id]
		);
		break;
	}
	
	// Определяем инвентарь сумки
	if (id == INVALID_PARAM && type_inv == TYPE_INV_PLAYER)
	{
		new slot = GetInventorySlotBag(playerid, TYPE_INV_PLAYER), 
			index = GetBagIndexBySlot(playerid, slot, TYPE_INV_PLAYER);

		if (slot != INVALID_PARAM && index != INVALID_PARAM)
		{
			if (GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_use_slot))
			{
				itindex = bag_data[index][bag_type];
				id = index;
				type_inv = TYPE_INV_BAG;
				show_slots = item_list[itindex][it_param_1];
				
				format:str_dialog_inv_name("Взаимодействие с " #cPROJECT "%s", 
					item_list[itindex][it_name]
				);
				
				clean:<str_textdraw_inv_name>;
				strcat(str_textdraw_inv_name, "Bag");
			}
		}
	}
	
	SetPVarInt(playerid, "Inventory:TypeInv", type_inv);
	SetPVarInt(playerid, "Inventory:Id", id);

	if (type == TEXTDRAW_INVENTORY)
	{	
		if (is_update_textdraw_inv)
		{
			ShowAdditionalTextdraw(playerid, type_inv == TYPE_INV_PLAYER ? false : true, type_inv, str_textdraw_inv_name, id, show_slots);
		}
		else 
		{
			ShowInventoryTextdraw(playerid, true, type_inv, str_textdraw_inv_name, id, show_slots);
		}
	}
	else if (type == DIALOG_INVENTORY)
	{
		if (type_inv != TYPE_INV_PLAYER)
		{	
			format:g_string(" Открыть инвентарь\n \
					[            %s" #cWHITE "            ]\n \
					Положить предмет\n \
					Взять предмет\n",
				 str_dialog_inv_name
			);
			
			if (type_inv == TYPE_INV_VEHICLE)
			{
				strcat(g_string, " Прикрепить предмет");
			}
			
			ShowPlayerDialog(playerid, D_INV - 1, DIALOG_STYLE_LIST, " ", 
				 g_string,
				 "Выбрать", "Закрыть" 
			);
		}
		else
		{
			ShowInventoryDialog(playerid);
		}
	}
	
	return 1;
}

/// Other item typical functions
GetInventoryLighter(playerid)
{
	new itindex;
	
	for (new i; i < MAX_INVENTORY_SLOTS; i++)
	{
		if ((itindex = GetItemIndexById(GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id))) == INVALID_ITEM_ID)
		{
			continue;
		}
		
		if (item_list[itindex][it_type] == INV_LIGHTER)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

GetInventoryDefaultPhone(playerid)
{
	new slot = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_PHONE, _, true),
		index = GetPhoneIndexBySlot(playerid, slot);
		
	return index;
}

ResetPlayerSkin(playerid)
{
	new race = character_data[playerid][c_race],
		sex = character_data[playerid][c_sex];
	
	if (race == RACE_BLACK)
	{
		return sex ? 139 : 18;
	}
	else if (race == RACE_CAUCASOID)
	{
		return sex ? 138 : 154;
	}
	else
	{
		return sex ? 140 : 97;
	}
}
	
GetInventoryItemValueFormat(item, param_1, param_2, text[128], bool: show_default = false, item_id = INVALID_PARAM)
{
	clean:<text>;
	
	switch(item_list[item][it_type])
	{
		case INV_WEAPON_SMALL, INV_WEAPON_BIG :
		{
			format:text("Патронов: " #cPROJECT "%d",
				param_1
			);
			
			if (item_id != INVALID_PARAM)
			{
				if (param_2 > 0) // Is Legal
				{
					format:g_string("%s, серийный номер: " #cPROJECT "№%05d" #cWHITE ".",
						g_string,
						GetWeaponSerialNumber(item_id)
					);
				}
			}
		}
		
		case INV_AMMO : 
		{
			format:text("Патронов в содержимом: " #cPROJECT "%i" #cWHITE ".",
				param_1
			);
		}
		
		case INV_BAG : 
		{
			format:text("Вместимость до " #cPROJECT "%i предмета(-ов)" #cWHITE ".",
				item_list[item][it_param_1]
			);
		}
		
		case INV_SMOKE :
		{
			format:text("%sСигарет в пачке " #cPROJECT "%i" #cWHITE ".",
				item_list[item][it_param_1]
			);
		}
		
		case INV_SKIN :
		{
			format:text("Номер одежды " #cPROJECT "#%i" #cWHITE ".",
				param_1
			);
		}
		
		default:
		{
			if (show_default)
			{
				format:text("(" #cPROJECT "%d" #cWHITE " | " #cPROJECT "%d" #cWHITE ")",
					param_1,
					param_2
				);
			}
		}
	}
}

CheckInventoryServiceItem(playerid, index)
{
	if (!(0 <= index < MAX_INVENTORY_SLOTS))
	{
		return 0;
	}
	
	new itindex = GetItemIndexById(
		GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id)
	);
	
	switch (item_list[itindex][it_type])
	{
		case INV_ATTACH, INV_RADIO, INV_WEAPON_BIG, INV_WEAPON_SMALL:
		{
			if (GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_2) == INVENTORY_FRACTION_ITEM)
			{
				return 1;
			}
		}
	}
	
	return 0;
}