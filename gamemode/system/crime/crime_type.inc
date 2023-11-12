/*!
	@brief Файл с загрузкой криминальных систем
	@author Flavo
	@date 03.11.2019
*/

Load:crtype_data()
{
	format:g_small_string("SELECT * FROM crimes_type");
	
	mysql_tquery(db, g_small_string, "OnCrimeTypeLoad");
}

function OnCrimeTypeLoad()
{
	new rows;
	
	cache_get_row_count(rows);
	
	if (rows == 0)
	{
		return 1;
	}
	
	for (new i; i < rows; i++)
	{
		cache_get_value_name_int(i, "cr_id", crtype_data[i][cr_id]);
		cache_get_value_name(i, "cr_name", crtype_data[i][cr_name], MAX_CRIME_TYPE_NAME);
		cache_get_value_name_int(i, "cr_max_money", crtype_data[i][cr_max_money]);
	}
	
	printf("[OnCrimeTypeLoad]: Crime Types have been loaded. All - %d",
		rows
	);
	
	return 1;
}