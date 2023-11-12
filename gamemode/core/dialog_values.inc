/**
    @brief Dialog values
    @date 24.01.2021
*/

/**
    Constants
*/
const MAX_DIALOG_ITEMS = 100;

/**
    Variables
*/

new g_dialog_select[MAX_PLAYERS][MAX_DIALOG_ITEMS];


/**
    Public function
*/

public OnPlayerConnect(playerid)
{
    ResetPlayerDialogItemsValue(playerid);

    #if defined DV_OnPlayerConnect
        return DV_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define OnPlayerConnect DV_OnPlayerConnect
#if defined DV_OnPlayerConnect
	forward DV_OnPlayerConnect(playerid);
#endif


/**
    Other function
*/
stock GetPlayerDialogItemValue(playerid, index)
{
    return g_dialog_select[playerid][index];
}

stock SetPlayerDialogItemValue(playerid, index, value)
{
    g_dialog_select[playerid][index] = value;
}

stock ResetPlayerDialogItemsValue(playerid)
{
    for (new i; i < sizeof(g_dialog_select[]); i++)
    {
        SetPlayerDialogItemValue(playerid, i, 0);
    }
}