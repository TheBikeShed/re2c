/* Generated by re2c */
#line 1 "unicode_group_Nd.8--encoding-policy(substitute).re"
#include <stdio.h>
#include "utf8.h"
#define YYCTYPE unsigned char
bool scan(const YYCTYPE * start, const YYCTYPE * const limit)
{
	__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used
#	define YYCURSOR start
Nd:
	
#line 13 "<stdout>"
{
	YYCTYPE yych;

	yych = *YYCURSOR;
	switch (yych) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':	goto yy4;
	case 0xD9:	goto yy6;
	case 0xDB:	goto yy7;
	case 0xDF:	goto yy8;
	case 0xE0:	goto yy9;
	case 0xE1:	goto yy10;
	case 0xEA:	goto yy11;
	case 0xEF:	goto yy12;
	case 0xF0:	goto yy13;
	default:	goto yy2;
	}
yy2:
	++YYCURSOR;
yy3:
#line 13 "unicode_group_Nd.8--encoding-policy(substitute).re"
	{ return YYCURSOR == limit; }
#line 44 "<stdout>"
yy4:
	++YYCURSOR;
yy5:
#line 12 "unicode_group_Nd.8--encoding-policy(substitute).re"
	{ goto Nd; }
#line 50 "<stdout>"
yy6:
	yych = *++YYCURSOR;
	switch (yych) {
	case 0xA0:
	case 0xA1:
	case 0xA2:
	case 0xA3:
	case 0xA4:
	case 0xA5:
	case 0xA6:
	case 0xA7:
	case 0xA8:
	case 0xA9:	goto yy19;
	default:	goto yy3;
	}
yy7:
	yych = *++YYCURSOR;
	switch (yych) {
	case 0xB0:
	case 0xB1:
	case 0xB2:
	case 0xB3:
	case 0xB4:
	case 0xB5:
	case 0xB6:
	case 0xB7:
	case 0xB8:
	case 0xB9:	goto yy19;
	default:	goto yy3;
	}
yy8:
	yych = *++YYCURSOR;
	switch (yych) {
	case 0x80:
	case 0x81:
	case 0x82:
	case 0x83:
	case 0x84:
	case 0x85:
	case 0x86:
	case 0x87:
	case 0x88:
	case 0x89:	goto yy19;
	default:	goto yy3;
	}
yy9:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 0xA5:
	case 0xA7:
	case 0xA9:
	case 0xAB:
	case 0xAD:
	case 0xAF:
	case 0xB1:
	case 0xB3:
	case 0xB5:	goto yy20;
	case 0xB9:
	case 0xBB:	goto yy22;
	case 0xBC:	goto yy18;
	default:	goto yy3;
	}
yy10:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 0x81:	goto yy23;
	case 0x82:
	case 0xA0:
	case 0xA7:
	case 0xAD:	goto yy22;
	case 0x9F:	goto yy18;
	case 0xA5:	goto yy25;
	case 0xAA:
	case 0xB1:	goto yy26;
	case 0xAE:	goto yy24;
	default:	goto yy3;
	}
yy11:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 0x98:	goto yy18;
	case 0xA3:
	case 0xA7:
	case 0xA9:	goto yy22;
	case 0xA4:	goto yy23;
	case 0xAF:	goto yy24;
	default:	goto yy3;
	}
yy12:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 0xBC:	goto yy22;
	default:	goto yy3;
	}
yy13:
	yych = *(YYMARKER = ++YYCURSOR);
	switch (yych) {
	case 0x90:	goto yy17;
	case 0x91:	goto yy16;
	case 0x9D:	goto yy14;
	default:	goto yy3;
	}
yy14:
	yych = *++YYCURSOR;
	switch (yych) {
	case 0x9F:	goto yy21;
	default:	goto yy15;
	}
yy15:
	YYCURSOR = YYMARKER;
	goto yy3;
yy16:
	yych = *++YYCURSOR;
	switch (yych) {
	case 0x81:	goto yy20;
	default:	goto yy15;
	}
yy17:
	yych = *++YYCURSOR;
	switch (yych) {
	case 0x92:	goto yy18;
	default:	goto yy15;
	}
yy18:
	yych = *++YYCURSOR;
	switch (yych) {
	case 0xA0:
	case 0xA1:
	case 0xA2:
	case 0xA3:
	case 0xA4:
	case 0xA5:
	case 0xA6:
	case 0xA7:
	case 0xA8:
	case 0xA9:	goto yy19;
	default:	goto yy15;
	}
yy19:
	yych = *++YYCURSOR;
	goto yy5;
yy20:
	yych = *++YYCURSOR;
	switch (yych) {
	case 0xA6:
	case 0xA7:
	case 0xA8:
	case 0xA9:
	case 0xAA:
	case 0xAB:
	case 0xAC:
	case 0xAD:
	case 0xAE:
	case 0xAF:	goto yy19;
	default:	goto yy15;
	}
yy21:
	yych = *++YYCURSOR;
	switch (yych) {
	case 0x8E:
	case 0x8F:
	case 0x90:
	case 0x91:
	case 0x92:
	case 0x93:
	case 0x94:
	case 0x95:
	case 0x96:
	case 0x97:
	case 0x98:
	case 0x99:
	case 0x9A:
	case 0x9B:
	case 0x9C:
	case 0x9D:
	case 0x9E:
	case 0x9F:
	case 0xA0:
	case 0xA1:
	case 0xA2:
	case 0xA3:
	case 0xA4:
	case 0xA5:
	case 0xA6:
	case 0xA7:
	case 0xA8:
	case 0xA9:
	case 0xAA:
	case 0xAB:
	case 0xAC:
	case 0xAD:
	case 0xAE:
	case 0xAF:
	case 0xB0:
	case 0xB1:
	case 0xB2:
	case 0xB3:
	case 0xB4:
	case 0xB5:
	case 0xB6:
	case 0xB7:
	case 0xB8:
	case 0xB9:
	case 0xBA:
	case 0xBB:
	case 0xBC:
	case 0xBD:
	case 0xBE:
	case 0xBF:	goto yy19;
	default:	goto yy15;
	}
yy22:
	yych = *++YYCURSOR;
	switch (yych) {
	case 0x90:
	case 0x91:
	case 0x92:
	case 0x93:
	case 0x94:
	case 0x95:
	case 0x96:
	case 0x97:
	case 0x98:
	case 0x99:	goto yy19;
	default:	goto yy15;
	}
yy23:
	yych = *++YYCURSOR;
	switch (yych) {
	case 0x80:
	case 0x81:
	case 0x82:
	case 0x83:
	case 0x84:
	case 0x85:
	case 0x86:
	case 0x87:
	case 0x88:
	case 0x89:	goto yy19;
	default:	goto yy15;
	}
yy24:
	yych = *++YYCURSOR;
	switch (yych) {
	case 0xB0:
	case 0xB1:
	case 0xB2:
	case 0xB3:
	case 0xB4:
	case 0xB5:
	case 0xB6:
	case 0xB7:
	case 0xB8:
	case 0xB9:	goto yy19;
	default:	goto yy15;
	}
yy25:
	yych = *++YYCURSOR;
	switch (yych) {
	case 0x86:
	case 0x87:
	case 0x88:
	case 0x89:
	case 0x8A:
	case 0x8B:
	case 0x8C:
	case 0x8D:
	case 0x8E:
	case 0x8F:	goto yy19;
	default:	goto yy15;
	}
yy26:
	++YYCURSOR;
	switch ((yych = *YYCURSOR)) {
	case 0x80:
	case 0x81:
	case 0x82:
	case 0x83:
	case 0x84:
	case 0x85:
	case 0x86:
	case 0x87:
	case 0x88:
	case 0x89:
	case 0x90:
	case 0x91:
	case 0x92:
	case 0x93:
	case 0x94:
	case 0x95:
	case 0x96:
	case 0x97:
	case 0x98:
	case 0x99:	goto yy19;
	default:	goto yy15;
	}
}
#line 14 "unicode_group_Nd.8--encoding-policy(substitute).re"

}
static const unsigned int chars_Nd [] = {0x30,0x39,  0x660,0x669,  0x6f0,0x6f9,  0x7c0,0x7c9,  0x966,0x96f,  0x9e6,0x9ef,  0xa66,0xa6f,  0xae6,0xaef,  0xb66,0xb6f,  0xbe6,0xbef,  0xc66,0xc6f,  0xce6,0xcef,  0xd66,0xd6f,  0xe50,0xe59,  0xed0,0xed9,  0xf20,0xf29,  0x1040,0x1049,  0x1090,0x1099,  0x17e0,0x17e9,  0x1810,0x1819,  0x1946,0x194f,  0x19d0,0x19d9,  0x1a80,0x1a89,  0x1a90,0x1a99,  0x1b50,0x1b59,  0x1bb0,0x1bb9,  0x1c40,0x1c49,  0x1c50,0x1c59,  0xa620,0xa629,  0xa8d0,0xa8d9,  0xa900,0xa909,  0xa9d0,0xa9d9,  0xaa50,0xaa59,  0xabf0,0xabf9,  0xff10,0xff19,  0x104a0,0x104a9,  0x11066,0x1106f,  0x1d7ce,0x1d7ff,  0x0,0x0};
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
	YYCTYPE * buffer_Nd = new YYCTYPE [1684];
	unsigned int buffer_len = encode_utf8 (chars_Nd, sizeof (chars_Nd) / sizeof (unsigned int), buffer_Nd);
	if (!scan (reinterpret_cast<const YYCTYPE *> (buffer_Nd), reinterpret_cast<const YYCTYPE *> (buffer_Nd + buffer_len)))
		printf("test 'Nd' failed\n");
	delete [] buffer_Nd;
	return 0;
}
