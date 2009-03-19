-- phpMyAdmin SQL Dump
-- version 2.11.3deb1ubuntu1.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Mar 19, 2009 at 04:25 PM
-- Server version: 5.0.51
-- PHP Version: 5.2.4-2ubuntu5.5

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Database: `feature_db`
--

-- --------------------------------------------------------

--
-- Table structure for table `k_centers`
--

CREATE TABLE IF NOT EXISTS `k_centers` (
  `Center_ID` int(11) NOT NULL auto_increment,
  `Sigma` double default '0',
  `Coeff1` double NOT NULL,
  `Coeff2` double NOT NULL,
  `Coeff3` double NOT NULL,
  `Coeff4` double NOT NULL,
  `Coeff5` double NOT NULL,
  `Coeff6` double NOT NULL,
  `Coeff7` double NOT NULL,
  `Coeff8` double NOT NULL,
  `Coeff9` double NOT NULL,
  `Coeff10` double NOT NULL,
  `Coeff11` double NOT NULL,
  `Coeff12` double NOT NULL,
  `Coeff13` double NOT NULL,
  `Coeff14` double NOT NULL,
  `Coeff15` double NOT NULL,
  `Coeff16` double NOT NULL,
  `Coeff17` double NOT NULL,
  `Coeff18` double NOT NULL,
  `Coeff19` double NOT NULL,
  `Coeff20` double NOT NULL,
  `Coeff21` double NOT NULL,
  `Coeff22` double NOT NULL,
  `Coeff23` double NOT NULL,
  `Coeff24` double NOT NULL,
  `Coeff25` double NOT NULL,
  `Coeff26` double NOT NULL,
  `Coeff27` double NOT NULL,
  `Coeff28` double NOT NULL,
  `Coeff29` double NOT NULL,
  `Coeff30` double NOT NULL,
  `Coeff31` double NOT NULL,
  `Coeff32` double NOT NULL,
  `Coeff33` double NOT NULL,
  `Coeff34` double NOT NULL,
  `Coeff35` double NOT NULL,
  `Coeff36` double NOT NULL,
  `Coeff37` double NOT NULL,
  `Coeff38` double NOT NULL,
  `Coeff39` double NOT NULL,
  `Coeff40` double NOT NULL,
  `Coeff41` double NOT NULL,
  `Coeff42` double NOT NULL,
  `Coeff43` double NOT NULL,
  `Coeff44` double NOT NULL,
  `Coeff45` double NOT NULL,
  `Coeff46` double NOT NULL,
  `Coeff47` double NOT NULL,
  `Coeff48` double NOT NULL,
  `Coeff49` double NOT NULL,
  `Coeff50` double NOT NULL,
  `Coeff51` double NOT NULL,
  `Coeff52` double NOT NULL,
  `Coeff53` double NOT NULL,
  `Coeff54` double NOT NULL,
  `Coeff55` double NOT NULL,
  `Coeff56` double NOT NULL,
  `Coeff57` double NOT NULL,
  `Coeff58` double NOT NULL,
  `Coeff59` double NOT NULL,
  `Coeff60` double NOT NULL,
  `Coeff61` double NOT NULL,
  `Coeff62` double NOT NULL,
  `Coeff63` double NOT NULL,
  `Coeff64` double NOT NULL,
  `Coeff65` double NOT NULL,
  `Coeff66` double NOT NULL,
  `Coeff67` double NOT NULL,
  `Coeff68` double NOT NULL,
  `Coeff69` double NOT NULL,
  `Coeff70` double NOT NULL,
  `Coeff71` double NOT NULL,
  `Coeff72` double NOT NULL,
  `Coeff73` double NOT NULL,
  `Coeff74` double NOT NULL,
  `Coeff75` double NOT NULL,
  `Coeff76` double NOT NULL,
  `Coeff77` double NOT NULL,
  `Coeff78` double NOT NULL,
  `Coeff79` double NOT NULL,
  `Coeff80` double NOT NULL,
  `Coeff81` double NOT NULL,
  `Coeff82` double NOT NULL,
  `Coeff83` double NOT NULL,
  `Coeff84` double NOT NULL,
  `Coeff85` double NOT NULL,
  `Coeff86` double NOT NULL,
  `Coeff87` double NOT NULL,
  `Coeff88` double NOT NULL,
  `Coeff89` double NOT NULL,
  `Coeff90` double NOT NULL,
  `Coeff91` double NOT NULL,
  `Coeff92` double NOT NULL,
  `Coeff93` double NOT NULL,
  `Coeff94` double NOT NULL,
  `Coeff95` double NOT NULL,
  `Coeff96` double NOT NULL,
  `Coeff97` double NOT NULL,
  `Coeff98` double NOT NULL,
  `Coeff99` double NOT NULL,
  `Coeff100` double NOT NULL,
  `Coeff101` double NOT NULL,
  `Coeff102` double NOT NULL,
  `Coeff103` double NOT NULL,
  `Coeff104` double NOT NULL,
  `Coeff105` double NOT NULL,
  `Coeff106` double NOT NULL,
  `Coeff107` double NOT NULL,
  `Coeff108` double NOT NULL,
  `Coeff109` double NOT NULL,
  `Coeff110` double NOT NULL,
  `Coeff111` double NOT NULL,
  `Coeff112` double NOT NULL,
  `Coeff113` double NOT NULL,
  `Coeff114` double NOT NULL,
  `Coeff115` double NOT NULL,
  `Coeff116` double NOT NULL,
  `Coeff117` double NOT NULL,
  `Coeff118` double NOT NULL,
  `Coeff119` double NOT NULL,
  `Coeff120` double NOT NULL,
  `Coeff121` double NOT NULL,
  `Coeff122` double NOT NULL,
  `Coeff123` double NOT NULL,
  `Coeff124` double NOT NULL,
  `Coeff125` double NOT NULL,
  `Coeff126` double NOT NULL,
  `Coeff127` double NOT NULL,
  `Coeff128` double NOT NULL,
  PRIMARY KEY  (`Center_ID`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=11 ;

--
-- Dumping data for table `k_centers`
--

INSERT INTO `k_centers` (`Center_ID`, `Sigma`, `Coeff1`, `Coeff2`, `Coeff3`, `Coeff4`, `Coeff5`, `Coeff6`, `Coeff7`, `Coeff8`, `Coeff9`, `Coeff10`, `Coeff11`, `Coeff12`, `Coeff13`, `Coeff14`, `Coeff15`, `Coeff16`, `Coeff17`, `Coeff18`, `Coeff19`, `Coeff20`, `Coeff21`, `Coeff22`, `Coeff23`, `Coeff24`, `Coeff25`, `Coeff26`, `Coeff27`, `Coeff28`, `Coeff29`, `Coeff30`, `Coeff31`, `Coeff32`, `Coeff33`, `Coeff34`, `Coeff35`, `Coeff36`, `Coeff37`, `Coeff38`, `Coeff39`, `Coeff40`, `Coeff41`, `Coeff42`, `Coeff43`, `Coeff44`, `Coeff45`, `Coeff46`, `Coeff47`, `Coeff48`, `Coeff49`, `Coeff50`, `Coeff51`, `Coeff52`, `Coeff53`, `Coeff54`, `Coeff55`, `Coeff56`, `Coeff57`, `Coeff58`, `Coeff59`, `Coeff60`, `Coeff61`, `Coeff62`, `Coeff63`, `Coeff64`, `Coeff65`, `Coeff66`, `Coeff67`, `Coeff68`, `Coeff69`, `Coeff70`, `Coeff71`, `Coeff72`, `Coeff73`, `Coeff74`, `Coeff75`, `Coeff76`, `Coeff77`, `Coeff78`, `Coeff79`, `Coeff80`, `Coeff81`, `Coeff82`, `Coeff83`, `Coeff84`, `Coeff85`, `Coeff86`, `Coeff87`, `Coeff88`, `Coeff89`, `Coeff90`, `Coeff91`, `Coeff92`, `Coeff93`, `Coeff94`, `Coeff95`, `Coeff96`, `Coeff97`, `Coeff98`, `Coeff99`, `Coeff100`, `Coeff101`, `Coeff102`, `Coeff103`, `Coeff104`, `Coeff105`, `Coeff106`, `Coeff107`, `Coeff108`, `Coeff109`, `Coeff110`, `Coeff111`, `Coeff112`, `Coeff113`, `Coeff114`, `Coeff115`, `Coeff116`, `Coeff117`, `Coeff118`, `Coeff119`, `Coeff120`, `Coeff121`, `Coeff122`, `Coeff123`, `Coeff124`, `Coeff125`, `Coeff126`, `Coeff127`, `Coeff128`) VALUES
(1, 114.821, 17.6378, 14.5323, 14.7773, 18.8212, 22.184, 22.3102, 22.9586, 19.2106, 52.0012, 25.6545, 14.8893, 13.2694, 14.0634, 16.9502, 25.8852, 41.1079, 72.5407, 42.5005, 22.6177, 13.9728, 9.03062, 8.05629, 14.7643, 41.253, 29.2515, 27.9889, 25.6059, 22.9381, 16.5104, 10.3474, 11.6765, 18.4179, 22.0526, 25.7188, 35.4995, 37.9882, 26.9245, 17.794, 14.7253, 15.5834, 65.918, 27.5298, 31.7569, 38.2558, 27.339, 19.1098, 20.802, 37.8766, 115.827, 45.6455, 17.2827, 11.6907, 8.12187, 6.88432, 12.021, 62.0606, 40.0535, 25.0909, 24.0804, 28.8658, 26.6944, 17.7389, 14.4145, 20.6239, 24.1358, 42.918, 59.6604, 44.6406, 19.9369, 9.54036, 8.7275, 12.614, 36.2598, 58.2147, 88.292, 66.0724, 23.2539, 7.97526, 6.18342, 10.5017, 103.341, 76.875, 47.6629, 19.8719, 9.19054, 9.77575, 12.8277, 30.9242, 35.8617, 21.8342, 17.3211, 20.2815, 23.9409, 24.8685, 24.0384, 25.3573, 24.0244, 36.0458, 44.0399, 29.0736, 13.7346, 9.54006, 13.3099, 16.8024, 23.2833, 41.4565, 55.09, 36.5348, 18.2623, 14.373, 16.6737, 16.5568, 28.9805, 38.906, 41.8834, 26.5929, 17.3585, 16.7761, 18.3659, 19.524, 21.8673, 23.5088, 24.4952, 18.3755, 16.1463, 17.0718, 17.781, 18.1404),
(2, 115.782, 24.9046, 16.5752, 13.0995, 10.6072, 14.6022, 28.9692, 40.3863, 32.9265, 25.2088, 16.4964, 15.6656, 14.4668, 18.8175, 36.7618, 52.8386, 40.5036, 29.6206, 19.1872, 17.3164, 17.3057, 18.4547, 27.4689, 42.0898, 40.2127, 22.9452, 18.4428, 17.468, 17.569, 16.5939, 17.9227, 24.8309, 25.8945, 23.9476, 13.9686, 10.2085, 11.7447, 21.8418, 43.4689, 55.0581, 38.3738, 32.6677, 10.1967, 6.83057, 10.2695, 28.2263, 68.8152, 85.6137, 54.2405, 105.409, 32.5252, 13.7165, 10.8137, 9.92269, 20.7002, 47.9168, 76.9532, 36.7417, 25.9085, 25.0163, 27.0767, 25.8507, 21.5338, 18.6206, 22.5868, 20.7734, 15.5435, 15.5681, 20.8137, 28.9719, 37.5225, 35.4665, 25.6069, 58.7456, 35.348, 23.4529, 25.7402, 33.6751, 39.7992, 30.2755, 25.8587, 117.847, 63.2616, 14.0646, 8.30924, 9.24259, 13.1007, 18.5847, 47.6315, 38.989, 20.383, 15.0059, 19.5983, 29.6357, 33.2693, 27.7808, 26.096, 16.3812, 17.4271, 21.3205, 24.1653, 23.5986, 21.1528, 17.6034, 15.63, 46.2787, 37.3146, 25.4209, 19.4259, 16.7183, 16.21, 18.4813, 26.875, 68.8086, 39.2106, 15.6724, 8.96209, 10.471, 15.3978, 25.6911, 44.5782, 28.088, 18.4576, 12.1173, 11.2663, 18.3172, 24.8241, 27.9938, 28.4645),
(3, 106.494, 19.5618, 11.5189, 8.24098, 9.21923, 17.6171, 14.666, 12.6119, 13.1629, 70.5939, 24.9634, 9.45049, 7.38609, 9.63681, 9.31568, 12.4602, 28.6359, 122.61, 48.5675, 7.83228, 3.73097, 5.28506, 3.71265, 6.79851, 37.0329, 76.4851, 35.2762, 12.3291, 7.66485, 7.89239, 3.98941, 5.86434, 24.1274, 26.1843, 14.8077, 10.3569, 11.931, 20.6497, 14.9287, 12.5137, 15.1929, 96.7516, 26.2813, 10.3546, 9.92358, 13.2421, 12.3592, 13.8234, 31.3217, 138.119, 44.2101, 8.26875, 5.38294, 6.37235, 3.92301, 5.32828, 44.2553, 92.3074, 35.1663, 10.5246, 7.53606, 8.97968, 5.7676, 7.05467, 28.7192, 25.7819, 15.1998, 12.0089, 14.3744, 20.089, 12.4974, 10.943, 15.0418, 97.5821, 31.1955, 12.9811, 12.1408, 13.0693, 9.77218, 9.66657, 25.9837, 138.38, 43.9765, 5.47853, 4.04665, 6.2862, 5.14339, 7.59616, 44.1803, 91.3097, 27.9851, 7.12994, 5.26045, 8.50258, 7.63537, 11.1777, 35.9127, 19.148, 14.0572, 13.4445, 14.8266, 16.8746, 8.71265, 8.21294, 11.0698, 70.3226, 27.7816, 12.8955, 9.72954, 9.54522, 6.77619, 9.10103, 25.4828, 120.029, 35.6966, 6.22782, 3.45535, 4.88294, 4.09817, 9.3526, 49.7707, 74.5129, 23.0844, 5.17258, 3.74156, 7.21437, 8.14969, 13.8011, 36.4554),
(4, 110.504, 26.1303, 14.932, 10.8956, 11.632, 19.8014, 13.5944, 11.5872, 13.4113, 60.1983, 24.1189, 13.1303, 12.2871, 18.0695, 11.7554, 12.2754, 25.0315, 87.3221, 37.4026, 16.3122, 20.3809, 27.1018, 7.96658, 6.55526, 25.1014, 17.2955, 10.2374, 11.597, 37.665, 85.9772, 24.8788, 6.86783, 6.76149, 34.0934, 17.6327, 11.8473, 14.2062, 24.03, 14.5913, 12.5321, 16.9138, 75.6969, 19.0919, 9.7049, 15.1857, 29.3255, 22.9058, 18.1622, 30.147, 120.927, 30.0201, 8.22104, 16.5477, 32.4216, 11.7535, 8.3984, 42.5051, 21.2697, 7.19863, 7.64603, 46.3528, 118.024, 39.932, 6.14394, 6.45575, 33.2024, 17.5822, 13.8811, 15.6741, 23.8826, 14.7243, 12.1671, 17.4565, 75.6464, 30.2241, 18.2526, 21.444, 29.3627, 17.1512, 10.1789, 19.3069, 120.665, 42.2704, 8.17433, 10.7455, 32.0592, 16.7991, 8.87619, 30.1261, 20.9878, 5.97076, 5.89366, 38.5883, 118.744, 48.0266, 8.39423, 7.42005, 25.7945, 14.0543, 12.7607, 14.6134, 20.5085, 11.681, 11.0877, 14.2324, 58.6381, 25.5887, 13.7953, 12.5367, 18.7239, 12.4831, 12.779, 22.812, 87.2184, 25.0839, 7.46639, 7.92556, 26.7148, 19.9339, 16.286, 36.4569, 17.0744, 6.60729, 6.86327, 25.1223, 87.64, 38.9677, 11.6145, 10.0429),
(5, 116.145, 25.1369, 16.2386, 14.8652, 25.1819, 39.9982, 18.0956, 9.41286, 12.7041, 30.1446, 13.766, 12.6322, 31.2466, 68.8695, 29.7853, 12.8643, 16.2885, 93.0119, 37.0346, 12.6974, 11.0052, 17.7216, 11.3767, 10.8413, 31.7905, 38.2135, 21.6689, 15.0928, 18.3501, 24.223, 11.7332, 9.32404, 15.8711, 33.7191, 20.8502, 17.3078, 30.2383, 48.9979, 21.2239, 10.6444, 17.2092, 39.072, 9.634, 9.27443, 42.558, 107.524, 50.6753, 13.3038, 15.6046, 129.419, 36.373, 8.3268, 9.84655, 20.3149, 13.2404, 9.87933, 43.9672, 47.623, 20.3639, 15.3443, 25.1547, 37.6631, 18.5917, 9.60582, 15.2799, 33.7185, 17.524, 11.5553, 24.0925, 49.1292, 27.0368, 16.46, 20.6922, 38.0184, 15.4364, 14.1804, 53.8711, 107.683, 40.2711, 9.57917, 9.25237, 128.862, 43.615, 10.2015, 13.8006, 20.4781, 9.82603, 9.15406, 37.4983, 46.8202, 14.7363, 9.62052, 18.6061, 36.5256, 24.8695, 16.5035, 21.4833, 24.7587, 11.6147, 9.79969, 18.8352, 40.1194, 24.2074, 15.7522, 16.4897, 28.3348, 14.5314, 13.0695, 30.1568, 69.3078, 32.151, 13.9035, 13.6135, 88.8606, 30.3323, 10.7188, 11.4515, 18.241, 11.5329, 13.5577, 37.9985, 36.9718, 15.2273, 8.99632, 10.8784, 23.5957, 18.3727, 16.3268, 22.3158),
(6, 114.527, 16.0413, 21.6392, 25.7741, 19.7358, 16.9503, 16.4361, 14.016, 12.5904, 25.0241, 34.9681, 35.0437, 25.1154, 17.8798, 15.2139, 14.3702, 15.6813, 38.659, 65.7298, 53.0985, 24.2506, 11.9554, 9.6253, 11.1873, 15.6238, 25.7392, 50.5666, 59.0316, 29.6247, 11.1205, 7.26265, 9.73735, 13.2681, 26.6054, 26.8078, 26.1982, 21.4964, 19.4247, 17.859, 16.8533, 19.9997, 52.4494, 28.3036, 23.9048, 27.9867, 33.4639, 30.2991, 23.2732, 25.9967, 113.25, 81.8958, 39.9961, 15.3877, 7.83163, 8.23645, 11.3904, 38.5346, 35.0593, 52.1521, 62.6955, 45.616, 25.953, 16.9539, 12.1139, 14.2398, 27.2575, 20.2087, 17.2639, 18.1732, 18.909, 20.194, 24.2807, 26.7867, 54.2988, 27.0136, 24.8955, 31.9877, 33.7127, 25.7422, 19.0021, 25.963, 116.284, 41.6404, 13.7419, 9.29669, 7.84127, 12.6702, 30.7575, 76.1157, 37.9018, 17.1524, 14.622, 19.7142, 27.2717, 40.687, 51.9464, 46.7226, 18.8244, 14.4678, 15.3916, 17.3392, 17.1211, 16.6729, 21.5657, 20.7063, 31.4771, 19.1012, 16.6633, 17.4843, 18.563, 21.2666, 27.7666, 32.5506, 49.0681, 19.8765, 12.737, 11.1843, 11.6476, 19.2777, 41.5687, 61.1509, 27.8557, 14.9006, 10.6364, 8.83916, 12.7958, 27.0021, 48.8334, 45.2711),
(7, 115.683, 28.8107, 15.0688, 9.51928, 9.8203, 19.0404, 26.6042, 28.2705, 29.9081, 76.5728, 40.7742, 13.3939, 8.16176, 11.1816, 16.5236, 25.4663, 46.6339, 50.9389, 37.5903, 23.1366, 18.2043, 21.2638, 20.1757, 20.1939, 27.8487, 17.8444, 16.4813, 19.2919, 21.4097, 26.4207, 25.0935, 19.448, 16.827, 41.4601, 18.0225, 12.1213, 17.2132, 27.53, 31.9223, 25.9116, 25.8701, 122.853, 66.0493, 13.0418, 7.29888, 8.98366, 12.4068, 16.1066, 46.4081, 57.0137, 34.0174, 23.4384, 24.5878, 40.6893, 49.3155, 32.2552, 25.2116, 22.6157, 15.8436, 14.4588, 16.846, 28.4009, 40.4138, 37.5356, 27.6572, 37.8503, 27.121, 25.534, 25.9499, 24.6757, 20.0763, 13.5932, 17.9871, 111.122, 32.6095, 12.5916, 9.04526, 9.49598, 20.5495, 44.0129, 78.2499, 27.9896, 9.91644, 7.57177, 10.2413, 35.1221, 76.2335, 80.5187, 49.1141, 27.557, 18.6706, 11.7175, 10.1824, 20.2665, 37.872, 47.5728, 37.207, 22.364, 22.3452, 22.4122, 19.7547, 16.6521, 14.8591, 16.195, 17.3725, 31.9033, 25.1393, 22.3329, 18.8318, 17.3998, 21.3731, 30.0908, 32.8511, 22.9231, 21.7667, 21.4839, 16.6751, 19.1039, 30.1982, 39.3441, 31.3669, 25.5723, 21.9617, 17.4124, 10.8091, 12.7563, 21.2094, 29.2914, 27.2611),
(8, 112.694, 17.4442, 6.91057, 7.11815, 25.0604, 85.7258, 33.9938, 9.91906, 9.64426, 86.9037, 26.3548, 8.27448, 9.54308, 29.4834, 18.5359, 13.6867, 32.0042, 49.8424, 22.3695, 13.2601, 17.2578, 31.1208, 15.7131, 12.3163, 19.3104, 28.6178, 14.0617, 11.8832, 15.0444, 23.6886, 13.4178, 11.2957, 15.1488, 21.9386, 6.25979, 5.49576, 36.4106, 115.625, 44.2931, 7.52121, 7.11619, 123.494, 41.5157, 8.97128, 11.8916, 34.439, 15.7559, 7.4344, 26.999, 62.1772, 25.9458, 18.8655, 29.1407, 48.2037, 21.7706, 9.05973, 14.3146, 36.9693, 18.6834, 13.3789, 16.4112, 28.2229, 16.0875, 12.1374, 17.8492, 22.2063, 7.11978, 7.00326, 42.9827, 116.409, 37.265, 5.43473, 6.3985, 123.714, 27.2784, 7.20268, 15.0587, 34.123, 12.0738, 7.3205, 40.8734, 63.5548, 15.3149, 9.99445, 21.8362, 49.2291, 28.2901, 15.2196, 24.5013, 36.498, 19.2598, 13.0666, 16.656, 28.0189, 15.4298, 11.3567, 17.2901, 17.9931, 9.72846, 9.86227, 34.0659, 86.983, 25.1057, 6.77611, 7.28394, 90.4625, 33.2555, 13.0917, 18.127, 28.9011, 8.53884, 7.03362, 26.1204, 50.9752, 19.2888, 12.1057, 16.4768, 31.97, 15.971, 11.5343, 21.5894, 27.9161, 14.8913, 11.3287, 13.3802, 23.904, 14.8198, 10.9044, 13.7846),
(9, 106.038, 54.4594, 17.3635, 5.64361, 5.24817, 10.6633, 11.1606, 16.9285, 33.2849, 117.543, 36.2513, 6.15461, 2.97039, 4.03223, 4.6229, 11.9738, 52.5296, 79.1525, 34.6745, 13.0265, 7.27358, 6.64701, 5.14177, 8.26468, 28.1192, 16.9767, 14.5891, 13.923, 12.734, 12.0673, 6.94156, 7.13836, 9.73113, 69.1184, 21.7898, 7.57678, 8.45388, 13.3181, 12.528, 15.1714, 31.8168, 140.94, 51.6499, 6.10089, 2.98716, 3.94785, 4.15907, 9.06184, 49.586, 106.937, 40.1166, 15.4227, 8.57023, 8.65514, 6.32678, 7.61714, 29.9392, 22.5697, 15.3873, 13.2896, 12.2746, 13.4468, 8.77411, 8.21803, 12.0996, 70.1169, 29.6326, 13.6101, 12.8729, 13.9437, 8.56316, 7.71619, 23.4423, 142.238, 47.7987, 8.02883, 4.2217, 3.81184, 2.76546, 4.87107, 51.3077, 111.064, 31.8698, 9.4565, 7.16221, 8.51232, 7.40645, 10.9007, 36.7476, 22.4544, 13.8097, 9.98401, 9.6174, 13.745, 11.5438, 10.4879, 12.2267, 54.8257, 32.506, 16.7372, 11.8952, 10.7904, 5.26494, 5.60089, 18.0886, 123.247, 53.9914, 11.3407, 4.51074, 3.64282, 2.27909, 5.09775, 37.5288, 83.9534, 29.093, 8.14806, 5.14177, 6.55739, 7.32914, 11.8003, 33.9389, 16.3019, 9.73061, 6.97982, 6.73113, 12.2178, 13.1724, 13.0333, 13.1606),
(10, 116.616, 29.2746, 17.4176, 13.5044, 11.6663, 13.8478, 19.1884, 28.4314, 29.2598, 46.5925, 29.5206, 23.1285, 19.6434, 17.9581, 17.7147, 24.6596, 34.1562, 20.9627, 19.8896, 27.4278, 33.2892, 37.261, 25.6916, 21.6543, 18.7842, 23.1508, 18.0409, 19.7891, 21.1056, 21.2077, 16.8835, 19.554, 20.538, 42.6132, 17.1127, 12.8873, 17.5733, 22.4954, 27.2217, 30.9499, 31.8703, 117.339, 58.1208, 29.665, 19.5384, 12.833, 9.8997, 16.4636, 43.9846, 28.3654, 27.9192, 48.6713, 73.019, 67.3345, 24.6237, 10.2831, 10.5767, 29.6869, 25.7368, 29.2257, 31.9633, 29.7905, 18.0663, 16.8259, 21.8578, 44.6065, 30.6636, 30.7781, 31.645, 24.9068, 15.6723, 11.7651, 17.233, 123.685, 52.0043, 17.9216, 12.2543, 12.3903, 9.85015, 11.1066, 51.1356, 43.8245, 18.6626, 25.0764, 53.1676, 72.1864, 36.4357, 16.7915, 21.6265, 26.1822, 26.6867, 33.0265, 38.4426, 36.0474, 18.1651, 11.708, 15.5287, 33.0859, 33.4034, 31.2788, 23.2184, 15.8571, 9.32478, 10.1658, 16.0938, 74.2873, 49.5337, 26.2247, 15.7143, 13.4217, 10.2399, 13.0211, 33.2555, 35.783, 23.9196, 21.9923, 29.2063, 40.2689, 24.2235, 18.3706, 24.276, 19.0267, 19.0551, 22.632, 27.6073, 30.9378, 19.8817, 14.1185, 12.9822);
