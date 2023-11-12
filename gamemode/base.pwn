/*!
	@brief Скелет игрового мода
	@author Found (evg.savosin)
	@date 16.12.2016, update 16.01.2018

*/

main() 
{
	print("Development: Found (evg.savosin)");
}

public OnGameModeInit()
{	
	strglobalclear();
	
	Server_OnGameModeInit();
	DB_OnGameModeInit();
	
	Include_ServerObjects();
	Include_GlobalTextDraw();
	
	Player_OnGameModeInit();
	Weather_OnGameModeInit();
	Inv_OnGameModeInit();
	Hostel_OnGameModeInit();
	House_OnGameModeInit();
	Vehicle_OnGameModeInit();
	Admin_OnGameModeInit();
	AdminLog_OnGameModeInit();
	Garage_OnGameModeInit();
	VehShop_OnGameModeInit();
	Enters_OnGameModeInit();
	Rent_OnGameModeInit();
	Recyc_OnGameModeInit();
	Phone_OnGameModeInit();
	Site_OnGameModeInit();
	Bank_OnGameModeInit();
	Lic_OnGameModeInit();
	Premise_OnGameModeInit();
	Bus_OnGameModeInit();
	Gas_OnGameModeInit();
	Fun_OnGameModeInit();
	Corpse_OnGameModeInit();
	GunShop_OnGameModeInit();
	Fraction_OnGameModeInit();
	PReception_OnGameModeInit();
	Autoservice_OnGameModeInit();
	Crime_OnGameModeInit();
	
	// Fraction
	News_OnGameModeInit();
	
	#if defined __DEBUG
		Test_OnGameModeInit(); /// !! Remove
	#endif
	return 1;
}

public OnGameModeExit()
{
	DB_OnGameModeExit();
	
	foreach (new playerid : Player)
	{
		HidePlayerDialog(playerid);
	}
	
	return 1;
}

public OnPlayerConnect(playerid)
{
	strglobalclear();
	
	Include_RemoveObject(playerid);
	Include_PlayerTextDraw(playerid);
	
	Connection_OnPlayerConnect(playerid);
	TextDraw_OnPlayerConnect(playerid);
	Vehicle_OnPlayerConnect(playerid);
	Weather_OnPlayerConnect(playerid);
	return 1;
}

public OnPlayerRequestClass(playerid, classid) 
{
	strglobalclear();
	
	Player_OnPlayerRequestClass(playerid, classid);
	return 1;
}

public OnPlayerRequestSpawn(playerid) 
{
	strglobalclear();
	
	if (!Player_OnPlayerRequestSpawn(playerid)) 
	{
		return 0;
	}
	
	return 1;
}

public OnPlayerSpawn(playerid)
{
	strglobalclear();
	
	Inv_OnPlayerSpawn(playerid);
	Ren_OnPlayerSpawn(playerid);
	Death_OnPlayerSpawn(playerid);
	Fraction_OnPlayerSpawn(playerid);
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	strglobalclear();
	
	TextDraw_OnPlayerDisconnect(playerid, reason);
	Phone_OnPlayerDisconnect(playerid, reason);
	Player_OnPlayerDisconnect(playerid, reason);
	Connection_OnPlayerDisconnect(playerid);
	Vehicle_OnPlayerDisconnect(playerid, reason);
	Inv_OnPlayerDisconnect(playerid, reason);
	Music_OnPlayerDisconnect(playerid);
	Death_OnPlayerDisconnect(playerid);
	Corpse_OnPlayerDisconnect(playerid);
	Fraction_OnPlayerDisconnect(playerid);
	Furn_OnPlayerDisconnect(playerid);
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	strglobalclear();
	
	if (!IsPlayerLogged(playerid))
	{
		return 1;
	}
	
	HidePlayerDialog(playerid);
	
	Admin_OnPlayerDeath(playerid, killerid, reason);
	Death_OnPlayerDeath(playerid, killerid, reason);
	TextDraw_OnPlayerDeath(playerid, killerid, reason);
	Vehicle_OnPlayerDeath(playerid, killerid, reason);
	Ren_OnPlayerDeath(playerid, killerid, reason);
	Phone_OnPlayerDeath(playerid, killerid, reason);
	Fraction_OnPlayerDeath(playerid);
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
	strglobalclear();
	
	#if defined __DEBUG
		Test_OnPlayerClickMap(playerid, Float: fX, Float: fY, Float: fZ);
	#endif
	
	Phone_OnPlayerClickMap(playerid, Float: fX, Float: fY, Float: fZ);
	Admin_OnPlayerClickMap(playerid, Float: fX, Float: fY, Float: fZ);
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	strglobalclear();
	
	strreplace(inputtext, '%', '#');
	strreplace(inputtext, '\n', '#');
	
	if (dialogid == INVALID_DIALOG_ID || player_dialog_id[playerid] == INVALID_DIALOG_ID)
	{
		return 1;
	}
	
	if (player_dialog_id[playerid] != dialogid)
	{
		HidePlayerDialog(playerid);
		return 1;
	}
	
	player_dialog_id[playerid] = INVALID_DIALOG_ID;
	
	Player_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Admin_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Inv_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	House_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Vehicle_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	GPS_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Ren_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Furn_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Recyc_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	VehShop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Pay_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Rent_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Phone_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Site_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Bank_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Premise_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Lic_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Bus_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Music_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Gas_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Death_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Corpse_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	GunShop_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Fraction_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	PReception_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Donate_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Autoservice_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	Crime_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	News_OnDialogResponse(playerid, dialogid, response, listitem, inputtext);
	return 1;
}

public OnPlayerText(playerid, text[])
{
	Chat_OnPlayerText(playerid, text);
	return 0;
}

public OnPlayerCommandText(playerid, cmdtext[]) 
{
	return 0;
}

public OnPlayerCommandReceived(playerid, cmdtext[]) 
{
	strglobalclear();
	
	new server_tick = GetTickCount();
	
	if (GetPVarInt(playerid, "CmdTime:Command") > server_tick)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
		return 0;
	}
	
	if (!IsPlayerLogged(playerid)) 
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете использовать команды, пока не авторизуетесь.");
		return 0;
	}
	
	SetPVarInt(playerid, "CmdTime:Command", server_tick + 1000);
	
	return 1;
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success) 
{
	strglobalclear();
	
	if (!success)
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Несуществующая команда. Для помощи используйте " #cPROJECT "Y" #cWHITE ".");
		return 1;
	}
	
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate) 
{	
	strglobalclear();
	Player_OnPlayerStateChange(playerid, newstate, oldstate);
	Vehicle_OnPlayerStateChange(playerid, newstate, oldstate);
	Phone_OnPlayerStateChange(playerid, newstate, oldstate);
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys) 
{
	strglobalclear();
	
	if (!IsPlayerLogged(playerid))
	{
		return 1;
	}
	
	if (!Autoservice_OnPlayerKSC(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Phone_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Menu3D_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Inv_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Ren_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Vehicle_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!House_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Hostel_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Death_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!HGarage_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Enters_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!VehShop_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Rent_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Recyc_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Bank_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Lic_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Premise_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Gas_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!PrBuy_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Fun_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Bus_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!GunShop_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!PReception_OnPlayerKeySC(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Crime_OnPlayerKeyStateChange(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	if (!Fraction_OnPlayerKeyStateC(playerid, newkeys, oldkeys))
	{
		return 1;
	}
	
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText: playertextid)
{
	strglobalclear();
	
	TextDraw_OnPlayerClickPTD(playerid, PlayerText: playertextid);
	Inv_OnPlayerClickPlayerTextDraw(playerid, PlayerText: playertextid);
	Furn_OnPlayerClickPTD(playerid, PlayerText: playertextid);
	VehShop_OnPlayerClickPTD(playerid, PlayerText: playertextid);
	Rent_OnPlayerClickPTD(playerid, PlayerText: playertextid);
	Phone_OnPlayerClickPTD(playerid, PlayerText: playertextid);
	Site_OnPlayerClickPTD(playerid, PlayerText: playertextid);
	Assort_OnPlayerClickPTD(playerid, PlayerText: playertextid);
	PrBuy_OnPlayerClickPTD(playerid, PlayerText: playertextid);
	GunShop_OnPlayerClickPTD(playerid, PlayerText: playertextid);
	Vehicle_OnPlayerClickPTD(playerid, PlayerText: playertextid);
	Fraction_OnPlayerClickPTD(playerid, PlayerText: playertextid);
	return 1;
}

public OnPlayerClickTextDraw(playerid, Text: clickedid)
{
	strglobalclear();

	Inv_OnPlayerClickTextDraw(playerid, Text: clickedid);
	Furn_OnPlayerClickTextDraw(playerid, Text: clickedid);
	Phone_OnPlayerClickTextDraw(playerid, Text: clickedid);
	VehShop_OnPlayerClickTextDraw(playerid, Text: clickedid);
	Rent_OnPlayerClickTextDraw(playerid, Text: clickedid);
	Site_OnPlayerClickTextDraw(playerid, Text: clickedid);
	Assort_OnPlayerClickTextDraw(playerid, Text: clickedid);
	PrBuy_OnPlayerClickTextDraw(playerid, Text: clickedid);
	GunShop_OnPlayerClickTextDraw(playerid, Text: clickedid);
	Vehicle_OnPlayerClickTextDraw(playerid, Text: clickedid);
	Computer_OnPlayerClickTextDraw(playerid, Text: clickedid);
	Fraction_OnPlayerClickTD(playerid, Text: clickedid);
	return 1; 
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz)
{	
	strglobalclear();
	
	if (!IsPlayerLogged(playerid))
	{
		return 1;
	}
	
	MoveDynamicObject(objectid, x, y, z, 10.0, rx, ry, rz);
	
	Inv_OnPlayerEditDynamicObject(playerid, objectid, response, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz);
	Furn_OnPlayerEditDynamicObject(playerid, objectid, response, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz);
	Donate_OnPlayerEditDO(playerid, objectid, response, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz);
	Fraction_OnPlayerEditDO(playerid, objectid, response, Float: x, Float: y, Float: z, Float: rx, Float: ry, Float: rz);
	return 1;
}

public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float: fOffsetX, Float: fOffsetY, Float: fOffsetZ, Float: fRotX, Float: fRotY, Float: fRotZ, Float: fScaleX, Float: fScaleY, Float: fScaleZ)
{
	strglobalclear();
	
	if (!IsPlayerLogged(playerid))
	{
		return 1;
	}
	
	Att_OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float: fOffsetX, Float: fOffsetY, Float: fOffsetZ, Float: fRotX, Float: fRotY, Float: fRotZ, Float: fScaleX, Float: fScaleY, Float: fScaleZ);
	Fraction_OnPlayerEditAO(playerid, response, index, modelid, boneid, Float: fOffsetX, Float: fOffsetY, Float: fOffsetZ, Float: fRotX, Float: fRotY, Float: fRotZ, Float: fScaleX, Float: fScaleY, Float: fScaleZ);
	return 1;
}

public OnVehicleSpawn(vehicleid)
{	
	strglobalclear();
	
	Vehicle_OnVehicleSpawn(vehicleid);
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row) 
{
	strglobalclear();
	
	Admin_OnPlayerSelectedMenuRow(playerid, row);
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	strglobalclear();
	
	if (!IsPlayerLogged(playerid))
	{
		return 1;
	}
	
	GPS_OnPlayerEnterCheckpoint(playerid);
	Phone_OnPlayerEnterCheckpoint(playerid);
	return 1;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float: fX, Float: fY, Float: fZ)
{
	strglobalclear();
	
	if (!IsPlayerLogged(playerid))
	{
		return 0;
	}
	
	if (hittype == BULLET_HIT_TYPE_PLAYER && IsPlayerAfk(hitid))
	{
		return 0;
	}
	
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	strglobalclear();
	
	Death_OnPlayerEnterVehicle(playerid, vehicleid, ispassenger);
	Fraction_OnPlayerEnterVehicle(playerid, vehicleid);
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	strglobalclear();
	
	Fraction_OnPlayerExitVehicle(playerid, vehicleid);
	return 1;
}

public OnPlayerSelectDynamicObject(playerid, objectid, modelid, Float: x, Float: y, Float: z)
{
	strglobalclear();
	
	if (!Furn_OnPlayerSDO(playerid, objectid, modelid, Float: x, Float: y, Float: z))
	{
		return 1;
	}
	
	if (!Fraction_OnPlayerSDO(playerid, objectid, modelid, Float: x, Float: y, Float: z))
	{
		return 1;
	}
	
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	Admin_OnPlayerExitedMenu(playerid);
	return 1;
} 

public OnPlayerEnterDynamicArea(playerid, areaid)
{
	Inv_OnPlayerEnterDynamicArea(playerid, areaid);
	Corpse_OnPlayerEnterDynamicArea(playerid, areaid);
	Phone_OnPlayerEnterDynamicArea(playerid, areaid);
	return 1;
}

public OnPlayerLeaveDynamicArea(playerid, areaid)
{	
	Inv_OnPlayerLeaveDynamicArea(playerid, areaid);
	Corpse_OnPlayerLeaveDynamicArea(playerid, areaid);
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart)
{
	Player_OnPlayerTakeDamage(playerid, issuerid, amount, weaponid, bodypart);
	Death_OnPlayerTakeDamage(playerid, issuerid, amount, weaponid, bodypart);
	return 1;
}

public OnUnoccupiedVehicleUpdate(vehicleid, playerid, passenger_seat, Float:new_x, Float:new_y, Float:new_z, Float:vel_x, Float:vel_y, Float:vel_z)
{	
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	Vehicle_OnVehicleMod(playerid, vehicleid, componentid);
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
    Vehicle_OnVehiclePaintjob(playerid, vehicleid, paintjobid);
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	Vehicle_OnVehicleRespray(playerid, vehicleid, color1, color2);
	return 1;
}	

public OnVehicleDeath(vehicleid, killerid)
{
	Fraction_OnVehicleDeath(vehicleid, killerid);
	return 1;
}


/**
    Custom public events
*/

// Character
function OnCharacterAfterLoad(playerid)
{
    return 1;
}

function OnCharacterBeforeLogout(playerid)
{
    return 1;
}

// Player
function OnPlayerAfterSpawn(playerid)
{
    return 1;
}

function OnPlayerDataReset(playerid, bool: is_relogin)
{
    return 1;
}