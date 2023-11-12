/*!
	@brief Система урона
	@author Found (evg.savosin)
	@date 26.04.2017
*/

// Public function
Player_OnPlayerTakeDamage(playerid, issuerid, Float: amount, weaponid, bodypart) 
{
	new bool: is_write_attack_name;
	
	if (issuerid != INVALID_PLAYER_ID)
	{
		character_data[playerid][c_attack_weapon_id] = weaponid;
		
		switch(weaponid)
		{
			case 0 :
			{
				if (GetPVarInt(issuerid, "Player:UseKnife"))
				{
					clean:<character_data[issuerid][c_attack_name_cold]>;
					strcat(character_data[issuerid][c_attack_name_cold], GetCharacterName(playerid), MAX_PLAYER_NAME);
					character_data[playerid][c_attack_weapon_id] = 1;
				}
				else 
				{
					clean:<character_data[issuerid][c_attack_name_fist]>;
					strcat(character_data[issuerid][c_attack_name_fist], GetCharacterName(playerid), MAX_PLAYER_NAME);
				}
				
				is_write_attack_name = true;
			}
			
			case 1 .. 15 :
			{
				clean:<character_data[issuerid][c_attack_name_cold]>;
				strcat(character_data[issuerid][c_attack_name_cold], GetCharacterName(playerid), MAX_PLAYER_NAME);
				is_write_attack_name = true;
			}
		}
		
		if (GetPVarInt(issuerid, "Player:CorpseCamera"))
		{
			clean:<character_data[playerid][c_attack_name_camera]>;
			strcat(character_data[playerid][c_attack_name_camera], GetCharacterName(issuerid), MAX_PLAYER_NAME);
		}
		
		if (is_write_attack_name)
		{
			SetPVarInt(playerid, "Player:AttackNameTime", gettime());
		}
	}
	
	if (GetCharacterDeath(playerid) != TYPE_DEATH_DIED)
	{
		switch(weaponid)
		{
			case 0 :
			{
				if (GetPVarInt(issuerid, "Player:UseKnife"))
				{
					amount += 15.0;
					weaponid = WEAPON_KNIFE;
				}
			}
			
			case WEAPON_KATANA :
			{
				amount += 25.0;
			}
			
			case WEAPON_COLT45 : 
			{
				amount += 15.75;
			}
			
			case WEAPON_SILENCED : 
			{
				if (GetPVarInt(issuerid, "Player:Taser"))
				{
					amount = 0;
					
					SetPVarInt(playerid, "Player:Stunned", 30);
					TogglePlayerControllable(playerid, false);
					
					format:g_small_string("Оглушил%s %s", 
						EndWordSex(playerid), 
						GetPlayerCurrentName(playerid)
					);
					
					SendRPMessage(ACTION_AME, issuerid, g_small_string);
					
					ApplyAnimation(playerid, "CRACK", "crckdeth4", 4.0, 0, 0, 0, 1, 0, 1);
					
					SendClientMessage(playerid, C_WHITE, !#DEFAULT " Вы были оглушены электрошокером на 30 секунд.");
				}
				else 
				{
					amount += 11.8;
				}
			}
			
			case WEAPON_DEAGLE : 
			{
				amount += 3.8;
			}
			
			case WEAPON_SHOTGUN : 
			{
				amount += 30.0;
			}
			
			case WEAPON_SAWEDOFF :
			{
				amount += 15.0;
			}
			
			case WEAPON_SHOTGSPA : 
			{
				amount += 8.05;
			}
			
			case WEAPON_UZI : 
			{
				amount += 11.5;
			}
			
			case WEAPON_MP5 : 
			{
				amount += 15.75;
			}
			
			case WEAPON_AK47 : 
			{
				amount += 25.5;
			}
			
			case WEAPON_M4 : 
			{
				amount += 20.1;
			}
			
			case WEAPON_TEC9 : 
			{
				amount += 9.4;
			}
			
			case WEAPON_RIFLE : 
			{
				amount += 11.25;
			}
			
			case WEAPON_SNIPER : 
			{
				amount += 35.75;
			}

			case WEAPON_BRASSKNUCKLE:
			{
				amount += 2.0;
			}
		}
	}
	
	if (IsArmourExistsAtPlayer(playerid))
	{
		new armour_type = GetArmourType(playerid), 
			index = GetInventoryIndexById(playerid, GetArmourItemId(playerid));
		
		// Если есть бронежилет, то уменьшаем урон в зависимости от бронежилета
		amount -= (armour_type == TYPE_ARMOUR_LIGHT ? (amount * 0.5) : (amount * 0.8));
		SetArmourValue(playerid, (GetArmourValue(playerid) - 10));
		SetInventoryEnumItem(playerid, index, TYPE_INV_PLAYER, inv_param_2, (GetArmourValue(playerid) - 10));
		
		if (IsArmourWornout(playerid)) /// Если изношен
		{
			if (index != INVALID_PARAM)
			{
				Update:item_data(playerid, index, TYPE_INV_PLAYER, _, _, _, true);
			}
			
			Clear:armour_data(playerid);
		}
	}
	
	new Float: health_diff = (GetCharacterHealth(playerid) - amount);
	SetPlayerHealth(playerid, (health_diff < 0.0 ? 0.0 : health_diff));
	
	AddDamageForPlayer(
		playerid, 
		amount, 
		weaponid, 
		bodypart, 
		issuerid
	);
	
    return;
}