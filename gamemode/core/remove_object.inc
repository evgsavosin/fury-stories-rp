/*!
	@brief Удаление объектов у игроков
	@author Found (evg.savosin)
	@date 16.12.2016, update 15.01.2018
*/

Include_RemoveObject(playerid)
{
	RemoveBuilding_Interior(playerid);
	
	// Factions
	RemoveBuilding_PD(playerid);
	RemoveBuilding_FD(playerid);
	RemoveBuilding_SD(playerid);
	RemoveBuilding_NPL(playerid);
	RemoveBuilding_Prison(playerid);
	
	// Idlewood Pizza
	RemoveBuildingForPlayer(playerid, 5530, 2112.937, -1797.093, 19.335, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 2091.164, -1826.835, 12.703, 0.250);
	RemoveBuildingForPlayer(playerid, 1408, 2099.851, -1813.906, 13.101, 0.250);
	RemoveBuildingForPlayer(playerid, 1408, 2099.859, -1819.359, 13.101, 0.250);
	RemoveBuildingForPlayer(playerid, 1408, 2099.859, -1799.421, 13.101, 0.250);
	RemoveBuildingForPlayer(playerid, 1408, 2102.601, -1822.078, 13.117, 0.250);
	RemoveBuildingForPlayer(playerid, 1432, 2104.015, -1812.421, 12.671, 0.250);
	RemoveBuildingForPlayer(playerid, 1432, 2101.992, -1814.710, 12.570, 0.250);
	RemoveBuildingForPlayer(playerid, 1432, 2103.406, -1817.304, 12.671, 0.250);
	RemoveBuildingForPlayer(playerid, 1432, 2102.125, -1819.953, 12.671, 0.250);
	RemoveBuildingForPlayer(playerid, 1432, 2101.632, -1798.171, 12.671, 0.250);
	RemoveBuildingForPlayer(playerid, 1432, 2103.960, -1800.562, 12.671, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 2128.312, -1826.835, 12.703, 0.250);
	RemoveBuildingForPlayer(playerid, 1522, 2105.921, -1807.250, 12.515, 0.250);
	RemoveBuildingForPlayer(playerid, 5418, 2112.937, -1797.093, 19.335, 0.250);
	RemoveBuildingForPlayer(playerid, 1408, 2099.851, -1793.976, 13.101, 0.250);
	RemoveBuildingForPlayer(playerid, 712, 2100.812, -1764.375, 21.390, 0.250);
	RemoveBuildingForPlayer(playerid, 1408, 2102.664, -1791.328, 13.101, 0.250);
	RemoveBuildingForPlayer(playerid, 1432, 2103.687, -1795.906, 12.671, 0.250);
	RemoveBuildingForPlayer(playerid, 1432, 2102.062, -1793.140, 12.671, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2105.085, -1765.609, 10.804, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 2114.718, -1785.179, 16.398, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 2128.312, -1786.710, 12.703, 0.250);
	
	// El Corona
	RemoveBuildingForPlayer(playerid, 3588, 1907.630, -2025.938, 15.131, 0.250);
	RemoveBuildingForPlayer(playerid, 3667, 1907.630, -2025.938, 15.131, 0.250);
	RemoveBuildingForPlayer(playerid, 3588, 1904.800, -1991.739, 15.125, 0.250);
	RemoveBuildingForPlayer(playerid, 3667, 1904.800, -1991.739, 15.125, 0.250);
	RemoveBuildingForPlayer(playerid, 3588, 1861.448, -1991.750, 15.210, 0.250);
	RemoveBuildingForPlayer(playerid, 3667, 1861.448, -1991.750, 15.210, 0.250);
	RemoveBuildingForPlayer(playerid, 3588, 1858.630, -2025.938, 15.210, 0.250);
	RemoveBuildingForPlayer(playerid, 3667, 1858.630, -2025.938, 15.210, 0.250);
	RemoveBuildingForPlayer(playerid, 3588, 1826.598, -1989.609, 15.210, 0.250);
	RemoveBuildingForPlayer(playerid, 3667, 1826.598, -1989.609, 15.210, 0.250);
	RemoveBuildingForPlayer(playerid, 5086, 1892.540, -2012.828, 21.375, 0.250);
	RemoveBuildingForPlayer(playerid, 4982, 1892.540, -2012.828, 21.375, 0.250);
	RemoveBuildingForPlayer(playerid, 4859, 1868.948, -2003.660, 13.750, 0.250);
	RemoveBuildingForPlayer(playerid, 4966, 1868.948, -2003.660, 13.750, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 1893.520, -2042.670, 12.600, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 1893.948, -2013.050, 12.694, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 1882.369, -1992.130, 16.273, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 1882.369, -1975.938, 16.273, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 1882.369, -2012.660, 16.273, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 1873.109, -2013.050, 12.600, 0.250);
	RemoveBuildingForPlayer(playerid, 671, 1921.489, -2040.520, 12.640, 0.250);
	RemoveBuildingForPlayer(playerid, 1307, 1922.578, -2023.550, 12.710, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 1924.588, -2002.348, 16.273, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 1924.588, -1977.088, 16.273, 0.250);
	RemoveBuildingForPlayer(playerid, 1531, 1889.239, -1982.510, 15.756, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 1914.880, -1980.338, 9.670, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 1922.119, -1981.208, 9.670, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 1849.530, -2041.290, 9.670, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 1870.188, -2041.040, 9.670, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 1872.328, -2042.869, 12.812, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 1841.930, -2007.479, 16.273, 0.250);
	RemoveBuildingForPlayer(playerid, 712, 1839.948, -2041.000, 21.959, 0.250);
	RemoveBuildingForPlayer(playerid, 1307, 1832.630, -2012.828, 12.687, 0.250);
	RemoveBuildingForPlayer(playerid, 671, 1835.010, -2015.359, 12.640, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 1870.380, -1971.359, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1865.098, -1971.359, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1859.818, -1971.359, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1875.630, -1971.588, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1852.979, -1965.359, 13.647, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1850.479, -1968.660, 13.647, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1847.729, -1971.359, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 1841.930, -1977.088, 16.273, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 1813.088, -2013.030, 12.750, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 1822.958, -2015.910, 16.389, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 1818.718, -2017.609, 16.273, 0.250);
	RemoveBuildingForPlayer(playerid, 708, 1837.640, -1968.338, 12.187, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1810.828, -1971.359, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1816.109, -1971.359, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 1821.380, -1971.359, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1826.640, -1971.588, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1831.910, -1971.588, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 1837.170, -1971.359, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1842.448, -1971.359, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1880.900, -1971.588, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 1886.160, -1971.359, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1891.448, -1971.359, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1896.729, -1971.359, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 1902.000, -1971.359, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1907.260, -1971.588, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1912.520, -1971.588, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1412, 1917.790, -1971.359, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1413, 1923.050, -1971.578, 13.734, 0.250);
	RemoveBuildingForPlayer(playerid, 3625, 1941.979, -1970.697, 14.984, 0.250);
	RemoveBuildingForPlayer(playerid, 4857, 1942.680, -1986.750, 14.897, 0.250);
	RemoveBuildingForPlayer(playerid, 4979, 1942.680, -1986.750, 14.897, 0.250);
	RemoveBuildingForPlayer(playerid, 4850, 1940.187, -2007.300, 15.335, 0.250);
	RemoveBuildingForPlayer(playerid, 4978, 1940.187, -2007.300, 15.335, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 1936.260, -1999.380, 16.343, 0.250);
	RemoveBuildingForPlayer(playerid, 3061, 1868.127, -1984.983, 14.325, 80.000);
	RemoveBuildingForPlayer(playerid, 1410, 814.039, -520.023, 16.023, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 1808.880, -1985.339, 9.671, 0.250);
	RemoveBuildingForPlayer(playerid, 1307, 1923.800, -2042.079, 12.687, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 1951.380, -2039.619, 12.601, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 1951.229, -2017.790, 11.515, 0.250);
	RemoveBuildingForPlayer(playerid, 5017, 1932.430, -2123.409, 15.945, 0.250);
	RemoveBuildingForPlayer(playerid, 4969, 1932.430, -2123.409, 15.945, 0.250);
	RemoveBuildingForPlayer(playerid, 1267, 1935.180, -2140.110, 19.187, 0.250);
	RemoveBuildingForPlayer(playerid, 1261, 1935.180, -2140.110, 19.187, 0.250);
	RemoveBuildingForPlayer(playerid, 4849, 1892.339, -2109.510, 12.546, 0.250);
	RemoveBuildingForPlayer(playerid, 5018, 1892.339, -2109.510, 12.546, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 1944.800, -2136.260, 15.851, 0.250);
	RemoveBuildingForPlayer(playerid, 1532, 1939.599, -2116.760, 12.679, 0.250);
	RemoveBuildingForPlayer(playerid, 1531, 1936.880, -2134.909, 14.218, 0.250);
	
	// East Los Santos
	RemoveBuildingForPlayer(playerid, 700, 2226.520, -1426.770, 23.117, 0.250);
	RemoveBuildingForPlayer(playerid, 1264, 2224.129, -1408.839, 23.398, 0.250);
	RemoveBuildingForPlayer(playerid, 1264, 2224.979, -1408.910, 23.398, 0.250);
	RemoveBuildingForPlayer(playerid, 1230, 2223.879, -1396.800, 23.304, 0.250);
	RemoveBuildingForPlayer(playerid, 1221, 2223.469, -1396.089, 23.375, 0.250);
	RemoveBuildingForPlayer(playerid, 1220, 2222.879, -1396.130, 23.304, 0.250);
	RemoveBuildingForPlayer(playerid, 1220, 2224.860, -1393.959, 23.304, 0.250);
	RemoveBuildingForPlayer(playerid, 1230, 2225.850, -1394.630, 23.304, 0.250);
	RemoveBuildingForPlayer(playerid, 1224, 2225.979, -1396.680, 23.531, 0.250);
	RemoveBuildingForPlayer(playerid, 1221, 2227.949, -1396.849, 23.375, 0.250);
	RemoveBuildingForPlayer(playerid, 3582, 2230.610, -1401.780, 25.640, 0.250);
	RemoveBuildingForPlayer(playerid, 3562, 2230.610, -1401.780, 25.640, 0.250);
	RemoveBuildingForPlayer(playerid, 1221, 2226.850, -1404.739, 23.632, 0.250);
	RemoveBuildingForPlayer(playerid, 3582, 2243.709, -1401.780, 25.640, 0.250);
	RemoveBuildingForPlayer(playerid, 3562, 2243.709, -1401.780, 25.640, 0.250);
	RemoveBuildingForPlayer(playerid, 1221, 2253.219, -1409.890, 23.632, 0.250);
	RemoveBuildingForPlayer(playerid, 3582, 2256.659, -1401.780, 25.640, 0.250);
	RemoveBuildingForPlayer(playerid, 3562, 2256.659, -1401.780, 25.640, 0.250);
	RemoveBuildingForPlayer(playerid, 645, 2237.530, -1395.479, 23.039, 0.250);
	RemoveBuildingForPlayer(playerid, 3593, 2265.080, -1424.479, 23.500, 0.250);
	RemoveBuildingForPlayer(playerid, 3593, 2261.770, -1441.099, 23.500, 0.250);
	RemoveBuildingForPlayer(playerid, 1220, 2222.959, -1469.739, 23.195, 0.250);
	RemoveBuildingForPlayer(playerid, 1230, 2223.629, -1468.750, 23.195, 0.250);
	RemoveBuildingForPlayer(playerid, 1230, 2225.800, -1470.729, 23.195, 0.250);
	RemoveBuildingForPlayer(playerid, 1221, 2225.090, -1471.130, 23.273, 0.250);
	RemoveBuildingForPlayer(playerid, 1220, 2225.129, -1471.729, 23.195, 0.250);
	RemoveBuildingForPlayer(playerid, 1224, 2225.679, -1468.619, 23.429, 0.250);
	RemoveBuildingForPlayer(playerid, 1221, 2225.850, -1466.650, 23.273, 0.250);
	RemoveBuildingForPlayer(playerid, 3582, 2232.399, -1464.800, 25.648, 0.250);
	RemoveBuildingForPlayer(playerid, 3562, 2232.399, -1464.800, 25.648, 0.250);
	RemoveBuildingForPlayer(playerid, 645, 2239.570, -1468.800, 22.687, 0.250);
	RemoveBuildingForPlayer(playerid, 3582, 2247.530, -1464.800, 25.546, 0.250);
	RemoveBuildingForPlayer(playerid, 3562, 2247.530, -1464.800, 25.546, 0.250);
	RemoveBuildingForPlayer(playerid, 1221, 2251.290, -1461.829, 23.632, 0.250);
	RemoveBuildingForPlayer(playerid, 3582, 2263.719, -1464.800, 25.437, 0.250);
	RemoveBuildingForPlayer(playerid, 3562, 2263.719, -1464.800, 25.437, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2267.469, -1470.199, 21.718, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2274.580, -1398.489, 22.507, 0.250);
	RemoveBuildingForPlayer(playerid, 1220, 2256.659, -1456.900, 22.859, 0.250);
	RemoveBuildingForPlayer(playerid, 1230, 2255.979, -1457.910, 22.859, 0.250);
	RemoveBuildingForPlayer(playerid, 16020, -155.179, 2635.510, 63.398, 0.250);
	RemoveBuildingForPlayer(playerid, 1230, 2255.979, -1457.910, 22.859, 0.250);
	RemoveBuildingForPlayer(playerid, 1220, 2256.659, -1456.900, 22.859, 0.250);
	RemoveBuildingForPlayer(playerid, 673, 2227.199, -1444.500, 22.960, 0.250);
	RemoveBuildingForPlayer(playerid, 673, 2229.020, -1411.640, 22.960, 0.250);
	
	// Las Colinas Houses
	RemoveBuildingForPlayer(playerid, 3720, 2053.257, -1061.843, 26.734, 0.250);
	RemoveBuildingForPlayer(playerid, 3720, 2038.359, -1055.390, 26.601, 0.250);
	RemoveBuildingForPlayer(playerid, 3720, 2025.523, -1049.085, 26.546, 0.250);
	RemoveBuildingForPlayer(playerid, 5637, 2043.898, -1138.390, 31.007, 0.250);
	RemoveBuildingForPlayer(playerid, 1307, 2033.929, -1062.992, 23.851, 0.250);
	RemoveBuildingForPlayer(playerid, 3642, 2038.359, -1055.390, 26.601, 0.250);
	RemoveBuildingForPlayer(playerid, 3642, 2025.523, -1049.085, 26.546, 0.250);
	RemoveBuildingForPlayer(playerid, 3642, 2053.257, -1061.843, 26.734, 0.250);
	
	// Glen Park
	RemoveBuildingForPlayer(playerid, 5458, 1995.020, -1198.349, 21.109, 0.250);
	RemoveBuildingForPlayer(playerid, 5460, 1995.020, -1198.349, 21.109, 0.250);
	RemoveBuildingForPlayer(playerid, 708, -755.195, 1086.380, 38.531, 0.250);
	RemoveBuildingForPlayer(playerid, 5640, 1914.030, -1198.329, 19.593, 0.250);
	RemoveBuildingForPlayer(playerid, 5666, 1914.030, -1198.329, 19.593, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2036.699, -1214.189, 21.187, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2029.750, -1227.699, 19.765, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2050.389, -1208.349, 21.812, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2043.260, -1187.079, 21.929, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2038.810, -1168.630, 21.023, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2010.380, -1153.430, 21.062, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 1998.660, -1168.880, 19.578, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 1989.729, -1153.900, 18.109, 0.250);
	RemoveBuildingForPlayer(playerid, 739, 2011.229, -1218.979, 19.125, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2009.739, -1212.520, 17.992, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2018.430, -1206.660, 19.234, 0.250);
	RemoveBuildingForPlayer(playerid, 740, 2025.140, -1244.510, 22.304, 0.250);
	RemoveBuildingForPlayer(playerid, 645, 2004.349, -1240.089, 20.695, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2048.600, -1232.890, 21.625, 0.250);
	RemoveBuildingForPlayer(playerid, 1297, 2040.430, -1256.359, 26.171, 0.250);
	RemoveBuildingForPlayer(playerid, 700, 2046.670, -1160.670, 22.476, 0.250);
	RemoveBuildingForPlayer(playerid, 700, 2040.130, -1158.089, 22.398, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 1880.130, -1152.130, 20.804, 0.250);
	RemoveBuildingForPlayer(playerid, 714, 1906.410, -1152.260, 22.023, 0.250);
	RemoveBuildingForPlayer(playerid, 700, 1989.050, -1171.119, 19.492, 0.250);
	RemoveBuildingForPlayer(playerid, 1525, 1966.9453, -1174.7266, 20.0391, 0.250);
	
	// Little Armenia
	RemoveBuildingForPlayer(playerid, 3699, 2471.670, -1428.131, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 3699, 2490.695, -1428.131, 30.514, 0.250);
	RemoveBuildingForPlayer(playerid, 3699, 2490.695, -1413.897, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 3699, 2471.670, -1413.897, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 3699, 2490.695, -1395.265, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 3699, 2471.670, -1395.265, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 3699, 2490.695, -1379.828, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 3699, 2471.670, -1379.828, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 3699, 2490.695, -1362.656, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 3699, 2471.670, -1362.656, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 17954, 2577.233, -1350.397, 56.539, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2463.209, -1433.116, 27.475, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2463.070, -1374.828, 27.131, 0.250);
	RemoveBuildingForPlayer(playerid, 700, 2462.709, -1386.178, 27.858, 0.250);
	RemoveBuildingForPlayer(playerid, 3698, 2471.670, -1428.131, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 3698, 2471.670, -1413.897, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 3698, 2471.670, -1395.265, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 3698, 2471.670, -1379.828, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 2483.795, -1422.718, 27.992, 0.250);
	RemoveBuildingForPlayer(playerid, 673, 2481.695, -1431.515, 27.000, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 2483.593, -1384.953, 27.959, 0.250);
	RemoveBuildingForPlayer(playerid, 673, 2485.545, -1372.553, 27.444, 0.250);
	RemoveBuildingForPlayer(playerid, 3698, 2490.695, -1428.131, 30.514, 0.250);
	RemoveBuildingForPlayer(playerid, 3698, 2490.695, -1413.897, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 673, 2499.812, -1419.569, 23.992, 0.250);
	RemoveBuildingForPlayer(playerid, 3698, 2490.695, -1395.265, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 3698, 2490.695, -1379.828, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 620, 2496.601, -1369.959, 27.131, 0.250);
	RemoveBuildingForPlayer(playerid, 3698, 2471.670, -1362.656, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 17528, 2484.976, -1357.834, 28.750, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 2484.093, -1357.319, 27.992, 0.250);
	RemoveBuildingForPlayer(playerid, 700, 2481.101, -1360.006, 27.858, 0.250);
	RemoveBuildingForPlayer(playerid, 3698, 2490.695, -1362.656, 30.812, 0.250);
	RemoveBuildingForPlayer(playerid, 17943, 2540.882, -1350.796, 42.601, 0.250);
	
	// Grotti Vinewood
	RemoveBuildingForPlayer(playerid, 5896, 1103.520, -896.929, 63.898, 0.250);
	RemoveBuildingForPlayer(playerid, 5897, 1103.520, -896.929, 63.898, 0.250);
	RemoveBuildingForPlayer(playerid, 1309, 1091.150, -908.687, 58.148, 0.250);
	RemoveBuildingForPlayer(playerid, 1309, 1127.319, -912.679, 58.148, 0.250);
	RemoveBuildingForPlayer(playerid, 1309, 1127.319, -912.679, 58.148, 0.250);
	RemoveBuildingForPlayer(playerid, 1309, 1091.150, -908.687, 58.148, 0.250);
	RemoveBuildingForPlayer(playerid, 5896, 1103.520, -896.929, 63.898, 0.250);
	RemoveBuildingForPlayer(playerid, 5897, 1103.520, -896.929, 63.898, 0.250);
	RemoveBuildingForPlayer(playerid, 5854, 992.5313, -962.7344, 60.7813, 0.250);
	
	// Little Italy
	RemoveBuildingForPlayer(playerid, 4046, 1479.522, -1852.640, 24.514, 0.250);
	RemoveBuildingForPlayer(playerid, 4047, 1531.631, -1852.640, 24.514, 0.250);
	RemoveBuildingForPlayer(playerid, 4217, 1449.250, -1852.569, 22.367, 0.250);
	RemoveBuildingForPlayer(playerid, 4004, 1479.522, -1852.640, 24.514, 0.250);
	RemoveBuildingForPlayer(playerid, 4048, 1531.631, -1852.640, 24.514, 0.250);
	RemoveBuildingForPlayer(playerid, 4927, 1583.687, -1897.843, 19.334, 0.250);
	RemoveBuildingForPlayer(playerid, 4928, 1478.718, -1900.765, 22.398, 0.250);
	RemoveBuildingForPlayer(playerid, 5058, 1457.562, -1895.928, 22.131, 0.250);
	RemoveBuildingForPlayer(playerid, 4894, 1583.687, -1897.843, 19.334, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1442.125, -1906.319, 23.437, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1454.968, -1906.319, 23.437, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1442.147, -1906.281, 22.545, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1454.991, -1906.281, 22.545, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1448.756, -1901.413, 22.593, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1448.734, -1901.453, 23.483, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1440.734, -1899.875, 22.545, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1440.709, -1899.913, 23.437, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1478.631, -1904.156, 21.750, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1478.609, -1904.194, 22.639, 0.250);
	RemoveBuildingForPlayer(playerid, 4887, 1478.718, -1900.765, 22.398, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1485.046, -1904.125, 22.593, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1485.069, -1904.084, 21.702, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1440.709, -1886.937, 23.437, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1440.734, -1886.906, 22.545, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1465.187, -1887.881, 21.639, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1465.163, -1887.921, 22.531, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1472.350, -1887.703, 21.639, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1472.328, -1887.741, 22.531, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1485.069, -1887.631, 21.639, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1485.046, -1887.671, 22.531, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1478.631, -1887.703, 21.639, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1478.609, -1887.741, 22.531, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1449.584, -1886.288, 23.437, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1449.609, -1886.250, 22.545, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1456.656, -1886.250, 22.545, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1456.631, -1886.288, 23.437, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1561.796, -1894.756, 13.756, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1561.819, -1894.718, 12.866, 0.250);
	RemoveBuildingForPlayer(playerid, 625, 1566.178, -1893.100, 13.210, 0.250);
	RemoveBuildingForPlayer(playerid, 625, 1573.453, -1893.100, 13.210, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1573.975, -1894.828, 13.756, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1574.000, -1894.788, 12.866, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1561.796, -1889.890, 13.756, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1561.819, -1889.859, 12.866, 0.250);
	RemoveBuildingForPlayer(playerid, 625, 1566.178, -1887.343, 13.210, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1561.625, -1884.866, 13.756, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1561.647, -1884.828, 12.866, 0.250);
	RemoveBuildingForPlayer(playerid, 625, 1573.453, -1887.343, 13.210, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1574.000, -1889.944, 12.866, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1573.975, -1889.984, 13.756, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1574.015, -1884.953, 13.756, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1574.038, -1884.921, 12.866, 0.250);
	RemoveBuildingForPlayer(playerid, 4046, 1479.522, -1852.640, 24.514, 0.250);
	RemoveBuildingForPlayer(playerid, 4047, 1531.631, -1852.640, 24.514, 0.250);
	RemoveBuildingForPlayer(playerid, 4217, 1449.250, -1852.569, 22.367, 0.250);
	RemoveBuildingForPlayer(playerid, 4004, 1479.522, -1852.640, 24.514, 0.250);
	RemoveBuildingForPlayer(playerid, 4048, 1531.631, -1852.640, 24.514, 0.250);
	RemoveBuildingForPlayer(playerid, 4927, 1583.687, -1897.843, 19.334, 0.250);
	RemoveBuildingForPlayer(playerid, 4928, 1478.718, -1900.765, 22.398, 0.250);
	RemoveBuildingForPlayer(playerid, 5058, 1457.562, -1895.928, 22.131, 0.250);
	RemoveBuildingForPlayer(playerid, 4894, 1583.687, -1897.843, 19.334, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1442.125, -1906.319, 23.437, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1454.968, -1906.319, 23.437, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1442.147, -1906.281, 22.545, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1454.991, -1906.281, 22.545, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1448.756, -1901.413, 22.593, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1448.734, -1901.453, 23.483, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1440.734, -1899.875, 22.545, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1440.709, -1899.913, 23.437, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1478.631, -1904.156, 21.750, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1478.609, -1904.194, 22.639, 0.250);
	RemoveBuildingForPlayer(playerid, 4887, 1478.718, -1900.765, 22.398, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1485.046, -1904.125, 22.593, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1485.069, -1904.084, 21.702, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1440.709, -1886.937, 23.437, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1440.734, -1886.906, 22.545, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1465.187, -1887.881, 21.639, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1465.163, -1887.921, 22.531, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1472.350, -1887.703, 21.639, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1472.328, -1887.741, 22.531, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1485.069, -1887.631, 21.639, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1485.046, -1887.671, 22.531, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1478.631, -1887.703, 21.639, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1478.609, -1887.741, 22.531, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1449.584, -1886.288, 23.437, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1449.609, -1886.250, 22.545, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1456.656, -1886.250, 22.545, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1456.631, -1886.288, 23.437, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1561.796, -1894.756, 13.756, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1561.819, -1894.718, 12.866, 0.250);
	RemoveBuildingForPlayer(playerid, 625, 1566.178, -1893.100, 13.210, 0.250);
	RemoveBuildingForPlayer(playerid, 625, 1573.453, -1893.100, 13.210, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1573.975, -1894.828, 13.756, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1574.000, -1894.788, 12.866, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1561.796, -1889.890, 13.756, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1561.819, -1889.859, 12.866, 0.250);
	RemoveBuildingForPlayer(playerid, 625, 1566.178, -1887.343, 13.210, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1561.625, -1884.866, 13.756, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1561.647, -1884.828, 12.866, 0.250);
	RemoveBuildingForPlayer(playerid, 625, 1573.453, -1887.343, 13.210, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1574.000, -1889.944, 12.866, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1573.975, -1889.984, 13.756, 0.250);
	RemoveBuildingForPlayer(playerid, 642, 1574.015, -1884.953, 13.756, 0.250);
	RemoveBuildingForPlayer(playerid, 643, 1574.038, -1884.921, 12.866, 0.250);
	RemoveBuildingForPlayer(playerid, 4046, 1479.522, -1852.640, 24.514, 0.250);
	RemoveBuildingForPlayer(playerid, 4047, 1531.631, -1852.640, 24.514, 0.250);
	RemoveBuildingForPlayer(playerid, 4004, 1479.522, -1852.640, 24.514, 0.250);
	RemoveBuildingForPlayer(playerid, 4048, 1531.631, -1852.640, 24.514, 0.250);
	RemoveBuildingForPlayer(playerid, 4927, 1583.687, -1897.843, 19.334, 0.250);
	RemoveBuildingForPlayer(playerid, 4928, 1478.718, -1900.765, 22.398, 0.250);
	RemoveBuildingForPlayer(playerid, 4894, 1583.687, -1897.843, 19.334, 0.250);
	RemoveBuildingForPlayer(playerid, 4887, 1478.718, -1900.765, 22.398, 0.250);
	
	// China Town
	RemoveBuildingForPlayer(playerid, 5882, 1316.579, -984.789, 86.890, 0.250);
	RemoveBuildingForPlayer(playerid, 5884, 1316.579, -984.789, 86.890, 0.250);
	RemoveBuildingForPlayer(playerid, 729, 1251.109, -1027.250, 30.953, 0.250);
	RemoveBuildingForPlayer(playerid, 5881, 1310.020, -985.437, 41.906, 0.250);
	RemoveBuildingForPlayer(playerid, 5883, 1310.020, -985.437, 41.906, 0.250);
	RemoveBuildingForPlayer(playerid, 732, 1276.560, -1003.000, 35.843, 0.250);
	RemoveBuildingForPlayer(playerid, 727, 1275.010, -968.031, 38.750, 0.250);
	RemoveBuildingForPlayer(playerid, 1297, 1258.449, -1000.020, 37.390, 0.250);
	RemoveBuildingForPlayer(playerid, 1297, 1267.760, -987.984, 38.734, 0.250);
	RemoveBuildingForPlayer(playerid, 1297, 1258.250, -970.625, 41.015, 0.250);
	RemoveBuildingForPlayer(playerid, 1297, 1266.520, -948.031, 44.257, 0.250);
	RemoveBuildingForPlayer(playerid, 1297, 1268.040, -1017.190, 35.531, 0.250);
	RemoveBuildingForPlayer(playerid, 732, 1338.670, -1022.880, 29.679, 0.250);
	RemoveBuildingForPlayer(playerid, 727, 1321.229, -1023.840, 29.789, 0.250);
	RemoveBuildingForPlayer(playerid, 729, 1294.880, -1024.380, 32.734, 0.250);
	RemoveBuildingForPlayer(playerid, 729, 1304.339, -947.195, 38.828, 0.250);
	RemoveBuildingForPlayer(playerid, 729, 1342.130, -1004.369, 32.710, 0.250);
	RemoveBuildingForPlayer(playerid, 729, 1340.420, -953.382, 35.531, 0.250);
	
	// Recycle Los Santos
	RemoveBuildingForPlayer(playerid, 3593, 2377.409, -1427.989, 23.687, 0.250);
	RemoveBuildingForPlayer(playerid, 3593, 2407.310, -1418.359, 23.687, 0.250);

	
	// Harbor
	/*RemoveBuildingForPlayer(playerid, 5156, 2838.039, -2423.882, 10.960, 0.250);
	RemoveBuildingForPlayer(playerid, 5159, 2838.031, -2371.953, 7.296, 0.250);
	RemoveBuildingForPlayer(playerid, 5160, 2829.953, -2479.570, 5.265, 0.250);
	RemoveBuildingForPlayer(playerid, 5161, 2838.023, -2358.476, 21.312, 0.250);
	RemoveBuildingForPlayer(playerid, 5162, 2838.039, -2423.882, 10.960, 0.250);
	RemoveBuildingForPlayer(playerid, 5163, 2838.039, -2532.773, 17.023, 0.250);
	RemoveBuildingForPlayer(playerid, 5164, 2838.140, -2447.843, 15.726, 0.250);
	RemoveBuildingForPlayer(playerid, 5165, 2838.031, -2520.187, 18.414, 0.250);
	RemoveBuildingForPlayer(playerid, 5166, 2829.953, -2479.570, 5.265, 0.250);
	RemoveBuildingForPlayer(playerid, 5167, 2838.031, -2371.953, 7.296, 0.250);
	RemoveBuildingForPlayer(playerid, 3689, 2685.382, -2366.054, 19.953, 0.250);
	RemoveBuildingForPlayer(playerid, 3707, 2716.234, -2452.593, 20.203, 0.250);
	RemoveBuildingForPlayer(playerid, 3707, 2720.320, -2530.914, 19.976, 0.250);
	RemoveBuildingForPlayer(playerid, 3690, 2685.382, -2366.054, 19.953, 0.250);
	RemoveBuildingForPlayer(playerid, 3710, 2788.156, -2417.789, 16.726, 0.250);
	RemoveBuildingForPlayer(playerid, 3710, 2788.156, -2455.882, 16.726, 0.250);
	RemoveBuildingForPlayer(playerid, 3710, 2788.156, -2493.984, 16.726, 0.250);
	RemoveBuildingForPlayer(playerid, 3708, 2720.320, -2530.914, 19.976, 0.250);
	RemoveBuildingForPlayer(playerid, 3708, 2716.234, -2452.593, 20.203, 0.250);
	RemoveBuildingForPlayer(playerid, 3744, 2771.070, -2372.445, 15.218, 0.250);
	RemoveBuildingForPlayer(playerid, 3744, 2789.210, -2377.625, 15.218, 0.250);
	RemoveBuildingForPlayer(playerid, 3744, 2774.796, -2386.851, 15.218, 0.250);
	RemoveBuildingForPlayer(playerid, 3744, 2771.070, -2520.546, 15.218, 0.250);
	RemoveBuildingForPlayer(playerid, 3744, 2774.796, -2534.953, 15.218, 0.250);
	RemoveBuildingForPlayer(playerid, 3746, 2814.265, -2356.570, 25.515, 0.250);
	RemoveBuildingForPlayer(playerid, 3746, 2814.265, -2521.492, 25.515, 0.250);
	RemoveBuildingForPlayer(playerid, 3758, 2702.398, -2324.257, 3.039, 0.250);
	RemoveBuildingForPlayer(playerid, 5335, 2829.953, -2479.570, 5.265, 0.250);
	RemoveBuildingForPlayer(playerid, 5336, 2829.953, -2479.570, 5.265, 0.250);
	RemoveBuildingForPlayer(playerid, 3770, 2795.828, -2394.242, 14.171, 0.250);
	RemoveBuildingForPlayer(playerid, 3770, 2746.406, -2453.484, 14.078, 0.250);
	RemoveBuildingForPlayer(playerid, 5352, 2838.195, -2488.664, 29.312, 0.250);
	RemoveBuildingForPlayer(playerid, 1278, 2592.492, -2359.421, 26.703, 0.250);
	RemoveBuildingForPlayer(playerid, 1278, 2626.234, -2391.523, 26.703, 0.250);
	RemoveBuildingForPlayer(playerid, 1635, 2704.367, -2487.867, 20.562, 0.250);
	RemoveBuildingForPlayer(playerid, 1306, 2742.265, -2481.515, 19.843, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 2696.023, -2474.859, 16.414, 0.250);
	RemoveBuildingForPlayer(playerid, 5326, 2661.515, -2465.140, 20.109, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 2696.023, -2446.625, 16.414, 0.250);
	RemoveBuildingForPlayer(playerid, 1306, 2742.265, -2416.523, 19.843, 0.250);
	RemoveBuildingForPlayer(playerid, 3578, 2639.195, -2392.820, 13.171, 0.250);
	RemoveBuildingForPlayer(playerid, 3578, 2663.835, -2392.820, 13.171, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 2637.171, -2385.867, 16.414, 0.250);
	RemoveBuildingForPlayer(playerid, 1306, 2669.906, -2394.507, 19.843, 0.250);
	RemoveBuildingForPlayer(playerid, 1278, 2708.406, -2391.523, 26.703, 0.250);
	RemoveBuildingForPlayer(playerid, 3574, 2774.796, -2534.953, 15.218, 0.250);
	RemoveBuildingForPlayer(playerid, 3574, 2771.070, -2520.546, 15.218, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2783.781, -2501.835, 14.695, 0.250);
	RemoveBuildingForPlayer(playerid, 3624, 2788.156, -2493.984, 16.726, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2783.781, -2486.960, 14.656, 0.250);
	RemoveBuildingForPlayer(playerid, 3578, 2747.007, -2480.242, 13.171, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2783.781, -2463.820, 14.632, 0.250);
	RemoveBuildingForPlayer(playerid, 1278, 2773.343, -2479.968, 26.703, 0.250);
	RemoveBuildingForPlayer(playerid, 3624, 2788.156, -2455.882, 16.726, 0.250);
	RemoveBuildingForPlayer(playerid, 3626, 2746.406, -2453.484, 14.078, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2783.781, -2448.476, 14.632, 0.250);
	RemoveBuildingForPlayer(playerid, 1278, 2773.343, -2443.171, 26.703, 0.250);
	RemoveBuildingForPlayer(playerid, 3577, 2744.570, -2436.187, 13.343, 0.250);
	RemoveBuildingForPlayer(playerid, 3577, 2744.570, -2427.320, 13.351, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2783.781, -2425.351, 14.632, 0.250);
	RemoveBuildingForPlayer(playerid, 3574, 2774.796, -2386.851, 15.218, 0.250);
	RemoveBuildingForPlayer(playerid, 3574, 2771.070, -2372.445, 15.218, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2783.781, -2410.210, 14.671, 0.250);
	RemoveBuildingForPlayer(playerid, 3624, 2788.156, -2417.789, 16.726, 0.250);
	RemoveBuildingForPlayer(playerid, 3574, 2789.210, -2377.625, 15.218, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2791.953, -2501.835, 14.632, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2797.515, -2486.828, 14.632, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2791.953, -2486.960, 14.632, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2791.953, -2463.820, 14.632, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2797.515, -2448.343, 14.632, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2791.953, -2448.476, 14.632, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2791.953, -2425.351, 14.671, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2791.953, -2410.210, 14.656, 0.250);
	RemoveBuildingForPlayer(playerid, 5351, 2789.656, -2418.695, 12.664, 0.250);
	RemoveBuildingForPlayer(playerid, 3761, 2797.515, -2410.078, 14.632, 0.250);
	RemoveBuildingForPlayer(playerid, 3626, 2795.828, -2394.242, 14.171, 0.250);
	RemoveBuildingForPlayer(playerid, 3620, 2814.265, -2521.492, 25.515, 0.250);
	RemoveBuildingForPlayer(playerid, 5157, 2838.039, -2532.773, 17.023, 0.250);
	RemoveBuildingForPlayer(playerid, 5154, 2838.140, -2447.843, 15.750, 0.250);
	RemoveBuildingForPlayer(playerid, 3724, 2838.195, -2488.664, 29.312, 0.250);
	RemoveBuildingForPlayer(playerid, 3620, 2814.265, -2356.570, 25.515, 0.250);
	RemoveBuildingForPlayer(playerid, 5155, 2838.023, -2358.476, 21.312, 0.250);
	RemoveBuildingForPlayer(playerid, 3724, 2838.195, -2407.140, 29.312, 0.250);
	RemoveBuildingForPlayer(playerid, 3753, 2702.398, -2324.257, 3.039, 0.250);
	RemoveBuildingForPlayer(playerid, 1278, 2762.757, -2333.382, 26.703, 0.250);
	RemoveBuildingForPlayer(playerid, 1278, 2804.242, -2333.382, 26.703, 0.250);
	RemoveBuildingForPlayer(playerid, 5158, 2837.773, -2334.476, 11.992, 0.250);
	RemoveBuildingForPlayer(playerid, 8378, 1586.257, 1222.703, 19.750, 0.250);
	RemoveBuildingForPlayer(playerid, 8379, 1586.257, 1222.703, 19.750, 0.250);*/
	
	// Liverpool Park
	RemoveBuildingForPlayer(playerid, 17758, 2260.000, -1707.734, 17.171, 0.250);
	RemoveBuildingForPlayer(playerid, 1498, 2229.664, -1720.421, 12.554, 0.250);
	RemoveBuildingForPlayer(playerid, 17515, 2260.000, -1707.734, 17.171, 0.250);
	RemoveBuildingForPlayer(playerid, 17978, 2260.000, -1707.734, 17.171, 0.250);
	
	// West
	RemoveBuildingForPlayer(playerid, 6404, 415.687, -1745.530, 14.132, 0.250);
	RemoveBuildingForPlayer(playerid, 6410, 415.687, -1745.530, 14.132, 0.250);
	
	// Market
	RemoveBuildingForPlayer(playerid, 5857, 1259.439, -1246.810, 17.109, 0.250);
	RemoveBuildingForPlayer(playerid, 5967, 1259.439, -1246.810, 17.109, 0.250);
	RemoveBuildingForPlayer(playerid, 1388, 1238.380, -1258.280, 57.203, 0.250);
	RemoveBuildingForPlayer(playerid, 1391, 1238.380, -1258.270, 44.664, 0.250);
	RemoveBuildingForPlayer(playerid, 1219, 1332.839, -1241.719, 13.414, 0.250);
	
	// East Los Santos (Market)
	RemoveBuildingForPlayer(playerid, 17856, 2492.320, -1484.804, 28.265, 0.250);
	RemoveBuildingForPlayer(playerid, 17853, 2492.320, -1484.804, 28.265, 0.250);
	RemoveBuildingForPlayer(playerid, 17854, 2492.789, -1490.015, 34.640, 0.250);
	
	// Autoservice
	RemoveBuildingForPlayer(playerid, 4179, 1686.881, -1459.959, 16.295, 0.250);
	RemoveBuildingForPlayer(playerid, 4178, 1686.881, -1459.959, 16.295, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 1690.053, -1475.187, 16.420, 0.250);
	
	// Russian
	RemoveBuildingForPlayer(playerid, 3697, 2336.919, -1242.089, 31.429, 0.250);
	RemoveBuildingForPlayer(playerid, 3696, 2336.919, -1242.089, 31.429, 0.250);
	RemoveBuildingForPlayer(playerid, 3697, 2336.919, -1211.420, 31.429, 0.250);
	RemoveBuildingForPlayer(playerid, 3696, 2336.919, -1211.420, 31.429, 0.250);
	RemoveBuildingForPlayer(playerid, 3697, 2336.919, -1273.550, 31.429, 0.250);
	RemoveBuildingForPlayer(playerid, 3696, 2336.919, -1273.550, 31.429, 0.250);
	RemoveBuildingForPlayer(playerid, 17552, 2337.159, -1179.800, 31.984, 0.250);
	RemoveBuildingForPlayer(playerid, 17593, 2337.159, -1179.800, 31.984, 0.250);
	RemoveBuildingForPlayer(playerid, 17928, 2337.159, -1179.800, 31.984, 0.250);
	RemoveBuildingForPlayer(playerid, 17593, 2337.159, -1179.800, 31.984, 0.250);
	RemoveBuildingForPlayer(playerid, 673, 2317.409, -1173.420, 26.320, 0.250);
	RemoveBuildingForPlayer(playerid, 13728, 811.046, -917.906, 67.500, 0.250);
	RemoveBuildingForPlayer(playerid, 17958, 2337.610, -1185.609, 27.937, 0.250);
	RemoveBuildingForPlayer(playerid, 760, 2339.110, -1169.550, 26.960, 0.250);
	RemoveBuildingForPlayer(playerid, 760, 2334.939, -1169.550, 26.960, 0.250);
	RemoveBuildingForPlayer(playerid, 760, 2318.050, -1178.630, 26.781, 0.250);
	RemoveBuildingForPlayer(playerid, 760, 2317.709, -1180.630, 26.781, 0.250);
	RemoveBuildingForPlayer(playerid, 17552, 2337.159, -1179.800, 31.984, 0.250);
	RemoveBuildingForPlayer(playerid, 17593, 2337.159, -1179.800, 31.984, 0.250);
	RemoveBuildingForPlayer(playerid, 673, 2343.629, -1227.130, 26.000, 0.250);
	RemoveBuildingForPlayer(playerid, 673, 2331.060, -1227.119, 26.000, 0.250);
	RemoveBuildingForPlayer(playerid, 1408, 2279.860, 151.813, 26.015, 0.250);
	RemoveBuildingForPlayer(playerid, 3648, 2395.260, -1347.459, 26.320, 0.250);
	RemoveBuildingForPlayer(playerid, 3647, 2395.260, -1347.459, 26.320, 0.250);
}

RemoveBuilding_PD(playerid)
{
	// Los Santos PD HQ
	RemoveBuildingForPlayer(playerid, 3976, 1571.599, -1675.750, 35.679, 0.250);
	RemoveBuildingForPlayer(playerid, 4064, 1571.599, -1675.750, 35.679, 0.250);
	
	// PD - Headquarters
	RemoveBuildingForPlayer(playerid, 3976, 1571.599, -1675.750, 35.679, 0.250);

	// PD - 64th Saints 
	RemoveBuildingForPlayer(playerid, 17740, 2765.083, -1454.437, 29.437, 0.250);
	RemoveBuildingForPlayer(playerid, 17955, 2717.490, -1416.187, 50.429, 0.250);
	RemoveBuildingForPlayer(playerid, 1297, 2742.294, -1450.328, 32.726, 0.250);
	RemoveBuildingForPlayer(playerid, 17555, 2765.083, -1454.437, 29.437, 0.250);
	
	
	// PD - 96th Verona 
	RemoveBuildingForPlayer(playerid, 6073, 1003.890, -1598.039, 17.843, 0.250);
	RemoveBuildingForPlayer(playerid, 6036, 1003.890, -1598.039, 17.843, 0.250);
}

stock RemoveBuilding_FD(playerid)
{
	// FD - HQ
	RemoveBuildingForPlayer(playerid, 6491, 717.484, -1357.303, 20.295, 0.250);
	RemoveBuildingForPlayer(playerid, 1226, 665.812, -1390.241, 16.312, 0.250);
	RemoveBuildingForPlayer(playerid, 1689, 650.835, -1377.663, 21.756, 0.250);
	RemoveBuildingForPlayer(playerid, 1689, 650.835, -1356.584, 21.756, 0.250);
	RemoveBuildingForPlayer(playerid, 1689, 650.835, -1338.241, 21.756, 0.250);
	RemoveBuildingForPlayer(playerid, 1635, 677.195, -1328.875, 25.108, 0.250);
	RemoveBuildingForPlayer(playerid, 1689, 745.585, -1381.109, 25.875, 0.250);
	RemoveBuildingForPlayer(playerid, 1689, 751.335, -1368.031, 25.875, 0.250);
	RemoveBuildingForPlayer(playerid, 6490, 717.484, -1357.303, 20.295, 0.250);
	RemoveBuildingForPlayer(playerid, 6516, 717.687, -1357.281, 18.045, 0.250);
	RemoveBuildingForPlayer(playerid, 1635, 696.195, -1328.875, 25.108, 0.250);
	RemoveBuildingForPlayer(playerid, 1635, 702.234, -1328.875, 25.108, 0.250);
	RemoveBuildingForPlayer(playerid, 1635, 721.210, -1328.875, 25.108, 0.250);
	RemoveBuildingForPlayer(playerid, 1415, 732.851, -1332.897, 12.687, 0.250);
	RemoveBuildingForPlayer(playerid, 1439, 732.726, -1341.772, 12.631, 0.250);
	
	// FD - Downtown
	/*RemoveBuildingForPlayer(playerid, 1265, 1425.914, -1322.273, 12.968, 0.250);
	RemoveBuildingForPlayer(playerid, 1227, 1425.531, -1320.578, 13.367, 0.250);
	RemoveBuildingForPlayer(playerid, 1227, 1425.570, -1317.968, 13.367, 0.250);
	RemoveBuildingForPlayer(playerid, 1265, 1425.851, -1316.226, 12.968, 0.250);
	RemoveBuildingForPlayer(playerid, 1617, 1436.390, -1322.875, 16.421, 0.250);
	RemoveBuildingForPlayer(playerid, 1227, 1439.859, -1323.703, 13.382, 0.250);
	RemoveBuildingForPlayer(playerid, 1265, 1441.554, -1323.312, 12.984, 0.250);*/
}

RemoveBuilding_SD(playerid)
{
	// Los Santos
	RemoveBuildingForPlayer(playerid, 5225, 2375.921, -1946.960, 17.007, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 2369.601, -1962.531, 11.515, 0.250);
	RemoveBuildingForPlayer(playerid, 5177, 2375.921, -1946.960, 17.007, 0.250);
	RemoveBuildingForPlayer(playerid, 5233, 2374.773, -1937.179, 20.195, 0.250);
	RemoveBuildingForPlayer(playerid, 1687, 2376.742, -1947.757, 21.125, 0.250);
	RemoveBuildingForPlayer(playerid, 5371, 2374.773, -1937.179, 20.195, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 2403.789, -1960.421, 11.515, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 2394.375, -1962.640, 11.515, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 2403.976, -1936.757, 11.515, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 2423.398, -1982.640, 11.460, 0.250);
	RemoveBuildingForPlayer(playerid, 5168, 2385.189, -1906.520, 18.445, 0.250);
	RemoveBuildingForPlayer(playerid, 5224, 2385.189, -1906.520, 18.445, 0.250);
	RemoveBuildingForPlayer(playerid, 1415, 2382.020, -1941.040, 12.664, 0.250);
	
	// Blueberry
	RemoveBuildingForPlayer(playerid, 13133, 299.203, -193.625, 3.828, 0.250);
	RemoveBuildingForPlayer(playerid, 13203, 308.093, -168.726, 4.367, 0.250);
	RemoveBuildingForPlayer(playerid, 13398, 307.804, -176.843, 0.570, 0.250);
	RemoveBuildingForPlayer(playerid, 1294, 323.710, -203.148, 5.031, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 322.312, -188.914, 0.703, 0.250);
	RemoveBuildingForPlayer(playerid, 1294, 323.882, -150.773, 5.031, 0.250);
	RemoveBuildingForPlayer(playerid, 1308, 293.625, -152.484, 0.703, 0.250);
	RemoveBuildingForPlayer(playerid, 1294, 291.156, -171.500, 5.031, 0.250);
	RemoveBuildingForPlayer(playerid, 12814, 307.804, -176.843, 0.570, 0.250);
	RemoveBuildingForPlayer(playerid, 13190, 308.093, -168.726, 4.367, 0.250);
	RemoveBuildingForPlayer(playerid, 1495, 293.750, -194.687, 0.765, 0.250);
	RemoveBuildingForPlayer(playerid, 13132, 299.203, -193.625, 3.828, 0.250);
	RemoveBuildingForPlayer(playerid, 1687, 303.937, -194.929, 4.367, 0.250);
	RemoveBuildingForPlayer(playerid, 1691, 297.101, -195.609, 4.945, 0.250);
	RemoveBuildingForPlayer(playerid, 1440, 312.640, -199.875, 1.062, 0.250);
	RemoveBuildingForPlayer(playerid, 1440, 305.132, -188.562, 1.062, 0.250);
	RemoveBuildingForPlayer(playerid, 19436, 315.000, 776489280.000, -174.000, 0.250);
}

RemoveBuilding_Prison(playerid)
{
	RemoveBuildingForPlayer(playerid, 4000, 1787.130, -1565.680, 11.968, 0.250);
}

RemoveBuilding_NPL(playerid)
{
	// Office
	RemoveBuildingForPlayer(playerid, 18535, -2001.031, -2388.083, 38.451, 0.250);
	RemoveBuildingForPlayer(playerid, 785, -1622.843, -2211.593, 21.875, 0.250);
	RemoveBuildingForPlayer(playerid, 785, -1456.484, -2181.076, 0.492, 0.250);
	RemoveBuildingForPlayer(playerid, 785, -1487.818, -2353.232, 4.203, 0.250);
	RemoveBuildingForPlayer(playerid, 785, -1909.271, -2478.052, 29.208, 0.250);
	RemoveBuildingForPlayer(playerid, 785, -1984.937, -2507.851, 29.958, 0.250);
	RemoveBuildingForPlayer(playerid, 785, -1585.396, -2211.638, 8.130, 0.250);
	RemoveBuildingForPlayer(playerid, 791, -1909.271, -2478.052, 29.208, 0.250);
	RemoveBuildingForPlayer(playerid, 18609, -1951.218, -2441.146, 30.708, 0.250);
	RemoveBuildingForPlayer(playerid, 791, -1487.818, -2353.232, 4.203, 0.250);
	RemoveBuildingForPlayer(playerid, 791, -1984.937, -2507.851, 29.958, 0.250);
	RemoveBuildingForPlayer(playerid, 18568, -2061.187, -2365.951, 30.326, 0.250);
	RemoveBuildingForPlayer(playerid, 18566, -2029.552, -2389.039, 30.187, 0.250);
	RemoveBuildingForPlayer(playerid, 18569, -2048.427, -2373.607, 30.708, 0.250);
	RemoveBuildingForPlayer(playerid, 18621, -2016.005, -2431.513, 33.875, 0.250);
	RemoveBuildingForPlayer(playerid, 18567, -2018.250, -2400.539, 30.576, 0.250);
	RemoveBuildingForPlayer(playerid, 18365, -2001.031, -2388.083, 38.451, 0.250);
	RemoveBuildingForPlayer(playerid, 18565, -2000.630, -2372.552, 30.708, 0.250);
	RemoveBuildingForPlayer(playerid, 18258, -1638.359, -2239.427, 30.750, 0.250);
	RemoveBuildingForPlayer(playerid, 18259, -1633.224, -2238.833, 30.388, 0.250);
	RemoveBuildingForPlayer(playerid, 791, -1585.396, -2211.638, 8.130, 0.250);
	RemoveBuildingForPlayer(playerid, 791, -1622.843, -2211.593, 21.875, 0.250);
	RemoveBuildingForPlayer(playerid, 791, -1456.484, -2181.076, 0.492, 0.250);
	RemoveBuildingForPlayer(playerid, 18614, -1358.734, -2064.695, 38.756, 0.250);
	RemoveBuildingForPlayer(playerid, 785, -762.015, -2483.187, 72.273, 0.250);
	RemoveBuildingForPlayer(playerid, 18345, -2016.010, -2431.520, 33.875, 0.250);
	RemoveBuildingForPlayer(playerid, 18489, -2016.010, -2431.520, 33.875, 0.250);
	RemoveBuildingForPlayer(playerid, 18476, -2048.600, -2487.270, 32.304, 0.250);
	RemoveBuildingForPlayer(playerid, 18546, -2048.600, -2487.270, 32.304, 0.250);

	// Forest
	RemoveBuildingForPlayer(playerid, 785, -1622.843, -2211.593, 21.875, 0.250);
	RemoveBuildingForPlayer(playerid, 785, -1457.255, -2213.708, 6.967, 0.250);
	RemoveBuildingForPlayer(playerid, 785, -1456.484, -2181.076, 0.492, 0.250);
	RemoveBuildingForPlayer(playerid, 785, -1487.818, -2353.232, 4.203, 0.250);
	RemoveBuildingForPlayer(playerid, 785, -1585.396, -2211.638, 8.130, 0.250);
	RemoveBuildingForPlayer(playerid, 791, -1487.818, -2353.232, 4.203, 0.250);
	RemoveBuildingForPlayer(playerid, 18258, -1638.359, -2239.427, 30.750, 0.250);
	RemoveBuildingForPlayer(playerid, 18259, -1633.224, -2238.833, 30.388, 0.250);
	RemoveBuildingForPlayer(playerid, 791, -1585.396, -2211.638, 8.130, 0.250);
	RemoveBuildingForPlayer(playerid, 791, -1622.843, -2211.593, 21.875, 0.250);
	RemoveBuildingForPlayer(playerid, 791, -1457.255, -2213.708, 6.967, 0.250);
	RemoveBuildingForPlayer(playerid, 791, -1456.484, -2181.076, 0.492, 0.250);
	RemoveBuildingForPlayer(playerid, 18614, -1358.734, -2064.695, 38.756, 0.250);
	RemoveBuildingForPlayer(playerid, 785, -762.015, -2483.187, 72.273, 0.250);
	RemoveBuildingForPlayer(playerid, 18367, -2172.189, -1830.329, 216.468, 0.250);
	RemoveBuildingForPlayer(playerid, 18437, -2253.370, -1934.199, 253.483, 0.250);
	RemoveBuildingForPlayer(playerid, 18439, -2125.699, -1771.810, 204.085, 0.250);
	RemoveBuildingForPlayer(playerid, 18438, -2172.129, -1847.239, 221.335, 0.250);
	RemoveBuildingForPlayer(playerid, 18436, -2330.030, -1941.550, 295.796, 0.250);
	RemoveBuildingForPlayer(playerid, 694, -2367.979, -1944.000, 305.804, 0.250);
	RemoveBuildingForPlayer(playerid, 784, -2367.979, -1944.000, 305.804, 0.250);
	RemoveBuildingForPlayer(playerid, 18447, -2323.560, -1941.839, 291.117, 0.250);
	RemoveBuildingForPlayer(playerid, 18366, -2146.550, -1803.800, 240.858, 0.250);
	RemoveBuildingForPlayer(playerid, 18551, -2146.550, -1803.800, 240.858, 0.250);
	RemoveBuildingForPlayer(playerid, 694, -2367.979, -1944.000, 305.804, 0.250);
	RemoveBuildingForPlayer(playerid, 784, -2367.979, -1944.000, 305.804, 0.250);
	RemoveBuildingForPlayer(playerid, 18435, -2426.949, -1934.270, 304.468, 0.250);
	RemoveBuildingForPlayer(playerid, 18438, -2172.129, -1847.239, 221.335, 0.250);
	RemoveBuildingForPlayer(playerid, 18367, -2172.189, -1830.329, 216.468, 0.250);
	RemoveBuildingForPlayer(playerid, 694, -2256.879, -1888.680, 242.195, 0.250);
	RemoveBuildingForPlayer(playerid, 784, -2256.879, -1888.680, 242.195, 0.250);
	RemoveBuildingForPlayer(playerid, 791, -2056.189, -1532.069, 119.351, 0.250);
	RemoveBuildingForPlayer(playerid, 785, -2056.189, -1532.069, 119.351, 0.250);
	RemoveBuildingForPlayer(playerid, 694, -2488.020, -1918.199, 300.054, 0.250);
	RemoveBuildingForPlayer(playerid, 784, -2488.020, -1918.199, 300.054, 0.250);
	RemoveBuildingForPlayer(playerid, 18245, -1849.520, -1701.160, 32.953, 0.250);
	RemoveBuildingForPlayer(playerid, 18499, -1849.520, -1701.160, 32.953, 0.250);
	RemoveBuildingForPlayer(playerid, 18249, -1818.810, -1675.540, 27.070, 0.250);
	RemoveBuildingForPlayer(playerid, 18608, -1818.449, -1613.040, 32.789, 0.250);
	RemoveBuildingForPlayer(playerid, 18254, -1813.800, -1615.560, 29.851, 0.250);
	RemoveBuildingForPlayer(playerid, 18555, -1813.800, -1615.560, 29.851, 0.250);
	RemoveBuildingForPlayer(playerid, 18250, -1857.300, -1617.979, 26.812, 0.250);
	RemoveBuildingForPlayer(playerid, 18557, -1857.300, -1617.979, 26.812, 0.250);
	RemoveBuildingForPlayer(playerid, 18253, -1888.800, -1604.130, 23.375, 0.250);
	RemoveBuildingForPlayer(playerid, 18252, -1888.979, -1633.270, 24.484, 0.250);
	RemoveBuildingForPlayer(playerid, 18251, -1907.619, -1666.680, 29.851, 0.250);
	RemoveBuildingForPlayer(playerid, 18556, -1907.619, -1666.680, 29.851, 0.250);
	RemoveBuildingForPlayer(playerid, 18246, -1857.839, -1573.380, 23.312, 0.250);
	RemoveBuildingForPlayer(playerid, 18364, -1835.930, -1647.680, 26.500, 0.250);
	RemoveBuildingForPlayer(playerid, 18400, -1835.930, -1647.680, 26.500, 0.250);
	RemoveBuildingForPlayer(playerid, 18248, -1852.260, -1676.219, 28.617, 0.250);
	RemoveBuildingForPlayer(playerid, 18247, -1874.339, -1680.949, 25.437, 0.250);
	RemoveBuildingForPlayer(playerid, 18560, -1874.339, -1680.949, 25.437, 0.250);
	RemoveBuildingForPlayer(playerid, 18255, -1939.910, -1731.479, 24.945, 0.250);
	RemoveBuildingForPlayer(playerid, 823, -622.351, -2448.909, 330.523, 0.250);
	RemoveBuildingForPlayer(playerid, 825, -631.179, -2444.949, 330.523, 0.250);
	RemoveBuildingForPlayer(playerid, 826, -609.750, -2421.219, 330.523, 0.250);
	RemoveBuildingForPlayer(playerid, 803, -600.320, -2426.590, 329.812, 0.250);
}

RemoveBuilding_Interior(playerid)
{
	RemoveBuildingForPlayer(playerid, 14784, 1281.140, -30.093, 1009.409, 0.250); //< Для гаража
}