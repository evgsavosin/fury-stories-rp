/*!
	@brief Заголовок системы кредитов
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

#define DIALOG_CREDIT_INFO			"\
 " #DEFAULT " Оформить кредитную карту\n\
  \n\
  После оформления карты Вы получите сумму, зависящую от Вашей кредитной истории.\n\
  Срок, на который предоставляются деньги - месяц.\n\
  После успешного погашения кредита Вы получите " #cPROJECT "кредитную историю" #cWHITE ", которая определяет\n\
  возможность взять максимально доступную сумму для кредитования.\n\
  \n\
  Если кредит не оплачивается в срок, то начисляется задолжность в размере " #cPROJECT "20%" #cWHITE" от суммы.\n\
  При большой задолжности существует риск конфискации имущества, а также судебных разбирательств.\n\
  \n\
  " #cGRAY "Внимание! С кредитной карты не могут производиться транзакции на другие счета.\n\
  Данный вид карт предназначен лишь для покупок.\n\
  Имущество, купленное через кредитную карту, не может быть продано другому игроку, если кредит не погашен." #cWHITE "\n\
  \n\
  Вы желаете продолжить?\
"

#define DIALOG_CREDIT_DISSOLVE		"\
   " #DEFAULT " Расторгнуть кредитный договор\n\
   \n\
   Расторгнув договор, Вы сохраните " #cPROJECT "кредитную историю" #cWHITE ".\
   \n\
   Вы желаете продолжить?\
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
	{"Отсутствует", 15_000},
	{"Незначительная", 35_000},
	{"Умеренная", 50_000},
	{"Большая", 80_000}
};

enum E_CREDIT_DATA
{
	credit_card, // Средства - кредитная карта
	credit_expense, // Затраты за все время кредита
	credit_limit, // Лимит, который был взят
	credit_give_time // Когда был взял
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
