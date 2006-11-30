/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     sySkip = 258,
     syRoutine = 259,
     sySimpleRoutine = 260,
     sySimpleProcedure = 261,
     syProcedure = 262,
     syFunction = 263,
     sySubsystem = 264,
     syKernelUser = 265,
     syKernelServer = 266,
     syMsgOption = 267,
     syMsgSeqno = 268,
     syWaitTime = 269,
     syNoWaitTime = 270,
     syErrorProc = 271,
     syServerPrefix = 272,
     syUserPrefix = 273,
     syServerDemux = 274,
     syRCSId = 275,
     syImport = 276,
     syUImport = 277,
     sySImport = 278,
     syIn = 279,
     syOut = 280,
     syInOut = 281,
     syRequestPort = 282,
     syReplyPort = 283,
     sySReplyPort = 284,
     syUReplyPort = 285,
     syType = 286,
     syArray = 287,
     syStruct = 288,
     syOf = 289,
     syInTran = 290,
     syOutTran = 291,
     syDestructor = 292,
     syCType = 293,
     syCUserType = 294,
     syCServerType = 295,
     syCString = 296,
     syColon = 297,
     sySemi = 298,
     syComma = 299,
     syPlus = 300,
     syMinus = 301,
     syStar = 302,
     syDiv = 303,
     syLParen = 304,
     syRParen = 305,
     syEqual = 306,
     syCaret = 307,
     syTilde = 308,
     syLAngle = 309,
     syRAngle = 310,
     syLBrack = 311,
     syRBrack = 312,
     syBar = 313,
     syError = 314,
     syNumber = 315,
     sySymbolicType = 316,
     syIdentifier = 317,
     syString = 318,
     syQString = 319,
     syFileName = 320,
     syIPCFlag = 321
   };
#endif
/* Tokens.  */
#define sySkip 258
#define syRoutine 259
#define sySimpleRoutine 260
#define sySimpleProcedure 261
#define syProcedure 262
#define syFunction 263
#define sySubsystem 264
#define syKernelUser 265
#define syKernelServer 266
#define syMsgOption 267
#define syMsgSeqno 268
#define syWaitTime 269
#define syNoWaitTime 270
#define syErrorProc 271
#define syServerPrefix 272
#define syUserPrefix 273
#define syServerDemux 274
#define syRCSId 275
#define syImport 276
#define syUImport 277
#define sySImport 278
#define syIn 279
#define syOut 280
#define syInOut 281
#define syRequestPort 282
#define syReplyPort 283
#define sySReplyPort 284
#define syUReplyPort 285
#define syType 286
#define syArray 287
#define syStruct 288
#define syOf 289
#define syInTran 290
#define syOutTran 291
#define syDestructor 292
#define syCType 293
#define syCUserType 294
#define syCServerType 295
#define syCString 296
#define syColon 297
#define sySemi 298
#define syComma 299
#define syPlus 300
#define syMinus 301
#define syStar 302
#define syDiv 303
#define syLParen 304
#define syRParen 305
#define syEqual 306
#define syCaret 307
#define syTilde 308
#define syLAngle 309
#define syRAngle 310
#define syLBrack 311
#define syRBrack 312
#define syBar 313
#define syError 314
#define syNumber 315
#define sySymbolicType 316
#define syIdentifier 317
#define syString 318
#define syQString 319
#define syFileName 320
#define syIPCFlag 321




/* Copy the first part of user declarations.  */
#line 117 "parser.y"


#include <stdio.h>

#include "error.h"
#include "lexxer.h"
#include "global.h"
#include "mig_string.h"
#include "type.h"
#include "routine.h"
#include "statement.h"

static const char *import_name(statement_kind_t sk);

void
yyerror(const char *s)
{
    error(s);
}


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 139 "parser.y"
{
    u_int number;
    identifier_t identifier;
    const_string_t string;
    statement_kind_t statement_kind;
    ipc_type_t *type;
    struct
    {
	u_int innumber;		/* msgt_name value, when sending */
	const_string_t instr;
	u_int outnumber;	/* msgt_name value, when receiving */
	const_string_t outstr;
	u_int size;		/* 0 means there is no default size */
    } symtype;
    routine_t *routine;
    arg_kind_t direction;
    argument_t *argument;
    ipc_flags_t flag;
}
/* Line 193 of yacc.c.  */
#line 269 "../parser.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 282 "../parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   219

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNRULES -- Number of states.  */
#define YYNSTATES  213

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   321

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    13,    16,    19,    22,
      25,    28,    31,    34,    37,    41,    44,    47,    49,    52,
      57,    59,    60,    63,    65,    67,    69,    71,    75,    79,
      81,    84,    87,    90,    93,    97,    99,   101,   103,   107,
     110,   114,   116,   125,   134,   142,   147,   152,   157,   159,
     161,   164,   167,   170,   173,   175,   177,   184,   185,   189,
     195,   197,   199,   201,   205,   207,   212,   218,   226,   232,
     238,   243,   250,   254,   258,   262,   266,   268,   272,   274,
     276,   278,   280,   282,   286,   290,   294,   298,   303,   306,
     310,   312,   316,   321,   322,   324,   326,   328,   330,   332,
     334,   336,   338,   340,   342,   345,   348,   349,   350
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      68,     0,    -1,    -1,    68,    69,    -1,    70,    43,    -1,
      77,    43,    -1,    76,    43,    -1,    78,    43,    -1,    79,
      43,    -1,    80,    43,    -1,    81,    43,    -1,    85,    43,
      -1,    99,    43,    -1,     3,    43,    -1,     3,    60,    43,
      -1,    82,    43,    -1,    84,    43,    -1,    43,    -1,     1,
      43,    -1,    71,    72,    74,    75,    -1,     9,    -1,    -1,
      72,    73,    -1,    10,    -1,    11,    -1,    62,    -1,    60,
      -1,   110,    12,    63,    -1,   110,    14,    63,    -1,    15,
      -1,    16,    62,    -1,    17,    62,    -1,    18,    62,    -1,
      19,    62,    -1,   111,    83,    65,    -1,    21,    -1,    22,
      -1,    23,    -1,   112,    20,    64,    -1,    31,    86,    -1,
      62,    51,    87,    -1,    88,    -1,    87,    35,    42,    62,
      62,    49,    62,    50,    -1,    87,    36,    42,    62,    62,
      49,    62,    50,    -1,    87,    37,    42,    62,    49,    62,
      50,    -1,    87,    38,    42,    62,    -1,    87,    39,    42,
      62,    -1,    87,    40,    42,    62,    -1,    89,    -1,    93,
      -1,    94,    88,    -1,    95,    88,    -1,    52,    88,    -1,
      96,    88,    -1,    97,    -1,    92,    -1,    49,    92,    44,
      98,    90,    50,    -1,    -1,    90,    44,    66,    -1,    90,
      44,    66,    56,    57,    -1,    60,    -1,    61,    -1,    91,
      -1,    91,    58,    91,    -1,    62,    -1,    32,    56,    57,
      34,    -1,    32,    56,    47,    57,    34,    -1,    32,    56,
      47,    42,    98,    57,    34,    -1,    32,    56,    98,    57,
      34,    -1,    33,    56,    98,    57,    34,    -1,    41,    56,
      98,    57,    -1,    41,    56,    47,    42,    98,    57,    -1,
      98,    45,    98,    -1,    98,    46,    98,    -1,    98,    47,
      98,    -1,    98,    48,    98,    -1,    60,    -1,    49,    98,
      50,    -1,   100,    -1,   101,    -1,   102,    -1,   103,    -1,
     104,    -1,     4,    62,   105,    -1,     5,    62,   105,    -1,
       7,    62,   105,    -1,     6,    62,   105,    -1,     8,    62,
     105,   109,    -1,    49,    50,    -1,    49,   106,    50,    -1,
     107,    -1,   107,    43,   106,    -1,   108,    62,   109,    90,
      -1,    -1,    24,    -1,    25,    -1,    26,    -1,    27,    -1,
      28,    -1,    29,    -1,    30,    -1,    14,    -1,    12,    -1,
      13,    -1,    42,    62,    -1,    42,    86,    -1,    -1,    -1,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   161,   161,   162,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   183,   185,   187,   188,   189,   190,   194,
     207,   219,   220,   223,   229,   237,   240,   243,   260,   266,
     274,   282,   290,   298,   306,   317,   318,   319,   322,   332,
     342,   346,   348,   368,   388,   403,   417,   426,   438,   440,
     442,   444,   446,   448,   450,   454,   460,   470,   471,   478,
     487,   493,   497,   499,   523,   527,   529,   531,   536,   540,
     544,   546,   551,   553,   555,   557,   559,   561,   566,   567,
     568,   569,   570,   573,   577,   581,   585,   589,   593,   595,
     600,   602,   609,   619,   620,   621,   622,   623,   624,   625,
     626,   627,   628,   629,   632,   638,   643,   647,   651
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "sySkip", "syRoutine", "sySimpleRoutine",
  "sySimpleProcedure", "syProcedure", "syFunction", "sySubsystem",
  "syKernelUser", "syKernelServer", "syMsgOption", "syMsgSeqno",
  "syWaitTime", "syNoWaitTime", "syErrorProc", "syServerPrefix",
  "syUserPrefix", "syServerDemux", "syRCSId", "syImport", "syUImport",
  "sySImport", "syIn", "syOut", "syInOut", "syRequestPort", "syReplyPort",
  "sySReplyPort", "syUReplyPort", "syType", "syArray", "syStruct", "syOf",
  "syInTran", "syOutTran", "syDestructor", "syCType", "syCUserType",
  "syCServerType", "syCString", "syColon", "sySemi", "syComma", "syPlus",
  "syMinus", "syStar", "syDiv", "syLParen", "syRParen", "syEqual",
  "syCaret", "syTilde", "syLAngle", "syRAngle", "syLBrack", "syRBrack",
  "syBar", "syError", "syNumber", "sySymbolicType", "syIdentifier",
  "syString", "syQString", "syFileName", "syIPCFlag", "$accept",
  "Statements", "Statement", "Subsystem", "SubsystemStart",
  "SubsystemMods", "SubsystemMod", "SubsystemName", "SubsystemBase",
  "MsgOption", "WaitTime", "Error", "ServerPrefix", "UserPrefix",
  "ServerDemux", "Import", "ImportIndicant", "RCSDecl", "TypeDecl",
  "NamedTypeSpec", "TransTypeSpec", "TypeSpec", "BasicTypeSpec",
  "IPCFlags", "PrimIPCType", "IPCType", "PrevTypeSpec", "VarArrayHead",
  "ArrayHead", "StructHead", "CStringSpec", "IntExp", "RoutineDecl",
  "Routine", "SimpleRoutine", "Procedure", "SimpleProcedure", "Function",
  "Arguments", "ArgumentList", "Argument", "Direction", "ArgumentType",
  "LookString", "LookFileName", "LookQString", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    67,    68,    68,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    70,
      71,    72,    72,    73,    73,    74,    75,    76,    77,    77,
      78,    79,    80,    81,    82,    83,    83,    83,    84,    85,
      86,    87,    87,    87,    87,    87,    87,    87,    88,    88,
      88,    88,    88,    88,    88,    89,    89,    90,    90,    90,
      91,    91,    92,    92,    93,    94,    94,    94,    95,    96,
      97,    97,    98,    98,    98,    98,    98,    98,    99,    99,
      99,    99,    99,   100,   101,   102,   103,   104,   105,   105,
     106,   106,   107,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   109,   109,   110,   111,   112
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     2,     2,     1,     2,     4,
       1,     0,     2,     1,     1,     1,     1,     3,     3,     1,
       2,     2,     2,     2,     3,     1,     1,     1,     3,     2,
       3,     1,     8,     8,     7,     4,     4,     4,     1,     1,
       2,     2,     2,     2,     1,     1,     6,     0,     3,     5,
       1,     1,     1,     3,     1,     4,     5,     7,     5,     5,
       4,     6,     3,     3,     3,     3,     1,     3,     1,     1,
       1,     1,     1,     3,     3,     3,     3,     4,     2,     3,
       1,     3,     4,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     0,     0,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
      20,    29,     0,     0,     0,     0,     0,    17,     3,     0,
      21,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    78,    79,    80,    81,    82,     0,     0,     0,    18,
      13,     0,     0,     0,     0,     0,     0,    30,    31,    32,
      33,     0,    39,     4,     0,     6,     5,     7,     8,     9,
      10,    15,    16,    11,    12,     0,     0,    35,    36,    37,
       0,     0,    14,    93,    83,    84,    86,    85,     0,     0,
      23,    24,    25,    22,     0,    27,    28,    34,    38,   102,
     103,   101,    94,    95,    96,    97,    98,    99,   100,    88,
       0,    90,     0,     0,    87,     0,     0,     0,     0,     0,
      60,    61,    64,    40,    41,    48,    62,    55,    49,     0,
       0,     0,    54,    26,    19,    89,    93,     0,   104,   105,
       0,     0,     0,     0,    52,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    53,    91,    57,     0,     0,     0,
      76,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    63,    92,     0,     0,     0,    65,     0,     0,
       0,     0,     0,     0,     0,    70,    57,     0,     0,     0,
      45,    46,    47,     0,     0,    66,    77,    72,    73,    74,
      75,    68,    69,     0,     0,     0,     0,     0,    58,     0,
      71,    56,     0,     0,     0,     0,    67,     0,     0,    44,
      59,    42,    43
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    54,    83,    84,   124,    21,
      22,    23,    24,    25,    26,    27,    70,    28,    29,    52,
     113,   114,   115,   163,   116,   117,   118,   119,   120,   121,
     122,   151,    30,    31,    32,    33,    34,    35,    74,   100,
     101,   102,   104,    36,    37,    38
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -106
static const yytype_int16 yypact[] =
{
    -106,     2,  -106,    -5,   -31,   -16,    27,    28,    30,    33,
    -106,  -106,    35,    49,    71,    72,    89,  -106,  -106,     6,
    -106,    60,    67,   107,   109,   110,   111,   112,   113,   114,
     115,  -106,  -106,  -106,  -106,  -106,    56,     9,    51,  -106,
    -106,   116,   117,   117,   117,   117,   117,  -106,  -106,  -106,
    -106,   118,  -106,  -106,   -10,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,    98,    99,  -106,  -106,  -106,
      95,   100,  -106,    48,  -106,  -106,  -106,  -106,   121,    47,
    -106,  -106,  -106,  -106,   105,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
     120,   124,   106,   119,  -106,   122,   123,   126,    -7,    47,
    -106,  -106,  -106,   101,  -106,  -106,   125,  -106,  -106,    47,
      47,    47,  -106,  -106,  -106,  -106,    88,   121,   118,  -106,
     -13,   -45,   -12,   127,  -106,   130,   131,   132,   133,   134,
     135,    -7,  -106,  -106,  -106,  -106,  -106,   -29,   -45,   146,
    -106,    -6,    10,   142,    36,   -45,   128,   129,   136,   137,
     138,   139,  -106,   141,   -45,   152,    82,  -106,   -45,   -45,
     -45,   -45,   153,   154,   -45,  -106,    97,   140,   143,   144,
    -106,  -106,  -106,   145,    74,  -106,  -106,    39,    39,  -106,
    -106,  -106,  -106,    78,    41,   147,   148,   150,   151,   155,
    -106,  -106,   156,   157,   158,   149,  -106,   159,   160,  -106,
    -106,  -106,  -106
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,  -106,    91,
    -106,   -15,  -106,    16,    54,    96,  -106,  -106,  -106,  -106,
    -106,  -105,  -106,  -106,  -106,  -106,  -106,  -106,   103,    77,
    -106,  -106,    86,  -106,  -106,  -106
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -109
static const yytype_int16 yytable[] =
{
      80,    81,     2,     3,   148,     4,     5,     6,     7,     8,
       9,    10,    40,   164,  -106,   150,  -106,    11,    12,    13,
      14,    15,  -108,  -107,  -107,  -107,   152,   154,   165,    41,
      67,    68,    69,    16,   147,   153,   148,   148,    39,   168,
     169,   170,   171,   166,   149,    17,    42,   150,   150,    53,
     176,   172,    82,   110,   111,   168,   169,   170,   171,   184,
      89,    90,    91,   187,   188,   189,   190,   173,    65,   193,
      66,    71,    92,    93,    94,    95,    96,    97,    98,   105,
     106,   168,   169,   170,   171,   183,   170,   171,   107,    43,
      44,   201,    45,   175,   134,    46,   108,    47,    99,   109,
      89,    90,    91,    55,   142,   143,   144,   110,   111,   112,
      56,    48,    92,    93,    94,    95,    96,    97,    98,   168,
     169,   170,   171,   168,   169,   170,   171,   168,   169,   170,
     171,   199,   186,    49,    50,   200,   135,   136,   137,   138,
     139,   140,   168,   169,   170,   171,    75,    76,    77,    78,
      57,    51,    58,    59,    60,    61,    62,    63,    64,    72,
      87,    85,    86,   103,    88,   123,    73,   126,   127,    79,
     125,   155,   156,   157,   158,   159,   160,   161,   130,   131,
     167,   128,   132,   141,   174,   183,   185,   191,   192,   206,
     177,   178,   194,   197,   129,   162,   202,   203,   179,   180,
     181,   182,   195,   145,   133,   196,   210,   205,   209,   211,
     212,   198,   204,   146,     0,     0,     0,     0,   207,   208
};

static const yytype_int16 yycheck[] =
{
      10,    11,     0,     1,    49,     3,     4,     5,     6,     7,
       8,     9,    43,    42,    12,    60,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,   131,   132,    57,    60,
      21,    22,    23,    31,    47,    47,    49,    49,    43,    45,
      46,    47,    48,   148,    57,    43,    62,    60,    60,    43,
     155,    57,    62,    60,    61,    45,    46,    47,    48,   164,
      12,    13,    14,   168,   169,   170,   171,    57,    12,   174,
      14,    20,    24,    25,    26,    27,    28,    29,    30,    32,
      33,    45,    46,    47,    48,    44,    47,    48,    41,    62,
      62,    50,    62,    57,   109,    62,    49,    62,    50,    52,
      12,    13,    14,    43,   119,   120,   121,    60,    61,    62,
      43,    62,    24,    25,    26,    27,    28,    29,    30,    45,
      46,    47,    48,    45,    46,    47,    48,    45,    46,    47,
      48,    57,    50,    62,    62,    57,    35,    36,    37,    38,
      39,    40,    45,    46,    47,    48,    43,    44,    45,    46,
      43,    62,    43,    43,    43,    43,    43,    43,    43,    43,
      65,    63,    63,    42,    64,    60,    49,    43,    62,    51,
      50,    44,    42,    42,    42,    42,    42,    42,    56,    56,
      34,    62,    56,    58,    42,    44,    34,    34,    34,    34,
      62,    62,   176,    49,   103,   141,    49,    49,    62,    62,
      62,    62,    62,   126,   108,    62,    57,    56,    50,    50,
      50,    66,    62,   127,    -1,    -1,    -1,    -1,    62,    62
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    68,     0,     1,     3,     4,     5,     6,     7,     8,
       9,    15,    16,    17,    18,    19,    31,    43,    69,    70,
      71,    76,    77,    78,    79,    80,    81,    82,    84,    85,
      99,   100,   101,   102,   103,   104,   110,   111,   112,    43,
      43,    60,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    86,    43,    72,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    12,    14,    21,    22,    23,
      83,    20,    43,    49,   105,   105,   105,   105,   105,    51,
      10,    11,    62,    73,    74,    63,    63,    65,    64,    12,
      13,    14,    24,    25,    26,    27,    28,    29,    30,    50,
     106,   107,   108,    42,   109,    32,    33,    41,    49,    52,
      60,    61,    62,    87,    88,    89,    91,    92,    93,    94,
      95,    96,    97,    60,    75,    50,    43,    62,    62,    86,
      56,    56,    56,    92,    88,    35,    36,    37,    38,    39,
      40,    58,    88,    88,    88,   106,   109,    47,    49,    57,
      60,    98,    98,    47,    98,    44,    42,    42,    42,    42,
      42,    42,    91,    90,    42,    57,    98,    34,    45,    46,
      47,    48,    57,    57,    42,    57,    98,    62,    62,    62,
      62,    62,    62,    44,    98,    34,    50,    98,    98,    98,
      98,    34,    34,    98,    90,    62,    62,    49,    66,    57,
      57,    50,    49,    49,    62,    56,    34,    62,    62,    50,
      57,    50,    50
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


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
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

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

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 12:
#line 174 "parser.y"
    {
    register statement_t *st = stAlloc();

    st->stKind = skRoutine;
    st->stRoutine = (yyvsp[(1) - (2)].routine);
    rtCheckRoutine((yyvsp[(1) - (2)].routine));
    if (BeVerbose)
	rtPrintRoutine((yyvsp[(1) - (2)].routine));
}
    break;

  case 13:
#line 184 "parser.y"
    { rtSkip(1); }
    break;

  case 14:
#line 186 "parser.y"
    { rtSkip((yyvsp[(2) - (3)].number)); }
    break;

  case 18:
#line 191 "parser.y"
    { yyerrok; }
    break;

  case 19:
#line 196 "parser.y"
    {
    if (BeVerbose)
    {
	printf("Subsystem %s: base = %u%s%s\n\n",
	       SubsystemName, SubsystemBase,
	       IsKernelUser ? ", KernelUser" : "",
	       IsKernelServer ? ", KernelServer" : "");
    }
}
    break;

  case 20:
#line 208 "parser.y"
    {
    if (SubsystemName != strNULL)
    {
	warn("previous Subsystem decl (of %s) will be ignored", SubsystemName);
	IsKernelUser = FALSE;
	IsKernelServer = FALSE;
	strfree((string_t) SubsystemName);
    }
}
    break;

  case 23:
#line 224 "parser.y"
    {
    if (IsKernelUser)
	warn("duplicate KernelUser keyword");
    IsKernelUser = TRUE;
}
    break;

  case 24:
#line 230 "parser.y"
    {
    if (IsKernelServer)
	warn("duplicate KernelServer keyword");
    IsKernelServer = TRUE;
}
    break;

  case 25:
#line 237 "parser.y"
    { SubsystemName = (yyvsp[(1) - (1)].identifier); }
    break;

  case 26:
#line 240 "parser.y"
    { SubsystemBase = (yyvsp[(1) - (1)].number); }
    break;

  case 27:
#line 244 "parser.y"
    {
    if (streql((yyvsp[(3) - (3)].string), "MACH_MSG_OPTION_NONE"))
    {
	MsgOption = strNULL;
	if (BeVerbose)
	    printf("MsgOption: canceled\n\n");
    }
    else
    {
	MsgOption = (yyvsp[(3) - (3)].string);
	if (BeVerbose)
	    printf("MsgOption %s\n\n",(yyvsp[(3) - (3)].string));
    }
}
    break;

  case 28:
#line 261 "parser.y"
    {
    WaitTime = (yyvsp[(3) - (3)].string);
    if (BeVerbose)
	printf("WaitTime %s\n\n", WaitTime);
}
    break;

  case 29:
#line 267 "parser.y"
    {
    WaitTime = strNULL;
    if (BeVerbose)
	printf("NoWaitTime\n\n");
}
    break;

  case 30:
#line 275 "parser.y"
    {
    ErrorProc = (yyvsp[(2) - (2)].identifier);
    if (BeVerbose)
	printf("ErrorProc %s\n\n", ErrorProc);
}
    break;

  case 31:
#line 283 "parser.y"
    {
    ServerPrefix = (yyvsp[(2) - (2)].identifier);
    if (BeVerbose)
	printf("ServerPrefix %s\n\n", ServerPrefix);
}
    break;

  case 32:
#line 291 "parser.y"
    {
    UserPrefix = (yyvsp[(2) - (2)].identifier);
    if (BeVerbose)
	printf("UserPrefix %s\n\n", UserPrefix);
}
    break;

  case 33:
#line 299 "parser.y"
    {
    ServerDemux = (yyvsp[(2) - (2)].identifier);
    if (BeVerbose)
	printf("ServerDemux %s\n\n", ServerDemux);
}
    break;

  case 34:
#line 307 "parser.y"
    {
    register statement_t *st = stAlloc();
    st->stKind = (yyvsp[(2) - (3)].statement_kind);
    st->stFileName = (yyvsp[(3) - (3)].string);

    if (BeVerbose)
	printf("%s %s\n\n", import_name((yyvsp[(2) - (3)].statement_kind)), (yyvsp[(3) - (3)].string));
}
    break;

  case 35:
#line 317 "parser.y"
    { (yyval.statement_kind) = skImport; }
    break;

  case 36:
#line 318 "parser.y"
    { (yyval.statement_kind) = skUImport; }
    break;

  case 37:
#line 319 "parser.y"
    { (yyval.statement_kind) = skSImport; }
    break;

  case 38:
#line 323 "parser.y"
    {
    if (RCSId != strNULL)
	warn("previous RCS decl will be ignored");
    if (BeVerbose)
	printf("RCSId %s\n\n", (yyvsp[(3) - (3)].string));
    RCSId = (yyvsp[(3) - (3)].string);
}
    break;

  case 39:
#line 333 "parser.y"
    {
    register identifier_t name = (yyvsp[(2) - (2)].type)->itName;

    if (itLookUp(name) != itNULL)
	warn("overriding previous definition of %s", name);
    itInsert(name, (yyvsp[(2) - (2)].type));
}
    break;

  case 40:
#line 343 "parser.y"
    { itTypeDecl((yyvsp[(1) - (3)].identifier), (yyval.type) = (yyvsp[(3) - (3)].type)); }
    break;

  case 41:
#line 347 "parser.y"
    { (yyval.type) = itResetType((yyvsp[(1) - (1)].type)); }
    break;

  case 42:
#line 350 "parser.y"
    {
    (yyval.type) = (yyvsp[(1) - (8)].type);

    if (((yyval.type)->itTransType != strNULL) && !streql((yyval.type)->itTransType, (yyvsp[(4) - (8)].identifier)))
	warn("conflicting translation types (%s, %s)",
	     (yyval.type)->itTransType, (yyvsp[(4) - (8)].identifier));
    (yyval.type)->itTransType = (yyvsp[(4) - (8)].identifier);

    if (((yyval.type)->itInTrans != strNULL) && !streql((yyval.type)->itInTrans, (yyvsp[(5) - (8)].identifier)))
	warn("conflicting in-translation functions (%s, %s)",
	     (yyval.type)->itInTrans, (yyvsp[(5) - (8)].identifier));
    (yyval.type)->itInTrans = (yyvsp[(5) - (8)].identifier);

    if (((yyval.type)->itServerType != strNULL) && !streql((yyval.type)->itServerType, (yyvsp[(7) - (8)].identifier)))
	warn("conflicting server types (%s, %s)",
	     (yyval.type)->itServerType, (yyvsp[(7) - (8)].identifier));
    (yyval.type)->itServerType = (yyvsp[(7) - (8)].identifier);
}
    break;

  case 43:
#line 370 "parser.y"
    {
    (yyval.type) = (yyvsp[(1) - (8)].type);

    if (((yyval.type)->itServerType != strNULL) && !streql((yyval.type)->itServerType, (yyvsp[(4) - (8)].identifier)))
	warn("conflicting server types (%s, %s)",
	     (yyval.type)->itServerType, (yyvsp[(4) - (8)].identifier));
    (yyval.type)->itServerType = (yyvsp[(4) - (8)].identifier);

    if (((yyval.type)->itOutTrans != strNULL) && !streql((yyval.type)->itOutTrans, (yyvsp[(5) - (8)].identifier)))
	warn("conflicting out-translation functions (%s, %s)",
	     (yyval.type)->itOutTrans, (yyvsp[(5) - (8)].identifier));
    (yyval.type)->itOutTrans = (yyvsp[(5) - (8)].identifier);

    if (((yyval.type)->itTransType != strNULL) && !streql((yyval.type)->itTransType, (yyvsp[(7) - (8)].identifier)))
	warn("conflicting translation types (%s, %s)",
	     (yyval.type)->itTransType, (yyvsp[(7) - (8)].identifier));
    (yyval.type)->itTransType = (yyvsp[(7) - (8)].identifier);
}
    break;

  case 44:
#line 390 "parser.y"
    {
    (yyval.type) = (yyvsp[(1) - (7)].type);

    if (((yyval.type)->itDestructor != strNULL) && !streql((yyval.type)->itDestructor, (yyvsp[(4) - (7)].identifier)))
	warn("conflicting destructor functions (%s, %s)",
	     (yyval.type)->itDestructor, (yyvsp[(4) - (7)].identifier));
    (yyval.type)->itDestructor = (yyvsp[(4) - (7)].identifier);

    if (((yyval.type)->itTransType != strNULL) && !streql((yyval.type)->itTransType, (yyvsp[(6) - (7)].identifier)))
	warn("conflicting translation types (%s, %s)",
	     (yyval.type)->itTransType, (yyvsp[(6) - (7)].identifier));
    (yyval.type)->itTransType = (yyvsp[(6) - (7)].identifier);
}
    break;

  case 45:
#line 404 "parser.y"
    {
    (yyval.type) = (yyvsp[(1) - (4)].type);

    if (((yyval.type)->itUserType != strNULL) && !streql((yyval.type)->itUserType, (yyvsp[(4) - (4)].identifier)))
	warn("conflicting user types (%s, %s)",
	     (yyval.type)->itUserType, (yyvsp[(4) - (4)].identifier));
    (yyval.type)->itUserType = (yyvsp[(4) - (4)].identifier);

    if (((yyval.type)->itServerType != strNULL) && !streql((yyval.type)->itServerType, (yyvsp[(4) - (4)].identifier)))
	warn("conflicting server types (%s, %s)",
	     (yyval.type)->itServerType, (yyvsp[(4) - (4)].identifier));
    (yyval.type)->itServerType = (yyvsp[(4) - (4)].identifier);
}
    break;

  case 46:
#line 418 "parser.y"
    {
    (yyval.type) = (yyvsp[(1) - (4)].type);

    if (((yyval.type)->itUserType != strNULL) && !streql((yyval.type)->itUserType, (yyvsp[(4) - (4)].identifier)))
	warn("conflicting user types (%s, %s)",
	     (yyval.type)->itUserType, (yyvsp[(4) - (4)].identifier));
    (yyval.type)->itUserType = (yyvsp[(4) - (4)].identifier);
}
    break;

  case 47:
#line 428 "parser.y"
    {
    (yyval.type) = (yyvsp[(1) - (4)].type);

    if (((yyval.type)->itServerType != strNULL) && !streql((yyval.type)->itServerType, (yyvsp[(4) - (4)].identifier)))
	warn("conflicting server types (%s, %s)",
	     (yyval.type)->itServerType, (yyvsp[(4) - (4)].identifier));
    (yyval.type)->itServerType = (yyvsp[(4) - (4)].identifier);
}
    break;

  case 48:
#line 439 "parser.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 49:
#line 441 "parser.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 50:
#line 443 "parser.y"
    { (yyval.type) = itVarArrayDecl((yyvsp[(1) - (2)].number), (yyvsp[(2) - (2)].type)); }
    break;

  case 51:
#line 445 "parser.y"
    { (yyval.type) = itArrayDecl((yyvsp[(1) - (2)].number), (yyvsp[(2) - (2)].type)); }
    break;

  case 52:
#line 447 "parser.y"
    { (yyval.type) = itPtrDecl((yyvsp[(2) - (2)].type)); }
    break;

  case 53:
#line 449 "parser.y"
    { (yyval.type) = itStructDecl((yyvsp[(1) - (2)].number), (yyvsp[(2) - (2)].type)); }
    break;

  case 54:
#line 451 "parser.y"
    { (yyval.type) = (yyvsp[(1) - (1)].type); }
    break;

  case 55:
#line 455 "parser.y"
    {
    (yyval.type) = itShortDecl((yyvsp[(1) - (1)].symtype).innumber, (yyvsp[(1) - (1)].symtype).instr,
		     (yyvsp[(1) - (1)].symtype).outnumber, (yyvsp[(1) - (1)].symtype).outstr,
		     (yyvsp[(1) - (1)].symtype).size);
}
    break;

  case 56:
#line 462 "parser.y"
    {
    (yyval.type) = itLongDecl((yyvsp[(2) - (6)].symtype).innumber, (yyvsp[(2) - (6)].symtype).instr,
		    (yyvsp[(2) - (6)].symtype).outnumber, (yyvsp[(2) - (6)].symtype).outstr,
		    (yyvsp[(2) - (6)].symtype).size, (yyvsp[(4) - (6)].number), (yyvsp[(5) - (6)].flag));
}
    break;

  case 57:
#line 470 "parser.y"
    { (yyval.flag) = flNone; }
    break;

  case 58:
#line 472 "parser.y"
    {
    if ((yyvsp[(1) - (3)].flag) & (yyvsp[(3) - (3)].flag))
	warn("redundant IPC flag ignored");
    else
	(yyval.flag) = (yyvsp[(1) - (3)].flag) | (yyvsp[(3) - (3)].flag);
}
    break;

  case 59:
#line 479 "parser.y"
    {
    if ((yyvsp[(3) - (5)].flag) != flDealloc)
	warn("only Dealloc is variable");
    else
	(yyval.flag) = (yyvsp[(1) - (5)].flag) | flMaybeDealloc;
}
    break;

  case 60:
#line 488 "parser.y"
    {
    (yyval.symtype).innumber = (yyval.symtype).outnumber = (yyvsp[(1) - (1)].number);
    (yyval.symtype).instr = (yyval.symtype).outstr = strNULL;
    (yyval.symtype).size = 0;
}
    break;

  case 61:
#line 494 "parser.y"
    { (yyval.symtype) = (yyvsp[(1) - (1)].symtype); }
    break;

  case 62:
#line 498 "parser.y"
    { (yyval.symtype) = (yyvsp[(1) - (1)].symtype); }
    break;

  case 63:
#line 500 "parser.y"
    {
    if ((yyvsp[(1) - (3)].symtype).size != (yyvsp[(3) - (3)].symtype).size)
    {
	if ((yyvsp[(1) - (3)].symtype).size == 0)
	    (yyval.symtype).size = (yyvsp[(3) - (3)].symtype).size;
	else if ((yyvsp[(3) - (3)].symtype).size == 0)
	    (yyval.symtype).size = (yyvsp[(1) - (3)].symtype).size;
	else
	{
	    error("sizes in IPCTypes (%d, %d) aren't equal",
		  (yyvsp[(1) - (3)].symtype).size, (yyvsp[(3) - (3)].symtype).size);
	    (yyval.symtype).size = 0;
	}
    }
    else
	(yyval.symtype).size = (yyvsp[(1) - (3)].symtype).size;
    (yyval.symtype).innumber = (yyvsp[(1) - (3)].symtype).innumber;
    (yyval.symtype).instr = (yyvsp[(1) - (3)].symtype).instr;
    (yyval.symtype).outnumber = (yyvsp[(3) - (3)].symtype).outnumber;
    (yyval.symtype).outstr = (yyvsp[(3) - (3)].symtype).outstr;
}
    break;

  case 64:
#line 524 "parser.y"
    { (yyval.type) = itPrevDecl((yyvsp[(1) - (1)].identifier)); }
    break;

  case 65:
#line 528 "parser.y"
    { (yyval.number) = 0; }
    break;

  case 66:
#line 530 "parser.y"
    { (yyval.number) = 0; }
    break;

  case 67:
#line 533 "parser.y"
    { (yyval.number) = (yyvsp[(5) - (7)].number); }
    break;

  case 68:
#line 537 "parser.y"
    { (yyval.number) = (yyvsp[(3) - (5)].number); }
    break;

  case 69:
#line 541 "parser.y"
    { (yyval.number) = (yyvsp[(3) - (5)].number); }
    break;

  case 70:
#line 545 "parser.y"
    { (yyval.type) = itCStringDecl((yyvsp[(3) - (4)].number), FALSE); }
    break;

  case 71:
#line 548 "parser.y"
    { (yyval.type) = itCStringDecl((yyvsp[(5) - (6)].number), TRUE); }
    break;

  case 72:
#line 552 "parser.y"
    { (yyval.number) = (yyvsp[(1) - (3)].number) + (yyvsp[(3) - (3)].number);	}
    break;

  case 73:
#line 554 "parser.y"
    { (yyval.number) = (yyvsp[(1) - (3)].number) - (yyvsp[(3) - (3)].number);	}
    break;

  case 74:
#line 556 "parser.y"
    { (yyval.number) = (yyvsp[(1) - (3)].number) * (yyvsp[(3) - (3)].number);	}
    break;

  case 75:
#line 558 "parser.y"
    { (yyval.number) = (yyvsp[(1) - (3)].number) / (yyvsp[(3) - (3)].number);	}
    break;

  case 76:
#line 560 "parser.y"
    { (yyval.number) = (yyvsp[(1) - (1)].number);	}
    break;

  case 77:
#line 562 "parser.y"
    { (yyval.number) = (yyvsp[(2) - (3)].number);	}
    break;

  case 78:
#line 566 "parser.y"
    { (yyval.routine) = (yyvsp[(1) - (1)].routine); }
    break;

  case 79:
#line 567 "parser.y"
    { (yyval.routine) = (yyvsp[(1) - (1)].routine); }
    break;

  case 80:
#line 568 "parser.y"
    { (yyval.routine) = (yyvsp[(1) - (1)].routine); }
    break;

  case 81:
#line 569 "parser.y"
    { (yyval.routine) = (yyvsp[(1) - (1)].routine); }
    break;

  case 82:
#line 570 "parser.y"
    { (yyval.routine) = (yyvsp[(1) - (1)].routine); }
    break;

  case 83:
#line 574 "parser.y"
    { (yyval.routine) = rtMakeRoutine((yyvsp[(2) - (3)].identifier), (yyvsp[(3) - (3)].argument)); }
    break;

  case 84:
#line 578 "parser.y"
    { (yyval.routine) = rtMakeSimpleRoutine((yyvsp[(2) - (3)].identifier), (yyvsp[(3) - (3)].argument)); }
    break;

  case 85:
#line 582 "parser.y"
    { (yyval.routine) = rtMakeProcedure((yyvsp[(2) - (3)].identifier), (yyvsp[(3) - (3)].argument)); }
    break;

  case 86:
#line 586 "parser.y"
    { (yyval.routine) = rtMakeSimpleProcedure((yyvsp[(2) - (3)].identifier), (yyvsp[(3) - (3)].argument)); }
    break;

  case 87:
#line 590 "parser.y"
    { (yyval.routine) = rtMakeFunction((yyvsp[(2) - (4)].identifier), (yyvsp[(3) - (4)].argument), (yyvsp[(4) - (4)].type)); }
    break;

  case 88:
#line 594 "parser.y"
    { (yyval.argument) = argNULL; }
    break;

  case 89:
#line 596 "parser.y"
    { (yyval.argument) = (yyvsp[(2) - (3)].argument); }
    break;

  case 90:
#line 601 "parser.y"
    { (yyval.argument) = (yyvsp[(1) - (1)].argument); }
    break;

  case 91:
#line 603 "parser.y"
    {
    (yyval.argument) = (yyvsp[(1) - (3)].argument);
    (yyval.argument)->argNext = (yyvsp[(3) - (3)].argument);
}
    break;

  case 92:
#line 610 "parser.y"
    {
    (yyval.argument) = argAlloc();
    (yyval.argument)->argKind = (yyvsp[(1) - (4)].direction);
    (yyval.argument)->argName = (yyvsp[(2) - (4)].identifier);
    (yyval.argument)->argType = (yyvsp[(3) - (4)].type);
    (yyval.argument)->argFlags = (yyvsp[(4) - (4)].flag);
}
    break;

  case 93:
#line 619 "parser.y"
    { (yyval.direction) = akNone; }
    break;

  case 94:
#line 620 "parser.y"
    { (yyval.direction) = akIn; }
    break;

  case 95:
#line 621 "parser.y"
    { (yyval.direction) = akOut; }
    break;

  case 96:
#line 622 "parser.y"
    { (yyval.direction) = akInOut; }
    break;

  case 97:
#line 623 "parser.y"
    { (yyval.direction) = akRequestPort; }
    break;

  case 98:
#line 624 "parser.y"
    { (yyval.direction) = akReplyPort; }
    break;

  case 99:
#line 625 "parser.y"
    { (yyval.direction) = akSReplyPort; }
    break;

  case 100:
#line 626 "parser.y"
    { (yyval.direction) = akUReplyPort; }
    break;

  case 101:
#line 627 "parser.y"
    { (yyval.direction) = akWaitTime; }
    break;

  case 102:
#line 628 "parser.y"
    { (yyval.direction) = akMsgOption; }
    break;

  case 103:
#line 629 "parser.y"
    { (yyval.direction) = akMsgSeqno; }
    break;

  case 104:
#line 633 "parser.y"
    {
    (yyval.type) = itLookUp((yyvsp[(2) - (2)].identifier));
    if ((yyval.type) == itNULL)
	error("type '%s' not defined", (yyvsp[(2) - (2)].identifier));
}
    break;

  case 105:
#line 639 "parser.y"
    { (yyval.type) = (yyvsp[(2) - (2)].type); }
    break;

  case 106:
#line 643 "parser.y"
    { LookString(); }
    break;

  case 107:
#line 647 "parser.y"
    { LookFileName(); }
    break;

  case 108:
#line 651 "parser.y"
    { LookQString(); }
    break;


/* Line 1267 of yacc.c.  */
#line 2358 "../parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 654 "parser.y"


static const char *
import_name(statement_kind_t sk)
{
    switch (sk)
    {
      case skImport:
	return "Import";
      case skSImport:
	return "SImport";
      case skUImport:
	return "UImport";
      default:
	fatal("import_name(%d): not import statement", (int) sk);
	/*NOTREACHED*/
    }
}

