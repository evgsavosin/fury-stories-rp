/*!
	@brief ��������� ��� ������� ��������� (������� � ����������� �� �����������)
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
	
	� �������� ��������� ����� ��������:
	a) �� ������� ������;
	b) �� ����, ���� �� �������;
	c) ����������� ������ � ����������� �� ����� ������;
	d) � ����������� �� ����������� ������ �������;
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