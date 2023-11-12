/*!
	@brief Форматированные функции для диалогов
	@author Found (evg.savosin)
	@date 07.04.2019
*/

ShowHouseDialogSell_Player(playerid, error[] = "")
{
	format:g_string(#DEFAULT " Продажа жилищного помещения игроку\n\n\
		Введите ID игрока, которому Вы хотите продать имущество:%s\
		" #cRED "%s",
		!isnull(error) ? ("\n\n") : (""),
		error
	);
	
	return ShowPlayerDialog(playerid, D_HOUSE + 15, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
}

ShowHouseDialogSell_Summ(playerid, index, error[] = "")
{
	format:g_string("" #DEFAULT " Продажа жилищного помещения игроку\n\n\
		Введите сумму за которую Вы хотите продать имущество:\n\n\
		" #cGRAY "Минимальная цена продажи: " #cGREEN "$%i" #cGRAY ".\n\
		" #cGRAY "Максимальная цена продажи: " #cGREEN "$%i" #cGRAY ".%s\
		" #cRED"%s",
		GetMinSaleHousePrice(index),
		GetMaxSaleHousePrice(index),
		!isnull(error) ? ("\n\n") : (""),
		error
	);
	
	return ShowPlayerDialog(playerid, D_HOUSE + 16, DIALOG_STYLE_INPUT, " ", g_string, "Далее", "Назад");
}