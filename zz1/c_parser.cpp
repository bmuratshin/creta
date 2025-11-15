/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 9 "c_gramm.y"

#include <stdio.h>
#include "c_driver.h"
#include "c_tree.h"

typedef void* yyscan_t;

void yyerror (yyscan_t yyscanner, void *ptr, char const *msg);

#line 81 "c_parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "c_parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_STRING_LITERAL = 4,             /* STRING_LITERAL  */
  YYSYMBOL_I_CONSTANT = 5,                 /* I_CONSTANT  */
  YYSYMBOL_F_CONSTANT = 6,                 /* F_CONSTANT  */
  YYSYMBOL_FUNC_NAME = 7,                  /* FUNC_NAME  */
  YYSYMBOL_SIZEOF = 8,                     /* SIZEOF  */
  YYSYMBOL_STRUCT = 9,                     /* STRUCT  */
  YYSYMBOL_UNION = 10,                     /* UNION  */
  YYSYMBOL_PTR_OP = 11,                    /* PTR_OP  */
  YYSYMBOL_INC_OP = 12,                    /* INC_OP  */
  YYSYMBOL_DEC_OP = 13,                    /* DEC_OP  */
  YYSYMBOL_LEFT_OP = 14,                   /* LEFT_OP  */
  YYSYMBOL_RIGHT_OP = 15,                  /* RIGHT_OP  */
  YYSYMBOL_LE_OP = 16,                     /* LE_OP  */
  YYSYMBOL_GE_OP = 17,                     /* GE_OP  */
  YYSYMBOL_EQ_OP = 18,                     /* EQ_OP  */
  YYSYMBOL_NE_OP = 19,                     /* NE_OP  */
  YYSYMBOL_AND_OP = 20,                    /* AND_OP  */
  YYSYMBOL_OR_OP = 21,                     /* OR_OP  */
  YYSYMBOL_MUL_ASSIGN = 22,                /* MUL_ASSIGN  */
  YYSYMBOL_DIV_ASSIGN = 23,                /* DIV_ASSIGN  */
  YYSYMBOL_MOD_ASSIGN = 24,                /* MOD_ASSIGN  */
  YYSYMBOL_ADD_ASSIGN = 25,                /* ADD_ASSIGN  */
  YYSYMBOL_SUB_ASSIGN = 26,                /* SUB_ASSIGN  */
  YYSYMBOL_LEFT_ASSIGN = 27,               /* LEFT_ASSIGN  */
  YYSYMBOL_RIGHT_ASSIGN = 28,              /* RIGHT_ASSIGN  */
  YYSYMBOL_AND_ASSIGN = 29,                /* AND_ASSIGN  */
  YYSYMBOL_XOR_ASSIGN = 30,                /* XOR_ASSIGN  */
  YYSYMBOL_OR_ASSIGN = 31,                 /* OR_ASSIGN  */
  YYSYMBOL_JUST_ASSIGN = 32,               /* JUST_ASSIGN  */
  YYSYMBOL_TYPEDEF_NAME = 33,              /* TYPEDEF_NAME  */
  YYSYMBOL_ENUMERATION_CONSTANT = 34,      /* ENUMERATION_CONSTANT  */
  YYSYMBOL_TYPEDEF = 35,                   /* TYPEDEF  */
  YYSYMBOL_EXTERN = 36,                    /* EXTERN  */
  YYSYMBOL_STATIC = 37,                    /* STATIC  */
  YYSYMBOL_AUTO = 38,                      /* AUTO  */
  YYSYMBOL_REGISTER = 39,                  /* REGISTER  */
  YYSYMBOL_INLINE = 40,                    /* INLINE  */
  YYSYMBOL_CONST = 41,                     /* CONST  */
  YYSYMBOL_RESTRICT = 42,                  /* RESTRICT  */
  YYSYMBOL_VOLATILE = 43,                  /* VOLATILE  */
  YYSYMBOL_BOOL = 44,                      /* BOOL  */
  YYSYMBOL_CHAR = 45,                      /* CHAR  */
  YYSYMBOL_SHORT = 46,                     /* SHORT  */
  YYSYMBOL_INT = 47,                       /* INT  */
  YYSYMBOL_LONG = 48,                      /* LONG  */
  YYSYMBOL_SIGNED = 49,                    /* SIGNED  */
  YYSYMBOL_UNSIGNED = 50,                  /* UNSIGNED  */
  YYSYMBOL_FLOAT = 51,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 52,                    /* DOUBLE  */
  YYSYMBOL_VOID = 53,                      /* VOID  */
  YYSYMBOL_COMPLEX = 54,                   /* COMPLEX  */
  YYSYMBOL_IMAGINARY = 55,                 /* IMAGINARY  */
  YYSYMBOL_ENUM = 56,                      /* ENUM  */
  YYSYMBOL_ELLIPSIS = 57,                  /* ELLIPSIS  */
  YYSYMBOL_CASE = 58,                      /* CASE  */
  YYSYMBOL_DEFAULT = 59,                   /* DEFAULT  */
  YYSYMBOL_IF = 60,                        /* IF  */
  YYSYMBOL_ELSE = 61,                      /* ELSE  */
  YYSYMBOL_SWITCH = 62,                    /* SWITCH  */
  YYSYMBOL_WHILE = 63,                     /* WHILE  */
  YYSYMBOL_DO = 64,                        /* DO  */
  YYSYMBOL_FOR = 65,                       /* FOR  */
  YYSYMBOL_GOTO = 66,                      /* GOTO  */
  YYSYMBOL_CONTINUE = 67,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 68,                     /* BREAK  */
  YYSYMBOL_RETURN = 69,                    /* RETURN  */
  YYSYMBOL_ALIGNAS = 70,                   /* ALIGNAS  */
  YYSYMBOL_ALIGNOF = 71,                   /* ALIGNOF  */
  YYSYMBOL_ATOMIC = 72,                    /* ATOMIC  */
  YYSYMBOL_GENERIC = 73,                   /* GENERIC  */
  YYSYMBOL_NORETURN = 74,                  /* NORETURN  */
  YYSYMBOL_STATIC_ASSERT = 75,             /* STATIC_ASSERT  */
  YYSYMBOL_THREAD_LOCAL = 76,              /* THREAD_LOCAL  */
  YYSYMBOL_77_ = 77,                       /* '('  */
  YYSYMBOL_78_ = 78,                       /* ')'  */
  YYSYMBOL_79_ = 79,                       /* ','  */
  YYSYMBOL_80_ = 80,                       /* ':'  */
  YYSYMBOL_81_ = 81,                       /* '['  */
  YYSYMBOL_82_ = 82,                       /* ']'  */
  YYSYMBOL_83_ = 83,                       /* '.'  */
  YYSYMBOL_84_ = 84,                       /* '{'  */
  YYSYMBOL_85_ = 85,                       /* '}'  */
  YYSYMBOL_86_ = 86,                       /* '&'  */
  YYSYMBOL_87_ = 87,                       /* '*'  */
  YYSYMBOL_88_ = 88,                       /* '+'  */
  YYSYMBOL_89_ = 89,                       /* '-'  */
  YYSYMBOL_90_ = 90,                       /* '~'  */
  YYSYMBOL_91_ = 91,                       /* '!'  */
  YYSYMBOL_92_ = 92,                       /* '/'  */
  YYSYMBOL_93_ = 93,                       /* '%'  */
  YYSYMBOL_94_ = 94,                       /* '<'  */
  YYSYMBOL_95_ = 95,                       /* '>'  */
  YYSYMBOL_96_ = 96,                       /* '^'  */
  YYSYMBOL_97_ = 97,                       /* '|'  */
  YYSYMBOL_98_ = 98,                       /* '?'  */
  YYSYMBOL_99_ = 99,                       /* ';'  */
  YYSYMBOL_YYACCEPT = 100,                 /* $accept  */
  YYSYMBOL_primary_expression = 101,       /* primary_expression  */
  YYSYMBOL_constant = 102,                 /* constant  */
  YYSYMBOL_some_identifier = 103,          /* some_identifier  */
  YYSYMBOL_enumeration_constant = 104,     /* enumeration_constant  */
  YYSYMBOL_string = 105,                   /* string  */
  YYSYMBOL_generic_selection = 106,        /* generic_selection  */
  YYSYMBOL_generic_assoc_list = 107,       /* generic_assoc_list  */
  YYSYMBOL_generic_association = 108,      /* generic_association  */
  YYSYMBOL_postfix_expression = 109,       /* postfix_expression  */
  YYSYMBOL_argument_expression_list = 110, /* argument_expression_list  */
  YYSYMBOL_unary_expression = 111,         /* unary_expression  */
  YYSYMBOL_unary_operator = 112,           /* unary_operator  */
  YYSYMBOL_cast_expression = 113,          /* cast_expression  */
  YYSYMBOL_multiplicative_expression = 114, /* multiplicative_expression  */
  YYSYMBOL_additive_expression = 115,      /* additive_expression  */
  YYSYMBOL_shift_expression = 116,         /* shift_expression  */
  YYSYMBOL_relational_expression = 117,    /* relational_expression  */
  YYSYMBOL_equality_expression = 118,      /* equality_expression  */
  YYSYMBOL_and_expression = 119,           /* and_expression  */
  YYSYMBOL_exclusive_or_expression = 120,  /* exclusive_or_expression  */
  YYSYMBOL_inclusive_or_expression = 121,  /* inclusive_or_expression  */
  YYSYMBOL_logical_and_expression = 122,   /* logical_and_expression  */
  YYSYMBOL_logical_or_expression = 123,    /* logical_or_expression  */
  YYSYMBOL_conditional_expression = 124,   /* conditional_expression  */
  YYSYMBOL_assignment_expression = 125,    /* assignment_expression  */
  YYSYMBOL_assignment_operator = 126,      /* assignment_operator  */
  YYSYMBOL_expression = 127,               /* expression  */
  YYSYMBOL_constant_expression = 128,      /* constant_expression  */
  YYSYMBOL_declaration = 129,              /* declaration  */
  YYSYMBOL_declaration_specifiers = 130,   /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 131,     /* init_declarator_list  */
  YYSYMBOL_init_declarator = 132,          /* init_declarator  */
  YYSYMBOL_storage_class_specifier = 133,  /* storage_class_specifier  */
  YYSYMBOL_type_specifier = 134,           /* type_specifier  */
  YYSYMBOL_struct_or_union_specifier = 135, /* struct_or_union_specifier  */
  YYSYMBOL_struct_or_union = 136,          /* struct_or_union  */
  YYSYMBOL_struct_declaration_list = 137,  /* struct_declaration_list  */
  YYSYMBOL_struct_declaration = 138,       /* struct_declaration  */
  YYSYMBOL_specifier_qualifier_list = 139, /* specifier_qualifier_list  */
  YYSYMBOL_struct_declarator_list = 140,   /* struct_declarator_list  */
  YYSYMBOL_struct_declarator = 141,        /* struct_declarator  */
  YYSYMBOL_enum_specifier = 142,           /* enum_specifier  */
  YYSYMBOL_enumerator_list = 143,          /* enumerator_list  */
  YYSYMBOL_enumerator = 144,               /* enumerator  */
  YYSYMBOL_atomic_type_specifier = 145,    /* atomic_type_specifier  */
  YYSYMBOL_type_qualifier = 146,           /* type_qualifier  */
  YYSYMBOL_function_specifier = 147,       /* function_specifier  */
  YYSYMBOL_alignment_specifier = 148,      /* alignment_specifier  */
  YYSYMBOL_declarator = 149,               /* declarator  */
  YYSYMBOL_direct_declarator = 150,        /* direct_declarator  */
  YYSYMBOL_pointer = 151,                  /* pointer  */
  YYSYMBOL_type_qualifier_list = 152,      /* type_qualifier_list  */
  YYSYMBOL_parameter_type_list = 153,      /* parameter_type_list  */
  YYSYMBOL_parameter_list = 154,           /* parameter_list  */
  YYSYMBOL_parameter_declaration = 155,    /* parameter_declaration  */
  YYSYMBOL_identifier_list = 156,          /* identifier_list  */
  YYSYMBOL_type_name = 157,                /* type_name  */
  YYSYMBOL_abstract_declarator = 158,      /* abstract_declarator  */
  YYSYMBOL_direct_abstract_declarator = 159, /* direct_abstract_declarator  */
  YYSYMBOL_initializer = 160,              /* initializer  */
  YYSYMBOL_initializer_list = 161,         /* initializer_list  */
  YYSYMBOL_designation = 162,              /* designation  */
  YYSYMBOL_designator_list = 163,          /* designator_list  */
  YYSYMBOL_designator = 164,               /* designator  */
  YYSYMBOL_static_assert_declaration = 165, /* static_assert_declaration  */
  YYSYMBOL_statement = 166,                /* statement  */
  YYSYMBOL_labeled_statement = 167,        /* labeled_statement  */
  YYSYMBOL_compound_statement = 168,       /* compound_statement  */
  YYSYMBOL_block_item_list = 169,          /* block_item_list  */
  YYSYMBOL_block_item = 170,               /* block_item  */
  YYSYMBOL_expression_statement = 171,     /* expression_statement  */
  YYSYMBOL_selection_statement = 172,      /* selection_statement  */
  YYSYMBOL_iteration_statement = 173,      /* iteration_statement  */
  YYSYMBOL_jump_statement = 174,           /* jump_statement  */
  YYSYMBOL_translation_unit = 175,         /* translation_unit  */
  YYSYMBOL_external_declaration = 176,     /* external_declaration  */
  YYSYMBOL_function_definition = 177,      /* function_definition  */
  YYSYMBOL_declaration_list = 178          /* declaration_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  68
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2542

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  100
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  79
/* YYNRULES -- Number of rules.  */
#define YYNRULES  276
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  481

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   331


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    91,     2,     2,     2,    93,    86,     2,
      77,    78,    87,    88,    79,    89,    83,    92,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    80,    99,
      94,     2,    95,    98,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    81,     2,    82,    96,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    84,    97,    85,    90,     2,     2,     2,
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
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   131,   131,   132,   133,   134,   138,   142,   146,   150,
     157,   164,   168,   172,   179,   186,   187,   191,   192,   196,
     197,   198,   202,   206,   207,   208,   212,   216,   220,   227,
     231,   238,   239,   243,   247,   251,   255,   259,   266,   267,
     268,   269,   270,   271,   275,   276,   283,   284,   288,   292,
     299,   300,   304,   311,   312,   316,   323,   324,   328,   332,
     336,   343,   344,   348,   355,   356,   363,   364,   371,   372,
     379,   380,   387,   388,   395,   396,   400,   401,   408,   409,
     410,   411,   412,   413,   414,   415,   416,   417,   418,   422,
     423,   427,   431,   435,   439,   446,   454,   460,   466,   470,
     478,   484,   492,   498,   504,   511,   515,   522,   523,   527,
     528,   529,   530,   531,   532,   536,   540,   544,   548,   552,
     556,   560,   564,   568,   572,   576,   580,   584,   588,   592,
     596,   603,   607,   611,   618,   619,   623,   627,   634,   638,
     642,   649,   650,   651,   652,   656,   660,   667,   668,   669,
     673,   677,   681,   685,   689,   696,   697,   701,   702,   706,
     713,   714,   715,   716,   720,   721,   725,   729,   736,   740,
     744,   745,   749,   750,   751,   752,   753,   754,   755,   756,
     757,   758,   762,   763,   767,   768,   769,   770,   774,   775,
     779,   783,   787,   791,   798,   802,   806,   813,   814,   818,
     819,   823,   824,   825,   829,   830,   831,   832,   833,   834,
     835,   836,   837,   838,   839,   840,   841,   842,   843,   844,
     845,   846,   847,   848,   849,   853,   854,   855,   859,   860,
     861,   862,   866,   870,   871,   875,   876,   880,   887,   888,
     889,   890,   891,   892,   896,   900,   904,   911,   915,   922,
     926,   933,   934,   938,   942,   949,   954,   959,   963,   964,
     965,   966,   967,   968,   972,   976,   980,   984,   988,   995,
    1000,  1008,  1009,  1013,  1017,  1024,  1025
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "STRING_LITERAL", "I_CONSTANT", "F_CONSTANT", "FUNC_NAME", "SIZEOF",
  "STRUCT", "UNION", "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP", "RIGHT_OP",
  "LE_OP", "GE_OP", "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "MUL_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN",
  "RIGHT_ASSIGN", "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "JUST_ASSIGN",
  "TYPEDEF_NAME", "ENUMERATION_CONSTANT", "TYPEDEF", "EXTERN", "STATIC",
  "AUTO", "REGISTER", "INLINE", "CONST", "RESTRICT", "VOLATILE", "BOOL",
  "CHAR", "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE",
  "VOID", "COMPLEX", "IMAGINARY", "ENUM", "ELLIPSIS", "CASE", "DEFAULT",
  "IF", "ELSE", "SWITCH", "WHILE", "DO", "FOR", "GOTO", "CONTINUE",
  "BREAK", "RETURN", "ALIGNAS", "ALIGNOF", "ATOMIC", "GENERIC", "NORETURN",
  "STATIC_ASSERT", "THREAD_LOCAL", "'('", "')'", "','", "':'", "'['",
  "']'", "'.'", "'{'", "'}'", "'&'", "'*'", "'+'", "'-'", "'~'", "'!'",
  "'/'", "'%'", "'<'", "'>'", "'^'", "'|'", "'?'", "';'", "$accept",
  "primary_expression", "constant", "some_identifier",
  "enumeration_constant", "string", "generic_selection",
  "generic_assoc_list", "generic_association", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "struct_or_union_specifier",
  "struct_or_union", "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "atomic_type_specifier", "type_qualifier", "function_specifier",
  "alignment_specifier", "declarator", "direct_declarator", "pointer",
  "type_qualifier_list", "parameter_type_list", "parameter_list",
  "parameter_declaration", "identifier_list", "type_name",
  "abstract_declarator", "direct_abstract_declarator", "initializer",
  "initializer_list", "designation", "designator_list", "designator",
  "static_assert_declaration", "statement", "labeled_statement",
  "compound_statement", "block_item_list", "block_item",
  "expression_statement", "selection_statement", "iteration_statement",
  "jump_statement", "translation_unit", "external_declaration",
  "function_definition", "declaration_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-265)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    2229,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,
    -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,
    -265,  -265,  -265,  -265,  -265,    31,   -46,   -38,  -265,   -24,
    -265,  -265,    39,  2326,  2326,  -265,    44,  -265,  -265,  2326,
    2326,  2326,  -265,   887,  -265,  -265,   -55,    24,   975,  2470,
    1716,  -265,    87,   -17,  -265,  -265,   -30,  -265,  2029,    90,
     149,  -265,  -265,   -21,  2374,  -265,  -265,  -265,  -265,  -265,
      24,  -265,    36,   -47,  -265,  -265,  -265,  -265,  -265,  1739,
    1762,  1762,  -265,    -1,    78,   975,  -265,  -265,  -265,  -265,
    -265,  -265,  -265,  -265,  -265,  -265,  -265,   222,  -265,  1716,
    -265,   -57,   143,   240,   124,   239,    35,    73,    69,   156,
     106,  -265,   103,  2470,    91,  2470,   125,   130,   137,   146,
    -265,  -265,  -265,   -17,    87,  -265,  1469,   461,  -265,    39,
    -265,  2079,  2133,   365,    90,  2374,  1930,  -265,    45,  -265,
     101,  1716,    18,  -265,   975,  -265,   975,  -265,  -265,  2470,
    1716,   453,  -265,  -265,   184,   151,   224,  -265,  -265,  1492,
    1716,   233,  -265,  1716,  1716,  1716,  1716,  1716,  1716,  1716,
    1716,  1716,  1716,  1716,  1716,  1716,  1716,  1716,  1716,  1716,
    1716,  1716,  -265,  -265,  1881,   998,   129,  -265,   132,  -265,
    -265,  -265,   246,  -265,  -265,  -265,  -265,   228,  1446,  -265,
    -265,   189,  1716,   197,   210,   217,   219,   766,   227,   263,
     209,   215,   789,  -265,  -265,    80,  -265,  -265,  -265,  -265,
     580,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,
      58,   238,   251,  -265,   186,  1311,  -265,   236,   243,  1087,
    1978,  -265,  -265,  1716,  -265,    83,  -265,   226,    25,  -265,
    -265,  -265,  -265,   254,   260,   264,   265,  -265,  -265,  -265,
    -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  1716,  -265,
    1716,  1581,  -265,  -265,   193,  -265,    75,  -265,  -265,  -265,
    -265,   -57,   -57,   143,   143,   240,   240,   240,   240,   124,
     124,   239,    35,    73,    69,   156,   195,  -265,   267,   269,
    1311,  -265,   270,   271,  1110,   132,  2181,  1199,   278,  1716,
     357,  -265,   115,  1469,    -9,  -265,   766,   281,   766,  1716,
    1716,  1716,   300,   677,   275,  -265,  -265,  -265,    94,  -265,
    -265,  -265,  1828,  -265,   144,  -265,  -265,  2277,  -265,   361,
     297,  1311,  -265,  -265,  1716,  -265,   298,   299,  -265,  -265,
      76,  -265,  1716,  -265,   301,   301,  -265,  2422,  -265,  -265,
    1446,  -265,  -265,  1716,  -265,  1716,  -265,  -265,   302,  1311,
    -265,  -265,  1716,  -265,   304,  -265,   305,  1311,  -265,   307,
     312,  1222,   283,   313,  -265,  1334,  -265,  -265,  -265,  -265,
    -265,   766,  -265,   202,   204,   207,   310,   878,   878,  -265,
    -265,  -265,  -265,  -265,  -265,   314,   315,  -265,  -265,  -265,
    -265,   321,   212,  -265,   348,   120,  -265,  -265,  -265,   347,
     349,  -265,  -265,   350,  1311,  -265,  -265,  1716,  -265,   351,
    -265,  -265,  -265,  -265,  1469,  -265,   766,   766,   766,  1716,
    1604,  1627,  -265,  -265,  1716,  -265,  2422,  1716,  1357,  -265,
    -265,  -265,  -265,   352,   353,  -265,  -265,   369,  -265,  -265,
     223,   766,   234,   766,   244,  -265,  -265,  -265,  -265,  -265,
    -265,   766,   340,  -265,   766,  -265,   766,  -265,  -265,  -265,
    -265
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       0,   134,   135,   130,   109,   110,   111,   113,   114,   164,
     160,   161,   162,   124,   116,   117,   118,   119,   122,   123,
     120,   121,   115,   125,   126,     0,     0,   163,   165,     0,
     112,   272,     0,    96,    98,   128,     0,   129,   127,   100,
     102,   104,    94,     0,   269,   271,   154,     0,     0,     0,
       0,    10,     0,   187,    92,   170,     0,   105,   108,   169,
       0,    95,    97,   133,     0,    99,   101,   103,     1,   270,
       0,    11,   158,     0,   155,    12,     7,     8,    13,     0,
       0,     0,     9,     0,     0,     0,    38,    39,    40,    41,
      42,    43,    19,     3,     2,     4,     6,    31,    44,     0,
      46,    50,    53,    56,    61,    64,    66,    68,    70,    72,
      74,    91,     0,   142,   200,   144,     0,     0,     0,     0,
     163,   188,   186,   185,     0,    93,     0,     0,   275,     0,
     274,     0,     0,     0,   168,     0,     0,   136,     0,   140,
       0,     0,     0,   150,     0,    35,     0,    32,    33,     0,
       0,    44,    76,    89,     0,     0,     0,    25,    26,     0,
       0,     0,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   167,   141,     0,     0,   202,   199,   203,   143,
     166,   159,     0,   171,   189,   184,   106,   108,     0,   227,
     107,    10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   247,   253,     0,   251,   252,   238,   239,
       0,   249,   240,   241,   242,   243,   276,   273,   197,   182,
     196,     0,   191,   192,     0,     0,   172,    39,     0,     0,
       0,   131,   137,     0,   138,     0,   145,   149,     0,   152,
     157,   151,   156,     0,     0,     0,     0,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    78,     0,     5,
       0,     0,    24,    21,     0,    29,     0,    23,    47,    48,
      49,    51,    52,    54,    55,    59,    60,    57,    58,    62,
      63,    65,    67,    69,    71,    73,     0,   221,     0,     0,
       0,   205,    39,     0,     0,   201,     0,     0,     0,     0,
       0,   229,     0,     0,     0,   233,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   265,   266,   267,     0,   254,
     248,   250,     0,   194,   202,   195,   181,     0,   183,     0,
       0,     0,   173,   180,     0,   179,    39,     0,   132,   147,
       0,   139,     0,   153,    36,     0,    37,     0,    77,    90,
       0,    45,    22,     0,    20,     0,   222,   204,     0,     0,
     206,   212,     0,   211,     0,   223,     0,     0,   213,    39,
       0,     0,     0,     0,   236,     0,   225,   228,   232,   234,
     244,     0,   246,     0,     0,     0,     0,     0,     0,   264,
     268,   190,   193,   198,   175,     0,     0,   176,   178,   146,
     148,     0,     0,    15,     0,     0,    30,    75,   208,     0,
       0,   210,   224,     0,     0,   214,   220,     0,   219,     0,
     237,   235,   226,   231,     0,   245,     0,     0,     0,     0,
       0,     0,   174,   177,     0,    14,     0,     0,     0,    27,
     207,   209,   216,     0,     0,   217,   230,   256,   257,   258,
       0,     0,     0,     0,     0,    18,    16,    17,    28,   215,
     218,     0,     0,   262,     0,   260,     0,   255,   259,   263,
     261
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -265,  -265,  -265,    59,  -265,  -265,  -265,  -265,    -6,  -265,
    -265,   247,  -265,   -81,   170,   171,    70,   175,   268,   266,
     272,   262,   277,  -265,    10,   -93,  -265,   -82,   -41,   -50,
      11,  -265,   322,  -265,   -42,  -265,  -265,   323,  -116,   -18,
    -265,    95,  -265,   378,  -128,  -265,   -48,  -265,  -265,   -15,
     -56,   -34,   -77,  -122,  -265,   122,  -265,   100,   -99,  -174,
    -124,   102,  -220,  -265,   147,   -23,   -71,  -265,   -45,  -265,
     252,  -264,  -265,  -265,  -265,  -265,   417,  -265,  -265
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    92,    93,    94,    72,    95,    96,   412,   413,    97,
     274,   151,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   152,   153,   268,   215,   112,    31,
     129,    56,    57,    33,    34,    35,    36,   136,   137,   114,
     245,   246,    37,    73,    74,    38,    39,    40,    41,   119,
      59,    60,   123,   298,   232,   233,   234,   414,   299,   188,
     311,   312,   313,   314,   315,    42,   217,   218,   219,   220,
     221,   222,   223,   224,   225,    43,    44,    45,   131
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     115,   115,   200,   154,   134,   121,   113,   113,   128,   118,
     231,    32,   305,   130,   252,   187,   115,    58,   162,   122,
     242,    51,   113,   388,    10,    11,    12,    51,    51,    70,
     163,    48,   142,   199,    46,   164,   165,   115,   143,    49,
     238,   139,    51,   113,    61,    62,   138,    63,    51,   124,
      65,    66,    67,    50,    32,   120,   239,   256,   111,   398,
     111,    51,   154,   135,   154,   115,   275,   115,   141,   125,
      53,   113,   309,   113,   310,   194,   149,   216,   276,    51,
     186,   226,   278,   279,   280,   121,   227,   115,   115,   195,
      51,    55,   303,   113,   113,   183,   115,   189,   115,   296,
     250,   115,   113,   251,   113,   199,    71,   113,   304,   197,
     353,    55,   139,   139,   197,    47,    52,   138,   138,    55,
     252,   176,    52,   247,   242,   243,    53,   180,    64,    71,
     328,   335,    53,   440,   441,   332,   322,   121,    54,   185,
     170,   171,   340,   230,   244,    53,   347,    51,   116,   117,
     186,   111,    51,    52,   270,   150,   243,   364,   341,   270,
     305,   317,   350,    53,    52,   434,   178,   132,   184,   177,
     216,   133,   185,   270,    53,   358,   179,   359,    53,   329,
     248,   182,   351,    55,   376,   155,   249,   121,    55,   387,
     361,   194,   115,   400,   385,   230,   334,    55,   113,   448,
     386,    71,   349,   190,   181,   449,   184,   368,   191,   306,
     185,   374,   111,   307,   380,   333,   192,   139,   172,   173,
     199,   332,   138,   369,   193,   185,    52,   272,   434,   271,
     381,   166,   167,   156,   157,   158,   277,   393,   394,   395,
     285,   286,   287,   288,   253,   390,   254,   392,   405,   255,
     308,   406,   121,   111,   168,   169,   194,   174,   175,   121,
     126,   433,   269,   270,   338,   339,   324,   199,   383,   316,
     416,   362,   363,   397,   270,   365,   419,   318,   134,   420,
     436,   270,   437,   270,   423,   438,   270,   319,   429,    55,
     445,   446,   199,   194,   320,    98,   321,    98,   334,   159,
     424,   472,   270,   160,   323,   161,   352,    71,   325,   115,
     456,   410,   474,   270,   326,   113,   336,   230,   342,   111,
     435,   194,   476,   270,   433,   343,   145,   147,   148,   121,
     337,   453,   354,   194,   454,   247,   281,   282,   355,   283,
     284,   199,   356,   230,   357,   366,    98,   367,   230,   289,
     290,   465,   370,   371,   467,   199,   382,   460,   462,   464,
     384,   391,   111,   396,   403,   457,   458,   459,    51,    75,
      76,    77,    78,    79,   399,   417,   194,    80,    81,   404,
     407,   408,   430,   422,   418,   360,   421,   439,    98,   425,
     473,    55,   475,    55,   426,   431,   442,   443,   115,    82,
     477,   444,   235,   479,   113,   480,    10,    11,    12,    55,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,   447,   450,
     471,   451,   452,   455,   469,   470,    83,   120,    84,   478,
     466,   294,    85,   292,   291,   409,   196,   236,   140,    98,
     293,    86,   237,    88,    89,    90,    91,   295,   240,   402,
      69,   389,   415,     0,   201,    75,    76,    77,    78,    79,
       1,     2,   331,    80,    81,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,     0,     0,     0,     0,
      98,     0,     0,     0,     3,    82,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    98,   202,
     203,   204,     0,   205,   206,   207,   208,   209,   210,   211,
     212,    26,    83,    27,    84,    28,    29,    30,    85,     0,
       0,     0,     0,     0,     0,   127,   213,    86,    87,    88,
      89,    90,    91,     0,     0,     0,    98,     0,     0,     0,
     214,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   201,    75,    76,    77,    78,    79,     1,
       2,     0,    80,    81,     0,     0,     0,     0,     0,    98,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    98,     3,    82,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     0,   202,   203,
     204,     0,   205,   206,   207,   208,   209,   210,   211,   212,
      26,    83,    27,    84,    28,    29,    30,    85,     0,     0,
       0,     0,     0,     0,   127,   330,    86,    87,    88,    89,
      90,    91,     0,     0,     0,     0,     0,     0,     0,   214,
      51,    75,    76,    77,    78,    79,     1,     2,     0,    80,
      81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       3,    82,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    26,    83,    27,
      84,    28,    29,    30,    85,     0,     0,     0,     0,     0,
       0,     0,     0,    86,    87,    88,    89,    90,    91,   201,
      75,    76,    77,    78,    79,     0,   214,     0,    80,    81,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,    75,    76,    77,    78,    79,     0,     0,
      82,    80,    81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    82,   202,   203,   204,     0,   205,   206,
     207,   208,   209,   210,   211,   212,     0,    83,     0,    84,
       0,     0,     0,    85,     0,     0,     0,     0,     0,     0,
     127,     0,    86,    87,    88,    89,    90,    91,     0,     0,
      83,     0,    84,     0,     0,   214,    85,     0,     0,     0,
       0,     0,     0,     0,     0,    86,    87,    88,    89,    90,
      91,    51,    75,    76,    77,    78,    79,    68,   327,     0,
      80,    81,     0,     0,     0,     0,     1,     2,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    82,     0,     0,     0,     0,     0,     0,     0,
       3,     0,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,     0,     0,     0,     0,     0,    83,
       0,    84,     0,     0,     0,    85,     0,    26,     0,    27,
       0,    28,    29,    30,    86,    87,    88,    89,    90,    91,
       0,     0,     0,     0,     0,     0,     0,   214,    51,    75,
      76,    77,    78,    79,     1,     2,     0,    80,    81,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,    75,    76,    77,    78,    79,     0,     3,    82,
      80,    81,     0,     0,     0,     0,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    82,     0,     0,   300,     0,     0,     0,    10,
      11,    12,     0,     0,     0,     0,    83,    27,    84,     0,
       0,     0,    85,     0,     0,     0,     0,     0,     0,     0,
       0,    86,    87,    88,    89,    90,    91,     0,     0,    83,
     120,    84,     0,     0,     0,    85,     0,     0,     0,     0,
     301,     0,     0,     0,    86,   302,    88,    89,    90,    91,
      51,    75,    76,    77,    78,    79,     0,     0,     0,    80,
      81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,    75,    76,    77,    78,    79,     0,
       0,    82,    80,    81,   344,     0,     0,     0,    10,    11,
      12,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,     0,   372,     0,     0,
       0,    10,    11,    12,     0,     0,     0,     0,    83,   120,
      84,     0,     0,     0,    85,     0,     0,     0,     0,   345,
       0,     0,     0,    86,   346,    88,    89,    90,    91,     0,
       0,    83,   120,    84,     0,     0,     0,    85,     0,     0,
       0,     0,   373,     0,     0,     0,    86,    87,    88,    89,
      90,    91,    51,    75,    76,    77,    78,    79,     0,     0,
       0,    80,    81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,    75,    76,    77,    78,
      79,     0,     0,    82,    80,    81,   377,     0,     0,     0,
      10,    11,    12,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    82,     0,     0,   427,
       0,     0,     0,    10,    11,    12,     0,     0,     0,     0,
      83,   120,    84,     0,     0,     0,    85,     0,     0,     0,
       0,   378,     0,     0,     0,    86,   379,    88,    89,    90,
      91,     0,     0,    83,   120,    84,     0,     0,     0,    85,
       0,     0,     0,     0,   428,     0,     0,     0,    86,    87,
      88,    89,    90,    91,    51,    75,    76,    77,    78,    79,
       0,     0,     0,    80,    81,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    75,    76,
      77,    78,    79,     0,     0,    82,    80,    81,     0,     0,
       0,     0,    10,    11,    12,     0,     0,     0,     0,     0,
      51,    75,    76,    77,    78,    79,     0,     0,    82,    80,
      81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    83,   120,    84,     0,     0,     0,    85,     0,
       0,    82,     0,     0,     0,     0,     0,    86,    87,    88,
      89,    90,    91,     0,     0,    83,     0,    84,     0,     0,
       0,    85,     0,     0,     0,   309,     0,   310,   198,   432,
      86,    87,    88,    89,    90,    91,     0,     0,    83,     0,
      84,     0,     0,     0,    85,     0,     0,     0,   309,     0,
     310,   198,   468,    86,    87,    88,    89,    90,    91,    51,
      75,    76,    77,    78,    79,     0,     0,     0,    80,    81,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,    75,    76,    77,    78,    79,     0,     0,
      82,    80,    81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,    75,    76,    77,    78,
      79,     0,     0,    82,    80,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,     0,    84,
       0,     0,     0,    85,     0,     0,    82,   309,     0,   310,
     198,     0,    86,    87,    88,    89,    90,    91,     0,     0,
      83,     0,    84,     0,     0,     0,    85,     0,     0,     0,
       0,     0,     0,   198,     0,    86,    87,    88,    89,    90,
      91,     0,     0,    83,     0,    84,     0,     0,     0,    85,
     273,     0,     0,     0,     0,     0,     0,     0,    86,    87,
      88,    89,    90,    91,    51,    75,    76,    77,    78,    79,
       0,     0,     0,    80,    81,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    75,    76,
      77,    78,    79,     0,     0,    82,    80,    81,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,    75,    76,    77,    78,    79,     0,     0,    82,    80,
      81,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    83,     0,    84,     0,     0,     0,    85,     0,
       0,    82,     0,     0,     0,   360,     0,    86,    87,    88,
      89,    90,    91,     0,     0,    83,     0,    84,     0,     0,
       0,    85,   461,     0,     0,     0,     0,     0,     0,     0,
      86,    87,    88,    89,    90,    91,     0,     0,    83,     0,
      84,     0,     0,     0,    85,   463,     0,     0,     0,     0,
       0,     0,     0,    86,    87,    88,    89,    90,    91,    51,
      75,    76,    77,    78,    79,     0,     0,     0,    80,    81,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,    75,    76,    77,    78,    79,     0,     0,
      82,    80,    81,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,    75,    76,    77,    78,
      79,     0,     0,    82,    80,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,     0,    84,
       0,     0,     0,    85,     0,     0,    82,     0,     0,     0,
       0,     0,    86,    87,    88,    89,    90,    91,     0,     0,
      83,     0,    84,     0,     0,     0,   144,     0,     0,     0,
       0,     0,     0,     0,     0,    86,    87,    88,    89,    90,
      91,    51,     0,    83,     0,    84,     0,     1,     2,   146,
       0,     0,     0,     0,     0,     0,     0,     0,    86,    87,
      88,    89,    90,    91,     0,     0,     0,     0,     0,     0,
       0,     3,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,     0,     0,     0,     0,     0,
       1,     2,     0,     0,     0,     0,     0,     0,    26,     0,
      27,     0,    28,     0,    30,   332,   297,     0,     0,   185,
       0,     0,     0,     0,     3,    53,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     0,     1,
       2,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    26,     0,    27,     0,    28,     0,    30,   184,   297,
       0,     0,   185,     3,     0,     0,     0,     0,    53,     0,
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     1,     2,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,     0,     0,    29,     0,     0,     0,     0,
       0,     3,     0,     0,     0,   241,     0,     0,     0,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,     0,     0,     0,     1,     2,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      27,     0,     0,    29,     0,     0,     0,     0,     0,     0,
       0,   126,     3,   348,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,     0,     0,     1,     2,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    26,
       0,    27,     0,    28,    29,    30,     0,     0,     0,     0,
       0,     0,     3,   127,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,   228,     0,     0,     0,
       0,     0,     1,     2,     0,     0,     0,     0,     0,    26,
       0,    27,     0,    28,    29,    30,     0,     0,     0,     0,
       0,     0,     0,   127,     0,     0,     3,     0,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
       1,     2,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    26,     0,    27,     0,    28,     0,    30,
       0,   229,     0,     0,     3,     0,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,     1,     2,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    26,     0,    27,     0,    28,     0,    30,     0,   375,
       0,     0,     3,     0,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,     1,     2,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    26,
       0,    27,     0,    28,    29,    30,     0,     0,     0,     0,
       3,     0,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,   401,     1,     2,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    26,     0,    27,
       0,    28,     0,    30,     0,     0,     0,     0,     0,     3,
       0,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,     1,     2,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,     0,    27,     0,
      28,     0,    30,     0,     0,     0,     0,     3,     0,     0,
       0,     0,     0,     0,     0,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,     1,     2,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    27,     0,     0,    29,
       0,     0,     0,     0,     0,     3,     0,     0,     0,     0,
       0,     0,     0,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,     1,
       2,   411,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     0,     0,     0,     0,     0,     0,
       0,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27
};

static const yytype_int16 yycheck[] =
{
      48,    49,   126,    85,    60,    53,    48,    49,    58,    50,
     132,     0,   186,    58,   142,   114,    64,    32,    99,    53,
     136,     3,    64,    32,    41,    42,    43,     3,     3,    84,
      87,    77,    79,   126,     3,    92,    93,    85,    85,    77,
     133,    64,     3,    85,    33,    34,    64,     3,     3,    79,
      39,    40,    41,    77,    43,    72,   133,   150,    48,   323,
      50,     3,   144,    84,   146,   113,   159,   115,    32,    99,
      87,   113,    81,   115,    83,   123,    77,   127,   160,     3,
     114,   131,   163,   164,   165,   133,   131,   135,   136,   123,
       3,    32,   185,   135,   136,   113,   144,   115,   146,   181,
     141,   149,   144,    85,   146,   198,    47,   149,   185,   124,
      85,    52,   135,   136,   129,    84,    77,   135,   136,    60,
     248,    86,    77,   138,   240,    80,    87,    21,    84,    70,
     212,   230,    87,   397,   398,    77,   207,   185,    99,    81,
      16,    17,   235,   132,    99,    87,   239,     3,    48,    49,
     184,   141,     3,    77,    79,    77,    80,    82,   235,    79,
     334,   202,    79,    87,    77,   385,    97,    77,    77,    96,
     220,    81,    81,    79,    87,   268,    20,   270,    87,    99,
      79,    78,    99,   124,   306,    85,    85,   235,   129,   313,
     271,   239,   240,    99,    79,   184,   230,   138,   240,    79,
      85,   142,   243,    78,    98,    85,    77,   300,    78,    77,
      81,   304,   202,    81,   307,   230,    79,   240,    94,    95,
     313,    77,   240,   300,    78,    81,    77,     3,   448,    78,
     307,    88,    89,    11,    12,    13,     3,   319,   320,   321,
     170,   171,   172,   173,   144,   316,   146,   318,   341,   149,
       4,   344,   300,   243,    14,    15,   304,    18,    19,   307,
      32,   385,    78,    79,    78,    79,     3,   360,   309,    80,
     363,    78,    79,   323,    79,    80,   369,    80,   334,   372,
      78,    79,    78,    79,   377,    78,    79,    77,   381,   230,
      78,    79,   385,   341,    77,    48,    77,    50,   332,    77,
     377,    78,    79,    81,    77,    83,    80,   248,    99,   357,
     434,   352,    78,    79,    99,   357,    78,   306,    82,   309,
     391,   369,    78,    79,   448,    82,    79,    80,    81,   377,
      79,   424,    78,   381,   427,   350,   166,   167,    78,   168,
     169,   434,    78,   332,    79,    78,    99,    78,   337,   174,
     175,   444,    82,    82,   447,   448,    78,   439,   440,   441,
       3,    80,   352,    63,     3,   436,   437,   438,     3,     4,
       5,     6,     7,     8,    99,   365,   424,    12,    13,    82,
      82,    82,    99,    78,    82,    84,    82,    77,   141,    82,
     461,   332,   463,   334,    82,    82,    82,    82,   446,    34,
     471,    80,    37,   474,   446,   476,    41,    42,    43,   350,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,    80,    82,
      61,    82,    82,    82,    82,    82,    71,    72,    73,    99,
     446,   179,    77,   177,   176,   350,   124,    82,    70,   202,
     178,    86,    87,    88,    89,    90,    91,   180,   135,   337,
      43,   314,   360,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,   220,    12,    13,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    -1,    -1,    -1,    -1,
     243,    -1,    -1,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,   271,    58,
      59,    60,    -1,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,    -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    -1,    -1,   309,    -1,    -1,    -1,
      99,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,   352,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   365,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    58,    59,
      60,    -1,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    -1,    -1,
      -1,    -1,    -1,    -1,    84,    85,    86,    87,    88,    89,
      90,    91,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,
       3,     4,     5,     6,     7,     8,     9,    10,    -1,    12,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    90,    91,     3,
       4,     5,     6,     7,     8,    -1,    99,    -1,    12,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,    -1,    -1,
      34,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    58,    59,    60,    -1,    62,    63,
      64,    65,    66,    67,    68,    69,    -1,    71,    -1,    73,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,
      84,    -1,    86,    87,    88,    89,    90,    91,    -1,    -1,
      71,    -1,    73,    -1,    -1,    99,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,    90,
      91,     3,     4,     5,     6,     7,     8,     0,    99,    -1,
      12,    13,    -1,    -1,    -1,    -1,     9,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    71,
      -1,    73,    -1,    -1,    -1,    77,    -1,    70,    -1,    72,
      -1,    74,    75,    76,    86,    87,    88,    89,    90,    91,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    99,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    12,    13,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,    -1,    33,    34,
      12,    13,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    34,    -1,    -1,    37,    -1,    -1,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,    71,    72,    73,    -1,
      -1,    -1,    77,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    90,    91,    -1,    -1,    71,
      72,    73,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,
      82,    -1,    -1,    -1,    86,    87,    88,    89,    90,    91,
       3,     4,     5,     6,     7,     8,    -1,    -1,    -1,    12,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,    -1,
      -1,    34,    12,    13,    37,    -1,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    -1,    -1,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    71,    72,
      73,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    82,
      -1,    -1,    -1,    86,    87,    88,    89,    90,    91,    -1,
      -1,    71,    72,    73,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    91,     3,     4,     5,     6,     7,     8,    -1,    -1,
      -1,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,    -1,    34,    12,    13,    37,    -1,    -1,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    -1,    -1,    37,
      -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      71,    72,    73,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      -1,    82,    -1,    -1,    -1,    86,    87,    88,    89,    90,
      91,    -1,    -1,    71,    72,    73,    -1,    -1,    -1,    77,
      -1,    -1,    -1,    -1,    82,    -1,    -1,    -1,    86,    87,
      88,    89,    90,    91,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,    -1,    34,    12,    13,    -1,    -1,
      -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,    -1,    -1,    34,    12,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    -1,    -1,    -1,    77,    -1,
      -1,    34,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,
      89,    90,    91,    -1,    -1,    71,    -1,    73,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    81,    -1,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    -1,    -1,    71,    -1,
      73,    -1,    -1,    -1,    77,    -1,    -1,    -1,    81,    -1,
      83,    84,    85,    86,    87,    88,    89,    90,    91,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,    -1,    -1,
      34,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,    -1,    34,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    73,
      -1,    -1,    -1,    77,    -1,    -1,    34,    81,    -1,    83,
      84,    -1,    86,    87,    88,    89,    90,    91,    -1,    -1,
      71,    -1,    73,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    86,    87,    88,    89,    90,
      91,    -1,    -1,    71,    -1,    73,    -1,    -1,    -1,    77,
      78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    90,    91,     3,     4,     5,     6,     7,     8,
      -1,    -1,    -1,    12,    13,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,    -1,    -1,    34,    12,    13,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,     4,     5,     6,     7,     8,    -1,    -1,    34,    12,
      13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    -1,    73,    -1,    -1,    -1,    77,    -1,
      -1,    34,    -1,    -1,    -1,    84,    -1,    86,    87,    88,
      89,    90,    91,    -1,    -1,    71,    -1,    73,    -1,    -1,
      -1,    77,    78,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    91,    -1,    -1,    71,    -1,
      73,    -1,    -1,    -1,    77,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    90,    91,     3,
       4,     5,     6,     7,     8,    -1,    -1,    -1,    12,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     3,     4,     5,     6,     7,     8,    -1,    -1,
      34,    12,    13,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,    -1,    -1,    34,    12,    13,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,    73,
      -1,    -1,    -1,    77,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    86,    87,    88,    89,    90,    91,    -1,    -1,
      71,    -1,    73,    -1,    -1,    -1,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,    90,
      91,     3,    -1,    71,    -1,    73,    -1,     9,    10,    77,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,
      88,    89,    90,    91,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,
      72,    -1,    74,    -1,    76,    77,    78,    -1,    -1,    81,
      -1,    -1,    -1,    -1,    33,    87,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    -1,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    72,    -1,    74,    -1,    76,    77,    78,
      -1,    -1,    81,    33,    -1,    -1,    -1,    -1,    87,    -1,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,     9,    10,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    -1,    75,    -1,    -1,    -1,    -1,
      -1,    33,    -1,    -1,    -1,    85,    -1,    -1,    -1,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    -1,    -1,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    33,    85,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,     9,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      -1,    72,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    84,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,     3,    -1,    -1,    -1,
      -1,    -1,     9,    10,    -1,    -1,    -1,    -1,    -1,    70,
      -1,    72,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    84,    -1,    -1,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    -1,    72,    -1,    74,    -1,    76,
      -1,    78,    -1,    -1,    33,    -1,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,     9,    10,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    72,    -1,    74,    -1,    76,    -1,    78,
      -1,    -1,    33,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,     9,    10,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      -1,    72,    -1,    74,    75,    76,    -1,    -1,    -1,    -1,
      33,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,     9,    10,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,
      -1,    74,    -1,    76,    -1,    -1,    -1,    -1,    -1,    33,
      -1,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,     9,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    -1,
      74,    -1,    76,    -1,    -1,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    -1,    75,
      -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,     9,
      10,    59,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    33,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    70,    72,    74,    75,
      76,   129,   130,   133,   134,   135,   136,   142,   145,   146,
     147,   148,   165,   175,   176,   177,     3,    84,    77,    77,
      77,     3,    77,    87,    99,   103,   131,   132,   149,   150,
     151,   130,   130,     3,    84,   130,   130,   130,     0,   176,
      84,   103,   104,   143,   144,     4,     5,     6,     7,     8,
      12,    13,    34,    71,    73,    77,    86,    87,    88,    89,
      90,    91,   101,   102,   103,   105,   106,   109,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   128,   134,   139,   146,   157,   157,   128,   149,
      72,   146,   151,   152,    79,    99,    32,    84,   129,   130,
     168,   178,    77,    81,   150,    84,   137,   138,   139,   165,
     143,    32,    79,    85,    77,   111,    77,   111,   111,    77,
      77,   111,   124,   125,   127,   157,    11,    12,    13,    77,
      81,    83,   113,    87,    92,    93,    88,    89,    14,    15,
      16,    17,    94,    95,    18,    19,    86,    96,    97,    20,
      21,    98,    78,   139,    77,    81,   151,   158,   159,   139,
      78,    78,    79,    78,   146,   151,   132,   149,    84,   125,
     160,     3,    58,    59,    60,    62,    63,    64,    65,    66,
      67,    68,    69,    85,    99,   127,   129,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   129,   168,     3,    78,
     130,   153,   154,   155,   156,    37,    82,    87,   125,   152,
     137,    85,   138,    80,    99,   140,   141,   149,    79,    85,
     128,    85,   144,   157,   157,   157,   125,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,   126,    78,
      79,    78,     3,    78,   110,   125,   127,     3,   113,   113,
     113,   114,   114,   115,   115,   116,   116,   116,   116,   117,
     117,   118,   119,   120,   121,   122,   127,    78,   153,   158,
      37,    82,    87,   125,   152,   159,    77,    81,     4,    81,
      83,   160,   161,   162,   163,   164,    80,   128,    80,    77,
      77,    77,   166,    77,     3,    99,    99,    99,   127,    99,
      85,   170,    77,   149,   151,   158,    78,    79,    78,    79,
     125,   152,    82,    82,    37,    82,    87,   125,    85,   128,
      79,    99,    80,    85,    78,    78,    78,    79,   125,   125,
      84,   113,    78,    79,    82,    80,    78,    78,   125,   152,
      82,    82,    37,    82,   125,    78,   153,    37,    82,    87,
     125,   152,    78,   128,     3,    79,    85,   160,    32,   164,
     166,    80,   166,   127,   127,   127,    63,   129,   171,    99,
      99,    57,   155,     3,    82,   125,   125,    82,    82,   141,
     128,    59,   107,   108,   157,   161,   125,   124,    82,   125,
     125,    82,    78,   125,   152,    82,    82,    37,    82,   125,
      99,    82,    85,   160,   162,   166,    78,    78,    78,    77,
     171,   171,    82,    82,    80,    78,    79,    80,    79,    85,
      82,    82,    82,   125,   125,    82,   160,   166,   166,   166,
     127,    78,   127,    78,   127,   125,   108,   125,    85,    82,
      82,    61,    78,   166,    78,   166,    78,   166,    99,   166,
     166
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,   100,   101,   101,   101,   101,   101,   102,   102,   102,
     103,   104,   105,   105,   106,   107,   107,   108,   108,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   110,
     110,   111,   111,   111,   111,   111,   111,   111,   112,   112,
     112,   112,   112,   112,   113,   113,   114,   114,   114,   114,
     115,   115,   115,   116,   116,   116,   117,   117,   117,   117,
     117,   118,   118,   118,   119,   119,   120,   120,   121,   121,
     122,   122,   123,   123,   124,   124,   125,   125,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   127,
     127,   128,   129,   129,   129,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   131,   131,   132,   132,   133,
     133,   133,   133,   133,   133,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   135,   135,   135,   136,   136,   137,   137,   138,   138,
     138,   139,   139,   139,   139,   140,   140,   141,   141,   141,
     142,   142,   142,   142,   142,   143,   143,   144,   144,   145,
     146,   146,   146,   146,   147,   147,   148,   148,   149,   149,
     150,   150,   150,   150,   150,   150,   150,   150,   150,   150,
     150,   150,   150,   150,   151,   151,   151,   151,   152,   152,
     153,   153,   154,   154,   155,   155,   155,   156,   156,   157,
     157,   158,   158,   158,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   159,   159,   159,
     159,   159,   159,   159,   159,   160,   160,   160,   161,   161,
     161,   161,   162,   163,   163,   164,   164,   165,   166,   166,
     166,   166,   166,   166,   167,   167,   167,   168,   168,   169,
     169,   170,   170,   171,   171,   172,   172,   172,   173,   173,
     173,   173,   173,   173,   174,   174,   174,   174,   174,   175,
     175,   176,   176,   177,   177,   178,   178
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     6,     1,     3,     3,     3,     1,
       4,     3,     4,     3,     3,     2,     2,     6,     7,     1,
       3,     1,     2,     2,     2,     2,     4,     4,     1,     1,
       1,     1,     1,     1,     1,     4,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     5,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     2,     3,     1,     2,     1,     2,     1,     2,
       1,     2,     1,     2,     1,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     5,     2,     1,     1,     1,     2,     2,     3,
       1,     2,     1,     2,     1,     1,     3,     2,     3,     1,
       4,     5,     5,     6,     2,     1,     3,     3,     1,     4,
       1,     1,     1,     1,     1,     1,     4,     4,     2,     1,
       1,     3,     3,     4,     6,     5,     5,     6,     5,     4,
       4,     4,     3,     4,     3,     2,     2,     1,     1,     2,
       3,     1,     1,     3,     2,     2,     1,     1,     3,     2,
       1,     2,     1,     1,     3,     2,     3,     5,     4,     5,
       4,     3,     3,     3,     4,     6,     5,     5,     6,     4,
       4,     2,     3,     3,     4,     3,     4,     1,     2,     1,
       4,     3,     2,     1,     2,     3,     2,     7,     1,     1,
       1,     1,     1,     1,     3,     4,     3,     2,     3,     1,
       2,     1,     1,     1,     2,     7,     5,     5,     5,     7,
       6,     7,     6,     7,     3,     2,     2,     2,     3,     1,
       2,     1,     1,     4,     3,     1,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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
        yyerror (yyscanner, driver, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, yyscanner, driver); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, yyscan_t yyscanner, c_driver_t *driver)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yyscanner);
  YY_USE (driver);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, yyscan_t yyscanner, c_driver_t *driver)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, yyscanner, driver);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule, yyscan_t yyscanner, c_driver_t *driver)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)], yyscanner, driver);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, yyscanner, driver); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, yyscan_t yyscanner, c_driver_t *driver)
{
  YY_USE (yyvaluep);
  YY_USE (yyscanner);
  YY_USE (driver);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t yyscanner, c_driver_t *driver)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, yyscanner, driver);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 5: /* primary_expression: '(' expression ')'  */
#line 135 "c_gramm.y"
        {
		(yyval.tree) = (yyvsp[-1].tree);
	}
#line 2038 "c_parser.cpp"
    break;

  case 7: /* constant: I_CONSTANT  */
#line 143 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->mp_.box_long ((yyvsp[0].intval)); 
	}
#line 2046 "c_parser.cpp"
    break;

  case 8: /* constant: F_CONSTANT  */
#line 147 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->mp_.box_double ((yyvsp[0].floatval)); 
	}
#line 2054 "c_parser.cpp"
    break;

  case 9: /* constant: ENUMERATION_CONSTANT  */
#line 151 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (2, STMT_LITERAL, driver->mp_.box_long (0)); 
	}
#line 2062 "c_parser.cpp"
    break;

  case 10: /* some_identifier: IDENTIFIER  */
#line 158 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (2, STMT_IDENTIFIER, driver->mp_.box_string ((yyvsp[0].strval))); 
	}
#line 2070 "c_parser.cpp"
    break;

  case 12: /* string: STRING_LITERAL  */
#line 169 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (2, STMT_LITERAL, driver->mp_.box_string ((yyvsp[0].strval))); 
	}
#line 2078 "c_parser.cpp"
    break;

  case 13: /* string: FUNC_NAME  */
#line 173 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL; 
	}
#line 2086 "c_parser.cpp"
    break;

  case 14: /* generic_selection: GENERIC '(' assignment_expression ',' generic_assoc_list ')'  */
#line 180 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2094 "c_parser.cpp"
    break;

  case 21: /* postfix_expression: postfix_expression '(' ')'  */
#line 199 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (4, STMT_CALL, (yyvsp[-2].tree), NULL, NULL); 
	}
#line 2102 "c_parser.cpp"
    break;

  case 22: /* postfix_expression: postfix_expression '(' argument_expression_list ')'  */
#line 203 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (4, STMT_CALL, (yyvsp[-3].tree), driver->mp_.list_to_array ((yyvsp[-1].list)), NULL); 
	}
#line 2110 "c_parser.cpp"
    break;

  case 25: /* postfix_expression: postfix_expression INC_OP  */
#line 209 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (2, STMT_SOP_POSTINC, (yyvsp[-1].tree)); 
	}
#line 2118 "c_parser.cpp"
    break;

  case 26: /* postfix_expression: postfix_expression DEC_OP  */
#line 213 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (2, STMT_SOP_POSTDEC, (yyvsp[-1].tree)); 
	}
#line 2126 "c_parser.cpp"
    break;

  case 27: /* postfix_expression: '(' type_name ')' '{' initializer_list '}'  */
#line 217 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2134 "c_parser.cpp"
    break;

  case 28: /* postfix_expression: '(' type_name ')' '{' initializer_list ',' '}'  */
#line 221 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2142 "c_parser.cpp"
    break;

  case 29: /* argument_expression_list: assignment_expression  */
#line 228 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.cons_set ((yyvsp[0].tree), NULL); 
	}
#line 2150 "c_parser.cpp"
    break;

  case 30: /* argument_expression_list: argument_expression_list ',' assignment_expression  */
#line 232 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.box_set_conc ((yyvsp[-2].list), driver->mp_.cons_set ((yyvsp[0].tree), NULL)); 
	}
#line 2158 "c_parser.cpp"
    break;

  case 32: /* unary_expression: INC_OP unary_expression  */
#line 240 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (2, STMT_SOP_PREINC, (yyvsp[0].tree)); 
	}
#line 2166 "c_parser.cpp"
    break;

  case 33: /* unary_expression: DEC_OP unary_expression  */
#line 244 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (2, STMT_SOP_PREDEC, (yyvsp[0].tree)); 
	}
#line 2174 "c_parser.cpp"
    break;

  case 34: /* unary_expression: unary_operator cast_expression  */
#line 248 "c_gramm.y"
        {
		(yyval.tree) = (yyvsp[0].tree);
	}
#line 2182 "c_parser.cpp"
    break;

  case 35: /* unary_expression: SIZEOF unary_expression  */
#line 252 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2190 "c_parser.cpp"
    break;

  case 36: /* unary_expression: SIZEOF '(' type_name ')'  */
#line 256 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2198 "c_parser.cpp"
    break;

  case 37: /* unary_expression: ALIGNOF '(' type_name ')'  */
#line 260 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2206 "c_parser.cpp"
    break;

  case 45: /* cast_expression: '(' type_name ')' cast_expression  */
#line 277 "c_gramm.y"
        {
		(yyval.tree) = (yyvsp[0].tree);
	}
#line 2214 "c_parser.cpp"
    break;

  case 47: /* multiplicative_expression: multiplicative_expression '*' cast_expression  */
#line 285 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_TIMES, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2222 "c_parser.cpp"
    break;

  case 48: /* multiplicative_expression: multiplicative_expression '/' cast_expression  */
#line 289 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_DIV, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2230 "c_parser.cpp"
    break;

  case 49: /* multiplicative_expression: multiplicative_expression '%' cast_expression  */
#line 293 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_MODULO, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2238 "c_parser.cpp"
    break;

  case 51: /* additive_expression: additive_expression '+' multiplicative_expression  */
#line 301 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_PLUS, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2246 "c_parser.cpp"
    break;

  case 52: /* additive_expression: additive_expression '-' multiplicative_expression  */
#line 305 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_MINUS, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2254 "c_parser.cpp"
    break;

  case 54: /* shift_expression: shift_expression LEFT_OP additive_expression  */
#line 313 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_LSHIFT, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2262 "c_parser.cpp"
    break;

  case 55: /* shift_expression: shift_expression RIGHT_OP additive_expression  */
#line 317 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_RSHIFT, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2270 "c_parser.cpp"
    break;

  case 57: /* relational_expression: relational_expression '<' shift_expression  */
#line 325 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_LT, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2278 "c_parser.cpp"
    break;

  case 58: /* relational_expression: relational_expression '>' shift_expression  */
#line 329 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_GT, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2286 "c_parser.cpp"
    break;

  case 59: /* relational_expression: relational_expression LE_OP shift_expression  */
#line 333 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_LTE, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2294 "c_parser.cpp"
    break;

  case 60: /* relational_expression: relational_expression GE_OP shift_expression  */
#line 337 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_GTE, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2302 "c_parser.cpp"
    break;

  case 62: /* equality_expression: equality_expression EQ_OP relational_expression  */
#line 345 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_EQ, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2310 "c_parser.cpp"
    break;

  case 63: /* equality_expression: equality_expression NE_OP relational_expression  */
#line 349 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_NEQ, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2318 "c_parser.cpp"
    break;

  case 65: /* and_expression: and_expression '&' equality_expression  */
#line 357 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_BAND, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2326 "c_parser.cpp"
    break;

  case 67: /* exclusive_or_expression: exclusive_or_expression '^' and_expression  */
#line 365 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_BXOR, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2334 "c_parser.cpp"
    break;

  case 69: /* inclusive_or_expression: inclusive_or_expression '|' exclusive_or_expression  */
#line 373 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_BOR, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2342 "c_parser.cpp"
    break;

  case 71: /* logical_and_expression: logical_and_expression AND_OP inclusive_or_expression  */
#line 381 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_AND, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2350 "c_parser.cpp"
    break;

  case 73: /* logical_or_expression: logical_or_expression OR_OP logical_and_expression  */
#line 389 "c_gramm.y"
        {
		(yyval.tree) = (c_tree_t*)driver->list (3, STMT_BOP_OR, (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 2358 "c_parser.cpp"
    break;

  case 77: /* assignment_expression: unary_expression assignment_operator assignment_expression  */
#line 402 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (4, STMT_ASSIGN, driver->mp_.list_to_array (driver->mp_.cons_set ((yyvsp[-2].tree), NULL)), (yyvsp[0].tree), (yyvsp[-1].intval)); 
	}
#line 2366 "c_parser.cpp"
    break;

  case 92: /* declaration: declaration_specifiers ';'  */
#line 432 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_DCL, NULL, driver->mp_.list_to_array ((yyvsp[-1].list))); 
	}
#line 2374 "c_parser.cpp"
    break;

  case 93: /* declaration: declaration_specifiers init_declarator_list ';'  */
#line 436 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_DCL, driver->mp_.list_to_array ((yyvsp[-1].list)), driver->mp_.list_to_array ((yyvsp[-2].list))); 
	}
#line 2382 "c_parser.cpp"
    break;

  case 94: /* declaration: static_assert_declaration  */
#line 440 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2390 "c_parser.cpp"
    break;

  case 95: /* declaration_specifiers: storage_class_specifier declaration_specifiers  */
#line 447 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.box_set_conc (
			driver->mp_.cons_set (
				(TT*)driver->list (2, STMT_STOR_CLASS, (yyvsp[-1].intval)), 
				NULL),
			driver->mp_.cons_set ((yyvsp[0].list), NULL)); 
	}
#line 2402 "c_parser.cpp"
    break;

  case 96: /* declaration_specifiers: storage_class_specifier  */
#line 455 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.cons_set (
			(TT*)driver->list (2, STMT_STOR_CLASS, (yyvsp[0].intval)), 
			NULL); 
	}
#line 2412 "c_parser.cpp"
    break;

  case 97: /* declaration_specifiers: type_specifier declaration_specifiers  */
#line 461 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.box_set_conc (
			driver->mp_.cons_set ((yyvsp[-1].tree), NULL),
			driver->mp_.cons_set ((yyvsp[0].list), NULL)); 
	}
#line 2422 "c_parser.cpp"
    break;

  case 98: /* declaration_specifiers: type_specifier  */
#line 467 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.cons_set ((yyvsp[0].tree), NULL); 
	}
#line 2430 "c_parser.cpp"
    break;

  case 99: /* declaration_specifiers: type_qualifier declaration_specifiers  */
#line 471 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.box_set_conc (
			driver->mp_.cons_set (
				(TT*)driver->list (2, STMT_TYPE_QUAL, (yyvsp[-1].intval)),
				NULL),
			driver->mp_.cons_set ((yyvsp[0].list), NULL)); 
	}
#line 2442 "c_parser.cpp"
    break;

  case 100: /* declaration_specifiers: type_qualifier  */
#line 479 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.cons_set (
			(TT*)driver->list (2, STMT_TYPE_QUAL, (yyvsp[0].intval)), 
			NULL); 
	}
#line 2452 "c_parser.cpp"
    break;

  case 101: /* declaration_specifiers: function_specifier declaration_specifiers  */
#line 485 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.box_set_conc (
			driver->mp_.cons_set (
				(TT*)driver->list (2, STMT_FUNC_SPEC, (yyvsp[-1].intval)),
				NULL),
			driver->mp_.cons_set ((yyvsp[0].list), NULL)); 
	}
#line 2464 "c_parser.cpp"
    break;

  case 102: /* declaration_specifiers: function_specifier  */
#line 493 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.cons_set (
			(TT*)driver->list (2, STMT_FUNC_SPEC, (yyvsp[0].intval)), 
			NULL); 
	}
#line 2474 "c_parser.cpp"
    break;

  case 103: /* declaration_specifiers: alignment_specifier declaration_specifiers  */
#line 499 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.box_set_conc (
			driver->mp_.cons_set ((yyvsp[-1].tree), NULL),
			driver->mp_.cons_set ((yyvsp[0].list), NULL)); 
	}
#line 2484 "c_parser.cpp"
    break;

  case 104: /* declaration_specifiers: alignment_specifier  */
#line 505 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.cons_set ((yyvsp[0].tree), NULL); 
	}
#line 2492 "c_parser.cpp"
    break;

  case 105: /* init_declarator_list: init_declarator  */
#line 512 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.cons_set ((yyvsp[0].tree), NULL); 
	}
#line 2500 "c_parser.cpp"
    break;

  case 106: /* init_declarator_list: init_declarator_list ',' init_declarator  */
#line 516 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.box_set_conc ((yyvsp[-2].list), driver->mp_.cons_set ((yyvsp[0].tree), NULL)); 
	}
#line 2508 "c_parser.cpp"
    break;

  case 115: /* type_specifier: VOID  */
#line 537 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, VOID, NULL); 
	}
#line 2516 "c_parser.cpp"
    break;

  case 116: /* type_specifier: CHAR  */
#line 541 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, CHAR, NULL); 
	}
#line 2524 "c_parser.cpp"
    break;

  case 117: /* type_specifier: SHORT  */
#line 545 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, SHORT, NULL); 
	}
#line 2532 "c_parser.cpp"
    break;

  case 118: /* type_specifier: INT  */
#line 549 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, INT, NULL); 
	}
#line 2540 "c_parser.cpp"
    break;

  case 119: /* type_specifier: LONG  */
#line 553 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, LONG, NULL); 
	}
#line 2548 "c_parser.cpp"
    break;

  case 120: /* type_specifier: FLOAT  */
#line 557 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, FLOAT, NULL); 
	}
#line 2556 "c_parser.cpp"
    break;

  case 121: /* type_specifier: DOUBLE  */
#line 561 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, DOUBLE, NULL); 
	}
#line 2564 "c_parser.cpp"
    break;

  case 122: /* type_specifier: SIGNED  */
#line 565 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, SIGNED, NULL); 
	}
#line 2572 "c_parser.cpp"
    break;

  case 123: /* type_specifier: UNSIGNED  */
#line 569 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, UNSIGNED, NULL); 
	}
#line 2580 "c_parser.cpp"
    break;

  case 124: /* type_specifier: BOOL  */
#line 573 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, BOOL, NULL); 
	}
#line 2588 "c_parser.cpp"
    break;

  case 125: /* type_specifier: COMPLEX  */
#line 577 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, COMPLEX, NULL); 
	}
#line 2596 "c_parser.cpp"
    break;

  case 126: /* type_specifier: IMAGINARY  */
#line 581 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, IMAGINARY, NULL); 
	}
#line 2604 "c_parser.cpp"
    break;

  case 127: /* type_specifier: atomic_type_specifier  */
#line 585 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, 0, (yyvsp[0].tree)); 
	}
#line 2612 "c_parser.cpp"
    break;

  case 128: /* type_specifier: struct_or_union_specifier  */
#line 589 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, 0, (yyvsp[0].tree)); 
	}
#line 2620 "c_parser.cpp"
    break;

  case 129: /* type_specifier: enum_specifier  */
#line 593 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, 0, (yyvsp[0].tree)); 
	}
#line 2628 "c_parser.cpp"
    break;

  case 130: /* type_specifier: TYPEDEF_NAME  */
#line 597 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_TYPE_SPEC, 0, (yyvsp[0].intval)); 
	}
#line 2636 "c_parser.cpp"
    break;

  case 131: /* struct_or_union_specifier: struct_or_union '{' struct_declaration_list '}'  */
#line 604 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (4, STMT_STRUCT_DEF, NULL, (yyvsp[-3].intval), driver->mp_.list_to_array ((yyvsp[-1].list))); 
	}
#line 2644 "c_parser.cpp"
    break;

  case 132: /* struct_or_union_specifier: struct_or_union IDENTIFIER '{' struct_declaration_list '}'  */
#line 608 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (4, STMT_STRUCT_DEF, (yyvsp[-3].strval), (yyvsp[-4].intval), driver->mp_.list_to_array ((yyvsp[-1].list))); 
	}
#line 2652 "c_parser.cpp"
    break;

  case 133: /* struct_or_union_specifier: struct_or_union IDENTIFIER  */
#line 612 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_SC_VARDEF, (yyvsp[0].strval), (yyvsp[-1].intval)); 
	}
#line 2660 "c_parser.cpp"
    break;

  case 136: /* struct_declaration_list: struct_declaration  */
#line 624 "c_gramm.y"
        {
      (yyval.list) = driver->mp_.cons_set ((yyvsp[0].tree), NULL); 
	}
#line 2668 "c_parser.cpp"
    break;

  case 137: /* struct_declaration_list: struct_declaration_list struct_declaration  */
#line 628 "c_gramm.y"
        {
      (yyval.list) = driver->mp_.box_set_conc ((yyvsp[-1].list), driver->mp_.cons_set ((yyvsp[0].tree), NULL)); 
	}
#line 2676 "c_parser.cpp"
    break;

  case 138: /* struct_declaration: specifier_qualifier_list ';'  */
#line 635 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2684 "c_parser.cpp"
    break;

  case 139: /* struct_declaration: specifier_qualifier_list struct_declarator_list ';'  */
#line 639 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2692 "c_parser.cpp"
    break;

  case 140: /* struct_declaration: static_assert_declaration  */
#line 643 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2700 "c_parser.cpp"
    break;

  case 145: /* struct_declarator_list: struct_declarator  */
#line 657 "c_gramm.y"
        {
      (yyval.list) = driver->mp_.cons_set ((yyvsp[0].tree), NULL); 
	}
#line 2708 "c_parser.cpp"
    break;

  case 146: /* struct_declarator_list: struct_declarator_list ',' struct_declarator  */
#line 661 "c_gramm.y"
        {
      (yyval.list) = driver->mp_.box_set_conc ((yyvsp[-2].list), driver->mp_.cons_set ((yyvsp[0].tree), NULL)); 
	}
#line 2716 "c_parser.cpp"
    break;

  case 150: /* enum_specifier: ENUM '{' enumerator_list '}'  */
#line 674 "c_gramm.y"
        {
		(yyval.tree)=(TT*)NULL;
	}
#line 2724 "c_parser.cpp"
    break;

  case 151: /* enum_specifier: ENUM '{' enumerator_list ',' '}'  */
#line 678 "c_gramm.y"
        {
		(yyval.tree)=(TT*)NULL;
	}
#line 2732 "c_parser.cpp"
    break;

  case 152: /* enum_specifier: ENUM IDENTIFIER '{' enumerator_list '}'  */
#line 682 "c_gramm.y"
        {
		(yyval.tree)=(TT*)NULL;
	}
#line 2740 "c_parser.cpp"
    break;

  case 153: /* enum_specifier: ENUM IDENTIFIER '{' enumerator_list ',' '}'  */
#line 686 "c_gramm.y"
        {
		(yyval.tree)=(TT*)NULL;
	}
#line 2748 "c_parser.cpp"
    break;

  case 154: /* enum_specifier: ENUM IDENTIFIER  */
#line 690 "c_gramm.y"
        {
		(yyval.tree)=(TT*)NULL;
	}
#line 2756 "c_parser.cpp"
    break;

  case 159: /* atomic_type_specifier: ATOMIC '(' type_name ')'  */
#line 707 "c_gramm.y"
        {
		(yyval.tree)=(yyvsp[-1].tree);
	}
#line 2764 "c_parser.cpp"
    break;

  case 166: /* alignment_specifier: ALIGNAS '(' type_name ')'  */
#line 726 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_ALIGN_SPEC, NULL, (yyvsp[-1].tree)); 
	}
#line 2772 "c_parser.cpp"
    break;

  case 167: /* alignment_specifier: ALIGNAS '(' constant_expression ')'  */
#line 730 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_ALIGN_SPEC, NULL, (yyvsp[-1].tree)); 
	}
#line 2780 "c_parser.cpp"
    break;

  case 168: /* declarator: pointer direct_declarator  */
#line 737 "c_gramm.y"
        {
		(yyval.tree) = (yyvsp[0].tree);
	}
#line 2788 "c_parser.cpp"
    break;

  case 171: /* direct_declarator: '(' declarator ')'  */
#line 746 "c_gramm.y"
        {
		(yyval.tree) = (yyvsp[-1].tree);
	}
#line 2796 "c_parser.cpp"
    break;

  case 181: /* direct_declarator: direct_declarator '(' parameter_type_list ')'  */
#line 759 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_PROC_HEAD, (yyvsp[-3].tree), driver->mp_.list_to_array ((yyvsp[-1].list))); 
	}
#line 2804 "c_parser.cpp"
    break;

  case 190: /* parameter_type_list: parameter_list ',' ELLIPSIS  */
#line 780 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.box_set_conc ((yyvsp[-2].list), driver->mp_.cons_set (driver->mp_.box_int((yyvsp[0].intval)), NULL)); 
	}
#line 2812 "c_parser.cpp"
    break;

  case 192: /* parameter_list: parameter_declaration  */
#line 788 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.cons_set ((yyvsp[0].tree), NULL); 
	}
#line 2820 "c_parser.cpp"
    break;

  case 193: /* parameter_list: parameter_list ',' parameter_declaration  */
#line 792 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.box_set_conc ((yyvsp[-2].list), driver->mp_.cons_set ((yyvsp[0].tree), NULL)); 
	}
#line 2828 "c_parser.cpp"
    break;

  case 194: /* parameter_declaration: declaration_specifiers declarator  */
#line 799 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_PARAM_DEF, (yyvsp[0].tree), driver->mp_.list_to_array ((yyvsp[-1].list))); 
	}
#line 2836 "c_parser.cpp"
    break;

  case 195: /* parameter_declaration: declaration_specifiers abstract_declarator  */
#line 803 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_PARAM_DEF, (yyvsp[0].tree), driver->mp_.list_to_array ((yyvsp[-1].list))); 
	}
#line 2844 "c_parser.cpp"
    break;

  case 196: /* parameter_declaration: declaration_specifiers  */
#line 807 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (3, STMT_PARAM_DEF, NULL, driver->mp_.list_to_array ((yyvsp[0].list))); 
	}
#line 2852 "c_parser.cpp"
    break;

  case 237: /* static_assert_declaration: STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';'  */
#line 881 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2860 "c_parser.cpp"
    break;

  case 244: /* labeled_statement: IDENTIFIER ':' statement  */
#line 897 "c_gramm.y"
        {
		(yyval.tree) = (yyvsp[0].tree);
	}
#line 2868 "c_parser.cpp"
    break;

  case 245: /* labeled_statement: CASE constant_expression ':' statement  */
#line 901 "c_gramm.y"
        {
		(yyval.tree) = (yyvsp[0].tree);
	}
#line 2876 "c_parser.cpp"
    break;

  case 246: /* labeled_statement: DEFAULT ':' statement  */
#line 905 "c_gramm.y"
        {
		(yyval.tree) = (yyvsp[0].tree);
	}
#line 2884 "c_parser.cpp"
    break;

  case 247: /* compound_statement: '{' '}'  */
#line 912 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2892 "c_parser.cpp"
    break;

  case 248: /* compound_statement: '{' block_item_list '}'  */
#line 916 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (2, STMT_LIST, driver->mp_.list_to_array ((yyvsp[-1].list))); 
	}
#line 2900 "c_parser.cpp"
    break;

  case 249: /* block_item_list: block_item  */
#line 923 "c_gramm.y"
    {
      (yyval.list) = driver->mp_.cons_set ((yyvsp[0].tree), NULL); 
    }
#line 2908 "c_parser.cpp"
    break;

  case 250: /* block_item_list: block_item_list block_item  */
#line 927 "c_gramm.y"
    {
      (yyval.list) = driver->mp_.box_set_conc ((yyvsp[-1].list), driver->mp_.cons_set ((yyvsp[0].tree), NULL)); 
    }
#line 2916 "c_parser.cpp"
    break;

  case 253: /* expression_statement: ';'  */
#line 939 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2924 "c_parser.cpp"
    break;

  case 254: /* expression_statement: expression ';'  */
#line 943 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (2, STMT_STMT, (yyvsp[-1].tree));
	}
#line 2932 "c_parser.cpp"
    break;

  case 255: /* selection_statement: IF '(' expression ')' statement ELSE statement  */
#line 950 "c_gramm.y"
        {
      (yyval.tree) = (TT*)driver->list (
		4, STMT_IF, (yyvsp[-4].tree), (yyvsp[-2].tree), (yyvsp[0].tree));
	}
#line 2941 "c_parser.cpp"
    break;

  case 256: /* selection_statement: IF '(' expression ')' statement  */
#line 955 "c_gramm.y"
        {
      (yyval.tree) = (TT*)driver->list (
		4, STMT_IF, (yyvsp[-2].tree), (yyvsp[0].tree), NULL);
	}
#line 2950 "c_parser.cpp"
    break;

  case 264: /* jump_statement: GOTO IDENTIFIER ';'  */
#line 973 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2958 "c_parser.cpp"
    break;

  case 265: /* jump_statement: CONTINUE ';'  */
#line 977 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2966 "c_parser.cpp"
    break;

  case 266: /* jump_statement: BREAK ';'  */
#line 981 "c_gramm.y"
        {
		(yyval.tree) = (TT*)NULL;
	}
#line 2974 "c_parser.cpp"
    break;

  case 267: /* jump_statement: RETURN ';'  */
#line 985 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (2, STMT_RETURN, NULL); 
	}
#line 2982 "c_parser.cpp"
    break;

  case 268: /* jump_statement: RETURN expression ';'  */
#line 989 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (2, STMT_RETURN, (yyvsp[-1].tree)); 
	}
#line 2990 "c_parser.cpp"
    break;

  case 269: /* translation_unit: external_declaration  */
#line 996 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.cons_set ((yyvsp[0].tree), NULL); 
		driver->parse_list_ = (yyval.list);
	}
#line 2999 "c_parser.cpp"
    break;

  case 270: /* translation_unit: translation_unit external_declaration  */
#line 1001 "c_gramm.y"
        {
		(yyval.list) = driver->mp_.box_set_conc ((yyvsp[-1].list), driver->mp_.cons_set ((yyvsp[0].tree), NULL)); 
		driver->parse_list_ = (yyval.list);
	}
#line 3008 "c_parser.cpp"
    break;

  case 273: /* function_definition: declaration_specifiers declarator declaration_list compound_statement  */
#line 1014 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (4, STMT_PROC_DEF, driver->mp_.list_to_array ((yyvsp[-3].list)), (yyvsp[-2].tree), (yyvsp[0].tree)); 
	}
#line 3016 "c_parser.cpp"
    break;

  case 274: /* function_definition: declaration_specifiers declarator compound_statement  */
#line 1018 "c_gramm.y"
        {
		(yyval.tree) = (TT*)driver->list (4, STMT_PROC_DEF, driver->mp_.list_to_array ((yyvsp[-2].list)), (yyvsp[-1].tree), (yyvsp[0].tree)); 
	}
#line 3024 "c_parser.cpp"
    break;


#line 3028 "c_parser.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (yyscanner, driver, YY_("syntax error"));
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
                      yytoken, &yylval, yyscanner, driver);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yyscanner, driver);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (yyscanner, driver, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, yyscanner, driver);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yyscanner, driver);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1028 "c_gramm.y"


typedef void* yyscan_t;
void yyerror(yyscan_t yyscanner, void *ptr, const char *s)
{
	fflush(stdout);
	fprintf(stderr, "*** --------------------------- ***\n");
	fprintf(stderr, "*** %s ***\n", s);
	fprintf(stderr, "*** in line:%d\n", yyget_lineno  (yyscanner));
	fprintf(stderr, "*** near '%s'\n\n", yyget_text(yyscanner));
}

char *mp_strdup(char *str, void *user_data)
{
	c_driver_t *pdrv = (c_driver_t *)user_data;
	return pdrv->mp_.strdup_(str);
}
