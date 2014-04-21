/* Generated by re2c */
#line 1 "unicode_group_Pi.u--encoding-policy(ignore).re"
#include <stdio.h>

#define YYCTYPE unsigned int
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Pi:
	
#line 13 "<stdout>"
{
	YYCTYPE yych;

	yych = *YYCURSOR;
	if (yych <= 0x00002E01) {
		if (yych <= 0x0000201A) {
			if (yych <= 0x000000AB) {
				if (yych >= 0x000000AB) goto yy4;
			} else {
				if (yych == 0x00002018) goto yy4;
			}
		} else {
			if (yych <= 0x0000201F) {
				if (yych <= 0x0000201C) goto yy4;
				if (yych >= 0x0000201F) goto yy4;
			} else {
				if (yych == 0x00002039) goto yy4;
			}
		}
	} else {
		if (yych <= 0x00002E0B) {
			if (yych <= 0x00002E04) {
				if (yych != 0x00002E03) goto yy4;
			} else {
				if (yych == 0x00002E09) goto yy4;
			}
		} else {
			if (yych <= 0x00002E1C) {
				if (yych <= 0x00002E0C) goto yy4;
				if (yych >= 0x00002E1C) goto yy4;
			} else {
				if (yych == 0x00002E20) goto yy4;
			}
		}
	}
	++YYCURSOR;
#line 13 "unicode_group_Pi.u--encoding-policy(ignore).re"
	{ return YYCURSOR == limit; }
#line 52 "<stdout>"
yy4:
	++YYCURSOR;
#line 12 "unicode_group_Pi.u--encoding-policy(ignore).re"
	{ goto Pi; }
#line 57 "<stdout>"
}
#line 14 "unicode_group_Pi.u--encoding-policy(ignore).re"

}
static const unsigned int chars_Pi [] = {0xab,0xab,  0x2018,0x2018,  0x201b,0x201c,  0x201f,0x201f,  0x2039,0x2039,  0x2e02,0x2e02,  0x2e04,0x2e04,  0x2e09,0x2e09,  0x2e0c,0x2e0c,  0x2e1c,0x2e1c,  0x2e20,0x2e20,  0x0,0x0};
static unsigned int encode_utf32 (const unsigned int * ranges, unsigned int ranges_count, unsigned int * s)
{
	unsigned int * const s_start = s;
	for (unsigned int i = 0; i < ranges_count; i += 2)
		for (unsigned int j = ranges[i]; j <= ranges[i + 1]; ++j)
			*s++ = j;
	return s - s_start;
}

int main ()
{
	YYCTYPE * buffer_Pi = new YYCTYPE [13];
	unsigned int buffer_len = encode_utf32 (chars_Pi, sizeof (chars_Pi) / sizeof (unsigned int), buffer_Pi);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Pi), reinterpret_cast<const YYCTYPE *> (buffer_Pi + buffer_len)))
		printf("test 'Pi' failed\n");
	delete [] buffer_Pi;
	return 0;
}
