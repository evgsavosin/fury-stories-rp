/*!
	@brief Заголовок системы тюрьмы на сервере
	@author Found (evg.savosin)
	@date 16.12.2016, update 14.02.2018
*/

Create:fprison_text()
{	
	CreatePickupWith3DTextLabel(
		"Пульт управления\n"#cPROJECT "H", 
		INVALID_PARAM, 
		PRISON_MENU_POS
	);
}

Create:fprison_door_all()
{
	static Float: door_pos[MAX_FRACTION_PRISON_DOORS][MAX_FRACTION_PRISON_DOOR_OBJ][12] = 
	{
		{
			{-1660.953125, 1991.098632, 2599.099853, 180.000000, 90.000000, 90.000000,  -1662.794067, 1991.098632, 2599.099853, 0.000000, 270.000000, -90.000007},
			{-1660.953125, 1991.098632, 2599.540283, 180.000000, 90.000000, 90.000000,  -1662.794067, 1991.098632, 2599.540283, 0.000000, 270.000000, -90.000007},
			{-1660.953125, 1991.098632, 2599.970458, 180.000000, 90.000000, 90.000000,  -1662.794067, 1991.098632, 2599.970458, 0.000000, 270.000000, -90.000007},
			{-1660.953125, 1991.098632, 2600.399902, 180.000000, 90.000000, 90.000000,  -1662.794067, 1991.098632, 2600.399902, 0.000000, 270.000000, -90.000007},
			{-1660.953125, 1991.098632, 2600.840332, 180.000000, 90.000000, 90.000000,  -1662.794067, 1991.098632, 2600.840332, 0.000000, 270.000000, -90.000007},
			{-1660.953125, 1991.098632, 2601.270507, 180.000000, 90.000000, 90.000000,  -1662.794067, 1991.098632, 2601.270507, 0.000000, 270.000000, -90.000007}
		},
		
		{
			{1823.044921, -1539.375610, 14.296708, 0.000000, 0.000000, -16.100000,  1822.243530, -1542.152587, 14.296708, 0.000000, 0.000000, -16.100000},
			{1823.938110, -1536.281494, 14.296708, 0.000000, 0.000000, -16.100000,  1822.275268, -1542.038696, 14.296708, 0.000000, 0.000000, -16.100000},
			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
		},
		
		{
			{1752.820800, -1591.391357, 14.296708, 0.000000, 0.000000, 76.200004,  1758.299804, -1592.738769, 14.296708, 0.000000, 0.000000, 76.200004},
			{1755.912597, -1592.152465, 14.296708, 0.000000, 0.000000, 256.200012,  1758.214599, -1592.718261, 14.296708, 0.000000, 0.000000, 256.200012},
			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
			{0.0, 0.0, 0.0, 0.0, 0.0, 0.0,  0.0, 0.0, 0.0, 0.0, 0.0, 0.0}
		}
	};
	
	new tmpobjid;
	
	for (new j; j < MAX_FRACTION_PRISON_DOORS; j++)
	{
		for (new i; i < MAX_FRACTION_PRISON_DOOR_OBJ; i++)
		{
			if (door_pos[j][i][0] == 0.0)
			{
				continue;
			}
			
			tmpobjid = Create:fprison_door(
				j,
				i, 
				door_pos[j][i][0], 
				door_pos[j][i][1], 
				door_pos[j][i][2] + 0.001, 
				door_pos[j][i][3], 
				door_pos[j][i][4], 
				door_pos[j][i][5],
				door_pos[j][i][6], 
				door_pos[j][i][7], 
				door_pos[j][i][8] - 0.001, 
				door_pos[j][i][9], 
				door_pos[j][i][10], 
				door_pos[j][i][11],
				j == 0 ? 19940 : 19353
			);
			
			if (j == 0)
			{
				SetDynamicObjectMaterial(tmpobjid, 0, 16322, "a51_stores", "fence_64", 0xFFF0FFFF);
				SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
			}
			else 
			{
				SetDynamicObjectMaterial(tmpobjid, 0, 3998, "civic04_lan", "sl_prisongate1", 0x00000000);
			}
		}
	}
}

SetFractionPrisonStateDoor(index)
{
	new Float: speed = 0.5;
	
	for (new i; i < MAX_FRACTION_PRISON_DOOR_OBJ; i++)
	{
		if (fprison_door[index][i][fr_status])
		{
			MoveDynamicObject(
				fprison_door[index][i][fr_object_id], 
				fprison_door[index][i][fr_begin_pos][0],
				fprison_door[index][i][fr_begin_pos][1],
				fprison_door[index][i][fr_begin_pos][2], 
				speed, 
				fprison_door[index][i][fr_begin_pos][3],
				fprison_door[index][i][fr_begin_pos][4],
				fprison_door[index][i][fr_begin_pos][5]
			);
		}
		else 
		{
			MoveDynamicObject(
				fprison_door[index][i][fr_object_id], 
				fprison_door[index][i][fr_end_pos][0],
				fprison_door[index][i][fr_end_pos][1],
				fprison_door[index][i][fr_end_pos][2], 
				speed, 
				fprison_door[index][i][fr_end_pos][3],
				fprison_door[index][i][fr_end_pos][4],
				fprison_door[index][i][fr_end_pos][5]
			);
		}
		
		fprison_door[index][i][fr_status] = !fprison_door[index][i][fr_status];
	}
}

ImprisonPlayerToJail(playerid, time = 0)
{
	new index = GetFractionCameraJailIndex();
	
	SetPlayerPos(
		playerid, 
		fraction_camera[index][fr_pos_camera][0],
		fraction_camera[index][fr_pos_camera][1],
		fraction_camera[index][fr_pos_camera][2]
	);
	
	SetPlayerFacingAngle(playerid, fraction_camera[index][fr_pos_camera][3]);
	
	character_data[playerid][c_arrest_camera] = index;
	character_data[playerid][c_arrest_time] = time != 0 ? (gettime() + (time * 60)) : 0;
	character_data[playerid][c_arrest_type] = TYPE_ARREST_JAIL;
	
	format:g_small_string("FROM_UNIXTIME(%d)", character_data[playerid][c_arrest_time]);
	Update:character_string(playerid, "c_arrest_date", g_small_string, false);
	Update:character_int(playerid, "c_arrest_camera", index);
	Update:character_int(playerid, "c_arrest_type", TYPE_ARREST_JAIL);
	
	return index;
}

ShowPrisonMenu(playerid)
{
	format:g_string(" Камеры блока\t%s",
		fprison_camera_status ? (#cPROJECT "Открыты") : (#cGRAY "Закрыты")
	);
	
	ShowPlayerDialog(playerid, D_FRACTION + 58, DIALOG_STYLE_TABLIST, " ", g_string, "Выбрать", "Закрыть");
}