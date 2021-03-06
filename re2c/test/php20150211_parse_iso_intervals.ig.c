/* Generated by re2c */
/*
   +----------------------------------------------------------------------+
   | PHP Version 7                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2015 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Derick Rethans <derick@derickrethans.nl>                    |
   +----------------------------------------------------------------------+
 */

/* $Id$ */

#include "timelib.h"

#include <stdio.h>
#include <ctype.h>

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif

#if defined(_MSC_VER)
# define strtoll(s, f, b) _atoi64(s)
#elif !defined(HAVE_STRTOLL)
# if defined(HAVE_ATOLL)
#  define strtoll(s, f, b) atoll(s)
# else
#  define strtoll(s, f, b) strtol(s, f, b)
# endif
#endif

#define TIMELIB_UNSET   -99999

#define TIMELIB_SECOND  1
#define TIMELIB_MINUTE  2
#define TIMELIB_HOUR    3
#define TIMELIB_DAY     4
#define TIMELIB_MONTH   5
#define TIMELIB_YEAR    6

#define EOI      257

#define TIMELIB_PERIOD  260
#define TIMELIB_ISO_DATE 261
#define TIMELIB_ERROR   999

typedef unsigned char uchar;

#define   BSIZE	   8192

#define   YYCTYPE      uchar
#define   YYCURSOR     cursor
#define   YYLIMIT      s->lim
#define   YYMARKER     s->ptr
#define   YYFILL(n)    return EOI;

#define   RET(i)       {s->cur = cursor; return i;}

#define timelib_string_free free

#define TIMELIB_INIT  s->cur = cursor; str = timelib_string(s); ptr = str
#define TIMELIB_DEINIT timelib_string_free(str)

#ifdef DEBUG_PARSER
#define DEBUG_OUTPUT(s) printf("%s\n", s);
#define YYDEBUG(s,c) { if (s != -1) { printf("state: %d ", s); printf("[%c]\n", c); } }
#else
#define DEBUG_OUTPUT(s)
#define YYDEBUG(s,c)
#endif

#include "timelib_structs.h"

typedef struct Scanner {
	int           fd;
	uchar        *lim, *str, *ptr, *cur, *tok, *pos;
	unsigned int  line, len;
	struct timelib_error_container *errors;

	struct timelib_time     *begin;
	struct timelib_time     *end;
	struct timelib_rel_time *period;
	int                      recurrences;

	int have_period;
	int have_recurrences;
	int have_date;
	int have_begin_date;
	int have_end_date;
} Scanner;

static void add_warning(Scanner *s, char *error)
{
	s->errors->warning_count++;
	s->errors->warning_messages = realloc(s->errors->warning_messages, s->errors->warning_count * sizeof(timelib_error_message));
	s->errors->warning_messages[s->errors->warning_count - 1].position = s->tok ? s->tok - s->str : 0;
	s->errors->warning_messages[s->errors->warning_count - 1].character = s->tok ? *s->tok : 0;
	s->errors->warning_messages[s->errors->warning_count - 1].message = strdup(error);
}

static void add_error(Scanner *s, char *error)
{
	s->errors->error_count++;
	s->errors->error_messages = realloc(s->errors->error_messages, s->errors->error_count * sizeof(timelib_error_message));
	s->errors->error_messages[s->errors->error_count - 1].position = s->tok ? s->tok - s->str : 0;
	s->errors->error_messages[s->errors->error_count - 1].character = s->tok ? *s->tok : 0;
	s->errors->error_messages[s->errors->error_count - 1].message = strdup(error);
}

static char *timelib_string(Scanner *s)
{
	char *tmp = calloc(1, s->cur - s->tok + 1);
	memcpy(tmp, s->tok, s->cur - s->tok);

	return tmp;
}

static timelib_sll timelib_get_nr(char **ptr, int max_length)
{
	char *begin, *end, *str;
	timelib_sll tmp_nr = TIMELIB_UNSET;
	int len = 0;

	while ((**ptr < '0') || (**ptr > '9')) {
		if (**ptr == '\0') {
			return TIMELIB_UNSET;
		}
		++*ptr;
	}
	begin = *ptr;
	while ((**ptr >= '0') && (**ptr <= '9') && len < max_length) {
		++*ptr;
		++len;
	}
	end = *ptr;
	str = calloc(1, end - begin + 1);
	memcpy(str, begin, end - begin);
	tmp_nr = strtoll(str, NULL, 10);
	free(str);
	return tmp_nr;
}

static timelib_ull timelib_get_unsigned_nr(char **ptr, int max_length)
{
	timelib_ull dir = 1;

	while (((**ptr < '0') || (**ptr > '9')) && (**ptr != '+') && (**ptr != '-')) {
		if (**ptr == '\0') {
			return TIMELIB_UNSET;
		}
		++*ptr;
	}

	while (**ptr == '+' || **ptr == '-')
	{
		if (**ptr == '-') {
			dir *= -1;
		}
		++*ptr;
	}
	return dir * timelib_get_nr(ptr, max_length);
}

static void timelib_eat_spaces(char **ptr)
{
	while (**ptr == ' ' || **ptr == '\t') {
		++*ptr;
	}
}

static void timelib_eat_until_separator(char **ptr)
{
	while (strchr(" \t.,:;/-0123456789", **ptr) == NULL) {
		++*ptr;
	}
}

static timelib_long timelib_get_zone(char **ptr, int *dst, timelib_time *t, int *tz_not_found, const timelib_tzdb *tzdb)
{
	timelib_long retval = 0;

	*tz_not_found = 0;

	while (**ptr == ' ' || **ptr == '\t' || **ptr == '(') {
		++*ptr;
	}
	if ((*ptr)[0] == 'G' && (*ptr)[1] == 'M' && (*ptr)[2] == 'T' && ((*ptr)[3] == '+' || (*ptr)[3] == '-')) {
		*ptr += 3;
	}
	if (**ptr == '+') {
		++*ptr;
		t->is_localtime = 1;
		t->zone_type = TIMELIB_ZONETYPE_OFFSET;
		*tz_not_found = 0;
		t->dst = 0;

		retval = -1 * timelib_parse_tz_cor(ptr);
	} else if (**ptr == '-') {
		++*ptr;
		t->is_localtime = 1;
		t->zone_type = TIMELIB_ZONETYPE_OFFSET;
		*tz_not_found = 0;
		t->dst = 0;

		retval = timelib_parse_tz_cor(ptr);
	}
	while (**ptr == ')') {
		++*ptr;
	}
	return retval;
}

#define timelib_split_free(arg) {       \
	int i;                         \
	for (i = 0; i < arg.c; i++) {  \
		free(arg.v[i]);            \
	}                              \
	if (arg.v) {                   \
		free(arg.v);               \
	}                              \
}

/* date parser's scan function too large for VC6 - VC7.x
   drop the optimization solves the problem */
#ifdef PHP_WIN32
#pragma optimize( "", off )
#endif
static int scan(Scanner *s)
{
	uchar *cursor = s->cur;
	char *str, *ptr = NULL;

std:
	s->tok = cursor;
	s->len = 0;



{
	YYCTYPE yych;
	unsigned int yyaccept = 0;
	static const unsigned char yybm[] = {
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		128, 128, 128, 128, 128, 128, 128, 128, 
		128, 128,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
		  0,   0,   0,   0,   0,   0,   0,   0, 
	};
	if ((YYLIMIT - YYCURSOR) < 20) YYFILL(20);
	yych = *YYCURSOR;
	{
		static void *yytarget[256] = {
			&&yy2,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy6,  &&yy2,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy6,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy6,  &&yy4,  &&yy6,  &&yy6,
			&&yy8,  &&yy8,  &&yy8,  &&yy8,  &&yy8,  &&yy8,  &&yy8,  &&yy8,
			&&yy8,  &&yy8,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy9,  &&yy4,  &&yy11, &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,
			&&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4,  &&yy4
		};
		goto *yytarget[yych];
	}
yy2:
	++YYCURSOR;
	{
		s->pos = cursor; s->line++;
		goto std;
	}
yy4:
	++YYCURSOR;
yy5:
	{
		add_error(s, "Unexpected character");
		goto std;
	}
yy6:
	++YYCURSOR;
	{
		goto std;
	}
yy8:
	yyaccept = 0;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy5;
	if (yych <= '9') goto yy12;
	goto yy5;
yy9:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy10;
	if (yych <= '9') goto yy14;
	if (yych == 'T') goto yy15;
yy10:
	{
		timelib_sll nr;
		int         in_time = 0;
		DEBUG_OUTPUT("period");
		TIMELIB_INIT;
		ptr++;
		do {
			if ( *ptr == 'T' ) {
				in_time = 1;
				ptr++;
			}
			if ( *ptr == '\0' ) {
				add_error(s, "Missing expected time part");
				break;
			}

			nr = timelib_get_unsigned_nr((char **) &ptr, 12);
			switch (*ptr) {
				case 'Y': s->period->y = nr; break;
				case 'W': s->period->d = nr * 7; break;
				case 'D': s->period->d = nr; break;
				case 'H': s->period->h = nr; break;
				case 'S': s->period->s = nr; break;
				case 'M':
					if (in_time) {
						s->period->i = nr;
					} else {
						s->period->m = nr;
					}
					break;
				default:
					add_error(s, "Undefined period specifier");
					break;
			}
			ptr++;
		} while (!s->errors->error_count && *ptr);
		s->have_period = 1;
		TIMELIB_DEINIT;
		return TIMELIB_PERIOD;
	}
yy11:
	yych = *++YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy16;
	}
	goto yy5;
yy12:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy19;
yy13:
	YYCURSOR = YYMARKER;
	if (yyaccept == 0) {
		goto yy5;
	} else {
		goto yy10;
	}
yy14:
	yych = *++YYCURSOR;
	{
		static void *yytarget[256] = {
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy20, &&yy20, &&yy20, &&yy20, &&yy20, &&yy20, &&yy20, &&yy20,
			&&yy20, &&yy20, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy21, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy22, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy23,
			&&yy13, &&yy24, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13
		};
		goto *yytarget[yych];
	}
yy15:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy10;
	if (yych <= '9') goto yy25;
	goto yy10;
yy16:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yybm[0+yych] & 128) {
		goto yy16;
	}
	{
		DEBUG_OUTPUT("recurrences");
		TIMELIB_INIT;
		ptr++;
		s->recurrences = timelib_get_unsigned_nr((char **) &ptr, 9);
		TIMELIB_DEINIT;
		s->have_recurrences = 1;
		return TIMELIB_PERIOD;
	}
yy19:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy27;
	goto yy13;
yy20:
	yych = *++YYCURSOR;
	{
		static void *yytarget[256] = {
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy28, &&yy28, &&yy28, &&yy28, &&yy28, &&yy28, &&yy28, &&yy28,
			&&yy28, &&yy28, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy21, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy22, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy23,
			&&yy13, &&yy24, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13
		};
		goto *yytarget[yych];
	}
yy21:
	yych = *++YYCURSOR;
	if (yych == 'T') goto yy15;
	goto yy10;
yy22:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy10;
	if (yych <= '9') goto yy29;
	if (yych == 'T') goto yy15;
	goto yy10;
yy23:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy10;
	if (yych <= '9') goto yy31;
	if (yych == 'T') goto yy15;
	goto yy10;
yy24:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy10;
	if (yych <= '9') goto yy33;
	if (yych == 'T') goto yy15;
	goto yy10;
yy25:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	{
		static void *yytarget[256] = {
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy25, &&yy25, &&yy25, &&yy25, &&yy25, &&yy25, &&yy25, &&yy25,
			&&yy25, &&yy25, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy35, &&yy13, &&yy13, &&yy13, &&yy13, &&yy36, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy37, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13
		};
		goto *yytarget[yych];
	}
yy27:
	yych = *++YYCURSOR;
	if (yych <= '/') {
		if (yych == '-') goto yy38;
		goto yy13;
	} else {
		if (yych <= '0') goto yy39;
		if (yych <= '1') goto yy40;
		goto yy13;
	}
yy28:
	yych = *++YYCURSOR;
	{
		static void *yytarget[256] = {
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy41, &&yy41, &&yy41, &&yy41, &&yy41, &&yy41, &&yy41, &&yy41,
			&&yy41, &&yy41, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy21, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy22, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy23,
			&&yy13, &&yy24, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13
		};
		goto *yytarget[yych];
	}
yy29:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
	if (yych <= 'C') {
		if (yych <= '/') goto yy13;
		if (yych <= '9') goto yy29;
		goto yy13;
	} else {
		if (yych <= 'D') goto yy21;
		if (yych == 'W') goto yy23;
		goto yy13;
	}
yy31:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy31;
	if (yych == 'D') goto yy21;
	goto yy13;
yy33:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
	{
		static void *yytarget[256] = {
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy33, &&yy33, &&yy33, &&yy33, &&yy33, &&yy33, &&yy33, &&yy33,
			&&yy33, &&yy33, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy21, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy22, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy23,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13
		};
		goto *yytarget[yych];
	}
yy35:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy10;
	if (yych <= '9') goto yy42;
	goto yy10;
yy36:
	yyaccept = 1;
	yych = *(YYMARKER = ++YYCURSOR);
	if (yych <= '/') goto yy10;
	if (yych <= '9') goto yy44;
	goto yy10;
yy37:
	yych = *++YYCURSOR;
	goto yy10;
yy38:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '0') goto yy46;
	if (yych <= '1') goto yy47;
	goto yy13;
yy39:
	yych = *++YYCURSOR;
	if (yych <= '0') goto yy13;
	if (yych <= '9') goto yy48;
	goto yy13;
yy40:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '2') goto yy48;
	goto yy13;
yy41:
	yych = *++YYCURSOR;
	if (yych == '-') goto yy49;
	goto yy51;
yy42:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 2) YYFILL(2);
	yych = *YYCURSOR;
	if (yych <= 'L') {
		if (yych <= '/') goto yy13;
		if (yych <= '9') goto yy42;
		goto yy13;
	} else {
		if (yych <= 'M') goto yy36;
		if (yych == 'S') goto yy37;
		goto yy13;
	}
yy44:
	++YYCURSOR;
	if (YYLIMIT <= YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy44;
	if (yych == 'S') goto yy37;
	goto yy13;
yy46:
	yych = *++YYCURSOR;
	if (yych <= '0') goto yy13;
	if (yych <= '9') goto yy52;
	goto yy13;
yy47:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '2') goto yy52;
	goto yy13;
yy48:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '0') goto yy53;
	if (yych <= '2') goto yy54;
	if (yych <= '3') goto yy55;
	goto yy13;
yy49:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '0') goto yy56;
	if (yych <= '1') goto yy57;
	goto yy13;
yy50:
	++YYCURSOR;
	if ((YYLIMIT - YYCURSOR) < 3) YYFILL(3);
	yych = *YYCURSOR;
yy51:
	{
		static void *yytarget[256] = {
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy50, &&yy50, &&yy50, &&yy50, &&yy50, &&yy50, &&yy50, &&yy50,
			&&yy50, &&yy50, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy21, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy22, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy23,
			&&yy13, &&yy24, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13,
			&&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13, &&yy13
		};
		goto *yytarget[yych];
	}
yy52:
	yych = *++YYCURSOR;
	if (yych == '-') goto yy58;
	goto yy13;
yy53:
	yych = *++YYCURSOR;
	if (yych <= '0') goto yy13;
	if (yych <= '9') goto yy59;
	goto yy13;
yy54:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy59;
	goto yy13;
yy55:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '1') goto yy59;
	goto yy13;
yy56:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy60;
	goto yy13;
yy57:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '2') goto yy60;
	goto yy13;
yy58:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '0') goto yy61;
	if (yych <= '2') goto yy62;
	if (yych <= '3') goto yy63;
	goto yy13;
yy59:
	yych = *++YYCURSOR;
	if (yych == 'T') goto yy64;
	goto yy13;
yy60:
	yych = *++YYCURSOR;
	if (yych == '-') goto yy65;
	goto yy13;
yy61:
	yych = *++YYCURSOR;
	if (yych <= '0') goto yy13;
	if (yych <= '9') goto yy66;
	goto yy13;
yy62:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy66;
	goto yy13;
yy63:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '1') goto yy66;
	goto yy13;
yy64:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '1') goto yy67;
	if (yych <= '2') goto yy68;
	goto yy13;
yy65:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '2') goto yy69;
	if (yych <= '3') goto yy70;
	goto yy13;
yy66:
	yych = *++YYCURSOR;
	if (yych == 'T') goto yy71;
	goto yy13;
yy67:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy72;
	goto yy13;
yy68:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '4') goto yy72;
	goto yy13;
yy69:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy73;
	goto yy13;
yy70:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '1') goto yy73;
	goto yy13;
yy71:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '1') goto yy74;
	if (yych <= '2') goto yy75;
	goto yy13;
yy72:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '5') goto yy76;
	goto yy13;
yy73:
	yych = *++YYCURSOR;
	if (yych == 'T') goto yy77;
	goto yy13;
yy74:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy78;
	goto yy13;
yy75:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '4') goto yy78;
	goto yy13;
yy76:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy79;
	goto yy13;
yy77:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '1') goto yy80;
	if (yych <= '2') goto yy81;
	goto yy13;
yy78:
	yych = *++YYCURSOR;
	if (yych == ':') goto yy82;
	goto yy13;
yy79:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '5') goto yy83;
	goto yy13;
yy80:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy84;
	goto yy13;
yy81:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '4') goto yy84;
	goto yy13;
yy82:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '5') goto yy85;
	goto yy13;
yy83:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy86;
	goto yy13;
yy84:
	yych = *++YYCURSOR;
	if (yych == ':') goto yy87;
	goto yy13;
yy85:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '9') goto yy88;
	goto yy13;
yy86:
	yych = *++YYCURSOR;
	if (yych == 'Z') goto yy89;
	goto yy13;
yy87:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych <= '5') goto yy91;
	goto yy13;
yy88:
	yych = *++YYCURSOR;
	if (yych == ':') goto yy79;
	goto yy13;
yy89:
	++YYCURSOR;
	{
		timelib_time *current;

		if (s->have_date || s->have_period) {
			current = s->end;
			s->have_end_date = 1;
		} else {
			current = s->begin;
			s->have_begin_date = 1;
		}
		DEBUG_OUTPUT("datetimebasic | datetimeextended");
		TIMELIB_INIT;
		current->y = timelib_get_nr((char **) &ptr, 4);
		current->m = timelib_get_nr((char **) &ptr, 2);
		current->d = timelib_get_nr((char **) &ptr, 2);
		current->h = timelib_get_nr((char **) &ptr, 2);
		current->i = timelib_get_nr((char **) &ptr, 2);
		current->s = timelib_get_nr((char **) &ptr, 2);
		s->have_date = 1;
		TIMELIB_DEINIT;
		return TIMELIB_ISO_DATE;
	}
yy91:
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= ':') goto yy13;
	yych = *++YYCURSOR;
	if (yych != ':') goto yy13;
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= '6') goto yy13;
	yych = *++YYCURSOR;
	if (yych <= '/') goto yy13;
	if (yych >= ':') goto yy13;
	++YYCURSOR;
	{
		DEBUG_OUTPUT("combinedrep");
		TIMELIB_INIT;
		s->period->y = timelib_get_unsigned_nr((char **) &ptr, 4);
		ptr++;
		s->period->m = timelib_get_unsigned_nr((char **) &ptr, 2);
		ptr++;
		s->period->d = timelib_get_unsigned_nr((char **) &ptr, 2);
		ptr++;
		s->period->h = timelib_get_unsigned_nr((char **) &ptr, 2);
		ptr++;
		s->period->i = timelib_get_unsigned_nr((char **) &ptr, 2);
		ptr++;
		s->period->s = timelib_get_unsigned_nr((char **) &ptr, 2);
		s->have_period = 1;
		TIMELIB_DEINIT;
		return TIMELIB_PERIOD;
	}
}

}
#ifdef PHP_WIN32
#pragma optimize( "", on )
#endif

#define YYMAXFILL 20

void timelib_strtointerval(char *s, size_t len,
                           timelib_time **begin, timelib_time **end,
						   timelib_rel_time **period, int *recurrences,
						   struct timelib_error_container **errors)
{
	Scanner in;
	int t;
	char *e = s + len - 1;

	memset(&in, 0, sizeof(in));
	in.errors = malloc(sizeof(struct timelib_error_container));
	in.errors->warning_count = 0;
	in.errors->warning_messages = NULL;
	in.errors->error_count = 0;
	in.errors->error_messages = NULL;

	if (len > 0) {
		while (isspace(*s) && s < e) {
			s++;
		}
		while (isspace(*e) && e > s) {
			e--;
		}
	}
	if (e - s < 0) {
		add_error(&in, "Empty string");
		if (errors) {
			*errors = in.errors;
		} else {
			timelib_error_container_dtor(in.errors);
		}
		return;
	}
	e++;

	/* init cursor */
	in.str = malloc((e - s) + YYMAXFILL);
	memset(in.str, 0, (e - s) + YYMAXFILL);
	memcpy(in.str, s, (e - s));
	in.lim = in.str + (e - s) + YYMAXFILL;
	in.cur = in.str;

	/* init value containers */
	in.begin = timelib_time_ctor();
	in.begin->y = TIMELIB_UNSET;
	in.begin->d = TIMELIB_UNSET;
	in.begin->m = TIMELIB_UNSET;
	in.begin->h = TIMELIB_UNSET;
	in.begin->i = TIMELIB_UNSET;
	in.begin->s = TIMELIB_UNSET;
	in.begin->f = 0;
	in.begin->z = 0;
	in.begin->dst = 0;
	in.begin->is_localtime = 0;
	in.begin->zone_type = TIMELIB_ZONETYPE_OFFSET;

	in.end = timelib_time_ctor();
	in.end->y = TIMELIB_UNSET;
	in.end->d = TIMELIB_UNSET;
	in.end->m = TIMELIB_UNSET;
	in.end->h = TIMELIB_UNSET;
	in.end->i = TIMELIB_UNSET;
	in.end->s = TIMELIB_UNSET;
	in.end->f = 0;
	in.end->z = 0;
	in.end->dst = 0;
	in.end->is_localtime = 0;
	in.end->zone_type = TIMELIB_ZONETYPE_OFFSET;

	in.period = timelib_rel_time_ctor();
	in.period->y = 0;
	in.period->d = 0;
	in.period->m = 0;
	in.period->h = 0;
	in.period->i = 0;
	in.period->s = 0;
	in.period->weekday = 0;
	in.period->weekday_behavior = 0;
	in.period->first_last_day_of = 0;
	in.period->days = TIMELIB_UNSET;

	in.recurrences = 1;

	do {
		t = scan(&in);
#ifdef DEBUG_PARSER
		printf("%d\n", t);
#endif
	} while(t != EOI);

	free(in.str);
	if (errors) {
		*errors = in.errors;
	} else {
		timelib_error_container_dtor(in.errors);
	}
	if (in.have_begin_date) {
		*begin = in.begin;
	} else {
		timelib_time_dtor(in.begin);
	}
	if (in.have_end_date) {
		*end   = in.end;
	} else {
		timelib_time_dtor(in.end);
	}
	if (in.have_period) {
		*period = in.period;
	} else {
		timelib_rel_time_dtor(in.period);
	}
	if (in.have_recurrences) {
		*recurrences = in.recurrences;
	}
}


/*
 * vim: syntax=c
 */
