/*!
	@brief Зона закапывания для системы смерти
	@author Found (evg.savosin)
	@date 26.04.2017
*/

CorpseDirtAreaPlayerEnter(playerid, areaid) 
{
	if (corpse_dirt_zone == areaid)
	{
		SetPVarInt(playerid, "Player:CorpseDirt", true);
	}
}

CorpseDirtAreaPlayerLeave(playerid, areaid) 
{
	if (corpse_dirt_zone == areaid)
	{
		DeletePVar(playerid, "Player:CorpseDirt");
	}
}

CorpseDirtArea()
{
	corpse_dirt_zone = CreateDynamicPolygon(Float: {
		2992.0,-1012.0,2320.0,-912.0,1824.0,-612.0,1344.0,-548.0,1068.0,-516.0,
		576.0,-764.0,-60.0,-1228.0,-284.0,-1936.0,32.0,-2716.0,-1496.0,-2844.0,
		-1800.0,-2656.0,-2632.0,-2756.0,-2648.0,-2240.0,-1932.0,-1480.0,-884.0,
		-408.0,-816.0,140.0,-152.0,232.0,1120.0,540.0,2032.0,352.0,2760.0,268.0,
		2992.0,-1012.0
	});
}