/*!
	@brief Заголовок для системы помещений (Интерьеры)
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

#define GetPremiseSettings(%0,%1)			premise_settings[premise_data[%0][pr_int_type]][%1]

enum E_PREMISE_INTERIOR
{
	pint_wall_begin,
	pint_wall_end,
	
	pint_roof_begin,
	pint_roof_end,
	
	pint_floor_begin,
	pint_floor_end,
	
	pint_object_material,
	pint_object_type
};

enum E_PREMISE_SETTINGS // Настройки интерьеров домов
{
	pset_name								[	32	],
	Float: pset_pos							[	4 	],
	pset_rooms, // количество комнат
	pset_furnitures,
	pset_electrocity
};

// Интерьеры помещений
new const premise_settings					[	][	E_PREMISE_SETTINGS] = 
{
	{"", {0.0, 0.0, 0.0, 0.0}, 0, 0}, // 0 - None
	
	{"Магазин #1 (2 комнаты)", {1707.8646, 1145.7828, 2468.5034, 273.4208}, 2, 70, 35}, // 1 - Shop 1
	{"Магазин #2 (3 комнаты)", {2019.3137, 1223.4076, 2462.0605, 272.6491}, 3, 80, 50}, // 2 - Shop 2
	
	{"Минимаркет #1 (2 комнаты)", {-3069.1526, -1195.0200, 2410.1545, 90.9375}, 2, 65, 35}, // 3 - Minimarket 1
	{"Минимаркет #2 (2 комнаты)", {-3002.1782, -1196.4399, 2404.6943, 270.3109}, 2, 65, 52}, // 4 - Minimarket 2
	{"Минимаркет #3 (2 комнаты)", {-2912.9299, -814.9474, 2383.4873, 273.6129}, 2, 65, 45}, // 5 - Minimarket 3
	
	{"Паб #1 (4 комнаты)", {2887.6038, 803.9901, 2516.3259, 357.3949}, 4, 100, 60}, // 6 - Pub 1
	{"Паб #2 (2 комнаты)", {2883.1069, 1303.6837, 2516.3237, 348.6447}, 2, 70, 37}, // 7 - Pub 2
	{"Паб #3 (3 комнаты)", {2485.0894, 1906.9923, 2516.3159, 0.8651}, 3, 90, 45}, // 8 - Pub 2
	
	{"Цок. магазин #1 (4 комнаты)", {2233.0901, 2529.7063, 2934.2268, 86.2375}, 4, 80, 50}, // 9 - Socle 1
	
	{"Клуб (6 комнат)", {-2783.7629, -514.8989, 1883.4873, 269.3708}, 6, 160, 70} // 10 - Club 1
};

new premise_int_obj							[sizeof premise_data  ][	MAX_ROOMS 	][	E_PREMISE_INTERIOR	];