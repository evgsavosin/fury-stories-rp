/*!
	@brief «аголовок дл€ системы контактов
	@author Found (evg.savosin)
	@date 16.12.2016, update 11.02.2018
*/

/// Structures
enum E_CONTACTS_DATA
{
	pc_number, // номер контакта 
	pc_name				[MAX_PLAYER_NAME + 1 ], // им€
	pc_created_time
};

new contact_data		[MAX_PHONES][MAX_CONTACTS][E_CONTACTS_DATA];


Clear:contact_data(id, index)
{
	/// Integer
	contact_data[id][index][pc_created_time] =
	contact_data[id][index][pc_number] = 0;
	
	/// String
	contact_data[id][index][pc_name][0] = EOS;
}
