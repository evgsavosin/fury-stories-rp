/*!
	@brief ������� ���� ������
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
			��������\t" #cPROJECT "%s\n \
			���������\t" #cGRAY "/inv\n \
			�������\t" #cGRAY "/phone\n \
			��������\t" #cGRAY "/anim\n \
			���������\t" #cGRAY "/rep & /ask\n \
			������\t" #cGRAY "/help\n \
			���������\t" #cGRAY "/settings\n \
			�����\t" #cGRAY "/donate",
		GetCharacterRPName(playerid)
	);
	
	Dialog_Open(playerid, Dialog:PLAYER_MENU, DIALOG_STYLE_TABLIST, "����", 
		g_string, 
		"�������", "�������"
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
                ����������\t" #cGRAY "/stats\n \
                ������� ���������\t" #cGRAY "/relogin"
            );

            Dialog_Open(playerid, Dialog:PLAYER_MENU_CHARACTER, DIALOG_STYLE_TABLIST, "��������", 
                g_string, 
                "�������", "�������"
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
    Dialog_Open(playerid, Dialog:PLAYER_MENU_SUPPORT, DIALOG_STYLE_TABLIST, "���������",
        " ��������� ������\t" #cGRAY "/rep\n \
        ������ ������\t" #cGRAY "/ask",
        "�������", "�����"
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
    format:g_string(#CI_DIALOG_INFO "������� ����� ������:%s%s%s",
        !isnull(params) ? "\n\n" : "",
        !isnull(params) ? cRED : "",
        !isnull(params) ? params : ""
    );

    Dialog_Open(playerid, Dialog:PLAYER_MENU_SUPPORT_REPORT, DIALOG_STYLE_INPUT, "��������� ������", 
        g_string,
        "���������", "�����"
    );

    return 1;
}

DialogResponse:PLAYER_MENU_SUPPORT_REPORT(playerid, response, listitem, inputtext[])
{
    if (isnull(inputtext))
	{
        Dialog_Show(playerid, Dialog:PLAYER_MENU_SUPPORT_REPORT, "�� �� ����� ����� ������.");
        return 1;
    }

    cmd_rep(playerid, inputtext);
    return 1;
}

// PLAYER_MENU_SUPPORT_ASK
DialogCreate:PLAYER_MENU_SUPPORT_ASK(playerid, params[])
{
    format:g_string(#CI_DIALOG_INFO "������� ����� �������:%s%s%s",
        !isnull(params) ? "\n\n" : "",
        !isnull(params) ? cRED : "",
        !isnull(params) ? params : ""
    );

    Dialog_Open(playerid, Dialog:PLAYER_MENU_SUPPORT_ASK, DIALOG_STYLE_INPUT, "��������� ������", 
        g_string,
        "���������", "�����"
    );

    return 1;
}

DialogResponse:PLAYER_MENU_SUPPORT_ASK(playerid, response, listitem, inputtext[])
{
    if (isnull(inputtext))
	{
        Dialog_Show(playerid, Dialog:PLAYER_MENU_SUPPORT_ASK, "�� �� ����� ����� �������.");
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
    Dialog_Open(playerid, Dialog:PLAYER_MENU_HELP, DIALOG_STYLE_LIST, "������", 
		" ������ ������\n \
		  ������� ����������\n \
		  ������",
		"�����", "�����"
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
    Dialog_Open(playerid, Dialog:PLAYER_MENU_HELP_COMMANDS, DIALOG_STYLE_LIST, "������ ������", " \
        �������� �������\n \
        �������\n \
        ��������� ����\n \
        ��������������\n \
        ���������\n \
        �����\n \
        ������\n \
        ���������\n \
        �����������",
        "�����", "�����"
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

    if (listitem == 0) // �������� �������
    {
        strcat(g_big_string,
            "" #cPROJECT "/help" #cWHITE " � ���� � �������;\n\
            " #cPROJECT "/anim" #cWHITE " � ��������;\n\
            " #cPROJECT "/fa" #cWHITE " � ��������� ��������;\n\
            " #cPROJECT "/stats" #cWHITE " � ����������;\n\
            " #cPROJECT "/inv" #cWHITE " � ���������;\n\
            " #cPROJECT "/afk" #cWHITE " � ��������� ����� ������� � ���;\n\
            " #cPROJECT "/gps" #cWHITE " � ���������;\n\
            " #cPROJECT "/id" #cWHITE " � ����� ������ �� ����;\n\
            " #cPROJECT "/ask" #cWHITE " � ������ ������;\n\
            " #cPROJECT "/rep" #cWHITE " � ������ ������;\n\
            " #cPROJECT "/nameon, /nameoff" #cWHITE " - ���/���� ����������� ���-������;\n\
            " #cPROJECT "/blind" #cWHITE " - ������ �����;"
        );
    } 
    else if (listitem == 1) // �������
    {
        strcat(g_big_string,
            "" #cPROJECT "/b" #cWHITE " � OOC-���;\n\
            " #cPROJECT "/bon, /boff" #cWHITE " - ���/���� ��� ���;\n\
            " #cPROJECT "/ab" #cWHITE " � ���-��� ��� �������;\n\
            " #cPROJECT "/w [ID ������]" #cWHITE " � �����;\n\
            " #cPROJECT "/low" #cWHITE " � ������� ����;\n\
            " #cPROJECT "/s" #cWHITE " � ����;\n\
            " #cPROJECT "/pm [ID ������]" #cWHITE " � ������ OOC-���������;\n\
            " #cPROJECT "/pmon, /pmoff" #cWHITE " - ���/���� ������ ���-���������;\n\
            " #cPROJECT "/r" #cWHITE " � �����;\n\
            " #cPROJECT "/sms [�����]" #cWHITE " � ��������� ���������;\n\
            " #cPROJECT "/channel" #cWHITE " � ������� ����� � �����;\n\
            " #cPROJECT "/slot" #cWHITE " � ������� ���� � �����;"
        );
    }
    else if (listitem == 2) // ��������� ����
    {
        strcat(g_big_string,
            "" #cPROJECT "/me" #cWHITE " � �������� ��� ��������;\n\
            " #cPROJECT "/ame" #cWHITE " � �������� �������� �� ������� ����;\n\
            " #cPROJECT "/do" #cWHITE " � ��������;\n\
            " #cPROJECT "/setdesc" #cWHITE " � ��������/�������� �������� ���������;\n\
            " #cPROJECT "/desc" #cWHITE " � ����������� �������� ���������;\n\
            " #cPROJECT "/action" #cWHITE " � ������������ �������� � ���������;\n\
            " #cPROJECT "/setcdesc" #cWHITE " � c�������/�������� �������� ����������;\n\
            " #cPROJECT "/cdesc" #cWHITE " � ����������� �������� ����������."
        );
    }
    else if (listitem == 3) // ��������������
    {
        strcat(g_big_string,
            "" #cPROJECT "/helpup [ID ������]" #cWHITE " � ����������� ������� �������� � ������;\n\
            " #cPROJECT "/showid [ID ������]" #cWHITE " � �������� ��������, �������������� ��������;\n\
            " #cPROJECT "/frisk [ID ������]" #cWHITE " � �������� ��������;\n\
            " #cPROJECT "/corpse [ID ����� ��� {���� �����}]" #cWHITE " � �������������� � ������;\n\
            " #cPROJECT "/eject" #cWHITE " � �������� ������ �� ����������;\n\
            " #cPROJECT "/pboot [ID ������]" #cWHITE " - ��������� � �������� ������/����;\n\
            " #cPROJECT "/pay [ID ������]" #cWHITE " � �������� �����;\n\
            " #cPROJECT "/pmenu" #cWHITE " � ��������/��������� �������;\n\
            " #cPROJECT "/time" #cWHITE " � ���������� �����;"
        );
    }
    else if (listitem == 4) // ���������
    {
        strcat(g_big_string,
            "" #cPROJECT "/cmenu" #cWHITE " � ���� ���������� �����������;\n\
            " #cPROJECT "/clist" #cWHITE " � ������ ���������� ����������;\n\
            " #cPROJECT "/window [ l | r | rl | rr ]" #cWHITE " � ����;\n\
            " #cPROJECT "/hood" #cWHITE " � �����;\n\
            " #cPROJECT "/boot" #cWHITE " � ��������;\n\
            " #cPROJECT "/park" #cWHITE " � ������������ ���������;\n\
            " #cPROJECT "/clock" #cWHITE " � �������/������� ���������;\n\
            " #cPROJECT "/sellcar [ID ������]" #cWHITE " � ������� ���������;\n\
            " #cPROJECT "/trustcar [ID ������]" #cWHITE " � �������� ���������;\n\
            " #cPROJECT "/ckey" #cWHITE " � ������ ����������;\n\
            " #cPROJECT "/swapcar [ID ������]" #cWHITE " � �������� ���������."
        );
    }
    else if (listitem == 5) // ���
    {
        strcat(g_big_string,
            "" #cPROJECT "/hmenu" #cWHITE " � ���� ���������� �����;\n\
            " #cPROJECT "/hlist" #cWHITE " � ������ ���������� ������������;\n\
            " #cPROJECT "/hlock" #cWHITE " - �������/������� ���;\n\
            " #cPROJECT "/evict" #cWHITE " - ���������� ���� �� ������� � ����;\n\
            " #cPROJECT "/gmenu" #cWHITE " - ���� ������;\n\
            " #cPROJECT "/glock" #cWHITE " - �������/������� �����;"
        );
    }
    else if (listitem == 6)
    {
        strcat(g_big_string,
            "" #cPROJECT "/bmenu" #cWHITE " � ���� ���������� ��������;"
        );
    }
    else if (listitem == 7)
    {
        strcat(g_big_string,
            "" #cPROJECT "/prmenu" #cWHITE " � ���� ���������� ����������;\n\
            " #cPROJECT "/prlock" #cWHITE " � �������/������� ������;\n\
            " #cPROJECT "/prlist" #cWHITE " � ������ ��������� ���������;"
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
            "" #cPROJECT "/fmenu" #cWHITE " � ���� ���������� ������������;\n\
            " #cPROJECT "/finvite" #cWHITE " � ������� ��������� � �����������;\n\
            " #cPROJECT "/funinvite" #cWHITE " � ������� ��������� �� �����������;\n\
            " #cPROJECT "/setrank" #cWHITE " � �������� ���� ����������;\n\
            " #cPROJECT "/setunit" #cWHITE " � �������� ������������� ����������;\n\
            " #cPROJECT "/fmembers" #cWHITE " - ������ �����������;\n\
            " #cPROJECT "/f" #cWHITE " - OOC-��� �������;\n\
            " #cPROJECT "/fpark" #cWHITE " - ������������ ���������;\n\
            " #cPROJECT "/color" #cWHITE " - ���� ����;\n\
            " #cPROJECT "/frepair" #cWHITE " - �������� � ��������� ���������;\n\
            " #cPROJECT "/d(ep)" #cWHITE " - ��� ������������;\n"
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
                    "" #cPROJECT "/s(trobe)l(ight)" #cWHITE " - �����������;\n\
                    " #cPROJECT "/m" #cWHITE " - ����������������;\n\
                    " #cPROJECT "/mdc" #cWHITE " - Mobile Data Computer;\n\
                    " #cPROJECT "/accept" #cWHITE " - ������� �����;\n\
                    " #cPROJECT "/callsign" #cWHITE " - ���������� ����������;\n\
                    " #cPROJECT "/dcallsign" #cWHITE " - ������� ����������;\n\
                    " #cPROJECT "/frisk" #cWHITE " - ��������;\n\
                    " #cPROJECT "/hale" #cWHITE " - ����� �� �����;\n\
                    " #cPROJECT "/unhale" #cWHITE " - ���������� ����� �� �����;\n\
                    " #cPROJECT "/put" #cWHITE " - �������� � ��������� ������;\n\
                    " #cPROJECT "/cuff" #cWHITE " - ������ ���������;\n\
                    " #cPROJECT "/uncuff" #cWHITE " - ����� ���������;\n\
                    " #cPROJECT "/su" #cWHITE " - �������� � ������;\n\
                    " #cPROJECT "/unsu" #cWHITE " - ����� ������;\n\
                    " #cPROJECT "/taser" #cWHITE " - ��������������� ��������������;\n\
                    " #cPROJECT "/arrest" #cWHITE " - ����������;\n\
                    " #cPROJECT "/unarrest" #cWHITE " - ����� �����;\n\
                    " #cPROJECT "/ram" #cWHITE " - ������ ����� ���������\n");
                    
                if (fraction_id == FRACTION_SD)
                {
                    strcat(g_big_string,
                        "" #cPROJECT "/jail" #cWHITE " - �������� � ��������� ������;\n\
                        " #cPROJECT "/unjail" #cWHITE " - ��������� �� ��������� ������;\n\
                        " #cPROJECT "/setjail" #cWHITE " - �������� ����� ���������� � ������;"
                    );
                }
            }
            
            case FRACTION_FD:
            {
                strcat(g_big_string, 
                    "" #cPROJECT "/heal" #cWHITE " - �������� ������;\n\
                    " #cPROJECT "/fireshape" #cWHITE " - ������� �����;\n");
            }
            
            case FRACTION_NEWS:
            {
                strcat(g_big_string, 
                    "" #cPROJECT "/e" #cWHITE " - ����� ����;\n");
            }
            
            case FRACTION_NP:
            {
                strcat(g_big_string, 
                    "" #cPROJECT "/s(trobe)l(ight)" #cWHITE " - �����������;\n\
                    " #cPROJECT "/m" #cWHITE " - ����������������;\n\
                    " #cPROJECT "/callsign" #cWHITE " - ���������� ����������;\n\
                    " #cPROJECT "/dcallsign" #cWHITE " - ������� ����������;\n\
                    " #cPROJECT "/frisk" #cWHITE " - ��������;\n\
                    " #cPROJECT "/hale" #cWHITE " - ����� �� �����;\n\
                    " #cPROJECT "/unhale" #cWHITE " - ���������� ����� �� �����;\n\
                    " #cPROJECT "/put" #cWHITE " - �������� � ��������� ������;\n\
                    " #cPROJECT "/cuff" #cWHITE " - ������ ���������;\n\
                    " #cPROJECT "/uncuff" #cWHITE " - ����� ���������;\n\
                    " #cPROJECT "/arrest" #cWHITE " - ����������;\n\
                    " #cPROJECT "/unarrest" #cWHITE " - ����� �����;\n");
                    
            }
            
            case FRACTION_HOSPITAL:
            {
                strcat(g_big_string, 
                    "" #cPROJECT "/heal" #cWHITE " - �������� ������;\n");
            }
        }
    }
    
    Dialog_Open(
        playerid, 
        Dialog:PLAYER_MENU_HELP_COMMANDS_R, 
        DIALOG_STYLE_MSGBOX,
        inputtext, 
        g_big_string, 
        "�����", 
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
        "������� ����������", "\
        " #CI_DIALOG_INFO " ����� ���������� �� ������ ������� " #cPROJECT "Fury Stories" #cWHITE "!\n\
        ��� ������� ����������, ������� ������� ��������� �� �������.\n\
        \n\
        ��� ���� ����� ����� � ������, ����������� ������� �������������� \"H\".\n\
        �� ������ ���������� ��� ������ ���������, ��� ����� ����� ����� � ���� � ������ ������� \"N\".\n\
        ��� ����, ����� ����� ����������� ����� ����������� - /gps.\n\
        �� ��������� �������� � ������������ ����� ������ � ���� ������ - /help.\n\
        \n\
        � ��� ����� ������� ��������� �������, ������� ��������� �� ����� \"Start\".\n\
        �� �������� ���������� �������� ����� ���������� ��� ���������� �����, ��������� ��� ���������.\n\
        ����� � ������� ����� ����� ������������ � �� ������ ������.\n\
        ���������� �������� �������� � ���� ����� ������, ������ �� ������ ����� ���������.\n\
        ������ ��������� ������ �������� � ������ ����� ����� ���������� �� ���� �������� ��������� �����.\n\
        \n\
        ������� ������� � ������� �������� �� ������ ������� ����. ��� �����, ���������� �������� 2 ����, �\n\
        ����� �������� ������������ ����� � ����������� �� ���� ������������.\n\
        �� ������ ����������� ��� ��� ����� ������������� �����������, ������� ���������� 20% �� ����� ��������.\n\
        \n\
        �������� ����!",
        "�����",
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
    Dialog_Open(playerid, Dialog:PLAYER_MENU_HELP_JOB, DIALOG_STYLE_MSGBOX, "������", "\
        " #CI_DIALOG_INFO "��������� ������ �� ������� ������� � ��������.\n\n\
        ���� �� " #cGRAY "����������" #cWHITE " �����, �� �� ������ ����� �� �����������\n\
        " #cGOLD "������ ��������" #cWHITE " � �Fuber�.\n\
        \n\
        ��� �������� ���������� ��� ������ ������� � ���������� �� ���� ������ �������.\n\
        \n\
        ���� �� ��� " #cGRAY "������� ��� �����������" #cWHITE " �����, �� ����������� ������������ � " #cPROJECT"������� ���������" #cWHITE ".",
        "�����",
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
	    " #cWHITE "����� ���������\t" #cGRAY "%s\n \ 
	    " #cWHITE "��������� ���������\t" #cGRAY "%s",
		GetUserName(playerid),
		GetCharacterRPName(playerid)
	);
	
	Dialog_Open(playerid, Dialog:PLAYER_MENU_SETTINGS, DIALOG_STYLE_TABLIST, "���������",
		g_string,
		"�����", "�����" 
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

	strcat(g_big_string, #DEFAULT " �������\n\n");
	
	format:g_small_string("���:     			  " #cPROJECT "\t\t%s\n", user_data[playerid][u_name]);
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "����������� �����:     " #cPROJECT "\t\t\t%s\n", user_data[playerid][u_email]);
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "��������������:     	 " #cPROJECT "\t\t%i/3\n", user_data[playerid][u_warn]);
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "���� �����������:      " #cPROJECT "\t\t\t%02d/%02d/%04d\n", day, month, year);
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "VIP �������:      	 " #cPROJECT "\t\t\t%s\n", GetUserVipText(playerid));
	strcat(g_big_string, g_small_string);
	
	if (VIP_STARTER <= GetUserVip(playerid) <= VIP_ADVANCED)
	{
		format:g_small_string("" #cWHITE "���� �������� VIP:      	 " #cPROJECT "\t%d ����\n", GetUserVipEndDayCount(playerid));
		strcat(g_big_string, g_small_string);
	}
	else if (GetUserVip(playerid) == VIP_PRO)
	{
		format:g_small_string("" #cWHITE "���� �������� VIP:      	 " #cGOLD "\t��������\n", GetUserVipEndDayCount(playerid));
		strcat(g_big_string, g_small_string);
	}
	
	if (is_admin)
	{
		format:g_small_string("" #cWHITE "��������������� IP:      " #cPROJECT "\t\t%s\n", user_data[playerid][u_reg_ip]);
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("" #cWHITE "��������� IP:      " #cPROJECT "\t\t%s\n", user_data[playerid][u_last_ip]);
		strcat(g_big_string, g_small_string);
		
		format:g_small_string("" #cWHITE "������� IP:      	" #cPROJECT "\t\t%s\n", user_data[playerid][u_ip]);
		strcat(g_big_string, g_small_string);
	}
	
	strcat(g_big_string, "\n\n" #DEFAULT " ��������\n\n");
	
	format:g_small_string("" #cWHITE "���:     			  	 " #cPROJECT "\t%s\n", GetCharacterName(playerid));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "��� ���������:   	  	 " #cPROJECT "\t%s\n", (!character_data[playerid][c_sex]) ? ("�������") : ("�������"));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "�������� ������: 	  	 " #cPROJECT "\t" #cGREEN"$%d" #cWHITE "\n", GetCharacterMoney(playerid));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "���� � �����: 	 	 " #cPROJECT "\t\t" #cGREEN"$%d" #cWHITE "\n", GetCharacterBank(playerid));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "�����: 	 		 	 " #cPROJECT "\t" #cGREEN"$%d" #cWHITE "\n", GetCharacterCardBalance(playerid));
	strcat(g_big_string, g_small_string);
	
	if (GetCharacterCardStart(playerid) > 0)
	{
		format:g_small_string("" #cWHITE "����� �Start�: 	 	 " #cPROJECT "\t\t" #cGREEN"$%d" #cWHITE "\n", GetCharacterCardStart(playerid));
		strcat(g_big_string, g_small_string);
	}
	
	if (IsCreditCardExists(playerid))
	{
		gmtime(GetCreditDateSuccess(credit_data[playerid][credit_give_time]), year, month, day);
	
	    format:g_small_string("" #cWHITE "��������� �����: 	 	    " #cPROJECT "\t" #cGREEN"$%d" #cWHITE " (��������� " #cGREEN "$%d" #cWHITE " �� %02d.%02d.%d)\n", 
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
		strcat(g_string, "�����������");
	}
	else 
	{
		new findex = GetFractionMember(playerid);
		
		strcat(
			g_string, 
			GetFractionName(findex)
		);
	}
	
	format:g_small_string("" #cWHITE "�����������:         	  	" #cPROJECT "\t%s\n",
		g_string
	);
	
	strcat(g_big_string, g_small_string);
	

	clean:<g_string>;
	if (!IsFractionMember(playerid))
	{
		strcat(g_string, "�����������");
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
			strcat(g_string, "�����������");
		}
	}
	
	format:g_small_string("" #cWHITE "���������:       	  	" #cPROJECT "\t%s\n",
		g_string
	);
	
	strcat(g_big_string, g_small_string);
	
	clean:<g_string>;
	if (GetCrimeMember(playerid) == INVALID_PARAM)
	{
		strcat(g_string, "�����������");
	}
	else
	{
		strcat(g_string, GetCrimeName(playerid));
	}
	
	format:g_small_string("" #cWHITE "��������:				" #cPROJECT "%s\n",
		g_string
	);
	
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "�����: 	  		   	" #cPROJECT "%d\n", GetPlayerHousesCount(playerid));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "���������: 	  	   	" #cPROJECT "\t%d\n", GetPlayerPremisesCount(playerid));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "����������: 	  	   	" #cPROJECT "\t%d\n", GetPlayerVehiclesCount(playerid));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "��������: 	  	   	" #cPROJECT "\t%d\n", GetPlayerBusinessesCount(playerid));
	strcat(g_big_string, g_small_string);
	
	format:g_small_string("" #cWHITE "������: 	  	   		" #cPROJECT "%d\n", GetPlayerSitesCount(playerid));
	strcat(g_big_string, g_small_string);
	
    if (targetid == INVALID_PLAYER_ID)
    {
        Dialog_Open(
            playerid,
            Dialog:PLAYER_MENU_RETURN,
            DIALOG_STYLE_MSGBOX, 
            "����������", 
            g_big_string, 
            "�����", 
            "" 
        );
    }
    else
    {
        Dialog_Open(
            targetid,
            Dialog:NONE,
            DIALOG_STYLE_MSGBOX, 
            "����������", 
            g_big_string, 
            "�����", 
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