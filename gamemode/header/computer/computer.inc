/*!
	@brief Заголовок системы компьютера
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
*/

// Defines

// Constants
const MAX_COMPUTER_LABELS = 10,
	  MAX_COMPUTER_LABEL = 16;

// Structures
enum 
{
	COMP_APP_COMPUTER = 1, // Приложение "этот компьютер"
	COMP_APP_POLICE, // Приложение для полиции
}

enum E_COMPUTER_LABEL
{
	c_label,
	c_name					[MAX_COMPUTER_LABEL],
	c_color
}

new computer_label_list		[][E_COMPUTER_LABEL] = 
{
	{COMP_APP_COMPUTER, "This PC", 0xFFFFFFFF},
	{COMP_APP_POLICE, "Police DB", 0x0000B4FF}
};