/*!
	@brief Интерьеры для системы домов
	@author Found (evg.savosin)
	@date 16.12.2016, update 21.03.2018
*/

Create:house_object(modelid, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz, worldid = -1)
{
	new objectid = CreateDynamicObject(modelid, x, y, z, rx, ry, rz, worldid, INT_HOUSE);
	
	Streamer_SetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID, TYPE_REN_HOUSE);
	
	return objectid;
}

Create:house_int_obj(index, interiorid)
{
	new world = house_data[index][h_id];
		
	switch(interiorid)
	{
		case 1 : // Студия [1]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_roof_begin] = Create:house_object(19379, -2715.014404, -1508.109497, 2604.557617, 0.000000, 90.000007, 0.000000, world); // roof1
			house_int_obj[index][0][hint_roof_end] = Create:house_object(19379, -2718.515136, -1517.742797, 2604.557617, 0.000000, 90.000007, 0.000000, world); // roof1
			
			// [1]
			house_int_obj[index][1][hint_roof_end] =
			house_int_obj[index][1][hint_roof_begin] = Create:house_object(19379, -2708.016357, -1517.742797, 2604.557617, 0.000000, 90.000007, 0.000000, world); // roof2
			
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_wall_begin] = Create:house_object(19397, -2718.628173, -1513.911743, 2602.781738, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:house_object(19369, -2718.628417, -1517.122680, 2602.781494, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:house_object(19461, -2718.125732, -1518.632812, 2602.781250, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19369, -2713.363281, -1519.402709, 2602.781494, 0.000000, 0.000014, 0.000000, world); // wall 1
			Create:house_object(19442, -2713.362060, -1513.783325, 2602.781250, 0.000000, 0.000014, 0.000000, world); // wall1
			Create:house_object(19461, -2713.724609, -1506.023144, 2602.781250, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19461, -2718.629150, -1507.523559, 2602.781250, 0.000000, 0.000000, 180.000000, world); // wall1
			Create:house_object(19461, -2709.768066, -1508.083984, 2602.781250, 0.000000, 0.000000, 180.000000, world); // wall1
			Create:house_object(19397, -2713.363281, -1516.191650, 2602.781250, 0.000000, 0.000014, 0.000000, world);  // wall1
			house_int_obj[index][0][hint_wall_end] = Create:house_object(19461, -2708.633789, -1512.901123, 2602.781250, 0.000000, 0.000000, 90.000000, world); // wall1
			
			// [1]
			house_int_obj[index][1][hint_wall_begin] = Create:house_object(19442, -2713.185058, -1513.783325, 2602.781250, 0.000000, 0.000014, 0.000000, world); // wall2
			Create:house_object(19397, -2713.185058, -1516.191650, 2602.781250, 0.000000, 0.000014, 0.000000, world); // wall2
			Create:house_object(19369, -2713.185302, -1519.402709, 2602.781494, 0.000000, 0.000014, 0.000000, world); // wall2
			Create:house_object(19369, -2711.500976, -1518.643676, 2602.781494, 0.000014, 0.000000, 89.999954, world); // wall2
			Create:house_object(19369, -2711.490966, -1513.169677, 2602.781494, 0.000014, 0.000000, 89.999954, world); // wall2
			house_int_obj[index][1][hint_wall_end] = Create:house_object(19461, -2709.812744, -1517.897460, 2602.781250, 0.000000, -0.000014, 179.999908, world); // wall2
			
			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_floor_begin] = Create:house_object(19379, -2715.014404, -1508.109497, 2600.966308, 0.000000, 90.000015, 0.000000, world); // floor1
			house_int_obj[index][0][hint_floor_end] = Create:house_object(19379, -2718.515136, -1517.742797, 2600.966308, 0.000000, 90.000015, 0.000000, world); // floor1
			
			// [1]
			house_int_obj[index][1][hint_floor_end] =
			house_int_obj[index][1][hint_floor_begin] = Create:house_object(19379, -2708.016357, -1517.742797, 2600.966308, 0.000000, 90.000015, 0.000000, world); // floor2
		}
		
		case 2 : // Студия [2]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_roof_begin] = Create:house_object(19379, -2420.007080, -1181.272949, 2611.651123, 0.000000, 90.000007, 0.000000, world); // roof0
			house_int_obj[index][0][hint_roof_end] = Create:house_object(19379, -2416.514648, -1171.643066, 2611.651123, 0.000000, 90.000007, 0.000000, world); // roof0

			// [1]
			house_int_obj[index][1][hint_roof_end] = 
			house_int_obj[index][1][hint_roof_begin] = Create:house_object(19379, -2409.506591, -1181.272949, 2611.651123, 0.000000, 90.000007, 0.000000, world); // roof1
			
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_wall_begin] = Create:house_object(19461, -2421.549072, -1168.496948, 2609.856689, -0.022998, 0.000000, 180.002990, world); // wall0
			Create:house_object(19461, -2411.928466, -1168.433471, 2609.855468, -0.022998, 0.000000, 180.002990, world); // wall0
			Create:house_object(19397, -2411.933349, -1174.852294, 2609.852050, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2416.809570, -1171.353759, 2609.855468, -0.022998, 0.000000, 90.002998, world); // wall0
			Create:house_object(19461, -2411.915039, -1176.544799, 2609.855468, -0.022998, 0.000000, 90.002998, world); // wall0
			Create:house_object(19461, -2416.716552, -1182.625366, 2609.855468, -0.022998, 0.000000, 90.002998, world); // wall0
			Create:house_object(19461, -2421.549072, -1178.115966, 2609.854003, -0.022998, 0.000000, 180.002990, world); // wall0
			Create:house_object(19461, -2414.843261, -1184.628295, 2609.854003, -0.022998, 0.000000, 180.002990, world); // wall0
			house_int_obj[index][0][hint_wall_end] = Create:house_object(19397, -2414.843750, -1178.232788, 2609.857910, 0.000000, 0.000000, 0.000000, world); // wall0
			
			// [1]
			house_int_obj[index][1][hint_wall_begin] = Create:house_object(19461, -2409.833496, -1176.564819, 2609.855468, -0.022998, 0.000000, 90.002998, world); // wall1
			Create:house_object(19461, -2409.833496, -1182.605346, 2609.855468, -0.022998, 0.000000, 90.002998, world); // wall1
			Create:house_object(19461, -2414.665039, -1184.628295, 2609.854003, -0.022998, 0.000000, 180.002990, world); // wall1
			Create:house_object(19397, -2414.665527, -1178.232788, 2609.857910, 0.000000, 0.000000, 0.000000, world); // wall1
			house_int_obj[index][1][hint_wall_end] = Create:house_object(19461, -2411.958740, -1181.396362, 2609.854003, -0.022998, 0.000000, 180.002990, world); // wall1

			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_floor_begin] = Create:house_object(19379, -2420.007080, -1181.272949, 2608.027587, 0.000000, 90.000000, 0.000000, world); // floor0
			house_int_obj[index][0][hint_floor_end] = Create:house_object(19379, -2416.514648, -1171.643066, 2608.027587, 0.000000, 90.000000, 0.000000, world); // floor0
			
			// [1]
			house_int_obj[index][1][hint_floor_end] =
			house_int_obj[index][1][hint_floor_begin] = Create:house_object(19379, -2409.506591, -1181.272949, 2608.027587, 0.000000, 90.000000, 0.000000, world); // floor1
		}
		
		case 3 : // Студия [3]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_roof_begin] = Create:house_object(19379, -2461.317871, -752.526550, 2613.909667, 0.000000, 90.000007, 0.000000, world); // roof0
			Create:house_object(19379, -2471.810302, -755.744628, 2613.909667, 0.000000, 90.000007, 0.000000, world); // roof0
			house_int_obj[index][0][hint_roof_end] = Create:house_object(19379, -2461.317871, -742.896850, 2613.909667, 0.000000, 90.000007, 0.000000, world); // roof0
			
			// [1]
			house_int_obj[index][1][hint_roof_end] = 
			house_int_obj[index][1][hint_roof_begin] = Create:house_object(19379, -2471.810302, -746.114440, 2613.909667, 0.000000, 90.000007, 0.000000, world); // roof1

			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_wall_begin] = Create:house_object(19397, -2463.189941, -747.957275, 2612.072753, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19369, -2461.504394, -749.473449, 2612.073242, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2459.813476, -753.837341, 2612.072509, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2464.713378, -755.937011, 2612.072509, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2469.594726, -751.047241, 2612.072509, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2466.446044, -746.278076, 2612.072509, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19397, -2468.130859, -751.008117, 2612.072753, 0.000000, 0.000000, 90.000000, world); // wall0
			house_int_obj[index][0][hint_wall_end] = Create:house_object(19461, -2461.543701, -746.287109, 2612.072509, 0.000000, 0.000000, 90.000000, world); // wall0

			// [1]
			house_int_obj[index][1][hint_wall_begin] = Create:house_object(19461, -2468.024169, -746.267089, 2612.072509, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19461, -2466.616210, -746.087890, 2612.072509, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:house_object(19397, -2468.130859, -750.837951, 2612.072753, 0.000000, 0.000000, 90.000000, world); // wall1
			house_int_obj[index][1][hint_wall_end] = Create:house_object(19461, -2469.584716, -746.047424, 2612.072509, 0.000000, 0.000000, 0.000000, world); // wall1
			
			/*
				
				@brief Floor - Пол
				
			*/

			// [0]
			house_int_obj[index][0][hint_floor_begin] = Create:house_object(19379, -2461.317871, -752.526550, 2610.236083, 0.000000, 90.000000, 0.000000, world); // floor0
			Create:house_object(19379, -2471.810302, -755.744628, 2610.236083, 0.000000, 90.000000, 0.000000, world); // floor0
			house_int_obj[index][0][hint_floor_end] = Create:house_object(19379, -2461.317871, -742.896850, 2610.236083, 0.000000, 90.000000, 0.000000, world); // floor0
			
			// [1]
			house_int_obj[index][1][hint_floor_end] = 
			house_int_obj[index][1][hint_floor_begin] = Create:house_object(19379, -2471.810302, -746.114440, 2610.236083, 0.000000, 90.000000, 0.000000, world); // floor1
		}
		
		case 4 : // 1 комната [1]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_roof_end] = 
			house_int_obj[index][0][hint_roof_begin] = Create:house_object(19381, -2606.739990, 647.419982, 2569.560058, 0.000000, 90.000000, 0.000000, world); // roof0
			
			// [1]
			house_int_obj[index][1][hint_roof_end] = 
			house_int_obj[index][1][hint_roof_begin] = Create:house_object(19381, -2606.739990, 637.789978, 2569.560058, 0.000000, 90.000000, 0.000000, world); // roof1
			
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_wall_begin] = Create:house_object(19397, -2601.590087, 647.419982, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2601.590087, 653.840026, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2601.590087, 641.000000, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19397, -2603.280029, 642.690002, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2609.699951, 642.690002, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2611.310058, 647.419982, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2606.489990, 652.299987, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall0
			house_int_obj[index][0][hint_wall_end] = Create:house_object(19461, -2607.389892, 651.219970, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall0
			
			// [1]
			house_int_obj[index][1][hint_wall_begin] = Create:house_object(19461, -2609.702636, 642.510559, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19397, -2603.280029, 642.510009, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19461, -2601.659912, 637.630004, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:house_object(19461, -2606.479980, 638.149902, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall1
			house_int_obj[index][1][hint_wall_end] = Create:house_object(19461, -2606.761474, 637.750000, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall1
			
			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_floor_end] = 
			house_int_obj[index][0][hint_floor_begin] = Create:house_object(19379, -2606.739990, 647.419982, 2565.919921, 0.000000, 90.000000, 0.000000, world); // floor0
			
			// [1]
			house_int_obj[index][1][hint_floor_end] = 
			house_int_obj[index][1][hint_floor_begin] = Create:house_object(19379, -2606.739990, 637.789978, 2565.919921, 0.000000, 90.000000, 0.000000, world); // floor1
		}
		
		case 5 : // 1 комната [2]
		{

			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_roof_end] = 
			house_int_obj[index][0][hint_roof_begin] = Create:house_object(19381, -2616.447021, 1147.439941, 2569.489990, 0.000000, 90.000000, 0.000000, world); // roof0
			
			// [1]
			house_int_obj[index][1][hint_roof_end] = 
			house_int_obj[index][1][hint_roof_begin] = Create:house_object(19381, -2620.199951, 1157.069946, 2569.419921, 0.000000, 90.000000, 0.000000, world); // roof1
			
			// [2]
			house_int_obj[index][2][hint_roof_end] = 
			house_int_obj[index][2][hint_roof_begin] = Create:house_object(19381, -2626.886718, 1147.439941, 2569.489990, 0.000000, 90.000000, 0.000000, world); // roof2
			
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_wall_begin] = Create:house_object(19397, -2615.040039, 1149.030029, 2567.669921, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19442, -2615.040039, 1151.429931, 2567.669921, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2615.040039, 1142.619995, 2567.669921, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19397, -2616.729980, 1152.160034, 2567.669921, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2616.867919, 1146.341430, 2567.669921, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2621.600097, 1141.609985, 2567.669921, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2623.149902, 1152.160034, 2567.669921, 0.000000, 0.000000, 90.000000, world); // wall0 - 1
			house_int_obj[index][0][hint_wall_end] = Create:house_object(19461, -2621.600097, 1155.439697, 2567.669921, 0.000000, 0.000000, 0.000000, world); // wall0
			
			// [1]
			house_int_obj[index][1][hint_wall_begin] = Create:house_object(19397, -2616.729980, 1152.329956, 2567.669921, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19461, -2615.060058, 1157.170043, 2567.669921, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:house_object(19461, -2618.399902, 1157.199951, 2567.669921, 0.000000, 0.000000, 0.000000, world); // wall1
			house_int_obj[index][1][hint_wall_end] = Create:house_object(19461, -2619.790039, 1156.140014, 2567.669921, 0.000000, 0.000000, 90.000000, world); // wall1
			
			// [2]
			house_int_obj[index][2][hint_wall_begin] = Create:house_object(19461, -2626.449902, 1151.750034, 2567.669921, 0.000000, 0.000000, 90.000000, world); // wall2 - 1
			Create:house_object(19461, -2625.530029, 1147.449951, 2567.669921, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:house_object(19461, -2625.798583, 1145.120361, 2567.669921, 0.000000, 0.000000, 90.000000, world); // wall2
			house_int_obj[index][2][hint_wall_end] = Create:house_object(19461, -2621.780273, 1155.439697, 2567.669921, 0.000000, 0.000000, 0.000000, world); // wall2
			
			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_floor_end] = 
			house_int_obj[index][0][hint_floor_begin] = Create:house_object(19379, -2616.437255, 1147.439941, 2565.860107, 0.000000, 90.000000, 0.000000, world); // floor0

			// [1]
			house_int_obj[index][1][hint_floor_end] = 
			house_int_obj[index][1][hint_floor_begin] = Create:house_object(19379, -2620.199951, 1157.069946, 2565.860107, 0.000000, 90.000000, 0.000000, world); // floor1

			// [2]
			house_int_obj[index][2][hint_floor_end] = 
			house_int_obj[index][2][hint_floor_begin] = Create:house_object(19379, -2626.930175, 1147.439941, 2565.860107, 0.000000, 90.000000, 0.000000, world); // floor2
			
		}
		
		case 6 : // 1 комната [3]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_roof_end] = 
			house_int_obj[index][0][hint_roof_begin] = Create:house_object(19379, -2247.990478, -1033.053955, 2616.286865, 0.000000, 90.000007, 0.000000, world); // roof0
			
			// [1]
			house_int_obj[index][1][hint_roof_end] = 
			house_int_obj[index][1][hint_roof_begin] = Create:house_object(19379, -2247.995605, -1042.688110, 2616.286865, 0.000000, 90.000007, 0.000000, world); // roof1
			
			// [2]
			house_int_obj[index][2][hint_roof_end] = 
			house_int_obj[index][2][hint_roof_begin] = Create:house_object(19379, -2237.488769, -1040.288330, 2616.286865, 0.000000, 90.000007, 0.000000, world); // roof2

			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_wall_begin] = Create:house_object(19397, -2249.399169, -1036.097900, 2614.511474, 0.000000, 0.000007, 0.000000, world); // wall0
			Create:house_object(19461, -2252.373046, -1037.782836, 2614.511230, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19397, -2245.949707, -1037.782958, 2614.511474, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19442, -2243.541503, -1037.782836, 2614.511230, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2242.827880, -1030.516967, 2614.511230, 0.000000, 0.000000, 180.000000, world); // wall0
			Create:house_object(19397, -2242.827392, -1036.931274, 2614.511474, 0.000000, 0.000000, 180.000000, world); // wall0
			Create:house_object(19461, -2244.720214, -1030.828051, 2614.511230, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19369, -2249.399169, -1032.932495, 2614.510498, 0.000000, -0.000014, 179.999908, world); // wall0
			house_int_obj[index][0][hint_wall_end] = Create:house_object(19369, -2249.399169, -1029.721069, 2614.510498, 0.000000, -0.000014, 179.999908, world); // wall0
			
			// [1]
			house_int_obj[index][1][hint_wall_begin] = Create:house_object(19461, -2247.639160, -1042.801269, 2614.511230, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:house_object(19461, -2247.732177, -1042.748413, 2614.511230, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19461, -2242.837402, -1042.689208, 2614.511230, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:house_object(19442, -2243.543457, -1037.953002, 2614.511230, 0.000000, 0.000000, 90.000000, world); // wall1
			house_int_obj[index][1][hint_wall_end] = Create:house_object(19397, -2245.949707, -1037.960937, 2614.511474, 0.000000, 0.000000, 90.000000, world); // wall1
			
			// [2]
			house_int_obj[index][2][hint_wall_begin] = Create:house_object(19461, -2237.741943, -1035.413696, 2614.511230, 0.000000, 0.000000, 90.000000, world); // wall2
			Create:house_object(19461, -2235.150634, -1040.289062, 2614.511230, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:house_object(19397, -2242.650146, -1036.931030, 2614.511474, 0.000000, 0.000000, 180.000000, world); // wall2
			Create:house_object(19461, -2237.741943, -1042.001953, 2614.511230, 0.000000, 0.000000, 90.000000, world); // wall2
			Create:house_object(19369, -2242.396484, -1037.788085, 2614.510498, 0.000000, 0.000000, 90.000000, world); // wall2
			Create:house_object(19461, -2240.709716, -1042.514404, 2614.510253, 0.000000, 0.000000, 0.000000, world); // wall2
			house_int_obj[index][2][hint_wall_end] = Create:house_object(19461, -2233.551025, -1038.818359, 2614.511230, 0.000000, 0.000000, 45.000000, world); // wall2

			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_floor_end] = 
			house_int_obj[index][0][hint_floor_begin] = Create:house_object(19379, -2247.990478, -1033.053955, 2612.674072, 0.000000, 90.000000, 0.000000, world); // floor0
			
			// [1]
			house_int_obj[index][1][hint_floor_end] = 
			house_int_obj[index][1][hint_floor_begin] = Create:house_object(19379, -2247.995605, -1042.688110, 2612.674072, 0.000000, 90.000000, 0.000000, world); // floor1
			
			// [2]
			house_int_obj[index][2][hint_floor_end] = 
			house_int_obj[index][2][hint_floor_begin] = Create:house_object(19379, -2237.488769, -1040.288330, 2612.674072, 0.000000, 90.000000, 0.000000, world); // floor2
		}
		
		case 7 : // 2 комната [1]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_roof_end] = 
			house_int_obj[index][0][hint_roof_begin] = Create:house_object(19381, -2586.060058, 38.659999, 2569.580078, 0.000000, 90.000000, 0.000000, world); // roof0
			
			// [1]
			house_int_obj[index][1][hint_roof_end] = 
			house_int_obj[index][1][hint_roof_begin] = Create:house_object(19381, -2580.540039, 48.290000, 2569.580078, 0.000000, 90.000000, 0.000000, world); // roof1

			// [2]
			house_int_obj[index][2][hint_roof_end] = 
			house_int_obj[index][2][hint_roof_begin] = Create:house_object(19381, -2591.050048, 48.290000, 2569.580078, 0.000000, 90.000000, 0.000000, world); // roof2
			
			// [3]
			house_int_obj[index][3][hint_roof_end] = 
			house_int_obj[index][3][hint_roof_begin] = Create:house_object(19381, -2596.560058, 38.659999, 2569.580078, 0.000000, 90.000000, 0.000000, world); // roof3
			
			// [4]
			house_int_obj[index][4][hint_roof_end] = 
			house_int_obj[index][4][hint_roof_begin] = Create:house_object(19381, -2586.060058, 35.179985, 2569.577148, 0.000000, 90.000000, 0.000000, world); // roof4

			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_wall_begin] = Create:house_object(19461, -2582.408447, 40.229995, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19397, -2580.889892, 41.880001, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19397, -2591.219970, 41.869998, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19397, -2582.439941, 43.389999, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19369, -2585.639892, 43.389999, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19397, -2588.819091, 43.389999, 2567.750000, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:house_object(19461, -2595.242187, 43.388996, 2567.748046, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19442, -2591.227783, 40.229995, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall0
			house_int_obj[index][0][hint_wall_end] = Create:house_object(19397, -2588.819091, 40.230056, 2567.750000, 0.000015, 0.000000, 89.999954, world); // wall0
			
			// [1]
			house_int_obj[index][1][hint_wall_begin] = Create:house_object(19397, -2582.439941, 43.569999, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19461, -2576.020019, 43.569999, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19461, -2578.432617, 48.279998, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:house_object(19461, -2584.129882, 48.400001, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall1
			house_int_obj[index][1][hint_wall_end] = Create:house_object(19461, -2580.010009, 50.330181, 2567.750000, 0.000015, 0.000000, 89.999954, world); // wall1
			
			// [2]
			house_int_obj[index][2][hint_wall_begin] = Create:house_object(19397, -2588.819091, 43.569999, 2567.750000, 0.000007, 0.000000, 89.999977, world); // wall2
			Create:house_object(19461, -2584.728759, 48.319999, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:house_object(19461, -2589.608886, 50.280181, 2567.750000, 0.000015, 0.000000, 89.999954, world); // wall2
			Create:house_object(19369, -2585.639892, 43.570014, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall2
			Create:house_object(19461, -2593.988525, 48.359958, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall2
			house_int_obj[index][2][hint_wall_end] = Create:house_object(19461, -2595.239257, 43.569999, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall2
			
			// [3]
			house_int_obj[index][3][hint_wall_begin] = Create:house_object(19397, -2591.399902, 41.869998, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall3
			Create:house_object(19461, -2596.229980, 40.380001, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall3
			Create:house_object(19461, -2596.229980, 43.329998, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall3
			Create:house_object(19461, -2594.029052, 38.689987, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall3
			house_int_obj[index][3][hint_wall_end] = Create:house_object(19381, -2596.560058, 38.659999, 2569.580078, 0.000000, 90.000000, 0.000000, world); // wall3
			
			// [4]
			house_int_obj[index][4][hint_wall_begin] = Create:house_object(19397, -2588.819091, 40.050056, 2567.750000, 0.000015, 0.000000, 89.999954, world); // wall4
			Create:house_object(19461, -2582.408447, 40.050006, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall4
			Create:house_object(19461, -2590.475585, 35.209953, 2567.750000, 0.000000, 0.000000, 0.000000, world); // wall4
			Create:house_object(19461, -2586.055908, 37.279930, 2567.750000, 0.000000, 0.000000, 90.000000, world); // wall4
			house_int_obj[index][4][hint_wall_end] = Create:house_object(19461, -2581.266601, 35.159931, 2567.750000, 0.000000, 0.000000, 180.000000, world); // wall4
			
			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_floor_end] = 
			house_int_obj[index][0][hint_floor_begin] = Create:house_object(19379, -2586.060058, 38.659999, 2565.919921, 0.000000, 90.000000, 0.000000, world); // floor0
			
			// [1]
			house_int_obj[index][1][hint_floor_end] = 
			house_int_obj[index][1][hint_floor_begin] = Create:house_object(19379, -2579.549072, 48.290000, 2565.919921, 0.000000, 90.000000, 0.000000, world); // floor1
			
			// [2]
			house_int_obj[index][2][hint_floor_end] = 
			house_int_obj[index][2][hint_floor_begin] = Create:house_object(19379, -2590.059082, 48.290000, 2565.919921, 0.000000, 90.000000, 0.000000, world); // floor2
			
			// [3]
			house_int_obj[index][3][hint_floor_end] = 
			house_int_obj[index][3][hint_floor_begin] = Create:house_object(19379, -2596.560058, 38.659999, 2565.919921, 0.000000, 90.000000, 0.000000, world); // floor3
			
			// [4]
			house_int_obj[index][4][hint_floor_end] = 
			house_int_obj[index][4][hint_floor_begin] = Create:house_object(19379, -2586.060058, 35.329975, 2565.922851, 0.000000, 90.000000, 0.000000, world); // floor4
		}
		
		case 8 : // 2 комнаты [2]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_roof_begin] = Create:house_object(19379, -2215.090820, -654.406372, 2613.941650, 0.000000, 90.000007, 0.000000, world); // roof0
			Create:house_object(19379, -2212.640136, -648.336120, 2613.942626, 0.000000, 90.000007, 0.000000, world); // roof0
			house_int_obj[index][0][hint_roof_end] = Create:house_object(19379, -2225.590576, -654.406372, 2613.941650, 0.000000, 90.000007, 0.000000, world); // roof0
			
			// [1]
			house_int_obj[index][1][hint_roof_end] = 
			house_int_obj[index][1][hint_roof_begin] = Create:house_object(19379, -2223.286865, -646.702331, 2613.883789, 0.000000, 90.000000, 17.200004, world); // roof1
			
			// [2]
			house_int_obj[index][2][hint_roof_end] = 
			house_int_obj[index][2][hint_roof_begin] = Create:house_object(19379, -2212.308837, -659.984497, 2613.940673, 0.000000, 90.000022, 0.000000, world); // roof2
			
			// [3]
			house_int_obj[index][3][hint_roof_end] = 
			house_int_obj[index][3][hint_roof_begin] = Create:house_object(19379, -2222.968017, -659.984497, 2613.940673, 0.000000, 90.000022, 0.000000, world); // roof3
			
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_wall_begin] = Create:house_object(19397, -2209.905273, -652.857360, 2612.106445, 0.000000, 0.000007, 0.000000, world); // wall0
			Create:house_object(19461, -2218.232666, -645.162597, 2612.105957, 0.000007, 0.000000, -162.400085, world); // wall0
			Create:house_object(19461, -2213.014404, -646.338378, 2612.105957, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:house_object(19397, -2218.385253, -650.237304, 2612.106445, 0.000022, 0.000000, 109.999938, world); // wall0
			Create:house_object(19461, -2224.881347, -649.596252, 2612.105957, 0.000007, 0.000000, 179.999969, world); // wall0
			Create:house_object(19461, -2209.905517, -646.436950, 2612.105957, 0.000000, -0.000007, 179.999954, world); // wall0
			Create:house_object(19461, -2224.052490, -653.192871, 2612.105957, 0.000007, 0.000000, 660.000000, world); // wall0
			Create:house_object(19369, -2209.904296, -656.068298, 2612.106445, 0.000000, 0.000007, 0.000000, world); // wall0
			Create:house_object(19461, -2209.609375, -655.085021, 2612.105957, 0.000029, 0.000000, 89.999908, world); // wall0
			Create:house_object(19461, -2225.663574, -655.085021, 2612.105957, 0.000029, 0.000000, 89.999908, world); // wall0
			Create:house_object(19397, -2219.243652, -655.085754, 2612.106445, 0.000014, 0.000007, 89.999954, world); // wall0
			Create:house_object(19369, -2224.881591, -655.961120, 2612.106445, 0.000000, 0.000007, 0.000000, world); // wall1
			house_int_obj[index][0][hint_wall_end] = Create:house_object(19397, -2216.032470, -655.085754, 2612.106445, 0.000014, 0.000007, 89.999954, world); // wall0
			
			// [1]
			house_int_obj[index][1][hint_wall_begin] = Create:house_object(19461, -2218.320556, -645.148925, 2612.105957, 0.000007, 0.000000, -162.400085, world); // wall1
			Create:house_object(19461, -2220.437011, -646.206115, 2612.105957, 0.000007, 0.000000, 179.999969, world); // wall1
			Create:house_object(19397, -2218.439941, -650.086914, 2612.106445, 0.000022, 0.000000, 109.999938, world); // wall1
			Create:house_object(19461, -2222.588867, -646.328613, 2612.105957, 0.000000, 0.000000, -90.000007, world); // wall1
			house_int_obj[index][1][hint_wall_end] = Create:house_object(19461, -2224.105957, -653.039184, 2612.105957, 0.000007, 0.000000, 660.000000, world); // wall1
			
			// [2]
			house_int_obj[index][2][hint_wall_begin] = Create:house_object(19461, -2210.477783, -659.986022, 2612.105957, 0.000014, -0.000014, 179.999862, world); // wall2
			Create:house_object(19461, -2212.728027, -661.676757, 2612.105957, 0.000000, 0.000000, -90.000015, world); // wall2
			Create:house_object(19397, -2216.032470, -655.264770, 2612.106445, 0.000014, 0.000007, 89.999954, world); // wall2
			Create:house_object(19461, -2209.609375, -655.265014, 2612.105957, 0.000029, 0.000000, 89.999908, world); // wall2
			house_int_obj[index][2][hint_wall_end] = Create:house_object(19461, -2217.627441, -659.986022, 2612.105957, 0.000014, -0.000014, 179.999862, world); // wall2

			// [3]
			house_int_obj[index][3][hint_wall_begin] = Create:house_object(19461, -2217.758056, -659.986022, 2612.105957, 0.000014, -0.000014, 179.999862, world); // wall3
			Create:house_object(19461, -2224.802490, -659.986022, 2612.105957, 0.000014, -0.000014, 179.999862, world); // wall3
			Create:house_object(19461, -2222.537597, -663.266662, 2612.105957, 0.000000, 0.000000, -90.000015, world); // wall3
			Create:house_object(19397, -2219.243652, -655.264770, 2612.106445, 0.000014, 0.000007, 89.999954, world); // wall3
			house_int_obj[index][3][hint_wall_end] = Create:house_object(19461, -2225.663574, -655.264038, 2612.105957, 0.000029, 0.000000, 89.999908, world); // wall3
			
			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_floor_begin] = Create:house_object(19379, -2213.510253, -648.336120, 2610.267089, 0.000000, 90.000000, 0.000000, world); // floor0
			Create:house_object(19379, -2225.590576, -654.406372, 2610.268066, 0.000000, 90.000000, 0.000000, world); // floor0
			house_int_obj[index][0][hint_floor_end] = Create:house_object(19379, -2215.090820, -654.406372, 2610.268066, 0.000000, 90.000000, 0.000000, world); // floor0

			// [1]
			house_int_obj[index][1][hint_floor_end] = 
			house_int_obj[index][1][hint_floor_begin] = Create:house_object(19379, -2223.286865, -646.702331, 2610.270996, 0.000000, 90.000000, 17.200004, world); // floor1
			
			// [2]
			house_int_obj[index][2][hint_floor_end] = 
			house_int_obj[index][2][hint_floor_begin] = Create:house_object(19379, -2212.308837, -659.984497, 2610.269042, 0.000000, 90.000015, 0.000000, world); // floor2
			
			// [3]
			house_int_obj[index][3][hint_floor_end] = 
			house_int_obj[index][3][hint_floor_begin] = Create:house_object(19379, -2222.968017, -659.984497, 2610.269042, 0.000000, 90.000015, 0.000000, world); // floor3
		}
		
		case 9 : // 3 комнаты [1]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_roof_begin] = Create:house_object(19379, -1771.407836, -658.643066, 2588.395019, 0.000000, 90.000007, 0.000000, world); // roof0
			house_int_obj[index][0][hint_roof_end] = Create:house_object(19379, -1771.407836, -649.023498, 2588.395019, 0.000000, 90.000007, 0.000000, world); // roof0
			
			// [1]
			house_int_obj[index][1][hint_roof_end] = 
			house_int_obj[index][1][hint_roof_begin] = Create:house_object(19379, -1768.029541, -652.573181, 2588.394042, 0.000000, 90.000007, 0.000000, world); // roof1
			
			// [2]
			house_int_obj[index][2][hint_roof_end] = 
			house_int_obj[index][2][hint_roof_begin] = Create:house_object(19379, -1781.998779, -656.313781, 2588.395996, 0.000000, 90.000007, 0.000000, world); // roof2
			
			// [3]
			house_int_obj[index][3][hint_roof_end] = 
			house_int_obj[index][3][hint_roof_begin] = Create:house_object(19379, -1781.908081, -646.683044, 2588.396972, 0.000000, 90.000007, 0.000000, world); // roof3
			
			// [4]
			house_int_obj[index][4][hint_roof_end] = 
			house_int_obj[index][4][hint_roof_begin] = Create:house_object(19379, -1776.948852, -639.389221, 2588.395996, 0.000000, 90.000007, 0.000000, world); // roof4
			
			// [5]
			house_int_obj[index][5][hint_roof_end] = 
			house_int_obj[index][5][hint_roof_begin] = Create:house_object(19379, -1787.258178, -639.273376, 2588.395019, 0.000000, 90.000007, 0.000000, world); // roof5
			
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_wall_begin] = Create:house_object(19397, -1768.846069, -645.985168, 2586.583984, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -1773.369140, -655.794433, 2586.583984, 0.000000, -0.000007, 179.999954, world); // wall0
			Create:house_object(19461, -1768.639404, -647.677917, 2586.583984, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:house_object(19461, -1768.639404, -644.289184, 2586.583984, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:house_object(19397, -1773.368041, -649.371582, 2586.583984, 0.000000, 0.000007, 0.000000, world); // wall0
			Create:house_object(19397, -1776.568969, -653.031982, 2586.583984, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -1771.769897, -655.914123, 2586.583984, 0.000000, -0.000007, 269.999938, world); // wall0
			Create:house_object(19461, -1776.571533, -659.443908, 2586.583984, 0.000000, -0.000007, 359.999938, world); // wall0
			Create:house_object(19397, -1776.568969, -649.822021, 2586.583984, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19369, -1776.569213, -646.610839, 2586.584472, 0.000000, 0.000000, 180.000000, world); // wall0
			house_int_obj[index][0][hint_wall_end] = Create:house_object(19442, -1776.569702, -644.830017, 2586.584960, 0.000000, 0.000000, 0.000000, world); // wall0
			
			// [1]
			house_int_obj[index][1][hint_wall_begin] = Create:house_object(19461, -1768.352905, -657.205383, 2586.583984, 0.000009, -0.000009, 135.000000, world); // wall1
			Create:house_object(19461, -1768.589355, -655.847778, 2586.583984, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19461, -1764.922241, -652.835693, 2586.583984, 0.000000, -0.000014, 179.999908, world); // wall1
			Create:house_object(19461, -1763.698974, -650.912048, 2586.583984, -0.000009, -0.000009, -135.000000, world); // wall1
			Create:house_object(19397, -1773.188964, -649.371582, 2586.583984, 0.000000, 0.000007, 0.000000, world); // wall1
			Create:house_object(19461, -1773.190063, -655.794433, 2586.583984, 0.000000, -0.000007, 179.999954, world); // wall1
			house_int_obj[index][1][hint_wall_end] = Create:house_object(19461, -1768.519287, -647.768981, 2586.583984, 0.000007, 0.000000, 89.999977, world); // wall1
			
			// [2]
			house_int_obj[index][2][hint_wall_begin] = Create:house_object(19461, -1775.469726, -656.974853, 2586.583984, 0.000000, -0.000007, 269.999938, world); // wall2
			Create:house_object(19397, -1776.748046, -653.031982, 2586.583984, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:house_object(19461, -1776.741699, -659.443908, 2586.583984, 0.000000, -0.000007, 359.999938, world); // wall2
			Create:house_object(19461, -1779.917602, -656.317077, 2586.583984, 0.000000, 0.000000, 180.000000, world); // wall2
			house_int_obj[index][2][hint_wall_end] = Create:house_object(19461, -1781.479125, -651.408081, 2586.583984, 0.000000, 0.000000, 90.000000, world); // wall2
			
			// [3]
			house_int_obj[index][3][hint_wall_begin] = Create:house_object(19461, -1781.479125, -651.407104, 2586.583984, 0.000000, 0.000000, 90.000000, world); // wall3
			Create:house_object(19397, -1776.748046, -649.822021, 2586.583984, 0.000000, 0.000000, 0.000000, world); // wall3
			Create:house_object(19369, -1776.748413, -646.610839, 2586.584472, 0.000000, -0.000029, 179.999816, world); // wall3
			Create:house_object(19442, -1776.748901, -644.830017, 2586.584960, 0.000000, 0.000029, 0.000000, world); // wall3
			Create:house_object(19461, -1781.439086, -644.118347, 2586.583984, 0.000000, 0.000000, 90.000000, world); // wall3
			house_int_obj[index][3][hint_wall_end] = Create:house_object(19461, -1784.129760, -648.980407, 2586.583984, 0.000000, 0.000000, 180.000000, world); // wall3
			
			// [4]
			house_int_obj[index][4][hint_wall_begin] = Create:house_object(19461, -1773.367187, -639.394592, 2586.583984, 0.000000, -0.000007, 179.999954, world); // wall4
			Create:house_object(19461, -1769.516113, -637.704956, 2586.583984, 0.000000, 0.000000, 270.000000, world); // wall4
			Create:house_object(19461, -1779.150634, -637.704956, 2586.583984, 0.000000, 0.000000, 270.000000, world); // wall4
			Create:house_object(19461, -1782.119506, -635.994628, 2586.583984, 0.000000, 0.000000, 180.000000, world); // wall4
			Create:house_object(19397, -1782.117919, -642.421569, 2586.583984, 0.000000, 0.000000, 0.000000, world); // wall4
			house_int_obj[index][4][hint_wall_end] = Create:house_object(19461, -1781.298950, -644.097351, 2586.583984, 0.000000, 0.000000, 90.000000, world); // wall4
			
			// [5]
			house_int_obj[index][5][hint_wall_begin] = Create:house_object(19461, -1787.030395, -637.705932, 2586.583984, 0.000000, 0.000000, 270.000000, world); // wall5
			Create:house_object(19461, -1788.591430, -640.106140, 2586.583984, 0.000000, 0.000000, 360.000000, world); // wall5
			Create:house_object(19461, -1787.019531, -644.086364, 2586.583984, 0.000000, 0.000000, 90.000000, world); // wall5
			Create:house_object(19397, -1782.296997, -642.421569, 2586.583984, 0.000000, 0.000000, 0.000000, world); // wall5
			house_int_obj[index][5][hint_wall_end] = Create:house_object(19461, -1782.298583, -635.994628, 2586.583984, 0.000000, 0.000000, 180.000000, world); // wall5
			
			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_floor_begin] = Create:house_object(19379, -1771.407836, -649.023498, 2584.761474, 0.000000, 90.000000, 0.000000, world); // floor0
			house_int_obj[index][0][hint_floor_end] = Create:house_object(19379, -1771.407836, -658.653564, 2584.761474, 0.000000, 90.000000, 0.000000, world); // floor0
			
			// [1]
			house_int_obj[index][1][hint_floor_end] = 
			house_int_obj[index][1][hint_floor_begin] = Create:house_object(19379, -1768.029541, -652.573181, 2584.762451, 0.000000, 90.000000, 0.000000, world); // floor1
			
			// [2]
			house_int_obj[index][2][hint_floor_end] = 
			house_int_obj[index][2][hint_floor_begin] = Create:house_object(19379, -1781.887084, -656.313781, 2584.760498, 0.000000, 90.000000, 0.000000, world); // floor2
			
			// [3]
			house_int_obj[index][3][hint_floor_end] = 
			house_int_obj[index][3][hint_floor_begin] = Create:house_object(19379, -1781.908081, -646.683044, 2584.760498, 0.000000, 90.000000, 0.000000, world); // floor3
			
			// [4]
			house_int_obj[index][4][hint_floor_end] = 
			house_int_obj[index][4][hint_floor_begin] = Create:house_object(19379, -1776.948852, -639.389221, 2584.762451, 0.000000, 90.000000, 0.000000, world); // floor4
			
			// [5]
			house_int_obj[index][5][hint_floor_end] = 
			house_int_obj[index][5][hint_floor_begin] = Create:house_object(19379, -1787.258178, -639.273376, 2584.761474, 0.000000, 90.000000, 0.000000, world); // floor5
		}
		
		case 10 : // 4 комнаты 2 этажа [1]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_roof_begin] = Create:house_object(19381, -1076.100097, 1649.449951, 2569.409912, 0.000000, 90.000000, 0.000000, world); // roof0
			house_int_obj[index][0][hint_roof_end] = Create:house_object(19381, -1065.600097, 1655.659912, 2569.409912, 0.000000, 90.000000, 0.000000, world); // roof0
			
			// [1]
			house_int_obj[index][1][hint_roof_end] = 
			house_int_obj[index][1][hint_roof_begin] = Create:house_object(19381, -1068.709960, 1646.030029, 2569.409912, 0.000000, 90.000000, 0.000000, world); // roof1
			
			// [2]
			house_int_obj[index][2][hint_roof_end] = 
			house_int_obj[index][2][hint_roof_begin] = Create:house_object(19381, -1068.709960, 1665.290039, 2569.409912, 0.000000, 90.000000, 0.000000, world); // roof2
			
			// [3]
			house_int_obj[index][3][hint_roof_end] = 
			house_int_obj[index][3][hint_roof_begin] = Create:house_object(19381, -1079.330322, 1665.290039, 2569.409912, 0.000000, 90.000000, 0.000000, world); // roof3
			
			// [4]
			house_int_obj[index][4][hint_roof_begin] = Create:house_object(19381, -1068.709960, 1665.109985, 2573.050048, 0.000000, 90.000000, 0.000000, world); // roof4
			house_int_obj[index][4][hint_roof_end] = Create:house_object(19381, -1068.169921, 1655.479980, 2573.050048, 0.000000, 90.000000, 0.000000, world); // roof4
			
			// [5]
			house_int_obj[index][5][hint_roof_end] = 
			house_int_obj[index][5][hint_roof_begin] = Create:house_object(19381, -1062.550048, 1660.739990, 2573.030029, 0.000000, 90.000000, 0.000000, world); // roof5
			
			// [7]
			house_int_obj[index][6][hint_roof_end] = 
			house_int_obj[index][6][hint_roof_begin] = Create:house_object(19381, -1068.709960, 1645.849975, 2573.050048, 0.000000, 90.000000, 0.000000, world); // roof6
			
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_wall_begin] = Create:house_object(19397, -1063.550048, 1655.489990, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19397, -1066.729980, 1650.939941, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19397, -1066.729980, 1660.380004, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -1063.550048, 1649.070068, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -1063.550048, 1661.909912, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -1060.310058, 1660.380004, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -1073.149902, 1660.380004, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -1073.159912, 1650.939941, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -1060.310058, 1650.939941, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -1073.360107, 1655.659912, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall0
			house_int_obj[index][0][hint_wall_end] = Create:house_object(19461, -1070.939941, 1657.320068, 2565.330078, 35.000000, 0.000000, 0.000000, world); // wall0
			
			// [1]
			house_int_obj[index][1][hint_wall_begin] = Create:house_object(19397, -1066.729980, 1650.760009, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19461, -1060.310058, 1650.760009, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19461, -1073.159912, 1650.760009, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19461, -1063.619873, 1645.909912, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:house_object(19461, -1068.489746, 1642.340087, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall1
			house_int_obj[index][1][hint_wall_end] = Create:house_object(19461, -1070.909912, 1645.870117, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall1
			
			// [2]
			house_int_obj[index][2][hint_wall_begin] = Create:house_object(19369, -1070.820068, 1662.070068, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:house_object(19461, -1069.139892, 1668.219970, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall2
			Create:house_object(19369, -1072.340087, 1663.590087, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall2
			Create:house_object(19397, -1066.729980, 1660.560058, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall2
			Create:house_object(19461, -1073.149902, 1660.560058, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall2
			Create:house_object(19461, -1060.310058, 1660.560058, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall2
			Create:house_object(19461, -1064.280029, 1665.469970, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:house_object(19397, -1073.870117, 1666.570068, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall2
			house_int_obj[index][2][hint_wall_end] = Create:house_object(19461, -1073.870117, 1660.150024, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall2
			
			// [3]
			house_int_obj[index][3][hint_wall_begin] = Create:house_object(19397, -1074.050048, 1666.570068, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall3
			Create:house_object(19461, -1074.050048, 1660.150024, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall3
			Create:house_object(19461, -1078.429931, 1668.260009, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall3
			Create:house_object(19461, -1078.949951, 1660.709960, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall3
			house_int_obj[index][3][hint_wall_end] = Create:house_object(19461, -1077.807983, 1663.760009, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall3
			
			// [4]
			house_int_obj[index][4][hint_wall_begin] = Create:house_object(19461, -1073.360107, 1655.550048, 2571.229980, 0.000000, 0.000000, 0.000000, world); // wall4
			Create:house_object(19461, -1073.159912, 1650.939941, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall4
			Create:house_object(19397, -1066.729980, 1650.939941, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall4
			Create:house_object(19461, -1060.310058, 1650.939941, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall4
			Create:house_object(19461, -1067.820068, 1660.560058, 2571.229980, 0.000000, 0.000000, 0.000000, world); // wall4
			Create:house_object(19461, -1064.580078, 1655.849975, 2571.229980, 0.000000, 0.000000, 0.000000, world); // wall4
			Create:house_object(19461, -1068.540039, 1662.199951, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall4
			Create:house_object(19397, -1066.290039, 1655.830078, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall4
			house_int_obj[index][4][hint_wall_end] = Create:house_object(19461, -1073.360107, 1665.179931, 2571.229980, 0.000000, 0.000000, 0.000000, world); // wall4
			
			// [5]
			house_int_obj[index][5][hint_wall_begin] = Create:house_object(19461, -1062.899902, 1660.129882, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall5
			Create:house_object(19461, -1064.669921, 1660.650024, 2571.229980, 0.000000, 0.000000, 0.000000, world); // wall5
			Create:house_object(19461, -1067.699951, 1660.560058, 2571.229980, 0.000000, 0.000000, 0.000000, world); // wall5
			house_int_obj[index][5][hint_wall_end] = Create:house_object(19397, -1066.290039, 1656.010009, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall5
			
			// [6]
			house_int_obj[index][6][hint_wall_begin] = Create:house_object(19461, -1063.729980, 1645.909912, 2571.229980, 0.000000, 0.000000, 0.000000, world); // wall6
			Create:house_object(19461, -1067.379882, 1643.979980, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall6
			Create:house_object(19461, -1070.919921, 1646.050048, 2571.229980, 0.000000, 0.000000, 0.000000, world); // wall6
			Create:house_object(19397, -1066.729980, 1650.760009, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall6
			Create:house_object(19461, -1060.310058, 1650.760009, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall6
			house_int_obj[index][6][hint_wall_end] = Create:house_object(19461, -1073.159912, 1650.760009, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall6
			
			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_floor_end] = 
			house_int_obj[index][0][hint_floor_begin] = Create:house_object(19379, -1068.709960, 1655.659912, 2565.909912, 0.000000, 90.000000, 0.000000, world); // floor0
			
			// [1]
			house_int_obj[index][1][hint_floor_end] = 
			house_int_obj[index][1][hint_floor_begin] = Create:house_object(19379, -1068.709960, 1646.030029, 2565.909912, 0.000000, 90.000000, 0.000000, world); // floor1
			
			// [2]
			house_int_obj[index][2][hint_floor_end] = 
			house_int_obj[index][2][hint_floor_begin] = Create:house_object(19379, -1068.709960, 1665.290039, 2565.909912, 0.000000, 90.000000, 0.000000, world); // floor2
			
			// [3]
			house_int_obj[index][3][hint_floor_end] = 
			house_int_obj[index][3][hint_floor_begin] = Create:house_object(19379, -1079.209960, 1665.290039, 2565.909912, 0.000000, 90.000000, 0.000000, world); // floor3
			
			// [4]
			house_int_obj[index][4][hint_floor_begin] = Create:house_object(19379, -1068.709960, 1665.109985, 2569.429931, 0.000000, 90.000000, 0.000000, world); // floor4
			Create:house_object(19379, -1065.610107, 1655.479980, 2569.429931, 0.000000, 90.000000, 0.000000, world); // floor4
			house_int_obj[index][4][hint_floor_end] = Create:house_object(19379, -1076.110107, 1649.459960, 2569.429931, 0.000000, 90.000000, 0.000000, world); // floor4
			
			// [5]
			house_int_obj[index][5][hint_floor_end] = 
			house_int_obj[index][5][hint_floor_begin] = Create:house_object(19379, -1062.550048, 1660.739990, 2569.449951, 0.000000, 90.000000, 0.000000, world); // floor5
			
			// [6]
			house_int_obj[index][6][hint_floor_end] = 
			house_int_obj[index][6][hint_floor_begin] = Create:house_object(19379, -1068.709960, 1645.849975, 2569.429931, 0.000000, 90.000000, 0.000000, world); // floor6
		}
		
		case 11 : // 5 комнат 2 этажа [1]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_roof_begin] = Create:house_object(19381, -2575.719970, -1353.609985, 2569.560058, 0.000000, 90.000000, 0.000000, world); // roof0
			Create:house_object(19381, -2571.979980, -1343.979980, 2569.560058, 0.000000, 90.000000, 0.000000, world); // roof0
			house_int_obj[index][0][hint_roof_end] = Create:house_object(19381, -2582.479980, -1342.709960, 2569.560058, 0.000000, 90.000000, 0.000000, world); // roof0
			
			// [1]
			house_int_obj[index][1][hint_roof_end] = 
			house_int_obj[index][1][hint_roof_begin] = Create:house_object(19381, -2575.719970, -1359.739990, 2569.540039, 0.000000, 90.000000, 0.000000, world); // roof1
			
			// [2]
			house_int_obj[index][2][hint_roof_end] = 
			house_int_obj[index][2][hint_roof_begin] = Create:house_object(19381, -2586.209960, -1349.920043, 2569.540039, 0.000000, 90.000000, 0.000000, world); // roof2
			
			// [3]
			house_int_obj[index][3][hint_roof_end] = 
			house_int_obj[index][3][hint_roof_begin] = Create:house_object(19381, -2575.719970, -1340.479980, 2569.540039, 0.000000, 90.000000, 0.000000, world); // roof3
			
			// [4]
			house_int_obj[index][4][hint_roof_end] = 
			house_int_obj[index][4][hint_roof_begin] = Create:house_object(19381, -2586.219970, -1340.479980, 2569.540039, 0.000000, 90.000000, 0.000000, world); // roof4
			
			// [5]
			house_int_obj[index][5][hint_roof_begin] = Create:house_object(19381, -2575.669921, -1352.349975, 2573.260009, 0.000000, 90.000000, 0.000000, world); // roof5
			house_int_obj[index][5][hint_roof_end] = Create:house_object(19381, -2586.169921, -1352.349975, 2573.260009, 0.000000, 90.000000, 0.000000, world); // roof5
			
			// [6]
			house_int_obj[index][6][hint_roof_end] = 
			house_int_obj[index][6][hint_roof_begin] = Create:house_object(19381, -2592.090087, -1352.319946, 2573.239990, 0.000000, 90.000000, 0.000000, world); // roof6
			
			// [7]
			house_int_obj[index][7][hint_roof_end] = 
			house_int_obj[index][7][hint_roof_begin] = Create:house_object(19381, -2582.459960, -1342.719970, 2573.260009, 0.000000, 90.000000, 0.000000, world); // roof7
			
			// [8]
			house_int_obj[index][8][hint_roof_end] = 
			house_int_obj[index][8][hint_roof_begin] = Create:house_object(19381, -2575.679931, -1353.630004, 2573.239990, 0.000000, 90.000000, 0.000000, world); // roof8
			
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_wall_begin] = Create:house_object(19461, -2571.570068, -1356.670043, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19397, -2571.570068, -1350.250000, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2571.570068, -1343.829956, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2580.889892, -1346.729980, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19397, -2573.250000, -1345.390014, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19397, -2573.250000, -1354.839965, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2579.669921, -1354.839965, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2579.669921, -1345.390014, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19442, -2576.340087, -1345.170043, 2567.729980, 0.000000, 0.000000, -20.000000, world); // wall0
			Create:house_object(19442, -2578.550048, -1347.180053, 2567.729980, 0.000000, 0.000000, -70.000000, world); // wall0
			Create:house_object(19442, -2580.070068, -1347.449951, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19442, -2577.199951, -1346.400024, 2567.729980, 0.000000, 0.000000, -50.000000, world); // wall0
			house_int_obj[index][0][hint_wall_end] = Create:house_object(19397, -2580.889892, -1353.150024, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall0
			
			// [1]
			house_int_obj[index][1][hint_wall_begin] = Create:house_object(19397, -2573.250000, -1355.020019, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19461, -2579.669921, -1355.020019, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19461, -2571.629882, -1359.859985, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:house_object(19461, -2576.139892, -1363.239990, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19461, -2579.520019, -1359.920043, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:house_object(19461, -2578.939941, -1362.290039, 2567.729980, 0.000000, 0.000000, 45.000000, world); // wall1
			house_int_obj[index][1][hint_wall_end] = Create:house_object(19461, -2572.239990, -1362.270019, 2567.729980, 0.000000, 0.000000, -45.000000, world); // wall1
			
			// [2]
			house_int_obj[index][2][hint_wall_begin] = Create:house_object(19397, -2581.070068, -1353.150024, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:house_object(19461, -2581.070068, -1346.729980, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:house_object(19461, -2586.010009, -1349.060058, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall2
			Create:house_object(19461, -2584.639892, -1350.229980, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall2
			house_int_obj[index][2][hint_wall_end] = Create:house_object(19461, -2585.939941, -1354.719970, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall2

			// [3]
			house_int_obj[index][3][hint_wall_begin] = Create:house_object(19397, -2573.250000, -1345.209960, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall3
			Create:house_object(19461, -2579.669921, -1345.209960, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall3
			Create:house_object(19461, -2571.639892, -1340.339965, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall3
			Create:house_object(19461, -2576.419921, -1335.719970, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall3
			Create:house_object(19397, -2580.889892, -1337.420043, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall3
			Create:house_object(19369, -2580.889892, -1340.630004, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall3
			Create:house_object(19369, -2580.729980, -1342.000000, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall3
			Create:house_object(19369, -2577.520019, -1342.000000, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall3
			house_int_obj[index][3][hint_wall_end] = Create:house_object(19369, -2576.010009, -1343.520019, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall3
			
			// [4]
			house_int_obj[index][4][hint_wall_begin] = Create:house_object(19397, -2581.070068, -1337.420043, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall4
			Create:house_object(19461, -2581.070068, -1343.839965, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall4
			Create:house_object(19461, -2585.889892, -1341.949951, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall4
			Create:house_object(19461, -2585.929931, -1335.859985, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall4
			house_int_obj[index][4][hint_wall_end] = Create:house_object(19461, -2585.109619, -1339.420043, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall4
			
			// [5]
			house_int_obj[index][5][hint_wall_begin] = Create:house_object(19397, -2584.699951, -1347.449951, 2571.429931, 0.000000, 0.000000, 90.000000, world); // wall5
			Create:house_object(19461, -2578.280029, -1347.449951, 2571.429931, 0.000000, 0.000000, 90.000000, world); // wall5
			Create:house_object(19461, -2591.120117, -1347.449951, 2571.429931, 0.000000, 0.000000, 90.000000, world); // wall5
			Create:house_object(19397, -2586.750000, -1351.459960, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall5
			Create:house_object(19461, -2586.750000, -1345.040039, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall5
			Create:house_object(19461, -2586.750000, -1357.880004, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall5
			Create:house_object(19461, -2577.169921, -1344.000000, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall5
			Create:house_object(19461, -2576.110839, -1348.904907, 2571.429931, 0.000000, 0.000000, 90.000000, world); // wall5
			Create:house_object(19397, -2580.840087, -1352.030029, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall5
			Create:house_object(19442, -2580.840087, -1349.619995, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall5
			Create:house_object(19461, -2580.840087, -1358.449951, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall5
			house_int_obj[index][5][hint_wall_end] = Create:house_object(19461, -2585.699951, -1355.020019, 2571.429931, 0.000000, 0.000000, 90.000000, world); // wall5
			
			// [6]
			house_int_obj[index][6][hint_wall_begin] = Create:house_object(19461, -2591.580078, -1354.119995, 2571.429931, 0.000000, 0.000000, 90.000000, world); // wall6
			Create:house_object(19461, -2589.969970, -1352.160034, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall6
			Create:house_object(19461, -2591.610107, -1349.750000, 2571.429931, 0.000000, 0.000000, 90.000000, world); // wall6
			Create:house_object(19397, -2586.929931, -1351.459960, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall6
			house_int_obj[index][6][hint_wall_end] = Create:house_object(19461, -2586.929931, -1357.880004, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall6
			
			// [7]
			house_int_obj[index][7][hint_wall_begin] = Create:house_object(19461, -2586.600097, -1342.420043, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall7
			Create:house_object(19461, -2582.530029, -1340.619995, 2571.429931, 0.000000, 0.000000, 90.000000, world); // wall7
			Create:house_object(19461, -2578.750000, -1342.689941, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall7
			Create:house_object(19397, -2584.699951, -1347.270019, 2571.429931, 0.000000, 0.000000, 90.000000, world); // wall7
			Create:house_object(19461, -2578.280029, -1347.270019, 2571.429931, 0.000000, 0.000000, 90.000000, world); // wall7
			house_int_obj[index][7][hint_wall_end] = Create:house_object(19461, -2591.120117, -1347.270019, 2571.429931, 0.000000, 0.000000, 90.000000, world); // wall7
			
			// [8]
			house_int_obj[index][8][hint_wall_begin] = Create:house_object(19461, -2576.000000, -1355.979980, 2571.429931, 0.000000, 0.000000, 90.000000, world); // wall8
			Create:house_object(19461, -2572.120117, -1352.640014, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall8
			Create:house_object(19397, -2580.659912, -1352.030029, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall8
			Create:house_object(19461, -2580.659912, -1358.449951, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall8
			Create:house_object(19442, -2580.659912, -1349.619995, 2571.429931, 0.000000, 0.000000, 0.000000, world); // wall8
			house_int_obj[index][8][hint_wall_end] = Create:house_object(19461, -2575.820068, -1349.079956, 2571.429931, 0.000000, 0.000000, 90.000000, world); // wall8

			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_floor_end] = 
			house_int_obj[index][0][hint_floor_begin] = Create:house_object(19379, -2575.719970, -1350.109985, 2565.899902, 0.000000, 90.000000, 0.000000, world); // floor0
			
			// [1]
			house_int_obj[index][1][hint_floor_end] = 
			house_int_obj[index][1][hint_floor_begin] = Create:house_object(19379, -2575.719970, -1359.739990, 2565.899902, 0.000000, 90.000000, 0.000000, world); // floor1
			
			// [2]
			house_int_obj[index][2][hint_floor_end] = 
			house_int_obj[index][2][hint_floor_begin] = Create:house_object(19379, -2586.209960, -1349.920043, 2565.899902, 0.000000, 90.000000, 0.000000, world); // floor2
			
			// [3]
			house_int_obj[index][3][hint_floor_end] = 
			house_int_obj[index][3][hint_floor_begin] = Create:house_object(19379, -2575.719970, -1340.479980, 2565.899902, 0.000000, 90.000000, 0.000000, world); // floor3
			
			// [4]
			house_int_obj[index][4][hint_floor_end] = 
			house_int_obj[index][4][hint_floor_begin] = Create:house_object(19379, -2586.219970, -1340.479980, 2565.899902, 0.000000, 90.000000, 0.000000, world); // floor4
			
			// [5]
			house_int_obj[index][5][hint_floor_end] = 
			house_int_obj[index][5][hint_floor_begin] = Create:house_object(19379, -2586.169921, -1352.349975, 2569.600097, 0.000000, 90.000000, 0.000000, world); // floor5
			
			// [6]
			house_int_obj[index][6][hint_floor_end] = 
			house_int_obj[index][6][hint_floor_begin] = Create:house_object(19379, -2592.090087, -1352.319946, 2569.620117, 0.000000, 90.000000, 0.000000, world); // floor6
			
			// [7]
			house_int_obj[index][7][hint_floor_end] = 
			house_int_obj[index][7][hint_floor_begin] = Create:house_object(19379, -2582.459960, -1342.719970, 2569.600097, 0.000000, 90.000000, 0.000000, world); // floor7
			
			// [8]
			house_int_obj[index][8][hint_floor_end] = 
			house_int_obj[index][8][hint_floor_begin] = Create:house_object(19379, -2575.679931, -1353.599975, 2569.600097, 0.000000, 90.000000, 0.000000, world); // floor8
		}
		
		case 12 : // Особняк [1]
		{
			/*
				
				@brief Roof - Крыша
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_roof_begin] = Create:house_object(19381, -2571.169921, -1844.719970, 2571.468750, 0.000000, 90.000000, 0.000000, world); // roof0
			Create:house_object(19381, -2560.669921, -1844.760009, 2571.458496, 0.000000, 90.000000, 0.000000, world); // roof0
			Create:house_object(19381, -2571.189941, -1838.349975, 2569.560058, 0.000000, 90.000000, 0.000000, world); // roof0
			Create:house_object(19381, -2575.392578, -1844.719970, 2573.029785, 0.000000, 90.000000, 0.000000, world); // roof0
			Create:house_object(19381, -2571.979980, -1343.979980, 2569.729736, 0.000000, 90.000000, 0.000000, world);
			house_int_obj[index][0][hint_roof_end] = Create:house_object(19381, -2581.688232, -1838.349975, 2569.557128, 0.000000, 90.000000, 0.000000, world); // roof0
			
			// [1]
			house_int_obj[index][1][hint_roof_end] = 
			house_int_obj[index][1][hint_roof_begin] = Create:house_object(19381, -2571.947998, -1854.349975, 2569.530029, 0.000000, 90.000000, 0.000000, world); // roof1
			
			// [2]
			house_int_obj[index][2][hint_roof_end] = 
			house_int_obj[index][2][hint_roof_begin] = Create:house_object(19381, -2582.458251, -1854.349975, 2569.429931, 0.000000, 90.000000, 0.000000, world); // roof2
			
			// [3]
			house_int_obj[index][3][hint_roof_end] = 
			house_int_obj[index][3][hint_roof_begin] = Create:house_object(19381, -2572.169921, -1835.609130, 2569.550048, 0.000000, 90.000000, 0.000000, world); // roof3
			
			// [4]
			house_int_obj[index][4][hint_roof_begin] = Create:house_object(19381, -2593.118164, -1835.529052, 2569.447998, 0.000000, 90.000000, 0.000000, world); // roof4
			house_int_obj[index][4][hint_roof_end] = Create:house_object(19381, -2582.629638, -1835.549072, 2569.447998, 0.000000, 90.000000, 0.000000, world); // wall4
			
			// [5]
			house_int_obj[index][5][hint_roof_end] = 
			house_int_obj[index][5][hint_roof_begin] = Create:house_object(19381, -2585.730957, -1841.968627, 2569.451904, 0.000000, 90.000000, 0.000000, world); // roof5
			
			// [6]
			house_int_obj[index][6][hint_roof_end] = 
			house_int_obj[index][6][hint_roof_begin] = Create:house_object(19381, -2585.872802, -1844.719970, 2573.032226, 0.000000, 90.000000, 0.000000, world); // roof6
			
			// [7]
			house_int_obj[index][7][hint_roof_end] = 
			house_int_obj[index][7][hint_roof_begin] = Create:house_object(19381, -2585.889404, -1854.469116, 2573.030273, 0.000000, 90.000000, 0.000000, world); // roof7
			
			// [8]
			house_int_obj[index][8][hint_roof_end] = 
			house_int_obj[index][8][hint_roof_begin] = Create:house_object(19381, -2596.530761, -1844.828491, 2573.030273, 0.000000, 90.000000, 0.000000, world); // roof8
			
			// [9]
			house_int_obj[index][9][hint_roof_begin] = Create:house_object(19381, -2578.459228, -1842.288940, 2573.030273, 0.000000, 90.000000, 0.000000, world); // roof9
			house_int_obj[index][9][hint_roof_end] = Create:house_object(19381, -2588.962402, -1839.408081, 2573.030273, 0.000000, 90.000000, 0.000000, world); // roof9
			
			/*
				
				@brief Wall - Стены
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_wall_begin] = Create:house_object(19461, -2581.849121, -1847.030761, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2572.620117, -1843.089965, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2565.790039, -1849.469970, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2576.500000, -1844.920043, 2573.121826, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2564.459960, -1844.920043, 2571.229980, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2565.500000, -1843.099975, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2566.030029, -1843.099975, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19369, -2570.770019, -1841.589599, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2560.550048, -1844.719970, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2560.550048, -1847.910034, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2565.290039, -1852.640014, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2565.290039, -1839.989990, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2565.290039, -1839.989990, 2571.229980, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2560.550048, -1844.719970, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2560.550048, -1847.910034, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2565.290039, -1852.640014, 2571.229980, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2570.179931, -1844.920043, 2571.779296, 0.000000, 0.000000, 0.000000, world); // wall0
			Create:house_object(19461, -2569.219970, -1849.469848, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2575.429931, -1849.469970, 2571.229980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19397, -2575.639892, -1849.469848, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19369, -2578.830078, -1849.469360, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19397, -2572.620117, -1840.460449, 2567.729980, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:house_object(19369, -2575.820068, -1840.460449, 2567.729980, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:house_object(19397, -2579.030029, -1840.460449, 2567.729980, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:house_object(19369, -2579.038085, -1843.089843, 2571.231689, 0.000000, 0.000000, 90.000000, world); // wall0
			Create:house_object(19461, -2580.551513, -1842.289794, 2571.229980, 0.000000, 0.000000, 180.000000, world); // wall0
			Create:house_object(19397, -2580.549316, -1845.367309, 2567.729980, 0.000007, 0.000000, 179.999969, world); // wall0
			Create:house_object(19442, -2570.210937, -1840.456420, 2567.729980, 0.000007, 0.000000, 89.999977, world); // wall0
			Create:house_object(19369, -2580.553710, -1842.156250, 2567.729980, 0.000000, 0.000000, 180.000000, world); // wall0
			house_int_obj[index][0][hint_wall_end] = Create:house_object(19369, -2582.039306, -1849.469360, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall0
			
			// [1]
			house_int_obj[index][1][hint_wall_begin] = Create:house_object(19461, -2569.219970, -1849.650024, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall1
			Create:house_object(19397, -2577.106201, -1851.316650, 2567.729980, 0.000007, 0.000000, 179.999969, world); // wall1
			Create:house_object(19461, -2577.099853, -1857.660644, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:house_object(19461, -2570.770019, -1854.410034, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall1
			Create:house_object(19397, -2575.639892, -1849.649902, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall1
			house_int_obj[index][1][hint_wall_end] = Create:house_object(19461, -2573.110107, -1859.109985, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall1
			
			// [2]
			house_int_obj[index][2][hint_wall_begin] = Create:house_object(19397, -2577.276367, -1851.316650, 2567.729980, 0.000007, 0.000000, 179.999969, world); // wall2
			Create:house_object(19461, -2581.991455, -1849.961059, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall2
			Create:house_object(19461, -2577.278076, -1857.660644, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall2
			Create:house_object(19461, -2580.568847, -1854.849731, 2567.729980, 0.000000, 0.000000, 0.000000, world); // wall2
			house_int_obj[index][2][hint_wall_end] = Create:house_object(19461, -2581.930175, -1856.279907, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall2
			
			// [3]
			house_int_obj[index][3][hint_wall_begin] = Create:house_object(19461, -2567.176757, -1837.846069, 2567.729980, 0.000007, 0.000000, 121.099945, world); // wall3
			Create:house_object(19397, -2572.620117, -1840.290405, 2567.729980, 0.000007, 0.000000, 89.999977, world); // wall3
			Create:house_object(19369, -2575.820068, -1840.290405, 2567.729980, 0.000007, 0.000000, 89.999977, world); // wall3
			Create:house_object(19461, -2569.689941, -1835.460449, 2567.729980, 0.000000, 0.000007, 0.000000, world); // wall3
			Create:house_object(19461, -2572.489990, -1831.200439, 2567.729980, 0.000007, 0.000000, 89.999977, world); // wall3
			Create:house_object(19397, -2577.340087, -1838.612548, 2567.729980, 0.000000, 0.000037, 0.000000, world); // wall3
			Create:house_object(19461, -2577.338867, -1832.210449, 2567.729980, 0.000007, 0.000000, 179.999969, world); // wall3
			house_int_obj[index][3][hint_wall_end] = Create:house_object(19461, -2569.557861, -1833.294067, 2567.729980, 0.000007, 0.000000, 931.099975, world); // wall3
			
			// [4]
			house_int_obj[index][4][hint_wall_begin] = Create:house_object(19461, -2577.519042, -1832.210449, 2567.729980, 0.000007, 0.000000, 179.999969, world); // wall4
			Create:house_object(19397, -2579.030029, -1840.280517, 2567.729980, 0.000007, 0.000000, 89.999977, world); // wall4
			Create:house_object(19397, -2577.510009, -1838.612548, 2567.729980, 0.000000, 0.000037, 0.000000, world); // wall4
			Create:house_object(19461, -2582.119628, -1831.200439, 2567.729980, 0.000007, 0.000000, 89.999977, world); // wall4
			Create:house_object(19369, -2582.233886, -1840.275512, 2567.729980, 0.000000, 0.000000, 270.000000, world); // wall4
			Create:house_object(19461, -2591.750000, -1831.200439, 2567.729980, 0.000007, 0.000000, 89.999977, world); // wall4
			house_int_obj[index][4][hint_wall_end] = Create:house_object(19461, -2589.577880, -1835.529785, 2567.729980, 0.000007, 0.000000, 179.999969, world); // wall4

			// [5]
			house_int_obj[index][5][hint_wall_begin] = Create:house_object(19369, -2580.713867, -1842.156250, 2567.729980, 0.000000, 0.000000, 180.000000, world); // wall5
			Create:house_object(19397, -2580.709472, -1845.367309, 2567.729980, 0.000007, 0.000000, 179.999969, world); // wall5
			Create:house_object(19461, -2585.288818, -1847.000732, 2567.729980, 0.000000, 0.000000, 90.000000, world); // wall5
			Create:house_object(19369, -2582.233886, -1840.455688, 2567.729980, 0.000000, 0.000000, 270.000000, world); // wall5
			house_int_obj[index][5][hint_wall_end] = Create:house_object(19461, -2589.577880, -1845.170043, 2567.729980, 0.000007, 0.000000, 179.999969, world); // wall5
			
			// [6]
			house_int_obj[index][6][hint_wall_begin] = Create:house_object(19369, -2581.839111, -1849.469360, 2571.231689, 0.000000, 0.000000, 90.000000, world); // wall6
			Create:house_object(19397, -2585.032470, -1849.468261, 2571.229736, 0.000000, 0.000000, 90.000000, world); // wall6
			Create:house_object(19461, -2591.416259, -1849.459716, 2571.229980, -0.000007, 0.000000, -89.999977, world); // wall6
			Create:house_object(19369, -2582.099365, -1847.018920, 2571.231689, 0.000000, 0.000000, 90.000000, world); // wall6
			Create:house_object(19369, -2583.629394, -1845.503540, 2571.231689, 0.000000, 0.000000, 180.000000, world); // wall6
			Create:house_object(19397, -2585.294921, -1844.142456, 2571.229736, 0.000000, 0.000000, 90.000000, world); // wall6
			Create:house_object(19461, -2591.714355, -1844.142333, 2571.229980, 0.000000, 0.000007, 89.999969, world); // wall6
			Create:house_object(19397, -2591.052490, -1848.630004, 2571.229736, 0.000000, 0.000000, 180.000000, world); // wall6
			house_int_obj[index][6][hint_wall_end] = Create:house_object(19461, -2591.053955, -1842.211669, 2571.229980, 0.000000, 0.000007, 179.999969, world); // wall6
			
			// [7]
			house_int_obj[index][7][hint_wall_begin] = Create:house_object(19461, -2581.920654, -1854.429809, 2571.229980, 0.000000, 0.000000, 180.000000, world); // wall7
			Create:house_object(19461, -2585.537597, -1856.800048, 2571.229980, 0.000000, 0.000000, 270.000000, world); // wall7
			Create:house_object(19397, -2585.032470, -1849.648437, 2571.229736, 0.000000, 0.000000, 90.000000, world); // wall7
			Create:house_object(19461, -2591.416259, -1849.649902, 2571.229980, -0.000007, 0.000000, -89.999977, world); // wall7
			Create:house_object(19461, -2590.395507, -1854.459960, 2571.229980, -0.000007, 0.000000, 0.000022, world); // wall7
			house_int_obj[index][7][hint_wall_end] = Create:house_object(19369, -2581.839111, -1849.648803, 2571.229736, 0.000000, 0.000000, 90.000000, world); // wall7
			
			// [8]
			house_int_obj[index][8][hint_wall_begin] = Create:house_object(19397, -2591.232666, -1848.630004, 2571.229736, 0.000000, -0.000007, 179.999954, world); // wall8
			Create:house_object(19461, -2591.234130, -1842.211669, 2571.229980, 0.000000, 0.000000, 179.999923, world); // wall8
			Create:house_object(19461, -2596.045654, -1844.152221, 2571.229980, 0.000000, 0.000007, 269.999969, world); // wall8
			Create:house_object(19461, -2596.185791, -1845.422973, 2571.229980, 0.000000, 0.000007, 359.999969, world); // wall8
			house_int_obj[index][8][hint_wall_end] = Create:house_object(19461, -2595.976806, -1849.439819, 2571.229980, -0.000007, 0.000000, -89.999977, world); // wall8
			
			// [9]
			house_int_obj[index][9][hint_wall_begin] = Create:house_object(19397, -2585.294921, -1843.962280, 2571.229736, 0.000000, 0.000000, 90.000000, world); // wall9
			Create:house_object(19369, -2582.099365, -1846.778686, 2571.231689, 0.000000, 0.000000, 90.000000, world); // wall9
			Create:house_object(19369, -2583.599365, -1845.478881, 2571.231689, 0.000000, 0.000000, 180.000000, world); // wall9
			Create:house_object(19461, -2580.701660, -1842.289794, 2571.229980, 0.000000, 0.000000, 180.000000, world); // wall9
			Create:house_object(19461, -2591.714355, -1843.962158, 2571.229980, 0.000000, 0.000007, 89.999969, world); // wall9
			Create:house_object(19461, -2585.563720, -1837.549804, 2571.229980, -0.000007, 0.000000, 90.000022, world); // wall9
			house_int_obj[index][9][hint_wall_end] = Create:house_object(19461, -2590.283447, -1839.191772, 2571.229980, 0.000000, 0.000007, 179.999969, world); // wall9
			
			/*
				
				@brief Floor - Пол
				
			*/
			
			// [0]
			house_int_obj[index][0][hint_floor_begin] = Create:house_object(19379, -2575.389892, -1844.718994, 2565.899902, 0.000000, 90.000000, 0.000000, world); // floor0
			house_int_obj[index][0][hint_floor_end] = Create:house_object(19379, -2564.889892, -1844.718872, 2565.899902, 0.000000, 90.000000, 0.000000, world); // floor0
			
			// [1]
			house_int_obj[index][1][hint_floor_end] = 
			house_int_obj[index][1][hint_floor_begin] = Create:house_object(19379, -2571.938720, -1854.349975, 2565.899902, 0.000000, 90.000000, 0.000000, world); // floor1
			
			// [2]
			house_int_obj[index][2][hint_floor_end] = 
			house_int_obj[index][2][hint_floor_begin] = Create:house_object(19379, -2582.438964, -1854.349975, 2565.899902, 0.000000, 90.000000, 0.000000, world); // floor2
			
			// [3]
			house_int_obj[index][3][hint_floor_end] = 
			house_int_obj[index][3][hint_floor_begin] = Create:house_object(19379, -2572.179931, -1835.550415, 2565.901855, 0.000000, 90.000007, 0.000000, world); // floor3
			
			// [4]
			house_int_obj[index][4][hint_floor_begin] = Create:house_object(19379, -2582.679931, -1835.550415, 2565.901855, 0.000000, 90.000007, 0.000000, world); // floor4
			house_int_obj[index][4][hint_floor_end] = Create:house_object(19379, -2593.088867, -1835.550415, 2565.901855, 0.000000, 90.000007, 0.000000, world); // floor4
			
			// [5]
			house_int_obj[index][5][hint_floor_end] = 
			house_int_obj[index][5][hint_floor_begin] = Create:house_object(19379, -2585.878173, -1844.718994, 2565.899902, 0.000000, 90.000000, 0.000000, world); // floor5
			
			// [6]
			house_int_obj[index][6][hint_floor_begin] = Create:house_object(19379, -2585.890136, -1842.290527, 2569.573486, 0.000000, 90.000000, 0.000000, world); // floor6
			house_int_obj[index][6][hint_floor_end] = Create:house_object(19379, -2587.250976, -1851.910400, 2569.573242, 0.000000, 90.000000, 0.000000, world); // floor6
			
			// [7]
			house_int_obj[index][7][hint_floor_end] = 
			house_int_obj[index][7][hint_floor_begin] = Create:house_object(19379, -2587.200927, -1854.370605, 2569.574218, 0.000000, 90.000000, 0.000000, world); // floor7
			
			// [8]
			house_int_obj[index][8][hint_floor_end] = 
			house_int_obj[index][8][hint_floor_begin] = Create:house_object(19379, -2596.409423, -1846.840087, 2569.579101, 0.000000, 90.000000, 0.000000, world); // floor8
			
			// [9]
			house_int_obj[index][9][hint_floor_begin] = Create:house_object(19370, -2582.105224, -1845.130859, 2569.576904, 0.000000, 90.000000, 90.000000, world); // floor9
			house_int_obj[index][9][hint_floor_end] = Create:house_object(19379, -2585.969482, -1839.221069, 2569.578613, 0.000000, 90.000000, 0.000000, world); // floor9
		}
	}
}

IsHouseObject(objectid, houseid)
{
	new type,
		worldid;
	
	type = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_EXTRA_ID);
	worldid = Streamer_GetIntData(STREAMER_TYPE_OBJECT, objectid, E_STREAMER_WORLD_ID);

	return (type == TYPE_REN_HOUSE && houseid == worldid);
}

Destroy:house_int_obj(index)
{
	new room = GetHouseSettings(index, hset_rooms),
		houseid = GetHouseId(index);
		
	for (new i; i < room; i++)
	{
		for (new j = house_int_obj[index][i][hint_roof_begin]; j <= house_int_obj[index][i][hint_roof_end]; j++)
		{
			if (IsValidDynamicObject(j) && IsHouseObject(j, houseid))
			{
				DestroyDynamicObject(j);
			}
		}
		
		for (new j = house_int_obj[index][i][hint_wall_begin]; j <= house_int_obj[index][i][hint_wall_end]; j++)
		{
			if (IsValidDynamicObject(j) && IsHouseObject(j, houseid))
			{
				DestroyDynamicObject(j);
			}
		}
		
		for (new j = house_int_obj[index][i][hint_floor_begin]; j <= house_int_obj[index][i][hint_floor_end]; j++)
		{
			if (IsValidDynamicObject(j) && IsHouseObject(j, houseid))
			{
				DestroyDynamicObject(j);
			}
		}
	}
}


HouseInteriorStaticObjects()
{
	new tmpobjid;
	
	// 1 - Студия - [1]
	CreateObject(19545, -2715.529052, -1509.251831, 2600.976562, 0.000000, 0.000000, 0.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19369, -2718.789306, -1513.931762, 2602.748535, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 2 - Студия - [2]
	CreateObject(19538, -2365.562011, -1172.852416, 2608.029785, 0.000000, 0.000000, 0.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19369, -2411.747802, -1174.866333, 2609.422607, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 3 - Студия - [3]
	CreateObject(19538, -2436.633300, -752.252258, 2610.195800, 0.000000, 0.000000, 0.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19461, -2463.016357, -744.387817, 2611.853027, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 4 - 1 комната - [1]
	CreateObject(19545, -2612.769775, 645.679931, 2565.929931, 0.000000, 0.000000, 90.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19369, -2601.419921, 647.450012, 2567.750000, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 5 - 1 комната - [2]
	CreateObject(19545, -2622.350097, 1150.349243, 2565.889892, 0.000000, 0.000000, 90.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19369, -2614.949951, 1149.000000, 2567.669921, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 6 - 1 комната - [3]
	CreateObject(19538, -2225.808349, -1034.427490, 2612.741455, 0.000000, 0.000000, 0.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19369, -2249.546875, -1036.476806, 2614.353515, 0.000000, 0.000007, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 7 - 2 комнаты - [1]
	CreateObject(19538, -2622.350097, 44.270000, 2565.929931, 0.000000, 0.000000, 0.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19369, -2580.770019, 41.880001, 2567.750000, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 8 - 2 комнаты - [2]
	CreateObject(19538, -2231.378906, -644.187255, 2610.278564, 0.000000, 0.000000, 0.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19369, -2209.751220, -652.858154, 2611.965332, 0.000000, 0.000007, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 9 - 3 комнаты - [1]
	CreateObject(19538, -1763.966552, -640.121032, 2584.727050, 0.000000, 0.000000, 0.000000, 300.00); // fco
	tmpobjid = CreateDynamicObject(19369, -1768.672363, -645.871520, 2586.527587, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	// 10 - 4 комнаты 2 этажа [1]
	CreateObject(19538, -1122.350097, 1655.489990, 2565.929931, 0.000000, 0.000000, 0.000000, 300.00); // fco
	CreateObject(19538, -1039.579345, 1691.550048, 2569.489990, 0.000000, 0.000000, 90.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19353, -1063.370117, 1655.479980, 2567.729980, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	tmpobjid = CreateDynamicObject(14877, -1072.449951, 1659.349975, 2567.260009, 0.000000, 0.000000, 90.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1655.770019, 2567.020019, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(19087, -1070.939941, 1657.250000, 2568.260009, -55.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(19087, -1070.939941, 1659.250000, 2569.659912, -55.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(19087, -1070.939941, 1660.229980, 2570.350097, -55.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1660.130004, 2570.070068, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1659.510009, 2569.639892, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1658.890014, 2569.209960, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1658.260009, 2568.770019, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1657.650024, 2568.340087, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1657.040039, 2567.919921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1656.400024, 2567.459960, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1655.449951, 2566.790039, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1656.070068, 2567.219970, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1656.719970, 2567.679931, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1657.340087, 2568.110107, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1657.949951, 2568.550048, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1658.580078, 2568.989990, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1659.209960, 2569.429931, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.870117, 1659.830078, 2569.860107, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1660.130004, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(19087, -1070.820068, 1660.229980, 2570.389892, -90.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1659.830078, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1659.510009, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1659.209960, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1658.890014, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1658.580078, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1658.260009, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1657.949951, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1657.650024, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1657.340087, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1657.040039, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1656.719970, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1656.400024, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1656.070068, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1655.770019, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1655.469970, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1655.150024, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1654.830078, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1654.489990, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1070.750000, 1654.169921, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1071.070068, 1654.169921, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1071.399902, 1654.169921, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1071.739990, 1654.169921, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1072.080078, 1654.169921, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1072.419921, 1654.169921, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1073.159912, 1654.169921, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(336, -1072.790039, 1654.169921, 2570.169921, 4.000000, 180.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(19087, -1070.820068, 1656.659912, 2570.389892, -90.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(19087, -1070.820068, 1658.280029, 2570.389892, -90.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(19087, -1073.270019, 1654.209960, 2570.389892, -90.000000, 0.000000, 90.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // Ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14652, "ab_trukstpa", "mp_diner_wood", 0x00000000);
	tmpobjid = CreateDynamicObject(983, -1070.941162, 1658.075683, 2568.104492, 32.200008, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // invisiblewall
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 3, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 4, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 5, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(983, -1070.833496, 1657.108642, 2569.826171, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // invisiblewall
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 3, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 4, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 5, 19962, "samproadsigns", "materialtext1", 0x00000000);
	tmpobjid = CreateDynamicObject(983, -1074.015136, 1654.188720, 2569.826171, 0.000000, 0.000000, 90.000000, -1, INT_HOUSE, -1, 300.00, 300.00); // invisiblewell
	SetDynamicObjectMaterial(tmpobjid, 0, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 1, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 2, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 3, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 4, 19962, "samproadsigns", "materialtext1", 0x00000000);
	SetDynamicObjectMaterial(tmpobjid, 5, 19962, "samproadsigns", "materialtext1", 0x00000000);

	// 11 - 5 Room [1]
	CreateObject(19538, -2611.090087, -1344.530029, 2565.929931, 0.000000, 0.000000, 0.000000, 300.00); // fco
	CreateObject(19538, -2612.418457, -1344.530029, 2569.650390, 0.000000, 0.000000, 90.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19353, -2571.419921, -1350.250000, 2567.729980, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE, -1, 300.00, 300.00);
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	
	tmpobjid = CreateDynamicObject(19325, -2580.040039, -1348.790039, 2567.439941, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); // setka
	SetDynamicObjectMaterial(tmpobjid, 0, 10806, "airfence_sfse", "ws_griddyfence", 0xFF000000);
	
	tmpobjid = CreateDynamicObject(19940, -2580.760009, -1347.540039, 2569.290039, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2580.520019, -1347.540039, 2569.090087, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2580.280029, -1347.540039, 2568.889892, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2580.040039, -1347.540039, 2568.689941, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2579.800048, -1347.540039, 2568.489990, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2579.560058, -1347.540039, 2568.290039, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2579.320068, -1347.540039, 2568.090087, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2579.080078, -1347.540039, 2567.889892, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2578.840087, -1347.540039, 2567.689941, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2578.600097, -1347.540039, 2567.489990, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2578.360107, -1347.540039, 2567.290039, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2578.120117, -1347.540039, 2567.090087, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2577.879882, -1347.540039, 2566.889892, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2577.639892, -1347.540039, 2566.689941, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2577.399902, -1347.540039, 2566.489990, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2577.159912, -1347.540039, 2566.290039, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2576.919921, -1347.540039, 2566.090087, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19940, -2580.959960, -1347.540039, 2569.469970, 0.000000, 0.000000, 0.000000, -1, INT_HOUSE); // ladder-1
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(1319, -2579.624511, -1348.037597, 2568.041992, 0.000000, -50.200080, 0.000000, -1, INT_HOUSE); // new_ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14789, "ab_sfgymmain", "ab_wood02", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(1319, -2580.430419, -1348.037597, 2568.714599, 0.000000, -50.200080, 0.000000, -1, INT_HOUSE); // new_ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14789, "ab_sfgymmain", "ab_wood02", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(1319, -2578.810058, -1348.037597, 2567.362792, 0.000000, -50.200080, 0.000000, -1, INT_HOUSE); // new_ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14789, "ab_sfgymmain", "ab_wood02", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(1319, -2577.987304, -1348.037597, 2566.677246, 0.000000, -50.200080, 0.000000, -1, INT_HOUSE); // new_ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14789, "ab_sfgymmain", "ab_wood02", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(1319, -2577.175537, -1348.037597, 2566.000732, 0.000000, -50.200080, 0.000000, -1, INT_HOUSE); // new_ladder
	SetDynamicObjectMaterial(tmpobjid, 0, 14789, "ab_sfgymmain", "ab_wood02", 0xFFFFFFFF);
	
	// 12 - Mansion [1]
	CreateObject(19538, -2589.026855, -1851.029907, 2565.939941, 0.000000, 0.000000, 90.000000, 300.00); // fco
	
	tmpobjid = CreateDynamicObject(19353, -2564.300048, -1846.290039, 2567.729980, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); // blackwell
	SetDynamicObjectMaterial(tmpobjid, 0, 18646, "matcolours", "grey-90-percent", 0x00000000);
	tmpobjid = CreateDynamicObject(14877, -2581.073242, -1848.544555, 2567.400390, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // stairs
	SetDynamicObjectMaterial(tmpobjid, 0, 10101, "2notherbuildsfe", "Bow_Abpave_Gen", 0xFF646464);
	tmpobjid = CreateDynamicObject(19325, -2564.409912, -1846.410034, 2570.610107, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); // glass
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19325, -2570.179931, -1846.550048, 2570.610107, 0.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); // glass
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19325, -2570.179931, -1842.770019, 2565.189941, 90.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); // glass_window
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	tmpobjid = CreateDynamicObject(19325, -2570.179931, -1849.939941, 2565.189941, 90.000000, 0.000000, 0.000000, -1, -1, -1, 300.00, 300.00); // glass_window
	SetDynamicObjectMaterial(tmpobjid, 0, -1, "none", "none", 0xFFFFFFFF);
	CreateDynamicObject(1897, -2564.310058, -1845.189941, 2568.550048, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2564.310058, -1847.410034, 2568.550048, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2564.310058, -1844.869995, 2569.709960, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2564.310058, -1847.770019, 2569.709960, 0.000000, 0.000000, 90.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2564.310058, -1845.209960, 2569.429931, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2564.310058, -1847.430053, 2569.429931, 0.000000, 90.000000, 90.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1844.680053, 2567.429931, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1843.130004, 2567.429931, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1847.760009, 2567.429931, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1849.239990, 2567.429931, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1847.949951, 2565.209960, 180.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1849.430053, 2565.209960, 180.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1844.869995, 2565.209960, 180.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1843.319946, 2565.209960, 180.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1843.670043, 2565.939941, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1848.979980, 2565.939941, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1848.959960, 2568.439941, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1843.030029, 2568.439941, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1845.239990, 2568.629882, -90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1846.739990, 2568.629882, -90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1844.680053, 2569.669921, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1843.130004, 2569.669921, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1847.760009, 2569.669921, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1849.239990, 2569.669921, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1846.219970, 2569.669921, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1843.939941, 2567.429931, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1844.130004, 2565.209960, 180.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1848.540039, 2567.429931, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1848.729980, 2565.209960, 180.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1843.650024, 2567.620117, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1843.650024, 2566.780029, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1848.959960, 2567.620117, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1848.959960, 2566.780029, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1843.939941, 2569.669921, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1848.540039, 2569.669921, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1847.010009, 2569.669921, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1845.469970, 2569.669921, 0.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1843.650024, 2569.159912, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1843.650024, 2569.919921, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1845.869995, 2569.919921, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1848.229980, 2569.919921, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1846.670043, 2569.919921, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1846.670043, 2569.159912, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1845.869995, 2569.159912, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
	CreateDynamicObject(1897, -2570.179931, -1848.229980, 2569.159912, 90.000000, 0.000000, 180.000000, -1, -1, -1, 300.00, 300.00); // glass
}

SetHouseInteriorMaterial(index, room, E_HOUSE_INTERIOR: enum_item_1, E_HOUSE_INTERIOR: enum_item_2, texture_type, texture)
{
	new model,
		txd_name				[	34	],
		texture_name			[	34 	],
		houseid = GetHouseId(index);
	
	GetTextureByType(texture_type, texture, model, txd_name, texture_name);

	for (new i = house_int_obj[index][room][enum_item_1]; i <= house_int_obj[index][room][enum_item_2]; i++)
	{
		if (IsHouseObject(i, houseid))
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

HouseInteriorText3D()
{
	for (new i = 1; i < sizeof house_settings; i++)
	{
		CreateDynamic3DTextLabel(
			"Выход", 
			-1, 
			house_settings[i][hset_pos][0], 
			house_settings[i][hset_pos][1], 
			house_settings[i][hset_pos][2] - 0.2, 
			TEXT3D_DRAW_DISTANCE, 
			_, 
			_, 
			_, 
			_,
			INT_HOUSE,
			_, 
			TEXT3D_DRAW_DISTANCE
		);
	}
}