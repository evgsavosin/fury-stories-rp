/*!
	@brief Заголовок системы фракций на сервере
	@author Found (evg.savosin)
	@date 16.12.2016, update 14.02.2018
*/

// Defines
#define GetFractionId(%0)			fraction_data[%0][fr_id]
#define GetFractionName(%0)			fraction_data[%0][fr_name]
#define GetFractionAltName(%0)		fraction_data[%0][fr_alt_name]
#define GetFractionLeader(%0)		character_data[%0][c_fraction_leader]
#define GetFractionMember(%0)		character_data[%0][c_fraction_index]
#define GetFractionMemberId(%0)		GetFractionIdByIndex(GetFractionMember(%0))
#define GetFractionMemberRank(%0)	character_data[%0][c_fraction_rank_index]
#define GetFractionMemberUnit(%0)	character_data[%0][c_fraction_unit_index]
#define GetFractionColor(%0)		fraction_data[%0][fr_color]
#define GetFractionMemberSkin(%0)	character_data[%0][c_fraction_skin]

#define IsFractionMemberOnDuty(%0)	character_data[%0][c_fraction_duty]

#define FRACTION_VEHICLE 			" \
	Список транспорта\n \
	Вернуть весь транспорт на парковочные места\
"
#define FRACTION_VEHICLE_DIALOG		D_FRACTION + 16, DIALOG_STYLE_LIST, " ", FRACTION_VEHICLE, "Выбрать", "Назад"

#define FRACTION_SETTINGS			" \
	Список рангов\n \
	Список подразделений\n \
	Ранг по умолчанию\
"
#define FRACTION_SETTINGS_DIALOG	D_FRACTION + 23, DIALOG_STYLE_LIST, " ", FRACTION_SETTINGS, "Выбрать", "Назад"

#define FRACTION_BONE_DIALOG 		"\
" #cGRAY "Выберите часть тела:" #cWHITE "\n \
	Спина\n \
	Голова\n \
	Плечо левой руки\n \
	Плечо правой руки\n \
	Левая рука\n \
	Правая рука\n \
	Левое бедро\n \
	Правое бедро\n \
	Левая нога\n \
	Правая нога\n \
	Правые икры\n \
	Левые икры\n \
	Левое предплечье\n \
	Правое предплечье\n \
	Левая ключица\n \
	Правая ключица\n \
	Шея\n \
	Челюсть\
"

// Constants
const MAX_FRACTIONS = 20,
	  MAX_FRACTION_NAME	= 64,
	  MAX_FRACTION_ALT_NAME = 16,
	  MAX_FRACTION_BUDGET = 16,
	  MAX_FRACTION_ITEM_NAME = 32,
	  MAX_FRACTION_SKINS = 20,
	  MAX_FRACTION_VEHICLES = 100;
	  
const MAX_FRACTION_ITEM_LIST = 20;

const MAX_FRACTION_UNITS = 10;
	  
const MAX_FRACTION_RANKS = 50,
	  MAX_FRACTION_RANK_PERM = 10,
	  MAX_FRACTION_RANK_NAME = 64;
	  
const MIN_FRACTION_SALARY = 400,
	  MAX_FRACTION_SALARY = 1800;

const EMERGENCY_NUMBER = 911,
	  NEWS_NUMBER = 777;
	  
const MAX_FRACTION_SPAWN_POS = 4;

// Structures & Array
enum
{
	FRAC_BUDGET_GOV = 1,
	FRAC_BUDGET_INDEPENDENT
};

enum
{
	FRACTION_NONE, // 0 
	FRACTION_GOVERNMENT, // 1
	FRACTION_COURT, // 2 
	FRACTION_PD, // 3
	FRACTION_FD, // 4
	FRACTION_SD, // 5
	FRACTION_NEWS, // 6
	FRACTION_NP, // 7
	FRACTION_HOSPITAL // 8
};

enum E_FRACTION_DATA
{
	fr_id,
	fr_name						[MAX_FRACTION_NAME],
	fr_alt_name					[MAX_FRACTION_ALT_NAME],
	fr_color,
	fr_type_budget,
	Float: fr_budget,
	fr_main, // Основная фракция
	fr_join_rank_id,
	Float: fr_spawn_pos			[MAX_FRACTION_SPAWN_POS],
	fr_spawn_int,
	fr_spawn_world,
	
	fr_leader_id,
	fr_leader_name				[MAX_PLAYER_NAME]
};

enum E_FRACTION_ITEM_SELECT
{
	fr_id,
	fr_name						[MAX_FRACTION_ITEM_NAME],
	fr_object_id,
	fr_item_param_1,
	fr_item_param_2
};

enum E_FRACTION_MEMBER_SELECT
{
	fr_id,
	fr_name						[MAX_PLAYER_NAME],
	fr_status,
	fr_rank_index,
	fr_unit_index
};

new fraction_data				[MAX_FRACTIONS][E_FRACTION_DATA],
	fraction_item_select		[MAX_PLAYERS][MAX_ITEM_LIST + 2][E_FRACTION_ITEM_SELECT],
	fraction_member_select		[MAX_PLAYERS][MAX_FRACTION_ITEM_LIST][E_FRACTION_MEMBER_SELECT];	

// Functions
Clear:fraction_data(index)
{
	// Int
	fraction_data[index][fr_main] =
	fraction_data[index][fr_id] =
	fraction_data[index][fr_color] =
	fraction_data[index][fr_leader_name] =
	fraction_data[index][fr_join_rank_id] =
	fraction_data[index][fr_spawn_int] = 
	fraction_data[index][fr_spawn_world] = 
	fraction_data[index][fr_type_budget] = 0;
	
	// Float
	fraction_data[index][fr_budget] = 0.0;
	
	// String
	fraction_data[index][fr_name][0] = 
	fraction_data[index][fr_leader_name][0] = 
	fraction_data[index][fr_alt_name][0] = EOS;
	
	// Ranks
	for (new i; i < MAX_FRACTION_RANKS; i++)
	{
		Clear:fraction_rank_data(index, i);
	}
	
	// Units
	for (new i; i < MAX_FRACTION_UNITS; i++)
	{
		Clear:fraction_unit_data(index, i);
	}
}
	
Create:fraction_data(playerid, index)
{
	format:g_string("\
		INSERT INTO " #__FRACTIONS " \
		(fr_name, fr_alt_name, fr_color) \
			VALUES \
		('%q', '%q', '%q')",
		fraction_data[index][fr_name],
		fraction_data[index][fr_alt_name],
		fraction_data[index][fr_color]
	);
	
	mysql_tquery(db, g_string, "OnFractionCreate", "dd", playerid, index);
}

function OnFractionCreate(playerid, index)
{
	fraction_data[index][fr_id] = cache_insert_id();
	
	pformat:(#SUCCESS " Фракция " #cPROJECT "%s (#%d)" #cWHITE " успешно создана.",
		fraction_data[index][fr_alt_name],
		fraction_data[index][fr_id]
	);
	
	psend:(playerid, C_WHITE);
	
	printf("[OnFractionCreate]: Fraction [ID:%d] has been created.",
		fraction_data[index][fr_id]
	);
	
	return 1;
}

stock Remove:fraction_data(index)
{	
	format:g_string("DELETE FROM " #__FRACTIONS " WHERE fr_id = %d",
		GetFractionId(index)
	);
	
	mysql_tquery(db, g_string);
	
	foreach (new playerid : Player)
	{
		if (!IsPlayerLogged(playerid))
		{
			continue;
		}
		
		if (GetFractionMember(playerid) == index)
		{
			pformat:("Фракция (%s), в которой Вы состояли, была удалена.",
				GetFractionAltName(index)
			);
			
			psend:(playerid, C_LIGHTRED);
			
			character_data[playerid][c_fraction_index] =
			character_data[playerid][c_fraction_unit_index] =
			character_data[playerid][c_fraction_rank_index] =
			character_data[playerid][c_fraction_leader] = 0;
		}
	}
	
	format:g_string("UPDATE " #__CHARACTERS " \
		SET \
			c_fraction_id = 0, \
			c_fraction_unit_id = 0, \
			c_fraction_rank_id = 0 \
		WHERE c_id = %d",
		GetFractionId(index)
	);
	
	mysql_tquery(db, g_string);
	
	Clear:fraction_data(index);
}

// Fraction
stock Update:fraction_int(index, column[], _: value)
{
	format:g_string("UPDATE "#__FRACTIONS" SET %s = %d WHERE fr_id = %d LIMIT 1",
		column,
		value,
		GetFractionId(index)
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:fraction_string(index, column[], const value[], bool: quotes = true)
{
	format:g_string("UPDATE " #__FRACTIONS " SET %s = %s%q%s WHERE fr_id = %d LIMIT 1",
		column,
		quotes ? ("'") : (""),
		value,
		quotes ? ("'") : (""),
		GetFractionId(index)
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:fraction_float(index, column[], Float: value)
{
	format:g_string("UPDATE " #__FRACTIONS " SET %s = %f WHERE fr_id = %d LIMIT 1",
		column,
		value,
		GetFractionId(index)
	);
	
	return mysql_tquery(db, g_string);
}

// Object fraction
stock Create:fraction_object_data(const fraction_id, const object_id, name[])
{
	format:g_string("INSERT INTO " #__FRACTIONS_OBJECT " (fo_fraction_id, fo_object_id, fo_name) \
		VALUES (%d, %d, '%q')",
		fraction_id,
		object_id,
		name
	);
	
	return mysql_tquery(db, g_string);
}

stock Remove:fraction_object(id)
{
	format:g_string("DELETE FROM " #__FRACTIONS_OBJECT " WHERE fo_id = %d",
		id
	);
	
	return mysql_tquery(db, g_string);
}

// Update
stock Update:fraction_object_int(id, column[], _: value)
{
	format:g_string("UPDATE " #__FRACTIONS_OBJECT " SET %s = %d WHERE fo_id = %d LIMIT 1",
		column,
		value,
		id
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:fraction_object_string(id, column[], const value[], bool: quotes = true)
{
	format:g_string("UPDATE " #__FRACTIONS_OBJECT " SET %s = %s%q%s WHERE fo_id = %d LIMIT 1",
		column,
		quotes ? ("'") : (""),
		value,
		quotes ? ("'") : (""),
		id
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:fraction_object_float(id, column[], Float: value)
{
	format:g_string("UPDATE " #__FRACTIONS_OBJECT " SET %s = %f WHERE fo_id = %d LIMIT 1",
		column,
		value,
		id
	);
	
	return mysql_tquery(db, g_string);
}

// Attach fraction
stock Create:fraction_attach(const fraction_id, const object_id, name[])
{
	format:g_string("INSERT INTO " #__FRACTIONS_ATTACH " (fr_fraction_id, fr_object_id, fr_name) \
		VALUES (%d, %d, '%q')",
		fraction_id,
		object_id,
		name
	);
	
	return mysql_tquery(db, g_string);
}

stock Remove:fraction_attach(id)
{
	format:g_string("DELETE FROM " #__FRACTIONS_ATTACH " WHERE fr_id = %d",
		id
	);
	
	return mysql_tquery(db, g_string);
}

// Update
stock Update:fraction_attach_int(id, column[], _: value)
{
	format:g_string("UPDATE " #__FRACTIONS_ATTACH " SET %s = %d WHERE fr_id = %d LIMIT 1",
		column,
		value,
		id
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:fraction_attach_string(id, column[], const value[], bool: quotes = true)
{
	format:g_string("UPDATE " #__FRACTIONS_ATTACH " SET %s = %s%q%s WHERE fr_id = %d LIMIT 1",
		column,
		quotes ? ("'") : (""),
		value,
		quotes ? ("'") : (""),
		id
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:fraction_attach_float(id, column[], Float: value)
{
	format:g_string("UPDATE " #__FRACTIONS_ATTACH " SET %s = %f WHERE fr_id = %d LIMIT 1",
		column,
		value,
		id
	);
	
	return mysql_tquery(db, g_string);
}

// Weapon fraction
stock Create:fraction_item(const fraction_id, const item_id, const param_1, const param_2)
{
	format:g_string("INSERT INTO " #__FRACTIONS_ITEM " (fr_fraction_id, fr_item_id, fr_item_param_1, fr_item_param_2) \
		VALUES (%d, %d, %d, %d)",
		fraction_id,
		item_id,
		param_1,
		param_2
	);
	
	return mysql_tquery(db, g_string);
}

stock Remove:fraction_item(id)
{
	format:g_string("DELETE FROM " #__FRACTIONS_ITEM " WHERE fr_id = %d",
		id
	);
	
	return mysql_tquery(db, g_string);
}

// Update
stock Update:fraction_item_int(id, column[], _: value)
{
	format:g_string("UPDATE " #__FRACTIONS_ITEM " SET %s = %d WHERE fr_id = %d LIMIT 1",
		column,
		value,
		id
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:fraction_item_string(id, column[], const value[], bool: quotes = true)
{
	format:g_string("UPDATE " #__FRACTIONS_ITEM " SET %s = %s%q%s WHERE fr_id = %d LIMIT 1",
		column,
		quotes ? ("'") : (""),
		value,
		quotes ? ("'") : (""),
		id
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:fraction_item_float(id, column[], Float: value)
{
	format:g_string("UPDATE " #__FRACTIONS_ITEM " SET %s = %f WHERE fr_id = %d LIMIT 1",
		column,
		value,
		id
	);
	
	return mysql_tquery(db, g_string);
}