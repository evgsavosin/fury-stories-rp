/*!
	@brief Диалоги для системы инвентаря
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

function Inv_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		// Взаи	модействие
		case D_INV - 1 :
		{
			if (!response)
			{
				return 1;
			}
			
			if (listitem == 0)
			{
				return ShowInventoryDialog(playerid);
			}
			else if (listitem == 1)
			{
				return ShowInventory(playerid, DIALOG_INVENTORY);
			}
			
			SetPVarInt(playerid, "Inventory:VehicleAttach", false);
			
			listitem = listitem - 2;
			
			if (listitem == 2)
			{
				if (GetPVarInt(playerid, "Drop:Edit") || GetPVarInt(playerid, "VehicleAttach:Edit"))
				{
					DeletePVar(playerid, "Inventory:VehicleAttach");
					return 1;
				}
				
				listitem = INV_ACTION_PUT;
				SetPVarInt(playerid, "Inventory:VehicleAttach", true);
			}
			
			SetPVarInt(playerid, "Inventory:Action", listitem);
			
			ShowInventoryDialog(playerid, 
				listitem == INV_ACTION_PUT ? TYPE_INV_PLAYER : GetPVarInt(playerid, "Inventory:TypeInv"), 
				listitem == INV_ACTION_PUT ? playerid : GetPVarInt(playerid, "Inventory:Id"), 
				D_INV - 2,
				listitem
			);
		}
		
		case D_INV - 2 :
		{
			if (!response)
			{
				DeletePVar(playerid, "Inventory:Action");
				DeletePVar(playerid, "Inventory:VehicleAttach");
				return 1;
			}
			
			new type_inv = GetPVarInt(playerid, "Inventory:TypeInv"),
				id = GetPVarInt(playerid, "Inventory:Id"),
				action = GetPVarInt(playerid, "Inventory:Action");
			
			if (inventory_list_id[playerid][listitem] == INVALID_PARAM)
			{
				return ShowInventoryDialog(playerid, 
					action == INV_ACTION_PUT ? TYPE_INV_PLAYER : type_inv, 
					action == INV_ACTION_PUT ? playerid : id, 
					D_INV - 2,
					action
				);
			}	
			
			SetPVarInt(playerid, "Inventory:Select", inventory_select_slot[playerid][listitem]);
			
			if (GetPVarInt(playerid, "Inventory:AddSelect") == INVALID_PARAM)
			{
				SetPVarInt(playerid, "Inventory:AddSelect", inventory_select_slot[playerid][listitem]);
			}
			
			if (action == INV_ACTION_PUT)
			{
				pformat:("" #SUCCESS " Вы успешно положили предмет " #cPROJECT "%s" #cWHITE ".",
					item_list[GetItemIndexById(GetInventoryEnumItem(playerid, GetPVarInt(playerid, "Inventory:Select"), TYPE_INV_PLAYER, inv_item_id))][it_name]
				);
				
				psend:(playerid, C_WHITE);
			}
			else if (action == INV_ACTION_TAKE)
			{
				pformat:("" #SUCCESS " Вы успешно взяли предмет " #cPROJECT "%s" #cWHITE ".",
					item_list[GetItemIndexById(GetInventoryEnumItem(id, GetPVarInt(playerid, "Inventory:AddSelect"), type_inv, inv_item_id))][it_name]
				);
				
				psend:(playerid, C_WHITE);
			}
			
			if (!ActionDataInventorySlot(playerid, 
				action, 
				GetPVarInt(playerid, "Inventory:Select"), 
				INVALID_PARAM, 
				id, 
				type_inv 
			))
			{
				return 1;
			}
			
			SetPVarInt(playerid, "Inventory:AddSelect", INVALID_PARAM);
			
			ShowInventoryDialog(playerid, 
				action == INV_ACTION_PUT ? TYPE_INV_PLAYER : type_inv, 
				action == INV_ACTION_PUT ? playerid : id, 
				D_INV - 2,
				action
			);
		}
		
		// Player Inventory
		case D_INV :
		{
			if (!response)
			{
				return 1;
			}
			
			if (inventory_list_id[playerid][listitem] == INVALID_PARAM)
			{
				ShowInventoryDialog(playerid);
				return 1;
			}
			else if (inventory_list_id[playerid][listitem] == (sizeof item_list + character_data[playerid][c_skin]))
			{
				cmd_undress(playerid);
				return 1;
			}
			
			if (inventory_select_slot[playerid][listitem] == INVALID_PARAM)
			{
				return 1;
			}
			
			new slot = inventory_select_slot[playerid][listitem],
				item = GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id));
			
			SetPVarInt(playerid, "Inventory:Select", slot);
			
			if (item_list[item][it_type] == INV_WEAPON_SMALL 
			|| item_list[item][it_type] == INV_WEAPON_BIG
			|| item_list[item][it_type] == INV_BAG)
			{
				format:g_string(DIALOG_INV_SELECT, 
					("Действия")
				);
			}
			else 
			{
				format:g_string(DIALOG_INV_SELECT, 
					(!GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_use_slot)) ? ("Использовать") : ("Убрать")
				);
			}
			
			ShowPlayerDialog(playerid, D_INV + 1, DIALOG_STYLE_LIST, item_list[item][it_name], 
				g_string, 
				"Далее", "Назад" 
			);
		}
		
		case D_INV + 1 :
		{
			new slot = GetPVarInt(playerid, "Inventory:Select");
			
			if (!response || !IsItemExists(playerid, slot, TYPE_INV_PLAYER))
			{
				ShowInventoryDialog(playerid);
				return 1;
			}
			
			switch(listitem)
			{
				case 0 : // Информация
				{
					ShowInventoryItemInformation(playerid, slot);
				}
				
				case 1 : // Использовать / убрать
				{
					if (!GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_use_slot))
					{
						if (!InventoryUseItem(playerid, slot))
						{
							return SendClientMessage(playerid, C_WHITE, !#ERROR " Данный предмет нельзя использовать подобным образом.");
						}
					}
					else 
					{
						InventoryUnuseItem(playerid, slot, true, false);
					}
				}
				
				case 2 : // Передача
				{
					ShowPlayerDialog(playerid, D_INV + 3, DIALOG_STYLE_INPUT, item_list[GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id))][it_name], 
						"" #DEFAULT " Передать предмет\n\n\
						Для того, чтобы передать предмет, введите ID игрока:\n\n\
						" #cGRAY "Данный игрок должен находиться рядом с Вами.", 
						"Далее", "Назад" 
					);
				}
				
				case 3 : // Выбросить
				{
					format:g_string("" #DEFAULT " Выбросить предмет\n\n\
						Вы действительно собираетесь выбросить предмет " #cPROJECT "%s" #cWHITE "?",
						item_list[GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id))][it_name]
					);
					
					ShowPlayerDialog(playerid, D_INV + 5, DIALOG_STYLE_MSGBOX, item_list[GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id))][it_name], 
						g_string, 
						"Далее", "Назад" 
					);
				}
				
				case 4 : // Удалить
				{
					format:g_string("" #DEFAULT " Удалить предмет\n\n\
						Вы действительно собираетесь удалить предмет " #cPROJECT "%s" #cGRAY "?",
						item_list[GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id))][it_name]
					);
					
					ShowPlayerDialog(playerid, D_INV + 4, DIALOG_STYLE_MSGBOX, item_list[GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id))][it_name], 
						g_string, 
						"Далее", "Назад" 
					);
				}
			}
		}
		
		case D_INV + 2 :
		{	
			UpdateInventory(playerid, GetPVarInt(playerid, "Inventory:TempSelect"));
		}

		case D_INV + 3 :
		{
			new index = GetPVarInt(playerid, "Inventory:Select");
				
			if (response)
			{
				if (!IsItemExists(playerid, index, TYPE_INV_PLAYER))
				{
					return 1;
				}
				
				new itindex = GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id)),
					item_id = item_list[itindex][it_id];
				
				if (CheckInventoryServiceItem(playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете передать служебный предмет.");
					return 1;
				}
				
				if (isnull(inputtext) || !IsInt(inputtext))
				{
					ShowPlayerDialog(playerid, D_INV + 3, DIALOG_STYLE_INPUT, item_list[itindex][it_name], 
						"" #DEFAULT " Передать предмет\n\n\
						Для того, чтобы передать предмет, введите ID игрока:\n\n\
						" #cGRAY "Данный игрок должен находиться рядом с Вами.", 
						"Далее", "Назад" 
					);
					
					return 1;
				}
			
				new targetid = strval(inputtext),
					param_1 = GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1),
					param_2 = GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_2);
				
				// Check valid player
				if (!IsPlayerLogged(targetid) 
				|| targetid == playerid 
				|| !IsPlayerAroundOfPlayer(playerid, targetid))
				{
					ShowPlayerDialog(playerid, D_INV + 3, DIALOG_STYLE_INPUT, item_list[itindex][it_name], 
						"" #DEFAULT " Передать предмет\n\n\
						Для того, чтобы передать предмет, введите ID игрока:\n\n\
						" #cRED "Вы ввели неверный ID игрока.", 
						"Далее", "Назад" 
					);
					
					return 1;
				}
				
				// Check free slots
				if (!CheckInventoryFreeForItem(targetid, item_id))
				{
					SendClientMessage(playerid, C_WHITE, !ERROR_NO_SLOTS);
					return 1;
				}
				
				// Recreate bag and phone
				new type = item_list[itindex][it_type];
				if (type == INV_BAG)
				{
					param_1 = GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_id);
				}
				
				// Action
				RemoveInventoryItem(playerid, index, true, false);
				GiveInventoryItem(targetid, item_id, param_1, param_2);
				
				// Messages
				pformat:("" #SUCCESS " Вы успешно передали предмет " #cPROJECT "%s" #cWHITE " игроку " #cGREEN "%s" #cWHITE ".",
					item_list[itindex][it_name],
					GetPlayerCurrentName(targetid)
				);
				
				psend:(playerid, C_WHITE);
				
				pformat:("" #SUCCESS " Вы получили предмет " #cPROJECT "%s" #cWHITE " от игрока " #cGREEN "%s" #cWHITE ".",
					item_list[itindex][it_name],
					GetPlayerCurrentName(playerid)
				);
				
				psend:(targetid, C_WHITE);
				
				format:g_small_string("Передал%s предмет - %s.", 
					EndWordSex(playerid),
					GetPlayerCurrentName(targetid) 
				);
				
				SendRPMessage(ACTION_AME, playerid, g_small_string);
				
				format:g_small_string("Получил%s предмет от - %s", 
					EndWordSex(playerid),
					GetPlayerCurrentName(playerid) 
				);
				
				SendRPMessage(ACTION_AME, targetid, g_small_string);
			}
		}
			
		case D_INV + 4 :
		{
			new slot = GetPVarInt(playerid, "Inventory:Select"),
				item;
				
			if (response)
			{
				if (!IsItemExists(playerid, slot, TYPE_INV_PLAYER))
				{
					UpdateInventory(playerid, slot);
					return 1;
				}
				
				item = GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id));
				
				if (!RemoveInventoryItem(playerid, slot))
				{
					SendClientMessage(playerid, C_WHITE, !ERROR_SYSTEM);
					return 1;
				}
				
				format:g_small_string( "(( Удалил предмет '%s' ))",
					item_list[item][it_name]
				);
				
				SetPlayerChatBubble(playerid, g_small_string, 0xFFFFFF50, 25.0, 5000);
				
				pformat:("" #SUCCESS " Вы успешно удалили предмет " #cPROJECT "%s" #cWHITE ".",
					item_list[item][it_name]
				);
				
				psend:(playerid, C_WHITE);
				return 1;
			}
		}

		case D_INV + 5 :
		{
			new index = GetPVarInt(playerid, "Inventory:Select");
				
			if (!response 
			|| !IsItemExists(playerid, index, TYPE_INV_PLAYER) 
			|| GetPVarInt(playerid, "Drop:Edit") 
			|| GetPVarInt(playerid, "VehicleAttach:Edit"))
			{
				UpdateInventory(playerid, index);
				return 1;
			}
			
			if (CheckInventoryServiceItem(playerid, index))
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете выкинуть служебный предмет.");
				return 1;
			}
			
			if (!InventoryDropItem(playerid, index))
			{
				print("[INVENTORY][ERROR]: Limit drop item has been ended.");
				SendClientMessage(playerid, C_WHITE, !#ERROR " Превышен лимит объектов, Вы не можете выбросить объект.");
				return 1;
			}
		}
		
		case D_INV + 6 :
		{
			new index = GetPVarInt(playerid, "Inventory:TempSelect");
	
			if (!response || !CheckActionSlot(playerid, index, INV_WEAPON_SMALL, INV_WEAPON_BIG))
			{
				DeletePVar(playerid, "Inventory:IsColdWeapon");
				UpdateInventory(playerid, index);
				return 1;
			}
			
			if (GetPVarInt(playerid, "Inventory:IsColdWeapon")
			&& listitem == 1)
			{
				DeletePVar(playerid, "Inventory:IsColdWeapon");
				listitem = 3; 
			}
			
			new player_state = GetPlayerState(playerid);
			
			if (player_state == PLAYER_STATE_DRIVER)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете использовать оружие, находясь на месте водителя.");
				UpdateInventory(playerid, index);
				return 1;
			}
			
			if (listitem == 0)
			{
				if (IsWeaponCold(playerid, index))
				{
					SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1, 1);
				}
				
				if (!GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " В данном оружие отсутствуют патроны. Для использования необходимо зарядить.");
					UpdateInventory(playerid, index);
					return 1;
				}
				
				GiveInventoryWeapon(playerid, index);
				UpdateInventory(playerid, index);
			}
			else if (listitem == 1)
			{	
				if (IsWeaponCold(playerid, index))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Недоступно для данного типа оружия.");
					UpdateInventory(playerid, index);
					return 1;
				}
				
				for (new i; i < MAX_INVENTORY_SLOTS; i++)
				{
					if (GiveInventoryAmmoForWeapon(playerid, i, index))
					{
						pformat:("" #SUCCESS " Вы зарядили оружие - " #cPROJECT "%s" #cWHITE ".",
							item_list[GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id))][it_name]
						);
						
						psend:(playerid, C_WHITE);
						UpdateInventory(playerid, index);
						return 1;
					}
				}
				
				SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас нет нужного калибра патрон для зарядки данного оружия.");
			}
			else if (listitem == 2)
			{
				if (IsWeaponCold(playerid, index)
				|| GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_2) == INVENTORY_FRACTION_ITEM)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Недоступно для данного типа оружия.");
					UpdateInventory(playerid, index);
					return 1;
				}
				
				format:g_string("" #DEFAULT " Разрядить\n\n\
					Всего патрон в обойме: " #cPROJECT "%i шт.\n\
					Введите количество патрон, которое Вы хотите разрядить:",
					GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1)
				);
				
				ShowPlayerDialog(playerid, D_INV + 9, DIALOG_STYLE_INPUT, 
					item_list[GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id))][it_name],
					g_string,
					"Далее", "Назад"
				);
			}
			else if (listitem == 3)
			{			
				if (GetItemStaticAttach(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id)) != 0)
				{
					UpdateInventory(playerid, index);
					return 1;
				}
				
				AttachPlayerInventoryItem(playerid, index);
			}
		}
		
		case D_INV + 7 :
		{
			new attach_exists = GetPVarInt(playerid, "Inventory:AttachExists"),
				slot = GetPVarInt(playerid, "Inventory:AttachSlot"),
				bool: is_bag = false;
			
			if (!response || (!CheckActionSlot(playerid, slot, INV_ATTACH, INV_BAG) 
			&& !CheckActionSlot(playerid, slot, INV_WEAPON_SMALL)
			&& (!CheckActionSlot(playerid, slot, INV_WEAPON_BIG) && !IsWeaponCold(playerid, slot))))
			{
				Clear:attach_pvar(playerid);
				UpdateInventory(playerid, slot);
				return 1;
			}
			
			if (GetPVarInt(playerid, "Inventory:AttachType") == BAG_ATTACH 
			&& inventory_attach[playerid][SLOT_ATTACH_BAG] != INVALID_PARAM)
			{
				SetPVarInt(playerid, "Inventory:AttachEditBag", 1);
				is_bag = true;
				listitem++;
			}
			
			if (!is_bag && GetFreeAttachSlot(playerid) == INVALID_PARAM)
			{
				UpdateInventory(playerid, slot);
				SendClientMessage(playerid, C_WHITE, !#ERROR " На Вас максимально доступное количество прикрепленных предметов.");
				return 1;
			}
			
			SetPVarInt(playerid, "Inventory:AttachState", ATTACH_STATE_DEFAULT);
			
			if (attach_exists)
			{	
				if (listitem == 0) // use
				{
					OnInventoryAttachItem(
						playerid, 
						GetPVarInt(playerid, "Inventory:AttachModel"),
						inv_data[playerid][slot][inv_bone],
						inv_data[playerid][slot][inv_pos_x], 
						inv_data[playerid][slot][inv_pos_y], 
						inv_data[playerid][slot][inv_pos_z],
						inv_data[playerid][slot][inv_rot_x], 
						inv_data[playerid][slot][inv_rot_y], 
						inv_data[playerid][slot][inv_rot_z],
						inv_data[playerid][slot][inv_scale_x],
						inv_data[playerid][slot][inv_scale_y],
						inv_data[playerid][slot][inv_scale_z],
						slot,
						0
					);

				}
				else if (listitem == 1) // edit
				{
					OnInventoryAttachItem(
						playerid, 
						GetPVarInt(playerid, "Inventory:AttachModel"),
						inv_data[playerid][slot][inv_bone],
						inv_data[playerid][slot][inv_pos_x], 
						inv_data[playerid][slot][inv_pos_y], 
						inv_data[playerid][slot][inv_pos_z],
						inv_data[playerid][slot][inv_rot_x], 
						inv_data[playerid][slot][inv_rot_y], 
						inv_data[playerid][slot][inv_rot_z],
						inv_data[playerid][slot][inv_scale_x],
						inv_data[playerid][slot][inv_scale_y],
						inv_data[playerid][slot][inv_scale_z],
						slot,
						1
					);
				}
				else if (listitem == 2) // edit null
				{
					Clear:attach_inv_data(playerid, slot, TYPE_INV_PLAYER);

					AttachPlayerInventoryItem(playerid, slot, GetPVarInt(playerid, "Inventory:AttachType"));
				}
 			}
			else 
			{
				if (listitem == 0)
				{
					ShowPlayerDialog(playerid, D_INV + 7, DIALOG_STYLE_LIST, " ", DIALOG_INV_BONE, "Выбрать", "Закрыть");
					return 1;
				}
				
				
				new itindex = GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id));
				if ((item_list[itindex][it_type] == INV_ATTACH 
				&& item_list[itindex][it_param_1] == INV_FUNC_KNIFE 
				&& (listitem != 5 && listitem != 6)))
				{
					SendClientMessage(playerid, C_WHITE, #ERROR " Прикрепить нож можно только к рукам персонажа.");
					ShowPlayerDialog(playerid, D_INV + 7, DIALOG_STYLE_LIST, " ", DIALOG_INV_BONE, "Выбрать", "Закрыть");
					return 1;
				}

				inv_data[playerid][slot][inv_bone] = listitem;
				
				OnInventoryAttachItem(
					playerid, 
					GetPVarInt(playerid, "Inventory:AttachModel"),
					inv_data[playerid][slot][inv_bone],
					inv_data[playerid][slot][inv_pos_x], 
					inv_data[playerid][slot][inv_pos_y], 
					inv_data[playerid][slot][inv_pos_z],
					inv_data[playerid][slot][inv_rot_x], 
					inv_data[playerid][slot][inv_rot_y], 
					inv_data[playerid][slot][inv_rot_z],
					inv_data[playerid][slot][inv_scale_x],
					inv_data[playerid][slot][inv_scale_y],
					inv_data[playerid][slot][inv_scale_z],
					slot,
					2
				);
			}
		}
		
		case D_INV + 8 :
		{
			new slot = GetPVarInt(playerid, "Inventory:TempSelect");
				
			if (!response || !CheckActionSlot(playerid, slot, INV_WEAPON_SMALL, INV_WEAPON_BIG))
			{	
				UpdateInventory(playerid, slot);
				return 1;
			}
			
			if (listitem == 0)
			{
				RemoveInventoryWeapon(playerid, slot);
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно убрали оружие.");
				UpdateInventory(playerid, slot);
			}
			else if (listitem == 1)
			{
				format:g_string("" #DEFAULT " Разрядить\n\nВведите количество патрон, которое Вы хотите разрядить:\n\
					Всего патрон в обойме: " #cPROJECT "%i шт.",
					GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_1)
				);
				
				ShowPlayerDialog(playerid, D_INV + 9, DIALOG_STYLE_INPUT, 
					item_list[GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id))][it_name],
					g_string,
					"Далее", "Назад"
				);
			}
		}
		
		case D_INV + 9 :
		{
			new index = GetPVarInt(playerid, "Inventory:TempSelect"),
				itindex = GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id)),
				ammo = strval(inputtext);
				
			if (!response)
			{
				if (GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_use_slot))
				{
					ShowInventoryWeaponUnUse(playerid, index, itindex);
				}
				else
				{
					ShowInventoryWeaponUse(playerid, index, itindex);
				}
				
				return 1;
			}
			
			if (!CheckActionSlot(playerid, index, INV_WEAPON_SMALL, INV_WEAPON_BIG))
			{
				UpdateInventory(playerid, index);
				return 1;
			}
			
			if (isnull(inputtext) || !IsInt(inputtext)
			|| !(0 < ammo <= GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1)))
			{
				format:g_string("" #DEFAULT " Разрядить\n\n\
					Всего патрон в обойме: " #cPROJECT "%i шт.\n\
					Введите количество патрон, которое Вы хотите разрядить:\n\n\
					" #cRED "Вы ввели некорректное количество патрон.",
					GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1)
				);
				
				ShowPlayerDialog(playerid, D_INV + 9, DIALOG_STYLE_INPUT, 
					item_list[itindex][it_name],
					g_string,
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			if (GiveInventoryItem(playerid, item_list[itindex][it_param_2], ammo) == INVALID_PARAM)
			{
				SendClientMessage(playerid, C_WHITE, !ERROR_NO_SLOTS);
				UpdateInventory(playerid, index);
				return 1;
			}
			
			SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1, 
				GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1) - ammo
			);
			
			SetPlayerAmmo(playerid, item_list[itindex][it_param_1], GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1));
			
			Update:item_data(playerid, index, TYPE_INV_PLAYER);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно разрядили оружие.");
			
			UpdateInventory(playerid, index);
		}
		
		case D_INV + 10 :
		{
			if (!response)
			{
				return 1;
			}
			
			if (GiveInventoryItem(playerid, 1, character_data[playerid][c_skin]) == INVALID_PARAM)
			{
				SendClientMessage(playerid, C_WHITE, !ERROR_NO_SLOTS);
				return 1;
			}
			
			new Float: x,
				Float: y,
				Float: z,
				Float: angle;
			
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			
			character_data[playerid][c_skin] = ResetPlayerSkin(playerid);
			SetSpawnInfo(playerid, 264, character_data[playerid][c_skin], x, y, z, angle, 0, 0, 0, 0, 0, 0);
			SetPlayerSkin(playerid, character_data[playerid][c_skin]);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно сняли одежду с персонажа.");
			
			Update:character_int(playerid, "c_skin",  character_data[playerid][c_skin]);
		}
		
		case D_INV + 11 :
		{
			if (!response)
			{
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Drop:TakeIndex");
			
			if (!IsPlayerInRangeOfPoint(playerid, 1.5, 
				drop_data[index][drop_pos_x], 
				drop_data[index][drop_pos_y],
				drop_data[index][drop_pos_z])
				|| IsPlayerInAnyVehicle(playerid)
			)
			{
				return 1;
			}
			
			if (!drop_data[index][drop_item_id])
			{
				return 1;
			}
			
			if (listitem == 0)
			{
				InventoryTakeItem(playerid, index);
			}
		}
		
		case D_INV + 12 :
		{
			new slot = GetPVarInt(playerid, "Inventory:TempSelect");
				
			if (!response)
			{
				UpdateInventory(playerid, slot);
				return 1;
			}
			
			if (listitem == 0)
			{
				AttachPlayerInventoryItem(playerid, slot, BAG_ATTACH, true);
			}
			else if (listitem == 1)
			{
				if (GetBagCountItems(GetBagIndexBySlot(playerid, slot, TYPE_INV_PLAYER)) != 0)
				{
					UpdateInventory(playerid, slot);
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы не можете убрать сумку, заполненную содержимым.");
					return 1;
				}
				
				RemovePlayerAttachedObject(playerid, SLOT_ATTACH_BAG);
				inventory_attach[playerid][SLOT_ATTACH_BAG] = INVALID_PARAM;
				inv_data[playerid][slot][inv_use_slot] = false;
				Update:item_data(playerid, slot, TYPE_INV_PLAYER);
				
				ShowInventory(playerid, GetUserSettings(playerid, SET_INVENTORY), true);
			}
		}
		
		case D_INV + 13 :
		{
			new index = GetPVarInt(playerid, "Inventory:TempSelect");
			
			if (!response)
			{
				UpdateInventory(playerid, index);
				return 1;
			}
			
			new itindex = GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id)),
				model = item_list[itindex][it_param_1] == INV_FUNC_SINGLE_SMOKE ? 3044 : 19625;
			
			if (!CheckActionSlot(playerid, index, INV_SMOKE))
			{
				UpdateInventory(playerid, index);
				return 1;
			}
			
			if(IsInventoryTextDrawShowed(playerid))
			{
				ShowInventoryTextdraw(playerid, false);
			}
			
			if (listitem == 0)
			{
				SetPlayerAttachedObject(
					playerid, 
					SLOT_ATTACH_SMOKE, 
					model, 
					2, 
					-0.013000, 
					0.110999, 
					-0.008000,  
					-5.000001, 
					0.000000, 
					-178.599838, 
					1.000000, 
					1.000000, 
					1.000000 
				);
			}
			else if (listitem == 1)
			{
				SetPlayerAttachedObject(
					playerid, 
					SLOT_ATTACH_SMOKE,  
					model, 
					6,
					0.098999, 
					-0.003000, 
					0.020000,  
					-2.999998, 
					-24.799991, 
					45.300014, 
					1.000000, 
					1.000000, 
					1.000000 
				);
			}
			else if (listitem == 2)
			{
				SetPlayerAttachedObject(
					playerid, 
					SLOT_ATTACH_SMOKE, 
					model, 
					5, 
					0.116999, 
					-0.019000, 
					0.000000, 
					0.000000, 
					0.000000, 
					34.400043, 
					1.000000, 
					1.000000, 
					1.000000 
				);
			}
			
			SetPVarInt(playerid, "Inventory:AttachSlot", index);
			SetPVarInt(playerid, "Inventory:AttachState", ATTACH_STATE_SMOKE);
			
			EditAttachedObject(playerid, SLOT_ATTACH_SMOKE);
		}
		
		case D_INV + 14 :
		{
			new index = GetPVarInt(playerid, "Inventory:TempSelect");
			
			if (!response)
			{	
				DeletePVar(playerid, "Inventory:TempSelect");
				UpdateInventory(playerid, index);
				return 1;
			}
			
			if (listitem == 0) // Использовать
			{
				if (IsInventoryTextDrawShowed(playerid))
				{
					ShowInventoryTextdraw(playerid, false, _, _, _, _, false);
				}
				
				ShowPhone(playerid, index);
			}
			else if (listitem == 1) // Убрать по умолчанию
			{
				InventoryUnuseItem(playerid, index, true, true);
				UpdateInventory(playerid, index);
			}
		}
		
		case D_INV + 15 :
		{
			if (!response)
			{
				DeletePVar(playerid, "Drop:TakeIndex");
				DeletePVar(playerid, "Drop:Model");
				return 1;
			}
			
			if (inventory_attach[playerid][SLOT_ATTACH_BAG] != INVALID_PARAM)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " На Вас уже имеется прикрепленная сумка.");
				DeletePVar(playerid, "Drop:TakeIndex");
				DeletePVar(playerid, "Drop:Model");
				return 1;
			}
			
			SetPVarInt(playerid, "Inventory:AttachState", ATTACH_STATE_BAG);
			SetPlayerAttachedObject(playerid, SLOT_ATTACH_BAG, GetPVarInt(playerid, "Drop:Model"), listitem);
			EditAttachedObject(playerid, SLOT_ATTACH_BAG);
			SendClientMessage(playerid, C_WHITE, !HELP_EDITOR);
			DeletePVar(playerid, "Drop:Model");
		}
		
		case D_INV + 16 :
		{
			if (response)
			{
				InventoryTakeItem(playerid, GetPVarInt(playerid, "Drop:Select"));
			}
			
			DeletePVar(playerid, "Drop:Select");
		}
		
		case D_INV + 17:
		{	
			if (!response)
			{
				return 1;
			}
			
			new index = g_dialog_select[playerid][listitem];
			
			if (index == ITEM_LIST_NEXT || index == ITEM_LIST_BACK)
			{
				ShowInventoryItemList(playerid, index);
				return 1;
			}
		
			SetPVarInt(playerid, "Inventory:TempItemId", index);
				
			ShowInventoryAddParam(playerid, 1, index);
		}
		
		case D_INV + 18:
		{
			if (!response)
			{
				ShowInventoryItemList(playerid, ITEM_LIST_CURRENT);
				return 1;
			}
			
			new param = strval(inputtext),
				index = GetPVarInt(playerid, "Inventory:TempItemId");
				
			SetPVarInt(playerid, "Inventory:TempParam1", param);
			ShowInventoryAddParam(playerid, 2, index);
		}
		
		case D_INV + 19:
		{
			new index = GetPVarInt(playerid, "Inventory:TempItemId"),
				param_1 = GetPVarInt(playerid, "Inventory:TempParam1"),
				param_2 = strval(inputtext);
				
			if (!response)
			{
				ShowInventoryAddParam(playerid, 1, index);
				return 1;
			}
				
			clean:<g_small_string>;
			GetPVarString(playerid, "Inventory:TempItemCallback", g_small_string, sizeof g_small_string);
			
			if (!isnull(g_small_string))
			{
				CallLocalFunction(g_small_string, "iiii", playerid, item_list[index][it_id], param_1, param_2);
			}
			
			DeletePVar(playerid, "Inventory:TempItemCallback"),
			DeletePVar(playerid, "Inventory:TempItemId"),
			DeletePVar(playerid, "Inventory:TempParam1"),
			DeletePVar(playerid, "Inventory:TempParam2");
		}
		
		case D_INV_DRUG_USE:
		{
			new index = GetPVarInt(playerid, "Inventory:TempSelect"),
				itindex = GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id)),
				value = GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1);
	
			if (!response || !CheckActionSlot(playerid, index, INV_DRUGS))
			{
				UpdateInventory(playerid, index);
				return 1;
			}
			
			if (listitem == 0) // Употребить
			{
				pformat:("" #SUCCESS " Вы успешно употребили " #cPROJECT "%s" #cWHITE ".",
					GetInventoryItemName(itindex)
				);
				psend:(playerid, C_WHITE);
				
				ShowPlayerDrugEffect(playerid, item_list[itindex][it_param_1]);
				
				SetPVarInt(playerid, "Inventory:DrugSelect", item_list[itindex][it_param_1]);
				
				if (value <= 1)
				{
					RemoveInventoryItem(playerid, index);
					return 1;
				}
				
				value -= 1;
					
				SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1, value);
				Update:item_data(playerid, index, TYPE_INV_PLAYER);
				
				return 1;
			}
			
			listitem += (value <= 1 && GetUserSettings(playerid, SET_INVENTORY) == 1) ? (1) : (0);
			
			if (listitem == 1) // Расфасовать
			{
				ShowInventoryDrugSplit(playerid, index);
				return 1;
			}
			
			if (listitem == 2) // Соединить
			{		
				new select_index,
					first_item_id = GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_id),
					second_item_id,
					presence;
			
				for (new i; i < MAX_INVENTORY_SLOTS; i++)
				{
					select_index = GetItemIndexById(GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id));
					second_item_id = GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_id);
				
					if (item_list[select_index][it_param_1] == item_list[itindex][it_param_1]
					&& second_item_id != first_item_id)
					{
						value = GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_param_1);
						
						SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1,
							GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1) + value)
						;
						
						RemoveInventoryItem(playerid, i);
						
						presence++;
					}
				}
				
				if (presence == 0)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " В инвентаре нет подходящих видов наркотика для фасовки.");
					return 1;
				}
				
				Update:item_data(playerid, index, TYPE_INV_PLAYER);
			
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно расфасовали наркотик.");
				
				UpdateInventory(playerid, index);
			}
		}
		
		case D_INV_DRUG_SPLIT:
		{
			new index = GetPVarInt(playerid, "Inventory:TempSelect"),
				itindex = GetItemIndexById(GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_item_id)),
				gramm = strval(inputtext),
				values = GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1);
				
			if (!response || !CheckActionSlot(playerid, index, INV_DRUGS))
			{
				ShowInventoryDrugUse(playerid, itindex, values);
				return 1;
			}
			
			if (isnull(inputtext) || !IsInt(inputtext)
			|| !(0 < gramm <= GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1))
			|| gramm == GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1))
			{
				format:g_string("" #DEFAULT " Расфасовать\n\n\
					Наркотиков в наличии: " #cPROJECT "%i грамм.\n\
					Введите количество грамм, которое Вы хотите расфасовать:\n\n\
					" #cRED "Вы ввели некорректное количество грамм.",
					GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1)
				);
				
				ShowPlayerDialog(playerid, D_INV_DRUG_SPLIT, DIALOG_STYLE_INPUT, 
					item_list[itindex][it_name],
					g_string,
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			if (GiveInventoryItem(playerid, item_list[itindex][it_id], gramm, TYPE_INV_PLAYER) == INVALID_PARAM)
			{
				SendClientMessage(playerid, C_WHITE, !ERROR_NO_SLOTS);
				UpdateInventory(playerid, index);
				return 1;
			}
			
			SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1, 
				GetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_1) - gramm
			);
			
			Update:item_data(playerid, index, TYPE_INV_PLAYER);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно расфасовали наркотик.");
			
			UpdateInventory(playerid, index);
		}
	}
	
	return 1;
}
