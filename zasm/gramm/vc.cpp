#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <wchar.h>
#include <assert.h>


#include "../../common/box.h"
#include "zasm_tree.h"
#include "../../common/instr.h"
#undef YY_DECL_IS_OURS
#define YY_DECL int zasmlex( YYSTYPE * yylval_param, yyscan_t yyscanner, void *user_data )

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
//#define new DEBUG_NEW
#endif

#ifdef _WIN32
#include <io.h>
#define isatty _isatty
#define fileno _fileno
#else
#include <unistd.h>
#endif

#include "zasm_driver.h"

#include "zasm_parser.h"
#include "zasm_scanner.cpp"
#include "zasm_scanner.h"
#undef yylval
#include "zasm_parser.cpp"

