/*!
	@brief ��������������� ������� ��� ��������
	@author Found (evg.savosin)
	@date 11.01.2019
*/

// Window
ShowVehicleMenuWindow(playerid, vehicleid)
{
	format:g_string(" %s [�������� ������������]\t" #cGRAY "/window l\n \ 
		 " #cWHITE "%s [�������� ������������]\t" #cGRAY "/window r\n \
		 " #cWHITE "%s [������ ����� ������������]\t" #cGRAY "/window rl\n \
		 " #cWHITE "%s [������ ������ ������������]\t" #cGRAY "/window rr",
		vehicle_data[vehicleid][v_window][0] ? ("" #cPROJECT "�������" #cWHITE "") : ("" #cGRAY "�������" #cWHITE ""),
		vehicle_data[vehicleid][v_window][1] ? ("" #cPROJECT "�������" #cWHITE "") : ("" #cGRAY "�������" #cWHITE ""),
		vehicle_data[vehicleid][v_window][2] ? ("" #cPROJECT "�������" #cWHITE "") : ("" #cGRAY "�������" #cWHITE ""),
		vehicle_data[vehicleid][v_window][3] ? ("" #cPROJECT "�������" #cWHITE "") : ("" #cGRAY "�������" #cWHITE "")
	);
	
	ShowPlayerDialog(playerid, D_CAR + 4, DIALOG_STYLE_TABLIST, " ",
		g_string,
		 "�������", "�����" 
	);
}

// Sell
ShowVehicleSellPlayer(playerid, error[] = "")
{
	format:g_string("" #DEFAULT " ������� ����������\n\n\
		������� ��������� ����� ������ ������.\n\
		������� ID ������, �������� �� ������ ������� ���������:%s\
		" #cRED "%s",
		!isnull(error) ? ("\n\n") : (""),
		error
	);
	
	return ShowPlayerDialog(playerid, D_CAR + 5, DIALOG_STYLE_INPUT, " ", g_string, "�������", "�������");
}

ShowVehicleSellSumm(playerid, vehicleid, error[] = "")
{
	format:g_string("" #DEFAULT " ������� ����������\n\n\
		������� ����� �� ������� �� ������ ������� ��������� " #cPROJECT "%s" #cWHITE ":\n\n\
		" #cGRAY "����������� ���� �������: " #cGREEN "$%i" #cGRAY ".\n\
		" #cGRAY "������������ ���� �������: " #cGREEN "$%i" #cGRAY ".%s\
		" #cRED "%s",
		GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name),
		GetMinSaleVehiclePrice(vehicleid),
		GetMaxSaleVehiclePrice(vehicleid),
		!isnull(error) ? ("\n\n") : (""),
		error
	);
	
	return ShowPlayerDialog(playerid, D_CAR + 6, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

// Swap
ShowVehicleSellSwap(playerid, error[] = "")
{
	format:g_string("" #DEFAULT " ����� ����������\n\n\
		������� ID ������, � ������� �� ������ ���������� �����������:%s\
		" #cRED "%s",
		!isnull(error) ? ("\n\n") : (""),
		error
	);
	
	ShowPlayerDialog(playerid, D_CAR + 9, DIALOG_STYLE_INPUT, " ", g_string, "�������", "�������");
}

ShowVehicleBreakRent(playerid, vehicleid)
{
	format:g_string("" #DEFAULT " ��������� ������� ������\n\n\
	��� ��������� " #cPROJECT "%s" #cWHITE " ��� ��������� � ������������ ��������.\n\
	� ��� ������� ����������� ��������� ������� ������ ��������������, �� ��� �����������.\n\n\
	�� ������������� ������ ��������� ������� �� ������ ����������?",
		GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name)
	);
	
	ShowPlayerDialog(playerid, D_CAR + 15, DIALOG_STYLE_MSGBOX, " ", g_string, "��", "���");
}