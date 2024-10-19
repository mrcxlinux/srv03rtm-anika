
/* A Bison parser, made from parse.y
   by GNU bison 1.29.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	YYIDENT	257
# define	YYINT	258
# define	YYSTRING	259
# define	YYSHEET	260
# define	YYSHEETREF	261
# define	YYRECT	262
# define	YYPOINT	263
# define	YYRGB	264
# define	YYARGB	265
# define	YYGRADIENT	266
# define	YYGRAPHIC	267
# define	YYDFC	268
# define	YYDTB	269
# define	YYTRUE	270
# define	YYFALSE	271
# define	YYRESID	272
# define	YYATOM	273
# define	YYRCSTR	274
# define	YYRCBMP	275
# define	YYRCINT	276
# define	YYRCCHAR	277
# define	YYPT	278
# define	YYRP	279
# define	YYSYSMETRIC	280
# define	YYSYSMETRICSTR	281
# define	YYHANDLEMAP	282



#include "stdafx.h"
#include "parser.h"

#include "duiparserobj.h"

#pragma warning (push,3)
#pragma warning (disable:4242)
#pragma warning (disable:4244)

namespace DirectUI
{

// Parser prototypes
void yyerror(LPCSTR s);  // Parser direct call
int yylex(BOOL* pfRes);
extern int yylineno;
extern char* yytext;

void CallbackParseError(LPCWSTR pszError, LPCWSTR pszToken);

// Check if callback forced an error
#define CBCHK()         if (Parser::g_fParseAbort || FAILED(Parser::g_hrParse)) YYABORT;
#define HRCHK()         if (FAILED(Parser::g_hrParse)) YYABORT;

#define MEMCHK(m)       if (!(m)) { Parser::g_hrParse = E_OUTOFMEMORY; YYABORT; }

#define CUSTOMALLOC     HAlloc
#define CUSTOMFREE      HFree

#define ppc Parser::g_pParserCtx
#define hr  Parser::g_hrParse

// Tail of namespace wrap is located in bison.skl to allow for wrapping
// auto-generated tables
//} // namespace DirectUI


typedef union
{
    /// Temporary data returned from tokens (lexer) and productions (parser)
    int num;                    /// Stored by lexer (YYINT) and inter-production data transfer
    WCHAR ident[MAXIDENT];      /// Stored by lexer (YYIDENT)
    LPWSTR str;                 /// Tracked pointer with quotes stripped (YYSTRING)

    EnumsList el;               /// Inter-production data transfer
    ParamsList pl;              /// Inter-production data transfer
    StartTag st;                /// Inter-production data transfer
    COLORREF cr;                /// Inter-production data transfer
    HANDLE h;                   /// Inter-production data transfer

    ValueNode* pvn;             /// NT_ValueNode
    PropValPairNode* ppvpn;     /// NT_PropValPairNode
    ElementNode* pen;           /// NT_ElementNode
    AttribNode* pan;            /// NT_AttribNode
    RuleNode* prn;              /// NT_RuleNode
    SheetNode* psn;             /// NT_SheetNode
} YYSTYPE;
#include <stdio.h>



#define	YYFINAL		239
#define	YYFLAG		-32768
#define	YYNTBASE	44

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 282 ? yytranslate[x] : 68)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,     2,     2,     2,     2,     2,
      33,    35,     2,     2,    34,     2,     2,    31,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    42,    43,
      29,    32,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,    36,    38,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28
};

#if YYDEBUG != 0
static const short yyprhs[] =
{
       0,     0,     3,     6,     8,    10,    14,    18,    21,    23,
      28,    34,    38,    43,    48,    54,    61,    66,    72,    75,
      77,    81,    84,    86,    90,    92,    94,    96,   107,   114,
     116,   125,   136,   143,   152,   157,   164,   181,   186,   193,
     210,   229,   231,   236,   243,   248,   250,   254,   259,   264,
     269,   271,   274,   277,   279,   284,   289,   294,   296,   300,
     309,   320,   324,   326,   331,   335,   337,   347,   350,   352,
     358,   363,   366,   368,   374,   378,   385,   388,   390
};
static const short yyrhs[] =
{
      44,    45,     0,    44,    61,     0,    45,     0,    61,     0,
      46,    49,    47,     0,    46,     5,    47,     0,    46,    47,
       0,    48,     0,    29,     3,    51,    30,     0,    29,     3,
      50,    51,    30,     0,    29,     3,    30,     0,    29,     3,
      50,    30,     0,    29,    31,     3,    30,     0,    29,     3,
      51,    31,    30,     0,    29,     3,    50,    51,    31,    30,
       0,    29,     3,    31,    30,     0,    29,     3,    50,    31,
      30,     0,    49,    45,     0,    45,     0,    18,    32,     3,
       0,    51,    52,     0,    52,     0,     3,    32,    53,     0,
      54,     0,    16,     0,    17,     0,     8,    33,    54,    34,
      54,    34,    54,    34,    54,    35,     0,     9,    33,    54,
      34,    54,    35,     0,    57,     0,    12,    33,    57,    34,
      57,    34,     4,    35,     0,    12,    33,    57,    34,    57,
      34,    57,    34,     4,    35,     0,    14,    33,    54,    34,
      54,    35,     0,    15,    33,    59,    34,    54,    34,    54,
      35,     0,    13,    33,     5,    35,     0,    13,    33,     5,
      34,     4,    35,     0,    13,    33,     5,    34,     4,    34,
       4,    34,    54,    34,    54,    34,     4,    34,     4,    35,
       0,    21,    33,     4,    35,     0,    21,    33,     4,    34,
       4,    35,     0,    21,    33,     4,    34,     4,    34,     4,
      34,    54,    34,    54,    34,     4,    34,     4,    35,     0,
      21,    33,     4,    34,     4,    34,     4,    34,    54,    34,
      54,    34,     4,    34,     4,    34,    59,    35,     0,     5,
       0,    20,    33,     4,    35,     0,    20,    33,     4,    34,
      59,    35,     0,    27,    33,     4,    35,     0,    58,     0,
       3,    33,    35,     0,     3,    33,    60,    35,     0,     7,
      33,     3,    35,     0,    19,    33,     3,    35,     0,    55,
       0,    55,    24,     0,    55,    25,     0,    56,     0,    22,
      33,     4,    35,     0,    23,    33,     4,    35,     0,    26,
      33,     4,    35,     0,     4,     0,    56,    36,     4,     0,
      10,    33,     4,    34,     4,    34,     4,    35,     0,    11,
      33,     4,    34,     4,    34,     4,    34,     4,    35,     0,
      58,    36,     3,     0,     3,     0,    28,    33,     4,    35,
       0,    60,    34,     4,     0,     4,     0,    29,     6,    50,
      30,    62,    29,    31,     6,    30,     0,    62,    63,     0,
      63,     0,     3,    64,    37,    66,    38,     0,     3,    37,
      66,    38,     0,    64,    65,     0,    65,     0,    39,     3,
      32,    53,    40,     0,    39,     3,    40,     0,    39,     3,
      41,    32,    53,    40,     0,    66,    67,     0,    67,     0,
       3,    42,    53,    43,     0
};

#endif

#if YYDEBUG != 0
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   124,   128,   132,   136,   142,   153,   162,   171,   177,
     182,   187,   193,   200,   205,   210,   215,   220,   227,   233,
     238,   242,   248,   253,   259,   264,   269,   274,   279,   284,
     289,   294,   299,   304,   309,   316,   323,   334,   339,   344,
     353,   362,   367,   372,   377,   383,   388,   395,   404,   408,
     415,   418,   421,   426,   429,   440,   451,   456,   459,   464,
     468,   474,   482,   492,   497,   503,   511,   517,   523,   528,
     532,   538,   544,   549,   554,   559,   566,   572,   577
};
#endif


#if YYDEBUG != 0 || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "YYIDENT", "YYINT", "YYSTRING", "YYSHEET", 
  "YYSHEETREF", "YYRECT", "YYPOINT", "YYRGB", "YYARGB", "YYGRADIENT", 
  "YYGRAPHIC", "YYDFC", "YYDTB", "YYTRUE", "YYFALSE", "YYRESID", "YYATOM", 
  "YYRCSTR", "YYRCBMP", "YYRCINT", "YYRCCHAR", "YYPT", "YYRP", 
  "YYSYSMETRIC", "YYSYSMETRICSTR", "YYHANDLEMAP", "'<'", "'>'", "'/'", 
  "'='", "'('", "','", "')'", "'|'", "'{'", "'}'", "'['", "']'", "'!'", 
  "':'", "';'", "document", "element", "stag", "etag", "nctag", 
  "children", "resid", "pvpairs", "pvpair", "value", "number", 
  "magnitude", "bitmask", "argb", "enum", "handle", "params", "sheet", 
  "rules", "rule", "attribs", "attrib", "decls", "decl", NULL
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    44,    44,    44,    44,    45,    45,    45,    45,    46,
      46,    46,    46,    47,    48,    48,    48,    48,    49,    49,
      50,    51,    51,    52,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      54,    54,    54,    55,    55,    55,    55,    56,    56,    57,
      57,    58,    58,    59,    60,    60,    61,    62,    62,    63,
      63,    64,    64,    65,    65,    65,    66,    66,    67
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     2,     2,     1,     1,     3,     3,     2,     1,     4,
       5,     3,     4,     4,     5,     6,     4,     5,     2,     1,
       3,     2,     1,     3,     1,     1,     1,    10,     6,     1,
       8,    10,     6,     8,     4,     6,    16,     4,     6,    16,
      18,     1,     4,     6,     4,     1,     3,     4,     4,     4,
       1,     2,     2,     1,     4,     4,     4,     1,     3,     8,
      10,     3,     1,     4,     3,     1,     9,     2,     1,     5,
       4,     2,     1,     5,     3,     6,     2,     1,     4
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       0,     0,     0,     3,     0,     8,     4,     0,     0,     1,
       2,     0,     0,    19,     7,     0,     0,     0,    11,     0,
       0,     0,    22,     0,     0,     6,     0,    18,     5,     0,
       0,    16,    12,     0,     0,     9,     0,    21,     0,     0,
      62,    57,    41,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    25,    26,     0,     0,     0,     0,     0,     0,
       0,    23,    24,    50,    53,    29,    45,    20,    17,    10,
       0,    14,     0,     0,    68,    13,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,    52,     0,     0,    15,     0,     0,
       0,    72,     0,    67,    65,    46,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    58,    61,     0,     0,    77,     0,
       0,    71,     0,     0,    47,    48,     0,     0,     0,     0,
       0,     0,    34,     0,     0,     0,    49,     0,    42,     0,
      37,    54,    55,    56,    44,     0,    70,    76,     0,    74,
       0,     0,     0,    64,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    69,    66,
       0,    28,     0,     0,     0,     0,    35,    32,    63,     0,
      43,     0,    38,    78,    73,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    75,     0,    59,     0,    30,     0,
       0,    33,     0,     0,     0,     0,     0,     0,    27,    60,
      31,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,     0,    39,     0,    40,     0,     0
};

static const short yydefgoto[] =
{
       2,     3,     4,    14,     5,    15,    20,    21,    22,    61,
      62,    63,    64,    65,    66,   116,   106,     6,    73,    74,
     100,   101,   127,   128
};

static const short yypact[] =
{
     -12,    18,     8,-32768,     5,-32768,-32768,    13,    34,-32768,
  -32768,     9,    20,-32768,-32768,    37,    39,    67,-32768,    59,
      15,    17,-32768,    86,    72,-32768,   114,-32768,-32768,    65,
     115,-32768,-32768,    89,    19,-32768,    90,-32768,   118,    92,
      91,-32768,-32768,    93,    95,    96,    97,    98,   100,   102,
     103,   104,-32768,-32768,   105,   106,   107,   108,   109,   112,
     113,-32768,-32768,    30,   111,-32768,   116,-32768,-32768,-32768,
     119,-32768,    56,     6,-32768,-32768,     7,   120,    10,    10,
     121,   144,    87,   145,    10,   123,   150,   151,   152,   153,
     154,   155,   156,-32768,-32768,   157,   159,-32768,   160,   161,
      57,-32768,   134,-32768,-32768,-32768,    -5,   131,   133,   135,
     136,   137,   138,    66,   139,   141,   142,   140,    71,    73,
     143,   146,   147,   148,-32768,-32768,   126,     1,-32768,   -13,
     160,-32768,   171,   175,-32768,-32768,    10,    10,   176,   180,
      87,   181,-32768,    10,   182,    10,-32768,   123,-32768,   183,
  -32768,-32768,-32768,-32768,-32768,    65,-32768,-32768,    65,-32768,
     122,     2,   158,-32768,   162,   163,   165,   166,   167,    75,
     168,   169,   172,   170,    78,   149,   173,    65,-32768,-32768,
      10,-32768,   185,   186,    52,   187,-32768,-32768,-32768,    10,
  -32768,   189,-32768,-32768,-32768,   174,   177,   184,   178,   188,
     190,   191,   192,   194,-32768,    10,-32768,   193,-32768,   198,
      10,-32768,    10,   195,   196,   197,   199,   200,-32768,-32768,
  -32768,    10,    10,   201,   202,   203,   204,   205,   206,   211,
     212,   207,    80,-32768,   123,-32768,   208,-32768,   209,-32768
};

static const short yypgoto[] =
{
  -32768,    11,-32768,    42,-32768,-32768,   210,   217,    -9,   -94,
     -78,-32768,-32768,   -80,-32768,  -144,-32768,   215,-32768,   179,
  -32768,    94,    99,  -120
};


#define	YYLAST		252


static const short yytable[] =
{
     108,   109,   112,   173,   126,   126,   114,   157,   238,    72,
      11,   104,    37,     9,    41,    13,    16,     1,    16,   158,
      16,     7,    16,     7,     8,    37,    27,   159,   160,   133,
     134,    17,    57,    58,    12,   102,    59,     1,    24,   156,
     178,   157,   105,    18,    19,    32,    33,    35,    36,    69,
      70,    26,    17,    25,    93,    94,   199,    28,   164,   165,
     168,   175,    46,    47,   176,   170,    12,   172,    40,    41,
      42,    29,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,   195,    54,    55,    56,    57,    58,    31,
     236,    59,    60,    98,   130,    99,    99,    46,    47,    30,
     141,   142,   196,    26,   200,   147,   148,   149,   150,   185,
     186,   202,   191,   192,   234,   235,    38,    39,    67,    68,
      71,    72,    75,   107,    76,   110,    77,   213,    78,    79,
      80,    81,   216,    82,   217,    83,    84,    85,    86,    87,
      88,    89,    90,   223,   224,    91,    92,    95,   111,    97,
     113,   115,    96,   117,   177,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   129,   132,   135,   136,   155,   137,
     138,   139,   140,   143,   144,   146,   145,   162,   151,   163,
     166,   152,   153,   154,   167,   169,   171,   174,   179,   197,
     198,   201,   193,   203,   131,     0,   180,   214,   181,   182,
     183,   184,   215,   187,   188,   190,   189,   227,   228,   239,
       0,   205,   207,   194,   204,   231,   232,    10,    23,   206,
       0,     0,     0,   208,   209,   210,     0,   211,   212,   161,
     218,   219,   220,   221,   222,   225,   226,    34,     0,   229,
     230,     0,   233,   237,     0,     0,     0,     0,     0,     0,
       0,     0,   103
};

static const short yycheck[] =
{
      78,    79,    82,   147,     3,     3,    84,   127,     0,     3,
       5,     4,    21,     2,     4,     4,     3,    29,     3,    32,
       3,     3,     3,     3,     6,    34,    15,    40,    41,    34,
      35,    18,    22,    23,    29,    29,    26,    29,    29,    38,
      38,   161,    35,    30,    31,    30,    31,    30,    31,    30,
      31,    31,    18,    11,    24,    25,     4,    15,   136,   137,
     140,   155,    10,    11,   158,   143,    29,   145,     3,     4,
       5,    32,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,   177,    19,    20,    21,    22,    23,    30,
     234,    26,    27,    37,    37,    39,    39,    10,    11,    32,
      34,    35,   180,    31,   184,    34,    35,    34,    35,    34,
      35,   189,    34,    35,    34,    35,    30,     3,     3,    30,
      30,     3,    30,     3,    33,     4,    33,   205,    33,    33,
      33,    33,   210,    33,   212,    33,    33,    33,    33,    33,
      33,    33,    33,   221,   222,    33,    33,    36,     4,    30,
       5,    28,    36,     3,    32,     4,     4,     4,     4,     4,
       4,     4,     3,     3,     3,    31,    35,    34,    42,    34,
      34,    34,    34,    34,    33,    35,    34,     6,    35,     4,
       4,    35,    35,    35,     4,     4,     4,     4,    30,     4,
       4,     4,    43,     4,   100,    -1,    34,     4,    35,    34,
      34,    34,     4,    35,    35,    35,    34,     4,     4,     0,
      -1,    34,    34,    40,    40,     4,     4,     2,     8,    35,
      -1,    -1,    -1,    35,    34,    34,    -1,    35,    34,   130,
      35,    35,    35,    34,    34,    34,    34,    20,    -1,    34,
      34,    -1,    35,    35,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */

/* Skeleton output parser for bison,
   Copyright 1984, 1989, 1990, 2000, 2001 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
# ifdef alloca
#  define YYSTACK_USE_ALLOCA 1
# else /* alloca not defined */
#  ifdef __GNUC__
#   define YYSTACK_USE_ALLOCA 1
#   define alloca __builtin_alloca
#  else /* not GNU C.  */
#   if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#    define YYSTACK_USE_ALLOCA 1
#    include <alloca.h>
#   else /* not sparc */
     /* We think this test detects Watcom and Microsoft C.  */
     /* This used to test MSDOS, but that is a bad idea since that
	symbol is in the user namespace.  */
#    if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#     if 0
       /* No need for malloc.h, which pollutes the namespace; instead,
	  just don't use alloca.  */
#      include <malloc.h>
#     endif
#    else /* not MSDOS, or __TURBOC__ */
#     if defined(_AIX)
       /* I don't know what this was needed for, but it pollutes the
	  namespace.  So I turned it off.  rms, 2 May 1997.  */
       /* #include <malloc.h>  */
 #pragma alloca
#      define YYSTACK_USE_ALLOCA 1
#     else /* not MSDOS, or __TURBOC__, or _AIX */
#      if 0
	/* haible@ilog.fr says this works for HPUX 9.05 and up, and on
	   HPUX 10.  Eventually we can turn this on.  */
#       ifdef __hpux
#        define YYSTACK_USE_ALLOCA 1
#        define alloca __builtin_alloca
#  	endif /* __hpux */
#      endif
#     endif /* not _AIX */
#    endif /* not MSDOS, or __TURBOC__ */
#   endif /* not sparc */
#  endif /* not GNU C */
# endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#if YYSTACK_USE_ALLOCA
# define YYSTACK_ALLOC alloca
#else
# define YYSTACK_ALLOC malloc
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

//
// 4chan: add lex_result param to YYLEX definition
//
#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&lex_result, &yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&lex_result, &yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&lex_result, &yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&lex_result, &yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex (&lex_result)
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG
# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    fprintf Args;				\
} while (0)
/* Nonzero means print parse trace. [The following comment makes no
   sense to me.  Could someone clarify it?  --akim] Since this is
   uninitialized, it does not stop multiple parsers from coexisting.
   */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).  */
#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
# define __yy_memcpy(To, From, Count)	__builtin_memcpy (To, From, Count)
#else				/* not GNU C or C++ */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
# ifndef __cplusplus
__yy_memcpy (to, from, count)
     char *to;
     const char *from;
     unsigned int count;
# else /* __cplusplus */
__yy_memcpy (char *to, const char *from, unsigned int count)
# endif
{
  register const char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif



/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# ifdef __cplusplus
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else /* !__cplusplus */
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif /* !__cplusplus */
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define _YY_DECL_VARIABLES				\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
_YY_DECL_VARIABLES				\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
_YY_DECL_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yysv': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
# if YYLSP_NEEDED
  YYLTYPE yyloc;
# endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;
  
 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack. Use copies of
	 these so that the &'s don't force the real ones into memory.
	 */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#if YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of the
	 data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow ("parser stack overflow",
		  &yyss1, size * sizeof (*yyssp),
		  &yyvs1, size * sizeof (*yyvsp),
		  &yyls1, size * sizeof (*yylsp),
		  &yystacksize);
# else
      yyoverflow ("parser stack overflow",
		  &yyss1, size * sizeof (*yyssp),
		  &yyvs1, size * sizeof (*yyvsp),
		  &yystacksize);
# endif

      yyss = yyss1; yyvs = yyvs1;
# if YYLSP_NEEDED
      yyls = yyls1;
# endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror ("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
# if YYLSP_NEEDED
	      free (yyls);
# endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
# ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
# endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
# if YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
# endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#if YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %d\n", yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  //
  // 4chan: add lex_result param & check below
  //
  BOOL lex_result = true;
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
      if (!lex_result)
      {
        yyerror("failure in scanner");
        return 3;
      }
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
{
                                                    hr = ppc->_pdaElementList->Add(yyvsp[0].pen);
                                                    HRCHK();
                                                ;
    break;}
case 2:
{
                                                    hr = ppc->_pdaSheetList->Add(yyvsp[0].psn);
                                                    HRCHK();
                                                ;
    break;}
case 3:
{
                                                    ppc->_pdaElementList->Add(yyvsp[0].pen);
                                                    HRCHK();
                                                ;
    break;}
case 4:
{
                                                    ppc->_pdaSheetList->Add(yyvsp[0].psn);
                                                    HRCHK();
                                                ;
    break;}
case 5:
{
                                                    if (_wcsicmp(yyvsp[-2].st.szTag, yyvsp[0].ident))
                                                    {
                                                        CallbackParseError(L"Mismatched tag", yyvsp[0].ident);
                                                        YYABORT;
                                                    }
                                                    yyval.pen = ppc->_CreateElementNode(&yyvsp[-2].st, NULL);
                                                    CBCHK();

                                                    yyval.pen->pChild = yyvsp[-1].pen;
                                                ;
    break;}
case 6:
{
                                                    if (_wcsicmp(yyvsp[-2].st.szTag, yyvsp[0].ident))
                                                    {
                                                        CallbackParseError(L"Mismatched tag", yyvsp[0].ident);
                                                        YYABORT;
                                                    }
                                                    yyval.pen = ppc->_CreateElementNode(&yyvsp[-2].st, Value::CreateString(yyvsp[-1].str));
                                                    CBCHK();
                                                ;
    break;}
case 7:
{
                                                    if (_wcsicmp(yyvsp[-1].st.szTag, yyvsp[0].ident))
                                                    {
                                                        CallbackParseError(L"Mismatched tag", yyvsp[0].ident);
                                                        YYABORT;
                                                    }
                                                    yyval.pen = ppc->_CreateElementNode(&yyvsp[-1].st, NULL);
                                                    CBCHK();
                                                ;
    break;}
case 8:
{
                                                    yyval.pen = ppc->_CreateElementNode(&yyvsp[0].st, NULL);
                                                    CBCHK();
                                                ;
    break;}
case 9:
{
                                                    wcscpy(yyval.st.szTag, yyvsp[-2].ident);
                                                    yyval.st.szResID[0] = 0;
                                                    yyval.st.pPVNodes = yyvsp[-1].ppvpn;
                                                ;
    break;}
case 10:
{
                                                    wcscpy(yyval.st.szTag, yyvsp[-3].ident);
                                                    wcscpy(yyval.st.szResID, yyvsp[-2].ident);
                                                    yyval.st.pPVNodes = yyvsp[-1].ppvpn;
                                                ;
    break;}
case 11:
{
                                                    wcscpy(yyval.st.szTag, yyvsp[-1].ident);
                                                    yyval.st.szResID[0] = 0;
                                                    yyval.st.pPVNodes = NULL;
                                                ;
    break;}
case 12:
{
                                                    wcscpy(yyval.st.szTag, yyvsp[-2].ident);
                                                    wcscpy(yyval.st.szResID, yyvsp[-1].ident);
                                                    yyval.st.pPVNodes = NULL;
                                                ;
    break;}
case 13:
{
                                                    wcscpy(yyval.ident, yyvsp[-1].ident);
                                                ;
    break;}
case 14:
{
                                                    wcscpy(yyval.st.szTag, yyvsp[-3].ident);
                                                    yyval.st.szResID[0] = 0;
                                                    yyval.st.pPVNodes = yyvsp[-2].ppvpn;
                                                ;
    break;}
case 15:
{
                                                    wcscpy(yyval.st.szTag, yyvsp[-4].ident);
                                                    wcscpy(yyval.st.szResID, yyvsp[-3].ident);
                                                    yyval.st.pPVNodes = yyvsp[-2].ppvpn;
                                                ;
    break;}
case 16:
{
                                                    wcscpy(yyval.st.szTag, yyvsp[-2].ident);
                                                    yyval.st.szResID[0] = 0;
                                                    yyval.st.pPVNodes = NULL;
                                                ;
    break;}
case 17:
{
                                                    wcscpy(yyval.st.szTag, yyvsp[-3].ident);
                                                    wcscpy(yyval.st.szResID, yyvsp[-2].ident);
                                                    yyval.st.pPVNodes = NULL;
                                                ;
    break;}
case 18:
{
                                                    ElementNode* pn = yyvsp[-1].pen;
                                                    while(pn->pNext) pn = pn->pNext;
                                                    pn->pNext = yyvsp[0].pen;
                                                    yyval.pen = yyvsp[-1].pen;
                                                ;
    break;}
case 19:
{
                                                    yyval.pen = yyvsp[0].pen;
                                                ;
    break;}
case 20:
{
                                                    wcscpy(yyval.ident, yyvsp[0].ident);
                                                ;
    break;}
case 21:
{
                                                    PropValPairNode* ppvpn = yyvsp[-1].ppvpn;
                                                    while(ppvpn->pNext) ppvpn = ppvpn->pNext;
                                                    ppvpn->pNext = yyvsp[0].ppvpn;
                                                    yyval.ppvpn = yyvsp[-1].ppvpn;
                                                ;
    break;}
case 22:
{
                                                    yyval.ppvpn = yyvsp[0].ppvpn;
                                                ;
    break;}
case 23:
{
                                                    yyval.ppvpn = ppc->_CreatePropValPairNode(yyvsp[-2].ident, yyvsp[0].pvn);
                                                    CBCHK();
                                                ;
    break;}
case 24:
{
                                                    // DUIV_INT
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateInt(yyvsp[0].num));
                                                    CBCHK();
                                                ;
    break;}
case 25:
{
                                                    // DUIV_BOOL
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::pvBoolTrue);
                                                    CBCHK();
                                                ;
    break;}
case 26:
{
                                                    // DUIV_BOOL
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::pvBoolFalse);
                                                    CBCHK();
                                                ;
    break;}
case 27:
{
                                                    // DUIV_RECT
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateRect(yyvsp[-7].num, yyvsp[-5].num, yyvsp[-3].num, yyvsp[-1].num));
                                                    CBCHK();
                                                ;
    break;}
case 28:
{
                                                    // DUIV_POINT
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreatePoint(yyvsp[-3].num, yyvsp[-1].num));
                                                    CBCHK();
                                                ;
    break;}
case 29:
{
                                                    // DUIV_FILL
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateColor(yyvsp[0].cr));
                                                    CBCHK();
                                                ;
    break;}
case 30:
{
                                                    // DUIV_FILL
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateColor(yyvsp[-5].cr, yyvsp[-3].cr, (BYTE)yyvsp[-1].num));
                                                    CBCHK();
                                                ;
    break;}
case 31:
{
                                                    // DUIV_FILL
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateColor(yyvsp[-7].cr, yyvsp[-5].cr, yyvsp[-3].cr, (BYTE)yyvsp[-1].num));
                                                    CBCHK();
                                                ;
    break;}
case 32:
{
                                                    // DUIV_FILL
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateDFCFill(yyvsp[-3].num, yyvsp[-1].num));
                                                    CBCHK();
                                                ;
    break;}
case 33:
{
                                                    // DUIV_FILL
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateDTBFill(yyvsp[-5].h, yyvsp[-3].num, yyvsp[-1].num));
                                                    CBCHK();
                                                ;
    break;}
case 34:
{
                                                    // DUIV_GRAPHIC
                                                    WCHAR szGraphicPath[MAX_PATH];
                                                    ppc->GetPath(yyvsp[-1].str, szGraphicPath, sizeof(szGraphicPath));
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateGraphic(szGraphicPath));
                                                    CBCHK();
                                                ;
    break;}
case 35:
{
                                                    // DUIV_GRAPHIC
                                                    WCHAR szGraphicPath[MAX_PATH];
                                                    ppc->GetPath(yyvsp[-3].str, szGraphicPath, sizeof(szGraphicPath));
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateGraphic(szGraphicPath, (BYTE)yyvsp[-1].num));
                                                    CBCHK();
                                                ;
    break;}
case 36:
{
                                                    // DUIV_GRAPHIC
                                                    WCHAR szGraphicPath[MAX_PATH];
                                                    bool bFlip = true;
                                                    bool bRTL = false;
                                                    ppc->GetPath(yyvsp[-13].str, szGraphicPath, sizeof(szGraphicPath));
                                                    if (!yyvsp[-3].num) bFlip = false;
                                                    if (yyvsp[-1].num) bRTL = true;
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateGraphic(szGraphicPath, (BYTE)yyvsp[-11].num, (UINT)yyvsp[-9].num, yyvsp[-7].num, yyvsp[-5].num, NULL, bFlip, bRTL));
                                                    CBCHK();
                                                ;
    break;}
case 37:
{
                                                    // DUIV_GRAPHIC
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateGraphic(MAKEINTRESOURCEW(yyvsp[-1].num), GRAPHIC_TransColor, (UINT)-1, 0, 0, ppc->GetHInstance()));
                                                    CBCHK();
                                                ;
    break;}
case 38:
{
                                                    // DUIV_GRAPHIC
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateGraphic(MAKEINTRESOURCEW(yyvsp[-3].num), (BYTE)yyvsp[-1].num, 0, 0, 0, ppc->GetHInstance()));
                                                    CBCHK();
                                                ;
    break;}
case 39:
{
                                                    // DUIV_GRAPHIC
                                                    bool bFlip = true;
                                                    bool bRTL = false;
                                                    if (!yyvsp[-3].num) bFlip = false;
                                                    if (yyvsp[-1].num) bRTL = true;
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateGraphic(MAKEINTRESOURCEW(yyvsp[-13].num), (BYTE)yyvsp[-11].num, (UINT)yyvsp[-9].num, yyvsp[-7].num, yyvsp[-5].num, ppc->GetHInstance(), bFlip, bRTL));
                                                    CBCHK();
                                                ;
    break;}
case 40:
{
                                                    // DUIV_GRAPHIC
                                                    bool bFlip = true;
                                                    bool bRTL = false;
                                                    if (!yyvsp[-5].num) bFlip = false;
                                                    if (yyvsp[-3].num) bRTL = true;
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateGraphic(MAKEINTRESOURCEW(yyvsp[-15].num), (BYTE)yyvsp[-13].num, (UINT)yyvsp[-11].num, yyvsp[-9].num, yyvsp[-7].num, static_cast<HINSTANCE>(yyvsp[-1].h), bFlip, bRTL));
                                                    CBCHK();
                                                ;
    break;}
case 41:
{
                                                    // DUIV_STRING
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateString(yyvsp[0].str));
                                                    CBCHK();
                                                ;
    break;}
case 42:
{
                                                    // DUIV_STRING
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateString(MAKEINTRESOURCEW(yyvsp[-1].num), ppc->GetHInstance()));
                                                    CBCHK();
                                                ;
    break;}
case 43:
{
                                                    // DUIV_STRING
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateString(MAKEINTRESOURCEW(yyvsp[-3].num), static_cast<HINSTANCE>(yyvsp[-1].h)));
                                                    CBCHK();
                                                ;
    break;}
case 44:
{
                                                    // DUIV_STRING
                                                    WCHAR sz[64];
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateString(Parser::_QuerySysMetricStr(yyvsp[-1].num, sz, DUIARRAYSIZE(sz))));
                                                    CBCHK();
                                                ;
    break;}
case 45:
{
                                                    // DUIV_INT (enumeration), EnumsList (strings to convert and OR)
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_EnumFixup, &yyvsp[0].el);
                                                    CBCHK();
                                                ;
    break;}
case 46:
{
                                                    // DUIV_LAYOUT (instantiated on a per-basis)
                                                    LayoutCreate lc = {0};
                                                    lc.pszLayout = yyvsp[-2].ident;
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_LayoutCreate, &lc);
                                                    CBCHK();
                                                ;
    break;}
case 47:
{
                                                    // DUIV_LAYOUT (instantiated on a per-basis)
                                                    LayoutCreate lc = {0};
                                                    lc.pszLayout = yyvsp[-3].ident;
                                                    lc.dNumParams = yyvsp[-1].pl.dNumParams;
                                                    lc.pParams = yyvsp[-1].pl.pParams;
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_LayoutCreate, &lc);
                                                    CBCHK();
                                                ;
    break;}
case 48:
{
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_SheetRef, yyvsp[-1].ident);
                                                    CBCHK();
                                                ;
    break;}
case 49:
{
                                                    // DUIV_ATOM
                                                    yyval.pvn = ppc->_CreateValueNode(VNT_Normal, Value::CreateAtom(yyvsp[-1].ident));
                                                    CBCHK();
                                                ;
    break;}
case 50:
{
                                                    yyval.num = yyvsp[0].num;
                                                ;
    break;}
case 51:
{
                                                    yyval.num = PointToPixel(yyvsp[-1].num, Parser::g_nDPI);
                                                ;
    break;}
case 52:
{
                                                    yyval.num = RelPixToPixel(yyvsp[-1].num, Parser::g_nDPI);
                                                ;
    break;}
case 53:
{
                                                    yyval.num = yyvsp[0].num;
                                                ;
    break;}
case 54:
{
                                                    WCHAR szRes[256];
                                                    ZeroMemory(szRes, sizeof(szRes));
                                                    int cRead = LoadStringW(ppc->GetHInstance(), yyvsp[-1].num, szRes, DUIARRAYSIZE(szRes));
                                                    if (!cRead)
                                                    {
                                                        CallbackParseError(L"RCINT failure. String table ID not found.", _itow(yyvsp[-1].num, szRes, 10));
                                                        YYABORT;
                                                    }
                                                    yyval.num =  _wtoi(szRes);
                                                ;
    break;}
case 55:
{
                                                    WCHAR szRes[256];
                                                    ZeroMemory(szRes, sizeof(szRes));
                                                    int cRead = LoadStringW(ppc->GetHInstance(), yyvsp[-1].num, szRes, DUIARRAYSIZE(szRes) - 1);
                                                    if (!cRead)
                                                    {
                                                        CallbackParseError(L"RCCHAR failure. String table ID not found.", _itow(yyvsp[-1].num, szRes, 10));
                                                        YYABORT;
                                                    }
                                                    yyval.num = (int)szRes[0];
                                                ;
    break;}
case 56:
{
                                                    yyval.num = Parser::_QuerySysMetric(yyvsp[-1].num);
                                                ;
    break;}
case 57:
{
                                                    yyval.num = yyvsp[0].num;
                                                ;
    break;}
case 58:
{
                                                    yyval.num = yyvsp[-2].num | yyvsp[0].num;
                                                ;
    break;}
case 59:
{
                                                    yyval.cr = ORGB(yyvsp[-5].num, yyvsp[-3].num, yyvsp[-1].num);
                                                ;
    break;}
case 60:
{
                                                    yyval.cr = ARGB(yyvsp[-7].num, yyvsp[-5].num, yyvsp[-3].num, yyvsp[-1].num);
                                                ;
    break;}
case 61:
{
                                                    yyval.el.dNumParams = yyvsp[-2].el.dNumParams + 1;
                                                    yyval.el.pEnums = (LPWSTR*)ppc->_TrackTempReAlloc(yyval.el.pEnums, sizeof(LPWSTR) * yyval.el.dNumParams);  // Track not lost on failure
                                                    MEMCHK(yyval.el.pEnums);
                                                    (yyval.el.pEnums)[yyval.el.dNumParams - 1] = (LPWSTR)ppc->_TrackTempAlloc((wcslen(yyvsp[0].ident) + 1) * sizeof(WCHAR));
                                                    MEMCHK((yyval.el.pEnums)[yyval.el.dNumParams - 1]);
                                                    wcscpy((yyval.el.pEnums)[yyval.el.dNumParams - 1], yyvsp[0].ident);
                                                ;
    break;}
case 62:
{
                                                    yyval.el.dNumParams = 1;
                                                    yyval.el.pEnums = (LPWSTR*)ppc->_TrackTempAlloc(sizeof(LPWSTR));
                                                    MEMCHK(yyval.el.pEnums);
                                                    *(yyval.el.pEnums) = (LPWSTR)ppc->_TrackTempAlloc((wcslen(yyvsp[0].ident) + 1) * sizeof(WCHAR));
                                                    MEMCHK(*(yyval.el.pEnums));
                                                    wcscpy(*(yyval.el.pEnums), yyvsp[0].ident);
                                                ;
    break;}
case 63:
{
                                                    yyval.h = ppc->GetHandle(yyvsp[-1].num);
                                                ;
    break;}
case 64:
{
                                                    yyval.pl.dNumParams = yyvsp[-2].pl.dNumParams + 1;
                                                    yyval.pl.pParams = (int*)ppc->_TrackTempReAlloc(yyval.pl.pParams, sizeof(int) * yyval.pl.dNumParams);  // Track not lost on failure
                                                    MEMCHK(yyval.pl.pParams);
                                                    (yyval.pl.pParams)[yyval.pl.dNumParams - 1] = yyvsp[0].num;
                                                ;
    break;}
case 65:
{
                                                    yyval.pl.dNumParams = 1;
                                                    yyval.pl.pParams = (int*)ppc->_TrackTempAlloc(sizeof(int));
                                                    MEMCHK(yyval.pl.pParams);
                                                    *(yyval.pl.pParams) = yyvsp[0].num;
                                                ;
    break;}
case 66:
{
                                                    yyval.psn = ppc->_CreateSheetNode(yyvsp[-6].ident, yyvsp[-4].prn);
                                                    CBCHK();
                                                ;
    break;}
case 67:
{
                                                    RuleNode* prn = yyvsp[-1].prn;
                                                    while(prn->pNext) prn = prn->pNext;
                                                    prn->pNext = yyvsp[0].prn;
                                                    yyval.prn = yyvsp[-1].prn;
                                                ;
    break;}
case 68:
{
                                                    yyval.prn = yyvsp[0].prn;
                                                ;
    break;}
case 69:
{
                                                    yyval.prn = ppc->_CreateRuleNode(yyvsp[-4].ident, yyvsp[-3].pan, yyvsp[-1].ppvpn);
                                                    CBCHK();
                                                ;
    break;}
case 70:
{
                                                    yyval.prn = ppc->_CreateRuleNode(yyvsp[-3].ident, NULL, yyvsp[-1].ppvpn);
                                                    CBCHK();
                                                ;
    break;}
case 71:
{
                                                    AttribNode* pan = yyvsp[-1].pan;
                                                    while(pan->pNext) pan = (AttribNode*)pan->pNext;
                                                    pan->pNext = yyvsp[0].pan;
                                                    yyval.pan = yyvsp[-1].pan;
                                                ;
    break;}
case 72:
{
                                                    yyval.pan = yyvsp[0].pan;
                                                ;
    break;}
case 73:
{
                                                    UINT nLogOp = PALOGOP_Equal;
                                                    yyval.pan = (AttribNode*)ppc->_CreatePropValPairNode(yyvsp[-3].ident, yyvsp[-1].pvn, &nLogOp);
                                                    CBCHK();
                                                ;
    break;}
case 74:
{
                                                    UINT nLogOp = PALOGOP_Equal;
                                                    yyval.pan = (AttribNode*)ppc->_CreatePropValPairNode(yyvsp[-1].ident, ppc->_CreateValueNode(VNT_Normal, Value::pvBoolTrue), &nLogOp);
                                                    CBCHK();
                                                ;
    break;}
case 75:
{
                                                    UINT nLogOp = PALOGOP_NotEqual;
                                                    yyval.pan = (AttribNode*)ppc->_CreatePropValPairNode(yyvsp[-4].ident, yyvsp[-1].pvn, &nLogOp);
                                                    CBCHK();
                                                ;
    break;}
case 76:
{
                                                    PropValPairNode* ppvpn = yyvsp[-1].ppvpn;
                                                    while(ppvpn->pNext) ppvpn = ppvpn->pNext;
                                                    ppvpn->pNext = yyvsp[0].ppvpn;
                                                    yyval.ppvpn = yyvsp[-1].ppvpn;
                                                ;
    break;}
case 77:
{
                                                    yyval.ppvpn = yyvsp[0].ppvpn;
                                                ;
    break;}
case 78:
{
                                                    yyval.ppvpn = ppc->_CreatePropValPairNode(yyvsp[-3].ident, yyvsp[-1].pvn);
                                                    CBCHK();
                                                ;
    break;}
}



  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (int) (sizeof (yytname) / sizeof (char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen (yytname[x]) + 15, count++;
	  size += strlen ("parse error, unexpected `") + 1;
	  size += strlen (yytname[YYTRANSLATE (yychar)]);
	  msg = (char *) malloc (size);
	  if (msg != 0)
	    {
	      strcpy (msg, "parse error, unexpected `");
	      strcat (msg, yytname[YYTRANSLATE (yychar)]);
	      strcat (msg, "'");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (int) (sizeof (yytname) / sizeof (char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat (msg, count == 0 ? ", expecting `" : " or `");
			strcat (msg, yytname[x]);
			strcat (msg, "'");
			count++;
		      }
		}
	      yyerror (msg);
	      free (msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#if YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#if YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}

//
// 4chan: add namespace terminator here (as described in parse.y:44
//
}


namespace DirectUI
{

// DirectUI callback-specific Parse Error
void CallbackParseError(LPCWSTR pszError, LPCWSTR pszToken)
{
    Parser::g_hrParse = DU_E_GENERIC;
    Parser::g_fParseAbort = true;
    ppc->_ParseError(pszError, pszToken, yylineno);
}

// Internal Parse Error: Called by Parser for fatal conditions
void yyerror(LPCSTR s)
{
    // Convert string and current token to Unicode
    LPWSTR pszError = MultiByteToUnicode(s);
    LPWSTR pszToken = MultiByteToUnicode(yytext);
    
    ppc->_ParseError(pszError, pszToken, yylineno);

    if (pszToken)
        HFree(pszToken);
    if (pszError)
        HFree(pszError);
}

} // namespace DirectUI
