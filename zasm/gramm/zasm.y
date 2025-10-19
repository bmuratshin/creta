/*
 *  zasm.y
 *
 *
 *  ZZ assembler parser
 *
 */
%parse-param { yyscan_t yyscanner }
%parse-param { zasm_driver_t *driver }

%lex-param { yyscan_t yyscanner } 
%lex-param { zasm_driver_t *driver }
%define api.pure


%{

#include <stdint.h>
#include "box.h"
#include "zasm_driver.h"
#include "zasm_tree.h"


void yyerror (yyscan_t yyscanner, zasm_driver_t *driver, char const *msg);

%}

/* symbolic tokens */
%union {
  int64_t  intval;
  double   floatval;
  char    *strval;
  wchar_t *wstrval;

  const struct instr_def_t *instr;
  struct zasm_tree_t *tree;
  box_set_t   list;
  box_t       box;
};

%token		ZASM_DATA_SECTION ZASM_CCODE_SECTION ZASM_XCODE_SECTION 

%token		<instr>	   ZASM_INSTR

%token		<floatval> ZASM_FLOAT_LITERAL
%token		<wstrval>  ZASM_IDENTIFIER
%token		<strval>   ZASM_STRING_LITERAL
%token		<intval>   ZASM_INTEGER_LITERAL
%token		<strval>   ZASM_PRAGMA

%token 			ZASM_LEXICAL_ERROR

%type <list>	section_list  
%type <tree>	section data_section xcode_section ccode_section
%type <list>	data_list data_elem_list code_list instr_args
%type <tree>	data_item data_elem code_item instr_item instr_arg



%start section_list

%%

section_list
	: section
	{
		$$ = driver->mp_.cons_set ($1, NULL); 
	}
	| section_list section
	{
		$$ = driver->mp_.box_set_conc ($1, driver->mp_.cons_set ($2, NULL)); 
	}
	;

section
	:	data_section
	|	ccode_section
	|   xcode_section
	;

/*************************************************************************************/
data_section
	: ZASM_DATA_SECTION '{' data_list '}'
	{
		$$ = NULL;
	}

data_list
	: data_item
	{
		$$ = NULL;
	}
	| data_list data_item
	{
		$$ = NULL;
	}
	;

data_item
	: ZASM_IDENTIFIER ':' data_elem_list ';'
	{
		driver->add_var(driver->mp_.box_string($1), $3);
		$$ = NULL;
	}
	;

data_elem_list
	: data_elem
	{
		$$ = driver->mp_.cons_set ($1, NULL); 
		  driver->parse_list_ = $$;
	}
	| data_elem_list data_elem
	{
		$$ = driver->mp_.box_set_conc ($1, driver->mp_.cons_set ($2, NULL)); 
		driver->parse_list_ = $$;
	}
	;

data_elem
	: ZASM_INTEGER_LITERAL
	{
		uint64_t *ptr = (uint64_t *)driver->mp_.alloc(sizeof(uint64_t));
		*ptr = $1;
		$$ = (TT*)driver->list (3, ZASM_DATAITEM, 4 /* int32 */, ptr); 
	}
	;

/*************************************************************************************/

ccode_section 
	: ZASM_CCODE_SECTION 
	{
		driver->set_in_cf();
	}
	'{' code_list '}'
	{
		driver->test_stop();
		$$ = NULL;
	}
	;

code_list
	: code_item
	{
		$$ = driver->mp_.cons_set ($1, NULL); 
		  driver->parse_list_ = $$;
	}
	| code_list code_item
	{
		$$ = driver->mp_.box_set_conc ($1, driver->mp_.cons_set ($2, NULL)); 
		driver->parse_list_ = $$;
	}
	;

code_item
	: ZASM_IDENTIFIER ':' 
	{
		driver->add_bookmark($1);
		$$ = NULL;
	}
	| instr_item
	{
		$$ = NULL;
	}
	;




/*************************************************************************************/

xcode_section 
	: ZASM_XCODE_SECTION 
	{
		driver->set_in_xf();
	}
	'{' code_list '}'
	{
		driver->test_stop();
		$$ = NULL;
	}
	;

/*************************************************************************************/


instr_item
	: ZASM_INSTR instr_args ';'
	{
		driver->add_instr($1, $2);
		$$ = NULL;
	}
	| ZASM_INSTR ';'
	{
		driver->add_instr($1, NULL);
		$$ = NULL;
	}
	;

instr_args 
	: instr_arg
	{
		$$ = driver->mp_.cons_set ($1, NULL); 
	}
	| instr_args instr_arg
	{
		$$ = driver->mp_.box_set_conc ($1, driver->mp_.cons_set ($2, NULL)); 
	}
	;

instr_arg
	: ZASM_FLOAT_LITERAL
	{
		$$ = (TT*)driver->list (3, ZASM_INSTR_ARG, instrArgTypes::iatDouble, driver->mp_.box_double($1)); 
	}
	| ZASM_IDENTIFIER
	{
		$$ = (TT*)driver->list (3, ZASM_INSTR_ARG, instrArgTypes::iatIdent, driver->mp_.box_string($1)); 
	}
	| ZASM_STRING_LITERAL
	{
		$$ = (TT*)driver->list (3, ZASM_INSTR_ARG, instrArgTypes::iatLong, driver->mp_.box_string($1)); 
	}
	| ZASM_INTEGER_LITERAL
	{
		$$ = (TT*)driver->list (3, ZASM_INSTR_ARG, instrArgTypes::iatLong, driver->mp_.box_long($1)); 
	}
	;


%%


void zasmerror(yyscan_t yyscanner, zasm_driver_t *driver, const char *s)
{
	char buf[64];
	snprintf(buf, sizeof(buf), "Line %d: ", driver->lineno_ + 1);
	driver->error_ = buf;
	driver->error_ += s;
	driver->error_ += " at ";
	driver->error_ += (yyget_text(yyscanner));
	throw (driver->error_.c_str ());
}


