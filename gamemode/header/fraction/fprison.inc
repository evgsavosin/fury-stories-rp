/*!
	@brief Заголовок системы тюрьмы на сервере
	@author Found (evg.savosin)
	@date 16.12.2016, update 14.02.2018
*/

// Defines 
#define PRISON_MENU_POS				-1539.8058,1991.2582,1144.6448

// Constants
const MAX_FRACTION_PRISON_DOORS = 3,
	  MAX_FRACTION_PRISON_DOOR_OBJ = 6,
	  MAX_FRACTION_PRISON_DOOR_POS = 6;

// Structures
enum E_FRACTION_PRISON_DOOR
{
	fr_object_id,
	Float: fr_begin_pos				[MAX_FRACTION_PRISON_DOOR_POS],
	Float: fr_end_pos				[MAX_FRACTION_PRISON_DOOR_POS],
	bool: fr_status
};

new fprison_door					[MAX_FRACTION_PRISON_DOORS][MAX_FRACTION_PRISON_DOOR_OBJ][E_FRACTION_PRISON_DOOR],
	bool: fprison_camera_status;

// Functions
Create:fprison_door(index, oindex, Float: x1, Float: y1, Float: z1, Float: rx1, Float: ry1, Float: rz1, Float: x2, Float: y2, Float: z2, Float: rx2, Float: ry2, Float: rz2, modelid)
{
	fprison_door[index][oindex][fr_object_id] = CreateDynamicObject(modelid, x1, y1, z1, rx1, ry1, rz1, -1, -1, -1, 300.00, 300.00);
	fprison_door[index][oindex][fr_begin_pos][0] = x1;
	fprison_door[index][oindex][fr_begin_pos][1] = y1;
	fprison_door[index][oindex][fr_begin_pos][2] = z1;
	fprison_door[index][oindex][fr_begin_pos][3] = rx1;
	fprison_door[index][oindex][fr_begin_pos][4] = ry1;
	fprison_door[index][oindex][fr_begin_pos][5] = rz1;
	
	fprison_door[index][oindex][fr_end_pos][0] = x2;
	fprison_door[index][oindex][fr_end_pos][1] = y2;
	fprison_door[index][oindex][fr_end_pos][2] = z2;
	fprison_door[index][oindex][fr_end_pos][3] = rx2;
	fprison_door[index][oindex][fr_end_pos][4] = ry2;
	fprison_door[index][oindex][fr_end_pos][5] = rz2;
	
	return fprison_door[index][oindex][fr_object_id];
}