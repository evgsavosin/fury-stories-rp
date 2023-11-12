/*!
	@brief Главное меню игрока
	@author Found (evg.savosin)
	@date 26.04.2018
*/

/**
    Public function
*/

function OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if (PRESSED(KEY_YES))
	{
		Dialog_Show(playerid, Dialog:PLAYER_MENU);
		return 1;
	}
	
	#if defined PlayerMe_OnPlayerKeyStateChange
		return PlayerMe_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
	#else 
		return 1;
	#endif
}
#if defined _ALS_OnPlayerKeyStateChange
    #undef OnPlayerKeyStateChange
#else
    #define _ALS_OnPlayerKeyStateChange
#endif

#define	OnPlayerKeyStateChange	PlayerMe_OnPlayerKeyStateChange
#if defined PlayerMe_OnPlayerKeyStateChange
	forward PlayerMe_OnPlayerKeyStateChange(playerid, newkeys, oldkeys);
#endif


/**
    Dialogs
*/

// PLAYER_MENU
DialogCreate:PLAYER_MENU(playerid)
{
    format:g_string(" \
			Персонаж\t" #cPROJECT "%s\n \
			Инвентарь\t" #cGRAY "/inv\n \
			Телефон\t" #cGRAY "/phone\n \
			Анимации\t" #cGRAY "/anim\n \
			Поддержка\t" #cGRAY "/rep & /ask\n \
			Помощь\t" #cGRAY "/help\n \
			Настройки\t" #cGRAY "/settings\n \
			Донат\t" #cGRAY "/donate",
		GetCharacterRPName(playerid)
	);
	
	Dialog_Open(playerid, Dialog:PLAYER_MENU, DIALOG_STYLE_TABLIST, "Меню", 
		g_string, 
		"Выбрать", "Закрыть"
	);

    return 1;
}

DialogResponse:PLAYER_MENU(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        return 1;
    }

    switch (listitem)
    {
        case 0: // Character
        {
            format:g_string(" \
                Информация\t" #cGRAY "/stats\n \
                Сменить персонажа\t" #cGRAY "/relogin"
            );

            Dialog_Open(playerid, Dialog:PLAYER_MENU_CHARACTER, DIALOG_STYLE_TABLIST, "Персонаж", 
                g_string, 
                "Выбрать", "Закрыть"
            );
        }
        
        case 1: // Inventory
        {
            ShowInventory(playerid, 
                (!user_data[playerid][u_settings][SET_INVENTORY]) ? TEXTDRAW_INVENTORY : DIALOG_INVENTORY 
            );
        }
        
        case 2: // Phone
        {
            cmd_phone(playerid);
        }
        
        case 3: // Anim
        {
            cmd_anim(playerid);
        }
        
        case 4: // Support
        {
            Dialog_Show(playerid, Dialog:PLAYER_MENU_SUPPORT);
        }
        
        case 5: // Help
        {
            Dialog_Show(playerid, Dialog:PLAYER_MENU_HELP);
        }
        
        case 6: // Settings
        {
            Dialog_Show(playerid, Dialog:PLAYER_MENU_SETTINGS);
        }
        
        case 7: // Donate
        {
            ShowPlayerDonate(playerid);
        }
    }
    return 1;
}

// PLAYER_MENU_CHARACTER
DialogResponse:PLAYER_MENU_CHARACTER(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        Dialog_Show(playerid, Dialog:PLAYER_MENU);
        return 1;
    }
    
    if (listitem == 0) // Information
    {
        cmd_stats(playerid);
    }
    else if (listitem == 1) // Change character
    {
        cmd_relogin(playerid);
    }

    return 1;
}

// PLAYER_MENU_SUPPORT
DialogCreate:PLAYER_MENU_SUPPORT(playerid)
{
    Dialog_Open(playerid, Dialog:PLAYER_MENU_SUPPORT, DIALOG_STYLE_TABLIST, "Поддержка",
        " Отправить жалобу\t" #cGRAY "/rep\n \
        Задать вопрос\t" #cGRAY "/ask",
        "Выбрать", "Назад"
    );

    return 1;
}

DialogResponse:PLAYER_MENU_SUPPORT(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        Dialog_Show(playerid, Dialog:PLAYER_MENU);
        return 1;
    }
    
    if (listitem == 0) 
    {
        Dialog_Show(playerid, Dialog:PLAYER_MENU_SUPPORT_REPORT);
    }
    else 
    {
        Dialog_Show(playerid, Dialog:PLAYER_MENU_SUPPORT_ASK);
    }

    return 1;
}

// PLAYER_MENU_SUPPORT_REPORT
DialogCreate:PLAYER_MENU_SUPPORT_REPORT(playerid, params[])
{
    format:g_string(#CI_DIALOG_INFO "Введите текст жалобы:%s%s%s",
        !isnull(params) ? "\n\n" : "",
        !isnull(params) ? cRED : "",
        !isnull(params) ? params : ""
    );

    Dialog_Open(playerid, Dialog:PLAYER_MENU_SUPPORT_REPORT, DIALOG_STYLE_INPUT, "Отправить жалобу", 
        g_string,
        "Отправить", "Назад"
    );

    return 1;
}

DialogResponse:PLAYER_MENU_SUPPORT_REPORT(playerid, response, listitem, inputtext[])
{
    if (isnull(inputtext))
	{
        Dialog_Show(playerid, Dialog:PLAYER_MENU_SUPPORT_REPORT, "Вы не ввели текст жалобы.");
        return 1;
    }

    cmd_rep(playerid, inputtext);
    return 1;
}

// PLAYER_MENU_SUPPORT_ASK
DialogCreate:PLAYER_MENU_SUPPORT_ASK(playerid, params[])
{
    format:g_string(#CI_DIALOG_INFO "Введите текст вопроса:%s%s%s",
        !isnull(params) ? "\n\n" : "",
        !isnull(params) ? cRED : "",
        !isnull(params) ? params : ""
    );

    Dialog_Open(playerid, Dialog:PLAYER_MENU_SUPPORT_ASK, DIALOG_STYLE_INPUT, "Отправить вопрос", 
        g_string,
        "Отправить", "Назад"
    );

    return 1;
}

DialogResponse:PLAYER_MENU_SUPPORT_ASK(playerid, response, listitem, inputtext[])
{
    if (isnull(inputtext))
	{
        Dialog_Show(playerid, Dialog:PLAYER_MENU_SUPPORT_ASK, "Вы не ввели текст вопроса.");
        return 1;
    }

    cmd_ask(playerid, inputtext);
    return 1;
}

// PLAYER_MENU_RETURN
DialogResponse:PLAYER_MENU_RETURN(playerid, response, listitem, inputtext[])
{
    return Dialog_Show(playerid, Dialog:PLAYER_MENU);
}

// PLAYER_MENU_HELP
DialogCreate:PLAYER_MENU_HELP(playerid)
{
    Dialog_Open(playerid, Dialog:PLAYER_MENU_HELP, DIALOG_STYLE_LIST, "Помощь", 
		" Список команд\n \
		  Базовая информация\n \
		  Работы",
		"Далее", "Назад"
	);

    return 1;
}

DialogResponse:PLAYER_MENU_HELP(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        return 1;
    }

    if (listitem == 0) // Command list
    {
        Dialog_Show(playerid, Dialog:PLAYER_MENU_HELP_COMMANDS);
    }
    else if (listitem == 1) // Base information
    {
        Dialog_Show(playerid, Dialog:PLAYER_MENU_HELP_BASE);
    }
    else if (listitem == 2) // Job information
    {
        Dialog_Show(playerid, Dialog:PLAYER_MENU_HELP_JOB);
    }

    return 1;
}

// PLAYER_MENU_HELP_COMMANDS
DialogCreate:PLAYER_MENU_HELP_COMMANDS(playerid)
{
    Dialog_Open(playerid, Dialog:PLAYER_MENU_HELP_COMMANDS, DIALOG_STYLE_LIST, "Список команд", " \
        Основные команды\n \
        Общение\n \
        Отыгровка роли\n \
        Взаимодействие\n \
        Транспорт\n \
        Жилье\n \
        Бизнес\n \
        Помещения\n \
        Организация",
        "Далее", "Назад"
    );

    return 1;
}

DialogResponse:PLAYER_MENU_HELP_COMMANDS(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        Dialog_Show(playerid, Dialog:PLAYER_MENU_HELP);
        return 1;
    }
    
    clean:<g_big_string>;

    if (listitem == 0) // Основные команды
    {
        strcat(g_big_string,
            "" #cPROJECT "/help" #cWHITE " – окно с помощью;\n\
            " #cPROJECT "/anim" #cWHITE " – анимации;\n\
            " #cPROJECT "/fa" #cWHITE " – избранные анимации;\n\
            " #cPROJECT "/stats" #cWHITE " – статистика;\n\
            " #cPROJECT "/inv" #cWHITE " – инвентарь;\n\
            " #cPROJECT "/afk" #cWHITE " – проверить время простоя в афк;\n\
            " #cPROJECT "/gps" #cWHITE " – навигация;\n\
            " #cPROJECT "/id" #cWHITE " – поиск игрока по нику;\n\
            " #cPROJECT "/ask" #cWHITE " – задать вопрос;\n\
            " #cPROJECT "/rep" #cWHITE " – подать жалобу;\n\
            " #cPROJECT "/nameon, /nameoff" #cWHITE " - вкл/выкл отображение ник-неймов;\n\
            " #cPROJECT "/blind" #cWHITE " - черный экран;"
        );
    } 
    else if (listitem == 1) // Общение
    {
        strcat(g_big_string,
            "" #cPROJECT "/b" #cWHITE " – OOC-чат;\n\
            " #cPROJECT "/bon, /boff" #cWHITE " - вкл/выкл ООС чат;\n\
            " #cPROJECT "/ab" #cWHITE " – ООС-чат над головой;\n\
            " #cPROJECT "/w [ID игрока]" #cWHITE " – шепот;\n\
            " #cPROJECT "/low" #cWHITE " – сказать тихо;\n\
            " #cPROJECT "/s" #cWHITE " – крик;\n\
            " #cPROJECT "/pm [ID игрока]" #cWHITE " – личные OOC-сообщения;\n\
            " #cPROJECT "/pmon, /pmoff" #cWHITE " - вкл/выкл личные ООС-сообщения;\n\
            " #cPROJECT "/r" #cWHITE " – рация;\n\
            " #cPROJECT "/sms [номер]" #cWHITE " – отправить сообщение;\n\
            " #cPROJECT "/channel" #cWHITE " – сменить канал у рации;\n\
            " #cPROJECT "/slot" #cWHITE " – сменить слот у рации;"
        );
    }
    else if (listitem == 2) // Отыгровка роли
    {
        strcat(g_big_string,
            "" #cPROJECT "/me" #cWHITE " – описание или действие;\n\
            " #cPROJECT "/ame" #cWHITE " – короткое действие от первого лица;\n\
            " #cPROJECT "/do" #cWHITE " – описание;\n\
            " #cPROJECT "/setdesc" #cWHITE " – создание/удаление описания персонажа;\n\
            " #cPROJECT "/desc" #cWHITE " – просмотреть описание персонажа;\n\
            " #cPROJECT "/action" #cWHITE " – прикрепление описания к местности;\n\
            " #cPROJECT "/setcdesc" #cWHITE " – cоздание/удаление описания автомобиля;\n\
            " #cPROJECT "/cdesc" #cWHITE " – просмотреть описание автомобиля."
        );
    }
    else if (listitem == 3) // Взаимодействие
    {
        strcat(g_big_string,
            "" #cPROJECT "/helpup [ID игрока]" #cWHITE " – возможность поднять человека с стадии;\n\
            " #cPROJECT "/showid [ID игрока]" #cWHITE " – показать документ, удостоверяющий личность;\n\
            " #cPROJECT "/frisk [ID игрока]" #cWHITE " – обыскать человека;\n\
            " #cPROJECT "/corpse [ID трупа или {стоя рядом}]" #cWHITE " – взаимодействие с трупом;\n\
            " #cPROJECT "/eject" #cWHITE " – выкинуть игрока из автомобиля;\n\
            " #cPROJECT "/pboot [ID игрока]" #cWHITE " - погрузить в багажник игрока/труп;\n\
            " #cPROJECT "/pay [ID игрока]" #cWHITE " – передать денег;\n\
            " #cPROJECT "/pmenu" #cWHITE " – включить/выключить телефон;\n\
            " #cPROJECT "/time" #cWHITE " – посмотреть время;"
        );
    }
    else if (listitem == 4) // Транспорт
    {
        strcat(g_big_string,
            "" #cPROJECT "/cmenu" #cWHITE " – меню управления транспортом;\n\
            " #cPROJECT "/clist" #cWHITE " – список имеющегося транспорта;\n\
            " #cPROJECT "/window [ l | r | rl | rr ]" #cWHITE " – окна;\n\
            " #cPROJECT "/hood" #cWHITE " – капот;\n\
            " #cPROJECT "/boot" #cWHITE " – багажник;\n\
            " #cPROJECT "/park" #cWHITE " – припарковать транспорт;\n\
            " #cPROJECT "/clock" #cWHITE " – открыть/закрыть транспорт;\n\
            " #cPROJECT "/sellcar [ID игрока]" #cWHITE " – продать транспорт;\n\
            " #cPROJECT "/trustcar [ID игрока]" #cWHITE " – доверить транспорт;\n\
            " #cPROJECT "/ckey" #cWHITE " – брелок управления;\n\
            " #cPROJECT "/swapcar [ID игрока]" #cWHITE " – обменять транспорт."
        );
    }
    else if (listitem == 5) // Дом
    {
        strcat(g_big_string,
            "" #cPROJECT "/hmenu" #cWHITE " – меню управления домом;\n\
            " #cPROJECT "/hlist" #cWHITE " – список имеющегося домовладения;\n\
            " #cPROJECT "/hlock" #cWHITE " - открыть/закрыть дом;\n\
            " #cPROJECT "/evict" #cWHITE " - выселиться если Вы сожилец в доме;\n\
            " #cPROJECT "/gmenu" #cWHITE " - меню гаража;\n\
            " #cPROJECT "/glock" #cWHITE " - открыть/закрыть гараж;"
        );
    }
    else if (listitem == 6)
    {
        strcat(g_big_string,
            "" #cPROJECT "/bmenu" #cWHITE " – меню управления бизнесом;"
        );
    }
    else if (listitem == 7)
    {
        strcat(g_big_string,
            "" #cPROJECT "/prmenu" #cWHITE " – меню управления помещением;\n\
            " #cPROJECT "/prlock" #cWHITE " – открыть/закрыть бизнес;\n\
            " #cPROJECT "/prlist" #cWHITE " – список имеющихся помещений;"
        );
    }
    else if (listitem == 8)
    {
        if (!IsFractionMember(playerid))
        {
            Dialog_Show(playerid, Dialog:PLAYER_MENU_HELP_COMMANDS);
            SendClientMessage(playerid, C_WHITE, !PLAYER_NO_ACCESS);
            return 1;
        }
        
        strcat(g_big_string,
            "" #cPROJECT "/fmenu" #cWHITE " – меню управления организацией;\n\
            " #cPROJECT "/finvite" #cWHITE " – принять персонажа в организацию;\n\
            " #cPROJECT "/funinvite" #cWHITE " – уволить персонажа из организации;\n\
            " #cPROJECT "/setrank" #cWHITE " – изменить ранг сотрудника;\n\
            " #cPROJECT "/setunit" #cWHITE " – изменить подразделение сотрудника;\n\
            " #cPROJECT "/fmembers" #cWHITE " - список сотрудников;\n\
            " #cPROJECT "/f" #cWHITE " - OOC-чат фракции;\n\
            " #cPROJECT "/fpark" #cWHITE " - припарковать транспорт;\n\
            " #cPROJECT "/color" #cWHITE " - цвет ника;\n\
            " #cPROJECT "/frepair" #cWHITE " - починить и заправить транспорт;\n\
            " #cPROJECT "/d(ep)" #cWHITE " - чат департамента;\n"
        );
        
        new fraction_id = GetFractionMemberId(playerid);
        
        switch (fraction_id)
        {
            case FRACTION_GOVERNMENT:
            {
            }
            
            case FRACTION_COURT:
            {
            }
            
            case FRACTION_PD, FRACTION_SD:
            {
                strcat(g_big_string, 
                    "" #cPROJECT "/s(trobe)l(ight)" #cWHITE " - стробоскопы;\n\
                    " #cPROJECT "/m" #cWHITE " - громкоговоритель;\n\
                    " #cPROJECT "/mdc" #cWHITE " - Mobile Data Computer;\n\
                    " #cPROJECT "/accept" #cWHITE " - Принять вызов;\n\
                    " #cPROJECT "/callsign" #cWHITE " - установить маркировку;\n\
                    " #cPROJECT "/dcallsign" #cWHITE " - удалить маркировку;\n\
                    " #cPROJECT "/frisk" #cWHITE " - обыскать;\n\
                    " #cPROJECT "/hale" #cWHITE " - вести за собой;\n\
                    " #cPROJECT "/unhale" #cWHITE " - прекратить вести за собой;\n\
                    " #cPROJECT "/put" #cWHITE " - посадить в транспорт игрока;\n\
                    " #cPROJECT "/cuff" #cWHITE " - надеть наручники;\n\
                    " #cPROJECT "/uncuff" #cWHITE " - снять наручники;\n\
                    " #cPROJECT "/su" #cWHITE " - объявить в розыск;\n\
                    " #cPROJECT "/unsu" #cWHITE " - снять розыск;\n\
                    " #cPROJECT "/taser" #cWHITE " - воспользоваться электрошокером;\n\
                    " #cPROJECT "/arrest" #cWHITE " - арестовать;\n\
                    " #cPROJECT "/unarrest" #cWHITE " - снять арест;\n\
                    " #cPROJECT "/ram" #cWHITE " - выбить дверь помещения\n");
                    
                if (fraction_id == FRACTION_SD)
                {
                    strcat(g_big_string,
                        "" #cPROJECT "/jail" #cWHITE " - посадить в городскую тюрьму;\n\
                        " #cPROJECT "/unjail" #cWHITE " - выпустить из городской тюрьмы;\n\
                        " #cPROJECT "/setjail" #cWHITE " - изменить время заключения в тюрьме;"
                    );
                }
            }
            
            case FRACTION_FD:
            {
                strcat(g_big_string, 
                    "" #cPROJECT "/heal" #cWHITE " - вылечить игрока;\n\
                    " #cPROJECT "/fireshape" #cWHITE " - сменить форму;\n");
            }
            
            case FRACTION_NEWS:
            {
                strcat(g_big_string, 
                    "" #cPROJECT "/e" #cWHITE " - вести эфир;\n");
            }
            
            case FRACTION_NP:
            {
                strcat(g_big_string, 
                    "" #cPROJECT "/s(trobe)l(ight)" #cWHITE " - стробоскопы;\n\
                    " #cPROJECT "/m" #cWHITE " - громкоговоритель;\n\
                    " #cPROJECT "/callsign" #cWHITE " - установить маркировку;\n\
                    " #cPROJECT "/dcallsign" #cWHITE " - удалить маркировку;\n\
                    " #cPROJECT "/frisk" #cWHITE " - обыскать;\n\
                    " #cPROJECT "/hale" #cWHITE " - вести за собой;\n\
                    " #cPROJECT "/unhale" #cWHITE " - прекратить вести за собой;\n\
                    " #cPROJECT "/put" #cWHITE " - посадить в транспорт игрока;\n\
                    " #cPROJECT "/cuff" #cWHITE " - надеть наручники;\n\
                    " #cPROJECT "/uncuff" #cWHITE " - снять наручники;\n\
                    " #cPROJECT "/arrest" #cWHITE " - арестовать;\n\
                    " #cPROJECT "/unarrest" #cWHITE " - снять арест;\n");
                    
            }
            
            case FRACTION_HOSPITAL:
            {
                strcat(g_big_string, 
                    "" #cPROJECT "/heal" #cWHITE " - вылечить игрока;\n");
            }
        }
    }
    
    Dialog_Open(
        playerid, 
        Dialog:PLAYER_MENU_HELP_COMMANDS_R, 
        DIALOG_STYLE_MSGBOX,
        inputtext, 
        g_big_string, 
        "Назад", 
        ""
    );

    return 1;
}

// PLAYER_MENU_HELP_BASE
DialogCreate:PLAYER_MENU_HELP_BASE(playerid)
{
    Dialog_Open(
        playerid, 
        Dialog:PLAYER_MENU_HELP_BASE, 
        DIALOG_STYLE_MSGBOX, 
        "Базовая информация", "\
        " #CI_DIALOG_INFO " Добро пожаловать на сервер проекта " #cPROJECT "Fury Stories" #cWHITE "!\n\
        Это вводная инструкция, которая поможет освоиться на сервере.\n\
        \n\
        Для того чтобы войти в здание, используйте клавишу взаимодействия \"H\".\n\
        Вы можете арендовать или купить имущество, для этого нужно войти в него и нажать клавишу \"N\".\n\
        Для того, чтобы найти необходимое место используйте - /gps.\n\
        Об остальных командах и возможностях можно узнать в меню помощи - /help.\n\
        \n\
        У Вас также имеется стартовый капитал, который находится на карте \"Start\".\n\
        На средства стартового капитала можно приобрести или арендовать жилье, транспорт или помещения.\n\
        Также с помощью карты можно расплатиться и за другие услуги.\n\
        Обналичить денежные средства с этой карты нельзя, однако ее баланс можно пополнить.\n\
        Спустя несколько недель средства с данной карты будут направлены на Вашу основную дебетовую карту.\n\
        \n\
        Выплата зарплат и пособий проходит за полный рабочий день. Для этого, необходимо отыграть 2 часа, а\n\
        после получить определенную сумму в зависимости от рода деятельности.\n\
        За каждый последующий час Вам будут выплачиваться премиальные, которые составляют 20% от Вашей зарплаты.\n\
        \n\
        Приятной игры!",
        "Назад",
        ""
    );

    return 1;
}

DialogResponse:PLAYER_MENU_HELP_BASE(playerid, response, listitem, inputtext[])
{
    Dialog_Show(playerid, Dialog:PLAYER_MENU_HELP);
    return 1;
}

// PLAYER_MENU_HELP_JOB
DialogCreate:PLAYER_MENU_HELP_JOB(playerid)
{
    Dialog_Open(playerid, Dialog:PLAYER_MENU_HELP_JOB, DIALOG_STYLE_MSGBOX, "Работы", "\
        " #CI_DIALOG_INFO "Системные работы на сервере сведены к минимуму.\n\n\
        Если Вы " #cGRAY "начинающий" #cWHITE " игрок, то на первое время мы рекомендуем\n\
        " #cGOLD "работу таксиста" #cWHITE " в «Fuber».\n\
        \n\
        Это позволит заработать Вам первые средств и посмотреть на игру других игроков.\n\
        \n\
        Если Вы уже " #cGRAY "опытный или освоившийся" #cWHITE " игрок, то рекомендуем ознакомиться с " #cPROJECT"рабочим капиталом" #cWHITE ".",
        "Назад",
        ""
    );

    return 1;
}

DialogResponse:PLAYER_MENU_HELP_JOB(playerid, response, listitem, inputtext[])
{
    Dialog_Show(playerid, Dialog:PLAYER_MENU_HELP);
    return 1;
}

// PLAYER_MENU_HELP_COMMANDS_RETURN
DialogResponse:PLAYER_MENU_HELP_COMMANDS_R(playerid, response, listitem, inputtext[])
{
    Dialog_Show(playerid, Dialog:PLAYER_MENU_HELP);
    return 1;
}

// PLAYER_MENU_SETTINGS
DialogCreate:PLAYER_MENU_SETTINGS(playerid)
{
    format:g_string(" \
	    " #cWHITE "Общие настройки\t" #cGRAY "%s\n \ 
	    " #cWHITE "Настройки персонажа\t" #cGRAY "%s",
		GetUserName(playerid),
		GetCharacterRPName(playerid)
	);
	
	Dialog_Open(playerid, Dialog:PLAYER_MENU_SETTINGS, DIALOG_STYLE_TABLIST, "Настройки",
		g_string,
		"Далее", "Назад" 
	);

    return 1;
}

DialogResponse:PLAYER_MENU_SETTINGS(playerid, response, listitem, inputtext[])
{
    if (!response)
    {
        cmd_menu(playerid);
        return 1;
    }
    
    if (listitem == 0)
    {
        ShowUserSettings(playerid);
    }
    else
    {
        ShowAccountSettings(playerid);
    }

    return 1;
}


/**
    Other function
*/

ShowPlayerStats(playerid, targetid = INVALID_PLAYER_ID, bool: is_admin = false)
{
	strglobalclear();

	new year,
		month,
		day;

	gmtime(user_data[playerid][u_register_time], year, month, day);

	strcat(g_big_string, #DEFAULT " Аккаунт\n\n");
	
	format:g_small_string("Имя:     			  " #cPROJECT "\t\t%s\n", user_data[playerid][u_name]);
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "Электронная почта:     " #cPROJECT "\t\t\t%s\n", user_data[playerid][u_email]);
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "Предупреждения:     	 " #cPROJECT "\t\t%i/3\n", user_data[playerid][u_warn]);
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "Дата регистрации:      " #cPROJECT "\t\t\t%02d/%02d/%04d\n", day, month, year);
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "VIP аккаунт:      	 " #cPROJECT "\t\t\t%s\n", GetUserVipText(playerid));
	strcat(g_big_string, g_small_string);
	
	if (VIP_STARTER <= GetUserVip(playerid) <= VIP_ADVANCED)
	{
		format:g_small_string("" #cWHITE "Срок действия VIP:      	 " #cPROJECT "\t%d дней\n", GetUserVipEndDayCount(playerid));
		strcat(g_big_string, g_small_string);
	}
	else if (GetUserVip(playerid) == VIP_PRO)
	{
		format:g_small_string("" #cWHITE "Срок действия VIP:      	 " #cGOLD "\tнавсегда\n", GetUserVipEndDayCount(playerid));
		strcat(g_big_string, g_small_string);
	}
	
	if (is_admin)
	{
		format:g_small_string("" #cWHITE "Регистрационный IP:      " #cPROJECT "\t\t%s\n", user_data[playerid][u_reg_ip]);
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("" #cWHITE "Последний IP:      " #cPROJECT "\t\t%s\n", user_data[playerid][u_last_ip]);
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("" #cWHITE "Текущий IP:      	" #cPROJECT "\t\t%s\n", user_data[playerid][u_ip]);
		strcat(g_big_string, g_small_string);
	}
	
	strcat(g_big_string, "\n\n" #DEFAULT " Персонаж\n\n");
	
	format:g_small_string("" #cWHITE "Имя:     			  	 " #cPROJECT "\t%s\n", GetCharacterName(playerid));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "Пол персонажа:   	  	 " #cPROJECT "\t%s\n", (!character_data[playerid][c_sex]) ? ("Мужской") : ("Женский"));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "Наличные деньги: 	  	 " #cPROJECT "\t" #cGREEN"$%d" #cWHITE "\n", GetCharacterMoney(playerid));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "Счёт в банке: 	 	 " #cPROJECT "\t\t" #cGREEN"$%d" #cWHITE "\n", GetCharacterBank(playerid));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "Карта: 	 		 	 " #cPROJECT "\t" #cGREEN"$%d" #cWHITE "\n", GetCharacterCardBalance(playerid));
	strcat(g_big_string, g_small_string);
	
	if (GetCharacterCardStart(playerid) > 0)
	{
		format:g_small_string("" #cWHITE "Карта «Start»: 	 	 " #cPROJECT "\t\t" #cGREEN"$%d" #cWHITE "\n", GetCharacterCardStart(playerid));
		strcat(g_big_string, g_small_string);
	}
	
	if (IsCreditCardExists(playerid))
	{
		gmtime(GetCreditDateSuccess(credit_data[playerid][credit_give_time]), year, month, day);
	
	    format:g_small_string("" #cWHITE "Кредитная карта: 	 	    " #cPROJECT "\t" #cGREEN"$%d" #cWHITE " (пополнить " #cGREEN "$%d" #cWHITE " до %02d.%02d.%d)\n", 
			GetCreditCardBalance(playerid),
			credit_data[playerid][credit_limit],
			day,
			month,
			year
		);
		
		strcat(g_big_string, g_small_string);
	}
	
	clean:<g_string>;
	
	if (!IsFractionMember(playerid))
	{
		strcat(g_string, "Отсутствует");
	}
	else 
	{
		new findex = GetFractionMember(playerid);
		
		strcat(
			g_string, 
			GetFractionName(findex)
		);
	}
	
	format:g_small_string("" #cWHITE "Организация:         	  	" #cPROJECT "\t%s\n",
		g_string
	);
	
	strcat(g_big_string, g_small_string);
	

	clean:<g_string>;
	if (!IsFractionMember(playerid))
	{
		strcat(g_string, "Отсутствует");
	}
	else 
	{
		new findex = GetFractionMember(playerid),
			rindex = GetFractionMemberRank(playerid);
		
		if (rindex != INVALID_PARAM)
		{
			strcat(
				g_string, 
				fraction_rank_data[findex][rindex][fr_name]
			);
		}
		else 
		{
			strcat(g_string, "Отсутствует");
		}
	}
	
	format:g_small_string("" #cWHITE "Должность:       	  	" #cPROJECT "\t%s\n",
		g_string
	);
	
	strcat(g_big_string, g_small_string);
	
	clean:<g_string>;
	if (GetCrimeMember(playerid) == INVALID_PARAM)
	{
		strcat(g_string, "Отсутствует");
	}
	else
	{
		strcat(g_string, GetCrimeName(playerid));
	}
	
	format:g_small_string("" #cWHITE "Криминал:				" #cPROJECT "%s\n",
		g_string
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "Домов: 	  		   	" #cPROJECT "%d\n", GetPlayerHousesCount(playerid));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "Помещений: 	  	   	" #cPROJECT "\t%d\n", GetPlayerPremisesCount(playerid));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "Транспорта: 	  	   	" #cPROJECT "\t%d\n", GetPlayerVehiclesCount(playerid));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "Компаний: 	  	   	" #cPROJECT "\t%d\n", GetPlayerBusinessesCount(playerid));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "Сайтов: 	  	   		" #cPROJECT "%d\n", GetPlayerSitesCount(playerid));
	strcat(g_big_string, g_small_string);
	
    if (targetid == INVALID_PLAYER_ID)
    {
        Dialog_Open(
            playerid,
            Dialog:PLAYER_MENU_RETURN,
            DIALOG_STYLE_MSGBOX, 
            "Статистика", 
            g_big_string, 
            "Назад", 
            "" 
        );
    }
    else
    {
        Dialog_Open(
            targetid,
            Dialog:NONE,
            DIALOG_STYLE_MSGBOX, 
            "Статистика", 
            g_big_string, 
            "Назад", 
            "" 
        );
    }

	return 1;
}


/**
    Commands
*/

CMD:mm(playerid)
{
    return cmd_menu(playerid);
}

CMD:mn(playerid)
{
    return cmd_menu(playerid);
}

CMD:menu(playerid)
{
	return Dialog_Show(playerid, Dialog:PLAYER_MENU);
}

CMD:settings(playerid)
{
    return Dialog_Show(playerid, Dialog:PLAYER_MENU_SETTINGS);
}

CMD:stats(playerid)
{
	ShowPlayerStats(playerid);
	return 1;
}

CMD:help(playerid)
{
    Dialog_Show(playerid, Dialog:PLAYER_MENU_HELP);
	return 1;
}