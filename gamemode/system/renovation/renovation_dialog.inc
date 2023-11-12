/*!
	@brief Диалоги для системы ремонта
	@author Found (evg.savosin)
	@date 12.02.2020
*/

function Ren_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == D_RENOVATION)
	{
		if (!response)
		{
			return 1;
		}
		
		new property_type = GetPVarInt(playerid, "TextureList:PropertyType"),
			furn_index = GetPVarInt(playerid, "Furn:Select"),
			room,
			type = ren_data[playerid][ren_type],
			index = ren_data[playerid][ren_index],
			texture_type = GetPVarInt(playerid, "TextureList:Type");
		
		if (listitem == 0)
		{
			if ((GetCharacterMoney(playerid) - COST_RETEXTURE) < 0)
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
				return 1;
			}

			if (property_type == TYPE_MULTI)
			{
				if (type == TYPE_REN_HOUSE)
				{
					room = GetPVarInt(playerid, "House:Room");
					
					if (texture_type == TEXTURE_ROOF)
					{
						hroom_data[index][room][r_roof] = GetPVarInt(playerid, "TextureList:BuyIndex");
					}
					else if (texture_type == TEXTURE_WALL)
					{
						hroom_data[index][room][r_wall] = GetPVarInt(playerid, "TextureList:BuyIndex");
					}
					else if (texture_type == TEXTURE_FLOOR)
					{
						hroom_data[index][room][r_floor] = GetPVarInt(playerid, "TextureList:BuyIndex");
					}
					
					Update:room_data(index, room, type);
				}
				else if (type == TYPE_REN_PREMISE)
				{
					room = GetPVarInt(playerid, "Premise:Room");
					
					if (texture_type == TEXTURE_ROOF)
					{
						proom_data[index][room][r_roof] = GetPVarInt(playerid, "TextureList:BuyIndex");
					}
					else if (texture_type == TEXTURE_WALL)
					{
						proom_data[index][room][r_wall] = GetPVarInt(playerid, "TextureList:BuyIndex");
					}
					else if (texture_type == TEXTURE_FLOOR)
					{
						proom_data[index][room][r_floor] = GetPVarInt(playerid, "TextureList:BuyIndex");
					}
					
					Update:room_data(index, room, type);
				}
			}
			else if (property_type == TYPE_SINGLE && type != TYPE_REN_NONE)
			{
				new model_id,
					txd_name			[	64	],
					texture_name		[	64	],
					temp;
				
				GetDynamicObjectMaterial(
					furn_data[furn_index][f_object], 
					furniture_list[furn_data[furn_index][f_item_index]][fitem_material_index], 
					model_id, 
					txd_name, 
					texture_name, 
					temp 
				);
				
				SetPVarInt(playerid, "FurnTexture:ModelId", model_id);
				SetPVarString(playerid, "FurnTexture:TxdName", txd_name);
				SetPVarString(playerid, "FurnTexture:TextureName", texture_name);
				
				furn_data[furn_index][f_texture_type] = texture_type;
				furn_data[furn_index][f_texture_index] = GetPVarInt(playerid, "TextureList:BuyIndex");
				
				Update:furn_data(furn_index);
			}
			
			GivePlayerCash(playerid, -COST_RETEXTURE);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно приобрели текстуру.");
		}
		else if (listitem == 1)
		{
			if (property_type == TYPE_MULTI)
			{
				ResetToDefaultTextures(playerid, property_type);
			}
			else 
			{
				SetFurnMaterial(furn_index, INVALID_PARAM, INVALID_PARAM);
			}
		}
		
		ShowTextureList(playerid, false, TEXTURE_NONE);
	}
	
	return 1;
}