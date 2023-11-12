/*!
	@brief Функции пожарного департамента
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

CMD:fireshape(playerid, params[])
{
	if (!IsFractionMember(playerid, FRACTION_FD))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	if (!CheckFractionDuty(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_ON_DUTY);
		return 1;
	}
	
	new vehicleid = GetVehicleAroundOfPlayer(playerid);
	
	if (vehicleid == 0 
	|| vehicle_data[vehicleid][v_owner_type] != TYPE_VEH_FRACTION
	|| vehicle_data[vehicleid][v_owner_id] != GetFractionMemberId(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы должны находиться около служебного транспорта.");
		return 1;
	}
	
	
	new index;
	
	if (sscanf(params, "D(-1)", index))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /fireshape [1 - 3]");
		return 1;
	}
	
	if (index == INVALID_PARAM)
	{
		SetPlayerSkin(playerid, 
			character_data[playerid][c_fraction_skin] == 0 ? GetCharacterSkin(playerid) : GetFractionMemberSkin(playerid)
		);
		
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно сняли пожарную форму.");
		return 1;
	}
	
	if ((0 < index < 3))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы ввели неверный номер пожарной формы.");
		return 1;
	}
	
	new skin_id;
	
	switch (index)
	{
		case 1:
		{
			skin_id = 277;
		}
		
		case 2:
		{
			skin_id = 278;
		}
		
		case 3:
		{
			skin_id = 279;
		}
	}
	
	SetPlayerSkin(playerid, skin_id);
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы переоделись в пожарную форму.");
	
	SendRPMessage(ACTION_AME, playerid, 
		character_data[playerid][c_sex] == 0 ? ("Переоделся") : ("Переоделась")
	);
	
	return 1;
}