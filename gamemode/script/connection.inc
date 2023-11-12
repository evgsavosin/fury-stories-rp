/*!
	@brief Соединение с сервером
	@author Flavo
	@date 25.01.2020
*/

// Constants
const MAX_CONNECTION_TIME = 15,
	  MAX_CONNECTION_IP = 2;

// Structures
enum E_CONNECTION_DATA
{
	c_ip						[MAX_PLAYER_IP],
	c_time
};

// Arrays
new connection_data				[MAX_PLAYERS][E_CONNECTION_DATA];

// Funtions
Connection_OnPlayerConnect(playerid)
{
	// Задержка авторизации (MAX_CONNECTION_TIME == 15 секунд)
	for (new i, time = gettime(); i < MAX_PLAYERS; i++)
	{
		if (isnull(connection_data[i][c_ip]))
		{
			continue;
		}
		
		if (strcmp(GetUserIp(playerid), connection_data[i][c_ip]) == 0
		&& (time - MAX_CONNECTION_TIME) < connection_data[i][c_time])
		{
			pformat:("Перезайдите на сервер через %d секунд.", MAX_CONNECTION_TIME);
			psend:(playerid, C_LIGHTRED);
			
			Kick(playerid);
			break;
		}
	}
	
	// Максимальное подключение с IP-адресов
	new count;
	
	foreach (new i : Player)
	{	
		if (strcmp(GetUserIp(playerid), GetUserIp(i)) == 0)
		{
			count++;
		}
	}
	
	if (count >= MAX_CONNECTION_IP)
	{
		SendClientMessage(playerid, C_LIGHTRED, "Превышен лимит одинаковых IP-адресов на сервере.");
		Kick(playerid);
	}
}

Connection_OnPlayerDisconnect(playerid)
{
	clean:<connection_data[playerid][c_ip]>;
	strcat(connection_data[playerid][c_ip], GetUserIp(playerid), MAX_PLAYER_IP);
	connection_data[playerid][c_time] = gettime();
}