/*!
	@brief Система выхода на дежурства
	@author Found (evg.savosin)
	@date 05.01.2020
*/

Create:fraction_duty_text()
{
	for (new i; i < sizeof fraction_duty; i++)
	{
		CreatePickupWith3DTextLabel(
			"Раздевалка\n" #cPROJECT "H", 
			1275, 
			fraction_duty[i][fr_pos][0], 
			fraction_duty[i][fr_pos][1], 
			fraction_duty[i][fr_pos][2]
		);
	}
}

CheckFractionDuty(playerid)
{
	if (!IsFractionMember(playerid))
	{
		return 0;
	}
	
	new id = GetFractionMemberId(playerid);
	
	switch (id)
	{
		case FRACTION_PD, FRACTION_SD, FRACTION_FD, FRACTION_NP:
		{
			return IsFractionMemberOnDuty(playerid);
		}
	}
	
	return 1;
}

ShowFractionMemberDuty(playerid)
{
	if (!IsFractionMemberOnDuty(playerid))
	{
		ShowPlayerDialog(playerid, D_FRACTION + 48, DIALOG_STYLE_LIST, " ", 
			" Заступить на дежурство в рабочей форме\n \
			Заступить на дежурство в гражданской форме",
			"Далее", "Закрыть"
		);
	}
	else 
	{
		ShowPlayerDialog(playerid, D_FRACTION + 49, DIALOG_STYLE_MSGBOX, " ", "\
			" #DEFAULT " Дежурство\n\n\
			Вы желаете покинуть дежурство?",
			"Да", "Нет"
		);
	}
}

FractionMemberDuty(playerid, states, skin = INVALID_PARAM)
{
	new server_tick = GetTickCount();
	
	if (GetPVarInt(playerid, "Fraction:DutyTime") > server_tick)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
		return;
	}
	
	if (!IsFractionMember(playerid))
	{
		return;
	}
	
	new findex = GetFractionMember(playerid);
	
	character_data[playerid][c_fraction_duty] = states;
	
	SendRPMessage(ACTION_AME, playerid, 
		character_data[playerid][c_sex] == 0 ? ("Переоделся") : ("Переоделась")
	);
		
	if (states)
	{	
		if (skin != INVALID_PARAM)
		{
			new Float: x,
				Float: y,
				Float: z,
				Float: angle;
			
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			
			character_data[playerid][c_fraction_skin] = skin;
			SetSpawnInfo(playerid, 264, character_data[playerid][c_fraction_skin], x, y, z, angle, 0, 0, 0, 0, 0, 0);
			SetPlayerSkin(playerid, skin);
		}
		
		SetPlayerColor(playerid,
			GetFractionColor(findex)
		);
		
		format:g_small_string(#FRACTION_MESSAGE " %s заступил%s на дежурство.",
			GetPlayerCurrentName(playerid),
			EndWordSex(playerid)
		);
		
		SendFractionMessage(findex, g_small_string);
		SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы успешно заступили на дежурство.");
	}
	else 
	{
		if (character_data[playerid][c_fraction_skin] != 0)
		{	
			new Float: x,
				Float: y,
				Float: z,
				Float: angle;
			
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			
			SetSpawnInfo(playerid, 264, GetCharacterSkin(playerid), x, y, z, angle, 0, 0, 0, 0, 0, 0);
			SetPlayerSkin(playerid, GetCharacterSkin(playerid));
		}
		
		character_data[playerid][c_fraction_skin] = 0;
		
		SetPlayerColor(playerid, C_TEAM_DEFAULT);
		
		// Удаляем служебные предметы
		RemoveInventoryFractionWeapon(playerid);
		
		format:g_small_string(#FRACTION_MESSAGE " %s закончил%s дежурство.",
			GetPlayerCurrentName(playerid),
			EndWordSex(playerid)
		);
		
		SendFractionMessage(findex, g_small_string);
		SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы успешно закончили дежурство.");
	}
	
	Update:character_int(playerid, "c_fraction_skin", character_data[playerid][c_fraction_skin]);
	Update:character_int(playerid, "c_fraction_duty", character_data[playerid][c_fraction_duty]);
	
	SetPVarInt(playerid, "Fraction:DutyTime", server_tick + 1000);
}

ShowFractionSkinList(playerid, states, findex = INVALID_PARAM, uindex = INVALID_PARAM)
{
	if (!ShowSelectMenu(playerid, states, "Choose skin"))
	{
		SendClientMessage(playerid, C_WHITE, !ERROR_INTERFACE);
		return;
	}
	
	if (states)
	{	
		SetPVarInt(playerid, "Fraction:SkinPage", 0);
		SetPVarInt(playerid, "Fraction:SkinFractionIndex", findex);
		SetPVarInt(playerid, "Fraction:SkinUnitIndex", uindex);
		
		SelectTextDraw(playerid, C_GRAY);
		
		UpdateFractionSkinList(playerid, 0);
	}
	else 
	{	
		for (new i; i < TD_SELECT_MENU_ARRAY; i++)
		{
			g_td_select[playerid][i] = INVALID_PARAM;
		}
		
		DeletePVar(playerid, "Fraction:SkinPage");
		DeletePVar(playerid, "Fraction:SkinFractionIndex");
		DeletePVar(playerid, "Fraction:SkinUnitIndex");
		
		CancelSelectTextDraw(playerid);
	}
	
	SetPVarInt(playerid, "Fraction:SkinStates", states);
}

UpdateFractionSkinList(playerid, index)
{		
	if (!(0 <= index < MAX_FRACTION_SKINS))
	{
		return;
	}
	
	new findex = GetPVarInt(playerid, "Fraction:SkinFractionIndex"),
		uindex = GetPVarInt(playerid, "Fraction:SkinUnitIndex");
	
	if (!IsFractionSkinListExists(findex, uindex, index))
	{
		return;
	}
	
	SetPVarInt(playerid, "Fraction:SkinPage", index);
	
	if (uindex == INVALID_PARAM)
	{
		return;
	}
	
	for (new j; j < TD_SELECT_MENU_ARRAY; j++)
	{
		PlayerTextDrawHide(playerid, ptd_select_menu[playerid][j]);
		g_td_select[playerid][j] = INVALID_PARAM;
	}
	
	for (new i; i < TD_SELECT_MENU_ARRAY; i++)
	{
		if (i + index > MAX_FRACTION_SKINS)
		{
			PlayerTextDrawHide(playerid, ptd_select_menu[playerid][i]);
			g_td_select[playerid][i] = INVALID_PARAM;
			continue;
		}
		
		if (fraction_unit_data[findex][uindex][fr_skins][i + index] == 0)
		{
			continue;
		}
		
		PlayerTextDrawSetPreviewModel(
			playerid, 
			ptd_select_menu[playerid][i], 
			fraction_unit_data[findex][uindex][fr_skins][i + index]
		);
		
		PlayerTextDrawSetPreviewRot(
			playerid, 
			ptd_select_menu[playerid][i], 
			0.0, 
			0.0, 
			0.0, 
			1.0
		);
		
		PlayerTextDrawShow(playerid, ptd_select_menu[playerid][i]);
		
		g_td_select[playerid][i] = fraction_unit_data[findex][uindex][fr_skins][i + index];
		SetPVarInt(playerid, "Fraction:SkinNextIndex", i);
	}
}

IsFractionSkinListExists(findex, uindex, index)
{
	new bool: is_exists;
	
	for (new i = index; i < MAX_FRACTION_SKINS; i++)
	{
		if (fraction_unit_data[findex][uindex][fr_skins][i] != 0)
		{
			is_exists = true;
		}
	}
	
	return is_exists;
}