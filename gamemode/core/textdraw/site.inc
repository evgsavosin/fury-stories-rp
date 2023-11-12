/*!
	@brief Текстдравы сайта
	@author Found (evg.savosin)
	@date 25.11.2019
*/

// Defines
#define TD_SITE_TEMPLATE_1				(11)
#define TD_SITE_TEMPLATE_2				(12)
#define TD_SITE_TEMPLATE_3				(11)

#define TD_DARK_TEMPLATE_1				(11)

// Variables
new Text: td_browser					[	7	],
	Text: td_browser_tor,
	Text: td_browser_black,

	Text: td_site_gog					[	33  ],
	Text: td_site_template_1			[	7 	],
	Text: td_site_template_2			[	4 	],
	Text: td_site_template_3			[	3 	],
	
	Text: td_dark_template_1,
	
	PlayerText: ptd_site_template_1		[	MAX_PLAYERS 	][	TD_SITE_TEMPLATE_1 	],
	PlayerText: ptd_site_template_2		[	MAX_PLAYERS 	][ TD_SITE_TEMPLATE_2 	],
	PlayerText: ptd_site_template_3		[	MAX_PLAYERS 	][ TD_SITE_TEMPLATE_3 ],
	
	PlayerText: ptd_dark_template_1		[	MAX_PLAYERS 	][ TD_DARK_TEMPLATE_1 	],
	
	PlayerText: ptd_address_line		[	MAX_PLAYERS		];

	
// Functions
TD_Global_Site()
{
	/*!	
		@brief Ѕраузер
	*/
	
	td_browser[0] = TextDrawCreate(160.217666, 136.916687, "box"); // browser-back 
	TextDrawLetterSize(td_browser[0], 0.000000, 25.294115);
	TextDrawTextSize(td_browser[0], 477.100000, 0.000000);
	TextDrawAlignment(td_browser[0], 1);
	TextDrawColor(td_browser[0], -1);
	TextDrawUseBox(td_browser[0], 1);
	TextDrawBoxColor(td_browser[0], -1);
	TextDrawSetOutline(td_browser[0], 0);
	TextDrawBackgroundColor(td_browser[0], 255);
	TextDrawFont(td_browser[0], 1);
	TextDrawSetProportional(td_browser[0], 1);
	TextDrawSetShadow(td_browser[0], 0);

	td_browser[1] = TextDrawCreate(160.217666, 136.916641, "box"); // browser-panel 
	TextDrawLetterSize(td_browser[1], 0.000000, 1.225831);
	TextDrawTextSize(td_browser[1], 477.100000, 0.000000);
	TextDrawAlignment(td_browser[1], 1);
	TextDrawColor(td_browser[1], -1);
	TextDrawUseBox(td_browser[1], 1);
	TextDrawBoxColor(td_browser[1], 188);
	TextDrawSetOutline(td_browser[1], 0);
	TextDrawBackgroundColor(td_browser[1], 255);
	TextDrawFont(td_browser[1], 1);
	TextDrawSetProportional(td_browser[1], 1);
	TextDrawSetShadow(td_browser[1], 0);

	td_browser[2] = TextDrawCreate(465.201354, 134.899963, "LD_BEAT:chit"); // browser-elem-1 
	TextDrawLetterSize(td_browser[2], 0.000000, 0.000000);
	TextDrawTextSize(td_browser[2], 13.000000, 15.000000);
	TextDrawAlignment(td_browser[2], 1);
	TextDrawColor(td_browser[2], -2147483543);
	TextDrawSetOutline(td_browser[2], 0);
	TextDrawBackgroundColor(td_browser[2], 255);
	TextDrawFont(td_browser[2], 4);
	TextDrawSetProportional(td_browser[2], 0);
	TextDrawSetShadow(td_browser[2], 0);
	TextDrawSetSelectable(td_browser[2], true);
	
	td_browser[3] = TextDrawCreate(468.266632, 135.749954, "X"); // browser-elem-2 
	TextDrawLetterSize(td_browser[3], 0.279529, 1.244163);
	TextDrawAlignment(td_browser[3], 1);
	TextDrawColor(td_browser[3], -1061109587);
	TextDrawSetOutline(td_browser[3], 0);
	TextDrawBackgroundColor(td_browser[3], 255);
	TextDrawFont(td_browser[3], 2);
	TextDrawSetProportional(td_browser[3], 1);
	TextDrawSetShadow(td_browser[3], 0);
	
	td_browser[4] = TextDrawCreate(162.570587, 137.266799, "< >"); // browser-arrows 
	TextDrawLetterSize(td_browser[4], 0.249410, 1.179998);
	TextDrawTextSize(td_browser[4], 180.699981, 7.000000);
	TextDrawAlignment(td_browser[4], 1);
	TextDrawColor(td_browser[4], -130);
	TextDrawSetOutline(td_browser[4], 0);
	TextDrawBackgroundColor(td_browser[4], 255);
	TextDrawFont(td_browser[4], 2);
	TextDrawSetProportional(td_browser[4], 1);
	TextDrawSetShadow(td_browser[4], 0);
	TextDrawSetSelectable(td_browser[4], true);
	
	td_browser[5] = TextDrawCreate(452.800598, 134.899963, "LD_BEAT:chit"); // 
	TextDrawLetterSize(td_browser[5], 0.000000, 0.000000);
	TextDrawTextSize(td_browser[5], 13.000000, 15.000000);
	TextDrawAlignment(td_browser[5], 1);
	TextDrawColor(td_browser[5], -5963734);
	TextDrawSetShadow(td_browser[5], 0);
	TextDrawSetOutline(td_browser[5], 0);
	TextDrawBackgroundColor(td_browser[5], 255);
	TextDrawFont(td_browser[5], 4);
	TextDrawSetProportional(td_browser[5], 0);
	TextDrawSetShadow(td_browser[5], 0);
	TextDrawSetSelectable(td_browser[5], true);

	td_browser[6] = TextDrawCreate(456.588195, 137.199981, "F"); // 
	TextDrawLetterSize(td_browser[6], 0.295058, 1.045833);
	TextDrawAlignment(td_browser[6], 1);
	TextDrawColor(td_browser[6], -1061109606);
	TextDrawSetShadow(td_browser[6], 0);
	TextDrawSetOutline(td_browser[6], 0);
	TextDrawBackgroundColor(td_browser[6], 255);
	TextDrawFont(td_browser[6], 2);
	TextDrawSetProportional(td_browser[6], 1);
	TextDrawSetShadow(td_browser[6], 0);
	
	
	td_browser_tor = TextDrawCreate(318.535064, 127.416671, "TOR"); // 
	TextDrawLetterSize(td_browser_tor, 0.213174, 0.695833);
	TextDrawTextSize(td_browser_tor, -10.000000, 317.000000);
	TextDrawAlignment(td_browser_tor, 2);
	TextDrawColor(td_browser_tor, -1);
	TextDrawUseBox(td_browser_tor, 1);
	TextDrawBoxColor(td_browser_tor, -2139062017);
	TextDrawSetShadow(td_browser_tor, 0);
	TextDrawSetOutline(td_browser_tor, 0);
	TextDrawBackgroundColor(td_browser_tor, 255);
	TextDrawFont(td_browser_tor, 1);
	TextDrawSetProportional(td_browser_tor, 1);
	TextDrawSetShadow(td_browser_tor, 0);
	
	td_browser_black = TextDrawCreate(160.217666, 151.00000, "box"); // 
	TextDrawLetterSize(td_browser_black, 0.000000, 25.616914);
	TextDrawTextSize(td_browser_black, 477.100000, 0.000000);
	//TextDrawTextSize(td_browser_black, 477.030029, 168.000000);
	TextDrawAlignment(td_browser_black, 1);
	TextDrawColor(td_browser_black, -1);
	TextDrawUseBox(td_browser_black, 1);
	TextDrawBoxColor(td_browser_black, 240);
	TextDrawSetShadow(td_browser_black, 0);
	TextDrawSetOutline(td_browser_black, 0);
	TextDrawBackgroundColor(td_browser_black, 255);
	TextDrawFont(td_browser_black, 1);
	TextDrawSetProportional(td_browser_black, 1);
	TextDrawSetShadow(td_browser_black, 0);

	/*!	
		
		@brief GOG.COM
		
	*/
	
	
	td_site_gog[0] = TextDrawCreate(160.308761, 151.000, "box"); // 
	TextDrawLetterSize(td_site_gog[0], 0.000000, 4.258820);
	TextDrawTextSize(td_site_gog[0], 477.000000, 0.000000);
	TextDrawAlignment(td_site_gog[0], 1);
	TextDrawColor(td_site_gog[0], -1);
	TextDrawUseBox(td_site_gog[0], 1);
	TextDrawBoxColor(td_site_gog[0], -1378294017);
	TextDrawSetShadow(td_site_gog[0], 0);
	TextDrawSetOutline(td_site_gog[0], 0);
	TextDrawBackgroundColor(td_site_gog[0], 255);
	TextDrawFont(td_site_gog[0], 1);
	TextDrawSetProportional(td_site_gog[0], 1);
	TextDrawSetShadow(td_site_gog[0], 0);

	td_site_gog[1] = TextDrawCreate(199.647079, 161.999969, "GOG"); // 
	TextDrawLetterSize(td_site_gog[1], 0.437175, 1.763332);
	TextDrawAlignment(td_site_gog[1], 1);
	TextDrawColor(td_site_gog[1], -662699777);
	TextDrawSetShadow(td_site_gog[1], 0);
	TextDrawSetOutline(td_site_gog[1], 0);
	TextDrawBackgroundColor(td_site_gog[1], 255);
	TextDrawFont(td_site_gog[1], 1);
	TextDrawSetProportional(td_site_gog[1], 1);
	TextDrawSetShadow(td_site_gog[1], 0);

	td_site_gog[2] = TextDrawCreate(240.741012, 165.499969, "Start writing..."); // 
	TextDrawLetterSize(td_site_gog[2], 0.237176, 1.051666);
	TextDrawTextSize(td_site_gog[2], 408.800537, 20.000000);
	TextDrawAlignment(td_site_gog[2], 1);
	TextDrawColor(td_site_gog[2], -1);
	TextDrawUseBox(td_site_gog[2], 1);
	TextDrawBoxColor(td_site_gog[2], -2139062017);
	TextDrawSetShadow(td_site_gog[2], 0);
	TextDrawSetOutline(td_site_gog[2], 0);
	TextDrawBackgroundColor(td_site_gog[2], 255);
	TextDrawFont(td_site_gog[2], 1);
	TextDrawSetProportional(td_site_gog[2], 1);
	TextDrawSetShadow(td_site_gog[2], 0);
	TextDrawSetSelectable(td_site_gog[2], true);

	td_site_gog[3] = TextDrawCreate(413.132476, 165.283386, "Search"); // 
	TextDrawLetterSize(td_site_gog[3], 0.220232, 1.098332);
	TextDrawTextSize(td_site_gog[3], 437.603027, 0.000000);
	TextDrawAlignment(td_site_gog[3], 1);
	TextDrawColor(td_site_gog[3], -1);
	TextDrawUseBox(td_site_gog[3], 1);
	TextDrawBoxColor(td_site_gog[3], 1672472319);
	TextDrawSetShadow(td_site_gog[3], 0);
	TextDrawSetOutline(td_site_gog[3], 0);
	TextDrawBackgroundColor(td_site_gog[3], 255);
	TextDrawFont(td_site_gog[3], 1);
	TextDrawSetProportional(td_site_gog[3], 1);
	TextDrawSetShadow(td_site_gog[3], 0);

	td_site_gog[4] = TextDrawCreate(199.176513, 195.833374, "FEATURED SITES:"); // 
	TextDrawLetterSize(td_site_gog[4], 0.342586, 1.302497);
	TextDrawAlignment(td_site_gog[4], 1);
	TextDrawColor(td_site_gog[4], -1061109505);
	TextDrawSetShadow(td_site_gog[4], 0);
	TextDrawSetOutline(td_site_gog[4], 0);
	TextDrawBackgroundColor(td_site_gog[4], 255);
	TextDrawFont(td_site_gog[4], 1);
	TextDrawSetProportional(td_site_gog[4], 1);
	TextDrawSetShadow(td_site_gog[4], 0);

	td_site_gog[5] = TextDrawCreate(199.791046, 215.949996, "LD_SPAC:white"); // Click arthouse
	TextDrawLetterSize(td_site_gog[5], 0.000000, 0.000000);
	TextDrawTextSize(td_site_gog[5], 87.000000, 45.000000);
	TextDrawAlignment(td_site_gog[5], 1);
	TextDrawColor(td_site_gog[5], -1159351297);
	TextDrawSetShadow(td_site_gog[5], 0);
	TextDrawSetOutline(td_site_gog[5], 0);
	TextDrawBackgroundColor(td_site_gog[5], 255);
	TextDrawFont(td_site_gog[5], 4);
	TextDrawSetProportional(td_site_gog[5], 0);
	TextDrawSetShadow(td_site_gog[5], 0);
	TextDrawSetSelectable(td_site_gog[5], true);

	td_site_gog[6] = TextDrawCreate(207.465057, 230.533233, "AGENCY"); // 
	TextDrawLetterSize(td_site_gog[6], 0.148233, 0.742498);
	TextDrawAlignment(td_site_gog[6], 1);
	TextDrawColor(td_site_gog[6], 1804992767);
	TextDrawSetShadow(td_site_gog[6], 0);
	TextDrawSetOutline(td_site_gog[6], 0);
	TextDrawBackgroundColor(td_site_gog[6], 255);
	TextDrawFont(td_site_gog[6], 1);
	TextDrawSetProportional(td_site_gog[6], 1);
	TextDrawSetShadow(td_site_gog[6], 0);

	td_site_gog[11] = TextDrawCreate(207.176544, 218.583282, "ESTATE"); // 
	TextDrawLetterSize(td_site_gog[11], 0.349646, 1.582499);
	TextDrawAlignment(td_site_gog[11], 1);
	TextDrawColor(td_site_gog[11], 8388863);
	TextDrawSetShadow(td_site_gog[11], 0);
	TextDrawSetOutline(td_site_gog[11], 0);
	TextDrawBackgroundColor(td_site_gog[11], 255);
	TextDrawFont(td_site_gog[11], 1);
	TextDrawSetProportional(td_site_gog[11], 1);
	TextDrawSetShadow(td_site_gog[11], 0);

	td_site_gog[12] = TextDrawCreate(208.008880, 246.683288, "www.estateagency.com"); // 
	TextDrawLetterSize(td_site_gog[12], 0.117173, 0.654999);
	TextDrawAlignment(td_site_gog[12], 1);
	TextDrawColor(td_site_gog[12], -2139062017);
	TextDrawSetShadow(td_site_gog[12], 0);
	TextDrawSetOutline(td_site_gog[12], 0);
	TextDrawBackgroundColor(td_site_gog[12], 255);
	TextDrawFont(td_site_gog[12], 2);
	TextDrawSetProportional(td_site_gog[12], 1);
	TextDrawSetShadow(td_site_gog[12], 0);

	td_site_gog[13] = TextDrawCreate(299.085174, 215.949951, "LD_SPAC:white"); // Click avders
	TextDrawLetterSize(td_site_gog[13], 0.000000, 0.000000);
	TextDrawTextSize(td_site_gog[13], 87.000000, 45.000000);
	TextDrawAlignment(td_site_gog[13], 1);
	TextDrawColor(td_site_gog[13], -1378294017);
	TextDrawSetShadow(td_site_gog[13], 0);
	TextDrawSetOutline(td_site_gog[13], 0);
	TextDrawBackgroundColor(td_site_gog[13], 255);
	TextDrawFont(td_site_gog[13], 4);
	TextDrawSetProportional(td_site_gog[13], 0);
	TextDrawSetShadow(td_site_gog[13], 0);
	TextDrawSetSelectable(td_site_gog[13], true);

	td_site_gog[14] = TextDrawCreate(304.991607, 217.583236, "ADVERTS"); // 
	TextDrawLetterSize(td_site_gog[14], 0.437175, 1.763332);
	TextDrawAlignment(td_site_gog[14], 1);
	TextDrawColor(td_site_gog[14], -662699777);
	TextDrawSetShadow(td_site_gog[14], 0);
	TextDrawSetOutline(td_site_gog[14], 0);
	TextDrawBackgroundColor(td_site_gog[14], 255);
	TextDrawFont(td_site_gog[14], 1);
	TextDrawSetProportional(td_site_gog[14], 1);
	TextDrawSetShadow(td_site_gog[14], 0);

	td_site_gog[15] = TextDrawCreate(306.000061, 231.183547, "BUY? TO SELL? YOUR ADS"); // 
	TextDrawLetterSize(td_site_gog[15], 0.142116, 0.678332);
	TextDrawAlignment(td_site_gog[15], 1);
	TextDrawColor(td_site_gog[15], -1300954881);
	TextDrawSetShadow(td_site_gog[15], 0);
	TextDrawSetOutline(td_site_gog[15], 0);
	TextDrawBackgroundColor(td_site_gog[15], 255);
	TextDrawFont(td_site_gog[15], 1);
	TextDrawSetProportional(td_site_gog[15], 1);
	TextDrawSetShadow(td_site_gog[15], 0);

	td_site_gog[16] = TextDrawCreate(306.020599, 245.433105, "www.ad.gog.com"); // 
	TextDrawLetterSize(td_site_gog[16], 0.117173, 0.654999);
	TextDrawAlignment(td_site_gog[16], 1);
	TextDrawColor(td_site_gog[16], -2139062017);
	TextDrawSetShadow(td_site_gog[16], 0);
	TextDrawSetOutline(td_site_gog[16], 0);
	TextDrawBackgroundColor(td_site_gog[16], 255);
	TextDrawFont(td_site_gog[16], 2);
	TextDrawSetProportional(td_site_gog[16], 1);
	TextDrawSetShadow(td_site_gog[16], 0);

	td_site_gog[17] = TextDrawCreate(199.815231, 274.900360, "LD_SPAC:white"); // Click bank
	TextDrawLetterSize(td_site_gog[17], 0.000000, 0.000000);
	TextDrawTextSize(td_site_gog[17], 87.000000, 45.000000);
	TextDrawAlignment(td_site_gog[17], 1);
	TextDrawColor(td_site_gog[17], -2147483442);
	TextDrawSetShadow(td_site_gog[17], 0);
	TextDrawSetOutline(td_site_gog[17], 0);
	TextDrawBackgroundColor(td_site_gog[17], 255);
	TextDrawFont(td_site_gog[17], 4);
	TextDrawSetProportional(td_site_gog[17], 0);
	TextDrawSetShadow(td_site_gog[17], 0);
	TextDrawSetSelectable(td_site_gog[17], true);

	td_site_gog[18] = TextDrawCreate(209.462219, 275.933349, "LS Bank"); // 
	TextDrawLetterSize(td_site_gog[18], 0.437175, 1.763332);
	TextDrawAlignment(td_site_gog[18], 1);
	TextDrawColor(td_site_gog[18], -1);
	TextDrawSetShadow(td_site_gog[18], 0);
	TextDrawSetOutline(td_site_gog[18], 0);
	TextDrawBackgroundColor(td_site_gog[18], 255);
	TextDrawFont(td_site_gog[18], 1);
	TextDrawSetProportional(td_site_gog[18], 1);
	TextDrawSetShadow(td_site_gog[18], 0);
	
	td_site_gog[19] = TextDrawCreate(210.194641, 290.549804, "YOUR MONEY HERE"); // 
	TextDrawLetterSize(td_site_gog[19], 0.133175, 0.654999);
	TextDrawAlignment(td_site_gog[19], 1);
	TextDrawColor(td_site_gog[19], -1061109505);
	TextDrawSetShadow(td_site_gog[19], 0);
	TextDrawSetOutline(td_site_gog[19], 0);
	TextDrawBackgroundColor(td_site_gog[19], 255);
	TextDrawFont(td_site_gog[19], 1);
	TextDrawSetProportional(td_site_gog[19], 1);
	TextDrawSetShadow(td_site_gog[19], 0);

	td_site_gog[20] = TextDrawCreate(209.909042, 307.016754, "www.lsbank.com"); // 
	TextDrawLetterSize(td_site_gog[20], 0.117173, 0.654999);
	TextDrawAlignment(td_site_gog[20], 1);
	TextDrawColor(td_site_gog[20], -1061109505);
	TextDrawSetShadow(td_site_gog[20], 0);
	TextDrawSetOutline(td_site_gog[20], 0);
	TextDrawBackgroundColor(td_site_gog[20], 255);
	TextDrawFont(td_site_gog[20], 2);
	TextDrawSetProportional(td_site_gog[20], 1);
	TextDrawSetShadow(td_site_gog[20], 0);

	td_site_gog[21] = TextDrawCreate(299.052185, 274.317016, "LD_SPAC:white"); // Click cnn
	TextDrawLetterSize(td_site_gog[21], 0.000000, 0.000000);
	TextDrawTextSize(td_site_gog[21], 87.000000, 45.000000);
	TextDrawAlignment(td_site_gog[21], 1);
	TextDrawColor(td_site_gog[21], 0xEAF6FFFF);
	TextDrawSetShadow(td_site_gog[21], 0);
	TextDrawSetOutline(td_site_gog[21], 0);
	TextDrawBackgroundColor(td_site_gog[21], 255);
	TextDrawFont(td_site_gog[21], 4);
	TextDrawSetProportional(td_site_gog[21], 0);
	TextDrawSetShadow(td_site_gog[21], 0);
	TextDrawSetSelectable(td_site_gog[21], true);

	td_site_gog[22] = TextDrawCreate(305.882690, 276.033477, "LS Portal"); // 
	TextDrawLetterSize(td_site_gog[22], 0.437175, 1.763332);
	TextDrawAlignment(td_site_gog[22], 1);
	TextDrawColor(td_site_gog[22], 0x0E2941FF);
	TextDrawSetShadow(td_site_gog[22], 0);
	TextDrawSetOutline(td_site_gog[22], 0);
	TextDrawBackgroundColor(td_site_gog[22], 255);
	TextDrawFont(td_site_gog[22], 1);
	TextDrawSetProportional(td_site_gog[22], 1);
	TextDrawSetShadow(td_site_gog[22], 0);

	td_site_gog[23] = TextDrawCreate(307.563171, 291.133178, "CITY PORTAL WITH~n~ORGANIZATIONS"); // 
	TextDrawLetterSize(td_site_gog[23], 0.146351, 0.701665);
	TextDrawAlignment(td_site_gog[23], 1);
	TextDrawColor(td_site_gog[23], 0x0E2941FF);
	TextDrawSetShadow(td_site_gog[23], 0);
	TextDrawSetOutline(td_site_gog[23], 0);
	TextDrawBackgroundColor(td_site_gog[23], 255);
	TextDrawFont(td_site_gog[23], 1);
	TextDrawSetProportional(td_site_gog[23], 1);
	TextDrawSetShadow(td_site_gog[23], 0);

	td_site_gog[24] = TextDrawCreate(308.262115, 308.350006, "www.lsportal.com"); // 
	TextDrawLetterSize(td_site_gog[24], 0.117173, 0.654999);
	TextDrawAlignment(td_site_gog[24], 1);
	TextDrawColor(td_site_gog[24], 0x0E2941FF);
	TextDrawSetShadow(td_site_gog[24], 0);
	TextDrawSetOutline(td_site_gog[24], 0);
	TextDrawBackgroundColor(td_site_gog[24], 255);
	TextDrawFont(td_site_gog[24], 2);
	TextDrawSetProportional(td_site_gog[24], 1);
	TextDrawSetShadow(td_site_gog[24], 0);

	td_site_gog[25] = TextDrawCreate(201.279632, 353.816497, "GOG Corporation (c) 2020"); // 
	TextDrawLetterSize(td_site_gog[25], 0.117173, 0.654999);
	TextDrawAlignment(td_site_gog[25], 1);
	TextDrawColor(td_site_gog[25], -2139062017);
	TextDrawSetShadow(td_site_gog[25], 0);
	TextDrawSetOutline(td_site_gog[25], 0);
	TextDrawBackgroundColor(td_site_gog[25], 255);
	TextDrawFont(td_site_gog[25], 1);
	TextDrawSetProportional(td_site_gog[25], 1);
	TextDrawSetShadow(td_site_gog[25], 0);

	td_site_gog[26] = TextDrawCreate(199.647079, 176.000045, "BEST SEARCH ENGINE"); // 
	TextDrawLetterSize(td_site_gog[26], 0.101645, 0.538331);
	TextDrawAlignment(td_site_gog[26], 1);
	TextDrawColor(td_site_gog[26], -662699777);
	TextDrawSetShadow(td_site_gog[26], 0);
	TextDrawSetOutline(td_site_gog[26], 0);
	TextDrawBackgroundColor(td_site_gog[26], 255);
	TextDrawFont(td_site_gog[26], 1);
	TextDrawSetProportional(td_site_gog[26], 1);
	TextDrawSetShadow(td_site_gog[26], 0);

	td_site_gog[27] = TextDrawCreate(216.879348, 153.083282, "24, Tuesday"); // Date
	TextDrawLetterSize(td_site_gog[27], 0.175058, 0.759998);
	TextDrawAlignment(td_site_gog[27], 2);
	TextDrawColor(td_site_gog[27], -1079681537);
	TextDrawSetShadow(td_site_gog[27], 0);
	TextDrawSetOutline(td_site_gog[27], 0);
	TextDrawBackgroundColor(td_site_gog[27], 255);
	TextDrawFont(td_site_gog[27], 1);
	TextDrawSetProportional(td_site_gog[27], 1);
	TextDrawSetShadow(td_site_gog[27], 0);

	td_site_gog[28] = TextDrawCreate(442.275360, 165.283386, "Inbox"); // 
	TextDrawLetterSize(td_site_gog[28], 0.220232, 1.098332);
	TextDrawTextSize(td_site_gog[28], 462.000000, 0.000000);
	TextDrawAlignment(td_site_gog[28], 1);
	TextDrawColor(td_site_gog[28], -1);
	TextDrawUseBox(td_site_gog[28], 1);
	TextDrawBoxColor(td_site_gog[28], 1672472319);
	TextDrawSetShadow(td_site_gog[28], 0);
	TextDrawSetOutline(td_site_gog[28], 0);
	TextDrawBackgroundColor(td_site_gog[28], 255);
	TextDrawFont(td_site_gog[28], 1);
	TextDrawSetProportional(td_site_gog[28], 1);
	TextDrawSetShadow(td_site_gog[28], 0);
	
	td_site_gog[29] = TextDrawCreate(397.277557, 215.366607, "LD_SPAC:white"); // ovh io 
	TextDrawLetterSize(td_site_gog[29], 0.000000, 0.000000);
	TextDrawTextSize(td_site_gog[29], 50.399597, 104.710151);
	TextDrawAlignment(td_site_gog[29], 1);
	TextDrawColor(td_site_gog[29], 0x97a8b1FF);
	TextDrawSetShadow(td_site_gog[29], 0);
	TextDrawSetOutline(td_site_gog[29], 0);
	TextDrawBackgroundColor(td_site_gog[29], 255);
	TextDrawFont(td_site_gog[29], 4);
	TextDrawSetProportional(td_site_gog[29], 0);
	TextDrawSetShadow(td_site_gog[29], 0);
	TextDrawSetSelectable(td_site_gog[29], true);

	td_site_gog[30] = TextDrawCreate(403.811920, 219.150024, "OVH"); // 
	TextDrawLetterSize(td_site_gog[30], 0.410823, 2.031667);
	TextDrawAlignment(td_site_gog[30], 1);
	TextDrawColor(td_site_gog[30], 1198292991);
	TextDrawSetShadow(td_site_gog[30], 0);
	TextDrawSetOutline(td_site_gog[30], 0);
	TextDrawBackgroundColor(td_site_gog[30], 255);
	TextDrawFont(td_site_gog[30], 1);
	TextDrawSetProportional(td_site_gog[30], 1);
	TextDrawSetShadow(td_site_gog[30], 0);

	td_site_gog[31] = TextDrawCreate(402.941192, 237.250167, "Innovation is Freedom.~n~Best web-hosting, dedicated servers, VPS, CDN, domains.~n~~n~Create your own website."); // 
	TextDrawTextSize(td_site_gog[31], 441.000000, 0.000000);
	TextDrawLetterSize(td_site_gog[31], 0.135529, 0.643333);
	TextDrawAlignment(td_site_gog[31], 1);
	TextDrawColor(td_site_gog[31], -1);
	TextDrawSetShadow(td_site_gog[31], 0);
	TextDrawSetOutline(td_site_gog[31], 0);
	TextDrawBackgroundColor(td_site_gog[31], 255);
	TextDrawFont(td_site_gog[31], 1);
	TextDrawSetProportional(td_site_gog[31], 1);
	TextDrawSetShadow(td_site_gog[31], 0);

	td_site_gog[32] = TextDrawCreate(403.650268, 308.249694, "www.ovh.com"); // 
	TextDrawLetterSize(td_site_gog[32], 0.117173, 0.654999);
	TextDrawAlignment(td_site_gog[32], 1);
	TextDrawColor(td_site_gog[32], -2139062017);
	TextDrawSetShadow(td_site_gog[32], 0);
	TextDrawSetOutline(td_site_gog[32], 0);
	TextDrawBackgroundColor(td_site_gog[32], 255);
	TextDrawFont(td_site_gog[32], 2);
	TextDrawSetProportional(td_site_gog[32], 1);
	TextDrawSetShadow(td_site_gog[32], 0);
	
	/*!	
		
		@brief TEMPLATE 1 (Default Orange)
		
	*/
	

	td_site_template_1[0] = TextDrawCreate(387.882415, 162.766860, "14, Tuesday~n~Log In or Register"); // 
	TextDrawLetterSize(td_site_template_1[0], 0.155763, 0.643329);
	TextDrawAlignment(td_site_template_1[0], 1);
	TextDrawColor(td_site_template_1[0], 255);
	TextDrawSetShadow(td_site_template_1[0], 0);
	TextDrawSetOutline(td_site_template_1[0], 0);
	TextDrawBackgroundColor(td_site_template_1[0], 255);
	TextDrawFont(td_site_template_1[0], 1);
	TextDrawSetProportional(td_site_template_1[0], 1);
	TextDrawSetShadow(td_site_template_1[0], 0);

	td_site_template_1[1] = TextDrawCreate(392.365264, 216.634109, "box"); // side-block 
	TextDrawLetterSize(td_site_template_1[1], 0.000000, 1.341174);
	TextDrawTextSize(td_site_template_1[1], 458.100677, -8.000000);
	TextDrawAlignment(td_site_template_1[1], 1);
	TextDrawColor(td_site_template_1[1], -1378294017);
	TextDrawUseBox(td_site_template_1[1], 1);
	TextDrawBoxColor(td_site_template_1[1], 255);
	TextDrawSetShadow(td_site_template_1[1], 0);
	TextDrawSetOutline(td_site_template_1[1], 0);
	TextDrawBackgroundColor(td_site_template_1[1], 255);
	TextDrawFont(td_site_template_1[1], 1);
	TextDrawSetProportional(td_site_template_1[1], 1);
	TextDrawSetShadow(td_site_template_1[1], 0);
	
	td_site_template_1[2] = TextDrawCreate(393.529449, 233.166687, "shsdjohsdhodsh sdf[hpjsdh \
	sd[fpjh sd[fpjhsdfjhpsdj[psd hsdfp[jhd [pfj \
	sdfp[jsd ag sdgkshs dhk[sdhodkh d[fhk d[fhk df[hdfhdfh"); // ltnews 
	TextDrawLetterSize(td_site_template_1[2], 0.076235, 0.351667);
	TextDrawTextSize(td_site_template_1[2], 456.999938, -4.000000);
	TextDrawAlignment(td_site_template_1[2], 1);
	TextDrawColor(td_site_template_1[2], -2139062017);
	TextDrawSetShadow(td_site_template_1[2], 0);
	TextDrawSetOutline(td_site_template_1[2], 0);
	TextDrawBackgroundColor(td_site_template_1[2], 255);
	TextDrawFont(td_site_template_1[2], 2);
	TextDrawSetProportional(td_site_template_1[2], 1);
	TextDrawSetShadow(td_site_template_1[2], 0);

	td_site_template_1[3] = TextDrawCreate(185.529556, 335.250030, "- ZGepwylplsg~n~-Geowkw3030l~n~- faoKtgwgk~n~- At2tgOAgksk"); // 
	TextDrawLetterSize(td_site_template_1[3], 0.151528, 0.188332);
	TextDrawTextSize(td_site_template_1[3], 249.000000, 8.000000);
	TextDrawAlignment(td_site_template_1[3], 1);
	TextDrawColor(td_site_template_1[3], -2139062017);
	TextDrawSetShadow(td_site_template_1[3], 0);
	TextDrawSetOutline(td_site_template_1[3], 0);
	TextDrawBackgroundColor(td_site_template_1[3], 255);
	TextDrawFont(td_site_template_1[3], 2);
	TextDrawSetProportional(td_site_template_1[3], 1);
	TextDrawSetShadow(td_site_template_1[3], 0);

	td_site_template_1[4] = TextDrawCreate(276.352935, 336.899993, "- Woy T vv Tewt~n~- TetT yweyw~n~- Tewtwglnsdg"); // 
	TextDrawLetterSize(td_site_template_1[4] , 0.163293, 0.205833);
	TextDrawTextSize(td_site_template_1[4] , 337.000000, 2.000000);
	TextDrawAlignment(td_site_template_1[4], 1);
	TextDrawColor(td_site_template_1[4], -2139062017);
	TextDrawSetShadow(td_site_template_1[4], 0);
	TextDrawSetOutline(td_site_template_1[4], 0);
	TextDrawBackgroundColor(td_site_template_1[4], 255);
	TextDrawFont(td_site_template_1[4], 2);
	TextDrawSetProportional(td_site_template_1[4], 1);
	TextDrawSetShadow(td_site_template_1[4], 0);

	td_site_template_1[5] = TextDrawCreate(195.882339, 210.016860, "> Home"); // 
	TextDrawLetterSize(td_site_template_1[5], 0.174586, 0.754163);
	TextDrawAlignment(td_site_template_1[5], 1);
	TextDrawColor(td_site_template_1[5], -2139062017);
	TextDrawSetShadow(td_site_template_1[5], 0);
	TextDrawSetOutline(td_site_template_1[5], 0);
	TextDrawBackgroundColor(td_site_template_1[5], 255);
	TextDrawFont(td_site_template_1[5], 1);
	TextDrawSetProportional(td_site_template_1[5], 1);
	TextDrawSetShadow(td_site_template_1[5], 0);
	
	td_site_template_1[6] = TextDrawCreate(397.294036, 219.350189, "Latest News"); // 
	TextDrawLetterSize(td_site_template_1[6], 0.193882, 0.829997);
	TextDrawAlignment(td_site_template_1[6], 1);
	TextDrawColor(td_site_template_1[6], -1);
	TextDrawSetShadow(td_site_template_1[6], 0);
	TextDrawSetOutline(td_site_template_1[6], 0);
	TextDrawBackgroundColor(td_site_template_1[6], 255);
	TextDrawFont(td_site_template_1[6], 1);
	TextDrawSetProportional(td_site_template_1[6], 1);
	TextDrawSetShadow(td_site_template_1[6], 0);
	
	/*!	
		
		@brief TEMPLATE 2 (Default Blog)
		
	*/

	td_site_template_2[0] = TextDrawCreate(160.217666, 193.299987, "box"); // 
	TextDrawLetterSize(td_site_template_2[0], 0.000000, 0.959644);
	TextDrawTextSize(td_site_template_2[0], 477.100006, -110.000000);
	TextDrawAlignment(td_site_template_2[0], 1);
	TextDrawColor(td_site_template_2[0], -1);
	TextDrawUseBox(td_site_template_2[0], 1);
	TextDrawBoxColor(td_site_template_2[0], -2139062017);
	TextDrawSetShadow(td_site_template_2[0], 0);
	TextDrawSetOutline(td_site_template_2[0], 0);
	TextDrawBackgroundColor(td_site_template_2[0], 255);
	TextDrawFont(td_site_template_2[0], 1);
	TextDrawSetProportional(td_site_template_2[0], 1);
	TextDrawSetShadow(td_site_template_2[0], 0);

	td_site_template_2[1] = TextDrawCreate(207.599853, 220.584091, "box"); // 
	TextDrawLetterSize(td_site_template_2[1], 0.000000, 13.083868);
	TextDrawTextSize(td_site_template_2[1], 430.000000, 34.000000);
	TextDrawAlignment(td_site_template_2[1], 1);
	TextDrawColor(td_site_template_2[1], -1);
	TextDrawUseBox(td_site_template_2[1], 1);
	TextDrawBoxColor(td_site_template_2[1], -1061109692);
	TextDrawSetShadow(td_site_template_2[1], 0);
	TextDrawSetOutline(td_site_template_2[1], 0);
	TextDrawBackgroundColor(td_site_template_2[1], 255);
	TextDrawFont(td_site_template_2[1], 1);
	TextDrawSetProportional(td_site_template_2[1], 1);
	TextDrawSetShadow(td_site_template_2[1], 0);

	td_site_template_2[2] = TextDrawCreate(413.894104, 194.366775, "SEARCH"); // 
	TextDrawLetterSize(td_site_template_2[2], 0.167529, 0.759997);
	TextDrawTextSize(td_site_template_2[2], 0.000000, 32.000000);
	TextDrawAlignment(td_site_template_2[2], 2);
	TextDrawColor(td_site_template_2[2], -1);
	TextDrawUseBox(td_site_template_2[2], 1);
	TextDrawBoxColor(td_site_template_2[2], -1061109662);
	TextDrawSetShadow(td_site_template_2[2], 0);
	TextDrawSetOutline(td_site_template_2[2], 0);
	TextDrawBackgroundColor(td_site_template_2[2], 255);
	TextDrawFont(td_site_template_2[2], 1);
	TextDrawSetProportional(td_site_template_2[2], 1);
	TextDrawSetShadow(td_site_template_2[2], 0);

	td_site_template_2[3] = TextDrawCreate(208.247161, 194.583328, "> HOME"); // 
	TextDrawLetterSize(td_site_template_2[3], 0.139293, 0.672499);
	TextDrawAlignment(td_site_template_2[3], 1);
	TextDrawColor(td_site_template_2[3], -1);
	TextDrawSetShadow(td_site_template_2[3], 0);
	TextDrawSetOutline(td_site_template_2[3], 0);
	TextDrawBackgroundColor(td_site_template_2[3], 255);
	TextDrawFont(td_site_template_2[3], 1);
	TextDrawSetProportional(td_site_template_2[3], 1);
	TextDrawSetShadow(td_site_template_2[3], 0);
	
	/*!	
		
		@brief TEMPLATE 3 (Site Menu)
		
	*/
	
	td_site_template_3[0] = TextDrawCreate(160.263961, 152.734085, "box"); // menu-background 
	TextDrawLetterSize(td_site_template_3[0], 0.000000, 23.543853);
	TextDrawTextSize(td_site_template_3[0], 244.000000, 278.000000);
	TextDrawAlignment(td_site_template_3[0], 1);
	TextDrawColor(td_site_template_3[0], -1378294017);
	TextDrawUseBox(td_site_template_3[0], 1);
	TextDrawBoxColor(td_site_template_3[0], 421075455);
	TextDrawSetShadow(td_site_template_3[0], 0);
	TextDrawSetOutline(td_site_template_3[0], 0);
	TextDrawBackgroundColor(td_site_template_3[0], 255);
	TextDrawFont(td_site_template_3[0], 1);
	TextDrawSetProportional(td_site_template_3[0], 1);
	TextDrawSetShadow(td_site_template_3[0], 0);
	
	td_site_template_3[1] = TextDrawCreate(236.352905, 152.200027, "-~n~-~n~-"); // 
	TextDrawLetterSize(td_site_template_3[1], 0.579764, 0.351666);
	TextDrawAlignment(td_site_template_3[1], 1);
	TextDrawColor(td_site_template_3[1], -1061109505);
	TextDrawSetShadow(td_site_template_3[1], 0);
	TextDrawSetOutline(td_site_template_3[1], 0);
	TextDrawBackgroundColor(td_site_template_3[1], 255);
	TextDrawFont(td_site_template_3[1], 3);
	TextDrawSetProportional(td_site_template_3[1], 1);
	TextDrawSetShadow(td_site_template_3[1], 0);

	td_site_template_3[2] = TextDrawCreate(257.929595, 178.566726, "03, Saturday"); // 
	TextDrawLetterSize(td_site_template_3[2], 0.125176, 0.631666);
	TextDrawAlignment(td_site_template_3[2], 1);
	TextDrawColor(td_site_template_3[2], 421075455);
	TextDrawSetShadow(td_site_template_3[2], 0);
	TextDrawSetOutline(td_site_template_3[2], 0);
	TextDrawBackgroundColor(td_site_template_3[2], 255);
	TextDrawFont(td_site_template_3[2], 1);
	TextDrawSetProportional(td_site_template_3[2], 1);
	TextDrawSetShadow(td_site_template_3[2], 0);

	
	/*!	
		
		@brief DARKNET TEMPLATE 1 (Green)
		
	*/

	td_dark_template_1 = TextDrawCreate(215.176544, 329.999877, "Your remain 100% anonymouse, \
	by using Tor Browser your ip is not revealeted to us, we don't need any information about you"); // 
	TextDrawLetterSize(td_dark_template_1, 0.135995, 0.689997);
	TextDrawTextSize(td_dark_template_1, 417.000000, -11.000000);
	TextDrawAlignment(td_dark_template_1, 1);
	TextDrawColor(td_dark_template_1, -1);
	TextDrawSetShadow(td_dark_template_1, 0);
	TextDrawSetOutline(td_dark_template_1, 0);
	TextDrawBackgroundColor(td_dark_template_1, 255);
	TextDrawFont(td_dark_template_1, 1);
	TextDrawSetProportional(td_dark_template_1, 1);
	TextDrawSetShadow(td_dark_template_1, 0);
}

TD_Player_Site(playerid)
{
	/*!	
		@brief Ѕраузер
	*/
	
	ptd_address_line[playerid] = CreatePlayerTextDraw(playerid, 185.886611, 139.116760, "_"); 
	PlayerTextDrawLetterSize(playerid, ptd_address_line[playerid], 0.178882, 0.783333);
	PlayerTextDrawTextSize(playerid, ptd_address_line[playerid], 444.950469, 10.000000);
	PlayerTextDrawAlignment(playerid, ptd_address_line[playerid], 1);
	PlayerTextDrawColor(playerid, ptd_address_line[playerid], -150);
	PlayerTextDrawUseBox(playerid, ptd_address_line[playerid], 1);
	PlayerTextDrawBoxColor(playerid, ptd_address_line[playerid], 43);
	PlayerTextDrawSetOutline(playerid, ptd_address_line[playerid], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_address_line[playerid], 255);
	PlayerTextDrawFont(playerid, ptd_address_line[playerid], 2);
	PlayerTextDrawSetProportional(playerid, ptd_address_line[playerid], 1);
	PlayerTextDrawSetShadow(playerid, ptd_address_line[playerid], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_address_line[playerid], true);
	
	
	/*!	
		
		@brief TEMPLATE 1 (Default Orange)
		
	*/
	
	ptd_site_template_1[playerid][0] = CreatePlayerTextDraw(playerid, 186.163986, 187.467498, "box"); // menu-background 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_1[playerid][0], 0.000000, 1.858821);
	PlayerTextDrawTextSize(playerid, ptd_site_template_1[playerid][0], 457.899322, 0.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_1[playerid][0], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_1[playerid][0], -1378294017);
	PlayerTextDrawUseBox(playerid, ptd_site_template_1[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, ptd_site_template_1[playerid][0], -5963521);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_1[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_1[playerid][0], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_1[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_1[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][0], 0);

	ptd_site_template_1[playerid][1] = CreatePlayerTextDraw(playerid, 202.470596, 160.250045, "Site Name"); // logo text 
	PlayerTextDrawTextSize(playerid, ptd_site_template_1[playerid][1], 321.000000, 6.000000);
	PlayerTextDrawLetterSize(playerid, ptd_site_template_1[playerid][1], 0.328469, 1.640830);
	PlayerTextDrawAlignment(playerid, ptd_site_template_1[playerid][1], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_1[playerid][1], 255);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_1[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_1[playerid][1], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_1[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_1[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][1], 0);

	ptd_site_template_1[playerid][2] = CreatePlayerTextDraw(playerid, 227.294921, 191.300109, "HOME"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_1[playerid][2], 0.248465, 1.069164);
	PlayerTextDrawTextSize(playerid, ptd_site_template_1[playerid][2], 10.000000, 53.009998);
	PlayerTextDrawAlignment(playerid, ptd_site_template_1[playerid][2], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_1[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_1[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_1[playerid][2], -1);
	PlayerTextDrawFont(playerid, ptd_site_template_1[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_1[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_site_template_1[playerid][2], true);

	ptd_site_template_1[playerid][3] = CreatePlayerTextDraw(playerid, 286.398529, 191.300109, "FORUM"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_1[playerid][3], 0.248465, 1.069164);
	PlayerTextDrawTextSize(playerid, ptd_site_template_1[playerid][3], 10.000000, 53.009998);
	PlayerTextDrawAlignment(playerid, ptd_site_template_1[playerid][3], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_1[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_1[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_1[playerid][3], -1);
	PlayerTextDrawFont(playerid, ptd_site_template_1[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_1[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_site_template_1[playerid][3], true);

	ptd_site_template_1[playerid][4] = CreatePlayerTextDraw(playerid, 345.402130, 191.300109, "INFO"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_1[playerid][4], 0.248465, 1.069164);
	PlayerTextDrawTextSize(playerid, ptd_site_template_1[playerid][4], 10.000000, 53.009998);
	PlayerTextDrawAlignment(playerid, ptd_site_template_1[playerid][4], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_1[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_1[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_1[playerid][4], -1);
	PlayerTextDrawFont(playerid, ptd_site_template_1[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_1[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_site_template_1[playerid][4], true);

	ptd_site_template_1[playerid][5] = CreatePlayerTextDraw(playerid, 404.243316, 191.300109, "ABOUT US"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_1[playerid][5], 0.248465, 1.069164);
	PlayerTextDrawTextSize(playerid, ptd_site_template_1[playerid][5], 10.000000, 53.009998);
	PlayerTextDrawAlignment(playerid, ptd_site_template_1[playerid][5], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_1[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_1[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_1[playerid][5], -1);
	PlayerTextDrawFont(playerid, ptd_site_template_1[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_1[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_site_template_1[playerid][5], true);

	ptd_site_template_1[playerid][6] = CreatePlayerTextDraw(playerid, 185.741119, 227.333389, "re magna aliqua."); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_1[playerid][6], 0.241879, 1.197496);
	PlayerTextDrawTextSize(playerid, ptd_site_template_1[playerid][6], 371.000000, -20.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_1[playerid][6], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_1[playerid][6], 255);
	PlayerTextDrawUseBox(playerid, ptd_site_template_1[playerid][6], 1);
	PlayerTextDrawBoxColor(playerid, ptd_site_template_1[playerid][6], -1061109694);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_1[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_1[playerid][6], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_1[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_1[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][6], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_site_template_1[playerid][6], true);

	ptd_site_template_1[playerid][7] = CreatePlayerTextDraw(playerid, 386.941558, 329.600158, "(c) 2020 Site Name. All Rights Reserved."); // 
	PlayerTextDrawTextSize(playerid, ptd_site_template_1[playerid][7], 459.000000, 0.000000);
	PlayerTextDrawLetterSize(playerid, ptd_site_template_1[playerid][7], 0.150113, 0.584994);
	PlayerTextDrawAlignment(playerid, ptd_site_template_1[playerid][7], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_1[playerid][7], -5963521);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_1[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_1[playerid][7], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_1[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_1[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][7], 0);

	ptd_site_template_1[playerid][8] = CreatePlayerTextDraw(playerid, 208.588333, 174.983291, "your slogan here"); // 
	PlayerTextDrawTextSize(playerid, ptd_site_template_1[playerid][8] , 288.000000, 0.000000);
	PlayerTextDrawLetterSize(playerid, ptd_site_template_1[playerid][8], 0.168941, 0.654999);
	PlayerTextDrawAlignment(playerid, ptd_site_template_1[playerid][8], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_1[playerid][8], -2139062017);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_1[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_1[playerid][8], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_1[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_1[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][8], 0);
	
	ptd_site_template_1[playerid][9] = CreatePlayerTextDraw(playerid, 185.999954, 323.766967, "Links"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_1[playerid][9], 0.193882, 0.829997);
	PlayerTextDrawTextSize(playerid, ptd_site_template_1[playerid][9], 249.000000, -4.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_1[playerid][9], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_1[playerid][9], -1);
	PlayerTextDrawUseBox(playerid, ptd_site_template_1[playerid][9], 1);
	PlayerTextDrawBoxColor(playerid, ptd_site_template_1[playerid][9], -5963521);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_1[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_1[playerid][9], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_1[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_1[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][9], 0);
	
	ptd_site_template_1[playerid][10] = CreatePlayerTextDraw(playerid, 275.624847, 323.766906, "Features"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_1[playerid][10], 0.193882, 0.829997);
	PlayerTextDrawTextSize(playerid, ptd_site_template_1[playerid][10], 336.801391, -4.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_1[playerid][10], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_1[playerid][10], -1);
	PlayerTextDrawUseBox(playerid, ptd_site_template_1[playerid][10], 1);
	PlayerTextDrawBoxColor(playerid, ptd_site_template_1[playerid][10], -5963521);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_1[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_1[playerid][10], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_1[playerid][10], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_1[playerid][10], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_1[playerid][10], 0);
	
	
	/*!	
		
		@brief TEMPLATE 2 (Default Blog)
		
	*/
	
	ptd_site_template_2[playerid][0] = CreatePlayerTextDraw(playerid, 160.281661, 152.667526, "box"); // menu-background 152.667526
	PlayerTextDrawLetterSize(playerid, ptd_site_template_2[playerid][0], 0.000000, 4.0000); // 4.776469
	PlayerTextDrawTextSize(playerid, ptd_site_template_2[playerid][0], 477.100097, 37.000000); // 37.000000
	PlayerTextDrawAlignment(playerid, ptd_site_template_2[playerid][0], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_2[playerid][0], -2147450625);
	PlayerTextDrawUseBox(playerid, ptd_site_template_2[playerid][0], 1);
	PlayerTextDrawBoxColor(playerid, ptd_site_template_2[playerid][0], -1523963137);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_2[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_2[playerid][0], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_2[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_2[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][0], 0);

	ptd_site_template_2[playerid][1] = CreatePlayerTextDraw(playerid, 167.333816, 166.216735, "Site Name"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_2[playerid][1], 0.260702, 1.203330);
	PlayerTextDrawTextSize(playerid, ptd_site_template_2[playerid][1], 250.000000, -16.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_2[playerid][1], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_2[playerid][1], -1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_2[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_2[playerid][1], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_2[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_2[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][1], 0);

	ptd_site_template_2[playerid][2] = CreatePlayerTextDraw(playerid, 447.073974, 167.216812, "About us"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_2[playerid][2], 0.189646, 0.835830);
	PlayerTextDrawTextSize(playerid, ptd_site_template_2[playerid][2], 8.000000, 41.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_2[playerid][2], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_2[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_2[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_2[playerid][2], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_2[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_2[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_site_template_2[playerid][2], true);

	ptd_site_template_2[playerid][3] = CreatePlayerTextDraw(playerid, 402.338684, 167.333526, "Info"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_2[playerid][3], 0.189646, 0.835830);
	PlayerTextDrawTextSize(playerid, ptd_site_template_2[playerid][3], 8.000000, 41.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_2[playerid][3], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_2[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_2[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_2[playerid][3], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_2[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_2[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_site_template_2[playerid][3], true);

	ptd_site_template_2[playerid][4] = CreatePlayerTextDraw(playerid, 357.562255, 167.150222, "Forum"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_2[playerid][4], 0.189646, 0.835830);
	PlayerTextDrawTextSize(playerid, ptd_site_template_2[playerid][4], 8.000000, 41.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_2[playerid][4], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_2[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_2[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_2[playerid][4], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_2[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_2[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_site_template_2[playerid][4], true);

	ptd_site_template_2[playerid][5] = CreatePlayerTextDraw(playerid, 312.738616, 167.200119, "Home"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_2[playerid][5], 0.189646, 0.835830);
	PlayerTextDrawTextSize(playerid, ptd_site_template_2[playerid][5], 8.000000, 41.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_2[playerid][5], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_2[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_2[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_2[playerid][5], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_2[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_2[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_site_template_2[playerid][5], true);

	ptd_site_template_2[playerid][6] = CreatePlayerTextDraw(playerid, 214.258575, 224.850112, "Lorem ipsl yergher ekdfhokdfh rohkdohbkdr ohkdroyhkrbodkrho rdohkdohkd drohkdrohk;eowd"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_2[playerid][6], 0.335996, 1.413334);
	PlayerTextDrawTextSize(playerid, ptd_site_template_2[playerid][6], 422.199829, 10.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_2[playerid][6], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_2[playerid][6], -2147483393);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_2[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_2[playerid][6], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_2[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_2[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][6], 0);

	ptd_site_template_2[playerid][7] = CreatePlayerTextDraw(playerid, 314.770538, 334.366668, "(c) 2020 Site Name. All Right Reserved."); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_2[playerid][7], 0.131292, 0.742500);
	PlayerTextDrawTextSize(playerid, ptd_site_template_2[playerid][7], -26.000000, 134.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_2[playerid][7], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_2[playerid][7], -2139062017);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_2[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_2[playerid][7], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_2[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_2[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][7], 0);

	ptd_site_template_2[playerid][8] = CreatePlayerTextDraw(playerid, 167.416030, 176.133438, "Description"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_2[playerid][8], 0.197642, 0.923331);
	PlayerTextDrawTextSize(playerid, ptd_site_template_2[playerid][8], 249.878967, -16.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_2[playerid][8], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_2[playerid][8], -1061109505);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_2[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_2[playerid][8], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_2[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_2[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][8], 0);
	
	ptd_site_template_2[playerid][9] = CreatePlayerTextDraw(playerid, 217.752593, 208.450027, "02, Saturday"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_2[playerid][9], 0.111529, 0.625832);
	PlayerTextDrawAlignment(playerid, ptd_site_template_2[playerid][9], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_2[playerid][9], -2147483393);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_2[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_2[playerid][9], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_2[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_2[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][9], 0);

	ptd_site_template_2[playerid][10] = CreatePlayerTextDraw(playerid, 386.734710, 208.233337, "Sign In___Register"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_2[playerid][10], 0.119998, 0.643333);
	PlayerTextDrawAlignment(playerid, ptd_site_template_2[playerid][10], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_2[playerid][10], -2147483393);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_2[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_2[playerid][10], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_2[playerid][10], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_2[playerid][10], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_2[playerid][10], 0);
	
	/*!	
		
		@brief TEMPLATE 3 (Side Menu)
		
	*/

	ptd_site_template_3[playerid][0] = CreatePlayerTextDraw(playerid, 202.064498, 168.434265, "Site Name"); // logo text 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_3[playerid][0], 0.265410, 1.430829);
	PlayerTextDrawTextSize(playerid, ptd_site_template_3[playerid][0], -4.000000, 81.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_3[playerid][0], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_3[playerid][0], -5963521);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_3[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_3[playerid][0], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_3[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_3[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][0], 0);

	ptd_site_template_3[playerid][1] = CreatePlayerTextDraw(playerid, 202.064498, 183.635192, "Your slogan"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_3[playerid][1], 0.166115, 0.789162);
	PlayerTextDrawTextSize(playerid, ptd_site_template_3[playerid][1], -4.000000, 81.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_3[playerid][1], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_3[playerid][1], -1061109505);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_3[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_3[playerid][1], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_3[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_3[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][1], 0);

	ptd_site_template_3[playerid][2] = CreatePlayerTextDraw(playerid, 201.935058, 211.051818, "Home"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_3[playerid][2], 0.179292, 0.969995);
	PlayerTextDrawTextSize(playerid, ptd_site_template_3[playerid][2], 8.000000, 81.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_3[playerid][2], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_3[playerid][2], -5963521);
	PlayerTextDrawUseBox(playerid, ptd_site_template_3[playerid][2], 1);
	PlayerTextDrawBoxColor(playerid, ptd_site_template_3[playerid][2], 41);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_3[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_3[playerid][2], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_3[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_3[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_site_template_3[playerid][2], true);

	ptd_site_template_3[playerid][3] = CreatePlayerTextDraw(playerid, 201.935058, 225.052673, "Forum"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_3[playerid][3], 0.179292, 0.969995);
	PlayerTextDrawTextSize(playerid, ptd_site_template_3[playerid][3], 8.000000, 81.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_3[playerid][3], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_3[playerid][3], -5963521);
	PlayerTextDrawUseBox(playerid, ptd_site_template_3[playerid][3], 1);
	PlayerTextDrawBoxColor(playerid, ptd_site_template_3[playerid][3], 41);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_3[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_3[playerid][3], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_3[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_3[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_site_template_3[playerid][3], true);

	ptd_site_template_3[playerid][4] = CreatePlayerTextDraw(playerid, 201.935058, 239.153533, "Information"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_3[playerid][4], 0.179292, 0.969995);
	PlayerTextDrawTextSize(playerid, ptd_site_template_3[playerid][4], 8.000000, 81.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_3[playerid][4], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_3[playerid][4], -5963521);
	PlayerTextDrawUseBox(playerid, ptd_site_template_3[playerid][4], 1);
	PlayerTextDrawBoxColor(playerid, ptd_site_template_3[playerid][4], 41);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_3[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_3[playerid][4], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_3[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_3[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_site_template_3[playerid][4], true);

	ptd_site_template_3[playerid][5] = CreatePlayerTextDraw(playerid, 201.935058, 253.354400, "About us"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_3[playerid][5], 0.179292, 0.969995);
	PlayerTextDrawTextSize(playerid, ptd_site_template_3[playerid][5], 8.000000, 81.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_3[playerid][5], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_3[playerid][5], -5963521);
	PlayerTextDrawUseBox(playerid, ptd_site_template_3[playerid][5], 1);
	PlayerTextDrawBoxColor(playerid, ptd_site_template_3[playerid][5], 41);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_3[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_3[playerid][5], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_3[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_3[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_site_template_3[playerid][5], true);

	ptd_site_template_3[playerid][6] = CreatePlayerTextDraw(playerid, 247.717681, 152.549972, "box"); // breadcrumb-back-home 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_3[playerid][6], 0.000000, 1.940936);
	PlayerTextDrawTextSize(playerid, ptd_site_template_3[playerid][6], 477.289306, -105.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_3[playerid][6], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_3[playerid][6], -1);
	PlayerTextDrawUseBox(playerid, ptd_site_template_3[playerid][6], 1);
	PlayerTextDrawBoxColor(playerid, ptd_site_template_3[playerid][6], -5963521);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_3[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_3[playerid][6], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_3[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_3[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][6], 0);

	ptd_site_template_3[playerid][7] = CreatePlayerTextDraw(playerid, 263.141906, 198.383392, "agshsdyh dh djh dfjdfj dfj dfj dfj df"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_3[playerid][7], 0.392941, 1.623335);
	PlayerTextDrawTextSize(playerid, ptd_site_template_3[playerid][7], 448.000000, -28.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_3[playerid][7], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_3[playerid][7], 421075455);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_3[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_3[playerid][7], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_3[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_3[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][7], 0);

	ptd_site_template_3[playerid][8] = CreatePlayerTextDraw(playerid, 354.400146, 355.316833, "2020 (c). Site name, All rights Reserved"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_3[playerid][8], 0.125176, 0.631666);
	PlayerTextDrawTextSize(playerid, ptd_site_template_3[playerid][8], -15.000000, 135.000000);
	PlayerTextDrawAlignment(playerid, ptd_site_template_3[playerid][8], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_3[playerid][8], 421075455);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_3[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_3[playerid][8], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_3[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_3[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][8], 0);
	
	ptd_site_template_3[playerid][9] = CreatePlayerTextDraw(playerid, 253.694244, 156.400115, "> Home"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_3[playerid][9], 0.236235, 1.028333);
	PlayerTextDrawAlignment(playerid, ptd_site_template_3[playerid][9], 1);
	PlayerTextDrawColor(playerid, ptd_site_template_3[playerid][9], 421075455);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_3[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_3[playerid][9], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_3[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_3[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][9], 0);

	ptd_site_template_3[playerid][10] = CreatePlayerTextDraw(playerid, 451.124084, 153.683502, "Log In~n~~g~Register"); // 
	PlayerTextDrawLetterSize(playerid, ptd_site_template_3[playerid][10], 0.177411, 0.853332);
	PlayerTextDrawAlignment(playerid, ptd_site_template_3[playerid][10], 2);
	PlayerTextDrawColor(playerid, ptd_site_template_3[playerid][10], 421075455);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, ptd_site_template_3[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_site_template_3[playerid][10], 255);
	PlayerTextDrawFont(playerid, ptd_site_template_3[playerid][10], 1);
	PlayerTextDrawSetProportional(playerid, ptd_site_template_3[playerid][10], 1);
	PlayerTextDrawSetShadow(playerid, ptd_site_template_3[playerid][10], 0);
	
	
	/*!	
		
		@brief DARKNET TEMPLATE 1 (Green)
		
	*/
	
	ptd_dark_template_1[playerid][0] = CreatePlayerTextDraw(playerid, 218.000000, 164.116653, "Site Name"); // 
	PlayerTextDrawLetterSize(playerid, ptd_dark_template_1[playerid][0], 0.348704, 1.419165);
	PlayerTextDrawTextSize(playerid, ptd_dark_template_1[playerid][0], 312.000000, 11.000000);
	PlayerTextDrawAlignment(playerid, ptd_dark_template_1[playerid][0], 1);
	PlayerTextDrawColor(playerid, ptd_dark_template_1[playerid][0], -1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][0], 0);
	PlayerTextDrawSetOutline(playerid, ptd_dark_template_1[playerid][0], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_dark_template_1[playerid][0], 255);
	PlayerTextDrawFont(playerid, ptd_dark_template_1[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, ptd_dark_template_1[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][0], 0);

	ptd_dark_template_1[playerid][1] = CreatePlayerTextDraw(playerid, 219.882324, 176.616333, "your slogan here"); // 
	PlayerTextDrawLetterSize(playerid, ptd_dark_template_1[playerid][1], 0.219291, 0.917499);
	PlayerTextDrawTextSize(playerid, ptd_dark_template_1[playerid][1], 310.000000, -4.000000);
	PlayerTextDrawAlignment(playerid, ptd_dark_template_1[playerid][1], 1);
	PlayerTextDrawColor(playerid, ptd_dark_template_1[playerid][1], 16711935);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][1], 0);
	PlayerTextDrawSetOutline(playerid, ptd_dark_template_1[playerid][1], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_dark_template_1[playerid][1], 255);
	PlayerTextDrawFont(playerid, ptd_dark_template_1[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, ptd_dark_template_1[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][1], 0);

	ptd_dark_template_1[playerid][2] = CreatePlayerTextDraw(playerid, 208.588287, 201.083328, "Home"); // 
	PlayerTextDrawLetterSize(playerid, ptd_dark_template_1[playerid][2], 0.241411, 0.829999);
	PlayerTextDrawTextSize(playerid, ptd_dark_template_1[playerid][2], 246.000000, 8.000000);
	PlayerTextDrawAlignment(playerid, ptd_dark_template_1[playerid][2], 1);
	PlayerTextDrawColor(playerid, ptd_dark_template_1[playerid][2], -1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][2], 0);
	PlayerTextDrawSetOutline(playerid, ptd_dark_template_1[playerid][2], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_dark_template_1[playerid][2], 255);
	PlayerTextDrawFont(playerid, ptd_dark_template_1[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, ptd_dark_template_1[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_dark_template_1[playerid][2], true);

	ptd_dark_template_1[playerid][3] = CreatePlayerTextDraw(playerid, 250.352874, 201.016738, "Services"); // 
	PlayerTextDrawLetterSize(playerid, ptd_dark_template_1[playerid][3], 0.241411, 0.829999);
	PlayerTextDrawTextSize(playerid, ptd_dark_template_1[playerid][3], 287.989990, 8.000000);
	PlayerTextDrawAlignment(playerid, ptd_dark_template_1[playerid][3], 1);
	PlayerTextDrawColor(playerid, ptd_dark_template_1[playerid][3], -1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][3], 0);
	PlayerTextDrawSetOutline(playerid, ptd_dark_template_1[playerid][3], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_dark_template_1[playerid][3], 255);
	PlayerTextDrawFont(playerid, ptd_dark_template_1[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, ptd_dark_template_1[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_dark_template_1[playerid][3], true);

	ptd_dark_template_1[playerid][4] = CreatePlayerTextDraw(playerid, 292.229583, 201.016738, "Order"); // 
	PlayerTextDrawLetterSize(playerid, ptd_dark_template_1[playerid][4], 0.241411, 0.829999);
	PlayerTextDrawTextSize(playerid, ptd_dark_template_1[playerid][4], 327.000000, 8.000000);
	PlayerTextDrawAlignment(playerid, ptd_dark_template_1[playerid][4], 1);
	PlayerTextDrawColor(playerid, ptd_dark_template_1[playerid][4], -1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][4], 0);
	PlayerTextDrawSetOutline(playerid, ptd_dark_template_1[playerid][4], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_dark_template_1[playerid][4], 255);
	PlayerTextDrawFont(playerid, ptd_dark_template_1[playerid][4], 1);
	PlayerTextDrawSetProportional(playerid, ptd_dark_template_1[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][4], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_dark_template_1[playerid][4], true);

	ptd_dark_template_1[playerid][5] = CreatePlayerTextDraw(playerid, 331.046752, 201.133438, "Payment Process"); // 
	PlayerTextDrawLetterSize(playerid, ptd_dark_template_1[playerid][5], 0.241411, 0.829999);
	PlayerTextDrawTextSize(playerid, ptd_dark_template_1[playerid][5], 408.989990, 8.000000);
	PlayerTextDrawAlignment(playerid, ptd_dark_template_1[playerid][5], 1);
	PlayerTextDrawColor(playerid, ptd_dark_template_1[playerid][5], -1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][5], 0);
	PlayerTextDrawSetOutline(playerid, ptd_dark_template_1[playerid][5], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_dark_template_1[playerid][5], 255);
	PlayerTextDrawFont(playerid, ptd_dark_template_1[playerid][5], 1);
	PlayerTextDrawSetProportional(playerid, ptd_dark_template_1[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][5], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_dark_template_1[playerid][5], true);

	ptd_dark_template_1[playerid][6] = CreatePlayerTextDraw(playerid, 221.294036, 225.000076, "Lorem ipsum dolor sit amet"); // 
	PlayerTextDrawLetterSize(playerid, ptd_dark_template_1[playerid][6], 0.319058, 1.261666);
	PlayerTextDrawTextSize(playerid, ptd_dark_template_1[playerid][6], 415.000000, -3.000000);
	PlayerTextDrawAlignment(playerid, ptd_dark_template_1[playerid][6], 1);
	PlayerTextDrawColor(playerid, ptd_dark_template_1[playerid][6], 16711935);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][6], 0);
	PlayerTextDrawSetOutline(playerid, ptd_dark_template_1[playerid][6], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_dark_template_1[playerid][6], 255);
	PlayerTextDrawFont(playerid, ptd_dark_template_1[playerid][6], 1);
	PlayerTextDrawSetProportional(playerid, ptd_dark_template_1[playerid][6], 1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][6], 0);
	PlayerTextDrawSetSelectable(playerid, ptd_dark_template_1[playerid][6], true);
	
	ptd_dark_template_1[playerid][7] = CreatePlayerTextDraw(playerid, 317.523529, 163.866485, "Username"); // 
	PlayerTextDrawLetterSize(playerid, ptd_dark_template_1[playerid][7], 0.167529, 0.759998);
	PlayerTextDrawTextSize(playerid, ptd_dark_template_1[playerid][7], 352.700042, -2.000000);
	PlayerTextDrawAlignment(playerid, ptd_dark_template_1[playerid][7], 1);
	PlayerTextDrawColor(playerid, ptd_dark_template_1[playerid][7], 16711935);
	PlayerTextDrawUseBox(playerid, ptd_dark_template_1[playerid][7], 1);
	PlayerTextDrawBoxColor(playerid, ptd_dark_template_1[playerid][7], -2139062017);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][7], 0);
	PlayerTextDrawSetOutline(playerid, ptd_dark_template_1[playerid][7], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_dark_template_1[playerid][7], 255);
	PlayerTextDrawFont(playerid, ptd_dark_template_1[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, ptd_dark_template_1[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][7], 0);

	ptd_dark_template_1[playerid][8] = CreatePlayerTextDraw(playerid, 359.741302, 163.949783, "Password"); // 
	PlayerTextDrawLetterSize(playerid, ptd_dark_template_1[playerid][8], 0.167529, 0.759998);
	PlayerTextDrawTextSize(playerid, ptd_dark_template_1[playerid][8], 394.199951, -2.000000);
	PlayerTextDrawAlignment(playerid, ptd_dark_template_1[playerid][8], 1);
	PlayerTextDrawColor(playerid, ptd_dark_template_1[playerid][8], 16711935);
	PlayerTextDrawUseBox(playerid, ptd_dark_template_1[playerid][8], 1);
	PlayerTextDrawBoxColor(playerid, ptd_dark_template_1[playerid][8], -2139062017);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][8], 0);
	PlayerTextDrawSetOutline(playerid, ptd_dark_template_1[playerid][8], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_dark_template_1[playerid][8], 255);
	PlayerTextDrawFont(playerid, ptd_dark_template_1[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, ptd_dark_template_1[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][8], 0);

	ptd_dark_template_1[playerid][9] = CreatePlayerTextDraw(playerid, 402.564727, 163.366485, "Sign In"); // 
	PlayerTextDrawLetterSize(playerid, ptd_dark_template_1[playerid][9], 0.167529, 0.759998);
	PlayerTextDrawAlignment(playerid, ptd_dark_template_1[playerid][9], 1);
	PlayerTextDrawColor(playerid, ptd_dark_template_1[playerid][9], 16711935);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][9], 0);
	PlayerTextDrawSetOutline(playerid, ptd_dark_template_1[playerid][9], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_dark_template_1[playerid][9], 255);
	PlayerTextDrawFont(playerid, ptd_dark_template_1[playerid][9], 1);
	PlayerTextDrawSetProportional(playerid, ptd_dark_template_1[playerid][9], 1);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][9], 0);

	ptd_dark_template_1[playerid][10] = CreatePlayerTextDraw(playerid, 161.000061, 213.900207, "LD_BEAT:chit"); // 
	PlayerTextDrawLetterSize(playerid, ptd_dark_template_1[playerid][10], 0.000000, 0.000000);
	PlayerTextDrawTextSize(playerid, ptd_dark_template_1[playerid][10], 320.000000, -1.029999);
	PlayerTextDrawAlignment(playerid, ptd_dark_template_1[playerid][10], 1);
	PlayerTextDrawColor(playerid, ptd_dark_template_1[playerid][10], 16711935);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][10], 0);
	PlayerTextDrawSetOutline(playerid, ptd_dark_template_1[playerid][10], 0);
	PlayerTextDrawBackgroundColor(playerid, ptd_dark_template_1[playerid][10], 255);
	PlayerTextDrawFont(playerid, ptd_dark_template_1[playerid][10], 4);
	PlayerTextDrawSetProportional(playerid, ptd_dark_template_1[playerid][10], 0);
	PlayerTextDrawSetShadow(playerid, ptd_dark_template_1[playerid][10], 0);
}

TD_UpdateSiteDate()
{
	new day,
		weekday		[	16	];
	
	getdate(_, _, day);
	GetNameOfWeekday(weekday);
	
	/// GOG
	format:g_small_string("%02d, %s", day, weekday);
	TextDrawSetString(td_site_gog[27], g_small_string);
	
	/// Custom 1
	format:g_small_string("%02d, %s~n~Log In or Register", day, weekday);
	TextDrawSetString(td_site_template_1[0], g_small_string);
	
	/// Custom 2
	foreach (new playerid : Player)
	{
		if (!IsPlayerLogged(playerid))
		{
			continue;
		}
		
		format:g_small_string("%02d, %s", day, weekday);
		PlayerTextDrawSetString(playerid, ptd_site_template_2[playerid][9], g_small_string);
	}
	
	/// Custom 3
	format:g_small_string("%02d, %s", day, weekday);
	TextDrawSetString(td_site_template_3[2], g_small_string);
}