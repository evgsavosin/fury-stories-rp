/*!
	@brief Команды для системы телефонов Fuber
	@author Found (evg.savosin)
	@date 01.09.2019
*/

CMD:cancelfuber(playerid)
{
	if (GetPVarInt(playerid, "Fuber:SelectMap"))
	{
		DeletePVar(playerid, "Admin:MapTeleportIgnore");
		DeletePVar(playerid, "Phone:HideCursor");
		DeletePVar(playerid, "Fuber:SelectMap");
		ShowFuberPassengerOrderDialog(playerid, D_PHONE_APP_FUBER + 2);
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы отменили процесс проложения маршрута.");
	}
	
	return 1;
}