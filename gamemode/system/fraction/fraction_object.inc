/*!
	@brief Система объектов (/object)
	@author Found (evg.savosin)
	@date 16.12.2016, update 02.03.2018
*/

GetFreeIndexForFractionObject(index)
{
	for (new i; i < MAX_FRACTION_OBJECTS; i++)
	{
		if (fraction_object[index][i][fr_object_id] == INVALID_OBJECT_ID)
		{
			return i;
		}
	}
	
	return INVALID_PARAM;
}