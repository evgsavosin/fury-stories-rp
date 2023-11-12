/*!
	@brief Основные функции
	@author Found (evg.savosin)
	@date 16.12.2016, update 16.01.2018
*/

// Common functions
function strglobalclear()
{
	g_small_string[0] =
	g_string[0] = 
	g_big_string[0] = EOS;
}

strreplace(string[], find, replace) 
{
	for (new i, j = strlen(string); i < j; i++) 
	{
		if (string[i] != find) 
		{
			continue;
		}
		
		string[i] = replace;
	}
}

strtolower(string[])
{
	for (new i, j = strlen(string); i < j; i++)
	{
		string[i] = tolower(string[i]);
	}
}

// Other functions
GetWeekDay(year, month, day) // From the documentation Pawn Language
{
    if (month <= 2)
	{
        month += 12;
		--year;
   }
	
	new j = year % 100;
    new e = year / 100;
    return (day +  (month + 1) * 26 / 10 + j + j / 4 + e / 4 - 2 * e) % 7;
}  

IsValidPassword(password[])
{
	new len = strlen(password);
		
	if (len < 6 || len > 32)
	{
		return 0;
	}
	
	while (len-- != 0)
	{
		switch(password[len])
		{	
			case 'а' .. 'я', 'А' .. 'Я', '/', '\n', '`', '~', '%', '^', '&', '[', ']', '{', '}', '|', ''', '\\' :
			{
				return 0;
			}
			
			default:
			{
				continue;
			}
		}
	}
	
	return 1;
} 

stock IsValidName(name[]) 
{
	new len = strlen(name),
		bool: valid = false;
		
	if (len < 6 || len > MAX_PLAYER_NAME)
	{
		return 0;
	}
	
	while (len-- != 0)
	{
		switch (name[len])
		{	
			case '0' .. '9', 'а' .. 'я', 'А' .. 'Я', '/', '\n', '`', '~', '%', '^', '&', '[', ']', '{', '}', '|', ''', '-', '+', '(', ')', '=', '$', '#', '@', '!':
			{
				return 0;
			}
			
			case '_' :
			{
				valid = true;
			}
			
			default :
			{
				continue;
			}
		}
	}
	
	return valid ? 1 : 0;
}

stock IsValidVehicleNumber(number[]) 
{
	new len = strlen(number);
		
	if (len < 4 || len > 8)
	{
		return 0;
	}
	
	while (len-- != 0)
	{
		switch (number[len])
		{	
			case 'a' .. 'z', 'а' .. 'я', 'А' .. 'Я', '/', '\n', '`', '~', '%', '^', '&', '[', ']', '{', '}', '|', ''', '+', '(', ')', '=', '$', '#', '@', '!':
			{
				return 0;
			}
			
			default:
			{
				continue;
			}
		}
	}
	
	return 1;
}


IsInt(number[])
{
	new len = strlen(number);
		
	while (len-- != 0)
	{
		switch (number[len])
		{
			case '0' .. '9' :
			{
				continue;
			}
			
			default:
			{
				return 0;
			}
		}
	}
	
	return 1;
}

gmtime(timestamp, &year = 1970, &month = 1, &day = 1, &hour = 0, &minute = 0, &second = 0)
{
	#define SECS_DAY        (24 * 60 * 60)
	#define LEAPYEAR(%0)    (!((%0) % 4) && (((%0) % 100) || !((%0) % 400)))
	#define YEARSIZE(%0)    (LEAPYEAR(%0) ? 366 : 365)
	
	new day_clock,
		_ytab[2][12] = 
		{
			{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
			{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
		};

	year = 1970;
	day_clock = timestamp % SECS_DAY;
	day = timestamp / SECS_DAY;

	second = day_clock % 60;
	minute = (day_clock % 3600) / 60;
	hour = day_clock / 3600;

	while (day >= YEARSIZE(year)) 
	{
		day -= YEARSIZE(year);
		year++;
	}

	month = 0;

	while (day >= _ytab[LEAPYEAR(year)][month]) 
	{
		day -= _ytab[LEAPYEAR(year)][month];
		month++;
	}

	day++;
	month++;
	
	#undef SECS_DAY
	#undef LEAPYEAR
	#undef YEARSIZE
}

GetWeaponSlot(weaponid) 
{
    switch (weaponid) 
    {
        case 0, 1: 
		{
			return 0; 
		}
        
		case 2 .. 9: 
		{
			return 1; 
        }
		
		case 22 .. 24: 
		{
			return 2; 
        }
		
		case 25 .. 27: 
		{
			return 3; 
        }
		
		case 28, 29, 32: 
		{
			return 4; 
		}
        
		case 30, 31: 
		{
			return 5;
		}
        
		case 33, 34: 
		{
			return 6;
		}
        
		case 35 .. 38: 
		{
			return 7; 
        }
		
		case 16 .. 18, 39 : 
		{
			return 8; 
        }
		
		case 41 .. 43: 
		{
			return 9; 
        }
		
		case 10 .. 15: 
		{
			return 10; 
        }
		
		case 44 .. 46: 
		{
			return 11; 
        }
		
		case 40: 
		{
			return 12; 
		}
	} 
	
    return -1; 
}  

GenerateBase32String(string[], size)
{
	clean:<string>;
	
	for (new i; i < size; i++)
	{
		format(string, size, "%s%c", string,
			random(2) == 1 ? (random(90 - 65) + 65) : (random(55 - 50) + 50)
		);
	}
}

RemovePlayerWeapon(playerid, weaponid)
{
    if (!(0 <= weaponid <= 50))
	{
        return;
	}
	
	new weapon			[	MAX_WEAPON_SLOTS	], 
		ammo			[	MAX_WEAPON_SLOTS	],
		i;
	
	i = 0x0;
 
	do
	{
        GetPlayerWeaponData(playerid, i, weapon[i], ammo[i]);
	}
	while (++i < MAX_WEAPON_SLOTS);
	
	ResetPlayerWeapons(playerid);
	
	i = 0x0;
    do
	{	
        if (weapon[i] == weaponid)
		{
            continue;
		}
		
        GivePlayerWeapon(playerid, weapon[i], ammo[i]);
	}
	while (++i < MAX_WEAPON_SLOTS);
	
    GivePlayerWeapon(playerid, 0, 1);
}

SecondToMinute(seconds, &to_minute = 0, &to_second = 0)
{
	if (seconds > 59)
	{
		to_minute = floatround(seconds / 60);
		to_second = floatround(seconds - (to_minute * 60));
	}
	else 
	{
		to_second = seconds;
	}
}

stock GetWeaponModel(weapon_id)
{
	switch(weapon_id)
	{
		case 1 :
		{
			return 331;
		}
		
		case 2 .. 8 : 
		{
			return 331 + weapon_id;
		}
		
		case 9 :
		{
			return 341;
		}
		
		case 10 .. 15 :
		{
			return 311 + weapon_id;
		}
		
		case 16 .. 18 :
		{
			return 326 + weapon_id;
		}
		
		case 22 .. 29, 34 .. 39, 41, 42 : 
		{
			return weapon_id + 324;
		}
		
		case 30, 31, 46 : 
		{
			return weapon_id + 325;
		}
		
		case 32 : 
		{
			return 372;
		}
	}
	
	return 0;
}

Float: GetDistanceBetweenPoints(Float: x1, Float: y1, Float: z1, Float: x2, Float: y2, Float: z2)
{
    return VectorSize(x1 - x2, y1 - y2, z1 - z2);
}

IsPlayerAroundOfPlayer(playerid, targetid, Float: radius = FACTOR_TRADE_RADIUS)
{
	new Float: x,
		Float: y,
		Float: z;
		
	if (!GetPlayerPos(playerid, x, y, z))
	{
		return 0;
	}
	
	return ((GetCharacterInt(playerid) == GetCharacterInt(targetid))
	&& (GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid))
	&& (IsPlayerInRangeOfPoint(targetid, radius, x, y, z)));
}

Float: TextDrawBackgroundCalculated(Float: begin, Float: end, Float: value, Float: max_value)
{
	if (value > max_value)
	{
		value = max_value;
	}
	
	if (value < 0)
	{
		value = 0;
	}
	
	return begin + ((end - begin) / max_value) * value;
}

Float: GetVehicleSpeed(vehicleid)
{
	new Float: vel_x,
		Float: vel_y,
		Float: vel_z;
	
	GetVehicleVelocity(vehicleid, vel_x, vel_y, vel_z);
	return Float: floatsqroot(vel_x * vel_x + vel_y * vel_y) * 130.0;
}

SetVehicleSpeed(vehicleid, Float: speed)
{
    new Float: x1, 
		Float: y1, 
		Float: z1, 
		Float: x2, 
		Float: y2, 
		Float: z2, 
		Float: angle;
		
    GetVehicleVelocity(vehicleid, x1, y1, z1);
    GetVehiclePos(vehicleid, x2, y2, z2);
    GetVehicleZAngle(vehicleid, angle); 
	
	angle = 360 - angle;
    x1 = (floatsin(angle, degrees) * (speed / 130) + floatcos(angle, degrees) * 0 + x2) - x2;
    y1 = (floatcos(angle, degrees) * (speed / 130) + floatsin(angle, degrees) * 0 + y2) - y2;
	
    SetVehicleVelocity(vehicleid, x1, y1, z1);
}

GetVehicleMaxSeats(const modelid)
{
	if (!(400 <= modelid <= 611))
	{
		return 0;
	}
	
	new const max_seats[] = {
		4, 2, 2, 2, 4, 4, 1, 2, 2, 4, 2, 2, 2, 4, 2, 2, 4, 2, 4, 2, 4, 4, 2, 2, 2,
		1, 4, 4, 4, 2, 1, 9, 1, 2, 2, 0, 2, 9, 4, 2, 4, 1, 2, 2, 2, 4, 1, 2, 1, 0,
		0, 2, 1, 1, 1, 2, 2, 2, 4, 4, 2, 2, 2, 2, 1, 1, 4, 4, 2, 2, 4, 2, 1, 1, 2,
		2, 1, 2, 2, 4, 2, 1, 4, 3, 1, 1, 1, 4, 2, 2, 4, 2, 4, 1, 2, 2, 2, 4, 4, 2,
		2, 1, 2, 2, 2, 2, 2, 4, 2, 1, 1, 2, 1, 1, 2, 2, 4, 2, 2, 1, 1, 2, 2, 2, 2,
		2, 2, 2, 2, 4, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 4, 2, 2, 2, 2, 2, 4, 4, 2, 2,
		4, 4, 2, 1, 2, 2, 2, 2, 2, 2, 4, 4, 2, 2, 1, 2, 4, 4, 1, 0, 0, 1, 1, 2, 1,
		2, 2, 1, 2, 4, 4, 2, 4, 1, 0, 4, 2, 2, 2, 2, 0, 0, 2, 2, 2, 1, 4, 4, 4, 2,
		2, 2, 2, 2, 4, 2, 0, 0, 0, 4, 0, 0 
	};
	
	return max_seats[modelid - 400];
}

IsBikeVehicle(vehicleid)
{
	switch (GetVehicleModel(vehicleid))
	{
		case 509, 481, 510:
		{
			return 1;
		}
	}
	
	return 0;
}

stock IsMotoVehicle(vehicleid)
{
	switch (GetVehicleModel(vehicleid))
	{
		case 448, 461, 462, 463, 468, 471, 521, 522, 523, 581, 586:
		{
			return 1;
		}
	}
	
	return 0;
}

IsAirVehicle(vehicleid)
{
	switch (GetVehicleModel(vehicleid))
    {
        case 417, 425, 447, 460, 469, 476, 487, 488, 497, 511 .. 513,
        519, 520, 548, 553, 563, 577, 592, 593: 
		{
			 return 1;
		}
   }
	
	return 0;
}

IsBoatVehicle(vehicleid)
{
	switch (GetVehicleModel(vehicleid))
    {
        case 430, 446, 452, 453, 454, 472, 473, 484, 493, 595: 
		{
			 return 1;
		}
   }
	
	return 0;
}

IsTrainVehicle(vehicleid)
{
	switch (GetVehicleModel(vehicleid))
    {
        case 570, 537, 538: 
		{
			 return 1;
		}
   }
	
	return 0;
}

SendSplitMessage(playerid, color, string[])
{
	new len = strlen(string),
		i_len = len / MAX_SPLIT_CHARS,
		str_line [MAX_CHAT_MESSAGE];
		
	new index,
		last_index;
		
	if (len % MAX_SPLIT_CHARS)
	{
		i_len++;
	}
		
	while (index < i_len)
	{
		clean:<str_line>;
		
		if (i_len > 1)
		{
			last_index = strfind(string, " ", true, MAX_SPLIT_CHARS);
			last_index = last_index == INVALID_PARAM ? len : last_index;
			
			if (last_index == len)
			{
				strcat(str_line, string, MAX_CHAT_MESSAGE);
				index = i_len;
			}
			else 
			{
				strmid(
					str_line, 
					string, 
					(index * last_index), 
					(index * last_index) + last_index 
				);

				if (index == 0)
				{
					format(str_line, sizeof str_line, "%s ...", str_line);
				}
				else 
				{
					format(str_line, sizeof str_line, "... %s", str_line);
					index++;
				}
			}
		}	
		else 
		{
			strcat(str_line, string, MAX_CHAT_MESSAGE);
		}
		
		SendClientMessage(playerid, color, str_line);
		index++;
	}
	
	return 1;
}

SendSplitMessageToAll(color, string[])
{
	new len = strlen(string),
		i_len = len / MAX_SPLIT_CHARS,
		str_line [MAX_CHAT_MESSAGE];
		
	new index,
		last_index;
		
	if (len % MAX_SPLIT_CHARS)
	{
		i_len++;
	}
		
	while (index < i_len)
	{
		clean:<str_line>;
		
		if (i_len > 1)
		{
			last_index = strfind(string, " ", true, MAX_SPLIT_CHARS);
			last_index = last_index == INVALID_PARAM ? len : last_index;
			
			if (last_index == len)
			{
				strcat(str_line, string, MAX_CHAT_MESSAGE);
				index = i_len;
			}
			else 
			{
				strmid(
					str_line, 
					string, 
					(index * last_index), 
					(index * last_index) + last_index 
				);

				if (index == 0)
				{
					format(str_line, sizeof str_line, "%s ...", str_line);
				}
				else 
				{
					format(str_line, sizeof str_line, "... %s", str_line);
					index++;
				}
			}
		}	
		else 
		{
			strcat(str_line, string, MAX_CHAT_MESSAGE);
		}
		
		SendClientMessageToAll(color, str_line);
		index++;
	}
	
	return 1;
}

GetWithoutUnderscore(string[], dest[])
{
	dest[0] = EOS;
	for (new i, j = strlen(string); i < j; i++)
	{
		if (string[i] == '_')
		{
			dest[i] = ' ';
			continue;
		}

		dest[i] = string[i];
	}
}

ReplacePlayerName(playerid, type)
{
	new result;
	
	player_temp_name[playerid][0] = EOS;
	DeletePVar(playerid, "Player:Mask");
	
	if (type == TYPE_OOC)
	{
		result = SetPlayerName(playerid, user_data[playerid][u_name]);
		strcat(player_temp_name[playerid], user_data[playerid][u_name], MAX_PLAYER_NAME);
	}
	else if (type == TYPE_IC)
	{
		result = SetPlayerName(playerid, character_data[playerid][c_name]);
		strcat(player_temp_name[playerid], character_data[playerid][c_rpname], MAX_PLAYER_NAME);
	}
	else if (type == TYPE_HIDDEN)
	{
		clean:<g_small_string>;
		format:g_small_string("Hidden_%i", GetMaskId(playerid));
		result = SetPlayerName(playerid, g_small_string);
		
		clean:<g_small_string>;
		format:g_small_string("Hidden %i", GetMaskId(playerid));
		strcat(player_temp_name[playerid], g_small_string, MAX_PLAYER_NAME);
		
		SetPVarInt(playerid, "Player:Mask", true);
	}
	
	return result;
}

GetVehicleComponentPos(vehicleid, bool: is_boot, &Float: x, &Float: y, &Float: z)
{	
	new Float: distance,
		Float: angle;
		
	GetVehicleZAngle(vehicleid, angle);
	GetVehicleModelInfo(vehicle_data[vehicleid][v_model], VEHICLE_MODEL_INFO_SIZE, x, distance, z); // x - ширина; y - длина; z - высота
	if (!GetVehiclePos(vehicleid, x, y, z))
	{
		x = 
		y =
		z = 0.0;
		return;
	}
	
	// For bullet
	if (vehicle_data[vehicleid][v_model] == 451) 
	{
		is_boot = !is_boot;
	}
	
	distance = distance / 2 + 0.1; // делим на 2 и половину отнимаем
	if (!is_boot)
	{
		x -= distance * floatsin(-angle + 180, degrees);
		y -= distance * floatcos(-angle + 180, degrees);
	}
	else 
	{
		x += distance * floatsin(-angle + 180, degrees);
		y += distance * floatcos(-angle + 180, degrees);
	}
}
			
IsValidSkin(skin_id, _: sex)
{
	switch(skin_id)
	{
		case 1 .. 8, 14 .. 30, 32 .. 37, 42 .. 52, 57 .. 62, 66 .. 68, 70 .. 73, 78 .. 84, 86, 94 .. 128,
		132 .. 137, 142 .. 144, 146, 147, 149, 153 .. 156, 158 .. 168, 170, 171, 173 .. 177, 179 .. 189,
		200, 202 .. 204, 206, 208 .. 210, 212, 213, 217, 220 .. 223, 227 .. 230, 234 .. 236, 239 .. 242,
		247 .. 250, 252 .. 255, 258 .. 262, 264 .. 297, 299 .. 305, 310 .. 311 : // Male skin
		{
			return !sex;
		}
		
		case  9 .. 13, 31, 38 .. 41, 53 .. 56, 63 .. 65, 69, 75 .. 77, 85, 87 .. 93, 129 .. 131, 138 .. 141,
		145, 148, 150 .. 152, 157, 169, 172, 178, 190 .. 199, 201, 205, 207, 211, 214 .. 216, 218, 219, 224 .. 226,
		231 .. 233, 237, 238, 243 .. 246, 251, 256, 257, 263, 298, 306 .. 309 : // Female skin
		{
			return sex;
		}
		
		default : // 0, 74 Skip
		{
			return 0;
		}
	}
	
	return 1;
}

GetZoneName(Float: x, Float: y, zonename[], len)
{
	for (new i; i < sizeof sa_zones; i++)
	{	
		if ((sa_zones[i][sz_pos][0] <= x <= sa_zones[i][sz_pos][3])
		&& (sa_zones[i][sz_pos][1] <= y <= sa_zones[i][sz_pos][4]))
		{
			zonename[0] = EOS;
			return strcat(zonename, sa_zones[i][sz_name], len);
		}
	}
	
	return 0;
}

HidePlayerDialog(playerid)
{
	player_dialog_id[playerid] = INVALID_DIALOG_ID;
	ShowPlayerDialog(playerid, INVALID_PARAM, 0, "", "", "", "");
	return 1;
}

CreatePickupWith3DTextLabel(text[], model, Float: x, Float: y, Float: z, world = -1, int = -1)
{
	if (model != INVALID_PARAM)
	{
		CreateDynamicPickup(model, 23, x, y, z, world, int, -1, PICKUP_DRAW_DISTANCE);
	}
	
	CreateDynamic3DTextLabel(
		text, 
		C_WHITE, 
		x, 
		y, 
		z, 
		TEXT3D_DRAW_DISTANCE, 
		INVALID_PLAYER_ID, 
		INVALID_VEHICLE_ID, 
		1, 
		world, 
		int,
		-1,
		TEXT3D_DRAW_DISTANCE 
	);
}

GetNameOfWeekday(string[], len = sizeof(string))
{
	new year,
		month,
		day;
	
	getdate(year, month, day);
	
	string[0] = EOS;
	switch(GetWeekDay(year, month, day))
	{
		case 0 :
		{
			strcat(string, "Saturday", len);
		}
		
		case 1 :
		{
			strcat(string, "Sunday", len);
		}
		
		case 2 :
		{
			strcat(string, "Monday", len);
		}
		
		case 3 :
		{
			strcat(string, "Tuesday", len);
		}
		
		case 4 :
		{
			strcat(string, "Wednesday", len);
		}
		
		case 5 :
		{
			strcat(string, "Thursday", len);
		}
		
		case 6 :
		{
			strcat(string, "Friday", len);
		}
	}
}

IsInterfaceActive(playerid)
{
	if (GetPVarInt(playerid, !"Inventory:States")
	|| GetPVarInt(playerid, !"Site:States") 
	|| GetPVarInt(playerid, !"SelectMenu:States")
	|| IsPhoneShowed(playerid)
	|| GetPVarInt(playerid, !"KeyAlarm:States"))
	{
		return 1;
	}
	
	return 0;
}

// Decode & Encode damage helpers
// Panels
stock DecodeDamagePanels(panels, &front_left_panel, &front_right_panel, &rear_left_panel, &rear_right_panel, &windshield, &front_bumper, &rear_bumper)
{
    front_left_panel = panels & 15;
    front_right_panel = panels >> 4 & 15;
    rear_left_panel = panels >> 8 & 15;
    rear_right_panel = panels >> 12 & 15;
    windshield = panels >> 16 & 15;
    front_bumper = panels >> 20 & 15;
    rear_bumper = panels >> 24 & 15;
}

stock EncodeDamagePanels(front_left_panel, front_right_panel, rear_left_panel, rear_right_panel, windshield, front_bumper, rear_bumper)
{
    return front_left_panel | (front_right_panel << 4) | (rear_left_panel << 8) | (rear_right_panel << 12) | (windshield << 16) | (front_bumper << 20) | (rear_bumper << 24);
}
 
// Doors
stock DecodeDamageDoors(doors, &bonnet, &boot, &driver_door, &passenger_door)
{
    bonnet = doors & 7;
    boot = doors >> 8 & 7;
    driver_door = doors >> 16 & 7;
    passenger_door = doors >> 24 & 7;
}

stock EncodeDamageDoors(bonnet, boot, driver_door, passenger_door)
{
    return bonnet | (boot << 8) | (driver_door << 16) | (passenger_door << 24);
}
 
// Lights
stock DecodeDamageLights(lights, &front_left_light, &front_right_light, &back_lights)
{
    front_left_light = lights & 1;
    front_right_light = lights >> 2 & 1;
    back_lights = lights >> 6 & 1;
}

stock EncodeDamageLights(front_left_light, front_right_light, back_lights)
{
    return front_left_light | (front_right_light << 2) | (back_lights << 6);
}
 
// Tires
stock DecodeDamageTires(tires, &rear_right_tire, &front_right_tire, &rear_left_tire, &front_left_tire)
{
    rear_right_tire = tires & 1;
    front_right_tire = tires >> 1 & 1;
    rear_left_tire = tires >> 2 & 1;
    front_left_tire = tires >> 3 & 1;
}

stock EncodeDamageTires(rear_right_tire, front_right_tire, rear_left_tire, front_left_tire)
{
	return rear_right_tire | (front_right_tire << 1) | (rear_left_tire << 2) | (front_left_tire << 3);
}

HasVehicleClosedSpace(vehicleid)
{
	switch (GetVehicleModel(vehicleid))
	{
		case 424, 430, 441, 446, 448, 449, 452, 453, 454, 457, 461, 462, 463, 464, 465, 
		468, 471, 472, 473, 481, 484, 485, 486, 493, 501, 509, 510, 521, 522, 523, 
		530, 531, 532, 537, 538, 539, 564, 568, 570, 571, 572, 581, 586, 594, 595 : 
		{
			 return 1;
		}
	}
	
	return 0;
}

SetPlayerFacePlayer(playerid, targetid) 
{
    new Float: px,
        Float: py,
        Float: pz,
        Float: gx,
        Float: gy,
        Float: gz;
		
    if (GetPlayerPos(playerid, px, py, pz) && GetPlayerPos(targetid, gx, gy, gz))
	{
        SetPlayerFacingAngle(playerid, (px = -atan2((gx - px), (gy - py))));
        return SetPlayerFacingAngle(targetid, (px + 180.0));
    }
	
    return false;
}

function Float: GetDistanceBetweenPlayers(playerid_one, playerid_two) 
{
	new Float: x1,
		Float: y1,
		Float: z1,
		Float: x2,
		Float: y2,
		Float: z2;
		
	GetPlayerPos(playerid_one, x1, y1, z1);
	GetPlayerPos(playerid_two, x2, y2, z2);
	
	return floatsqroot( 
		floatpower(floatabs(floatsub(x2, x1)), 2) 
		+ floatpower(floatabs(floatsub(y2, y1)), 2) 
		+ floatpower(floatabs(floatsub(z2, z1)), 2) 
	);
}
