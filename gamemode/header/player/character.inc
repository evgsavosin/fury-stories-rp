/*!
	@brief Основной заголовок для системы персонажа
	@author Found (evg.savosin)
	@date 16.12.2016, update 16.01.2018
*/

// Defines
#define GetCharacterId(%0)					(character_data[%0][c_id])
#define GetCharacterSettings(%0,%1)			(character_data[%0][c_settings][%1])
#define GetCharacterRPName(%0)				(character_data[%0][c_rpname])
#define GetCharacterName(%0)				(character_data[%0][c_name])
#define GetCharacterMoney(%0)   			(character_data[%0][c_money])
#define GetCharacterBank(%0)				(character_data[%0][c_bank])
#define GetCharacterSex(%0)					(character_data[%0][c_sex])
#define GetCharacterHealth(%0)				(character_data[%0][c_health])
#define GetCharacterCardNumber(%0)			(56120131+character_data[%0][c_id])
#define GetCharacterCardBalance(%0)   		(character_data[%0][c_card])
#define GetCharacterCardStart(%0)   		(character_data[%0][c_start_capital])
#define GetCharacterDesc(%0)				character_data[%0][c_desc]
#define GetCharacterDescCreatedTime(%0)		(character_data[%0][c_desc_created_time])
#define GetCharacterDeath(%0)				(character_data[%0][c_death])
#define GetCharacterSkin(%0)				(character_data[%0][c_skin])
#define GetCharacterInt(%0)					(character_data[%0][c_int])
#define GetCharacterWorld(%0)				(character_data[%0][c_world])
#define GetCharacterRaceText(%0)			(character_race_info[character_data[%0][c_race]])
#define GetCharacterFightStyle(%0)			(character_fighting_style[GetCharacterSettings(%0,SET_STYLE)])
#define GetCharacterRole(%0)				(character_data[%0][c_role])
#define GetCharacterArrestType(%0)			(character_data[%0][c_arrest_type])

#define SetCharacterHealth(%0,%1)			(character_data[%0][c_health]=%1)
#define SetCharacterSettings(%0,%1,%2)		(character_data[%0][c_settings][%1]=%2)
#define SetCharacterDescCreatedTime(%0,%1)	(character_data[%0][c_desc_created_time]=%1)
#define SetCharacterDeath(%0,%1)			(character_data[%0][c_death]=%1)
#define SetCharacterLoaded(%0,%1)			(character_loaded{%0}=%1)

#define IsCharacterCardStartExists(%0)		(character_data[%0][c_start_capital] > 0)
#define IsCharacterLoaded(%0)				(character_loaded{%0})
#define IsCharacterArrested(%0)				(character_data[%0][c_arrest_type] != TYPE_ARREST_NONE)
#define IsCharacterJailed(%0)				(character_data[%0][c_arrest_type] == TYPE_ARREST_JAIL)

// Constants
const MAX_CHARACTER_SUSPECT = 128;

const MAX_CHARACTER_BENEFIT = 200;

const MAX_PAYDAY = 60;

// Structures & Variables
// Статус персонажа
enum E_DRUGS_TIMER // Счетчик таймеров наркотических эффектов
{
	drug_effect_minute_timer,
	drug_effect_second_timer
}

enum 
{
	STATUS_WAIT, // на рассмотрении
	STATUS_ACCEPT, // одобрен
	STATUS_CANCEL, // отклонен
	STATUS_CK // character kill
};

// Раса персонажа
enum
{
	RACE_BLACK = 0,
	RACE_CAUCASOID,
	RACE_MONGOLOID
};

new const character_race_info 			[][] = {
	{"Негроидная"},
	{"Европеоидная"},
	{"Монголоидная"}
};

// Роль персонажа
enum 
{
	ROLE_RESIDENT,
	ROLE_CONVICTED
};

enum E_CHARACTER_SETTINGS /// Настройки персонажа
{
	SET_SPAWN,
	SET_SPAWN_STREET,
	SET_WALK,
	SET_TALK,
	SET_GREETINGS,
	SET_STYLE
};

enum E_CHARACTER_DATA
{
	c_id, // ID персонажа
	c_name								[MAX_PLAYER_NAME],
	Float: c_health,
	Float: c_pos						[4],
	c_world,
	c_int,
	c_role, // Роль
	c_race, // Раса
	c_age, // Возраст
	c_sex, // Пол
	c_skin, // Одежда
	c_money, // Наличные
	c_card, // Средства - Дебетовая карта
	c_bank, // Средства - Банковский счет
	c_credit_level, // Уровень доверия кредитом
	c_last_time,
	c_register_time,
	c_desc								[MAX_PLAYER_DESC],
	c_desc_created_time,
	c_death,
	c_attack_weapon_id,
	c_attack_name_fist					[MAX_PLAYER_NAME],
	c_attack_name_cold					[MAX_PLAYER_NAME],
	c_attack_name_camera				[MAX_PLAYER_NAME],
	c_buy_weapon_count,
	c_payday,
	
	// Стартовый капитал
	c_start_capital, 
	c_start_pack_buy_time, // Время покупки стартового пакета
	
	// Рабочий капитал
	c_capital_value, 
	c_capital_end_time, // Время окончания рабочего капитала
	
	// Fuber
	c_fuber_balance,
	c_fuber_reputation,
	c_fuber_method_payment,
	c_fuber_reputation_time,
	
	// Система фракции
	c_fraction_index, // Fraction ID
	c_fraction_rank_index,
	c_fraction_unit_index,
	c_fraction_leader,
	c_fraction_unit_leader_index,
	c_fraction_duty,
	c_fraction_skin,
	
	// Система наркотиков
	c_drugs_effect						[E_DRUGS_TIMER],
	
	// Настройки
	c_settings							[E_CHARACTER_SETTINGS], 
	
	// Розыск
	c_suspect							[MAX_CHARACTER_SUSPECT],
	
	// Арест игрока
	c_arrest_time,
	c_arrest_type,
	c_arrest_camera,
	
	// Не относящиеся к БД
	c_rpname							[MAX_PLAYER_NAME]
};

enum E_CHARACTER_SELECT_DATA
{
	cs_id,
	cs_name								[MAX_PLAYER_NAME],
	cs_status,
	cs_ban_reason						[64],
	cs_ban_admin_name					[MAX_PLAYER_NAME],
	cs_ban_date,
	cs_ban_before_date,
	bool: cs_is_banned		
};

enum
{
	SPAWN_STREET,
	SPAWN_HOUSE,
	SPAWN_PREMISE,
	SPAWN_FRACTION,
	SPAWN_LAST
}

new const character_spawn_info			[][] =
{
	{"Улица"},
	{"Жилищное помещение"},
	{"Помещение"},
	{"Организация"},
	{"Последняя позиция"}
};

enum E_CHARACTER_SPAWN_STREET_DATA
{
	Float: spawn_street_pos				[ 4 ],
	spawn_street_name					[ 32 ]
};

new const character_spawn_street_info	[][E_CHARACTER_SPAWN_STREET_DATA] =
{
	{{1601.6753, -1247.2823, 17.4714, 180.6457}, "Downtown, Los Santos"},
	{{1771.2964, -1950.0138, 14.1096, 358.5974}, "Unity Station, Los Santos"},
	{{1153.5142, -1489.0834, 22.7690, 89.8016}, "Verona Mall, Los Santos"},
	{{-2138.4736, -2426.7405, 30.6250, 232.0800}, "Angel Pine, Flint County"},
	{{172.4331, -107.9728, 1.5466, 270.9806}, "Blueberry, Red County"}
};

new const character_status_info		[][] = 
{
	{"На рассмотрении"}, 
	{"Активирован"}, 
	{"Отклонен"}, 
	{"Character Kill / Архив"} 
};

new const character_talk_anim		[][] = 
{
	{"IDLE_chat"},
	{"IDLE_chat"},
	{"prtial_gngtlkA"},
	{"prtial_gngtlkB"},
	{"prtial_gngtlkD"},
	{"prtial_gngtlkE"},
	{"prtial_gngtlkF"},
	{"prtial_gngtlkG"}
};

new const character_walk_anim		[][] = 
{
	{"WALK_civi"},
	{"WALK_gang1"},
	{"WALK_gang2"},
	{"WALK_old"},
	{"WALK_fatold"},
	{"WALK_fat"},
	{"WOMAN_walknorm"},
	{"WOMAN_walkbusy"},
	{"WOMAN_walkpro"},
	{"WOMAN_walksexy"},
	{"WALK_drunk"},
	{"Walk_Wuzi"}
};

enum E_CHARACTER_GREETINGS
{
	c_lib	[32],
	c_name	[32]
};

new const character_greetings_anim		[][E_CHARACTER_GREETINGS] =
{
	{"RIOT", "RIOT_ANGRY"},
	{"GANGS", "hndshkfa"},
	{"GANGS", "hndshkfa_swt"},
	{"GANGS", "hndshkba"},
	{"GANGS", "hndshkca"},
	{"GANGS", "hndshkcb"},
	{"GANGS", "hndshkda"},
	{"GANGS", "hndshkea"},
	{"GANGS", "hndshkaa"}
};

new const character_fighting_style	[] =
{
    FIGHT_STYLE_GRABKICK,
    FIGHT_STYLE_BOXING,
    FIGHT_STYLE_KUNGFU,
    FIGHT_STYLE_KNEEHEAD,
    FIGHT_STYLE_ELBOW
};


new character_data					[MAX_PLAYERS][E_CHARACTER_DATA],
	character_select				[MAX_PLAYERS][MAX_CHARACTERS][E_CHARACTER_SELECT_DATA];

new character_loaded 				[MAX_PLAYERS char];

// Functions
Clear:character_select(playerid)
{
	for (new i; i < MAX_CHARACTERS; i++)
	{
		character_select[playerid][i][cs_ban_date] =
		character_select[playerid][i][cs_ban_before_date] =
		character_select[playerid][i][cs_status] = 
		character_select[playerid][i][cs_id] = 0;
		
		character_select[playerid][i][cs_ban_reason][0] =
		character_select[playerid][i][cs_name][0] =
		character_select[playerid][i][cs_ban_admin_name][0] = EOS; 

		character_select[playerid][i][cs_is_banned] = false;
	}
}

Clear:character_data(playerid)
{		
	Clear:character_settings(playerid);
	Clear:character_actions(playerid);
	
	// Other
	character_loaded{playerid} = false;
	
	// String
	character_data[playerid][c_suspect][0] = 
	character_data[playerid][c_attack_name_fist][0] = 
	character_data[playerid][c_attack_name_cold][0] = 
	character_data[playerid][c_attack_name_camera][0] = 
	character_data[playerid][c_desc][0] =
	character_data[playerid][c_name][0] =
	character_data[playerid][c_rpname][0] = EOS;

	// Integer
	character_data[playerid][c_arrest_time] =
	character_data[playerid][c_arrest_camera] =
	character_data[playerid][c_arrest_type] = 0;
	
	character_data[playerid][c_fuber_reputation_time] =
	character_data[playerid][c_fuber_balance] =
	character_data[playerid][c_fuber_reputation] =
	character_data[playerid][c_fuber_method_payment] = 0;
	
	character_data[playerid][c_id] =
	character_data[playerid][c_sex] =
	character_data[playerid][c_skin] =
	character_data[playerid][c_money] =
	character_data[playerid][c_bank] = 
	character_data[playerid][c_card] =
	character_data[playerid][c_int] = 
	character_data[playerid][c_world] =
	character_data[playerid][c_role] =
	character_data[playerid][c_race] =
	character_data[playerid][c_age] =
	character_data[playerid][c_last_time] = 
	character_data[playerid][c_register_time] = 
	character_data[playerid][c_desc_created_time] = 
	character_data[playerid][c_attack_weapon_id] = 
	character_data[playerid][c_buy_weapon_count] =
	character_data[playerid][c_payday] = 
	character_data[playerid][c_start_capital] = 
	character_data[playerid][c_start_pack_buy_time] = 
	character_data[playerid][c_capital_value] = 
	character_data[playerid][c_capital_end_time] = 
	character_data[playerid][c_credit_level] = 0;
	
	character_data[playerid][c_fraction_skin] = 
	character_data[playerid][c_fraction_duty] = 0;
	
	character_data[playerid][c_fraction_index] =
	character_data[playerid][c_fraction_rank_index] =
	character_data[playerid][c_fraction_unit_index] =
	character_data[playerid][c_fraction_unit_leader_index] = 
	character_data[playerid][c_fraction_leader] = INVALID_PARAM;
	
	character_data[playerid][c_drugs_effect][drug_effect_minute_timer] = 
	character_data[playerid][c_drugs_effect][drug_effect_second_timer] = 0;

	// Float
	character_data[playerid][c_pos][0] = 
	character_data[playerid][c_pos][1] = 
	character_data[playerid][c_pos][2] = 
	character_data[playerid][c_pos][3] = 0.0;
	character_data[playerid][c_health] = 100.0;
}

Update:character_int(playerid, column[], _: value)
{
	format:g_string("UPDATE " #__CHARACTERS " SET %s = %d WHERE c_id = %d LIMIT 1",
		column,
		value,
		GetCharacterId(playerid)
	);
	
	mysql_tquery(db, g_string);
}

stock Update:character_string(playerid, column[], const value[], bool: quotes = true)
{
	format:g_string("UPDATE " #__CHARACTERS " SET %s = %s%q%s WHERE c_id = %d LIMIT 1",
		column,
		quotes ? ("'") : (""),
		value,
		quotes ? ("'") : (""),
		GetCharacterId(playerid)
	);
	
	return mysql_tquery(db, g_string);
}

stock Update:character_float(playerid, column[], Float: value)
{
	format:g_string("UPDATE " #__CHARACTERS " SET %s = %f WHERE c_id = %d LIMIT 1",
		column,
		value,
		GetCharacterId(playerid)
	);
	
	return mysql_tquery(db, g_string);
}

Clear:character_settings(playerid)
{
	character_data[playerid][c_settings][SET_WALK] = 
	character_data[playerid][c_settings][SET_SPAWN] = 
	character_data[playerid][c_settings][SET_SPAWN_STREET] = 
	character_data[playerid][c_settings][SET_GREETINGS] = 
	character_data[playerid][c_settings][SET_STYLE] = 
	character_data[playerid][c_settings][SET_TALK] = 0;
}

Update:character_settings(playerid)
{
	if (!IsUserAllowQuery(playerid))
	{
		return;
	}
	
	format:g_string("\
		UPDATE " #__CSETTINGS " \
		SET \
			set_spawn = %i, \
			set_spawn_street = %i, \
			set_walk = %i, \
			set_talk = %i, \
			set_greetings = %i, \
			set_style = %i \
		WHERE \
			set_character_id = %i \
		LIMIT 1",
		GetCharacterSettings(playerid, SET_SPAWN),
		GetCharacterSettings(playerid, SET_SPAWN_STREET),
		GetCharacterSettings(playerid, SET_WALK),
		GetCharacterSettings(playerid, SET_TALK),
		GetCharacterSettings(playerid, SET_GREETINGS),
		GetCharacterSettings(playerid, SET_STYLE),
		GetCharacterId(playerid)
	);
	
	mysql_tquery(db, g_string, "OnCharacterSettingsUpdate", "d", playerid);
	
	SetUserAllowQuery(playerid, false);
}

function OnCharacterSettingsUpdate(playerid)
{
	SetUserAllowQuery(playerid, true);
	return 1;
}