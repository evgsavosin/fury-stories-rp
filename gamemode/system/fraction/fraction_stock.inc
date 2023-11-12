/*!
	@brief Система склада
	@author Found (evg.savosin)
	@date 05.01.2020
*/

Create:fraction_stock_text()
{
	for (new i; i < sizeof fraction_stock; i++)
	{
		CreatePickupWith3DTextLabel(
			"Склад\n" #cPROJECT "H", 
			1239, 
			fraction_stock[i][fr_pos][0], 
			fraction_stock[i][fr_pos][1], 
			fraction_stock[i][fr_pos][2]
		);
	}
}