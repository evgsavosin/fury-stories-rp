/*!
	@brief Заголовок для системы разговоров
	@author Found (evg.savosin)
	@date 16.12.2016, update 23.02.2018
*/

#define IsPlayerCalling(%0)			(call_data[%0][c_player_id] != INVALID_PLAYER_ID && call_data[%0][c_index] != INVALID_PARAM)

enum E_CALL_DATA
{
	c_player_id, /// ID Вызываемого
	c_index // Вызываемый Id телефона
};

new call_data			[	MAX_PLAYERS		][	E_CALL_DATA		];


Clear:call_data(playerid)
{
	call_data[playerid][c_index] = INVALID_PARAM;
	call_data[playerid][c_player_id] = INVALID_PLAYER_ID;
}