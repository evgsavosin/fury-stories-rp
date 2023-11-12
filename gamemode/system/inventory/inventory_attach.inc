/*!
	@brief Система аттача инвентаря
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

function Att_OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float: fOffsetX, Float: fOffsetY, Float: fOffsetZ, Float: fRotX, Float: fRotY, Float: fRotZ, Float: fScaleX, Float: fScaleY, Float: fScaleZ)
{
	new attach_state = GetPVarInt(playerid, "Inventory:AttachState"),
		sindex = GetPVarInt(playerid, "Inventory:AttachSlot"),
		itindex = GetItemIndexById(inv_data[playerid][sindex][inv_item_id]);
	
	/// Default attach
	if(attach_state == ATTACH_STATE_DEFAULT)
	{	
		if(response) // Сохранение
		{		
			inv_data[playerid][sindex][inv_bone] = boneid;
			
			inv_data[playerid][sindex][inv_pos_x] = fOffsetX;
			inv_data[playerid][sindex][inv_pos_y] = fOffsetY;
			inv_data[playerid][sindex][inv_pos_z] = fOffsetZ;
			
			inv_data[playerid][sindex][inv_rot_x] = fRotX;
			inv_data[playerid][sindex][inv_rot_y] = fRotY;
			inv_data[playerid][sindex][inv_rot_z] = fRotZ;
			
			inv_data[playerid][sindex][inv_scale_x] = fScaleX;
			inv_data[playerid][sindex][inv_scale_y] = fScaleY;
			inv_data[playerid][sindex][inv_scale_z] = fScaleZ;
			
			inv_data[playerid][sindex][inv_use_attach] = true;
			
			SetPlayerAttachedObject(playerid, index, modelid, boneid, Float: fOffsetX, Float: fOffsetY, Float: fOffsetZ, Float: fRotX, Float: fRotY, Float: fRotZ, Float: fScaleX, Float: fScaleY, Float: fScaleZ);
			
			/// Функция
			AttachUseItemFunction(playerid, sindex, itindex);
			
			/// Если сумка
			if(GetPVarInt(playerid, "Inventory:AttachType") == BAG_ATTACH)
			{
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы прикрепили сумку к персонажу.");
			}
			else
			{
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно прикрепили данный предмет к персонажу.");
			}
			
			Update:item_data(playerid, sindex, TYPE_INV_PLAYER);
		}
		else // Отмена
		{
			if(!GetPVarInt(playerid, "Inventory:AttachEditBag"))
			{
				inv_data[playerid][sindex][inv_use_slot] = false;
				SetAttachItem(playerid, sindex, INVALID_PARAM);
				
				RemovePlayerAttachedObject(playerid, index);
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы отменили прикрепление предмета к персонажу.");
				
				Update:item_data(playerid, sindex, TYPE_INV_PLAYER);
			}
		}
		
		ShowInventory(playerid, GetUserSettings(playerid, SET_INVENTORY));
	}
	else if(attach_state == ATTACH_STATE_SMOKE)
	{
		if(response)
		{	
			new lindex = GetInventoryLighter(playerid);
			
			if (lindex == INVALID_PARAM)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас отсутствует зажигалка.");
				RemovePlayerAttachedObject(playerid, SLOT_ATTACH_SMOKE);
				UpdateInventory(playerid, index);
			}
			else 
			{	
				/// INV_LIGHTER
				if (GetInventoryEnumItem(playerid, lindex, TYPE_INV_PLAYER, inv_param_1) > 0)
				{
					SetInventoryEnumItem(playerid, lindex, TYPE_INV_PLAYER, inv_param_1, 
						GetInventoryEnumItem(playerid, lindex, TYPE_INV_PLAYER, inv_param_1) - 1 
					);
					
					Update:item_data(playerid, index, TYPE_INV_PLAYER);
				}
				else 
				{
					RemoveInventoryItem(playerid, index);
				}
				
				SetInventoryEnumItem(playerid, sindex, TYPE_INV_PLAYER, inv_param_1, 
					GetInventoryEnumItem(playerid, sindex, TYPE_INV_PLAYER, inv_param_1) - 1 
				);
				
				if (GetInventoryEnumItem(playerid, sindex, TYPE_INV_PLAYER, inv_param_1) <= 0)
				{
					RemoveInventoryItem(playerid, sindex);
					SendClientMessage(playerid, C_WHITE, 
						item_list[itindex][it_param_1] != INV_FUNC_SINGLE_SMOKE ? 
						("" #DEFAULT " Вы использовали всю пачку сигарет.") : ("" #DEFAULT " Вы использовали сигару.") 
					);
				}
				else 
				{
					Update:item_data(playerid, sindex, TYPE_INV_PLAYER);
					
					pformat:("" #SUCCESS " Вы использовали одну сигарету (Осталось: " #cPROJECT "%i" #cWHITE "). " #cGRAY "(/remsmoke - убрать сигарету)" #cWHITE ".",
						GetInventoryEnumItem(playerid, sindex, TYPE_INV_PLAYER, inv_param_1)
					);
					
					psend:(playerid, C_WHITE);
				}
				
				format:g_small_string("Закурил%s сигарету %s", 
					EndWordSex(playerid),
					item_list[itindex][it_name]
				);
				
				SendRPMessage(ACTION_AME, playerid, g_small_string);
				
				SetPlayerAttachedObject(playerid, index, modelid, boneid, Float: fOffsetX, Float: fOffsetY, Float: fOffsetZ, Float: fRotX, Float: fRotY, Float: fRotZ, Float: fScaleX, Float: fScaleY, Float: fScaleZ);
			}
		}
		else 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы отменили прикрепление сигареты к персонажу.");
			RemovePlayerAttachedObject(playerid, SLOT_ATTACH_SMOKE);
		}
		
		ShowInventory(playerid, GetUserSettings(playerid, SET_INVENTORY));
	}
	else if(attach_state == ATTACH_STATE_BAG)
	{
		if(response)
		{
			SetPVarInt(playerid, "Drop:BagTake", true);
			
			if((sindex = InventoryTakeItem(playerid, GetPVarInt(playerid, "Drop:TakeIndex"))) == INVALID_PARAM)
			{
				RemovePlayerAttachedObject(playerid, SLOT_ATTACH_BAG);
				return 1;
			}
			
			inv_data[playerid][sindex][inv_bone] = boneid;
			
			inv_data[playerid][sindex][inv_pos_x] = fOffsetX;
			inv_data[playerid][sindex][inv_pos_y] = fOffsetY;
			inv_data[playerid][sindex][inv_pos_z] = fOffsetZ;
			
			inv_data[playerid][sindex][inv_rot_x] = fRotX;
			inv_data[playerid][sindex][inv_rot_y] = fRotY;
			inv_data[playerid][sindex][inv_rot_z] = fRotZ;
			
			inv_data[playerid][sindex][inv_scale_x] = fScaleX;
			inv_data[playerid][sindex][inv_scale_y] = fScaleY;
			inv_data[playerid][sindex][inv_scale_z] = fScaleZ;
			
			inv_data[playerid][sindex][inv_use_attach] = true;
			
			SetPlayerAttachedObject(playerid, index, modelid, boneid, Float: fOffsetX, Float: fOffsetY, Float: fOffsetZ, Float: fRotX, Float: fRotY, Float: fRotZ, Float: fScaleX, Float: fScaleY, Float: fScaleZ);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы прикрепили сумку к персонажу.");
			
			Update:item_data(playerid, sindex, TYPE_INV_PLAYER);
		}
		else 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы отменили прикрепление предмета к персонажу.");
		}
		
		DeletePVar(playerid, "Drop:BagTake");
		DeletePVar(playerid, "Drop:TakeIndex" );
		DeletePVar(playerid, "Drop:Model");
	}

	Clear:attach_pvar(playerid);
	return 1;
}

Clear:attach_pvar(playerid)
{
	DeletePVar(playerid, "Inventory:AttachState");
	DeletePVar(playerid, "Inventory:AttachType");
	DeletePVar(playerid, "Inventory:AttachEditBag");
	DeletePVar(playerid, "Inventory:AttachSlot");
	DeletePVar(playerid, "Inventory:AttachExists");
	DeletePVar(playerid, "Inventory:AttachModel");
}

function OnInventoryAttachItem(playerid, modelid, bone, Float: fOffsetX, Float: fOffsetY, Float: fOffsetZ, Float: fRotX, Float: fRotY, Float: fRotZ, Float: fScaleX, Float: fScaleY, Float: fScaleZ, slot, _: is_edit)
{
	new index,
		itindex;
	
	if(GetPVarInt(playerid, "Inventory:AttachType") == BAG_ATTACH)
	{
		index = SLOT_ATTACH_BAG;
	}
	else 
	{
		index = GetFreeAttachSlot(playerid);
		
		if(index == INVALID_PARAM)
		{
			Clear:attach_pvar(playerid);
			return 1;
		}
	}

	itindex = GetItemIndexById(GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id));

	inventory_attach[playerid][index] = slot;
	
	if(is_edit != INVALID_PARAM)
	{
		if(item_list[itindex][it_type] == INV_WEAPON_BIG 
		|| item_list[itindex][it_type] == INV_WEAPON_SMALL)
		{
			inv_data[playerid][slot][inv_use_slot] = TYPE_USE_ATTACH;
		}
		else 
		{
			inv_data[playerid][slot][inv_use_slot] = TYPE_USE_DEFAULT;
		}
	}
	
	switch(is_edit)
	{
		case 1, 2 : // Редактирование
		{
			if(IsInventoryTextDrawShowed(playerid))
			{
				ShowInventoryTextdraw(playerid, false);
			}
			
			if(is_edit == 1)
			{
				SetPlayerAttachedObject(playerid, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
			}
			else if(is_edit == 2)
			{
				SetPlayerAttachedObject(playerid, index, modelid, bone);
			}
			
			EditAttachedObject(playerid, index);
			SendClientMessage(playerid, C_WHITE, !HELP_EDITOR);
		}
		
		case 0, INVALID_PARAM : // Использование
		{
			if(IsInventoryTextDrawShowed(playerid))
			{
				UpdateInventorySlotModel(playerid, slot);
				UpdateInventorySelect(playerid, inventory_td_select[playerid], false, slot);
			}
			
			SetPlayerAttachedObject(playerid, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ);
			
			AttachUseItemFunction(playerid, slot, itindex);
			
			if(is_edit != INVALID_PARAM)
			{
				Update:item_data(playerid, slot, TYPE_INV_PLAYER);
			}
			
			if(GetPVarInt(playerid, "Inventory:AttachType") == BAG_ATTACH)
			{
				if(is_edit != INVALID_PARAM)
				{
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы прикрепили сумку к персонажу.");
					ShowInventory(playerid, GetUserSettings(playerid, SET_INVENTORY), true);
				}
			}
			else 
			{
				if(is_edit != INVALID_PARAM)
				{
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно прикрепили данный предмет к персонажу.");
				}
			}
		}
	}
	
	return 1;
}

AttachUseItemFunction(playerid, sindex, itindex)
{
	new param = item_list[itindex][it_param_1];
	
	if(param == INV_FUNC_HIDDEN_NAME)
	{
		ReplacePlayerName(playerid, TYPE_HIDDEN);
	}
	else if(param == INV_FUNC_KNIFE)
	{
		SetPVarInt(playerid, "Player:UseKnife", true);
	}
	else if(param == INV_FUNC_ARMOUR_LIGHT
	|| param == INV_FUNC_ARMOUR_HEAVY)
	{
		SetArmourType(playerid, (item_list[itindex][it_param_1] == INV_FUNC_ARMOUR_LIGHT ? TYPE_ARMOUR_LIGHT : TYPE_ARMOUR_HEAVY));
		SetArmourValue(playerid, inv_data[playerid][sindex][inv_param_2]);
		SetArmourItemId(playerid, inv_data[playerid][sindex][inv_id]);
	}
}

SetAttachItem(playerid, slot, value)
{
	for(new i; i < MAX_INVENTORY_ATTACH + 1; i++)
	{
		if(inventory_attach[playerid][i] != slot)
		{
			continue;
		}
		
		inventory_attach[playerid][i] = value;
		break;
	}
}

RemoveAttachItemBySlot(playerid, slot)
{
	for(new i; i < MAX_INVENTORY_ATTACH + 1; i++)
	{
		if(inventory_attach[playerid][i] != slot)
		{
			continue;
		}
		
		RemovePlayerAttachedObject(playerid, i);
		inventory_attach[playerid][i] = INVALID_PARAM;
	}
}

GetFreeAttachSlot(playerid)
{
	for(new i; i < MAX_INVENTORY_ATTACH; i++)
	{
		if(IsPlayerAttachedObjectSlotUsed(playerid, i))
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

AttachPlayerInventoryItem(playerid, slot, type = DEFAULT_ATTACH, hide_use_position = false)
{
	new attach_exists = IsAttachExists(playerid, slot, TYPE_INV_PLAYER);
	
	SetPVarInt(playerid, "Inventory:AttachExists", attach_exists);
	SetPVarInt(playerid, "Inventory:AttachModel", GetItemModel(playerid, slot, TYPE_INV_PLAYER));
	SetPVarInt(playerid, "Inventory:AttachSlot", slot);
	SetPVarInt(playerid, "Inventory:AttachState", ATTACH_STATE_OFF);
	SetPVarInt(playerid, "Inventory:AttachEditBag", 0); // редактируем сумку
	SetPVarInt(playerid, "Inventory:AttachType", type);
	
	if(attach_exists)
	{
		clean:<g_string>;
		
		if(!hide_use_position) 
		{
			strcat(g_string, " Использовать сохраненную позицию\n");
		}
		
		strcat(g_string, " Редактировать позицию\n");
		strcat(g_string, " Установить заново позицию");
		ShowPlayerDialog(playerid, D_INV + 7, DIALOG_STYLE_LIST, " ", 
			g_string, 
			"Выбрать", "Закрыть" 
		);
	}
	else 
	{
		ShowPlayerDialog(playerid, D_INV + 7, DIALOG_STYLE_LIST, " ", DIALOG_INV_BONE, "Выбрать", "Закрыть");
	}
}

IsAttachExists(const id, index, type)
{
	if(type == TYPE_INV_PLAYER)
	{
		if(inv_data[id][index][inv_use_attach])
		{
			return 1;
		}
	}
	else if(type == TYPE_INV_VEHICLE)
	{
		if(vehicle_inv_data[id][index][inv_use_attach])
		{
			return 1;
		}
	}
	
	return 0;
}

Timer:static_attach(playerid)
{
	new is_attached = IsPlayerAttachedObjectSlotUsed(playerid, SLOT_ATTACH_BACK);
	
	if (IsWeaponStaticAttach(GetPlayerWeapon(playerid))) 
	{
		if(is_attached)
		{
			RemovePlayerAttachedObject(playerid, SLOT_ATTACH_BACK);
		}
	}
	else 
	{	
		if (!is_attached)
		{
			for (new i, item; i < MAX_INVENTORY_SLOTS; i++)
			{
				item = GetItemStaticAttach(GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id));
				
				if (item != 0)
				{	
					SetPlayerAttachedObject(playerid, 
						SLOT_ATTACH_BACK, 
						item_list[item][it_model], 
						16, 
						0.019280, 
						0.155553, 
						0.396286, 
						70.920410, 
						274.673919, 
						253.978057, 
						1.000000, 
						1.000000, 
						1.000000 
					); 
					
					return 1;
				}
			}	
		}
	}
	
	return 1;
}

GetItemStaticAttach(item_id)
{
	new itindex = GetItemIndexById(item_id);
		
	if (item_list[itindex][it_type] == INV_WEAPON_BIG)
	{
		if (IsWeaponStaticAttach(item_list[itindex][it_param_1]))
		{
			return itindex;
		}
	}
	
	return 0;
}

IsWeaponStaticAttach(weaponid)
{
	switch(weaponid)
	{
		case WEAPON_SHOTGUN,
			 WEAPON_SHOTGSPA,
			 WEAPON_MP5,
			 WEAPON_AK47,
			 WEAPON_RIFLE,
			 WEAPON_M4,
			 WEAPON_SNIPER :
		{
			return 1;
		}
	}
	
	return 0;
}

// Vehicle Attach
function InventoryVehicleAttach(playerid, vehicleid, slot)
{
	new item = GetItemIndexById(GetInventoryEnumItem(vehicleid, slot, TYPE_INV_VEHICLE, inv_item_id)),
		model,
		attach_slot = GetFreeVehicleAttachSlot(vehicleid),
		Float: x,
		Float: y,
		Float: z,
		Float: angle;
		
	if (item == INVALID_ITEM_ID)
	{
		return 0;
	}
	
	if (attach_slot == INVALID_PARAM)
	{
		return 0;
	}
	
	model = GetItemDropObjectModel(vehicleid, slot, TYPE_INV_VEHICLE);
	GetVehiclePos(vehicleid, x, y, z);
	GetVehicleZAngle(vehicleid, angle);
	
	x += 0.5 * floatcos(-angle, degrees);
	y -= 0.5 * floatsin(-angle, degrees);
	z -= 0.5;
	
	inventory_veh_attach[vehicleid][attach_slot][a_slot] = slot;
	inventory_veh_attach[vehicleid][attach_slot][a_object] = CreateDynamicObject(
		model, 
		x,
		y,
		z,
		0.0,
		0.0,
		0.0,
		0,
		0,
		_,
		100
	);
	
	if (IsInventoryTypeShow(playerid, TEXTDRAW_INVENTORY)
	&& IsInventoryTextDrawShowed(playerid))
	{
		ShowInventoryTextdraw(playerid, false);
	}
	
	SetPVarInt(playerid, "VehicleAttach:Edit", true);
	SetPVarInt(playerid, "VehicleAttach:Vehicle", vehicleid);
	SetPVarInt(playerid, "VehicleAttach:Slot", slot);
	SetPVarInt(playerid, "VehicleAttach:AttachSlot", attach_slot);
	
	Streamer_Update(playerid);
	
	EditDynamicObject(playerid, inventory_veh_attach[vehicleid][attach_slot][a_object]);
	return 1;
}

function InventoryVehicleUpdateAttach(vehicleid, oldslot, newslot)
{
	for (new i; i < MAX_INVENTORY_ATTACH; i++)
	{
		if (oldslot == inventory_veh_attach[vehicleid][i][a_slot])
		{
			inventory_veh_attach[vehicleid][i][a_slot] = newslot;
			break;
		}
	}
	
	return 1;
}

function InventoryVehicleUnattach(playerid, vehicleid, slot)
{
	for (new i; i < MAX_INVENTORY_ATTACH; i++)
	{
		if (slot != inventory_veh_attach[vehicleid][i][a_slot])
		{
			continue;
		}
		
		DestroyDynamicObject(inventory_veh_attach[vehicleid][i][a_object]);
		
		inventory_veh_attach[vehicleid][i][a_object] = 
		inventory_veh_attach[vehicleid][i][a_slot] = INVALID_PARAM;
			
		UpdateInventory(playerid, slot);
		
		return 1;
	}
	
	return 0;
}

GetVehicleSlotIsAttached(vehicleid, slot)
{
	for(new index; index < MAX_INVENTORY_ATTACH; index++)
	{
		if(inventory_veh_attach[vehicleid][index][a_slot] != slot)
		{
			continue;
		}
		
		return 1;
	}
	
	return 0;
}

GetFreeVehicleAttachSlot(vehicleid)
{
	for(new index; index < MAX_INVENTORY_ATTACH; index++)
	{
		if(inventory_veh_attach[vehicleid][index][a_slot] != INVALID_PARAM)
		{
			continue;
		}
		
		return index;
	}
	
	return INVALID_PARAM;
}
