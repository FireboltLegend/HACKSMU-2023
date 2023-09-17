#include "fxp32_16.h"
fxp32_16 fxp_sqrt(fxp32_16 x)
{

	if (x <= 0)
	{
		return 0;
	}
	static unsigned int lut[64] = {
		// add 64 bit values for the fxp32_31 sqrt values for the first 6 bits of the number.
		2147483647, 2130900514, 2114695712, 2098855072, 2083365155, 2068213207, 2053387115, 2038875363,
		2024666999, 2010751597, 1997119226, 1983760419, 1970666148, 1957827795, 1945237132, 1932886295,
		1920767766, 1908874353, 1897199171, 1885735627, 1874477403, 1863418443, 1852552937, 1841875309,
		1831380208, 1821062491, 1810917217, 1800939636, 1791125178, 1781469446, 1771968208, 1762617387,
		1753413056, 1744351429, 1735428857, 1726641819, 1717986918, 1709460876, 1701060526, 1692782810,
		1684624773, 1676583558, 1668656405, 1660840641, 1653133683, 1645533028, 1638036255, 1630641020,
		1623345050, 1616146145, 1609042172, 1602031061, 1595110808, 1588279467, 1581535150, 1574876026,
		1568300314, 1561806289, 1555392273, 1549056637, 1542797796, 1536614213, 1530504391, 1524466875,
	};
	unsigned int m = x;
	unsigned char exp = 15;
	while (m < 2147483648)
	{
		exp--;
		m <<= 1;
	}
	unsigned long long mantissa = m;
	unsigned long long approx_rsqrt = lut[(mantissa >> 25) & 63];
	approx_rsqrt = (approx_rsqrt * (3221225472 - ((((approx_rsqrt * approx_rsqrt) >> 31) * mantissa) >> 32))) >> 31; // newton raphson in fxp32_31
	approx_rsqrt = (approx_rsqrt * (3221225472 - ((((approx_rsqrt * approx_rsqrt) >> 31) * mantissa) >> 32))) >> 31; // newton raphson in fxp32_31
	unsigned long long sqrt = (approx_rsqrt * mantissa) >> 31;														 // compute the sqrt of the mantissa to 24 bits.
	if ((exp & 1) == 1)
	{
		sqrt = (sqrt * 3037000500) >> 31; // multiply by sqrt(2)
	}
	exp >>= 1; // divide exp by 2;
	sqrt >>= (14 - exp);
	sqrt++;
	return sqrt >> 1;
}

static void fxp_cordic_tan_helper(fxp32_16 *sinV, fxp32_16 *cosV, fxp32_16 *tanV, fxp32_16 arg)
{
	int angle = arg << 14;
	static fxp32_16 arctanOfInversePowerOf2[16] = {
		268435456, 158466702, 83729453, 42502378,
		21333665, 10677232, 5339919, 2670122,
		1335081, 667543, 333772, 166886,
		83443, 41721, 20860, 10430};
	int x = 652032874, y = 0, temp;
	for (char i = 0; i < 16; i++)
	{
		if (angle > 0)
		{
			temp = x;
			x = x - (y >> i);
			y = y + (temp >> i);
			angle -= arctanOfInversePowerOf2[i];
		}
		else
		{
			temp = x;
			x = x + (y >> i);
			y = y - (temp >> i);
			angle += arctanOfInversePowerOf2[i];
		}
	}
	if (sinV)
	{
		*sinV = (fxp32_16)(y >> 14);
	}
	if (cosV)
	{
		*cosV = (fxp32_16)(x >> 14);
	}
	if (tanV)
	{
		*tanV = (fxp32_16)(((((unsigned long long)y) << 30) / x) >> 14);
	}
}

static inline fxp32_16 evalPolySin(fxp32_16 x)
{
	long long val = x;
	return fxp_mul(x, fxp_mul(x, fxp_mul(x, fxp_mul(x, 183835) - 415226) + 13824) + 204987);
}

static fxp32_16 fxp_lut_sin(fxp32_16 angle){
	static unsigned short lut[65] = {
		 0,     804,   1607,  2410,  3211,
		 4011,  4807,  5601,  6392,  7179,
		 7961,  8739,  9511,  10278, 11038,
		 11792, 12539, 13278, 14009, 14732,
		 15446, 16150, 16845, 17530, 18204,
		 18867, 19519, 20159, 20787, 21402,
		 22004, 22594, 23169, 23731, 24278,
		 24811, 25329, 25831, 26318, 26789,
		 27244, 27683, 28105, 28510, 28897,
		 29268, 29621, 29955, 30272, 30571,
		 30851, 31113, 31356, 31580, 31785,
		 31970, 32137, 32284, 32412, 32520,
		 32609, 32678, 32727, 32757, 32767,
	};
	fxp32_16 upper = lut[(angle >> 10) + 1];
	fxp32_16 lower = lut[angle >> 10];
	angle &= 0x3ff;
	return fxp_lerp(lower, upper, angle);
}
static fxp32_16 fxp_lut_tan(fxp32_16 angle)
{
	static unsigned int lut[65] = {
	0, 1608, 3219, 4834,
	6454, 8083, 9721, 11371,
	13035, 14716, 16415, 18136,
	19880, 21650, 23449, 25280,
	27145, 29050, 30996, 32988,
	35029, 37125, 39280, 41500,
	43789, 46155, 48604, 51144,
	53784, 56531, 59398, 62395,
	65535, 68834, 72307, 75974,
	79855, 83976, 88365, 93053,
	98081, 103492, 109340, 115687,
	122609, 130197, 138564, 147846,
	158217, 169895, 183160, 198380,
	216043, 236816, 261634, 291845,
	329471, 377693, 441807, 531351,
	665398, 888449, 1334015, 2669640,
	0
	};

	fxp32_16 upper = lut[(angle >> 10) + 1];
	fxp32_16 lower = lut[angle >> 10];
	angle &= 0x3ff;
	return fxp_lerp(lower, upper, angle);
}
fxp32_16 fxp_sin(fxp32_16 x, char precision)
{ // 1: lut. 2: polynomial sin, 3: cordic sin
	unsigned int angle = x & (0x1ffff);
	long long sign = 65536;
	if (angle < 32768)
	{
		// change nothing
	}
	else if (angle < 65536)
	{
		angle = 65536 - angle;
	}
	else if (angle < 98304)
	{
		angle = angle - 65536;
		sign = -65536;
	}
	else
	{
		angle = 131072 - angle;
		sign = -65536;
	}
	fxp32_16 value;
	if (precision == 1)
	{
		value = fxp_lut_sin(angle);
	}
	else if (precision == 2)
	{
		value = evalPolySin(angle);
	}
	else
	{
		fxp_cordic_tan_helper(&value, (void*)(0), (void*)(0), angle);
	}
	return fxp_mul(sign, value);
}

fxp32_16 fxp_tan(fxp32_16 x, char precision)
{										// precision value of 1 is lut. Error around 1%, precision value 2 is the cordic tangent, a full 16 bits is computed.(4.5 digits of accuracy)
	unsigned int angle = x & (0x1ffff); // lsb 17
	long long sign = 65536;
	if (angle < 32768)
	{
	}
	else if (angle < 65536)
	{
		sign = -65536;
		angle = 65536 - angle;
	}
	else if (angle < 98304)
	{
		angle = angle - 65536;
	}
	else
	{
		angle = 131072 - angle;
		sign = -65536;
	}
	fxp32_16 value;
	if (precision == 1)
	{
		value = fxp_lut_tan(angle);
	}
	else
	{
		fxp_cordic_tan_helper((void*)(0), (void*)(0), &value, angle);
	}
	return fxp_mul(sign, value);
}
