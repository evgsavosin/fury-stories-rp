/*!
	@brief Заголовок для системы помещений (Прибыль в зависимости от посетителей)
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
	
	У бизнесов несколько видов прибылей:
	a) За покупку товара;
	b) За вход, если он платный;
	c) Минимальный оплата в зависимости от суммы аренды;
	d) В зависимости от посетителей самого бизнеса;
*/

enum E_PREMISE_VISITORS
{
	prv_character_id,
	prv_ip				[	MAX_PLAYER_IP	]
}

new premise_visitors			[	MAX_PREMISES	][	MAX_PREMISE_VISITORS ][E_PREMISE_VISITORS];


Clear:premise_visitors(index)
{
	for (new i; i < MAX_PREMISE_VISITORS; i++)
	{
		premise_visitors[index][i][prv_ip][0] = EOS;
		
		premise_visitors[index][i][prv_character_id] = 0;
	}
}