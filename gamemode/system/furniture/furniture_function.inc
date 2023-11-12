/*!
	@brief Функции для системы фурнитуры
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

Clear:furn_pvar(playerid)
{
	SetPVarInt(playerid, "Furn:Select", INVALID_PARAM);
	
	DeletePVar(playerid, "Furn:SelectObject");
	
	DeletePVar(playerid, "FurnList:Index");
	DeletePVar(playerid, "FurnList:BeginIndex");
	DeletePVar(playerid, "FurnList:EndIndex");
	
	DeletePVar(playerid, "Furn:Edit");
	DeletePVar(playerid, "Furn:EditIndex");
	
	Clear:player_furn_pvar(playerid);
}

Clear:player_furn_pvar(playerid)
{
	DeletePVar(playerid, "Player:IsFurnEditing");
	DeletePVar(playerid, "Player:FurnEditIndex");
}

// Public function
Furn_OnPlayerDisconnect(playerid)
{
	if (!IsPlayerLogged(playerid))
	{
		return;
	}
	
	if (GetPVarInt(playerid, "Furn:Edit"))
	{
		new index = GetPVarInt(playerid, "Furn:EditIndex");
		
		if (!furn_data[index][f_state])
		{
			if (IsValidDynamicObject(furn_data[index][f_object]))
			{
				DestroyDynamicObject(furn_data[index][f_object]);
			}

			furn_data[index][f_object] = INVALID_OBJECT_ID;
		}
		else 
		{
			SetDynamicObjectPos(furn_data[index][f_object], 
				furn_data[index][f_pos_x], 
				furn_data[index][f_pos_y], 
				furn_data[index][f_pos_z]
			);
			
			SetDynamicObjectRot(furn_data[index][f_object], 
				furn_data[index][f_rot_x], 
				furn_data[index][f_rot_y], 
				furn_data[index][f_rot_z] 
			);
		}
	}
}

Furn_OnPlayerClickPTD(playerid, PlayerText: playertextid)
{
	if (!GetPVarInt(playerid, "FurnList:States"))
	{
		return 1;
	}
	
	new furn_index,
		cat_index,
		slots,
		str_slots			[	16	];
		
	for (new i; i < TD_SELECT_MENU_ARRAY; i++)
	{
		if (playertextid == ptd_select_menu[playerid][i])
		{
			furn_index = g_td_select[playerid][i];
			cat_index = furniture_list[furn_index][fitem_cat];
			slots = furniture_list[furn_index][fitem_slot];
			
			SetPVarInt(playerid, "FurnList:BuyIndex", 
				furn_index
			);
			
			clean:<str_slots>;
			
			if (slots != 0)
			{
				format:str_slots("- %i слот%s", 
					slots,
					EndWordSlot(slots)
				);
			}
			
			format:g_string("" #DEFAULT " Информация\n\n\
			Категория: " #cPROJECT "%s" #cWHITE"\n\
			Вместимость предметов: %s %s" #cWHITE "\n\
			Изменение текстуры: %s" #cWHITE "\n\n\
			Вы подтверждаете покупку " #cPROJECT "%s" #cWHITE " за " #cGREEN "$%i" #cWHITE "?",
				furniture_cat_list[cat_index][fcat_name],
				slots ? ("" #cPROJECT "да") : ("" #cGRAY "нет"),
				str_slots,
				(furniture_list[furn_index][fitem_material_index] != INVALID_PARAM) ? ("" #cPROJECT "да") : ("" #cGRAY "нет"),
				furniture_list[furn_index][fitem_name],
				furniture_cat_list[cat_index][fcat_cost]
				
			);
			
			ShowPlayerDialog(playerid, D_FURN + 4, DIALOG_STYLE_MSGBOX, " ", g_string, "Да", "Нет");
			break;
		}
	}
	
	return 1;
}

Furn_OnPlayerClickTextDraw(playerid, Text: clickedid)
{
	if (clickedid == INVALID_TEXT_DRAW)
	{
		if (GetPVarInt(playerid, "FurnList:States"))
		{
			ShowFurnList(playerid, false);
			ShowFurnCat(playerid, D_FURN + 3);
		}
	}
	else if (clickedid == td_select_menu[1]) // next
	{
		UpdateFurnList(playerid, GetPVarInt(playerid, "FurnList:Index") + TD_SELECT_MENU_ARRAY);
	}
	else if (clickedid == td_select_menu[2]) // last 
	{
		UpdateFurnList(playerid, GetPVarInt(playerid, "FurnList:Index") - TD_SELECT_MENU_ARRAY);
	}
	
	return 1;
}

function Furn_OnPlayerSDO(playerid, objectid, modelid, Float: x, Float: y, Float: z) 
{
	if (!GetPVarInt(playerid, "Furn:SelectObject") || !IsPlayerRenovation(playerid))
	{
		return 1;
	}
	
	new furn_object;
		
	for (new i; i < sizeof furn_data; i++)
	{
		if ((furn_object = furn_data[i][f_object]) == INVALID_OBJECT_ID)
		{
			continue;
		}
		
		if (furn_object == objectid)
		{
			SetPVarInt(playerid, "Furn:SelectByCMD", true);
			SetPVarInt(playerid, "Furn:Select", i);
			ShowFurnItemMenu(playerid, i);
			DeletePVar(playerid, "Furn:SelectObject");
			break;
		}
	}
	
	return 1;
}

function Furn_OnPlayerEditDynamicObject(playerid, objectid, response, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz)
{
	if (!GetPVarInt(playerid, "Furn:Edit") || !IsPlayerRenovation(playerid))
	{
		DeletePVar(playerid, "Furn:Edit");
		DeletePVar(playerid, "Furn:EditIndex");
		return 1;
	}
	
	new index = GetPVarInt(playerid, "Furn:EditIndex");
	
	if (response == EDIT_RESPONSE_CANCEL)
	{
		if (!furn_data[index][f_state])
		{
			if (IsValidDynamicObject(furn_data[index][f_object]))
			{
				DestroyDynamicObject(furn_data[index][f_object]);
			}

			furn_data[index][f_object] = INVALID_OBJECT_ID;
		}
		else 
		{
			SetDynamicObjectPos(objectid, 
				furn_data[index][f_pos_x], 
				furn_data[index][f_pos_y], 
				furn_data[index][f_pos_z]
			);
			
			SetDynamicObjectRot(objectid, 
				furn_data[index][f_rot_x], 
				furn_data[index][f_rot_y], 
				furn_data[index][f_rot_z] 
			);
		}
	}
	else if (response == EDIT_RESPONSE_FINAL)
	{
		furn_data[index][f_pos_x] = x;
		furn_data[index][f_pos_y] = y;
		furn_data[index][f_pos_z] = z;
		
		furn_data[index][f_rot_x] = rx;
		furn_data[index][f_rot_y] = ry;
		furn_data[index][f_rot_z] = rz;
		
		furn_data[index][f_state] = 1;
		
		Update:furn_data(index);
		
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно отредактировали положение мебели.");
	}
	
	if (response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL)
	{
		DeletePVar(playerid, "Furn:Edit");
		DeletePVar(playerid, "Furn:EditIndex");
		
		if (!GetPVarInt(playerid, "Furn:SelectByCMD"))
		{
			ShowFurnItemMenu(playerid, GetPVarInt(playerid, "Furn:Select"));
		}
	}
	
	return 1;
}

// Other function
Create:furn(id, furn_index, type, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz)
{
	new interior,
		texture_index;
		
	if (type == TYPE_REN_HOUSE)
	{
		interior = INT_HOUSE;
	}
	else if (type == TYPE_REN_GARAGE)
	{
		interior = INT_GARAGE;
	}
	else if (type == TYPE_REN_PREMISE)
	{
		interior = INT_PREMISE;
	}
	
	furn_data[furn_index][f_object] = CreateDynamicObject(
		furniture_list[furn_data[furn_index][f_item_index]][fitem_model],
		x,
		y,
		z,
		rx,
		ry,
		rz,
		id,
		interior,
		_,
		100 // stream distance
	);
	
	if ((texture_index = furn_data[furn_index][f_texture_index]))
	{
		SetFurnMaterial(
			furn_index, 
			furn_data[furn_index][f_texture_type], 
			texture_index
		);
	}
}

Remove:furn(index)
{
	if (furn_data[index][f_state])
	{
		DestroyDynamicObject(furn_data[index][f_object]);
	}
	
	Clear:furniture_data(index);
}

ShowFurnMenu(playerid, action, dialogid)
{
	clean:<g_big_string>;
	
	Clear:player_furn_pvar(playerid);
	
	new index = GetRenovationIndex(playerid),
		type = GetRenovationType(playerid),
		page,
		count,
		str_furn_edit			[	64 	];
	
	if (action == ITEM_LIST_BEGIN)
	{
		SetPVarInt(playerid, "Furn:Page", 0);
		page = 0;
	}
	else if (action == ITEM_LIST_CURRENT)
	{
		page = GetPVarInt(playerid, "Furn:Page");
	}
	else if (action == ITEM_LIST_NEXT)
	{
		GivePVarInt(playerid, "Furn:Page", 1);
		page = GetPVarInt(playerid, "Furn:Page");
	}
	else if (action == ITEM_LIST_BACK)
	{
		TakePVarInt(playerid, "Furn:Page", 1);
		page = GetPVarInt(playerid, "Furn:Page");
	}
	
	strcat(g_big_string, "" #cGRAY "Добавить мебель\t" #cWHITE "\n");
	for (new i, j; i < sizeof furn_data; i++)
	{		
		if (!furn_data[i][f_id] 
		|| furn_data[i][f_owner_index] != index 
		|| furn_data[i][f_owner_type] != type)
		{	
			continue;
		}
		
		if (j != (page * MAX_ITEM_LIST))
		{
			j++;
			continue;
		}
		
		clean:<str_furn_edit>;
		if (IsFurnEditing(i, playerid))
		{
			strcat(str_furn_edit, " " #cWHITE "[" #cDARKRED " редактируется " #cWHITE "]");
		}
		
		format:g_big_string("%s %s%s\t%s" #cWHITE "\n",
			g_big_string,
			furniture_list[furn_data[i][f_item_index]][fitem_name],
			str_furn_edit,
			furn_data[i][f_state] ? ("" #cPROJECT "Установлено") : ("" #cGRAY "Не установлено")
		);
		
		g_dialog_select[playerid][count++] = i;
		if (count == MAX_ITEM_LIST)
		{
			break;
		}
	}

	if (count == MAX_ITEM_LIST)
	{
		strcat(g_big_string, "" #cGRAY "Вперед\t\t" #cWHITE ">>");
		g_dialog_select[playerid][count++] = ITEM_LIST_NEXT;
	}
	
	if (page > 0)
	{
		strcat(g_big_string, "\n" #cGRAY "Назад\t" #cWHITE "<<");
		g_dialog_select[playerid][count] = ITEM_LIST_BACK;
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, " ", g_big_string, "Выбрать", "Назад");
	return 1;
}

ShowFurnItemMenu(playerid, index)
{
	if (IsFurnEditing(index, playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный объект мебели уже редактируется другим игроком.");
		
		if (!GetPVarInt(playerid, "Furn:SelectByCMD"))
		{
			ShowFurnMenu(playerid, ITEM_LIST_CURRENT, D_FURN);
		}
		
		return;
	}
	
	SetPVarInt(playerid, "Player:IsFurnEditing", true);
	SetPVarInt(playerid, "Player:FurnEditIndex", index);
	
	format:g_string(
		" %s\n \
		Убрать мебель\n \
		Изменить текстуру\n \
		Удалить мебель",
		!furn_data[index][f_state] ? ("Установить положение мебели") : ("Изменить положение мебели")
	);
	
	ShowPlayerDialog(playerid, D_FURN + 1, DIALOG_STYLE_LIST, 
		furniture_list[furn_data[index][f_item_index]][fitem_name], 
		g_string,
		"Выбрать", "Назад" 
	);
}

IsFurnEditing(index, playerid)
{
	foreach (new i : Player)
	{
		if (playerid == i)
		{
			continue;
		}
		
		if (GetPVarInt(i, "Player:IsFurnEditing") 
		&& GetPVarInt(i, "Player:FurnEditIndex") == index)
		{
			return 1;
		}
	}
	
	return 0;
}

ShowFurnCat(playerid, dialogid)
{	
	clean:<g_big_string>;
	
	strcat(g_big_string, "" #cPROJECT "Категория\t" #cPROJECT "Количество объектов\t" #cPROJECT "Цена\n");
	for (new i; i < sizeof furniture_cat_list; i++)
	{
		format:g_small_string(" %s\t" #cGRAY "%i\t" #cGREEN "$%i" #cWHITE "\n",
			furniture_cat_list[i][fcat_name],
			GetFurnListCountByCat(i),
			furniture_cat_list[i][fcat_cost]
		);
		
		strcat(g_big_string, g_small_string);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, " ", g_big_string, "Далее", "Назад");
}

ShowFurnList(playerid, states, cat = INVALID_PARAM)
{
	new begin_index,
		end_index;
	
	if (!ShowSelectMenu(playerid, states))
	{
		SendClientMessage(playerid, C_WHITE, !ERROR_INTERFACE);
		return;
	}
	
	if (states)
	{	
		GetFurnIdentifyEnds(cat, begin_index, end_index);
		
		SetPVarInt(playerid, "FurnList:Index", begin_index);
		SetPVarInt(playerid, "FurnList:BeginIndex", begin_index);
		SetPVarInt(playerid, "FurnList:EndIndex", end_index);
		
		SelectTextDraw(playerid, C_GRAY);
		
		UpdateFurnList(playerid, begin_index);
	}
	else 
	{	
		for (new i; i < TD_SELECT_MENU_ARRAY; i++)
		{
			g_td_select[playerid][i] = INVALID_PARAM;
		}
		
		DeletePVar(playerid, "FurnList:Index");
		DeletePVar(playerid, "FurnList:BeginIndex");
		DeletePVar(playerid, "FurnList:EndIndex");
	}
	
	SetPVarInt(playerid, "FurnList:States", states);
}

UpdateFurnList(playerid, index)
{	
	new begin_index = GetPVarInt(playerid, "FurnList:BeginIndex"),
		end_index = GetPVarInt(playerid, "FurnList:EndIndex");
		
	if (!(begin_index <= index <= end_index))
	{
		return;
	}
	
	SetPVarInt(playerid, "FurnList:Index", index);
	
	for (new i; i < TD_SELECT_MENU_ARRAY; i++)
	{
		if (i + index > end_index)
		{
			PlayerTextDrawHide(playerid, ptd_select_menu[playerid][i]);
			g_td_select[playerid][i] = INVALID_PARAM;
			continue;
		}
		
		PlayerTextDrawSetPreviewModel(
			playerid, 
			ptd_select_menu[playerid][i], 
			furniture_list[i + index][fitem_model] 
		);
		
		PlayerTextDrawSetPreviewRot(
			playerid, 
			ptd_select_menu[playerid][i], 
			0.0, 
			0.0, 
			0.0, 
			1.3
		);
		
		PlayerTextDrawShow(playerid, ptd_select_menu[playerid][i]);
		
		g_td_select[playerid][i] = i + index;
	}
}

GetFurnIdentifyEnds(cat, &begin_index, &end_index)
{
	for (new i; i < sizeof furniture_list; i++)
	{
		if (furniture_list[i][fitem_cat] != cat)
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

GetFurnListCountByCat(cat)
{
	new begin_index,
		end_index;
		
	GetFurnIdentifyEnds(cat, begin_index, end_index);
	return (end_index - begin_index) + 1;
}

GetFurnCount(index, type)
{
	new count;
		
	for (new i; i < sizeof furn_data; i++)
	{
		if (!furn_data[i][f_id])
		{
			continue;
		}
		
		if (furn_data[i][f_owner_index] != index
		|| furn_data[i][f_owner_type] != type)
		{
			continue;
		}
		
		count++;
	}
	
	return count;
}

GetFurnMaxCount(index, type)
{
	if (type == TYPE_REN_HOUSE)
	{
		return GetHouseSettings(index, hset_furnitures) ;
	}
	else if (type == TYPE_REN_GARAGE)
	{
		return GetGarageSettings(index, hgset_furnitures) ;
	}
	else if (type == TYPE_REN_PREMISE)
	{
		return GetPremiseSettings(index, pset_furnitures) ;
	}
	
	return 0;
}

SetFurnMaterial(index, texture_type = INVALID_PARAM, texture = INVALID_PARAM)
{
	if (texture_type == INVALID_PARAM)
	{
		SetDynamicObjectMaterial(
			furn_data[index][f_object], 
			furniture_list[furn_data[index][f_item_index]][fitem_material_index], 
			-1, 
			"none", 
			"none", 
			0 
		);
		
		return;
	}
	
	new model,
		txd_name				[	34	],
		texture_name			[	34 	];
	
	GetTextureByType(texture_type, texture, model, txd_name, texture_name);
	
	SetDynamicObjectMaterial(
		furn_data[index][f_object], 
		furniture_list[furn_data[index][f_item_index]][fitem_material_index], 
		model, 
		txd_name, 
		texture_name, 
		0
	);
}

GetFurnItemIndexByItemId(const item_id)
{
	for (new i; i < sizeof furniture_list; i++)
	{
		if (furniture_list[i][fitem_id] == item_id)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

GetFurnOwnerId(const index, type)
{
	if (type == TYPE_REN_HOUSE || type == TYPE_REN_GARAGE)
	{	
		return GetHouseId(index);
	}
	else if (type == TYPE_REN_PREMISE)
	{
		return GetPremiseId(index);
	}

	return INVALID_PARAM;
}