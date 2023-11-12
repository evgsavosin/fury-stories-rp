/*!
	@brief Заголовок системы транспорта
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
*/

#define GetFuelRate(%0)					floatabs(vehicle_info[%0-400][v_fuel_rate]-(vehicle_info[%0-400][v_max_fuel]*0.05))

/// Расход топлива по типам транспорта
#define TYPE_FUEL_NONE  				0/// велосипеды, прицепы и пр.
#define TYPE_FUEL_CAR 					25 /// легковые
#define TYPE_FUEL_AIR 					50 /// вертолеты - самолеты
#define TYPE_FUEL_BOAT 	 				5 /// лодка
#define TYPE_FUEL_SUV  					19 /// внедорожник
#define TYPE_FUEL_SUPERCAR  			16 /// спорт/супер-кар
#define TYPE_FUEL_MOTO  				45 /// мотоциклы

/// Сортировка транспорта по категориям аренды
enum 
{
	RENT_NONE,
	RENT_CAR,
	RENT_MOTO,
	RENT_SPECIAL,
	RENT_FLY,
	RENT_WATER
}

/// Сортировка транспорта по автосалонам
enum 
{
	NOT_SALE, // не продается
	SALE_CAR, // продается в обычном автосалоне
	SALE_MOTO, // продается в мотосалоне
	SALE_BIKE, // продается на велорынке
}

enum E_VEHICLE_INFO
{
	v_name						[	32	], /// имя
	v_type						[	32	], /// тип
	v_drive						[	32	], /// привод
	v_cost,	/// цена
	v_seat, /// дополнительные места. если отсутствуют, то 0
	Float: v_max_fuel, /// максимальная вместительность бака в галлонах (приблизительная)
	v_comp_max_slots, /// слоты в бардачке
	v_max_slots, /// слотов от 0 до 10.
	v_fuel_rate, /// расход
	v_sale,
	v_rent,
}

new const vehicle_info			[][E_VEHICLE_INFO] = 
{
	{"Landstalker", "Внедорожник", "Полный", 16_000, 0, 25.0, 3, 7, TYPE_FUEL_SUV, SALE_CAR, RENT_NONE}, // 400
	{"Bravura", "Седан", "Передний", 3_200, 0, 19.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 401
	{"Buffalo", "Спорт-кар", "Задний", 38_400, 0, 19.0, 3, 4, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 402
	{"Linerunner", "Грузовик", "Задний", 50_000, 1, 250.0, 3, 0, TYPE_FUEL_SUV, SALE_CAR, RENT_SPECIAL}, // 403
	{"Perennial", "Универсал", "Передний", 3_700, 0, 15.0, 3, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 404
	{"Sentinel", "Седан", "Задний", 10_400, 0, 19.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 405
	{"Dumper", "Самосвал", "Задний", 250_000, 2, 1100.0, 3, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 406
	{"Firetruck", "Спецтранспорт", "Задний", 190_000, 8, 110.0, 3, 10, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 407
	{"Trashmaster", "Мусоровоз", "Задний", 32_000, 0, 80.0, 3, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 408
	{"Stretch", "Лимузин", "Задний", 48_700, 4, 25.0, 3, 3, TYPE_FUEL_CAR, NOT_SALE, RENT_CAR}, // 409
	{"Manana", "Купе", "Передний", 3_650, 0, 17.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 410
	{"Infernus", "Суперкар", "Полный", 410_650, 0, 19.0, 3, 2, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 411
	{"Voodoo", "Купе", "Задний", 4_500, 0, 21.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 412
	{"Pony", "Фургон", "Задний", 7_300, 2, 24.0, 3, 9, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 413
	{"Mule", "Фургон", "Задний", 15_000, 0, 57.0, 3, 10, TYPE_FUEL_SUV, SALE_CAR, RENT_SPECIAL}, // 414
	{"Cheetah", "Спорт-кар", "Задний", 335_000, 0, 22.0, 3, 2, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 415
	{"Ambulance", "Спецтранспорт", "Задний", 55_000, 4, 52.0, 2, 10, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 416
	{"Leviathan", "Вертолёт", "Двухдвигательный", 2_000_000, 16, 1100.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 417
	{"Moonbeam", "Минивэн", "Задний", 6_600, 0, 25.0, 3, 10, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 418
	{"Esperanto", "Купе", "Задний", 9_800, 0, 15.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 419
	{"Taxi", "Седан", "Передний", 12_000, 0, 18.0, 3, 5, TYPE_FUEL_CAR, NOT_SALE, RENT_SPECIAL}, // 420
	{"Washington", "Седан", "Задний", 23_000, 0, 21.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 421
	{"Bobcat", "Пикап", "Полный", 9_500, 0, 17.0, 3, 8, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 422
	{"Mr. Whoopee", "Спецтранспорт", "Полный", 38_000, 4, 17.0, 3, 12, TYPE_FUEL_CAR, NOT_SALE, RENT_CAR}, // 423
	{"BF Injection", "Багги", "Задний", 15_200, 0, 30.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 424
	{"Hunter", "Вертолёт", "Двухдвигательный", 0, 2, 720.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 425
	{"Premier", "Седан", "Задний", 17_200, 1, 18.0, 0, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 426
	{"Enforcer", "Спецтранспорт", "Задний", 160_000, 12, 70.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 427
	{"Securicar", "Спецтранспорт", "Задний", 100_000, 8, 65.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 428
	{"Banshee", "Спорт-кар", "Задний", 110_000, 0, 16.0, 2, 3, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 429
	{"Predator", "Катер", "Двухмоторный", 400_000, 0, 800.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_NONE}, // 430
	{"Bus", "Автобус", "Задний", 23_000, 30, 42.0, 0, 8, TYPE_FUEL_SUV, NOT_SALE, RENT_CAR}, // 431
	{"Rhino", "Спецтранспорт", "Полный", 0, 4, 48.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 432
	{"Barracks", "Бортовой", "Полный", 50_000, 14, 56.0, 2, 8, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 433
	{"Hotknife", "Хот-род", "Задний", 82_000, 0, 15.0, 2, 3, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 434
	{"Article Trailer", "Прицеп", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 435
	{"Previon", "Купе", "Передний", 4_100, 0, 13.0, 2, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 436
	{"Coach", "Автобус", "Задний", 32_000, 32, 42.0, 0, 8, TYPE_FUEL_SUV, NOT_SALE, RENT_CAR}, // 431
	{"Cabbie", "Седан", "Задний", 15_400, 0, 17.0, 2, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_SPECIAL}, // 438
	{"Stallion", "Кабриолет", "Задний", 14_000, 0, 16.0, 2, 3, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 439
	{"Rumpo", "Фургон", "Передний", 9_500, 2, 21.0, 3, 10, TYPE_FUEL_CAR, NOT_SALE, RENT_CAR}, // 440
	{"RC Bandit", "Игрушка", "Задний", 0, 0, 0.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 441
	{"Romero", "Катафалк", "Задний", 18_000, 2, 14.0, 2, 6, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 442
	{"Packer", "Грузовик", "Задний", 37_000, 0, 44.0, 2, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 443
	{"Monster", "Монстр", "Полный", 0, 0, 39.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 444
	{"Admiral", "Седан", "Передний", 22_800, 0, 20.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 445
	{"Squallo", "Катер", "Двухмоторный", 249_250, 0, 780.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_WATER}, // 446
	{"Seasparrow", "Вертолёт", "Однодвигательный", 0, 0, 480.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 447
	{"Pizzaboy", "Мопед", "Задний", 1_200, 0, 3.5, 1, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 448
	{"Tram", "Трамвай", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 449
	{"Article Trailer 2", "Прицеп", "Нет", 600, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 450
	{"Turismo", "Спорт-кар", "Полный", 325_000, 0, 19.0, 2, 2, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 451
	{"Speeder", "Катер", "Двухмоторный", 210_500, 0, 720.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_NONE}, // 452
	{"Reefer", "Лодка", "Одномоторный", 36_000, 0, 600.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_NONE}, // 453
	{"Tropic", "Яхта", "Одномоторный", 170_000, 0, 1100.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_WATER}, // 454
	{"Flatbed", "Бортовой", "Задний", 36_000, 14, 75.0, 2, 8, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 455
	{"Yankee", "Фургон", "Задний", 31_600, 8, 41.0, 3, 10, TYPE_FUEL_SUV, NOT_SALE, RENT_SPECIAL}, // 456
	{"Caddy", "Гольфкар", "Полный", 10_000, 0, 10.0, 2, 2, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 457
	{"Solair", "Универсал", "Задний", 13_000, 0, 19.0, 0, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 458
	{"Topfun Van (Berkley's RC)", "Фургон", "Задний", 11_200, 2, 23.0, 2, 10, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 459
	{"Skimmer", "Самолёт", "Турбовинтовой", 576_200, 0, 500.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 460
	{"PCJ-600", "Мотоцикл", "Задний", 18_900, 0, 6.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_NONE}, // 461
	{"Faggio", "Мопед", "Задний", 1_100, 0, 3.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_NONE}, // 462
	{"Freeway", "Байк", "Задний", 12_300, 0, 7.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_NONE}, // 463
	{"RC Baron", "Игрушка", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 464
	{"RC Raider", "Игрушка", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 465
	{"Glendale", "Седан", "Задний", 8_100, 0, 17.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 466
	{"Oceanic", "Седан", "Задний", 7_900, 0, 17.5, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 467
	{"Sanchez", "Мотоцикл", "Задний", 7_000, 0, 8.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_NONE}, // 468
	{"Sparrow", "Вертолёт", "Однодвигательный", 520_000, 0, 480.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 469
	{"Patriot", "Внедорожник", "Полный", 62_000, 0, 35.0, 3, 2, TYPE_FUEL_SUV, SALE_CAR, RENT_NONE}, // 470
	{"Quad", "Квадроцикл", "Задний", 2_800, 0, 8.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_MOTO}, // 471
	{"Coastguard", "Катер", "Двухмоторный", 450_000, 0, 680.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_NONE}, // 472
	{"Dinghy", "Лодка", "Двухмоторный", 19_000, 0, 120.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_WATER}, // 473
	{"Hermes", "Купе", "Передний", 23_000, 0, 14.0, 3, 4, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 474
	{"Sabre", "Маслкар", "Задний", 16_000, 0, 17.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 475
	{"Rustler", "Самолёт", "Турбовинтовый", 360_000, 1, 700.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 476
	{"ZR-350", "Спорт-кар", "Задний", 70_000, 0, 17.0, 2, 5, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 477
	{"Walton", "Пикап", "Задний", 2_900, 0, 14.0, 2, 7, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 478
	{"Regina", "Универсал", "Передний", 6_800, 0, 15.0, 3, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 479
	{"Comet", "Спорт-кар", "Задний", 85_000, 0, 16.0, 2, 4, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 480
	{"BMX", "Велосипед", "Нет", 200, 0, 0.0, 0, 0, TYPE_FUEL_NONE, SALE_BIKE, RENT_NONE}, // 481
	{"Burrito", "Фургон", "Задний", 26_000, 0, 22.0, 2, 10, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 482
	{"Camper", "Минивэн", "Задний", 9_000, 3, 16.0, 2, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 483
	{"Marquis", "Яхта", "Одномоторный", 210_000, 0, 1200.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_NONE}, // 484
	{"Baggage", "Спецтранспорт", "Задний", 16_000, 0, 7.0, 3, 2, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 485
	{"Dozer", "Бульдозер", "Полный", 38_000, 0, 34.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 486
	{"Maverick", "Вертолёт", "Однодвигательный", 1_050_000, 6, 530.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_FLY}, // 487
	{"SANMav", "Вертолёт", "Однодвигательный", 1_060_000, 2, 17.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 488
	{"Rancher A", "Внедорожник", "Полный", 13_000, 0, 26.0, 3, 6, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 489
	{"FBI Rancher", "Внедорожник", "Полный", 47_000, 0, 32.0, 3, 7, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 490
	{"Virgo", "Купе", "Задний", 11_000, 0, 16.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 491
	{"Greenwood", "Седан", "Задний", 12_000, 0, 17.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 492
	{"Jetmax", "Катер", "Двухмоторный", 263_000, 0, 800.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_WATER}, // 493
	{"Hotring Racer", "Спорткар", "Задний", 80_000, 0, 18.0, 1, 3, TYPE_FUEL_SUPERCAR, NOT_SALE, RENT_NONE}, // 494
	{"Sandking", "Внедорожник", "Задний", 90_000, 0, 25.0, 1, 4, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 495
	{"Blista Compact", "Седан", "Задний", 8_000, 0, 16.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 496
	{"POLMav", "Вертолёт", "Двухдвигательный", 1_600_000, 8, 490.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 497
	{"Boxville", "Фургон", "Задний", 25_000, 0, 23.0, 2, 10, TYPE_FUEL_SUV, NOT_SALE, RENT_SPECIAL}, // 498
	{"Benson", "Фургон", "Задний", 20_000, 0, 24.0, 3, 10, TYPE_FUEL_SUV, NOT_SALE, RENT_SPECIAL}, // 499
	{"Mesa", "Внедорожник", "Задний", 22_000, 0, 25.0, 3, 6, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 500
	{"RC Goblin", "Игрушка", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 501
	{"Hotring Racer A", "Суперкар", "полный", 79_000, 0, 18.0, 1, 3, TYPE_FUEL_SUPERCAR, NOT_SALE, RENT_NONE}, // 502
	{"Hotring Racer B", "Суперкар", "Полный", 78_000, 0, 18.0, 1, 3, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 503
	{"Bloodring Banger", "Суперкар", "Задний", 65_000, 0, 16.0, 1, 2, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 504
	{"Rancher B", "Внедорожник", "Полный", 13_200, 0, 23.0, 3, 7, TYPE_FUEL_SUV, SALE_CAR, RENT_NONE}, // 505
	{"Super GT", "Спорткар", "Задний", 210_000, 0, 18.0, 2, 4, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 506
	{"Elegant", "Седан", "Задний", 12_000, 0, 16.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 507
	{"Journey", "Дом на колёсах", "Задний", 16_000, 4, 26.0, 1, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 508
	{"Bike", "Велосипед", "Нет", 100, 0, 0.0, 0, 0, TYPE_FUEL_NONE, SALE_BIKE, RENT_NONE}, // 509
	{"Mountain Bike", "Велосипед", "Нет", 250, 0, 0.0, 0, 0, TYPE_FUEL_NONE, SALE_BIKE, RENT_NONE}, // 510
	{"Beagle", "Самолёт", "Двухтурбовинтовой", 240_000, 4, 710.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 511
	{"Cropduster", "Самолёт", "Турбовинтовой", 130_000, 0, 500.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 512
	{"Stuntplane", "Самолёт", "Турбовинтовой", 140_000, 0, 510.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 513
	{"Tanker", "Грузовик", "Задний", 39_000, 2, 230.0, 3, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_SPECIAL}, // 514
	{"Roadtraint", "Грузовик", "Задний", 36_000, 2, 248.0, 3, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_SPECIAL}, // 515
	{"Nebula", "Седан", "Передний", 13_500, 0, 15.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 516
	{"Majestic", "Купе", "Задний", 9_000, 0, 15.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 517
	{"Buccaneer", "Купе", "Задний", 4_300, 0, 14.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 518
	{"Shamal", "Самолёт", "Реактивный", 1_400_000, 0, 960.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 519
	{"Hydra", "Истребитель", "Реактивный", 2_500_000, 0, 1200.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 520
	{"FCR-900", "Мотоцикл", "Задний", 27_000, 0, 8.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_NONE}, // 521
	{"NRG-500", "Мотоцикл", "Задний", 63_000, 0, 9.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_NONE}, // 522
	{"HPV1000", "Мотоцикл", "Задний", 22_000, 0, 10.0, 1, 0, TYPE_FUEL_MOTO, NOT_SALE, RENT_NONE}, // 523
	{"Cement Truck", "Грузовик", "Задний", 27_000, 2, 31.0, 2, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 524
	{"Towtruck", "Эвакуатор", "Задний", 17_000, 0, 18.0, 2, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 525
	{"Fortune", "Купе", "Задний", 16_000, 0, 19.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 526
	{"Cadrona", "Купе", "Задний", 9_500, 0, 16.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 527
	{"FBI Truck", "Спецтранспорт", "Полный", 140_000, 0, 26.0, 1, 6, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 528
	{"Willard", "Седан", "Задний", 10_000, 0, 16.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 529
	{"Forklift", "Спецтранспорт", "Передний", 6_000, 0, 10.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 530
	{"Tractor", "Трактор", "Задний", 2_500, 0, 11.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 531
	{"Combine Harvester", "Комбайн", "Полный", 21_000, 0, 18.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 532
	{"Feltzer", "Кабриолет", "Задний", 24_000, 0, 17.0, 2, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 533
	{"Remington", "Купе", "Задний", 14_000, 0, 16.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 534
	{"Slamvan", "Хот-род", "Задний", 25_000, 0, 19.0, 3, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 535
	{"Blade", "Кабриолет", "Задний", 15_100, 0, 17.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 536
	{"Freight", "Поезд", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 537
	{"Brownstreak", "Поезд", "Нет", 24_000, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 538
	{"Vortex", "СВП", "Задний", 60_000, 0, 11.0, 3, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_NONE}, // 539
	{"Vincent", "Седан", "Передний", 14_000, 0, 17.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 540
	{"Bullet", "Спорткар", "Задний", 310_000, 0, 18.0, 3, 2, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_CAR}, // 541
	{"Clover", "Маслкар", "Задний", 6_500, 0, 18.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 542
	{"Sadler", "Пикап", "Задний", 4_200, 0, 17.0, 3, 8, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 543
	{"Firetruck LA", "Спецтранспорт", "Задний", 120_000, 10, 32.0, 3, 10, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 544
	{"Hustler", "Хот-род", "Задний", 93_000, 0, 19.0, 2, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 545
	{"Intruder", "Седан", "Задний", 5_800, 0, 17.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 546
	{"Primo", "Седан", "Задний", 10_200, 0, 18.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 547
	{"Cargobob", "Вертолёт", "Двухдвигательный", 2_100_000, 0, 18.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 548
	{"Tampa", "Маслкар", "Задний", 3_300, 0, 17.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 549
	{"Sunrise", "Седан", "Передний", 20_000, 0, 18.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 550
	{"Merit", "Седан", "Задний", 22_000, 0, 18.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 551
	{"Utility Van", "Пикап", "Задний", 20_900, 0, 19.0, 3, 8, TYPE_FUEL_CAR, NOT_SALE, RENT_CAR}, // 552
	{"Nevada", "Самолёт", "Двухтурбовинтовой", 1_650_500, 50, 520.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 553
	{"Yosemite", "Пикап", "Задний", 35_000, 0, 28.0, 3, 8, TYPE_FUEL_SUV, SALE_CAR, RENT_NONE}, // 554
	{"Windsor", "Кабриолет", "Задний", 110_000, 0, 17.0, 3, 3, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 555
	{"Monster A", "Монстр-трак", "Полный", 0, 0, 40.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 556
	{"Monster В", "Монстр-трак", "Полный", 0, 0, 40.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 557
	{"Uranus", "Спорткар", "Задний", 34_000, 0, 19.0, 3, 4, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_CAR}, // 558
	{"Jester", "Спорткар", "Передний", 41_000, 0, 18.0, 3, 4, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 559
	{"Sultan", "Седан", "Полный", 47_200, 0, 20.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 560
	{"Stratum", "Универсал", "Задний", 32_000, 0, 19.0, 3, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 561
	{"Elegy", "Купе", "Задний", 52_000, 0, 19.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 562
	{"Raindance", "Вертолёт", "Двухдвигательный", 1_400_500, 15, 900.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 563
	{"RC Tiger", "Игрушка", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 564
	{"Flash", "Спорткар", "Передний", 43_200, 0, 17.0, 2, 3, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 565
	{"Tahoma", "Седан", "Задний", 16_000, 0, 19.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 566
	{"Savanna", "Кабриолет", "Задний", 14_000, 0, 19.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 567
	{"Bandito", "Багги", "Задний", 12_000, 0, 15.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 568
	{"Freight Flat Traile", "Прицеп", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 569
	{"Streak Traile", "Прицеп", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 570
	{"Kart", "Карт", "Задний", 3_200, 0, 6.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 571
	{"Mower", "Газонокосилка", "Передний", 2_100, 0, 5.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 572
	{"Dune", "Спорткар", "Полный", 90_000, 0, 36.0, 2, 5, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 573
	{"Sweeper", "Спецтранспорт", "Передний", 9_000, 0, 12.0, 1, 5, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 574
	{"Broadway", "Кабриолет", "Задний", 90_000, 0, 17.0, 2, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 575
	{"Tornado", "Купе", "Задний", 95_000, 0, 19.0, 2, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 576
	{"AT400", "Самолёт", "Реактивный", 2_235_000, 70, 2100.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 577
	{"DFT-30", "Грузовик", "Задний", 32_000, 0, 31.0, 2, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 578
	{"Huntley", "Внедорожник", "Полный", 45_000, 0, 24.0, 3, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 579
	{"Stafford", "Седан", "Задний", 30_000, 0, 20.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 580
	{"BF-400", "Мотоцкил", "Задний", 20_000, 0, 7.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_NONE}, // 581
	{"Newsvan", "Фургон", "Задний", 21_000, 2, 19.0, 3, 10, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 582
	{"Tug", "Спецтранспорт", "Задний", 4_000, 0, 11.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 583
	{"Petrol Trailer", "Прицеп", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 584
	{"Emperor", "Седан", "Задний", 12_000, 0, 17.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 585
	{"Wayfarer", "Мотоцикл", "Задний", 14_000, 0, 7.0, 4, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_MOTO}, // 586
	{"Euros", "Спорткар", "Полный", 38_000, 0, 19.0, 3, 6, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_CAR}, // 587
	{"Hotdog", "Спецтранспорт", "Задний", 18_200, 0, 20.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 588
	{"Club", "Хэтчбек", "Передний", 22_200, 0, 17.0, 2, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 589
	{"Freight Box Trailer", "Прицеп", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 590
	{"Article Trailer 3", "Прицеп", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 591
	{"Andromada", "Самолёт", "Реактивный", 2_500_000, 100, 2300.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 592
	{"Dodo", "Самолёт", "Турбовинтовый", 420_000, 0, 420.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_FLY}, // 593
	{"RC Cam", "Игрушка", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 594
	{"Launch", "Катер", "Двухмоторный", 190_000, 0, 690.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_NONE}, // 595
	{"Police Car(LS)", "Седан", "Задний", 33_000, 0, 20.0, 4, 6, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 596
	{"Police Car(SF)", "Седан", "Задний", 33_000, 0, 20.0, 4, 6, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 597
	{"Police Car(LV)", "Седан", "Задний", 33_000, 0, 20.0, 4, 6, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 598
	{"Police Ranger", "Внедорожник", "Полный", 35_000, 0, 28.0, 4, 8, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 599
	{"Picador", "Пикап", "Задний", 3_800, 0, 17.0, 3, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 600
	{"S.W.A.T.", "Спецтранспорт", "Полный", 320_000, 6, 30.0, 4, 3, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 601
	{"Alpha", "Купе", "Задний", 35_000, 0, 18.0, 3, 5, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 602
	{"Phoenix", "Маслкар", "Задний", 42_000, 0, 19.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 603
	{"Glendale", "Седан", "Задний", 0, 0, 19.0, 3, 3, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 604
	{"Sadler", "Пикап", "Задний", 0, 0, 19.0, 0, 6, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 605
	{"Luggage Trailer A", "Прицеп", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 606
	{"Luggage Trailer B", "Прицеп", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 607
	{"Stair Trailer", "Прицеп", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 608
	{"Boxville", "Фургон", "Задний", 26_000, 0, 23.0, 0, 10, TYPE_FUEL_SUV, NOT_SALE, RENT_SPECIAL}, // 609
	{"Farm Trailer", "Прицеп", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 610
	{"Utility Trailer", "Прицеп", "Нет", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE} // 611
};