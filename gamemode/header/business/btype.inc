/*!
	@brief ���� ��������
	@author Found (evg.savosin)
	@date 23.04.2018
*/

// Defines
#define DIALOG_BUSINESS_TYPE	"\
" #cPROJECT "��� ������������\t" #cPROJECT "�������������\n\
������������\t" #cGRAY "��������, �����������, ������, ������, ������������ ���������, ����-���\n\
������������ �������\t" #cGRAY "����������, ��������, ���, �������\n\
���������� ��������\t" #cGRAY "��������, ������-����\n\
�����������\t" #cGRAY "����\n\
������\t" #cGRAY "������ ��������������\
"

#define GetBusinessTypeText(%0)			business_type[business_data[%0][b_type]]
#define GetBusinessSubtypeText(%0)		business_subtype[business_data[%0][b_type]][business_data[%0][b_subtype]][bst_name]
#define GetBusinessSubtypeSlots(%0)		business_subtype[business_data[%0][b_type]][business_data[%0][b_subtype]][bst_slots]
#define GetBusinessSubtypeEntrance(%0)	business_subtype[business_data[%0][b_type]][business_data[%0][b_subtype]][bst_entrance]

// Structures
new const business_type					[	][	] = 
{
	"������������",
	"������������ �������",
	"���������� ��������",
	"�����������",
	"������"
};

enum E_BUSINESS_SUBTYPE
{
	bst_name							[	32	],
	bst_slots,
	bool: bst_entrance
};

new const business_subtype				[sizeof business_type - 1][MAX_BUSINESS_SUBTYPE	][E_BUSINESS_SUBTYPE] = 
{
	{// ������������
		{"������� 24/7", 5, false},
		{"������� �����������", 6, false},
		{"������� ������", 30, false},
		{"������������� �������", 6, false},
		{"������������ �������", 7, false},
		{"����-���", 7, false}
	},
	
	{// ������������ �������
		{"���", 7, true},
		{"��������", 8, true},
		{"����������", 5, true},
		{"�������", 4, true},
		{"", 0, false},
		{"", 0, false}
	},
	
	{// ���������� ��������
		{"��������", 6, false},
		{"������-����", 6, false},
		{"", 0, false},
		{"", 0, false},
		{"", 0, false},
		{"", 0, false}
	},
	
	{// �����������
		{"����", 10, true},
		{"", 0, false},
		{"", 0, false},
		{"", 0, false},
		{"", 0, false},
		{"", 0, false}
	}
};