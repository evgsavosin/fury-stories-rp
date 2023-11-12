/*!
	@brief Текстдравы брелка автосигнализации
	@author Found (evg.savosin)
	@date 25.11.2019
*/

// Defines 
#define IsKeyAlarmShowed(%0)		GetPVarInt(%0,"KeyAlarm:States")

enum PlayerText:
{
	PTD_KA_START = 0,
	PTD_KA_ICON_ENGINE = PTD_KA_START,
	PTD_KA_ICON_LOCK,
	PTD_KA_ICON_BOOT_1,
	PTD_KA_ICON_BOOT_2,
	PTD_KA_ICON_BOOT_3,
	PTD_KA_ICON_BOOT_4,
	PTD_KA_END
};

new Text: td_key_alarm				[27],
	PlayerText: ptd_key_alarm		[MAX_PLAYERS][PTD_KA_END];

ShowKeyAlarm(playerid, states, vehicleid = 0)
{
	if (states)
	{
		if (IsInterfaceActive(playerid))
		{
			return 0;
		}
		
		SelectTextDraw(playerid, 0x7CAD81FF);
		
		for (new i; i < sizeof td_key_alarm; i++)
		{
			TextDrawShowForPlayer(playerid, td_key_alarm[i]);
			
			if (i < _: PTD_KA_END)
			{
				PlayerTextDrawShow(playerid, ptd_key_alarm[playerid][PlayerText: i]);
			}
		}
	}
	else 
	{
		for (new i; i < sizeof td_key_alarm; i++)
		{
			TextDrawHideForPlayer(playerid, td_key_alarm[i]);
			
			if (i < _: PTD_KA_END)
			{
				PlayerTextDrawHide(playerid, ptd_key_alarm[playerid][PlayerText: i]);
			}
		}
		
		SetPVarInt(playerid, "KeyAlarm:Progress", 0);
	}
	
	SetPVarInt(playerid, "KeyAlarm:VehicleId", vehicleid);
	SetPVarInt(playerid, "KeyAlarm:States", states);
	return 1;
}

TD_Global_KeyAlarm()
{
	td_key_alarm[0] = TextDrawCreate(431.594390, 260.816680, ""); //  
	TextDrawLetterSize(td_key_alarm[0], 0.000000, 0.000000);
	TextDrawTextSize(td_key_alarm[0], 202.000000, 117.000000);
	TextDrawAlignment(td_key_alarm[0], 1);
	TextDrawColor(td_key_alarm[0], 1179010815);
	TextDrawSetShadow(td_key_alarm[0], 0);
	TextDrawSetOutline(td_key_alarm[0], 0);
	TextDrawBackgroundColor(td_key_alarm[0], 0);
	TextDrawFont(td_key_alarm[0], 5);
	TextDrawSetProportional(td_key_alarm[0], 0);
	TextDrawSetShadow(td_key_alarm[0], 0);
	TextDrawSetPreviewModel(td_key_alarm[0], 18875);
	TextDrawSetPreviewRot(td_key_alarm[0], 90.000000, 360.000000, 90.000000, 1.000000);

	td_key_alarm[1] = TextDrawCreate(466.605743, 287.332702, ""); //  
	TextDrawLetterSize(td_key_alarm[1], 0.000000, 0.000000);
	TextDrawTextSize(td_key_alarm[1], 49.000000, 28.000000);
	TextDrawAlignment(td_key_alarm[1], 1);
	TextDrawColor(td_key_alarm[1], 1179010815);
	TextDrawSetShadow(td_key_alarm[1], 0);
	TextDrawSetOutline(td_key_alarm[1], 0);
	TextDrawBackgroundColor(td_key_alarm[1], 0);
	TextDrawFont(td_key_alarm[1], 5);
	TextDrawSetProportional(td_key_alarm[1], 0);
	TextDrawSetShadow(td_key_alarm[1], 0);
	TextDrawSetPreviewModel(td_key_alarm[1], 18875);
	TextDrawSetPreviewRot(td_key_alarm[1], 90.000000, 360.000000, 90.000000, 1.000000);

	td_key_alarm[2] = TextDrawCreate(559.758789, 329.866973, "LD_BEAT:chit"); //  
	TextDrawLetterSize(td_key_alarm[2], 0.000000, 0.000000);
	TextDrawTextSize(td_key_alarm[2], 7.000000, 9.000000);
	TextDrawAlignment(td_key_alarm[2], 1);
	TextDrawColor(td_key_alarm[2], -1700291329);
	TextDrawSetShadow(td_key_alarm[2], 0);
	TextDrawSetOutline(td_key_alarm[2], 0);
	TextDrawBackgroundColor(td_key_alarm[2], 255);
	TextDrawFont(td_key_alarm[2], 4);
	TextDrawSetProportional(td_key_alarm[2], 0);
	TextDrawSetShadow(td_key_alarm[2], 0);

	td_key_alarm[3] = TextDrawCreate(434.882202, 262.916748, ""); //  
	TextDrawLetterSize(td_key_alarm[3], 0.000000, 0.000000);
	TextDrawTextSize(td_key_alarm[3], 196.000000, 113.000000);
	TextDrawAlignment(td_key_alarm[3], 1);
	TextDrawColor(td_key_alarm[3], -1061109505);
	TextDrawSetShadow(td_key_alarm[3], 0);
	TextDrawSetOutline(td_key_alarm[3], 0);
	TextDrawBackgroundColor(td_key_alarm[3], -1061109760);
	TextDrawFont(td_key_alarm[3], 5);
	TextDrawSetProportional(td_key_alarm[3], 0);
	TextDrawSetShadow(td_key_alarm[3], 0);
	TextDrawSetPreviewModel(td_key_alarm[3], 18875);
	TextDrawSetPreviewRot(td_key_alarm[3], 90.000000, 360.000000, 90.000000, 1.000000);

	td_key_alarm[4] = TextDrawCreate(507.882202, 303.166656, "box"); //  
	TextDrawLetterSize(td_key_alarm[4], 0.000000, 3.411761);
	TextDrawTextSize(td_key_alarm[4], 563.000000, -72.000000);
	TextDrawAlignment(td_key_alarm[4], 1);
	TextDrawColor(td_key_alarm[4], -1129857793);
	TextDrawUseBox(td_key_alarm[4], 1);
	TextDrawBoxColor(td_key_alarm[4], -1700291329);
	TextDrawSetShadow(td_key_alarm[4], 0);
	TextDrawSetOutline(td_key_alarm[4], 0);
	TextDrawBackgroundColor(td_key_alarm[4], 255);
	TextDrawFont(td_key_alarm[4], 1);
	TextDrawSetProportional(td_key_alarm[4], 1);
	TextDrawSetShadow(td_key_alarm[4], 0);

	td_key_alarm[5] = TextDrawCreate(503.669921, 329.866973, "LD_BEAT:chit"); //  
	TextDrawLetterSize(td_key_alarm[5], 0.000000, 0.000000);
	TextDrawTextSize(td_key_alarm[5], 7.000000, 9.000000);
	TextDrawAlignment(td_key_alarm[5], 1);
	TextDrawColor(td_key_alarm[5], -1700291329);
	TextDrawSetShadow(td_key_alarm[5], 0);
	TextDrawSetOutline(td_key_alarm[5], 0);
	TextDrawBackgroundColor(td_key_alarm[5], 255);
	TextDrawFont(td_key_alarm[5], 4);
	TextDrawSetProportional(td_key_alarm[5], 0);
	TextDrawSetShadow(td_key_alarm[5], 0);

	td_key_alarm[6] = TextDrawCreate(509.482299, 339.716674, "box"); //  
	TextDrawLetterSize(td_key_alarm[6], 0.000000, -0.776471);
	TextDrawTextSize(td_key_alarm[6], 561.989013, -121.000000);
	TextDrawAlignment(td_key_alarm[6], 1);
	TextDrawColor(td_key_alarm[6], -1129857793);
	TextDrawUseBox(td_key_alarm[6], 1);
	TextDrawBoxColor(td_key_alarm[6], -1700291329);
	TextDrawSetShadow(td_key_alarm[6], 0);
	TextDrawSetOutline(td_key_alarm[6], 0);
	TextDrawBackgroundColor(td_key_alarm[6], 255);
	TextDrawFont(td_key_alarm[6], 1);
	TextDrawSetProportional(td_key_alarm[6], 1);
	TextDrawSetShadow(td_key_alarm[6], 0);

	td_key_alarm[7] = TextDrawCreate(503.440460, 298.165039, "LD_BEAT:chit"); //  
	TextDrawLetterSize(td_key_alarm[7], 0.000000, 0.000000);
	TextDrawTextSize(td_key_alarm[7], 7.000000, 9.000000);
	TextDrawAlignment(td_key_alarm[7], 1);
	TextDrawColor(td_key_alarm[7], -1700291329);
	TextDrawSetShadow(td_key_alarm[7], 0);
	TextDrawSetOutline(td_key_alarm[7], 0);
	TextDrawBackgroundColor(td_key_alarm[7], 255);
	TextDrawFont(td_key_alarm[7], 4);
	TextDrawSetProportional(td_key_alarm[7], 0);
	TextDrawSetShadow(td_key_alarm[7], 0);

	td_key_alarm[8] = TextDrawCreate(506.658905, 305.782623, "box"); //  
	TextDrawLetterSize(td_key_alarm[8], 0.000000, 2.775938);
	TextDrawTextSize(td_key_alarm[8], 506.000000, -79.000000);
	TextDrawAlignment(td_key_alarm[8], 1);
	TextDrawColor(td_key_alarm[8], -1129857793);
	TextDrawUseBox(td_key_alarm[8], 1);
	TextDrawBoxColor(td_key_alarm[8], -1700291329);
	TextDrawSetShadow(td_key_alarm[8], 0);
	TextDrawSetOutline(td_key_alarm[8], 0);
	TextDrawBackgroundColor(td_key_alarm[8], 255);
	TextDrawFont(td_key_alarm[8], 1);
	TextDrawSetProportional(td_key_alarm[8], 1);
	TextDrawSetShadow(td_key_alarm[8], 0);

	td_key_alarm[9] = TextDrawCreate(559.758789, 298.265045, "LD_BEAT:chit"); //  
	TextDrawLetterSize(td_key_alarm[9], 0.000000, 0.000000);
	TextDrawTextSize(td_key_alarm[9], 7.000000, 9.000000);
	TextDrawAlignment(td_key_alarm[9], 1);
	TextDrawColor(td_key_alarm[9], -1700291329);
	TextDrawSetShadow(td_key_alarm[9], 0);
	TextDrawSetOutline(td_key_alarm[9], 0);
	TextDrawBackgroundColor(td_key_alarm[9], 255);
	TextDrawFont(td_key_alarm[9], 4);
	TextDrawSetProportional(td_key_alarm[9], 0);
	TextDrawSetShadow(td_key_alarm[9], 0);

	td_key_alarm[10] = TextDrawCreate(567.264648, 304.615844, "box"); //  
	TextDrawLetterSize(td_key_alarm[10], 0.000000, 2.893932);
	TextDrawTextSize(td_key_alarm[10], 557.900024, -79.000000);
	TextDrawAlignment(td_key_alarm[10], 1);
	TextDrawColor(td_key_alarm[10], -1129857793);
	TextDrawUseBox(td_key_alarm[10], 1);
	TextDrawBoxColor(td_key_alarm[10], -1700291329);
	TextDrawSetShadow(td_key_alarm[10], 0);
	TextDrawSetOutline(td_key_alarm[10], 0);
	TextDrawBackgroundColor(td_key_alarm[10], 255);
	TextDrawFont(td_key_alarm[10], 1);
	TextDrawSetProportional(td_key_alarm[10], 1);
	TextDrawSetShadow(td_key_alarm[10], 0);

	td_key_alarm[11] = TextDrawCreate(509.259246, 301.982574, "box"); //  
	TextDrawLetterSize(td_key_alarm[11], 0.000000, -0.117830);
	TextDrawTextSize(td_key_alarm[11], 560.899291, -114.000000);
	TextDrawAlignment(td_key_alarm[11], 1);
	TextDrawColor(td_key_alarm[11], -1129857793);
	TextDrawUseBox(td_key_alarm[11], 1);
	TextDrawBoxColor(td_key_alarm[11], -1700291329);
	TextDrawSetShadow(td_key_alarm[11], 0);
	TextDrawSetOutline(td_key_alarm[11], 0);
	TextDrawBackgroundColor(td_key_alarm[11], 255);
	TextDrawFont(td_key_alarm[11], 1);
	TextDrawSetProportional(td_key_alarm[11], 1);
	TextDrawSetShadow(td_key_alarm[11], 0);

	td_key_alarm[12] = TextDrawCreate(502.329315, 300.250030, "particle:lamp_shad_64"); //  
	TextDrawLetterSize(td_key_alarm[12], 0.000000, 0.000000);
	TextDrawTextSize(td_key_alarm[12], 65.000000, 37.000000);
	TextDrawAlignment(td_key_alarm[12], 1);
	TextDrawColor(td_key_alarm[12], -103);
	TextDrawSetShadow(td_key_alarm[12], 0);
	TextDrawSetOutline(td_key_alarm[12], 0);
	TextDrawBackgroundColor(td_key_alarm[12], 255);
	TextDrawFont(td_key_alarm[12], 4);
	TextDrawSetProportional(td_key_alarm[12], 0);
	TextDrawSetShadow(td_key_alarm[12], 0);

	td_key_alarm[13] = TextDrawCreate(506.758758, 316.601135, "box"); //  
	TextDrawLetterSize(td_key_alarm[13], 0.000000, -0.447059);
	TextDrawTextSize(td_key_alarm[13], 538.000000, -125.000000);
	TextDrawAlignment(td_key_alarm[13], 1);
	TextDrawColor(td_key_alarm[13], 255);
	TextDrawUseBox(td_key_alarm[13], 1);
	TextDrawBoxColor(td_key_alarm[13], 65);
	TextDrawSetShadow(td_key_alarm[13], 0);
	TextDrawSetOutline(td_key_alarm[13], 0);
	TextDrawBackgroundColor(td_key_alarm[13], 255);
	TextDrawFont(td_key_alarm[13], 1);
	TextDrawSetProportional(td_key_alarm[13], 1);
	TextDrawSetShadow(td_key_alarm[13], 0);

	td_key_alarm[14] = TextDrawCreate(506.648254, 303.817413, "22:00"); //  
	TextDrawLetterSize(td_key_alarm[14], 0.169881, 0.794999);
	TextDrawAlignment(td_key_alarm[14], 1);
	TextDrawColor(td_key_alarm[14], 90);
	TextDrawSetShadow(td_key_alarm[14], 0);
	TextDrawSetOutline(td_key_alarm[14], 0);
	TextDrawBackgroundColor(td_key_alarm[14], 255);
	TextDrawFont(td_key_alarm[14], 1);
	TextDrawSetProportional(td_key_alarm[14], 1);
	TextDrawSetShadow(td_key_alarm[14], 0);

	td_key_alarm[15] = TextDrawCreate(495.738067, 293.482330, ""); //  
	TextDrawLetterSize(td_key_alarm[15], 0.000000, 0.000000);
	TextDrawTextSize(td_key_alarm[15], 45.000000, 64.000000);
	TextDrawAlignment(td_key_alarm[15], 1);
	TextDrawColor(td_key_alarm[15], -179);
	TextDrawSetShadow(td_key_alarm[15], 0);
	TextDrawSetOutline(td_key_alarm[15], 0);
	TextDrawBackgroundColor(td_key_alarm[15], 0);
	TextDrawFont(td_key_alarm[15], 5);
	TextDrawSetProportional(td_key_alarm[15], 0);
	TextDrawSetShadow(td_key_alarm[15], 0);
	TextDrawSetPreviewModel(td_key_alarm[15], 560);
	TextDrawSetPreviewRot(td_key_alarm[15], 0.000000, 0.000000, 30.000000, 1.000000);
	TextDrawSetPreviewVehCol(td_key_alarm[15], 0, 1);

	td_key_alarm[16] = TextDrawCreate(541.582031, 301.968170, "box"); //  
	TextDrawLetterSize(td_key_alarm[16], 0.000000, 3.788233);
	TextDrawTextSize(td_key_alarm[16], 538.249938, -72.000000);
	TextDrawAlignment(td_key_alarm[16], 1);
	TextDrawColor(td_key_alarm[16], 255);
	TextDrawUseBox(td_key_alarm[16], 1);
	TextDrawBoxColor(td_key_alarm[16], 65);
	TextDrawSetShadow(td_key_alarm[16], 0);
	TextDrawSetOutline(td_key_alarm[16], 0);
	TextDrawBackgroundColor(td_key_alarm[16], 255);
	TextDrawFont(td_key_alarm[16], 1);
	TextDrawSetProportional(td_key_alarm[16], 1);
	TextDrawSetShadow(td_key_alarm[16], 0);

	td_key_alarm[17] = TextDrawCreate(527.347106, 305.966400, "box"); //  
	TextDrawLetterSize(td_key_alarm[17], 0.000000, 0.305880);
	TextDrawTextSize(td_key_alarm[17], 535.001342, -121.000000);
	TextDrawAlignment(td_key_alarm[17], 1);
	TextDrawColor(td_key_alarm[17], -1);
	TextDrawUseBox(td_key_alarm[17], 1);
	TextDrawBoxColor(td_key_alarm[17], 79);
	TextDrawSetShadow(td_key_alarm[17], 0);
	TextDrawSetOutline(td_key_alarm[17], 0);
	TextDrawBackgroundColor(td_key_alarm[17], 255);
	TextDrawFont(td_key_alarm[17], 1);
	TextDrawSetProportional(td_key_alarm[17], 1);
	TextDrawSetShadow(td_key_alarm[17], 0);

	td_key_alarm[18] = TextDrawCreate(528.396850, 306.816192, "box"); //  
	TextDrawLetterSize(td_key_alarm[18], 0.000000, 0.100822);
	TextDrawTextSize(td_key_alarm[18], 534.029724, -121.000000);
	TextDrawAlignment(td_key_alarm[18], 1);
	TextDrawColor(td_key_alarm[18], -1);
	TextDrawUseBox(td_key_alarm[18], 1);
	TextDrawBoxColor(td_key_alarm[18], -1296059137);
	TextDrawSetShadow(td_key_alarm[18], 0);
	TextDrawSetOutline(td_key_alarm[18], 0);
	TextDrawBackgroundColor(td_key_alarm[18], 255);
	TextDrawFont(td_key_alarm[18], 1);
	TextDrawSetProportional(td_key_alarm[18], 1);
	TextDrawSetShadow(td_key_alarm[18], 0);

	td_key_alarm[19] = TextDrawCreate(528.653747, 307.799438, "box"); //  
	TextDrawLetterSize(td_key_alarm[19], 0.000000, -0.100648);
	TextDrawTextSize(td_key_alarm[19], 527.354492, -129.000000);
	TextDrawAlignment(td_key_alarm[19], 1);
	TextDrawColor(td_key_alarm[19], -1);
	TextDrawUseBox(td_key_alarm[19], 1);
	TextDrawBoxColor(td_key_alarm[19], 79);
	TextDrawSetShadow(td_key_alarm[19], 0);
	TextDrawSetOutline(td_key_alarm[19], 0);
	TextDrawBackgroundColor(td_key_alarm[19], 255);
	TextDrawFont(td_key_alarm[19], 1);
	TextDrawSetProportional(td_key_alarm[19], 1);
	TextDrawSetShadow(td_key_alarm[19], 0);

	td_key_alarm[20] = TextDrawCreate(531.703002, 307.799438, "box"); //  
	TextDrawLetterSize(td_key_alarm[20], 0.000000, -0.100648);
	TextDrawTextSize(td_key_alarm[20], 530.403747, -129.000000);
	TextDrawAlignment(td_key_alarm[20], 1);
	TextDrawColor(td_key_alarm[20], -1);
	TextDrawUseBox(td_key_alarm[20], 1);
	TextDrawBoxColor(td_key_alarm[20], 79);
	TextDrawSetShadow(td_key_alarm[20], 0);
	TextDrawSetOutline(td_key_alarm[20], 0);
	TextDrawBackgroundColor(td_key_alarm[20], 255);
	TextDrawFont(td_key_alarm[20], 1);
	TextDrawSetProportional(td_key_alarm[20], 1);
	TextDrawSetShadow(td_key_alarm[20], 0);

	td_key_alarm[21] = TextDrawCreate(534.752258, 307.799438, "box"); //  
	TextDrawLetterSize(td_key_alarm[21], 0.000000, -0.100648);
	TextDrawTextSize(td_key_alarm[21], 533.453002, -129.000000);
	TextDrawAlignment(td_key_alarm[21], 1);
	TextDrawColor(td_key_alarm[21], -1);
	TextDrawUseBox(td_key_alarm[21], 1);
	TextDrawBoxColor(td_key_alarm[21], 79);
	TextDrawSetShadow(td_key_alarm[21], 0);
	TextDrawSetOutline(td_key_alarm[21], 0);
	TextDrawBackgroundColor(td_key_alarm[21], 255);
	TextDrawFont(td_key_alarm[21], 1);
	TextDrawSetProportional(td_key_alarm[21], 1);
	TextDrawSetShadow(td_key_alarm[21], 0);

	td_key_alarm[22] = TextDrawCreate(577.058776, 306.666595, "box"); //  
	TextDrawLetterSize(td_key_alarm[22], 0.000000, 0.023528);
	TextDrawTextSize(td_key_alarm[22], 580.000000, -120.000000);
	TextDrawAlignment(td_key_alarm[22], 1);
	TextDrawColor(td_key_alarm[22], -1);
	TextDrawUseBox(td_key_alarm[22], 1);
	TextDrawBoxColor(td_key_alarm[22], -1061109505);
	TextDrawSetShadow(td_key_alarm[22], 0);
	TextDrawSetOutline(td_key_alarm[22], 0);
	TextDrawBackgroundColor(td_key_alarm[22], 255);
	TextDrawFont(td_key_alarm[22], 1);
	TextDrawSetProportional(td_key_alarm[22], 1);
	TextDrawSetShadow(td_key_alarm[22], 0);

	td_key_alarm[23] = TextDrawCreate(577.941101, 303.166564, "LD_BEAT:chit"); //  
	TextDrawLetterSize(td_key_alarm[23], 0.000000, 0.000000);
	TextDrawTextSize(td_key_alarm[23], 6.000000, 7.000000);
	TextDrawAlignment(td_key_alarm[23], 1);
	TextDrawColor(td_key_alarm[23], -1061109505);
	TextDrawSetShadow(td_key_alarm[23], 0);
	TextDrawSetOutline(td_key_alarm[23], 0);
	TextDrawBackgroundColor(td_key_alarm[23], 255);
	TextDrawFont(td_key_alarm[23], 4);
	TextDrawSetProportional(td_key_alarm[23], 0);
	TextDrawSetShadow(td_key_alarm[23], 0);

	td_key_alarm[24] = TextDrawCreate(576.929565, 309.500000, "box"); //  
	TextDrawLetterSize(td_key_alarm[24], 0.000000, -0.286823);
	TextDrawTextSize(td_key_alarm[24], 580.185791, -128.000000);
	TextDrawAlignment(td_key_alarm[24], 1);
	TextDrawColor(td_key_alarm[24], -2139062017);
	TextDrawUseBox(td_key_alarm[24], 1);
	TextDrawBoxColor(td_key_alarm[24], -2139062090);
	TextDrawSetShadow(td_key_alarm[24], 0);
	TextDrawSetOutline(td_key_alarm[24], 0);
	TextDrawBackgroundColor(td_key_alarm[24], 255);
	TextDrawFont(td_key_alarm[24], 1);
	TextDrawSetProportional(td_key_alarm[24], 1);
	TextDrawSetShadow(td_key_alarm[24], 0);

	td_key_alarm[25] = TextDrawCreate(579.140808, 305.183380, "LD_BEAT:chit"); //  
	TextDrawLetterSize(td_key_alarm[25], 0.000000, 0.000000);
	TextDrawTextSize(td_key_alarm[25], 3.430000, 3.400000);
	TextDrawAlignment(td_key_alarm[25], 1);
	TextDrawColor(td_key_alarm[25], 109);
	TextDrawSetShadow(td_key_alarm[25], 0);
	TextDrawSetOutline(td_key_alarm[25], 0);
	TextDrawBackgroundColor(td_key_alarm[25], 255);
	TextDrawFont(td_key_alarm[25], 4);
	TextDrawSetProportional(td_key_alarm[25], 0);
	TextDrawSetShadow(td_key_alarm[25], 0);

	td_key_alarm[26] = TextDrawCreate(498.400024, 311.533264, "T~n~R~n~K"); //  
	TextDrawLetterSize(td_key_alarm[26], 0.174116, 0.526665);
	TextDrawAlignment(td_key_alarm[26], 1);
	TextDrawColor(td_key_alarm[26], -1061109505);
	TextDrawSetShadow(td_key_alarm[26], 0);
	TextDrawSetOutline(td_key_alarm[26], 0);
	TextDrawBackgroundColor(td_key_alarm[26], 255);
	TextDrawFont(td_key_alarm[26], 0);
	TextDrawSetProportional(td_key_alarm[26], 1);
	TextDrawSetShadow(td_key_alarm[26], 0);
}

TD_Player_KeyAlarm(playerid)
{
	new PlayerText: ptd;
	
	ptd_key_alarm[playerid][PTD_KA_ICON_ENGINE] = CreatePlayerTextDraw(playerid, 543.034118, 298.250366, ""); // Engine-hover 
	PlayerTextDrawLetterSize(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_ENGINE], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_ENGINE], 18.000000, 15.000000);
	PlayerTextDrawAlignment(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_ENGINE], 1);
	PlayerTextDrawColor(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_ENGINE], 98);
	PlayerTextDrawSetShadow(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_ENGINE], 0);
	PlayerTextDrawSetOutline(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_ENGINE], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_ENGINE], 0);
	PlayerTextDrawFont(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_ENGINE], 5);
	PlayerTextDrawSetProportional(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_ENGINE], 0);
	PlayerTextDrawSetShadow(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_ENGINE], 0);
	PlayerTextDrawSetPreviewModel(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_ENGINE], 11746);
	PlayerTextDrawSetPreviewRot(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_ENGINE], 180.000000, 0.000000, 180.000000, 0.400000);
	PlayerTextDrawSetSelectable(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_ENGINE], true);

	ptd_key_alarm[playerid][PTD_KA_ICON_LOCK] = CreatePlayerTextDraw(playerid, 545.063720, 312.150024, ""); // Lock-hover 
	PlayerTextDrawLetterSize(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_LOCK], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_LOCK], 13.000000, 13.000000);
	PlayerTextDrawAlignment(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_LOCK], 1);
	PlayerTextDrawColor(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_LOCK], 103);
	PlayerTextDrawSetShadow(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_LOCK], 0);
	PlayerTextDrawSetOutline(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_LOCK], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_LOCK], 0);
	PlayerTextDrawFont(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_LOCK], 5);
	PlayerTextDrawSetProportional(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_LOCK], 0);
	PlayerTextDrawSetShadow(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_LOCK], 0);
	PlayerTextDrawSetPreviewModel(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_LOCK], 19804);
	PlayerTextDrawSetPreviewRot(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_LOCK], 0.000000, 0.000000, 0.000000, 0.600000);
	PlayerTextDrawSetSelectable(playerid, ptd_key_alarm[playerid][PTD_KA_ICON_LOCK], true);
	
	ptd_key_alarm[playerid][PTD_KA_ICON_BOOT_1] = ptd = CreatePlayerTextDraw(playerid, 547.564941, 327.083343, ""); // Boot 
	PlayerTextDrawLetterSize(playerid, ptd, 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, ptd, 13.000000, 9.000000);
	PlayerTextDrawAlignment(playerid, ptd, 1);
	PlayerTextDrawColor(playerid, ptd, 105);
	PlayerTextDrawSetShadow(playerid, ptd, 0);
	PlayerTextDrawSetOutline(playerid, ptd, 0);
	PlayerTextDrawBackgroundColor(playerid, ptd, 0);
	PlayerTextDrawFont(playerid, ptd, 5);
	PlayerTextDrawSetProportional(playerid, ptd, 0);
	PlayerTextDrawSetShadow(playerid, ptd, 0);
	PlayerTextDrawSetPreviewModel(playerid, ptd, 2187);
	PlayerTextDrawSetPreviewRot(playerid, ptd, 0.000000, 0.000000, -90.000000, 1.500000);
	PlayerTextDrawSetSelectable(playerid, ptd, true);

	ptd_key_alarm[playerid][PTD_KA_ICON_BOOT_2] = ptd = CreatePlayerTextDraw(playerid, 553.629150, 329.233245, "LD_BEAT:chit"); // Boot 
	PlayerTextDrawLetterSize(playerid, ptd, 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, ptd, 2.000000, 6.000000);
	PlayerTextDrawAlignment(playerid, ptd, 1);
	PlayerTextDrawColor(playerid, ptd, 102);
	PlayerTextDrawSetShadow(playerid, ptd, 0);
	PlayerTextDrawSetOutline(playerid, ptd, 0);
	PlayerTextDrawBackgroundColor(playerid, ptd, 255);
	PlayerTextDrawFont(playerid, ptd, 4);
	PlayerTextDrawSetProportional(playerid, ptd, 0);
	PlayerTextDrawSetShadow(playerid, ptd, 0);

	ptd_key_alarm[playerid][PTD_KA_ICON_BOOT_3] = ptd = CreatePlayerTextDraw(playerid, 548.723388, 331.533203, "LD_BEAT:chit"); // Boot 
	PlayerTextDrawLetterSize(playerid, ptd, 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, ptd, 5.000000, 4.000000);
	PlayerTextDrawAlignment(playerid, ptd, 1);
	PlayerTextDrawColor(playerid, ptd, -112);
	PlayerTextDrawSetShadow(playerid, ptd, 0);
	PlayerTextDrawSetOutline(playerid, ptd, 0);
	PlayerTextDrawBackgroundColor(playerid, ptd, 255);
	PlayerTextDrawFont(playerid, ptd, 4);
	PlayerTextDrawSetProportional(playerid, ptd, 0);
	PlayerTextDrawSetShadow(playerid, ptd, 0);

	ptd_key_alarm[playerid][PTD_KA_ICON_BOOT_4] = ptd = CreatePlayerTextDraw(playerid, 553.100219, 327.049865, "/"); // Boot 
	PlayerTextDrawLetterSize(playerid, ptd, 0.200470, 0.398333);
	PlayerTextDrawTextSize(playerid, ptd, -31.000000, -26.000000);
	PlayerTextDrawAlignment(playerid, ptd, 2);
	PlayerTextDrawColor(playerid, ptd, 127);
	PlayerTextDrawUseBox(playerid, ptd, 1);
	PlayerTextDrawBoxColor(playerid, ptd, 0);
	PlayerTextDrawSetShadow(playerid, ptd, 0);
	PlayerTextDrawSetOutline(playerid, ptd, 0);
	PlayerTextDrawBackgroundColor(playerid, ptd, 255);
	PlayerTextDrawFont(playerid, ptd, 1);
	PlayerTextDrawSetProportional(playerid, ptd, 1);
	PlayerTextDrawSetShadow(playerid, ptd, 0);
}

TD_UpdateKeyAlarmTime()
{
	new hour,
		minute;
		
	gettime(hour, minute);
	
	format:g_small_string("%02d:%02d", hour, minute);
	TextDrawSetString(td_key_alarm[14], g_small_string);
}