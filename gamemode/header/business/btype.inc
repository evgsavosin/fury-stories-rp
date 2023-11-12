/*!
	@brief Типы бизнесов
	@author Found (evg.savosin)
	@date 23.04.2018
*/

// Defines
#define DIALOG_BUSINESS_TYPE	"\
" #cPROJECT "Вид деятельности\t" #cPROJECT "Специализация\n\
Товарооборот\t" #cGRAY "Продукты, электроника, одежда, туризм, строительные материалы, секс-шоп\n\
Общественное питание\t" #cGRAY "Закусочная, ресторан, паб, кофейня\n\
Спортивный комплекс\t" #cGRAY "Спортзал, фитнес-клуб\n\
Развлечения\t" #cGRAY "Клуб\n\
Прочее\t" #cGRAY "Разная направленность\
"

#define GetBusinessTypeText(%0)			business_type[business_data[%0][b_type]]
#define GetBusinessSubtypeText(%0)		business_subtype[business_data[%0][b_type]][business_data[%0][b_subtype]][bst_name]
#define GetBusinessSubtypeSlots(%0)		business_subtype[business_data[%0][b_type]][business_data[%0][b_subtype]][bst_slots]
#define GetBusinessSubtypeEntrance(%0)	business_subtype[business_data[%0][b_type]][business_data[%0][b_subtype]][bst_entrance]

// Structures
new const business_type					[	][	] = 
{
	"Товарооборот",
	"Общественное питание",
	"Спортивный комплекс",
	"Развлечения",
	"Прочее"
};

enum E_BUSINESS_SUBTYPE
{
	bst_name							[	32	],
	bst_slots,
	bool: bst_entrance
};

new const business_subtype				[sizeof business_type - 1][MAX_BUSINESS_SUBTYPE	][E_BUSINESS_SUBTYPE] = 
{
	{// Товарооборот
		{"Магазин 24/7", 5, false},
		{"Магазин электроники", 6, false},
		{"Магазин одежды", 30, false},
		{"Туристический магазин", 6, false},
		{"Строительный магазин", 7, false},
		{"Секс-шоп", 7, false}
	},
	
	{// Общественное питание
		{"Бар", 7, true},
		{"Ресторан", 8, true},
		{"Закусочная", 5, true},
		{"Кофейня", 4, true},
		{"", 0, false},
		{"", 0, false}
	},
	
	{// Спортивный комплекс
		{"Спортзал", 6, false},
		{"Финтес-клуб", 6, false},
		{"", 0, false},
		{"", 0, false},
		{"", 0, false},
		{"", 0, false}
	},
	
	{// Развлечения
		{"Клуб", 10, true},
		{"", 0, false},
		{"", 0, false},
		{"", 0, false},
		{"", 0, false},
		{"", 0, false}
	}
};