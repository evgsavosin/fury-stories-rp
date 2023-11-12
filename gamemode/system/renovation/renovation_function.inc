/*!
	@brief Функции для системы ремонта
	@author Found (evg.savosin)
	@date 12.02.2020
*/

public OnPlayerSelect3DMenuBox(playerid, boxid)
{
	if (!IsPlayerRenovation(playerid))
	{
		return 1;
	}
	
	SetPVarInt(playerid, "TextureList:BuyIndex", (GetPVarInt(playerid, "TextureList:Page")) + boxid);
	
	format:g_string(" Приобрести текстуру\t" #cGREEN "$%d" #cWHITE "\n \
	Выйти из редактора", COST_RETEXTURE);
	ShowPlayerDialog(playerid, D_RENOVATION, DIALOG_STYLE_TABLIST, " ", g_string, "Выбрать", "Закрыть");
	return 1;
}

public OnPlayerChange3DMenuBox(playerid, boxid)
{
	if (!IsPlayerRenovation(playerid))
	{
		return 1;
	}
	
	new	
		property_type = GetPVarInt(playerid, "TextureList:PropertyType"),
		furn_index = GetPVarInt(playerid, "Furn:Select"),
		room,
		type = ren_data[playerid][ren_type],
		index = ren_data[playerid][ren_index],
		texture_index = (GetPVarInt(playerid, "TextureList:Page")) + boxid,
		texture_type = GetPVarInt(playerid, "TextureList:Type");
		
	if (property_type == TYPE_MULTI)
	{
		if (type == TYPE_REN_HOUSE)
		{
			room = GetPVarInt(playerid, "House:Room");
			
			if (texture_type == TEXTURE_ROOF)
			{
				SetHouseInteriorMaterial(
					index, 
					room, 
					hint_roof_begin, 
					hint_roof_end, 
					TEXTURE_ROOF,
					texture_index
				);
			}
			else if (texture_type == TEXTURE_WALL)
			{
				SetHouseInteriorMaterial(
					index, 
					room, 
					hint_wall_begin, 
					hint_wall_end, 
					TEXTURE_WALL,
					texture_index
				);
			}
			else if (texture_type == TEXTURE_FLOOR)
			{
				SetHouseInteriorMaterial(
					index, 
					room, 
					hint_floor_begin, 
					hint_floor_end, 
					TEXTURE_FLOOR,
					texture_index
				);
			}
		}
		else if (type == TYPE_REN_PREMISE)
		{
			room = GetPVarInt(playerid, "Premise:Room");
			
			if (texture_type == TEXTURE_ROOF)
			{
				SetPremiseInteriorMaterial(
					index, 
					room, 
					pint_roof_begin, 
					pint_roof_end, 
					TEXTURE_ROOF,
					texture_index
				);
			}
			else if (texture_type == TEXTURE_WALL)
			{
				SetPremiseInteriorMaterial(
					index, 
					room, 
					pint_wall_begin, 
					pint_wall_end, 
					TEXTURE_WALL,
					texture_index
				);
			}
			else if (texture_type == TEXTURE_FLOOR)
			{
				SetPremiseInteriorMaterial(
					index, 
					room, 
					pint_floor_begin, 
					pint_floor_end, 
					TEXTURE_FLOOR,
					texture_index
				);
			}
		}
	}
	else if (property_type == TYPE_SINGLE) // объект фурнитуры
	{
		SetFurnMaterial(furn_index, texture_type, texture_index);
	}
	
	return 1;
}

Ren_OnPlayerSpawn(playerid)
{
	if (IsPlayerRenovation(playerid))
	{
		SetRenovationMode(playerid, false);
	}
	
	return 1;
}

Ren_OnPlayerDeath(playerid, killerid, reason)
{
	#pragma unused killerid
	#pragma unused reason 
	
	if (IsPlayerRenovation(playerid))
	{
		SetRenovationMode(playerid, false);
	}
	
	return 1;
}

Ren_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (!IsPlayerRenovation(playerid))
	{
		return 1;
	}
	
	if (PRESSED(KEY_NO))
	{
		if (ShowRenovationMenu(playerid))
		{
			return 0;
		}
	}
	
	if (GetPVarInt(playerid, "TextureList:States"))
	{
		new type = GetPVarInt(playerid, "TextureList:Type"),
			page = GetPVarInt(playerid, "TextureList:Page");
		
		if (PRESSED(KEY_ANALOG_LEFT))
		{
			UpdateTextureList(playerid, page - 8, type);
			UpdateSelect3DMenu(playerid);
			
			return 0;
		}
		else if (PRESSED(KEY_ANALOG_RIGHT))
		{
			UpdateTextureList(playerid, page + 8, type);
			UpdateSelect3DMenu(playerid);
			
			return 0;
		}
	}
	
	return 1;
}

ShowTextureList(playerid, states, type = INVALID_PARAM, property_type = TYPE_MULTI)
{
	if (states)
	{
		new Float: x,
			Float: y,
			Float: z,
			Float: angle;
			
		if (!GetPlayerPos(playerid, x, y, z))
		{
			return;
		}
		
		GetPlayerFacingAngle(playerid, angle);
		
		x += (1.7 * floatsin(-angle, degrees));
		y += (1.7 * floatcos(-angle, degrees));

		SetPVarInt(playerid, "TextureList:Type", type);
		SetPVarInt(playerid, "TextureList:PropertyType", property_type);
		
		Create3DMenu(playerid, x, y, z, angle, 8);
		UpdateTextureList(playerid, 0, type);
		Select3DMenu(playerid);
		
		SendClientMessage(playerid, C_WHITE, !HELP_3DMENU_ONE);
		SendClientMessage(playerid, C_WHITE, !HELP_3DMENU_TWO);
	}
	else 
	{
		DeletePVar(playerid, "TextureList:BuyIndex");
		DeletePVar(playerid, "TextureList:Type");
		DeletePVar(playerid, "TextureList:Page");
		DeletePVar(playerid, "TextureList:PropertyType");
		
		CancelSelect3DMenu(playerid);
		Destroy3DMenu(playerid);
	}
	
	SetPVarInt(playerid, "TextureList:States", states);
}

UpdateTextureList(playerid, page = 0, texture_type)
{
	new model,
		txd_name				[	34	],
		texture_name			[	34 	],
		sizeof_textures,
		page_calculcate;
	
	switch(texture_type)
	{
		case TEXTURE_ROOF :
		{
			sizeof_textures = sizeof textures_roof;
		}
		case TEXTURE_WALL :
		{
			sizeof_textures = sizeof textures_wall;
		}
		
		case TEXTURE_FLOOR :
		{
			sizeof_textures = sizeof textures_floor;
		}
		
		case TEXTURE_DOOR :
		{
			sizeof_textures = sizeof textures_door;
		}
		
		case TEXTURE_WINDOW :
		{
			sizeof_textures = sizeof textures_window;
		}
	}
		

	if (page < 0)
	{
		page_calculcate = (8 - (sizeof_textures % 8));
		page = (sizeof_textures + (page_calculcate == 8 ? 0 : page_calculcate)) - 8;
	}
	else if (page >= sizeof_textures)
	{
		page = 0;
	}	
	
	SetPVarInt(playerid, "TextureList:Page", page);
	
	for (new i; i < MAX_BOXES; i++)
	{	
		if (i + page >= sizeof_textures)
		{
			SetBoxMaterial(
				playerid, 
				i, 
				0, 
				19480, 
				"signsurf", 
				"sign",
				0, 
				0x00000000,
				true
			);
			
			continue;
		}
		
		GetTextureByType(texture_type, i + page, model, txd_name, texture_name);

		SetBoxMaterial(
			playerid, 
			i, 
			0, 
			model, 
			txd_name, 
			texture_name,
			0, 
			0xFF999999 
		);
		
	}
}

ShowRenovationInfo(playerid, states)
{
	if (states)
	{
		TextDrawShowForPlayer(playerid, td_renovation);

		UpdateRenovationInfo(playerid);
		
		PlayerTextDrawShow(playerid, td_ren_text[playerid]);
	}
	else 
	{
		TextDrawHideForPlayer(playerid, td_renovation);
		PlayerTextDrawHide(playerid, td_ren_text[playerid]);
	}
}

UpdateRenovationInfo(playerid)
{
	format:g_small_string("Renovation ~g~On~w~~h~~n~Objects: %i~n~~w~~h~Object Limit: %i", 
		GetFurnCount(GetRenovationIndex(playerid), GetRenovationType(playerid)),
		GetRenovationMaxFurn(playerid)
	);
	
	PlayerTextDrawSetString(playerid, td_ren_text[playerid], g_small_string);
}

SetRenovationMode(playerid, states, type = TYPE_REN_NONE, index = INVALID_PARAM, id = 0, max_furn = 0)
{	
	if (states)
	{
		ren_data[playerid][ren_id] = id;
		ren_data[playerid][ren_index] = index;
		ren_data[playerid][ren_type] = type;
		ren_data[playerid][ren_max_furn] = max_furn;
		Create:ren_text3d(playerid, type, index);
	}
	else 
	{
		if (GetPVarInt(playerid, "TextureList:States"))
		{
			ResetToDefaultTextures(playerid, GetPVarInt(playerid, "FurnList:PropertyType"));
			ShowTextureList(playerid, false);
		}
		
		if (GetPVarInt(playerid, "SelectMenu:States"))
		{
			ShowFurnList(playerid, false);
		}
		
		Clear:furn_pvar(playerid);
		Clear:ren_data(playerid);
	}
	
	ShowRenovationInfo(playerid, states);
}

ResetToDefaultTextures(playerid, property_type)
{
	new furn_index = GetPVarInt(playerid, "Furn:Select"),
		room,
		type = ren_data[playerid][ren_type],
		index = ren_data[playerid][ren_index],
		texture_type = GetPVarInt(playerid, "TextureList:Type");
	
	if (property_type == TYPE_MULTI)
	{
		if (type == TYPE_REN_HOUSE)
		{
			room = GetPVarInt(playerid, "House:Room");
			
			if (texture_type == TEXTURE_ROOF)
			{
				SetHouseInteriorMaterial(
					index, 
					room, 
					hint_roof_begin, 
					hint_roof_end, 
					TEXTURE_ROOF,
					hroom_data[index][room][r_roof] 
				);
			}
			else if (texture_type == TEXTURE_WALL)
			{
				SetHouseInteriorMaterial(
					index, 
					room, 
					hint_wall_begin, 
					hint_wall_end, 
					TEXTURE_WALL,
					hroom_data[index][room][r_wall] 
				);
			}
			else if (texture_type == TEXTURE_FLOOR)
			{
				SetHouseInteriorMaterial(
					index, 
					room, 
					hint_floor_begin, 
					hint_floor_end, 
					TEXTURE_FLOOR,
					hroom_data[index][room][r_floor] 
				);
			}
		}
		else if (type == TYPE_REN_PREMISE)
		{
			room = GetPVarInt(playerid, "Premise:Room");
			
			if (texture_type == TEXTURE_ROOF)
			{
				SetPremiseInteriorMaterial(
					index, 
					room, 
					pint_roof_begin, 
					pint_roof_end, 
					TEXTURE_ROOF,
					proom_data[index][room][r_roof] 
				);
			}
			else if (texture_type == TEXTURE_WALL)
			{
				SetPremiseInteriorMaterial(
					index, 
					room, 
					pint_wall_begin, 
					pint_wall_end, 
					TEXTURE_WALL,
					proom_data[index][room][r_wall] 
				);
			}
			else if (texture_type == TEXTURE_FLOOR)
			{
				SetPremiseInteriorMaterial(
					index, 
					room, 
					pint_floor_begin, 
					pint_floor_end, 
					TEXTURE_FLOOR,
					proom_data[index][room][r_floor] 
				);
			}
		}
	}
	else if (property_type == TYPE_SINGLE)
	{
		new txd_name		[	64	],
			texture_name	[	64	];
			
		GetPVarString(playerid, "FurnTexture:TxdName", txd_name, sizeof txd_name);
		GetPVarString(playerid, "FurnTexture:TextureName", texture_name, sizeof texture_name);
		
		new furn_list_index = furn_data[furn_index][f_item_index];
			
		SetDynamicObjectMaterial(
			furn_data[furn_index][f_object], 
			furniture_list[furn_list_index][fitem_material_index], 
			GetPVarInt(playerid, "FurnTexture:ModelId"),
			txd_name,
			texture_name
		);
	}
	
	
	DeletePVar(playerid, "FurnTexture:TxdName");
	DeletePVar(playerid, "FurnTexture:TextureName");
	DeletePVar(playerid, "FurnTexture:ModelId");
}

Create:ren_text3d(playerid, type, index)
{
	new world,
		room,
		int_type,
		room_index;

	if (type == TYPE_REN_HOUSE)
	{
		world = GetHouseId(index);
		int_type = house_data[index][h_int_type];
		room = house_settings[int_type][hset_rooms];

		for (new i, Text3D: text; i < room; i++)
		{
			room_index = GetRoomIndexByNumber(type, int_type, i);

			if (room_index == INVALID_PARAM)
			{
				continue;
			}
			
			format:g_small_string("Зона #%d",
				i + 1
			);
			
			text = CreateDynamic3DTextLabel(
				g_small_string, 
				C_WHITE, 
				hroom_coord[room_index][rc_pos][0], 
				hroom_coord[room_index][rc_pos][1], 
				hroom_coord[room_index][rc_pos][2] - 0.2, 
				TEXT3D_DRAW_DISTANCE, 
				_,
				_, 
				1, 
				world, 
				INT_HOUSE, 
				playerid,
				TEXT3D_DRAW_DISTANCE
			);
			
			if (i == 0)
			{
				ren_data[playerid][ren_text][0] = text;
			}
			else if (i == room)
			{
				ren_data[playerid][ren_text][1] = text;
			}
		}
	}
	else if (type == TYPE_REN_PREMISE)
	{
		world = GetPremiseId(index);
		int_type = premise_data[index][pr_int_type];
		room = premise_settings[int_type][pset_rooms];

		for (new i, Text3D: text; i < room; i++)
		{
			room_index = GetRoomIndexByNumber(type, int_type, i);

			if (room_index == INVALID_PARAM)
			{
				continue;
			}
			
			format:g_small_string("Зона #%d",
				i + 1
			);
			
			text = CreateDynamic3DTextLabel(
				g_small_string, 
				C_WHITE, 
				proom_coord[room_index][rc_pos][0], 
				proom_coord[room_index][rc_pos][1], 
				proom_coord[room_index][rc_pos][2] - 0.2, 
				TEXT3D_DRAW_DISTANCE, 
				_,
				_, 
				1, 
				world, 
				INT_PREMISE, 
				playerid,
				TEXT3D_DRAW_DISTANCE
			);
			
			if (i == 0)
			{
				ren_data[playerid][ren_text][0] = text;
			}
			else if (i == room)
			{
				ren_data[playerid][ren_text][1] = text;
			}
		}
	}
}

GetRoomIndexByNumber(type, type_int, number)
{
	if (type == TYPE_REN_HOUSE)
	{
		for (new i; i < sizeof hroom_coord; i++)
		{
			if (type_int == hroom_coord[i][rc_id]
			&& number == hroom_coord[i][rc_number])
			{
				return i;
			}
		}
	}
	else if (type == TYPE_REN_PREMISE)
	{
		for (new i; i < sizeof proom_coord; i++)
		{
			if (type_int == proom_coord[i][rc_id]
			&& number == proom_coord[i][rc_number])
			{
				return i;
			}
		}
	}
	
	return INVALID_PARAM;
}

ShowRenovationMenu(playerid)
{
	switch(GetRenovationType(playerid))
	{
		case TYPE_REN_HOUSE :
		{
			return HouseRenovation(playerid);
		}
		
		case TYPE_REN_GARAGE :
		{
			return GarageRenovation(playerid);
		}
		
		case TYPE_REN_PREMISE :
		{
			return PremiseRenovation(playerid);
		}
	}
	
	return 0;
}

/*
* @cmd: /ren
* @action: Меню ремонта
*/
CMD:ren(playerid)
{
	ShowRenovationMenu(playerid);
	
	return 1;
}
