/*!
	@brief Система появления
	@author Found (evg.savosin)
	@date 16.12.2016, update 28.02.2018
*/

GetSpawnInfo(playerid, &Float: x, &Float: y, &Float: z, &Float: angle, bool: is_after_death = false)
{
	new	bool: is_spawned = false;
		
	if (GetPVarInt(playerid, "Admin:SpectateMode"))
	{
		x = GetPVarFloat(playerid, "Admin:PosX");
		y = GetPVarFloat(playerid, "Admin:PosY");
		z = GetPVarFloat(playerid, "Admin:PosZ");
		angle = GetPVarFloat(playerid, "Admin:PosAngle");
		
		SetPlayerVirtualWorld(playerid, GetPVarInt(playerid, "Admin:World"));
		SetPlayerInterior(playerid, GetPVarInt(playerid, "Admin:Interior"));
		is_spawned = true;
	}
	
	if (IsCharacterArrested(playerid) || GetCharacterRole(playerid) == ROLE_CONVICTED)
	{
		new index;
		
		if (!IsCharacterArrested(playerid))
		{
			index = ImprisonPlayerToJail(playerid);
		}
		else
		{
			index = character_data[playerid][c_arrest_camera];
		}
		
		x = fraction_camera[index][fr_pos_camera][0];
		y = fraction_camera[index][fr_pos_camera][1];
		z = fraction_camera[index][fr_pos_camera][2];
		angle = fraction_camera[index][fr_pos_camera][3];
		
		SetPlayerVirtualWorld(playerid, fraction_camera[index][fr_world]);
		SetPlayerInterior(playerid, fraction_camera[index][fr_int]);
		
		is_spawned = true;
	}
	
	if (!is_after_death 
	&& (!is_spawned 
	&& GetCharacterDeath(playerid) != TYPE_DEATH_NONE 
	|| (character_data[playerid][c_last_time] != 0 
	&& (character_data[playerid][c_last_time] + 900) >= gettime())))
	{
		x = character_data[playerid][c_pos][0]; 
		y = character_data[playerid][c_pos][1];
		z = character_data[playerid][c_pos][2]; 
		angle = character_data[playerid][c_pos][3];
		
		SetPlayerVirtualWorld(playerid, character_data[playerid][c_world]);
		SetPlayerInterior(playerid, character_data[playerid][c_int]);
		
		is_spawned = true;
	}
	
	if (is_spawned)
	{
		return;
	}
	
	if (!is_after_death)
	{
		switch (GetCharacterSettings(playerid, SET_SPAWN))
		{
			case 0 : // Улица
			{
				new spawn_street = GetCharacterSettings(playerid, SET_SPAWN_STREET);
				x = character_spawn_street_info[spawn_street][spawn_street_pos][0]; 
				y = character_spawn_street_info[spawn_street][spawn_street_pos][1]; 
				z = character_spawn_street_info[spawn_street][spawn_street_pos][2];
				angle = character_spawn_street_info[spawn_street][spawn_street_pos][3];
				
				SetPlayerVirtualWorld(playerid, 0);
				SetPlayerInterior(playerid, 0);
				is_spawned = true;
			}
			
			case 1 : // Жилищное помещение
			{
				new index = GetPlayerHouse(playerid);

				if (index != INVALID_PARAM)
				{
					new type = house_data[index][h_int_type];
				
					x = house_settings[type][hset_pos][0];
					y = house_settings[type][hset_pos][1];
					z = house_settings[type][hset_pos][2];
					angle = house_settings[type][hset_pos][3];
					
					SetPlayerVirtualWorld(playerid, GetHouseId(index));
					SetPlayerInterior(playerid, INT_HOUSE);
					is_spawned = true;
				}
				else 
				{
					SetCharacterSettings(playerid, SET_SPAWN, 0);
					Update:character_settings(playerid);
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " Жилищное помещение, в котором Вы проживали, было продано.");
				}
			}
		
			case 2 : // Помещение
			{
				new index = GetPlayerPremise(playerid);
				
				if (index != INVALID_PARAM)
				{
					new type = premise_data[index][pr_int_type];
				
					x = premise_settings[type][pset_pos][0];
					y = premise_settings[type][pset_pos][1];
					z = premise_settings[type][pset_pos][2];
					angle = premise_settings[type][pset_pos][3];
					
					SetPlayerVirtualWorld(playerid, GetPremiseId(index));
					SetPlayerInterior(playerid, INT_PREMISE);
					is_spawned = true;
				}
				else 
				{
					SetCharacterSettings(playerid, SET_SPAWN, 0);
					Update:character_settings(playerid);
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " Помещение, в котором Вы проживали, было продано.");
				}
			}

			case 3 : // Организация
			{
				if (IsFractionMember(playerid))
				{
					new findex = GetFractionMember(playerid),
						uindex = GetFractionMemberUnit(playerid);
					
					if (uindex == INVALID_PARAM 
					&& fraction_data[findex][fr_spawn_pos][0] != 0.0 
					&& fraction_data[findex][fr_spawn_pos][1] != 0.0)
					{
						x = fraction_data[findex][fr_spawn_pos][0];
						y = fraction_data[findex][fr_spawn_pos][1];
						z = fraction_data[findex][fr_spawn_pos][2];
						angle = fraction_data[findex][fr_spawn_pos][3];
						
						SetPlayerInterior(playerid, fraction_data[findex][fr_spawn_int]);
						SetPlayerVirtualWorld(playerid, fraction_data[findex][fr_spawn_world]);
					}
					else 
					{
						x = fraction_unit_data[findex][uindex][fr_pos_x];
						y = fraction_unit_data[findex][uindex][fr_pos_y];
						z = fraction_unit_data[findex][uindex][fr_pos_z];
						angle = fraction_unit_data[findex][uindex][fr_pos_angle];
						
						SetPlayerInterior(playerid, fraction_unit_data[findex][uindex][fr_int]);
						SetPlayerVirtualWorld(playerid, fraction_unit_data[findex][uindex][fr_world]);
					}
					
					is_spawned = true;
				}
				else 
				{
					SetCharacterSettings(playerid, SET_SPAWN, 0);
					Update:character_settings(playerid);
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы были исключены из организации, в которой состояли.");
				}
			}
			
			case 4 : // Последняя позиция
			{
				x = character_data[playerid][c_pos][0];
				y = character_data[playerid][c_pos][1];
				z = character_data[playerid][c_pos][2];
				angle = character_data[playerid][c_pos][3];
				
				SetPlayerVirtualWorld(playerid, character_data[playerid][c_world]);
				SetPlayerInterior(playerid, character_data[playerid][c_int]);
				is_spawned = true;
			}
		}
	}
	
	if (!is_spawned)
	{
		new spawn_street = GetCharacterSettings(playerid, SET_SPAWN_STREET);
		x = character_spawn_street_info[spawn_street][spawn_street_pos][0]; 
		y = character_spawn_street_info[spawn_street][spawn_street_pos][1]; 
		z = character_spawn_street_info[spawn_street][spawn_street_pos][2];
		angle = character_spawn_street_info[spawn_street][spawn_street_pos][3];
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerInterior(playerid, 0);
	}
}