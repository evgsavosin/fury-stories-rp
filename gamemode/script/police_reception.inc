/*!
	@brief ����������� �������� � headquarters
	@author Found (evg.savosin)
	@date 25.04.2019
*/

#define NUMBER_ABC_LENGTH					3
#define NUMBER_INT_LENGTH					4
#define NUMBER_COST							200

#define POLICE_RECEPTION_DIALOG				D_POLICE_RECEPTION, DIALOG_STYLE_LIST," "," ��������� ��������� �����","�����","�������"
#define POLICE_RECEPTION_POS				-337.3520, 2521.1594, 1504.4490

// Public functions
PReception_OnGameModeInit()
{
	CreatePickupWith3DTextLabel("�������", 1239, POLICE_RECEPTION_POS, WORLD_PD_HEADQUARTERS, INT_OTHER);
}

PReception_OnPlayerKeySC(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{
		if (IsPlayerInRangeOfPoint(playerid, 
		FACTOR_TELEPORT_RADIUS, 
		POLICE_RECEPTION_POS))
		{
			ShowPlayerDialog(playerid, POLICE_RECEPTION_DIALOG);
			return 0;
		}
	}
	
	return 1;
}

PReception_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	#pragma unused listitem
	
	if (dialogid == D_POLICE_RECEPTION)
	{
		if (!response)
		{
			return 1;
		}
		
		if (listitem == 0) // ��������� ��������� �����
		{
			if (!ShowVehicleList(playerid, D_POLICE_RECEPTION + 1, _, "�����"))
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " � ��� ����������� ���������.");
				return 1;
			}
		}
	}
	else if (dialogid == D_POLICE_RECEPTION + 1)
	{
		if (!response)
		{
			ShowPlayerDialog(playerid, POLICE_RECEPTION_DIALOG);
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
			if (!isnull(vehicle_data[vehicleid][v_number]))
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " ������ ��������� ��� ����� �����.");
				ShowVehicleList(playerid, D_POLICE_RECEPTION + 1, _, "�����");
				return 1;
			}
			
			SetPVarInt(playerid, "Vehicle:Select", vehicleid);
			
			format:g_string(#DEFAULT " ��������� ��������� �����\n\n\
				- �������: " #cGREEN "$%d" #cWHITE "\n\
				- ������ �������� ���������\n\n\
				�� ������������� ������� �������� �������� ���� ��� " #cPROJECT "%s" #cWHITE "?",
				NUMBER_COST,
				GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name)
			);
			
			ShowPlayerDialog(playerid, D_POLICE_RECEPTION + 3, DIALOG_STYLE_MSGBOX, " ", 
				g_string,
				"��", "���"
			);
		}
		else 
		{
			ShowPlayerDialog(playerid, D_POLICE_RECEPTION + 2, DIALOG_STYLE_MSGBOX, " ", 
				"" #DEFAULT " ����������\n\n\
				��������! ������ ��������� �� ������ �� �������.",
				"�����", ""
			);
		}
	}
	else if (dialogid == D_POLICE_RECEPTION + 2)
	{
		ShowVehicleList(playerid, D_POLICE_RECEPTION + 1, _, "�����");
	}
	else if (dialogid == D_POLICE_RECEPTION + 3)
	{
		new vehicleid = GetPVarInt(playerid, "Vehicle:Select");
		
		DeletePVar(playerid, "Vehicle:Select");
			
		if (!response)
		{
			ShowVehicleList(playerid, D_POLICE_RECEPTION + 1, _, "�����");
			return 1;
		}
		
		if (!GivePlayerCash(playerid, -NUMBER_COST))
		{
			SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
			ShowVehicleList(playerid, D_POLICE_RECEPTION + 1, _, "�����");
			return 1;
		}
		
		clean:<vehicle_data[vehicleid][v_number]>;
		GenerateVehicleNumber(vehicle_data[vehicleid][v_number], 32);
		SetVehicleNumberPlate(vehicleid, vehicle_data[vehicleid][v_number]);
		
		Update:vehicle_data(vehicleid, playerid);
		
		pformat:(#SUCCESS " �� ������� �������� �������� ���� " #cPROJECT "%s" #cWHITE " ��� " #cPROJECT "%s" #cWHITE ".",
			vehicle_data[vehicleid][v_number],
			GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name)
		);
		psend:(playerid, C_WHITE);
	}
	
	return 1;
}

// Functions
GenerateVehicleNumber(string[], size)
{
	clean:<string>;
	
	for (new i; i < NUMBER_ABC_LENGTH; i++)
	{
		format(string, size, "%s%c", 
			string,
			(random(90 - 65) + 65)
		);
	}
	
	strcat(string, "-", size);
	
	for (new i; i < NUMBER_INT_LENGTH; i++)
	{
		format(string, size, "%s%d", string, random(9));
	}
}