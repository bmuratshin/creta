#pragma once


enum instrArgTypes {
	iatDAddr = 1,
	iatXAddr,
	iatCAddr,
	iatInt,
	iatLong,
	iatFloat,
	iatDouble,
	iatString,
	iatIdent,
};

struct instr_def_t {
	const char*   name_;
	unsigned      opcode_ : 31;
	unsigned      cf_ : 1;
	unsigned      nargs_;
	instrArgTypes arg_types_[4];
};

enum instrCSOpcodes {
	ioCSstop = 0,
	ioCSnop,
	ioCSexec,
	ioCScall,
	ioCSif,
	ioCSret,
	ioCSgoto,

	ioCS_MAX,
};

enum instrCXOpcodes {
	ioCXstop = 0,
	ioCXnop,
	ioCXimdpush,
	ioCXlocpush,
	ioCXlocpushd,
	ioCXeval,
	ioCXcmp,
	ioCXadd,
	ioCXneg,
	ioCXsub,

	ioCXmul,
	ioCXdiv,
	ioCXvarpush,
	ioCXvarpushd,
	ioCXeq,
	ioCXne,
	ioCXgt,
	ioCXge,
	ioCXlt,
	ioCXle,

	ioCXdec,
	ioCXinc,
	ioCXpostdec,
	ioCXpostinc,
	ioCXpreand,
	ioCXand,
	ioCXpreor,
	ioCXor,
	ioCXnot,
	ioCXband,

	ioCXbor,
	ioCXxor,
	ioCXbnot,
	ioCXassign,
	ioCXpop,

	ioCX_MAX,
};


extern const instr_def_t *test_asm_name(const char* str, bool cf);

constexpr int opcode2ix(int opcode, bool cf)
{
	assert(opcode >= 0);
	return (opcode << 1) + cf ? 1 : 0;
}

extern constexpr const instr_def_t* get_asm_instr(int opix);
extern constexpr const instr_def_t* get_asm_instr(int opcode, bool cf);
