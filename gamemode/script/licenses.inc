/*!
	@brief Система лицензий
	@author Found (evg.savosin)
	@date 26.04.2018
*/

#define LIC_DRIVE_COST 		70
#define LIC_BOAT_COST 		150
#define LIC_FLY_COST 		5000

#define DIALOG_LIC_PRICE_LIST	"\
" #cPROJECT "Наименование\t" #cPROJECT "Стоимость\n\
Водительские права\t" #cGREEN "$" #LIC_DRIVE_COST "\n\
Сертификат судоводителя\t" #cGREEN "$" #LIC_BOAT_COST "\n\
Лицензия пилота-любителя\t" #cGREEN "$"# LIC_FLY_COST "\
"

#define BUY_LICENSE_POS		240.7703, 1856.9331, 1503.9016

Lic_OnGameModeInit()
{
	CreatePickupWith3DTextLabel("" #cPROJECT "H", 
		INVALID_PARAM, 
		BUY_LICENSE_POS,
		WORLD_OTHER + 7, 
		INT_OTHER 
	);
}

Lic_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{
		if (IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, BUY_LICENSE_POS))
		{
			ShowPlayerDialog(playerid, D_LICENSES, DIALOG_STYLE_TABLIST_HEADERS, " ", DIALOG_LIC_PRICE_LIST, "Выбрать", "Закрыть");
			return 0;
		}
	}
	
	return 1;
}

Lic_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	#pragma unused inputtext
	if (dialogid == D_LICENSES)
	{
		if (!response)
		{
			return 1;
		}
		
		new cost;
		
		SetPVarInt(playerid, "License:Type", listitem);
		
		if (IsPlayerLicenseExists(playerid, E_LICENSES_INFO: listitem))
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " У Вас уже имеется данная лицензия.");
			return 1;
		}
		
		if (listitem == 0) // Права
		{
			cost = LIC_DRIVE_COST;
		}
		
		else if (listitem == 1) // Судоводитель
		{
			cost = LIC_BOAT_COST;
		}
		
		else if (listitem == 2) // Пилот
		{
			cost = LIC_FLY_COST;
		}
		
		MakePayment(playerid, cost, "buy_license");
	}
	
	return 1;
}

function PAY:buy_license(playerid, status)
{
	if (!status)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_CASH);
		DeletePVar(playerid, "License:Type");
		return 1;
	}
	
	new type = GetPVarInt(playerid, "License:Type");
	
	GivePlayerLicense(playerid, E_LICENSES_INFO: type);
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно приобрели лицензию.");
	
	DeletePVar(playerid, "License:Type");
	return 1;
}


