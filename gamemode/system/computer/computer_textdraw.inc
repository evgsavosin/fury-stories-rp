/*!
	@brief Текстдравы для системы компьютера
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

ShowComputer(playerid, bool: states, labels[MAX_COMPUTER_LABELS] = {INVALID_PARAM, ...})
{
	ShowComputerDesktop(playerid, states, labels);
	
	if (!states) 
	{
		ShowComputerShowApp(playerid, false);
	}
}

ShowComputerShowApp(playerid, bool: states = false)
{
	return OnComputerShowApp(playerid, states);
}

CMD:pccccccc(playerid)
{
	ShowComputer(playerid, true, {
		COMP_APP_COMPUTER, 
		COMP_APP_POLICE,
		INVALID_PARAM,
		INVALID_PARAM,
		INVALID_PARAM,
		INVALID_PARAM,
		INVALID_PARAM,
		INVALID_PARAM,
		INVALID_PARAM,
		INVALID_PARAM
	});
	
	return 1;
}