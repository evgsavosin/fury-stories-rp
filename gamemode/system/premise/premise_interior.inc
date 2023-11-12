/*!
	@brief Интерьер для системы помещений
	@author Found (evg.savosin)
	@date 16.12.2016, update 19.03.2018
*/

/*
	pint_roof_begin/end
	pint_wall_begin/end 
	pint_floor_begin/end
	
	premise_int_obj[index][номер_комнаты][pint_roof_begin]
	premise_int_obj[index][номер_комнаты][pint_roof_end]
*/

Create:premise_object(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1)
{
	new objectid = CreateDynamicObject(modelid, x, y, z, rx, ry, rz, worldid, INT_PREMISE);
	
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID, TYPE_REN_PREMISE);
	
	return objectid;
}

Create:premise_int_obj(index, interiorid)
{
	new world = premise_data[index][pr_id];
		
	switch(interiorid)
	{
		case 1 : // Магазин [1]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_roof_end] =
			premise_int_obj[index][0][pint_roof_begin] = Create:premise_object(19381, 1710.447265, 1148.925292, 2471.003662, 0.000000, 90.000000, 0.000000, world); // roof0
			
			// [1]
			premise_int_obj[index][1][pint_roof_end] =
			premise_int_obj[index][1][pint_roof_begin] = Create:premise_object(19381, 1720.920043, 1149.210327, 2471.007568, 0.000000, 90.000000, 0.000000, world); // roof1
			
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_wall_begin] = Create:premise_object(19397, 1707.515380, 1145.777832, 2469.177734, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, 1707.508666, 1152.200805, 2469.188232, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, 1710.736791, 1152.080810, 2469.188232, 0.000000, 0.000000, 90.000000, world); // wall0 - x
			Create:premise_object(19461, 1715.619384, 1144.490722, 2469.188232, 0.000000, 0.000000, 180.000000, world); // wall0
			Create:premise_object(19461, 1710.745971, 1144.280761, 2469.188232, 0.000000, 0.000000, 90.000000, world); // wall0
			premise_int_obj[index][0][pint_wall_end] = Create:premise_object(19397, 1715.626220, 1150.897705, 2469.177734, 0.000000, 0.000000, 0.000000, world); // wall0
			
			// [1]
			premise_int_obj[index][1][pint_wall_begin] = Create:premise_object(19461, 1720.475219, 1153.920776, 2469.188232, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:premise_object(19461, 1712.336791, 1152.580810, 2469.188232, 0.000000, 0.000000, 90.000000, world); // wall1 - x
			Create:premise_object(19461, 1721.829345, 1149.100830, 2469.188232, 0.000000, 0.000000, 180.000000, world); // wall1
			Create:premise_object(19461, 1720.515258, 1144.280761, 2469.188232, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:premise_object(19461, 1715.799560, 1144.490722, 2469.188232, 0.000000, 0.000000, 180.000000, world); // wall1
			Create:premise_object(19397, 1715.796386, 1150.897705, 2469.187500, 0.000000, 0.000000, 0.000000, world); // wall1
			premise_int_obj[index][1][pint_wall_end] = Create:premise_object(19461, 1717.235229, 1157.310668, 2469.188232, 0.000000, 0.000000, 180.000000, world); // wall1
			
			/*
				
				@brief Floor - Пол
				
			*/
			
			premise_int_obj[index][0][pint_floor_end] =
			premise_int_obj[index][0][pint_floor_begin] = Create:premise_object(19379, 1710.463378, 1147.732177, 2467.417480, 0.000000, 90.000000, 0.000000, world); // floor0
			
			premise_int_obj[index][1][pint_floor_end] =
			premise_int_obj[index][1][pint_floor_begin] = Create:premise_object(19379, 1720.953857, 1149.171997, 2467.417480, 0.000000, 90.000000, 0.000000, world); // floor1
		}
		
		case 2 : // Магазин [2]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_roof_begin] = Create:premise_object(19381, 2020.002929, 1224.754272, 2464.588867, 0.000000, 90.000000, 0.000000, world); // roof0
			premise_int_obj[index][0][pint_roof_end] = Create:premise_object(19381, 2019.993652, 1234.296508, 2464.593017, 0.000000, 90.000000, 0.000000, world); // roof0
			
			// [1]
			premise_int_obj[index][1][pint_roof_begin] = Create:premise_object(19381, 2030.571166, 1230.617675, 2464.588867, 0.000000, 90.000000, 0.000000, world); // roof1
			premise_int_obj[index][1][pint_roof_end] = Create:premise_object(19381, 2035.341796, 1220.984008, 2464.588867, 0.000000, 90.000000, 0.000000, world); // roof1
			
			// [2]
			premise_int_obj[index][2][pint_roof_end] = 
			premise_int_obj[index][2][pint_roof_begin] = Create:premise_object(19381, 2028.119506, 1220.984008, 2464.597167, 0.000000, 90.000000, 0.000000, world); // roof2

			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_wall_begin] = Create:premise_object(19397, 2018.849731, 1223.407348, 2462.763183, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, 2018.850219, 1229.806762, 2462.763183, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, 2020.546630, 1229.788574, 2462.762207, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19397, 2025.281372, 1228.104736, 2462.759277, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, 2025.285034, 1221.715087, 2462.762207, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, 2020.546630, 1219.906250, 2462.762207, 0.000000, 0.000000, 90.000000, world); // wall0
			premise_int_obj[index][0][pint_wall_end] = Create:premise_object(19461, 2018.850219, 1216.996093, 2462.763183, 0.000000, 0.000000, 0.000000, world); // wall0
		
			// [1]
			premise_int_obj[index][1][pint_wall_begin] = Create:premise_object(19461, 2034.982666, 1219.794921, 2462.762207, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:premise_object(19461, 2035.012695, 1224.673950, 2462.762207, 0.000000, 0.000000, 180.000000, world); // wall1
			Create:premise_object(19461, 2030.161499, 1229.414916, 2462.762207, 0.000000, 0.000000, 270.000000, world); // wall1
			Create:premise_object(19461, 2030.106079, 1221.064941, 2462.762207, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:premise_object(19397, 2028.574218, 1225.801391, 2462.760253, 0.000000, 0.000000, 450.000000, world); // wall1
			Create:premise_object(19442, 2026.173583, 1225.800659, 2462.762207, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:premise_object(19397, 2025.461547, 1228.104736, 2462.759277, 0.000000, 0.000000, 0.000000, world); // wall1
			premise_int_obj[index][1][pint_wall_end] = Create:premise_object(19461, 2025.463256, 1221.696289, 2462.762207, 0.000000, 0.000000, 0.000000, world); // wall1
			
			// [2]
			premise_int_obj[index][2][pint_wall_begin] = Create:premise_object(19442, 2026.173583, 1225.640502, 2462.762207, 0.000000, 0.000000, 90.000000, world); // wall2
			Create:premise_object(19397, 2028.574218, 1225.641235, 2462.760253, 0.000000, 0.000000, 450.000000, world); // wall2
			Create:premise_object(19461, 2030.046875, 1221.064941, 2462.762207, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:premise_object(19461, 2025.374267, 1219.794921, 2462.762207, 0.000000, 0.000000, 90.000000, world); // wall2
			premise_int_obj[index][2][pint_wall_end] = Create:premise_object(19461, 2025.665405, 1221.064453, 2462.762207, 0.000000, 0.000000, 0.000000, world); // wall2

			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_floor_begin] = Create:premise_object(19379, 2020.068481, 1224.609985, 2460.974609, 0.000000, 90.000000, 0.000000, world); // floor0
			premise_int_obj[index][0][pint_floor_end] = Create:premise_object(19379, 2020.050415, 1234.220581, 2460.978759, 0.000000, 90.000000, 0.000000, world); // floor0
			
			// [1]
			premise_int_obj[index][1][pint_floor_begin] = Create:premise_object(19379, 2035.414672, 1224.609985, 2460.974609, 0.000000, 90.000000, 0.000000, world); // floor1
			premise_int_obj[index][1][pint_floor_end] = Create:premise_object(19379, 2024.920654, 1230.499633, 2460.971679, 0.000000, 90.000000, 0.000000, world); // floor1
			
			// [2]
			premise_int_obj[index][2][pint_floor_end] =
			premise_int_obj[index][2][pint_floor_begin] = Create:premise_object(19379, 2024.920654, 1220.898803, 2460.968750, 0.000000, 90.000000, 0.000000, world); // floor2
		}
		
		case 3 : // Минимаркет [1]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_roof_begin] = Create:premise_object(19381, -3071.875732, -1191.190551, 2412.715820, 0.000000, 90.000000, 0.000000, world); // roof0
			premise_int_obj[index][0][pint_roof_end] = Create:premise_object(19381, -3071.875732, -1200.820068, 2412.715820, 0.000000, 90.000000, 0.000000, world); // roof0
			
			// [1]
			premise_int_obj[index][1][pint_roof_end] =
			premise_int_obj[index][1][pint_roof_begin] = Create:premise_object(19381, -3082.524902, -1200.820068, 2412.715820, 0.000000, 90.000000, 0.000000, world); // roof1
			
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_wall_begin] = Create:premise_object(19397, -3068.869628, -1194.946777, 2410.902587, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, -3068.869140, -1188.524780, 2410.902099, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, -3073.774414, -1188.394775, 2410.902099, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19461, -3068.869140, -1201.368408, 2410.902099, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, -3073.774414, -1200.804687, 2410.902099, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19461, -3077.118408, -1193.300415, 2410.902099, 0.000000, 0.000000, 0.000000, world); // wall0
			premise_int_obj[index][0][pint_wall_end] = Create:premise_object(19397, -3077.118408, -1199.722045, 2410.902587, 0.000000, 0.000000, 0.000000, world); // wall0
			
			// [1]
			premise_int_obj[index][1][pint_wall_begin] = Create:premise_object(19461, -3077.297119, -1193.300415, 2410.902099, 0.000000, 0.000022, 0.000000, world); // wall1
			Create:premise_object(19397, -3077.297119, -1199.722045, 2410.902587, 0.000000, 0.000022, 0.000000, world); // wall1
			Create:premise_object(19461, -3080.677978, -1197.620483, 2410.902099, 0.000000, 0.000022, 0.000000, world); // wall1
			Create:premise_object(19461, -3082.194580, -1200.794677, 2410.902099, 0.000000, 0.000000, 90.000000, world); // wall1
			premise_int_obj[index][1][pint_wall_end] = Create:premise_object(19461, -3082.194580, -1196.034667, 2410.902099, 0.000000, 0.000000, 90.000000, world); // wall1
			
			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_floor_begin] = Create:premise_object(19379, -3071.935791, -1193.252563, 2409.068603, 0.000000, 90.000007, 0.000000, world); // floor0
			premise_int_obj[index][0][pint_floor_end] = Create:premise_object(19379, -3071.935791, -1202.885986, 2409.068603, 0.000000, 90.000007, 0.000000, world); // floor0
			
			// [1]
			premise_int_obj[index][1][pint_floor_end] =
			premise_int_obj[index][1][pint_floor_begin] = Create:premise_object(19379, -3082.436767, -1196.442626, 2409.068603, 0.000000, 90.000007, 0.000000, world); // floor1
		}
		
		case 4 : // Минимаркет [2]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_roof_begin] = Create:premise_object(19381, -2997.697753, -1194.706542, 2407.256591, 0.000000, 90.000000, 0.000000, world); // roof0
			premise_int_obj[index][0][pint_roof_end] = Create:premise_object(19381, -2997.697753, -1185.088745, 2407.256591, 0.000000, 90.000000, 0.000000, world); // roof0
			
			// [1]
			premise_int_obj[index][1][pint_roof_end] =
			premise_int_obj[index][1][pint_roof_begin] = Create:premise_object(19381, -2989.822753, -1184.938232, 2407.255615, 0.000000, 90.000000, 0.000000, world); // roof1
		
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_wall_begin] = Create:premise_object(19397, -3002.541503, -1196.501464, 2405.440185, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, -3002.541748, -1202.924438, 2405.440673, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, -2997.650634, -1199.543579, 2405.440673, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19461, -2988.030761, -1199.543579, 2405.440673, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19461, -2992.501953, -1194.663574, 2405.440673, 0.000000, 0.000000, 180.000000, world); // wall0
			Create:premise_object(19461, -3002.541748, -1190.084960, 2405.440673, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, -3004.592285, -1192.806030, 2405.440673, 0.000000, 0.000000, 115.599906, world); // wall0
			Create:premise_object(19461, -3000.299316, -1185.984985, 2405.440673, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, -2995.182373, -1185.032958, 2405.440673, 0.000000, 0.000000, 180.000000, world); // wall0
			Create:premise_object(19397, -2993.663574, -1189.761352, 2405.440185, 0.000000, 0.000000, 90.000000, world); // wall0
			premise_int_obj[index][0][pint_wall_end] = Create:premise_object(19461, -2997.650634, -1183.635253, 2405.440673, 0.000000, 0.000000, 90.000000, world); // wall0
			
			// [1]
			premise_int_obj[index][1][pint_wall_begin] = Create:premise_object(19461, -2990.370117, -1185.285888, 2405.440673, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:premise_object(19461, -2995.152343, -1184.682983, 2405.440673, 0.000000, 0.000000, 180.000000, world); // wall1
			Create:premise_object(19397, -2993.663574, -1189.584106, 2405.440185, 0.000000, 0.000000, 90.000000, world); // wall1
			premise_int_obj[index][1][pint_wall_end] = Create:premise_object(19461, -2992.081542, -1185.032958, 2405.440673, 0.000000, 0.000000, 180.000000, world); // wall1
		
			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_floor_begin] = Create:premise_object(19379, -2997.382568, -1194.769653, 2403.608398, 0.000000, 90.000000, 0.000000, world); // floor0
			premise_int_obj[index][0][pint_floor_end] = Create:premise_object(19379, -2997.386230, -1185.138793, 2403.608398, 0.000000, 90.000000, 0.000000, world); // floor0
			
			// [1]
			
			premise_int_obj[index][1][pint_floor_end] =
			premise_int_obj[index][1][pint_floor_begin] = Create:premise_object(19379, -2989.825195, -1184.858398, 2403.609375, 0.000000, 90.000000, 0.000000, world); // floor1
		}
		
		case 5 : // Минимаркет [3]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_roof_begin] = Create:premise_object(19381, -2910.614501, -814.265197, 2386.048828, 0.000000, 90.000007, 0.000000, world); // roof0
			Create:premise_object(19381, -2910.614501, -804.645507, 2386.048828, 0.000000, 90.000007, 0.000000, world); // roof0
			premise_int_obj[index][0][pint_roof_end] = Create:premise_object(19381, -2900.132812, -807.867126, 2386.048828, 0.000000, 90.000007, 0.000000, world); // roof0
			
			// [1]
			premise_int_obj[index][1][pint_roof_end] = 
			premise_int_obj[index][1][pint_roof_begin] = Create:premise_object(19381, -2899.724853, -817.375488, 2386.048828, 0.000000, 90.000007, 0.000000, world); // roof1

			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_wall_begin] = Create:premise_object(19397, -2913.123046, -814.946716, 2384.236816, 0.000000, 0.000007, 0.000000, world); // wall0
			Create:premise_object(19461, -2913.123291, -821.368225, 2384.236328, 0.000000, 0.000007, 0.000000, world); // wall0
			Create:premise_object(19461, -2910.271484, -818.987121, 2384.236328, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:premise_object(19461, -2913.123291, -808.528686, 2384.236328, 0.000000, 0.000007, 0.000000, world); // wall0
			Create:premise_object(19461, -2908.239746, -803.693359, 2384.236328, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:premise_object(19461, -2905.388183, -803.853027, 2384.236328, 0.000000, 0.000007, 0.000000, world); // wall0
			Create:premise_object(19397, -2905.387695, -810.275024, 2384.236816, 0.000000, 0.000007, 0.000000, world); // wall0
			Create:premise_object(19461, -2905.388183, -816.672790, 2384.236328, 0.000000, 0.000007, 0.000000, world); // wall0
			Create:premise_object(19397, -2903.806152, -812.496215, 2384.236816, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:premise_object(19461, -2900.549072, -809.185668, 2384.236328, 0.000007, 0.000000, 89.999977, world); // wall0
			premise_int_obj[index][0][pint_wall_end] = Create:premise_object(19461, -2902.430664, -807.855468, 2384.236328, 0.000000, -0.000007, 179.999954, world); // wall0

			// [1]
			premise_int_obj[index][1][pint_wall_begin] = Create:premise_object(19461, -2902.983886, -815.964782, 2378.847900, 28.799995, 0.000008, -0.000004, world); // wall1
			Create:premise_object(19461, -2904.665283, -817.543640, 2380.738281, 0.000000, 0.000036, 0.000000, world); // wall1
			Create:premise_object(19461, -2904.665283, -817.543640, 2384.234375, 0.000000, 0.000036, 0.000000, world); // wall1
			Create:premise_object(19461, -2900.453613, -812.674194, 2380.738037, 0.000022, 0.000000, 89.999931, world); // wall1
			Create:premise_object(19461, -2897.971191, -812.673217, 2384.223388, 0.000022, 0.000000, 89.999931, world); // wall1
			Create:premise_object(19397, -2903.806152, -812.674438, 2384.236816, 0.000007, 0.000000, 89.999977, world); // wall1
			Create:premise_object(19461, -2899.054931, -816.672790, 2380.737304, 0.000000, 0.000014, 0.000000, world); // wall1
			Create:premise_object(19461, -2899.054931, -816.672790, 2384.233642, 0.000000, 0.000014, 0.000000, world); // wall1
			Create:premise_object(19461, -2902.374755, -818.524597, 2380.738037, 0.000029, 0.000000, 89.999908, world); // wall1
			premise_int_obj[index][1][pint_wall_end] = Create:premise_object(19461, -2899.892333, -818.523620, 2384.234130, 0.000029, 0.000000, 89.999908, world); // wall1 

			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_floor_begin] = Create:premise_object(19379, -2910.644775, -814.163757, 2382.401367, 0.000000, 90.000007, 0.000000, world); // floor0
			Create:premise_object(19379, -2910.645751, -804.534912, 2382.401367, 0.000000, 90.000007, 0.000000, world); // floor0
			premise_int_obj[index][0][pint_floor_end] = Create:premise_object(19379, -2900.210449, -807.767456, 2382.401367, 0.000000, 90.000007, 0.000000, world); // floor0
			
			// [1]
			premise_int_obj[index][1][pint_floor_end] =
			premise_int_obj[index][1][pint_floor_begin] = Create:premise_object(19379, -2901.832031, -816.686462, 2381.481689, 0.000000, 90.000007, 0.000000, world); // floor1
		}
		
		case 6 : // Паб [1]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_roof_begin] = Create:premise_object(19381, 2896.151367, 806.769775, 2518.889892, 0.000000, 90.000007, 0.000000, world); // roof0
			Create:premise_object(19381, 2885.660400, 809.479736, 2518.889892, 0.000000, 90.000007, 0.000000, world); // roof0
			Create:premise_object(19381, 2885.660400, 799.850463, 2518.889892, 0.000000, 90.000007, 0.000000, world); // roof0
			Create:premise_object(19381, 2875.161621, 809.479736, 2518.889892, 0.000000, 90.000007, 0.000000, world); // roof0
			premise_int_obj[index][0][pint_roof_end] = Create:premise_object(19381, 2875.161621, 799.849914, 2518.889892, 0.000000, 90.000007, 0.000000, world); // roof0
			
			// [1]
			premise_int_obj[index][1][pint_roof_end] =
			premise_int_obj[index][1][pint_roof_begin] = Create:premise_object(19381, 2885.639892, 819.120666, 2518.889892, 0.000000, 90.000007, 0.000000, world); // roof1
			
			// [2]
			premise_int_obj[index][2][pint_roof_end] =
			premise_int_obj[index][2][pint_roof_begin] = Create:premise_object(19381, 2896.290039, 822.829772, 2518.870117, 0.000000, 90.000007, 0.000000, world); // roof2
			
			// [3]
			premise_int_obj[index][3][pint_roof_end] =
			premise_int_obj[index][3][pint_roof_begin] = Create:premise_object(19381, 2896.139892, 816.399780, 2518.889892, 0.000000, 90.000007, 0.000000, world); // roof3

			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_wall_begin] = Create:premise_object(19397, 2882.859130, 814.389648, 2517.080078, 0.000029, 0.000000, 89.999908, world); // wall0
			Create:premise_object(19442, 2890.163574, 814.231140, 2517.081542, 0.000004, 0.000004, 69.999984, world); // wall0
			Create:premise_object(19442, 2885.090332, 814.216613, 2517.081542, 0.000004, -0.000004, 110.000000, world); // wall0
			Create:premise_object(19369, 2889.270751, 814.390502, 2517.080078, 0.000014, 0.000007, 89.999954, world); // wall0
			Create:premise_object(19369, 2886.069824, 814.389770, 2517.080078, 0.000007, 0.000007, 89.999977, world); // wall0
			Create:premise_object(19461, 2876.449462, 811.493408, 2517.080078, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:premise_object(19397, 2892.479980, 811.499816, 2517.080078, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:premise_object(19397, 2887.580078, 803.620971, 2517.080078, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:premise_object(19461, 2894.000000, 803.620971, 2517.080078, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:premise_object(19461, 2881.159912, 803.620971, 2517.080078, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:premise_object(19461, 2878.808837, 807.229980, 2517.080078, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19397, 2882.871093, 811.493408, 2517.080078, 0.000037, 0.000000, 89.999885, world); // wall0
			Create:premise_object(19369, 2890.959960, 813.199768, 2517.080078, 0.000000, 0.000007, 0.000000, world); // wall0
			Create:premise_object(19369, 2884.388427, 813.040832, 2517.080078, 0.000000, 0.000029, 0.000000, world); // wall0
			Create:premise_object(19461, 2881.199951, 816.439697, 2517.080078, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19369, 2895.689941, 811.499816, 2517.080078, 0.000007, 0.000000, 89.999977, world); // wall0
			premise_int_obj[index][0][pint_wall_end] = Create:premise_object(19461, 2897.009033, 806.769775, 2517.080078, 0.000000, 0.000007, 0.000000, world); // wall0
			
			// [1]
			premise_int_obj[index][1][pint_wall_begin] = Create:premise_object(19397, 2882.859130, 814.559692, 2517.080078, 0.000029, 0.000000, 89.999908, world); // wall1
			Create:premise_object(19461, 2881.219970, 819.140075, 2517.080078, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:premise_object(19461, 2886.050048, 821.109680, 2517.072265, 0.000007, 0.000000, 89.999977, world); // wall1
			Create:premise_object(19397, 2890.959960, 819.609802, 2517.080078, 0.000000, 0.000007, 0.000000, world); // wall1
			Create:premise_object(19369, 2890.958007, 816.179565, 2517.080078, 0.000000, 0.000007, 0.000000, world); // wall1
			Create:premise_object(19369, 2890.959960, 816.399780, 2517.080078, 0.000000, 0.000007, 0.000000, world); // wall1
			Create:premise_object(19369, 2889.270751, 814.555297, 2517.080078, 0.000014, 0.000007, 89.999954, world); // wall1
			premise_int_obj[index][1][pint_wall_end] = Create:premise_object(19369, 2886.069824, 814.554809, 2517.080078, 0.000014, 0.000007, 89.999954, world); // wall1
			
			// [2]
			premise_int_obj[index][2][pint_wall_begin] = Create:premise_object(19397, 2891.139892, 819.609802, 2517.080078, 0.000000, 0.000007, 0.000000, world); // wall2
			Create:premise_object(19461, 2891.139892, 826.029785, 2517.080078, 0.000000, 0.000007, 0.000000, world); // wall2
			Create:premise_object(19461, 2894.469970, 825.769775, 2517.080078, 0.000007, 0.000000, 89.999977, world); // wall2
			Create:premise_object(19461, 2898.580078, 822.839782, 2517.080078, 0.000000, 0.000007, 0.000000, world); // wall2
			premise_int_obj[index][2][pint_wall_end] = Create:premise_object(19461, 2895.790039, 818.099792, 2517.080078, 0.000007, 0.000000, 89.999977, world); // wall2
			
			// [3]
			premise_int_obj[index][3][pint_wall_begin] = Create:premise_object(19369, 2895.689941, 811.519836, 2517.080078, 0.000007, 0.000000, 89.999977, world); // wall3
			Create:premise_object(19397, 2894.000000, 813.199768, 2517.080078, 0.000000, 0.000007, 0.000000, world); // wall3
			Create:premise_object(19397, 2892.479980, 811.678833, 2517.080078, 0.000007, 0.000000, 89.999977, world); // wall3
			Create:premise_object(19397, 2894.000000, 816.399780, 2517.080078, 0.000000, 0.000007, 0.000000, world); // wall3
			Create:premise_object(19369, 2891.060058, 816.399780, 2517.080078, 0.000000, 0.000007, 0.000000, world); // wall3
			Create:premise_object(19369, 2891.060058, 813.199768, 2517.080078, 0.000000, 0.000007, 0.000000, world); // wall3
			Create:premise_object(19369, 2895.520019, 814.809814, 2517.080078, 0.000007, 0.000000, 89.999977, world); // wall3
			Create:premise_object(19461, 2897.189941, 813.329772, 2517.080078, 0.000000, 0.000007, 0.000000, world); // wall3
			premise_int_obj[index][3][pint_wall_end] = Create:premise_object(19461, 2895.790039, 817.999816, 2517.080078, 0.000007, 0.000000, 89.999977, world); // wall3

			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_floor_begin] = Create:premise_object(19379, 2875.130859, 800.016662, 2515.239990, 0.000000, 90.000007, 0.000000, world); // floor0
			Create:premise_object(19379, 2885.631103, 800.026000, 2515.239990, 0.000000, 90.000007, 0.000000, world); // floor0
			Create:premise_object(19379, 2896.133300, 809.656250, 2515.239990, 0.000000, 90.000007, 0.000000, world); // floor0
			Create:premise_object(19379, 2896.133300, 800.026550, 2515.239990, 0.000000, 90.000007, 0.000000, world); // floor0
			Create:premise_object(19379, 2875.130859, 809.656250, 2515.239990, 0.000000, 90.000007, 0.000000, world); // floor0
			premise_int_obj[index][0][pint_floor_end] = Create:premise_object(19379, 2885.631103, 809.656250, 2515.239990, 0.000000, 90.000007, 0.000000, world); // floor0
			
			// [1]
			premise_int_obj[index][1][pint_floor_end] =
			premise_int_obj[index][1][pint_floor_begin] = Create:premise_object(19379, 2885.800048, 819.288757, 2515.250000, 0.000000, 90.000007, 0.000000, world); // floor1
			
			// [2]
			premise_int_obj[index][2][pint_floor_end] =
			premise_int_obj[index][2][pint_floor_begin] = Create:premise_object(19379, 2896.290039, 822.829772, 2515.250000, 0.000000, 90.000007, 0.000000, world); // floor2
			
			// [3]
			premise_int_obj[index][3][pint_floor_end] =
			premise_int_obj[index][3][pint_floor_begin] = Create:premise_object(19379, 2896.139892, 816.399780, 2515.240966, 0.000000, 90.000007, 0.000000, world); // floor3
		}
		
		case 7 : // Паб [2]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_roof_begin] = Create:premise_object(19381, 2894.560058, 1307.530029, 2518.889892, 0.000000, 90.000000, 0.000000, world); // roof0
			premise_int_obj[index][0][pint_roof_end] = Create:premise_object(19381, 2884.060058, 1307.530029, 2518.889892, 0.000000, 90.000000, 0.000000, world); // roof0
			
			// [1]
			premise_int_obj[index][1][pint_roof_end] =
			premise_int_obj[index][1][pint_roof_begin] = Create:premise_object(19381, 2894.560058, 1317.160034, 2518.889892, 0.000000, 90.000000, 0.000000, world); // roof1
		
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_wall_begin] = Create:premise_object(19461, 2884.560058, 1312.260009, 2517.080078, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19397, 2883.100097, 1303.340454, 2517.080078, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19461, 2879.840087, 1307.520019, 2517.080078, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, 2876.699951, 1303.340454, 2517.080078, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19461, 2889.520019, 1302.839965, 2517.080078, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19461, 2897.399902, 1312.260009, 2517.080078, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19397, 2890.979980, 1312.260009, 2517.080078, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19461, 2893.989990, 1307.560058, 2517.080078, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, 2887.719970, 1316.775878, 2517.080078, 0.000007, 0.000015, -0.000061, world); // wall0
			Create:premise_object(19442, 2888.450927, 1312.040039, 2517.084960, -0.000015, 0.000007, -90.000038, world); // wall0
			Create:premise_object(19461, 2889.171142, 1316.775878, 2517.080078, 0.000007, 0.000015, -0.000061, world); // wall0
			Create:premise_object(19461, 2882.096679, 1316.775878, 2517.080078, 0.000007, 0.000007, -0.000061, world); // wall0
			Create:premise_object(19442, 2882.827636, 1312.040039, 2517.084960, -0.000007, 0.000007, -90.000061, world); // wall0
			Create:premise_object(19461, 2883.547851, 1316.775878, 2517.080078, 0.000007, 0.000007, -0.000061, world); // wall0
			premise_int_obj[index][0][pint_wall_end] = Create:premise_object(19461, 2888.834960, 1300.948974, 2517.080078, 0.000000, 0.000000, 240.000000, world); // wall0
			
			// [1]
			premise_int_obj[index][1][pint_wall_begin] = Create:premise_object(19461, 2897.399902, 1312.439941, 2517.080078, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:premise_object(19397, 2890.979980, 1312.439941, 2517.080078, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:premise_object(19461, 2889.459960, 1317.229980, 2517.080078, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:premise_object(19461, 2896.931396, 1317.260009, 2517.080078, 0.000000, 0.000000, 0.000000, world); // wall1
			premise_int_obj[index][1][pint_wall_end] = Create:premise_object(19461, 2892.749755, 1316.700195, 2517.080078, 0.000000, 0.000000, 90.000000, world); // wall1
			
			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_floor_begin] = Create:premise_object(19379, 2884.060058, 1307.530029, 2515.237792, 0.000000, 90.000000, 0.000000, world); // floor0
			premise_int_obj[index][0][pint_floor_end] = Create:premise_object(19379, 2894.560058, 1307.530029, 2515.237792, 0.000000, 90.000000, 0.000000, world); // floor0
			
			// [1]
			premise_int_obj[index][1][pint_floor_end] = 
			premise_int_obj[index][1][pint_floor_begin] = Create:premise_object(19379, 2894.560058, 1317.160034, 2515.237792, 0.000000, 90.000000, 0.000000, world); // floor1
		}
		
		case 8 : // Паб [3]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_roof_begin] = Create:premise_object(19381, 2484.060058, 1907.530029, 2518.895263, 0.000000, 90.000000, 0.000000, world); // roof0
			Create:premise_object(19381, 2480.070068, 1917.160034, 2518.895263, 0.000000, 90.000000, 0.000000, world); // roof0
			premise_int_obj[index][0][pint_roof_end] = Create:premise_object(19381, 2480.070068, 1926.790039, 2518.895263, 0.000000, 90.000000, 0.000000, world); // roof0
			
			// [1]
			premise_int_obj[index][1][pint_roof_end] = 
			premise_int_obj[index][1][pint_roof_begin] = Create:premise_object(19381, 2487.300048, 1923.579956, 2518.875244, 0.000000, 90.000000, 0.000000, world); // roof1

			// [2]
			premise_int_obj[index][2][pint_roof_end] = 
			premise_int_obj[index][2][pint_roof_begin] = Create:premise_object(19381, 2490.550048, 1917.160034, 2518.909912, 0.000000, 90.000000, 0.000000, world); // roof2
		
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_wall_begin] = Create:premise_object(19461, 2481.874267, 1907.971923, 2517.065429, 0.000000, 0.000000, 25.000000, world); // wall0
			Create:premise_object(19397, 2485.100097, 1906.619995, 2517.065429, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19461, 2478.679931, 1906.619995, 2517.065429, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19461, 2491.520019, 1906.619995, 2517.065429, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19461, 2488.370117, 1907.550048, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19397, 2486.879882, 1912.300048, 2517.065429, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19369, 2485.350097, 1913.810058, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19369, 2485.350097, 1917.020019, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, 2486.699951, 1918.699951, 2517.065429, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19369, 2481.959960, 1920.219970, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, 2475.099121, 1912.280029, 2517.065429, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19461, 2474.960205, 1917.160034, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19397, 2481.959960, 1926.630004, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19369, 2481.959960, 1923.420043, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, 2474.960205, 1926.790039, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall0
			premise_int_obj[index][0][pint_wall_end] = Create:premise_object(19461, 2478.360107, 1928.270019, 2517.065429, 0.000000, 0.000000, 90.000000, world); // wall0
			
			// [1]
			premise_int_obj[index][1][pint_wall_begin] = Create:premise_object(19397, 2482.139892, 1926.630004, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:premise_object(19369, 2482.139892, 1923.420043, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:premise_object(19461, 2486.929931, 1928.099975, 2517.065429, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:premise_object(19461, 2491.540039, 1923.709960, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:premise_object(19461, 2486.699951, 1918.880004, 2517.065429, 0.000000, 0.000000, 90.000000, world); // wall1
			premise_int_obj[index][1][pint_wall_end] = Create:premise_object(19369, 2482.139892, 1920.219970, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall1
			
			// [2]
			premise_int_obj[index][2][pint_wall_begin] = Create:premise_object(19397, 2488.560058, 1913.810058, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:premise_object(19397, 2488.560058, 1917.020019, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:premise_object(19369, 2490.229980, 1912.300048, 2517.065429, 0.000000, 0.000000, 90.000000, world); // wall2
			Create:premise_object(19369, 2490.229980, 1915.430053, 2517.065429, 0.000000, 0.000000, 90.000000, world); // wall2
			Create:premise_object(19461, 2491.600097, 1915.689941, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:premise_object(19369, 2485.409912, 1914.069946, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:premise_object(19369, 2485.409912, 1917.280029, 2517.065429, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:premise_object(19397, 2486.879882, 1912.380004, 2517.065429, 0.000000, 0.000000, 90.000000, world); // wall2
			premise_int_obj[index][2][pint_wall_end] = Create:premise_object(19461, 2490.250488, 1918.579833, 2517.065429, 0.000000, 0.000000, 90.000000, world); // wall2
		
			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_floor_begin] = Create:premise_object(19379, 2484.060058, 1907.530029, 2515.229980, 0.000000, 90.000000, 0.000000, world); // floor0
			Create:premise_object(19379, 2480.290283, 1917.160034, 2515.229980, 0.000000, 90.000000, 0.000000, world); // floor0
			premise_int_obj[index][0][pint_floor_end] = Create:premise_object(19379, 2476.807128, 1926.790039, 2515.229980, 0.000000, 90.000000, 0.000000, world); // floor0
			
			// [1]
			premise_int_obj[index][1][pint_floor_end] = 
			premise_int_obj[index][1][pint_floor_begin] = Create:premise_object(19379, 2487.300048, 1923.579956, 2515.231201, 0.000000, 90.000000, 0.000000, world); // floor1
			
			// [2]
			premise_int_obj[index][2][pint_floor_end] = 
			premise_int_obj[index][2][pint_floor_begin] = Create:premise_object(19379, 2490.650146, 1917.160400, 2515.230224, 0.000000, 90.000000, 0.000000, world); // floor2
		}
		
		case 9 : // Цокольныный [0]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_roof_begin] = Create:premise_object(19381, 2228.193359, 2526.091064, 2936.780029, 0.000000, 90.000061, 0.000000, world); // roof0
			premise_int_obj[index][0][pint_roof_end] = Create:premise_object(19381, 2229.203369, 2526.091064, 2935.753906, 0.000000, 61.800060, 0.000000, world); // roof0
		
			// [1]
			premise_int_obj[index][1][pint_roof_end] = 
			premise_int_obj[index][1][pint_roof_begin] = Create:premise_object(19381, 2219.411132, 2526.398681, 2933.287353, 0.000000, 90.000000, 0.000000, world); // roof1
			
			// [2]
			premise_int_obj[index][2][pint_roof_end] = 
			premise_int_obj[index][2][pint_roof_begin] = Create:premise_object(19381, 2212.218017, 2527.519775, 2933.267333, 0.000000, 90.000000, 0.000000, world); // roof2
			
			// [3]
			premise_int_obj[index][3][pint_roof_end] = 
			premise_int_obj[index][3][pint_roof_begin] = Create:premise_object(19381, 2212.218017, 2535.884765, 2933.247314, 0.000000, 90.000000, 0.000000, world); // roof3
		
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_wall_begin] = Create:premise_object(19461, 2229.300292, 2528.452148, 2931.468994, -0.000060, 0.000000, -90.000823, world); // wall0
			Create:premise_object(19461, 2229.300292, 2528.452148, 2934.968017, -0.000060, 0.000000, -90.000823, world); // wall0
			Create:premise_object(19461, 2229.308349, 2530.969970, 2934.968994, 0.000060, 0.000000, 89.998817, world); // wall0
			Create:premise_object(19397, 2233.468505, 2529.667968, 2934.968994, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, 2229.300292, 2530.959960, 2931.468994, -0.000060, 0.000000, -90.000823, world); // wall0
			premise_int_obj[index][0][pint_wall_end] = Create:premise_object(19397, 2224.624267, 2529.675537, 2931.469726, 0.000000, 0.000000, 0.000000, world); // wall0
			
			// [1]
			premise_int_obj[index][1][pint_wall_begin] = Create:premise_object(19461, 2222.176025, 2530.979980, 2931.468994, -0.000060, 0.000000, -90.000823, world); // wall1
			Create:premise_object(19461, 2224.447509, 2523.258544, 2931.468994, -0.000060, 0.000000, -0.000822, world); // wall1
			Create:premise_object(19397, 2217.590576, 2524.562255, 2931.469726, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:premise_object(19461, 2222.315673, 2521.837402, 2931.468994, -0.000060, 0.000000, 89.999176, world); // wall1
			Create:premise_object(19397, 2224.446044, 2529.676513, 2931.469726, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:premise_object(19461, 2217.591552, 2530.979980, 2931.468994, -0.000060, 0.000000, -0.000822, world); // wall1
			premise_int_obj[index][1][pint_wall_end] = Create:premise_object(19461, 2217.585205, 2518.127197, 2931.468994, -0.000060, 0.000000, 179.999176, world); // wall1

			// [2]
			premise_int_obj[index][2][pint_wall_begin] = Create:premise_object(19461, 2217.441406, 2530.979980, 2931.468994, -0.000060, 0.000000, -0.000822, world); // wall2
			Create:premise_object(19397, 2217.414306, 2524.566162, 2931.469726, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:premise_object(19461, 2212.637695, 2522.916503, 2931.468994, -0.000060, 0.000000, 89.999176, world); // wall2
			Create:premise_object(19461, 2207.783447, 2527.668212, 2931.468994, -0.000060, 0.000000, 179.999176, world); // wall2
			Create:premise_object(19461, 2215.860839, 2530.991455, 2931.468994, -0.000060, 0.000000, 269.999176, world); // wall2
			premise_int_obj[index][2][pint_wall_end] = Create:premise_object(19397, 2209.454345, 2530.995849, 2931.469726, 0.000000, 0.000000, 90.000000, world); // wall2
			
			// [3]
			premise_int_obj[index][3][pint_wall_begin] = Create:premise_object(19397, 2209.451416, 2531.171630, 2931.469726, 0.000000, 0.000000, 90.000000, world); // wall3
			Create:premise_object(19461, 2213.287597, 2535.842773, 2931.468994, -0.000060, 0.000000, -0.000822, world); // wall3
			Create:premise_object(19461, 2211.625976, 2534.391357, 2931.468994, -0.000060, 0.000000, 89.999176, world); // wall3
			Create:premise_object(19461, 2207.843017, 2535.842773, 2931.468994, -0.000060, 0.000000, 179.999176, world); // wall3
			premise_int_obj[index][3][pint_wall_end] = Create:premise_object(19461, 2215.860839, 2531.172851, 2931.468994, -0.000060, 0.000000, 269.999176, world); // wall3
			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_floor_end] = 
			premise_int_obj[index][0][pint_floor_begin] = Create:premise_object(19379, 2229.724853, 2526.155029, 2929.642089, 0.000000, 90.000061, 0.000000, world); // floor0

			// [1]
			premise_int_obj[index][1][pint_floor_begin] = Create:premise_object(19379, 2222.728271, 2526.155029, 2929.638183, 0.000000, 90.000061, 0.000000, world); // floor1
			premise_int_obj[index][1][pint_floor_end] = Create:premise_object(19379, 2222.728271, 2516.525146, 2929.638183, 0.000000, 90.000061, 0.000000, world); // floor1
			
			// [2]
			premise_int_obj[index][2][pint_floor_end] = 
			premise_int_obj[index][2][pint_floor_begin] = Create:premise_object(19379, 2212.244873, 2526.155029, 2929.642089, 0.000000, 90.000061, 0.000000, world); // floor2
			
			// [3]
			premise_int_obj[index][3][pint_floor_end] = 
			premise_int_obj[index][3][pint_floor_begin] = Create:premise_object(19379, 2212.244873, 2535.748046, 2929.645996, 0.000000, 90.000061, 0.000000, world); // floor3
		}
		
		case 10 : // Клуб [0]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_roof_end] = 
			premise_int_obj[index][0][pint_roof_begin] = Create:premise_object(19381, -2784.734130, -514.124023, 1886.044433, 0.000000, 90.000000, 0.000000, world); // roof0
			
			// [1]
			premise_int_obj[index][1][pint_roof_begin] = Create:premise_object(19381, -2774.165283, -514.124023, 1886.044433, 0.000000, 90.000000, 0.000000, world); // roof1
			Create:premise_object(19381, -2763.665283, -514.124023, 1886.044433, 0.000000, 90.000000, 0.000000, world); // roof1
			Create:premise_object(19381, -2768.997070, -523.753601, 1891.215087, 0.000000, 180.000000, 0.000000, world); // roof1
			Create:premise_object(19381, -2766.116699, -518.853637, 1891.215087, 0.000000, 180.000000, 90.000000, world); // roof1
			Create:premise_object(19381, -2766.116699, -527.343322, 1891.215087, 0.000000, 180.000000, 90.000000, world); // roof1
			Create:premise_object(19381, -2761.736572, -523.753601, 1891.215087, 0.000000, 180.000000, 0.000000, world); // roof1
			Create:premise_object(19381, -2763.665283, -532.092773, 1886.044433, 0.000000, 90.000000, 0.000000, world); // roof1
			Create:premise_object(19381, -2774.163085, -523.753601, 1886.044433, 0.000000, 90.000000, 0.000000, world); // roof1
			premise_int_obj[index][1][pint_roof_end] = Create:premise_object(19381, -2774.166259, -533.383605, 1886.044433, 0.000000, 90.000000, 0.000000, world); // roof1
	
			// [2]
			premise_int_obj[index][2][pint_roof_end] = 
			premise_int_obj[index][2][pint_roof_begin] = Create:premise_object(19381, -2763.665283, -523.753601, 1886.324707, 0.000000, 90.000000, 0.000000, world); // roof2
			
			// [3]
			premise_int_obj[index][3][pint_roof_end] = 
			premise_int_obj[index][3][pint_roof_begin] = Create:premise_object(19381, -2784.832519, -523.753601, 1886.044433, 0.000000, 90.000000, 0.000000, world); // roof3
			
			// [4]
			premise_int_obj[index][4][pint_roof_end] = 
			premise_int_obj[index][4][pint_roof_begin] = Create:premise_object(19381, -2781.549804, -532.113342, 1886.043457, 0.000000, 90.000000, 0.000000, world); // roof4
			
			// [5]
			premise_int_obj[index][5][pint_roof_end] = 
			premise_int_obj[index][5][pint_roof_begin] = Create:premise_object(19381, -2775.116210, -535.323486, 1886.043457, 0.000000, 90.000000, 0.000000, world); // roof5

			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_wall_begin] = Create:premise_object(19397, -2784.059326, -514.946716, 1884.236816, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, -2784.390380, -518.987121, 1884.236328, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:premise_object(19461, -2784.059570, -508.528564, 1884.236328, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:premise_object(19461, -2779.595703, -510.968688, 1884.236328, 0.000000, 0.000014, 0.000000, world); // wall0
			Create:premise_object(19397, -2779.596191, -517.391113, 1884.236816, 0.000000, 0.000014, 0.000000, world); // wall0
			Create:premise_object(19461, -2784.059570, -521.368225, 1884.236328, 0.000000, 0.000000, 0.000000, world); // wall0 - x
			premise_int_obj[index][0][pint_wall_end] = Create:premise_object(19461, -2784.440185, -513.196838, 1884.236328, 0.000014, 0.000000, 89.999954, world); // wall0
			
			// [1]
			premise_int_obj[index][1][pint_wall_begin] = Create:premise_object(19461, -2779.417480, -510.968688, 1884.236328, 0.000000, 0.000022, 0.000000, world); // wall1
			Create:premise_object(19397, -2779.417968, -517.391113, 1884.236816, 0.000000, 0.000022, 0.000000, world); // wall1
			Create:premise_object(19369, -2779.418945, -520.602050, 1884.238525, 0.000000, 0.000007, 0.000000, world); // wall1
			Create:premise_object(19397, -2779.418945, -523.813293, 1884.238769, 0.000000, 0.000022, 0.000000, world); // wall1
			Create:premise_object(19442, -2779.418457, -526.222106, 1884.236816, 0.000000, 0.000007, 0.000000, world); // wall1
			Create:premise_object(19397, -2777.794433, -527.092041, 1884.236816, 0.000007, 0.000014, 89.999977, world); // wall1
			Create:premise_object(19369, -2777.737304, -514.801208, 1884.238525, 0.000000, 0.000007, 90.000000, world); // wall1
			Create:premise_object(19369, -2776.055664, -516.402343, 1884.238525, 0.000000, 0.000007, 180.000000, world); // wall1
			Create:premise_object(19369, -2774.361328, -517.918457, 1884.238525, 0.000000, 0.000007, 90.000000, world); // wall1
			Create:premise_object(19369, -2771.150878, -517.918457, 1884.238525, 0.000000, 0.000007, 90.000000, world); // wall1
			Create:premise_object(19369, -2769.462646, -516.402343, 1884.238525, 0.000000, 0.000007, 180.000000, world); // wall1
			Create:premise_object(19461, -2766.199462, -515.717834, 1884.236328, 0.000014, 0.000000, 89.999954, world); // wall1
			Create:premise_object(19461, -2774.612304, -530.571899, 1884.236328, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:premise_object(19397, -2769.884521, -532.266296, 1884.238769, 0.000000, 0.000022, 0.000000, world); // wall1
			Create:premise_object(19461, -2763.378173, -515.988098, 1884.236328, 0.000014, 0.000000, 179.999954, world); // wall1
			Create:premise_object(19461, -2764.981933, -535.112548, 1884.238281, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:premise_object(19461, -2769.884521, -538.689392, 1884.238281, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:premise_object(19461, -2763.378173, -530.218017, 1884.236328, 0.000014, 0.000000, 179.999954, world); // wall1
			Create:premise_object(19461, -2776.218505, -529.369689, 1884.239257, 0.000000, 0.000000, 0.000000, world); // wall1
			premise_int_obj[index][1][pint_wall_end] = Create:premise_object(19461, -2763.378173, -523.768676, 1887.737060, 0.000014, 180.000000, 179.999954, world); // wall1
			
			// [2]
			premise_int_obj[index][2][pint_wall_begin] = Create:premise_object(19461, -2758.505859, -518.377380, 1884.236328, 0.000014, 0.000000, 269.999938, world); // wall2
			Create:premise_object(19461, -2758.505859, -528.087097, 1884.236328, 0.000014, 0.000000, 269.999938, world); // wall2
			Create:premise_object(19461, -2766.199462, -517.898681, 1881.394775, 0.000014, 0.000000, 89.999954, world); // wall2
			Create:premise_object(19369, -2772.559082, -526.182739, 1881.397949, 180.000000, 180.000000, 180.000000, world); // wall2
			Create:premise_object(19369, -2772.559082, -529.393676, 1881.397949, 180.000000, 180.000000, 180.000000, world); // wall2
			Create:premise_object(19369, -2774.180664, -524.664550, 1881.397949, 180.000000, 180.000000, 270.000000, world); // wall2
			Create:premise_object(19369, -2774.581054, -524.665527, 1881.396972, 180.000000, 180.000000, 270.000000, world); // wall2
			premise_int_obj[index][2][pint_wall_end] = Create:premise_object(19461, -2761.707519, -523.208190, 1884.236328, 0.000014, 0.000000, 179.999954, world); // wall2
			
			// [3]
			premise_int_obj[index][3][pint_wall_begin] = Create:premise_object(19369, -2779.597167, -520.603027, 1884.238525, 0.000000, 0.000000, 0.000000, world); // wall3
			Create:premise_object(19397, -2779.597167, -523.813293, 1884.238769, 0.000000, 0.000014, 0.000000, world); // wall3
			Create:premise_object(19442, -2779.596679, -526.222106, 1884.236816, 0.000000, 0.000000, 0.000000, world); // wall3
			Create:premise_object(19461, -2784.029541, -523.728820, 1884.236328, 0.000000, 0.000000, 0.000000, world); // wall3
			Create:premise_object(19461, -2784.390380, -518.997741, 1884.236328, 0.000000, 0.000000, 90.000000, world); // wall3
			premise_int_obj[index][3][pint_wall_end] = Create:premise_object(19461, -2784.390380, -527.079895, 1884.236328, 0.000000, 0.000000, 90.000000, world); // wall3
			
			// [4]
			premise_int_obj[index][4][pint_wall_begin] = Create:premise_object(19461, -2776.278564, -532.028320, 1884.239257, 0.000000, 0.000000, 0.000000, world); // wall4
			Create:premise_object(19461, -2784.217285, -527.269104, 1884.236328, 0.000007, 0.000000, 89.999977, world); // wall4
			Create:premise_object(19461, -2784.009521, -532.158325, 1884.236328, 0.000000, 0.000000, 0.000000, world); // wall4
			Create:premise_object(19461, -2781.156250, -530.551757, 1884.236328, 0.000000, 0.000000, 90.000000, world); // wall4
			premise_int_obj[index][4][pint_wall_end] = Create:premise_object(19397, -2777.794433, -527.269287, 1884.236816, 0.000007, 0.000014, 89.999977, world); // wall4
			
			// [5]
			premise_int_obj[index][5][pint_wall_begin] = Create:premise_object(19461, -2774.782470, -530.942260, 1884.236328, 0.000000, 0.000000, 90.000000, world); // wall5
			Create:premise_object(19397, -2770.062255, -532.266296, 1884.238769, 0.000000, 0.000022, 0.000000, world); // wall5
			Create:premise_object(19461, -2774.612304, -535.112548, 1884.238281, 0.000000, 0.000000, 90.000000, world); // wall5
			Create:premise_object(19461, -2776.178466, -535.459960, 1884.236328, 0.000000, 0.000000, 0.000000, world); // wall5
			premise_int_obj[index][5][pint_wall_end] = Create:premise_object(19461, -2770.062744, -538.689392, 1884.238281, 0.000000, 0.000000, 0.000000, world); // wall5
			
			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			premise_int_obj[index][0][pint_floor_end] = 
			premise_int_obj[index][0][pint_floor_begin] = Create:premise_object(19379, -2784.802490, -514.163757, 1882.401367, 0.000000, 90.000000, 0.000000, world); // floor0
	
			// [1]
			premise_int_obj[index][1][pint_floor_begin] = Create:premise_object(19379, -2774.287353, -522.413635, 1882.401367, 0.000000, 90.000000, 0.000000, world); // floor1
			Create:premise_object(19379, -2774.287353, -512.785095, 1882.401367, 0.000000, 90.000000, 0.000000, world); // floor1
			Create:premise_object(19379, -2763.788330, -522.413635, 1882.401367, 0.000000, 90.000000, 0.000000, world); // floor1
			Create:premise_object(19379, -2774.287109, -532.043395, 1882.381367, 0.000000, 90.000000, 0.000000, world); // floor1
			premise_int_obj[index][1][pint_floor_end] = Create:premise_object(19379, -2763.788330, -532.043395, 1882.401367, 0.000000, 90.000000, 0.000000, world); // floor1
			
			// [2]
			premise_int_obj[index][2][pint_object_material] = 1;
			premise_int_obj[index][2][pint_object_type] = _: pint_floor_begin;
			premise_int_obj[index][2][pint_floor_begin] = Create:premise_object(13649, -2763.232177, -522.960388, 1882.544433, 0.000000, 0.000000, 0.000000, world); // floor2
			SetDynamicObjectMaterial(premise_int_obj[index][2][pint_floor_begin], 0, 14789, "ab_sfgymmain", "ab_wood02", 0xFFFFFFFF);
			
			Create:premise_object(19461, -2761.607421, -523.268249, 1883.055175, 0.000014, 270.000000, 179.999954, world); // floor2
			Create:premise_object(19369, -2774.380859, -526.182739, 1883.057373, 0.000000, 90.000000, 180.000000, world); // floor2
			Create:premise_object(19369, -2774.380859, -529.392517, 1883.057373, 0.000000, 90.000000, 180.000000, world); // floor2
			premise_int_obj[index][2][pint_floor_end] = Create:premise_object(19461, -2765.159179, -516.057983, 1883.055175, 0.000014, 270.000000, 269.999938, world); // floor2
			
			// [3]
			premise_int_obj[index][3][pint_floor_end] = 
			premise_int_obj[index][3][pint_floor_begin] = Create:premise_object(19379, -2784.782470, -523.863525, 1882.401367, 0.000000, 90.000000, 0.000000, world); // floor3
			
			// [4]
			premise_int_obj[index][4][pint_floor_end] = 
			premise_int_obj[index][4][pint_floor_begin] = Create:premise_object(19379, -2781.449218, -531.992065, 1882.402343, 0.000000, 90.000000, 0.000000, world); // floor4

			// [5]
			premise_int_obj[index][5][pint_floor_end] =
			premise_int_obj[index][5][pint_floor_begin] = Create:premise_object(19379, -2775.223144, -535.303527, 1882.401367, 0.000000, 90.000000, 0.000000, world); // floor5
		}
	}
}

IsPremiseObject(objectid, premiseid)
{
	new type,
		worldid;
	
	type = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID);
	worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_WORLD_ID);

	return (type == TYPE_REN_PREMISE && premiseid == worldid);
}

Destroy:premise_int_obj(index)
{
	new room = GetPremiseSettings(index, pset_rooms),
		premiseid = GetPremiseId(index);
	
	for (new i; i < room; i++)
	{
		for (new j = premise_int_obj[index][i][pint_roof_begin]; j <= premise_int_obj[index][i][pint_roof_end]; j++)
		{
			if (IsValidDynamicObject(j) && IsPremiseObject(j, premiseid))
			{
				DestroyDynamicObject(j);
			}
		}
		
		for (new j = premise_int_obj[index][i][pint_wall_begin]; j <= premise_int_obj[index][i][pint_wall_end]; j++)
		{
			if (IsValidDynamicObject(j) && IsPremiseObject(j, premiseid))
			{
				DestroyDynamicObject(j);
			}
		}
		
		for (new j = premise_int_obj[index][i][pint_floor_begin]; j <= premise_int_obj[index][i][pint_floor_end]; j++)
		{
			if (IsValidDynamicObject(j) && IsPremiseObject(j, premiseid))
			{
				DestroyDynamicObject(j);
			}
		}
	}
}

PremiseInteriorStaticObjects()
{
	new tmpobjid;
	
	// 1 - Магазин - [1]
	CreateObject(19545, 1718.930908, 1147.206787, 2467.458984, 0.000000, 0.000000, 90.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19353, 1707.399047, 1145.779174, 2469.228027, 0.000000, 0.000000, 0.000000, -1, INT_PREMISE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 2 - Магазин - [2]
	CreateObject(19545, 2019.910888, 1223.638671, 2460.975097, 0.000000, 0.000000, 90.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19353, 2018.715332, 1223.412841, 2462.140869, 0.000000, 0.000000, 0.000000, -1, INT_PREMISE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 3 - Минимаркет - [1]
	CreateObject(19545, -3075.531982, -1194.675781, 2409.001708, 0.000000, 0.000000, 90.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19353, -3068.721679, -1194.749267, 2410.397949, 0.000000, 0.000000, 0.000000, -1, INT_PREMISE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 4 - Минимаркет - [2]
	CreateObject(19545, -2995.115234, -1183.693481, 2403.544189, 0.000000, 0.000000, 0.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19353, -3002.694580, -1196.490112, 2405.239013, 0.000000, 0.000000, 0.000000, -1, INT_PREMISE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 5 - Минимаркет - [3]
	CreateObject(19545, -2912.843261, -825.314270, 2382.358154, 0.000000, 0.000000, 0.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19353, -2913.286621, -814.943725, 2384.213378,0.000000, 0.000000, 0.000000, -1, INT_PREMISE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	tmpobjid = CreateDynamicObject(14407, -2905.017578, -814.756896, 2379.305664, 0.000000, 0.000000, 180.000000, -1, INT_PREMISE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0xFFFFFFFF); // Ступеньки
	
	// 6 - Паб - [1]
	CreateObject(19538, 2867.432861, 805.459167, 2515.245849, 0.000000, 0.000000, 0.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19353, 2887.580078, 803.460937, 2517.060058,0.000007, 0.000000, 89.999977, -1, INT_PREMISE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 7 - Паб - [2]
	CreateObject(19538, 2908.767578, 1324.548706, 2515.265869, 0.000000, 0.000000, 0.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19353, 2883.100097, 1303.210693, 2517.050048, 0.000000, 0.000000, 90.000000, -1, INT_PREMISE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 8 - Паб - [3]
	CreateObject(19538, 2466.965087, 1926.223510, 2515.276123, 0.000000, 0.000000, 0.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19353, 2484.780029, 1906.479980, 2517.065429, 0.000000, 0.000000, 90.000000, -1, INT_PREMISE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 9 - Цокольный - [0]
	CreateObject(19538, 2227.069091, 2548.148437, 2929.677734, 0.000000, 0.000000, 90.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19353, 2233.494140, 2530.325927, 2934.167724, 0.000000, 0.000000, 0.000000, -1, INT_PREMISE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);

	tmpobjid = CreateObject(14877, 2230.963623, 2529.653320, 2931.140869, 0.000000, 0.000060, 0.000000, 300.00); // Лестница
	SetObjectMaterial(tmpobjid, 0, 4833, "airprtrunway_las", "greyground256", 0xFFFFFFFF);
	SetObjectMaterial(tmpobjid, 1, 4833, "airprtrunway_las", "greyground256", 0x00000000);
	SetObjectMaterial(tmpobjid, 2, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0x00000000);
	
	// 10 - Клуб - [0]
	CreateObject(19538, -2783.770507, -529.926635, 1882.380371, 0.000000, 0.000000, 0.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19353, -2784.222900, -514.943725, 1883.551757, 0.000000, 0.000000, 0.000000, -1, INT_PREMISE, -1, 300.00, 300.00); // blackwall
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(1319, -2768.769775, -518.263671, 1882.667968, 45.000000, 180.000000, 180.000000, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	SetDynamicObjectMaterial(tmpobjid, 0, 14789, "ab_sfgymmain", "ab_wood02", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(1319, -2764.112304, -520.541870, 1882.667968, 44.999992, 180.000122, 18.499853, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	SetDynamicObjectMaterial(tmpobjid, 0, 14789, "ab_sfgymmain", "ab_wood02", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(1319, -2772.180908, -526.045166, 1882.667968, 44.999908, 179.999984, -89.899810, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	SetDynamicObjectMaterial(tmpobjid, 0, 14789, "ab_sfgymmain", "ab_wood02", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(1319, -2772.180908, -529.495300, 1882.667968, 44.999900, 179.999984, -89.899787, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	SetDynamicObjectMaterial(tmpobjid, 0, 14789, "ab_sfgymmain", "ab_wood02", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(1319, -2764.065185, -525.385742, 1882.667968, 44.999992, 180.000137, 151.199905, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	SetDynamicObjectMaterial(tmpobjid, 0, 14789, "ab_sfgymmain", "ab_wood02", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19939, -2763.998291, -525.308898, 1883.055419, -0.000063, 0.000015, 61.200107, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	tmpobjid = CreateDynamicObject(19939, -2764.075683, -525.449279, 1882.885253, -0.000063, 0.000015, 61.200107, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	tmpobjid = CreateDynamicObject(19939, -2764.162109, -525.607299, 1882.725097, -0.000063, 0.000015, 61.200107, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	tmpobjid = CreateDynamicObject(19939, -2768.748291, -518.164123, 1883.055419, 0.000000, 0.000000, 90.000000, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	tmpobjid = CreateDynamicObject(19939, -2768.748291, -518.324279, 1882.885253, 0.000000, 0.000000, 90.000000, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	tmpobjid = CreateDynamicObject(19939, -2768.748291, -518.504394, 1882.725097, 0.000000, 0.000000, 90.000000, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	tmpobjid = CreateDynamicObject(19939, -2764.101318, -520.643188, 1883.055419, -0.000057, 0.000012, -71.499969, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	tmpobjid = CreateDynamicObject(19939, -2764.152099, -520.491271, 1882.885253, -0.000057, 0.000012, -71.499969, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	tmpobjid = CreateDynamicObject(19939, -2764.209472, -520.320434, 1882.725097, -0.000057, 0.000012, -71.499969, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	tmpobjid = CreateDynamicObject(19939, -2772.280761, -526.023864, 1883.055419, 0.000007, -0.000068, -179.899597, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	tmpobjid = CreateDynamicObject(19939, -2772.120361, -526.023620, 1882.885253, 0.000007, -0.000068, -179.899597, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	tmpobjid = CreateDynamicObject(19939, -2771.940185, -526.023254, 1882.725097, 0.000007, -0.000068, -179.899597, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	tmpobjid = CreateDynamicObject(19939, -2772.280761, -529.473999, 1883.055419, 0.000007, -0.000075, -179.899551, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	tmpobjid = CreateDynamicObject(19939, -2772.120361, -529.473754, 1882.885253, 0.000007, -0.000075, -179.899551, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
	tmpobjid = CreateDynamicObject(19939, -2771.940185, -529.473388, 1882.725097, 0.000007, -0.000075, -179.899551, -1, INT_PREMISE, -1, 300.00, 300.00); // stairs
}

PremiseInteriorText3D()
{
	for (new i = 1; i < sizeof premise_settings; i++)
	{
		CreateDynamic3DTextLabel(
			"Выход", 
			-1, 
			premise_settings[i][pset_pos][0], 
			premise_settings[i][pset_pos][1], 
			premise_settings[i][pset_pos][2] - 0.2, 
			TEXT3D_DRAW_DISTANCE, 
			_, 
			_, 
			_, 
			_,
			INT_PREMISE,
			_, 
			TEXT3D_DRAW_DISTANCE
		);
	}
}

SetPremiseInteriorMaterial(index, room, E_PREMISE_INTERIOR: enum_item_1, E_PREMISE_INTERIOR: enum_item_2, texture_type, texture)
{
	new model,
		txd_name				[	34	],
		texture_name			[	34 	],
		premiseid = GetPremiseId(index);
	
	GetTextureByType(texture_type, texture, model, txd_name, texture_name);
	
	for (new i = premise_int_obj[index][room][enum_item_1]; i <= premise_int_obj[index][room][enum_item_2]; i++)
	{	
		if (IsPremiseObject(i, premiseid))
		{
			SetDynamicObjectMaterial(i, 
				0, 
				model, 
				txd_name, 
				texture_name, 
				0
			);
		}
	}
}

