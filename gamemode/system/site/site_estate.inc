/*!
	@brief Список покупки домов (GOG - arthouse.com)
	@author Found (evg.savosin)
	@date 16.12.2016, update 12.03.2018
*/

ShowSiteEstateList(playerid, type, dialogid, page, bool: zone_sort = false, 
	price_sort_1 = INVALID_PARAM, price_sort_2 = INVALID_PARAM, 
	price_rent_sort_1 = INVALID_PARAM, price_rent_sort_2 = INVALID_PARAM)
{
	strglobalclear();
	
	new count,
		zone_1 			[	28		],
		zone_2			[	28		],
		Float: x,
		Float: y,
		Float: z;
	
	GetPlayerPos(playerid, x, y, z);
	
	SetPVarInt(playerid, "Site:EstatePage", page);
	
	strcat(g_big_string, "" #cPROJECT "#\t" #cPROJECT "Цена покупки\t" #cPROJECT "Цена аренды в неделю\n");
	
	if (type == TYPE_ESTATE_HOUSE)
	{
		for (new i, j; i < sizeof house_data; i++)
		{
			if (GetHouseId(i) == 0 || IsHouseBought(i))
			{
				continue;
			}
			
			GetHouseStreetZone(i, zone_1, sizeof zone_1);
		
			if (zone_sort) /// Если сортировка по зоне
			{	
				GetZoneName(
					x, 
					y, 
					zone_2, 
					sizeof zone_2 
				);
				
				if (strcmp(zone_1, zone_2, true) != 0)
				{
					continue;
				}
			}
			
			if (price_sort_1 != INVALID_PARAM)
			{
				if (!(price_sort_1 <= GetHousePrice(i) <= price_sort_2))
				{
					continue;
				}
			}
			
			if (price_rent_sort_1 != INVALID_PARAM)
			{
				if (!(price_rent_sort_1 <= GetHouseRent(i) <= price_rent_sort_2))
				{
					continue;
				}
			}
			
			if (j != (page * MAX_ITEM_LIST))
			{
				j++;
				continue;
			}
			
			format:g_big_string("%s %s #%i, %s\t" #cGREEN "$%i" #cWHITE "\t" #cGREEN "$%i\n", 
				g_big_string,
				IsHouseType(i) == TYPE_HOUSE ? ("House") : ("Apart."),
				GetHouseId(i),			
				zone_1,
				GetHousePrice(i),
				GetHouseRent(i)
			);
			
			g_dialog_select[playerid][count++] = i;
			if (count == MAX_ITEM_LIST)
			{
				break;
			}
		}
	}
	else 
	{
		for (new i, j; i < sizeof premise_data; i++)
		{
			if (count == MAX_ITEM_LIST)
			{
				break;
			}
			
			if (GetPremiseId(i) == 0 || IsPremiseBought(i))
			{
				continue;
			}
			
			GetPremiseStreetZone(i, zone_1, sizeof zone_1);
		
			if (zone_sort) /// Если сортировка по зоне
			{	
				GetZoneName(
					x, 
					y, 
					zone_2, 
					sizeof zone_2 
				);
				
				if (strcmp(zone_1, zone_2, true) != 0)
				{
					continue;
				}
			}
			
			if (price_sort_1 != INVALID_PARAM)
			{
				if (!(price_sort_1 <= GetPremisePrice(i) <= price_sort_2))
				{
					continue;
				}
			}
			
			if (price_rent_sort_1 != INVALID_PARAM)
			{
				if (!(price_rent_sort_1 <= GetPremiseRent(i) <= price_rent_sort_2))
				{
					continue;
				}
			}
			
			if (j != (page * MAX_ITEM_LIST))
			{
				j++;
				continue;
			}
			
			format:g_big_string("%s Premise #%i, %s\t" #cGREEN "$%i" #cWHITE "\t" #cGREEN "$%i\n", 
				g_big_string,
				GetPremiseId(i),			
				zone_1,
				GetPremisePrice(i),
				GetPremiseRent(i)
			);
			
			g_dialog_select[playerid][count++] = i;
			if (count == MAX_ITEM_LIST)
			{
				break;
			}
		}
	}
	
	if (count == MAX_ITEM_LIST)
	{
		strcat(g_big_string, "" #cGRAY "Вперед\t\t" #cWHITE ">>");
		g_dialog_select[playerid][count++] = ITEM_LIST_NEXT;
	}
	
	if (page > 0)
	{
		strcat(g_big_string, "\n" #cGRAY "Назад\t" #cWHITE "<<");
		g_dialog_select[playerid][count] = ITEM_LIST_BACK;
	}
	
	return (count == 0 && page == 0) ? 0 :
	ShowPlayerDialog(playerid, dialogid, DIALOG_STYLE_TABLIST_HEADERS, 
		(type == TYPE_ESTATE_HOUSE ? ("www.estateagency.com/houses") : ("www.estateagency.com/premises")), 
		g_big_string, 
		"Выбрать", "Назад" 
	);
}
