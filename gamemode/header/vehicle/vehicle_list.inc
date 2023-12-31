/*!
	@brief ��������� ������� ����������
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
*/

#define GetFuelRate(%0)					floatabs(vehicle_info[%0-400][v_fuel_rate]-(vehicle_info[%0-400][v_max_fuel]*0.05))

/// ������ ������� �� ����� ����������
#define TYPE_FUEL_NONE  				0/// ����������, ������� � ��.
#define TYPE_FUEL_CAR 					25 /// ��������
#define TYPE_FUEL_AIR 					50 /// ��������� - ��������
#define TYPE_FUEL_BOAT 	 				5 /// �����
#define TYPE_FUEL_SUV  					19 /// �����������
#define TYPE_FUEL_SUPERCAR  			16 /// �����/�����-���
#define TYPE_FUEL_MOTO  				45 /// ���������

/// ���������� ���������� �� ���������� ������
enum 
{
	RENT_NONE,
	RENT_CAR,
	RENT_MOTO,
	RENT_SPECIAL,
	RENT_FLY,
	RENT_WATER
}

/// ���������� ���������� �� �����������
enum 
{
	NOT_SALE, // �� ���������
	SALE_CAR, // ��������� � ������� ����������
	SALE_MOTO, // ��������� � ����������
	SALE_BIKE, // ��������� �� ���������
}

enum E_VEHICLE_INFO
{
	v_name						[	32	], /// ���
	v_type						[	32	], /// ���
	v_drive						[	32	], /// ������
	v_cost,	/// ����
	v_seat, /// �������������� �����. ���� �����������, �� 0
	Float: v_max_fuel, /// ������������ ��������������� ���� � �������� (���������������)
	v_comp_max_slots, /// ����� � ��������
	v_max_slots, /// ������ �� 0 �� 10.
	v_fuel_rate, /// ������
	v_sale,
	v_rent,
}

new const vehicle_info			[][E_VEHICLE_INFO] = 
{
	{"Landstalker", "�����������", "������", 16_000, 0, 25.0, 3, 7, TYPE_FUEL_SUV, SALE_CAR, RENT_NONE}, // 400
	{"Bravura", "�����", "��������", 3_200, 0, 19.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 401
	{"Buffalo", "�����-���", "������", 38_400, 0, 19.0, 3, 4, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 402
	{"Linerunner", "��������", "������", 50_000, 1, 250.0, 3, 0, TYPE_FUEL_SUV, SALE_CAR, RENT_SPECIAL}, // 403
	{"Perennial", "���������", "��������", 3_700, 0, 15.0, 3, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 404
	{"Sentinel", "�����", "������", 10_400, 0, 19.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 405
	{"Dumper", "��������", "������", 250_000, 2, 1100.0, 3, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 406
	{"Firetruck", "�������������", "������", 190_000, 8, 110.0, 3, 10, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 407
	{"Trashmaster", "���������", "������", 32_000, 0, 80.0, 3, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 408
	{"Stretch", "�������", "������", 48_700, 4, 25.0, 3, 3, TYPE_FUEL_CAR, NOT_SALE, RENT_CAR}, // 409
	{"Manana", "����", "��������", 3_650, 0, 17.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 410
	{"Infernus", "��������", "������", 410_650, 0, 19.0, 3, 2, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 411
	{"Voodoo", "����", "������", 4_500, 0, 21.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 412
	{"Pony", "������", "������", 7_300, 2, 24.0, 3, 9, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 413
	{"Mule", "������", "������", 15_000, 0, 57.0, 3, 10, TYPE_FUEL_SUV, SALE_CAR, RENT_SPECIAL}, // 414
	{"Cheetah", "�����-���", "������", 335_000, 0, 22.0, 3, 2, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 415
	{"Ambulance", "�������������", "������", 55_000, 4, 52.0, 2, 10, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 416
	{"Leviathan", "�������", "����������������", 2_000_000, 16, 1100.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 417
	{"Moonbeam", "�������", "������", 6_600, 0, 25.0, 3, 10, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 418
	{"Esperanto", "����", "������", 9_800, 0, 15.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 419
	{"Taxi", "�����", "��������", 12_000, 0, 18.0, 3, 5, TYPE_FUEL_CAR, NOT_SALE, RENT_SPECIAL}, // 420
	{"Washington", "�����", "������", 23_000, 0, 21.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 421
	{"Bobcat", "�����", "������", 9_500, 0, 17.0, 3, 8, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 422
	{"Mr. Whoopee", "�������������", "������", 38_000, 4, 17.0, 3, 12, TYPE_FUEL_CAR, NOT_SALE, RENT_CAR}, // 423
	{"BF Injection", "�����", "������", 15_200, 0, 30.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 424
	{"Hunter", "�������", "����������������", 0, 2, 720.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 425
	{"Premier", "�����", "������", 17_200, 1, 18.0, 0, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 426
	{"Enforcer", "�������������", "������", 160_000, 12, 70.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 427
	{"Securicar", "�������������", "������", 100_000, 8, 65.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 428
	{"Banshee", "�����-���", "������", 110_000, 0, 16.0, 2, 3, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 429
	{"Predator", "�����", "������������", 400_000, 0, 800.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_NONE}, // 430
	{"Bus", "�������", "������", 23_000, 30, 42.0, 0, 8, TYPE_FUEL_SUV, NOT_SALE, RENT_CAR}, // 431
	{"Rhino", "�������������", "������", 0, 4, 48.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 432
	{"Barracks", "��������", "������", 50_000, 14, 56.0, 2, 8, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 433
	{"Hotknife", "���-���", "������", 82_000, 0, 15.0, 2, 3, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 434
	{"Article Trailer", "������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 435
	{"Previon", "����", "��������", 4_100, 0, 13.0, 2, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 436
	{"Coach", "�������", "������", 32_000, 32, 42.0, 0, 8, TYPE_FUEL_SUV, NOT_SALE, RENT_CAR}, // 431
	{"Cabbie", "�����", "������", 15_400, 0, 17.0, 2, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_SPECIAL}, // 438
	{"Stallion", "���������", "������", 14_000, 0, 16.0, 2, 3, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 439
	{"Rumpo", "������", "��������", 9_500, 2, 21.0, 3, 10, TYPE_FUEL_CAR, NOT_SALE, RENT_CAR}, // 440
	{"RC Bandit", "�������", "������", 0, 0, 0.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 441
	{"Romero", "��������", "������", 18_000, 2, 14.0, 2, 6, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 442
	{"Packer", "��������", "������", 37_000, 0, 44.0, 2, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 443
	{"Monster", "������", "������", 0, 0, 39.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 444
	{"Admiral", "�����", "��������", 22_800, 0, 20.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 445
	{"Squallo", "�����", "������������", 249_250, 0, 780.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_WATER}, // 446
	{"Seasparrow", "�������", "����������������", 0, 0, 480.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 447
	{"Pizzaboy", "�����", "������", 1_200, 0, 3.5, 1, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 448
	{"Tram", "�������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 449
	{"Article Trailer 2", "������", "���", 600, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 450
	{"Turismo", "�����-���", "������", 325_000, 0, 19.0, 2, 2, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 451
	{"Speeder", "�����", "������������", 210_500, 0, 720.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_NONE}, // 452
	{"Reefer", "�����", "������������", 36_000, 0, 600.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_NONE}, // 453
	{"Tropic", "����", "������������", 170_000, 0, 1100.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_WATER}, // 454
	{"Flatbed", "��������", "������", 36_000, 14, 75.0, 2, 8, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 455
	{"Yankee", "������", "������", 31_600, 8, 41.0, 3, 10, TYPE_FUEL_SUV, NOT_SALE, RENT_SPECIAL}, // 456
	{"Caddy", "��������", "������", 10_000, 0, 10.0, 2, 2, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 457
	{"Solair", "���������", "������", 13_000, 0, 19.0, 0, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 458
	{"Topfun Van (Berkley's RC)", "������", "������", 11_200, 2, 23.0, 2, 10, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 459
	{"Skimmer", "������", "�������������", 576_200, 0, 500.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 460
	{"PCJ-600", "��������", "������", 18_900, 0, 6.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_NONE}, // 461
	{"Faggio", "�����", "������", 1_100, 0, 3.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_NONE}, // 462
	{"Freeway", "����", "������", 12_300, 0, 7.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_NONE}, // 463
	{"RC Baron", "�������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 464
	{"RC Raider", "�������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 465
	{"Glendale", "�����", "������", 8_100, 0, 17.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 466
	{"Oceanic", "�����", "������", 7_900, 0, 17.5, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 467
	{"Sanchez", "��������", "������", 7_000, 0, 8.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_NONE}, // 468
	{"Sparrow", "�������", "����������������", 520_000, 0, 480.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 469
	{"Patriot", "�����������", "������", 62_000, 0, 35.0, 3, 2, TYPE_FUEL_SUV, SALE_CAR, RENT_NONE}, // 470
	{"Quad", "����������", "������", 2_800, 0, 8.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_MOTO}, // 471
	{"Coastguard", "�����", "������������", 450_000, 0, 680.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_NONE}, // 472
	{"Dinghy", "�����", "������������", 19_000, 0, 120.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_WATER}, // 473
	{"Hermes", "����", "��������", 23_000, 0, 14.0, 3, 4, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 474
	{"Sabre", "�������", "������", 16_000, 0, 17.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 475
	{"Rustler", "������", "�������������", 360_000, 1, 700.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 476
	{"ZR-350", "�����-���", "������", 70_000, 0, 17.0, 2, 5, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 477
	{"Walton", "�����", "������", 2_900, 0, 14.0, 2, 7, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 478
	{"Regina", "���������", "��������", 6_800, 0, 15.0, 3, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 479
	{"Comet", "�����-���", "������", 85_000, 0, 16.0, 2, 4, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 480
	{"BMX", "���������", "���", 200, 0, 0.0, 0, 0, TYPE_FUEL_NONE, SALE_BIKE, RENT_NONE}, // 481
	{"Burrito", "������", "������", 26_000, 0, 22.0, 2, 10, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 482
	{"Camper", "�������", "������", 9_000, 3, 16.0, 2, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 483
	{"Marquis", "����", "������������", 210_000, 0, 1200.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_NONE}, // 484
	{"Baggage", "�������������", "������", 16_000, 0, 7.0, 3, 2, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 485
	{"Dozer", "���������", "������", 38_000, 0, 34.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 486
	{"Maverick", "�������", "����������������", 1_050_000, 6, 530.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_FLY}, // 487
	{"SANMav", "�������", "����������������", 1_060_000, 2, 17.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 488
	{"Rancher A", "�����������", "������", 13_000, 0, 26.0, 3, 6, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 489
	{"FBI Rancher", "�����������", "������", 47_000, 0, 32.0, 3, 7, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 490
	{"Virgo", "����", "������", 11_000, 0, 16.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 491
	{"Greenwood", "�����", "������", 12_000, 0, 17.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 492
	{"Jetmax", "�����", "������������", 263_000, 0, 800.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_WATER}, // 493
	{"Hotring Racer", "��������", "������", 80_000, 0, 18.0, 1, 3, TYPE_FUEL_SUPERCAR, NOT_SALE, RENT_NONE}, // 494
	{"Sandking", "�����������", "������", 90_000, 0, 25.0, 1, 4, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 495
	{"Blista Compact", "�����", "������", 8_000, 0, 16.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 496
	{"POLMav", "�������", "����������������", 1_600_000, 8, 490.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 497
	{"Boxville", "������", "������", 25_000, 0, 23.0, 2, 10, TYPE_FUEL_SUV, NOT_SALE, RENT_SPECIAL}, // 498
	{"Benson", "������", "������", 20_000, 0, 24.0, 3, 10, TYPE_FUEL_SUV, NOT_SALE, RENT_SPECIAL}, // 499
	{"Mesa", "�����������", "������", 22_000, 0, 25.0, 3, 6, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 500
	{"RC Goblin", "�������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 501
	{"Hotring Racer A", "��������", "������", 79_000, 0, 18.0, 1, 3, TYPE_FUEL_SUPERCAR, NOT_SALE, RENT_NONE}, // 502
	{"Hotring Racer B", "��������", "������", 78_000, 0, 18.0, 1, 3, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 503
	{"Bloodring Banger", "��������", "������", 65_000, 0, 16.0, 1, 2, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 504
	{"Rancher B", "�����������", "������", 13_200, 0, 23.0, 3, 7, TYPE_FUEL_SUV, SALE_CAR, RENT_NONE}, // 505
	{"Super GT", "��������", "������", 210_000, 0, 18.0, 2, 4, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 506
	{"Elegant", "�����", "������", 12_000, 0, 16.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 507
	{"Journey", "��� �� ������", "������", 16_000, 4, 26.0, 1, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 508
	{"Bike", "���������", "���", 100, 0, 0.0, 0, 0, TYPE_FUEL_NONE, SALE_BIKE, RENT_NONE}, // 509
	{"Mountain Bike", "���������", "���", 250, 0, 0.0, 0, 0, TYPE_FUEL_NONE, SALE_BIKE, RENT_NONE}, // 510
	{"Beagle", "������", "�����������������", 240_000, 4, 710.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 511
	{"Cropduster", "������", "�������������", 130_000, 0, 500.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 512
	{"Stuntplane", "������", "�������������", 140_000, 0, 510.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 513
	{"Tanker", "��������", "������", 39_000, 2, 230.0, 3, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_SPECIAL}, // 514
	{"Roadtraint", "��������", "������", 36_000, 2, 248.0, 3, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_SPECIAL}, // 515
	{"Nebula", "�����", "��������", 13_500, 0, 15.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 516
	{"Majestic", "����", "������", 9_000, 0, 15.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 517
	{"Buccaneer", "����", "������", 4_300, 0, 14.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 518
	{"Shamal", "������", "����������", 1_400_000, 0, 960.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 519
	{"Hydra", "�����������", "����������", 2_500_000, 0, 1200.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 520
	{"FCR-900", "��������", "������", 27_000, 0, 8.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_NONE}, // 521
	{"NRG-500", "��������", "������", 63_000, 0, 9.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_NONE}, // 522
	{"HPV1000", "��������", "������", 22_000, 0, 10.0, 1, 0, TYPE_FUEL_MOTO, NOT_SALE, RENT_NONE}, // 523
	{"Cement Truck", "��������", "������", 27_000, 2, 31.0, 2, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 524
	{"Towtruck", "���������", "������", 17_000, 0, 18.0, 2, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 525
	{"Fortune", "����", "������", 16_000, 0, 19.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 526
	{"Cadrona", "����", "������", 9_500, 0, 16.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 527
	{"FBI Truck", "�������������", "������", 140_000, 0, 26.0, 1, 6, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 528
	{"Willard", "�����", "������", 10_000, 0, 16.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 529
	{"Forklift", "�������������", "��������", 6_000, 0, 10.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 530
	{"Tractor", "�������", "������", 2_500, 0, 11.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 531
	{"Combine Harvester", "�������", "������", 21_000, 0, 18.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 532
	{"Feltzer", "���������", "������", 24_000, 0, 17.0, 2, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 533
	{"Remington", "����", "������", 14_000, 0, 16.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 534
	{"Slamvan", "���-���", "������", 25_000, 0, 19.0, 3, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 535
	{"Blade", "���������", "������", 15_100, 0, 17.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 536
	{"Freight", "�����", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 537
	{"Brownstreak", "�����", "���", 24_000, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 538
	{"Vortex", "���", "������", 60_000, 0, 11.0, 3, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_NONE}, // 539
	{"Vincent", "�����", "��������", 14_000, 0, 17.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 540
	{"Bullet", "��������", "������", 310_000, 0, 18.0, 3, 2, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_CAR}, // 541
	{"Clover", "�������", "������", 6_500, 0, 18.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 542
	{"Sadler", "�����", "������", 4_200, 0, 17.0, 3, 8, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 543
	{"Firetruck LA", "�������������", "������", 120_000, 10, 32.0, 3, 10, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 544
	{"Hustler", "���-���", "������", 93_000, 0, 19.0, 2, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 545
	{"Intruder", "�����", "������", 5_800, 0, 17.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 546
	{"Primo", "�����", "������", 10_200, 0, 18.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 547
	{"Cargobob", "�������", "����������������", 2_100_000, 0, 18.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 548
	{"Tampa", "�������", "������", 3_300, 0, 17.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 549
	{"Sunrise", "�����", "��������", 20_000, 0, 18.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 550
	{"Merit", "�����", "������", 22_000, 0, 18.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 551
	{"Utility Van", "�����", "������", 20_900, 0, 19.0, 3, 8, TYPE_FUEL_CAR, NOT_SALE, RENT_CAR}, // 552
	{"Nevada", "������", "�����������������", 1_650_500, 50, 520.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 553
	{"Yosemite", "�����", "������", 35_000, 0, 28.0, 3, 8, TYPE_FUEL_SUV, SALE_CAR, RENT_NONE}, // 554
	{"Windsor", "���������", "������", 110_000, 0, 17.0, 3, 3, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 555
	{"Monster A", "������-����", "������", 0, 0, 40.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 556
	{"Monster �", "������-����", "������", 0, 0, 40.0, 0, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 557
	{"Uranus", "��������", "������", 34_000, 0, 19.0, 3, 4, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_CAR}, // 558
	{"Jester", "��������", "��������", 41_000, 0, 18.0, 3, 4, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 559
	{"Sultan", "�����", "������", 47_200, 0, 20.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 560
	{"Stratum", "���������", "������", 32_000, 0, 19.0, 3, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 561
	{"Elegy", "����", "������", 52_000, 0, 19.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 562
	{"Raindance", "�������", "����������������", 1_400_500, 15, 900.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 563
	{"RC Tiger", "�������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 564
	{"Flash", "��������", "��������", 43_200, 0, 17.0, 2, 3, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 565
	{"Tahoma", "�����", "������", 16_000, 0, 19.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 566
	{"Savanna", "���������", "������", 14_000, 0, 19.0, 3, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 567
	{"Bandito", "�����", "������", 12_000, 0, 15.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 568
	{"Freight Flat Traile", "������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 569
	{"Streak Traile", "������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 570
	{"Kart", "����", "������", 3_200, 0, 6.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 571
	{"Mower", "�������������", "��������", 2_100, 0, 5.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 572
	{"Dune", "��������", "������", 90_000, 0, 36.0, 2, 5, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 573
	{"Sweeper", "�������������", "��������", 9_000, 0, 12.0, 1, 5, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 574
	{"Broadway", "���������", "������", 90_000, 0, 17.0, 2, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 575
	{"Tornado", "����", "������", 95_000, 0, 19.0, 2, 4, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 576
	{"AT400", "������", "����������", 2_235_000, 70, 2100.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 577
	{"DFT-30", "��������", "������", 32_000, 0, 31.0, 2, 0, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 578
	{"Huntley", "�����������", "������", 45_000, 0, 24.0, 3, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 579
	{"Stafford", "�����", "������", 30_000, 0, 20.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 580
	{"BF-400", "��������", "������", 20_000, 0, 7.0, 1, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_NONE}, // 581
	{"Newsvan", "������", "������", 21_000, 2, 19.0, 3, 10, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 582
	{"Tug", "�������������", "������", 4_000, 0, 11.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 583
	{"Petrol Trailer", "������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 584
	{"Emperor", "�����", "������", 12_000, 0, 17.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 585
	{"Wayfarer", "��������", "������", 14_000, 0, 7.0, 4, 0, TYPE_FUEL_MOTO, SALE_MOTO, RENT_MOTO}, // 586
	{"Euros", "��������", "������", 38_000, 0, 19.0, 3, 6, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_CAR}, // 587
	{"Hotdog", "�������������", "������", 18_200, 0, 20.0, 0, 0, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 588
	{"Club", "�������", "��������", 22_200, 0, 17.0, 2, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 589
	{"Freight Box Trailer", "������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 590
	{"Article Trailer 3", "������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 591
	{"Andromada", "������", "����������", 2_500_000, 100, 2300.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_NONE}, // 592
	{"Dodo", "������", "�������������", 420_000, 0, 420.0, 0, 0, TYPE_FUEL_AIR, NOT_SALE, RENT_FLY}, // 593
	{"RC Cam", "�������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 594
	{"Launch", "�����", "������������", 190_000, 0, 690.0, 0, 0, TYPE_FUEL_BOAT, NOT_SALE, RENT_NONE}, // 595
	{"Police Car(LS)", "�����", "������", 33_000, 0, 20.0, 4, 6, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 596
	{"Police Car(SF)", "�����", "������", 33_000, 0, 20.0, 4, 6, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 597
	{"Police Car(LV)", "�����", "������", 33_000, 0, 20.0, 4, 6, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 598
	{"Police Ranger", "�����������", "������", 35_000, 0, 28.0, 4, 8, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 599
	{"Picador", "�����", "������", 3_800, 0, 17.0, 3, 6, TYPE_FUEL_CAR, SALE_CAR, RENT_CAR}, // 600
	{"S.W.A.T.", "�������������", "������", 320_000, 6, 30.0, 4, 3, TYPE_FUEL_SUV, NOT_SALE, RENT_NONE}, // 601
	{"Alpha", "����", "������", 35_000, 0, 18.0, 3, 5, TYPE_FUEL_SUPERCAR, SALE_CAR, RENT_NONE}, // 602
	{"Phoenix", "�������", "������", 42_000, 0, 19.0, 3, 5, TYPE_FUEL_CAR, SALE_CAR, RENT_NONE}, // 603
	{"Glendale", "�����", "������", 0, 0, 19.0, 3, 3, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 604
	{"Sadler", "�����", "������", 0, 0, 19.0, 0, 6, TYPE_FUEL_CAR, NOT_SALE, RENT_NONE}, // 605
	{"Luggage Trailer A", "������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 606
	{"Luggage Trailer B", "������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 607
	{"Stair Trailer", "������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 608
	{"Boxville", "������", "������", 26_000, 0, 23.0, 0, 10, TYPE_FUEL_SUV, NOT_SALE, RENT_SPECIAL}, // 609
	{"Farm Trailer", "������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE}, // 610
	{"Utility Trailer", "������", "���", 0, 0, 0.0, 0, 0, TYPE_FUEL_NONE, NOT_SALE, RENT_NONE} // 611
};