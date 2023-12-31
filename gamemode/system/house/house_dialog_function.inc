/*!
	@brief ��������������� ������� ��� ��������
	@author Found (evg.savosin)
	@date 07.04.2019
*/

ShowHouseDialogSell_Player(playerid, error[] = "")
{
	format:g_string(#DEFAULT " ������� ��������� ��������� ������\n\n\
		������� ID ������, �������� �� ������ ������� ���������:%s\
		" #cRED "%s",
		!isnull(error) ? ("\n\n") : (""),
		error
	);
	
	return ShowPlayerDialog(playerid, D_HOUSE + 15, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}

ShowHouseDialogSell_Summ(playerid, index, error[] = "")
{
	format:g_string("" #DEFAULT " ������� ��������� ��������� ������\n\n\
		������� ����� �� ������� �� ������ ������� ���������:\n\n\
		" #cGRAY "����������� ���� �������: " #cGREEN "$%i" #cGRAY ".\n\
		" #cGRAY "������������ ���� �������: " #cGREEN "$%i" #cGRAY ".%s\
		" #cRED"%s",
		GetMinSaleHousePrice(index),
		GetMaxSaleHousePrice(index),
		!isnull(error) ? ("\n\n") : (""),
		error
	);
	
	return ShowPlayerDialog(playerid, D_HOUSE + 16, DIALOG_STYLE_INPUT, " ", g_string, "�����", "�����");
}