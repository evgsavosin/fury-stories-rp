/*!
	@brief Заголовок системы помещений
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

// Defines
#define DIALOG_PREMISE_NAME				"\
" #DEFAULT " Изменить название\n\n\
Название, как правило, отображается при входе в само помещение.\n\
Введите текст:\n\n\
" #cGRAY "Текст должен содержать только латинские буквы и цифры.\n\
" #cGRAY "Пример: 24/7 'Name', Restaurant 'Name', Bar 'Name', 'Name' Office;"

#define GetPremiseId(%0)				premise_data[%0][pr_id]
#define GetPremisePrice(%0)				premise_data[%0][pr_price]
#define GetPremiseCommunal(%0)			(floatround(premise_data[%0][pr_price]*PERCENT_ELECTRIC_PREMISE))
#define GetPremiseRent(%0)				(floatround(premise_data[%0][pr_price]*PERCENT_RENT_PREMISE))
#define GetPremiseDebt(%0)				premise_data[%0][pr_debt]
#define GetPremiseElectric(%0)			(floatround(premise_data[%0][pr_price]*PERCENT_ELECTRIC_PREMISE))
#define GetPremiseEntrance(%0)			(premise_data[%0][pr_entrance])
#define GetPremiseProfit(%0)			(premise_data[%0][pr_profit])
#define GetPremiseMinProfit(%0)			(floatround(GetPremiseRent(%0)*PERCENT_MIN_PROFIT_PREMISE))
#define GetPremiseBusinessId(%0)		(premise_data[%0][pr_business_id])
#define GetPremiseTypeBought(%0)		(premise_data[%0][pr_buy_type])
#define IsPremiseBought(%0)				(premise_data[%0][pr_character_id] != 0)
#define IsPremiseTied(%0)				(premise_data[%0][pr_business_id] != 0)
#define IsPremiseCashExists(%0)			(premise_data[%0][pr_cash_text] != Text3D: INVALID_3DTEXT_ID)
#define IsPremisePayCredit(%0)			(premise_data[%0][pr_is_credit])

// Constants
const MAX_ASSORT_STOCK = 1000;

// Structures 
enum 
{
	TYPE_PREMISE_MEMBER,
	TYPE_PREMISE_OWNER
};

enum E_PREMISE_DATA 
{
	/// Основные
	pr_id,
	pr_character_id,
	pr_buy_type, 
	pr_name								[	MAX_PREMISE_NAME	],
	Float: pr_pos 						[	4 	], 
	pr_world, 
	pr_interior, 
	pr_price, 
	pr_int_type, // тип интерьера
	pr_lock,
	pr_time,
	pr_debt,
	pr_debt_count,
	Text3D: pr_text, 
	pr_pickup, 
	bool: pr_is_credit,
	
	/// Бизнес
	pr_profit, // Доход
	pr_business_id, // Компания
	pr_assort_stock, // Склад
	pr_entrance, // Платный вход
	Float: pr_cash_pos					[	3	],  // Расположение кассы 
	Text3D: pr_cash_text, // 3D Text расположения кассы
};

new premise_data						  [		MAX_PREMISES	][	E_PREMISE_DATA	],
	
	player_premise						  [		MAX_PLAYERS		][	MAX_PLAYER_PREMISES];
	
Clear:premise_data(index)
{
	Clear:premise_cash(index);
	Clear:premise_visitors(index);
	
	/// Integer
	premise_data[index][pr_id] =
	premise_data[index][pr_character_id] =
	premise_data[index][pr_buy_type] =
	premise_data[index][pr_world] =
	premise_data[index][pr_interior] =
	premise_data[index][pr_price] =
	premise_data[index][pr_int_type] =
	premise_data[index][pr_lock] =
	premise_data[index][pr_time] =
	premise_data[index][pr_debt] =
	premise_data[index][pr_debt_count] =
	premise_data[index][pr_pickup] = 0;
	
	/// Float
	premise_data[index][pr_pos][0] = 
	premise_data[index][pr_pos][1] = 
	premise_data[index][pr_pos][2] = 
	premise_data[index][pr_pos][3] = 0.0;
	
	/// String
	premise_data[index][pr_name][0] = EOS;
	
	/// Bool
	premise_data[index][pr_is_credit] = false;
	
	/// Other
	premise_data[index][pr_text] = Text3D: INVALID_3DTEXT_ID;
}

Clear:player_premise(playerid)
{
	player_premise[playerid][0] =
	player_premise[playerid][1] = INVALID_PARAM;
}

Clear:premise_cash(index)
{
	premise_data[index][pr_cash_pos][0] =
	premise_data[index][pr_cash_pos][1] =
	premise_data[index][pr_cash_pos][2] = 0.0;
	
	premise_data[index][pr_cash_text] = Text3D: INVALID_3DTEXT_ID;
}

Clear:premise_business(index)
{
	Clear:premise_cash(index);
	
	premise_data[index][pr_profit] =
	premise_data[index][pr_entrance] =
	premise_data[index][pr_business_id] = 
	premise_data[index][pr_assort_stock] = 0;
}

Create:premise_data(index, playerid = INVALID_PLAYER_ID)
{
	clean:<g_big_string>;
	
	format:g_big_string("INSERT INTO " #__PREMISES " \ 
		(pr_price, pr_int_type, pr_lock, pr_pos_x, pr_pos_y, pr_pos_z, pr_pos_angle, pr_world, pr_interior) \
			VALUES \ 
		(%i, %i, %i, %f, %f, %f, %f, %i, %i)", 
		premise_data[index][pr_price],
		premise_data[index][pr_int_type],
		premise_data[index][pr_lock],
		premise_data[index][pr_pos][0],
		premise_data[index][pr_pos][1],
		premise_data[index][pr_pos][2],
		premise_data[index][pr_pos][3],
		premise_data[index][pr_world],
		premise_data[index][pr_interior]
	);

	mysql_tquery(db, g_big_string, "OnPremiseCreate", "ii", index, playerid);

	return 1;
}

Update:premise_int(index, column[], _: value, bool: is_pquery = false)
{
	clean:<g_string>;
	
	format:g_string("UPDATE `"#__PREMISES"` SET `%s` = %d WHERE `pr_id` = %d LIMIT 1",
		column,
		value,
		GetPremiseId(index)
	);
	
	return !is_pquery ? mysql_tquery(db, g_string) : mysql_pquery(db, g_string);
}

Update:premise_string(index, column[], value[])
{
	format:g_string("UPDATE `"#__PREMISES"` SET `%s` = '%q' WHERE `pr_id` = %d LIMIT 1",
		column,
		value,
		GetPremiseId(index)
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:premise_float(index, column[], Float: value)
{
	format:g_string("UPDATE `"#__PREMISES"` SET `%s` = %f WHERE `pr_id` = %d LIMIT 1",
		column,
		value,
		GetPremiseId(index)
	);
	
	return mysql_tquery(db, g_string);
}

Update:premise_cash(index)
{
	format:g_string("\
		UPDATE " #__PREMISES " \
		SET pr_cash_pos_x = %f, \
			pr_cash_pos_y = %f, \
			pr_cash_pos_z = %f \
		WHERE pr_id = %i \
		LIMIT 1",
		premise_data[index][pr_cash_pos][0],
		premise_data[index][pr_cash_pos][1],
		premise_data[index][pr_cash_pos][2],
		GetPremiseId(index)
	);
	
	mysql_tquery(db, g_string);
}

Update:premise_business(index)
{
	format:g_string("\
		UPDATE " #__PREMISES " \
		SET pr_business_id = %i, \
			pr_assort_stock = %i, \
			pr_entrance = %i, \
			pr_profit = %i \
		WHERE pr_id = %i \
		LIMIT 1",
		premise_data[index][pr_business_id],
		premise_data[index][pr_assort_stock],
		premise_data[index][pr_entrance],
		premise_data[index][pr_profit],
		GetPremiseId(index)
	);
	
	mysql_tquery(db, g_string);
}