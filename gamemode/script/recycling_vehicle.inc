/*!
	@brief ������� ���������� ����������
	@author Found (evg.savosin)
	@date 16.12.2016
*/

#define RECYCLE_LS_POS				2411.3958, -1426.2118, 23.7124 /// In Los Santos
#define RECYCLE_RC_POS				639.7700, -499.8184, 16.0630 /// In Red County

#define GetRecycleSumm(%0)			floatround(GetVehicleInfo(%0,v_cost)*0.5)

// Public function
Recyc_OnGameModeInit()
{
	CreatePickupWith3DTextLabel("���������� ���������� #1\n" #cPROJECT "ALT", INVALID_PARAM, RECYCLE_LS_POS);
	CreatePickupWith3DTextLabel("���������� ���������� #2\n" #cPROJECT "ALT", INVALID_PARAM, RECYCLE_RC_POS);
}

Recyc_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_FIRE))
	{
		new vehicleid = GetPlayerVehicleID(playerid),
			modelid;
				
		if (vehicleid != 0
		&& GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{		
			modelid = vehicle_data[vehicleid][v_model];
		
			if (IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, RECYCLE_LS_POS) 
			|| IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, RECYCLE_RC_POS))
			{
				if (!IsOwnerVehicle(playerid, vehicleid))
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " �� �� ������ ������������� ������ ���������.");
					return 1;
				}
				
				if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " �� �� ������ ������������� ������������ ���������.");
					return 1;
				}
			
				SetPVarInt(playerid, !"Recycle:VehicleId", vehicleid);
				format:g_string("" #DEFAULT " ���������� ����������\n\n\
					�� ����������� ������������� ��������� " #cPROJECT "%s" #cWHITE ".\n\
					���������� ����� ����� ����� 50%% �� �������� ��������� ����������.\n\
					%s" #cWHITE "\n\n\
					�� ������������� ������ ������������� ��������� �� " #cGREEN "$%i" #cWHITE "?",
					GetVehicleInfo(modelid, v_name),
					(GetVehicleTypeBought(vehicleid) == TYPE_BUY_START_CAPITAL) ? ("" #cWHITE "�������� ����� ���������� �� ����� " #cPROJECT "\"Start\"") : (""),
					GetRecycleSumm(modelid)
				);
				
				ShowPlayerDialog(playerid, D_RECYCLE, DIALOG_STYLE_MSGBOX, " ", g_string, "��", "���");
				return 0;
			}
		}
	}

	return 1;
}

function Recyc_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == D_RECYCLE)
	{
		if (response)
		{
			new vehicleid = GetPVarInt(playerid, !"Recycle:VehicleId");
			SellVehicle(playerid, vehicleid);
		}

		DeletePVar(playerid, !"Recycle:VehicleId");
	}
	
	return 1;
}