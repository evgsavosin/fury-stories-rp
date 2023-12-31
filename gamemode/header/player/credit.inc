/*!
	@brief ��������� ������� ��������
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

#define DIALOG_CREDIT_INFO			"\
 " #DEFAULT " �������� ��������� �����\n\
  \n\
  ����� ���������� ����� �� �������� �����, ��������� �� ����� ��������� �������.\n\
  ����, �� ������� ��������������� ������ - �����.\n\
  ����� ��������� ��������� ������� �� �������� " #cPROJECT "��������� �������" #cWHITE ", ������� ����������\n\
  ����������� ����� ����������� ��������� ����� ��� ������������.\n\
  \n\
  ���� ������ �� ������������ � ����, �� ����������� ����������� � ������� " #cPROJECT "20%" #cWHITE" �� �����.\n\
  ��� ������� ����������� ���������� ���� ����������� ���������, � ����� �������� ��������������.\n\
  \n\
  " #cGRAY "��������! � ��������� ����� �� ����� ������������� ���������� �� ������ �����.\n\
  ������ ��� ���� ������������ ���� ��� �������.\n\
  ���������, ��������� ����� ��������� �����, �� ����� ���� ������� ������� ������, ���� ������ �� �������." #cWHITE "\n\
  \n\
  �� ������� ����������?\
"

#define DIALOG_CREDIT_DISSOLVE		"\
   " #DEFAULT " ����������� ��������� �������\n\
   \n\
   ���������� �������, �� ��������� " #cPROJECT "��������� �������" #cWHITE ".\
   \n\
   �� ������� ����������?\
"


#define GetCreditCardBalance(%0) 	credit_data[%0][credit_card]
#define GetCreditCardNumber(%0)		(47200025+character_data[%0][c_id])
#define GetCreditPledge(%0)			(floatround(%0*0.2))
#define GetCreditDifference(%0)		(credit_data[%0][credit_limit]-credit_data[%0][credit_card])
#define GetCreditDateSuccess(%0)	(%0+60*60*24*7*4)
#define AddDebtForCredit(%0)		(floatround(credit_level_info[%0][cl_limit_sum]*0.2))

#define IsCreditOverdue(%0)			(credit_data[%0][credit_give_time] >= (gettime()+(60*60*24)*7)*6)
#define IsCreditCardExists(%0)		(credit_data[%0][credit_limit] == 0 ? 0 : 1)
#define IsAvaibleCreditLimit(%0,%1)	(character_data[%0][c_credit_level] >= %1 ? 1 : 0)
#define IsCreditCardUse(%0)			(credit_data[%0][credit_limit] > credit_data[%0][credit_card])


enum E_CREDIT_LEVEL
{
	cl_reputation_text					[	32	],
	cl_limit_sum
};

new const credit_level_info				[	][E_CREDIT_LEVEL] = 
{
	{"�����������", 15_000},
	{"��������������", 35_000},
	{"���������", 50_000},
	{"�������", 80_000}
};

enum E_CREDIT_DATA
{
	credit_card, // �������� - ��������� �����
	credit_expense, // ������� �� ��� ����� �������
	credit_limit, // �����, ������� ��� ����
	credit_give_time // ����� ��� ����
};

new credit_data						[	MAX_PLAYERS	][	E_CREDIT_DATA	];


Clear:credit_data(playerid)
{
	credit_data[playerid][credit_card] = 
	credit_data[playerid][credit_limit] = 
	credit_data[playerid][credit_expense] =
	credit_data[playerid][credit_give_time] = 0;
}

Remove:credit_data(playerid)
{
	format:g_string("DELETE FROM " #__CREDITS " WHERE credit_character_id = %i LIMIT 1",
		GetCharacterId(playerid)
	);
	
	mysql_tquery(db, g_string);
}

Update:credit_data(playerid)
{
	Update:character_int(playerid, "c_credit_level", character_data[playerid][c_credit_level]);
	
	format:g_string("INSERT INTO " #__CREDITS " VALUES (%i, %i, %i, %i, %i) \
		ON DUPLICATE KEY UPDATE \
			credit_card = VALUES(credit_card), \
			credit_limit = VALUES(credit_limit), \
			credit_expense = VALUES(credit_expense), \
			credit_give_time = VALUES(credit_give_time)",
		GetCharacterId(playerid),
		credit_data[playerid][credit_card],
		credit_data[playerid][credit_limit],
		credit_data[playerid][credit_expense],
		credit_data[playerid][credit_give_time]
	);
	
	mysql_tquery(db, g_string);
}
