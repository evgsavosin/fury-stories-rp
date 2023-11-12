/*!
	@brief Заголовок системы фракций на сервере
	@author Found (evg.savosin)
	@date 16.12.2016, update 14.02.2018
*/

// Defines
#define GetFractionUnitId(%0,%1)				fraction_unit_data[GetFractionMember(%0)][%1][fr_id]
#define GetFractionUnitName(%0,%1)				fraction_unit_data[GetFractionMember(%0)][%1][fr_name]

// Constants
const MAX_FRACTION_UNIT_NAME = MAX_FRACTION_NAME;

// Structures & Array
enum E_FRACTION_UNIT_DATA
{
	fr_id,
	fr_leader_id,
	fr_leader_name				[MAX_PLAYER_NAME],
	fr_name						[MAX_FRACTION_NAME],
	fr_alt_name					[MAX_FRACTION_ALT_NAME],
	fr_skins					[MAX_FRACTION_SKINS],
	
	Float: fr_pos_x,
	Float: fr_pos_y,
	Float: fr_pos_z,
	Float: fr_pos_angle,
	
	fr_int,
	fr_world
};

new fraction_unit_data			[MAX_FRACTIONS][MAX_FRACTION_UNITS][E_FRACTION_UNIT_DATA];

// Functions
Clear:fraction_unit_data(findex, index)
{
	// Int
	fraction_unit_data[findex][index][fr_id] =
	fraction_unit_data[findex][index][fr_int] =
	fraction_unit_data[findex][index][fr_leader_id] =
	fraction_unit_data[findex][index][fr_world] = 0;
	
	// Float 
	fraction_unit_data[findex][index][fr_pos_x] =
	fraction_unit_data[findex][index][fr_pos_y] =
	fraction_unit_data[findex][index][fr_pos_z] = 
	fraction_unit_data[findex][index][fr_pos_angle] = 0.0;
	
	// String
	fraction_unit_data[findex][index][fr_name][0] = 
	fraction_unit_data[findex][index][fr_alt_name][0] = 
	fraction_unit_data[findex][index][fr_leader_name][0] = EOS;
	
	for (new i; i < MAX_FRACTION_SKINS; i++)
	{
		fraction_unit_data[findex][index][fr_skins][i] = 0;
	}
}

Create:fraction_unit_data(playerid, findex, index)
{
	format:g_string("\
		INSERT INTO " #__FRACTIONS_UNIT " \
		(fr_fraction_id, fr_name, fr_alt_name) \
			VALUES \
		(%d, '%q', '%q')",
		GetFractionId(findex),
		fraction_unit_data[findex][index][fr_name],
		fraction_unit_data[findex][index][fr_alt_name]
	);
	
	mysql_tquery(db, g_string, "OnFractionUnitCreate", "ddd", playerid, findex, index);
}

function OnFractionUnitCreate(playerid, findex, index)
{
	fraction_unit_data[findex][index][fr_id] = cache_insert_id();
	
	pformat:(#SUCCESS " Подразделение " #cPROJECT "%s" #cWHITE " успешно создан. Настроить его можно в настройках.",
		fraction_unit_data[findex][index][fr_name]
	);
	
	psend:(playerid, C_WHITE);
	
	printf("[OnFractionUnitCreate]: Fraction unit [ID:%d] has been created.",
		fraction_unit_data[findex][index][fr_id]
	);
	
	return 1;
}

Remove:fraction_unit_data(findex, index)
{
	format:g_string("DELETE FROM " #__FRACTIONS_UNIT " WHERE fr_id = %d", 
		fraction_unit_data[findex][index][fr_id]
	);
	
	mysql_tquery(db, g_string);
	
	format:g_string("UPDATE " #__CHARACTERS " SET c_fraction_unit_id = 0 WHERE c_fraction_unit_id = %d",
		fraction_unit_data[findex][index][fr_id]
	);
	
	mysql_tquery(db, g_string);
	
	foreach (new playerid : Player)
	{
		if (!IsPlayerLogged(playerid))
		{
			continue;
		}
		
		if (GetFractionMember(playerid) != findex 
		|| GetFractionMemberUnit(playerid) != index)
		{
			continue;
		}
		
		character_data[playerid][c_fraction_unit_leader_index] =
		character_data[playerid][c_fraction_unit_index] = 0;
		Update:character_int(playerid, "c_fraction_unit_id", 0);
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Подразделение, в котором Вы находились, было удалёно.");
	}
	
	Clear:fraction_unit_data(findex, index);
}

stock Update:fraction_unit_int(findex, index, column[], _: value)
{
	format:g_string("UPDATE " #__FRACTIONS_UNIT " SET %s = %d WHERE fr_id = %d LIMIT 1",
		column,
		value,
		fraction_unit_data[findex][index][fr_id]
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:fraction_unit_string(findex, index, column[], const value[], bool: quotes = true)
{
	format:g_string("UPDATE " #__FRACTIONS_UNIT " SET %s = %s%q%s WHERE fr_id = %d LIMIT 1",
		column,
		quotes ? ("'") : (""),
		value,
		quotes ? ("'") : (""),
		fraction_unit_data[findex][index][fr_id]
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:fraction_unit_float(findex, index, column[], Float: value)
{
	format:g_string("UPDATE " #__FRACTIONS_UNIT " SET %s = %f WHERE fr_id = %d LIMIT 1",
		column,
		value,
		fraction_unit_data[findex][index][fr_id]
	);
	
	return mysql_tquery(db, g_string);
}

Update:fraction_unit_skins(findex, index)
{
	clean:<g_string>;
	
	for (new i; i < MAX_FRACTION_SKINS; i++)
	{
		format:g_string("%s%d",
			g_string,
			fraction_unit_data[findex][index][fr_skins][i]
		);
		
		if (i < (MAX_FRACTIONS - 1))
		{
			strcat(g_string, "|");
		}
	}
	
	format:g_string("UPDATE " #__FRACTIONS_UNIT " SET fr_skins = '%q' WHERE fr_id = %d",
		g_string,
		fraction_unit_data[findex][index][fr_id]
	);
	
	mysql_tquery(db, g_string);
}