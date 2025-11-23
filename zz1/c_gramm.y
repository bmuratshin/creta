
%parse-param { yyscan_t yyscanner }
%parse-param { c_driver_t *driver }
%lex-param { yyscan_t yyscanner } 
%lex-param { zasm_driver_t *driver }
%define api.pure


%{
#include <stdio.h>
#include "c_driver.h"
#include "c_tree.h"

typedef void* yyscan_t;

void yyerror (yyscan_t yyscanner, void *ptr, char const *msg);
%}

%token	<strval> IDENTIFIER STRING_LITERAL 
%token	<intval> I_CONSTANT 
%token	<floatval> F_CONSTANT 

%token	<strval> FUNC_NAME 
%token	<intval> SIZEOF STRUCT UNION 
%token	<intval> PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token	<intval> AND_OP OR_OP 

%token	<intval> MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token	<intval> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token	<intval> XOR_ASSIGN OR_ASSIGN JUST_ASSIGN 

%token	<intval> TYPEDEF_NAME ENUMERATION_CONSTANT

%token	<intval> TYPEDEF EXTERN STATIC AUTO REGISTER INLINE
%token	<intval> CONST RESTRICT VOLATILE
%token	<intval> BOOL CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOID
%token	<intval> COMPLEX IMAGINARY 
%token	<intval> ENUM 
%token	<intval> ELLIPSIS

%token	<intval> CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token	<intval> ALIGNAS ALIGNOF ATOMIC GENERIC NORETURN STATIC_ASSERT THREAD_LOCAL

%type <intval> assignment_operator
%type <intval> struct_or_union

%type <tree> function_definition
%type <tree> some_identifier
%type <tree> declarator
%type <tree> pointer
%type <tree> direct_declarator
%type <tree> external_declaration
%type <list> translation_unit
%type <list> block_item_list
%type <tree> block_item
%type <tree> declaration

%type <tree> statement
%type <tree> labeled_statement
%type <tree> compound_statement
%type <tree> expression_statement
%type <tree> selection_statement
%type <tree> iteration_statement
%type <tree> jump_statement

%type <tree> expression
%type <tree> assignment_expression
%type <tree> primary_expression
%type <tree> conditional_expression
%type <tree> constant_expression
%type <tree> unary_expression
%type <tree> postfix_expression
%type <tree> cast_expression
%type <tree> logical_or_expression
%type <tree> logical_and_expression
%type <tree> inclusive_or_expression
%type <tree> exclusive_or_expression
%type <tree> equality_expression
%type <tree> relational_expression
%type <tree> and_expression
%type <tree> shift_expression
%type <tree> additive_expression
%type <tree> multiplicative_expression
%type <tree> constant
%type <tree> string
%type <tree> generic_selection
%type <tree> static_assert_declaration

%type <tree> struct_or_union_specifier

%type <list> init_declarator_list
%type <tree> init_declarator

%type <list> struct_declaration_list
%type <tree> struct_declaration
%type <list> struct_declarator_list
%type <tree> struct_declarator

%type <list> parameter_type_list
%type <list> parameter_list
%type <tree> parameter_declaration
%type <list> declaration_specifiers
%type <tree> abstract_declarator

%type <intval> storage_class_specifier 
%type <intval> type_qualifier 
%type <intval> function_specifier
%type <tree> type_specifier
%type <tree> type_name
%type <tree> alignment_specifier
%type <tree> atomic_type_specifier
%type <tree> enum_specifier
%type <list> argument_expression_list

%start translation_unit

%union {
  long        intval;
  double      floatval;
  char       *strval;

  c_tree_t   *tree;
  box_set_t   list;
  box_t       box;
};

%%

primary_expression
	: some_identifier
	| constant
	| string
	| '(' expression ')'
	{
		$$ = $2;
	}
	| generic_selection
	;

constant
	: I_CONSTANT		/* includes character_constant */
	{
		$$ = (TT*)driver->mp_.box_long ($1); 
	}
	| F_CONSTANT
	{
		$$ = (TT*)driver->mp_.box_double ($1); 
	}
	| ENUMERATION_CONSTANT	/* after it has been defined as such */
	{
		$$ = (TT*)driver->mk_node (2, STMT_LITERAL, driver->mp_.box_long (0)); 
	}
	;

some_identifier
	: IDENTIFIER
	{
		$$ = (TT*)driver->mk_node (2, STMT_IDENTIFIER, driver->mp_.box_string ($1)); 
	}
	;

enumeration_constant		/* before it has been defined as such */
	: some_identifier
	;

string
	: STRING_LITERAL
	{
		$$ = (TT*)driver->mk_node (2, STMT_LITERAL, driver->mp_.box_string ($1)); 
	}
	| FUNC_NAME
	{
		$$ = (TT*)NULL; 
	}
	;

generic_selection
	: GENERIC '(' assignment_expression ',' generic_assoc_list ')'
	{
		$$ = (TT*)NULL;
	}
	;

generic_assoc_list
	: generic_association
	| generic_assoc_list ',' generic_association
	;

generic_association
	: type_name ':' assignment_expression
	| DEFAULT ':' assignment_expression
	;

postfix_expression
	: primary_expression
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	{
		$$ = (TT*)driver->mk_node (4, STMT_CALL, $1, NULL, NULL); 
	}
	| postfix_expression '(' argument_expression_list ')'
	{
		$$ = (TT*)driver->mk_node (4, STMT_CALL, $1, driver->mp_.list_to_array ($3), NULL); 
	}
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP
	{
		$$ = (c_tree_t*)driver->mk_node (2, STMT_SOP_POSTINC, $1); 
	}
	| postfix_expression DEC_OP
	{
		$$ = (c_tree_t*)driver->mk_node (2, STMT_SOP_POSTDEC, $1); 
	}
	| '(' type_name ')' '{' initializer_list '}'
	{
		$$ = (TT*)NULL;
	}
	| '(' type_name ')' '{' initializer_list ',' '}'
	{
		$$ = (TT*)NULL;
	}
	;

argument_expression_list
	: assignment_expression
	{
		$$ = driver->mp_.cons_set ($1, NULL); 
	}
	| argument_expression_list ',' assignment_expression
	{
		$$ = driver->mp_.box_set_conc ($1, driver->mp_.cons_set ($3, NULL)); 
	}
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression
	{
		$$ = (c_tree_t*)driver->mk_node (2, STMT_SOP_PREINC, $2); 
	}
	| DEC_OP unary_expression
	{
		$$ = (c_tree_t*)driver->mk_node (2, STMT_SOP_PREDEC, $2); 
	}
	| unary_operator cast_expression
	{
		$$ = $2;
	}
	| SIZEOF unary_expression
	{
		$$ = (TT*)NULL;
	}
	| SIZEOF '(' type_name ')'
	{
		$$ = (TT*)NULL;
	}
	| ALIGNOF '(' type_name ')'
	{
		$$ = (TT*)NULL;
	}
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	{
		$$ = $4;
	}
	;

multiplicative_expression
	: cast_expression
	| multiplicative_expression '*' cast_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_TIMES, $1, $3); 
	}
	| multiplicative_expression '/' cast_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_DIV, $1, $3); 
	}
	| multiplicative_expression '%' cast_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_MODULO, $1, $3); 
	}
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_PLUS, $1, $3); 
	}
	| additive_expression '-' multiplicative_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_MINUS, $1, $3); 
	}
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_LSHIFT, $1, $3); 
	}
	| shift_expression RIGHT_OP additive_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_RSHIFT, $1, $3); 
	}
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_LT, $1, $3); 
	}
	| relational_expression '>' shift_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_GT, $1, $3); 
	}
	| relational_expression LE_OP shift_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_LTE, $1, $3); 
	}
	| relational_expression GE_OP shift_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_GTE, $1, $3); 
	}
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_EQ, $1, $3); 
	}
	| equality_expression NE_OP relational_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_NEQ, $1, $3); 
	}
	;

and_expression
	: equality_expression
	| and_expression '&' equality_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_BAND, $1, $3); 
	}
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_BXOR, $1, $3); 
	}
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_BOR, $1, $3); 
	}
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_AND, $1, $3); 
	}
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	{
		$$ = (c_tree_t*)driver->mk_node (3, STMT_BOP_OR, $1, $3); 
	}
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	{
		$$ = (TT*)driver->mk_node (4, STMT_ASSIGN, driver->mp_.list_to_array (driver->mp_.cons_set ($1, NULL)), $3, $2); 
	}
	;

assignment_operator
	: JUST_ASSIGN
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression	/* with constraints */
	;

declaration
	: declaration_specifiers ';'
	{
		$$ = (TT*)driver->mk_node (3, STMT_DCL, NULL, driver->mp_.list_to_array ($1)); 
	}
	| declaration_specifiers init_declarator_list ';'
	{
		$$ = (TT*)driver->mk_node (3, STMT_DCL, driver->mp_.list_to_array ($2), driver->mp_.list_to_array ($1)); 
	}
	| static_assert_declaration
	{
		$$ = (TT*)NULL;
	}
	;

declaration_specifiers
	: storage_class_specifier declaration_specifiers
	{
		$$ = driver->mp_.box_set_conc (
			driver->mp_.cons_set (
				(TT*)driver->mk_node (2, STMT_STOR_CLASS, $1), 
				NULL),
			driver->mp_.cons_set ($2, NULL)); 
	}
	| storage_class_specifier
	{
		$$ = driver->mp_.cons_set (
			(TT*)driver->mk_node (2, STMT_STOR_CLASS, $1), 
			NULL); 
	}
	| type_specifier declaration_specifiers
	{
		$$ = driver->mp_.box_set_conc (
			driver->mp_.cons_set ($1, NULL),
			driver->mp_.cons_set ($2, NULL)); 
	}
	| type_specifier
	{
		$$ = driver->mp_.cons_set ($1, NULL); 
	}
	| type_qualifier declaration_specifiers
	{
		$$ = driver->mp_.box_set_conc (
			driver->mp_.cons_set (
				(TT*)driver->mk_node (2, STMT_TYPE_QUAL, $1),
				NULL),
			driver->mp_.cons_set ($2, NULL)); 
	}
	| type_qualifier
	{
		$$ = driver->mp_.cons_set (
			(TT*)driver->mk_node (2, STMT_TYPE_QUAL, $1), 
			NULL); 
	}
	| function_specifier declaration_specifiers
	{
		$$ = driver->mp_.box_set_conc (
			driver->mp_.cons_set (
				(TT*)driver->mk_node (2, STMT_FUNC_SPEC, $1),
				NULL),
			driver->mp_.cons_set ($2, NULL)); 
	}
	| function_specifier
	{
		$$ = driver->mp_.cons_set (
			(TT*)driver->mk_node (2, STMT_FUNC_SPEC, $1), 
			NULL); 
	}
	| alignment_specifier declaration_specifiers
	{
		$$ = driver->mp_.box_set_conc (
			driver->mp_.cons_set ($1, NULL),
			driver->mp_.cons_set ($2, NULL)); 
	}
	| alignment_specifier
	{
		$$ = driver->mp_.cons_set ($1, NULL); 
	}
	;

init_declarator_list
	: init_declarator
	{
		$$ = driver->mp_.cons_set ($1, NULL); 
	}
	| init_declarator_list ',' init_declarator
	{
		$$ = driver->mp_.box_set_conc ($1, driver->mp_.cons_set ($3, NULL)); 
	}
	;

init_declarator
	: declarator JUST_ASSIGN initializer
	| declarator
	;

storage_class_specifier
	: TYPEDEF	/* identifiers must be flagged as TYPEDEF_NAME */
	| EXTERN
	| STATIC
	| THREAD_LOCAL
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, VOID, NULL); 
	}
	| CHAR
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, CHAR, NULL); 
	}
	| SHORT
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, SHORT, NULL); 
	}
	| INT
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, INT, NULL); 
	}
	| LONG
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, LONG, NULL); 
	}
	| FLOAT
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, FLOAT, NULL); 
	}
	| DOUBLE
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, DOUBLE, NULL); 
	}
	| SIGNED
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, SIGNED, NULL); 
	}
	| UNSIGNED
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, UNSIGNED, NULL); 
	}
	| BOOL
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, BOOL, NULL); 
	}
	| COMPLEX
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, COMPLEX, NULL); 
	}
	| IMAGINARY	  	/* non-mandated extension */
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, IMAGINARY, NULL); 
	}
	| atomic_type_specifier
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, 0, $1); 
	}
	| struct_or_union_specifier
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, 0, $1); 
	}
	| enum_specifier
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, 0, $1); 
	}
	| TYPEDEF_NAME		/* after it has been defined as such */
	{
		$$ = (TT*)driver->mk_node (3, STMT_TYPE_SPEC, 0, $1); 
	}
	;

struct_or_union_specifier
	: struct_or_union '{' struct_declaration_list '}'
	{
		$$ = (TT*)driver->mk_node (4, STMT_STRUCT_DEF, NULL, $1, driver->mp_.list_to_array ($3)); 
	}
	| struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	{
		$$ = (TT*)driver->mk_node (4, STMT_STRUCT_DEF, $2, $1, driver->mp_.list_to_array ($4)); 
	}
	| struct_or_union IDENTIFIER
	{
		$$ = (TT*)driver->mk_node (3, STMT_SC_VARDEF, $2, $1); 
	}
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	{
      $$ = driver->mp_.cons_set ($1, NULL); 
	}
	| struct_declaration_list struct_declaration
	{
      $$ = driver->mp_.box_set_conc ($1, driver->mp_.cons_set ($2, NULL)); 
	}
	;

struct_declaration
	: specifier_qualifier_list ';'	/* for anonymous struct/union */
	{
		$$ = (TT*)NULL;
	}
	| specifier_qualifier_list struct_declarator_list ';'
	{
		$$ = (TT*)NULL;
	}
	| static_assert_declaration
	{
		$$ = (TT*)NULL;
	}
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	{
      $$ = driver->mp_.cons_set ($1, NULL); 
	}
	| struct_declarator_list ',' struct_declarator
	{
      $$ = driver->mp_.box_set_conc ($1, driver->mp_.cons_set ($3, NULL)); 
	}
	;

struct_declarator
	: ':' constant_expression
	| declarator ':' constant_expression
	| declarator
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	{
		$$=(TT*)NULL;
	}
	| ENUM '{' enumerator_list ',' '}'
	{
		$$=(TT*)NULL;
	}
	| ENUM IDENTIFIER '{' enumerator_list '}'
	{
		$$=(TT*)NULL;
	}
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'
	{
		$$=(TT*)NULL;
	}
	| ENUM IDENTIFIER
	{
		$$=(TT*)NULL;
	}
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator	/* identifiers must be flagged as ENUMERATION_CONSTANT */
	: enumeration_constant JUST_ASSIGN constant_expression
	| enumeration_constant
	;

atomic_type_specifier
	: ATOMIC '(' type_name ')'
	{
		$$=$3;
	}
	;

type_qualifier
	: CONST
	| RESTRICT
	| VOLATILE
	| ATOMIC
	;

function_specifier
	: INLINE
	| NORETURN
	;

alignment_specifier
	: ALIGNAS '(' type_name ')'
	{
		$$ = (TT*)driver->mk_node (3, STMT_ALIGN_SPEC, NULL, $3); 
	}
	| ALIGNAS '(' constant_expression ')'
	{
		$$ = (TT*)driver->mk_node (3, STMT_ALIGN_SPEC, NULL, $3); 
	}
	;

declarator
	: pointer direct_declarator
	{
		$$ = $2;
	}
	| direct_declarator
	;

direct_declarator
	: some_identifier
	| '(' declarator ')'
	{
		$$ = $2;
	}
	| direct_declarator '[' ']'
	| direct_declarator '[' '*' ']'
	| direct_declarator '[' STATIC type_qualifier_list assignment_expression ']'
	| direct_declarator '[' STATIC assignment_expression ']'
	| direct_declarator '[' type_qualifier_list '*' ']'
	| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'
	| direct_declarator '[' type_qualifier_list assignment_expression ']'
	| direct_declarator '[' type_qualifier_list ']'
	| direct_declarator '[' assignment_expression ']'
	| direct_declarator '(' parameter_type_list ')'
	{
		$$ = (TT*)driver->mk_node (3, STMT_PROC_HEAD, $1, driver->mp_.list_to_array ($3)); 
	}
	| direct_declarator '(' ')'
	| direct_declarator '(' identifier_list ')'
	;

pointer
	: '*' type_qualifier_list pointer
	| '*' type_qualifier_list
	| '*' pointer
	| '*'
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;

parameter_type_list
	: parameter_list ',' ELLIPSIS
	{
		$$ = driver->mp_.box_set_conc ($1, driver->mp_.cons_set (driver->mp_.box_int($3), NULL)); 
	}
	| parameter_list
	;

parameter_list
	: parameter_declaration
	{
		$$ = driver->mp_.cons_set ($1, NULL); 
	}
	| parameter_list ',' parameter_declaration
	{
		$$ = driver->mp_.box_set_conc ($1, driver->mp_.cons_set ($3, NULL)); 
	}
	;

parameter_declaration
	: declaration_specifiers declarator
	{
		$$ = (TT*)driver->mk_node (3, STMT_PARAM_DEF, $2, driver->mp_.list_to_array ($1)); 
	}
	| declaration_specifiers abstract_declarator
	{
		$$ = (TT*)driver->mk_node (3, STMT_PARAM_DEF, $2, driver->mp_.list_to_array ($1)); 
	}
	| declaration_specifiers
	{
		$$ = (TT*)driver->mk_node (3, STMT_PARAM_DEF, NULL, driver->mp_.list_to_array ($1)); 
	}
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list abstract_declarator
	| specifier_qualifier_list
	;

abstract_declarator
	: pointer direct_abstract_declarator
	| pointer
	| direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' '*' ']'
	| '[' STATIC type_qualifier_list assignment_expression ']'
	| '[' STATIC assignment_expression ']'
	| '[' type_qualifier_list STATIC assignment_expression ']'
	| '[' type_qualifier_list assignment_expression ']'
	| '[' type_qualifier_list ']'
	| '[' assignment_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' '*' ']'
	| direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
	| direct_abstract_declarator '[' STATIC assignment_expression ']'
	| direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
	| direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
	| direct_abstract_declarator '[' type_qualifier_list ']'
	| direct_abstract_declarator '[' assignment_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	| assignment_expression
	;

initializer_list
	: designation initializer
	| initializer
	| initializer_list ',' designation initializer
	| initializer_list ',' initializer
	;

designation
	: designator_list JUST_ASSIGN
	;

designator_list
	: designator
	| designator_list designator
	;

designator
	: '[' constant_expression ']'
	| '.' IDENTIFIER
	;

static_assert_declaration
	: STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';'
	{
		$$ = (TT*)NULL;
	}
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER ':' statement
	{
		$$ = $3;
	}
	| CASE constant_expression ':' statement
	{
		$$ = $4;
	}
	| DEFAULT ':' statement
	{
		$$ = $3;
	}
	;

compound_statement
	: '{' '}'
	{
		$$ = (TT*)NULL;
	}
	| '{'  block_item_list '}'
	{
		$$ = (TT*)driver->mk_node (2, STMT_LIST, driver->mp_.list_to_array ($2)); 
	}
	;

block_item_list
	: block_item
    {
      $$ = driver->mp_.cons_set ($1, NULL); 
    }
	| block_item_list block_item
    {
      $$ = driver->mp_.box_set_conc ($1, driver->mp_.cons_set ($2, NULL)); 
    }
	;

block_item
	: declaration
	| statement
	;

expression_statement
	: ';'
	{
		$$ = (TT*)NULL;
	}
	| expression ';'
	{
		$$ = (TT*)driver->mk_node (2, STMT_STMT, $1);
	}
	;

selection_statement
	: IF '(' expression ')' statement ELSE statement
	{
      $$ = (TT*)driver->mk_node (
		4, STMT_IF, $3, $5, $7);
	}
	| IF '(' expression ')' statement
	{
      $$ = (TT*)driver->mk_node (
		4, STMT_IF, $3, $5, NULL);
	}
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	| FOR '(' declaration expression_statement ')' statement
	| FOR '(' declaration expression_statement expression ')' statement
	;

jump_statement
	: GOTO IDENTIFIER ';'
	{
		$$ = (TT*)NULL;
	}
	| CONTINUE ';'
	{
		$$ = (TT*)NULL;
	}
	| BREAK ';'
	{
		$$ = (TT*)NULL;
	}
	| RETURN ';'
	{
		$$ = (TT*)driver->mk_node (2, STMT_RETURN, NULL); 
	}
	| RETURN expression ';'
	{
		$$ = (TT*)driver->mk_node (2, STMT_RETURN, $2); 
	}
	;

translation_unit
	: external_declaration
	{
		$$ = driver->mp_.cons_set ($1, NULL); 
		driver->parse_list_ = $$;
	}
	| translation_unit external_declaration
	{
		$$ = driver->mp_.box_set_conc ($1, driver->mp_.cons_set ($2, NULL)); 
		driver->parse_list_ = $$;
	}
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	{
		$$ = (TT*)driver->mk_node (4, STMT_PROC_DEF, driver->mp_.list_to_array ($1), $2, $4); 
	}
	| declaration_specifiers declarator compound_statement
	{
		$$ = (TT*)driver->mk_node (4, STMT_PROC_DEF, driver->mp_.list_to_array ($1), $2, $3); 
	}
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

%%

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
