/*!
	@brief Заголовок системы фракций на сервере
	@author Found (evg.savosin)
	@date 21.01.2020
*/

// Defines
#define NEWS_STUDIO_POS			-69.6267, -222.8305, 3182.4495

// Structures
enum E_FRACTION_NEWS_DATA
{
	fr_player_id, // Ведущий
};

new fraction_news_ether_data	[E_FRACTION_NEWS_DATA];

// Functions
Clear:fraction_news_ether_data()
{
	fraction_news_ether_data[fr_player_id] = INVALID_PLAYER_ID;
}