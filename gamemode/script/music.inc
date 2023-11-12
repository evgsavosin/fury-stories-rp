/*!
	@brief Система музыки
	@author Found (evg.savosin)
	@date 26.04.2018
*/

// Structures
enum 
{
	MUSIC_TYPE_BOOMBOX,
	MUSIC_TYPE_VEHICLE
};


new music_select			[	MAX_PLAYERS		][	MAX_MUSIC_URL_LIST	][	MAX_MUSIC_URL	];

// Functions
Music_OnPlayerDisconnect(playerid)
{
	if (!IsPlayerLogged(playerid))
	{
		return 1;
	}
	
	for (new i, targetid; i < sizeof drop_data; i++)
	{
		if ((targetid = drop_data[i][drop_character_id]) == INVALID_PLAYER_ID)
		{
			continue;
		}
		
		if (playerid == targetid)
		{
			MusicPlayForPlayer(false, _, MUSIC_TYPE_BOOMBOX, i);
		}
	}
	
	return 1;
}

MusicPlayForPlayer(bool: states, url[] = "", type = 0, index = 0)
{
	if (states)
	{
		if (type == MUSIC_TYPE_BOOMBOX)
		{	
			drop_data[index][drop_boombox_url][0] = EOS;
			strcat(drop_data[index][drop_boombox_url], url, MAX_MUSIC_URL);
			
			foreach (new i : Player)
			{
				if (!IsPlayerInDynamicArea(i, drop_data[index][drop_area]))
				{
					continue;
				}
				
				PlayAudioStreamForPlayer(
					i, 
					drop_data[index][drop_boombox_url], 
					drop_data[index][drop_pos_x], 
					drop_data[index][drop_pos_y],
					drop_data[index][drop_pos_z], 
					15.0, 
					1
				);
			}
		}
	}
	else 
	{
		if (type == MUSIC_TYPE_BOOMBOX)
		{
			foreach (new i : Player)
			{
				if (!IsPlayerInDynamicArea(i, drop_data[index][drop_area]))
				{
					continue;
				}
				
				StopAudioStreamForPlayer(
					i
				);
			}
		}
	}
}

ShowMusicMenu(playerid, type, index)
{
	SetPVarInt(playerid, "Music:Type", type);
	SetPVarInt(playerid, "Music:Index", index);
	
	ShowPlayerDialog(playerid, D_MUSIC, DIALOG_STYLE_LIST, " ",
		" Указать ссылку\n \
		Сохраненная музыка\n \
		" #cGRAY "Выключить музыку",
		"Далее", "Закрыть"
	);
}

ShowMusicList(playerid)
{
	new server_tick = GetTickCount();
	
	if (GetPVarInt(playerid, "TimeMySQL:ShowMusicList") > server_tick)
	{
		return 0;
	}
	
	format:g_string("SELECT m_url, m_name FROM " __MUSIC " WHERE m_character_id = %i LIMIT %i",
		GetCharacterId(playerid),
		MAX_MUSIC_URL_LIST
	);
	
	mysql_tquery(db, g_string, "OnMusicShowList", "i", playerid);

	SetPVarInt(playerid, "TimeMySQL:ShowMusicList", server_tick + 1000);
	
	return 1;
}

function OnMusicShowList(playerid)
{
	clean:<g_big_string>;
	
	new rows,
		name			[	64	];

	cache_get_row_count(rows);
	
	SetPVarInt(playerid, "Music:CountMusicList", rows);
	
	strcat(g_big_string, "" #cGRAY "Добавить музыку\n" #cWHITE "");
	for (new i; i < rows; i++)
	{
		cache_get_value_name(i, "m_name", name, 64);
		cache_get_value_name(i, "m_url", music_select[playerid][i], MAX_MUSIC_URL);
		
		format:g_big_string("%s %s\n",
			g_big_string,
			name
		);
	}
	
	ShowPlayerDialog(playerid, D_MUSIC + 2, DIALOG_STYLE_LIST, " ", g_big_string, "Выбрать", "Назад");
	return 1;
}

Music_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
		case D_MUSIC :
		{
			if (!response)
			{
				DeletePVar(playerid, "Music:Type");
				DeletePVar(playerid, "Music:Index");
				DeletePVar(playerid, "Music:IndexList");
				DeletePVar(playerid, "Music:CountMusicList");
				DeletePVar(playerid, "TimeMySQL:ShowMusicList");
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowPlayerDialog(playerid, D_MUSIC + 1, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Указать ссылку\n\n\
					Введите ссылку на аудиотрек или радио:\n\n\
					" #cGRAY "Ссылка должна быть в формате http://fs-rp.ru/music.mp3",
					"Далее", "Назад"
				);
			}
			else if (listitem == 1)
			{
				ShowMusicList(playerid);
			}
			else
			{
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно выключили музыку.");
				MusicPlayForPlayer(
					false,
					_,
					GetPVarInt(playerid, "Music:Type"), 
					GetPVarInt(playerid, "Music:Index") 
				);
			}
		}

	    case D_MUSIC + 1 :
		{
			if (!response)
			{
				ShowMusicMenu(playerid, GetPVarInt(playerid, "Music:Type"), GetPVarInt(playerid, "Music:Index"));
				return 1;
			}
			
			if (isnull(inputtext))
			{
				ShowPlayerDialog(playerid, D_MUSIC + 1, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Указать ссылку\n\n\
					Введите ссылку на аудиотрек или радио:\n\
					" #cRED "Ссылка должна быть в формате http://fs-rp.ru/music.mp3",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			MusicPlayForPlayer(
				true, 
				inputtext, 
				GetPVarInt(playerid, "Music:Type"), 
				GetPVarInt(playerid, "Music:Index") 
			);
			
			ShowMusicMenu(playerid, GetPVarInt(playerid, "Music:Type"), GetPVarInt(playerid, "Music:Index"));
		}
	
		case D_MUSIC + 2 :
		{
			if (!response)
			{
				ShowMusicMenu(playerid, GetPVarInt(playerid, "Music:Type"), GetPVarInt(playerid, "Music:Index"));
				return 1;
			}
			
			if (listitem == 0)
			{
				if (GetPVarInt(playerid, "Music:CountMusicList") >= MAX_MUSIC_URL_LIST)
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете добавить больше 20 сохраненных аудиотреков.");
					
					if (!ShowMusicList(playerid))
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
					}
					return 1; 
				}
				
				ShowPlayerDialog(playerid, D_MUSIC + 3, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Добавить музыку\n\n\
					Введите ссылку на аудиотрек или радио:\n\n\
					" #cGRAY "Ссылка должна быть в формате http://fs-rp.ru/music.mp3",
					"Далее", "Назад"
				);
				
				return 1;
			}
			
			listitem--;
			SetPVarInt(playerid, "Music:IndexList", listitem);
			
			ShowPlayerDialog(playerid, D_MUSIC + 4, DIALOG_STYLE_LIST, " ", 
				" Воспроизвести\n \
				 Удалить",
				"Выбрать", "Назад"
			);
		}
		
		case D_MUSIC + 3 :
		{
			if (response)
			{
				if (isnull(inputtext))
				{
					ShowPlayerDialog(playerid, D_MUSIC + 3, DIALOG_STYLE_INPUT, " ",
						"" #DEFAULT " Добавить музыку\n\n\
						Введите ссылку на аудиотрек или радио:\n\
						" #cRED "Ссылка должна быть в формате http://fs-rp.ru/music.mp3",
						"Далее", "Назад"
					);
					
					return 1;
				}
				
				SetPVarString(playerid, "Music:AddUrl", inputtext);
				
				ShowPlayerDialog(playerid, D_MUSIC + 5, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Добавить музыку\n\n\
					Введите название аудиотрека:\n\n\
					" #cGRAY "Текст может содержать любые буквы и цифры.",
					"Далее", "Назад"
				);
			}
		}
		
		case D_MUSIC + 4 :
		{
			if (response)
			{
				new type = GetPVarInt(playerid, "Music:Type"),
					mlindex = GetPVarInt(playerid, "Music:IndexList"),
					index = GetPVarInt(playerid, "Music:Index");
						
				if (listitem == 0)
				{	
					MusicPlayForPlayer(
						true, 
						music_select[playerid][mlindex], 
						type, 
						index 
					);
				}
				else 
				{
					format:g_string("DELETE FROM " #__MUSIC " WHERE m_url = '%q'",
						music_select[playerid][mlindex]
					);
					
					mysql_pquery(db, g_string);
				}
			}
			
			if (!ShowMusicList(playerid))
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
			}
		}
		
		case D_MUSIC + 5 :
		{
			if (!response)
			{	
				DeletePVar(playerid, "Music:AddUrl");
				ShowPlayerDialog(playerid, D_MUSIC + 3, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Добавить музыку\n\n\
					Введите ссылку на аудиотрек или радио:\n\n\
					" #cGRAY "Ссылка должна быть в формате http://fs-rp.ru/music.mp3",
					"Далее", "Назад"
				);
				return 1;
			}
			
			if (isnull(inputtext))
			{
				ShowPlayerDialog(playerid, D_MUSIC + 5, DIALOG_STYLE_INPUT, " ",
					"" #DEFAULT " Добавить музыку\n\n\
					Введите название аудиотрека:\n\
					" #cGRAY "Текст может содержать любые буквы и цифры.\n\
					" #cRED "Вы ввели неверное название аудиотрека.",
					"Далее", "Назад"
				);
				DeletePVar(playerid, "Music:AddUrl");
				return 1;
			}
			
			clean:<g_small_string>;
			GetPVarString(playerid, "Music:AddUrl", g_small_string, sizeof g_small_string);
			format:g_string("INSERT INTO " #__MUSIC " (m_character_id, m_url, m_name, m_created_time) \
				VALUES (%i, '%q', '%q', %i)",
				GetCharacterId(playerid),
				g_small_string,
				inputtext,
				gettime()
			);
			
			mysql_pquery(db, g_string);
			
			if (!ShowMusicList(playerid))
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
			}
			
			DeletePVar(playerid, "Music:AddUrl");
		}
	}
	
	return 1;
}