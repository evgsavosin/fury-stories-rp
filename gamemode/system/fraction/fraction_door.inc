/*!
	@brief Система дверей
	@author Found (evg.savosin)
	@date 05.01.2020
*/

Create:fraction_door_all(findex)
{
	new tmpobjid,
		id = GetFractionIdByIndex(findex);
	
	if (id == FRACTION_PD)
	{
		/*
			
			@brief LSPD Headquarters
			
		*/
		
		// Interior
		tmpobjid = CreateDynamicObject(19857, -344.937957, 2517.413574, 1504.649291, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); // pdhq_1_close
		SetDynamicObjectMaterial(tmpobjid, 0, 14846, "genintintpoliceb", "p_door1", 0xFFFFFFFF);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-344.937957, 2517.413574, 1504.649291, 0.000000, 0.000000, 90.000000,
			-344.937957, 2517.413574, 1504.649291, 0.000000, 0.000000, 160.000000
		);
		
		tmpobjid = CreateDynamicObject(19857, -329.617431, 2518.904785, 1504.649291, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00); // pdhq_2_close
		SetDynamicObjectMaterial(tmpobjid, 0, 14846, "genintintpoliceb", "p_door1", 0xFFFFFFFF);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-329.617431, 2518.904785, 1504.649291, 0.000000, 0.000000, 270.000000,
			-329.617431, 2518.904785, 1504.649291, 0.000000, 0.000000, 340.000000
		);
		
		tmpobjid = CreateDynamicObject(1495, -717.167602, 2537.195556, 1500.387329, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00); // pdhq_3_close
		SetDynamicObjectMaterial(tmpobjid, 0, 2343, "cb_bar_bits", "CJ_POLISHED", 0xFFFFFFFF);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-717.167602, 2537.195556, 1500.387329, 0.000000, 0.000000, 270.000000,
			-717.167602, 2537.195556, 1500.387329, 0.000000, 0.000000, 360.000000
		);
		
		// Exterior
		tmpobjid = CreateDynamicObject(968, 1544.703979, -1630.747192, 13.130474, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00); // pdhq_ex_1_close
		SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 3629, "arprtxxref_las", "chevron64HVa", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 15.0,
			1544.703979, -1630.747192, 13.130474, 0.000000, 90.000000, 90.000000,
			1544.703979, -1630.747192, 13.130474, 0.000000, 10.000000, 90.000000
		);
		
		/*
			
			@brief LSPD Verona 96th
			
		*/
		
		// Interior
		tmpobjid = CreateDynamicObject(19857, 886.026977, 895.021362, 1504.054321, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00); // pdverona_1_close
		SetDynamicObjectMaterial(tmpobjid, 0, 14846, "genintintpoliceb", "p_door1", 0xFFFFFFFF);
		Create:fraction_door(findex, tmpobjid, 2.0,
			886.026977, 895.021362, 1504.054321, 0.000000, 0.000000, 270.000000,
			886.026977, 895.021362, 1504.054321, 0.000000, 0.000000, 360.000000
		);
		
		tmpobjid = CreateDynamicObject(19857, 886.026977, 885.531250, 1504.054321, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00); // pdverona_2_close
		SetDynamicObjectMaterial(tmpobjid, 0, 14846, "genintintpoliceb", "p_door1", 0xFFFFFFFF);
		Create:fraction_door(findex, tmpobjid, 2.0,
			886.026977, 885.531250, 1504.054321, 0.000000, 0.000000, 270.000000,
			886.026977, 885.531250, 1504.054321, 0.000000, 0.000000, 360.000000
		);
		
		// Exterior
		
		
		/*
			
			@brief LSPD Saints 
			
		*/
		
		// Interior
		tmpobjid = CreateDynamicObject(3089, 1088.666137, 1936.692504, 1504.568969, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // pdsaints_1_close
		SetDynamicObjectMaterial(tmpobjid, 0, 14581, "ab_mafiasuitea", "barbersmir1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 2343, "cb_bar_bits", "CJ_POLISHED", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 2, 2423, "cj_ff_counters", "CJ_Laminate1", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			1088.666137, 1936.692504, 1504.568969, 0.000000, 0.000000, 180.000000,
			1088.666137, 1936.692504, 1504.568969, 0.000000, 0.000000, 270.000000
		);
		
		tmpobjid = CreateDynamicObject(3089, 1063.059570, 2450.238769, 1500.907104, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); // pdsaints_2_close
		SetDynamicObjectMaterial(tmpobjid, 0, 14581, "ab_mafiasuitea", "barbersmir1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 2343, "cb_bar_bits", "CJ_POLISHED", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 2, 2423, "cj_ff_counters", "CJ_Laminate1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 3, 2423, "cj_ff_counters", "CJ_Laminate1", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			1063.059570, 2450.238769, 1500.907104, 0.000000, 0.000000, 90.000000,
			1063.059570, 2450.238769, 1500.907104, 0.000000, 0.000000, 180.000000
		);
		
		tmpobjid = CreateDynamicObject(3089, 1067.061279, 2451.719970, 1500.907104, 0.000000, 0.000000, 270.000000, -1, -1, -1, 300.00, 300.00); // pdsaints_4_close
		SetDynamicObjectMaterial(tmpobjid, 0, 14581, "ab_mafiasuitea", "barbersmir1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 2343, "cb_bar_bits", "CJ_POLISHED", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 2, 2423, "cj_ff_counters", "CJ_Laminate1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 3, 2423, "cj_ff_counters", "CJ_Laminate1", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			1067.061279, 2451.719970, 1500.907104, 0.000000, 0.000000, 270.000000,
			1067.061279, 2451.719970, 1500.907104, 0.000000, 0.000000, 360.000000
		);
		
		// Exterior
		tmpobjid = CreateDynamicObject(968, 2748.013183, -1471.458251, 30.188800, 0.000000, 10.000000, 90.000000, -1, -1, -1, 300.00, 300.00); // pdsaints_ex_1_close
		SetDynamicObjectMaterial(tmpobjid, 0, 3629, "arprtxxref_las", "chevron64HVa", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 3629, "arprtxxref_las", "chevron64HVa", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 15.0,
			2748.013183, -1471.458251, 30.188800, 0.000000, 10.000000, 90.000000,
			2748.013183, -1471.458251, 30.188800, 0.000000, 90.000000, 90.000000
		);
	}
	else if (id == FRACTION_SD)
	{
		/*
			
			@brief LSCSD Los Santos
			
		*/
		
		// Interior
		tmpobjid = CreateDynamicObject(3089, 349.825653, 2311.735107, 1504.420166, 0.000000, 0.000000, -89.900093, -1, -1, -1, 300.00, 300.00); // sdrc_1_close
		SetDynamicObjectMaterial(tmpobjid, 0, 14581, "ab_mafiasuitea", "barbersmir1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 1560, "7_11_door", "cj_sheetmetal2", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 2, 19339, "coffin01", "coffin_top01", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			349.825653, 2311.735107, 1504.420166, 0.000000, 0.000000, -89.900093,
			349.825653, 2311.735107, 1504.420166, 0.000000, 0.000000, -179.900085
		);
		
		tmpobjid = CreateDynamicObject(3089, 357.755493, 2311.743896, 1504.420166, 0.000000, 0.000000, -89.900093, -1, -1, -1, 300.00, 300.00); // sdrc_2_close
		SetDynamicObjectMaterial(tmpobjid, 0, 14581, "ab_mafiasuitea", "barbersmir1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 1560, "7_11_door", "cj_sheetmetal2", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 2, 19339, "coffin01", "coffin_top01", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			357.755493, 2311.743896, 1504.420166, 0.000000, 0.000000, -89.900093,
			357.755493, 2311.743896, 1504.420166, 0.000000, 0.000000, 0.099906
		);
		
		// Exterior
		tmpobjid = CreateDynamicObject(968, 2376.417724, -1960.596679, 13.206874, 0.000000, 270.000000, 0.000000, -1, -1, -1, 300.00, 300.00); // sdls_1_close
		SetDynamicObjectMaterial(tmpobjid, 0, 1239, "icons6", "lyellow32", 0xFFFFFFFF);
		SetDynamicObjectMaterial(tmpobjid, 1, 3629, "arprtxxref_las", "chevron64HVa", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 15.0,
			2376.417724, -1960.596679, 13.206874, 0.000000, 270.000000, 0.000000,
			2376.417724, -1960.596679, 13.206874, 0.000000, 350.000000, 0.000000
		);
		
		/*
			
			@brief Prison
			
		*/
		
		// Interior
		tmpobjid = CreateDynamicObject(19302, -1544.617431, 1986.980590, 1144.873168, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); // door_closed
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1544.617431, 1986.980590, 1144.873168, 0.000000, 0.000000, 90.000000,
			-1544.617431, 1985.890502, 1144.873168, 0.000000, 0.000000, 90.000000
		);
		
		// Решётки
		// left -3
		// right 2.2
		
		// 1
		tmpobjid = CreateDynamicObject(19869, -1534.146850, 1995.793334, 1139.389404, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); // gate1 - right
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1534.146850, 1995.793334, 1139.389404, 0.000000, 0.000000, 0.000000,
			-1534.146850 + 2.2, 1995.793334, 1139.389404, 0.000000, 0.000000, 0.000000,
			DOOR_PRISON
		);
		
		// 2
		tmpobjid = CreateDynamicObject(19869, -1529.035522, 1995.793334, 1139.389404, 0.000000, 0.000007, 0.000000, -1, -1, -1, 300.00, 300.00); // gate2 - left
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1529.035522, 1995.793334, 1139.389404, 0.000000, 0.000007, 0.000000,
			-1529.035522 - 3.0, 1995.793334, 1139.389404, 0.000000, 0.000007, 0.000000,
			DOOR_PRISON
		);
		
		// 3
		tmpobjid = CreateDynamicObject(19869, -1523.904541, 1995.793334, 1139.389404, 0.000000, 0.000014, 0.000000, -1, -1, -1, 300.00, 300.00); // gate3 - right
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1523.904541, 1995.793334, 1139.389404, 0.000000, 0.000014, 0.000000,
			-1523.904541 + 2.2, 1995.793334, 1139.389404, 0.000000, 0.000014, 0.000000,
			DOOR_PRISON
		);
		
		
		// 4
		tmpobjid = CreateDynamicObject(19869, -1518.764038, 1995.793334, 1139.389404, 0.000000, 0.000022, 0.000000, -1, -1, -1, 300.00, 300.00); // gate4 - left
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1518.764038, 1995.793334, 1139.389404, 0.000000, 0.000022, 0.000000,
			-1518.764038 - 3.0, 1995.793334, 1139.389404, 0.000000, 0.000022, 0.000000,
			DOOR_PRISON
		);
		
		// 5
		tmpobjid = CreateDynamicObject(19869, -1513.653076, 1995.793334, 1139.389404, 0.000000, 0.000029, 0.000000, -1, -1, -1, 300.00, 300.00); // gate5 - right
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1513.653076, 1995.793334, 1139.389404, 0.000000, 0.000029, 0.000000,
			-1513.653076 + 2.2, 1995.793334, 1139.389404, 0.000000, 0.000029, 0.000000,
			DOOR_PRISON
		);
		
		// 6
		tmpobjid = CreateDynamicObject(19869, -1534.880004, 1986.942138, 1139.389404, 0.000000, 0.000037, 179.999893, -1, -1, -1, 300.00, 300.00); // gate6 - left
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1534.880004, 1986.942138, 1139.389404, 0.000000, 0.000037, 179.999893,
			-1534.880004 - 2.2, 1986.942138, 1139.389404, 0.000000, 0.000037, 179.999893,
			DOOR_PRISON
		);
		
		// 7
		tmpobjid = CreateDynamicObject(19869, -1529.749633, 1986.942138, 1139.389404, 0.000000, 0.000029, 179.999893, -1, -1, -1, 300.00, 300.00); // gate7 - right
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1529.749633, 1986.942138, 1139.389404, 0.000000, 0.000029, 179.999893,
			-1529.749633 + 3.0, 1986.942138, 1139.389404, 0.000000, 0.000029, 179.999893,
			DOOR_PRISON
		);
		
		// 8
		tmpobjid = CreateDynamicObject(19869, -1524.638671, 1986.942138, 1139.389404, 0.000000, 0.000022, 179.999893, -1, -1, -1, 300.00, 300.00); // gate8 - left
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1524.638671, 1986.942138, 1139.389404, 0.000000, 0.000022, 179.999893,
			-1524.638671 - 2.2, 1986.942138, 1139.389404, 0.000000, 0.000022, 179.999893,
			DOOR_PRISON
		);
		
		
		// 9
		tmpobjid = CreateDynamicObject(19869, -1519.498168, 1986.942138, 1139.389404, 0.000000, 0.000014, 179.999893, -1, -1, -1, 300.00, 300.00); // gate9 - right
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1519.498168, 1986.942138, 1139.389404, 0.000000, 0.000014, 179.999893,
			-1519.498168 + 3.0, 1986.942138, 1139.389404, 0.000000, 0.000014, 179.999893,
			DOOR_PRISON
		);
		
		// 10
		tmpobjid = CreateDynamicObject(19869, -1514.367187, 1986.942138, 1139.389404, 0.000000, 0.000007, 179.999893, -1, -1, -1, 300.00, 300.00); // gate10 - left
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1514.367187, 1986.942138, 1139.389404, 0.000000, 0.000007, 179.999893,
			-1514.367187 - 2.2, 1986.942138, 1139.389404, 0.000000, 0.000007, 179.999893,
			DOOR_PRISON
		);
		
		// 2 STAGE
		
		// 11
		tmpobjid = CreateDynamicObject(19869, -1534.146850, 1995.793334, 1143.630126, 0.000000, 0.000007, 0.000000, -1, -1, -1, 300.00, 300.00); // gate11 - right
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1534.146850, 1995.793334, 1143.630126, 0.000000, 0.000007, 0.000000,
			-1534.146850 + 2.2, 1995.793334, 1143.630126, 0.000000, 0.000007, 0.000000,
			DOOR_PRISON
		);
		
		// 12 
		tmpobjid = CreateDynamicObject(19869, -1529.035522, 1995.793334, 1143.630126, 0.000000, 0.000014, 0.000000, -1, -1, -1, 300.00, 300.00); // gate12 - left
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1529.035522, 1995.793334, 1143.630126, 0.000000, 0.000014, 0.000000,
			-1529.035522 - 3.0, 1995.793334, 1143.630126, 0.000000, 0.000014, 0.000000,
			DOOR_PRISON
		);
		
		// 13 
		tmpobjid = CreateDynamicObject(19869, -1523.904541, 1995.793334, 1143.630126, 0.000000, 0.000022, 0.000000, -1, -1, -1, 300.00, 300.00); // gate13 - right
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1523.904541, 1995.793334, 1143.630126, 0.000000, 0.000022, 0.000000,
			-1523.904541 + 2.2, 1995.793334, 1143.630126, 0.000000, 0.000022, 0.000000,
			DOOR_PRISON
		);
		
		// 14 
		tmpobjid = CreateDynamicObject(19869, -1518.764038, 1995.793334, 1143.630126, 0.000000, 0.000029, 0.000000, -1, -1, -1, 300.00, 300.00); // gate14 - left
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1518.764038, 1995.793334, 1143.630126, 0.000000, 0.000029, 0.000000,
			-1518.764038 - 3.0, 1995.793334, 1143.630126, 0.000000, 0.000029, 0.000000,
			DOOR_PRISON
		);
		
		// 15
		tmpobjid = CreateDynamicObject(19869, -1513.653076, 1995.793334, 1143.630126, 0.000000, 0.000037, 0.000000, -1, -1, -1, 300.00, 300.00); // gate15 - right
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1513.653076, 1995.793334, 1143.630126, 0.000000, 0.000037, 0.000000,
			-1513.653076 + 2.2, 1995.793334, 1143.630126, 0.000000, 0.000037, 0.000000,
			DOOR_PRISON
		);
		
		// 2 STAGE
		// 16
		tmpobjid = CreateDynamicObject(19869, -1534.880004, 1986.942138, 1143.630126, 0.000000, 0.000029, 179.999847, -1, -1, -1, 300.00, 300.00); // gate16 - left
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1534.880004, 1986.942138, 1143.630126, 0.000000, 0.000029, 179.999847,
			-1534.880004 - 2.2, 1986.942138, 1143.630126, 0.000000, 0.000029, 179.999847,
			DOOR_PRISON
		);
		
		// 17
		tmpobjid = CreateDynamicObject(19869, -1529.749633, 1986.942138, 1143.630126, 0.000000, 0.000022, 179.999847, -1, -1, -1, 300.00, 300.00); // gate17 - right
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1529.749633, 1986.942138, 1143.630126, 0.000000, 0.000022, 179.999847,
			-1529.749633 + 3.0, 1986.942138, 1143.630126, 0.000000, 0.000022, 179.999847,
			DOOR_PRISON
		);
		
		// 18 
		tmpobjid = CreateDynamicObject(19869, -1524.638671, 1986.942138, 1143.630126, 0.000000, 0.000014, 179.999847, -1, -1, -1, 300.00, 300.00); // gate18 - left
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1524.638671, 1986.942138, 1143.630126, 0.000000, 0.000014, 179.999847,
			-1524.638671 - 2.2, 1986.942138, 1143.630126, 0.000000, 0.000014, 179.999847,
			DOOR_PRISON
		);
		
		// 19
		tmpobjid = CreateDynamicObject(19869, -1519.498168, 1986.942138, 1143.630126, 0.000000, 0.000007, 179.999847, -1, -1, -1, 300.00, 300.00); // gate19 - right
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1519.498168, 1986.942138, 1143.630126, 0.000000, 0.000007, 179.999847,
			-1519.498168 + 3.0, 1986.942138, 1143.630126, 0.000000, 0.000007, 179.999847,
			DOOR_PRISON
		);
		
		// 20
		tmpobjid = CreateDynamicObject(19869, -1514.367187, 1986.942138, 1143.630126, 0.000000, 0.000000, 179.999847, -1, -1, -1, 300.00, 300.00); // gate20 - left
		SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
		SetDynamicObjectMaterial(tmpobjid, 1, 16322, "a51_stores", "fence_64", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-1514.367187, 1986.942138, 1143.630126, 0.000000, 0.000000, 179.999847,
			-1514.367187 - 2.2, 1986.942138, 1143.630126, 0.000000, 0.000000, 179.999847,
			DOOR_PRISON
		);
		
		// Exterior
		tmpobjid = CreateDynamicObject(1495, 1761.595458, -1561.498901, 8.598464, 0.000000, 0.000000, -179.500000, -1, -1, -1, 300.00, 300.00); // door_1_close
		Create:fraction_door(findex, tmpobjid, 2.0,
			1761.595458, -1561.498901, 8.598464, 0.000000, 0.000000, -179.500000,
			1761.595458, -1561.498901, 8.598464, 0.000000, 0.000000, -89.500000,
			DOOR_PRISON
		);
		
		tmpobjid = CreateDynamicObject(1495, 1781.247314, -1539.542602, 8.978474, 0.000000, 0.000000, 97.500022, -1, -1, -1, 300.00, 300.00); // door_2_close
		Create:fraction_door(findex, tmpobjid, 2.0,
			1781.247314, -1539.542602, 8.978474, 0.000000, 0.000000, 97.500022,
			1781.247314, -1539.542602, 8.978474, 0.000000, 0.000000, 7.500030,
			DOOR_PRISON
		);
	}
	else if (id == FRACTION_GOVERNMENT)
	{
		/*
			
			@brief LSG City Hall
			
		*/
		
		// Interior
		tmpobjid = CreateDynamicObject(1504, 1970.882446, 1364.383422, 2517.977050, 0.000000, 0.000036, 0.000000, -1, -1, -1, 300.00, 300.00); // ch_1_close
		SetDynamicObjectMaterial(tmpobjid, 0, 3698, "comedbarrio1_la", "compdoor5_LAe", 0xFFF0FFFF);
		Create:fraction_door(findex, tmpobjid, 2.0,
			1970.882446, 1364.383422, 2517.977050, 0.000000, 0.000036, 0.000000,
			1970.882446, 1364.383422, 2517.977050, 0.000000, 0.000036, 90.000000
		);
		
		tmpobjid = CreateDynamicObject(1504, 1973.892211, 1364.413452, 2517.977050, 0.000000, 0.000018, 179.999954, -1, -1, -1, 300.00, 300.00); // ch_2_close
		SetDynamicObjectMaterial(tmpobjid, 0, 3698, "comedbarrio1_la", "compdoor5_LAe", 0xFFF0FFFF);
		Create:fraction_door(findex, tmpobjid, 2.0,
			1973.892211, 1364.413452, 2517.977050, 0.000000, 0.000018, 179.999954,
			1973.892211, 1364.413452, 2517.977050, 0.000000, 0.000018, 89.999954
		);
		
		// Exterior
	}
	else if (id == FRACTION_NP)
	{
		// Interior
		tmpobjid = CreateDynamicObject(1495, -7.100724, 2050.064941, 1503.013305, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); // np_1_close
		SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
		Create:fraction_door(findex, tmpobjid, 2.0,
			-7.100724, 2050.064941, 1503.013305, 0.000000, 0.000000, 0.000000,
			-7.100724, 2050.064941, 1503.013305, 0.000000, 0.000000, 90.000000
		);
		
		tmpobjid = CreateDynamicObject(1495, 195.954269, 1419.625976, 1503.046264, 0.000000, 0.000000, 540.000000, -1, -1, -1, 300.00, 300.00); // np_2_close
		SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
		Create:fraction_door(findex, tmpobjid, 2.0,
			195.954269, 1419.625976, 1503.046264, 0.000000, 0.000000, 540.000000,
			195.954269, 1419.625976, 1503.046264, 0.000000, 0.000000, 630.000000
		);
	}
	else if (id == FRACTION_FD)
	{
		// Exterior
		tmpobjid = CreateDynamicObject(11319, 725.920471, -1340.083007, 15.411600, -0.000014, 0.000000, -89.999923, -1, -1, -1, 300.00, 300.00); // gate1-close
		SetDynamicObjectMaterial(tmpobjid, 0, 10763, "airport1_sfse", "ws_rollerdoor_fire", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 4.0,
			725.920471, -1340.083007, 15.411600, -0.000014, 0.000000, -89.999923,
			725.924865, -1340.083007, 18.245100, -0.000014, 85.000000, -89.999923
		);
		
		tmpobjid = CreateDynamicObject(11319, 736.472900, -1340.083007, 15.411600, -0.000014, 0.000000, -89.999923, -1, -1, -1, 300.00, 300.00); // gate2-close
		SetDynamicObjectMaterial(tmpobjid, 0, 10763, "airport1_sfse", "ws_rollerdoor_fire", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 4.0,
			736.472900, -1340.083007, 15.411600, -0.000014, 0.000000, -89.999923,
			736.474914, -1340.083007, 18.245100, -0.000014, 85.000000, -89.999923
		);
		
		tmpobjid = CreateDynamicObject(11319, 747.013916, -1340.083007, 15.411600, -0.000014, 0.000000, -89.999923, -1, -1, -1, 300.00, 300.00); // gate3-close
		SetDynamicObjectMaterial(tmpobjid, 0, 10763, "airport1_sfse", "ws_rollerdoor_fire", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 4.0,
			747.013916, -1340.083007, 15.411600, -0.000014, 0.000000, -89.999923,
			747.014709, -1340.083007, 18.245100, -0.000014, 85.000000, -89.999923
		);
		
		tmpobjid = CreateDynamicObject(11319, 757.474304, -1340.083007, 15.411600, -0.000014, 0.000000, -89.999923, -1, -1, -1, 300.00, 300.00); // gate4-close
		SetDynamicObjectMaterial(tmpobjid, 0, 10763, "airport1_sfse", "ws_rollerdoor_fire", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 4.0,
			757.474304, -1340.083007, 15.411600, -0.000014, 0.000000, -89.999923,
			757.489868, -1340.083007, 18.245100, -0.000014, 85.000000, -89.999923
		);
		
		tmpobjid = CreateDynamicObject(11319, 770.954528, -1330.562377, 15.411600, -0.000014, 0.000000, -89.999923, -1, -1, -1, 300.00, 300.00); // gate5-close
		SetDynamicObjectMaterial(tmpobjid, 0, 10763, "airport1_sfse", "ws_rollerdoor_fire", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 4.0,
			770.954528, -1330.562377, 15.411600, -0.000014, 0.000000, -89.999923,
			770.990905, -1330.507324, 18.375099, -0.000014, 85.000000, -89.999923
		);
		
		tmpobjid = CreateDynamicObject(11319, 770.999816, -1378.557983, 15.411600, -0.000014, 0.000000, -89.999923, -1, -1, -1, 300.00, 300.00); // gate6-close
		SetDynamicObjectMaterial(tmpobjid, 0, 10763, "airport1_sfse", "ws_rollerdoor_fire", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 4.0,
			770.999816, -1378.557983, 15.411600, -0.000014, 0.000000, -89.999923,
			770.990905, -1378.488891, 18.277439, -0.000014, -85.000000, -89.999923
		);
		
		tmpobjid = CreateDynamicObject(11319, 757.489868, -1369.118164, 15.411600, -0.000014, 0.000000, -89.999923, -1, -1, -1, 300.00, 300.00); // gate7-close
		SetDynamicObjectMaterial(tmpobjid, 0, 10763, "airport1_sfse", "ws_rollerdoor_fire", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 4.0,
			757.489868, -1369.118164, 15.411600, -0.000014, 0.000000, -89.999923,
			757.489990, -1368.988403, 18.235242, -0.000014, -85.000000, -89.999923
		);
		
		tmpobjid = CreateDynamicObject(11319, 747.014709, -1369.118164, 15.411600, -0.000014, 0.000000, -89.999923, -1, -1, -1, 300.00, 300.00); // gate8-close
		SetDynamicObjectMaterial(tmpobjid, 0, 10763, "airport1_sfse", "ws_rollerdoor_fire", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 4.0,
			747.014709, -1369.118164, 15.411600, -0.000014, 0.000000, -89.999923,
			747.010009, -1368.988403, 18.235242, -0.000014, -85.000000, -89.999923
		);
		
		tmpobjid = CreateDynamicObject(11319, 736.472900, -1369.118164, 15.411600, -0.000014, 0.000000, -89.999923, -1, -1, -1, 300.00, 300.00); // gate9-close
		SetDynamicObjectMaterial(tmpobjid, 0, 10763, "airport1_sfse", "ws_rollerdoor_fire", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 4.0,
			736.472900, -1369.118164, 15.411600, -0.000014, 0.000000, -89.999923,
			736.470031, -1368.988403, 18.235242, -0.000014, -85.000000, -89.999923
		);
		
		tmpobjid = CreateDynamicObject(11319, 725.920471, -1369.118164, 15.411600, -0.000014, 0.000000, -89.999923, -1, -1, -1, 300.00, 300.00); // gate10-close
		SetDynamicObjectMaterial(tmpobjid, 0, 10763, "airport1_sfse", "ws_rollerdoor_fire", 0x00000000);
		Create:fraction_door(findex, tmpobjid, 4.0,
			725.920471, -1369.118164, 15.411600, -0.000014, 0.000000, -89.999923,
			725.909973, -1368.988403, 18.235242, -0.000014, -85.000000, -89.999923
		);
	}
}

SetFractionCameraStateDoor(findex)
{
	new Float: speed = 1.0;
	
	fprison_camera_status = !fprison_camera_status;
	
	for (new i; i < MAX_FRACTION_DOORS; i++)
	{
		if (fraction_door[findex][i][fr_type] != DOOR_PRISON)
		{
			continue;
		}
		
		if (fprison_camera_status)
		{
			MoveDynamicObject(
				fraction_door[findex][i][fr_object_id], 
				fraction_door[findex][i][fr_begin_pos][0],
				fraction_door[findex][i][fr_begin_pos][1],
				fraction_door[findex][i][fr_begin_pos][2], 
				speed, 
				fraction_door[findex][i][fr_begin_pos][3],
				fraction_door[findex][i][fr_begin_pos][4],
				fraction_door[findex][i][fr_begin_pos][5]
			);
		}
		else
		{
			MoveDynamicObject(
				fraction_door[findex][i][fr_object_id], 
				fraction_door[findex][i][fr_end_pos][0],
				fraction_door[findex][i][fr_end_pos][1],
				fraction_door[findex][i][fr_end_pos][2], 
				speed, 
				fraction_door[findex][i][fr_end_pos][3],
				fraction_door[findex][i][fr_end_pos][4],
				fraction_door[findex][i][fr_end_pos][5]
			);
		}
		
		fraction_door[findex][i][fr_status] = fprison_camera_status;
	}
}

SetFractionStateDoor(findex, index)
{
	new Float: speed = 1.0;
	
	if (fraction_door[findex][index][fr_status])
	{
		MoveDynamicObject(
			fraction_door[findex][index][fr_object_id], 
			fraction_door[findex][index][fr_begin_pos][0],
			fraction_door[findex][index][fr_begin_pos][1],
			fraction_door[findex][index][fr_begin_pos][2], 
			speed, 
			fraction_door[findex][index][fr_begin_pos][3],
			fraction_door[findex][index][fr_begin_pos][4],
			fraction_door[findex][index][fr_begin_pos][5]
		);
	}
	else
	{
		MoveDynamicObject(
			fraction_door[findex][index][fr_object_id], 
			fraction_door[findex][index][fr_end_pos][0],
			fraction_door[findex][index][fr_end_pos][1],
			fraction_door[findex][index][fr_end_pos][2], 
			speed, 
			fraction_door[findex][index][fr_end_pos][3],
			fraction_door[findex][index][fr_end_pos][4],
			fraction_door[findex][index][fr_end_pos][5]
		);
	}
	
	fraction_door[findex][index][fr_status] = !fraction_door[findex][index][fr_status];
}