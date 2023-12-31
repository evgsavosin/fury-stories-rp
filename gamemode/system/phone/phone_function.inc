/*!
	@brief ������� ��� ������� ���������
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.01.2018
*/

Clear:phone_pvar(playerid)
{
	DeletePVar(playerid, "Phone:Select");
	DeletePVar(playerid, "Phone:ContactSelect");
	DeletePVar(playerid, "Phone:Page");
	DeletePVar(playerid, "Phone:States");
	DeletePVar(playerid, "Phone:ConversationNumber");
	DeletePVar(playerid, "Phone:AddNumber");
	DeletePVar(playerid, "Phone:HideCursor");
}

Phone_OnGameModeInit()
{
	_Phone_OnGameModeInit();
	
	/// ������� ���������, ������� ��� ������ 2 �������
	format:g_string("DELETE FROM " #__MESSAGES " WHERE pm_created_time <= %i",
		gettime() - (60 * 60 * 24 * 60)
	); 
	
	mysql_tquery(db, g_string);
	
	/// ������� ���������� ������, ������� ������ ���� �������
	format:g_string("DELETE FROM " #__CONVERSATIONS " WHERE pc_updated_time <= %i",
		gettime() - (60 * 60 * 24 * 60 * 2)
	);
	
	mysql_tquery(db, g_string);
	
	TD_UpdatePhoneDate();
}

Phone_OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	
	_Phone_OnPlayerDisconnect(playerid, reason);
	
	/*!
		��������� �������� �� ����� ���������� ������
	*/
	
	if (IsPhoneShowed(playerid))
	{
		ShowPhoneTextDraw(playerid, false, PH_PAGE_INVALID, GetPhoneShowedIndex(playerid));
	}
	
	return 1;
}

Phone_OnPlayerDeath(playerid, killerid, reason)
{
	#pragma unused killerid
	#pragma unused reason
	
	/*!
		��������� �������� �� ����� ������ ���������
	*/
	
	if (IsPhoneShowed(playerid))
	{
		ShowPhoneTextDraw(playerid, false, PH_PAGE_INVALID, GetPhoneShowedIndex(playerid));
	}
}

Phone_OnPlayerClickMap(playerid, Float: fX, Float: fY, Float: fZ)
{
	_Phone_OnPlayerClickMap(playerid, Float: fX, Float: fY, Float: fZ);
	return 1;
}

function Phone_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_NO))
	{
		if (IsPhoneShowed(playerid))
		{
			ShowPhoneCursor(playerid, true, true);
			return 0;
		}
	}
	
	return 1;
}

Phone_OnPlayerClickPTD(playerid, PlayerText: playertextid)
{
	new page = GetPVarInt(playerid, "Phone:Page"),
		index = GetPVarInt(playerid, "Phone:Select"),
		server_tick = GetTickCount();
		
	if (!GetPVarInt(playerid, "Phone:States"))
	{
		return 1;
	}
	
	if (page == PH_PAGE_SMS)
	{
		/// Action
		if (playertextid == ptd_phone_item_list[playerid][PH_ITEM_BUTTON])
		{
			ShowPlayerDialog(playerid, D_PHONE + 3, DIALOG_STYLE_TABLIST, " ",
				" �������� ���������\t" #cGRAY "/sms\n \
				������� ��� ���������",
				"�����", "�������"
			);
			
			return 1;
		}
		
		if (GetPVarInt(playerid, "TimeOut:PhoneShowMessage") > server_tick)
		{
			SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
			return 1;
		}
		
		for (new i; i < MAX_PHONE_ITEM_LIST; i++)
		{
			if (playertextid != ptd_phone_item_list[playerid][i])
			{
				continue;
			}	
			
			ShowPhoneConversation(playerid, index, g_td_select[playerid][i]);
			
			SetPVarInt(playerid, "TimeOut:PhoneShowMessage", server_tick + 1500);
			break;
		}
	}
	else if (page == PH_PAGE_CONTACTS)
	{
		/// Add Contact
		if (playertextid == ptd_phone_item_list[playerid][PH_ITEM_BUTTON])
		{
			/*ShowPlayerDialog(playerid, D_PHONE + 5, DIALOG_STYLE_INPUT, " ",
				"" #DEFAULT " �������� ����� �������\n\n\
				������� ����� ��������:\n\n\
				" #cGRAY "����� ������ ���� � ������� XXXXXX ��� XXX.",
				"�����", "�������"
			);*/
			
			UpdatePhone(playerid, PH_PAGE_CALL, index);
			
			return 1;
		}
		
		for (new i; i < MAX_PHONE_ITEM_LIST; i++)
		{
			if (playertextid != ptd_phone_item_list[playerid][i])
			{
				continue;
			}	
			
			ShowPhoneContactMenu(playerid, g_td_select[playerid][i]);
			break;
		}
	}
	
	return 1;
}

Phone_OnPlayerClickTextDraw(playerid, Text: clickedid)
{
	new page = GetPVarInt(playerid, "Phone:Page"),
		index = GetPVarInt(playerid, "Phone:Select");
	
	if (!GetPVarInt(playerid, "Phone:States"))
	{
		return 1;
	}
	
	if (clickedid == INVALID_TEXT_DRAW)
	{
		if (GetPVarInt(playerid, "Phone:HideCursor"))
		{
			return 1;
		}
		
		ShowPhoneTextDraw(playerid, false, PH_PAGE_INVALID, GetPhoneShowedIndex(playerid));
		
		if (GetPVarInt(playerid, "Speedometer:Hide"))
		{
			ShowSpeedometer(playerid, true);
		}
		
		return 1;
	}
		
	else if (clickedid == td_phone_breadcrumb)
	{
		UpdatePhone(playerid, PH_PAGE_DESKTOP, index);
	}
	
	else if (clickedid == td_phone_desktop[4]) // Call
	{
		UpdatePhone(playerid, PH_PAGE_CALL, index);
	}
	
	else if (clickedid == td_phone_desktop[5]) // Sms
	{
		UpdatePhone(playerid, PH_PAGE_SMS, index);
	}
	
	else if (clickedid == td_phone_desktop[6]) // Web
	{
		ShowPhoneTextDraw(playerid, false, _, _, false);
		ShowBrowser(playerid, true);
	}
	
	else if (clickedid == td_phone_desktop[7]) // Apps
	{
		ShowPlayerDialog(playerid, D_PHONE + 12, DIALOG_STYLE_LIST, "Apps", DIALOG_PHONE_APPS, "�������", "�������");
	}
	
	else if (clickedid == td_phone_item_list[0]) /// Up
	{
		if (page == PH_PAGE_SMS)
		{
			UpdatePhonePageConversation(playerid, GetPVarInt(playerid, "Phone:ItemListPage") - 1, index);
		}
		else if (page == PH_PAGE_CONTACTS)
		{
			UpdatePhonePageContacts(playerid, GetPVarInt(playerid, "Phone:ItemPage") - 1, index);
		}
	}
	
	else if (clickedid == td_phone_item_list[1]) /// Down
	{
		if (page == PH_PAGE_SMS)
		{
			UpdatePhonePageConversation(playerid, GetPVarInt(playerid, "Phone:ItemListPage") + 1, index);
		}
		else if (page == PH_PAGE_CONTACTS)
		{
			UpdatePhonePageContacts(playerid, GetPVarInt(playerid, "Phone:ItemPage") + 1, index);
		}
	}
	
	else if (clickedid == td_phone_desktop[10]) /// Widget contacts
	{
		UpdatePhone(playerid, PH_PAGE_CONTACTS, index);
	}
	
	else if (clickedid == td_phone_call[13]) /// clear
	{
		phone_call_number[playerid][0] = EOS;
		PlayerTextDrawSetString(playerid, ptd_phone_call_input[playerid], "_");
	}
	
	else if (clickedid == td_phone_call[11]) /// Call
	{
		if (!PhoneCall(playerid, index, strval(phone_call_number[playerid])))
		{
			ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", DIALOG_PHONE_NUMBER, "�������", "");
			return 1;
		}
	}
	
	else if (clickedid == td_phone_call[12]) // Add contact
	{
		new number = strval(phone_call_number[playerid]),
			is_valid = IsValidPhoneNumber(number);
			
		if (isnull(phone_call_number[playerid])
		|| is_valid == NUMBER_TYPE_INCORRECTLY)
		{
			ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", DIALOG_PHONE_NUMBER, "�������", "");
			return 1;
		}
		
		if (IsContactExists(index, number))
		{
			ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", DIALOG_PHONE_NUMBER_EXISTS, "�������", "");
			return 1;
		}
		
		if (is_valid == NUMBER_TYPE_PHONE)
		{
			format:g_string(
				"SELECT COUNT(ph_id) AS phone_valid \
				FROM " #__PHONES " \
				WHERE ph_number = %i \
				LIMIT 1",
				number
			);
			
			mysql_pquery(db, g_string, "OnPhoneAddContact", "ii", playerid, number);
		}
		else if (is_valid == NUMBER_TYPE_SPECIAL)
		{
			SetPVarInt(playerid, !"Phone:AddNumber", number);
			
			ShowPlayerDialog(playerid, D_PHONE + 5, DIALOG_STYLE_INPUT, " ",
				"" #DEFAULT " �������� ����� �������\n\n\
				������� �������� ��������:\n\n\
				" #cGRAY "�������� ������ ���� �������� �� ��������� ������ � ������.",
				"�����", "�����"
			);
		}
		
	}
	
	else if (clickedid == td_phone_action_call[0]) /// Accept call
	{
		PhoneAccept(playerid, index);
	}
	
	else if (clickedid == td_phone_action_call[1]) /// Decline call
	{
		PhoneDecline(playerid, index);
	}
	
	if (strlen(phone_call_number[playerid]) < MAX_NUMBER_LENGTH)
	{
		for (new i = 1, temp[1]; i <= 10; i++)
		{
			if (clickedid == td_phone_call[i])
			{
				valstr(temp, (i - 1));
				strcat(phone_call_number[playerid], temp, MAX_NUMBER_LENGTH);
				PlayerTextDrawSetString(playerid, ptd_phone_call_input[playerid], phone_call_number[playerid]);
				break;
			}
		}
	}
	
	return 1;
}

Phone_OnPlayerEnterDynamicArea(playerid, areaid)
{
	_Phone_OnPlayerEnterDynamicArea(playerid, areaid);
	return 1;
}

Phone_OnPlayerStateChange(playerid, newstate, oldstate)
{
	_Phone_OnPlayerStateChange(playerid, newstate, oldstate);
	return 1;
}

Phone_OnPlayerEnterCheckpoint(playerid)
{
	_Phone_OnPlayerEnterCheckpoint(playerid);
	return 1;
}

// Functions 
PhoneCall(playerid, index, number)
{
	new is_valid = IsValidPhoneNumber(number);
			
	if (is_valid == NUMBER_TYPE_INCORRECTLY)
	{
		return 0;
	}
	
	if (is_valid == NUMBER_TYPE_SPECIAL) /// ����������� �����
	{
		if (number == EMERGENCY_NUMBER) /// ���� ��������� � ���������� ������
		{
			ShowPlayerDialog(playerid, D_PHONE + 16, DIALOG_STYLE_INPUT, " ",
				"" #DEFAULT " ������ 911\n\n\
				������� ������� ��������:",
				"�����", "�������"
			);
		}
		else if (number == NEWS_NUMBER) /// ��������� � ������
		{
			
		}
	}
	
	else if (is_valid == NUMBER_TYPE_PHONE 
	&& IsPhoneNumberExists(number)) /// ���� ��������� �� �������, ������� �� �������
	{
		if (call_data[playerid][c_player_id] != INVALID_PLAYER_ID)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " �� ��� ��������� � ���-�� �� ��������. ��� ������ ����������� \"Decline\" �� ����������.");
			return 1;
		}
		
		new target_index = GetPhoneIndexByNumber(number),
			targetid,
			name			[	MAX_PLAYER_NAME		];
		
		
		if (target_index != INVALID_PARAM 
		&& !phone_data[target_index][ph_status])
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " ������� �������� �������� ��� ��������� ��� ���� �������� ����.");
			return 1;
		}
		
		targetid = phone_data[target_index][ph_player_id];
		
		if (targetid == INVALID_PLAYER_ID)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " �� �� ������ ����������� �� ������� ������.");
			return 1;
		}
		
		if (call_data[targetid][c_player_id] != INVALID_PLAYER_ID)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " �� ������� �������� ��� ���������� ��������. ����������� �����.");
			return 1;
		}
		
		/// ��� ������
		call_data[playerid][c_player_id] = targetid;
		call_data[playerid][c_index] = index;
		
		/// ��������� ������
		phone_data[index][ph_call_index] = target_index;
		
		GetItemListNameOfContact(index, number, name);
		
		format:g_small_string("" #DEFAULT " �� ��������� " #cPROJECT "%s" #cWHITE ".",
			name
		);
		
		psend:(playerid, C_WHITE);
		
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " ��� ����, ����� ��������, ������� " #cPROJECT "N" #cWHITE " � �������� \"Decline\".");
		
		if (IsPhoneShowed(playerid))
		{
			UpdatePhone(playerid, PH_PAGE_OUTGOING_CALL, index, target_index);
		}
		else
		{
			ShowPhoneTextDraw(playerid, true, PH_PAGE_OUTGOING_CALL, index, _, target_index);
		}
		
		ShowPhoneCursor(playerid, false, true);
		
		/// ���� ������
		call_data[targetid][c_player_id] = playerid;
		call_data[targetid][c_index] = target_index;
		
		/// �������� ������
		phone_data[target_index][ph_call_index] = index;
		
		GetItemListNameOfContact(target_index, GetPhoneNumber(index), name);
		
		if (IsPhoneShowed(targetid))
		{
			UpdatePhone(targetid, PH_PAGE_INCOMING_CALL, target_index, index);
		}
		else 
		{
			ShowPhoneTextDraw(targetid, true, PH_PAGE_INCOMING_CALL, target_index, _, index);
		}

		pformat:("" #DEFAULT " ��� �������� " #cPROJECT "%s" #cWHITE ". ��� ������ �������� ���������� ������� � ����������� \"Accept\" ��� \"Decline\".",
			name,
			target_index,
			GetPhoneNumber(target_index)
		);
		
		psend:(targetid, C_WHITE);
		
		PhonePlayMusic(targetid, phone_data[target_index][ph_music]);
		SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
	}
	else
	{
		return 0;
	}
	
	return 1;
}

PhoneAccept(playerid, index)
{
	new targetid = call_data[playerid][c_player_id],
		target_index = phone_data[index][ph_call_index];
		
	if (target_index == INVALID_PARAM)
	{
		return 0;
	}
	
	/// �������� ������ ������
	TextDrawHideForPlayer(playerid, td_phone_action_call[0]);
	
	DeletePVar(playerid, "Phone:CallTime");
	DeletePVar(targetid, "Phone:CallTime");
	
	phone_data[index][ph_call_timer] = SetTimerEx(
		"OnPhoneCallAction", 
		1200, 
		true,
		"i", 
		playerid 
	);
	
	phone_data[target_index][ph_call_timer] = SetTimerEx(
		"OnPhoneCallAction", 
		1200, 
		true, 
		"i", 
		targetid 
	);
	
	ShowPhoneCursor(playerid, false, true);
	
	PhonePlayMusic(playerid, 0);
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
	
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " �� �������� ����������� ��������. ��� ��������� ����������� ������� " #cPROJECT "/c" #cWHITE ".");
	SendClientMessage(targetid, C_WHITE, !#SUCCESS " ������� ������� �� ��� �����. ��� ��������� ����������� ������� " #cPROJECT "/c" #cWHITE ".");
	return 1;
}

PhoneDecline(playerid, index, bool: is_disconnect = false)
{
	new str_time		[			16			],
		name			[	MAX_PLAYER_NAME		],
		targetid = call_data[playerid][c_player_id],
		target_index = phone_data[index][ph_call_index],
		minutes,
		seconds;
		
	if (target_index == INVALID_PARAM)
	{
		return 0;
	}
		
	if (phone_data[index][ph_call_timer] != INVALID_PARAM) /// ���� ����������
	{
		SecondToMinute(GetPVarInt(playerid, "Phone:CallTime"), minutes, seconds);
		
		format:str_time("%02d:%02d", 
			minutes,
			seconds
		);
		
		GetItemListNameOfContact(target_index, GetPhoneNumber(index), name);
		pformat:("" #DEFAULT " ������� " #cPROJECT "%s" #cWHITE " ������� �����. ����� ���������: %s.",
			name,
			str_time
		);
		
		psend:(targetid, C_WHITE);
		
		if (!is_disconnect)
		{
			SecondToMinute(GetPVarInt(targetid, "Phone:CallTime"), minutes, seconds);
			
			format:str_time("%02d:%02d", 
				minutes,
				seconds
			);
		
			GetItemListNameOfContact(index, GetPhoneNumber(target_index), name);
			pformat:("" #DEFAULT " �� �������� ����� �������� " #cPROJECT "%s" #cWHITE ". ����� ���������: %s.",
				name,
				str_time
			);
			
			psend:(playerid, C_WHITE);
		}
	}
	else /// ����� ���
	{	
		GetItemListNameOfContact(target_index, GetPhoneNumber(index), name);
		
		pformat:("" #DEFAULT " ������� " #cPROJECT "%s" #cWHITE " ������� ��� �����.",
			name
		);

		psend:(targetid, C_WHITE);
		
		if (!is_disconnect)
		{
			GetItemListNameOfContact(index, GetPhoneNumber(target_index), name);
			pformat:("" #DEFAULT " �� �������� ����� �������� " #cPROJECT "%s" #cWHITE ".",
				name
			);
			
			psend:(playerid, C_WHITE);
		}
	}
	
	/// ��������� ��������� �������
	if (!is_disconnect)
	{
		ShowPhoneCursor(playerid, true, false);
		UpdatePhone(playerid, PH_PAGE_DESKTOP, index);
		PhonePlayMusic(playerid, 0);
	}
	
	ShowPhoneCursor(targetid, true, false);
	UpdatePhone(targetid, PH_PAGE_DESKTOP, index);
	PhonePlayMusic(targetid, 0);
	
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
	SetTimerEx("OnPhoneDelayApplyAnimation", 1500, false, "i", playerid);
	
	KillTimer(phone_data[index][ph_call_timer]);
	KillTimer(phone_data[target_index][ph_call_timer]);
	
	Clear:call_data(targetid);
	Clear:call_data(playerid);
	
	phone_data[index][ph_call_timer] = 
	phone_data[index][ph_call_index] =
	phone_data[target_index][ph_call_timer] =
	phone_data[target_index][ph_call_index] = INVALID_PARAM;
	
	DeletePVar(playerid, "Phone:CallTime");
	DeletePVar(targetid, "Phone:CallTime");
	return 1;
}

function OnPhoneDelayApplyAnimation(playerid)
{
	ApplyAnimationEx(playerid, "CASINO", "cards_loop", 4.1, 0, 1, 1, 1, 0);
	return 1;
}

function OnPhoneCallAction(playerid)
{
	new str_minutes		[	8	],
		minutes,
		seconds;
	
	GivePVarInt(playerid, "Phone:CallTime", 1);
	SecondToMinute(GetPVarInt(playerid, "Phone:CallTime"), minutes, seconds);
	
	if (minutes != 0)
	{
		format(str_minutes, sizeof str_minutes, "%im ", minutes);
	}
	
	format:g_small_string("%s%is", 
		str_minutes,
		seconds
	);
	
	PlayerTextDrawSetString(playerid, 
		ptd_phone_action_call[playerid][1],
		g_small_string
	);
	
	return 1;
}

function OnPhoneAddContact(playerid, number)
{
	new is_valid;
	
	cache_get_value_name_int(0, "phone_valid", is_valid);
	
	if (is_valid == 0)
	{
		ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", DIALOG_PHONE_NUMBER, "�������", "");
		return 1;
	}
	
	SetPVarInt(playerid, "Phone:AddNumber", number);
	
	ShowPlayerDialog(playerid, D_PHONE + 5, DIALOG_STYLE_INPUT, " ",
		"" #DEFAULT " �������� ����� �������\n\n\
		������� �������� ��������:\n\n\
		" #cGRAY "�������� ������ ���� �������� �� ��������� ������ � ������.",
		"�����", "�����"
	);
	
	return 1;
}

// Phone Functions
GetFreeIndexForPhone()
{
	for (new i; i < MAX_PHONES; i++)
	{
		if (GetPhoneId(i) != 0)
		{
			continue;
		}
		
		printf("[GetFreeIndexForPhone] = %d", i);
		return i; 
	}
	
	return INVALID_PARAM;
}

GetPhoneIndexBySlot(const id, index, type = TYPE_INV_PLAYER) // ���������� ������ � ������� (MAX_PHONES) � ������� �����
{
	new slot,
		is_phone;
		
	if (index == INVALID_PARAM)
	{
		return INVALID_PARAM;
	}
	
	if ((slot = GetInventoryEnumItem(id, index, type, inv_item_id)) == 0)
	{
		return INVALID_PARAM;
	}
	
	is_phone = item_list[GetItemIndexById(slot)][it_type] == INV_PHONE;	
	for (new i; i < MAX_PHONES; i++)
	{
		if (GetPhoneId(i) == 0)
		{
			continue;
		}
			
		if (!is_phone 
		|| GetInventoryEnumItem(id, index, type, inv_param_1) != GetPhoneId(i))
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

GetPhoneIndexById(const phone_id)
{
	if (phone_id == 0)
	{
		return INVALID_PARAM;
	}
	
	for (new i; i < MAX_PHONES; i++)
	{
		printf("%d != %d", phone_data[i][ph_id], phone_id);
		if (phone_data[i][ph_id] != phone_id)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

GetPhoneIndexByNumber(const number)
{
	for (new i; i < MAX_PHONES; i++)
	{
		if (phone_data[i][ph_number] != number)
		{
			continue;
		}
		
		return i;
	}
	
	return INVALID_PARAM;
}

IsPhoneNumberExists(const number)
{
	for (new i; i < MAX_PHONES; i++)
	{
		if (phone_data[i][ph_number] != number)
		{
			continue;
		}
		
		return 1;
	}
	
	return 0;
}

IsContactExists(phone_index, const number)
{
	for (new i; i < MAX_CONTACTS; i++)
	{
		if (contact_data[phone_index][i][pc_number] != number)
		{
			continue;
		}
		
		return 1;
	}
	
	return 0;
}

IsValidPhoneNumber(const number)
{
	if ((100_000 <= number <= 999_999))
	{
		return NUMBER_TYPE_PHONE;
	}
	else if (number == EMERGENCY_NUMBER 
	|| number == NEWS_NUMBER)
	{
		return NUMBER_TYPE_SPECIAL;
	}
	
	return NUMBER_TYPE_INCORRECTLY;
}

IsValidPhoneContactName(const text[], min, max)
{
	new len = strlen(text);
		
	if (!(min <= len <= max))
	{
		return 0;
	}
	
	while (len-- != 0)
	{
		switch(text[len])
		{	
			case '�' .. '�', '�' .. '�', '/', '\n', '`', '~', '%', '^', '&', '[', ']', '{', '}', '|', ''' :
			{
				return 0;
			}
		}
	}
	
	return 1;
}


/// Contacts functions
GetItemListNameOfContact(id, const number, name[], len = sizeof(name))
{
	name[0] = EOS;
	
	if (number == NUMBER_OVH)
	{
		strcat(name, "OVH Telecom", len);
		return;
	}
	
	for (new i; i < MAX_CONTACTS; i++)
	{
		if (contact_data[id][i][pc_number] == number 
		&& !isnull(contact_data[id][i][pc_name]))
		{
			strcat(name, contact_data[id][i][pc_name], len);
			
			return;
		}
	}
	
	valstr(name, number);
	
	return;
}

/// Other functions
Create:contact(playerid, index, const number, name[])
{
	clean:<g_string>;
	
	format:g_string("\
		INSERT INTO " #__CONTACTS " \
		VALUES (%i, %i, '%q', %i)",
		GetPhoneId(index),
		number, 
		name,
		gettime()
	);
	
	mysql_pquery(db, g_string);
	
	for (new i; i < MAX_CONTACTS; i++)
	{
		if (contact_data[index][i][pc_number] != 0)
		{
			continue;
		}
		
		contact_data[index][i][pc_number] = number;
		
		contact_data[index][i][pc_name][0] = EOS;
		strcat(contact_data[index][i][pc_name], name, MAX_PLAYER_NAME);
		
		contact_data[index][i][pc_created_time] = gettime();
		
		pformat:("" #SUCCESS " �� ������� �������� " #cPROJECT "%s (%i)" #cWHITE " � �������� ��������.",
			contact_data[index][i][pc_name],
			contact_data[index][i][pc_number]
		);
		psend:(playerid, C_WHITE);
		break;
	}
	
	return 1;
}

Create:message(playerid, to_number, const text[120], from_number = INVALID_PARAM)
{	
	clean:<g_big_string>;
	clean:<g_string>;
	
	new name			[	MAX_PLAYER_NAME		],
		index,
		to_index = GetPhoneIndexByNumber(to_number),
		targetid;

	if (playerid != INVALID_PLAYER_ID)
	{
		index = GetInventoryDefaultPhone(playerid);
		from_number = GetPhoneNumber(index);
		
		/// For mysql query
		format:g_string("(%i, %i, %i, %i),", 
			to_number,
			from_number,
			gettime(),
			gettime()
		);
	}

	format:g_big_string("\
		INSERT INTO " #__CONVERSATIONS " \
			(pc_from_number, pc_to_number, pc_created_time, pc_updated_time) \
		VALUES \
		%s \
		(%i, %i, %i, %i) \ 
		ON DUPLICATE KEY UPDATE \
			pc_from_number = VALUES(pc_from_number), \
			pc_to_number = VALUES(pc_to_number), \
			pc_updated_time = VALUES(pc_updated_time)",
		g_string,
		
		from_number,
		to_number,
		gettime(),
		gettime()
	);
	
	mysql_pquery(db, g_big_string);
	
	clean:<g_string>;
	if (playerid != INVALID_PLAYER_ID)
	{
		/// For mysql query
		format:g_string("(%i, %i, '%q', %i, %i),", 
			from_number,
			to_number,
			text,
			gettime(),
			TYPE_PH_OUTGOING
		);
		
		GetItemListNameOfContact(
			index, 
			to_number, 
			name	
		);
		
		format:g_small_string("" #SMS_MESSAGE " � %s: %s", 
			name,
			text
		);
		
		SendSplitMessage(playerid, C_DARKYELLOW, g_small_string);
	}
	
	format:g_big_string("INSERT INTO " #__MESSAGES " \
	(pm_from_number, pm_to_number, pm_text, pm_created_time, pm_type) \
	VALUES \
	%s (%i, %i, '%q', %i, %i)",
		g_string,
		
		from_number,
		to_number,
		text,
		gettime(),
		TYPE_PH_INCOMING
	);
	
	mysql_tquery(db, g_big_string);
	
	if (to_index != INVALID_PARAM 
	&& (targetid = phone_data[to_index][ph_player_id]) != INVALID_PLAYER_ID)
	{
		PlayerPlaySound(targetid, 17006, 0.0, 0.0, 0.0);

		GetItemListNameOfContact(
			(playerid == INVALID_PLAYER_ID) ? to_index : index, 
			from_number, 
			name	
		);
	
		format:g_small_string("" #SMS_MESSAGE " �� %s: %s", 
			name,
			text
		);
		
		SendSplitMessage(targetid, C_DARKYELLOW, g_small_string);
		
		SendRPMessage(ACTION_AME, targetid, "��������� �������");
	}
}

PhonePlayMusic(playerid, const music_id)
{
	if (!(0 <= music_id < sizeof phone_music))
	{
		return;
	}
	
	PlayerPlaySound(playerid, phone_music[music_id][pm_id], 0.0, 0.0, 0.0);
}

// Show phone 
ShowPhone(playerid, index)
{	
	new pindex = GetPhoneIndexBySlot(playerid, index, TYPE_INV_PLAYER);

	if (pindex == INVALID_PARAM)
	{
		printf("[ERROR]: In ShowPhone index is invalid param. (Slot: %i)", index);
		return;
	}
	
	if (GetPVarInt(playerid, "Speedometer:States"))
	{
		ShowSpeedometer(playerid, false);
		SetPVarInt(playerid, "Speedometer:Hide", true);
	}

	ShowPhoneTextDraw(playerid, true, PH_PAGE_DESKTOP, pindex);
}
