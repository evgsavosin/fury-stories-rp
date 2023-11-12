/*!
	@brief Диалоги для систем транспорта
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

function Vehicle_OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	strglobalclear();
	
	switch(dialogid)
	{
		case D_CAR - 1 :
		{
			return cmd_clist(playerid);
		}
		
		case D_CAR :
		{
			if (!response)
			{
				Clear:vehicle_pvar(playerid);
				return 1;
			}
			
			new index = g_dialog_select[playerid][listitem],
				id = player_vehicle[playerid][pv_id][index],
				vehicleid = player_vehicle[playerid][pv_server_id][index];
				
			SetPVarInt(playerid, "Vehicle:Select", vehicleid);
			
			if (!IsOwnerVehicle(playerid, vehicleid))
			{
				return 1;
			}
			
			if (vehicleid != 0)
			{
				ShowVehicleListControl(playerid, vehicleid);
			}
			else 
			{
				if (GetCountSpawnedVehicle(playerid) >= MAX_SPAWNED_VEHICLES)
				{
					ShowPlayerDialog(playerid, D_CAR - 1, DIALOG_STYLE_MSGBOX, " ", 
						"" #DEFAULT " Информация\n\n\
						Внимание! Данный транспорт не вызван на сервере.\n\
						Для того, чтобы его вызвать, Вам необходимо убрать один из вызванных Ваших транспортов.",
						"Назад", ""
					);
				}
				else 
				{
					new server_tick = GetTickCount();
					
					if (GetPVarInt(playerid, "TimeMySQL:LoadVehicle") > server_tick)
					{
						SendClientMessage(playerid, C_WHITE, !PLAYER_NO_FLOOD);
						return 1;
					}
					
					format:g_string("SELECT * FROM " #__VEHICLES " WHERE v_id = %i",
						id
					);
					
					mysql_tquery(db, g_string, "OnVehicleLoad", "ii", playerid, false);
					
					SetPVarInt(playerid, "TimeMySQL:LoadVehicle", server_tick + 10000);
				}
			}
		}
		
		case D_CAR + 1 :
		{
			if (!response)
			{
				cmd_clist(playerid);
				return 1;
			}
			
			new vehicleid = GetPVarInt(playerid, "Vehicle:Select"),
				index;
			
			if (!IsOwnerVehicle(playerid, vehicleid))
			{
				return 1;
			}
			
			if (listitem == 0)
			{
				ShowVehicleInformation(playerid, vehicle_data[vehicleid][v_model], vehicleid, D_CAR + 2, "Назад");
			}
			else if (listitem == 1)
			{
				SetPVarInt(playerid, "Vehicle:UseClist", 1);
				ShowVehicleMenu(playerid, vehicleid);
			}
			else if (listitem == 2) // убрать транспорт
			{
				index = GetPlayerVehicleIndexByServerId(playerid, vehicleid);
				if (player_vehicle[playerid][pv_delete][index])
				{
					KillTimer(vehicle_data[vehicleid][v_del_timer]);
					vehicle_data[vehicleid][v_del_timer] = INVALID_PARAM;

					player_vehicle[playerid][pv_delete][index] = false;
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы отменили удаление транспорта.");
				}
				else 
				{
					player_vehicle[playerid][pv_delete][index] = true;
					
					Destroy:vehicle_data(playerid, vehicleid, 1000 * 60 * 3, DELVEH_BY_PLAYER);
					
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " Ваш транспорт будет убран через 3 минуты. Отменить удаление можно в меню транспорта.");
				}
			}
		}
		
		case D_CAR + 2 :
		{
			ShowVehicleListControl(playerid, GetPVarInt(playerid, "Vehicle:Select"));
			return 1;
		}
		
		case D_CAR + 3 :
		{
			if (!response)
			{
				if (GetPVarInt(playerid, "Vehicle:UseClist"))
				{
					ShowVehicleListControl(playerid, GetPVarInt(playerid, "Vehicle:Select"));
					DeletePVar(playerid, "Vehicle:UseClist");
					
					return 1;
				}
				
				Clear:vehicle_pvar(playerid);
				return 1;
			}
			
			new vehicleid = GetPVarInt(playerid, "Vehicle:Select");
			
			if (IsBikeVehicle(vehicleid) && IsPlayerInVehicle(playerid, vehicleid))
			{
				if (listitem == 0)
				{
					cmd_park(playerid);
				}

				if (listitem == 1)
				{
					cmd_clock(playerid);
				}

				if (listitem == 2)
				{
					if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
					{
						cmd_unrentcar(playerid);
					}
					else
					{
						cmd_sellcar(playerid);
					}
					
					return 1;
				}

				if (listitem == 3)
				{
					cmd_swapcar(playerid);
					return 1;
				}

				if (listitem == 4)
				{
					cmd_trustcar(playerid);
					return 1;
				}

				ShowVehicleMenu(playerid, vehicleid);

				return 1;
			}
			else if (IsBikeVehicle(vehicleid) && !IsPlayerInVehicle(playerid, vehicleid))
			{
				if (listitem == 0)
				{
					SetVehicleToRespawn(vehicleid);
				}

				if (listitem == 1)
				{
					cmd_clock(playerid);
				}

				if (listitem == 2)
				{
					if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
					{
						cmd_unrentcar(playerid);
					}
					else
					{
						cmd_sellcar(playerid);
					}
					
					return 1;
				}

				if (listitem == 3)
				{
					cmd_swapcar(playerid);
					return 1;
				}

				if (listitem == 4)
				{
					cmd_trustcar(playerid);
					return 1;
				}

				ShowVehicleMenu(playerid, vehicleid);

				return 1;
			}

			if (IsPlayerInVehicle(playerid, vehicleid))
			{
				switch(listitem)
				{
					case 0:
					{
						cmd_en(playerid);
					}
					
					case 1:
					{
						if (IsBikeVehicle(vehicleid))
						{
							return 1;
						}
						
						CheckVehicleLight(playerid, vehicleid);
					}
					
					case 2:
					{
						if (IsBikeVehicle(vehicleid))
						{
							return 1;
						}
						
						ShowVehicleMenuWindow(playerid, vehicleid);
						return 1;
					}
					
					case 3:
					{
						if (IsBikeVehicle(vehicleid))
						{
							return 1;
						}

						CheckVehicleLimit(vehicleid);
					}
					
					case 4: // радиостанция
					{
						if (IsBikeVehicle(vehicleid))
						{
							return 1;
						}

						if (vehicle_data[vehicleid][v_radio])
						{
							vehicle_data[vehicleid][v_radio] = false;
						}
						else
						{
							vehicle_data[vehicleid][v_radio] = true;
						}
			
						SendClientMessage(playerid, C_WHITE, vehicle_data[vehicleid][v_radio] ? (#DEFAULT " Вы включили радиостанцию.") : (#DEFAULT " Вы выключили радиостанцию."));
					}
					
					case 5: // капот
					{
						if (IsBikeVehicle(vehicleid))
						{
							return 1;
						}
						
						cmd_hood(playerid);
					}
					
					case 6: // багажник 
					{
						if (IsBikeVehicle(vehicleid))
						{
							return 1;
						}
						
						cmd_boot(playerid);
					}
					
					case 7:
					{
						cmd_park(playerid);
					}
					
					case 8:
					{
						cmd_clock(playerid);
					}
					
					case 9:
					{
						if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
						{
							cmd_unrentcar(playerid);
						}
						else
						{
							cmd_sellcar(playerid);
						}
						
						return 1;
					}
					
					case 10:
					{
						cmd_swapcar(playerid);
						return 1;
					}
					
					case 11:
					{
						cmd_trustcar(playerid);
						return 1;
					}
				}
			}
			else
			{
				switch(listitem)
				{
					case 0 :
					{
						if (IsBikeVehicle(vehicleid))
						{
							return 1;
						}
						
						cmd_hood(playerid);
					}
					
					case 1 :
					{
						if (IsBikeVehicle(vehicleid))
						{
							return 1;
						}
						
						cmd_boot(playerid);
					}
					
					case 2 :
					{
						SetVehicleToRespawn(vehicleid);
					}
					
					case 3 :
					{
						CheckVehicleLock(playerid, vehicleid);
					}
					
					case 4:
					{
						cmd_cdetails(playerid);
						return 1;
					}
					
					case 5 :
					{
						if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
						{
							cmd_unrentcar(playerid);
						}
						else
						{
							cmd_sellcar(playerid);
						}
						
						return 1;
					}
					
					case 6 :
					{
						cmd_swapcar(playerid);
						return 1;
					}
					
					case 7 :
					{
						cmd_trustcar(playerid);
						return 1;
					}
				}
			}
			
			ShowVehicleMenu(playerid, vehicleid);
		}
		
		case D_CAR + 4 :
		{
			new vehicleid = GetPVarInt(playerid, "Vehicle:Select");
				
			if (!response)
			{
				ShowVehicleMenu(playerid, vehicleid);
				return 1;
			}
							 
			switch(listitem)
			{
				case 0 : 
				{
					cmd_window(playerid, "l");
				}
				
				case 1 : 
				{
					cmd_window(playerid, "r");
				}
				
				case 2 : 
				{
					cmd_window(playerid, "rl");
				}
				
				case 3 : 
				{
					cmd_window(playerid, "rr");
				}
			}
			
			ShowVehicleMenuWindow(playerid, vehicleid);
		}
		
		case D_CAR + 5 :
		{
			if (!response)
			{
				if (GetPVarInt(playerid, "Vehicle:UseClist"))
				{
					ShowVehicleListControl(playerid, GetPVarInt(playerid, "Vehicle:Select"));
					DeletePVar(playerid, "Vehicle:UseClist");
					return 1;
				}
				
				Clear:vehicle_pvar(playerid);
				return 1;
			}
			
			new targetid = strval(inputtext),
				vehicleid = GetPVarInt(playerid, "Vehicle:Select");
			
			if (isnull(inputtext) || !IsInt(inputtext) 
			|| !IsPlayerLogged(targetid)
			|| targetid == playerid)
			{
				ShowVehicleSellPlayer(playerid, "" #cRED "Вы ввели неверный ID игрока.");
				return 1;
			}
			
			if (!IsPlayerAroundOfPlayer(playerid, targetid))
			{
				ShowVehicleSellPlayer(playerid, "Данный игрок находится далеко от Вас.");
				return 1;
			}
			
			ShowVehicleSellSumm(playerid, vehicleid);
			SetPVarInt(playerid, "Player:TargetId", targetid);
		}
		
		case D_CAR + 6 :
		{
			if (!response)
			{
				ShowPlayerDialog(playerid, D_CAR + 5, DIALOG_STYLE_MSGBOX, " ", 
					"" #DEFAULT " Продажа транспорта\n\n\
					Продать транспорт можно только игроку.\n\
					Введите ID игрока, которому Вы хотите продать транспорт:", 
					"Выбрать", "Закрыть" 
				);
				
				return 1;
			}
			
			new targetid = GetPVarInt(playerid, "Player:TargetId"),
				money = strval(inputtext),
				vehicleid = GetPVarInt(playerid, "Vehicle:Select");
			
			if (isnull(inputtext) || !IsInt(inputtext) 
			|| !(GetMinSaleVehiclePrice(vehicleid) <= money <= GetMaxSaleVehiclePrice(vehicleid)))
			{
				ShowVehicleSellSumm(playerid, vehicleid);
				return 1;
			}
			
			if (!IsPlayerLogged(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid))
			{
				ShowVehicleSellSumm(playerid, vehicleid, "Игрок находится далеко от Вас либо его нет в сети.");
				return 1;
			}
		
			pformat:("" #SUCCESS " Вы отправили предложение о продаже %s " #cPROJECT "%s" #cWHITE ".",
				GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name),
				GetPlayerCurrentName(targetid)
			);
			
			psend:(playerid, C_WHITE);
			
			// -
			
			format:g_string("" #DEFAULT " Предложение\n\n\
				" #cPROJECT "%s" #cWHITE " предлагает Вам купить %s за " #cGREEN "$%i" #cWHITE ".\n\
				Вы принимаете предложение?",
				GetPlayerCurrentName(playerid),
				GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name),
				money
			);
			
			ShowPlayerDialog(targetid, D_CAR + 7, DIALOG_STYLE_MSGBOX, " ", 
				g_string,
				"Да", "Нет"
			);
			
			SetPVarInt(targetid, "Vehicle:OwnerId", playerid);
			SetPVarInt(targetid, "Vehicle:OwnerSelect", vehicleid);
			SetPVarInt(targetid, "Vehicle:Price", money);
		}
		
		case D_CAR + 7 :
		{
			new ownerid = GetPVarInt(playerid, "Vehicle:OwnerId"),
				vehicleid = GetPVarInt(playerid, "Vehicle:OwnerSelect"),
				money = GetPVarInt(playerid, "Vehicle:Price");
				
			if (response)
			{
				if (SellVehicleToPlayer(ownerid, vehicleid, playerid, money))
				{
					pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " принял Ваше предложение.",
						GetPlayerCurrentName(playerid)
					);
					
					psend:(ownerid, C_WHITE);
					
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы приняли предложение.");
				}
			}
			else 
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " отклонил Ваше предложение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы отклонили предложение.");
			}
			
			DeletePVar(playerid, "Vehicle:OwnerId");
			DeletePVar(playerid, "Vehicle:OwnerSelect");
			DeletePVar(playerid, "Vehicle:Price");
		}
		
		case D_CAR + 8 :
		{
			if (!response)
			{
				if (GetPVarInt(playerid, "Vehicle:UseClist"))
				{
					ShowVehicleListControl(playerid, GetPVarInt(playerid, "Vehicle:Select"));
					DeletePVar(playerid, "Vehicle:UseClist");
					return 1;
				}
				
				Clear:vehicle_pvar(playerid);
				
				return 1;
			}
			
			new index = g_dialog_select[playerid][listitem],
				vehicleid = player_vehicle[playerid][pv_server_id][index];
			
			if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
			{	
				ShowVehicleList(playerid, D_CAR + 8);
				SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы не можете обменять арендованный транспорт.");
				return 1;
			}
			
			SetPVarInt(playerid, "Vehicle:SelectSwap", vehicleid);
			
			ShowVehicleSellSwap(playerid);
		}
		
		case D_CAR + 9 :
		{
			if (!response)
			{
				cmd_swapcar(playerid);
				return 1;
			}
			
			new targetid,
				vehicleid = GetPVarInt(playerid, "Vehicle:SelectSwap");
			
			if (isnull(inputtext) || !IsInt(inputtext) 
			|| !IsPlayerLogged(targetid = strval(inputtext))
			|| targetid == playerid)
			{
				ShowVehicleSellSwap(playerid, "Вы ввели неверный ID игрока.");
				return 1;
			}
			
			if (!IsPlayerAroundOfPlayer(playerid, targetid))
			{
				ShowVehicleSellSwap(playerid, "Данный игрок находится далеко от Вас.");
				return 1;
			}
			
			if (ShowVehicleList(targetid, D_CAR + 10, "Выбрать", "Отказ"))
			{
				pformat:("" #SUCCESS " Вы отправили предложение об обмене %s " #cPROJECT "%s" #cWHITE ".",
					GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name),
					GetPlayerCurrentName(targetid)
				);
				
				psend:(playerid, C_WHITE);
				
				// ---
			
				pformat:("" #SUCCESS " %s предлагает обменяться с будучи выбранным Вашим транспортом на " #cPROJECT "%s" #cWHITE ".",
					GetPlayerCurrentName(playerid),
					GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name)
				);
				
				psend:(targetid, C_WHITE);
				
				SetPVarInt(targetid, "Player:OwnerId", playerid);
				SetPVarInt(playerid, "Player:TargetId", targetid);
			}
			else 
			{
				pformat:("" #ERROR " У игрока " #cPROJECT "%s" #cWHITE " отсутствует транспорт для обмена.",
					GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name),
					GetPlayerCurrentName(targetid)
				);
				
				psend:(playerid, C_WHITE);
			}
		}
		
		case D_CAR + 10 :
		{
			new index = g_dialog_select[playerid][listitem],
				vehicleid = player_vehicle[playerid][pv_server_id][index],
				ownerid = GetPVarInt(playerid, "Player:OwnerId"),
				owner_vehicleid = GetPVarInt(ownerid, "Vehicle:SelectSwap");
			
			if (response)
			{	
				if (vehicleid == 0)
				{
					ShowVehicleList(playerid, D_CAR + 10, "Выбрать", "Отказ");
					SendClientMessage(playerid, C_WHITE, !#ERROR " Транспорт должен быть вызван.");
					return 1;
				}
				
				if (GetVehicleTypeBought(vehicleid) == TYPE_BUY_RENT)
				{	
					ShowVehicleList(playerid, D_CAR + 10, "Выбрать", "Отказ");
					SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не можете обменять арендованный транспорт.");
					return 1;
				}
				
				SetPVarInt(playerid, "Vehicle:SelectSwap", vehicleid);
				
				format:g_string("" #DEFAULT " Обмен транспорта\n\n\
					Вы действительно хотите обменять Ваш транспорт " #cPROJECT "%s" #cWHITE "\n\
					на транспорт игрока " #cGRAY "%s" #cWHITE " - " #cPROJECT "%s" #cWHITE "?",
					GetVehicleInfo(vehicle_data[owner_vehicleid][v_model], v_name),
					GetPlayerCurrentName(playerid),
					GetVehicleInfo(vehicle_data[vehicleid][v_model], v_name)
				);
				
				ShowPlayerDialog(ownerid, D_CAR + 11, DIALOG_STYLE_MSGBOX, " ", g_string, "Далее", "Назад");
				
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " подтверждает обмен транспортными средствами.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
			}
			else 
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " отклонил Ваше предложение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(ownerid, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы отклонили предложение.");
				
				DeletePVar(playerid, "Player:OwnerId");
				DeletePVar(ownerid, "Player:TargetId");
				DeletePVar(ownerid, "Vehicle:SelectSwap");
			}
		}
		
		case D_CAR + 11 :
		{
			new targetid = GetPVarInt(playerid, "Player:TargetId");
			
			if (response)
			{	
				if (SwapVehicleToPlayer(playerid, 
					GetPVarInt(playerid, "Vehicle:SelectSwap"), 
					targetid, 
					GetPVarInt(targetid, "Vehicle:SelectSwap")) 
				)
				{
					pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " принял Ваше предложение.",
						GetPlayerCurrentName(playerid)
					);
					
					psend:(targetid, C_WHITE);
					
					SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы приняли предложение.");
				}
			}
			else 
			{
				pformat:("" #DEFAULT " " #cPROJECT "%s" #cWHITE " отклонил Ваше предложение.",
					GetPlayerCurrentName(playerid)
				);
				
				psend:(targetid, C_WHITE);
				
				SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы отклонили предложение.");
			}
			
			DeletePVar(targetid, "Player:OwnerId");
			DeletePVar(targetid, "Vehicle:SelectSwap");
			DeletePVar(playerid, "Player:TargetId");
			DeletePVar(playerid, "Vehicle:SelectSwap");
		}
		
		case D_CAR + 12 :
		{
			if (!response)
			{
				if (GetPVarInt(playerid, "Vehicle:UseClist"))
				{
					ShowVehicleListControl(playerid, GetPVarInt(playerid, "Vehicle:Select"));
					DeletePVar(playerid, "Vehicle:UseClist");
					return 1;
				}
				
				Clear:vehicle_pvar(playerid);
				
				return 1;
			}
			
			new targetid;
			
			if (isnull(inputtext) || !IsInt(inputtext) 
			|| !IsPlayerLogged(targetid = strval(inputtext))
			|| targetid == playerid)
			{
				ShowPlayerDialog(playerid, D_CAR + 12, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Доверенность\n\n\
					Вы можете предоставить доступ на временной основе игроку.\n\
					Введите ID игрока, которому Вы хотите доверить транспорт:\n\n\
					" #cRED "Вы ввели неверный ID игрока.", 
					"Выбрать", "Закрыть" 
				);
				
				return 1;
			}
			
			if (!IsPlayerAroundOfPlayer(playerid, targetid))
			{
				ShowPlayerDialog(playerid, D_CAR + 12, DIALOG_STYLE_INPUT, " ", 
					"" #DEFAULT " Доверенность\n\n\
					Вы можете предоставить доступ на временной основе игроку.\n\
					Введите ID игрока, которому Вы хотите доверить транспорт:\n\n\
					" #cRED "Данный игрок находится далеко от Вас.", 
					"Выбрать", "Закрыть" 
				);
				
				return 1;
			}
			
			pformat:("" #SUCCESS " " #cPROJECT "%s" #cWHITE " доверил временно Вам свой транспорт.",
				GetPlayerCurrentName(playerid)
			);
			
			psend:(targetid, C_WHITE);
			
			pformat:("" #SUCCESS " Вы временно доверили свой транспорт " #cPROJECT "%s" #cWHITE ".",
				GetPlayerCurrentName(targetid)
			);
			
			psend:(playerid, C_WHITE);
			
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Для того, чтобы забрать доступ у всех игроков, введите " #cPROJECT "/taketrustcar" #cWHITE ".");
			
			SetPVarInt(targetid, "Vehicle:Trust", GetCharacterId(playerid));
		}
		
		case D_CAR + 13:
		{
			if (!response)
			{
				return 1;
			}
			
			new vehicleid = GetVehicleAroundOfPlayer(playerid),
				panels, 
				doors, 
				lights,
				tires;
				
			GetVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
	
			new front_left_panel, 
				front_right_panel, 
				rear_left_panel, 
				rear_right_panel, 
				windshield, 
				front_bumper, 
				rear_bumper;
			
			DecodeDamagePanels(
				panels, 
				front_left_panel, 
				front_right_panel, 
				rear_left_panel, 
				rear_right_panel, 
				windshield, 
				front_bumper, 
				rear_bumper
			);
				
			if (listitem == 0)
			{
				front_bumper = 3;
			}
			else if (listitem == 1)
			{
				rear_bumper = 3;
			}
			
			panels = EncodeDamagePanels(
				front_left_panel, 
				front_right_panel, 
				rear_left_panel, 
				rear_right_panel, 
				windshield, 
				front_bumper, 
				rear_bumper
			);
			
			UpdateVehicleDamageStatus(vehicleid, panels, doors, lights, tires);
		}
		
		case D_CAR + 14: // Брелок
		{
			if (!response)
			{
				return 1;
			}
			
			new vehicleid = g_dialog_select[playerid][listitem];
			ShowKeyAlarm(playerid, true, vehicleid);
		}
		
		case D_CAR + 15:
		{
			if (!response)
			{
				return 1;
			}
			
			new vehicleid = GetPVarInt(playerid, "Vehicle:Select");
			
			BreakRentVehicle(playerid, vehicleid);
		}
	}
	
	return 1;
}