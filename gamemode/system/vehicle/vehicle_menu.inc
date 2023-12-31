/*!
	@brief ���� ����������
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.01.2018
*/

ShowVehicleListControl(playerid, const vehicleid)
{
	new index = GetPlayerVehicleIndexByServerId(playerid, vehicleid);
	
	if (index == INVALID_PARAM)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " ��������� �� ������ �� �������.");
		return;
	}
	
	new delete = player_vehicle[playerid][pv_delete][GetPlayerVehicleIndexByServerId(playerid, vehicleid)];
	
	format:g_string(" ���������� � ����������\n \
		���������� �����������\n \
		%s",
		(delete == 1) ? ("�������� �������� ����������") : ("������ ���������")
	);
	
	ShowPlayerDialog(playerid, D_CAR + 1, DIALOG_STYLE_LIST, 
		GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name), 
		g_string,
		"�������", "�����"
	);
}

ShowVehicleInformation(playerid, modelid, vehicleid, const dialogid, btn_1[] = "", btn_2[] = "")
{
	clean:<g_big_string>;
	
	new slots = GetVehicleInfo(modelid, v_max_slots),
		seat = GetVehicleInfo(modelid, v_seat);
	
	if (vehicleid != INVALID_PARAM)
	{
		format:g_big_string("" #DEFAULT " ���������� � ���������� #%d\n\n",
			GetVehicleId(vehicleid)
		);
	}
	else 
	{
		format:g_big_string("" #DEFAULT " ���������� � ����������\n\n");
	}
	
	if (vehicleid != INVALID_PARAM)
	{
		format:g_big_string("%s��� �������������: " #cPROJECT "%s" #cWHITE ".\n", 
			g_big_string,
			GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT ? ("������������") : ("�� ��������") 
		);
	}
	
	format:g_big_string("%s���: " #cPROJECT "%s" #cWHITE ".\n", 
		g_big_string,
		GetVehicleInfo(modelid, v_name) 
	);
	
	format:g_big_string("%s���: " #cPROJECT "%s" #cWHITE ".\n", 
		g_big_string,
		GetVehicleInfo(modelid, v_type) 
	);
	
	format:g_big_string("%s������: " #cPROJECT "%s" #cWHITE ".\n", 
		g_big_string, 
		GetVehicleInfo(modelid, v_drive) 
	);
	
	format:g_big_string("%s�������� ���������: " #cGREEN "$%i" #cWHITE "\n", 
		g_big_string,
		GetVehicleInfo(modelid, v_cost) 
	);

	if (vehicleid == INVALID_PARAM)
	{
		format:g_big_string("%s��������� ��������� ������: " #cGREEN "$%i" #cWHITE ".\n", 
			g_big_string,
			GetVehicleRent(modelid, 7) 
		);
	}
	
	format:g_big_string("%s�����: " #cPROJECT "%i" #cWHITE ".\n", 
		g_big_string,
		seat + GetVehicleMaxSeats(modelid)
	);
	
	format:g_big_string("%s��������������� ���������: " #cPROJECT "%i" #cWHITE " ����%s.\n", 
		g_big_string,
		slots,
		EndWordSlot(slots)
	);
	
	format:g_big_string("%s����� ���������� ����: " #cPROJECT "%0.2f" #cWHITE " ������.\n", 
		g_big_string,
		GetVehicleInfo(modelid, v_max_fuel)
	);
	
	format:g_big_string("%s������ �������: " #cPROJECT "%0.2f" #cWHITE " MPG.\n", 
		g_big_string,
		GetFuelRate(modelid)
	);

	if (vehicleid != INVALID_PARAM && vehicle_data[vehicleid][v_owner_id] == GetCharacterId(playerid)) // ���� ������������� ��������
	{
		format:g_big_string("%s��������� ���������: %s.", 
			g_big_string,
			("��������")
		);
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_MSGBOX, " ", g_big_string, btn_1, btn_2);
	return 1;
}

ShowVehicleMenu(playerid, vehicleid, dialogid = D_CAR + 3)
{
	clean:<g_big_string>;
	
	new is_owner = IsOwnerVehicle(playerid, vehicleid),
		in_vehicle = IsPlayerInVehicle(playerid, vehicleid);
	
	if (in_vehicle && !IsBikeVehicle(vehicleid))
	{
		format:g_big_string(" " #cWHITE "%s" #cWHITE " ���������\t" #cGRAY "2 | NUM | /en\n",
			vehicle_data[vehicleid][v_engine] == VEHICLE_PARAMS_ON ? ("" #cGRAY "���������") : ("" #cPROJECT "�������")
		);
		
		format:g_big_string("%s " #cWHITE "%s" #cWHITE " ����\t" #cGRAY "CTRL\n",
			g_big_string,
			vehicle_data[vehicleid][v_light] == VEHICLE_PARAMS_ON ? ("" #cGRAY "���������") : ("" #cPROJECT "��������")
		);
		
		strcat(g_big_string, " " #cWHITE "����\t" #cGRAY "/window\n");
			
		format:g_big_string("%s " #cWHITE "%s" #cWHITE " �����. ��������\n",
			g_big_string,
			vehicle_data[vehicleid][v_limit] == VEHICLE_PARAMS_ON ? ("" #cGRAY "���������") : ("" #cPROJECT "��������")
		);
		
		format:g_big_string("%s " #cWHITE "%s" #cWHITE " ������������\n",
			g_big_string,
			vehicle_data[vehicleid][v_radio] ? ("" #cGRAY "���������") : ("" #cPROJECT "��������")
		);
	}
	
	if (!IsBikeVehicle(vehicleid))
	{
		format:g_big_string("%s " #cWHITE "%s" #cWHITE " �����\t" #cGRAY "/hood\n",
			g_big_string,
			vehicle_data[vehicleid][v_hood] == VEHICLE_PARAMS_ON ? ("" #cGRAY "�������") : ("" #cPROJECT "�������")
		);
		
		format:g_big_string("%s " #cWHITE "%s" #cWHITE " ��������\t" #cGRAY "/boot\n",
			g_big_string,
			vehicle_data[vehicleid][v_boot] == VEHICLE_PARAMS_ON ? ("" #cGRAY "�������") : ("" #cPROJECT "�������")
		);
	}
	
	if (is_owner)
	{
		if (in_vehicle)
		{
			strcat(g_big_string, " " #cWHITE "������������\t" #cGRAY "/park\n");
		}
		else 
		{
			strcat(g_big_string, " " #cWHITE "������� ��������� �� ����������� �����\t\n");
		}
		
		format:g_big_string("%s " #cWHITE "%s" #cWHITE " ���������\t" #cGRAY "/clock\n",
			g_big_string,
			vehicle_data[vehicleid][v_lock] == VEHICLE_PARAMS_ON ? ("" #cPROJECT "�������") : ("" #cGRAY "�������")
		);
		
		if (!in_vehicle && !IsBikeVehicle(vehicleid))
		{
			strcat(g_big_string, " " #cWHITE "������ ����������\t" #cGRAY "/cdetails\n");
		}
		
		if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
		{
			strcat(g_big_string, " " #cWHITE "��������� ������� ������\t" #cGRAY "/unrentcar\n");
		}
		else 
		{
			strcat(g_big_string, " " #cWHITE "�������\t" #cGRAY "/sellcar\n");
		}
		
		strcat(g_big_string, " " #cWHITE "��������\t" #cGRAY "/swapcar\n");
		strcat(g_big_string, " " #cWHITE "��������\t" #cGRAY "/trustcar\n");
	}
	
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, " ", g_big_string, "�������", "�������");
	return 1;
}

ShowVehicleList(playerid, const dialogid = D_CAR, btn_1[] = "�������", btn_2[] = "�������")
{
	clean:<g_string>;
	
	new count;
	
	for (new i; i < MAX_PLAYER_VEHICLES; i++)
	{
		if (player_vehicle[playerid][pv_id][i] == 0)
		{
			continue;
		}
		
		format:g_string("%s " #cWHITE "%s\t%s" #cWHITE " %s\n",
			g_string,
			GetVehicleInfo(player_vehicle[playerid][pv_model][i], v_name),
			(player_vehicle[playerid][pv_server_id][i] != 0) ? ("" #cPROJECT "������") : (" "),
			(player_vehicle[playerid][pv_delete][i]) ? ("[" #cDARKRED "����� �����" #cWHITE "]") : (" ")
		);
		
		g_dialog_select[playerid][count] = i;
		count++;
	}
	
	return count ? ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, " ", g_string, btn_1, btn_2) : 0;
}

ShowVehicleAroundOfPlayerList(playerid, const dialogid, limit_display = 0)
{
	clean:<g_string>;
	
	new count;
	
	for (new i = 1, vehicles = GetVehiclePoolSize(); i <= vehicles; i++)
	{		
		if (!IsOwnerVehicle(playerid, i) 
		|| !IsPlayerAroundVehicle(playerid, i, 30.0)
		|| IsBikeVehicle(i))
		{
			continue;
		}

		format:g_string("%s " #cWHITE "%s\n",
			g_string,
			GetVehicleInfo(vehicle_data[i][v_model], v_name)
		);
		
		g_dialog_select[playerid][count] = i;
		count++;
	}
	
	printf("[ShowVehicleAroundOfPlayerList]: count %d", count);
	if (count > limit_display)
	{
		ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST, "��������� � �������", g_string, "�������", "�������");
		return count;
	}
	
	return count;
}