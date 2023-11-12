/**
    @brief Animation system
    @date 21.01.2021
*/

/**
    Defines
*/

// Table name
#define __CANIMATION                            "characters_animation"

/**
    Constants
*/

const MAX_PLAYER_ANIMATION = 10,
	  MAX_ANIM_CMD	= 16,
      MAX_ANIM_GROUP_NAME = 32,
      MAX_ANIM_DESCRIPTION = 64;


/**
    Arrays & Structures
*/

enum
{
    ANIM_HAND_GESTURES, // Жесты руками
    ANIM_EMOTION, // Эмоции
    ANIM_SIT, // Сидеть
    ANIM_LIE_DOWN, // Лежать
    ANIM_RACKS, // Стойки
    ANIM_TRAUMA, // Травмы
    ANIM_BATTLE, // Бой
    ANIM_WEAPON, // Оружие
    ANIM_INTERACTION, // Взаимодействие с объектами
    ANIM_TACTICAL, // Тактическое
    ANIM_SPORT, // Спорт
    ANIM_PROFESSIONAL, // Профессиональное
    ANIM_WALK, // Походки
    ANIM_DANCING, // Танцы
    ANIM_INTIMATE, // Интимное
};

enum E_ANIM_GROUP_LIST
{
    an_id,
    an_name         [MAX_ANIM_GROUP_NAME]
};

static const anim_group_list[][E_ANIM_GROUP_LIST] =
{
    {ANIM_HAND_GESTURES, "Жесты руками"},
    {ANIM_EMOTION, "Эмоции"},
    {ANIM_SIT, "Сидеть"},
    {ANIM_LIE_DOWN, "Лежать"},
    {ANIM_RACKS, "Стойки"},
    {ANIM_TRAUMA, "Травмы"},
    {ANIM_BATTLE, "Бой"},
    {ANIM_WEAPON, "Оружие"},
    {ANIM_INTERACTION, "Взаимодействие с объектами"},
    {ANIM_TACTICAL, "Тактическое"},
    {ANIM_SPORT, "Спорт"},
    {ANIM_PROFESSIONAL, "Профессиональное"},
    {ANIM_WALK, "Походки"},
    {ANIM_DANCING, "Танцы"},
    {ANIM_INTIMATE, "Интимное"}
};

enum E_ANIM_LIST
{
    an_group_id,
    an_cmd              [MAX_ANIM_CMD],
    an_cmd_param        [MAX_ANIM_CMD],
    an_cmd_param_allowed,
    an_description      [MAX_ANIM_DESCRIPTION],
};

static const anim_list[][E_ANIM_LIST] =
{	
    /**
        ANIM_HAND_GESTURES
     */

    {ANIM_HAND_GESTURES, "greet", "ID игрока", 0, "приветствие"},
    {ANIM_HAND_GESTURES, "handsup", "", 0, "поднять руки"},
    {ANIM_HAND_GESTURES, "stoptaxi", "", 0, "махнуть рукой"},
    {ANIM_HAND_GESTURES, "gsign", "1 - 10", 10, "распальцовки"},
    {ANIM_HAND_GESTURES, "hnds", "1 - 7", 7, "вопросительно разводить руками"},
    {ANIM_HAND_GESTURES, "rap", "1 - 9", 9, "активно жестикулировать"},
    {ANIM_HAND_GESTURES, "wave", "1 - 4", 4, "подозвать рукой"},
    {ANIM_HAND_GESTURES, "fucku", "", 0, "показать среднй палец"},
    {ANIM_HAND_GESTURES, "facepalm", "", 0, "рука-лицо"},
    {ANIM_HAND_GESTURES, "stopit", "", 0, "остановить рукой"},
    {ANIM_HAND_GESTURES, "riot", "", 0, "взмахнуть руками вверх"},
    {ANIM_HAND_GESTURES, "chat", "", 0, "общаться жестикулируя"},
    {ANIM_HAND_GESTURES, "chant", "1 - 2", 2, "активно поддерживать"},
    {ANIM_HAND_GESTURES, "rhandl", "", 0, "поднять левую руку."},
    {ANIM_HAND_GESTURES, "rhandr", "", 0, "поднять правую руку"},
    {ANIM_HAND_GESTURES, "hstand", "", 0, "одну руку за голову"},
    {ANIM_HAND_GESTURES, "taxi", "1 - 2", 2, "вытянуть руку в сторону"},
    {ANIM_HAND_GESTURES, "finger", "", 0, "показать что в руке"},
    {ANIM_HAND_GESTURES, "delight", "", 0, "взмахнуть рукой сверху вниз"},
    {ANIM_HAND_GESTURES, "hdelight", "", 0, "взмахнуть рукой снизу вверх"},
    {ANIM_HAND_GESTURES, "wobalance", "", 0, "махать руками у ограждения"},
    {ANIM_HAND_GESTURES, "sho", "", 0, "крикнуть и понтоваться"},
    {ANIM_HAND_GESTURES, "despair", "", 0, "злобно махнуть рукой"},
    {ANIM_HAND_GESTURES, "rooting", "", 0, "взмахивать руками"},
    {ANIM_HAND_GESTURES, "extend", "", 0, "раздвинуть руками"},
    {ANIM_HAND_GESTURES, "wshow", "", 0, "кричать вдаль"},
    {ANIM_HAND_GESTURES, "sh", "", 0, "кричать"},


    /**
        ANIM_EMOTION
    */

    {ANIM_EMOTION, "laugh", "", 0, "смеяться"},
    {ANIM_EMOTION, "cry", "", 0, "плакать"},
    {ANIM_EMOTION, "no", "", 0, "отказаться"},
    {ANIM_EMOTION, "yes", "", 0, "согласиться"},
    {ANIM_EMOTION, "tired", "", 0, "отдышаться"},
    {ANIM_EMOTION, "gro", "", 0, "сидеть на земле"},
    {ANIM_EMOTION, "cmouth", "", 0, "закрыть лицо"},
    {ANIM_EMOTION, "givecash", "", 0, "отдать с поднятыми руками"},
    {ANIM_EMOTION, "robr", "", 0, "испугаться с поднятыми руками"},
    {ANIM_EMOTION, "win", "", 0, "подпрыгнуть от радости"},
    {ANIM_EMOTION, "joy", "", 0, "подпрыгнуть от радости и собрать с пола"},


    /**
        ANIM_SIT
    */

    {ANIM_SIT, "sit", "", 0, "присесть"},
    {ANIM_SIT, "car", "1 - 11", 11, "усесться в машине"},
    {ANIM_SIT, "hide", "", 0, "на корточках с руками за головой"},
    {ANIM_SIT, "seat", "", 0, "рассесться"},
    {ANIM_SIT, "rseat", "", 0, "рассесться с рукой за головой"},
    {ANIM_SIT, "tatto", "", 0, "сидеть облокотив руку"},
    {ANIM_SIT, "wsit", "", 0, "присесть на колено"},
    {ANIM_SIT, "ksit", "", 0, "ударить по столу"},
    {ANIM_SIT, "esit", "", 0, "есть за столом"},
    {ANIM_SIT, "tsit", "", 0, "взглянуть на часы за столом"},
    {ANIM_SIT, "sprawl", "", 0, "присесть на выступ"},
    {ANIM_SIT, "hsit", "", 0, "лениво печатать"},
    {ANIM_SIT, "csit", "", 0, "печатать"},
    {ANIM_SIT, "fsit", "", 0, "сидеть закинув ногу на ногу"},


    /**
        ANIM_LIE_DOWN
    */

    {ANIM_LIE_DOWN, "sleep", "1 - 2", 2, "лечь спать в постель"},
    {ANIM_LIE_DOWN, "lay", "1 - 5", 5, "улечься"},
    {ANIM_LIE_DOWN, "crack", "1 - 7", 7, "лечь под приходом"},
    {ANIM_LIE_DOWN, "frontfall", "", 0, "лежать лицом вниз"},


    /**
        ANIM_RACKS
    */

    {ANIM_RACKS, "lean", "1 - 3", 3, "облокотиться"},
    {ANIM_RACKS, "stand", "", 0, "широко стоять"},
    {ANIM_RACKS, "hips", "", 0, "поместить руки на пояс"},
    {ANIM_RACKS, "crossarms", "", 0, "скрестить руки"},
    {ANIM_RACKS, "feettog", "", 0, "стоять смирно"},
    {ANIM_RACKS, "deal", "1 - 3", 3, "стойка торговца"},
    {ANIM_RACKS, "nlean", "", 0, "статуя свободы"},
    {ANIM_RACKS, "crossfingers", "", 0, "сложить руки в замок"},
    {ANIM_RACKS, "cmon", "", 0, "развести руками и скрестить их"},
    {ANIM_RACKS, "lose", "", 0, "рука-лицо и скрестить руки"},
    {ANIM_RACKS, "onehand", "", 0, "облокотиться руками назад"},
    {ANIM_RACKS, "mirro", "", 0, "стоять раздвинув руки"},
    {ANIM_RACKS, "lookfloor", "", 0, "держаться пригнувшись"},
    {ANIM_RACKS, "agreement", "", 0, "рассуждать сложив руки"},
    {ANIM_RACKS, "tlean", "", 0, "держать спереди двумя руками"},


    /**
        ANIM_TRAUMA
    */

    {ANIM_TRAUMA, "koface", "", 0, "упасть от удара в лицо"},
    {ANIM_TRAUMA, "kostomach", "", 0, "упасть от ранения"},
    {ANIM_TRAUMA, "rollfall", "", 0, "отлететь от удара"},
    {ANIM_TRAUMA, "hoodfrisked", "", 0, "упасть на капот"},
    {ANIM_TRAUMA, "nfall", "", 0, "упасть схватившись за горло"},
    {ANIM_TRAUMA, "wallow", "1 - 2", 2, "отлететь после столкновения"},
    {ANIM_TRAUMA, "nflip", "", 0, "упасть на спину"},
    {ANIM_TRAUMA, "csdead", "", 0, "умереть на животе"},
    {ANIM_TRAUMA, "swingback", "", 0, "подняться со спины"},
    {ANIM_TRAUMA, "pushup", "", 0, "подняться с живота"},
    {ANIM_TRAUMA, "flip", "", 0, "упасть с кувырком"},
    {ANIM_TRAUMA, "injured", "", 0, "лечь с колен"},


    /**
        ANIM_BATTLE
    */

    {ANIM_BATTLE, "gpunch", "", 0, "добить кулаком"},
    {ANIM_BATTLE, "gkick", "", 0, "добить ногой"},
    {ANIM_BATTLE, "tramplefloor", "", 0, "пригнувшись бить ногой"},
    {ANIM_BATTLE, "protection", "", 0, "отпрыгнуть в стойке"},
    {ANIM_BATTLE, "push", "", 0, "толкнуть"},


    /**
        ANIM_WEAPON
    */

    {ANIM_WEAPON, "aim", "", 0, "целиться одной рукой"},
    {ANIM_WEAPON, "gunthreat", "", 0, "угрожать винтовкой"},
    {ANIM_WEAPON, "getarrested", "", 0, "целиться двумя руками"},
    {ANIM_WEAPON, "faim", "", 0, "целиться вниз двумя руками"},
    {ANIM_WEAPON, "polwalk", "", 0, "идти целясь вниз"},
    {ANIM_WEAPON, "shotgun", "1 - 3", 3, "держать ружье"},
    {ANIM_WEAPON, "colt", "1 - 3", 3, "держать пистолет"},
    {ANIM_WEAPON, "waim", "1 - 3", 3, "целиться"},
    {ANIM_WEAPON, "shelter", "", 0, "целиться из-за укрытия"},
    {ANIM_WEAPON, "squat", "", 0, "выстрелить из-за укрытия"},


    /**
        ANIM_INTERACTION
    */

    {ANIM_INTERACTION, "aspray", "", 0, "распылять по стене"},
    {ANIM_INTERACTION, "caim", "", 0, "держать в руке"},
    {ANIM_INTERACTION, "smoke", "1 - 6", 6, "курить"},
    {ANIM_INTERACTION, "eat", "", 0, "кушать"},
    {ANIM_INTERACTION, "sipdrink", "", 0, "пить"},
    {ANIM_INTERACTION, "bomb", "", 0, "положить что-то на землю"},
    {ANIM_INTERACTION, "bat", "1 - 2", 2, "держать биту"},
    {ANIM_INTERACTION, "cellin", "", 0, "достать телефон"},
    {ANIM_INTERACTION, "cellout", "", 0, "убрать телефон"},
    {ANIM_INTERACTION, "grnd", "", 0, "потрогать что-то на земле"},
    {ANIM_INTERACTION, "wear", "", 0, "переносить в руках"},
    {ANIM_INTERACTION, "gog", "", 0, "держать у глаз"},
    {ANIM_INTERACTION, "spyglass", "", 0, "держать перед лицом"},
    {ANIM_INTERACTION, "readtable", "", 0, "стоя перелистнуть книгу"},
    {ANIM_INTERACTION, "swallow", "", 0, "достать из кармана"},
    {ANIM_INTERACTION, "showtable", "", 0, "стоя передать по столу"},
    {ANIM_INTERACTION, "tfacepalm", "", 0, "стоя ударить по столу"},
    {ANIM_INTERACTION, "tpull", "", 0, "вынуть из кармана и передать"},
    {ANIM_INTERACTION, "fail", "", 0, "ударить рукой и ногой по столу"},
    {ANIM_INTERACTION, "rtake", "", 0, "передать через столешницу"},
    {ANIM_INTERACTION, "taction", "", 0, "складывать что-то перед собой"},
    {ANIM_INTERACTION, "ssearch", "", 0, "вытаскивать снизу"},
    {ANIM_INTERACTION, "daim", "", 0, "держать тяжелое"},

    
    /**
        ANIM_TACTICAL
    */

    {ANIM_TACTICAL, "lookout", "1 - 3", 3, "выглядывать"},
    {ANIM_TACTICAL, "bend", "", 0, "подслушивать"},
    {ANIM_TACTICAL, "crawl", "", 0, "ползти и встать"},
    {ANIM_TACTICAL, "lifejump", "", 0, "кувыркнуться"},
    {ANIM_TACTICAL, "lookback", "", 0, "оглядеться"},
    {ANIM_TACTICAL, "follow", "", 0, "команда \"вперед!\""},
    {ANIM_TACTICAL, "lowthrow", "", 0, "подкинуть что-либо"},
    {ANIM_TACTICAL, "copa", "", 0, "жестикулировать сидя на колене"},
    {ANIM_TACTICAL, "sroll", "", 0, "перепрыгнуть через ограждение"},
    {ANIM_TACTICAL, "gesture", "", 0, "указать направление"},
    {ANIM_TACTICAL, "tgro", "", 0, "присесть на колено"},
    {ANIM_TACTICAL, "pullo", "", 0, "открыть с усилием"},
    {ANIM_TACTICAL, "heist", "", 0, "указать напротив"},
    {ANIM_TACTICAL, "beckon", "1 - 3", 3, "подозвать к себе"},
    {ANIM_TACTICAL, "takehead", "", 0, "держаться из-за угла"},
    {ANIM_TACTICAL, "pullhand", "", 0, "держать спереди одной рукой"},
    {ANIM_TACTICAL, "nlook", "", 0, "оглянуться по сторонам"},
    {ANIM_TACTICAL, "looksky", "", 0, "смотреть вдаль"},
    {ANIM_TACTICAL, "mshow", "", 0, "указывать вдаль"},
    {ANIM_TACTICAL, "catch", "", 0, "повиснуть с коленями на земле"},
    {ANIM_TACTICAL, "hshow", "", 0, "указывать вдаль"},
    {ANIM_TACTICAL, "obalance", "", 0, "глянуть вниз за ограждение"},
    {ANIM_TACTICAL, "crushjump", "", 0, "отпрыгнуть в сторону"},


    /**
        ANIM_SPORT
    */

    {ANIM_SPORT, "basket", "1 - 6", 6, "играть в баскетбол"},
    {ANIM_SPORT, "box", "", 0, "боксировать"},
    {ANIM_SPORT, "rod", "", 0, "жим лежа"},
    {ANIM_SPORT, "bracing", "", 0, "размять спину"},
    {ANIM_SPORT, "pool", "", 0, "играть в бильярд"},
    {ANIM_SPORT, "abp", "", 0, "демонстрация бицепса"},
    {ANIM_SPORT, "nbp", "", 0, "демонстрировать телосложение"},
    {ANIM_SPORT, "swing", "", 0, "стоя поднять штангу"},
    {ANIM_SPORT, "scatch", "", 0, "качаться на весу"},
    {ANIM_SPORT, "climb", "", 0, "подвиснуть на руках"},


    /**
        ANIM_PROFESSIONAL
    */

    {ANIM_PROFESSIONAL, "medic", "", 0, "реанимировать"},
    {ANIM_PROFESSIONAL, "police", "1 - 4", 4, "регулировать движение"},
    {ANIM_PROFESSIONAL, "akick", "", 0, "выбить ногой"},
    {ANIM_PROFESSIONAL, "lowbodypush", "", 0, "выбить плечом"},
    {ANIM_PROFESSIONAL, "repcar", "1 - 2", 0, "ремонтировать под машиной"},
    {ANIM_PROFESSIONAL, "serend", "", 0, "работать с кассой"},
    {ANIM_PROFESSIONAL, "bar", "", 0, "нагнуться под бар"},

    
    /**
        ANIM_WALK
    */

    {ANIM_WALK, "walk", "", 0, "походки"},
    {ANIM_WALK, "drunk", "", 0, "пьяная походка"},
    {ANIM_WALK, "creep", "", 0, "красться"},
    {ANIM_WALK, "backwalk", "", 0, "отходить назад держась за лицо"},


    /**
        ANIM_DANCING
    */

    {ANIM_DANCING, "dance", "1 - 12", 12, "танцевать"},
    {ANIM_DANCING, "strip", "", 0, "стриптиз"},
    {ANIM_DANCING, "taichi", "", 0, "медитировать"},

    
    /**
        ANIM_INTIMATE
    */

    {ANIM_INTIMATE, "piss", "", 0, "отливать"},
    {ANIM_INTIMATE, "balls", "", 0, "чесать пах"},
    {ANIM_INTIMATE, "slapass", "", 0, "шлепнуть"},
    {ANIM_INTIMATE, "blowj", "", 0, "удовлетворять орально"},
    {ANIM_INTIMATE, "pants", "", 0, "стоя давать в рот"},
    {ANIM_INTIMATE, "bj", "1 - 12", 12, "заниматься сексом"}, 
    {ANIM_INTIMATE, "spank", "", 0, "принимать и бить по заднице"},
    {ANIM_INTIMATE, "vomit", "", 0, "наблевать"},
    {ANIM_INTIMATE, "carbj", "1 - 6", 6, "секс в автомобиле"},
    {ANIM_INTIMATE, "hangon", "", 0, "подвиснуть задом кверху"}
};

static const anim_libs[][] = 
{
    {"PED"},
	{"BOMBER"},
	{"RAPPING"},
	{"SHOP"},
	{"BEACH"},
	{"SMOKING"},
	{"FOOD"},
	{"ON_LOOKERS"},
	{"DEALER"},
	{"CRACK"},
	{"CARRY"},
	{"COP_AMBIENT"},
	{"PARK"},
	{"INT_HOUSE"},
	{"GHANDS"},
	{"GANGS"},
	{"RIOT"},
	{"PAULNMAC"},
	{"FIGHT_B"},
	{"FIGHT_D"},
	{"SPRAYCAN"},
	{"MISC"},
	{"GRAVEYARD"},
	{"POLICE"},
	{"CAR_CHAT"},
	{"SWEET"},
	{"SUNBATHE"},
	{"CRIB"},
	{"BAR"},
	{"DANCING"},
	{"VENDING"},
	{"BSKTBALL"},
	{"BD_FIRE"},
	{"COLT45"},
	{"SILENCED"},
	{"TEC"},
	{"UZI"},
	{"OTB"},
	{"CAR"},
	{"MEDIC"},
	{"WUZI"},
	{"BLOWJOBZ"},
	{"LOWRIDER"},
	{"FINALE"},
	{"CLOTHES"},
	{"SNM"},
	{"CASINO"}
};

enum E_PLAYER_ANIM_DATA 
{
	an_cmd					                [MAX_ANIM_CMD],
	an_cmd_param
};

static player_anim_data		                [MAX_PLAYERS][MAX_PLAYER_ANIMATION][E_PLAYER_ANIM_DATA];

static player_anim_walk                     [MAX_PLAYERS],
       player_anim_count                    [MAX_PLAYERS char],
       player_anim_index                    [MAX_PLAYERS char],
       player_anim_cmd                      [MAX_PLAYERS][MAX_ANIM_CMD],
       player_anim_param                    [MAX_PLAYERS char],
       player_greet_target_id               [MAX_PLAYERS] = {INVALID_PLAYER_ID, ...},
       bool: player_anim_no_skip            [MAX_PLAYERS char],
       bool: player_anim_states             [MAX_PLAYERS char],
       bool: player_anim_reset_disable      [MAX_PLAYERS char],
       bool: player_anim_walk_active        [MAX_PLAYERS char],
       bool: player_anim_favorite_close     [MAX_PLAYERS char];


/**
    Getters & Setters
*/

// Player anim data
stock GetPlayerAnimData(playerid, const _: index, data[E_PLAYER_ANIM_DATA])
{
    data = player_anim_data[playerid][index];
}

stock SetPlayerAnimData(playerid, const _: index, const data[E_PLAYER_ANIM_DATA])
{
    player_anim_data[playerid][index] = data;
}

// Player anim count
static stock GetPlayerAnimCount(playerid)
{
    return player_anim_count{playerid};
}

static stock SetPlayerAnimCount(playerid, const _: value)
{
    player_anim_count{playerid} = value;
}

// Player anim index
static stock GetPlayerAnimIndex(playerid)
{
    return player_anim_index{playerid};
}

static stock SetPlayerAnimIndex(playerid, const _: value)
{
    player_anim_index{playerid} = value;
}

// Player anim param
static stock GetPlayerAnimParam(playerid)
{
    return player_anim_param{playerid};
}

static stock SetPlayerAnimParam(playerid, const _: value)
{
    player_anim_param{playerid} = value;
}

// Player anim target id
static stock GetPlayerGreetTargetID(playerid)
{
    return player_greet_target_id{playerid};
}

static stock SetPlayerGreetTargetID(playerid, const _: value)
{
    player_greet_target_id{playerid} = value;
}

// Player anim no skip
static stock HasPlayerAnimNoSkip(playerid)
{
    return player_anim_no_skip{playerid};
}

static stock TogglePlayerAnimNoSkip(playerid, const bool: value)
{
    player_anim_no_skip{playerid} = value;
}

// Player anim states
stock HasPlayerAnimStates(playerid)
{
    return player_anim_states{playerid};
}

static stock TogglePlayerAnimStates(playerid, const bool: value)
{
    player_anim_states{playerid} = value;
}

// Player anim reset disabled
stock HasPlayerAnimResetDisable(playerid)
{
    return player_anim_reset_disable{playerid};
}

stock TogglePlayerAnimResetDisable(playerid, const bool: value)
{
    player_anim_reset_disable{playerid} = value;
}

// Player anim walk active
stock HasPlayerAnimWalkActive(playerid)
{
    return player_anim_walk_active{playerid};
}

stock TogglePlayerAnimWalkActive(playerid, const bool: value)
{
    player_anim_walk_active{playerid} = value;
}

// Player anim favorite close
static stock HasPlayerAnimFavoriteClose(playerid)
{
    return player_anim_favorite_close{playerid};
}

static stock TogglePlayerAnimFavoriteClose(playerid, const bool: value)
{
    player_anim_favorite_close{playerid} = value;
}

// Player anim CMD
static stock GetPlayerAnimCMD(playerid, value[])
{
    clean:<value>;
    strcat(value, player_anim_cmd[playerid], MAX_ANIM_CMD);
}

static stock SetPlayerAnimCmd(playerid, const value[])
{
    clean:<player_anim_cmd[playerid]>;
    strcat(player_anim_cmd[playerid], value, MAX_ANIM_CMD);
}

static stock ResetPlayerAnimCmd(playerid)
{
    clean:<player_anim_cmd[playerid]>;
}

// Player walk
static stock GetPlayerAnimWalk(playerid)
{
    return player_anim_walk[playerid];
}

static stock SetPlayerAnimWalk(playerid, const _: value)
{
    player_anim_walk[playerid] = value;
}

static stock ResetPlayerAnimWalk(playerid)
{
    if (player_anim_walk[playerid] != 0)
    {
        KillTimer(player_anim_walk[playerid]);
    }

    player_anim_walk[playerid] = 0;
}

/**
    Data manipulation function
*/

ResetPlayerAnimData(playerid)
{
    new const data[E_PLAYER_ANIM_DATA] = {0, EOS};

    for (new i; i < MAX_PLAYER_ANIMATION; i++)
	{
		SetPlayerAnimData(playerid, i, data);
	}
    
    SetPlayerAnimCount(playerid, 0);
    SetPlayerAnimIndex(playerid, 0);
    SetPlayerAnimParam(playerid, 0);
    TogglePlayerAnimFavoriteClose(playerid, false);
    TogglePlayerAnimNoSkip(playerid, false);
    TogglePlayerAnimStates(playerid, false);
    TogglePlayerAnimResetDisable(playerid, false);
    ResetPlayerAnimCmd(playerid);
    ResetPlayerAnimWalk(playerid);

    SetPlayerGreetTargetID(playerid, INVALID_PLAYER_ID);
}

LoadPlayerAnimData(playerid)
{
	format:g_string("SELECT * FROM " #__CANIMATION " WHERE character_id = %i LIMIT %i",
		GetCharacterId(playerid),
		MAX_PLAYER_ANIMATION
	);
	
	mysql_tquery(db, g_string, "OnPlayerAnimationLoad", "d", playerid);
}

function OnPlayerAnimationLoad(playerid)
{
    new data    [E_PLAYER_ANIM_DATA];

	new rows,
		index;
	
	cache_get_row_count(rows);
	
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "index", index);
		
		if (!(0 <= index <= MAX_PLAYER_ANIMATION))
		{
			continue;
		}
		
		cache_get_value_name(i, "cmd", data[an_cmd], MAX_ANIM_CMD);
		cache_get_value_name_int(i, "cmd_param", data[an_cmd_param]);
        
        SetPlayerAnimData(playerid, index, data);
	}
	
	return 1;
}

SavePlayerAnimData(playerid, const index, const data[E_PLAYER_ANIM_DATA])
{
	if (!IsUserAllowQuery(playerid))
	{
		return;
	}
	
    new current_data[E_PLAYER_ANIM_DATA];
    GetPlayerAnimData(playerid, index, current_data);

    if (isnull(current_data[an_cmd])) // Create
    {   
        format:g_string("INSERT INTO " #__CANIMATION " \
            VALUES (%i, '%q', %d, %d)",
            GetCharacterId(playerid),
            data[an_cmd],
            data[an_cmd_param],
            index
        );
    }
	else // Update
    {
        format:g_string("UPDATE " #__CANIMATION " \
            SET \
                cmd = '%s', \
                cmd_param = %d \
            WHERE character_id = %d AND `index` = %d",
            data[an_cmd],
            data[an_cmd_param],
            GetCharacterId(playerid),
            index
        );
    }

    SetPlayerAnimData(playerid, index, data);
    mysql_tquery(db, g_string, "OnAnimPlayerDataSave", "d", playerid);

    SetUserAllowQuery(playerid, false);
}

function OnAnimPlayerDataSave(playerid)
{
	SetUserAllowQuery(playerid, true);

	return 1;
}

DeletePlayerAnimData(playerid, const index)
{
	format:g_string("DELETE FROM " #__CANIMATION " WHERE character_id = %d AND `index` = %d LIMIT 1",
		GetCharacterId(playerid),
		index
	);
	
	mysql_tquery(db, g_string);
	
    new data[E_PLAYER_ANIM_DATA];
    SetPlayerAnimData(playerid, index, data);
}


/**
    Public functions
*/

function OnCharacterAfterLoad(playerid)
{
    LoadPlayerAnimData(playerid);

	#if defined Anim_OnCharacterAfterLoad
		return Anim_OnCharacterAfterLoad(playerid);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnCharacterAfterLoad
    #undef OnCharacterAfterLoad
#else
    #define _ALS_OnCharacterAfterLoad
#endif

#define	OnCharacterAfterLoad	Anim_OnCharacterAfterLoad
#if defined Anim_OnCharacterAfterLoad
	forward Anim_OnCharacterAfterLoad(playerid);
#endif


function OnPlayerDataReset(playerid, bool: is_relogin)
{
    ResetPlayerAnimData(playerid);
	#if defined Anim_OnPlayerDataReset
		return Anim_OnPlayerDataReset(playerid, is_relogin);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDataReset
    #undef OnPlayerDataReset
#else
    #define _ALS_OnPlayerDataReset
#endif

#define	OnPlayerDataReset	Anim_OnPlayerDataReset
#if defined Anim_OnPlayerDataReset
	forward Anim_OnPlayerDataReset(playerid, bool: is_relogin);
#endif


public OnPlayerConnect(playerid)
{
    PreloadAnimationLibs(playerid);

	#if defined Anim_OnPlayerConnect
		return Anim_OnPlayerConnect(playerid);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif

#define	OnPlayerConnect	Anim_OnPlayerConnect
#if defined Anim_OnPlayerConnect
	forward Anim_OnPlayerConnect(playerid);
#endif


public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{	
	if (GetCharacterDeath(playerid) == TYPE_DEATH_NONE
	&& GetCharacterSettings(playerid, SET_WALK) != 0
    && !PRESSING(newkeys, KEY_JUMP)
	&& ((newkeys & KEY_WALK && newkeys & KEY_UP) 
	|| (newkeys & KEY_WALK && newkeys & KEY_DOWN) 
	|| (newkeys & KEY_WALK && newkeys & KEY_LEFT) 
	|| (newkeys & KEY_WALK && newkeys & KEY_RIGHT))
	|| ((oldkeys & KEY_WALK && newkeys & KEY_UP) 
	|| (oldkeys & KEY_WALK && newkeys & KEY_DOWN) 
	|| (oldkeys & KEY_WALK && newkeys & KEY_LEFT) 
	|| (oldkeys & KEY_WALK && newkeys & KEY_RIGHT))
	|| ((newkeys & KEY_WALK && oldkeys & KEY_UP) 
	|| (newkeys & KEY_WALK && oldkeys & KEY_DOWN) 
	|| (newkeys & KEY_WALK && oldkeys & KEY_LEFT) 
	|| (newkeys & KEY_WALK && oldkeys & KEY_RIGHT))
	&& GetPlayerState(playerid) == PLAYER_STATE_ONFOOT) 
	{
		SetPlayerAnimWalk(playerid,
            SetTimerEx("OnPlayerAnimationWalk", 200, false, "d", playerid)
        );
	}
	
	#if defined Anim_OnPlayerKeyStateChange
		return Anim_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange	Anim_OnPlayerKeyStateChange
#if defined Anim_OnPlayerKeyStateChange
	forward Anim_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif


function OnPlayerAnimationWalk(playerid)
{
    new index = GetCharacterSettings(playerid, SET_WALK);

	if (index == 0)
	{
		return 0;
	}
	
	new keys, 
		updown, 
		leftright;
		
	GetPlayerKeys(playerid, keys, updown, leftright);

	if ((keys & KEY_WALK && updown & KEY_UP) 
	|| (keys & KEY_WALK && updown & KEY_DOWN) 
	|| (keys & KEY_WALK && leftright & KEY_LEFT) 
	|| (keys & KEY_WALK && leftright & KEY_RIGHT)) 
	{
		ResetPlayerAnimWalk(playerid);
		ApplyAnimation(playerid, "PED", character_walk_anim[index], 4.1, 1, 1, 1, 1, 1);
		SetPlayerAnimWalk(playerid,
            SetTimerEx("OnPlayerAnimationWalk", 200, false, "i", playerid)
        );
	}
	else 
	{
		ApplyAnimation(playerid, "PED", character_walk_anim[index], 4.0, 0, 0, 0, 0, 1);
		ResetPlayerAnimWalk(playerid);
	}
	
	return 1;
}

/**
    Dialogs
*/

DialogResponse:ANIM(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        return 1;
    }

    if (listitem == 0)
    {
        Dialog_Show(playerid, Dialog:ANIM_GROUP_LIST);
    }
    else if (listitem == 1)
    {
        Dialog_Show(playerid, Dialog:ANIM_FAVORITES);
    }

    return 1;
}

// ANIM_GROUP_LIST
DialogCreate:ANIM_GROUP_LIST(playerid)
{
    clean:<g_big_string>;

    for (new i; i < sizeof(anim_group_list); i++)
	{
		format:g_big_string("%s %s\n", 
			g_big_string, 
			anim_group_list[i][an_name]
		);
	}

    Dialog_Open(playerid, Dialog:ANIM_GROUP_LIST, DIALOG_STYLE_LIST, "Список всех анимаций", g_big_string, "Выбрать", "Назад");
    return 1;
}

DialogResponse:ANIM_GROUP_LIST(playerid, response, listitem, inputtext[])
{
    if (!response) 
    {
        cmd_anim(playerid);
        return 1;
    }

    clean:<g_small_string>;
    valstr(g_small_string, listitem);
    Dialog_Show(playerid, Dialog:ANIM_GROUP_LIST_VIEW, g_small_string);
    return 1;
}

// ANIM_GROUP_LIST_VIEW
DialogCreate:ANIM_GROUP_LIST_VIEW(playerid, params[])
{
    new group_id = strval(params);

    if (!(0 <= group_id < sizeof(anim_group_list)))
    {
        return 1;
    }

    clean:<g_big_string>;

    for (new i; i < sizeof(anim_list); i++)
    {
        if (anim_list[i][an_group_id] != group_id)
        {
            continue;
        }

        format:g_big_string("%s " #cPROJECT "/%s%s%s%s" #cWHITE " -  %s.\n", 
            g_big_string,
            anim_list[i][an_cmd],
            isnull(anim_list[i][an_cmd_param]) ? "" : " [",
            anim_list[i][an_cmd_param],
            isnull(anim_list[i][an_cmd_param]) ? "" : "]",
            anim_list[i][an_description]
        );
    }
    
    Dialog_Open(
        playerid, 
        Dialog:ANIM_GROUP_LIST_VIEW, 
        DIALOG_STYLE_MSGBOX, 
        anim_group_list[group_id][an_name], 
        g_big_string, 
        "Назад", 
        ""
    );

    return 1;
}

DialogResponse:ANIM_GROUP_LIST_VIEW(playerid, response, listitem, inputtext[])
{
    Dialog_Show(playerid, Dialog:ANIM_GROUP_LIST);
    return 1;
}

// ANIM_FAVORITES
DialogCreate:ANIM_FAVORITES(playerid, params[])
{	
	new param[MAX_ANIM_CMD],
		count;
    
    clean:<g_string>;
	strcat(g_string, #cGRAY "Добавить анимацию\t\n");
	for (new i; i < MAX_PLAYER_ANIMATION; i++)
	{
		if (isnull(player_anim_data[playerid][i][an_cmd]))
		{
			continue;
		}
		
		clean:<param>;
		
		if (player_anim_data[playerid][i][an_cmd_param] != 0)
		{
			format:param(" %i", player_anim_data[playerid][i][an_cmd_param]);
		}
		
		format:g_string("%s " #cWHITE "/%s%s\t" #cGRAY "/an %i\n", 
			g_string, 
			player_anim_data[playerid][i][an_cmd],
			param,
			i + 1
		);
		
		g_dialog_select[playerid][count++] = i;
	}
	
    SetPlayerAnimCount(playerid, count);
	
	Dialog_Open(playerid, Dialog:ANIM_FAVORITES, DIALOG_STYLE_TABLIST, "Избранные анимации", g_string, "Выбрать", "Закрыть");
    return 1;
}

DialogResponse:ANIM_FAVORITES(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        if (HasPlayerAnimFavoriteClose(playerid))
        {
            TogglePlayerAnimFavoriteClose(playerid, false);
            return 1;
        }

        SetPlayerAnimIndex(playerid, 0);
        SetPlayerAnimCount(playerid, 0);
        cmd_anim(playerid);
        return 1;
    }
    
    if (listitem == 0)
    {
        new count = GetPlayerAnimCount(playerid);

        if (count == MAX_PLAYER_ANIMATION)
        {
            Dialog_Show(playerid, Dialog:ANIM_FAVORITES);
            SendClientMessage(playerid, C_WHITE, !#ERROR " Превышен лимит избранных анимаций");
            return 1;
        }

        Dialog_Show(playerid, Dialog:ANIM_FAVORITES_CREATE);
        return 1;
    }
    
    listitem--;
    new index = GetPlayerDialogItemValue(playerid, listitem);

    SetPlayerAnimIndex(playerid, index);

    clean:<g_small_string>;
    valstr(g_small_string, index);
    Dialog_Show(playerid, Dialog:ANIM_FAVORITES_ACTION, g_small_string);
    return 1;
}

// ANIM_FAVORITES_ACTION
DialogCreate:ANIM_FAVORITES_ACTION(playerid, params[])
{
    new data[E_PLAYER_ANIM_DATA];
    new index = strval(params);

    GetPlayerAnimData(playerid, index, data);
	
    clean:<g_small_string>;
    if (data[an_cmd_param] != 0)
    {
        format:g_small_string(" %d", data[an_cmd_param]);
    }   

    format:g_string(" \
        Изменить команду\t" #cPROJECT "/%s%s" #cWHITE "\n \
        Изменить слот\t" #cPROJECT "/an %d\n \
        " #CI_DIALOG_DELETE "Удалить",
        data[an_cmd],
        g_small_string,
        index + 1
    );

    Dialog_Open(
        playerid, 
        Dialog:ANIM_FAVORITES_ACTION, 
        DIALOG_STYLE_TABLIST, 
        "Действие", 
        g_string,
        "Далее", "Назад"
    );
    return 1;
}

DialogResponse:ANIM_FAVORITES_ACTION(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        if (listitem == 0) // Change command
        {
            Dialog_Show(playerid, Dialog:ANIM_FAVORITES_CHANGE_CMD);
            return 1;
        } 
        else if (listitem == 1) // Change slot
        {
            Dialog_Show(playerid, Dialog:ANIM_FAVORITES_CHANGE_SLOT);
            return 1;
        }

        new index = GetPlayerAnimIndex(playerid);
        DeletePlayerAnimData(playerid, index);
        SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно удалили анимацию из избранных.");
    }

    Dialog_Show(playerid, Dialog:ANIM_FAVORITES);

    return 1;
}

// ANIM_FAVORITES_CHANGE_CMD
DialogCreate:ANIM_FAVORITES_CHANGE_CMD(playerid, params[])
{
    format:g_string(#CI_DIALOG_INFO "Введите команду, на которую Вы хотите заменить действующую анимацию:\n\n\
        " #cGRAY "Пример: /laugh, /lean 2;%s\
        " #cRED "%s",
        isnull(params) ? "" : "\n",
        isnull(params) ? "" : params
    );

    Dialog_Open(playerid, Dialog:ANIM_FAVORITES_CHANGE_CMD, DIALOG_STYLE_INPUT, 
        "Изменить команду", 
        g_string,
        "Далее", "Назад"
    );

    return 1;
}

DialogResponse:ANIM_FAVORITES_CHANGE_CMD(playerid, response, listitem, inputtext[])
{
    new index = GetPlayerAnimIndex(playerid);

    if (!response)
    {
        clean:<g_small_string>;
        valstr(g_small_string, index);
        Dialog_Show(playerid, Dialog:ANIM_FAVORITES_ACTION, g_small_string);
        return 1;
    }

    new data[E_PLAYER_ANIM_DATA];
    
    strdel(inputtext, 0, 1);
    if (sscanf(inputtext, "s[13]I(0)", data[an_cmd], data[an_cmd_param]) 
    || !IsAnimationCmdValid(data[an_cmd], data[an_cmd_param])) 
    {
        Dialog_Show(playerid, Dialog:ANIM_FAVORITES_CHANGE_CMD, "Вы ввели неверную команду.");
        return 1;
    }

    if (IsPlayerAnimationExist(playerid, data[an_cmd], data[an_cmd_param]))
    {
        Dialog_Show(playerid, Dialog:ANIM_FAVORITES_CREATE, "Данная команда уже была добавлена.");
        return 1;
    }

    SavePlayerAnimData(playerid, index, data);

    clean:<g_small_string>;
    valstr(g_small_string, index);
    Dialog_Show(playerid, Dialog:ANIM_FAVORITES_ACTION, g_small_string);
    return 1;
}

// ANIM_FAVORITES_CHANGE_SLOT
DialogCreate:ANIM_FAVORITES_CHANGE_SLOT(playerid, params[])
{
    format:g_string(#CI_DIALOG_INFO "Введите номер свободного слота быстрого действия " #cGRAY "(/an)" #cWHITE ":\n\n\
        " #cGRAY "Занимаемый слот должен быть от 1 и до 10.%s\
        " #cRED "%s",
        isnull(params) ? "": "\n",
        isnull(params) ? "": params
    );

    Dialog_Open(playerid, Dialog:ANIM_FAVORITES_CHANGE_SLOT, DIALOG_STYLE_INPUT, "Изменить слот", 
        g_string,
        "Далее", "Назад"
    );

    return 1;
}

DialogResponse:ANIM_FAVORITES_CHANGE_SLOT(playerid, response, listitem, inputtext[])
{
    new index = GetPlayerAnimIndex(playerid);

    if (!response)
    {
        clean:<g_small_string>;
        valstr(g_small_string, index);
        Dialog_Show(playerid, Dialog:ANIM_FAVORITES_ACTION, g_small_string);
        return 1;
    }
    
    new value = strval(inputtext);
    
    if (!(1 <= value <= MAX_PLAYER_ANIMATION))
    {
        Dialog_Show(playerid, Dialog:ANIM_FAVORITES_CHANGE_SLOT, "Указан неверный слон.");
        return 1;
    }

    value--;

    new data[E_PLAYER_ANIM_DATA];
    GetPlayerAnimData(playerid, value, data);

    if (!isnull(data[an_cmd]))
    {
        Dialog_Show(playerid, Dialog:ANIM_FAVORITES_CHANGE_SLOT, "Указанный слот занят.");
        return 1;
    }

    GetPlayerAnimData(playerid, index, data);

    // Create record with new index
    SavePlayerAnimData(playerid, value, data);

    // Delete record with old index
    DeletePlayerAnimData(playerid, index);

    // Back to manage menu
    clean:<g_small_string>;
    valstr(g_small_string, value);
    Dialog_Show(playerid, Dialog:ANIM_FAVORITES_ACTION, g_small_string);
    return 1;
}

// ANIM_FAVORITES_CREATE
DialogCreate:ANIM_FAVORITES_CREATE(playerid, params[])
{
    format:g_string(#CI_DIALOG_INFO "Введите команду, которую Вы хотите добавить в избранное:\n\n\
        " #cGRAY "Пример: /laugh, /lean 2;%s\
        " #cRED "%s",
        isnull(params) ? "" : "\n",
        isnull(params) ? "" : params
    );

    Dialog_Open(playerid, Dialog:ANIM_FAVORITES_CREATE, DIALOG_STYLE_INPUT, 
        "Добавить анимацию", 
        g_string,
        "Далее", "Назад"
    );

    return 1;
}

DialogResponse:ANIM_FAVORITES_CREATE(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        ResetPlayerAnimCmd(playerid);
        SetPlayerAnimParam(playerid, 0);
        Dialog_Show(playerid, Dialog:ANIM_FAVORITES);
        return 1;
    }
    
    new data[E_PLAYER_ANIM_DATA];
    
    strdel(inputtext, 0, 1);
    if (sscanf(inputtext, "s[13]I(0)", data[an_cmd], data[an_cmd_param]) 
    || !IsAnimationCmdValid(data[an_cmd], data[an_cmd_param]))
    {
        Dialog_Show(playerid, Dialog:ANIM_FAVORITES_CREATE, "Вы ввели неверную команду.");
        return 1;
    }

    if (IsPlayerAnimationExist(playerid, data[an_cmd], data[an_cmd_param]))
    {
        Dialog_Show(playerid, Dialog:ANIM_FAVORITES_CREATE, "Данная команда уже была добавлена.");
        return 1;
    }
    
    SetPlayerAnimCmd(playerid, data[an_cmd]);
    SetPlayerAnimParam(playerid, data[an_cmd_param]);
    
    Dialog_Show(playerid, Dialog:ANIM_FAVORITES_CREATE_SLOT);
    return 1;
}

// ANIM_FAVORITES_CREATE_SLOT
DialogCreate:ANIM_FAVORITES_CREATE_SLOT(playerid, params[])
{
    format:g_string(#CI_DIALOG_INFO "Введите номер свободного слота быстрого действия " #cGRAY "(/an)" #cWHITE ":\n\n\
        " #cGRAY "Занимаемый слот должен быть от 1 и до 10.%s\
        " #cRED "%s",
        isnull(params) ? "": "\n",
        isnull(params) ? "": params
    );

    Dialog_Open(playerid, Dialog:ANIM_FAVORITES_CREATE_SLOT, DIALOG_STYLE_INPUT, "Добавить анимацию", 
        g_string,
        "Далее", "Назад"
    );

    return 1;
}

DialogResponse:ANIM_FAVORITES_CREATE_SLOT(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        Dialog_Show(playerid, Dialog:ANIM_FAVORITES_CREATE);
        return 1;
    }
    
    new value = strval(inputtext);
    
    if (!(1 <= value <= MAX_PLAYER_ANIMATION))
    {
        Dialog_Show(playerid, Dialog:ANIM_FAVORITES_CREATE_SLOT, "Указан неверный слот.");
        return 1;
    }

    value--;

    new data[E_PLAYER_ANIM_DATA];
    GetPlayerAnimData(playerid, value, data);

    if (!isnull(data[an_cmd]))
    {
        Dialog_Show(playerid, Dialog:ANIM_FAVORITES_CREATE_SLOT, "Указанный слот занят.");
        return 1;
    }

    GetPlayerAnimCMD(playerid, data[an_cmd]);
    data[an_cmd_param] = GetPlayerAnimParam(playerid);

    if (IsPlayerAnimationExist(playerid, data[an_cmd], data[an_cmd_param]))
    {
        Dialog_Show(playerid, Dialog:ANIM_FAVORITES_CREATE_SLOT, "Данная команда уже была добавлена.");
        return 1;
    }

    SavePlayerAnimData(playerid, value, data);
    
    // Reset temporary data
    ResetPlayerAnimCmd(playerid);
    SetPlayerAnimParam(playerid, 0);

    SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно добавили анимацию в избранные.");
    Dialog_Show(playerid, Dialog:ANIM_FAVORITES);
    return 1;
}

// ANIM_GREET
DialogCreate:ANIM_GREET(playerid, params[])
{
    new targetid = strval(params);

    format:g_string(#cPROJECT "%s" #cWHITE " хочет с Вами поздароваться.\n\
		Вы принимаете его предложение?",
		GetPlayerCurrentName(playerid)
	);
	
	Dialog_Open(targetid, Dialog:ANIM_GREET, DIALOG_STYLE_MSGBOX, "Предложение", 
		g_string,
		"Да", "Нет"
	);

    return 1;
}

DialogResponse:ANIM_GREET(playerid, response, listitem, inputtext[])
{
    if (response)
    {
        new targetid = GetPlayerGreetTargetID(playerid),
            anim;
        
        if (!IsPlayerLoggedForCMD(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid))
        {
            SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
            return 1;
        }
        
        if (IsPlayerInAnyVehicle(playerid))
        {
            SendClientMessage(playerid, C_WHITE, !ERROR_IN_VEHICLE);
            return 1;
        }
        
        ClearAnimationsEx(playerid);
        ClearAnimationsEx(targetid);
        
        SetPlayerFacePlayer(playerid, targetid);
        SetPlayerFacePlayer(targetid, playerid);
        
        anim = GetCharacterSettings(playerid, SET_GREETINGS);
        
        ApplyAnimation(
            playerid, 
            character_greetings_anim[anim][c_lib], 
            character_greetings_anim[anim][c_name], 
            4.0, 
            false, 
            0, 
            0, 
            0, 
            0, 
            0
        );
        
        anim = GetCharacterSettings(targetid, SET_GREETINGS);
        
        ApplyAnimation(
            targetid, 
            character_greetings_anim[anim][c_lib], 
            character_greetings_anim[anim][c_name], 
            4.0, 
            false, 
            0, 
            0, 
            0, 
            0, 
            0
        );
        
        format:g_small_string("Приветствует %s", GetPlayerCurrentName(targetid));
        SendRPMessage(ACTION_AME, playerid, g_small_string);
        
        format:g_small_string("Приветствует %s", GetPlayerCurrentName(playerid));
        SendRPMessage(ACTION_AME, targetid, g_small_string);
    }
    
    SetPlayerGreetTargetID(playerid, INVALID_PLAYER_ID);

    return 1;
}


/**
    Other functions
*/

stock ApplyAnimationEx(playerid, animlib[], animname[], Float: fDelta, loop, lockx, locky, freeze, time, forcesync = 0, bool: no_skip = false)
{
	if (GetCharacterDeath(playerid) != TYPE_DEATH_NONE || HasPlayerAnimNoSkip(playerid))
	{
		return;
	}

	if (no_skip)
	{
        TogglePlayerAnimNoSkip(playerid, true);
	}
	
	TogglePlayerAnimStates(playerid, true);
	ApplyAnimation(playerid, animlib, animname, fDelta, loop, lockx, locky, freeze, time, forcesync);
}

stock ClearAnimationsEx(playerid)
{
	TogglePlayerAnimNoSkip(playerid, false);
	TogglePlayerAnimStates(playerid, false);

	ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0);
}

static stock PreloadAnimationLibs(playerid)
{
    for (new i; i < sizeof anim_libs; i++)
    {
        ApplyAnimation(playerid, anim_libs[i], "null", 0.0, 0, 0, 0, 0, 0);
    }
}

static stock IsAnimationCmdValid(const cmd[], const param)
{
    // Exclude commands with PID's param
    static const exclude_cmd[] = {"greet"};
    
	for (new i; i < sizeof(anim_list); i++)
	{
        if (strcmp(cmd, anim_list[i][an_cmd]) != 0)
        {
            continue;
        }

        if (anim_list[i][an_cmd_param_allowed] != 0 && !(1 <= param <= anim_list[i][an_cmd_param_allowed]))
        {
            return false;
        }

        for (new j; j < sizeof(exclude_cmd); j++)
        {
            if (strcmp(cmd, exclude_cmd[j]))
            {
                return true;
            }
        }

        break;
	}
	
	return false;
}

static stock IsPlayerAnimationExist(playerid, const cmd[], cmd_param = 0)
{
    new cmd_string[MAX_ANIM_CMD],
        cmd_data_string[MAX_ANIM_CMD];

    for (new i; i < MAX_PLAYER_ANIMATION; i++)
    {
        format:cmd_string("%s%s%d",
            cmd,
            cmd_param == 0 ? "" : " ",
            cmd_param
        );

        format:cmd_data_string("%s%s%d",
            player_anim_data[playerid][i][an_cmd],
            player_anim_data[playerid][i][an_cmd_param] == 0 ? "" : " ",
            player_anim_data[playerid][i][an_cmd_param]
        );

        if (!strcmp(cmd_string, cmd_data_string, true))
        {
            return true;
        }
    }

    return false;
}

/**
    Commands
*/

CMD:an(playerid, params[])
{
	new param = strval(params);
	
	if (!(1 <= param <= MAX_PLAYER_ANIMATION))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /an [индекс избранной анимации]");
		return 1;
	}
	
	param--;
	
	if (isnull(player_anim_data[playerid][param][an_cmd]))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " За данным индексом не закреплена анимация.");
		return 1;
	}
	
	clean:<g_small_string>;
	format:g_small_string("cmd_%s", player_anim_data[playerid][param][an_cmd]);
	if (player_anim_data[playerid][param][an_cmd_param] != 0)
	{
		clean:<g_string>;
		valstr(g_string, player_anim_data[playerid][param][an_cmd_param]);
		CallLocalFunction(g_small_string, "is", playerid, g_string);
	}
	else 
	{
		CallLocalFunction(g_small_string, "i", playerid);
	}
	
	return 1;
}

CMD:fa(playerid)
{
    TogglePlayerAnimFavoriteClose(playerid, true);
    Dialog_Show(playerid, Dialog:ANIM_FAVORITES);
	return 1;
}

CMD:anim(playerid)
{
	Dialog_Open(playerid, Dialog:ANIM, DIALOG_STYLE_TABLIST, "Анимации", 
		" Список всех анимаций\t\n \
		  Избранные анимации\t" #cGRAY "/fa",
		"Далее", "Закрыть"
	);

	return 1;
}

CMD:walk(playerid) 
{
	if (GetCharacterDeath(playerid) != TYPE_DEATH_NONE)
	{
		return 1;
	}
	
	if (IsPlayerInAnyVehicle(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR" Вы не можете использовать данную команду в транспорте.");
		return 1;
	}
	
	if (HasPlayerAnimWalkActive(playerid)) 
	{
		TogglePlayerAnimWalkActive(playerid, false);
		ClearAnimationsEx(playerid);
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно выключили автоматическую походку.");
	}
	else 
	{
		TogglePlayerAnimWalkActive(playerid, true);
 	   	ApplyAnimationEx(playerid, "PED", character_walk_anim[GetCharacterSettings(playerid, SET_WALK)], 6.0, 1, 1, 1, 1, 1);
		SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно включили автоматическую походку.");
	}
	
	return 1;
}

CMD:greet(playerid, params[])
{
	if (GetCharacterDeath(playerid) != TYPE_DEATH_NONE)
	{
		return 1;
	}
	
	new targetid;
		
	if (sscanf(params, "u", targetid))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /greet [ID игрока]");
		return 1;
	}
	
	if (!IsPlayerLoggedForCMD(targetid) || !IsPlayerAroundOfPlayer(playerid, targetid) || playerid == targetid)
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_INCORRECT);
		return 1;
	}
	
    SetPlayerGreetTargetID(targetid, playerid);

    clean:<g_small_string>;
    valstr(g_small_string, targetid);
	Dialog_Show(playerid, Dialog:ANIM_GREET, g_small_string);
	return 1;
}

CMD:sa(playerid) 
{
	return cmd_stopanim(playerid);
}

CMD:stopanim(playerid) 
{
	if (GetCharacterDeath(playerid) != TYPE_DEATH_NONE || HasPlayerAnimResetDisable(playerid))
	{
		return 1;
	}
	
	ClearAnimationsEx(playerid);
	return 1;
}

CMD:handsup(playerid) 
{
	ApplyAnimationEx(playerid, "ROB_BANK", "SHP_HandsUp_Scr", 4.0, 0, 1, 1, 1, 0);
	return 1;
}

CMD:sit(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "SEAT_down",4.0,0,0,1,1,0);
	return 1;
}

CMD:aim(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "gang_gunstand",3.0,0,1,1,1,0);
	return 1;
}

CMD:cellin(playerid) 
{	
	if (GetCharacterDeath(playerid) != TYPE_DEATH_NONE)
	{
		return 1;
	}
	
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_USECELLPHONE);
	return 1;
}

CMD:cellout(playerid) 
{
	if (GetCharacterDeath(playerid) != TYPE_DEATH_NONE)
	{
		return 1;
	}
	
	SetPlayerSpecialAction(playerid, SPECIAL_ACTION_STOPUSECELLPHONE);
	return 1;
}

CMD:drunk(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "WALK_DRUNK", 4.1, 1, 1, 1, 1, 1);
	return 1;
}

CMD:bomb(playerid) 
{
	ApplyAnimationEx(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:bar(playerid) 
{
	ApplyAnimationEx(playerid, "BAR", "Barserve_bottle", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:stoptaxi(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "IDLE_taxi", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:getarrested(playerid) 
{
	ApplyAnimationEx(playerid, "ped", "ARRESTgun", 4.0, 0, 1, 1, 1, -1);
	return 1;
}

CMD:laugh(playerid) 
{
	ApplyAnimationEx(playerid, "RAPPING", "Laugh_01", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:crossarms(playerid) 
{
	ApplyAnimationEx(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, 0, 1, 1, 1, -1);
	return 1;
}

CMD:hide(playerid) 
{
	ApplyAnimationEx(playerid, "ped", "cower", 3.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:vomit(playerid) 
{
	ApplyAnimationEx(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:eat(playerid) 
{
	ApplyAnimationEx(playerid, "FOOD", "EAT_Burger", 4.1,1,1,1,1,1);
	return 1;
}

CMD:sipdrink(playerid) 
{
	ApplyAnimationEx(playerid, "GANGS", "drnkbr_prtl", 4.1,1,1,1,1,1);
	return 1;
}

CMD:slapass(playerid) 
{
	ApplyAnimationEx(playerid, "SWEET", "sweet_ass_slap", 4.0, 0, 0, 0, 0, 0);
	return 1;
}

CMD:chat(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "IDLE_CHAT",4.0,1,0,0,1,1);
	return 1;
}

CMD:fucku(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "fucku",4.0,0,0,0,0,0);
	return 1;
}

CMD:taichi(playerid) 
{
	ApplyAnimationEx(playerid, "PARK", "Tai_Chi_Loop",4.0,1,0,0,0,0);
	return 1;
}

CMD:injured(playerid) 
{
	ApplyAnimationEx(playerid, "SWEET", "Sweet_injuredloop", 4.0,0,0,1,1,0);
	return 1;
}

CMD:no(playerid) 
{
	ApplyAnimationEx(playerid, "GANGS", "Invite_No",4.0,0,0,0,0,0);
	return 1;
}

CMD:yes(playerid) 
{
	ApplyAnimationEx(playerid, "GANGS", "Invite_Yes",4.0,0,0,0,0,0);
	return 1;
}

CMD:crawl(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "CAR_crawloutRHS",4.0,0,0,0,0,0);
	return 1;
}

CMD:push(playerid) 
{
	ApplyAnimationEx(playerid, "GANGS", "shake_cara",4.0,0,0,0,0,0);
	return 1;
}

CMD:akick(playerid) 
{
	ApplyAnimationEx(playerid, "POLICE", "Door_Kick",4.0,0,0,0,0,0);
	return 1;
}

CMD:facepalm(playerid) 
{
	ApplyAnimationEx(playerid, "MISC", "plyr_shkhead",4.0,0,0,0,0,0);
	return 1;
}

CMD:balls(playerid) 
{
	ApplyAnimationEx(playerid, "MISC", "scratchballs_01",4.0,0,0,0,0,0);
	return 1;
}

CMD:lowbodypush(playerid) 
{
	ApplyAnimationEx(playerid, "GANGS", "shake_carSH",4.0,0,0,0,0,0);
	return 1;
}

CMD:aspray(playerid) 
{
	ApplyAnimationEx(playerid, "SPRAYCAN", "spraycan_full",4.0,0,0,0,0,0);
	return 1;
}

CMD:medic(playerid) 
{
	ApplyAnimationEx(playerid, "MEDIC", "CPR",4.0,0,0,0,0,0);
	return 1;
}

CMD:koface(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "KO_shot_face",4.0,0,1,1,1,0);
	return 1;
}

CMD:kostomach(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "KO_shot_stom",4.0,0,1,1,1,0);
	return 1;
}

CMD:lifejump(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "EV_dive",4.0,0,1,1,1,0);
	return 1;
}

CMD:rollfall(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "BIKE_fallR",4.0,0,1,1,1,0);
	return 1;
}

CMD:hoodfrisked(playerid) 
{
	ApplyAnimationEx(playerid, "POLICE", "crm_drgbst_01",1.0,0,1,1,1,0);
	return 1;
}

CMD:flip(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "KD_left",4.1,0,1,1,1,0);
	return 1;
}

CMD:box(playerid) 
{
	ApplyAnimationEx(playerid, "GYMNASIUM", "GYMshadowbox",4.0,1,1,1,1,0);
	return 1;
}

CMD:finger(playerid) 
{
	ApplyAnimationEx(playerid, "RIOT", "RIOT_FUKU",2.0,0,0,0,0,0);
	return 1;
}

CMD:gpunch(playerid) 
{
	ApplyAnimationEx(playerid, "FIGHT_B", "FightB_G",4.0,0,0,0,0,0);
	return 1;
}

CMD:gkick(playerid) 
{
	ApplyAnimationEx(playerid, "FIGHT_D", "FightD_G",4.0,0,0,0,0,0);
	return 1;
}

CMD:lowthrow(playerid) 
{
	ApplyAnimationEx(playerid, "GRENADE", "WEAPON_throwu",3.0,0,0,0,0,0);
	return 1;
}

CMD:riot(playerid) 
{
	ApplyAnimationEx(playerid, "RIOT", "RIOT_ANGRY",4.0,0,0,0,0,0);
	return 1;
}

CMD:abp(playerid) 
{
	ApplyAnimationEx(playerid, "benchpress", "gym_bp_celebrate",4.0,0,0,0,0,0);
	return 1;
}

CMD:cry(playerid) 
{
	ApplyAnimationEx(playerid, "GRAVEYARD", "mrnF_loop",4.0,1,0,0,0,0);
	return 1;
}

CMD:gro(playerid) 
{
	ApplyAnimationEx(playerid, "BEACH", "ParkSit_M_loop", 4.0, 1, 0, 0, 0, 0);
	return 1;
}

CMD:seat(playerid) 
{
	ApplyAnimationEx(playerid, "INT_HOUSE", "LOU_In",4.0,0,0,1,1,0);
	return 1;
}

CMD:tatto(playerid) 
{
	ApplyAnimationEx(playerid, "TATTOOS", "TAT_ArmR_Pose_P", 4.1, 0, 1, 1, 1, 0);
	return 1;
}

CMD:caim(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "IDLE_ROCKET",4.1,0,1,1,1,1);
	return 1;
}

CMD:creep(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "Player_Sneak",4.1,1,1,1,1,1);
	return 1;
}

CMD:sroll(playerid) 
{
	ApplyAnimationEx(playerid, "SWAT", "JMP_Wall1m_180",4.1,0,1,1,1,0);
	return 1;
}

CMD:gesture(playerid) 
{
	ApplyAnimationEx(playerid, "SWAT", "swt_lkt",4.0,0,0,0,0,0);
	return 1;
}

CMD:agreement(playerid) 
{
	ApplyAnimationEx(playerid, "COP_AMBIENT", "Coplook_think",4.0,1,0,0,0,0);
	return 1;
}

CMD:bend(playerid) 
{
	ApplyAnimationEx(playerid, "BAR", "Barserve_order",4.0,0,0,0,0,0);
	return 1;
}

CMD:rod(playerid) 
{
	ApplyAnimationEx(playerid, "benchpress", "gym_bp_up_A",4.0,0,0,1,1,0);
	return 1;
}

CMD:tgro(playerid) 
{
	ApplyAnimationEx(playerid, "CAMERA", "camcrch_cmon",4.0,0,0,1,1,0);
	return 1;
}

CMD:cmouth(playerid) 
{
	ApplyAnimationEx(playerid, "ON_LOOKERS", "panic_in",4.0,0,0,1,1,0);
	return 1;
}

CMD:gog(playerid) 
{
	ApplyAnimationEx(playerid, "goggles", "goggles_put_on",4.1,0,1,1,1,1);
	return 1;
}

CMD:nfall(playerid) 
{
	ApplyAnimationEx(playerid, "HEIST9", "CAS_G2_GasKO",4.1,0,1,1,1,0);
	return 1;
}

CMD:hsit(playerid) 
{
	ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Bored_Loop",4.0,1,0,1,1,0);
	return 1;
}

CMD:csit(playerid) 
{
	ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Type_Loop",4.0,1,0,1,1,0);
	return 1;
}

CMD:bracing(playerid) 
{
	ApplyAnimationEx(playerid, "PLAYIDLES", "stretch",4.0,0,0,0,0,0);
	return 1;
}

CMD:pool(playerid) 
{
	ApplyAnimationEx(playerid, "POOL", "POOL_Long_Start",4.1,0,1,1,1,0);
	return 1;
}

CMD:ssearch(playerid) 
{
	ApplyAnimationEx(playerid, "ROB_BANK", "CAT_Safe_Rob",4.0,1,0,0,0,0);
	return 1;
}

CMD:daim(playerid) 
{
	ApplyAnimationEx(playerid, "RYDER", "Van_Stand_Crate",3.0,0,1,1,1,0);
	return 1;
}

CMD:rhandl(playerid) 
{
	ApplyAnimationEx(playerid, "SCRATCHING", "scdlulp",4.0,0,0,1,1,0);
	return 1;
}

CMD:rhandr(playerid) 
{
	ApplyAnimationEx(playerid, "SCRATCHING", "scdrulp",4.0,0,0,1,1,0);
	return 1;
}

CMD:hstand(playerid) 
{
	ApplyAnimationEx(playerid, "SCRATCHING", "scdrdlp",4.0,0,0,1,1,0);
	return 1;
}

CMD:nlean(playerid) 
{
	ApplyAnimationEx(playerid, "SHAMAL", "SHAMAL_align",4.1,0,1,1,1,0);
	return 1;
}

CMD:shelter(playerid) 
{
	ApplyAnimationEx(playerid, "SHOP", "SHP_Duck_Fire",4.0,0,0,1,1,0);
	return 1;
}

CMD:lookback(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "flee_lkaround_01",4.0,0,0,0,0,0);
	return 1;
}

CMD:wsit(playerid) 
{
	ApplyAnimationEx(playerid, "SHOP", "SHP_Gun_Duck",4.0,0,0,1,1,0);
	return 1;
}

CMD:hangon(playerid) 
{
	ApplyAnimationEx(playerid, "TRAIN", "tran_ouch",4.0,0,0,1,1,0);
	return 1;
}

CMD:blowj(playerid)
{
	ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_START_W", 4.1, 0, 1, 1, 1, 0);
	return 1;
}

CMD:rseat(playerid) 
{
	ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_START_P", 4.1, 0, 1, 1, 1, 0);
	return 1;
}

CMD:polwalk(playerid) 
{
	ApplyAnimationEx(playerid, "POLICE", "Cop_move_FWD",3.0,1,1,1,1,1);
	return 1;
}

CMD:nflip(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "BIKE_fall_off",4.1,0,1,1,1,0);
	return 1;
}

CMD:csdead(playerid) 
{
	ApplyAnimationEx(playerid, "WUZI", "CS_Dead_Guy",4.1,0,1,1,1,0);
	return 1;
}

CMD:follow(playerid) 
{
	ApplyAnimationEx(playerid, "WUZI", "Wuzi_follow",4.1,0,1,1,1,1);
	return 1;
}

CMD:grnd(playerid) 
{
	ApplyAnimationEx(playerid, "WUZI", "Wuzi_grnd_chk",4.0,0,0,0,0,0);
	return 1;
}

CMD:copa(playerid) 
{
	ApplyAnimationEx(playerid, "COP_AMBIENT", "Copbrowse_in",4.1,0,1,1,1,0);
	return 1;
}

CMD:cmon(playerid) 
{
	ApplyAnimationEx(playerid, "OTB", "wtchrace_cmon",4.1,0,1,1,1,0);
	return 1;
}

CMD:lose(playerid) 
{
	ApplyAnimationEx(playerid, "OTB", "wtchrace_lose",4.1,0,1,1,1,0);
	return 1;
}

CMD:win(playerid) 
{
	ApplyAnimationEx(playerid, "OTB", "wtchrace_win",4.1,0,1,1,1,0);
	return 1;
}

CMD:gunthreat(playerid) 
{
	ApplyAnimationEx(playerid, "SHOP", "SHP_Gun_Threat",4.1,0,1,1,1,0);
	return 1;
}

CMD:givecash(playerid) 
{
	ApplyAnimationEx(playerid, "SHOP", "SHP_Rob_GiveCash",4.1,0,1,1,1,0);
	return 1;
}

CMD:robr(playerid) 
{
	ApplyAnimationEx(playerid, "SHOP", "SHP_Rob_React",4.1,0,1,1,1,0);
	return 1;
}

CMD:serend(playerid) 
{
	ApplyAnimationEx(playerid, "SHOP", "SHP_Serve_End",4.1,0,1,1,1,0);
	return 1;
}

CMD:heist(playerid) 
{
	ApplyAnimationEx(playerid, "HEIST9", "Use_SwipeCard",4.0,0,0,0,0,0);
	return 1;
}

CMD:frontfall(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "FLOOR_hit_f",4.1,0,1,1,1,0);
	return 1;
}

CMD:pants(playerid) 
{
	ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_END_P",4.0,0,0,0,0,0);
	return 1;
}

CMD:tired(playerid) 
{
	ApplyAnimationEx(playerid, "FAT", "IDLE_tired",4.0,0,0,1,1,0);
	return 1;
}

CMD:climb(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "CLIMB_jump",4.0,0,0,1,1,0);
	return 1;
}

CMD:tlean(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "DRIVE_BOAT",4.0,0,0,1,1,0);
	return 1;
}

CMD:pushup(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "getup_front", 4.0, 0, 0, 1, 1, 0);
	return 1;
}

CMD:protection(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "FightShB",4.0,0,1,1,1,1);
	return 1;
}

CMD:swallow(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "gum_eat",4.0,0,0,0,0,0);
	return 1;
}

CMD:stand(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "IDLE_HBHB",3.0,0,1,1,1,0);
	return 1;
}

CMD:pullhand(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "Jetpack_Idle",3.0,0,1,1,1,0);
	return 1;
}

CMD:nlook(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "roadcross_gang",4.0,0,0,0,0,0);
	return 1;
}

CMD:extend(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "Shove_Partial",4.1,0,1,1,1,1);
	return 1;
}

CMD:stopit(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "Walk_DoorPartial",4.0,0,0,0,0,0);
	return 1;
}

CMD:ksit(playerid) 
{
	ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Crash",4.0,1,0,1,1,0);
	return 1;
}

CMD:esit(playerid) 
{
	ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Drink",4.0,1,0,1,1,0);
	return 1;
}

CMD:tsit(playerid) 
{
	
	ApplyAnimationEx(playerid, "INT_OFFICE", "OFF_Sit_Watch",4.0,0,0,1,1,0);
	return 1;
}

CMD:rtake(playerid) 
{
	
	ApplyAnimationEx(playerid, "BAR", "Barserve_give",4.0,0,0,0,0,0);
	return 1;
}

CMD:forwardlook(playerid) 
{
	
	ApplyAnimationEx(playerid, "BD_FIRE", "BD_Panic_02",4.1,0,1,1,1,0);
	return 1;
}

CMD:wforwardlook(playerid) 
{
	ApplyAnimationEx(playerid, "BD_FIRE", "BD_Panic_03",4.1,0,1,1,1,0);
	return 1;
}

CMD:taction(playerid) 
{
	ApplyAnimationEx(playerid, "BD_FIRE", "wash_up",4.0,0,0,0,0,0);
	return 1;
}

CMD:catch(playerid) 
{
	ApplyAnimationEx(playerid, "MD_CHASE", "MD_HANG_Loop",4.1,0,1,1,1,0);
	return 1;
}

CMD:despair(playerid) 
{
	ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_react_miss",4.0,0,0,0,0,0);
	return 1;
}

CMD:rooting(playerid) 
{
	ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_react_score",4.1,1,1,1,1,0);
	return 1;
}

CMD:spyglass(playerid) 
{
	ApplyAnimationEx(playerid, "CAMERA", "picstnd_take",4.1,0,1,1,1,0);
	return 1;
}

CMD:looksky(playerid) 
{
	
	ApplyAnimationEx(playerid, "ON_LOOKERS", "lkup_loop",4.1,0,1,1,1,0);
	return 1;
}

CMD:mshow(playerid) 
{
	ApplyAnimationEx(playerid, "ON_LOOKERS", "panic_point",4.1,0,1,1,1,0);
	return 1;
}

CMD:wshow(playerid) 
{
	ApplyAnimationEx(playerid, "ON_LOOKERS", "panic_shout",4.1,0,1,1,1,0);
	return 1;
}

CMD:hshow(playerid) 
{
	ApplyAnimationEx(playerid, "ON_LOOKERS", "point_loop",4.1,0,1,1,1,0);
	return 1;
}

CMD:sh(playerid) 
{
	ApplyAnimationEx(playerid, "ON_LOOKERS", "shout_in",4.0,0,0,0,0,0);
	return 1;
}

CMD:crossfingers(playerid) 
{
	ApplyAnimationEx(playerid, "CASINO", "cards_loop",4.1,0,1,1,1,0);
	return 1;
}

CMD:delight(playerid) 
{
	ApplyAnimationEx(playerid, "CASINO", "manwinb",4.0,0,0,0,0,0);
	return 1;
}

CMD:hdelight(playerid) 
{
	ApplyAnimationEx(playerid, "CASINO", "manwind",4.0,0,0,0,0,0);
	return 1;
}

CMD:showtable(playerid) 
{
	ApplyAnimationEx(playerid, "CASINO", "Roulette_bet",4.1,0,1,1,1,0);
	return 1;
}

CMD:tfacepalm(playerid) 
{
	ApplyAnimationEx(playerid, "CASINO", "Roulette_lose",4.1,0,1,1,1,0);
	return 1;
}

CMD:tpull(playerid) 
{
	ApplyAnimationEx(playerid, "CASINO", "Slot_in",4.1,0,1,1,1,0);
	return 1;
}

CMD:fail(playerid) 
{
	ApplyAnimationEx(playerid, "CASINO", "Slot_lose_out",4.0,0,0,0,0,0);
	return 1;
}

CMD:joy(playerid) 
{
	ApplyAnimationEx(playerid, "CASINO", "Slot_win_out",4.0,0,0,0,0,0);
	return 1;
}

CMD:wear(playerid) 
{
	ApplyAnimationEx(playerid, "CARRY", "crry_prtial",4.1,0,1,1,1,1);
	return 1;
}

CMD:fsit(playerid) 
{
	ApplyAnimationEx(playerid, "JST_BUISNESS", "girl_02",4.1,0,1,1,1,0);
	return 1;
}

CMD:crushjump(playerid) 
{
	ApplyAnimationEx(playerid, "DODGE", "Crush_Jump",4.1,0,1,1,1,0);
	return 1;
}

CMD:scatch(playerid) 
{
	
	ApplyAnimationEx(playerid, "FINALE", "FIN_LegsUp_Loop",4.1,0,1,1,1,0);
	return 1;
}

CMD:lookfloor(playerid) 
{
	
	ApplyAnimationEx(playerid, "FINALE", "FIN_Cop1_Loop",4.1,0,1,1,1,0);
	return 1;
}

CMD:tramplefloor(playerid) 
{
	
	ApplyAnimationEx(playerid, "FINALE", "FIN_Cop1_Stomp",4.1,1,1,1,1,0);
	return 1;
}

CMD:swing(playerid) 
{
	
	ApplyAnimationEx(playerid, "Freeweights", "gym_free_B",4.1,0,1,1,1,0);
	return 1;
}

CMD:nbp(playerid) 
{
	
	ApplyAnimationEx(playerid, "Freeweights", "gym_free_celebrate",4.0,0,0,0,0,0);
	return 1;
}

CMD:takehead(playerid) 
{
	
	ApplyAnimationEx(playerid, "HAIRCUTS", "BRB_Cut",4.1,0,1,1,1,0);
	return 1;
}

CMD:readtable(playerid) 
{
	ApplyAnimationEx(playerid, "SCRATCHING", "sclng_r",4.1,0,1,1,1,0);
	return 1;
}

CMD:squat(playerid) 
{
	ApplyAnimationEx(playerid, "TEC", "TEC_crouchfire",4.1,0,1,1,1,0);
	return 1;
}

CMD:sprawl(playerid) 
{
	ApplyAnimationEx(playerid, "TATTOOS", "TAT_Idle_Loop_T",4.1,0,1,1,1,0);
	return 1;
}

CMD:sho(playerid) 
{
	ApplyAnimationEx(playerid, "STRIP", "PUN_HOLLER",4.0,0,0,0,0,0);
	return 1;
}

CMD:faim(playerid) 
{
	ApplyAnimationEx(playerid, "SWORD", "sword_IDLE",4.1,0,1,1,1,0);
	return 1;
}

CMD:piss(playerid) 
{
	ApplyAnimationEx(playerid, "PAULNMAC", "Piss_in",4.1,0,1,1,1,0);
	return 1;
}

CMD:swingback(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "getup", 4.1, 1, 1, 1, 1, 0);
	return 1;
}

CMD:onehand(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "CLIMB_jump2fall",4.1,0,1,1,1,0);
	return 1;
}

CMD:backwalk(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "gas_cwr", 4.1, 1, 1, 1, 1, 1);
	return 1;
}

CMD:feettog(playerid) 
{
	ApplyAnimationEx(playerid, "PED", "Idlestance_fat",4.1,0,1,1,1,0);
	return 1;
}

CMD:mirro(playerid) 
{
	ApplyAnimationEx(playerid, "CLOTHES", "CLO_Pose_Hat",4.1,0,1,1,1,0);
	return 1;
}

CMD:hips(playerid) 
{
	ApplyAnimationEx(playerid, "COP_AMBIENT", "Coplook_shake",4.1,0,1,1,1,0);
	return 1;
}

CMD:pullo(playerid) 
{
	ApplyAnimationEx(playerid, "AIRPORT", "thrw_barl_thrw",4.1,0,1,1,1,0);
	return 1;
}

CMD:obalance(playerid) 
{
	ApplyAnimationEx(playerid, "BD_FIRE", "BD_Panic_02",4.1,0,1,1,1,0);
	return 1;
}

CMD:wobalance(playerid) 
{
	ApplyAnimationEx(playerid, "BD_FIRE", "BD_Panic_03",4.1,0,1,1,1,0);
	return 1;
}

CMD:dance(playerid, params[]) 
{
	if (GetCharacterDeath(playerid) != TYPE_DEATH_NONE)
	{
		return 1;
	}
	
	new dance;
	
	if (sscanf(params, "i", dance))
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /dance [1 - 12]");
		return 1;
	}
	
	switch(dance) 
	{
		case 1: 
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE1);
		}
		
		case 2: 
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE2);
		}
		
		case 3: 
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE3);
		}
		
		case 4: 
		{
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DANCE4);
		}
		
		case 5: 
		{
			ApplyAnimationEx(playerid, "DANCING", "bd_clap",4.1,1,1,1,1,1);
		}
		
		case 6: 
		{	
			ApplyAnimationEx(playerid, "DANCING", "bd_clap1",4.1,1,1,1,1,1);
		}
		
		case 7: 
		{
			ApplyAnimationEx(playerid, "DANCING", "DAN_Down_A",4.1,1,1,1,1,1);
		}
		
		case 8: 
		{
			ApplyAnimationEx(playerid, "DANCING", "DAN_Left_A",4.1,1,1,1,1,1);
		}
		
		case 9: 
		{
			ApplyAnimationEx(playerid, "DANCING", "DAN_Loop_A",4.1,1,1,1,1,1);
		}
		case 10: 
		
		{
			ApplyAnimationEx(playerid, "DANCING", "DAN_Right_A",4.1,1,1,1,1,1);
		}
		
		case 11: 
		{
			ApplyAnimationEx(playerid, "DANCING", "DAN_Up_A",4.1,1,1,1,1,1);
		}
		
		case 12: 
		{
			ApplyAnimationEx(playerid, "DANCING", "dnce_M_a",4.1,1,1,1,1,1);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /dance [1 - 12]");
		}
	}
	
	return 1;
}

CMD:repcar(playerid, params[]) 
{
	new repcar;
	
	if (sscanf(params, "i", repcar)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /repcar [1 - 2]");
		return 1;
	}
	
	switch(repcar) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "CAR", "Fixn_Car_Loop",3.0,0,1,1,1,0);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "CAR", "Fixn_Car_Out",3.0,0,1,1,1,0);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /repcar [1 - 2]");
		}
	}
	return 1;
}

CMD:hnds(playerid, params[]) 
{
	new hnds;
	
	if (sscanf(params, "i", hnds)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /hnds [1 - 7]");
		return 1;
	}
	
	switch(hnds) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "LOWRIDER", "prtial_gngtlkB",4.1,0,1,1,1,1);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "LOWRIDER", "prtial_gngtlkC",4.1,0,1,1,1,1);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "LOWRIDER", "prtial_gngtlkD",4.1,0,1,1,1,1);
		}
		
		case 4: 
		{
			ApplyAnimationEx(playerid, "LOWRIDER", "prtial_gngtlkE",4.1,0,1,1,1,1);
		}
		
		case 5: 
		{
			ApplyAnimationEx(playerid, "LOWRIDER", "prtial_gngtlkF",4.1,0,1,1,1,1);
		}
		
		case 6: 
		{
			ApplyAnimationEx(playerid, "LOWRIDER", "prtial_gngtlkG",4.1,0,1,1,1,1);
		}
		
		case 7: 
		{
			ApplyAnimationEx(playerid, "LOWRIDER", "prtial_gngtlkH",4.1,0,1,1,1,1);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /hnds [1 - 7]");
		}
	}
	
	return 1;
}

CMD:strip(playerid, params[]) 
{
	new strip;
	
	if (sscanf(params, "i", strip)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /strip [1 - 14]");
		return 1;
	}
	
	switch(strip) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "STRIP", "strip_A", 4.1, 1, 1, 1, 1, 1);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "STRIP", "strip_B", 4.1, 1, 1, 1, 1, 1);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "STRIP", "strip_C", 4.1, 1, 1, 1, 1, 1);
		}
		
		case 4: 
		{
			ApplyAnimationEx(playerid, "STRIP", "strip_D", 4.1, 1, 1, 1, 1, 1);
		}
		
		case 5: 
		{
			ApplyAnimationEx(playerid, "STRIP", "strip_E", 4.1, 1, 1, 1, 1, 1);
		}
		
		case 6: 
		{
			ApplyAnimationEx(playerid, "STRIP", "strip_F", 4.1, 1, 1, 1, 1, 1);
		}
		
		case 7: 
		{
			ApplyAnimationEx(playerid, "STRIP", "strip_G", 4.1, 1, 1, 1, 1, 1);
     	}
		
		case 8: 
		{
			ApplyAnimationEx(playerid, "STRIP", "STR_A2B",4.1,1,1,1,1,1);
       }
		
		case 9: 
		{
			ApplyAnimationEx(playerid, "STRIP", "STR_B2C",4.1,1,1,1,1,1);
       }
		
		case 10: 
		{
			ApplyAnimationEx(playerid, "STRIP", "STR_C1",4.1,1,1,1,1,1);
       }
		
		case 11: 
		{
			ApplyAnimationEx(playerid, "STRIP", "STR_C2",4.1,1,1,1,1,1);
       }
		
		case 12: 
		{
			ApplyAnimationEx(playerid, "STRIP", "STR_Loop_A",4.1,1,1,1,1,1);
       }
		
		case 13: 
		{
			ApplyAnimationEx(playerid, "STRIP", "STR_Loop_B",4.1,1,1,1,1,1);
       }
		
		case 14: 
		{
			ApplyAnimationEx(playerid, "STRIP", "STR_Loop_C",4.1,1,1,1,1,1);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /strip [1 - 14]");
		}
	}
	return 1;
}

CMD:chant(playerid, params[]) 
{
    new param;
	
	if (!sscanf(params, "d", param)) 
	{
        switch (param) 
        {
            case 1: 
            {
                ApplyAnimationEx(playerid, "RIOT", "RIOT_CHANT",4.0,1,1,1,1,0);
            }

            case 2:
            {
                ApplyAnimationEx(playerid, "STRIP", "PUN_CASH",4.0,0,0,0,0,0);
            }
        }

        return 1;
    }

    SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /chant [1 - 2]");
	return 1;
}

CMD:throwmoney(playerid)
{
    return cmd_chant(playerid, "2");
}

CMD:deal(playerid, params[]) 
{
	new deal;
	
	if (sscanf(params, "i", deal)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /deal [1 - 3]");
		return 1;
	}
	
	switch (deal) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "DEALER", "DEALER_DEAL", 4.0, 0, 0, 0, 0, 0);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "DEALER", "DEALER_IDLE", 3.0,0,1,1,1,0);
		}
		case 3: 
		{
			ApplyAnimationEx(playerid, "GRAVEYARD", "mrnM_loop",3.0,0,1,1,1,0);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT "Введите: /deal [1 - 3]");
		}
	}
	
	return 1;
}

CMD:smoke(playerid, params[]) 
{
	new smoke;
	
	if (sscanf(params, "i", smoke)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /smoke [1 - 6]");
		return 1;
	}
	
	switch(smoke) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "SMOKING", "M_smklean_loop", 4.0, 1, 0, 0, 0, 0);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "SMOKING", "F_smklean_loop", 4.0, 1, 0, 0, 0, 0);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "SMOKING", "M_smkstnd_loop", 4.0, 1, 0, 0, 0, 0);
		}
		
		case 4: 
		{
			ApplyAnimationEx(playerid, "SMOKING", "M_smk_out", 4.0, 0, 0, 0, 0, 0);
		}
		
		case 5: 
		{
			ApplyAnimationEx(playerid, "SMOKING", "M_smk_in",3.0,0,0,0,0,0);
		}
		
		case 6: 
		{
			ApplyAnimationEx(playerid, "SMOKING", "M_smk_tap",3.0,0,0,0,0,0);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /smoke [1 - 6]");
		}
	}
	
	return 1;
}

CMD:rap(playerid, params[]) 
{
	new rap;
	
	if (sscanf(params, "i", rap)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /rap [1 - 9]");
		return 1;
	}
	
	switch(rap) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "RAPPING", "RAP_A_Loop",4.0,1,0,0,0,0);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "RAPPING", "RAP_C_Loop",4.0,1,0,0,0,0);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "GANGS", "prtial_gngtlkD",4.0,1,0,0,1,1);
		}
		
		case 4: 
		{
			ApplyAnimationEx(playerid, "GANGS", "prtial_gngtlkH",4.0,1,0,0,1,1);
		}
		
		case 5: 
		{
			ApplyAnimationEx(playerid, "GANGS", "prtial_gngtlkF",4.0,1,0,0,1,1);
		}
		
		case 6: 
		{
			ApplyAnimationEx(playerid, "GANGS", "prtial_gngtlkG",4.0,1,0,0,1,1);
		}
		
		case 7: 
		{
			ApplyAnimationEx(playerid, "PED", "ATM",4.0,0,0,0,0,0);
		}
		
		case 8: 
		{
			ApplyAnimationEx(playerid, "RAPPING", "RAP_B_IN",3.0,0,1,1,1,0);
		}
		
		case 9: 
		{
			ApplyAnimationEx(playerid, "GYMNASIUM", "gym_tread_celebrate",4.1,0,1,1,1,0);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /rap [1 - 9]");
		}
	}
	return 1;
}

CMD:bat(playerid, params[]) 
{
	new bat;
	
	if (sscanf(params, "i", bat)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /bat [1 - 2]");
		return 1;
	}
	
	switch(bat) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "CRACK", "Bbalbat_Idle_02",4.0, 1, 0, 0, 0, 0);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "CRACK", "Bbalbat_Idle_01",4.0, 1, 0, 0, 0, 0);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /bat [1 - 2]");
		}
	}
	
	return 1;
}

CMD:basket(playerid, params[]) 
{
	new basket;
	
	if (sscanf(params, "i", basket)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /basket [1 - 6]");
		return 1;
	}
	
	switch(basket) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_idleloop",4.0,1,0,0,0,0);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Jump_Shot",4.0,0,0,0,0,0);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_pickup",4.0,0,0,0,0,0);
		}
		
		case 4: 
		{
			ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_run",4.1,1,1,1,1,1);
		}
		
		case 5: 
		{
			ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_def_loop",4.0,1,0,0,0,0);
		}
		
		case 6: 
		{
			ApplyAnimationEx(playerid, "BSKTBALL", "BBALL_Dnk",4.0,0,0,0,0,0);
		}
		
		default:
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /basket [1 - 6]");
		}
	}
	
	return 1;
}

CMD:lean(playerid, params[]) 
{
	new lean;
	
	if (sscanf(params, "i", lean)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /lean [1 - 3]");
		return 1;
	}
	
	switch(lean) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "GANGS", "leanIDLE",4.0,0,0,1,1,0);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "MISC", "Plyrlean_loop",4.0,0,1,1,1,0);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "CAR_CHAT", "car_talkm_loop",4.0,0,1,1,1,0);
		}
		
		default:
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /lean [1 - 3]");
		}
	}
	
	return 1;
}

CMD:lay(playerid, params[]) 
{
	new lay;
	
	if (sscanf(params, "i", lay)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /lay [1 - 5]");
		return 1;
	}
	
	switch(lay) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "BEACH", "bather", 4.0, 1, 0, 0, 0, 0);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "SUNBATHE", "Lay_Bac_in",3.0,0,1,1,1,0);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "BEACH", "ParkSit_W_loop",3.0,0,1,1,1,0);
		}
		
		case 4: 
		{
			ApplyAnimationEx(playerid, "BEACH", "SitnWait_loop_W",4.0, 1, 0, 0, 0, 0);
		}
		
		case 5: 
		{
			ApplyAnimationEx(playerid, "SUNBATHE", "SBATHE_F_LieB2Sit",3.0,0,1,1,1,0);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /lay [1 - 5]");
		}
	}
	
	return 1;
}

CMD:gsign(playerid, params[]) 
{
	new gsign;
	
	if (sscanf(params, "i", gsign)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /gsign [1 - 10]");
		return 1;
	}
	
	switch(gsign) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "GHANDS", "gsign1",4.1,0,1,1,1,1);
		}
		case 2: 
		{
			ApplyAnimationEx(playerid, "GHANDS", "gsign1LH",4.1,0,1,1,1,1);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "GHANDS", "gsign2",4.1,0,1,1,1,1);
		}
		
		case 4: 
		{
			ApplyAnimationEx(playerid, "GHANDS", "gsign2LH",4.1,0,1,1,1,1);
		}
		
		case 5: 
		{
			ApplyAnimationEx(playerid, "GHANDS", "gsign3",4.1,0,1,1,1,1);
		}
		
		case 6: 
		{
			ApplyAnimationEx(playerid, "GHANDS", "gsign3LH",4.1,0,1,1,1,1);
		}
		
		case 7: 
		{
			ApplyAnimationEx(playerid, "GHANDS", "gsign4",4.1,0,1,1,1,1);
		}
		
		case 8: 
		{
			ApplyAnimationEx(playerid, "GHANDS", "gsign4LH",4.1,0,1,1,1,1);
		}
		
		case 9: 
		{
			ApplyAnimationEx(playerid, "GHANDS", "gsign5",4.1,0,1,1,1,1);
		}
		
		case 10: 
		{
			ApplyAnimationEx(playerid, "GHANDS", "gsign5LH",4.1,0,1,1,1,1);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /gsign [1 - 10]");
		}
	}
	
	return 1;
}

CMD:wave(playerid, params[]) 
{
	new wave;
	
	if (sscanf(params, "i", wave)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /wave [1 - 4]");
		return 1;
	}
	
	switch(wave) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "KISSING", "gfwave2", 4.1,0,1,1,0,0);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "ON_LOOKERS", "wave_loop", 4.1,1,1,1,0,0);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "CAMERA", "camstnd_cmon",4.0,0,0,0,0,0);
		}
		
		case 4: 
		{
			ApplyAnimationEx(playerid, "PED", "endchat_01",4.1,0,1,1,0,0);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /wave [1 - 4]");
		}
	}
	
	return 1;
}

CMD:police(playerid, params[]) 
{
	new police;
	
	if (sscanf(params, "i", police)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /police [1 - 4]");
		return 1;
	}
	
	switch(police) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "POLICE", "CopTraf_Away",3.0,1,0,0,1,0);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "POLICE", "CopTraf_Come",3.0,1,0,0,1,0);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "POLICE", "CopTraf_Left",3.0,1,0,0,1,0);
		}
		
		case 4: 
		{
			ApplyAnimationEx(playerid, "POLICE", "CopTraf_Stop",3.0,1,0,0,1,0);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /police [1 - 4]");
		}
	}
	return 1;
}

CMD:crack(playerid, params[]) 
{
	new crack;
	
	if (sscanf(params, "i", crack)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /crack [1 - 7]");
		return 1;
	}
	
	switch(crack) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "CRACK", "crckdeth2",3.0,1,1,1,1,0);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "CRACK", "crckdeth4",3.0,0,1,1,1,0);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "CRACK", "crckidle1",3.0,0,1,1,1,0);
		}
		
		case 4: 
		{
			ApplyAnimationEx(playerid, "CRACK", "crckidle2",3.0,0,1,1,1,0);
		}
		
		case 5: 
		{
			ApplyAnimationEx(playerid, "CRACK", "crckidle3",3.0,0,1,1,1,0);
		}
		
		case 6: 
		{
			ApplyAnimationEx(playerid, "CRACK", "crckdeth1",3.0,0,1,1,1,0);
		}
		
		case 7: 
		{
			ApplyAnimationEx(playerid, "CRACK", "crckdeth3",3.0,0,1,1,1,0);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /crack [1 - 7]");
		}
	}
	
	return 1;
}

CMD:car(playerid, params[]) 
{
	new car;
	
	if (sscanf(params, "i", car)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /car [1 - 11]");
		return 1;
	}
	
	switch(car) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_bdbnce", 4.1, 0, 1, 1, 1, 0, 1);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_hair", 4.1, 0, 1, 1, 1, 0, 1);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_idle_to_l0", 4.1, 0, 1, 1, 1, 0, 1);
		}
		
		case 4: 
		{
			ApplyAnimationEx(playerid, "PED", "Tap_hand", 4.1, 0, 1, 1, 1, 0, 1);
		}
		
		case 5: 
		{
			ApplyAnimationEx(playerid, "PED", "Tap_handP", 4.1, 0, 1, 1, 1, 0, 1);
		}
		
		case 6: 
		{
			ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l12_to_l0", 4.1, 0, 1, 1, 1, 0, 1);
		}
		
		case 7: 
		{
			ApplyAnimationEx(playerid, "LOWRIDER", "lrgirl_l2_to_l3", 4.1, 0, 1, 1, 1, 0, 1);
		}
		
		case 8: 
		{
			ApplyAnimationEx(playerid, "PED", "CAR_LB", 4.1, 0, 1, 1, 1, 0, 1);
		}
		
		case 9: 
		{
			ApplyAnimationEx(playerid, "PED", "CAR_sitp", 4.1, 0, 1, 1, 1, 0, 1);
		}
		
		case 10: 
		{
			ApplyAnimationEx(playerid, "PED", "CAR_sitpLO", 4.1, 0, 1, 1, 1, 0, 1);
		}
		
		case 11: 
		{
			ApplyAnimationEx(playerid, "CAR_CHAT", "carfone_loopA", 4.1, 1, 1, 1, 1, 0, 1);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /car [1 - 11]");
		}
	}
	
	return 1;
}

CMD:wallow(playerid, params[]) 
{
	new wallow;
	
	if (sscanf(params, "i", wallow)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /wallow [1 - 2]");
		return 1;
	}
	
	switch(wallow) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "MD_CHASE", "MD_BIKE_Lnd_Roll",4.1,0,1,1,1,0);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "MD_CHASE", "MD_BIKE_Lnd_Roll_F",4.1,0,1,1,1,0);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /wallow [1 - 2]");
		}
	}
	
	return 1;
}

CMD:beckon(playerid, params[]) 
{
	
	new beckon;
	
	if (sscanf(params, "i", beckon)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /beckon [1 - 3]");
		return 1;
	}
	
	switch(beckon) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "RYDER", "RYD_Beckon_01",4.1,0,1,1,1,1);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "RYDER", "RYD_Beckon_02",4.1,0,1,1,1,1);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "RYDER", "RYD_Beckon_03",4.1,0,1,1,1,1);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /beckon [1 - 3]");
		}
	}
	
	return 1;
}

CMD:shotgun(playerid, params[]) 
{
	
	new shotgun;
	
	if (sscanf(params, "i", shotgun)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /shotgun [1 - 3]");
		return 1;
	}
	
	switch(shotgun) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "SHOTGUN", "shotgun_crouchfire",4.1,0,1,1,1,1);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "SHOTGUN", "shotgun_fire",4.1,0,1,1,1,1);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "SHOTGUN", "shotgun_fire_poor",4.1,0,1,1,1,1);
		}
		
		default: 
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /shotgun [1 - 3]");
		}
	}
	
	return 1;
}

CMD:colt(playerid, params[])
{
	
	new colt;
	
	if (sscanf(params, "i", colt)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /colt [1 - 3]");
		return 1;
	}
	
	switch(colt) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "COLT45", "colt45_fire_2hands",4.1,0,1,1,1,1);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "COLT45", "colt45_reload",4.1,0,1,1,1,1);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "COLT45", "sawnoff_reload",4.1,0,1,1,1,1);
		}
		
		default:
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /colt [1 - 3]");
		}
	}
	
	return 1;
}

CMD:bj(playerid, params[]) 
{
	new param;
	
	if (!sscanf(params, "i", param)) 
	{
        switch (param) 
        {
            case 1: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_START_W", 4.0, 1, 1, 1, 1, 1);
            }
            
            case 2: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_START_P", 4.0, 1, 1, 1, 1, 1);
            }
            
            case 3: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 4.0, 1, 1, 1, 1, 1);
            }
            
            case 4: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_P", 4.0, 1, 1, 1, 1, 1);
            }
            
            case 5: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_END_W", 4.0, 1, 1, 1, 1, 1);
            }
            
            case 6: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_COUCH_END_P", 4.0, 1, 1, 1, 1, 1);
            }
            
            case 7: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_START_W", 4.0, 1, 1, 1, 1, 1);
            }
            
            case 8: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_START_P", 4.0, 1, 1, 1, 1, 1);
            }
            
            case 9: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_W", 4.0, 1, 1, 1, 1, 1);
            }
            
            case 10: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_P", 4.0, 1, 1, 1, 1, 1);
            }
            
            case 11: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_END_W", 4.0, 1, 1, 1, 1, 1);
            }
            
            case 12: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_STAND_END_P", 4.0, 1, 1, 1, 1, 1);
            }
        }

        return 1;
    }

    SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /bj [1 - 12]");

  	return 1;
}

CMD:carbj(playerid, params[])
{
    new param;

    if (!sscanf(params, "d", param))
    {
        switch (param)
        {       
            case 1: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_CAR_START_W", 4.0, 1, 1, 1, 1, 1, 1);
            }
            
            case 2: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_CAR_START_P", 4.0, 1, 1, 1, 1, 1, 1);
            }
            
            case 3: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_CAR_LOOP_W", 4.0, 1, 1, 1, 1, 1, 1);
            }
            
            case 4: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_CAR_LOOP_P", 4.0, 1, 1, 1, 1, 1, 1);
            }
            
            case 5: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_CAR_END_W", 4.0, 1, 1, 1, 1, 1, 1);
            }
            
            case 6: 
            {
                ApplyAnimationEx(playerid, "BLOWJOBZ", "BJ_CAR_END_P", 4.0, 1, 1, 1, 1, 1, 1);
            }
        }

        return 1;
    }

    SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /carbj [1 - 6]");

    return 1;
}

CMD:spank(playerid, params[]) 
{
	
	new spank;
	
	if (sscanf(params, "i", spank)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /spank [1 - 8]");
		return 1;
	}
	
	switch(spank) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "SNM", "SPANKING_IDLEW", 4.0, 1, 1, 1, 1, 1);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "SNM", "SPANKING_IDLEP", 4.0, 1, 1, 1, 1, 1);
		}
		
		case 3: 
		{
			ApplyAnimationEx(playerid, "SNM", "SPANKINGW", 4.0, 1, 1, 1, 1, 1);
		}
		case 4: 
		{
			ApplyAnimationEx(playerid, "SNM", "SPANKINGP", 4.0, 1, 1, 1, 1, 1);
		}
		
		case 5: 
		{
			ApplyAnimationEx(playerid, "SNM", "SPANKEDW", 4.0, 1, 1, 1, 1, 1);
		}
		
		case 6: 
		{
			ApplyAnimationEx(playerid, "SNM", "SPANKEDP", 4.0, 1, 1, 1, 1, 1);
		}
		
		case 7: 
		{
			ApplyAnimationEx(playerid, "SNM", "SPANKING_ENDW", 4.0, 1, 1, 1, 1, 1);
		}
		
		case 8: 
		{
			ApplyAnimationEx(playerid, "SNM", "SPANKING_ENDP", 4.0, 1, 1, 1, 1, 1);
		}
		
		default:
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /spank [1 - 8]");
		}
  	}
	
  	return 1;
}

CMD:sleep(playerid, params[]) 
{
	
	new value;
	
	if (sscanf(params, "i", value)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /sleep [1 - 2]");
		return 1;
	}
	
	switch(value) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "INT_HOUSE", "BED_In_L",4.0,0,0,1,1,0);
		}
		
		case 2:
		{
			ApplyAnimationEx(playerid, "INT_HOUSE", "BED_In_R",4.0,0,0,1,1,0);
		}
	
		default:
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /sleep [1 - 2]");
		}
	}
	
	return 1;
}

CMD:taxi(playerid, params[]) 
{
	
	new taxi;
	
	if (sscanf(params, "i", taxi)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /taxi [1 - 2]");
		return 1;
	}
	
	switch(taxi) 
	{
		case 1: 
		{
			ApplyAnimationEx(playerid, "MISC", "hiker_pose", 3.0,0,1,1,1,0);
		}
	
		case 2:
		{
			ApplyAnimationEx(playerid, "MISC", "hiker_pose_L", 3.0,0,1,1,1,0);
		}
		
		default:
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /taxi [1 - 2]");
		}
	}
	
	return 1;
}

CMD:waim(playerid, params[]) 
{
	
	new waim;
	
	if (sscanf(params, "i", waim)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /waim [1 - 3]");
		return 1;
	}
	
	switch(waim) 
	{
		case 1:
		{
			ApplyAnimationEx(playerid, "TEC", "TEC_reload",4.1,0,1,1,1,1);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "PED", "Driveby_L",4.1,0,1,1,1,1);
		}
		
		case 3:
		{
			ApplyAnimationEx(playerid, "PED", "Driveby_R",4.1,0,1,1,1,1);
		}
		
		default:
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /waim [1 - 3]");
		}
	}
	
	return 1;
}

CMD:lookout(playerid, params[]) 
{	
	new lookout;
	
	if (sscanf(params, "i", lookout)) 
	{
		SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /lookout [1 - 3]");
		return 1;
	}
	
	switch(lookout) 
	{
		case 1:
		{
			ApplyAnimationEx(playerid, "SHOP", "ROB_Shifty", 4.0, 0, 0, 0, 0, 0);
		}
		
		case 2: 
		{
			ApplyAnimationEx(playerid, "SWAT", "swt_wllpk_L",4.0,0,0,1,1,0);
		}
		
		case 3:
		{
			ApplyAnimationEx(playerid, "SWAT", "swt_wllpk_R",4.0,0,0,1,1,0);
		}
		
		default:
		{
			SendClientMessage(playerid, C_WHITE, !#DEFAULT " Введите: /lookout [1 - 3]");
		}	
	}

	return 1;
}

