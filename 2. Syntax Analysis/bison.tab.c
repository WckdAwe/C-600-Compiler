/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 7 "bison.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include "hashtbl.h"
#define MAX_ERRORS       0
#define MAX_STR_CONST  256

extern int yylex();
extern char *yytext;
extern FILE *yyin;

extern void yyterminate();


extern int lineno;
extern int line_init;
extern int error_count; 
extern char str_buf[MAX_STR_CONST];    
extern char* str_buf_ptr;

void yyerror(char* str);

#line 92 "bison.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_INT = 258,
    T_ENUM = 259,
    T_LENGTH = 260,
    T_ICONST = 261,
    T_FCONST = 262,
    T_TYPEDEF = 263,
    T_CHAR = 264,
    T_STRING = 265,
    T_SCONST = 266,
    T_CLASS = 267,
    T_PRIVATE = 268,
    T_PROTECTED = 269,
    T_PUBLIC = 270,
    T_STATIC = 271,
    T_UNION = 272,
    T_LIST = 273,
    T_CONTINUE = 274,
    T_BREAK = 275,
    T_IF = 276,
    T_ELSE = 277,
    T_WHILE = 278,
    T_FOR = 279,
    T_SWITCH = 280,
    T_DEFAULT = 281,
    T_RETURN = 282,
    T_NEW = 283,
    T_CIN = 284,
    T_COUT = 285,
    T_MAIN = 286,
    T_THIS = 287,
    T_ID = 288,
    T_OROP = 289,
    T_ANDOP = 290,
    T_EQUIOP = 291,
    T_ADDOP = 292,
    T_MULOP = 293,
    T_INCDEC = 294,
    T_SIZEOP = 295,
    T_LISTFUNC = 296,
    T_LPAREN = 297,
    T_RPAREN = 298,
    T_SEMI = 299,
    T_DOT = 300,
    T_COMMA = 301,
    T_ASSING = 302,
    T_COLON = 303,
    T_LBRACK = 304,
    T_RBRACK = 305,
    T_REFER = 306,
    T_LBRACE = 307,
    T_RBRACE = 308,
    T_METH = 309,
    T_INP = 310,
    T_OUT = 311,
    T_EOF = 312,
    T_ASSIGN = 313,
    T_CASE = 314,
    T_CCONST = 315,
    T_EQUOP = 316,
    T_FLOAT = 317,
    T_NOTOP = 318,
    T_RELOP = 319,
    T_VOID = 320,
    T = 321
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 33 "bison.y" /* yacc.c:355  */

	int intval;
	double doubleval; 
    char *strval;

#line 202 "bison.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 219 "bison.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   834

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  82
/* YYNRULES -- Number of rules.  */
#define YYNRULES  176
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  345

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   321

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    54,    54,    56,    57,    59,    60,    61,    62,    63,
      64,    66,    68,    69,    71,    72,    73,    74,    75,    77,
      78,    80,    81,    83,    84,    86,    88,    90,    91,    93,
      94,    95,    96,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   118,   119,   120,   121,   122,   124,   125,   127,
     128,   130,   131,   133,   134,   135,   136,   138,   140,   141,
     143,   145,   147,   148,   150,   151,   153,   154,   155,   156,
     158,   159,   161,   162,   164,   166,   167,   169,   171,   173,
     175,   176,   178,   180,   182,   183,   185,   187,   189,   190,
     192,   193,   195,   197,   199,   201,   202,   204,   206,   207,
     209,   210,   211,   213,   214,   216,   218,   220,   221,   223,
     224,   226,   228,   229,   230,   231,   233,   234,   236,   237,
     239,   240,   242,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   254,   256,   258,   259,   261,   263,   265,
     266,   268,   270,   271,   273,   274,   275,   276,   278,   279,
     281,   282,   283,   285,   286,   288,   290,   291,   293,   294,
     296,   298,   299,   301,   303,   305,   307
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_INT", "T_ENUM", "T_LENGTH",
  "T_ICONST", "T_FCONST", "T_TYPEDEF", "T_CHAR", "T_STRING", "T_SCONST",
  "T_CLASS", "T_PRIVATE", "T_PROTECTED", "T_PUBLIC", "T_STATIC", "T_UNION",
  "T_LIST", "T_CONTINUE", "T_BREAK", "T_IF", "T_ELSE", "T_WHILE", "T_FOR",
  "T_SWITCH", "T_DEFAULT", "T_RETURN", "T_NEW", "T_CIN", "T_COUT",
  "T_MAIN", "T_THIS", "T_ID", "T_OROP", "T_ANDOP", "T_EQUIOP", "T_ADDOP",
  "T_MULOP", "T_INCDEC", "T_SIZEOP", "T_LISTFUNC", "T_LPAREN", "T_RPAREN",
  "T_SEMI", "T_DOT", "T_COMMA", "T_ASSING", "T_COLON", "T_LBRACK",
  "T_RBRACK", "T_REFER", "T_LBRACE", "T_RBRACE", "T_METH", "T_INP",
  "T_OUT", "T_EOF", "T_ASSIGN", "T_CASE", "T_CCONST", "T_EQUOP", "T_FLOAT",
  "T_NOTOP", "T_RELOP", "T_VOID", "T", "$accept", "program",
  "global_declarations", "global_declaration", "typedef_declaration",
  "typename", "standard_type", "listspec", "dims", "dim",
  "enum_declaration", "enum_body", "id_list", "initializer", "init_value",
  "expression", "variable", "general_expression", "assignment",
  "expression_list", "constant", "listexpression", "init_values",
  "class_declaration", "class_body", "parent", "members_methods", "access",
  "member_or_method", "member", "var_declaration", "variabledefs",
  "variabledef", "anonymous_union", "union_body", "fields", "field",
  "method", "short_func_declaration", "short_par_func_header",
  "func_header_start", "parameter_types", "pass_list_dims",
  "nopar_func_header", "union_declaration", "global_var_declaration",
  "init_variabledefs", "init_variabledef", "func_declaration",
  "full_func_declaration", "full_par_func_header",
  "class_func_header_start", "func_class", "parameter_list",
  "pass_variabledef", "nopar_class_func_header", "decl_statements",
  "declarations", "decltype", "statements", "statement",
  "expression_statement", "if_statement", "if_tail", "while_statement",
  "for_statement", "optexpr", "switch_statement", "switch_tail",
  "decl_cases", "casestatements", "casestatement", "single_casestatement",
  "return_statement", "io_statement", "in_list", "in_item", "out_list",
  "out_item", "comp_statement", "main_function", "main_header", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
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

#define YYPACT_NINF -278

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-278)))

#define YYTABLE_NINF -158

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -278,    34,   114,  -278,    18,    26,   168,  -278,  -278,    57,
      66,  -278,  -278,  -278,  -278,  -278,   116,  -278,  -278,  -278,
    -278,   124,   127,   156,  -278,  -278,  -278,  -278,   141,   157,
     152,  -278,   171,   173,   188,  -278,   116,   206,   216,  -278,
     229,   226,   227,  -278,  -278,    15,  -278,   376,   376,    27,
     376,   376,   218,   256,   247,   260,   261,   251,   245,   168,
     252,    73,   266,   614,  -278,  -278,   116,  -278,     5,   174,
     186,   258,  -278,  -278,  -278,  -278,   257,   259,   263,   264,
     265,   267,   653,   268,   269,   255,  -278,   771,   105,   771,
     270,   276,  -278,   693,   376,  -278,   771,   149,   153,   228,
    -278,  -278,  -278,   273,   426,   172,   476,  -278,  -278,  -278,
    -278,  -278,  -278,  -278,  -278,  -278,   274,  -278,    32,   195,
     275,   281,  -278,   226,    83,  -278,  -278,  -278,  -278,    95,
     116,  -278,   132,  -278,  -278,  -278,   271,  -278,   614,  -278,
     149,   177,   286,   289,  -278,   290,   289,  -278,  -278,  -278,
    -278,   168,  -278,   168,   771,  -278,  -278,   771,   771,   653,
     771,   283,   291,   771,   105,   771,    43,   125,   149,   771,
     297,   196,   283,   293,   295,   149,   771,   771,   771,   771,
     771,   771,  -278,   693,   311,   771,   771,  -278,   771,  -278,
     172,   476,     2,   116,  -278,  -278,   290,  -278,  -278,  -278,
    -278,   324,  -278,   -11,   312,   313,   314,    13,   163,   231,
    -278,  -278,  -278,    11,  -278,  -278,    97,  -278,  -278,  -278,
     271,    33,    32,   203,   209,   210,   315,   217,  -278,   223,
     125,   -15,  -278,   283,   147,  -278,   224,  -278,  -278,  -278,
    -278,    64,    64,    43,   149,   149,   149,   321,  -278,   185,
    -278,   283,   116,   232,   226,  -278,  -278,  -278,  -278,  -278,
     163,   216,   116,  -278,  -278,  -278,  -278,  -278,  -278,   272,
     325,  -278,   116,   322,  -278,   614,  -278,  -278,  -278,  -278,
    -278,  -278,   574,   574,   653,   162,  -278,  -278,   105,  -278,
     771,  -278,  -278,  -278,   244,  -278,  -278,  -278,   327,   340,
      15,  -278,  -278,  -278,   352,  -278,   332,    41,    35,  -278,
    -278,  -278,  -278,  -278,  -278,   335,    33,   574,  -278,   732,
     331,    35,    80,   168,   337,    53,  -278,   336,  -278,   345,
     574,   343,   168,    53,  -278,  -278,   524,   574,   476,   326,
    -278,  -278,  -278,   476,  -278
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     1,    15,     0,     0,    14,    17,     0,
       0,    13,    16,    18,     3,     5,    20,    12,     6,     7,
     108,     0,     0,     0,     8,     9,    10,   109,     0,     0,
       0,     2,     0,     0,     0,    15,    20,    73,     0,    19,
       0,    30,     0,   106,    94,     0,    95,   129,   129,     0,
     129,   129,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,     0,   129,   107,   104,    20,   102,    20,     0,
       0,     0,    64,    65,    66,   128,     0,     0,     0,     0,
       0,     0,   129,     0,     0,     0,    56,   129,   129,   129,
       0,   129,   142,    62,   129,    63,   129,    60,    44,     0,
      58,    48,    51,     0,   129,     0,   124,   131,   132,   133,
     134,   135,   136,   137,   138,   139,     0,   121,    20,     0,
       0,     0,   176,    30,     0,    25,    22,    72,    70,    79,
      20,    92,     0,    91,   103,   116,    87,   115,   129,    29,
      31,    44,     0,     0,   105,   100,    22,   119,    99,   118,
      96,     0,   114,     0,   129,   140,   141,   129,   129,   129,
     129,   149,     0,   129,   129,   129,    40,    42,    41,   129,
       0,     0,    61,     0,     0,    39,   129,   129,   129,   129,
     129,   129,    43,    62,     0,   129,   129,   143,   129,   112,
       0,   122,    55,    20,   130,   110,     0,   113,   111,   175,
      28,     0,    26,     0,     0,     0,     0,    79,     0,     0,
      86,    89,    90,     0,    21,    69,     0,    55,    22,   120,
     101,    20,    20,     0,     0,     0,     0,     0,   165,     0,
     170,     0,   169,   173,     0,   172,     0,    50,    49,    67,
     174,    33,    34,    37,    38,    35,    36,     0,    53,     0,
      59,    57,    20,     0,    30,    11,    76,    77,    78,    71,
       0,     0,    20,    75,    80,    82,    83,    81,    93,     0,
       0,    84,    20,     0,    24,   129,    32,   100,    22,    98,
     117,    46,   129,   129,   129,     0,    47,   166,   129,   167,
     129,    54,    45,    52,     0,   127,    27,    74,     0,     0,
       0,    85,    23,    68,   146,   147,     0,   129,     0,   151,
     153,   168,   171,   126,    88,    22,    20,   129,   144,   129,
       0,     0,   129,     0,     0,   156,   159,     0,   145,     0,
     129,     0,     0,   154,   152,   158,   129,   129,   162,   129,
     164,   163,   148,   161,   160
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -278,  -278,  -278,  -278,  -278,    -2,   302,   -14,  -114,  -278,
    -278,  -278,  -278,  -109,  -127,   -18,   -24,   -72,   194,   211,
    -277,  -278,  -278,  -278,  -278,  -278,  -278,   191,   142,  -278,
    -192,  -178,   -13,  -278,   146,  -278,   277,  -278,   408,  -278,
     409,  -278,   193,   410,  -278,  -278,  -278,   353,  -278,  -278,
    -278,  -278,  -278,   372,   200,  -278,    25,   117,   -42,  -103,
     -93,  -278,  -278,  -278,  -278,  -278,  -152,  -278,  -278,  -278,
     101,  -195,    90,  -278,  -278,  -278,   139,  -278,   140,  -278,
    -278,  -278
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    14,    15,   130,    17,   143,   136,   214,
      18,    54,   124,    64,   139,    97,    98,    99,   100,   173,
     101,   102,   216,    19,    57,    58,   207,   208,   263,   264,
     131,   209,   210,   266,    60,   132,   133,   267,   268,    21,
     269,    69,   148,   270,    24,    25,    42,    43,    26,    27,
      28,    29,    62,    70,   149,    30,   103,   104,   142,   106,
     107,   108,   109,   318,   110,   111,   162,   112,   309,   324,
     325,   326,   310,   113,   114,   231,   232,   234,   235,   115,
      31,    32
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      16,   191,    40,    41,    36,   105,   105,   226,   105,   105,
     161,   215,   203,   194,   200,   253,   265,   273,    35,   171,
     -13,   172,    55,    39,     7,     8,   204,   205,   206,   287,
      35,   327,   220,   255,     3,   -13,     7,     8,   213,   141,
     288,    72,    73,    68,   331,   140,    74,   118,    11,    33,
      39,    39,   105,    41,   146,   147,   145,    75,    67,    34,
      11,   274,   190,   141,   167,   141,   259,   320,   265,   166,
     117,   168,   141,   116,   294,   120,   121,    12,   175,   320,
      13,   179,   223,   196,   277,   224,   225,   161,   227,    12,
      37,   229,    13,   233,  -157,    95,    75,   236,   194,    38,
     321,   178,   179,   193,   180,   147,   320,   181,   204,   205,
     206,   172,   321,   249,   141,   -97,   251,     4,     5,   174,
     140,    75,     6,     7,     8,   180,     9,   135,   181,   201,
     335,    10,   306,  -155,    39,    35,   202,    86,   335,   321,
     230,     7,     8,   275,   344,   296,    90,    11,   303,   221,
     276,   222,   141,   141,   141,   141,   141,   141,   241,   242,
     243,   244,   245,   246,   220,    11,    35,   329,    44,    45,
     184,    35,     7,     8,   185,    35,    12,     7,     8,    13,
     261,     7,     8,   176,   177,   211,   178,   179,   252,   304,
     305,   289,   182,    48,    12,   183,    11,    13,   184,    49,
      46,    11,   185,   290,    50,   192,   262,   278,    47,   147,
     180,   186,   161,   181,   307,    52,   182,   150,   233,   183,
     151,   308,   184,    51,   328,    12,   185,   338,    13,   152,
      12,   188,   153,    13,    12,   293,   343,    13,   197,   238,
      53,   153,   188,   340,   342,   194,   281,   161,   299,   188,
     194,   141,   282,   283,    56,   188,   188,   140,   262,   301,
     285,   122,    61,   188,   230,   323,   286,   291,    59,   188,
     188,    65,   187,    66,   188,   271,   295,   272,   272,    35,
     332,    71,    72,    73,    63,     7,     8,    74,   313,   123,
     272,   125,    75,   126,   127,   128,   134,   129,   316,   137,
     154,   155,   278,   156,    83,   157,   158,   159,    86,   160,
     163,   165,   169,    87,   300,    88,    89,    90,    91,   217,
     213,   193,   218,   219,   164,    93,   189,   195,   198,   188,
     252,    71,    72,    73,   199,   228,    95,    74,    12,    96,
     237,    13,    75,   239,   248,    76,    77,    78,   240,    79,
      80,    81,   320,    82,    83,    84,    85,   254,    86,   284,
     256,   257,   258,    87,   292,    88,    89,    90,    91,    46,
      92,   314,   302,   315,   317,    93,   319,   -97,    94,   330,
     250,    71,    72,    73,   336,   321,    95,    74,   337,    96,
     334,   339,    75,   170,   247,    76,    77,    78,   260,    79,
      80,    81,   297,    82,    83,    84,    85,   298,    86,   212,
      20,    22,    23,    87,   279,    88,    89,    90,    91,   144,
      92,   119,   280,   333,   322,    93,   341,   311,    94,  -125,
     312,    71,    72,    73,     0,     0,    95,    74,     0,    96,
       0,     0,    75,     0,     0,    76,    77,    78,     0,    79,
      80,    81,     0,    82,    83,    84,    85,     0,    86,     0,
       0,     0,     0,    87,     0,    88,    89,    90,    91,     0,
      92,     0,     0,     0,     0,    93,     0,     0,    94,  -123,
       0,    71,    72,    73,     0,     0,    95,    74,     0,    96,
       0,     0,    75,     0,     0,    76,    77,    78,     0,    79,
      80,    81,     0,    82,    83,    84,    85,     0,    86,  -129,
       0,     0,     0,    87,     0,    88,    89,    90,    91,     0,
      92,     0,     0,     0,     0,    93,     0,     0,    94,    71,
      72,    73,     0,     0,     0,    74,    95,     0,     0,    96,
      75,     0,     0,    76,    77,    78,     0,    79,    80,    81,
       0,    82,    83,    84,    85,     0,    86,     0,     0,     0,
       0,    87,     0,    88,    89,    90,    91,     0,    92,     0,
       0,     0,     0,    93,     0,     0,    94,     0,     0,    71,
      72,    73,     0,   308,    95,    74,     0,    96,     0,     0,
      75,     0,     0,    76,    77,    78,     0,    79,    80,    81,
       0,    82,    83,    84,    85,     0,    86,     0,     0,     0,
       0,    87,     0,    88,    89,    90,    91,     0,    92,    71,
      72,    73,     0,    93,     0,    74,    94,     0,     0,     0,
      75,     0,     0,     0,    95,     0,     0,    96,     0,     0,
       0,     0,    83,     0,     0,     0,    86,     0,     0,     0,
       0,    87,     0,    88,    89,    90,    91,     0,    71,    72,
      73,     0,     0,    93,    74,     0,   138,     0,     0,    75,
       0,     0,     0,     0,    95,     0,     0,    96,     0,     0,
       0,    83,     0,     0,     0,    86,     0,     0,     0,     0,
      87,     0,    88,    89,    90,    91,     0,  -150,    71,    72,
      73,     0,    93,     0,    74,     0,     0,     0,     0,    75,
       0,     0,     0,    95,     0,     0,    96,     0,     0,     0,
       0,    83,     0,     0,     0,    86,  -129,     0,     0,     0,
      87,     0,    88,    89,    90,    91,     0,    71,    72,    73,
       0,     0,    93,    74,     0,     0,     0,     0,    75,     0,
       0,     0,     0,    95,     0,     0,    96,     0,     0,     0,
      83,     0,     0,     0,    86,     0,     0,     0,     0,    87,
       0,    88,    89,    90,    91,  -150,    71,    72,    73,     0,
       0,    93,    74,     0,     0,     0,     0,    75,     0,     0,
       0,     0,    95,     0,     0,    96,     0,     0,     0,    83,
       0,     0,     0,    86,     0,     0,     0,     0,    87,     0,
      88,    89,    90,    91,     0,     0,     0,     0,     0,     0,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    95,     0,     0,    96
};

static const yytype_int16 yycheck[] =
{
       2,   104,    16,    16,     6,    47,    48,   159,    50,    51,
      82,   138,   126,   106,   123,   193,   208,     6,     3,    91,
      18,    93,    36,    18,     9,    10,    13,    14,    15,    44,
       3,   308,   146,    44,     0,    33,     9,    10,    49,    63,
      55,     6,     7,    45,   321,    63,    11,    49,    33,    31,
      18,    18,    94,    66,    68,    68,    51,    16,    43,    33,
      33,    50,   104,    87,    88,    89,    53,    26,   260,    87,
      43,    89,    96,    48,   252,    50,    51,    62,    96,    26,
      65,    38,   154,    51,    51,   157,   158,   159,   160,    62,
      33,   163,    65,   165,    53,    60,    16,   169,   191,    33,
      59,    37,    38,   105,    61,   118,    26,    64,    13,    14,
      15,   183,    59,   185,   138,    42,   188,     3,     4,    94,
     138,    16,     8,     9,    10,    61,    12,    54,    64,    46,
     325,    17,   284,    53,    18,     3,    53,    32,   333,    59,
     164,     9,    10,    46,   339,   254,    41,    33,   275,   151,
      53,   153,   176,   177,   178,   179,   180,   181,   176,   177,
     178,   179,   180,   181,   278,    33,     3,   319,    44,    42,
      45,     3,     9,    10,    49,     3,    62,     9,    10,    65,
      17,     9,    10,    34,    35,    53,    37,    38,   190,   282,
     283,    44,    39,    52,    62,    42,    33,    65,    45,    42,
      44,    33,    49,    56,    52,    33,   208,   221,    52,   222,
      61,    58,   284,    64,    52,    42,    39,    43,   290,    42,
      46,    59,    45,    52,   317,    62,    49,   330,    65,    43,
      62,    46,    46,    65,    62,    50,   339,    65,    43,    43,
      52,    46,    46,   336,   337,   338,    43,   319,   262,    46,
     343,   275,    43,    43,    48,    46,    46,   275,   260,   272,
      43,    43,    33,    46,   288,   307,    43,    43,    52,    46,
      46,    44,    44,    46,    46,    44,    44,    46,    46,     3,
     322,     5,     6,     7,    58,     9,    10,    11,    44,    33,
      46,    44,    16,    33,    33,    44,    44,    52,   300,    33,
      42,    44,   316,    44,    28,    42,    42,    42,    32,    42,
      42,    56,    42,    37,    42,    39,    40,    41,    42,    33,
      49,   323,    33,    33,    55,    49,    53,    53,    53,    46,
     332,     5,     6,     7,    53,    44,    60,    11,    62,    63,
      43,    65,    16,    50,    33,    19,    20,    21,    53,    23,
      24,    25,    26,    27,    28,    29,    30,    33,    32,    44,
      48,    48,    48,    37,    43,    39,    40,    41,    42,    44,
      44,    44,    50,    33,    22,    49,    44,    42,    52,    48,
     186,     5,     6,     7,    48,    59,    60,    11,    43,    63,
      53,    48,    16,    91,   183,    19,    20,    21,   207,    23,
      24,    25,   260,    27,    28,    29,    30,   261,    32,   132,
       2,     2,     2,    37,   221,    39,    40,    41,    42,    66,
      44,    49,   222,   322,   307,    49,   336,   288,    52,    53,
     290,     5,     6,     7,    -1,    -1,    60,    11,    -1,    63,
      -1,    -1,    16,    -1,    -1,    19,    20,    21,    -1,    23,
      24,    25,    -1,    27,    28,    29,    30,    -1,    32,    -1,
      -1,    -1,    -1,    37,    -1,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    -1,    49,    -1,    -1,    52,    53,
      -1,     5,     6,     7,    -1,    -1,    60,    11,    -1,    63,
      -1,    -1,    16,    -1,    -1,    19,    20,    21,    -1,    23,
      24,    25,    -1,    27,    28,    29,    30,    -1,    32,    33,
      -1,    -1,    -1,    37,    -1,    39,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    -1,    49,    -1,    -1,    52,     5,
       6,     7,    -1,    -1,    -1,    11,    60,    -1,    -1,    63,
      16,    -1,    -1,    19,    20,    21,    -1,    23,    24,    25,
      -1,    27,    28,    29,    30,    -1,    32,    -1,    -1,    -1,
      -1,    37,    -1,    39,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    52,    -1,    -1,     5,
       6,     7,    -1,    59,    60,    11,    -1,    63,    -1,    -1,
      16,    -1,    -1,    19,    20,    21,    -1,    23,    24,    25,
      -1,    27,    28,    29,    30,    -1,    32,    -1,    -1,    -1,
      -1,    37,    -1,    39,    40,    41,    42,    -1,    44,     5,
       6,     7,    -1,    49,    -1,    11,    52,    -1,    -1,    -1,
      16,    -1,    -1,    -1,    60,    -1,    -1,    63,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    37,    -1,    39,    40,    41,    42,    -1,     5,     6,
       7,    -1,    -1,    49,    11,    -1,    52,    -1,    -1,    16,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    63,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,
      37,    -1,    39,    40,    41,    42,    -1,    44,     5,     6,
       7,    -1,    49,    -1,    11,    -1,    -1,    -1,    -1,    16,
      -1,    -1,    -1,    60,    -1,    -1,    63,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    32,    33,    -1,    -1,    -1,
      37,    -1,    39,    40,    41,    42,    -1,     5,     6,     7,
      -1,    -1,    49,    11,    -1,    -1,    -1,    -1,    16,    -1,
      -1,    -1,    -1,    60,    -1,    -1,    63,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    37,
      -1,    39,    40,    41,    42,    43,     5,     6,     7,    -1,
      -1,    49,    11,    -1,    -1,    -1,    -1,    16,    -1,    -1,
      -1,    -1,    60,    -1,    -1,    63,    -1,    -1,    -1,    28,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    -1,    37,    -1,
      39,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    -1,    -1,    63
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    68,    69,     0,     3,     4,     8,     9,    10,    12,
      17,    33,    62,    65,    70,    71,    72,    73,    77,    90,
     105,   106,   107,   110,   111,   112,   115,   116,   117,   118,
     122,   147,   148,    31,    33,     3,    72,    33,    33,    18,
      74,    99,   113,   114,    44,    42,    44,    52,    52,    42,
      52,    52,    42,    52,    78,    74,    48,    91,    92,    52,
     101,    33,   119,    58,    80,    44,    46,    43,    72,   108,
     120,     5,     6,     7,    11,    16,    19,    20,    21,    23,
      24,    25,    27,    28,    29,    30,    32,    37,    39,    40,
      41,    42,    44,    49,    52,    60,    63,    82,    83,    84,
      85,    87,    88,   123,   124,   125,   126,   127,   128,   129,
     131,   132,   134,   140,   141,   146,   123,    43,    72,   120,
     123,   123,    43,    33,    79,    44,    33,    33,    44,    52,
      72,    97,   102,   103,    44,    54,    75,    33,    52,    81,
      82,    83,   125,    74,   114,    51,    74,    99,   109,   121,
      43,    46,    43,    46,    42,    44,    44,    42,    42,    42,
      42,    84,   133,    42,    55,    56,    82,    83,    82,    42,
      73,    84,    84,    86,   123,    82,    34,    35,    37,    38,
      61,    64,    39,    42,    45,    49,    58,    44,    46,    53,
     125,   126,    33,    72,   127,    53,    51,    43,    53,    53,
      80,    46,    53,    75,    13,    14,    15,    93,    94,    98,
      99,    53,   103,    49,    76,    81,    89,    33,    33,    33,
      75,    72,    72,    84,    84,    84,   133,    84,    44,    84,
      83,   142,   143,    84,   144,   145,    84,    43,    43,    50,
      53,    82,    82,    82,    82,    82,    82,    86,    33,    84,
      85,    84,    72,    98,    33,    44,    48,    48,    48,    53,
      94,    17,    72,    95,    96,    97,   100,   104,   105,   107,
     110,    44,    46,     6,    50,    46,    53,    51,    74,   109,
     121,    43,    43,    43,    44,    43,    43,    44,    55,    44,
      56,    43,    43,    50,    98,    44,    80,    95,   101,    74,
      42,    99,    50,    81,   127,   127,   133,    52,    59,   135,
     139,   143,   145,    44,    44,    33,    72,    22,   130,    44,
      26,    59,   124,   125,   136,   137,   138,    87,   127,   133,
      48,    87,   125,   137,    53,   138,    48,    43,   126,    48,
     127,   139,   127,   126,   138
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    67,    68,    69,    69,    70,    70,    70,    70,    70,
      70,    71,    72,    72,    73,    73,    73,    73,    73,    74,
      74,    75,    75,    76,    76,    77,    78,    79,    79,    80,
      80,    81,    81,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    83,    83,    83,    83,    83,    84,    84,    85,
      85,    86,    86,    87,    87,    87,    87,    88,    89,    89,
      90,    91,    92,    92,    93,    93,    94,    94,    94,    94,
      95,    95,    96,    96,    97,    98,    98,    99,   100,   101,
     102,   102,   103,   104,   105,   105,   106,   107,   108,   108,
     109,   109,   110,   111,   112,   113,   113,   114,   115,   115,
     116,   116,   116,   117,   117,   118,   119,   120,   120,   121,
     121,   122,   123,   123,   123,   123,   124,   124,   125,   125,
     126,   126,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   127,   128,   129,   130,   130,   131,   132,   133,
     133,   134,   135,   135,   136,   136,   136,   136,   137,   137,
     138,   138,   138,   139,   139,   140,   141,   141,   142,   142,
     143,   144,   144,   145,   146,   147,   148
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     1,     1,     1,     1,     1,
       1,     6,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     2,     0,     3,     2,     4,     3,     4,     2,     2,
       0,     1,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     2,     1,     4,     4,     4,     1,     3,
       3,     1,     4,     3,     4,     2,     1,     3,     1,     3,
       1,     1,     0,     1,     1,     1,     1,     3,     3,     1,
       4,     4,     2,     0,     3,     2,     2,     2,     2,     0,
       1,     1,     1,     1,     3,     3,     1,     3,     3,     3,
       2,     1,     1,     1,     2,     2,     4,     3,     4,     2,
       1,     2,     3,     4,     3,     3,     1,     2,     1,     1,
       4,     4,     4,     4,     4,     4,     2,     4,     2,     1,
       2,     3,     2,     1,     1,     0,     5,     4,     1,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     1,     2,     6,     2,     0,     5,     9,     1,
       0,     5,     3,     1,     2,     1,     1,     0,     2,     1,
       4,     4,     3,     4,     4,     3,     4,     4,     3,     1,
       1,     3,     1,     1,     3,     4,     4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
      
#line 1660 "bison.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 309 "bison.y" /* yacc.c:1906  */


