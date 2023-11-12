/*!
	@brief Заголовок системы лицензий
	@author Found (evg.savosin)
	@date 27.04.2018
*/

enum E_LICENSES_INFO
{
	li_start,
	li_drive = li_start,
	li_boat,
	li_fly,
	li_weapon,
	li_end
};

new const license_info [][] = 
{
	{"Водительское удостоверение"},
	{"Сертификат судоводителя"},
	{"Лицензия пилота"},
	{"Разрешение на ношение оружия"}
};

enum E_LICENSE_DATA
{
	l_id,
	l_gave_time,
	l_gave_name			[	MAX_PLAYER_NAME		],
	l_take_time,
	l_take_name			[	MAX_PLAYER_NAME		]
};

new license_data		[	MAX_PLAYERS			][	E_LICENSES_INFO	][	E_LICENSE_DATA	];


Clear:license_data(playerid, E_LICENSES_INFO: type)
{
	license_data[playerid][type][l_id] =
	license_data[playerid][type][l_gave_time] =
	license_data[playerid][type][l_take_time] = 0;
	
	license_data[playerid][type][l_gave_name][0] =
	license_data[playerid][type][l_take_name][0] = EOS;
}

Clear:all_license_data(playerid)
{
	for (new E_LICENSES_INFO: i = li_start; i < li_end; i++)
	{
		Clear:license_data(playerid, i);
	}
}