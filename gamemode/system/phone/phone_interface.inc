/*!
	@brief Интерфейс системы телефона
	@author Found (evg.savosin)
	@date 16.12.2016, update 04.02.2018
*/

ShowPhoneCursor(playerid, bool: states, forbid_cancel_select = false)
{
	SetPVarInt(playerid, "Phone:HideCursor", forbid_cancel_select);
	
	if (states)
	{
		SelectTextDraw(playerid, 0x3d597fFF);
	}
	else
	{
		CancelSelectTextDraw(playerid);
	}
}

ShowPhoneTextDraw(playerid, bool: states, page = PH_PAGE_INVALID, 
index = INVALID_PARAM, bool: cancel_select = true, target_index = INVALID_PARAM, bool: save_pvar = false)
{	
	new i;
	
	TD_SetPhoneBreadcrumb(playerid, false);
	
	if (states)
	{	
		SetPVarInt(playerid, "Phone:Select", index);
		
		TD_SetPhonePanel(playerid, true, phone_data[index][ph_col_panel]);
		
		/// Включен
		if (phone_data[index][ph_status])
		{	
			while (i < sizeof td_phone_static)
			{	
				if (i != 2)
				{
					TextDrawShowForPlayer(playerid, td_phone_static[i]);
				}
				
				i++;
			}
			
			TextDrawShowForPlayer(playerid, td_phone_head_time);
			
			UpdatePhone(playerid, page, index, target_index);
		}
		else 
		{
			while (i < sizeof td_phone_static)
			{
				switch(i)
				{
					case 3 .. 7, 13 .. 15 :
					{
						TextDrawShowForPlayer(playerid, td_phone_static[i]);
					}
				}
				
				i++;
			}
			
			TextDrawShowForPlayer(playerid, td_phone_offline);
		}
		
		format:g_small_string("Достал%s телефон", EndWordSex(playerid));
		SendRPMessage(ACTION_AME, playerid, g_small_string);
		
		if (!IsPlayerInAnyVehicle(playerid))
		{
			ApplyAnimationEx(playerid, "CASINO", "cards_loop", 4.1, 0, 1, 1, 1, 0, 1);
		}
		else 
		{
			ApplyAnimationEx(playerid, "CAR_CHAT", "carfone_loopA", 4.1, 1, 1, 1, 1, 0);
		}
		
		SetPlayerAttachedObject(
			playerid, 
			SLOT_ATTACH_PHONE, 
			18874, 
			6, 
			0.107999, 
			0.015000, 
			-0.016000, 
			97.100006, 
			-165.800048, 
			-3.000013 
		);
		
		format:g_small_string("" #DEFAULT " %s телефон " #cPROJECT "/pmenu" #cWHITE ", для выхода используйте " #cPROJECT "ESC" #cWHITE ".",
			phone_data[index][ph_status] ? ("Выключить") : ("Включить")
		);
		
		SendClientMessage(playerid, C_WHITE, g_small_string);
	
		ShowPhoneCursor(playerid, true);
	}
	else 
	{	
		/// Сбрасываем трубку
		if (index != INVALID_PARAM)
		{
			PhoneDecline(playerid, index, true);
		}
		
		/// Скрываем все статичные элементы и элементы декстопа
		while (i < sizeof td_phone_static)
		{
			if (i < sizeof td_phone_panel)
			{
				TextDrawHideForPlayer(playerid, td_phone_panel[i]);
			}
			
			TextDrawHideForPlayer(playerid, td_phone_static[i]);
			i++;
		}
		
		TextDrawHideForPlayer(playerid, td_phone_offline);
		TextDrawHideForPlayer(playerid, td_phone_head_time);
		
		/// Page: Desktop
		ShowPhonePageDesktop(playerid, false);
		
		/// Page: Item List
		ShowPhonePageConversation(playerid, false);
		
		/// Page: Call 
		ShowPhonePageCall(playerid, false);
		
		/// Page: Call Action
		ShowPhonePageCallAction(playerid, false);
		
		/// Other
		
		format:g_small_string("Убрал%s телефон", EndWordSex(playerid));
		SendRPMessage(ACTION_AME, playerid, g_small_string);
		
		ClearAnimationsEx(playerid);
		RemovePlayerAttachedObject(playerid, SLOT_ATTACH_PHONE);
		
		if (cancel_select)
		{
			CancelSelectTextDraw(playerid);
		}
		
		if (!save_pvar)
		{
			Clear:phone_pvar(playerid);
		}
	}
	
	SetPVarInt(playerid, "Phone:States", states);
	return true;
}

UpdatePhone(playerid, page, index, target_index = INVALID_PARAM)
{
	if (page == PH_PAGE_INVALID)
	{
		return;
	}
	
	new oldpage = GetPVarInt(playerid, "Phone:Page");
	
	/// Скрываем предыдущую страницу
	if (oldpage != PH_PAGE_INVALID)
	{
		if (oldpage == PH_PAGE_DESKTOP)
		{
			TD_SetPhoneBreadcrumb(playerid, false);
			ShowPhonePageDesktop(playerid, false);
		}
		else if (oldpage == PH_PAGE_CONTACTS) /// Контакты
		{
			ShowPhonePageContacts(playerid, false);
		}
		else if (oldpage == PH_PAGE_CALL) /// Ввод номера
		{
			ShowPhonePageCall(playerid, false);
		}
		else if (oldpage == PH_PAGE_INCOMING_CALL
		|| oldpage == PH_PAGE_OUTGOING_CALL) /// Входящий, исходящий
		{
			ShowPhonePageCallAction(playerid, false);
		}
		
		else if (oldpage == PH_PAGE_SMS)
		{
			ShowPhonePageConversation(playerid, false);
		}
	}
	
	/// Показываем новую
	if (page == PH_PAGE_DESKTOP)
	{
		ShowPhonePageDesktop(playerid, true);
	}
	else if (page == PH_PAGE_CONTACTS) /// Контакты
	{
		ShowPhonePageContacts(playerid, true, index);
	}
	else if (page == PH_PAGE_CALL) /// Ввод номера
	{
		ShowPhonePageCall(playerid, true);
	}
	else if (page == PH_PAGE_INCOMING_CALL) /// Входящий
	{
		ShowPhonePageCallAction(playerid, true, PH_INCOMING_CALL, index, target_index);
	}
	else if (page == PH_PAGE_OUTGOING_CALL) /// Исходящий
	{
		ShowPhonePageCallAction(playerid, true, PH_OUTGOING_CALL, index, target_index);
	}
	else if (page == PH_PAGE_SMS)
	{
		ShowPhonePageConversation(playerid, true, index);
	}
	
	SetPVarInt(playerid, "Phone:Page", page); 
}

ShowPhonePageDesktop(playerid, bool: states)
{
	new i;
	
	if (states)
	{
		while (i < sizeof td_phone_desktop)
		{
			if (i < TD_PHONE_DESKTOP_ARRAY)
			{
				PlayerTextDrawShow(playerid, ptd_phone_desktop[playerid][i]);
			}
			
			TextDrawShowForPlayer(playerid, td_phone_desktop[i]);
			i++;
		}
	}
	else 
	{
		while (i < sizeof td_phone_desktop)
		{
			if (i < TD_PHONE_DESKTOP_ARRAY)
			{
				PlayerTextDrawHide(playerid, ptd_phone_desktop[playerid][i]);
			}
				
			TextDrawHideForPlayer(playerid, td_phone_desktop[i]);
			i++;
		}
	}
}

ShowPhonePageConversation(playerid, bool: states, index = INVALID_PARAM)
{
	TD_SetPhoneBreadcrumb(playerid, states, "Conversations", true);
	
	if (states)
	{	
		PlayerTextDrawShow(playerid, ptd_phone_item_list[playerid][PH_ITEM_BUTTON]);
		PlayerTextDrawSetString(playerid, ptd_phone_item_list[playerid][PH_ITEM_BUTTON], "Action");
		
		UpdatePhonePageConversation(playerid, 0, index);
	}
	else 
	{
		TextDrawHideForPlayer(playerid, td_phone_item_list[0]); // up
		TextDrawHideForPlayer(playerid, td_phone_item_list[1]); // down
		
		for (new i = PH_ITEM_NAME_BEGIN; i <= PH_ITEM_NAME_END; i++)
		{
			PlayerTextDrawHide(playerid, ptd_phone_item_list[playerid][i]);
			TextDrawHideForPlayer(playerid, td_phone_item_list[i + PH_ITEM_AVA_BEGIN]);
		}
		
		PlayerTextDrawHide(playerid, ptd_phone_item_list[playerid][PH_ITEM_BUTTON]);
		
		DeletePVar(playerid, "Phone:ItemListPage");
	}
}

UpdatePhonePageConversation(playerid, page, index)
{
	if (page < 0)
	{
		return;
	}
	
	if (page > 0)
	{
		TextDrawShowForPlayer(playerid, td_phone_item_list[0]); // up
	}
	else 
	{
		TextDrawHideForPlayer(playerid, td_phone_item_list[0]);
	}
	
	/// Скрываем
	for (new i = PH_ITEM_NAME_BEGIN; i <= PH_ITEM_NAME_END; i++)
	{	
		PlayerTextDrawHide(playerid, ptd_phone_item_list[playerid][i]);
		TextDrawHideForPlayer(playerid, td_phone_item_list[i + PH_ITEM_AVA_BEGIN]);
	}
	
	SetPVarInt(playerid, "Phone:ItemListPage", page);
	
	page *= MAX_PHONE_ITEM_LIST;
	
	format:g_string("SELECT pc_id, pc_to_number FROM \ 
		" #__CONVERSATIONS " \
		WHERE pc_from_number = %i \
		ORDER BY pc_updated_time DESC \
		LIMIT %i, %i",
		GetPhoneNumber(index),
		page,
		MAX_PHONE_ITEM_LIST
	);
	
	mysql_pquery(db, g_string, "OnConversationListShow", "ii", playerid, index);
}

function OnConversationListShow(playerid, index)
{	
	new rows,
		number,
		name		[	MAX_PLAYER_NAME + 1];
	
	cache_get_row_count(rows);
	
	TextDrawHideForPlayer(playerid, td_phone_item_list[1]);
	
	if (rows == 0)
	{
		return 1; 
	}
	else if (rows == MAX_PHONE_ITEM_LIST)
	{
		TextDrawShowForPlayer(playerid, td_phone_item_list[1]); // down
	}
	
	for (new i = PH_ITEM_NAME_BEGIN; i <= PH_ITEM_NAME_END; i++)
	{
		if (i >= rows)
		{
			break;
		}
		
		cache_get_value_name_int(i, "pc_to_number", number);
		
		GetItemListNameOfContact(index, number, name);
		
		PlayerTextDrawShow(playerid, ptd_phone_item_list[playerid][i]);
		PlayerTextDrawSetString(playerid, ptd_phone_item_list[playerid][i], name);
		
		TextDrawShowForPlayer(playerid, td_phone_item_list[i + PH_ITEM_AVA_BEGIN]);
		
		g_td_select[playerid][i] = number;
	}
		
	return 1;
}

ShowPhonePageContacts(playerid, bool: states, index = INVALID_PARAM)
{
	TD_SetPhoneBreadcrumb(playerid, states, "Contacts", true);
	
	if (states)
	{	
		PlayerTextDrawShow(playerid, ptd_phone_item_list[playerid][PH_ITEM_BUTTON]);
		PlayerTextDrawSetString(playerid, ptd_phone_item_list[playerid][PH_ITEM_BUTTON], "Add contact");
		
		UpdatePhonePageContacts(playerid, 0, index);
	}
	else 
	{
		TextDrawHideForPlayer(playerid, td_phone_item_list[0]); // up
		TextDrawHideForPlayer(playerid, td_phone_item_list[1]); // down
		
		for (new i = PH_ITEM_NAME_BEGIN; i <= PH_ITEM_NAME_END; i++)
		{
			PlayerTextDrawHide(playerid, ptd_phone_item_list[playerid][i]);
			TextDrawHideForPlayer(playerid, td_phone_item_list[i + PH_ITEM_AVA_BEGIN]);
		}
		
		PlayerTextDrawHide(playerid, ptd_phone_item_list[playerid][PH_ITEM_BUTTON]);
		
		DeletePVar(playerid, "Phone:ItemPage");
	}
}

UpdatePhonePageContacts(playerid, page, phone_index)
{
	if (!(0 <= page <= (MAX_CONTACTS / MAX_PHONE_ITEM_LIST)))
	{
		return;
	}
	
	for (new i = PH_ITEM_NAME_BEGIN; i <= PH_ITEM_NAME_END; i++)
	{	
		PlayerTextDrawHide(playerid, ptd_phone_item_list[playerid][i]);
		TextDrawHideForPlayer(playerid, td_phone_item_list[i + PH_ITEM_AVA_BEGIN]);
	}
	

	TextDrawHideForPlayer(playerid, td_phone_item_list[1]);
	
	// Стрелка вверх
	if ((page * MAX_PHONE_ITEM_LIST) >= MAX_PHONE_ITEM_LIST)
	{
		TextDrawShowForPlayer(playerid, td_phone_item_list[0]); // up
	}
	else 
	{
		TextDrawHideForPlayer(playerid, td_phone_item_list[0]);
	}
	
	SetPVarInt(playerid, "Phone:ItemPage", page);
		
	for (new i, j, count = PH_ITEM_NAME_BEGIN; i < MAX_CONTACTS; i++)
	{	
		if (contact_data[phone_index][i][pc_number] == 0)
		{
			continue;
		}
		
		if (j != (page * MAX_PHONE_ITEM_LIST)) // После фильтряции определяем реальную страницу
		{
			j++;
			continue;
		}
		
		if (count == (PH_ITEM_NAME_END + 1))
		{
			TextDrawShowForPlayer(playerid, td_phone_item_list[1]);
			break;
		}
		
		PlayerTextDrawShow(playerid, ptd_phone_item_list[playerid][count]);
		PlayerTextDrawSetString(
			playerid, 
			ptd_phone_item_list[playerid][count], 
			contact_data[phone_index][i][pc_name]
		);
		
		TextDrawShowForPlayer(playerid, td_phone_item_list[count + PH_ITEM_AVA_BEGIN]);
		
		g_td_select[playerid][count] = i;
		
		count++;
	}
}

ShowPhonePageCall(playerid, bool: states)
{
	TD_SetPhoneBreadcrumb(playerid, states, "Call", true);
	
	if (states)
	{
		for (new i; i < sizeof td_phone_call; i++)
		{
			TextDrawShowForPlayer(playerid, td_phone_call[i]);
		}
		
		PlayerTextDrawShow(playerid, ptd_phone_call_input[playerid]);
	}
	else 
	{
		for (new i; i < sizeof td_phone_call; i++)
		{
			TextDrawHideForPlayer(playerid, td_phone_call[i]);
		}
		
		PlayerTextDrawHide(playerid, ptd_phone_call_input[playerid]);
	}
	
	PlayerTextDrawSetString(playerid, ptd_phone_call_input[playerid], "_");
	
	phone_call_number[playerid][0] = EOS;
}

ShowPhonePageCallAction(playerid, bool: states, type = INVALID_PARAM, index = INVALID_PARAM, target_index = INVALID_PARAM)
{
	TD_SetPhoneBreadcrumb(playerid, states, "Call");
	
	if (states)
	{
		new name		[	MAX_PLAYER_NAME		];
		
		PlayerTextDrawShow(playerid, ptd_phone_action_call[playerid][0]);
		PlayerTextDrawShow(playerid, ptd_phone_action_call[playerid][1]);
		
		PlayerTextDrawSetString(playerid, 
			ptd_phone_action_call[playerid][1],
			type == PH_INCOMING_CALL ? ("Incoming Call") : ("Outgoing Call")
		);
		
		GetItemListNameOfContact(index, GetPhoneNumber(target_index), name);
		
		PlayerTextDrawSetString(playerid, 
			ptd_phone_action_call[playerid][0],
			name
		);
		
		if (type != PH_OUTGOING_CALL)
		{
			TextDrawShowForPlayer(playerid, td_phone_action_call[0]); /// accept
		}
		
		TextDrawShowForPlayer(playerid, td_phone_action_call[1]); /// decline
		TextDrawShowForPlayer(playerid, td_phone_action_call[2]); /// avatar
	}
	else 
	{
		PlayerTextDrawHide(playerid, ptd_phone_action_call[playerid][0]);
		PlayerTextDrawHide(playerid, ptd_phone_action_call[playerid][1]);
		
		TextDrawHideForPlayer(playerid, td_phone_action_call[0]); /// accept
		TextDrawHideForPlayer(playerid, td_phone_action_call[1]); /// decline
		TextDrawHideForPlayer(playerid, td_phone_action_call[2]); /// avatar
	}
}
