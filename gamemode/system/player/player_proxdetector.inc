/*!
	@brief ProxDetector
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

ProxDetector(Float: radi, playerid, text[], col1, col2, col3, col4, col5, 
bool: is_split = true, bool: is_ignore_self = false, bool: is_admin = false, bool: is_ooc = false) 
{
    new Float: pos_x, 
		Float: pos_y,
		Float: pos_z, 		
		Float: radius,
		int = GetPlayerInterior(playerid),
		world = GetPlayerVirtualWorld(playerid);
		
    if (!GetPlayerPos(playerid, pos_x, pos_y, pos_z))
	{
		return 0;
	}
	
	radi = (int || world) ? radi / 2 : radi;
	
	foreach (new i : Player) 
	{	
		if (is_ignore_self && i == playerid)
		{
			continue;
		}
		
		if ((is_admin && GetUserSettings(i, SET_ADMIN_MESSAGE) == 1)
		|| (is_ooc && GetUserSettings(i, SET_B_MESSAGE) == 0))
		{
			continue;
		}
		
		if (world != GetPlayerVirtualWorld(i) || int != GetPlayerInterior(i))
		{
			continue;
		}
		
        if ((radius = GetPlayerDistanceFromPoint(i, pos_x, pos_y, pos_z)) > radi)
		{
			continue;
		}
		
		if (radius < radi / 16) 
		{
			if (is_split) 
			{
				SendSplitMessage(i, col1, text); 
			}
			else 
			{
				SendClientMessage(i, col1, text);
			}
       }
		else if (radius < radi / 8)
		{
			if (is_split) 
			{
				SendSplitMessage(i, col2, text); 
			}
			else 
			{
				SendClientMessage(i, col2, text);
			}
       }
        else if (radius < radi / 4)
		{
			if (is_split) 
			{
				SendSplitMessage(i, col3, text); 
			}
			else 
			{
				SendClientMessage(i, col3, text);
			}
		}
        else if (radius < radi / 2)		
		{
			if (is_split) 
			{
				SendSplitMessage(i, col4, text); 
			}
			else 
			{
				SendClientMessage(i, col4, text);
			}
		}
        else if (radius < radi)		
		{
			if (is_split) 
			{
				SendSplitMessage(i, col5, text); 
			}
			else 
			{
				SendClientMessage(i, col5, text);
			}
		}
   }
	
    return 1;
}