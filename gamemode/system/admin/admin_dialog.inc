/*!
	@brief Диалоги для системы администрирования
	@author Found (evg.savosin)
	@date 16.12.2016, update 08.03.2018
	
*/

Admin_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch (dialogid)
	{
		case D_ADMIN :
		{
			if (!response)
			{
				return 1;
			}
			
			if (!GetAdminLevel(playerid))
			{
				SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);	
				return 1;
			}
			
			switch(listitem)
			{
				case 0: // Список администраторов
				{
					cmd_admins(playerid);
				}
				
				case 1: // Список хелперов
				{
					cmd_helpers(playerid);
				}
				
				case 2: // Список команд
				{	
					format:g_big_string( #DEFAULT " Список команд.\n\nВаш уровень администрирования: " #cPROJECT "%i" #cWHITE "\n", 
						GetAdminLevel(playerid) 
					);
					
					if (GetAdminLevel(playerid) >= ADMIN_TRAINEE)
					{
						strcat(g_big_string, "\n" #cPROJECT "1 уровень:" #cWHITE "\n \
							/aduty, /amenu, /a, /kick, /mute(-/unmute), /ans, /h\n \
							/sp, /gotohouse, /gotopremise, /slap, /goto, /gethere, /weapons, /aspawn\n \
							/aafk, /ddesc, /daction, /warn, /aheal, /afrisk, /astats, /setint, /setworld\n \
							/warn, /deathlog, /dislog" 
						);
					}
					
					if (GetAdminLevel(playerid) >= ADMIN_JUNIOR)
					{
						strcat(g_big_string, "\n\n" #cPROJECT "2 уровень:" #cWHITE "\n \
							/sethp, /ban(-/unban), /vrespawn, /g, /aunarrest, /dcorpse, /mban, /getbuycar, /gotocorpse" 
						);
					}
					
					if (GetAdminLevel(playerid) >= ADMIN_NORMAL)
					{
						strcat(g_big_string, "\n\n" #cPROJECT "3 уровень:" #cWHITE "\n \
							/vrepair, /vfuel, /tmpskin, /aban(-/unban), /banip(-/unbanip), /afuninvite, /amban\n \
							/auncuff, /ddropitem" 
						);
					}
					
					if (GetAdminLevel(playerid) >= ADMIN_SENIOR)
					{
						strcat(g_big_string, "\n\n" #cPROJECT "4 уровень:" #cWHITE "\n \
							/vcreate, /vdel, /vdelall, /setfraction, /ahlock, /aprlock, /aclock" 
						);
					}
					
					if (GetAdminLevel(playerid) >= ADMIN_LEAD)
					{
						strcat(g_big_string, "\n\n" #cPROJECT "5 уровень:" #cWHITE "\n \
							/setweather, /xyz" 
						);
					}
					
					strcat(g_big_string, "\n\n" #DEFAULT " Дополнительные привелегии:\n");
					if (CheckAdminAccess(playerid, ADMIN_SENIOR, ap_developer))
					{
						strcat(g_big_string, "\n" #cPROJECT "Разработчика:" #cWHITE "\n \
							/restart, /skick, /addhouse, /edithouse, /delhouse, /lasthouse, /addhostel\n \
							/delhostel, /addgarage, /delgarage, /addpremise, /editpremise, /delpremise\n \
							/lastpremise, /resetcredit, /kickall" 
						);
					}
					
					if (CheckAdminAccess(playerid, ADMIN_SENIOR, ap_manage_admins))
					{
						strcat(g_big_string, "\n\n" #cPROJECT "Главного администратора:" #cWHITE "\n \
							/removeadmin, /removehelper" 
						);
					}
					
					/*if (CheckAdminAccess(playerid, ADMIN_TRAINEE, ap_property))
					{
						strcat(g_big_string, "\n\n" #cPROJECT "Ответственный за имуществом:" #cWHITE "\n \
							/giveitem, /givemoney" 
						);
					}*/
					
					ShowPlayerDialog(playerid, D_ADMIN + 2, DIALOG_STYLE_MSGBOX, " ", g_big_string, "Назад", "");
				}
				
				case 3: // Телепорт
				{
					ShowAdminTeleportList(playerid);
				}
				
				case 4: // Фракции
				{
					cmd_mfraction(playerid);
				}
				
				case 5: // Криминальные организации
				{
					cmd_mcrime(playerid);
				}
				
				case 6: // Античита 
				{
					cmd_manticheat(playerid);
				}
				
				case 7: // Лог отключений
				{
					ShowAdminDisconnectionLog(playerid);
				}
				
				case 8: // Лог смертей
				{
					ShowAdminDeathLog(playerid);
				}
			}
		}
		
		case D_ADMIN + 1 :
		{
			return cmd_amenu(playerid);
		}
		
		case D_ADMIN + 2 : 
		{
			if (!response)
			{
				return cmd_amenu(playerid);
			}
		}
		
		case D_ADMIN + 3 :
		{
			return 1; // teleports 
		}
		
		case D_ADMIN + 6 :
		{
			if (!response)
			{
				return 1;
			}
			
			SetPVarInt(playerid, "Admin:HouseInt", listitem + 1);
			
			ShowPlayerDialog(playerid, D_ADMIN + 7, DIALOG_STYLE_INPUT, " ", 
				"" #DEFAULT " Цена дома\n\n\
				Введите стоимость:\n\n\
				" #cGRAY "Сумма не должна быть ниже $1 и быть больше $10.000.000.",
				"Далее", "Назад" 
			);
		}
		
		case D_ADMIN + 7 :
		{
			if (!response)
			{
				DeletePVar(playerid, "Admin:HouseInt");
				cmd_addhouse(playerid);
				return 1;
			}
			
			new value = strval(inputtext);
			if (!value || !(0 < value < 10_000_000))
			{
				ShowPlayerDialog(playerid, D_ADMIN + 7, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Цена дома\n\n\
					Введите стоимость:\n\n\
					" #cRED "Сумма не должна быть ниже $1 и быть больше $10.000.000.",
					"Далее", "Назад" 
				);
				
				return 1;
			}
			
			new Float: x,
				Float: y,
				Float: z,
				Float: angle,
				bool: exists;
			
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			
			for (new i; i < sizeof house_data; i++)
			{
				if (house_data[i][h_id] != 0)
				{
					continue;
				}
				
				house_data[i][h_id] = INVALID_PARAM;
				house_data[i][h_pos][0] = x;
				house_data[i][h_pos][1] = y;
				house_data[i][h_pos][2] = z;
				house_data[i][h_pos][3] = angle;
				house_data[i][h_world] = GetPlayerVirtualWorld(playerid);
				house_data[i][h_interior] = GetPlayerInterior(playerid);
				house_data[i][h_price] = value;
				house_data[i][h_int_type] = GetPVarInt(playerid, "Admin:HouseInt");
				
				Create:house_data(i, playerid);
				exists = true;
				break;
			}
			
			DeletePVar(playerid, "Admin:HouseInt");
			if (!exists)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Превышен лимит на создание домов.");
			}
		}
		
		case D_ADMIN + 8 :
		{
			if (!response)
			{
				DeletePVar(playerid, "Admin:HouseSelect");
				return 1;
			}

			new index = GetPVarInt(playerid, "Admin:HouseSelect");
			
			switch(listitem)
			{
				case 0 : // Информация
				{
					ShowHouseInformation(playerid, index, D_ADMIN + 9, true, "Назад");
					
					return 1;
				}
				
				case 1 : // Установить вход
				{
					new Float: x,
						Float: y,
						Float: z,
						Float: angle;
						
					GetPlayerPos(playerid, x, y, z);
					GetPlayerFacingAngle(playerid, angle);
						
					house_data[index][h_pos][0] = x;
					house_data[index][h_pos][1] = y;
					house_data[index][h_pos][2] = z;
					house_data[index][h_pos][3] = angle;
					
					house_data[index][h_world] = GetPlayerVirtualWorld(playerid);
					house_data[index][h_interior] = GetPlayerInterior(playerid);
					
					format:g_string("\
					UPDATE " #__HOUSES " SET \
						h_pos_x = %f, \
						h_pos_y = %f, \
						h_pos_z = %f, \
						h_pos_angle = %f \
					WHERE h_id = %i \
					LIMIT 1",
						GetHouseId(index)
					);
					
					mysql_tquery(db, g_string);
					
					Destroy:house(index);
					Create:house(index);
					
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно обновили позицию входа.");
				}
				
				case 2 : // Установить интерьер 
				{
					ShowAdminHouseInteriors(playerid, D_ADMIN + 10);
					
					return 1;
				}
				
				case 3 : // Установить цену 
				{
					ShowPlayerDialog(playerid, D_ADMIN + 11, DIALOG_STYLE_INPUT, " ", 
						"" #DEFAULT " Цена дома\n\n\
						Введите стоимость:\n\n\
						" #cRED "Сумма не должна быть ниже $1 и быть больше $10.000.000.",
						"Далее", "Назад" 
					);
					
					return 1;
				}
				
				case 4 : // Установить аренду ком услуги
				{
					ShowAdminEditHouseTime(playerid, D_ADMIN + 12);
				}
				
				case 5 : // Обнулить задолжности
				{
					house_data[index][h_debt] = 
					house_data[index][h_debt_count] = 0;
					
					Update:house_int(index, "h_debt", 0);
					Update:house_int(index, "h_debt_count", 0);
					
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно обнулили задолжности.");
				}
				
				case 6 : // Продать
				{
					if (IsHouseBought(index))
					{
						SellHouse(index);
						SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно продали данное имущество.");
					}
					else 
					{
						SendClientMessage(playerid, C_WHITE, !#ERROR " Данное имущество не куплено кем-либо.");
					}
				}
			}
			
			ShowAdminEditHouse(playerid);
		}
		
		case D_ADMIN + 9 :
		{
			ShowAdminEditHouse(playerid);
			return 1;
		}
		
		case D_ADMIN + 10 :
		{
			if (!response)
			{
				ShowAdminEditHouse(playerid);
				return 1;
			}
			
			listitem++;
			
			new index = GetPVarInt(playerid, "Admin:HouseSelect");
			
			Destroy:house_int_obj(index);
			
			house_data[index][h_int_type] = listitem;
			Update:house_int(index, "h_int_type", listitem);
			
			Create:house_int_obj(index, listitem);
			
			ResetHouseInterior(index);
			
			ShowAdminEditHouse(playerid);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно установили новый интерьер.");
		}
		
		case D_ADMIN + 11 :
		{
			if (!response)
			{
				ShowAdminEditHouse(playerid);
				return 1;
			}
			
			new value = strval(inputtext),
				index = GetPVarInt(playerid, "Admin:HouseSelect");
				
			if (!value || !(0 < value < 10_000_000))
			{
				ShowPlayerDialog(playerid, D_ADMIN + 11, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Цена дома\n\n\
					Введите стоимость:\n\n\
					" #cRED "Сумма не должна быть ниже $1 и быть больше $10.000.000.",
					"Далее", "Назад" 
				);
				
				return 1;
			}
			
			house_data[index][h_price] = value;
			Update:house_int(index, "h_price", value);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно установили новую цену.");
		}
		
		case D_ADMIN + 12 :
		{
			if (!response)
			{
				ShowAdminEditHouse(playerid);
				return 1;
			}
			
			new value = strval(inputtext),
				index = GetPVarInt(playerid, "Admin:HouseSelect");
			
			if (!value || !(-100_000 < value < 100_000))
			{
				ShowAdminEditHouseTime(playerid, D_ADMIN + 12, _, true);
				return 1;
			}
			
			house_data[index][h_time] += value * (60 * 60 * 24);
			Update:house_int(index, "h_time", house_data[index][h_time]);
			
			ShowAdminEditHouseTime(playerid, D_ADMIN + 12);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно установили новую дату аренды/ком. услуг.");
		}
		
		case D_ADMIN + 13 :
		{
			if (!response)
			{
				return 1;
			}
			
			SetPVarInt(playerid, "Admin:HostelInt", listitem + 1);
			
			ShowPlayerDialog(playerid, D_ADMIN + 14, DIALOG_STYLE_INPUT, " ", 
				"" #DEFAULT " Цена квартир\n\n\
				Введите примерную стоимость квартир:\n\
				" #cGRAY "Сумма не должна быть ниже $1 и быть больше $10.000.000.",
				"Далее", "Назад" 
			);
		}
		
		case D_ADMIN + 14 :
		{
			if (!response)
			{	
				DeletePVar(playerid, "Admin:HostelInt");
				
				cmd_addhostel(playerid);
				return 1;
			}
			
			new value = strval(inputtext);
			
			if (!value || !(0 < value < 10_000_000))
			{
				ShowPlayerDialog(playerid, D_ADMIN + 14, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Цена квартир\n\n\
					Введите примерную стоимость квартир:\n\n\
					" #cRED "Сумма не должна быть ниже $1 и быть больше $10.000.000.",
					"Далее", "Назад" 
				);
				
				return 1;
			}
			
			new Float: x,
				Float: y,
				Float: z,
				Float: angle,
				bool: exists;
			
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			
			for (new i; i < sizeof hostel_data; i++)
			{
				if (hostel_data[i][hos_id] != 0)
				{
					continue;
				}
				
				hostel_data[i][hos_int_type] = GetPVarInt(playerid, "Admin:HostelInt");
				hostel_data[i][hos_pos][0] = x;
				hostel_data[i][hos_pos][1] = y;
				hostel_data[i][hos_pos][2] = z;
				hostel_data[i][hos_pos][3] = angle;
				
				Create:hostel_data(i, playerid, value);
				exists = true;
				break;
			}
			
			DeletePVar(playerid, "Admin:HostelInt");
			if (!exists)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Превышен лимит на создание подъездов.");
			}
		}
		
		case D_ADMIN + 15 :
		{
			if (!response)
			{
				return 1;
			}
			
			SetPVarInt(playerid, "Admin:PremiseInt", listitem + 1);
			
			ShowPlayerDialog(playerid, D_ADMIN + 16, DIALOG_STYLE_INPUT, " ", 
				"" #DEFAULT " Цена помещения\n\n\
				Введите стоимость:\n\n\
				" #cGRAY "Сумма не должна быть ниже $1 и быть больше $10.000.000.",
				"Далее", "Назад" 
			);
		}
		
		case D_ADMIN + 16 :
		{
			if (!response)
			{
				DeletePVar(playerid, "Admin:PremiseInt");
				cmd_addpremise(playerid);
				return 1;
			}
			
			new value = strval(inputtext);
			if (!value || !(0 < value < 10_000_000))
			{
				ShowPlayerDialog(playerid, D_ADMIN + 16, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Цена помещения\n\n\
					Введите стоимость:\n\n\
					" #cRED "Сумма не должна быть ниже $1 и быть больше $10.000.000.",
					"Далее", "Назад" 
				);
				
				return 1;
			}
			
			new Float: x,
				Float: y,
				Float: z,
				Float: angle,
				bool: exists;
			
			GetPlayerPos(playerid, x, y, z);
			GetPlayerFacingAngle(playerid, angle);
			
			for (new i; i < sizeof premise_data; i++)
			{
				if (premise_data[i][pr_id] != 0)
				{
					continue;
				}
				
				premise_data[i][pr_pos][0] = x;
				premise_data[i][pr_pos][1] = y;
				premise_data[i][pr_pos][2] = z;
				premise_data[i][pr_pos][3] = angle;
				premise_data[i][pr_world] = GetPlayerVirtualWorld(playerid);
				premise_data[i][pr_interior] = GetPlayerInterior(playerid);
				premise_data[i][pr_price] = value;
				premise_data[i][pr_int_type] = GetPVarInt(playerid, "Admin:PremiseInt");
				
				Create:premise_data(i, playerid);
				exists = true;
				break;
			}
			
			DeletePVar(playerid, "Admin:PremiseInt");
			if (!exists)
			{
				SendClientMessage(playerid, C_WHITE, !#ERROR " Превышен лимит на создание помещений.");
			}
		}
		
		case D_ADMIN + 17 :
		{
			if (!response)
			{
				DeletePVar(playerid, "Admin:PremiseSelect");
				return 1;
			}

			new index = GetPVarInt(playerid, "Admin:PremiseSelect");
			
			switch(listitem)
			{
				case 0 : // Информация
				{
					ShowPremiseInformation(playerid, index, D_ADMIN + 18, true, "Назад");
					
					return 1;
				}
				
				case 1 : // Установить вход
				{
					new Float: x,
						Float: y,
						Float: z,
						Float: angle;
						
					GetPlayerPos(playerid, x, y, z);
					GetPlayerFacingAngle(playerid, angle);
						
					premise_data[index][pr_pos][0] = x;
					premise_data[index][pr_pos][1] = y;
					premise_data[index][pr_pos][2] = z;
					premise_data[index][pr_pos][3] = angle;
					
					premise_data[index][pr_world] = GetPlayerVirtualWorld(playerid);
					premise_data[index][pr_interior] = GetPlayerInterior(playerid);
					
					format:g_string("\
					UPDATE " #__PREMISES " SET \
						pr_pos_x = %f, \
						pr_pos_y = %f, \
						pr_pos_z = %f, \
						pr_pos_angle = %f \
					WHERE pr_id = %i \
					LIMIT 1",
						premise_data[index][pr_pos][0],
						premise_data[index][pr_pos][1],
						premise_data[index][pr_pos][2],
						premise_data[index][pr_pos][3],
						GetPremiseId(index)
					);
					
					mysql_tquery(db, g_string);
					
					Destroy:premise(index);
					Create:premise(index);
					
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно обновили позицию входа.");
				}
				
				case 2 : // Установить интерьер 
				{
					ShowAdminPremiseInteriors(playerid, D_ADMIN + 19);
					
					return 1;
				}
				
				case 3 : // Установить цену 
				{
					ShowPlayerDialog(playerid, D_ADMIN + 20, DIALOG_STYLE_INPUT, " ", 
						"" #DEFAULT " Цена помещения\n\n\
						Введите стоимость:\n\n\
						" #cRED "Сумма не должна быть ниже $1 и быть больше $10.000.000.",
						"Далее", "Назад" 
					);
					
					return 1;
				}
				
				case 4 : // Установить аренду ком услуги
				{
					ShowAdminEditPremiseTime(playerid, D_ADMIN + 21);
				}
				
				case 5 : // Обнулить задолжности
				{
					premise_data[index][pr_debt] = 
					premise_data[index][pr_debt_count] = 0;
					
					Update:premise_int(index, "pr_debt", 0);
					Update:premise_int(index, "pr_debt_count", 0);
					
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно обнулили задолжности.");
				}
				
				case 6 : // Продать
				{
					if (IsPremiseBought(index))
					{
						SellPremise(index);
						SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно продали данное имущество.");
					}
					else 
					{
						SendClientMessage(playerid, C_WHITE, !#ERROR " Данное имущество не куплено кем-либо.");
					}
				}
			}
			
			ShowAdminEditPremise(playerid);
		}
		
		case D_ADMIN + 18 :
		{
			ShowAdminEditPremise(playerid);
		}
		
		case D_ADMIN + 19 :
		{
			if (!response)
			{
				ShowAdminEditPremise(playerid);
				return 1;
			}
			
			listitem++;
			
			new index = GetPVarInt(playerid, "Admin:PremiseSelect");
			
			Destroy:premise_int_obj(index);
			
			premise_data[index][pr_int_type] = listitem;
			Update:premise_int(index, "pr_int_type", listitem);
			
			Create:premise_int_obj(index, listitem);
			
			ResetPremiseInterior(index);
			
			ShowAdminEditPremise(playerid);
			
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно установили новый интерьер.");
		}
		
		case D_ADMIN + 20 :
		{
			if (!response)
			{
				ShowAdminEditPremise(playerid);
				return 1;
			}
			
			new value = strval(inputtext),
				index = GetPVarInt(playerid, "Admin:PremiseSelect");
				
			if (!value || !(0 < value < 10_000_000))
			{
				ShowPlayerDialog(playerid, D_ADMIN + 20, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Цена помещения\n\n\
					Введите стоимость:\n\n\
					" #cRED "Сумма не должна быть ниже $1 и быть больше $10.000.000.",
					"Далее", "Назад" 
				);
				
				return 1;
			}
			
			premise_data[index][pr_price] = value;
			Update:premise_int(index, "pr_price", value);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно установили новую цену.");
		}
		
		case D_ADMIN + 21 :
		{
			if (!response)
			{
				ShowAdminEditPremise(playerid);
				return 1;
			}
			
			new value = strval(inputtext),
				index = GetPVarInt(playerid, "Admin:PremiseSelect");
			
			if (!value || !(-100_000 < value < 100_000))
			{
				ShowAdminEditPremiseTime(playerid, D_ADMIN + 21, _, true);
				return 1;
			}
			
			premise_data[index][pr_time] += value * (60 * 60 * 24);
			Update:premise_int(index, "pr_time", premise_data[index][pr_time]);
			
			ShowAdminEditPremiseTime(playerid, D_ADMIN + 21);
			SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно установили новую дату аренды/ком. услуг.");
		}
		
		case D_ADMIN + 22 : 
		{
			if (!response)
			{
				return 1;
			}
			
			OnAdminServerRestart();
		}
		
		case D_ADMIN + 23:
		{
			if (!response)
			{
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowAdminFractionCreate(playerid, D_ADMIN + 24);
				return 1;
			}
			
			listitem--;
			
			SetPVarInt(playerid, "Admin:FractionSelect", listitem);
			ShowAdminFractionEdit(playerid, D_ADMIN + 28, listitem);
		}
		
		case D_ADMIN + 24:
		{
			if (!response)
			{
				ShowAdminFractionList(playerid);
				return 1;
			}
			
			if (isnull(inputtext))
			{
				ShowAdminFractionCreate(playerid, D_ADMIN + 24, "Вы ввели некорректное имя фракции.");
				return 1;
			}
			
			SetPVarString(playerid, "Admin:FractionName", inputtext);
			ShowAdminFractionCreate(playerid, D_ADMIN + 25);
		}
		
		case D_ADMIN + 25:
		{
			if (!response)
			{
				ShowAdminFractionCreate(playerid, D_ADMIN + 24);
				return 1;
			}
			
			SetPVarString(playerid, "Admin:FractionShortName", inputtext);
			ShowAdminFractionCreate(playerid, D_ADMIN + 26);
		}
		
		case D_ADMIN + 26:
		{
			if (!response)
			{
				ShowAdminFractionCreate(playerid, D_ADMIN + 25);
				return 1;
			}
			
			if (isnull(inputtext))
			{
				ShowAdminFractionCreate(playerid, D_ADMIN + 27, "Вы ввели некорректное имя фракции.");
				return 1;
			}
			
			SetPVarString(playerid, "Admin:FractionColor", inputtext);
			
			ShowAdminFractionCreate(playerid, D_ADMIN + 27);
		}
		
		case D_ADMIN + 27:
		{
			if (response)
			{
				new name 		[MAX_FRACTION_NAME],
					alt_name	[MAX_FRACTION_ALT_NAME],
					color		[16];
				
				GetPVarString(playerid, "Admin:FractionName", name, sizeof name);
				GetPVarString(playerid, "Admin:FractionShortName", alt_name, sizeof alt_name);
				GetPVarString(playerid, "Admin:FractionColor", color, sizeof color);
				
				new index = GetFreeIndexForFraction();

				if (index != INVALID_PARAM)
				{
					strcat(fraction_data[index][fr_name], name, MAX_FRACTION_NAME);
					strcat(fraction_data[index][fr_alt_name], alt_name, MAX_FRACTION_ALT_NAME);
					sscanf(color, "x", fraction_data[index][fr_color]);
				
					Create:fraction_data(playerid, index);
				}
				else 
				{
					SendClientMessage(playerid, C_WHITE, #ERROR " Превышен лимит на создание фракций.");
				}
				
				ShowAdminFractionList(playerid);
			}
			else 
			{
				ShowAdminFractionCreate(playerid, D_ADMIN + 26);
			}
		}
		
		case D_ADMIN + 28:
		{
			if (!response)
			{
				ShowAdminFractionList(playerid);
				return 1;
			}
			
			new index = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (listitem == 0) // Название
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 29, index);
			}
			else if (listitem == 1) // Сокращенное название
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 30, index);
			}
			else if (listitem == 2) // Цвет
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 31, index);
			}
			else if (listitem == 3) // Доступные объекты
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 32, index);
			}
			else if (listitem == 4) // Доступные прикреплённые объекты
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 38, index);
			}
			else if (listitem == 5) // Финансирование бюджета
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 44, index);
			}
			else if (listitem == 6) // Бюджет
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 45, index);
			}
			else if (listitem == 7) // Доступные предметы
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 46, index);
			}
			else if (listitem == 8) // Лидер
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 50, index);
			}
			else // Удалить фракцию
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 49, index);
			}
		}
		
		case D_ADMIN + 29:
		{
			new index = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (response)
			{
				if (isnull(inputtext))
				{
					ShowAdminFractionEdit(playerid, D_ADMIN + 29, index,
					"Вы ввели некорректное название фракции.");
					return 1;
				}
				
				clean:<fraction_data[index][fr_name]>;
				strcat(fraction_data[index][fr_name], inputtext, MAX_FRACTION_NAME);
				
				Update:fraction_string(index, "fr_name", inputtext);
			}
			
			ShowAdminFractionEdit(playerid, D_ADMIN + 28, index);
		}
		
		case D_ADMIN + 30:
		{
			new index = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (response)
			{
				if (isnull(inputtext))
				{
					ShowAdminFractionEdit(playerid, D_ADMIN + 30, index,
					"Вы ввели некорректное сокращённое название фракции.");
					return 1;
				}
				
				clean:<fraction_data[index][fr_alt_name]>;
				strcat(fraction_data[index][fr_alt_name], inputtext, MAX_FRACTION_ALT_NAME);
		
				Update:fraction_string(index, "fr_alt_name", inputtext);
			}
			
			ShowAdminFractionEdit(playerid, D_ADMIN + 28, index);
		}
		
		case D_ADMIN + 31:
		{
			new index = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (response)
			{
				if (isnull(inputtext) || sscanf(inputtext, "x", fraction_data[index][fr_color]))
				{
					ShowAdminFractionEdit(playerid, D_ADMIN + 30, index,
					"Вы ввели некорректный цвет.");
					return 1;
				}
				
				Update:fraction_string(index, "fr_color", inputtext);
			}
			
			ShowAdminFractionEdit(playerid, D_ADMIN + 28, index);
		}
		
		case D_ADMIN + 32: // Список объектов: выбор объекта
		{
			new index = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (!response)
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 28, index);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowAdminFractionObjectEdit(playerid, D_ADMIN + 36);
				return 1;
			}
			
			new id = fraction_item_select[playerid][listitem][fr_id];
			
			if (id == ITEM_LIST_NEXT || id == ITEM_LIST_BACK)
			{
				ShowFractionObjectList(playerid, dialogid, index, id);
				return 1;
			}
			
			listitem--;
			
			SetPVarInt(playerid, "Admin:FractionObjectSelect", listitem);
			ShowAdminFractionObjectEdit(playerid, D_ADMIN + 33);
		}
		
		case D_ADMIN + 33: // Список объектов: действие с выбранным объектом
		{
			new index = GetPVarInt(playerid, "Admin:FractionObjectSelect"),
				findex = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (!response)
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 32, findex);
				return 1;
			}
			
			if (listitem == 0) // Изменить название
			{
				ShowAdminFractionObjectEdit(playerid, D_ADMIN + 34, index);
			}
			else if (listitem == 1) // Изменить ID объекта
			{
				ShowAdminFractionObjectEdit(playerid, D_ADMIN + 35, index);
			}
			else // Удалить объект
			{
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно удалили объект.");
				
				Remove:fraction_object(
					fraction_item_select[playerid][index][fr_id]
				);
				
				ShowAdminFractionEdit(playerid, D_ADMIN + 32, findex);
			}
		}
		
		case D_ADMIN + 34: // Список объектов: редактирование имя объекта
		{
			new index = GetPVarInt(playerid, "Admin:FractionObjectSelect");
			
			if (response)
			{
				if (isnull(inputtext))
				{
					ShowAdminFractionObjectEdit(playerid, D_ADMIN + 34, index,
					"Вы ввели некорректное имя.");
					return 1;
				}
		
				Update:fraction_object_string(fraction_item_select[playerid][index][fr_id], "fo_name", inputtext);
			}
			
			ShowAdminFractionObjectEdit(playerid, D_ADMIN + 33);
		}
		
		case D_ADMIN + 35: // Список объектов: редактирование ID объекта
		{
			new index = GetPVarInt(playerid, "Admin:FractionObjectSelect");
			
			if (response)
			{
				if (isnull(inputtext) || !IsInt(inputtext))
				{
					ShowAdminFractionObjectEdit(playerid, D_ADMIN + 35, index,
						"Вы ввели ID объекта."
					);
					
					return 1;
				}
				
				new object_id = strval(inputtext);
				
				Update:fraction_object_int(fraction_item_select[playerid][index][fr_id], "fo_object_id", object_id);
			}
			
			ShowAdminFractionObjectEdit(playerid, D_ADMIN + 33);
		}
		
		case D_ADMIN + 36: // Список объектов: создание (ID объекта)
		{
			new findex = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (response)
			{
				if (isnull(inputtext) || !IsInt(inputtext))
				{
					ShowAdminFractionObjectEdit(playerid, dialogid, INVALID_PARAM,
						"Вы ввели неверный ID объекта."
					);
					return 1;
				}
				
				SetPVarInt(playerid, "Admin:FractionObjectId", strval(inputtext));
				ShowAdminFractionObjectEdit(playerid, D_ADMIN + 37);
			}
			else 
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 32, findex);
			}
		}
		
		case D_ADMIN + 37: // Список объектов: создание (имя)
		{
			new findex = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (response)
			{
				if (isnull(inputtext))
				{
					ShowAdminFractionObjectEdit(playerid, dialogid, INVALID_PARAM,
						"Вы ввели некорректное имя объекта."
					);
					
					return 1;
				}
				
				new objectid = GetPVarInt(playerid, "Admin:FractionObjectId");
				
				Create:fraction_object_data(
					GetFractionId(findex),
					objectid,
					inputtext
				);
				
				ShowAdminFractionEdit(playerid, D_ADMIN + 32, findex);
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно создали объект.");
			}
			else 
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 32, findex);
			}
		}
		
		case D_ADMIN + 38: // Список аттачей: выбор объекта
		{
			new index = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (!response)
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 28, index);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowAdminFractionAttachEdit(playerid, D_ADMIN + 42);
				return 1;
			}
			
			new id = fraction_item_select[playerid][listitem][fr_id];
			
			if (id == ITEM_LIST_NEXT || id == ITEM_LIST_BACK)
			{
				ShowFractionObjectList(playerid, dialogid, index, id);
				return 1;
			}
			
			listitem--;
			
			SetPVarInt(playerid, "Admin:FractionAttachSelect", listitem);
			ShowAdminFractionAttachEdit(playerid, D_ADMIN + 39);
		}
		
		case D_ADMIN + 39: // Список аттачей: действие с выбранным объектом
		{
			new index = GetPVarInt(playerid, "Admin:FractionAttachSelect"),
				findex = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (!response)
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 38, findex);
				return 1;
			}
			
			if (listitem == 0) // Изменить название
			{
				ShowAdminFractionAttachEdit(playerid, D_ADMIN + 40, index);
			}
			else if (listitem == 1) // Изменить ID объекта
			{
				ShowAdminFractionAttachEdit(playerid, D_ADMIN + 41, index);
			}
			else // Удалить объект
			{
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно удалили аттач.");
				
				Remove:fraction_attach(
					fraction_item_select[playerid][index][fr_id]
				);
				
				ShowAdminFractionEdit(playerid, D_ADMIN + 38, findex);
			}
		}
		
		case D_ADMIN + 40: // Список аттачей: редактирование имя объекта
		{
			new index = GetPVarInt(playerid, "Admin:FractionAttachSelect");
			
			if (response)
			{
				if (isnull(inputtext))
				{
					ShowAdminFractionAttachEdit(playerid, D_ADMIN + 40, index,
					"Вы ввели некорректное имя.");
					return 1;
				}
		
				Update:fraction_attach_string(fraction_item_select[playerid][index][fr_id], "fr_name", inputtext);
			}
			
			ShowAdminFractionAttachEdit(playerid, D_ADMIN + 39);
		}
		
		case D_ADMIN + 41: // Список аттачей: редактирование ID объекта
		{
			new index = GetPVarInt(playerid, "Admin:FractionAttachSelect");
			
			if (response)
			{
				if (isnull(inputtext) || !IsInt(inputtext))
				{
					ShowAdminFractionAttachEdit(playerid, D_ADMIN + 41, index,
						"Вы ввели ID объекта."
					);
					
					return 1;
				}
				
				new object_id = strval(inputtext);
				
				Update:fraction_attach_int(fraction_item_select[playerid][index][fr_id], "fr_object_id", object_id);
			}
			
			ShowAdminFractionAttachEdit(playerid, D_ADMIN + 39);
		}
		
		case D_ADMIN + 42: // Список аттачей: создание (ID объекта)
		{
			new findex = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (response)
			{
				if (isnull(inputtext) || !IsInt(inputtext))
				{
					ShowAdminFractionAttachEdit(playerid, D_ADMIN + 42, INVALID_PARAM,
						"Вы ввели неверный ID объекта."
					);
					
					return 1;
				}
				
				SetPVarInt(playerid, "Admin:FractionAttachId", strval(inputtext));
				ShowAdminFractionAttachEdit(playerid, D_ADMIN + 43);
			}
			else 
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 38, findex);
			}
		}
		
		case D_ADMIN + 43: // Список аттачей: создание (имя)
		{
			new findex = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (response)
			{
				if (isnull(inputtext))
				{
					ShowAdminFractionAttachEdit(playerid, D_ADMIN + 43, INVALID_PARAM,
						"Вы ввели некорректное имя объекта."
					);
					return 1;
				}
				
				new object_id = GetPVarInt(playerid, "Admin:FractionAttachId");
				
				Create:fraction_attach(
					GetFractionId(findex),
					object_id,
					inputtext
				);
				
				ShowAdminFractionEdit(playerid, D_ADMIN + 38, findex);
				
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно создали аттач.");
			}
			else 
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 32, findex);
			}
		}
		
		case D_ADMIN + 44: // Редактирование фракции: тип финансирования
		{
			new index = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (response)
			{		
				if (listitem == 0)
				{
					ShowAdminFractionEdit(playerid, D_ADMIN + 44, index);
					return 1;
				}
				
				fraction_data[index][fr_type_budget] = listitem;
				Update:fraction_int(index, "fr_type_budget", listitem);
			}
			
			ShowAdminFractionEdit(playerid, D_ADMIN + 28, index);
		}
		
		case D_ADMIN + 45: // Редактирование фракции: бюджет
		{
			new index = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (response)
			{		
				new Float: budget = floatstr(inputtext);
				if ((floatcmp(0.0, budget)) == 1 || floatcmp(99.999, budget) == -1)
				{
					ShowAdminFractionEdit(playerid, D_ADMIN + 45, index,
						"Вы ввели неверный диапазон значения."
					);
					
					return 1;
				}
				
				fraction_data[index][fr_budget] = budget;
				Update:fraction_float(index, "fr_budget", budget);
			}
			
			ShowAdminFractionEdit(playerid, D_ADMIN + 28, index);
		}
		
		case D_ADMIN + 46: // Список предметов
		{
			new index = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (!response)
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 28, index);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowInventoryItemList(playerid, ITEM_LIST_BEGIN, "admin_faction_add_item");
				return 1;
			}
			
			new id = fraction_item_select[playerid][listitem][fr_id];
			
			if (id == ITEM_LIST_NEXT || id == ITEM_LIST_BACK)
			{
				ShowFractionItemList(playerid, dialogid, index, id);
				return 1;
			}
			
			listitem--;
			
			SetPVarInt(playerid, "Admin:FractionItemSelect", listitem);
			
			ShowPlayerDialog(playerid, D_ADMIN + 47, DIALOG_STYLE_LIST, " ", "" #cRED "Удалить предмет",
				"Выбрать", "Назад"
			);
		}

		case D_ADMIN + 47: // Список предметов: действие с выбранным предметом
		{
			new index = GetPVarInt(playerid, "Admin:FractionItemSelect"),
				findex = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (!response)
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 46, findex);
				return 1;
			}
			
			if (listitem == 0) // Удалить
			{
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно удалили предмет.");
				
				Remove:fraction_item(
					fraction_item_select[playerid][index][fr_id]
				);
				
				ShowAdminFractionEdit(playerid, D_ADMIN + 46, findex);
			}
		}
		
		case D_ADMIN + 49: // Удаление фракции
		{
			new index = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (response)
			{
				if (!fraction_data[index][fr_main])
				{
					Remove:fraction_data(index);
					
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно удалили фракцию.");
				}
				else 
				{
					SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете удалить данную фракцию.");
				}
				
				ShowAdminFractionList(playerid);
			}
			else 
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 28, index);
			}
		}
		
		case D_ADMIN + 50: // Лидер
		{
			new index = GetPVarInt(playerid, "Admin:FractionSelect");
			
			if (!response)
			{
				ShowAdminFractionEdit(playerid, D_ADMIN + 28, index);
				return 1;
			}
			
			if (isnull(inputtext))
			{
				if (fraction_data[index][fr_leader_id] == 0)
				{
					ShowAdminFractionEdit(playerid, dialogid, index, "У данной фракции отсутствует лидер.");
					return 1;
				}
				
				new bool: exists = false;
				
				foreach (new i : Player)
				{
					if (!IsPlayerLogged(playerid))
					{
						continue;
					}
					
					if (character_data[i][c_fraction_leader] == index)
					{
						// Сброс фракции
						ResetPlayerFraction(i);
						
						exists = true;
						
						pformat:("Администратор %s[%i] снял Вас с поста лидера фракции - %s.",
							GetPlayerCurrentName(playerid),
							playerid,
							GetFractionName(index)
						);
						
						psend:(playerid, C_LIGHTRED);
						
						break;
					}
				}
				
				if (!exists)
				{
					format:g_string("\
						UPDATE " #__CHARACTERS " \
						SET \
							c_fraction_id = 0, \
							c_fraction_unit_id = 0, \
							c_fraction_rank_id = 0 \
						WHERE c_id = %d",
						fraction_data[index][fr_leader_id]
					);
				}
				
				Update:fraction_int(index, "fr_leader_id", 0);
				
				fraction_data[index][fr_leader_id] = 0;
				clean:<fraction_data[index][fr_leader_name]>;
				
				SendClientMessage(playerid, C_WHITE, #SUCCESS " Вы успешно сняли лидера фракции.");
				ShowAdminFractionEdit(playerid, D_ADMIN + 28, index);
				return 1;
			}
			
			Check:admin_fraction_leader(playerid, index, inputtext);
		}
		
		case D_ADMIN + 51: // Управление описанием местности игрока (/daction)
		{
			if (!response)
			{
				return 1;
			}
			
			new index = g_dialog_select[playerid][listitem];
			
			SetPVarInt(playerid, "Admin:SelectAction", index);
			
			ShowPlayerDialog(playerid, D_ADMIN + 52, DIALOG_STYLE_INPUT, " ",
				"" #DEFAULT " Удаление описания\n\n\
				Ввелите причину удаления:",
				"Да", "Нет"
			);
		}
		
		case D_ADMIN + 52: // Удаление описания
		{
			if (response)
			{
				new index = GetPVarInt(playerid, "Admin:SelectAction"),
					targetid = GetPVarInt(playerid, "Admin:SelectActionTargetId");
				
				if (IsValidDynamic3DTextLabel(character_action[targetid][index][c_text_id]))
				{
					DestroyDynamic3DTextLabel(
						character_action[targetid][index][c_text_id]
					);
				}
				
				Clear:character_action(targetid, index);
				
				pformat:("Администратор %s[%i] удалил Ваше действие. Причина: %s.",
					GetPlayerCurrentName(playerid),
					playerid,
					inputtext
				);
				
				psend:(targetid, C_LIGHTRED);
				
				format:g_small_string("~r~Admin %s(%i) has deleted action %s(%i).",
					GetPlayerCurrentName(playerid),
					playerid,
					GetPlayerCurrentName(targetid),
					targetid
				);

				SendAdminLog(g_small_string);
			}
			
			DeletePVar(playerid, "Admin:SelectAction");
			DeletePVar(playerid, "Admin:SelectActionTargetId");
		}
		
		case D_ADMIN + 53: // Временная установка фракции
		{
			if (!response)
			{
				return 1;
			}
			
			character_data[playerid][c_fraction_index] = listitem;
			
			new rindex = GetFractionRankById(listitem, fraction_data[listitem][fr_join_rank_id]);
			
			if (rindex != INVALID_PARAM)
			{
				character_data[playerid][c_fraction_rank_index] = listitem;
			}
			
			pformat:(#SUCCESS " Вы временно установили себе фракцию: " #cPROJECT "%s" #cWHITE ". " #cGRAY "(/setfraction повторно для снятия)", 
				fraction_data[listitem][fr_name]
			);
			
			psend:(playerid, C_WHITE);
			
			SetPVarInt(playerid, "Admin:SetFraction", true);
		}
		
		case D_ADMIN_CRIME: // CMD:crmanage
		{
			if (!response)
			{
				DeletePVar(playerid, "Admin:CrimeSelect");
				return 1;
			}
			
			if (listitem == 0) 
			{
				ShowAdminCrimeCreate(playerid);
				return 1;
			}
			
			listitem--;
			
			SetPVarInt(playerid, "Admin:CrimeSelect", listitem);
			ShowAdminCrimeEdit(playerid, listitem);
		}
		
		case D_ADMIN_CRIME_CREATE: // CMD:crmanage -> Создать фракцию
		{
			if (!response)
			{
				DeletePVar(playerid, "Admin:CrimeCreateName");
				DeletePVar(playerid, "Admin:CrimeCreateType");
				DeletePVar(playerid, "Admin:CrimeCreateTypeID");
				
				ShowAdminCrimeList(playerid);
				return 1;
			}
	
			switch (listitem) //0=Название. 1=Тип. 2=Создать.
			{
				case 0:
				{
					ShowAdminCrimeCreateName(playerid);
				}
				
				case 1:
				{
					ShowAdminCrimeType(playerid, D_ADMIN_CRIME_CREATE_TYPE);
				}
				
				case 2:
				{
					new empty_slot = GetCrimeEmptySlot();
				
					new bool: crime_index;
				
					clean:<g_small_string>;
					clean:<g_string>;
			
					if (GetPVarString(playerid, "Admin:CrimeCreateName", g_small_string, sizeof g_small_string)
					&& GetPVarString(playerid, "Admin:CrimeCreateType", g_string, sizeof g_string))
					{
						crime_index = true;
					}
					
					if (!crime_index)
					{
						pformat:( #ERROR " Выбраны не все свойства.");
						psend:(playerid, C_WHITE);
						
						ShowAdminCrimeCreate(playerid);
						
						return 1;
					}
					
					GetPVarString(playerid, "Admin:CrimeCreateName", crime_data[empty_slot][cr_name], sizeof crime_data);
					crime_data[empty_slot][cr_type_id] = GetPVarInt(playerid, "Admin:CrimeCreateTypeID") + 1;
					
					new max_money = crtype_data[GetPVarInt(playerid, "Admin:CrimeCreateTypeID")][cr_max_money];
					
					DeletePVar(playerid, "Admin:CrimeCreateName");
					DeletePVar(playerid, "Admin:CrimeCreateType");
					DeletePVar(playerid, "Admin:CrimeCreateTypeID");
					
					Create:crime_data(playerid, empty_slot, max_money);
				}
			}
		}
		
		case D_ADMIN_CRIME_CREATE_NAME: // CMD:crmanage -> Создать фракцию -> Название
		{
			if (!response)
			{
				ShowAdminCrimeCreate(playerid);
				return 1;
			}

			// Проверка на выполнение требований к длине вводимой строки
			if (!IsValidLenghtCrimeName(playerid, D_ADMIN_CRIME_CREATE_NAME, inputtext, "Превышен лимит символов или отправлена пустая строка."))
			{
				return 1;
			}
			
			// Проверка на ввод кириллицы
			if (!IsValidCrimeName(playerid, D_ADMIN_CRIME_CREATE_NAME, inputtext,"Название организации можно задать только латинскими символами."))
			{
				return 1;
			}
			
			// Проверка на наличие одноименных фракций
			if (!IsCrimeNameTwin(playerid, D_ADMIN_CRIME_CREATE_NAME, inputtext,"Организация с таким названием уже существует."))
			{
				return 1;
			}
			
			SetPVarString(playerid, "Admin:CrimeCreateName", inputtext);
			
			ShowAdminCrimeCreate(playerid);
		}
		
		case D_ADMIN_CRIME_CREATE_TYPE:	// CMD:crmanage -> Создать фракцию -> Тип
		{
			if (!response)
			{
				ShowAdminCrimeCreate(playerid);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowAdminCrimeType(playerid, D_ADMIN_CRIME_CREATE_TYPE);
				return 1;
			}
			
			listitem--;
			
			SetPVarInt(playerid, "Admin:CrimeCreateTypeID", listitem);
			SetPVarString(playerid, "Admin:CrimeCreateType", crtype_data[listitem][cr_name]);
			
			ShowAdminCrimeCreate(playerid);
		}
		
		case D_ADMIN_CRIME_EDIT: // CMD:crmanage -> Редактирование фракции
		{
			if (!response)
			{
				ShowAdminCrimeList(playerid);
				return 1;
			}
			
			new crime_index = GetPVarInt(playerid, "Admin:CrimeSelect");
			
			switch (listitem)
			{
				case 0: // Изменить название D_ADMIN_CRIME_EDIT_NAME
				{
					ShowAdminCrimeEditName(playerid);
				}
				
				case 1: // Изменить статус D_ADMIN_CRIME_EDIT_STATUS
				{
					ShowAdminCrimeEditStatus(playerid);
				}
				
				case 2: // Изменить тип D_ADMIN_CRIME_EDIT_TYPE
				{
					ShowAdminCrimeType(playerid, D_ADMIN_CRIME_EDIT_TYPE);
				}
				
				case 3: // Назначить лидера D_ADMIN_CRIME_EDIT_LEADER
				{
					ShowAdminCrimeEditLeader(playerid);
				}
				
				case 4: // Удалить лидера D_ADMIN_CRIME_DELETE_LEADER
				{
					new len = strlen(crime_data[crime_index][cr_leader_name]);

					if (!len)
					{
						pformat:("" #ERROR " Данная фракция не имеет лидера.");
						psend:(playerid, C_WHITE);
						
						ShowAdminCrimeEdit(playerid, crime_index);
						
						return 0;
					}
				
					ShowAdminCrimeDeleteLeader(playerid, crime_index);
				}
				
				case 5: // Удалить фракцию D_ADMIN_CRIME_CONFIRM
				{
					ShowAdminCrimeEditConfirm(playerid, crime_index);
				}
			}
		}
		
		case D_ADMIN_CRIME_EDIT_NAME: // Настройка названия фракции
		{
			new crime_index = GetPVarInt(playerid, "Admin:CrimeSelect");
		
			if (!response)
			{
				ShowAdminCrimeEdit(playerid, crime_index);
				return 1;
			}
			
			// Проверка на выполнение требований к длине вводимой строки
			if (!IsValidLenghtCrimeName(playerid, D_ADMIN_CRIME_EDIT_NAME, inputtext, "Превышен лимит символов или отправлена пустая строка."))
			{
				return 1;
			}
			
			// Проверка на ввод кириллицы
			if (!IsValidCrimeName(playerid, D_ADMIN_CRIME_EDIT_NAME, inputtext, "Название организации можно задать только латинскими символами."))
			{
				return 1;
			}
			
			// Проверка на наличие одноименных фракций
			if (!IsCrimeNameTwin(playerid, D_ADMIN_CRIME_EDIT_NAME, inputtext, "Организация с таким названием уже существует."))
			{
				return 1;
			}
			
			clean:<crime_data[crime_index][cr_name]>;
			strcat(crime_data[crime_index][cr_name], inputtext, MAX_CRIME_NAME);
			
			Update:crime_string(crime_index, "cr_name", crime_data[crime_index][cr_name]);
			
			ShowAdminCrimeEdit(playerid, crime_index);
		}
		
		case D_ADMIN_CRIME_EDIT_STATUS: // Настройка статуса фракции
		{
			new crime_index = GetPVarInt(playerid, "Admin:CrimeSelect");
		
			if (!response)
			{
				ShowAdminCrimeEdit(playerid, crime_index);
				return 1;
			}
			
			crime_data[crime_index][cr_official] = listitem;
			
			Update:crime_int(crime_index, "cr_official", crime_data[crime_index][cr_official]);
			
			ShowAdminCrimeEdit(playerid, crime_index);
		}
		
		case D_ADMIN_CRIME_EDIT_TYPE: // Настройка типа фракции
		{
			new crime_index = GetPVarInt(playerid, "Admin:CrimeSelect");
		
			if (!response)
			{
				ShowAdminCrimeEdit(playerid, crime_index);
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowAdminCrimeType(playerid, D_ADMIN_CRIME_EDIT_TYPE);
				return 1;
			}
			
			listitem--;
			
			crime_data[crime_index][cr_type_id] = listitem + 1;
			
			Update:crime_int(crime_index, "cr_type_id", crime_data[crime_index][cr_type_id]);
			
			ShowAdminCrimeEdit(playerid, crime_index);
		}
		
		case D_ADMIN_CRIME_EDIT_LEADER: // Назначение лидера
		{
			new crime_index = GetPVarInt(playerid, "Admin:CrimeSelect");
		
			if (!response)
			{
				ShowAdminCrimeEdit(playerid, crime_index);
				return 1;
			}
			
			if (!IsValidLenghtCrimeLeader(playerid, D_ADMIN_CRIME_EDIT_LEADER, inputtext, "Превышен лимит символов или отправлена пустая строка."))
			{
				return 1;
			}
			
			if (!IsValidCrimeLeaderName(playerid, D_ADMIN_CRIME_EDIT_LEADER, inputtext, "Имя лидера можно задать только латинскими символами."))
			{
				return 1;
			}
			
			clean:<g_big_string>;
			strcat(g_big_string, inputtext, MAX_PLAYER_NAME);
			
			Check:crime_leader_candidate(playerid, crime_index, g_big_string);
		}
		
		case D_ADMIN_CRIME_DELETE_LEADER: // Удаление лидера
		{
			new crime_index = GetPVarInt(playerid, "Admin:CrimeSelect");
		
			if (!response)
			{
				ShowAdminCrimeEdit(playerid, crime_index);
				return 1;
			}

			new len = strlen(crime_data[crime_index][cr_leader_name]);

			if (!len)
			{
				pformat:("" #ERROR " Данная фракция не имеет лидера.");
				psend:(playerid, C_WHITE);
				
				ShowAdminCrimeEdit(playerid, crime_index);
				
				return 0;
			}
			
			Update:crime_string(crime_index, "cr_leader_name", "");
			
			new crleader_id = GetCrimeLeaderId(crime_index);
			
			if (crleader_id > INVALID_PARAM)
			{
				Clear:crmember_data(crleader_id);
				
				pformat:("" ERROR " Вас сняли с лидерства криминальной организации " #cPROJECT "%s" #cWHITE ".", crime_data[crime_index][cr_name]);
				psend:(crleader_id, C_WHITE);
			}
			
			Destroy:crime_leader(crime_index);
			
			pformat:("" #SUCCESS " Лидер фракции " #cPROJECT "%s" #cWHITE " - " #cGRAY "%s" #cWHITE " успешно удален.",
				crime_data[crime_index][cr_name],
				crime_data[crime_index][cr_leader_name]
			);
			psend:(playerid, C_WHITE);
			
			clean:<crime_data[crime_index][cr_leader_name]>;
			
			ShowAdminCrimeEdit(playerid, crime_index);
		}
		
		case D_ADMIN_CRIME_CONFIRM: // Удаление фракции
		{
			new crime_index = GetPVarInt(playerid, "Admin:CrimeSelect");
		
			if (!response)
			{
				ShowAdminCrimeEdit(playerid, crime_index);
				return 1;
			}
			
			Destroy:crime_data(crime_index);
			
			ClearCrimeMemberDataToIndex(crime_index);
			
			pformat:("" #SUCCESS " Фракция " #cPROJECT "%s" #cWHITE " успешно удалена.",
				crime_data[crime_index][cr_name]
			);
			psend:(playerid, C_WHITE);
			
			ClearCrimeData();
			Load:crime_data();
			DeletePVar(playerid, "Admin:CrimeSelect");
		}
		
		case D_ADMIN_GETBUYCAR:
		{
			if (!response)
			{
				DeletePVar(playerid, "AdminCmd:GetBuyCar");
				return 1;
			}
			
			new targetid = GetPVarInt(playerid, "AdminCmd:GetBuyCar"),
				vehicleid,
				Float: x,
				Float: y,
				Float: z;
			
			if (targetid == INVALID_PARAM)
			{
				return 1;
			}
			
			for (; listitem < MAX_PLAYER_VEHICLES; listitem++)
			{
				if (player_vehicle[targetid][pv_server_id][listitem] <= 0)
				{
					continue;
				}
				
				vehicleid = player_vehicle[targetid][pv_server_id][listitem];
				break;
			}
			
			GetPlayerPos(playerid, x, y, z);
			SetVehiclePos(vehicleid, x, y, z);
			
			format:g_small_string("Admin %s(%i) teleported vehicle (%d).",
				GetUserName(playerid),
				playerid,
				vehicleid
			);

			SendAdminLog(g_small_string);
			DeletePVar(playerid, "AdminCmd:GetBuyCar");
			
			return 1;
		}
	}
	
	return 1;
}

Check:admin_fraction_leader(playerid, index, name[])
{
	format:g_string("SELECT COUNT(c_id) as character_exists, c_id AS character_id FROM " #__CHARACTERS " WHERE c_name = '%q'", name);
	mysql_tquery(db, g_string, "OnAdminFractionLeaderCheck", "dds", playerid, index, name);
}

function OnAdminFractionLeaderCheck(playerid, index, name[])
{
	new is_exists,
		character_id;
	
	cache_get_value_name_int(0, "character_exists", is_exists);
	cache_get_value_name_int(0, "character_id", character_id);
	
	if (!is_exists)
	{
		ShowAdminFractionEdit(playerid, D_ADMIN + 50, index, "Вы ввели неверное имя персонажа.");
		return 1;
	}
	
	is_exists = false;
				
	foreach (new i : Player)
	{
		if (!IsPlayerLogged(i))
		{
			continue;
		}
		
		if (character_data[i][c_id] == character_id)
		{
			character_data[i][c_fraction_leader] = 
			character_data[i][c_fraction_index] = index;
			character_data[i][c_fraction_rank_index] =
			character_data[i][c_fraction_unit_index] = INVALID_PARAM;
			
			Update:character_int(i, "c_fraction_id", GetFractionId(index));
			Update:character_int(i, "c_fraction_unit_id", 0);
			Update:character_int(i, "c_fraction_rank_id", 0);
			is_exists = true;
			
			pformat:("Администратор %s[%i] назначил Вас лидером фракции - %s.",
				GetPlayerCurrentName(playerid),
				playerid,
				GetFractionName(index)
			);
			
			psend:(i, C_LIGHTRED);
			
			break;
		}
	}
	
	fraction_data[index][fr_leader_id] = character_id;
	clean:<fraction_data[index][fr_leader_name]>;
	strcat(fraction_data[index][fr_leader_name], name, MAX_PLAYER_NAME);
	
	if (!is_exists)
	{
		format:g_string("\
			UPDATE " #__CHARACTERS " \
			SET \
				c_fraction_id = %d, \
				c_fraction_unit_id = 0, \
				c_fraction_rank_id = 0 \
			WHERE c_id = %d",
			GetFractionId(index),
			character_id
		);
		
		mysql_tquery(db, g_string);
	}
	
	Update:fraction_int(index, "fr_leader_id", character_id);
	
	pformat:(#SUCCESS " Вы успешно назначили " #cPROJECT "%s" #cWHITE " лидером фракции.", name);
	psend:(playerid, C_WHITE);
	
	ShowAdminFractionEdit(playerid, D_ADMIN + 28, index);
	return 1;
}