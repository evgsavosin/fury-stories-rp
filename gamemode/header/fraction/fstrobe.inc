/*!
	@brief Заголовок системы стробоскопов для системы фракций
	@author Found (evg.savosin)
	@date 05.02.2020
*/

new strobelight_timer	 [MAX_VEHICLES] = {INVALID_PARAM, ... },
	strobelight_time_out [MAX_VEHICLES] = {INVALID_PARAM, ... },
	strobelight_flash	 [MAX_VEHICLES char];