/*!
	@brief Диалоги для системы фурнитуры
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

Furn_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	
	switch(dialogid)
	{
		case D_FURN :
		{
			if (!IsPlayerRenovation(playerid))
			{
				return 1;
			}
			
			if (!response)
			{
				return 1;
			}
			
			if (listitem == 0)
			{
				new rindex = GetRenovationIndex(playerid),
					rtype = GetRenovationType(playerid);
					
				if (GetFurnCount(rindex, rtype) >= GetFurnMaxCount(rindex, rtype))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Превышен лимит на мебель.");
					ShowFurnMenu(playerid, ITEM_LIST_CURRENT, D_FURN);
				}
				else 
				{
					ShowFurnCat(playerid, D_FURN + 3);
				}
				
				return 1;
			}
			
			listitem--;
			
			new index = g_dialog_select[playerid][listitem];

			if (index == ITEM_LIST_BACK)
			{
				ShowFurnMenu(playerid, ITEM_LIST_BACK, D_FURN);
				return 1;
			}
			else if (index == ITEM_LIST_NEXT)
			{
				ShowFurnMenu(playerid, ITEM_LIST_NEXT, D_FURN);
				return 1;
			}
	
			SetPVarInt(playerid, "Furn:Select", index);
			
			ShowFurnItemMenu(playerid, index);
		}
		
		case D_FURN + 1 :
		{
			if (!IsPlayerRenovation(playerid))
			{
				return 1;
			}
			
			new furn_index = GetPVarInt(playerid, "Furn:Select");
				
			if (!response)
			{
				if (!GetPVarInt(playerid, "Furn:SelectByCMD"))
				{
					ShowFurnMenu(playerid, ITEM_LIST_CURRENT, D_FURN);
				}
				
				DeletePVar(playerid, "Furn:SelectByCMD");
				
				DeletePVar(playerid, "Player:IsFurnEditing");
				DeletePVar(playerid, "Player:FurnEditIndex");
				return 1;
			}
			
			if (IsFurnEditing(furn_index, playerid))
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Данный объект мебели уже редактируется другим игроком.");
				ShowFurnItemMenu(playerid, furn_index);
				return 1;
			}
				
			if (listitem == 0)
			{
				SetPVarInt(playerid, "Furn:Edit", true);
				SetPVarInt(playerid, "Furn:EditIndex", furn_index);
				
				SendClientMessage(playerid, C_WHITE, !HELP_EDITOR);
				
				if (furn_data[furn_index][f_state]) // edit
				{
					EditDynamicObject(playerid, furn_data[furn_index][f_object]);
					Streamer_Update(playerid);	
				}
				else // create
				{	
					new Float: x,
						Float: y,
						Float: z,
						Float: angle,
						furn_cat = GetFurnCat(furn_data[furn_index][f_item_index]);
						
					GetPlayerPos(playerid, x, y, z);
					GetPlayerFacingAngle(playerid, angle);
					
					x += (2.0 * floatsin(-angle, degrees));
					y += (2.0 * floatcos(-angle, degrees));
					
					if (!furn_data[furn_index][f_texture_index])
					{
						if (furn_cat == TYPE_WINDOW)
						{
							furn_data[furn_index][f_texture_type] = TEXTURE_WINDOW;
						}
						else if (furn_cat == TYPE_WALL)
						{
							furn_data[furn_index][f_texture_type] = TEXTURE_WALL;
						}
						else if (furn_cat == TYPE_DOOR)
						{
							furn_data[furn_index][f_texture_type] = TEXTURE_DOOR;
						}
						
						furn_data[furn_index][f_texture_index] = 0;
						
						SendClientMessage(playerid, C_WHITE, !#DEFAULT " На объект была наложена пробная текстура. Изменить её можно через " #cPROJECT "меню расстановки или /fs" #cWHITE ".");
					}
					
					Create:furn(
						GetRenovationId(playerid), 
						furn_index, 
						GetRenovationType(playerid), 
						x, 
						y, 
						z, 
						0.0, 
						0.0, 
						0.0 
					);
					
					SetPVarInt(playerid, "Furn:EditMode", true);
					SetPVarInt(playerid, "Furn:EditObject", furn_data[furn_index][f_object]);
					
					EditDynamicObject(playerid, furn_data[furn_index][f_object]);
					Streamer_Update(playerid);
				}
				
				return 1;
			}
			else if (listitem == 1)
			{
				if (!furn_data[furn_index][f_state])
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете убрать данную мебель, так как она уже была убрана.");
					ShowFurnItemMenu(playerid, furn_index);
					return 1;
				}
				
				DestroyDynamicObject(furn_data[furn_index][f_object]);
				Clear:furniture_pos(furn_index);
				
				furn_data[furn_index][f_object] = INVALID_OBJECT_ID;
				furn_data[furn_index][f_state] = 0;
				
				Update:furn_data(furn_index);
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно убрали данную мебель.");
			}
			else if (listitem == 2) // изменить текстуру
			{
				if (!furn_data[furn_index][f_state])
				{
					ShowFurnItemMenu(playerid, furn_index);
					return 1;
				}
				
				new furn_list_index = furn_data[furn_index][f_item_index],
					furn_cat = GetFurnCat(furn_list_index);
					
				if (!IsFurnChangeMaterial(furn_list_index))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете изменить текстуру для данного объекта мебели.");
					ShowFurnItemMenu(playerid, furn_index);
					return 1;
				}
				
				new model_id,
					txd_name			[	64	],
					texture_name		[	64	],
					temp;
					
				GetDynamicObjectMaterial(
					furn_data[furn_index][f_object], 
					furniture_list[furn_list_index][fitem_material_index], 
					model_id, 
					txd_name, 
					texture_name, 
					temp 
				);
				
				SetPVarInt(playerid, "FurnTexture:ModelId", model_id);
				SetPVarString(playerid, "FurnTexture:TxdName", txd_name);
				SetPVarString(playerid, "FurnTexture:TextureName", texture_name);
				
				if (furn_cat == TYPE_DOOR) 
				{
					ShowTextureList(playerid, true, TEXTURE_DOOR, TYPE_SINGLE);
				}
				else if (furn_cat == TYPE_WINDOW)
				{
					ShowTextureList(playerid, true, TEXTURE_WINDOW, TYPE_SINGLE);
				}
				else if (furn_cat == TYPE_WALL)
				{
					ShowTextureList(playerid, true, TEXTURE_WALL, TYPE_SINGLE);
				}
				
				return 1;
			}
			else if (listitem == 3)
			{
				format:g_string(
					"" #DEFAULT " Удалить мебель\n\n\
					Вы подтверждаете удаление объекта мебели - " #cPROJECT "%s" #cWHITE "?",
					furniture_list[furn_data[furn_index][f_item_index]][fitem_name]
				);
				
				ShowPlayerDialog(playerid, D_FURN + 2, DIALOG_STYLE_MSGBOX, " ", g_string, "Да", "Нет");
				
				return 1;
			}
			
			if (!GetPVarInt(playerid, "Furn:SelectByCMD"))
			{
				ShowFurnMenu(playerid, ITEM_LIST_CURRENT, D_FURN);
			}
		}
		
		case D_FURN + 2 :
		{
			if (!IsPlayerRenovation(playerid))
			{
				return 1;
			}
			
			new furn_index = GetPVarInt(playerid, "Furn:Select");
			
			if (response)
			{
				Remove:furn_data(GetFurnId(furn_index));
				Remove:furn(furn_index);
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Объект мебели был успешно удален.");
				
				UpdateRenovationInfo(playerid);
				
				if (!GetPVarInt(playerid, "Furn:SelectByCMD"))
				{
					ShowFurnMenu(playerid, ITEM_LIST_CURRENT, D_FURN);
				}
			}
			else 
			{
				ShowFurnItemMenu(playerid, furn_index);
			}
		}
		
		case D_FURN + 3 :
		{
			if (!IsPlayerRenovation(playerid))
			{
				return 1;
			}
				
			if (!response)
			{
				ShowFurnMenu(playerid, ITEM_LIST_CURRENT, D_FURN);
				return 1;
			}
			
			ShowFurnList(playerid, true, listitem);
		}
		
		case D_FURN + 4 :
		{
			if (!IsPlayerRenovation(playerid))
			{
				return 1;
			}
			
			if (!response)
			{
				DeletePVar(playerid, "FurnList:BuyIndex");  
				return 1;
			}
			
			new rindex = GetRenovationIndex(playerid),
				rtype = GetRenovationType(playerid);
				
			if (GetFurnCount(rindex, rtype) >= GetFurnMaxCount(rindex, rtype))
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Превышен лимит на мебель.");
				return 1;
			}
			
			new furn_list_index;
			if ((furn_list_index = GetPVarInt(playerid, "FurnList:BuyIndex")) == 0)
			{
				return 1;
			}
			
			new cost = furniture_cat_list[furniture_list[furn_list_index][fitem_cat]][fcat_cost];
			
			SetPVarInt(playerid, "FurnList:BuyListIndex", furn_list_index);
			MakePayment(playerid, cost, "buy_furniture");
		}
	}
	
	return 1;
}

function PAY:buy_furniture(playerid, status)
{
	if (!IsPlayerRenovation(playerid))
	{
		return 1;
	}
			
	new furn_list_index = GetPVarInt(playerid, "FurnList:BuyListIndex");
		
	if (!status)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
		return 1;
	}

	Create:furn_data(
		GetRenovationId(playerid), 
		GetRenovationIndex(playerid),
		GetRenovationType(playerid), 
		furn_list_index,
		playerid
	);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно приобрели мебель.");
	
	DeletePVar(playerid, "FurnList:BuyIndex"); 
	DeletePVar(playerid, "FurnList:BuyListIndex");  
	return 1;
}