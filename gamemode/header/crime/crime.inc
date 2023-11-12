/*!
	@brief Заголовочный файл криминальных систем
	@author Flavo
	@date 01.11.2019
*/

// Macro
#define GetCrimeName(%0)			crime_data[GetCrimeMember(%0)][cr_name]
#define GetCrimeId(%0)				crime_data[%0][cr_id]
#define GetCrimeStatus(%0)			crime_data[%0][cr_official]

// Constants
const MAX_CRIME_NAME = 32;
const MAX_CRIMES = 31;

enum
{
	CRIME_LIST_NEXT = INVALID_PARAM - 2,
	CRIME_LIST_BACK,
	CRIME_LIST_BEGIN,
	CRIME_LIST_CURRENT
};

// Structures
enum E_CRIME
{
	cr_id,
	cr_name							[MAX_CRIME_NAME],
	cr_leader_name					[MAX_PLAYER_NAME],
	cr_type_id,
	cr_official,
	cr_money,
	cr_update_date
};

// Arrays
new crime_data						[MAX_CRIMES][E_CRIME];

// Functions
Clear:crime_data(index)
{
	crime_data[index][cr_id]=
	crime_data[index][cr_name][0]=
	crime_data[index][cr_leader_name][0]= EOS;
	crime_data[index][cr_type_id]=
	crime_data[index][cr_official]=
	crime_data[index][cr_money]=
	crime_data[index][cr_update_date]= 0;
}