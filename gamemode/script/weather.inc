/*!
	@brief Система погоды
	@author Found (evg.savosin)
	@date 25.04.2019
*/

#define WEATHER_HOUR_TIME		(11)
#define WEATHER_INTERIOR		(1)

#define WEATHER_UPDATE_MINUTE	(30)

new const weather_list[] = 
{
	1, 1, 1, 1, 1, 1, 1, 12, 12, 15, 12, 12, 6, 6, 
	5, 5, 6, 11, 11, 11, 11, 11, 11, 11, 2, 2, 
	14, 14, 14, 14, 11, 11, 11, 11, 1, 1, 1, 1, 
	17, 17, 17, 17, 18, 18, 2, 1, 1, 0, 3, 3 
};

new g_weather = INVALID_PARAM;

// Public function
Weather_OnPlayerConnect(playerid)
{
	Update:player_weather(playerid);
}

Weather_OnGameModeInit() 
{
	DeleteSVar("Weather:UpdateTime");
	GenerateWeather();
	return 1;
}

// Other function
GenerateWeather(index = INVALID_PARAM, minutes = WEATHER_UPDATE_MINUTE)
{	
	new server_tick = GetTickCount();
	
	if (GetSVarInt("Weather:UpdateTime") > server_tick)
	{
		return;
	}
	
	if (g_weather == INVALID_PARAM)
	{
		g_weather = (0 <= index < sizeof weather_list) ? index : random(sizeof weather_list);
	}
	else 
	{
		g_weather = ++g_weather >= sizeof weather_list ? 0 : g_weather;
	}
	
	SetSVarInt("Weather:UpdateTime", server_tick + ((1000 * 60) * minutes));
}	
	
Update:player_weather(playerid)
{
	if (GetPVarInt(playerid, "Player:InInterior")) 
	{
		SetPlayerTime(playerid, WEATHER_HOUR_TIME, 0);
		SetPlayerWeather(playerid, WEATHER_INTERIOR);
	}
	else 
	{
		SetPlayerTime(playerid, g_hour, 0);
		SetPlayerWeather(playerid, weather_list[g_weather]);
	}
}

// Timers
Timer:weather(playerid = INVALID_PLAYER_ID)
{
	if (playerid == INVALID_PLAYER_ID)
	{
		GenerateWeather();
	}
	else 
	{
		Update:player_weather(playerid);
	}
}