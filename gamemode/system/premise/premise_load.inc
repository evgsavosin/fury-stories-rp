/*!
	@brief Загрузка для системы помещений
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

function OnPremiseLoad()
{
	new rows;
	
	cache_get_row_count(rows);
		
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "pr_id", premise_data[i][pr_id]);
		cache_get_value_name_int(i, "pr_character_id", premise_data[i][pr_character_id]);
		cache_get_value_name_int(i, "pr_buy_type", premise_data[i][pr_buy_type]);
		
		cache_get_value_name_float(i, "pr_pos_x", premise_data[i][pr_pos][0]);
		cache_get_value_name_float(i, "pr_pos_y", premise_data[i][pr_pos][1]);
		cache_get_value_name_float(i, "pr_pos_z", premise_data[i][pr_pos][2]);
		cache_get_value_name_float(i, "pr_pos_angle", premise_data[i][pr_pos][3]);
		
		cache_get_value_name_int(i, "pr_price", premise_data[i][pr_price]);
		cache_get_value_name_int(i, "pr_int_type", premise_data[i][pr_int_type]);
		cache_get_value_name_int(i, "pr_world", premise_data[i][pr_world]);
		cache_get_value_name_int(i, "pr_interior", premise_data[i][pr_interior]);
		cache_get_value_name_int(i, "pr_lock", premise_data[i][pr_lock]);
		cache_get_value_name_int(i, "pr_debt", premise_data[i][pr_debt]);
		cache_get_value_name_int(i, "pr_debt_count", premise_data[i][pr_debt_count]);
		cache_get_value_name_int(i, "pr_time", premise_data[i][pr_time]);
		
		cache_get_value_name_float(i, "pr_cash_pos_x", premise_data[i][pr_cash_pos][0]);
		cache_get_value_name_float(i, "pr_cash_pos_y", premise_data[i][pr_cash_pos][1]);
		cache_get_value_name_float(i, "pr_cash_pos_z", premise_data[i][pr_cash_pos][2]);
		
		cache_get_value_name_int(i, "pr_business_id", premise_data[i][pr_business_id]);
		cache_get_value_name_int(i, "pr_entrance", premise_data[i][pr_entrance]);
		cache_get_value_name_int(i, "pr_profit", premise_data[i][pr_profit]);
		cache_get_value_name_int(i, "pr_assort_stock", premise_data[i][pr_assort_stock]);
		
		cache_get_value_name_int(i, "pr_is_credit", premise_data[i][pr_is_credit]);
		
		cache_get_value_name(i, "pr_name", premise_data[i][pr_name], MAX_PREMISE_NAME);
		
		Create:premise(i);
		
		Load:room(GetPremiseId(i), i, TYPE_REN_PREMISE);
		Load:furn(GetPremiseId(i), i, TYPE_REN_PREMISE);
	}
	
	printf("[OnPremisesLoad]: Premises has been loaded on the server. (ALL: %d)", rows);
	
	return 1;
}

Load:character_premise(playerid)
{
	new debt;
	
	for (new i; i < sizeof premise_data; i++)
	{
		if (premise_data[i][pr_character_id] != GetCharacterId(playerid))
		{
			continue;
		}
		
		GivePremiseOwner(playerid, i);
		
		if (GetPremiseDebt(i) > 0)
		{
			debt++;
		}
		
		printf("[Load:character_premise]: Premises [ID:%d] has been loaded for player %s.",
			GetPremiseId(i),
			GetCharacterName(playerid)
		);
	}
	
	if (debt != 0)
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Внимание!" #cWHITE " У Вас имеются непогашенные задолжности за помещения.");
	}
}
