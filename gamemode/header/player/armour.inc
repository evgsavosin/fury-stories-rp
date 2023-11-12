/*!
	@brief Заголовок системы брони
	@author Found (evg.savosin)
	@date 27.04.2018
*/

// Defines 
#define GetArmourType(%0)			armour_data[%0][arm_type]
#define GetArmourValue(%0)			armour_data[%0][arm_value]
#define GetArmourItemId(%0)			armour_data[%0][arm_item_id]

#define SetArmourType(%0,%1)		armour_data[%0][arm_type]=%1
#define SetArmourValue(%0,%1)		armour_data[%0][arm_value]=%1
#define SetArmourItemId(%0,%1)		armour_data[%0][arm_item_id]=%1

#define IsArmourExistsAtPlayer(%0)	(armour_data[%0][arm_type] != TYPE_ARMOUR_NONE)
#define IsArmourWornout(%0)			(armour_data[%0][arm_value] <= 0)

// Structures & Variables
enum 
{	
	TYPE_ARMOUR_NONE,
	TYPE_ARMOUR_LIGHT,
	TYPE_ARMOUR_HEAVY
}

enum E_ARMOUR_DATA
{
	arm_type,
	arm_value,
	arm_item_id
}

new armour_data			[	MAX_PLAYERS		][	E_ARMOUR_DATA	];

// Function
Clear:armour_data(playerid)
{
	armour_data[playerid][arm_type] = TYPE_ARMOUR_NONE;
	armour_data[playerid][arm_value] = 0;
	armour_data[playerid][arm_item_id] = 0;
}