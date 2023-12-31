/*!
	@brief ��������� ��� ������� ������
	@author Found (evg.savosin)
	@date 16.12.2016, update 30.01.2018
*/

// Defines
#define GetSiteId(%0)					(site_data[%0][s_id])

#define IsSiteShowed(%0)				(GetPVarInt(%0, "Site:States"))

#define DIALOG_SITE_DOMAIN 				"\
	" #ERROR " ������\n\n\
	�� ������� �������� ������ � �����.\n\
	�� ����� �������� ����� �����.\
"

#define DIALOG_SITE_MANAGE				" \ 
	���������� � �����\n \
	���������� ������\n \
	�������� �������\n \
	������� �� ����\n \
	������� ����\
"

#define DIALOG_SITE_HOUSE				" \
	������ �����\n \
	����� ����� � ���� ������\n \
	������� ������� ���������\n \
	������� ������� ��������� ������\n \
	������� ����� �����\
"

#define DIALOG_SITE_PREMISE				" \
	������ ���������\n \
	����� ��������� � ���� ������\n \
	������� ������� ���������\n \
	������� ������� ��������� ������\n \
	������� ����� ���������\
"

#define NUMBER_OVH						(653	)

// �������
enum
{
	SITE_INVALID = INVALID_PARAM,
	SITE_GOG,
	SITE_CUSTOM,
};

// Action
enum 
{
	SITE_ACTION_NONE = 0,
	SITE_ACTION_CREATE,
	SITE_ACTION_EDIT
};

new const site_domains					[][] = 
{
	"us", 
	"com", 
	"net", 
	"info", 
	"org", 
	"jobs", 
	"name", 
	"biz",
	"pro", 
	"xxx",
	"onion"
};

enum E_SITE_TEMPLATES
{
	st_name								[	32	],
	bool: st_darknet
};

new const site_templates				[	][	E_SITE_TEMPLATES	] =
{
	{"������ #1 (��������)", false},
	{"������ #2", false},
	{"������ #3 (������� ����)", false},
	{"������ #4", true}
};
	
enum E_SITE_COLOR
{
	sc_color_int,
	sc_color							[	7	],
	sc_color_name						[	16 	],
};
	
new const site_colors					[	][	E_SITE_COLOR	] =
{
	{0x000000FF, "000000", "������"},
	{0xe49608FF, "e49608", "���������"},
	{0xc71717FF, "c71717", "�������"},
	{0x5f1616FF, "5f1616", "Ҹ���-�������"},
	{0x02dc02FF, "02dc02", "����-������"},
	{0x0d982bFF, "0d982b", "������"},
	{0x1a5026FF, "1a5026", "Ҹ���-������"},
	{0x179cd8FF, "179cd8", "�������"},
	{0x244da9FF, "244da9", "�����"},
	{0x344771FF, "344771", "Ҹ���-�����"},
	{0x6139a7FF, "6139a7", "����������"},
	{0xdc278bFF, "dc278b", "�������"},
	{0x616161FF, "616161", "�����"},
	{0xc39c0cFF, "c39c0c", "�������"},
	{0x29a57dFF, "29a57d", "���������"},
	{0x795548FF, "795548", "����������"},
	{0x8bc34aFF, "8bc34a", "���������"}
};

enum E_SITE_FAVORITE
{
	sf_id,
	sf_address					[	MAX_SITE_ADDRESS	],
	sf_name						[	MAX_SITE_NAME		]
};

enum E_SITE_DATA 
{
	s_id, 
	
	s_character_id,
	
	s_address					[		MAX_SITE_ADDRESS	],
	s_template,
	s_color,
	s_name						[		MAX_SITE_NAME		],
	s_slogan					[		32		],
	s_description				[		128		],
	
	s_name_page_1				[		MAX_SITE_PAGE_NAME		],
	s_name_page_2				[		MAX_SITE_PAGE_NAME		],
	s_name_page_3				[		MAX_SITE_PAGE_NAME		],
	s_name_page_4				[		MAX_SITE_PAGE_NAME		],
	
	s_desc_page_1				[		MAX_SITE_PAGE_DESC		],
	s_desc_page_2 				[		MAX_SITE_PAGE_DESC		],
	s_desc_page_3 				[		MAX_SITE_PAGE_DESC		],
	s_desc_page_4 				[		MAX_SITE_PAGE_DESC		],
	
	bool: s_is_darknet,
	
	s_rent_time, // ������
	s_created_time
};

new site_data					[		MAX_SITES			][		E_SITE_DATA	  	],
	site_fav_select				[		MAX_PLAYERS			][	MAX_SITE_FAVORITES	][	E_SITE_FAVORITE	],
	
	player_site					[		MAX_PLAYERS			][	MAX_PLAYER_SITES	];

Clear:site_data(index)
{
	/// Integer
	site_data[index][s_id] = 
	site_data[index][s_character_id] = 
	site_data[index][s_rent_time] = 
	site_data[index][s_color] =
	site_data[index][s_created_time] = 
	site_data[index][s_template] = 0;
	
	/// String
	site_data[index][s_address][0] = 
	site_data[index][s_name][0] = 
	site_data[index][s_slogan][0] =
	site_data[index][s_description][0] = 
	
	site_data[index][s_name_page_1][0] = 
	site_data[index][s_name_page_2][0] = 
	site_data[index][s_name_page_3][0] = 
	site_data[index][s_name_page_4][0] =
	
	site_data[index][s_desc_page_1][0] = 
	site_data[index][s_desc_page_2][0] = 
	site_data[index][s_desc_page_3][0] = 
	site_data[index][s_desc_page_4][0] = EOS;
	
	/// Bool
	site_data[index][s_is_darknet] = false;
}

Clear:site_fav_select(playerid)
{
	for (new i; i < MAX_SITE_FAVORITES; i++)
	{
		site_fav_select[playerid][i][sf_id] = 0;
		
		site_fav_select[playerid][i][sf_address][0] =
		site_fav_select[playerid][i][sf_name][0] = EOS;
	}
}

Clear:player_site(playerid)
{
	player_site[playerid][0] =
	player_site[playerid][1] =
	player_site[playerid][2] = INVALID_PARAM;
}

Create:site_data(playerid, index)
{
	Clear:site_data(index);
	
	ReplaceSiteDataPVar(playerid, index);
	
	site_data[index][s_character_id] = GetCharacterId(playerid);
	site_data[index][s_rent_time] = gettime() + (60 * 60 * 24 * 7);
	site_data[index][s_created_time] = gettime();
	
	Clear:site_edit_pvar(playerid);
	
	format:g_big_string("\
		INSERT INTO " #__SITES " (\
			s_character_id, \
			s_address, \
			s_template, \
			s_color, \
			s_name, \
			s_slogan, \
			s_description, \
			s_name_page_1, \
			s_name_page_2, \
			s_name_page_3, \
			s_name_page_4, \
			s_desc_page_1, \
			s_desc_page_2, \
			s_desc_page_3, \
			s_desc_page_4, \
			s_is_darknet, \
			s_rent_time, \
			s_created_time \
		) VALUES (\
			%i, \
			'%q', \
			%i, \
			%i, \
			'%q', \
			'%q', \
			'%q', \
			'%q', \
			'%q', \
			'%q', \
			'%q', \
			'%q', \
			'%q', \
			'%q', \
			'%q', \
			%i, \
			%i, \ 
			%i)",
		site_data[index][s_character_id],
		site_data[index][s_address],
		site_data[index][s_template],
		site_data[index][s_color],
		site_data[index][s_name],
		site_data[index][s_slogan],
		site_data[index][s_description],
		
		site_data[index][s_name_page_1],
		site_data[index][s_name_page_2],
		site_data[index][s_name_page_3],
		site_data[index][s_name_page_4],
		
		site_data[index][s_desc_page_1],
		site_data[index][s_desc_page_2],
		site_data[index][s_desc_page_3],
		site_data[index][s_desc_page_4],
		
		site_data[index][s_is_darknet],
		
		site_data[index][s_rent_time],
		site_data[index][s_created_time]
	);
	
	mysql_tquery(db, g_big_string, "OnSiteCreate", "ii", playerid, index);
}

Update:site_data(playerid, index)
{
	if (!IsUserAllowQuery(playerid))
	{
		return;
	}
	
	ReplaceSiteDataPVar(playerid, index);
	
	Clear:site_edit_pvar(playerid);
	
	format:g_big_string("\
		UPDATE " #__SITES " \
		SET \
			s_rent_time = %i, \
			s_address = '%q', \
			s_template = %i, \
			s_color = %i, \
			s_name = '%q', \
			s_slogan = '%q', \
			s_description = '%q', \
			s_is_darknet = %i \
		WHERE \
			s_id = %i",
		site_data[index][s_rent_time],
		site_data[index][s_address],
		site_data[index][s_template],
		site_data[index][s_color],
		site_data[index][s_name],
		site_data[index][s_slogan],
		site_data[index][s_description],
		site_data[index][s_is_darknet],
		GetSiteId(index)
	);
	
	mysql_pquery(db, g_big_string);
	
	format:g_big_string("\
		UPDATE " #__SITES " \
		SET \
			s_name_page_1 = '%q', \ 
			s_name_page_2 = '%q', \ 
			s_name_page_3 = '%q', \ 
			s_name_page_4 = '%q' \ 
		WHERE \
			s_id = %i",
		site_data[index][s_name_page_1],
		site_data[index][s_name_page_2],
		site_data[index][s_name_page_3],
		site_data[index][s_name_page_4],
		GetSiteId(index)
	);
	
	mysql_pquery(db, g_big_string);
	
	format:g_big_string("\
		UPDATE " #__SITES " \
		SET \
			s_name_page_1 = '%q', \ 
			s_name_page_2 = '%q' \ 
		WHERE \
			s_id = %i",
		site_data[index][s_desc_page_1],
		site_data[index][s_desc_page_2],
		GetSiteId(index)
	);
	
	mysql_pquery(db, g_big_string);
	
	format:g_big_string("\
		UPDATE " #__SITES " \
		SET \
			s_name_page_3 = '%q', \ 
			s_name_page_4 = '%q' \ 
		WHERE \
			s_id = %i",
		site_data[index][s_desc_page_3],
		site_data[index][s_desc_page_4],
		GetSiteId(index)
	);
	
	mysql_pquery(db, g_big_string, "OnSiteUpdate", "d", playerid);
	
	SetUserAllowQuery(playerid, false);
}

function OnSiteUpdate(playerid)
{
	SetUserAllowQuery(playerid, true);
	return 1;
}

function OnSiteCreate(playerid, index)
{
	site_data[index][s_id] = cache_insert_id();
	
	GiveSiteOwner(playerid, index);
	
	ShowPlayerDialog(playerid, INVALID_DIALOG_ID, DIALOG_STYLE_MSGBOX, " ", "\
		" #DEFAULT " ����������\n\n\
		�� ������� ������� ����.\n\
		�� �������� ������� ��������� ����� �� �������� ����-�����.\n\
		������� ��� ����� � ������-�����.",
		"�������", ""
	);
	
	return 1;
}

Remove:site_data(playerid, index)
{
	format:g_string("DELETE FROM " #__SITES " WHERE s_id = %i", site_data[index][s_id]);
	mysql_pquery(db, g_string);
	
	if (playerid != INVALID_PLAYER_ID)
	{
		RemoveSiteOwner(playerid, index);
	}
	
	Clear:site_data(index);
}