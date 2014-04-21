#include <stdio.h>
#include "utf8.h"
#define YYCTYPE unsigned char
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Mn:
	/*!re2c
		re2c:yyfill:enable = 0;
		Mn = [\u0300-\u036f\u0483-\u0487\u0591-\u05bd\u05bf-\u05bf\u05c1-\u05c2\u05c4-\u05c5\u05c7-\u05c7\u0610-\u061a\u064b-\u065f\u0670-\u0670\u06d6-\u06dc\u06df-\u06e4\u06e7-\u06e8\u06ea-\u06ed\u0711-\u0711\u0730-\u074a\u07a6-\u07b0\u07eb-\u07f3\u0816-\u0819\u081b-\u0823\u0825-\u0827\u0829-\u082d\u0859-\u085b\u0900-\u0902\u093a-\u093a\u093c-\u093c\u0941-\u0948\u094d-\u094d\u0951-\u0957\u0962-\u0963\u0981-\u0981\u09bc-\u09bc\u09c1-\u09c4\u09cd-\u09cd\u09e2-\u09e3\u0a01-\u0a02\u0a3c-\u0a3c\u0a41-\u0a42\u0a47-\u0a48\u0a4b-\u0a4d\u0a51-\u0a51\u0a70-\u0a71\u0a75-\u0a75\u0a81-\u0a82\u0abc-\u0abc\u0ac1-\u0ac5\u0ac7-\u0ac8\u0acd-\u0acd\u0ae2-\u0ae3\u0b01-\u0b01\u0b3c-\u0b3c\u0b3f-\u0b3f\u0b41-\u0b44\u0b4d-\u0b4d\u0b56-\u0b56\u0b62-\u0b63\u0b82-\u0b82\u0bc0-\u0bc0\u0bcd-\u0bcd\u0c3e-\u0c40\u0c46-\u0c48\u0c4a-\u0c4d\u0c55-\u0c56\u0c62-\u0c63\u0cbc-\u0cbc\u0cbf-\u0cbf\u0cc6-\u0cc6\u0ccc-\u0ccd\u0ce2-\u0ce3\u0d41-\u0d44\u0d4d-\u0d4d\u0d62-\u0d63\u0dca-\u0dca\u0dd2-\u0dd4\u0dd6-\u0dd6\u0e31-\u0e31\u0e34-\u0e3a\u0e47-\u0e4e\u0eb1-\u0eb1\u0eb4-\u0eb9\u0ebb-\u0ebc\u0ec8-\u0ecd\u0f18-\u0f19\u0f35-\u0f35\u0f37-\u0f37\u0f39-\u0f39\u0f71-\u0f7e\u0f80-\u0f84\u0f86-\u0f87\u0f8d-\u0f97\u0f99-\u0fbc\u0fc6-\u0fc6\u102d-\u1030\u1032-\u1037\u1039-\u103a\u103d-\u103e\u1058-\u1059\u105e-\u1060\u1071-\u1074\u1082-\u1082\u1085-\u1086\u108d-\u108d\u109d-\u109d\u135d-\u135f\u1712-\u1714\u1732-\u1734\u1752-\u1753\u1772-\u1773\u17b7-\u17bd\u17c6-\u17c6\u17c9-\u17d3\u17dd-\u17dd\u180b-\u180d\u18a9-\u18a9\u1920-\u1922\u1927-\u1928\u1932-\u1932\u1939-\u193b\u1a17-\u1a18\u1a56-\u1a56\u1a58-\u1a5e\u1a60-\u1a60\u1a62-\u1a62\u1a65-\u1a6c\u1a73-\u1a7c\u1a7f-\u1a7f\u1b00-\u1b03\u1b34-\u1b34\u1b36-\u1b3a\u1b3c-\u1b3c\u1b42-\u1b42\u1b6b-\u1b73\u1b80-\u1b81\u1ba2-\u1ba5\u1ba8-\u1ba9\u1be6-\u1be6\u1be8-\u1be9\u1bed-\u1bed\u1bef-\u1bf1\u1c2c-\u1c33\u1c36-\u1c37\u1cd0-\u1cd2\u1cd4-\u1ce0\u1ce2-\u1ce8\u1ced-\u1ced\u1dc0-\u1de6\u1dfc-\u1dff\u20d0-\u20dc\u20e1-\u20e1\u20e5-\u20f0\u2cef-\u2cf1\u2d7f-\u2d7f\u2de0-\u2dff\u302a-\u302f\u3099-\u309a\ua66f-\ua66f\ua67c-\ua67d\ua6f0-\ua6f1\ua802-\ua802\ua806-\ua806\ua80b-\ua80b\ua825-\ua826\ua8c4-\ua8c4\ua8e0-\ua8f1\ua926-\ua92d\ua947-\ua951\ua980-\ua982\ua9b3-\ua9b3\ua9b6-\ua9b9\ua9bc-\ua9bc\uaa29-\uaa2e\uaa31-\uaa32\uaa35-\uaa36\uaa43-\uaa43\uaa4c-\uaa4c\uaab0-\uaab0\uaab2-\uaab4\uaab7-\uaab8\uaabe-\uaabf\uaac1-\uaac1\uabe5-\uabe5\uabe8-\uabe8\uabed-\uabed\ufb1e-\ufb1e\ufe00-\ufe0f\ufe20-\ufe26\U000101fd-\U000101fd\U00010a01-\U00010a03\U00010a05-\U00010a06\U00010a0c-\U00010a0f\U00010a38-\U00010a3a\U00010a3f-\U00010a3f\U00011001-\U00011001\U00011038-\U00011046\U00011080-\U00011081\U000110b3-\U000110b6\U000110b9-\U000110ba\U0001d167-\U0001d169\U0001d17b-\U0001d182\U0001d185-\U0001d18b\U0001d1aa-\U0001d1ad\U0001d242-\U0001d244\U000e0100-\U000e01ef];
		Mn { goto Mn; }
		* { return YYCURSOR == limit; }
	*/
}
static const unsigned int chars_Mn [] = {0x300,0x36f,  0x483,0x487,  0x591,0x5bd,  0x5bf,0x5bf,  0x5c1,0x5c2,  0x5c4,0x5c5,  0x5c7,0x5c7,  0x610,0x61a,  0x64b,0x65f,  0x670,0x670,  0x6d6,0x6dc,  0x6df,0x6e4,  0x6e7,0x6e8,  0x6ea,0x6ed,  0x711,0x711,  0x730,0x74a,  0x7a6,0x7b0,  0x7eb,0x7f3,  0x816,0x819,  0x81b,0x823,  0x825,0x827,  0x829,0x82d,  0x859,0x85b,  0x900,0x902,  0x93a,0x93a,  0x93c,0x93c,  0x941,0x948,  0x94d,0x94d,  0x951,0x957,  0x962,0x963,  0x981,0x981,  0x9bc,0x9bc,  0x9c1,0x9c4,  0x9cd,0x9cd,  0x9e2,0x9e3,  0xa01,0xa02,  0xa3c,0xa3c,  0xa41,0xa42,  0xa47,0xa48,  0xa4b,0xa4d,  0xa51,0xa51,  0xa70,0xa71,  0xa75,0xa75,  0xa81,0xa82,  0xabc,0xabc,  0xac1,0xac5,  0xac7,0xac8,  0xacd,0xacd,  0xae2,0xae3,  0xb01,0xb01,  0xb3c,0xb3c,  0xb3f,0xb3f,  0xb41,0xb44,  0xb4d,0xb4d,  0xb56,0xb56,  0xb62,0xb63,  0xb82,0xb82,  0xbc0,0xbc0,  0xbcd,0xbcd,  0xc3e,0xc40,  0xc46,0xc48,  0xc4a,0xc4d,  0xc55,0xc56,  0xc62,0xc63,  0xcbc,0xcbc,  0xcbf,0xcbf,  0xcc6,0xcc6,  0xccc,0xccd,  0xce2,0xce3,  0xd41,0xd44,  0xd4d,0xd4d,  0xd62,0xd63,  0xdca,0xdca,  0xdd2,0xdd4,  0xdd6,0xdd6,  0xe31,0xe31,  0xe34,0xe3a,  0xe47,0xe4e,  0xeb1,0xeb1,  0xeb4,0xeb9,  0xebb,0xebc,  0xec8,0xecd,  0xf18,0xf19,  0xf35,0xf35,  0xf37,0xf37,  0xf39,0xf39,  0xf71,0xf7e,  0xf80,0xf84,  0xf86,0xf87,  0xf8d,0xf97,  0xf99,0xfbc,  0xfc6,0xfc6,  0x102d,0x1030,  0x1032,0x1037,  0x1039,0x103a,  0x103d,0x103e,  0x1058,0x1059,  0x105e,0x1060,  0x1071,0x1074,  0x1082,0x1082,  0x1085,0x1086,  0x108d,0x108d,  0x109d,0x109d,  0x135d,0x135f,  0x1712,0x1714,  0x1732,0x1734,  0x1752,0x1753,  0x1772,0x1773,  0x17b7,0x17bd,  0x17c6,0x17c6,  0x17c9,0x17d3,  0x17dd,0x17dd,  0x180b,0x180d,  0x18a9,0x18a9,  0x1920,0x1922,  0x1927,0x1928,  0x1932,0x1932,  0x1939,0x193b,  0x1a17,0x1a18,  0x1a56,0x1a56,  0x1a58,0x1a5e,  0x1a60,0x1a60,  0x1a62,0x1a62,  0x1a65,0x1a6c,  0x1a73,0x1a7c,  0x1a7f,0x1a7f,  0x1b00,0x1b03,  0x1b34,0x1b34,  0x1b36,0x1b3a,  0x1b3c,0x1b3c,  0x1b42,0x1b42,  0x1b6b,0x1b73,  0x1b80,0x1b81,  0x1ba2,0x1ba5,  0x1ba8,0x1ba9,  0x1be6,0x1be6,  0x1be8,0x1be9,  0x1bed,0x1bed,  0x1bef,0x1bf1,  0x1c2c,0x1c33,  0x1c36,0x1c37,  0x1cd0,0x1cd2,  0x1cd4,0x1ce0,  0x1ce2,0x1ce8,  0x1ced,0x1ced,  0x1dc0,0x1de6,  0x1dfc,0x1dff,  0x20d0,0x20dc,  0x20e1,0x20e1,  0x20e5,0x20f0,  0x2cef,0x2cf1,  0x2d7f,0x2d7f,  0x2de0,0x2dff,  0x302a,0x302f,  0x3099,0x309a,  0xa66f,0xa66f,  0xa67c,0xa67d,  0xa6f0,0xa6f1,  0xa802,0xa802,  0xa806,0xa806,  0xa80b,0xa80b,  0xa825,0xa826,  0xa8c4,0xa8c4,  0xa8e0,0xa8f1,  0xa926,0xa92d,  0xa947,0xa951,  0xa980,0xa982,  0xa9b3,0xa9b3,  0xa9b6,0xa9b9,  0xa9bc,0xa9bc,  0xaa29,0xaa2e,  0xaa31,0xaa32,  0xaa35,0xaa36,  0xaa43,0xaa43,  0xaa4c,0xaa4c,  0xaab0,0xaab0,  0xaab2,0xaab4,  0xaab7,0xaab8,  0xaabe,0xaabf,  0xaac1,0xaac1,  0xabe5,0xabe5,  0xabe8,0xabe8,  0xabed,0xabed,  0xfb1e,0xfb1e,  0xfe00,0xfe0f,  0xfe20,0xfe26,  0x101fd,0x101fd,  0x10a01,0x10a03,  0x10a05,0x10a06,  0x10a0c,0x10a0f,  0x10a38,0x10a3a,  0x10a3f,0x10a3f,  0x11001,0x11001,  0x11038,0x11046,  0x11080,0x11081,  0x110b3,0x110b6,  0x110b9,0x110ba,  0x1d167,0x1d169,  0x1d17b,0x1d182,  0x1d185,0x1d18b,  0x1d1aa,0x1d1ad,  0x1d242,0x1d244,  0xe0100,0xe01ef,  0x0,0x0};
static unsigned int encode_utf8 (const unsigned int * ranges, unsigned int ranges_count, unsigned char * s)
{
	unsigned char * const s_start = s;
	for (unsigned int i = 0; i < ranges_count - 2; i += 2)
		for (unsigned int j = ranges[i]; j <= ranges[i + 1]; ++j)
			s += re2c::utf8::rune_to_bytes (s, j);
	re2c::utf8::rune_to_bytes (s, ranges[ranges_count - 1]);
	return s - s_start + 1;
}

int main ()
{
	YYCTYPE * buffer_Mn = new YYCTYPE [4800];
	unsigned int buffer_len = encode_utf8 (chars_Mn, sizeof (chars_Mn) / sizeof (unsigned int), buffer_Mn);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Mn), reinterpret_cast<const YYCTYPE *> (buffer_Mn + buffer_len)))
		printf("test 'Mn' failed\n");
	delete [] buffer_Mn;
	return 0;
}
