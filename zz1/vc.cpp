#include "stdafx.h"


#define lint
#ifdef _WIN32
#include <io.h>
#define isatty _isatty
#define fileno _fileno
#endif

#include "box.h"
#include "c_tree.h"
#define YY_DECL int yylex( YYSTYPE * yylval_param, yyscan_t yyscanner, void *user_data )

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif

struct c_driver_t;
#include "c_scanner.cpp"
#include "c_scanner.h"
#undef yylval
#include "c_parser.cpp"
