/*!
	@brief Заголовок системы фракций на сервере
	@author Found (evg.savosin)
	@date 16.12.2016, update 14.02.2018
*/

// Defines
#define GetFractionRankPermCustom(%0,%1,%2)		fraction_rank_data[%0][%1][fr_perm_custom][%2]
#define GetFractionRankPerm(%0,%1,%2)			fraction_rank_data[%0][%1][%2]

// Constants
const MAX_FRACTION_PERM_NAME = 32;

// Structures & Array
enum E_FRACTION_RANK_DATA
{
	fr_id,
	fr_name						[MAX_FRACTION_RANK_NAME],
	fr_salary,
	
	fr_perm_invite, // Принять в организацию
	fr_perm_uninvite, // Уволить из организации
	fr_perm_set_rank, // Установить ранг 
	fr_perm_set_unit, // Установить подразделение
	fr_perm_manage, // Доступ к разделу - Настройки
	fr_perm_radio, // Использование частоты рации
	fr_perm_object, // Доступ к /object
	fr_perm_attach, // Доступ к /attach
	fr_perm_vehicle, // Использование транспорта
	fr_perm_clothes, // Использование служебной одежды
	fr_perm_items, // Доступ к предметам
	fr_perm_weapon, // Доступ к оружию
	fr_perm_spawn_vehicle, // Спавн транспорта
	
	fr_perm_custom				[MAX_FRACTION_RANK_PERM]
};

enum E_FRACTION_PERM_CUSTOM
{
	fr_id,
	fr_index,
	fr_name 					[MAX_FRACTION_PERM_NAME]
};

// FRACTION_GOVERNMENT
enum
{
	PERM_GOV_BUDGET,
	PERM_GOV_TICKET,
	PERM_GOV_WEB
};

new const fraction_perm_custom	[][E_FRACTION_PERM_CUSTOM] = 
{
	// FRACTION_GOVERNMENT
	{FRACTION_GOVERNMENT, PERM_GOV_BUDGET, "Регулирование экономики штата"},
	{FRACTION_GOVERNMENT, PERM_GOV_TICKET, "Управление штрафами"},
	{FRACTION_GOVERNMENT, PERM_GOV_WEB, "Доступ к сайту"}
};

new fraction_rank_data			[MAX_FRACTIONS][MAX_FRACTION_RANKS][E_FRACTION_RANK_DATA];

// Functions
Clear:fraction_rank_data(findex, index)
{	
	// Int
	fraction_rank_data[findex][index][fr_id] = 
	fraction_rank_data[findex][index][fr_perm_invite] = 
	fraction_rank_data[findex][index][fr_perm_uninvite] = 
	fraction_rank_data[findex][index][fr_perm_set_rank] = 
	fraction_rank_data[findex][index][fr_perm_set_unit] = 
	fraction_rank_data[findex][index][fr_perm_radio] = 
	fraction_rank_data[findex][index][fr_perm_object] = 
	fraction_rank_data[findex][index][fr_perm_attach] = 
	fraction_rank_data[findex][index][fr_perm_vehicle] = 
	fraction_rank_data[findex][index][fr_perm_clothes] = 
	fraction_rank_data[findex][index][fr_perm_items] = 
	fraction_rank_data[findex][index][fr_perm_weapon] = 
	fraction_rank_data[findex][index][fr_perm_spawn_vehicle] = 
	fraction_rank_data[findex][index][fr_perm_manage] = 0;
	
	// String
	fraction_rank_data[findex][index][fr_name][0] = EOS;
	
	for (new i; i < MAX_FRACTION_RANK_PERM; i++)
	{
		fraction_rank_data[findex][index][fr_perm_custom][i] = 0;
	}
}

Create:fraction_rank_data(playerid, findex, index)
{
	format:g_string("\
		INSERT INTO " #__FRACTIONS_RANK " \
		(fr_fraction_id, fr_name, fr_salary) \
			VALUES \
		(%d, '%q', %d)",
		GetFractionId(findex), 
		fraction_rank_data[findex][index][fr_name],
		fraction_rank_data[findex][index][fr_salary]
	);
	
	mysql_tquery(db, g_string, "OnFractionRankCreate", "ddd", playerid, findex, index);
}

function OnFractionRankCreate(playerid, findex, index)
{
	fraction_rank_data[findex][index][fr_id] = cache_insert_id();
	
	pformat:(#SUCCESS " Ранг " #cPROJECT "%s" #cWHITE " успешно создан. Настроить его можно в настройках.",
		fraction_rank_data[findex][index][fr_name]
	);
	
	psend:(playerid, C_WHITE);
	
	printf("[OnFractionRankCreate]: Fraction rank [ID:%d] has been created.",
		fraction_rank_data[findex][index][fr_id]
	);
	
	return 1;
}

Remove:fraction_rank_data(findex, index)
{
	format:g_string("DELETE FROM " #__FRACTIONS_RANK " WHERE fr_id = %d", 
		fraction_rank_data[findex][index][fr_id]
	);
	
	mysql_tquery(db, g_string);
	
	format:g_string("UPDATE " #__FRACTIONS_RANK " SET c_fraction_rank_id = 0 WHERE c_fraction_rank_id = %d",
		fraction_rank_data[findex][index][fr_id]
	);
	
	mysql_tquery(db, g_string);
	
	foreach (new playerid : Player)
	{
		if (!IsPlayerLogged(playerid))
		{
			continue;
		}
		
		if (GetFractionMember(playerid) != findex 
		|| GetFractionMemberRank(playerid) != index)
		{
			continue;
		}
		
		character_data[playerid][c_fraction_rank_index] = 0;
		Update:character_int(playerid, "c_fraction_rank_id", 0);
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Ранг, на котором Вы находились, был удалён.");
	}
	
	Clear:fraction_rank_data(findex, index);
}

stock Update:fraction_rank_int(findex, index, column[], _: value)
{
	format:g_string("UPDATE " #__FRACTIONS_RANK " SET %s = %d WHERE fr_id = %d LIMIT 1",
		column,
		value,
		fraction_rank_data[findex][index][fr_id]
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:fraction_rank_string(findex, index, column[], const value[], bool: quotes = true)
{
	format:g_string("UPDATE " #__FRACTIONS_RANK " SET %s = %s%q%s WHERE fr_id = %d LIMIT 1",
		column,
		quotes ? ("'") : (""),
		value,
		quotes ? ("'") : (""),
		fraction_rank_data[findex][index][fr_id]
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:fraction_rank_float(findex, index, column[], Float: value)
{
	format:g_string("UPDATE " #__FRACTIONS_RANK " SET %s = %f WHERE fr_id = %d LIMIT 1",
		column,
		value,
		fraction_rank_data[findex][index][fr_id]
	);
	
	return mysql_tquery(db, g_string);
}