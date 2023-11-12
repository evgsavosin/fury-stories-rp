/*!
	@brief Система оплаты
	@author Found (evg.savosin)
	@date 15.01.2018
	
	Ответ приходит в функцию:
	PAY:example(playerid, status, type)
*/

// Defines
#define GetPaymentTypeText(%0)		payment_type[%0]

// Structures
enum 
{
	TYPE_PAY_NONE = 0,
	TYPE_PAY_MONEY = 1,
	TYPE_PAY_CARD,
	TYPE_PAY_CREDIT,
	TYPE_PAY_START_CAPITAL // Стартовый капитал
}

new const payment_type[][] =
{
	"",
	"Наличные",
	"Карта",
	"Кредитная карта",
	"Карта «Start»"
};

// Functions

MakePayment(playerid, const cost, func_name[32], title[] = "Метод оплаты")
{
	new count = 0;
	
	new str_func_name		[32],
		str_sum_text		[64],
		str_credit_card		[128],
		str_start_capital	[128];
		
	format(str_func_name, sizeof str_func_name, "Pay_%s", func_name);
	
	if (funcidx(str_func_name) == INVALID_PARAM)
	{
		return;
	}
	
	g_dialog_select[playerid][count++] = TYPE_PAY_NONE;
	g_dialog_select[playerid][count++] = TYPE_PAY_MONEY;
	g_dialog_select[playerid][count++] = TYPE_PAY_CARD;
	
	// Кредит
	if (IsCreditCardExists(playerid))
	{
		format:str_credit_card("\n Кредитная карта [" #cPROJECT "№%i" #cWHITE "]\t" #cGREEN "$%i" #cWHITE "",
			GetCreditCardNumber(playerid),
			GetCreditCardBalance(playerid)
		);
		
		g_dialog_select[playerid][count++] = TYPE_PAY_CREDIT;
	}
	
	// Стартовый капитал
	if (character_data[playerid][c_start_capital] > 0)
	{
		format:str_start_capital("\n Дебетовая карта «Start»\t" #cGREEN "$%i" #cWHITE,
			character_data[playerid][c_start_capital]
		);
		
		g_dialog_select[playerid][count] = TYPE_PAY_START_CAPITAL;
	}
	
	if (cost > 0)
	{
		format:str_sum_text(#cGRAY " Сумма к оплате: \t" #cGREEN "$%i" #cWHITE,
			cost
		);
	}
	else 
	{
		strcat(str_sum_text, #cGRAY "Выберите способ оплаты:");
	}
	
	format:g_string("%s\n \
		Наличными\t" #cGREEN "$%i" #cWHITE "\n \
		Дебетовая карта [" #cPROJECT "№%i" #cWHITE "]\t" #cGREEN "$%i" #cWHITE "%s%s",
		str_sum_text,
		GetCharacterMoney(playerid),
		GetCharacterCardNumber(playerid),
		GetCharacterCardBalance(playerid),
		str_credit_card,
		str_start_capital
	);
	
	ShowPlayerDialog(playerid, D_BUY, DIALOG_STYLE_TABLIST, title, g_string, "Выбрать", "Закрыть");
	
	SetPVarInt(playerid, "Payment:Cost", cost);
	SetPVarString(playerid, "Payment:FuncName", str_func_name);
	SetPVarString(playerid, "Payment:FuncNameOrigin", func_name);
}

function Pay_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if (dialogid == D_BUY)
	{
		if (response)
		{
			new cost = GetPVarInt(playerid, "Payment:Cost"),
				type = g_dialog_select[playerid][listitem],
				bool: status = false;
			
			switch (type)
			{	
				case TYPE_PAY_MONEY:
				{
					if (GivePlayerCash(playerid, -cost))
					{
						status = true;
					}
				}
				
				case TYPE_PAY_CARD:
				{
					if (GiveDebitCardMoney(playerid, -cost))
					{
						status = true;
					}
				}
				
				case TYPE_PAY_CREDIT:
				{
					if (GiveCreditCardMoney(playerid, -cost))
					{
						status = true;
					}
				}
				
				case TYPE_PAY_START_CAPITAL:
				{
					if (GivePlayerStartCapital(playerid, -cost))
					{
						SetPVarInt(playerid, "Buy:StartCapital", 1);

						status = true;
					}
				}
				
				default:
				{
					new func_name		[32];
					GetPVarString(playerid, "Payment:FuncNameOrigin", func_name, sizeof func_name);
					MakePayment(playerid, GetPVarInt(playerid, "Payment:Cost"), func_name);
					return 1;
				}
			}
			
			clean:<g_small_string>;
			GetPVarString(playerid, "Payment:FuncName", g_small_string, sizeof g_small_string);
			
			if (!isnull(g_small_string))
			{
				CallLocalFunction(g_small_string, "iii", playerid, status, listitem);
			}
		}
		
		DeletePVar(playerid, "Payment:Cost");
		DeletePVar(playerid, "Payment:FuncName");
		DeletePVar(playerid, "Payment:FuncNameOrigin");
	}
	
	return 1;
}