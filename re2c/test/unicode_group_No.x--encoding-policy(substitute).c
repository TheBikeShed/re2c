/* Generated by re2c */
#line 1 "unicode_group_No.x--encoding-policy(substitute).re"
#include <stdio.h>
#include "utf16.h"
#define YYCTYPE unsigned short
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
No:
	
#line 13 "<stdout>"
{
	YYCTYPE yych;

	yych = *YYCURSOR;
	if (yych <= 0x215F) {
		if (yych <= 0x0D75) {
			if (yych <= 0x09F9) {
				if (yych <= 0x00B9) {
					if (yych <= 0x00B1) goto yy2;
					if (yych <= 0x00B3) goto yy4;
					if (yych >= 0x00B9) goto yy4;
				} else {
					if (yych <= 0x00BB) goto yy2;
					if (yych <= 0x00BE) goto yy4;
					if (yych >= 0x09F4) goto yy4;
				}
			} else {
				if (yych <= 0x0BF2) {
					if (yych <= 0x0B71) goto yy2;
					if (yych <= 0x0B77) goto yy4;
					if (yych >= 0x0BF0) goto yy4;
				} else {
					if (yych <= 0x0C77) goto yy2;
					if (yych <= 0x0C7E) goto yy4;
					if (yych >= 0x0D70) goto yy4;
				}
			}
		} else {
			if (yych <= 0x19DA) {
				if (yych <= 0x137C) {
					if (yych <= 0x0F29) goto yy2;
					if (yych <= 0x0F33) goto yy4;
					if (yych >= 0x1369) goto yy4;
				} else {
					if (yych <= 0x17EF) goto yy2;
					if (yych <= 0x17F9) goto yy4;
					if (yych >= 0x19DA) goto yy4;
				}
			} else {
				if (yych <= 0x2079) {
					if (yych == 0x2070) goto yy4;
					if (yych >= 0x2074) goto yy4;
				} else {
					if (yych <= 0x207F) goto yy2;
					if (yych <= 0x2089) goto yy4;
					if (yych >= 0x2150) goto yy4;
				}
			}
		}
	} else {
		if (yych <= 0x325F) {
			if (yych <= 0x2793) {
				if (yych <= 0x249B) {
					if (yych == 0x2189) goto yy4;
					if (yych >= 0x2460) goto yy4;
				} else {
					if (yych <= 0x24E9) goto yy2;
					if (yych <= 0x24FF) goto yy4;
					if (yych >= 0x2776) goto yy4;
				}
			} else {
				if (yych <= 0x3195) {
					if (yych == 0x2CFD) goto yy4;
					if (yych >= 0x3192) goto yy4;
				} else {
					if (yych <= 0x321F) goto yy2;
					if (yych <= 0x3229) goto yy4;
					if (yych >= 0x3251) goto yy4;
				}
			}
		} else {
			if (yych <= 0xD800) {
				if (yych <= 0x32BF) {
					if (yych <= 0x327F) goto yy2;
					if (yych <= 0x3289) goto yy4;
					if (yych >= 0x32B1) goto yy4;
				} else {
					if (yych <= 0xA82F) goto yy2;
					if (yych <= 0xA835) goto yy4;
					if (yych >= 0xD800) goto yy6;
				}
			} else {
				if (yych <= 0xD804) {
					if (yych <= 0xD801) goto yy2;
					if (yych <= 0xD802) goto yy7;
					if (yych <= 0xD803) goto yy8;
					goto yy9;
				} else {
					if (yych <= 0xD834) {
						if (yych >= 0xD834) goto yy10;
					} else {
						if (yych == 0xD83C) goto yy11;
					}
				}
			}
		}
	}
yy2:
	++YYCURSOR;
yy3:
#line 13 "unicode_group_No.x--encoding-policy(substitute).re"
	{ return YYCURSOR == limit; }
#line 116 "<stdout>"
yy4:
	++YYCURSOR;
yy5:
#line 12 "unicode_group_No.x--encoding-policy(substitute).re"
	{ goto No; }
#line 122 "<stdout>"
yy6:
	yych = *++YYCURSOR;
	if (yych <= 0xDD78) {
		if (yych <= 0xDD06) goto yy3;
		if (yych <= 0xDD33) goto yy12;
		if (yych <= 0xDD74) goto yy3;
		goto yy12;
	} else {
		if (yych <= 0xDD8A) {
			if (yych <= 0xDD89) goto yy3;
			goto yy12;
		} else {
			if (yych <= 0xDF1F) goto yy3;
			if (yych <= 0xDF23) goto yy12;
			goto yy3;
		}
	}
yy7:
	yych = *++YYCURSOR;
	if (yych <= 0xDE47) {
		if (yych <= 0xDD15) {
			if (yych <= 0xDC57) goto yy3;
			if (yych <= 0xDC5F) goto yy12;
			goto yy3;
		} else {
			if (yych <= 0xDD1B) goto yy12;
			if (yych <= 0xDE3F) goto yy3;
			goto yy12;
		}
	} else {
		if (yych <= 0xDF57) {
			if (yych <= 0xDE7C) goto yy3;
			if (yych <= 0xDE7E) goto yy12;
			goto yy3;
		} else {
			if (yych <= 0xDF5F) goto yy12;
			if (yych <= 0xDF77) goto yy3;
			if (yych <= 0xDF7F) goto yy12;
			goto yy3;
		}
	}
yy8:
	yych = *++YYCURSOR;
	if (yych <= 0xDE5F) goto yy3;
	if (yych <= 0xDE7E) goto yy12;
	goto yy3;
yy9:
	yych = *++YYCURSOR;
	if (yych <= 0xDC51) goto yy3;
	if (yych <= 0xDC65) goto yy12;
	goto yy3;
yy10:
	yych = *++YYCURSOR;
	if (yych <= 0xDF5F) goto yy3;
	if (yych <= 0xDF71) goto yy12;
	goto yy3;
yy11:
	yych = *++YYCURSOR;
	if (yych <= 0xDCFF) goto yy3;
	if (yych >= 0xDD0B) goto yy3;
yy12:
	++YYCURSOR;
	yych = *YYCURSOR;
	goto yy5;
}
#line 14 "unicode_group_No.x--encoding-policy(substitute).re"

}
static const unsigned int chars_No [] = {0xb2,0xb3,  0xb9,0xb9,  0xbc,0xbe,  0x9f4,0x9f9,  0xb72,0xb77,  0xbf0,0xbf2,  0xc78,0xc7e,  0xd70,0xd75,  0xf2a,0xf33,  0x1369,0x137c,  0x17f0,0x17f9,  0x19da,0x19da,  0x2070,0x2070,  0x2074,0x2079,  0x2080,0x2089,  0x2150,0x215f,  0x2189,0x2189,  0x2460,0x249b,  0x24ea,0x24ff,  0x2776,0x2793,  0x2cfd,0x2cfd,  0x3192,0x3195,  0x3220,0x3229,  0x3251,0x325f,  0x3280,0x3289,  0x32b1,0x32bf,  0xa830,0xa835,  0x10107,0x10133,  0x10175,0x10178,  0x1018a,0x1018a,  0x10320,0x10323,  0x10858,0x1085f,  0x10916,0x1091b,  0x10a40,0x10a47,  0x10a7d,0x10a7e,  0x10b58,0x10b5f,  0x10b78,0x10b7f,  0x10e60,0x10e7e,  0x11052,0x11065,  0x1d360,0x1d371,  0x1f100,0x1f10a,  0x0,0x0};
static unsigned int encode_utf16 (const unsigned int * ranges, unsigned int ranges_count, unsigned short * s)
{
	unsigned short * const s_start = s;
	for (unsigned int i = 0; i < ranges_count; i += 2)
		for (unsigned int j = ranges[i]; j <= ranges[i + 1]; ++j)
		{
			if (j <= re2c::utf16::MAX_1WORD_RUNE)
				*s++ = j;
			else
			{
				*s++ = re2c::utf16::lead_surr(j);
				*s++ = re2c::utf16::trail_surr(j);
			}
		}
	return s - s_start;
}

int main ()
{
	YYCTYPE * buffer_No = new YYCTYPE [914];
	unsigned int buffer_len = encode_utf16 (chars_No, sizeof (chars_No) / sizeof (unsigned int), buffer_No);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_No), reinterpret_cast<const YYCTYPE *> (buffer_No + buffer_len)))
		printf("test 'No' failed\n");
	delete [] buffer_No;
	return 0;
}
