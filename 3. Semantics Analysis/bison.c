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
#line 1 "bison.y" /* yacc.c:339  */

#include <string.h>
#include <stdio.h>
#include "c600.h"
#include "types.h"
#include "symbol.h"
#include "ast.h"
#include "error.h"


/* ---------------------------------------------------------------------
   ------------- External variables & functions from main.c ------------
   --------------------------------------------------------------------- */

extern void yyerror(const char *message);


/* ---------------------------------------------------------------------
   ------------- External variables & functions from lexer.l -----------
   --------------------------------------------------------------------- */

extern int yylex();
extern int lineno;
extern char *yytext;

/* ---------------------------------------------------------------------
   --------------- Local variables & functions for bison.y -------------
   --------------------------------------------------------------------- */

AST_program ast;



#line 100 "bison.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "bison.h".  */
#ifndef YY_YY_BISON_H_INCLUDED
# define YY_YY_BISON_H_INCLUDED
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
    T_EOF = 0,
    T_ICONST = 258,
    T_FCONST = 259,
    T_TYPEDEF = 260,
    T_CHAR = 261,
    T_STRING = 262,
    T_SCONST = 263,
    T_CLASS = 264,
    T_PRIVATE = 265,
    T_PROTECTED = 266,
    T_PUBLIC = 267,
    T_STATIC = 268,
    T_UNION = 269,
    T_LIST = 270,
    T_CONTINUE = 271,
    T_BREAK = 272,
    T_IF = 273,
    T_ELSE = 274,
    T_WHILE = 275,
    T_FOR = 276,
    T_SWITCH = 277,
    T_DEFAULT = 278,
    T_RETURN = 279,
    T_NEW = 280,
    T_CIN = 281,
    T_COUT = 282,
    T_MAIN = 283,
    T_THIS = 284,
    T_ID = 285,
    T_OROP = 286,
    T_ANDOP = 287,
    T_EQUOP = 288,
    T_ADDOP = 289,
    T_MULOP = 290,
    T_INCDEC = 291,
    T_SIZEOP = 292,
    T_LISTFUNC = 293,
    T_LPAREN = 294,
    T_RPAREN = 295,
    T_SEMI = 296,
    T_DOT = 297,
    T_COMMA = 298,
    T_COLON = 299,
    T_LBRACK = 300,
    T_RBRACK = 301,
    T_REFER = 302,
    T_LBRACE = 303,
    T_RBRACE = 304,
    T_METH = 305,
    T_INP = 306,
    T_OUT = 307,
    T_ASSIGN = 308,
    T_CASE = 309,
    T_CCONST = 310,
    T_FLOAT = 311,
    T_NOTOP = 312,
    T_RELOP = 313,
    T_VOID = 314,
    T_ENUM = 315,
    T_INT = 316,
    T_LENGTH = 317,
    UMINUS = 318,
    LOWER_THAN_ELSE = 319
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 38 "bison.y" /* yacc.c:355  */

    int intval;
    float floatval; 
    char charval;
    char *strval;

    Identifier identifier;

    Access access;
    Type type;
    List list;

    AST_constant constant;
    AST_variabledef variabledef;
    AST_func_header_start func_header_start;
    AST_class_func_header_start class_func_header_start;
    AST_typedef typedef_dcl;
    AST_passvar passvar;
    AST_var_declaration var_declaration;
    AST_member member;
    AST_union_dcl union_dcl;
    AST_short_func_dcl short_func_dcl;
    AST_member_or_method member_or_method;
    AST_class_body class_body;
    AST_class_dcl class_dcl;
    AST_general_expr general_expr;
    AST_stmt stmt;
    AST_casestmt casestmt;
    AST_decl_cases decl_cases;
    AST_full_par_func_header full_par_func_header;
    AST_full_func_dcl full_func_dcl;
    AST_dcl_stmt dcl_stmt;
    AST_switch_tail switch_tail;
    AST_init_value init_value;
    AST_expr expr;
    AST_enum_dcl enum_dcl;
    AST_func_dcl func_dcl;
    AST_init_variabledef init_variabledef;
    AST_global_var_declaration global_var_declaration;
    AST_assignment assignment;
    AST_variable variable;
    AST_exprlist exprlist;
    AST_global_decl global_decl;
    AST_program program;

#line 252 "bison.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 269 "bison.c" /* yacc.c:358  */

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
#define YYLAST   730

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  65
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  82
/* YYNRULES -- Number of rules.  */
#define YYNRULES  176
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  345

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   319

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
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   213,   213,   215,   222,   224,   225,   226,   227,   228,
     229,   231,   233,   234,   236,   237,   238,   239,   240,   242,
     243,   245,   246,   248,   249,   251,   253,   255,   256,   258,
     259,   261,   262,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   284,   285,   286,   287,   288,   291,   292,   294,
     295,   297,   298,   300,   301,   302,   303,   305,   307,   308,
     310,   312,   314,   315,   317,   318,   320,   321,   322,   323,
     325,   326,   328,   329,   331,   333,   334,   336,   338,   340,
     342,   343,   345,   347,   349,   350,   352,   354,   356,   357,
     359,   360,   362,   364,   366,   368,   369,   371,   373,   374,
     376,   377,   378,   380,   381,   383,   385,   387,   388,   390,
     391,   393,   395,   396,   397,   398,   400,   401,   403,   404,
     406,   407,   409,   410,   411,   412,   413,   414,   415,   416,
     417,   418,   419,   421,   423,   427,   429,   431,   434,   437,
     438,   440,   443,   444,   446,   447,   448,   449,   451,   452,
     454,   455,   456,   458,   459,   461,   463,   464,   466,   467,
     469,   471,   472,   474,   476,   478,   480
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "\"integer constant\"",
  "\"float constant\"", "\"typedef\"", "\"char\"", "\"string\"",
  "\"string const\"", "\"class\"", "\"private\"", "\"protected\"",
  "\"public\"", "\"static\"", "\"union\"", "\"list\"", "\"continue\"",
  "\"break\"", "\"if\"", "\"else\"", "\"while\"", "\"for\"", "\"switch\"",
  "\"default\"", "\"return\"", "\"new\"", "\"cin\"", "\"cout\"",
  "\"main\"", "\"this\"", "\"id\"", "\"||\"", "\"&&\"", "\"== or !=\"",
  "\"+ or -\"", "\"* or / or %\"", "\"-- or ++\"", "\"sizeof\"",
  "\"listfunc\"", "\"(\"", "\")\"", "\";\"", "\".\"", "\",\"", "\":\"",
  "\"[\"", "\"]\"", "\"&\"", "\"{\"", "\"}\"", "\"::\"", "\"<<\"",
  "\">>\"", "\"=\"", "\"case\"", "\"char const\"", "\"float\"", "\"!\"",
  "\"> or >= or < or <=\"", "\"void\"", "\"enum\"", "\"int\"",
  "\"length\"", "UMINUS", "LOWER_THAN_ELSE", "$accept", "program",
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
     315,   316,   317,   318,   319
};
# endif

#define YYPACT_NINF -253

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-253)))

#define YYTABLE_NINF -158

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -253,    34,    21,  -253,   390,  -253,  -253,    24,    80,  -253,
    -253,  -253,    97,   111,  -253,  -253,   138,  -253,  -253,  -253,
    -253,   122,   128,    71,  -253,  -253,  -253,  -253,   124,   158,
     176,  -253,   183,  -253,   138,   186,   195,   205,   228,  -253,
     224,   269,    30,  -253,  -253,   140,  -253,   311,   311,   177,
     311,   311,   295,   304,   298,   293,   390,   301,   313,   303,
     306,    78,   321,   510,  -253,  -253,   138,  -253,    23,    53,
      98,  -253,  -253,  -253,  -253,   312,   314,   315,   322,   324,
     325,   548,   326,   318,   330,  -253,   663,   107,   663,   338,
     153,  -253,   587,   311,  -253,   663,   345,   672,   126,   161,
    -253,  -253,  -253,   336,   354,   520,   397,  -253,  -253,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,   337,  -253,    27,   182,
     340,   349,  -253,  -253,  -253,   288,   138,  -253,    55,  -253,
    -253,   269,    15,  -253,  -253,  -253,   342,  -253,   510,  -253,
     672,   281,   364,   374,  -253,   376,   374,  -253,  -253,  -253,
    -253,   390,  -253,   390,  -253,  -253,   663,   663,   548,   663,
     365,   366,   663,   107,   663,  -253,   203,  -253,   663,   372,
     215,   365,   379,   380,  -253,   663,   663,   663,   663,   663,
     663,   663,  -253,   587,   398,   663,   663,  -253,   663,  -253,
     520,   397,    14,   138,  -253,  -253,   376,  -253,  -253,  -253,
      18,   386,   388,   393,   132,   220,   196,  -253,  -253,  -253,
    -253,   409,  -253,    22,  -253,  -253,   105,  -253,  -253,  -253,
     342,    37,    27,   219,   240,   399,   251,  -253,   252,   203,
      49,  -253,   365,   164,  -253,   264,  -253,  -253,  -253,  -253,
     266,   142,   160,    44,   406,  -253,   278,   407,  -253,   265,
    -253,  -253,   138,   247,  -253,  -253,  -253,  -253,  -253,   220,
     195,   138,  -253,  -253,  -253,  -253,  -253,  -253,   411,   414,
    -253,   138,   269,   417,  -253,   510,  -253,  -253,  -253,  -253,
    -253,   483,   483,   548,   175,  -253,  -253,   107,  -253,   663,
    -253,  -253,  -253,  -253,   275,  -253,  -253,   427,   441,   140,
    -253,  -253,  -253,  -253,   451,  -253,   431,    52,    42,  -253,
    -253,  -253,  -253,  -253,  -253,   434,    37,   483,  -253,   625,
     436,    42,    86,   390,   426,    13,  -253,   438,  -253,   443,
     483,   445,   390,    13,  -253,  -253,   440,   483,   397,   248,
    -253,  -253,  -253,   397,  -253
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     1,     0,    14,    17,     0,     0,    13,
      16,    18,     0,    15,     3,     5,    20,    12,     6,     7,
     108,     0,     0,     0,     8,     9,    10,   109,     0,     0,
       0,     2,     0,    15,    20,    73,     0,     0,     0,    19,
       0,    30,     0,   106,    94,     0,    95,   129,   129,     0,
     129,   129,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    22,     0,   129,   107,   104,    20,   102,    20,     0,
       0,    64,    65,    66,   128,     0,     0,     0,     0,     0,
       0,   129,     0,     0,     0,    56,   129,   129,   129,     0,
     129,   142,    62,   129,    63,   129,     0,    60,    44,     0,
      58,    48,    51,     0,   129,     0,   124,   131,   132,   133,
     134,   135,   136,   137,   138,   139,     0,   121,    20,     0,
       0,     0,    22,    72,    70,    79,    20,    92,     0,    91,
     103,    30,     0,    25,   176,   116,    87,   115,   129,    29,
      31,    44,     0,     0,   105,   100,    22,   119,    99,   118,
      96,     0,   114,     0,   140,   141,   129,   129,   129,   129,
     149,     0,   129,   129,   129,    40,    42,    41,   129,     0,
       0,    61,     0,     0,    39,   129,   129,   129,   129,   129,
     129,   129,    43,    62,     0,   129,   129,   143,   129,   112,
       0,   122,    55,    20,   130,   110,     0,   113,   111,   175,
       0,     0,     0,     0,    79,     0,     0,    86,    89,    90,
      28,     0,    26,     0,    21,    69,     0,    55,    22,   120,
     101,    20,    20,     0,     0,     0,     0,   165,     0,   170,
       0,   169,   173,     0,   172,     0,    50,    49,    67,   174,
       0,    33,    34,    35,    37,    38,    36,     0,    53,     0,
      59,    57,    20,     0,    11,    76,    77,    78,    71,     0,
       0,    20,    75,    80,    82,    83,    81,    93,     0,     0,
      84,    20,    30,     0,    24,   129,    32,   100,    22,    98,
     117,   129,   129,   129,     0,    47,   166,   129,   167,   129,
      54,    46,    45,    52,     0,   127,    74,     0,     0,     0,
      85,    27,    23,    68,   146,   147,     0,   129,     0,   151,
     153,   168,   171,   126,    88,    22,    20,   129,   144,   129,
       0,     0,   129,     0,     0,   156,   159,     0,   145,     0,
     129,     0,     0,   154,   152,   158,   129,   129,   162,   129,
     164,   163,   148,   161,   160
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -253,  -253,  -253,  -253,  -253,    -2,   394,   -15,  -109,  -253,
    -253,  -253,  -253,  -117,  -123,   -47,   -55,   -70,   307,   309,
    -252,  -253,  -253,  -253,  -253,  -253,  -253,   286,   239,  -253,
    -187,  -176,   -11,  -253,   246,  -253,   383,  -253,   513,  -253,
     514,  -253,   308,   523,  -253,  -253,  -253,   464,  -253,  -253,
    -253,  -253,  -253,   484,   310,  -253,   -27,   227,   -44,   -95,
     -96,  -253,  -253,  -253,  -253,  -253,  -146,  -253,  -253,  -253,
     214,  -175,   201,  -253,  -253,  -253,   254,  -253,   253,  -253,
    -253,  -253
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    14,    15,   126,    17,   143,   136,   214,
      18,    59,   132,    64,   139,    97,    98,    99,   100,   172,
     101,   102,   216,    19,    54,    55,   204,   205,   262,   263,
     127,   206,   207,   265,    57,   128,   129,   266,   267,    21,
     268,    69,   148,   269,    24,    25,    42,    43,    26,    27,
      28,    29,    62,    70,   149,    30,   103,   104,   142,   106,
     107,   108,   109,   318,   110,   111,   161,   112,   309,   324,
     325,   326,   310,   113,   114,   230,   231,   233,   234,   115,
      31,    32
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      16,    40,    34,   105,   105,    41,   105,   105,   141,   191,
     194,   160,   225,   200,   210,   215,   140,   253,   264,    52,
     170,   116,   171,   120,   121,   273,     4,     5,     6,   -13,
       7,   141,   166,   141,     3,     8,   320,   220,    39,   165,
     141,   167,    39,    68,   -13,    71,    72,   118,   174,   105,
      73,     9,    39,   146,    35,    41,   327,   147,   211,   254,
     190,     5,     6,   213,   212,    74,   173,   321,   274,   331,
     145,    65,   264,    66,   196,   320,   294,    10,   179,   180,
      11,    12,    13,   141,   277,     9,   223,   224,   160,   226,
     286,   140,   228,   150,   232,   194,   151,    94,   235,    74,
     287,  -157,   181,   193,   208,   240,   321,   147,   229,   320,
      36,    10,    46,   171,    11,   249,    33,   -97,   251,    47,
      74,   141,   141,   141,   141,   141,   141,    37,   135,   241,
     242,   243,   244,   245,   246,  -155,    85,   306,   152,    38,
     321,   153,   201,   202,   203,    89,     5,     6,   275,   221,
     335,   222,   303,    39,   276,   301,    71,    72,   335,     5,
       6,    73,   182,    44,   344,   183,    74,    45,   184,   220,
       9,   185,    48,   329,   177,   178,   179,   180,    82,   186,
      67,   258,    85,     5,     6,   304,   305,    86,   252,    87,
      88,    89,    90,   178,   179,   180,    10,    49,    92,    11,
     181,    33,   187,   261,   188,   288,   278,     9,    94,    10,
      95,   147,    11,   160,    33,    96,   289,   117,   181,   232,
     141,   328,   197,   307,    50,   153,     5,     6,   140,   308,
      53,    51,   229,    10,   260,   338,    11,   270,    33,   271,
     340,   342,   194,    56,   343,   184,   298,   194,   185,   160,
       9,    71,    72,    58,    61,   237,    73,   261,   188,   281,
     300,    74,   188,   323,    75,    76,    77,    60,    78,    79,
      80,   320,    81,    82,    83,    84,    10,    85,   332,    11,
     282,    33,    86,   188,    87,    88,    89,    90,   295,    91,
     271,   284,   285,    92,   188,   188,    93,   316,   201,   202,
     203,   278,   321,    94,   290,    95,   291,   188,   188,   188,
      96,   293,   179,   180,    71,    72,   313,   182,   271,    73,
     183,   193,    63,   184,    74,   122,   185,    75,    76,    77,
     252,    78,    79,    80,   123,    81,    82,    83,    84,   124,
      85,   125,   130,   131,   133,    86,   134,    87,    88,    89,
      90,   137,    91,   154,   156,   155,    92,    71,    72,    93,
    -125,   157,    73,   158,   159,   162,    94,    74,    95,   163,
      75,    76,    77,    96,    78,    79,    80,   168,    81,    82,
      83,    84,   164,    85,   175,   189,   195,   213,    86,   198,
      87,    88,    89,    90,   217,    91,     5,     6,   199,    92,
      71,    72,    93,  -123,   218,    73,   219,   227,   188,    94,
      74,    95,   236,    75,    76,    77,    96,    78,    79,    80,
       9,    81,    82,    83,    84,   238,    85,  -129,   248,   239,
     255,    86,   256,    87,    88,    89,    90,   257,    91,   272,
     283,   180,    92,    71,    72,    93,    10,   292,    73,    11,
     299,    33,    94,    74,    95,    46,    75,    76,    77,    96,
      78,    79,    80,   302,    81,    82,    83,    84,   314,    85,
     317,   315,   319,   -97,    86,   334,    87,    88,    89,    90,
     330,    91,   336,   337,   169,    92,    71,    72,    93,   339,
     259,    73,   247,   250,   308,    94,    74,    95,   296,    75,
      76,    77,    96,    78,    79,    80,   297,    81,    82,    83,
      84,   209,    85,    71,    72,    20,    22,    86,    73,    87,
      88,    89,    90,    74,    91,    23,     5,     6,    92,   279,
     144,    93,   280,   119,   322,    82,   333,   341,    94,    85,
      95,   311,   312,     0,    86,    96,    87,    88,    89,    90,
     192,    71,    72,     0,     0,    92,    73,     0,   138,     0,
       0,    74,     0,     0,     0,    94,     0,    95,     0,     0,
       0,     0,    96,    82,     0,     0,    10,    85,     0,    11,
       0,    33,    86,     0,    87,    88,    89,    90,     0,  -150,
      71,    72,     0,    92,     0,    73,     0,     0,     0,     0,
      74,     0,     0,    94,     0,    95,     0,     0,     0,     0,
      96,     0,    82,     0,     0,     0,    85,  -129,     0,     0,
       0,    86,     0,    87,    88,    89,    90,     0,    71,    72,
       0,     0,    92,    73,     0,     0,     0,     0,    74,     0,
       0,     0,    94,     0,    95,     0,     0,     0,     0,    96,
      82,     0,     0,     0,    85,     0,     0,     0,     0,    86,
       0,    87,    88,    89,    90,  -150,    71,    72,     0,     0,
      92,    73,     0,     0,     0,     0,    74,     0,     0,     0,
      94,     0,    95,     0,     0,     0,     0,    96,    82,     0,
       0,     0,    85,     0,     0,     0,     0,    86,     0,    87,
      88,    89,    90,   176,   177,   178,   179,   180,    92,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,     0,
      95,     0,     0,     0,     0,    96,     0,     0,     0,     0,
     181
};

static const yytype_int16 yycheck[] =
{
       2,    16,     4,    47,    48,    16,    50,    51,    63,   104,
     106,    81,   158,   122,   131,   138,    63,   193,   205,    34,
      90,    48,    92,    50,    51,     3,     5,     6,     7,    15,
       9,    86,    87,    88,     0,    14,    23,   146,    15,    86,
      95,    88,    15,    45,    30,     3,     4,    49,    95,    93,
       8,    30,    15,    68,    30,    66,   308,    68,    43,    41,
     104,     6,     7,    45,    49,    13,    93,    54,    46,   321,
      47,    41,   259,    43,    47,    23,   252,    56,    34,    35,
      59,    60,    61,   138,    47,    30,   156,   157,   158,   159,
      41,   138,   162,    40,   164,   191,    43,    55,   168,    13,
      51,    49,    58,   105,    49,   175,    54,   118,   163,    23,
      30,    56,    41,   183,    59,   185,    61,    39,   188,    48,
      13,   176,   177,   178,   179,   180,   181,    30,    50,   176,
     177,   178,   179,   180,   181,    49,    29,   283,    40,    28,
      54,    43,    10,    11,    12,    38,     6,     7,    43,   151,
     325,   153,   275,    15,    49,   272,     3,     4,   333,     6,
       7,     8,    36,    41,   339,    39,    13,    39,    42,   278,
      30,    45,    48,   319,    32,    33,    34,    35,    25,    53,
      40,    49,    29,     6,     7,   281,   282,    34,   190,    36,
      37,    38,    39,    33,    34,    35,    56,    39,    45,    59,
      58,    61,    41,   205,    43,    41,   221,    30,    55,    56,
      57,   222,    59,   283,    61,    62,    52,    40,    58,   289,
     275,   317,    40,    48,    48,    43,     6,     7,   275,    54,
      44,    48,   287,    56,    14,   330,    59,    41,    61,    43,
     336,   337,   338,    48,   339,    42,   261,   343,    45,   319,
      30,     3,     4,    48,    30,    40,     8,   259,    43,    40,
     271,    13,    43,   307,    16,    17,    18,    39,    20,    21,
      22,    23,    24,    25,    26,    27,    56,    29,   322,    59,
      40,    61,    34,    43,    36,    37,    38,    39,    41,    41,
      43,    40,    40,    45,    43,    43,    48,   299,    10,    11,
      12,   316,    54,    55,    40,    57,    40,    43,    43,    43,
      62,    46,    34,    35,     3,     4,    41,    36,    43,     8,
      39,   323,    53,    42,    13,    30,    45,    16,    17,    18,
     332,    20,    21,    22,    30,    24,    25,    26,    27,    41,
      29,    48,    41,    30,    41,    34,    40,    36,    37,    38,
      39,    30,    41,    41,    39,    41,    45,     3,     4,    48,
      49,    39,     8,    39,    39,    39,    55,    13,    57,    51,
      16,    17,    18,    62,    20,    21,    22,    39,    24,    25,
      26,    27,    52,    29,    39,    49,    49,    45,    34,    49,
      36,    37,    38,    39,    30,    41,     6,     7,    49,    45,
       3,     4,    48,    49,    30,     8,    30,    41,    43,    55,
      13,    57,    40,    16,    17,    18,    62,    20,    21,    22,
      30,    24,    25,    26,    27,    46,    29,    30,    30,    49,
      44,    34,    44,    36,    37,    38,    39,    44,    41,    30,
      41,    35,    45,     3,     4,    48,    56,    40,     8,    59,
      39,    61,    55,    13,    57,    41,    16,    17,    18,    62,
      20,    21,    22,    46,    24,    25,    26,    27,    41,    29,
      19,    30,    41,    39,    34,    49,    36,    37,    38,    39,
      44,    41,    44,    40,    90,    45,     3,     4,    48,    44,
     204,     8,   183,   186,    54,    55,    13,    57,   259,    16,
      17,    18,    62,    20,    21,    22,   260,    24,    25,    26,
      27,   128,    29,     3,     4,     2,     2,    34,     8,    36,
      37,    38,    39,    13,    41,     2,     6,     7,    45,   221,
      66,    48,   222,    49,   307,    25,   322,   336,    55,    29,
      57,   287,   289,    -1,    34,    62,    36,    37,    38,    39,
      30,     3,     4,    -1,    -1,    45,     8,    -1,    48,    -1,
      -1,    13,    -1,    -1,    -1,    55,    -1,    57,    -1,    -1,
      -1,    -1,    62,    25,    -1,    -1,    56,    29,    -1,    59,
      -1,    61,    34,    -1,    36,    37,    38,    39,    -1,    41,
       3,     4,    -1,    45,    -1,     8,    -1,    -1,    -1,    -1,
      13,    -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,
      62,    -1,    25,    -1,    -1,    -1,    29,    30,    -1,    -1,
      -1,    34,    -1,    36,    37,    38,    39,    -1,     3,     4,
      -1,    -1,    45,     8,    -1,    -1,    -1,    -1,    13,    -1,
      -1,    -1,    55,    -1,    57,    -1,    -1,    -1,    -1,    62,
      25,    -1,    -1,    -1,    29,    -1,    -1,    -1,    -1,    34,
      -1,    36,    37,    38,    39,    40,     3,     4,    -1,    -1,
      45,     8,    -1,    -1,    -1,    -1,    13,    -1,    -1,    -1,
      55,    -1,    57,    -1,    -1,    -1,    -1,    62,    25,    -1,
      -1,    -1,    29,    -1,    -1,    -1,    -1,    34,    -1,    36,
      37,    38,    39,    31,    32,    33,    34,    35,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      57,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,
      58
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    66,    67,     0,     5,     6,     7,     9,    14,    30,
      56,    59,    60,    61,    68,    69,    70,    71,    75,    88,
     103,   104,   105,   108,   109,   110,   113,   114,   115,   116,
     120,   145,   146,    61,    70,    30,    30,    30,    28,    15,
      72,    97,   111,   112,    41,    39,    41,    48,    48,    39,
      48,    48,    72,    44,    89,    90,    48,    99,    48,    76,
      39,    30,   117,    53,    78,    41,    43,    40,    70,   106,
     118,     3,     4,     8,    13,    16,    17,    18,    20,    21,
      22,    24,    25,    26,    27,    29,    34,    36,    37,    38,
      39,    41,    45,    48,    55,    57,    62,    80,    81,    82,
      83,    85,    86,   121,   122,   123,   124,   125,   126,   127,
     129,   130,   132,   138,   139,   144,   121,    40,    70,   118,
     121,   121,    30,    30,    41,    48,    70,    95,   100,   101,
      41,    30,    77,    41,    40,    50,    73,    30,    48,    79,
      80,    81,   123,    72,   112,    47,    72,    97,   107,   119,
      40,    43,    40,    43,    41,    41,    39,    39,    39,    39,
      82,   131,    39,    51,    52,    80,    81,    80,    39,    71,
      82,    82,    84,   121,    80,    39,    31,    32,    33,    34,
      35,    58,    36,    39,    42,    45,    53,    41,    43,    49,
     123,   124,    30,    70,   125,    49,    47,    40,    49,    49,
      73,    10,    11,    12,    91,    92,    96,    97,    49,   101,
      78,    43,    49,    45,    74,    79,    87,    30,    30,    30,
      73,    70,    70,    82,    82,   131,    82,    41,    82,    81,
     140,   141,    82,   142,   143,    82,    40,    40,    46,    49,
      82,    80,    80,    80,    80,    80,    80,    84,    30,    82,
      83,    82,    70,    96,    41,    44,    44,    44,    49,    92,
      14,    70,    93,    94,    95,    98,   102,   103,   105,   108,
      41,    43,    30,     3,    46,    43,    49,    47,    72,   107,
     119,    40,    40,    41,    40,    40,    41,    51,    41,    52,
      40,    40,    40,    46,    96,    41,    93,    99,    72,    39,
      97,    78,    46,    79,   125,   125,   131,    48,    54,   133,
     137,   141,   143,    41,    41,    30,    70,    19,   128,    41,
      23,    54,   122,   123,   134,   135,   136,    85,   125,   131,
      44,    85,   123,   135,    49,   136,    44,    40,   124,    44,
     125,   137,   125,   124,   136
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    65,    66,    67,    67,    68,    68,    68,    68,    68,
      68,    69,    70,    70,    71,    71,    71,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    76,    77,    77,    78,
      78,    79,    79,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    80,    80,
      80,    80,    81,    81,    81,    81,    81,    82,    82,    83,
      83,    84,    84,    85,    85,    85,    85,    86,    87,    87,
      88,    89,    90,    90,    91,    91,    92,    92,    92,    92,
      93,    93,    94,    94,    95,    96,    96,    97,    98,    99,
     100,   100,   101,   102,   103,   103,   104,   105,   106,   106,
     107,   107,   108,   109,   110,   111,   111,   112,   113,   113,
     114,   114,   114,   115,   115,   116,   117,   118,   118,   119,
     119,   120,   121,   121,   121,   121,   122,   122,   123,   123,
     124,   124,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   126,   127,   128,   128,   129,   130,   131,
     131,   132,   133,   133,   134,   134,   134,   134,   135,   135,
     136,   136,   136,   137,   137,   138,   139,   139,   140,   140,
     141,   142,   142,   143,   144,   145,   146
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
        case 2:
#line 213 "bison.y" /* yacc.c:1646  */
    {ast = (yyval.program) = ast_program((yyvsp[-1].list), (yyvsp[0].dcl_stmt));}
#line 1693 "bison.c" /* yacc.c:1646  */
    break;

  case 3:
#line 215 "bison.y" /* yacc.c:1646  */
    {
                                                                                                if((yyvsp[0].global_decl) == NULL) printf("I am null - Test & Remove\n");
                                                                                                else{
                                                                                                    (yyval.list) = list_add((yyvsp[-1].list), (void *) (yyvsp[0].global_decl));
                                                                                                    printf("I am not null - Test & Remove\n");
                                                                                                } 
                                                                                            }
#line 1705 "bison.c" /* yacc.c:1646  */
    break;

  case 4:
#line 222 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = NULL;}
#line 1711 "bison.c" /* yacc.c:1646  */
    break;

  case 5:
#line 224 "bison.y" /* yacc.c:1646  */
    {(yyval.global_decl) = ast_gdcl_typedef((yyvsp[0].typedef_dcl));}
#line 1717 "bison.c" /* yacc.c:1646  */
    break;

  case 6:
#line 225 "bison.y" /* yacc.c:1646  */
    {(yyval.global_decl) = ast_gdcl_enum((yyvsp[0].enum_dcl));}
#line 1723 "bison.c" /* yacc.c:1646  */
    break;

  case 7:
#line 226 "bison.y" /* yacc.c:1646  */
    {(yyval.global_decl) = ast_gdcl_class((yyvsp[0].class_dcl));}
#line 1729 "bison.c" /* yacc.c:1646  */
    break;

  case 8:
#line 227 "bison.y" /* yacc.c:1646  */
    {(yyval.global_decl) = ast_gdcl_union((yyvsp[0].union_dcl));}
#line 1735 "bison.c" /* yacc.c:1646  */
    break;

  case 9:
#line 228 "bison.y" /* yacc.c:1646  */
    {(yyval.global_decl) = ast_gdcl_gvar((yyvsp[0].global_var_declaration));}
#line 1741 "bison.c" /* yacc.c:1646  */
    break;

  case 10:
#line 229 "bison.y" /* yacc.c:1646  */
    {(yyval.global_decl) = ast_gdcl_func((yyvsp[0].func_dcl));}
#line 1747 "bison.c" /* yacc.c:1646  */
    break;

  case 11:
#line 231 "bison.y" /* yacc.c:1646  */
    {(yyval.typedef_dcl) = ast_typedef(id_make((yyvsp[-2].strval)), (yyvsp[-4].type), (yyvsp[-3].type), (yyvsp[-1].type));}
#line 1753 "bison.c" /* yacc.c:1646  */
    break;

  case 12:
#line 233 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = (yyvsp[0].type);}
#line 1759 "bison.c" /* yacc.c:1646  */
    break;

  case 13:
#line 234 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = type_id(id_make((yyvsp[0].strval)));}
#line 1765 "bison.c" /* yacc.c:1646  */
    break;

  case 14:
#line 236 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = type_basic(TYPE_char);}
#line 1771 "bison.c" /* yacc.c:1646  */
    break;

  case 15:
#line 237 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = type_basic(TYPE_int);}
#line 1777 "bison.c" /* yacc.c:1646  */
    break;

  case 16:
#line 238 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = type_basic(TYPE_float);}
#line 1783 "bison.c" /* yacc.c:1646  */
    break;

  case 17:
#line 239 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = type_basic(TYPE_str);}
#line 1789 "bison.c" /* yacc.c:1646  */
    break;

  case 18:
#line 240 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = type_basic(TYPE_void);}
#line 1795 "bison.c" /* yacc.c:1646  */
    break;

  case 19:
#line 242 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = type_list(NULL);}
#line 1801 "bison.c" /* yacc.c:1646  */
    break;

  case 20:
#line 243 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = NULL;}
#line 1807 "bison.c" /* yacc.c:1646  */
    break;

  case 21:
#line 245 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = ast_dims((yyvsp[-1].type), (yyvsp[0].type));}
#line 1813 "bison.c" /* yacc.c:1646  */
    break;

  case 22:
#line 246 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = NULL;}
#line 1819 "bison.c" /* yacc.c:1646  */
    break;

  case 23:
#line 248 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = type_array((yyvsp[-1].intval), NULL);}
#line 1825 "bison.c" /* yacc.c:1646  */
    break;

  case 24:
#line 249 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = type_array(-1, NULL);}
#line 1831 "bison.c" /* yacc.c:1646  */
    break;

  case 25:
#line 251 "bison.y" /* yacc.c:1646  */
    {(yyval.enum_dcl) = ast_enum_dcl(id_make((yyvsp[-2].strval)), (yyvsp[-1].list));}
#line 1837 "bison.c" /* yacc.c:1646  */
    break;

  case 26:
#line 253 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = (yyvsp[-1].list);}
#line 1843 "bison.c" /* yacc.c:1646  */
    break;

  case 27:
#line 255 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add((yyvsp[-3].list), ast_id(id_make((yyvsp[-1].strval)), (yyvsp[0].init_value)));}
#line 1849 "bison.c" /* yacc.c:1646  */
    break;

  case 28:
#line 256 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add(NULL, ast_id(id_make((yyvsp[-1].strval)), (yyvsp[0].init_value)));}
#line 1855 "bison.c" /* yacc.c:1646  */
    break;

  case 29:
#line 258 "bison.y" /* yacc.c:1646  */
    {(yyval.init_value) = (yyvsp[0].init_value);}
#line 1861 "bison.c" /* yacc.c:1646  */
    break;

  case 30:
#line 259 "bison.y" /* yacc.c:1646  */
    {(yyval.init_value) = ast_init_value_default();}
#line 1867 "bison.c" /* yacc.c:1646  */
    break;

  case 31:
#line 261 "bison.y" /* yacc.c:1646  */
    {(yyval.init_value) = ast_init_value_single((yyvsp[0].expr));}
#line 1873 "bison.c" /* yacc.c:1646  */
    break;

  case 32:
#line 262 "bison.y" /* yacc.c:1646  */
    {(yyval.init_value) = ast_init_value_multi((yyvsp[-1].list));}
#line 1879 "bison.c" /* yacc.c:1646  */
    break;

  case 33:
#line 264 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_new_binop_OR((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1885 "bison.c" /* yacc.c:1646  */
    break;

  case 34:
#line 265 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_new_binop_AND((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1891 "bison.c" /* yacc.c:1646  */
    break;

  case 35:
#line 266 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_new_binop_EQ((yyvsp[-2].expr), (yyvsp[0].expr));}
#line 1897 "bison.c" /* yacc.c:1646  */
    break;

  case 36:
#line 267 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_new_binop_REL((yyvsp[-2].expr), (yyvsp[-1].strval), (yyvsp[0].expr));}
#line 1903 "bison.c" /* yacc.c:1646  */
    break;

  case 37:
#line 268 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_new_binop_ADD((yyvsp[-2].expr), (yyvsp[-1].strval), (yyvsp[0].expr));}
#line 1909 "bison.c" /* yacc.c:1646  */
    break;

  case 38:
#line 269 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_new_binop_MUL((yyvsp[-2].expr), (yyvsp[-1].strval), (yyvsp[0].expr));}
#line 1915 "bison.c" /* yacc.c:1646  */
    break;

  case 39:
#line 270 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_unop((yyvsp[-1].strval), (yyvsp[0].expr));}
#line 1921 "bison.c" /* yacc.c:1646  */
    break;

  case 40:
#line 271 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_unop((yyvsp[-1].strval), (yyvsp[0].expr));}
#line 1927 "bison.c" /* yacc.c:1646  */
    break;

  case 41:
#line 272 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_unop((yyvsp[-1].strval), (yyvsp[0].expr));}
#line 1933 "bison.c" /* yacc.c:1646  */
    break;

  case 42:
#line 273 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_incdec((yyvsp[-1].strval), (yyvsp[0].variable));}
#line 1939 "bison.c" /* yacc.c:1646  */
    break;

  case 43:
#line 274 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_incdec((yyvsp[0].strval), (yyvsp[-1].variable));}
#line 1945 "bison.c" /* yacc.c:1646  */
    break;

  case 44:
#line 275 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_variable((yyvsp[0].variable));}
#line 1951 "bison.c" /* yacc.c:1646  */
    break;

  case 45:
#line 276 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_func((yyvsp[-3].variable), (yyvsp[-1].exprlist));}
#line 1957 "bison.c" /* yacc.c:1646  */
    break;

  case 46:
#line 277 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_length((yyvsp[-1].general_expr));}
#line 1963 "bison.c" /* yacc.c:1646  */
    break;

  case 47:
#line 278 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_new((yyvsp[-1].general_expr));}
#line 1969 "bison.c" /* yacc.c:1646  */
    break;

  case 48:
#line 279 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_constant((yyvsp[0].constant));}
#line 1975 "bison.c" /* yacc.c:1646  */
    break;

  case 49:
#line 280 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_general_expr((yyvsp[-1].general_expr));}
#line 1981 "bison.c" /* yacc.c:1646  */
    break;

  case 50:
#line 281 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_standardtype((yyvsp[-1].type));}
#line 1987 "bison.c" /* yacc.c:1646  */
    break;

  case 51:
#line 282 "bison.y" /* yacc.c:1646  */
    {(yyval.expr) = ast_expr_listexpr((yyvsp[0].exprlist));}
#line 1993 "bison.c" /* yacc.c:1646  */
    break;

  case 52:
#line 284 "bison.y" /* yacc.c:1646  */
    {(yyval.variable) = ast_variable_list((yyvsp[-3].variable), (yyvsp[-1].general_expr));}
#line 1999 "bison.c" /* yacc.c:1646  */
    break;

  case 53:
#line 285 "bison.y" /* yacc.c:1646  */
    {(yyval.variable) = ast_variable_nested((yyvsp[-2].variable), id_make((yyvsp[0].strval)));}
#line 2005 "bison.c" /* yacc.c:1646  */
    break;

  case 54:
#line 286 "bison.y" /* yacc.c:1646  */
    {(yyval.variable) = ast_variable_listfunc((yyvsp[-1].general_expr));}
#line 2011 "bison.c" /* yacc.c:1646  */
    break;

  case 55:
#line 287 "bison.y" /* yacc.c:1646  */
    {(yyval.variable) = ast_variable_definition((yyvsp[-1].intval), id_make((yyvsp[0].strval)));}
#line 2017 "bison.c" /* yacc.c:1646  */
    break;

  case 56:
#line 288 "bison.y" /* yacc.c:1646  */
    {(yyval.variable) = ast_variable_this();}
#line 2023 "bison.c" /* yacc.c:1646  */
    break;

  case 57:
#line 291 "bison.y" /* yacc.c:1646  */
    {(yyval.general_expr) = ast_gexpr_gexpr((yyvsp[-2].general_expr), (yyvsp[0].general_expr));}
#line 2029 "bison.c" /* yacc.c:1646  */
    break;

  case 58:
#line 292 "bison.y" /* yacc.c:1646  */
    {(yyval.general_expr) = ast_gexpr_assignment((yyvsp[0].assignment));}
#line 2035 "bison.c" /* yacc.c:1646  */
    break;

  case 59:
#line 294 "bison.y" /* yacc.c:1646  */
    {(yyval.assignment) = ast_assignment_var((yyvsp[-2].variable), (yyvsp[0].assignment));}
#line 2041 "bison.c" /* yacc.c:1646  */
    break;

  case 60:
#line 295 "bison.y" /* yacc.c:1646  */
    {(yyval.assignment) = ast_assignment_expr((yyvsp[0].expr));}
#line 2047 "bison.c" /* yacc.c:1646  */
    break;

  case 61:
#line 297 "bison.y" /* yacc.c:1646  */
    {(yyval.exprlist) = ast_exprlist_general((yyvsp[0].general_expr));}
#line 2053 "bison.c" /* yacc.c:1646  */
    break;

  case 62:
#line 298 "bison.y" /* yacc.c:1646  */
    {(yyval.exprlist) = ast_exprlist_general(NULL);}
#line 2059 "bison.c" /* yacc.c:1646  */
    break;

  case 63:
#line 300 "bison.y" /* yacc.c:1646  */
    {(yyval.constant) = ast_constant_cconst((yyvsp[0].charval));}
#line 2065 "bison.c" /* yacc.c:1646  */
    break;

  case 64:
#line 301 "bison.y" /* yacc.c:1646  */
    {(yyval.constant) = ast_constant_iconst((yyvsp[0].intval));}
#line 2071 "bison.c" /* yacc.c:1646  */
    break;

  case 65:
#line 302 "bison.y" /* yacc.c:1646  */
    {(yyval.constant) = ast_constant_fconst((yyvsp[0].floatval));}
#line 2077 "bison.c" /* yacc.c:1646  */
    break;

  case 66:
#line 303 "bison.y" /* yacc.c:1646  */
    {(yyval.constant) = ast_constant_sconst((yyvsp[0].strval));}
#line 2083 "bison.c" /* yacc.c:1646  */
    break;

  case 67:
#line 305 "bison.y" /* yacc.c:1646  */
    {(yyval.exprlist) = (yyvsp[-1].exprlist);}
#line 2089 "bison.c" /* yacc.c:1646  */
    break;

  case 68:
#line 307 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add((yyvsp[-2].list), (void * ) (yyvsp[0].init_value));}
#line 2095 "bison.c" /* yacc.c:1646  */
    break;

  case 69:
#line 308 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add(NULL, (yyvsp[0].init_value));}
#line 2101 "bison.c" /* yacc.c:1646  */
    break;

  case 70:
#line 310 "bison.y" /* yacc.c:1646  */
    {(yyval.class_dcl) = ast_class_dcl(id_make((yyvsp[-2].strval)), (yyvsp[-1].class_body));}
#line 2107 "bison.c" /* yacc.c:1646  */
    break;

  case 71:
#line 312 "bison.y" /* yacc.c:1646  */
    {(yyval.class_body) = ast_class_body((yyvsp[-3].identifier), (yyvsp[-1].list));}
#line 2113 "bison.c" /* yacc.c:1646  */
    break;

  case 72:
#line 314 "bison.y" /* yacc.c:1646  */
    {(yyval.identifier) = id_make((yyvsp[0].strval));}
#line 2119 "bison.c" /* yacc.c:1646  */
    break;

  case 73:
#line 315 "bison.y" /* yacc.c:1646  */
    {(yyval.identifier) = NULL;}
#line 2125 "bison.c" /* yacc.c:1646  */
    break;

  case 74:
#line 317 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add((yyvsp[-2].list), (void *) ast_members_method((yyvsp[-1].access), (yyvsp[0].member_or_method)));}
#line 2131 "bison.c" /* yacc.c:1646  */
    break;

  case 75:
#line 318 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add(NULL, (void *) ast_members_method((yyvsp[-1].access), (yyvsp[0].member_or_method)));}
#line 2137 "bison.c" /* yacc.c:1646  */
    break;

  case 76:
#line 320 "bison.y" /* yacc.c:1646  */
    {(yyval.access)=ACCESS_PRIVATE;}
#line 2143 "bison.c" /* yacc.c:1646  */
    break;

  case 77:
#line 321 "bison.y" /* yacc.c:1646  */
    {(yyval.access)=ACCESS_PROTECTED;}
#line 2149 "bison.c" /* yacc.c:1646  */
    break;

  case 78:
#line 322 "bison.y" /* yacc.c:1646  */
    {(yyval.access)=ACCESS_PUBLIC;}
#line 2155 "bison.c" /* yacc.c:1646  */
    break;

  case 79:
#line 323 "bison.y" /* yacc.c:1646  */
    {(yyval.access)=ACCESS_DEFAULT;}
#line 2161 "bison.c" /* yacc.c:1646  */
    break;

  case 80:
#line 325 "bison.y" /* yacc.c:1646  */
    {(yyval.member_or_method) = ast_mom_member((yyvsp[0].member));}
#line 2167 "bison.c" /* yacc.c:1646  */
    break;

  case 81:
#line 326 "bison.y" /* yacc.c:1646  */
    {(yyval.member_or_method) = ast_mom_method((yyvsp[0].short_func_dcl));}
#line 2173 "bison.c" /* yacc.c:1646  */
    break;

  case 82:
#line 328 "bison.y" /* yacc.c:1646  */
    {(yyval.member) = ast_member_variable((yyvsp[0].var_declaration));}
#line 2179 "bison.c" /* yacc.c:1646  */
    break;

  case 83:
#line 329 "bison.y" /* yacc.c:1646  */
    {(yyval.member) = ast_member_anon_union((yyvsp[0].list));}
#line 2185 "bison.c" /* yacc.c:1646  */
    break;

  case 84:
#line 331 "bison.y" /* yacc.c:1646  */
    {(yyval.var_declaration) = ast_var_declaration((yyvsp[-2].type), (yyvsp[-1].list));}
#line 2191 "bison.c" /* yacc.c:1646  */
    break;

  case 85:
#line 333 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add((yyvsp[-2].list), (void *) (yyvsp[0].variabledef));}
#line 2197 "bison.c" /* yacc.c:1646  */
    break;

  case 86:
#line 334 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add(NULL, (void *) (yyvsp[0].variabledef));}
#line 2203 "bison.c" /* yacc.c:1646  */
    break;

  case 87:
#line 336 "bison.y" /* yacc.c:1646  */
    {(yyval.variabledef) = ast_variabledef(id_make((yyvsp[-1].strval)), (yyvsp[-2].type), (yyvsp[0].type));}
#line 2209 "bison.c" /* yacc.c:1646  */
    break;

  case 88:
#line 338 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = (yyvsp[-1].list);}
#line 2215 "bison.c" /* yacc.c:1646  */
    break;

  case 89:
#line 340 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = (yyvsp[-1].list);}
#line 2221 "bison.c" /* yacc.c:1646  */
    break;

  case 90:
#line 342 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add((yyvsp[-1].list), (void *) (yyvsp[0].var_declaration));}
#line 2227 "bison.c" /* yacc.c:1646  */
    break;

  case 91:
#line 343 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add(NULL, (void *) (yyvsp[0].var_declaration));}
#line 2233 "bison.c" /* yacc.c:1646  */
    break;

  case 92:
#line 345 "bison.y" /* yacc.c:1646  */
    {(yyval.var_declaration) = (yyvsp[0].var_declaration);}
#line 2239 "bison.c" /* yacc.c:1646  */
    break;

  case 93:
#line 347 "bison.y" /* yacc.c:1646  */
    {(yyval.short_func_dcl) = (yyvsp[0].short_func_dcl);}
#line 2245 "bison.c" /* yacc.c:1646  */
    break;

  case 94:
#line 349 "bison.y" /* yacc.c:1646  */
    {(yyval.short_func_dcl) = (yyvsp[-1].short_func_dcl);}
#line 2251 "bison.c" /* yacc.c:1646  */
    break;

  case 95:
#line 350 "bison.y" /* yacc.c:1646  */
    {(yyval.short_func_dcl) = ast_short_func_dcl((yyvsp[-1].func_header_start), NULL);}
#line 2257 "bison.c" /* yacc.c:1646  */
    break;

  case 96:
#line 352 "bison.y" /* yacc.c:1646  */
    {(yyval.short_func_dcl) = ast_short_func_dcl((yyvsp[-3].func_header_start), (yyvsp[-1].list));}
#line 2263 "bison.c" /* yacc.c:1646  */
    break;

  case 97:
#line 354 "bison.y" /* yacc.c:1646  */
    {(yyval.func_header_start) = ast_func_header_start(id_make((yyvsp[0].strval)), (yyvsp[-2].type), (yyvsp[-1].type));}
#line 2269 "bison.c" /* yacc.c:1646  */
    break;

  case 98:
#line 356 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add((yyvsp[-3].list), (void *) get_parameter_type((yyvsp[-1].type), (yyvsp[0].type)));}
#line 2275 "bison.c" /* yacc.c:1646  */
    break;

  case 99:
#line 357 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add(NULL, (void *) get_parameter_type((yyvsp[-1].type), (yyvsp[0].type)));}
#line 2281 "bison.c" /* yacc.c:1646  */
    break;

  case 100:
#line 359 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = type_ref(NULL);}
#line 2287 "bison.c" /* yacc.c:1646  */
    break;

  case 101:
#line 360 "bison.y" /* yacc.c:1646  */
    {(yyval.type) = (yyvsp[-1].type) ? (yyvsp[-1].type) : (yyvsp[0].type);}
#line 2293 "bison.c" /* yacc.c:1646  */
    break;

  case 102:
#line 362 "bison.y" /* yacc.c:1646  */
    {(yyval.func_header_start) = (yyvsp[-2].func_header_start);}
#line 2299 "bison.c" /* yacc.c:1646  */
    break;

  case 103:
#line 364 "bison.y" /* yacc.c:1646  */
    {(yyval.union_dcl) = ast_union_dcl(id_make((yyvsp[-2].strval)), (yyvsp[-1].list));}
#line 2305 "bison.c" /* yacc.c:1646  */
    break;

  case 104:
#line 366 "bison.y" /* yacc.c:1646  */
    {(yyval.global_var_declaration) = ast_global_var_declaration((yyvsp[-2].type), (yyvsp[-1].list));}
#line 2311 "bison.c" /* yacc.c:1646  */
    break;

  case 105:
#line 368 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add((yyvsp[-2].list), (void *) (yyvsp[0].init_variabledef));}
#line 2317 "bison.c" /* yacc.c:1646  */
    break;

  case 106:
#line 369 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add(NULL, (void *) (yyvsp[0].init_variabledef));}
#line 2323 "bison.c" /* yacc.c:1646  */
    break;

  case 107:
#line 371 "bison.y" /* yacc.c:1646  */
    {(yyval.init_variabledef) = ast_init_variabledef((yyvsp[-1].variabledef), (yyvsp[0].init_value));}
#line 2329 "bison.c" /* yacc.c:1646  */
    break;

  case 108:
#line 373 "bison.y" /* yacc.c:1646  */
    {(yyval.func_dcl) = ast_func_dcl_short((yyvsp[0].short_func_dcl));}
#line 2335 "bison.c" /* yacc.c:1646  */
    break;

  case 109:
#line 374 "bison.y" /* yacc.c:1646  */
    {(yyval.func_dcl) = ast_func_dcl_full((yyvsp[0].full_func_dcl));}
#line 2341 "bison.c" /* yacc.c:1646  */
    break;

  case 110:
#line 376 "bison.y" /* yacc.c:1646  */
    {(yyval.full_func_dcl) = ast_full_func_dcl_full_par((yyvsp[-3].full_par_func_header), (yyvsp[-1].dcl_stmt));}
#line 2347 "bison.c" /* yacc.c:1646  */
    break;

  case 111:
#line 377 "bison.y" /* yacc.c:1646  */
    {(yyval.full_func_dcl) = ast_full_func_dcl_nopar_class((yyvsp[-3].class_func_header_start), (yyvsp[-1].dcl_stmt));}
#line 2353 "bison.c" /* yacc.c:1646  */
    break;

  case 112:
#line 378 "bison.y" /* yacc.c:1646  */
    {(yyval.full_func_dcl) = ast_full_func_dcl_nopar((yyvsp[-3].func_header_start), (yyvsp[-1].dcl_stmt));}
#line 2359 "bison.c" /* yacc.c:1646  */
    break;

  case 113:
#line 380 "bison.y" /* yacc.c:1646  */
    {(yyval.full_par_func_header) = ast_full_par_func_header_class((yyvsp[-3].class_func_header_start), (yyvsp[-1].list));}
#line 2365 "bison.c" /* yacc.c:1646  */
    break;

  case 114:
#line 381 "bison.y" /* yacc.c:1646  */
    {(yyval.full_par_func_header) = ast_full_par_func_header_noclass((yyvsp[-3].func_header_start), (yyvsp[-1].list));}
#line 2371 "bison.c" /* yacc.c:1646  */
    break;

  case 115:
#line 383 "bison.y" /* yacc.c:1646  */
    {(yyval.class_func_header_start) = ast_class_func_header_start(id_make((yyvsp[0].strval)), (yyvsp[-1].identifier), (yyvsp[-3].type), (yyvsp[-2].type));}
#line 2377 "bison.c" /* yacc.c:1646  */
    break;

  case 116:
#line 385 "bison.y" /* yacc.c:1646  */
    {(yyval.identifier) = id_make((yyvsp[-1].strval));}
#line 2383 "bison.c" /* yacc.c:1646  */
    break;

  case 117:
#line 387 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add((yyvsp[-3].list), (void *) ast_parameter((yyvsp[-1].type), (yyvsp[0].passvar)));}
#line 2389 "bison.c" /* yacc.c:1646  */
    break;

  case 118:
#line 388 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add(NULL, (void *) ast_parameter((yyvsp[-1].type), (yyvsp[0].passvar)));}
#line 2395 "bison.c" /* yacc.c:1646  */
    break;

  case 119:
#line 390 "bison.y" /* yacc.c:1646  */
    {(yyval.passvar) = ast_passvar_variable((yyvsp[0].variabledef));}
#line 2401 "bison.c" /* yacc.c:1646  */
    break;

  case 120:
#line 391 "bison.y" /* yacc.c:1646  */
    {(yyval.passvar) = ast_passvar_ref(id_make((yyvsp[0].strval)));}
#line 2407 "bison.c" /* yacc.c:1646  */
    break;

  case 121:
#line 393 "bison.y" /* yacc.c:1646  */
    {(yyval.class_func_header_start) = (yyvsp[-2].class_func_header_start);}
#line 2413 "bison.c" /* yacc.c:1646  */
    break;

  case 122:
#line 395 "bison.y" /* yacc.c:1646  */
    {(yyval.dcl_stmt) = ast_dcl_stmt_dcls_stmts((yyvsp[-1].list), (yyvsp[0].list));}
#line 2419 "bison.c" /* yacc.c:1646  */
    break;

  case 123:
#line 396 "bison.y" /* yacc.c:1646  */
    {(yyval.dcl_stmt) = ast_dcl_stmt_dcls((yyvsp[0].list));}
#line 2425 "bison.c" /* yacc.c:1646  */
    break;

  case 124:
#line 397 "bison.y" /* yacc.c:1646  */
    {(yyval.dcl_stmt) = ast_dcl_stmt_stmts((yyvsp[0].list));}
#line 2431 "bison.c" /* yacc.c:1646  */
    break;

  case 125:
#line 398 "bison.y" /* yacc.c:1646  */
    {(yyval.dcl_stmt) = ast_dcl_stmt_empty();}
#line 2437 "bison.c" /* yacc.c:1646  */
    break;

  case 126:
#line 400 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add((yyvsp[-4].list), (void *) ast_declaration((yyvsp[-2].type), (yyvsp[-3].intval), (yyvsp[-1].list)));}
#line 2443 "bison.c" /* yacc.c:1646  */
    break;

  case 127:
#line 401 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add(NULL, (void *) ast_declaration((yyvsp[-2].type), (yyvsp[-3].intval), (yyvsp[-1].list)));}
#line 2449 "bison.c" /* yacc.c:1646  */
    break;

  case 128:
#line 403 "bison.y" /* yacc.c:1646  */
    {(yyval.intval)=1;}
#line 2455 "bison.c" /* yacc.c:1646  */
    break;

  case 129:
#line 404 "bison.y" /* yacc.c:1646  */
    {(yyval.intval)=0;}
#line 2461 "bison.c" /* yacc.c:1646  */
    break;

  case 130:
#line 406 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add((yyvsp[-1].list), (void *)(yyvsp[0].stmt));}
#line 2467 "bison.c" /* yacc.c:1646  */
    break;

  case 131:
#line 407 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add(NULL, (void *)(yyvsp[0].stmt));}
#line 2473 "bison.c" /* yacc.c:1646  */
    break;

  case 132:
#line 409 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].stmt);}
#line 2479 "bison.c" /* yacc.c:1646  */
    break;

  case 133:
#line 410 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].stmt);}
#line 2485 "bison.c" /* yacc.c:1646  */
    break;

  case 134:
#line 411 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].stmt);}
#line 2491 "bison.c" /* yacc.c:1646  */
    break;

  case 135:
#line 412 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].stmt);}
#line 2497 "bison.c" /* yacc.c:1646  */
    break;

  case 136:
#line 413 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].stmt);}
#line 2503 "bison.c" /* yacc.c:1646  */
    break;

  case 137:
#line 414 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].stmt);}
#line 2509 "bison.c" /* yacc.c:1646  */
    break;

  case 138:
#line 415 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].stmt);}
#line 2515 "bison.c" /* yacc.c:1646  */
    break;

  case 139:
#line 416 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].stmt);}
#line 2521 "bison.c" /* yacc.c:1646  */
    break;

  case 140:
#line 417 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = ast_stmt_basic(STMT_CONTINUE);}
#line 2527 "bison.c" /* yacc.c:1646  */
    break;

  case 141:
#line 418 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = ast_stmt_basic(STMT_BREAK);}
#line 2533 "bison.c" /* yacc.c:1646  */
    break;

  case 142:
#line 419 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = ast_stmt_basic(STMT_SEMI);}
#line 2539 "bison.c" /* yacc.c:1646  */
    break;

  case 143:
#line 421 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = ast_expr_stmt((yyvsp[-1].general_expr));}
#line 2545 "bison.c" /* yacc.c:1646  */
    break;

  case 144:
#line 425 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = ast_if_stmt((yyvsp[-3].general_expr), (yyvsp[-1].stmt), (yyvsp[0].stmt));}
#line 2551 "bison.c" /* yacc.c:1646  */
    break;

  case 145:
#line 428 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = (yyvsp[0].stmt);}
#line 2557 "bison.c" /* yacc.c:1646  */
    break;

  case 146:
#line 429 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = NULL;}
#line 2563 "bison.c" /* yacc.c:1646  */
    break;

  case 147:
#line 432 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = ast_while_stmt((yyvsp[-2].general_expr), (yyvsp[0].stmt));}
#line 2569 "bison.c" /* yacc.c:1646  */
    break;

  case 148:
#line 435 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = ast_for_stmt((yyvsp[-6].general_expr), (yyvsp[-4].general_expr), (yyvsp[-2].general_expr), (yyvsp[0].stmt));}
#line 2575 "bison.c" /* yacc.c:1646  */
    break;

  case 149:
#line 437 "bison.y" /* yacc.c:1646  */
    {(yyval.general_expr) = (yyvsp[0].general_expr);}
#line 2581 "bison.c" /* yacc.c:1646  */
    break;

  case 150:
#line 438 "bison.y" /* yacc.c:1646  */
    {(yyval.general_expr) = NULL;}
#line 2587 "bison.c" /* yacc.c:1646  */
    break;

  case 151:
#line 441 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = ast_switch_stmt((yyvsp[-2].general_expr), (yyvsp[0].switch_tail));}
#line 2593 "bison.c" /* yacc.c:1646  */
    break;

  case 152:
#line 443 "bison.y" /* yacc.c:1646  */
    {(yyval.switch_tail) = ast_switch_tail_decl((yyvsp[-1].decl_cases));}
#line 2599 "bison.c" /* yacc.c:1646  */
    break;

  case 153:
#line 444 "bison.y" /* yacc.c:1646  */
    {(yyval.switch_tail) = ast_switch_tail_single((yyvsp[0].casestmt));}
#line 2605 "bison.c" /* yacc.c:1646  */
    break;

  case 154:
#line 446 "bison.y" /* yacc.c:1646  */
    {(yyval.decl_cases) = ast_decl_cases_both((yyvsp[-1].list), (yyvsp[0].list));}
#line 2611 "bison.c" /* yacc.c:1646  */
    break;

  case 155:
#line 447 "bison.y" /* yacc.c:1646  */
    {(yyval.decl_cases) = ast_decl_cases_single(DC_DECLARATION_ONLY, (yyvsp[0].list));}
#line 2617 "bison.c" /* yacc.c:1646  */
    break;

  case 156:
#line 448 "bison.y" /* yacc.c:1646  */
    {(yyval.decl_cases) = ast_decl_cases_single(DC_CASE_ONLY, (yyvsp[0].list));}
#line 2623 "bison.c" /* yacc.c:1646  */
    break;

  case 157:
#line 449 "bison.y" /* yacc.c:1646  */
    {(yyval.decl_cases) = ast_decl_cases_empty();}
#line 2629 "bison.c" /* yacc.c:1646  */
    break;

  case 158:
#line 451 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add((yyvsp[-1].list), (void *) (yyvsp[0].casestmt));}
#line 2635 "bison.c" /* yacc.c:1646  */
    break;

  case 159:
#line 452 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add(NULL, (void *) (yyvsp[0].casestmt));}
#line 2641 "bison.c" /* yacc.c:1646  */
    break;

  case 160:
#line 454 "bison.y" /* yacc.c:1646  */
    {(yyval.casestmt) = ast_casestmt_nextcase((yyvsp[-2].constant), (yyvsp[0].casestmt));}
#line 2647 "bison.c" /* yacc.c:1646  */
    break;

  case 161:
#line 455 "bison.y" /* yacc.c:1646  */
    {(yyval.casestmt) = ast_casestmt_multi((yyvsp[-2].constant), (yyvsp[0].list));}
#line 2653 "bison.c" /* yacc.c:1646  */
    break;

  case 162:
#line 456 "bison.y" /* yacc.c:1646  */
    {(yyval.casestmt) = ast_casestmt_default((yyvsp[0].list));}
#line 2659 "bison.c" /* yacc.c:1646  */
    break;

  case 163:
#line 458 "bison.y" /* yacc.c:1646  */
    {(yyval.casestmt) = ast_casestmt_nextcase((yyvsp[-2].constant), (yyvsp[0].casestmt));}
#line 2665 "bison.c" /* yacc.c:1646  */
    break;

  case 164:
#line 459 "bison.y" /* yacc.c:1646  */
    {(yyval.casestmt) = ast_casestmt_single((yyvsp[-2].constant), (yyvsp[0].stmt));}
#line 2671 "bison.c" /* yacc.c:1646  */
    break;

  case 165:
#line 461 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = ast_return_stmt((yyvsp[-1].general_expr));}
#line 2677 "bison.c" /* yacc.c:1646  */
    break;

  case 166:
#line 463 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = ast_io_stmt(STMT_INPUT, (yyvsp[-1].list));}
#line 2683 "bison.c" /* yacc.c:1646  */
    break;

  case 167:
#line 464 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = ast_io_stmt(STMT_OUTPUT, (yyvsp[-1].list));}
#line 2689 "bison.c" /* yacc.c:1646  */
    break;

  case 168:
#line 466 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add((yyvsp[-2].list), (void *) (yyvsp[0].variable));}
#line 2695 "bison.c" /* yacc.c:1646  */
    break;

  case 169:
#line 467 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add(NULL, (void *) (yyvsp[0].variable));}
#line 2701 "bison.c" /* yacc.c:1646  */
    break;

  case 170:
#line 469 "bison.y" /* yacc.c:1646  */
    {(yyval.variable) = (yyvsp[0].variable);}
#line 2707 "bison.c" /* yacc.c:1646  */
    break;

  case 171:
#line 471 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add((yyvsp[-2].list), (void *) (yyvsp[0].general_expr));}
#line 2713 "bison.c" /* yacc.c:1646  */
    break;

  case 172:
#line 472 "bison.y" /* yacc.c:1646  */
    {(yyval.list) = list_add(NULL, (void *) (yyvsp[0].general_expr));}
#line 2719 "bison.c" /* yacc.c:1646  */
    break;

  case 173:
#line 474 "bison.y" /* yacc.c:1646  */
    {(yyval.general_expr) = (yyvsp[0].general_expr);}
#line 2725 "bison.c" /* yacc.c:1646  */
    break;

  case 174:
#line 476 "bison.y" /* yacc.c:1646  */
    {(yyval.stmt) = ast_comp_stmt((yyvsp[-1].dcl_stmt));}
#line 2731 "bison.c" /* yacc.c:1646  */
    break;

  case 175:
#line 478 "bison.y" /* yacc.c:1646  */
    {(yyval.dcl_stmt) = (yyvsp[-1].dcl_stmt);}
#line 2737 "bison.c" /* yacc.c:1646  */
    break;

  case 176:
#line 480 "bison.y" /* yacc.c:1646  */
    {}
#line 2743 "bison.c" /* yacc.c:1646  */
    break;


#line 2747 "bison.c" /* yacc.c:1646  */
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
#line 482 "bison.y" /* yacc.c:1906  */
