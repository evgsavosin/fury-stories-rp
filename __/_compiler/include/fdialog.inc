/*
*
* @Author: Found
* @Version: 1.0
* @Realesed: 06.07.2016
*
*/

#include <a_samp>

#define MAX_FUNCTION_NAME	(32)

#if !defined FDIALOG_REDEFINE_RESPONSE
	#define FDIALOG_REDEFINE_RESPONSE true
#else
	#undef FDIALOG_REDEFINE_RESPONSE
#endif

#if defined fdialog_included
	#endinput
#else
	#define fdialog_included
#endif

#define DLG_RESPONSE:%0(%1) \
	forward _fd%0(%1);\
	public _fd%0(%1)

#define DLG_SHOW:<%0>(%1) fdialog_s_%0(%1)

#define FDIALOG_ID 	(0xFFFF)

	
static bool: f_g_performed = false,
	   bool: f_g_received = false;

static f_g_dialog	[MAX_PLAYERS][MAX_FUNCTION_NAME];

	
forward OnDialogPerformed(playerid, success);
forward OnDialogReceived(playerid);

#if defined FILTERSCRIPT

public OnFilterScriptInit()
{
	f_g_performed = funcidx("OnDialogPerformed") != -1;
	f_g_received = funcidx("OnDialogReceived") != -1;
    return CallLocalFunction("fdialog_OnFilterScriptInit", "");
}

#if defined _ALS_OnFilterScriptInit
    #undef OnFilterScriptInit
#else
    #define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit fdialog_OnFilterScriptInit

forward fdialog_OnFilterScriptInit();

#else

public OnGameModeInit()
{
	f_g_performed = funcidx("OnDialogPerformed") != -1;
	f_g_received = funcidx("OnDialogReceived") != -1;
	
	if (funcidx("fdialog_OnGameModeInit") != -1)
	{
		return CallLocalFunction("fdialog_OnGameModeInit", "");
	}

	return 1;
}

#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit fdialog_OnGameModeInit
forward fdialog_OnGameModeInit();


stock fdialog_ShowPlayerDialog(playerid, function[], style, caption[], info[], button1[], button2[])
{
	if (!f_g_received)
	{
		print("[fdialog][Exception]: OnDialogReceived not defined.");
		return 1;
	}

	f_g_dialog[playerid] = "_fd";
	strcat(f_g_dialog[playerid], function, MAX_FUNCTION_NAME);

	CallLocalFunction("OnDialogReceived", "ii", playerid);

	return ShowPlayerDialog(playerid, FDIALOG_ID, style, caption, info, button1, button2);
}

#define ShowPlayerDialogEx fdialog_ShowPlayerDialog

#if defined FDIALOG_REDEFINE_RESPONSE
	public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
#else
	fdialog_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
#endif
{
	if (dialogid != FDIALOG_ID)
	{
		return 0;
	}

	if (!f_g_performed)
	{
		print("[fdialog][Exception]: OnDialogPerformed not defined.");
		return 1;
	}

	new _f_function_exists;

	_f_function_exists = funcidx(f_g_dialog[playerid]) != -1 ? 1 : 0;

	if (_f_function_exists != 0)
	{
		CallLocalFunction(f_g_dialog[playerid] , "iiis", playerid, response, listitem, (inputtext[0] == EOS) ? ("\1") : inputtext);
	}

	return CallLocalFunction("OnDialogPerformed" , "ii", playerid, _f_function_exists);
}

#if defined FDIALOG_REDEFINE_RESPONSE
	#if defined _ALS_OnDialogResponse
	    #undef OnDialogResponse
	#else
	    #define _ALS_OnDialogResponse
	#endif

	#define OnDialogResponse	fdialog_OnDialogResponse

	forward fdialog_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[]);
#endif