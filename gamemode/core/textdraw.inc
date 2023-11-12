/*!
	@brief Игровой интерфейс (Textdraw)
	@author Found (evg.savosin)
	@date 16.12.2016, update 25.01.2018
*/

#include "textdraw\speedometer"
#include "textdraw\inventory"
#include "textdraw\renovation"
#include "textdraw\select_menu"
#include "textdraw\phone"
#include "textdraw\site"
#include "textdraw\key_alarm"
#include "textdraw\computer"
#include "textdraw\blind"
#include "textdraw\logo"

Include_GlobalTextDraw()
{
	TD_Global_Speedometer();
	TD_Global_Inv();
	TD_Global_Renovation();
	TD_Global_SelectMenu();
	TD_Global_Phone();
	TD_Global_Site();
	TD_Global_KeyAlarm();
	TD_Global_Computer();
	TD_Global_Blind();
	TD_Global_Logo();
}

Include_PlayerTextDraw(playerid)
{
	TD_Player_Speedometer(playerid);
	TD_Player_Inv(playerid);
	TD_Player_Renovation(playerid);
	TD_Player_SelectMenu(playerid);
	TD_Player_Phone(playerid);
	TD_Player_Site(playerid);
	TD_Player_KeyAlarm(playerid);
	TD_Player_Computer(playerid);
}

TextDraw_OnPlayerConnect(playerid)
{
	// Data functions
	Clear:ptd_computer_labels(playerid);
	
	// Show functions
	ShowSpeedometer(playerid, 0);
	ShowInventoryTextdraw(playerid, false);
	ShowFurnList(playerid, 0);
	ShowPhoneTextDraw(playerid, false);
	ShowBrowser(playerid, false);
	ShowKeyAlarm(playerid, false);
	ShowBlind(playerid, false);
	ShowPlayerLogo(playerid, true);
}

TextDraw_OnPlayerDisconnect(playerid, reason)
{
	#pragma unused reason
	
	if (IsPlayerInAnyVehicle(playerid))
	{
		ShowSpeedometer(playerid, 0);
	}
}

TextDraw_OnPlayerDeath(playerid, killerid, reason)
{
	#pragma unused killerid
	#pragma unused reason
	
	if (GetPVarInt(playerid, "SelectMenu:States"))
	{
		ShowFurnList(playerid, 0);
	}
	
	if (GetPVarInt(playerid, "Inventory:States"))
	{
		ShowInventoryTextdraw(playerid, false);
	}
	
	if (IsPlayerInAnyVehicle(playerid))
	{
		ShowSpeedometer(playerid, 0);
	}
	
	if (GetPVarInt(playerid, "Site:States"))
	{
		ShowBrowser(playerid, false);
	}
	
	if (GetPVarInt(playerid, "KeyAlarm:States"))
	{
		ShowKeyAlarm(playerid, false);
	}
	
	return 1;
}

TextDraw_OnPlayerClickPTD(playerid, PlayerText: playertextid)
{
	TD_Player_ComputerClick(playerid, PlayerText: playertextid);
}

// Timers 
Timer:textdraw_minute()
{
	// Site
	TD_UpdateSiteDate();
	
	// Computer
	TD_UpdateComputerDate();
}