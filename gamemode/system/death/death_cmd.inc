/*!
	@brief ������� ��� ������� ������
	@author Found (evg.savosin)
	@date 26.04.2017
*/

CMD:ck(playerid, params[])
{
	new targetid,
		server_tick = GetTickCount();

	if (GetPVarInt(playerid, "CmdTime:CK") > server_tick)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " ������� ����������� � �������� �CK� ����� ��� � 30 ������.");
		return 1;
	}
	
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " �������: /ck [ID ������]");
		return 1;
	}
	
	if (!IsPlayerLoggedForCMD(targetid))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
	if (GetCharacterDeath(targetid) != TYPE_DEATH_DIED)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " � ������� ������ �� ���� ��������.");
		return 1;
	}
	
	if (GetPVarInt(targetid, "Death:CKTrade"))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " ������� ������ ��� ���� ������� �����������.");
		return 1;
	}
	
	SetPVarInt(targetid, "Death:CKTrade", true);
	SetPVarInt(targetid, "Death:CKTargetId", playerid);
	
	pformat:("" #SUCCESS " �� ��������� ����������� � �������� �Character Kill� " #cPROJECT "%s" #cWHITE ".",
		GetPlayerCurrentName(targetid)
	);
	
	psend:(playerid, C_WHITE);
	
	pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " ���������� ��� ������� �Character Kill�.",
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
		"" #DEFAULT " ������������� �Player Kill�\n\n\
		��� ������� ������ \"��\" �� ���������� ������ ��������������, ��������� � ����� ���������.\n\
		�� ����� �� ������ ����� ������������ �� ����� ����� ������ � ������� ����, ���� ��������,\n\
		��������� � ����� ��������� �� ����� ��������.\n\
		��� �������� �������� � ��������� �����, � �� ���������� ����.\n\n\
		�� ������������� ������� ������� " #cPROJECT "�PK�" #cWHITE "?",
		"��", "���"
	);
	
	return 1;
}

CMD:dm(playerid, params[])
{
	clean:<g_big_string>;
	
	new damageid;
	
	if (sscanf(params, "u", damageid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " �������: /dm [ID ������]");
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
		
	strcat(g_big_string, "" #cPROJECT "����� ����\t" #cPROJECT "������\t" #cPROJECT "����\t" #cPROJECT "�����\n");
	
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
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " � ������� ��������� ��� �����������.");
		return 1;
	}
	
    ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_TABLIST_HEADERS, 
		GetPlayerCurrentName(damageid), 
		g_big_string, 
		"�������", "" 
	);
	
	return 1;
}