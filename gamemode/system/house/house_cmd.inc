/*!
	@brief Команды для системы домов
	@author Found (evg.savosin)
	@date 16.12.2016, update 25.03.2018
*/

/*!
	@brief Команды для дома
*/

CMD:hlist(playerid)
{
	if (!ShowHouseList(playerid, INVALID_DIALOG_ID, "Закрыть", "", 0))
	{
		SendClientMessage(playerid, C_WHITE, !PLAYER_NO_HOUSE);
	}
	
	return 1;
}

CMD:hmenu(playerid)
{
	HouseMenu(playerid);
	return 1;
}

HouseMenu(playerid, show_message = true)
{
	Clear:house_pvar(playerid);
	
	new world = GetCharacterWorld(playerid),
		index = GetHouseIndexById(world);
	
	if (!IsPlayerInHouse(playerid, index) || !IsValidHouse(world))
	{
		if (show_message)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Для использования данной команды Вы должны находиться в жилищном помещении.");
		}
		
		return 0;
	}
	
	SetPVarInt(playerid, "House:Select", index);
	SetPVarInt(playerid, "House:IsOwner", 0);
	
	if (!IsHouseBought(index))
	{
		format:g_string(
			" Информация о %s\n \
			Приобрести за " #cGREEN "$%d\n \
			Арендовать за " #cGREEN "$%d" #cWHITE "/неделя",
			(house_data[index][h_interior]) ? ("квартире") : ("доме"),
			house_data[index][h_price],
			GetHouseRent(index) 
		);
		
		ShowPlayerDialog(playerid, D_HOUSE + 1, DIALOG_STYLE_LIST, 
			" ",
			g_string,
			"Далее", "Закрыть"
		);
		
		return 1;
	}
	
	if (!CheckHouseAccess(TYPE_HOUSE_LODGER, playerid, index))
	{
		if (show_message)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Данный дом не является Вашей собственностью либо у Вас нет доступа к нему.");
		}
		
		return 0;
	}

	SetPVarInt(playerid, "House:IsOwner", 1);
	
	format:g_string(
		" Информация о %s\n \
		 Управление %s\n \
		 Сожители\n \
		 Режим ремонта\t%s\n \
		 Сейф\
		 %s",
		(house_data[index][h_interior]) ? ("квартире") : ("доме"),
		(house_data[index][h_interior]) ? ("квартирой") : ("домом"),
		(IsPlayerRenovation(playerid)) ? ("" #cPROJECT "Включен") : ("" #cGRAY "Выключен"),
		(GetHouseGarageExists(index)) ? ("\n Войти в гараж") : ("")
	);
	
	ShowPlayerDialog(playerid, D_HOUSE + 1, DIALOG_STYLE_TABLIST, 
		" ",
		g_string,
		"Далее", "Закрыть"
	);
	return 1;
}

CMD:hlock(playerid)
{
	HouseLock(playerid);
	return 1;
}

/*!
	@brief Команды для гаража
*/

CMD:gmenu(playerid)
{
	GarageMenu(playerid);
	return 1;
}

GarageMenu(playerid, show_message = true)
{
	Clear:house_pvar(playerid);
	
	new world = GetCharacterWorld(playerid),
		index = GetHouseIndexById(world);
		
	if (!IsPlayerInGarage(playerid, index, world) || !IsValidHouse(world))
	{
		if (show_message)
		{
			SendClientMessage(playerid, C_WHITE, !#ERROR " Для использования данной команды, Вы должны находиться в своем гараже.");
		}
		
		return 0;
	}

	if (!CheckHouseAccess(TYPE_HOUSE_LODGER, playerid, index, lod_perm_garage))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Данный гараж не является Вашей собственностью либо у Вас нет доступа к нему.");
		
		return 0;
	}
	
	SetPVarInt(playerid, "Garage:Select", index);
	
	format:g_string(
		"Управление гаражом\n\
		 Личный транспорт\t" #cGRAY "/carlist\n\
		 Режим ремонта\t%s\n\
		 Настройки",
		(IsPlayerRenovation(playerid)) ? ("" #cPROJECT "Включен") : ("" #cGRAY "Выключен")
	);
	
	ShowPlayerDialog(playerid, D_GARAGE, DIALOG_STYLE_TABLIST, 
		" ",
		g_string,
		"Далее", "Закрыть"
	);
	
	return 1;
}

HouseRenovation(playerid) // @cmd: /ren
{
	new renovation = IsPlayerRenovation(playerid);
		
	if (!renovation)
	{
		SendClientMessage(playerid, C_WHITE, !NOT_RENOVATION_MODE);
		
		return 0;
	}
	
	new world = GetPlayerVirtualWorld(playerid),
		index = GetHouseIndexById(world);
		
	if (!IsPlayerInHouse(playerid, index) || !IsValidHouse(world))
	{
		if (renovation)
		{
			SetRenovationMode(playerid, false, TYPE_REN_HOUSE, index);
		}
		
		SendClientMessage(playerid, C_WHITE, !#ERROR " Для использования данной команды Вы должны находиться в своем жилищном помещении.");
	
		return 0;
	}
	
	if (GetRenovationType(playerid) != TYPE_REN_HOUSE 
	&& GetRenovationId(playerid) != world)
	{
		return 0;
	}
	
	SetPVarInt(playerid, "House:Select", index);
	SetPVarInt(playerid, "House:IsOwner", 0);
	
	ShowPlayerDialog(playerid, D_HOUSE + 8, DIALOG_STYLE_TABLIST, " ", 
		" Открыть меню дома\t" #cGRAY "/hmenu\n \
		Расстановка мебели\n \
		Изменение текстур",
		"Далее", "Закрыть"
	);
	
	return 1;
}

GarageRenovation(playerid)
{
	new renovation = IsPlayerRenovation(playerid);
		
	if (!renovation)
	{
		SendClientMessage(playerid, C_WHITE, !NOT_RENOVATION_MODE);
		
		return 0;
	}
	
	new world = GetPlayerVirtualWorld(playerid),
		index = GetHouseIndexById(world);
		
	if (!IsPlayerInGarage(playerid, index, world) || !IsValidHouse(world))
	{
		if (renovation)
		{
			SetRenovationMode(playerid, false, TYPE_REN_GARAGE, index);
		}
		
		SendClientMessage(playerid, C_WHITE, !#ERROR " Для использования данной команды, Вы должны находиться в своем гараже.");
	
		return 0;
	}
	
	SetPVarInt(playerid, "Garage:Select", index);
	
	ShowPlayerDialog(playerid, D_GARAGE + 4, DIALOG_STYLE_TABLIST, " ", 
		" Открыть меню гаража\t" #cGRAY "/gmenu\n \
		Расстановка мебели",
		"Далее", "Закрыть"
	);
	
	return 1;
}

CMD:glock(playerid)
{
	GarageLock(playerid);
	return 1;
}

CMD:evict(playerid)
{
	if (!IsPlayerLodger(playerid))
	{
		SendClientMessage(playerid, C_WHITE, !#ERROR " Вы не являетесь сожителем.");
		return 1;
	}
	
	Remove:lod_data(GetCharacterId(playerid), playerid);
	SendClientMessage(playerid, C_WHITE, !#SUCCESS " Вы успешно выселились из жилищного помещения.");
	return 1;
}
