/*!
	@brief «аголовок системы выхода дежурства
	@author Found (evg.savosin)
	@date 05.02.2020
*/

// Constants
const MAX_FRACTION_DUTY_POS = 3;

// Structures
enum E_FRACTION_DUTY
{
	fr_fraction_id,
	Float: fr_pos	[MAX_FRACTION_DUTY_POS]
};

new fraction_duty 	[][E_FRACTION_DUTY] =
{
	{FRACTION_PD, {1066.3141,1924.2925,1504.2787}}, // saints
	{FRACTION_PD, {-347.1355,2535.1946,1504.4490}}, // hq
	{FRACTION_PD, {875.6721,878.0556,1503.8021}}, // verona
	
	{FRACTION_SD, {2377.9919,562.3474,2500.9688}}, // ls
	{FRACTION_SD, {351.3710,2325.0142,1504.3427}}, // blueberry
	{FRACTION_SD, {-1681.7312,1990.3463,2599.8726}}, // twin towers
	
	{FRACTION_NP, {-15.6952,2029.2394,1504.0242}}, // np
	
	{FRACTION_FD, {666.2942, 1764.7209, 1504.0741}} // fd
};
