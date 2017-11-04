//
//  myRSA.cpp
//  rsa-encryption-xcode
//
//  Created by 葛云祥 on 11/01/2017.
//  Copyright © 2017年 葛云祥. All rights reserved.
//

#include "myRSA.hpp"
#include <iostream>

#define DEBUG true

BigInt lowPrimes[] = {BigInt(3),BigInt(5),BigInt(7),BigInt(11),BigInt(13),BigInt(17),BigInt(19),BigInt(23),BigInt(29),BigInt(31),BigInt(37),BigInt(41),BigInt(43),BigInt(47),BigInt(53),BigInt(59),BigInt(61),BigInt(67),BigInt(71),BigInt(73),BigInt(79),BigInt(83),BigInt(89),BigInt(97),BigInt(101),BigInt(103),BigInt(107),BigInt(109),BigInt(113),BigInt(127),BigInt(131),BigInt(137),BigInt(139),BigInt(149),BigInt(151),BigInt(157),BigInt(163),BigInt(167),BigInt(173),BigInt(179),BigInt(181),BigInt(191),BigInt(193),BigInt(197),BigInt(199),BigInt(211),BigInt(223),BigInt(227),BigInt(229),BigInt(233),BigInt(239),BigInt(241),BigInt(251),BigInt(257),BigInt(263),BigInt(269),BigInt(271),BigInt(277),BigInt(281),BigInt(283),BigInt(293),BigInt(307),BigInt(311),BigInt(313),BigInt(317),BigInt(331),BigInt(337),BigInt(347),BigInt(349),BigInt(353),BigInt(359),BigInt(367),BigInt(373),BigInt(379),BigInt(383),BigInt(389),BigInt(397),BigInt(401),BigInt(409),BigInt(419),BigInt(421),BigInt(431),BigInt(433),BigInt(439),BigInt(443),BigInt(449),BigInt(457),BigInt(461),BigInt(463),BigInt(467),BigInt(479),BigInt(487),BigInt(491),BigInt(499),BigInt(503),BigInt(509),BigInt(521),BigInt(523),BigInt(541),BigInt(547),BigInt(557),BigInt(563),BigInt(569),BigInt(571),BigInt(577),BigInt(587),BigInt(593),BigInt(599),BigInt(601),BigInt(607),BigInt(613),BigInt(617),BigInt(619),BigInt(631),BigInt(641),BigInt(643),BigInt(647),BigInt(653),BigInt(659),BigInt(661),BigInt(673),BigInt(677),BigInt(683),BigInt(691),BigInt(701),BigInt(709),BigInt(719),BigInt(727),BigInt(733),BigInt(739),BigInt(743),BigInt(751),BigInt(757),BigInt(761),BigInt(769),BigInt(773),BigInt(787),BigInt(797),BigInt(809),BigInt(811),BigInt(821),BigInt(823),BigInt(827),BigInt(829),BigInt(839),BigInt(853),BigInt(857),BigInt(859),BigInt(863),BigInt(877),BigInt(881),BigInt(883),BigInt(887),BigInt(907),BigInt(911),BigInt(919),BigInt(929),BigInt(937),BigInt(941),BigInt(947),BigInt(953),BigInt(967),BigInt(971),BigInt(977),BigInt(983),BigInt(991),BigInt(997),BigInt(1009),BigInt(1013),BigInt(1019),BigInt(1021),BigInt(1031),BigInt(1033),BigInt(1039),BigInt(1049),BigInt(1051),BigInt(1061),BigInt(1063),BigInt(1069),BigInt(1087),BigInt(1091),BigInt(1093),BigInt(1097),BigInt(1103),BigInt(1109),BigInt(1117),BigInt(1123),BigInt(1129),BigInt(1151),BigInt(1153),BigInt(1163),BigInt(1171),BigInt(1181),BigInt(1187),BigInt(1193),BigInt(1201),BigInt(1213),BigInt(1217),BigInt(1223),BigInt(1229),BigInt(1231),BigInt(1237),BigInt(1249),BigInt(1259),BigInt(1277),BigInt(1279),BigInt(1283),BigInt(1289),BigInt(1291),BigInt(1297),BigInt(1301),BigInt(1303),BigInt(1307),BigInt(1319),BigInt(1321),BigInt(1327),BigInt(1361),BigInt(1367),BigInt(1373),BigInt(1381),BigInt(1399),BigInt(1409),BigInt(1423),BigInt(1427),BigInt(1429),BigInt(1433),BigInt(1439),BigInt(1447),BigInt(1451),BigInt(1453),BigInt(1459),BigInt(1471),BigInt(1481),BigInt(1483),BigInt(1487),BigInt(1489),BigInt(1493),BigInt(1499),BigInt(1511),BigInt(1523),BigInt(1531),BigInt(1543),BigInt(1549),BigInt(1553),BigInt(1559),BigInt(1567),BigInt(1571),BigInt(1579),BigInt(1583),BigInt(1597),BigInt(1601),BigInt(1607),BigInt(1609),BigInt(1613),BigInt(1619),BigInt(1621),BigInt(1627),BigInt(1637),BigInt(1657),BigInt(1663),BigInt(1667),BigInt(1669),BigInt(1693),BigInt(1697),BigInt(1699),BigInt(1709),BigInt(1721),BigInt(1723),BigInt(1733),BigInt(1741),BigInt(1747),BigInt(1753),BigInt(1759),BigInt(1777),BigInt(1783),BigInt(1787),BigInt(1789),BigInt(1801),BigInt(1811),BigInt(1823),BigInt(1831),BigInt(1847),BigInt(1861),BigInt(1867),BigInt(1871),BigInt(1873),BigInt(1877),BigInt(1879),BigInt(1889),BigInt(1901),BigInt(1907),BigInt(1913),BigInt(1931),BigInt(1933),BigInt(1949),BigInt(1951),BigInt(1973),BigInt(1979),BigInt(1987),BigInt(1993),BigInt(1997),BigInt(1999),BigInt(2003),BigInt(2011),BigInt(2017),BigInt(2027),BigInt(2029),BigInt(2039),BigInt(2053),BigInt(2063),BigInt(2069),BigInt(2081),BigInt(2083),BigInt(2087),BigInt(2089),BigInt(2099),BigInt(2111),BigInt(2113),BigInt(2129),BigInt(2131),BigInt(2137),BigInt(2141),BigInt(2143),BigInt(2153),BigInt(2161),BigInt(2179),BigInt(2203),BigInt(2207),BigInt(2213),BigInt(2221),BigInt(2237),BigInt(2239),BigInt(2243),BigInt(2251),BigInt(2267),BigInt(2269),BigInt(2273),BigInt(2281),BigInt(2287),BigInt(2293),BigInt(2297),BigInt(2309),BigInt(2311),BigInt(2333),BigInt(2339),BigInt(2341),BigInt(2347),BigInt(2351),BigInt(2357),BigInt(2371),BigInt(2377),BigInt(2381),BigInt(2383),BigInt(2389),BigInt(2393),BigInt(2399),BigInt(2411),BigInt(2417),BigInt(2423),BigInt(2437),BigInt(2441),BigInt(2447),BigInt(2459),BigInt(2467),BigInt(2473),BigInt(2477),BigInt(2503),BigInt(2521),BigInt(2531),BigInt(2539),BigInt(2543),BigInt(2549),BigInt(2551),BigInt(2557),BigInt(2579),BigInt(2591),BigInt(2593),BigInt(2609),BigInt(2617),BigInt(2621),BigInt(2633),BigInt(2647),BigInt(2657),BigInt(2659),BigInt(2663),BigInt(2671),BigInt(2677),BigInt(2683),BigInt(2687),BigInt(2689),BigInt(2693),BigInt(2699),BigInt(2707),BigInt(2711),BigInt(2713),BigInt(2719),BigInt(2729),BigInt(2731),BigInt(2741),BigInt(2749),BigInt(2753),BigInt(2767),BigInt(2777),BigInt(2789),BigInt(2791),BigInt(2797),BigInt(2801),BigInt(2803),BigInt(2819),BigInt(2833),BigInt(2837),BigInt(2843),BigInt(2851),BigInt(2857),BigInt(2861),BigInt(2879),BigInt(2887),BigInt(2897),BigInt(2903),BigInt(2909),BigInt(2917),BigInt(2927),BigInt(2939),BigInt(2953),BigInt(2957),BigInt(2963),BigInt(2969),BigInt(2971),BigInt(2999),BigInt(3001),BigInt(3011),BigInt(3019),BigInt(3023),BigInt(3037),BigInt(3041),BigInt(3049),BigInt(3061),BigInt(3067),BigInt(3079),BigInt(3083),BigInt(3089),BigInt(3109),BigInt(3119),BigInt(3121),BigInt(3137),BigInt(3163),BigInt(3167),BigInt(3169),BigInt(3181),BigInt(3187),BigInt(3191),BigInt(3203),BigInt(3209),BigInt(3217),BigInt(3221),BigInt(3229),BigInt(3251),BigInt(3253),BigInt(3257),BigInt(3259),BigInt(3271),BigInt(3299),BigInt(3301),BigInt(3307),BigInt(3313),BigInt(3319),BigInt(3323),BigInt(3329),BigInt(3331),BigInt(3343),BigInt(3347),BigInt(3359),BigInt(3361),BigInt(3371),BigInt(3373),BigInt(3389),BigInt(3391),BigInt(3407),BigInt(3413),BigInt(3433),BigInt(3449),BigInt(3457),BigInt(3461),BigInt(3463),BigInt(3467),BigInt(3469),BigInt(3491),BigInt(3499),BigInt(3511),BigInt(3517),BigInt(3527),BigInt(3529),BigInt(3533),BigInt(3539),BigInt(3541),BigInt(3547),BigInt(3557),BigInt(3559),BigInt(3571),BigInt(3581),BigInt(3583),BigInt(3593),BigInt(3607),BigInt(3613),BigInt(3617),BigInt(3623),BigInt(3631),BigInt(3637),BigInt(3643),BigInt(3659),BigInt(3671),BigInt(3673),BigInt(3677),BigInt(3691),BigInt(3697),BigInt(3701),BigInt(3709),BigInt(3719),BigInt(3727),BigInt(3733),BigInt(3739),BigInt(3761),BigInt(3767),BigInt(3769),BigInt(3779),BigInt(3793),BigInt(3797),BigInt(3803),BigInt(3821),BigInt(3823),BigInt(3833),BigInt(3847),BigInt(3851),BigInt(3853),BigInt(3863),BigInt(3877),BigInt(3881),BigInt(3889),BigInt(3907),BigInt(3911),BigInt(3917),BigInt(3919),BigInt(3923),BigInt(3929),BigInt(3931),BigInt(3943),BigInt(3947),BigInt(3967),BigInt(3989),BigInt(4001),BigInt(4003),BigInt(4007),BigInt(4013),BigInt(4019),BigInt(4021),BigInt(4027),BigInt(4049),BigInt(4051),BigInt(4057),BigInt(4073),BigInt(4079),BigInt(4091),BigInt(4093),BigInt(4099),BigInt(4111),BigInt(4127),BigInt(4129),BigInt(4133),BigInt(4139),BigInt(4153),BigInt(4157),BigInt(4159),BigInt(4177),BigInt(4201),BigInt(4211),BigInt(4217),BigInt(4219),BigInt(4229),BigInt(4231),BigInt(4241),BigInt(4243),BigInt(4253),BigInt(4259),BigInt(4261),BigInt(4271),BigInt(4273),BigInt(4283),BigInt(4289),BigInt(4297),BigInt(4327),BigInt(4337),BigInt(4339),BigInt(4349),BigInt(4357),BigInt(4363),BigInt(4373),BigInt(4391),BigInt(4397),BigInt(4409),BigInt(4421),BigInt(4423),BigInt(4441),BigInt(4447),BigInt(4451),BigInt(4457),BigInt(4463),BigInt(4481),BigInt(4483),BigInt(4493),BigInt(4507),BigInt(4513),BigInt(4517),BigInt(4519),BigInt(4523),BigInt(4547),BigInt(4549),BigInt(4561),BigInt(4567),BigInt(4583),BigInt(4591),BigInt(4597),BigInt(4603),BigInt(4621),BigInt(4637),BigInt(4639),BigInt(4643),BigInt(4649),BigInt(4651),BigInt(4657),BigInt(4663),BigInt(4673),BigInt(4679),BigInt(4691),BigInt(4703),BigInt(4721),BigInt(4723),BigInt(4729),BigInt(4733),BigInt(4751),BigInt(4759),BigInt(4783),BigInt(4787),BigInt(4789),BigInt(4793),BigInt(4799),BigInt(4801),BigInt(4813),BigInt(4817),BigInt(4831),BigInt(4861),BigInt(4871),BigInt(4877),BigInt(4889),BigInt(4903),BigInt(4909),BigInt(4919),BigInt(4931),BigInt(4933),BigInt(4937),BigInt(4943),BigInt(4951),BigInt(4957),BigInt(4967),BigInt(4969),BigInt(4973),BigInt(4987),BigInt(4993),BigInt(4999),BigInt(5003),BigInt(5009),BigInt(5011),BigInt(5021),BigInt(5023),BigInt(5039),BigInt(5051),BigInt(5059),BigInt(5077),BigInt(5081),BigInt(5087),BigInt(5099),BigInt(5101),BigInt(5107),BigInt(5113),BigInt(5119),BigInt(5147),BigInt(5153),BigInt(5167),BigInt(5171),BigInt(5179),BigInt(5189),BigInt(5197),BigInt(5209),BigInt(5227),BigInt(5231),BigInt(5233),BigInt(5237),BigInt(5261),BigInt(5273),BigInt(5279),BigInt(5281),BigInt(5297),BigInt(5303),BigInt(5309),BigInt(5323),BigInt(5333),BigInt(5347),BigInt(5351),BigInt(5381),BigInt(5387),BigInt(5393),BigInt(5399),BigInt(5407),BigInt(5413),BigInt(5417),BigInt(5419),BigInt(5431),BigInt(5437),BigInt(5441),BigInt(5443),BigInt(5449),BigInt(5471),BigInt(5477),BigInt(5479),BigInt(5483),BigInt(5501),BigInt(5503),BigInt(5507),BigInt(5519),BigInt(5521),BigInt(5527),BigInt(5531),BigInt(5557),BigInt(5563),BigInt(5569),BigInt(5573),BigInt(5581),BigInt(5591),BigInt(5623),BigInt(5639),BigInt(5641),BigInt(5647),BigInt(5651),BigInt(5653),BigInt(5657),BigInt(5659),BigInt(5669),BigInt(5683),BigInt(5689),BigInt(5693),BigInt(5701),BigInt(5711),BigInt(5717),BigInt(5737),BigInt(5741),BigInt(5743),BigInt(5749),BigInt(5779),BigInt(5783),BigInt(5791),BigInt(5801),BigInt(5807),BigInt(5813),BigInt(5821),BigInt(5827),BigInt(5839),BigInt(5843),BigInt(5849),BigInt(5851),BigInt(5857),BigInt(5861),BigInt(5867),BigInt(5869),BigInt(5879),BigInt(5881),BigInt(5897),BigInt(5903),BigInt(5923),BigInt(5927),BigInt(5939),BigInt(5953),BigInt(5981),BigInt(5987),BigInt(6007),BigInt(6011),BigInt(6029),BigInt(6037),BigInt(6043),BigInt(6047),BigInt(6053),BigInt(6067),BigInt(6073),BigInt(6079),BigInt(6089),BigInt(6091),BigInt(6101),BigInt(6113),BigInt(6121),BigInt(6131),BigInt(6133),BigInt(6143),BigInt(6151),BigInt(6163),BigInt(6173),BigInt(6197),BigInt(6199),BigInt(6203),BigInt(6211),BigInt(6217),BigInt(6221),BigInt(6229),BigInt(6247),BigInt(6257),BigInt(6263),BigInt(6269),BigInt(6271),BigInt(6277),BigInt(6287),BigInt(6299),BigInt(6301),BigInt(6311),BigInt(6317),BigInt(6323),BigInt(6329),BigInt(6337),BigInt(6343),BigInt(6353),BigInt(6359),BigInt(6361),BigInt(6367),BigInt(6373),BigInt(6379),BigInt(6389),BigInt(6397),BigInt(6421),BigInt(6427),BigInt(6449),BigInt(6451),BigInt(6469),BigInt(6473),BigInt(6481),BigInt(6491),BigInt(6521),BigInt(6529),BigInt(6547),BigInt(6551),BigInt(6553),BigInt(6563),BigInt(6569),BigInt(6571),BigInt(6577),BigInt(6581),BigInt(6599),BigInt(6607),BigInt(6619),BigInt(6637),BigInt(6653),BigInt(6659),BigInt(6661),BigInt(6673),BigInt(6679),BigInt(6689),BigInt(6691),BigInt(6701),BigInt(6703),BigInt(6709),BigInt(6719),BigInt(6733),BigInt(6737),BigInt(6761),BigInt(6763),BigInt(6779),BigInt(6781),BigInt(6791),BigInt(6793),BigInt(6803),BigInt(6823),BigInt(6827),BigInt(6829),BigInt(6833),BigInt(6841),BigInt(6857),BigInt(6863),BigInt(6869),BigInt(6871),BigInt(6883),BigInt(6899),BigInt(6907),BigInt(6911),BigInt(6917),BigInt(6947),BigInt(6949),BigInt(6959),BigInt(6961),BigInt(6967),BigInt(6971),BigInt(6977),BigInt(6983),BigInt(6991),BigInt(6997),BigInt(7001),BigInt(7013),BigInt(7019),BigInt(7027),BigInt(7039),BigInt(7043),BigInt(7057),BigInt(7069),BigInt(7079),BigInt(7103),BigInt(7109),BigInt(7121),BigInt(7127),BigInt(7129),BigInt(7151),BigInt(7159),BigInt(7177),BigInt(7187),BigInt(7193),BigInt(7207),BigInt(7211),BigInt(7213),BigInt(7219),BigInt(7229),BigInt(7237),BigInt(7243),BigInt(7247),BigInt(7253),BigInt(7283),BigInt(7297),BigInt(7307),BigInt(7309),BigInt(7321),BigInt(7331),BigInt(7333),BigInt(7349),BigInt(7351),BigInt(7369),BigInt(7393),BigInt(7411),BigInt(7417),BigInt(7433),BigInt(7451),BigInt(7457),BigInt(7459),BigInt(7477),BigInt(7481),BigInt(7487),BigInt(7489),BigInt(7499),BigInt(7507),BigInt(7517),BigInt(7523),BigInt(7529),BigInt(7537),BigInt(7541),BigInt(7547),BigInt(7549),BigInt(7559),BigInt(7561),BigInt(7573),BigInt(7577),BigInt(7583),BigInt(7589),BigInt(7591),BigInt(7603),BigInt(7607),BigInt(7621),BigInt(7639),BigInt(7643),BigInt(7649),BigInt(7669),BigInt(7673),BigInt(7681),BigInt(7687),BigInt(7691),BigInt(7699),BigInt(7703),BigInt(7717),BigInt(7723),BigInt(7727),BigInt(7741),BigInt(7753),BigInt(7757),BigInt(7759),BigInt(7789),BigInt(7793),BigInt(7817),BigInt(7823),BigInt(7829),BigInt(7841),BigInt(7853),BigInt(7867),BigInt(7873),BigInt(7877),BigInt(7879),BigInt(7883),BigInt(7901),BigInt(7907),BigInt(7919),BigInt(7927),BigInt(7933),BigInt(7937),BigInt(7949),BigInt(7951),BigInt(7963),BigInt(7993),BigInt(8009),BigInt(8011),BigInt(8017),BigInt(8039),BigInt(8053),BigInt(8059),BigInt(8069),BigInt(8081),BigInt(8087),BigInt(8089),BigInt(8093),BigInt(8101),BigInt(8111),BigInt(8117),BigInt(8123),BigInt(8147),BigInt(8161),BigInt(8167),BigInt(8171),BigInt(8179),BigInt(8191),BigInt(8209),BigInt(8219),BigInt(8221),BigInt(8231),BigInt(8233),BigInt(8237),BigInt(8243),BigInt(8263),BigInt(8269),BigInt(8273),BigInt(8287),BigInt(8291),BigInt(8293),BigInt(8297),BigInt(8311),BigInt(8317),BigInt(8329),BigInt(8353),BigInt(8363),BigInt(8369),BigInt(8377),BigInt(8387),BigInt(8389),BigInt(8419),BigInt(8423),BigInt(8429),BigInt(8431),BigInt(8443),BigInt(8447),BigInt(8461),BigInt(8467),BigInt(8501),BigInt(8513),BigInt(8521),BigInt(8527),BigInt(8537),BigInt(8539),BigInt(8543),BigInt(8563),BigInt(8573),BigInt(8581),BigInt(8597),BigInt(8599),BigInt(8609),BigInt(8623),BigInt(8627),BigInt(8629),BigInt(8641),BigInt(8647),BigInt(8663),BigInt(8669),BigInt(8677),BigInt(8681),BigInt(8689),BigInt(8693),BigInt(8699),BigInt(8707),BigInt(8713),BigInt(8719),BigInt(8731),BigInt(8737),BigInt(8741),BigInt(8747),BigInt(8753),BigInt(8761),BigInt(8779),BigInt(8783),BigInt(8803),BigInt(8807),BigInt(8819),BigInt(8821),BigInt(8831),BigInt(8837),BigInt(8839),BigInt(8849),BigInt(8861),BigInt(8863),BigInt(8867),BigInt(8887),BigInt(8893),BigInt(8923),BigInt(8929),BigInt(8933),BigInt(8941),BigInt(8951),BigInt(8963),BigInt(8969),BigInt(8971),BigInt(8999),BigInt(9001),BigInt(9007),BigInt(9011),BigInt(9013),BigInt(9029),BigInt(9041),BigInt(9043),BigInt(9049),BigInt(9059),BigInt(9067),BigInt(9091),BigInt(9103),BigInt(9109),BigInt(9127),BigInt(9133),BigInt(9137),BigInt(9151),BigInt(9157),BigInt(9161),BigInt(9173),BigInt(9181),BigInt(9187),BigInt(9199),BigInt(9203),BigInt(9209),BigInt(9221),BigInt(9227),BigInt(9239),BigInt(9241),BigInt(9257),BigInt(9277),BigInt(9281),BigInt(9283),BigInt(9293),BigInt(9311),BigInt(9319),BigInt(9323),BigInt(9337),BigInt(9341),BigInt(9343),BigInt(9349),BigInt(9371),BigInt(9377),BigInt(9391),BigInt(9397),BigInt(9403),BigInt(9413),BigInt(9419),BigInt(9421),BigInt(9431),BigInt(9433),BigInt(9437),BigInt(9439),BigInt(9461),BigInt(9463),BigInt(9467),BigInt(9473),BigInt(9479),BigInt(9491),BigInt(9497),BigInt(9511),BigInt(9521),BigInt(9533),BigInt(9539),BigInt(9547),BigInt(9551),BigInt(9587),BigInt(9601),BigInt(9613),BigInt(9619),BigInt(9623),BigInt(9629),BigInt(9631),BigInt(9643),BigInt(9649),BigInt(9661),BigInt(9677),BigInt(9679),BigInt(9689),BigInt(9697),BigInt(9719),BigInt(9721),BigInt(9733),BigInt(9739),BigInt(9743),BigInt(9749),BigInt(9767),BigInt(9769),BigInt(9781),BigInt(9787),BigInt(9791),BigInt(9803),BigInt(9811),BigInt(9817),BigInt(9829),BigInt(9833),BigInt(9839),BigInt(9851),BigInt(9857),BigInt(9859),BigInt(9871),BigInt(9883),BigInt(9887)}; // total 1219

bool RabinMiller(BigInt p) {
    //if(DEBUG) std::cout << "Inside rabin miller" << std::endl;
    BigInt s = p - ONE_BIG_INT;
    BigInt t(0);
    while(s % TWO_BIG_INT == ZERO_BIG_INT) {
        s = s / TWO_BIG_INT;
        t = t + ONE_BIG_INT;
    }
    for(int k = 0; k < 8; k++) {
        //if(DEBUG) std::cout << "rabin miller try: " << k << std::endl;
        BigInt a = getRandom(TWO_BIG_INT, p-ONE_BIG_INT);
        // if(DEBUG) std::cout << "random generated " << std::endl;
        // if(DEBUG) std::cout << "a " << a.toHex() << std::endl;
        // if(DEBUG) std::cout << "s " << s.toHex() << std::endl;
        // if(DEBUG) std::cout << "p " << p.toHex() << std::endl;
        BigInt v = pow(a, s, p);
        //if(DEBUG) std::cout << "a: " << a.toHex() << std::endl; // 87AD3D06606BD9
        //if(DEBUG) std::cout << "s: " << s.toHex() << std::endl; // 1B48460234FAE92ED937BEDA515BA1A1
        //if(DEBUG) std::cout << "p: " << p.toHex() << std::endl; // DA423011A7D74976C9BDF6D28ADD0D09
        //if(DEBUG) std::cout << "v: " << v.toHex() << std::endl; // 82551BCB6C2E991011AE998CE5D1D1FA
        //if(DEBUG) std::cout << "power calculated " << std::endl;
        if(v != ONE_BIG_INT) {
            BigInt i(0);
            while(v != (p-ONE_BIG_INT)) {
                if(i == t-ONE_BIG_INT)
                    return false;
                else {
                    i.increaseOne();
                    v = (v*v) % p;
                }
            }
        }
    }
    return true;
}

bool checkIfPrime(BigInt p) {
    if(p % TWO_BIG_INT == 0) return false;
    for(int i = 0; i < 400; i++) {// change this number to first filter out more low primes
        BigInt thisPrime = lowPrimes[i];
        // if(DEBUG) std::cout << lowPrimes[i].toHex() << std::endl;
        if(p == thisPrime) return true;
        if(p % thisPrime == ZERO_BIG_INT) {
            // if(DEBUG) std::cout << "???" << thisPrime.toHex() << std::endl;
            return false;
        }
    }
    return RabinMiller(p);
}

BigInt generatePrimeWithBitLength(int bitLength) {
    BigInt result(0);
    BigInt randInt;
    int r = 100; // try 100 times
    for(r = 100; r > 0; r--) {
        if(DEBUG) std::cout << "generate prime left try: " << r << std::endl;
        randInt = getRandom(pow(TWO_BIG_INT, BigInt(bitLength-1)), pow(TWO_BIG_INT, BigInt(bitLength)));
        if(DEBUG) std::cout << "generated randInt: " << randInt.toHex() << std::endl;
        if(checkIfPrime(randInt)) return randInt;
    }
    return result;
}

// Test functions
BigInt generateOrderedPrime(int bitLength) {
    BigInt result(0);
    BigInt randInt;
    BigInt start = pow(TWO_BIG_INT, BigInt(bitLength-1)), end = pow(TWO_BIG_INT, BigInt(bitLength));
    for(BigInt idx = start; idx < end; idx = idx + ONE_BIG_INT){
        //if(DEBUG) std::cout << "Trial: " << idx.toHex() << std::endl;
        if(checkIfPrime(idx)) return idx;
    }
    return result;
}

void listLowPrimes() {
    for(int i = 0; i < 167; i++) {
        std::cout << lowPrimes[i].toHex() << std::endl;
    }
}
