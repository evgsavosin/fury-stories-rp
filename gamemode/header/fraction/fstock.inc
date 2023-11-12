/*!
	@brief Заголовок системы склада
	@author Found (evg.savosin)
	@date 05.02.2020
*/

// Constants
const MAX_FRACTION_STOCK_POS = 3;

// Structures
enum E_FRACTION_STOCK
{
	fr_fraction_id,
	Float: fr_pos	[MAX_FRACTION_STOCK_POS],
};

new fraction_stock 	[][E_FRACTION_STOCK] =
{
	{FRACTION_PD, {1059.5853, 2447.7126, 1500.7565}}, // saints
	{FRACTION_PD, {-116.0587, 1097.5430, 1604.0436}}, // hq
	{FRACTION_PD, {1373.5503, 897.9427, 1503.8021}}, // verona
	
	{FRACTION_SD, {2365.0078, 548.9154, 2500.9688}}, // ls
	{FRACTION_SD, {332.1859, 2314.5383, 1504.3427}}, // blueberry
	{FRACTION_SD, {-1546.5598, 1983.9196, 1144.6448}}, // twin towers
	
	{FRACTION_NP, {-10.2806, 2053.9685, 1504.0242}}, // np
	
	{FRACTION_FD, {669.9392, 1755.0850, 1504.0741}} // fd
};