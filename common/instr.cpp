#include <stdarg.h>
#include <stdexcept>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <string>
#include <map>

#include "instr.h"

static instr_def_t sc_instrs[] = {
	{"stop",     ioCSstop, 0},
	{"nop",      ioCSnop,  0},
	{"exec",     ioCSexec, 1, {iatXAddr}},
	{"call",     ioCScall, 3, {iatCAddr, iatInt, iatInt}},
	{"if",       ioCSif,   1, {iatCAddr}},
	{"ret",      ioCSret,  0},
	{"goto",     ioCSgoto, 1, {iatCAddr}},
};

static instr_def_t sx_instrs[] = {
	{"stop",     ioCXstop},
	{"imdpush",  ioCXimdpush,  1, {iatInt}},
	{"locpush",  ioCXlocpush,  1, {iatInt}},
	{"eval",     ioCXeval,     0},
	{"cmp",      ioCXcmp,      1, {iatInt}},
	{"add",      ioCXadd,      0},
	{"sub",      ioCXsub,      0},
	{"mul",      ioCXmul,      0},
	{"div",      ioCXdiv,      0},
	{"varpush",  ioCXvarpush,  1, {iatDAddr}},
	{"varpushd", ioCXvarpushd, 1, {iatDAddr}},
};

static std::map<std::string, const instr_def_t*> cf_instrs;
static std::map<std::string, const instr_def_t*> cx_instrs;

static int init_maps()
{
	for (const auto &it : sx_instrs)
	{
		cx_instrs[it.name_] = &it;
	}

	for (const auto &it : sc_instrs)
	{
		cf_instrs[it.name_] = &it;
	}

	return 1;
}
static int inites = init_maps();



const instr_def_t* test_asm_name(const char* str, bool cf)
{
	const instr_def_t* ret = NULL;
	if (cf)
	{
		const auto& it = cf_instrs.find(str);
		if (it != cf_instrs.cend())
			return it->second;
	}
	else
	{
		const auto& it = cx_instrs.find(str);
		if (it != cx_instrs.cend())
			return it->second;
	}
	return NULL;
}

