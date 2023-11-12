/*!
	@brief »сполн€ющий файл соединени€ с базой данных
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
*/

DB_OnGameModeInit()
{
	db = mysql_connect_file("db.ini");
	
	if (mysql_errno() != 0)
	{
		printf("[DB_OnGameModeInit]: No connection to the database.");
	}
	else 
	{
		printf("[DB_OnGameModeInit]: Connection is established.");
	}
	
	/// Fix charset
	mysql_set_charset("cp1251");
	
	mysql_query(db, "UPDATE " #__CHARACTERS " SET c_online = 0");
	mysql_query(db, "UPDATE " #__USERS " SET u_online = 0");
	
	mysql_log(ALL);
}

DB_OnGameModeExit()
{
	mysql_close(db);
}