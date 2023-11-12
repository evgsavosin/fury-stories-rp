/*!
	@brief Заголовок для системы объявлений
	@author Found (evg.savosin)
	@date 16.12.2016, update 30.01.2018
*/

#define DIALOG_ADVERT_CAT	"\
	" #cGRAY "Выберите категорию:" #cWHITE "\n \
	Жилищное помещение\n \
	Транспортное средство\n \
	Коммерческая недвижимость\n \
	Другое"

#define DIALOG_ADVERT_TYPE 	 "\
	" #cGRAY "Выберите тип объявления: " #cWHITE "\n \
	Продам\n \
	Куплю"

enum
{
	TYPE_ADV_NONE = 0,
	TYPE_ADV_BUY,
	TYPE_ADV_SELL
};

new const site_adv_type			[	][	] =
{
	"",
	"Продам",
	"Куплю"
};

new const site_adv_cat			[	][	] = 
{
	"Жилищное помещение",
	"Транспортное средства",
	"Коммерческая недвижимость",
	"Другое"
};

enum E_SITE_ADVERTS
{
	ad_id,
	ad_number,
	ad_price,
	ad_category,
	ad_type,
	ad_text						[	128		],
	ad_created_time
};

new site_adv_select				[		MAX_PLAYERS			][	MAX_ADVERTS	+ 2][	E_SITE_ADVERTS	];

Clear:site_adv_select(playerid)
{
	for (new i; i < MAX_ADVERTS; i++)
	{
		site_adv_select[playerid][i][ad_price] =
		site_adv_select[playerid][i][ad_created_time] =
		site_adv_select[playerid][i][ad_number] =
		site_adv_select[playerid][i][ad_id] = 0;
		
		site_adv_select[playerid][i][ad_text][0] = EOS;
	}
}