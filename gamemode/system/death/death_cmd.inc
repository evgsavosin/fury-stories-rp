/*!
	@brief Команды для системы смерти
	@author Found (evg.savosin)
	@date 26.04.2017
*/

CMD:ck(playerid, params[])
{
	new targetid,
		server_tick = GetTickCount();

	if (GetPVarInt(playerid, "CmdTime:CK") > server_tick)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Выслать предложение о принятии «CK» можно раз в 30 секунд.");
		return 1;
	}
	
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /ck [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLoggedForCMD(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (GetCharacterDeath(targetid) != TYPE_DEATH_DIED)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " У данного игрока не умер персонаж.");
		return 1;
	}
	
	if (GetPVarInt(targetid, "Death:CKTrade"))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данному игроку уже было выслано предложение.");
		return 1;
	}
	
	SetPVarInt(targetid, "Death:CKTrade", true);
	SetPVarInt(targetid, "Death:CKTargetId", playerid);
	
	pformat:("" #SUCCESS " Вы отправили предложение о принятии «Character Kill» " #cPROJECT "%s" #cWHITE ".",
		GetPlayerCurrentName(targetid)
	);
	
	psend:(playerid, C_WHITE);
	
	pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " предлагает Вам принять «Character Kill».",
		GetPlayerCurrentName(playerid)
	);
	
	psend:(targetid, C_WHITE);
	SendClientMessage(targetid, C_WHITE, !HELP_TRADE);
	
	SetPVarInt(playerid, "CmdTime:CK", server_tick + (1000 * 30)); 
	return 1;
}

CMD:pk(playerid)
{
	if (GetCharacterDeath(playerid) != TYPE_DEATH_DIED 
	|| death_data[playerid][d_timer] != 0)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
		return 1;
	}
	
	ShowPlayerDialog(playerid, D_DEATH, DIALOG_STYLE_MSGBOX, " ",
		"" #DEFAULT " Подтверждение «Player Kill»\n\n\
		При нажатии кнопки \"Да\" Вы обязуетесь забыть обстоятельства, связанные с Вашим убийством.\n\
		Вы также не имеете право возвращаться на место Вашей смерти в течение часа, пока ситуация,\n\
		связанная с Вашим убийством не будет доиграна.\n\
		Ваш персонаж появится в случайном месте, а Вы продолжите игру.\n\n\
		Вы действительно желаете принять " #cPROJECT "«PK»" #cWHITE "?",
		"Да", "Нет"
	);
	
	return 1;
}

CMD:dm(playerid, params[])
{
	clean:<g_big_string>;
	
	new damageid;
	
	if (sscanf(params, "u", damageid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /dm [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLoggedForCMD(damageid) || !IsPlayerAroundOfPlayer(playerid, damageid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	new weapon_name					[		32 		],
		time						[		32 		],
		bodypart					[		32 		],
		bool: is_exists;
		
	strcat(g_big_string, "" #cPROJECT "Часть тела\t" #cPROJECT "Оружие\t" #cPROJECT "Урон\t" #cPROJECT "Время\n");
	
	for (new i; i < MAX_DAMAGES; i++) 
	{
  	    if (damage_data[damageid][i][dm_time] == 0)
		{
			continue;
		}
		
		clean:<weapon_name>;
		
		switch (damage_data[damageid][i][dm_weapon_id])
		{	
			case 1 .. 42, 49, 53, 54:
			{
				GetWeaponName(damage_data[damageid][i][dm_weapon_id], weapon_name, sizeof weapon_name);
			}
			
			default:
			{
				strcat(weapon_name, "Fist");
			}
		}
		
		GetDeathStringTime(damage_data[damageid][i][dm_time], time);
		GetDeathBodyPart(damage_data[damageid][i][dm_body_part], bodypart);

		format:g_big_string("%s%s\t%s\t%.1f\t%s\n",
			g_big_string,
			bodypart,
			weapon_name,
			damage_data[damageid][i][dm_amount],
			time
		);
		
		is_exists = true;
  	}
	
	if (!is_exists)
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " У данного персонажа нет повреждений.");
		return 1;
	}
	
    ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_TABLIST_HEADERS, 
		GetPlayerCurrentName(damageid), 
		g_big_string, 
		"Закрыть", "" 
	);
	
	return 1;
}