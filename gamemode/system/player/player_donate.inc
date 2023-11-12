/*!
	@brief Донат
	@author Found (evg.savosin)
	@date 26.04.2017
*/

ShowPlayerDonate(playerid)
{
	if (!IsUserAllowQuery(playerid))
	{
		return;
	}
	
	format:g_string("\
		SELECT d.*, di.title \
		FROM " #__DONATE " AS d \
		JOIN " #__DONATE_ITEM " AS di \
			ON di.id = d.donate_item_id \
		WHERE d.user_id = %d",
		GetUserId(playerid)
	);
	
	mysql_tquery(db, g_string, "OnPlayerDonateShow", "i", playerid);
	
	SetUserAllowQuery(playerid, false);
}

ShowPlayerDonateObjects(playerid)
{
	if (!IsUserVip(playerid))
	{
		return 0;
	}
	
	clean:<g_big_string>;
	
	for (new i; i < sizeof donate_objects; i++)
	{
		format:g_big_string("%s %s\n", 
			g_big_string,
			donate_objects[i][d_name]
		);
		
		g_dialog_select[playerid][i] = donate_objects[i][d_object_id];
	}

	ShowPlayerDialog(playerid, D_DONATE + 10, DIALOG_STYLE_LIST, " ", g_big_string, "Далее", "Закрыть");
	return 1;
}

function OnPlayerDonateShow(playerid)
{
	SetUserAllowQuery(playerid, true);
	
	clean:<g_big_string>;
	
	new rows,
		count;
	
	cache_get_row_count(rows);
	
	if (!rows)
	{
		ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ",
			"" #DEFAULT " Донат\n\n\
			У Вас отсутствуют донат-привилегии, которые можно активировать.\n\
			Пополнение счёта и покупка привилегий происходит в личном кабинете - " #cPROJECT "fs-rp.ru" #cWHITE ".",
			"Закрыть", ""
		);
		
		return 1;
	}
	
	new item_id;
	
	for (new i; i < rows; i++)
	{
		clean:<g_small_string>;
		cache_get_value_name(i, "title", g_small_string, sizeof g_small_string);
		cache_get_value_name_int(i, "donate_item_id", item_id);
		
		format:g_big_string("%s %s\n",
			g_big_string,
			g_small_string
		);
		
		g_dialog_select[playerid][count++] = item_id;
	}
	
	ShowPlayerDialog(playerid, D_DONATE, DIALOG_STYLE_LIST, " ", g_big_string, "Выбрать", "Закрыть");
	return 1;
}

ActivatePlayerDonate(playerid, item_id)
{
	SetPVarInt(playerid, "Donate:ActivateItem", item_id);
	
	switch (item_id)
	{
		case DONATE_CHANGE_CHARACTER_NAME:
		{
			ShowPlayerDialog(playerid, D_DONATE + 1, DIALOG_STYLE_INPUT, " ",
				"" #DEFAULT " Смена имени персонажа\n\n\
				Данная привилегия позволяет изменить имя и фамилию персонажа.\n\
				Введите новое имя:\n\n\
				" #cGRAY "Имя и фамилия должны состоять только из латинских букв с разделителем '_'.\n\
				Имя и фамилия должны начинаться с заглавных букв.\n\
				Максимальная длина ник-нейма - 24 символа.\n\
				Имя и фамилия персонажа не должно нарушать правила сервера.",
			"Далее", "Назад");
		}
		
		case DONATE_UNWARN:
		{
			if (GetUserWarn(playerid) != 0)
			{
				format:g_string("" #DEFAULT " Снять предупреждение\n\n\
					Данная привилегия позволяет снять одно предупреждение с Вашего аккаунта.\n\
					У Вас предупреждений: " #cPROJECT "%d" #cWHITE ".\n\n\
					Вы действительно хотите снять предупреждение?",
					GetUserWarn(playerid)
				);
				
				ShowPlayerDialog(playerid, D_DONATE + 3, DIALOG_STYLE_MSGBOX, " ", g_string, "Далее", "Назад");
			}
			else
			{
				ShowPlayerDonate(playerid);
				SendClientMessage(playerid, C_WHITE, #ERROR " На Вашем аккаунте отсутствуют предупреждения.");
			}
		}
		
		case DONATE_CHANGE_VEHICLE_NUMBER:
		{
			ShowVehicleList(playerid, D_DONATE + 4);
		}
		
		case DONATE_CHANGE_PHONE_NUMBER:
		{
			new index = GetInventoryTypeItemExists(playerid, TYPE_INV_PLAYER, INV_PHONE, _, true);
	
			if (index == INVALID_PARAM)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас отсутствует по умолчанию телефон. Выбрать его можно в инвентаре.");
				return 0;
			}
			
			new pindex = GetPhoneIndexBySlot(playerid, index, TYPE_INV_PLAYER);

			if (pindex == INVALID_PARAM)
			{
				printf("[ERROR]: In ShowPhone index is invalid param. (Slot: %i)", index);
				return 0;
			}
			
			SetPVarInt(playerid, "Phone:Select", pindex);
			
			ShowPlayerDialog(playerid, D_DONATE + 8, DIALOG_STYLE_INPUT, " ",
				"" #DEFAULT " Смена номера телефона\n\n\
				Данная привилегия позволяет изменить номер телефона.\n\
				Введите новый номер:\n\n\
				" #cGRAY "Минимальная длина номер - 4, максимальная - 6.",
			"Далее", "Назад");
		}
		
		
		case DONATE_WEAPON_CASE:
		{
			new bool: exists = false,
				max_count;
			
			if (GetInventoryTypeItemCount(playerid, INV_WEAPON_BIG, false) >= (max_count = GetInventoryMaxTypeItems(INV_WEAPON_BIG, false)))
			{
				exists = true;
			}
			
			if (exists)
			{
				pformat:(#ERROR " Освободите место в инвентаре, максимальное количество крупногабаритного оружия: " #cPROJECT "%d" #cWHITE ".",
					max_count
				);
				
				psend:(playerid, C_WHITE);
				ShowPlayerDonate(playerid);
				return 1;
			}
			
			if (GetInventoryTypeItemCount(playerid, INV_WEAPON_SMALL, false) >= GetInventoryMaxTypeItems(INV_WEAPON_SMALL, false))
			{
				exists = true;
			}
			
			if (exists)
			{
				pformat:(#ERROR " Освободите место в инвентаре, максимальное количество малогабаритного оружия: " #cPROJECT "%d" #cWHITE ".",
					max_count
				);
				
				psend:(playerid, C_WHITE);
				ShowPlayerDonate(playerid);
				return 1;
			}
			
			Remove:donate_item(playerid, item_id, "OnDonateWeaponCase");
		}
		
		case DONATE_ARMY_CASE:
		{
			new bool: exists = false,
				max_count;
			
			if (GetInventoryTypeItemCount(playerid, INV_WEAPON_BIG, false) >= (max_count = GetInventoryMaxTypeItems(INV_WEAPON_BIG, false)))
			{
				exists = true;
			}
			
			if (exists)
			{
				pformat:(#ERROR " Освободите место в инвентаре, максимальное количество крупногабаритного оружия: " #cPROJECT "%d" #cWHITE ".",
					max_count
				);
				
				psend:(playerid, C_WHITE);
				return 1;
			}
			
			if (GetInventoryTypeItemCount(playerid, INV_WEAPON_SMALL, false) >= GetInventoryMaxTypeItems(INV_WEAPON_SMALL, false))
			{
				exists = true;
			}
			
			if (exists)
			{
				pformat:(#ERROR " Освободите место в инвентаре, максимальное количество малогабаритного оружия: " #cPROJECT "%d" #cWHITE ".");
				psend:(playerid, C_WHITE);
				return 1;
			}
	
			Remove:donate_item(playerid, item_id, "OnDonateArmyCase");
		}
		
		case DONATE_PACK_1 .. DONATE_PACK_3:
		{
			if (character_data[playerid][c_start_pack_buy_time] > 0)
			{
				SendClientMessage(playerid, C_WHITE, #ERROR " На данном персонаже уже применён пакет со стартовым пакетом.");
				ShowPlayerDonate(playerid);
				return 1;
			}
			
			Remove:donate_item(playerid, item_id, "OnDonatePack");
		}
		
		
		case DONATE_VIP_STARTER .. DONATE_VIP_PRO:
		{
			Remove:donate_item(playerid, item_id, "OnDonateVip");
		}
	}

	return 1;
}

Donate_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	new item_id = GetPVarInt(playerid, "Donate:ActivateItem");
	
	switch (dialogid)
	{
		case D_DONATE:
		{
			if (!response)
			{
				return 1;
			}
			
			item_id = g_dialog_select[playerid][listitem];
			ActivatePlayerDonate(playerid, item_id);
		}
		
		case D_DONATE + 1:
		{
			if (!response)
			{
				ShowPlayerDonate(playerid);
				return 1;
			}
			
			if (!IsValidName(inputtext))
			{
				ShowPlayerDialog(playerid, D_DONATE + 1, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Смена имени персонажа\n\n\
					Данная привилегия позволяет изменить имя и фамилию персонажа\n\
					Введите новое имя:\n\n\
					" #cRED "Имя и фамилия должны состоять только из латинских букв с разделителем '_'.\n\
					Имя и фамилия должны начинаться с заглавных букв.\n\
					Максимальная длина ник-нейма - 24 символа.\n\
					Имя и фамилия персонажа не должно нарушать правила сервера.",
				"Далее", "Назад");
				return 1;
			}
			
			SetPVarString(playerid, "Donate:NewName", inputtext);
			
			format:g_string("" #DEFAULT " Смена имени персонажа\n\n\
				Новое имя: " #cPROJECT "%s" #cWHITE "\n\
				Старое имя: " #cPROJECT "%s" #cWHITE "\n\n\
				Вы подтверждаете смену имени персонажа?",
				inputtext,
				GetCharacterName(playerid)
			);
			
			ShowPlayerDialog(playerid, D_DONATE + 2, DIALOG_STYLE_MSGBOX, " ",
				g_string,
				"Да", "Нет"
			);
		}
		
		case D_DONATE + 2:
		{
			if (!response)
			{
				ActivatePlayerDonate(playerid, item_id);
				return 1;
			}
			
			Remove:donate_item(playerid, item_id, "OnDonateChangeCharacterName");
		}
		
		case D_DONATE + 3:
		{
			if (!response)
			{
				ShowPlayerDonate(playerid);
				return 1;
			}
			
			Remove:donate_item(playerid, item_id, "OnDonateUnwarn");
		}
		
		case D_DONATE + 4:
		{
			if (!response)
			{
				ShowPlayerDonate(playerid);
				return 1;
			}
			
			new index = g_dialog_select[playerid][listitem],
				vehicleid = player_vehicle[playerid][pv_server_id][index];
			
			if (!IsOwnerVehicle(playerid, vehicleid))
			{
				return 1;
			}
			
			if (vehicleid != 0)
			{
				SetPVarInt(playerid, "Vehicle:Select", vehicleid);
				
				ShowPlayerDialog(playerid, D_DONATE + 6, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Смена номера транспорта\n\n\
					Данная привилегия позволяет изменить номер транспорта.\n\n\
					Введите новый номер транспорта:\n\n\
					" #cGRAY "Номер должен состоять только из латинских букв и цифр, с возможным разделителем '-'.\n\
					Максимальная длина номерного знака - 8, минимальная - 4.",
				"Далее", "Назад");
			}
			else 
			{
				ShowPlayerDialog(playerid, D_DONATE + 5, DIALOG_STYLE_MSGBOX, " ", 
					"" #DEFAULT " Информация\n\n\
					Внимание! Данный транспорт не вызван на сервере.",
					"Назад", ""
				);
			}
		}
		
		case D_DONATE + 5:
		{
			ShowVehicleList(playerid, D_DONATE + 4);
		}
		
		case D_DONATE + 6:
		{
			if (!response)
			{
				ShowVehicleList(playerid, D_DONATE + 4);
				return 1;
			}
			
			if (!IsValidVehicleNumber(inputtext))
			{
				ShowPlayerDialog(playerid, D_DONATE + 6, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Смена номера транспорта\n\n\
					Данная привилегия позволяет изменить номер транспорта.\n\n\
					Введите новый номер транспорта:\n\n\
					" #cRED "Номер должен состоять только из латинских букв и цифр, с возможным разделителем '-'.\n\
					Максимальная длина номерного знака - 8, минимальная - 4.",
				"Далее", "Назад");
				return 1;
			}
			
			format:g_string("SELECT COUNT(v_id) AS is_exists FROM " #__VEHICLES " WHERE v_number = '%q'",
				inputtext
			);
			
			mysql_tquery(db, g_string, "OnDonateVehicleCheck", "ds", playerid, inputtext);
		}
		
		case D_DONATE + 7:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_DONATE + 6, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Смена номера транспорта\n\n\
					Данная привилегия позволяет изменить номер транспорта.\n\n\
					Введите новый номер транспорта:\n\n\
					" #cGRAY "Номер должен состоять только из латинских букв и цифр, с возможным разделителем '-'.\n\
					Максимальная длина номерного знака - 8, минимальная - 4.",
				"Далее", "Назад");
				
				return 1;
			}
			
			new vehicleid = GetPVarInt(playerid, "Vehicle:Select");
			
			if (!IsOwnerVehicle(playerid, vehicleid))
			{
				return 1;
			}
	
			Remove:donate_item(playerid, item_id, "OnDonateChangeVehicleNumber");
		}
		
		case D_DONATE + 8:
		{
			if (!response)
			{
				ShowPlayerDonate(playerid);
				return 1;
			}
			
			new number = strval(inputtext),
				len = strlen(inputtext);
			
			if (!(4 <= len <= 6) || !IsInt(inputtext))
			{
				ShowPlayerDialog(playerid, D_DONATE + 8, DIALOG_STYLE_INPUT, " ",
				"" #DEFAULT " Смена номера телефона\n\n\
					Данная привилегия позволяет изменить номер телефона.\n\
					Введите новый номер:\n\
					" #cRED "Минимальная длина номер - 4, максимальная - 6.",
				"Далее", "Назад");
				return 1;
			}
			
			format:g_string("SELECT COUNT(ph_id) AS is_exists FROM " #__PHONES " WHERE ph_number = %d",
				number
			);
			
			mysql_tquery(db, g_string, "OnDonatePhoneCheck", "dd", playerid, number);
		}
		
		case D_DONATE + 9:
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_DONATE + 8, DIALOG_STYLE_INPUT, " ",
				"" #DEFAULT " Смена номера телефона\n\n\
					Данная привилегия позволяет изменить номер телефона.\n\
					Введите новый номер:\n\
					" #cGRAY "Минимальная длина номер - 4, максимальная - 6.",
				"Далее", "Назад");
				return 1;
			}
			
			Remove:donate_item(playerid, item_id, "OnDonateChangePhoneNumber");
		}
		
		case D_DONATE + 10:
		{
			if (!response)
			{
				return 1;
			}
			
			new object_id = g_dialog_select[playerid][listitem];
			
			new Float: x,
				Float: y,
				Float: z,
				Float: angle;
			
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			
			x += 1.0 * floatsin(-angle, degrees);
			y += 1.0 * floatcos(-angle, degrees);
			
			SetPVarInt(playerid, "Donate:EditObject", true);
			
			donate_object[playerid][d_object_id] = CreateDynamicObject(
				object_id,
				x,
				y,
				z,
				0.0,
				0.0,
				0.0,
				_,
				_,
				_,
				100,
				100
			);
			
			EditDynamicObject(playerid, donate_object[playerid][d_object_id]);
		}
	}
	
	return 1;
}

function Donate_OnPlayerEditDO(playerid, objectid, response, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz)
{
	if (!GetPVarInt(playerid, "Donate:EditObject"))
	{
		return 1;
	}
	
	if (response == EDIT_RESPONSE_CANCEL)
	{
		DestroyDynamicObject(objectid);
		donate_object[playerid][d_object_id] = INVALID_OBJECT_ID;
	}
	else if (response == EDIT_RESPONSE_FINAL)
	{
		format:g_small_string("(( %s[%i] ))",
			GetPlayerCurrentName(playerid),
			playerid
		);
				
		donate_object[playerid][d_text_id] = CreateDynamic3DTextLabel(
			g_small_string, 
			C_WHITE, 
			x,
			y,
			z,
			1.5, 
			_, 
			_,
			_
		);
		
		SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы успешно поставили объект. Для удаления используйте " #cPROJECT "/vobject" #cWHITE " повторно.");
	}
	
	DeletePVar(playerid, "Donate:EditObject");

	return 1;
}

function OnDonateVehicleCheck(playerid, number[])
{
	new is_exists;
	
	cache_get_value_name_int(0, "is_exists", is_exists);
	
	if (is_exists != 0)
	{
		ShowPlayerDialog(playerid, D_DONATE + 6, DIALOG_STYLE_INPUT, " ",
			"" #DEFAULT " Смена номера транспорта\n\n\
			Данная привилегия позволяет изменить номер транспорта.\n\n\
			Введите новый номер транспорта:\n\n\
			" #cRED "Номер должен состоять только из латинских букв и цифр, с возможным разделителем '-'.\n\
			Максимальная длина номерного знака - 8, минимальная - 4.\n\
			Данный номер уже зарегистрирован.",
		"Далее", "Назад");
				
		return 1;
	}
	
	new vehicleid = GetPVarInt(playerid, "Vehicle:Select");
	
	SetPVarString(playerid, "Donate:NewVehicleNumber", number);
			
	format:g_string("" #DEFAULT " Смена номера транспорта\n\n\
		Новый номер: " #cPROJECT "%s" #cWHITE "\n\
		Старый номер: " #cPROJECT "%s" #cWHITE "\n\n\
		Вы подтверждаете смену номера?:\n\n",
		number,
		vehicle_data[vehicleid][v_number],
		GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name)
	);
	
	ShowPlayerDialog(playerid, D_DONATE + 7, DIALOG_STYLE_MSGBOX, " ", g_string, "Да", "Нет");
	return 1;
}

function OnDonatePhoneCheck(playerid, number)
{
	new is_exists;
	
	cache_get_value_name_int(0, "is_exists", is_exists);
	
	if (is_exists != 0)
	{
		ShowPlayerDialog(playerid, D_DONATE + 8, DIALOG_STYLE_INPUT, " ",
		"" #DEFAULT " Смена номера телефона\n\n\
			Данная привилегия позволяет изменить номер телефона.\n\
			Введите новый номер:\n\
			" #cRED "Данный номер уже занят.",
		"Далее", "Назад");
		return 1;
	}
	
	new index = GetPVarInt(playerid, "Phone:Select");
			
	SetPVarInt(playerid, "Donate:NewPhoneNumber", number);
	
	format:g_string("" #DEFAULT " Смена номера телефона\n\n\
		Новый номер: " #cPROJECT "%d" #cWHITE "\n\
		Старый номер: " #cPROJECT "%d" #cWHITE "\n\n\
		Вы подтверждаете смену номера?:\n\n",
		number,
		GetPhoneNumber(index)
	);
	
	ShowPlayerDialog(playerid, D_DONATE + 9, DIALOG_STYLE_MSGBOX, " ", g_string, "Да", "Нет");
			
	return 1;
}

function OnDonateChangeCharacterName(playerid, item_id)
{
	if (!cache_affected_rows())
	{
		return 1;
	}
	
	clean:<g_string>;
	GetPVarString(playerid, "Donate:NewName", g_string, sizeof g_string);
	
	pformat:(#SUCCESS " Вы успешно сменили имя персонажа с " #cPROJECT "%s" #cWHITE " на " #cPROJECT "%s" #cWHITE ".",
		character_data[playerid][c_name],
		g_string
	);
	psend:(playerid, C_WHITE);
	
	clean:<character_data[playerid][c_name]>;
	strcat(character_data[playerid][c_name], g_string, MAX_PLAYER_NAME);
	Update:character_string(playerid, "c_name", character_data[playerid][c_name]);
	
	new name			[MAX_PLAYER_NAME];
	
	// Without underscore
	GetWithoutUnderscore(character_data[playerid][c_name], name); /// Get name with out '_'
	
	clean:<character_data[playerid][c_rpname]>;
	strcat(character_data[playerid][c_rpname], name, MAX_PLAYER_NAME);
	ReplacePlayerName(playerid, TYPE_IC); /// Replace
	
	ShowPlayerDonate(playerid);
	
	DeletePVar(playerid, "Donate:NewName");
	return 1;
}

function OnDonateUnwarn(playerid, item_id)
{
	if (!cache_affected_rows())
	{
		return 1;
	}
	
	user_data[playerid][u_warn]--;
	if (user_data[playerid][u_warn] < 0)
	{
		user_data[playerid][u_warn] = 0;
	}
	
	Update:user_int(playerid, "u_warn", user_data[playerid][u_warn]);
	
	pformat:(#SUCCESS " Вы успешно сняли " #cPROJECT "1" #cWHITE " предупреждение. Осталось: " #cPROJECT "%d" #cWHITE "/",
		user_data[playerid][u_warn]
	);
	
	psend:(playerid, C_WHITE);
	
	ShowPlayerDonate(playerid);
	return 1;
}

function OnDonateChangeVehicleNumber(playerid, item_id)
{
	if (!cache_affected_rows())
	{
		return 1;
	}
	
	new vehicleid = GetPVarInt(playerid, "Vehicle:Select");
	
	clean:<g_small_string>;
	GetPVarString(playerid, "Donate:NewVehicleNumber", g_small_string, sizeof g_small_string);
	
	clean:<vehicle_data[vehicleid][v_number]>;
	strcat(vehicle_data[vehicleid][v_number], g_small_string, 32);
	SetVehicleNumberPlate(vehicleid, vehicle_data[vehicleid][v_number]);
	Update:vehicle_data(vehicleid, playerid);
	
	pformat:(#SUCCESS " Вы успешно изменили номер " #cPROJECT "%s" #cWHITE " для транспорта " #cPROJECT "%s" #cWHITE ".",
		vehicle_data[vehicleid][v_number],
		GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name)
	);
	psend:(playerid, C_WHITE);
	
	ShowPlayerDonate(playerid);

	DeletePVar(playerid, "Vehicle:Select");
	return 1;
}

function OnDonateChangePhoneNumber(playerid, item_id)
{
	if (!cache_affected_rows())
	{
		return 1;
	}
	
	new index = GetPVarInt(playerid, "Phone:Select"),
		number = GetPVarInt(playerid, "Donate:NewPhoneNumber");
	
	phone_data[index][ph_number] = number;
	Update:phone_data(playerid, index);
	
	pformat:(#SUCCESS " Вы успешно сменили номер телефона на " #cPROJECT "%d" #cWHITE ".",
		phone_data[index][ph_number]
	);
	
	psend:(playerid, C_WHITE);
	
	ShowPlayerDonate(playerid);

	DeletePVar(playerid, "Phone:Select");
	return 1;
}

function OnDonateWeaponCase(playerid, item_id)
{
	if (!cache_affected_rows())
	{
		return 1;
	}
	
	switch (random(10)) 
	{
		case 1 .. 8:
		{
			new rand = random(sizeof donate_weapon_case),
				ammo,
				param;
	
			if (donate_weapon_case[rand] == ITEM_ARMOUR)
			{
				ammo = 0;
				param = 100;
			}
			else if (donate_weapon_case[rand] == ITEM_KNIFE)
			{
				ammo = 0;
			}
			else 
			{
				ammo = (random(60 - 20) + 20);
			}
			
			GiveInventoryItem(playerid, donate_weapon_case[rand], ammo, param);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " В инвентарь был добавлен новый предмет.");
		}
		
		case 9:
		{
			new rand = random(200 - 100) + 100;
			
			format:g_string("UPDATE " #__USERS " SET u_donate = u_donate + %d WHERE u_id = %d",
				rand,
				GetUserId(playerid)
			);
			
			mysql_tquery(db, g_string);
			
			pformat:(#SUCCESS " Вам начислено " #cPROJECT "%d FPoint" #cWHITE " из кейса.");
			psend:(playerid, C_WHITE);
		}
	}
	
	return 1;
}

function OnDonateArmyCase(playerid, item_id)
{
	if (!cache_affected_rows())
	{
		return 1;
	}
	
	new rand = random(sizeof(donate_army_case)),
		ammo,
		param;
	
	if (donate_army_case[rand] == ITEM_KATANA || donate_army_case[rand] == ITEM_BRASSKNUCKLE)
	{
		ammo = 1;
	}
	else if (donate_army_case[rand] == ITEM_ARMOUR)
	{
		ammo = 0;
		param = 100;
	}
	else if (donate_army_case[rand] == ITEM_KNIFE)
	{
		ammo = 0;
	}
	else
	{
		ammo = (random(60 - 20) + 20) + 20;
	}

	GiveInventoryItem(playerid, donate_army_case[rand], ammo, param);
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " В инвентарь был добавлен новый предмет.");
	return 1;
}

function OnDonatePack(playerid, item_id)
{
	if (!cache_affected_rows())
	{
		return 1;
	}
	
	new min_value,
		max_value;
	
	if (item_id == DONATE_PACK_1)
	{
		min_value = 1500;
		max_value = 3000;
	}
	else if (item_id == DONATE_PACK_2)
	{
		min_value = 5000;
		max_value = 15000;
	}
	else if (item_id == DONATE_PACK_3)
	{
		min_value = 18000;
		max_value = 35000;
	}
	
	new rand = random(max_value - min_value) + min_value;
	character_data[playerid][c_start_capital] += rand;
	Update:character_int(playerid, "c_start_capital", character_data[playerid][c_start_capital]);
	Update:character_string(playerid, "c_start_pack_buy_date", "NOW()", false);
	
	pformat:(#SUCCESS " Вам начислен дополнительный стартовый капитал " #cGREEN "$%d" #cWHITE " из кейса.",
		rand
	);
	
	psend:(playerid, C_WHITE);
	return 1;
}

function OnDonateVip(playerid, item_id)
{
	if (!cache_affected_rows())
	{
		return 1;
	}
	
	new level;
		
	if (item_id == DONATE_VIP_STARTER)
	{
		level = VIP_STARTER;
	}
	else if (item_id == DONATE_VIP_DEFAULT)
	{
		level = VIP_DEFAULT;
		Create:donate_item(playerid, DONATE_CHANGE_CHARACTER_NAME);
	}
	else if (item_id == DONATE_VIP_ADVANCED)
	{
		level = VIP_ADVANCED;
		
		Create:donate_item(playerid, DONATE_CHANGE_CHARACTER_NAME);
		Create:donate_item(playerid, DONATE_CHANGE_PHONE_NUMBER);
	}
	else if (item_id == DONATE_VIP_PRO)
	{
		level = VIP_PRO;
		
		Create:donate_item(playerid, DONATE_CHANGE_CHARACTER_NAME);
		Create:donate_item(playerid, DONATE_CHANGE_PHONE_NUMBER);
		Create:donate_item(playerid, DONATE_CHANGE_VEHICLE_NUMBER);
	}
	
	user_data[playerid][u_vip] = level;
	user_data[playerid][u_vip_time] = gettime();
	
	Update:user_int(playerid, "u_vip", level);
	Update:user_string(playerid, "u_vip_date", "NOW()", false);
	
	if (item_id != DONATE_VIP_PRO)
	{
		pformat:(#SUCCESS " VIP аккаунт " #cPROJECT "%d" #cWHITE " уровня успешно активирован на 30 дней.",
			level
		);
	}
	else 
	{
		pformat:(#SUCCESS " VIP аккаунт " #cPROJECT "%d" #cWHITE " уровня успешно активирован навсегда.",
			level
		);
	}
	
	psend:(playerid, C_WHITE);
	return 1;
}