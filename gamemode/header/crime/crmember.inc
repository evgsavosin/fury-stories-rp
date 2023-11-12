/*!
	@brief Заголовочный файл участников криминальных систем
	@author Flavo
	@date 01.11.2019
*/

// Macro
#define GetCrimeMember(%0) 				crmember_data[%0][cr_crime_index] 
#define GetCrimeMemberPerm(%0,%1) 		crmember_data[%0][cr_perm][%1] 
#define IsCrimeLeader(%0) 				crmember_data[%0][cr_leader]
#define GetCrimeCharacterId(%0)			crmember_data[%0][cr_character_id]

// Constants
const MAX_CRIME_MEMBER_LIST = 10 + 3;

// Structures
// Привилегии
enum
{
	cr_perm_invite,
	cr_perm_uninvite,
	cr_perm_buy,
	cr_perm_manage,
	
	CRPERM_SETTINGS
};

enum E_CRIME_MEMBER
{
	cr_id,
	cr_leader,
	cr_perm					[CRPERM_SETTINGS],
	cr_crime_index
};

enum E_CRIME_MEMBER_LIST
{
	cr_crime_id,
	cr_character_id,
	cr_leader,
	cr_perm					[CRPERM_SETTINGS],
	cr_name					[MAX_PLAYER_NAME]
};

// Arrays
new crmember_data			[MAX_PLAYERS][E_CRIME_MEMBER],
	crmember_select			[MAX_PLAYERS][MAX_CRIME_MEMBER_LIST][E_CRIME_MEMBER_LIST];
	
// Functions
Clear:crmember_data(index)
{
	//crmember_data[index][cr_id]= 
	crmember_data[index][cr_leader]= 0;
	crmember_data[index][cr_crime_index]= INVALID_PARAM;
	crmember_data[index][cr_perm][cr_perm_invite]=
	crmember_data[index][cr_perm][cr_perm_uninvite]=
	crmember_data[index][cr_perm][cr_perm_buy]=
	crmember_data[index][cr_perm][cr_perm_manage]= 0;
}

Clear:crmember_select(index)
{
	for (new i; i < MAX_CRIME_MEMBER_LIST; i++)
	{
		crmember_select[index][i][cr_crime_id] =
		crmember_select[index][i][cr_character_id] =
		crmember_select[index][i][cr_leader] = 
		crmember_select[index][i][cr_name][0] = EOS;
		crmember_select[index][i][cr_perm][cr_perm_invite] =
		crmember_select[index][i][cr_perm][cr_perm_uninvite] =
		crmember_select[index][i][cr_perm][cr_perm_buy] =
		crmember_select[index][i][cr_perm][cr_perm_manage] = 0;
	}
}