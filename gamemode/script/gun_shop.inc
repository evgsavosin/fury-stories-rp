/*!
	@brief Оружейные магазины
	@author Found (evg.savosin)
	@date 26.04.2018
*/

// Defines and variables
#define BUY_GUN_POS						-1499.0854, 95.1520, 3201.9858
#define GUNSHOP_DIALOG_MENU				D_GUNSHOP, DIALOG_STYLE_LIST," "," Купить оружие\n Сдать купленное оружие","Далее","Закрыть"

enum 
{
	TYPE_GS_GUN,
	TYPE_GS_ATTACH,
	TYPE_GS_AMMO
}

enum E_GUN_SHOP_DATA 
{
	gs_type,
	gs_item_id,
	gs_cost,
	gs_param
}

new gun_shop_list		[	][E_GUN_SHOP_DATA	] = 
{
	{TYPE_GS_GUN, 8, 750, 0}, // Малогабаритный пистолет
	{TYPE_GS_GUN, 11, 1600, 0}, // Дробовик
	{TYPE_GS_GUN, 15, 2000, 0}, // ПП
	{TYPE_GS_GUN, 18, 2500, 0}, // Винтовка
	
	{TYPE_GS_ATTACH, 88, 45, 0}, // Нож выживания
	{TYPE_GS_ATTACH, 109, 260, 100}, // Лёгкий бронежилет
	{TYPE_GS_ATTACH, 74, 38, 0}, // Кобура
	{TYPE_GS_ATTACH, 76, 35, 0}, // Фонарик
	
	{TYPE_GS_AMMO, 20, 70, 25}, // Патроны 9 mm
	{TYPE_GS_AMMO, 21, 90, 14}, // Патроны .44 Magnum
	{TYPE_GS_AMMO, 22, 65, 15}, // Патроны 12 mm
	{TYPE_GS_AMMO, 23, 75, 30}, // Патроны 9x19 mm
	{TYPE_GS_AMMO, 24, 96, 30}  // Патроны 7,62х39 mm
};

// Functions
GunShop_OnGameModeInit()
{
	CreatePickupWith3DTextLabel("Покупка", 1239, BUY_GUN_POS, WORLD_AMMUNATION, INT_OTHER);
}

GunShop_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{
		if (IsPlayerInRangeOfPoint(playerid, 
		FACTOR_TELEPORT_RADIUS, 
		BUY_GUN_POS))
		{
			if (!IsPlayerLicenseExists(playerid, li_weapon))
			{
				SendClientMessage(playerid, C_WHITE, #ERROR " У Вас отсутствует лицензия на оружие.");
				return 1;
			}
			
			ShowPlayerDialog(playerid, GUNSHOP_DIALOG_MENU);
			return 0;
		}
	}
	
	return 1;
}

GunShop_OnPlayerClickTextDraw(playerid, Text: clickedid)
{	
	if (!GetPVarInt(playerid, "GunShop:States"))
	{
		return 1;
	}
	
	if (clickedid == INVALID_TEXT_DRAW)
	{
		ShowGunShopList(playerid, false);
	}
	else if (clickedid == td_select_menu[1]) // next
	{
		UpdateGunShopList(playerid, GetPVarInt(playerid, "GunShop:Page") + TD_SELECT_MENU_ARRAY);
	}
	else if (clickedid == td_select_menu[2]) // last 
	{
		UpdateGunShopList(playerid, GetPVarInt(playerid, "GunShop:Page") - TD_SELECT_MENU_ARRAY);
	}
	
	return 1;
}

GunShop_OnPlayerClickPTD(playerid, PlayerText: playertextid)
{
	if (!GetPVarInt(playerid, "GunShop:States"))
	{
		return 1;
	}
		
	new index,
		itindex,
		str_param						[	128 	];
		
	for (new i; i < TD_SELECT_MENU_ARRAY; i++)
	{
		if (playertextid == ptd_select_menu[playerid][i])
		{
			index = g_td_select[playerid][i];
			if ((itindex = GetItemIndexById(gun_shop_list[index][gs_item_id])) == INVALID_ITEM_ID)
			{
				continue;
			}
			
			SetPVarInt(playerid, "GunShop:Index", index);
			
			clean:<str_param>;
			if (gun_shop_list[index][gs_type] == TYPE_GS_AMMO)
			{
				format:str_param("Патронов в комплекте: " #cPROJECT "%i" #cWHITE "\n\n",
					gun_shop_list[index][gs_param]
				);
			}
			
			format:g_string("\
				" #DEFAULT " Покупка\n\n\
				Название: " #cPROJECT "%s" #cWHITE "\n\
				Описание: " #cPROJECT "%s" #cWHITE "\n\
				Цена: " #cGREEN "$%i" #cWHITE "\n%s\
				%s\
				Вы действительно желаете приобрести данный товар?",
				item_list[itindex][it_name],
				item_list[itindex][it_description],
				gun_shop_list[index][gs_cost],
				isnull(str_param) ? ("\n") : (""),
				str_param
			);
			
			ShowPlayerDialog(playerid, D_GUNSHOP + 1, DIALOG_STYLE_MSGBOX, " ", g_string, "Купить", "Отмена");
			break;
		}
	}
	
	return 1;
}

GunShop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	#pragma unused listitem
	
	if (dialogid == D_GUNSHOP)
	{
		if (!response)
		{
			return 1;
		}
		
		if (listitem == 0)
		{
			ShowGunShopList(playerid, true);
		}
		else if (listitem == 1)
		{
			ShowPlayerGunList(playerid);
		}
	}
	else if (dialogid == D_GUNSHOP + 1)
	{
		if (!response)
		{
			return 1;
		}
		
		new index = GetPVarInt(playerid, "GunShop:Index");
		
		if (gun_shop_list[index][gs_type] == TYPE_GS_GUN
		&& !GetPlayerAvaibleWeapon(playerid))
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете купить больше оружия.");
			DeletePVar(playerid, "GunShop:Index");
			return 1;
		}
		
		if (!IsInventorySlotFreeExists(playerid))
		{
			SendClientMessage(playerid, C_WHITE, !ERROR_NO_SLOTS);
			DeletePVar(playerid, "GunShop:Index");
			return 1;
		}
		
		MakePayment(playerid, gun_shop_list[index][gs_cost], "buy_gun");
	}
	else if (dialogid == D_GUNSHOP + 2)
	{
		if (!response)
		{
			ShowPlayerDialog(playerid, GUNSHOP_DIALOG_MENU);
			return 1;
		}
		
		new slot = g_dialog_select[playerid][listitem],
			id = GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_item_id);
			
		if (!CheckActionSlot(playerid, slot, INV_WEAPON_SMALL, INV_WEAPON_BIG) 
			|| GetInventoryEnumItem(playerid, slot, TYPE_INV_PLAYER, inv_param_2) != GetCharacterId(playerid)
			|| !RemoveInventoryItem(playerid, slot, true))
		{
			ShowPlayerGunList(playerid);
			return 1;
		}
		
		for (new i; i < sizeof gun_shop_list; i++)
		{
			if (gun_shop_list[i][gs_item_id] == id)
			{
				new money = floatround(gun_shop_list[i][gs_cost] / 2);
				
				GivePlayerMoney(playerid, money);
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно сдали оружие и получили половину от её стоимости.");
				ShowPlayerDialog(playerid, GUNSHOP_DIALOG_MENU);
				
				character_data[playerid][c_buy_weapon_count]--;
				Update:character_int(playerid, "c_buy_weapon_count", character_data[playerid][c_buy_weapon_count]);
				break;
			}
		}
	}
	
	return 1;
}

function PAY:buy_gun(playerid, status)
{
	new index = GetPVarInt(playerid, "GunShop:Index"),
		itindex = GetItemIndexById(gun_shop_list[index][gs_item_id]),
		type = gun_shop_list[index][gs_type];
	
	if (!IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, BUY_GUN_POS))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы должны находиться на месте покупки.");
		return 1;
	}
		
	if (!status)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
		return 1;
	}
	
	if (type == TYPE_GS_ATTACH)
	{
		if (GiveInventoryItem(playerid, gun_shop_list[index][gs_item_id], 0, gun_shop_list[index][gs_param]) == INVALID_PARAM)
		{
			SendClientMessage(playerid, C_WHITE, !ERROR_NO_SLOTS);
			return 1;
		}
	}
	else if (type == TYPE_GS_GUN)
	{
		if (GiveInventoryItem(playerid, gun_shop_list[index][gs_item_id], 0, GetCharacterId(playerid)))
		{
			SendClientMessage(playerid, C_WHITE, !ERROR_NO_SLOTS);
			return 1;
		}
		
		character_data[playerid][c_buy_weapon_count]++;
		Update:character_int(playerid, "c_buy_weapon_count", character_data[playerid][c_buy_weapon_count]);
	}
	else if (type == TYPE_GS_AMMO)
	{
		if (GiveInventoryItem(playerid, gun_shop_list[index][gs_item_id], gun_shop_list[index][gs_param], 0))
		{
			SendClientMessage(playerid, C_WHITE, !ERROR_NO_SLOTS);
			return 1;
		}
	}
	
	pformat:("" #SUCCESS " Вы успешно приобрели предмет " #cPROJECT "%s" #cWHITE ".",
		item_list[itindex][it_name]
	);
	
	psend:(playerid, C_WHITE);
	return 1;
}

ShowGunShopList(playerid, states)
{
	if (!ShowSelectMenu(playerid, states, "Buy"))
	{
		SendClientMessage(playerid, C_WHITE, !ERROR_INTERFACE);
		return;
	}
	
	if (states)
	{	
		SetPVarInt(playerid, "GunShop:Page", 0);
		
		SelectTextDraw(playerid, C_GRAY);
		
		UpdateGunShopList(playerid, 0);
	}
	else 
	{	
		for (new i; i < TD_SELECT_MENU_ARRAY; i++)
		{
			g_td_select[playerid][i] = INVALID_PARAM;
		}
		
		DeletePVar(playerid, "GunShop:Page");
	}
	
	SetPVarInt(playerid, "GunShop:States", states);
}

UpdateGunShopList(playerid, index)
{		
	if (!(0 <= index < sizeof gun_shop_list))
	{
		return;
	}
	
	SetPVarInt(playerid, "GunShop:Page", index);
	
	for (new i, itindex; i < TD_SELECT_MENU_ARRAY; i++)
	{
		if (i + index > sizeof gun_shop_list)
		{
			PlayerTextDrawHide(playerid, ptd_select_menu[playerid][i]);
			g_td_select[playerid][i] = INVALID_PARAM;
			continue;
		}
		
		if ((itindex = GetItemIndexById(gun_shop_list[i + index][gs_item_id])) == INVALID_ITEM_ID)
		{
			continue;
		}
		
		PlayerTextDrawSetPreviewModel(
			playerid, 
			ptd_select_menu[playerid][i], 
			item_list[itindex][it_model]
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

ShowPlayerGunList(playerid)
{
	new itindex,
		count;
	
	clean:<g_string>;
	strcat(g_string, #cPROJECT "Название\t" #cPROJECT "Серийный номер\n");
	
	for (new i; i < MAX_INVENTORY_SLOTS; i++)
	{
		itindex = GetItemIndexById(GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_item_id));
		
		if ((item_list[itindex][it_type] == INV_WEAPON_BIG || item_list[itindex][it_type] == INV_WEAPON_SMALL) 
		&& GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_param_2) == GetCharacterId(playerid))
		{
			format:g_string("%s " #cWHITE "%s\t" #cWHITE"№%i\n",
				g_string,
				item_list[itindex][it_name],
				GetWeaponSerialNumber(GetInventoryEnumItem(playerid, i, TYPE_INV_PLAYER, inv_id))
			);
			
			g_dialog_select[playerid][count] = i;
			count++;
		}
	}
	
	return count == 0 ? SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас отсутствует в инвентаре оружие, купленное в оружейном магазине.") 
	: ShowPlayerDialog(playerid, D_GUNSHOP + 2, DIALOG_STYLE_TABLIST_HEADERS, " ", g_string, "Далее", "Назад");
}

GetPlayerMaxWeapons(playerid)
{
	#pragma unused playerid
	
	return MAX_CHARACTER_BUY_WEAPON;
}

GetPlayerAvaibleWeapon(playerid)
{
	return (GetPlayerMaxWeapons(playerid) - character_data[playerid][c_buy_weapon_count]) <= 0 ? false : true;
}