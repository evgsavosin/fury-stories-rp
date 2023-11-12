/*!
	@brief Заголовочный файл криминальных типов
	@author Flavo
	@date 17.11.2019
*/

// Macro
#define GetCrimeType(%0)			crime_data[%0][cr_type_id]
#define GetCrimeTypeName(%0)		crtype_data[GetCrimeType(%0) - 1][cr_name]	
#define GetCrimeTypeMoney(%0)		crtype_data[GetCrimeType(%0) - 1][cr_max_money]

// Constants
const MAX_CRIME_TYPE = 5;
const MAX_CRIME_TYPE_NAME = 64;

// Structures
enum E_CRIME_TYPE
{
	cr_id,
	cr_name							[MAX_CRIME_TYPE_NAME],
	cr_max_money
};

// Arrays
new crtype_data						[MAX_CRIME_TYPE][E_CRIME_TYPE];
	
// Functions