%option header-file="zasm_scanner.h"
%option 8bit
%option reentrant 
%option bison-bridge 
%option noyyalloc noyyfree noyyrealloc
%option yylineno

alpha   [A-Za-z]
U1      [\x80-\xbf]
U2      [\xc2-\xdf]
U3      [\xe0-\xef]
U4      [\xf0-\xf4]
ualpha  {alpha}|{U2}{U1}|{U3}{U1}{U1}|{U4}{U1}{U1}{U1}
uname   ({ualpha}|\_)*

ws      [ \t\r]+

dig     [0-9]
hdig    [a-fA-F0-9]
bname   ({ualpha}|\_)({ualpha}|{dig}|\_)*
inumber {dig}+
hnumber 0x{hdig}+

fnumber1 {dig}+("."{dig}*)* 
fnumber2 {dig}+"." 
fnumber3 "."{dig}+ 
fnumber4 {dig}+[eE][+-]?{dig}+	
fnumber5 {dig}+"."{dig}*[eE][+-]?{dig}+ 
fnumber6 "."{dig}+[eE][+-]?{dig}+

fnumber  {fnumber1}|{fnumber2}|{fnumber3}|{fnumber4}|{fnumber5}|{fnumber6}
name	{bname}|{uname}

S_NL	(\r\n|\n|\r)




%{
// YY_DECL defined in vc.cpp
#include <stdio.h>
#include "zasm_parser.h"
#include "../../common/instr.h"

extern void zasmerror(yyscan_t yyscanner, zasm_driver_t *driver, const char *s);

%}

%x STRLIT
%x COMMENT
%s NORM

%%
%{
	BEGIN NORM;
%}


<NORM>\n        { 
	((zasm_driver_t*)user_data)->lineno_++; }
<NORM>{ws}      {}    /* white space */
<NORM>[-+*/(),.;:\!\[\]><={}]    {
  return (yytext[0]);
}

<NORM>"DATA"					{ return(ZASM_DATA_SECTION); }
<NORM>"CCODE"					{ return(ZASM_CCODE_SECTION); }
<NORM>"XCODE"					{ return(ZASM_XCODE_SECTION); }

<NORM>[A-Za-z_][A-Za-z0-9_@]** {
  const instr_def_t *k= NULL;
  char buf[64], *cp, *sp;
  for (cp = buf, sp = yytext; *sp && cp < &buf[63];)
    *cp++ = *sp++;
  *cp = 0;
  if ((k = test_asm_name(buf, ((zasm_driver_t*)user_data)->in_cf)) != 0)
  {
    yylval->instr = k;
	return ZASM_INSTR;
  }
  yylval->wstrval = ((zasm_driver_t*)user_data)->mp_.box_string (yytext);
  return ZASM_IDENTIFIER;
}
<NORM>{hnumber}  {
  yylval->intval = std::stoul(yytext, nullptr, 16);
  return ZASM_INTEGER_LITERAL;
}
<NORM>{inumber}  {
  yylval->intval = atoi (yytext);
  return ZASM_INTEGER_LITERAL;
}
<NORM>{fnumber}  {
  yylval->floatval = atof (yytext);
  return ZASM_FLOAT_LITERAL;
}



<NORM>'         { yymore(); BEGIN(STRLIT); } /* strliteral wants beg. quote */
<STRLIT>'      { /* saw closing quote - all done */
                 BEGIN(NORM); /* Back. */

				 yylval->strval = yytext + 1;  //apostrophe
				 size_t l = strlen (yylval->strval);
				 if (l)
					yylval->strval[l-1] = 0;    //apostrophe

                 return ZASM_STRING_LITERAL;
               }

<STRLIT>\n     { 
	((zasm_driver_t*)user_data)->lineno_++; 
	yymore(); } /* { BEGIN(NORM); destyyerror("Unterminated string"); } */

<STRLIT>\\\n[^'\\\n]*  { 
	yymore(); } /* Backslash + newline. */

<STRLIT>\\.[^'\\\n]* | /* Backslash + anything else (also another backslash) */

<STRLIT>''[^'\\\n]*  { yymore(); } /* Doubled singlequotes (SQL-standard) */

<STRLIT>[^'\\\n]+ { yymore(); } /* For everything else after beginning quote */

<NORM>"--#pragma"{ws}{bname}.*    {
  char *ptr = yytext + 10;
  while (*ptr && *ptr == ' ' || *ptr == '\t' || *ptr == '\r') ptr++;
  yylval->strval = ptr;
  return ZASM_PRAGMA;
}    /* pragma */

<NORM>"--".*    ;    /* comment */
<NORM>"/\*"    { BEGIN (COMMENT); }
<COMMENT>"/\*"  { zasmerror (yyscanner, (zasm_driver_t*)user_data, "Nested C style comments not supported"); }
<COMMENT>"\*/"    { BEGIN (NORM); }
<COMMENT>.    ;

<NORM>.        {return ZASM_LEXICAL_ERROR;}
.             { /* discard bad characters */ }

%%

int yywrap(yyscan_t yyscanner)        /* called at end of input */
{
    return 1;           /* terminate now */
}

void *yyalloc (yy_size_t  size , yyscan_t yyscanner)
{
	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	(void)yyg;
	return malloc(size);
}

void *yyrealloc  (void * ptr, yy_size_t  size , yyscan_t yyscanner)
{
	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	(void)yyg;

	/* The cast to (char *) in the following accommodates both
	 * implementations that use char* generic pointers, and those
	 * that use void* generic pointers.  It works with the latter
	 * because both ANSI C and C++ allow castless assignment from
	 * any pointer type to void*, and deal with argument conversions
	 * as though doing an assignment.
	 */
	return realloc(ptr, size);
}

void yyfree (void * ptr , yyscan_t yyscanner)
{
	struct yyguts_t * yyg = (struct yyguts_t*)yyscanner;
	(void)yyg;
	free( (char *) ptr );	/* see yyrealloc() for (char *) cast */
}
