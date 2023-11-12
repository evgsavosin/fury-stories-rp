/*!
	@brief Система администрирования (Система логов)
	@author Found (evg.savosin)
	@date 16.12.2016
		
	Максимальное количество уровней: 4;
*/

enum E_ADMIN_LOG
{
	Text: alog_textdraw,
	alog_text							[	MAX_ADMIN_LOG_LINE_LENGHT]
};

new alog_data							[	MAX_ADMIN_LOG_LINES	][	E_ADMIN_LOG	];