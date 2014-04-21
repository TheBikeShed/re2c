/* Generated by re2c */
#line 1 "unicode_group_Pf.u--encoding-policy(substitute).re"
#include <stdio.h>

#define YYCTYPE unsigned int
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Pf:
	
#line 13 "<stdout>"
{
	YYCTYPE yych;

	yych = *YYCURSOR;
	if (yych <= 0x00002E03) {
		if (yych <= 0x0000201C) {
			if (yych <= 0x000000BB) {
				if (yych >= 0x000000BB) goto yy4;
			} else {
				if (yych == 0x00002019) goto yy4;
			}
		} else {
			if (yych <= 0x00002039) {
				if (yych <= 0x0000201D) goto yy4;
			} else {
				if (yych <= 0x0000203A) goto yy4;
				if (yych >= 0x00002E03) goto yy4;
			}
		}
	} else {
		if (yych <= 0x00002E0C) {
			if (yych <= 0x00002E05) {
				if (yych >= 0x00002E05) goto yy4;
			} else {
				if (yych == 0x00002E0A) goto yy4;
			}
		} else {
			if (yych <= 0x00002E1D) {
				if (yych <= 0x00002E0D) goto yy4;
				if (yych >= 0x00002E1D) goto yy4;
			} else {
				if (yych == 0x00002E21) goto yy4;
			}
		}
	}
	++YYCURSOR;
#line 13 "unicode_group_Pf.u--encoding-policy(substitute).re"
	{ return YYCURSOR == limit; }
#line 52 "<stdout>"
yy4:
	++YYCURSOR;
#line 12 "unicode_group_Pf.u--encoding-policy(substitute).re"
	{ goto Pf; }
#line 57 "<stdout>"
}
#line 14 "unicode_group_Pf.u--encoding-policy(substitute).re"

}
static const unsigned int chars_Pf [] = {0xbb,0xbb,  0x2019,0x2019,  0x201d,0x201d,  0x203a,0x203a,  0x2e03,0x2e03,  0x2e05,0x2e05,  0x2e0a,0x2e0a,  0x2e0d,0x2e0d,  0x2e1d,0x2e1d,  0x2e21,0x2e21,  0x0,0x0};
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
	YYCTYPE * buffer_Pf = new YYCTYPE [11];
	unsigned int buffer_len = encode_utf32 (chars_Pf, sizeof (chars_Pf) / sizeof (unsigned int), buffer_Pf);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Pf), reinterpret_cast<const YYCTYPE *> (buffer_Pf + buffer_len)))
		printf("test 'Pf' failed\n");
	delete [] buffer_Pf;
	return 0;
}
