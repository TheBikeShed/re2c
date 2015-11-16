/* Generated by re2c */

#include <stdio.h>
#include <stdlib.h> /* malloc, free */

static void *read_file
    ( const char *fname
    , size_t unit
    , size_t padding
    , size_t *pfsize
    )
{
    void *buffer = NULL;
    size_t fsize = 0;

    /* open file */
    FILE *f = fopen(fname, "rb");
    if(f == NULL) {
        goto error;
    }

    /* get file size */
    fseek(f, 0, SEEK_END);
    fsize = (size_t) ftell(f) / unit;
    fseek(f, 0, SEEK_SET);

    /* allocate memory for file and padding */
    buffer = malloc(unit * (fsize + padding));
    if (buffer == NULL) {
        goto error;
    }

    /* read the whole file in memory */
    if (fread(buffer, unit, fsize, f) != fsize) {
        goto error;
    }

    fclose(f);
    *pfsize = fsize;
    return buffer;

error:
    fprintf(stderr, "error: cannot read file '%s'\n", fname);
    free(buffer);
    if (f != NULL) {
        fclose(f);
    }
    return NULL;
}

enum YYCONDTYPE {
    yycNormal,
    yycComment,
    yycSkiptoeol,
    yycString,
};


#define YYCTYPE unsigned char
#define YYKEYTYPE unsigned char
#define YYPEEK() *cursor
#define YYSKIP() ++cursor
#define YYLESSTHAN(n) (limit - cursor) < n
#define YYFILL(n) { break; }

static int action_line126_Comment
    ( unsigned int i
    , const YYKEYTYPE *keys
    , const YYCTYPE *start
    , const YYCTYPE *token
    , const YYCTYPE **cursor
    , YYKEYTYPE rule_act
    )
{
    const long pos = token - start;
    const long len_act = *cursor - token;
    const long len_exp = (long) keys [3 * i + 1];
    const YYKEYTYPE rule_exp = keys [3 * i + 2];
    if (rule_exp == 255) {
        fprintf
            ( stderr
            , "warning: lex_line126_Comment: control flow is undefined for input"
                " at position %ld, rerun re2c with '-W'\n"
            , pos
            );
    }
    if (len_act == len_exp && rule_act == rule_exp) {
        const YYKEYTYPE offset = keys[3 * i];
        *cursor = token + offset;
        return 0;
    } else {
        fprintf
            ( stderr
            , "error: lex_line126_Comment: at position %ld (iteration %u):\n"
                "\texpected: match length %ld, rule %u\n"
                "\tactual:   match length %ld, rule %u\n"
            , pos
            , i
            , len_exp
            , rule_exp
            , len_act
            , rule_act
            );
        return 1;
    }
}

int lex_line126_Comment()
{
    const size_t padding = 2; /* YYMAXFILL */
    int status = 0;
    size_t input_len = 0;
    size_t keys_count = 0;
    YYCTYPE *input = NULL;
    YYKEYTYPE *keys = NULL;
    const YYCTYPE *cursor = NULL;
    const YYCTYPE *limit = NULL;
    const YYCTYPE *token = NULL;
    const YYCTYPE *eof = NULL;
    unsigned int i = 0;

    input = (YYCTYPE *) read_file
        ("condition_10.Scgif.c.line126_Comment.input"
        , sizeof (YYCTYPE)
        , padding
        , &input_len
        );
    if (input == NULL) {
        status = 1;
        goto end;
    }

    keys = (YYKEYTYPE *) read_file
        ("condition_10.Scgif.c.line126_Comment.keys"
        , 3 * sizeof (YYKEYTYPE)
        , 0
        , &keys_count
        );
    if (keys == NULL) {
        status = 1;
        goto end;
    }

    cursor = input;
    limit = input + input_len + padding;
    eof = input + input_len;

    for (i = 0; status == 0 && i < keys_count; ++i) {
        token = cursor;
        YYCTYPE yych;

        if (YYLESSTHAN (2)) YYFILL(2);
        yych = YYPEEK ();
        if (yych != '*') goto yy5;
        YYSKIP ();
        if ((yych = YYPEEK ()) == '/') goto yy6;
yy4:
        status = action_line126_Comment(i, keys, input, token, &cursor, 15);
        continue;
yy5:
        YYSKIP ();
        yych = YYPEEK ();
        goto yy4;
yy6:
        YYSKIP ();
        status = action_line126_Comment(i, keys, input, token, &cursor, 14);
        continue;

    }
    if (status == 0) {
        if (cursor != eof) {
            status = 1;
            const long pos = token - input;
            fprintf(stderr, "error: lex_line126_Comment: unused input strings left at position %ld\n", pos);
        }
        if (i != keys_count) {
            status = 1;
            fprintf(stderr, "error: lex_line126_Comment: unused keys left after %u iterations\n", i);
        }
    }

end:
    free(input);
    free(keys);

    return status;
}

#undef YYCTYPE
#undef YYKEYTYPE
#undef YYPEEK
#undef YYSKIP
#undef YYLESSTHAN
#undef YYFILL

#define YYCTYPE unsigned char
#define YYKEYTYPE unsigned char
#define YYPEEK() *cursor
#define YYSKIP() ++cursor
#define YYBACKUP() marker = cursor
#define YYRESTORE() cursor = marker
#define YYLESSTHAN(n) (limit - cursor) < n
#define YYFILL(n) { break; }

static int action_line126_Normal
    ( unsigned int i
    , const YYKEYTYPE *keys
    , const YYCTYPE *start
    , const YYCTYPE *token
    , const YYCTYPE **cursor
    , YYKEYTYPE rule_act
    )
{
    const long pos = token - start;
    const long len_act = *cursor - token;
    const long len_exp = (long) keys [3 * i + 1];
    const YYKEYTYPE rule_exp = keys [3 * i + 2];
    if (rule_exp == 255) {
        fprintf
            ( stderr
            , "warning: lex_line126_Normal: control flow is undefined for input"
                " at position %ld, rerun re2c with '-W'\n"
            , pos
            );
    }
    if (len_act == len_exp && rule_act == rule_exp) {
        const YYKEYTYPE offset = keys[3 * i];
        *cursor = token + offset;
        return 0;
    } else {
        fprintf
            ( stderr
            , "error: lex_line126_Normal: at position %ld (iteration %u):\n"
                "\texpected: match length %ld, rule %u\n"
                "\tactual:   match length %ld, rule %u\n"
            , pos
            , i
            , len_exp
            , rule_exp
            , len_act
            , rule_act
            );
        return 1;
    }
}

int lex_line126_Normal()
{
    const size_t padding = 4; /* YYMAXFILL */
    int status = 0;
    size_t input_len = 0;
    size_t keys_count = 0;
    YYCTYPE *input = NULL;
    YYKEYTYPE *keys = NULL;
    const YYCTYPE *cursor = NULL;
    const YYCTYPE *limit = NULL;
    const YYCTYPE *token = NULL;
    const YYCTYPE *eof = NULL;
    unsigned int i = 0;

    input = (YYCTYPE *) read_file
        ("condition_10.Scgif.c.line126_Normal.input"
        , sizeof (YYCTYPE)
        , padding
        , &input_len
        );
    if (input == NULL) {
        status = 1;
        goto end;
    }

    keys = (YYKEYTYPE *) read_file
        ("condition_10.Scgif.c.line126_Normal.keys"
        , 3 * sizeof (YYKEYTYPE)
        , 0
        , &keys_count
        );
    if (keys == NULL) {
        status = 1;
        goto end;
    }

    cursor = input;
    limit = input + input_len + padding;
    eof = input + input_len;

    for (i = 0; status == 0 && i < keys_count; ++i) {
        token = cursor;
        const YYCTYPE *marker = NULL;
        YYCTYPE yych;

        if (YYLESSTHAN (4)) YYFILL(4);
        yych = YYPEEK ();
        {
            static void *yytarget[256] = {
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy15, &&yy17, &&yy17, &&yy17, &&yy17, &&yy14,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy13,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy11,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17,
                &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17, &&yy17
            };
            goto *yytarget[yych];
        }
yy11:
        YYSKIP ();
        YYBACKUP ();
        yych = YYPEEK ();
        if (yych == '?') goto yy28;
yy12:
        status = action_line126_Normal(i, keys, input, token, &cursor, 13);
        continue;
yy13:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych == '*') goto yy26;
        if (yych == '/') goto yy24;
        goto yy12;
yy14:
        YYSKIP ();
        YYBACKUP ();
        yych = YYPEEK ();
        if (yych == '"') goto yy18;
        if (yych == '\\') goto yy20;
        goto yy12;
yy15:
        YYSKIP ();
        status = action_line126_Normal(i, keys, input, token, &cursor, 12);
        continue;
yy17:
        YYSKIP ();
        yych = YYPEEK ();
        goto yy12;
yy18:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych == '\'') goto yy22;
yy19:
        YYRESTORE ();
        goto yy12;
yy20:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych != '"') goto yy19;
        YYSKIP ();
        yych = YYPEEK ();
        if (yych != '\'') goto yy19;
yy22:
        YYSKIP ();
        status = action_line126_Normal(i, keys, input, token, &cursor, 11);
        continue;
yy24:
        YYSKIP ();
        status = action_line126_Normal(i, keys, input, token, &cursor, 10);
        continue;
yy26:
        YYSKIP ();
        status = action_line126_Normal(i, keys, input, token, &cursor, 9);
        continue;
yy28:
        YYSKIP ();
        yych = YYPEEK ();
        {
            static void *yytarget[256] = {
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy43, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy41,
                &&yy29, &&yy31, &&yy19, &&yy19, &&yy19, &&yy45, &&yy19, &&yy39,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy33, &&yy37, &&yy35, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19,
                &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19, &&yy19
            };
            goto *yytarget[yych];
        }
yy29:
        YYSKIP ();
        status = action_line126_Normal(i, keys, input, token, &cursor, 0);
        continue;
yy31:
        YYSKIP ();
        status = action_line126_Normal(i, keys, input, token, &cursor, 1);
        continue;
yy33:
        YYSKIP ();
        status = action_line126_Normal(i, keys, input, token, &cursor, 2);
        continue;
yy35:
        YYSKIP ();
        status = action_line126_Normal(i, keys, input, token, &cursor, 3);
        continue;
yy37:
        YYSKIP ();
        status = action_line126_Normal(i, keys, input, token, &cursor, 4);
        continue;
yy39:
        YYSKIP ();
        status = action_line126_Normal(i, keys, input, token, &cursor, 5);
        continue;
yy41:
        YYSKIP ();
        status = action_line126_Normal(i, keys, input, token, &cursor, 6);
        continue;
yy43:
        YYSKIP ();
        status = action_line126_Normal(i, keys, input, token, &cursor, 7);
        continue;
yy45:
        YYSKIP ();
        status = action_line126_Normal(i, keys, input, token, &cursor, 8);
        continue;

    }
    if (status == 0) {
        if (cursor != eof) {
            status = 1;
            const long pos = token - input;
            fprintf(stderr, "error: lex_line126_Normal: unused input strings left at position %ld\n", pos);
        }
        if (i != keys_count) {
            status = 1;
            fprintf(stderr, "error: lex_line126_Normal: unused keys left after %u iterations\n", i);
        }
    }

end:
    free(input);
    free(keys);

    return status;
}

#undef YYCTYPE
#undef YYKEYTYPE
#undef YYPEEK
#undef YYSKIP
#undef YYBACKUP
#undef YYRESTORE
#undef YYLESSTHAN
#undef YYFILL

#define YYCTYPE unsigned char
#define YYKEYTYPE unsigned char
#define YYPEEK() *cursor
#define YYSKIP() ++cursor
#define YYBACKUP() marker = cursor
#define YYRESTORE() cursor = marker
#define YYLESSTHAN(n) (limit - cursor) < n
#define YYFILL(n) { break; }

static int action_line126_Skiptoeol
    ( unsigned int i
    , const YYKEYTYPE *keys
    , const YYCTYPE *start
    , const YYCTYPE *token
    , const YYCTYPE **cursor
    , YYKEYTYPE rule_act
    )
{
    const long pos = token - start;
    const long len_act = *cursor - token;
    const long len_exp = (long) keys [3 * i + 1];
    const YYKEYTYPE rule_exp = keys [3 * i + 2];
    if (rule_exp == 255) {
        fprintf
            ( stderr
            , "warning: lex_line126_Skiptoeol: control flow is undefined for input"
                " at position %ld, rerun re2c with '-W'\n"
            , pos
            );
    }
    if (len_act == len_exp && rule_act == rule_exp) {
        const YYKEYTYPE offset = keys[3 * i];
        *cursor = token + offset;
        return 0;
    } else {
        fprintf
            ( stderr
            , "error: lex_line126_Skiptoeol: at position %ld (iteration %u):\n"
                "\texpected: match length %ld, rule %u\n"
                "\tactual:   match length %ld, rule %u\n"
            , pos
            , i
            , len_exp
            , rule_exp
            , len_act
            , rule_act
            );
        return 1;
    }
}

int lex_line126_Skiptoeol()
{
    const size_t padding = 5; /* YYMAXFILL */
    int status = 0;
    size_t input_len = 0;
    size_t keys_count = 0;
    YYCTYPE *input = NULL;
    YYKEYTYPE *keys = NULL;
    const YYCTYPE *cursor = NULL;
    const YYCTYPE *limit = NULL;
    const YYCTYPE *token = NULL;
    const YYCTYPE *eof = NULL;
    unsigned int i = 0;

    input = (YYCTYPE *) read_file
        ("condition_10.Scgif.c.line126_Skiptoeol.input"
        , sizeof (YYCTYPE)
        , padding
        , &input_len
        );
    if (input == NULL) {
        status = 1;
        goto end;
    }

    keys = (YYKEYTYPE *) read_file
        ("condition_10.Scgif.c.line126_Skiptoeol.keys"
        , 3 * sizeof (YYKEYTYPE)
        , 0
        , &keys_count
        );
    if (keys == NULL) {
        status = 1;
        goto end;
    }

    cursor = input;
    limit = input + input_len + padding;
    eof = input + input_len;

    for (i = 0; status == 0 && i < keys_count; ++i) {
        token = cursor;
        const YYCTYPE *marker = NULL;
        YYCTYPE yych;

        if (YYLESSTHAN (5)) YYFILL(5);
        yych = YYPEEK ();
        {
            static void *yytarget[256] = {
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy54, &&yy56, &&yy56, &&yy53, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy50,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy52, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56,
                &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56, &&yy56
            };
            goto *yytarget[yych];
        }
yy50:
        YYSKIP ();
        YYBACKUP ();
        yych = YYPEEK ();
        if (yych == '?') goto yy63;
yy51:
        status = action_line126_Skiptoeol(i, keys, input, token, &cursor, 20);
        continue;
yy52:
        YYSKIP ();
        YYBACKUP ();
        yych = YYPEEK ();
        if (yych == '\n') goto yy61;
        if (yych == '\r') goto yy59;
        goto yy51;
yy53:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych == '\n') goto yy57;
        goto yy51;
yy54:
        YYSKIP ();
        status = action_line126_Skiptoeol(i, keys, input, token, &cursor, 19);
        continue;
yy56:
        YYSKIP ();
        yych = YYPEEK ();
        goto yy51;
yy57:
        YYSKIP ();
        status = action_line126_Skiptoeol(i, keys, input, token, &cursor, 18);
        continue;
yy59:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych == '\n') goto yy61;
yy60:
        YYRESTORE ();
        goto yy51;
yy61:
        YYSKIP ();
        status = action_line126_Skiptoeol(i, keys, input, token, &cursor, 17);
        continue;
yy63:
        YYSKIP ();
        yych = YYPEEK ();
        if (yych != '/') goto yy60;
        YYSKIP ();
        yych = YYPEEK ();
        if (yych == '\n') goto yy66;
        if (yych != '\r') goto yy60;
        YYSKIP ();
        yych = YYPEEK ();
        if (yych != '\n') goto yy60;
yy66:
        YYSKIP ();
        status = action_line126_Skiptoeol(i, keys, input, token, &cursor, 16);
        continue;

    }
    if (status == 0) {
        if (cursor != eof) {
            status = 1;
            const long pos = token - input;
            fprintf(stderr, "error: lex_line126_Skiptoeol: unused input strings left at position %ld\n", pos);
        }
        if (i != keys_count) {
            status = 1;
            fprintf(stderr, "error: lex_line126_Skiptoeol: unused keys left after %u iterations\n", i);
        }
    }

end:
    free(input);
    free(keys);

    return status;
}

#undef YYCTYPE
#undef YYKEYTYPE
#undef YYPEEK
#undef YYSKIP
#undef YYBACKUP
#undef YYRESTORE
#undef YYLESSTHAN
#undef YYFILL

#define YYCTYPE unsigned char
#define YYKEYTYPE unsigned char
#define YYPEEK() *cursor
#define YYSKIP() ++cursor
#define YYLESSTHAN(n) (limit - cursor) < n
#define YYFILL(n) { break; }

static int action_line126_String
    ( unsigned int i
    , const YYKEYTYPE *keys
    , const YYCTYPE *start
    , const YYCTYPE *token
    , const YYCTYPE **cursor
    , YYKEYTYPE rule_act
    )
{
    const long pos = token - start;
    const long len_act = *cursor - token;
    const long len_exp = (long) keys [3 * i + 1];
    const YYKEYTYPE rule_exp = keys [3 * i + 2];
    if (rule_exp == 255) {
        fprintf
            ( stderr
            , "warning: lex_line126_String: control flow is undefined for input"
                " at position %ld, rerun re2c with '-W'\n"
            , pos
            );
    }
    if (len_act == len_exp && rule_act == rule_exp) {
        const YYKEYTYPE offset = keys[3 * i];
        *cursor = token + offset;
        return 0;
    } else {
        fprintf
            ( stderr
            , "error: lex_line126_String: at position %ld (iteration %u):\n"
                "\texpected: match length %ld, rule %u\n"
                "\tactual:   match length %ld, rule %u\n"
            , pos
            , i
            , len_exp
            , rule_exp
            , len_act
            , rule_act
            );
        return 1;
    }
}

int lex_line126_String()
{
    const size_t padding = 2; /* YYMAXFILL */
    int status = 0;
    size_t input_len = 0;
    size_t keys_count = 0;
    YYCTYPE *input = NULL;
    YYKEYTYPE *keys = NULL;
    const YYCTYPE *cursor = NULL;
    const YYCTYPE *limit = NULL;
    const YYCTYPE *token = NULL;
    const YYCTYPE *eof = NULL;
    unsigned int i = 0;

    input = (YYCTYPE *) read_file
        ("condition_10.Scgif.c.line126_String.input"
        , sizeof (YYCTYPE)
        , padding
        , &input_len
        );
    if (input == NULL) {
        status = 1;
        goto end;
    }

    keys = (YYKEYTYPE *) read_file
        ("condition_10.Scgif.c.line126_String.keys"
        , 3 * sizeof (YYKEYTYPE)
        , 0
        , &keys_count
        );
    if (keys == NULL) {
        status = 1;
        goto end;
    }

    cursor = input;
    limit = input + input_len + padding;
    eof = input + input_len;

    for (i = 0; status == 0 && i < keys_count; ++i) {
        token = cursor;
        YYCTYPE yych;

        if (YYLESSTHAN (2)) YYFILL(2);
        yych = YYPEEK ();
        if (yych == '"') goto yy73;
        if (yych != '\\') goto yy75;
        YYSKIP ();
        if ((yych = YYPEEK ()) != '\n') goto yy76;
yy72:
        status = action_line126_String(i, keys, input, token, &cursor, 23);
        continue;
yy73:
        YYSKIP ();
        status = action_line126_String(i, keys, input, token, &cursor, 22);
        continue;
yy75:
        YYSKIP ();
        yych = YYPEEK ();
        goto yy72;
yy76:
        YYSKIP ();
        status = action_line126_String(i, keys, input, token, &cursor, 21);
        continue;

    }
    if (status == 0) {
        if (cursor != eof) {
            status = 1;
            const long pos = token - input;
            fprintf(stderr, "error: lex_line126_String: unused input strings left at position %ld\n", pos);
        }
        if (i != keys_count) {
            status = 1;
            fprintf(stderr, "error: lex_line126_String: unused keys left after %u iterations\n", i);
        }
    }

end:
    free(input);
    free(keys);

    return status;
}

#undef YYCTYPE
#undef YYKEYTYPE
#undef YYPEEK
#undef YYSKIP
#undef YYLESSTHAN
#undef YYFILL

int main()
{
    if(lex_line126_Comment() != 0) {
        return 1;
    }
    if(lex_line126_Normal() != 0) {
        return 1;
    }
    if(lex_line126_Skiptoeol() != 0) {
        return 1;
    }
    if(lex_line126_String() != 0) {
        return 1;
    }
    return 0;
}
*/* *.*0*� )+�??(??)??<??>??=??/??'??!??-?? ?? ??"??&??*??,??.??0??;?????�? ?>?@?�///*/ /)/+/./0/�'"''" '"&'"('"�'\"''\" '\"&'\"('\"�'\ '\!'\#'\�' '!'#'[']'�" !#&(.0>@� 
	??/
??/ ??/	??/??/�??/
??/ ??/	??/??/??/??/�?? ??.??0??�? ?>?@?�\
\ \	\\�\
\ \	\\\\�
 	�
 	>@[]�\ \	\\�\
" !#[]�