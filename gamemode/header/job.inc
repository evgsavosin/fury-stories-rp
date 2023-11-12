/*
*
*	JOB SYSTEM
*	Author & Developer: Found (evg.savosin)(Found) & Noirs
*		(c) 2017
*
*	MESSAGE:
*	-
*
*/

enum 
{
	// 1 уровень
	J_PORT, // Порт
	J_RAFFLE, // Свалка
	J_WOOD, // Лесопилка
	J_DRUG_FARM, // Ферма байкеров
	
	// 2 уровень 
	J_MINIBUS,
	J_TAXI,
	J_TRUCKER,
	J_MECHANIC,
	J_PORT_DRIVER,
}

enum E_JOB_DATA
{
	j_id,
	j_name			[	32	],
	j_description	[	512	],
	
	Float: j_pos	[	3	],
	bool: j_official,
	bool: j_special,
}


new job_settings	[	][	E_JOB_DATA	] = 
	{
		{J_PORT, "Грузчик", "" #cGRAY "Устроиство грузчиков в порту.\n\n\
							  Работа грузчика в порту является самой легкодоступной в области.\n\
							  Ваша обязанность переносить бочки с горючей жидкостью с порта на склад.\n\
							  За одну перенесенную бочку Вам заплатят: " #cGREEN "80" #cGRAY " рублей.\n\n\
							  Вы желаете продолжить?", {0.0, 0.0, 0.0}, false, false}
	};