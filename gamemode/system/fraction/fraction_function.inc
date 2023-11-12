/*!
	@brief Функции для системы фракций
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

// Public function
Fraction_OnGameModeInit()
{
	// Загрузка фракций
	Load:fraction_data();
	
	// Создаем 3D Тексты
	Create:fraction_duty_text();
	Create:fraction_stock_text();
	Create:fraction_garage_text();
	Create:fprison_text();
	
	// Очистка объектов
	Clear:fraction_object_all();
	
	// Создание объектов
	Create:fprison_door_all();
}

Fraction_OnPlayerDisconnect(playerid)
{
	ResetPlayerHale(playerid);
	
	for (new i; i < MAX_FRACTION_CALLS; i++)
	{
		if (fraction_call[i][c_player_id] != INVALID_PLAYER_ID
		&& playerid == fraction_call[i][c_player_id])
		{
			fraction_call[i][c_player_id] = INVALID_PLAYER_ID;
			break;
		}
	}
}

Fraction_OnPlayerSpawn(playerid)
{
	ResetPlayerHale(playerid);
}

Fraction_OnPlayerDeath(playerid)
{
	ResetPlayerHale(playerid);
}

function Fraction_OnPlayerKeyStateC(playerid, newkeys, oldkeys)
{	
	// Открытие дверей и шлагбаумов
	if (PRESSED(KEY_SECONDARY_ATTACK) 
	|| (PRESSED(KEY_CROUCH) 
	&& IsPlayerInAnyVehicle(playerid) 
	&& GetPlayerState(playerid) == PLAYER_STATE_DRIVER))
	{
		if (!IsFractionMember(playerid))
		{
			return 1;
		}
	
		new findex = GetFractionMember(playerid);
		
		for (new i; i < MAX_FRACTION_DOORS; i++)
		{
			if (IsPlayerInRangeOfPoint(playerid, 
			fraction_door[findex][i][fr_radius], 
			fraction_door[findex][i][fr_begin_pos][0], 
			fraction_door[findex][i][fr_begin_pos][1], 
			fraction_door[findex][i][fr_begin_pos][2])) 
			{
				SetFractionStateDoor(findex, i);
				return 0;
			}
		}
	}
	
	// Выход на дежурство (раздевалка)
	if (PRESSED(KEY_CTRL_BACK) && IsFractionMember(playerid))
	{	
		new id = GetFractionMemberId(playerid);
		
		for (new i; i < sizeof fraction_duty; i++)
		{
			if (IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, 
			fraction_duty[i][fr_pos][0], 
			fraction_duty[i][fr_pos][1], 
			fraction_duty[i][fr_pos][2]) && fraction_duty[i][fr_fraction_id] == id)
			{
				ShowFractionMemberDuty(playerid);
				return 0;
			}
		}
	}
	
	// Склад
	if (PRESSED(KEY_CTRL_BACK) && IsFractionMember(playerid))
	{	
		new findex = GetFractionMember(playerid),
			id = GetFractionIdByIndex(findex);
			
		for (new i; i < sizeof fraction_stock; i++)
		{
			if (IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, 
			fraction_stock[i][fr_pos][0], 
			fraction_stock[i][fr_pos][1], 
			fraction_stock[i][fr_pos][2]) && fraction_duty[i][fr_fraction_id] == id)
			{
				if (!CheckFractionDuty(playerid))
				{
					SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
					return 1;
				}
				
				ShowFractionItemList(playerid, D_FRACTION + 50, findex);
				return 0;
			}
		}
	}
	
	// Телепортация в гаражи
	new vehicleid = GetPlayerVehicleID(playerid),
		player_state = GetPlayerState(playerid);
		
	if (vehicleid != 0)
	{
		if (PRESSED(KEY_FIRE) && player_state == PLAYER_STATE_DRIVER) // Vehicle
		{
			for (new i; i < sizeof fraction_garage; i++)
			{
				if (GetCharacterWorld(playerid) == 0
				&& IsPlayerInRangeOfPoint(playerid, 
					10.0, 
					fraction_garage[i][fr_begin_pos][0], 
					fraction_garage[i][fr_begin_pos][1], 
					fraction_garage[i][fr_begin_pos][2])) 
				{
					Move:vehicle(vehicleid, 
						fraction_garage[i][fr_end_pos][0], 
						fraction_garage[i][fr_end_pos][1], 
						fraction_garage[i][fr_end_pos][2],
						fraction_garage[i][fr_world],
						fraction_garage[i][fr_int],
						true,
						fraction_garage[i][fr_end_pos][3]
					);
					
					return 0;
				}
				else if (GetCharacterWorld(playerid) == fraction_garage[i][fr_world]
				&& IsPlayerInRangeOfPoint(playerid, 
					10.0, 
					fraction_garage[i][fr_end_pos][0], 
					fraction_garage[i][fr_end_pos][1], 
					fraction_garage[i][fr_end_pos][2])) 
				{
					Move:vehicle(vehicleid, 
						fraction_garage[i][fr_begin_pos][0], 
						fraction_garage[i][fr_begin_pos][1], 
						fraction_garage[i][fr_begin_pos][2],
						0,
						0,
						true,
						fraction_garage[i][fr_begin_pos][3]
					);
					
					return 0;
				}
			}
		}
	}
	else
	{
		if (PRESSED(KEY_CTRL_BACK)) // PED
		{
			for (new i; i < sizeof fraction_garage; i++)
			{
				if (GetCharacterWorld(playerid) == 0
				&& IsPlayerInRangeOfPoint(playerid, 
					FACTOR_TELEPORT_RADIUS, 
					fraction_garage[i][fr_door_begin_pos][0], 
					fraction_garage[i][fr_door_begin_pos][1], 
					fraction_garage[i][fr_door_begin_pos][2])) 
				{
					Move:player(playerid, 
						fraction_garage[i][fr_door_end_pos][0], 
						fraction_garage[i][fr_door_end_pos][1], 
						fraction_garage[i][fr_door_end_pos][2],
						fraction_garage[i][fr_world],
						fraction_garage[i][fr_int],
						true,
						fraction_garage[i][fr_door_end_pos][3]
					);
					
					return 0;
				}
				else if (GetCharacterWorld(playerid) == fraction_garage[i][fr_world]
				&& IsPlayerInRangeOfPoint(playerid, 
					FACTOR_TELEPORT_RADIUS, 
					fraction_garage[i][fr_door_end_pos][0], 
					fraction_garage[i][fr_door_end_pos][1], 
					fraction_garage[i][fr_door_end_pos][2])) 
				{
					Move:player(playerid, 
						fraction_garage[i][fr_door_begin_pos][0], 
						fraction_garage[i][fr_door_begin_pos][1], 
						fraction_garage[i][fr_door_begin_pos][2],
						0,
						0,
						true,
						fraction_garage[i][fr_door_begin_pos][3]
					);
					
					return 0;
				}
			}
		}
	}
	
	// Тазер
	if (PRESSED(KEY_ANALOG_RIGHT))
	{
		if (!IsFractionMember(playerid))
		{
			return 1;
		}
		
		cmd_taser(playerid);
		return 0;
	}
	
	// Открытие в тюрьме двери
	if (vehicleid != 0)
	{
		if (PRESSED(KEY_FIRE)) // Vehicle
		{
			if (!IsFractionMember(playerid, FRACTION_SD))
			{
				return 1;
			}
			
			for (new i; i < MAX_FRACTION_PRISON_DOORS; i++)
			{
				if (IsPlayerInRangeOfPoint(playerid, 
					15.0, 
					fprison_door[i][0][fr_begin_pos][0],
					fprison_door[i][0][fr_begin_pos][1],
					fprison_door[i][0][fr_begin_pos][2]))
				{
					SetFractionPrisonStateDoor(i);
					return 0;
				}
			}
		}
	}
	else
	{
		if (PRESSED(KEY_SECONDARY_ATTACK))
		{
			if (!IsFractionMember(playerid, FRACTION_SD))
			{
				return 1;
			}
			
			for (new i; i < MAX_FRACTION_PRISON_DOORS; i++)
			{
				if (IsPlayerInRangeOfPoint(playerid, 
					3.0, 
					fprison_door[i][0][fr_begin_pos][0],
					fprison_door[i][0][fr_begin_pos][1],
					fprison_door[i][0][fr_begin_pos][2]))
				{
					SetFractionPrisonStateDoor(i);
					return 0;
				}
			}
		}
	}
	
	// Меню управления в тюрьме
	if (PRESSED(KEY_CTRL_BACK))
	{
		if (IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, PRISON_MENU_POS))
		{
			if (!IsFractionMember(playerid, FRACTION_SD))
			{
				return 1;
			}
			
			ShowPrisonMenu(playerid);
			return 0;
		}
	}
	
	return 1;
}

function Fraction_OnPlayerEditDO(playerid, objectid, response, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz)
{
	if (!IsFractionMember(playerid))
	{
		return 1;
	}
	
	// Редактирование объекта (/object)
	if (GetPVarInt(playerid, "Fraction:ObjectMode"))
	{
		new index = GetPVarInt(playerid, "Fraction:ObjectIndex"),
			findex = GetFractionMember(playerid);
				
		if (response == EDIT_RESPONSE_UPDATE)
		{
			new Float: distance = GetPlayerDistanceFromPoint(playerid, x, y, z);
				
			if (distance > MAX_FRACTION_OBJECT_EDIT_DIST)
			{
				Destroy:fraction_object(findex, index);
				
				CancelEdit( playerid );
			}
		}
		else if (response == EDIT_RESPONSE_FINAL)
		{	
			if (!IsValidDynamicObject(objectid))
			{
				return 1;
			}
				
			format:g_small_string( "[%d]", 
				index + 1
			);
			
			fraction_object[findex][index][fr_text_id] = CreateDynamic3DTextLabel(
				g_small_string,
				C_DARKGRAY, 
				x, 
				y, 
				z + 0.5, 
				3.0 
			);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно разместили объект. " #cGRAY "(/dobject - для удаления)");
		
			DeletePVar(playerid, "Fraction:ObjectMode");
			DeletePVar(playerid, "Fraction:ObjectIndex");
		}
		else if (response == EDIT_RESPONSE_CANCEL)
		{
			Destroy:fraction_object(findex, index);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы отменили размещение объекта.");
			
			DeletePVar(playerid, "Fraction:ObjectMode");
			DeletePVar(playerid, "Fraction:ObjectIndex");
		}
	}
	
	return 1;
}

function Fraction_OnPlayerSDO(playerid, objectid, modelid, Float: x, Float: y, Float: z)
{
	if (!IsFractionMember(playerid))
	{
		return 1;
	}
	
	if (GetPVarInt(playerid, "Fraction:ObjectSelect"))
	{		
		new findex = GetFractionMember(playerid);
		
		for (new i; i < MAX_FRACTION_OBJECTS; i++) 
		{
			if (fraction_object[findex][i][fr_object_id] == objectid)
			{
				Destroy:fraction_object(findex, i);
				CancelEdit(playerid);
				
				pformat:(#SUCCESS " Вы успешно удалили объект с ID: " #cPROJECT "%d" #cWHITE ".", 
					i + 1
				);
				
				psend:(playerid, C_WHITE);
				
				DeletePVar(playerid, "Fraction:ObjectSelect");
				break;
			}
		}
	}
	
	return 1;
}

Fraction_OnPlayerEditAO(playerid, response, index, modelid, boneid, Float: fOffsetX, Float: fOffsetY, Float: fOffsetZ, Float: fRotX, Float: fRotY, Float: fRotZ, Float: fScaleX, Float: fScaleY, Float: fScaleZ)
{
	if (GetPVarInt(playerid, "Fraction:AttachMode"))
	{
		if( response )
		{
			SetPlayerAttachedObject(playerid, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно прикрепили объект к персонажу.");
		}
		else 
		{
			RemovePlayerAttachedObject(playerid, index);
			SendClientMessage(playerid, C_WHITE, !#ERROR" Вы отменили прикрепление объекта к персонажу.");
		}
		
		DeletePVar(playerid, "Fraction:AttachMode");
	}
}	

function Fraction_OnPlayerEnterVehicle(playerid, vehicleid)
{
	if (strobelight_time_out[vehicleid])
	{
		KillTimer(strobelight_time_out[vehicleid]);
		strobelight_time_out[vehicleid] = INVALID_PARAM;
	}
}

function Fraction_OnVehicleDeath(vehicleid, killerid)
{
	if (strobelight_timer[vehicleid])
	{
		KillTimer(strobelight_timer[vehicleid]);
		strobelight_timer[vehicleid] = INVALID_PARAM;
	}
	
	if (strobelight_time_out[vehicleid])
	{
		KillTimer(strobelight_time_out[vehicleid]);
		strobelight_time_out[vehicleid] = INVALID_PARAM;
	}
}

function Fraction_OnPlayerExitVehicle(playerid, vehicleid)
{
	if (strobelight_time_out[vehicleid])
	{
		strobelight_time_out[vehicleid] = SetTimerEx("OnFractionVehicleStrobeTimeout", 900000, false, "d", vehicleid);
	}
}

Fraction_OnPlayerClickTD(playerid, Text: clickedid)
{	
	if (!GetPVarInt(playerid, "Fraction:SkinStates"))
	{
		return 1;
	}
	
	if (clickedid == INVALID_TEXT_DRAW)
	{
		ShowFractionSkinList(playerid, false);
	}
	else if (clickedid == td_select_menu[1]) // next
	{
		UpdateFractionSkinList(playerid, GetPVarInt(playerid, "Fraction:SkinPage") + TD_SELECT_MENU_ARRAY);
	}
	else if (clickedid == td_select_menu[2]) // last 
	{
		UpdateFractionSkinList(playerid, GetPVarInt(playerid, "Fraction:SkinPage") - TD_SELECT_MENU_ARRAY);
	}
	
	return 1;
}

Fraction_OnPlayerClickPTD(playerid, PlayerText: playertextid)
{
	if (!GetPVarInt(playerid, "Fraction:SkinStates"))
	{
		return 1;
	}
	
	for (new i; i < TD_SELECT_MENU_ARRAY; i++)
	{
		if (playertextid == ptd_select_menu[playerid][i])
		{
			FractionMemberDuty(playerid, true, g_td_select[playerid][i]);
			ShowFractionSkinList(playerid, false);
			break;
		}
	}
	
	return 1;
}

// Function
GetFreeIndexForFraction()
{
	for (new i; i < sizeof fraction_data; i++)
	{
		if (fraction_data[i][fr_id] == 0)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}

GetFractionIndexById(fraction_id)
{
	for (new i; i < sizeof fraction_data; i++)
	{
		if (fraction_data[i][fr_id] == fraction_id)
		{
			return i;
		}
	}
	
	return 0;
}

GetFractionIdByIndex(index)
{
	if (!(0 <= index < MAX_FRACTIONS))
	{
		return 0;
	}
	
	for (new i; i < sizeof fraction_data; i++)
	{
		if (fraction_data[i][fr_id] == fraction_data[index][fr_id])
		{
			return fraction_data[index][fr_id];
		}
	}
	
	return 0;
}

GetFractionMinSalary(index)
{
	return floatround(MIN_FRACTION_SALARY * fraction_data[index][fr_budget]);
}

GetFractionMaxSalary(index)
{
	return floatround(MAX_FRACTION_SALARY * fraction_data[index][fr_budget]);
}

IsFractionMember(playerid, fraction_id = FRACTION_NONE)
{
	new member_id = GetFractionMemberId(playerid);
	
	if (member_id == 0)
	{
		return 0;
	}
	
	if (fraction_id != FRACTION_NONE && fraction_id != member_id)
	{
		return 0;
	}
	
	return 1;
}

CheckFractionAccess(playerid, E_FRACTION_RANK_DATA: perm = E_FRACTION_RANK_DATA: INVALID_PARAM, custom_perm = INVALID_PARAM, bool: only_leader = true)
{
	new index = GetFractionMember(playerid);

	if (index == INVALID_PARAM)
	{
		return 0;
	}
	
	if (only_leader && GetFractionLeader(playerid) != INVALID_PARAM)
	{
		return 1;
	}
	
	new rank = GetFractionMemberRank(playerid);
	
	// Проверяем основной доступ
	if (perm != E_FRACTION_RANK_DATA: INVALID_PARAM)
	{
		if (rank == INVALID_PARAM)
		{	
			return 0;
		}
		
		if (!GetFractionRankPerm(index, rank, perm))
		{
			return 0;
		}
	}
	
	// Проверяем вторичный доступ
	if (custom_perm != INVALID_PARAM)
	{
		if (rank == INVALID_PARAM)
		{
			return 0;
		}
		
		if (!GetFractionRankPermCustom(index, rank, custom_perm))
		{
			return 0;
		}
	}
	
	return 1;
}

// Получаем бюджет в формате:
// $1.64 млрд. или $10 млн.
GetFractionBudgetFormat(Float: budget, text[MAX_FRACTION_BUDGET])
{
	format:text("%0.3f", budget);
	
	new billions,
		millions;
	
	printf("text: %s", text);
	
	sscanf(text, "p<.>dd", billions, millions);
	
	clean:<text>;
	
	printf("%d, %d", billions, millions);
	
	if (billions > 0)
	{
		format:text("$%d", billions);
		
		if (millions > 0)
		{
			format:text("%s.%d", text, millions);
		}
		
		strcat(text, " млрд.", sizeof text);
	}
	else if (millions > 0)
	{
		format:text("$%d млн.", millions);
	}
}

InvitePlayerToFraction(playerid, targetid, bool: is_dialog)
{
	if (!IsFractionMember(playerid) || !CheckFractionAccess(playerid, fr_perm_invite))
	{
		return 0;
	}
	
	new index = GetFractionMember(playerid);
	
	pformat:(#SUCCESS " Вы отправили приглашение " #cPROJECT "%s" #cWHITE ".",
		GetPlayerCurrentName(targetid)
	);
	
	psend:(playerid, C_WHITE);
	
	// Если пункт был выбран из диалога
	if (is_dialog)
	{
		ShowFractionStaff(playerid);
	}
	
	SetPVarInt(targetid, "Fraction:InviteMemberId", playerid);
	SetPVarInt(targetid, "Fraction:InviteMemberFractionIndex", index);
	
	format:g_string("" #DEFAULT " Приглашение\n\n\
		Приглашение от " #cPROJECT "%s" #cWHITE ".\n\
		Вас приглашают стать сотрудником организации " #cPROJECT "%s" #cWHITE ".\n\
		Вы принимаете приглашение?",
		GetPlayerCurrentName(playerid),
		GetFractionName(index)
	);
	
	ShowPlayerDialog(targetid, D_FRACTION + 4, DIALOG_STYLE_MSGBOX, " ", g_string, "Да", "Нет");
	return 1;
}

UninvitePlayerFromFraction(playerid, targetid, bool: is_dialog)
{
	if (!IsFractionMember(playerid) || !CheckFractionAccess(playerid, fr_perm_uninvite))
	{
		return 0;
	}
	
	new index = GetFractionMember(playerid);
	
	pformat:(#DEFAULT " " #cPROJECT "%s" #cWHITE " уволил Вас из организации " #cPROJECT "%s" #cWHITE ".",
		GetPlayerCurrentName(playerid),
		GetFractionName(index)
	);
	
	psend:(targetid, C_WHITE);
	
	// Если пункт был выбран из диалога
	if (is_dialog)
	{
		ShowFractionStaff(playerid);
		DeletePVar(playerid, "Fraction:IsDialogUninvite");
	}
	
	// Сообщение фракции
	format:g_small_string(#FRACTION_MESSAGE " %s уволил из организации %s.",
		GetPlayerCurrentName(playerid),
		GetPlayerCurrentName(targetid)
	);
	
	SendFractionMessage(index, g_small_string);
	
	// Сброс фракции
	ResetPlayerFraction(targetid);
	
	SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы успешно уволили игрока из организации.");
	return 1;
}

SetPlayerFractionRank(playerid, targetid, bool: is_dialog)
{	
	if (!IsFractionMember(playerid) || !CheckFractionAccess(playerid, fr_perm_set_rank))
	{
		return 0;
	}
	
	new index = GetFractionMember(playerid),
		is_leader = GetFractionLeader(playerid);
	
	// Разрешаем только лидеру изменять себе ранг
	if (playerid == targetid && !is_leader)
	{
		return 0;
	}
			
	SetPVarInt(playerid, "Fraction:IsDialogSetRank", _: is_dialog);
	SetPVarInt(playerid, "Fraction:TargetId", targetid);
	
	ShowFractionRanks(playerid, D_FRACTION + 7, index);
	return 1;
}

SetPlayerFractionUnit(playerid, targetid, bool: is_dialog)
{
	if (!IsFractionMember(playerid) || !CheckFractionAccess(playerid, fr_perm_set_unit))
	{
		return 0;
	}
	
	new index = GetFractionMember(playerid),
		is_leader = GetFractionLeader(playerid);
	
	// Разрешаем только лидеру изменять себе ранг
	if (playerid == targetid && !is_leader)
	{
		return 0;
	}
			
	SetPVarInt(playerid, "Fraction:IsDialogSetUnit", _: is_dialog);
	SetPVarInt(playerid, "Fraction:TargetId", targetid);
	
	ShowFractionUnits(playerid, D_FRACTION + 9, index);
	return 1;
}

SendFractionMessage(index, const text[], color = INVALID_PARAM)
{
	foreach (new playerid : Player)
	{
		if (GetFractionMember(playerid) == index && CheckFractionDuty(playerid))
		{	
			SendClientMessage(playerid, color == INVALID_PARAM ? GetFractionColor(index) : color, text);
		}
	}
}

ResetPlayerFraction(playerid)
{
	if (character_data[playerid][c_fraction_skin] != 0)
	{
		SetPlayerSkin(playerid, GetCharacterSkin(playerid));
	}
	
	character_data[playerid][c_fraction_skin] = 0;
	
	SetPlayerColor(playerid, C_TEAM_DEFAULT);
	
	character_data[playerid][c_fraction_leader] = 
	character_data[playerid][c_fraction_index] = 
	character_data[playerid][c_fraction_rank_index] =
	character_data[playerid][c_fraction_unit_index] = INVALID_PARAM;
	
	Update:character_int(playerid, "c_fraction_id", 0);
	Update:character_int(playerid, "c_fraction_unit_id", 0);
	Update:character_int(playerid, "c_fraction_rank_id", 0);
	
	Update:character_int(playerid, "c_fraction_skin", character_data[playerid][c_fraction_skin]);
	Update:character_int(playerid, "c_fraction_duty", character_data[playerid][c_fraction_duty]);
}

ResetPlayerHale(playerid)
{
	new follow_id = GetPVarInt(playerid, "Player:Follow");
	
	if (follow_id != INVALID_PLAYER_ID ) 
	{
		SetPVarInt(follow_id, "Player:Lead", INVALID_PLAYER_ID);
	}
	else if(GetPVarInt(playerid, "Player:Lead" ) != INVALID_PLAYER_ID)
	{
		SetPVarInt(follow_id, "Player:Follow", INVALID_PLAYER_ID);
	}
}

ResetPlayerArrest(playerid)
{
	new index = character_data[playerid][c_arrest_camera];
		
	SetPlayerPos( 
		playerid, 
		fraction_camera[index][fr_pos_exit][0],
		fraction_camera[index][fr_pos_exit][1],
		fraction_camera[index][fr_pos_exit][2]
	);
	
	SetPlayerFacingAngle(playerid, fraction_camera[index][fr_pos_exit][3]);
	SetPlayerVirtualWorld(playerid, fraction_camera[index][fr_world]);
	SetPlayerInterior(playerid, fraction_camera[index][fr_int]);
	
	character_data[playerid][c_arrest_time] =
	character_data[playerid][c_arrest_camera] =
	character_data[playerid][c_arrest_type] = 0;
	
	Update:character_string(playerid, "c_arrest_date", "FROM_UNIXTIME(0)", false);
	Update:character_int(playerid, "c_arrest_camera", 0);
	Update:character_int(playerid, "c_arrest_type", TYPE_ARREST_NONE);
}