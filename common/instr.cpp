#include <stdarg.h>
#include <stdexcept>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <string>
#include <map>

#include "instr.h"

static instr_def_t sc_instrs[] = {
	{"stop",     ioCSstop, 1, 0},
	{"nop",      ioCSnop,  1, 0},
	{"exec",     ioCSexec, 1, 1, {iatXAddr}},
	{"call",     ioCScall, 1, 3, {iatCAddr, iatInt, iatInt}},
	{"if",       ioCSif,   1, 1, {iatCAddr}},
	{"ret",      ioCSret,  1, 0},
	{"goto",     ioCSgoto, 1, 1, {iatCAddr}},
};

static instr_def_t sx_instrs[] = {
	{"stop",     ioCXstop},
	{"nop",      ioCXnop},
	{"imdpush",  ioCXimdpush,  0,  1, {iatInt}},
	{"locpush",  ioCXlocpush,  0,  1, {iatInt}},
	{"locpushd", ioCXlocpushd, 0,  1, {iatInt}},
	{"eval",     ioCXeval},
	{"cmp",      ioCXcmp,      0,  1, {iatInt}},
	{"add",      ioCXadd},
	{"neg",      ioCXneg},
	{"sub",      ioCXsub},

	{"mul",      ioCXmul},
	{"div",      ioCXdiv},
	{"varpush",  ioCXvarpush,  0,  1, {iatDAddr}},
	{"varpushd", ioCXvarpushd, 0, 1, {iatDAddr}},
	{"eq",       ioCXeq},
	{"ne",       ioCXne},
	{"gt",       ioCXgt},
	{"ge",       ioCXge},
	{"lt",       ioCXlt},
	{"le",       ioCXle},

	{"dec",      ioCXdec},
	{"inc",      ioCXinc},
	{"postdec",  ioCXpostdec},
	{"postinc",  ioCXpostinc},
	{"preand",   ioCXpreand},
	{"and",      ioCXand},
	{"preor",    ioCXpreor},
	{"or",       ioCXor},
	{"not",      ioCXnot},
	{"band",     ioCXband},

	{"bor",      ioCXbor},
	{"xor",      ioCXxor},
	{"bnot",     ioCXbnot},
	{"assign",   ioCXassign},
	{"pop",      ioCXpop},

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

const instr_def_t* get_asm_instr(unsigned opix)
{
	bool cf = opix & 1;
	int opcode = opix >> 1;
	return get_asm_instr(opcode, cf);
}


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


constexpr const instr_def_t* get_asm_instr(int opcode, bool cf)
{
	assert(ioCS_MAX == sizeof(sc_instrs) / sizeof(sc_instrs[0]));
	assert(ioCX_MAX == sizeof(sx_instrs) / sizeof(sx_instrs[0]));

	if (cf)
	{
		assert(sc_instrs[opcode].opcode_ == opcode);
		if (opcode < ioCS_MAX)
			return &sc_instrs[opcode];
		assert(0);
		return NULL;
	}
	else
	{
		assert(sx_instrs[opcode].opcode_ == opcode);
		if (opcode < ioCX_MAX)
			return &sx_instrs[opcode];
		assert(0);
		return NULL;
	}
}

