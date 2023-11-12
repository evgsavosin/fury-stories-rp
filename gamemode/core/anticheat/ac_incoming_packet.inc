/*!
	@brief Античит (FuryAC) - Incoming packets
	@author Found (evg.savosin)
	@date 12.05.2019
*/


/*!
	Синхронизация данных игрока
	@param [in] playerid Игрок
	@param [in] bs BitStream
*/

IPacket:ID_PLAYER_SYNC(playerid, BitStream: bs)
{
	new data		[PR_OnFootSync];
	
    BS_IgnoreBits(bs, 8);
    BS_ReadOnFootSync(bs, data);

	// Filter packets
	if (!Raknet_IsValidPosition(data[PR_position])
	|| !Raknet_IsValidQuaternion(data[PR_quaternion])
	|| !Raknet_IsValidVelocity(data[PR_velocity])
	&& (isnan(data[PR_surfingOffsets][0]) || floatcmp(floatabs(data[PR_surfingOffsets][0]), 100.0000) == 1
	|| isnan(data[PR_surfingOffsets][1]) || floatcmp(floatabs(data[PR_surfingOffsets][1]), 100.0000) == 1
	|| isnan(data[PR_surfingOffsets][2]) || floatcmp(floatabs(data[PR_surfingOffsets][2]), 100.0000) == 1)
	|| !(0 < data[PR_animationId] <= 1812))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [FILTER][ID_PLAYER_SYNC] Error sync (playerid: %i)", playerid);
		#endif
		
		return 0;
	}
	
	if (ac_log)
	{
		printf(
			"PLAYER_SYNC[%d]:\nlrKey %d \nudKey %d \nkeys %d \nposition: %.2f %.2f %.2f \nquaternion %.2f %.2f %.2f %.2f \nhealth %d \narmour %d \nadditionalKey %d \nweaponId %d \nspecialAction %d \nvelocity %.2f %.2f %.2f \nsurfingOffsets %.2f %.2f %.2f \nsurfingVehicleId %d \nanimationId %d \nanimationFlags %d",
			playerid,
			data[PR_lrKey],
			data[PR_udKey],
			data[PR_keys],
			data[PR_position][0],
			data[PR_position][1],
			data[PR_position][2],
			data[PR_quaternion][0],
			data[PR_quaternion][1],
			data[PR_quaternion][2],
			data[PR_quaternion][3],
			data[PR_health],
			data[PR_armour],
			data[PR_additionalKey],
			data[PR_weaponId],
			data[PR_specialAction],
			data[PR_velocity][0],
			data[PR_velocity][1],
			data[PR_velocity][2],
			data[PR_surfingOffsets][0],
			data[PR_surfingOffsets][1],
			data[PR_surfingOffsets][2],
			data[PR_surfingVehicleId],
			data[PR_animationId],
			data[PR_animationFlags]
		);
	}
	
	ac_player_data[playerid][ac_is_remove_from_vehicle] = false;
	
	// Anticheats
	if (!ID_PLAYER_SYNC:AC_SPECIAL_ACTION(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_PLAYER_SYNC][AC_SPECIAL_ACTION] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_PLAYER_SYNC:AC_ONFOOT_RVANKA(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_PLAYER_SYNC][AC_ONFOOT_RVANKA] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_PLAYER_SYNC:AC_ONFOOT_FLYHACK(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_PLAYER_SYNC][AC_ONFOOT_FLYHACK] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_PLAYER_SYNC:AC_INVISIBLE_SURF(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_PLAYER_SYNC][AC_INVISIBLE_SURF] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_PLAYER_SYNC:AC_ONFOOT_TELEPORT(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_PLAYER_SYNC][AC_ONFOOT_TELEPORT] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_PLAYER_SYNC:AC_ONFOOT_AIRBREAK(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_PLAYER_SYNC][AC_ONFOOT_AIRBREAK] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_PLAYER_SYNC:AC_WEAPON_HACK(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_PLAYER_SYNC][AC_WEAPON_HACK] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	// Save player info for next check
	AntiCheatDumpPlayerData(playerid, data[PR_position]);
	AntiCheatDumpPlayerVehicleData(playerid, INVALID_VEHICLE_ID, INVALID_PARAM);
	
	ac_player_data[playerid][ac_is_in_car] = false;
	return 1;
}

/*!
	Синхронизация транспорта (driver)
	@param [in] playerid Игрок
	@param [in] bs BitStream
*/

IPacket:ID_VEHICLE_SYNC(playerid, BitStream: bs)
{
	new data		[PR_InCarSync];
	
	BS_IgnoreBits(bs, 8);
	BS_ReadInCarSync(bs, data);
	
	// Filter packets
	if (!Raknet_IsValidPosition(data[PR_position])
	|| !Raknet_IsValidQuaternion(data[PR_quaternion])
	|| !Raknet_IsValidVelocity(data[PR_velocity])
	|| isnan(data[PR_vehicleHealth]) 
	|| isnan(data[PR_trainSpeed])) 
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [FILTER][ID_VEHICLE_SYNC] Error sync (playerid: %i)", playerid);
		#endif
		
		return 0;
	}
	
	if (ac_log)
	{
		printf(
			"VEHICLE_SYNC[%d]:\nvehicleId %d \nlrKey %d \nudKey %d \nkeys %d \nquaternion %.2f %.2f %.2f %.2f \nposition %.2f %.2f %.2f \nvelocity %.2f %.2f %.2f \nvehicleHealth %.2f \nplayerHealth %d \narmour %d \nadditionalKey %d \nweaponId %d \nsirenState %d \nlandingGearState %d \ntrailerId %d \ntrainSpeed %.2f",
			playerid,
			data[PR_vehicleId],
			data[PR_lrKey],
			data[PR_udKey],
			data[PR_keys],
			data[PR_quaternion][0],
			data[PR_quaternion][1],
			data[PR_quaternion][2],
			data[PR_quaternion][3],
			data[PR_position][0],
			data[PR_position][1],
			data[PR_position][2],
			data[PR_velocity][0],
			data[PR_velocity][1],
			data[PR_velocity][2],
			data[PR_vehicleHealth],
			data[PR_playerHealth],
			data[PR_armour],
			data[PR_additionalKey],
			data[PR_weaponId],
			data[PR_sirenState],
			data[PR_landingGearState],
			data[PR_trailerId],
			data[PR_trainSpeed]
		);
	}
	
	// Anticheats
	if (!ID_VEHICLE_SYNC:AC_DRIVER_ENTER(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_VEHICLE_SYNC][AC_DRIVER_ENTER] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_VEHICLE_SYNC:AC_DRIVER_FAST_ENTER(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_VEHICLE_SYNC][AC_DRIVER_FAST_ENTER] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_VEHICLE_SYNC:AC_DRIVER_RVANKA(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_VEHICLE_SYNC][AC_DRIVER_RVANKA] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_VEHICLE_SYNC:AC_DRIVER_TELEPORT(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_VEHICLE_SYNC][AC_DRIVER_TELEPORT] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_VEHICLE_SYNC:AC_DRIVER_AIRBREAK(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_VEHICLE_SYNC][AC_DRIVER_AIRBREAK] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_VEHICLE_SYNC:AC_CAR_SLAPPER(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_VEHICLE_SYNC][AC_CAR_SLAPPER] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_VEHICLE_SYNC:AC_WEAPON_HACK(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_VEHICLE_SYNC][AC_WEAPON_HACK] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_VEHICLE_SYNC:AC_DRIVER_SPEED_HACK(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_VEHICLE_SYNC][AC_DRIVER_SPEED_HACK] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	// NOP RemovePlayerFromVehicle
	CheckRemovePlayerFromVehicle(playerid);
	
	// Save player info for next check
	AntiCheatDumpPlayerData(playerid, data[PR_position]);
	AntiCheatDumpPlayerVehicleData(playerid, data[PR_vehicleId], 0);
	
	ac_player_data[playerid][ac_is_in_car] = true;
	return 1;
}

/*!
	Синхронизация транспорта (passenger)
	@param [in] playerid Игрок
	@param [in] bs BitStream
*/

IPacket:ID_PASSENGER_SYNC(playerid, BitStream: bs)
{
	new data		[PR_PassengerSync];
	
    BS_IgnoreBits(bs, 8);
    BS_ReadPassengerSync(bs, data);
	
	// Filter packets
	if (!Raknet_IsValidPosition(data[PR_position]))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [FILTER][ID_PASSENGER_SYNC] Error sync (playerid: %i)", playerid);
		#endif
		
		return 0;
	}
	
	if (ac_log)
	{
		printf(
        "PASSENGER_SYNC[%d]:\nvehicleId %d \ndriveBy %d \nseatId %d \nadditionalKey %d \nweaponId %d \nplayerHealth %d \nplayerArmour %d \nlrKey %d \nudKey %d \nkeys %d \nposition %.2f %.2f %.2f",
			playerid,
			data[PR_vehicleId],
			data[PR_driveBy],
			data[PR_seatId],
			data[PR_additionalKey],
			data[PR_weaponId],
			data[PR_playerHealth],
			data[PR_playerArmour],
			data[PR_lrKey],
			data[PR_udKey],
			data[PR_keys],
			data[PR_position][0],
			data[PR_position][1],
			data[PR_position][2]
		);
	}
	
	// Anticheats
	if (!ID_PASSENGER_SYNC:AC_PASSENGER_ENTER(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_PASSENGER_SYNC][AC_PASSENGER_ENTER] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_PASSENGER_SYNC:AC_PASSENGER_FAST_ENTER(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_PASSENGER_SYNC][AC_PASSENGER_FAST_ENTER] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	if (!ID_PASSENGER_SYNC:AC_WEAPON_HACK(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_PASSENGER_SYNC][AC_WEAPON_HACK] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}
	
	// NOP RemovePlayerFromVehicle
	CheckRemovePlayerFromVehicle(playerid);
	
	// Save player info for next check
	AntiCheatDumpPlayerData(playerid, data[PR_position]);
	AntiCheatDumpPlayerVehicleData(playerid, data[PR_vehicleId], data[PR_seatId]);
	
	ac_player_data[playerid][ac_is_in_car] = true;
	return 1;
}

/*!
	Синхронизация оружия
	@param [in] playerid Игрок
	@param [in] bs BitStream
*/

IPacket:ID_WEAPONS_UPDATE(playerid, BitStream: bs)
{
	new data		[PR_WeaponsUpdate];
	
    BS_IgnoreBits(bs, 8);
    BS_ReadWeaponsUpdate(bs, data);
	
	/*if (!ID_WEAPONS_UPDATE:AC_WEAPON_HACK(playerid, data))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [ID_WEAPONS_UPDATE][AC_WEAPON_HACK] detect (playerid: %i)", playerid);
		#endif
		return 1;
	}*/
    return 1;
}

/*!
	Синхронизация незанятого транспорта
	@param [in] playerid Игрок
	@param [in] bs BitStream
*/

IPacket:ID_UNOCCUPIED_SYNC(playerid, BitStream: bs)
{
	new data		[PR_UnoccupiedSync];
	
    BS_IgnoreBits(bs, 8); 
    BS_ReadUnoccupiedSync(bs, data);
	
	// Filter packets
    if (!Raknet_IsValidPosition(data[PR_position])
	|| !Raknet_IsValidVelocity(data[PR_velocity])
	|| !Raknet_IsValidAngularVelocity(data[PR_angularVelocity])
	|| isnan(data[PR_roll][0]) || floatcmp(floatabs(data[PR_roll][0]), 1.00000) == 1
	|| isnan(data[PR_roll][1]) || floatcmp(floatabs(data[PR_roll][1]), 1.00000) == 1
	|| isnan(data[PR_roll][2]) || floatcmp(floatabs(data[PR_roll][2]), 1.00000) == 1
	|| isnan(data[PR_direction][0]) || floatcmp(floatabs(data[PR_direction][0]), 1.00000) == 1
	|| isnan(data[PR_direction][1]) || floatcmp(floatabs(data[PR_direction][1]), 1.00000) == 1
	|| isnan(data[PR_direction][2]) || floatcmp(floatabs(data[PR_direction][2]), 1.00000) == 1
	|| !Raknet_IsValidData(data[PR_vehicleHealth])) 
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [FILTER][ID_UNOCCUPIED_SYNC] Error sync (playerid: %i)", playerid);
		#endif
		
		return 0;
	}
	
	if (ac_log)
	{
		printf(
			"UNOCCUPIED_SYNC[%d]:\nvehicleId %d \nseatId %d \nroll %.2f %.2f %.2f \ndirection %.2f %.2f %.2f \nposition %.2f %.2f %.2f \nvelocity %.2f %.2f %.2f \nangularVelocity %.2f %.2f %.2f \nvehicleHealth %.2f",
			playerid,
			data[PR_vehicleId],
			data[PR_seatId],
			data[PR_roll][0],
			data[PR_roll][1],
			data[PR_roll][2],
			data[PR_direction][0],
			data[PR_direction][1],
			data[PR_direction][2],
			data[PR_position][0],
			data[PR_position][1],
			data[PR_position][2],
			data[PR_velocity][0],
			data[PR_velocity][1],
			data[PR_velocity][2],
			data[PR_angularVelocity][0],
			data[PR_angularVelocity][1],
			data[PR_angularVelocity][2],
			data[PR_vehicleHealth]
		);
	}
	
	/// Anticheats
	if (!ID_UNOCCUPIED_SYNC:AC_UNOCCUPIED_RVANKA(playerid, data))
	{
		return 1;
	}
	
	return 1;
}

/*!
	Синхронизация урона
	@param [in] playerid Игрок
	@param [in] bs BitStream
*/

IPacket:ID_BULLET_SYNC(playerid, BitStream: bs)
{
	new data		[PR_BulletSync];
	
	BS_IgnoreBits(bs, 8);
	BS_ReadBulletSync(bs, data);

	if (!(BULLET_HIT_TYPE_NONE <= data[PR_hitType] <= BULLET_HIT_TYPE_PLAYER_OBJECT) 
	|| data[PR_hitType] == BULLET_HIT_TYPE_PLAYER && !(0 <= data[PR_hitId] < MAX_PLAYERS) 
	|| data[PR_hitType] == BULLET_HIT_TYPE_VEHICLE && !(1 <= data[PR_hitId] < MAX_VEHICLES) 
	|| data[PR_hitType] == BULLET_HIT_TYPE_OBJECT && !(1 <= data[PR_hitId] < MAX_OBJECTS) 
	|| data[PR_hitType] == BULLET_HIT_TYPE_PLAYER_OBJECT && !(1 <= data[PR_hitId] < MAX_OBJECTS)
	|| !IsBulletWeapon(data[PR_weaponId]))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [FILTER][ID_BULLET_SYNC] Error sync (playerid: %i)", playerid);
		#endif
		
		return 0;
	}
	
	if (ac_log)
	{
		printf(
			"BULLET_SYNC[%d]:\nhitType %d \nhitId %d \norigin %.2f %.2f %.2f \nhitPos %.2f %.2f %.2f \noffsets %.2f %.2f %.2f \nweaponId %d",
			playerid,
			data[PR_hitType],
			data[PR_hitId],
			data[PR_origin][0],
			data[PR_origin][1],
			data[PR_origin][2],
			data[PR_hitPos][0],
			data[PR_hitPos][1],
			data[PR_hitPos][2],
			data[PR_offsets][0],
			data[PR_offsets][1],
			data[PR_offsets][2],
			data[PR_weaponId]
		);
	}
	
	/// Anticheats
	if (!ID_BULLET_SYNC:AC_WEAPON_HACK(playerid, data))
	{
		return 1;
	}
	
	return 1;
}

/*!
	Синхронизация трейлера
	@param [in] playerid Игрок
	@param [in] bs BitStream
*/

IPacket:ID_TRAILER_SYNC(playerid, BitStream: bs)
{
	new data	[PR_TrailerSync];
	
    BS_IgnoreBits(bs, 8);
    BS_ReadTrailerSync(BitStream:bs, data);

	// Filter packets
	if (!Raknet_IsValidPosition(data[PR_position])
    || !Raknet_IsValidQuaternion(data[PR_quaternion])
	|| !Raknet_IsValidVelocity(data[PR_velocity])
	|| !Raknet_IsValidAngularVelocity(data[PR_velocity]))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [FILTER][ID_TRAILER_SYNC] Error sync (playerid: %i)", playerid);
		#endif
		
		return 0;
	}
	
	if (ac_log)
	{
		printf(
			"TRAILER_SYNC[%d]:\ntrailerId %d \nposition %.2f %.2f %.2f \nquaternion %.2f %.2f %.2f %.2f \nvelocity %.2f %.2f %.2f \nangularVelocity %.2f %.2f %.2f",
			playerid,
			data[PR_trailerId],
			data[PR_position][0],
			data[PR_position][1],
			data[PR_position][2],
			data[PR_quaternion][0],
			data[PR_quaternion][1],
			data[PR_quaternion][2],
			data[PR_quaternion][3],
			data[PR_velocity][0],
			data[PR_velocity][1],
			data[PR_velocity][2],
			data[PR_angularVelocity][0],
			data[PR_angularVelocity][1],
			data[PR_angularVelocity][2]
		);
	}
	
	/// Anticheats
	if (!ID_TRAILER_SYNC:AC_TRAILER_TELEPORT(playerid, data))
	{
		return 1;
	}
	
	return 1;
}

/*!
	Синхронизация прицеливания
	@param [in] playerid Игрок
	@param [in] bs BitStream
*/

IPacket:ID_AIM_SYNC(playerid, BitStream: bs)
{
	new data	[PR_AimSync];
	
    BS_IgnoreBits(bs, 8);
    BS_ReadAimSync(BitStream: bs, data);
	
	// Filter packets
	if (!Raknet_IsValidPosition(data[PR_camPos])
	|| !Raknet_IsValidAngularVelocity(data[PR_camFrontVec])
	|| !Raknet_IsValidData(data[PR_aimZ])
	|| floatcmp(floatabs(data[PR_aimZ]), 1.50000) == 1)
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [FILTER][ID_AIM_SYNC] Error sync (playerid: %i)", playerid);
		#endif
		
		return 0;
	}
	
	if (ac_log)
	{
		printf(
			"AIM_SYNC[%d]:\ncamMode %d \ncamFrontVec %.2f %.2f %.2f \ncamPos %.2f %.2f %.2f \naimZ %.2f \nweaponState %d \ncamZoom %d \naspectRatio %d",
			playerid,
			data[PR_camMode],
			data[PR_camFrontVec][0],
			data[PR_camFrontVec][1],
			data[PR_camFrontVec][2],
			data[PR_camPos][0],
			data[PR_camPos][1],
			data[PR_camPos][2],
			data[PR_aimZ],
			data[PR_weaponState],
			data[PR_camZoom],
			data[PR_aspectRatio]
		);
	}
	
	return 1;
}

/*!
	Синхронизация наблюдения
	@param [in] playerid Игрок
	@param [in] bs BitStream
*/

IPacket:ID_SPECTATOR_SYNC(playerid, BitStream: bs)
{
	new data		[PR_SpectatingSync];

	BS_IgnoreBits(bs, 8);
	BS_ReadSpectatingSync(bs, data);

	if (!Raknet_IsValidPosition(data[PR_position]))
	{
		#if __AC_DEBUG >= __AC_REPORTING_WARNING
			printf(#__AC_VERSION ": [FILTER][ID_SPECTATOR_SYNC] Error sync (playerid: %i)", playerid);
		#endif
		
		return 0;
	}
	
	return 1;
}


// Functions

// Валидация позиции
Raknet_IsValidPosition(Float: position[])
{
	return !(isnan(position[0]) || floatcmp(floatabs(position[0]), 20000.00000) == 1
	|| isnan(position[1]) || floatcmp(floatabs(position[1]), 20000.00000) == 1
	|| isnan(position[2]) || floatcmp(floatabs(position[2]), 20000.00000) == 1);
}

// Валидация кватернионов
Raknet_IsValidQuaternion(Float: quaternion[])
{
	return !(isnan(quaternion[0]) || floatcmp(floatabs(quaternion[0]), 1.0000) == 1
	|| isnan(quaternion[1]) || floatcmp(floatabs(quaternion[1]), 1.0000) == 1
	|| isnan(quaternion[2]) || floatcmp(floatabs(quaternion[2]), 1.0000) == 1
	|| isnan(quaternion[3]) || floatcmp(floatabs(quaternion[3]), 1.0000) == 1);
}

// Валидация velocity
Raknet_IsValidVelocity(Float: velocity[])
{
	return !(isnan(velocity[0]) || floatcmp(floatabs(velocity[0]), 100.0000) == 1
	|| isnan(velocity[1]) || floatcmp(floatabs(velocity[1]), 100.0000) == 1
	|| isnan(velocity[2]) || floatcmp(floatabs(velocity[2]), 100.0000) == 1);
}

// Валидация angular velocity
Raknet_IsValidAngularVelocity(Float: velocity[])
{
	return !(isnan(velocity[0]) || floatcmp(floatabs(velocity[0]), 1.00000) == 1
	|| isnan(velocity[1]) || floatcmp(floatabs(velocity[1]), 1.00000) == 1
	|| isnan(velocity[2]) || floatcmp(floatabs(velocity[2]), 1.00000) == 1);
}

// Валидация данных на NaN, минимальное и максимальное значение
Raknet_IsValidData(Float: data)
{
	return !(isnan(data) || floatcmp(data, 0x7F800000) == 0 || floatcmp(data, 0xFF800000) == 0);
}