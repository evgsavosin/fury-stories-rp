/*
*
*	JOB SYSTEM
*	Author & Developer: Found (evg.savosin)(Found) & Noirs
*		(c) 2017
*
*	MESSAGE:
*	-
*
*/

enum 
{
	// 1 �������
	J_PORT, // ����
	J_RAFFLE, // ������
	J_WOOD, // ���������
	J_DRUG_FARM, // ����� ��������
	
	// 2 ������� 
	J_MINIBUS,
	J_TAXI,
	J_TRUCKER,
	J_MECHANIC,
	J_PORT_DRIVER,
}

enum E_JOB_DATA
{
	j_id,
	j_name			[	32	],
	j_description	[	512	],
	
	Float: j_pos	[	3	],
	bool: j_official,
	bool: j_special,
}


new job_settings	[	][	E_JOB_DATA	] = 
	{
		{J_PORT, "�������", "" #cGRAY "���������� ��������� � �����.\n\n\
							  ������ �������� � ����� �������� ����� �������������� � �������.\n\
							  ���� ����������� ���������� ����� � ������� ��������� � ����� �� �����.\n\
							  �� ���� ������������ ����� ��� ��������: " #cGREEN "80" #cGRAY " ������.\n\n\
							  �� ������� ����������?", {0.0, 0.0, 0.0}, false, false}
	};