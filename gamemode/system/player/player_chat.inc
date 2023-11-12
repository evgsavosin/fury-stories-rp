/*!
	@brief —ат игрока (user, account)
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

/// Public function
Chat_OnPlayerText(playerid, text[])
{
	if (!IsPlayerLogged(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !"" ERROR " Для использования чата необходимо авторизоваться.");
		return 0;
	}	
	
	if (IsAdminLogged(playerid))
	{
		cmd_b(playerid, text);
	}
	else 
	{
		new vehicleid = GetPlayerVehicleID(playerid);
		new bool: in_vehicle = (vehicleid != 0 && !HasVehicleClosedSpace(vehicleid) && IsVehicleOpenWindows(vehicleid)),
			character_death = GetCharacterDeath(playerid);
			
		if (character_death == TYPE_DEATH_DIED)
		{
			SendClientMessage(playerid, C_WHITE, !ERROR " Ваш персонаж мёртв.");
			return 0;
		}
		
		// Если разговаривает по телефону
		if (IsPlayerCalling(playerid) && GetPVarInt(playerid, "Phone:CallTime") != 0)
		{
			new targetid = call_data[playerid][c_player_id],
				index = phone_data[call_data[playerid][c_index]][ph_call_index];
				
			new name		[MAX_PLAYER_NAME];

			
			/// Chat
			format:g_small_string("" PHONE_MESSAGE " Неизвестный говорит: %s",
				text
			);
			
			if (in_vehicle)
			{
				SendVehicleMessage(vehicleid, g_small_string);
			}
			else 
			{
				ProxDetector(1.0, targetid, g_small_string, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, COLOR_FADE5, true, true); 
			}
			
			format:g_small_string("%s говорит: %s",
				GetPlayerCurrentName(playerid),
				text
			);
			
			if (in_vehicle)
			{
				SendVehicleMessage(vehicleid, g_small_string);
				SendRPMessage(ACTION_AME, playerid, "Что-то говорит");
			}
			else
			{
				ProxDetector(10.0, playerid, g_small_string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5, true, true);
			}
			
			/// For Player
			format:g_small_string("" PHONE_MESSAGE " %s говорит: %s", 
				GetPlayerCurrentName(playerid),
				text
			);
			
			SendSplitMessage(playerid, COLOR_FADE1, g_small_string);
			
			GetItemListNameOfContact(index, GetPhoneNumber(phone_data[index][ph_call_index]), name);
			format:g_small_string("" PHONE_MESSAGE " %s говорит: %s", 
				name,
				text
			);
			
			SendSplitMessage(targetid, COLOR_FADE1, g_small_string);
			return 0;
		}
		
		if (in_vehicle)
		{		
			format:g_small_string(#VEHICLE_MESSAGE " %s говорит: %s", 
				GetPlayerCurrentName(playerid), 
				text
			);
			
			SendVehicleMessage(vehicleid, g_small_string);
			SendRPMessage(ACTION_AME, playerid, "Что-то говорит");
			return 0;
		}
		
		new house_index = GetHouseAroundOfPlayer(playerid, 6.0, false);
		if (house_index != INVALID_PARAM)
		{
			format:g_small_string(#STREET_MESSAGE " %s говорит: %s",
				GetPlayerCurrentName(playerid), 
				text
			);
			
			SendHouseMessage(house_index, COLOR_FADE2, g_small_string, 8.0);
		}

		format:g_small_string("%s говорит: %s", 
			GetPlayerCurrentName(playerid), 
			text
		);
		
		ProxDetector(20.0, playerid, g_small_string, COLOR_FADE1, COLOR_FADE2, COLOR_FADE3, COLOR_FADE4, COLOR_FADE5);
		
		SetPlayerChatBubble(playerid, text, COLOR_FADE2, 20.0, 7500);
		
		if (HasPlayerAnimStates(playerid) 
		|| IsPlayerInAnyVehicle(playerid) 
		|| character_death == TYPE_DEATH_INJURED)
		{
			return 0;
		}
		
		if (GetCharacterSettings(playerid, SET_TALK) != 0)
		{
			ApplyAnimation(playerid, 
				(GetCharacterSettings(playerid, SET_TALK) == 1) ? ("PED") : ("GANGS"), 
				character_talk_anim[GetCharacterSettings(playerid, SET_TALK)], 
				4.1,
				1, 
				1,
				1, 
				1,
				1, 
				1 
			);
			
			SetTimerEx("OnChatClearAnimation", (strlen(text) * 200 + 1000), false, "i", playerid);
		}
	}
	
	return 0;
}

function OnChatClearAnimation(playerid)
{
	ClearAnimationsEx(playerid);
	return 1;
}

// Other function
SendRPMessage(type, playerid, const action[])
{
	switch(type)
	{
		case ACTION_ME :
		{
			format:g_small_string("* %s %s", 
				GetPlayerCurrentName(playerid), 
				action 
			);
			ProxDetector(20.0, playerid, g_small_string, C_PURPLE, C_PURPLE, C_PURPLE, C_PURPLE, C_PURPLE); 
		}
		
		case ACTION_DO :
		{
			format:g_small_string("* %s (( %s ))", 
				action, 
				GetPlayerCurrentName(playerid)
			);
			
			ProxDetector(20.0, playerid, g_small_string, C_PURPLE, C_PURPLE, C_PURPLE, C_PURPLE, C_PURPLE); 
		}
		
		case ACTION_AME :
		{
			SetPlayerChatBubble(playerid, action, C_PURPLE, 20.0, 5500);
		}
	}
}