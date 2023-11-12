/*!
	@brief Телепортация в гаражи
	@author Found (evg.savosin)
	@date 05.01.2020
*/

Create:fraction_garage_text()
{
	for (new i; i < sizeof fraction_garage; i++)
	{
		CreatePickupWith3DTextLabel(
			"Въезд\n" #cPROJECT "ALT " #cWHITE "/" #cPROJECT " H", 
			INVALID_PARAM, 
			fraction_garage[i][fr_door_begin_pos][0], 
			fraction_garage[i][fr_door_begin_pos][1], 
			fraction_garage[i][fr_door_begin_pos][2]
		);
		
		CreatePickupWith3DTextLabel(
			"Выезд\n" #cPROJECT "ALT " #cWHITE "/" #cPROJECT " H", 
			INVALID_PARAM, 
			fraction_garage[i][fr_door_end_pos][0], 
			fraction_garage[i][fr_door_end_pos][1], 
			fraction_garage[i][fr_door_end_pos][2]
		);
	}
}
