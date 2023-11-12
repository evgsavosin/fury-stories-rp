/*!
	@brief Список предметов в системе инвентаря
	@author Found (evg.savosin)
	@date 16.12.2016, update 07.02.2018
	
*/

// Defines
#define GetInventoryItemId(%0)		item_list[%0][it_id]	
#define GetInventoryItemName(%0)	item_list[%0][it_name]	

// Structures
// Типы предметов
enum 
{
	INV_NONE = 0,
	INV_SKIN, // 1 
	INV_WEAPON_SMALL, // 2
	INV_WEAPON_BIG, // 3
	INV_EAT, // 4 
	INV_DRINK, // 5 
	INV_ATTACH, // 6 
	INV_AMMO, // 7
	INV_BAG, // 8 сумка
	INV_PHONE, // 9 
	INV_OBJECT, // 10
	INV_HEALTH, // 11
	INV_REPAIR, // 12
	INV_SMOKE, // 13
	INV_RADIO, // 14
	INV_FUEL, // 15
	INV_CHEMICAL, // 16
	INV_LIGHTER, // 17
	INV_DRUGS // 18
};

// Дополнительные функции к предметам
enum 
{
	INV_FUNC_HIDDEN_NAME = -1000,
	INV_FUNC_SOUND,
	INV_FUNC_SINGLE_SMOKE,
	INV_FUNC_RADIO_LOW,
	INV_FUNC_RADIO_HIGH,
	INV_FUNC_ARMOUR_LIGHT,
	INV_FUNC_ARMOUR_HEAVY,
	INV_FUNC_KNIFE,
	INV_FUNC_MARIJUANA,
	INV_FUNC_LSD,
	INV_FUNC_COCAINE
};

enum E_ITEM_DATA
{
	it_id,
	it_type,
	
	it_name						[	64		],
	it_model,
	
	Float: it_draw_x,
	Float: it_draw_y,
	Float: it_draw_z,
	Float: it_draw_zoom,
	
	it_param_1,
	it_param_2,
	
	it_description				[	256		],
	
	bool: it_is_glove_exists,
};

new const item_list				[		][		E_ITEM_DATA 	] = 
{
	{0, INV_NONE, "Пусто", 19374, 0.0, 0.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM, "", false}, // Пусто
	
	
	{1, INV_SKIN, "Одежда", 0, 0.0, 0.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"Совокупность швейных изделий, выполняющие эстетические функции.", false},

	
	{2, INV_WEAPON_BIG, "Клюшка для гольфа", 333, 0.0, -30.0, 0.0, 1.5, WEAPON_GOLFCLUB, INVALID_PARAM, 
		"Спортивный снаряд в виде палки с загнутым концом для игры в гольф.", false},
		
	{3, INV_WEAPON_BIG, "Резиновая дубинка", 334, 0.0, -30.0, 0.0, 1.5, WEAPON_NITESTICK, INVALID_PARAM, 
		"Несмертельное оружие, которое используется сотрудниками правоохранительных органов.", false},
		
	{5, INV_WEAPON_BIG, "Бейсбольная бита", 336, 0.0, -30.0, 0.0, 1.5, WEAPON_BAT, INVALID_PARAM, 
		"Спортивный снаряд, которым игроки в некоторых спортивных играх пытаются отбить поданный мяч.", false},
		
	{6, INV_WEAPON_BIG, "Лопата", 337, 0.0, -30.0, 0.0, 1.5, WEAPON_SHOVEL, INVALID_PARAM, 
		"Ручной инструмент для работы с грунтом.", false},
		
	{7, INV_WEAPON_BIG, "Катана", 339, 0.0, -30.0, 0.0, 1.5, WEAPON_KATANA, INVALID_PARAM, 
		"Длинная японская сабля.", false},
		
	{8, INV_WEAPON_SMALL, "Малогабаритный пистолет", 346, 0.0, -30.0, 0.0, 1.5, WEAPON_COLT45, 20,
		"Самозарядный пистолет.\n\
		Прототипы для отыгровки: " #cPROJECT "M1911, Beretta M9, Glock 17, HK VP9, ПМ,\nSmith & Wesson Model CS45, Kimber Classic" #cWHITE ".", true},
		
	{9, INV_WEAPON_SMALL, "Малогабаритный пистолет с глушителем", 347, 0.0, -30.0, 0.0, 1.5, WEAPON_SILENCED, 20,
		"Самозарядный пистолет с глушителем.\n\
		Прототипы для отыгровки: " #cPROJECT "M1911, Beretta M9, Glock 17, HK VP9, ПМ,\nSmith & Wesson Model CS45, Kimber Classic" #cWHITE ".", true},
		
	{10, INV_WEAPON_SMALL, "Тяжелый пистолет", 348, 0.0, -30.0, 0.0, 1.5, WEAPON_DEAGLE, 21,
		"Тяжелый самозарядный пистолет.\n\
		Прототипы для отыгровки: " #cPROJECT "Desert Eagle, Combat Magnum" #cWHITE ".", true},
	
	{11, INV_WEAPON_BIG, "Дробовик", 349, 0.0, -30.0, 0.0, 1.5, WEAPON_SHOTGUN, 22,
		"Гладкоствольное огнестрельное оружие.\n\
		Прототипы для отыгровки: " #cPROJECT "Remington 1100, Remington 870, Benelli Nova" #cWHITE ".", false},
		
	{12, INV_WEAPON_BIG, "Штурмовой дробовик", 351, 0.0, -30.0, 0.0, 1.5, WEAPON_SHOTGSPA, 22,
		"Автоматическое гладкоствольное огнестрельное оружие.\n\
		Прототипы для отыгровки: " #cPROJECT "SPAS-12" #cWHITE ".", false},
		
	{13, INV_WEAPON_SMALL, "Малогабаритный ПП", 352, 0.0, -30.0, 0.0, 1.5, WEAPON_UZI, 23,
		"Израильский малогабаритный пистолет-пулемёт.\n\
		Прототипы для отыгровки: " #cPROJECT "Micro UZI" #cWHITE ".", true},
		
	{14, INV_WEAPON_SMALL, "Полуавтоматический пистолет", 372, 0.0, -30.0, 0.0, 1.5, WEAPON_TEC9, 23,
		"Малогабаритный пистолет-пулемет, разработанный в Швеции в 1980-х годах.\n\
		Прототипы для отыгровки: " #cPROJECT "TEC-9" #cWHITE ".", true},	
		
	{15, INV_WEAPON_BIG, "ПП", 353, 0.0, -30.0, 0.0, 1.5, WEAPON_MP5, 23,
		"Пистолет-пулемет.\n\
		Прототипы для отыгровки: " #cPROJECT "HK MP5, HK MP7" #cWHITE ".", false},
	
	{16, INV_WEAPON_BIG, "Автомат Калашникова", 355, 0.0, -30.0, 0.0, 1.5, WEAPON_AK47, 24,
		"Автомат, принятый на вооружение в СССР.\n\
		Прототипы для отыгровки: " #cPROJECT "АКМ, АК-74, Сайга, СКС" #cWHITE ".", false},
		
	{17, INV_WEAPON_BIG, "AR-15", 356, 0.0, -30.0, 0.0, 1.5, WEAPON_M4, 25,
		"Американская полуавтоматическая винтовка под патрон.\n\
		Прототипы для отыгровки: " #cPROJECT "M4A1, HK416" #cWHITE ".", false},
	
	{18, INV_WEAPON_BIG, "Винтовка", 357, 0.0, -30.0, 0.0, 1.5, WEAPON_RIFLE, 24,
		"Нарезное стрелковое оружие.\n\
		Прототипы для отыгровки: " #cPROJECT "M14, M1 Garand" #cWHITE ".", false},
	
	{19, INV_WEAPON_BIG, "Снайперская винтовка", 358, 0.0, -30.0, 0.0, 1.5, WEAPON_SNIPER, 24,
		"Нарезное стрелковое оружие.\n\
		Прототипы для отыгровки: " #cPROJECT "Barrett M98B, M2010, M110,\nBor, СВД, AS50, Remington 700, M24" #cWHITE ".", false},
	
	
	{20, INV_AMMO, "Патроны 9 mm", 2037, 30.0, 30.0, 0.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"Патроны калибра 9 mm, который применяется в пистолетах.", true},
	
	{21, INV_AMMO, "Патроны .44 Magnum", 2037, 30.0, 30.0, 0.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"Патроны калибра .44 Magnum, которые применяется в тяжелых пистолетах.", true},
		
	{22, INV_AMMO, "Патроны 12 mm", 2043, -90.0, 0.0, 0.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"Патроны калибра 12 mm, которые применяется в дробовиках.", true},
		
	{23, INV_AMMO, "Патроны 9x19 mm", 2040, -10.0, 0.0, 30.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"Патроны калибра 9x19 mm, которые применяется в пистолетах-пулеметах.", true},
		
	{24, INV_AMMO, "Патроны 7,62х39 mm", 2040, -10.0, 0.0, 30.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"Патроны калибра 7,62х39 mm, которые применяется в автомате калашникова, винтовках, снайперских винтовках.", true},
	
	{25, INV_AMMO, "Патроны 5,56x45 mm NATO", 2040, -10.0, 0.0, 30.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"Патроны калибра 5,56x45 mm NATO, которые применяется в автоматическом карабине.", true},
	
	
	{26, INV_PHONE, "Смартфон", 18874, 90.0, 180.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"Мобильный телефон, дополненный функциональностью карманного персонального компьютера.\n\
		Прототипы для отыгровки: "#cPROJECT "Iphone X, Samsung Galaxy S9, SONY Experia XZ" #cWHITE ".", true},

		
	{27, INV_BAG, "Спортивная сумка", 11745, -30.0, 0.0, 90.0, 1.0, (5), INVALID_PARAM,
		"Емкость для переноса различных предметов.", false},
	
	{28, INV_BAG, "Походная сумка", 19559, -30.0, 0.0, 90.0, 1.0, (8), INVALID_PARAM,
		"Емкость для переноса различных предметов.", false},

	{29, INV_BAG, "Бумажный пакет", 2663, -16.0, 0.0, -55.0, 1.0, (2), INVALID_PARAM,
		"Емкость для переноса различных предметов.", false},
	
	{30, INV_BAG, "Чемодан", 19624, -16.0, 0.0, -55.0, 1.0, (6), INVALID_PARAM,
		"Емкость для переноса различных предметов.", false},
		

	{31, INV_EAT, "Гамбургер", 2768, 0.0, 0.0, 0.0, 1.0, 5, INVALID_PARAM,
		"Вид сэндвича, состоящий из рубленой жареной котлеты.", true},
		
	{32, INV_EAT, "Тако", 2769, 0.0, 0.0, -140.0, 0.75, 2, INVALID_PARAM,
		"Традиционное блюдо мексиканской кухни.", true},
		
	{33, INV_EAT, "Яблоко", 19576, -35.0, 15.0, -70.0, 0.7, 1, INVALID_PARAM,
		"Плод яблони, который употребляется в пищу в свежем виде.", true},
		
	{34, INV_EAT, "Апельсин", 19574, -35.0, 15.0, -70.0, 0.7, 1, INVALID_PARAM,
		"Плод апельсина, который употребляется в пищу в свежем виде.", true},
		
	{35, INV_EAT, "Банан", 19578, -35.0, 15.0, -70.0, 0.7, 1, INVALID_PARAM,
		"Плод травянистого одноименного растения, которое произрастает в тропическом климате.", true},
		
	{36, INV_EAT, "Окорок", 19847, 30.0, -45.0, 90.0, 1.0, 5, INVALID_PARAM,
		"Блюдо из тазобедренной части свиной туши.", true},
		
	{37, INV_EAT, "Хот-дог", 19346, -45.0, 0.0, 150.0, 1.5, 2, INVALID_PARAM,
		"Сосиска с хлебобулочным изделием и горчицей.", true},
		
	{38, INV_EAT, "Бифштекс", 2355, -30.0, -30.0, 180.0, 0.6, 10, INVALID_PARAM,
		"Блюдо из жареной говядины.", true},
		
	{39, INV_EAT, "Пицца", 2220, -30.0, -30.0, 180.0, 0.6, 10, INVALID_PARAM,
		"Итальянское национальное блюдо в виде круглой открытой лепёшки.", true},
		
	{40, INV_EAT, "Малый набор «Кофе и пончики»", 2221, -50.0, 0.0, 90.0, 0.7, 5, INVALID_PARAM,
		"Набор из пончика с кексом и стаканчиком с кофе.", true},
		
	{41, INV_EAT, "Средний набор «Кофе и пончики»", 2223, -50.0, 0.0, 90.0, 0.7, 8, INVALID_PARAM,
		"Глазированные пончики и стакан кофе.", true},
	
	{42, INV_EAT, "Большой набор «Кофе и пончики»", 2222, -50.0, 0.0, 90.0, 0.7, 10, INVALID_PARAM,
		"Несколько видов пончиков и стакан кофе.", true},
		
	
	{43, INV_DRINK, "Стакан с кофе", 19835, -40.0, 0.0, 170.0, 0.7, 5, INVALID_PARAM,
		"Ароматный кофе из свежемолотых зерен в бумажном стаканчике.", true},
	
	{44, INV_DRINK, "Газировка в стакане «Sprunk»", 1546, 0.0, 0.0, 260.0, 0.8, 5, INVALID_PARAM,
		"Безалкогольный газированный напиток в бумажном стаканчике.", true},
		
	{45, INV_DRINK, "Газировка в стакане «Burger Shot»", 2647, 0.0, 0.0, 260.0, 0.8, 5, INVALID_PARAM,
		"Безалкогольный газированный напиток в бумажном стаканчике.", true},
	
	{46, INV_DRINK, "Яблочный сок", 19564, 0.0, 0.0, 30.0, 1.0, 5, INVALID_PARAM,
		"Сок выжатый из яблок.", true},
		
	{47, INV_DRINK, "Апельсиновый сок", 19563, 0.0, 0.0, 30.0, 1.0, 5, INVALID_PARAM,
		"Сок выжатый из апельсинов.", true},
		
	{48, INV_DRINK, "Газировка в банке «Sprunk»", 2601, 0.0, 0.0, -70.0, 0.7, 5, INVALID_PARAM,
		"Безалкогольный газированный напиток в жестяной банке.", true},
	
	{49, INV_DRINK, "Пиво", 2958, 0.0, 0.0, 30.0, 0.9, 15, INVALID_PARAM,
		"Хмельный слабоалкогольный напиток.", true},
		
	{50, INV_DRINK, "Светлое пиво", 1544, 0.0, 0.0, 30.0, 0.9, 15, INVALID_PARAM,
		"Хмельный слабоалкогольный напиток.", true},
		
	{51, INV_DRINK, "Эль", 1950, 0.0, 0.0, 30.0, 0.9, 15, INVALID_PARAM,
		"Слабоалкогольный напиток.", true},
		
	{52, INV_DRINK, "Водка", 1668, 0.0, 0.0, 30.0, 0.9, 25, INVALID_PARAM,
		"Крепкий алкогольный напиток", true},
		
	{53, INV_DRINK, "Виски", 1669, 0.0, 0.0, 30.0, 0.9, 25, INVALID_PARAM,
		"Крепкий алкогольный напиток.", true},
		
	{54, INV_DRINK, "Коньяк", 1520, 0.0, 0.0, 30.0, 0.9, 25, INVALID_PARAM,
		"Крепкий алкогольный напиток.", true},
		
	{55, INV_DRINK, "Бренди", 19820, 0.0, 0.0, 30.0, 0.9, 25, INVALID_PARAM,
		"Крепкий алкогольный напиток.", true},
	
	{56, INV_DRINK, "Текила", 19821, 0.0, 0.0, 30.0, 0.9, 25, INVALID_PARAM,
		"Крепкий алкогольный напиток.", true},
	
	{57, INV_DRINK, "Ликер", 19823, 0.0, 0.0, 30.0, 0.9, 25, INVALID_PARAM,
		"Крепкий алкогольный напиток.", true},
	
	{58, INV_DRINK, "Красное вино", 19822, 0.0, 0.0, 30.0, 0.9, 20, INVALID_PARAM,
		"Алкогольный напиток.", true},
		
	{59, INV_DRINK, "Белое вино", 19824, 0.0, 0.0, 30.0, 0.9, 20, INVALID_PARAM,
		"Алкогольный напиток.", true},
	
	{60, INV_DRINK, "Бокал вина", 1667, 0.0, 0.0, 30.0, 0.9, 15, INVALID_PARAM,
		"Алкогольный напиток.", true},
		
	{61, INV_DRINK, "Бокал мартини", 19819, 0.0, 0.0, 30.0, 0.9, 15, INVALID_PARAM,
		"Алкогольный напиток.", true},
	
	{62, INV_DRINK, "Бокал шампанского", 19818, 0.0, 0.0, 30.0, 0.9, 15, INVALID_PARAM,
		"Алкогольный напиток.", true}, 
		
	{63, INV_DRINK, "Коктейль", 1666, 0.0, 0.0, 30.0, 0.9, 15, INVALID_PARAM,
		"Алкогольный напиток.", true}, 

	
	{64, INV_ATTACH, "Шапка", INVALID_PARAM, 220.0, 90.0, 0.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"Головной убор, состоящий из вязаного материала.", true},
	
	{65, INV_ATTACH, "Бандана", INVALID_PARAM, 60.0, 180.0, 180.0, 0.8, INVALID_PARAM, INVALID_PARAM,
		"Головной убор в виде косынки.", true},
	
	{66, INV_ATTACH, "Кепка", INVALID_PARAM, 120.0, 40.0, 80.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"Головной убор с маленьким твердым донышком.", true},
	
	{67, INV_ATTACH, "Очки", INVALID_PARAM, 10.0, 0.0, 90.0, 0.65, INVALID_PARAM, INVALID_PARAM,
		"Аксессуар.", true},
	
	{68, INV_ATTACH, "Платки на лицо", INVALID_PARAM, -45.0, 45.0, 170.0, 0.8, INVALID_PARAM, INVALID_PARAM,
		"Материал ткани, который закрывает часть лица.", true},
		
	{69, INV_ATTACH, "Шляпа", INVALID_PARAM, -10.0, -90.0, 30.0, 0.8, INVALID_PARAM, INVALID_PARAM,
		"Головной убор, состояющий из тульи.", true},
		
	{70, INV_ATTACH, "Механические часы", INVALID_PARAM, -10.0, 0.0, 30.0, 0.5, INVALID_PARAM, INVALID_PARAM,
		"Часы, использующие маятник, который периодом колебаний измеряет время в течение суток.", true},
		
	{71, INV_ATTACH, "Электрогитара", INVALID_PARAM, 0.0, 45.0, 180.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"Разновидность гитары с электромагнитными звукоснимателями.", false},
		
	{72, INV_ATTACH, "Наушники", INVALID_PARAM, 0.0, 45.0, 180.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"Устройство для персонального прослушивания звуковой информации.", true},
		
	{73, INV_ATTACH, "Электронные часы", INVALID_PARAM, -10.0, 0.0, 30.0, 0.5, INVALID_PARAM, INVALID_PARAM,
		"Часы, в которых для отсчёта времени используются периодические колебания электронного генератора.", true},
		
	
	{74, INV_ATTACH, "Кобура", 19773, 0.0, 0.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"Чехол для ношения личного огнестрельного оружия.", true},
		
	{75, INV_ATTACH, "Скейтборд", 19878, -60.0, 180.0, 160.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"Доска, состоящая из фанеры, которая содержит несколько слоёв шпона, \n\
		установленная на колёса небольшого диаметра.", false},
		
	{76, INV_ATTACH, "Фонарик", 18641, 0.0, 90.0, 0.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"Небольшой носимый источник света для индивидуального использования.", true},
		
	{77, INV_ATTACH, "Гантель", 2916, -50.0, 0.0, 0.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"Спортивный снаряд для выполнения физических упражнений.", false},
		
	{78, INV_ATTACH, "Баскетбольный мяч", 2114, -60.0, 180.0, 160.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"Спортивный снаряд для выполнения физических упражнений.", false},
		
	{79, INV_ATTACH, "Татуировочная машинка", 2711, 60.0, 60.0, -90.0, 0.6, INVALID_PARAM, INVALID_PARAM,
		"Инструмент для нанесения татуировки.", true},
		
	{80, INV_ATTACH, "Удочка", 18632, 0.0, 360.0, 0.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"Инструмент в виде гибкого хлыста для ловли рыбы.", false},
		
	{81, INV_ATTACH, "Гаечный ключ", 19627, 90.0, 0.0, 0.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"Инструмент в виде гибкого хлыста для ловли рыбы.", true},
		
	{82, INV_ATTACH, "Молоток", 18635, 0.0, 0.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"Молоток с гвоздодером.", true},
		
	{83, INV_ATTACH, "Баллонный ключ", 18633, 90.0, -90.0, 0.0, 1.3, INVALID_PARAM, INVALID_PARAM,
		"Ключ для монтажа колес.", true},
		
	{84, INV_ATTACH, "Кувалда", 19631, 260.0, 90.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"Ручной ударный инструмент.", false},
		
	{85, INV_ATTACH, "Швабра", 19622, 0.0, 0.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"Инструмент для влажной уборки.", false},
		
	{86, INV_ATTACH, "Отвертка", 18644, 0.0, 0.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"Ручной слесарный инструмент, предназначенный для завинчивания и \nотвинчивания крепёжных изделий с резьбой.", true},
		
	{87, INV_ATTACH, "Грабли", 18890, 0.0, 0.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"Сельскохозяйственный инструмент.", false},
		
	{88, INV_ATTACH, "Нож выживания", 335, 90.0, 0.0, -200.0, 1.0, INV_FUNC_KNIFE, INVALID_PARAM,
		"Крупный, как правило нескладной универсальный нож с большим числом функций.", true},
		
	{89, INV_ATTACH, "Каска", 18638, 0.0, 90.0, 230.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"Желтая пластиковая каска.", false},
		
	{90, INV_ATTACH, "Лыжная маска", 19801, 0.0, 0.0, 180.0, 0.7, INV_FUNC_HIDDEN_NAME, INVALID_PARAM,
		"Шерстяная лыжная маска.", true}, // @INV_FUNC_HIDDEN_NAME
		
	{91, INV_ATTACH, "Респиратор", 19472, 90.0, 120.0, 0.0, 1.0, INV_FUNC_HIDDEN_NAME, INVALID_PARAM,
		"Средство индивидуальной защиты органов дыхания.", true}, // @INV_FUNC_HIDDEN_NAME
	
	
	{92, INV_REPAIR, "Ящик с инструментами", 19921, 260.0, 180.0, 0.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"Красный ящик с набором инструмент для оказания поверхностного \n\
		ремонта автотранспорта.", false},
		
	{93, INV_HEALTH, "Пачка с бинтом", 11748, 90.0, 220.0, 0.0, 0.8, INVALID_PARAM, INVALID_PARAM,
		"Ткань для перевязки ран.", true},
		
		
	{94, INV_SMOKE, "Сигареты «Red Sticks»", 19896, 90.0, 220.0, 0.0, 0.5, INVALID_PARAM, INVALID_PARAM,
		"Красная пачка с сигаретами.", true},
	
	{95, INV_SMOKE, "Сигареты «C/K»", 19897, 90.0, 220.0, 0.0, 0.5, INVALID_PARAM, INVALID_PARAM,
		"Синяя пачка с сигаретами.", true},
		
	{96, INV_SMOKE, "Роскошная сигара", 3044, -320.0, -70.0, 0.0, 0.3, INV_FUNC_SINGLE_SMOKE, INVALID_PARAM,
		"Скрутка из листьев табака.", true},
		
		
	{97, INV_OBJECT, "Красная гриль", 19831, -20.0, 0.0, 220.0, 1.2, INVALID_PARAM, INVALID_PARAM,
		"Установка для приготовления блюд на углях, жару.", false},
		
	{98, INV_OBJECT, "Металлическая гриль", 1481, -20.0, 0.0, 220.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"Установка для приготовления блюд на углях, жару.", false},
		
		
	{99, INV_ATTACH, "Черный бумбокс", 2102, -20.0, 0.0, 220.0, 1.0, INV_FUNC_SOUND, INVALID_PARAM,
		"Тип переносного аудиоцентра.", true},
		
	{100, INV_ATTACH, "Красный бумбокс", 2226, -20.0, 0.0, 220.0, 1.0, INV_FUNC_SOUND, INVALID_PARAM,
		"Тип переносного аудиоцентра.", true},
	
	
	{101, INV_ATTACH, "Фаллоимитатор", INVALID_PARAM, 60.0, -20.0, 0.0, 0.5, INVALID_PARAM, INVALID_PARAM,
		"Изделие, относящееся к сексуальным игрушкам.", true},
		
		
	{102, INV_ATTACH, "Маска для ролевых игр", INVALID_PARAM, 10.0, 0.0, -110.0, 0.7, INV_FUNC_HIDDEN_NAME, INVALID_PARAM,
		"Изделие, относящееся к сексуальным игрушкам.", true},
	
	{103, INV_ATTACH, "Шлем", INVALID_PARAM, 60.0, -20.0, 0.0, 0.5, INV_FUNC_HIDDEN_NAME, INVALID_PARAM,
		"Элемент формы одежды защищающий область головы.", true},
	
	
	{104, INV_RADIO, "Рация", 2967, 260.0, 30.0, 180.0, 0.8, INV_FUNC_RADIO_LOW, INVALID_PARAM,
		"Переносное приёмо-передающее устройство.", true},
		
	{105, INV_RADIO, "Улучшенная рация", 19942, 0.0, 0.0, 200.0, 0.8, INV_FUNC_RADIO_HIGH, INVALID_PARAM,
		"Улучшенное переносное приёмо-передающее устройство.", true},
		
		
	{106, INV_ATTACH, "Ноутбук", 19893, -10.0, 0.0, -160.0, 0.7, INVALID_PARAM, INVALID_PARAM,
		"Переносной персональный компьютер.", false},
		
		
	{107, INV_BAG, "Ранец", 3026, 180.0, 0.0, 0.0, 1.0, (4), INVALID_PARAM,
		"Специализированная сумка для переноса предметов.", false},
		
		
	{108, INV_FUEL, "Канистра", 1650, 0.0, 0.0, 30.0, 1.0, INVALID_PARAM, INVALID_PARAM,
		"Канистра с топливной жидкостью на 5 галлон.", false},
		
		
	{109, INV_ATTACH, "Лёгкий бронежилет", 373, -90.0, 200.0, 310.0, 1.8, INV_FUNC_ARMOUR_LIGHT, INVALID_PARAM,
		"Элемент индивидуальной защиты человека, обеспечивающий защиту верхней части туловища.", false},
	
	{110, INV_ATTACH, "Тяжелый бронежилет", 19515, 0.0, -90.0, 0.0, 0.9, INV_FUNC_ARMOUR_HEAVY, INVALID_PARAM,
		"Элемент индивидуальной защиты человека, обеспечивающий защиту верхней части туловища.", false},
		
		
	{111, INV_CHEMICAL, "Химический раствор", 19570, -10.0, -10.0, 0.0, 0.9, INVALID_PARAM, INVALID_PARAM,
		"Химическая однородная смесь, состоящая из частиц определенного растворённого вещества.", false},
		
		
	{112, INV_LIGHTER, "Зажигалка", 19995, 90.0, 0.0, 10.0, 0.8, INVALID_PARAM, INVALID_PARAM,
		"Устройство для получения огня.", false},
		
		
	{113, INV_WEAPON_SMALL, "Кастет", 331, 90.0, 0.0, 10.0, 0.8, WEAPON_BRASSKNUCKLE, INVALID_PARAM,
		"Контактное ударно-раздробляющее оружие для кулачного боя из твёрдого материала.", false},
		
		
	{114, INV_DRUGS, "Марихуана", 3027, 90.0, 0.0, 10.0, 0.8, INV_FUNC_MARIJUANA, INVALID_PARAM,
		"Пакет с высушенной травкой.", false},
		
	{115, INV_DRUGS, "ЛСД", 2709, 90.0, 0.0, 10.0, 0.8, INV_FUNC_LSD, INVALID_PARAM,
		"Баночка с таблетками.", false},
	
	{116, INV_DRUGS, "Кокаин", 1575, 90.0, 0.0, 10.0, 0.8, INV_FUNC_COCAINE, INVALID_PARAM,
		"Пакет с белым порошком.", false}, 
		
		
	{117, INV_WEAPON_SMALL, "Аэрозольный баллончик", 365, 0.0, -30.0, 0.0, 1.5, WEAPON_SPRAYCAN, INVALID_PARAM,
		"Устройство для распыления жидких веществ или краски, применяемое преимущественно в быту.", true},
	
	{118, INV_WEAPON_SMALL, "Фотоаппарат", 367, 0.0, -30.0, 0.0, 1.5, WEAPON_CAMERA, INVALID_PARAM,
		"Устройство для регистрации неподвижных изображений.", true},
		
	{119, INV_WEAPON_SMALL, "Парашют", 367, 0.0, -30.0, 0.0, 1.5, WEAPON_PARACHUTE, INVALID_PARAM,
		"Устройство служит для замедления движения предмета в воздухе.", true}
};
