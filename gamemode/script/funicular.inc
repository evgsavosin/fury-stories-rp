/*!
	@brief Система фуникулера 
	@author Found (evg.savosin)
	@date 26.04.2018
*/

#define FUN_POS_1	 -1819.6361, -1793.9448, 77.0848
#define FUN_POS_2	 -1964.2053, -1636.7360, 77.4926

// Structures
new const Float: funicular_pos[][] = 
{
	{-1824.071655, -1792.916748, 79.638984, 0.000023, 0.000034, 132.500000},
	{-1964.843261, -1639.290649, 79.638984, 0.000023, 0.000034, 132.500000}
};

enum E_FUNICULAR_DATA
{
	fun_object,
	bool: fun_status,
	bool: fun_is_movement,
	fun_timer
}

new funicular_data[	E_FUNICULAR_DATA];


// Functions
Fun_OnGameModeInit()
{	
	CreatePickupWith3DTextLabel("" #cPROJECT "H", INVALID_PARAM, FUN_POS_1);
	CreatePickupWith3DTextLabel("" #cPROJECT "H", INVALID_PARAM, FUN_POS_2);
	
	funicular_data[fun_object] = CreateObject(
		18879, 
		funicular_pos[0][0],
		funicular_pos[0][1],
		funicular_pos[0][2],
		funicular_pos[0][3],
		funicular_pos[0][4],
		funicular_pos[0][5],
		700.00 
	);
	
	funicular_data[fun_status] = false;
	funicular_data[fun_is_movement] = false;
	funicular_data[fun_timer] = INVALID_PARAM;
}


Fun_OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_CTRL_BACK))
	{
		if (IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, FUN_POS_1)
		|| IsPlayerInRangeOfPoint(playerid, FACTOR_TELEPORT_RADIUS, FUN_POS_2))
		{
			if (funicular_data[fun_is_movement])
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Фуникулер уже находится в движении.");
				return 1;
			}
			
			SetFunicularStates(playerid, !funicular_data[fun_status]);
			return 0;
		}
	}
	
	return 1;
}

SetFunicularStates(playerid, bool: states)
{	
	funicular_data[fun_is_movement] = true;
	SetTimerEx("OnFunicularStates", 1000 * 60, false, "i", states);
	SendRPMessage(ACTION_AME, playerid, "Нажал на пульт");
	ProxDetector(20.0, playerid, "Динамик: Фуникулер будет отправлен через минуту, ожидайте.", C_PURPLE, C_PURPLE, C_PURPLE, C_PURPLE, C_PURPLE);
}

function OnFunicularStates(bool: states)
{
	new ms;
	
	if (states)
	{
		ms = MoveObject(funicular_data[fun_object], 
			funicular_pos[1][0],
			funicular_pos[1][1],
			funicular_pos[1][2],
			2.0, 
			funicular_pos[1][3],
			funicular_pos[1][4],
			funicular_pos[1][5]
		);
	}
	else 
	{
		ms = MoveObject(funicular_data[fun_object], 
			funicular_pos[0][0],
			funicular_pos[0][1],
			funicular_pos[0][2],
			2.0, 
			funicular_pos[0][3],
			funicular_pos[0][4],
			funicular_pos[0][5]
		);
	}

	funicular_data[fun_status] = states;
	funicular_data[fun_timer] = INVALID_PARAM;
	
	SetTimer("OnFunicularMovement", ms, false);
}

function OnFunicularMovement()
{
	funicular_data[fun_is_movement] = false;
}