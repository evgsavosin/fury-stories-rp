/*!
	@brief Заголовок системы сумок
	@author Found (evg.savosin)
	@date 16.12.2016, update 07.02.2018
	
*/

#define GetBagId(%0)					(bag_data[%0][bag_id])

/// Structures
enum E_BAG_DATA
{
	bag_id,
	bag_type
};

new bag_data							[	MAX_BAGS		][	E_BAG_DATA	];


Clear:bag_data(index)
{
	new i;
		
	do
	{
		Clear:inv_data_slot(index, i, TYPE_INV_BAG);
	} 
	while (++i < MAX_INVENTORY_SLOTS);
	
	bag_data[index][bag_id] = 
	bag_data[index][bag_type] = 0; 
}

