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
	unsigned      opcode_;
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
};

enum instrCXOpcodes {
	ioCXstop = 0,
	ioCXimdpush,
	ioCXlocpush,
	ioCXeval,
	ioCXcmp,
	ioCXadd,
	ioCXsub,
	ioCXmul,
	ioCXdiv,
	ioCXvarpush,
	ioCXvarpushd,
};


extern const instr_def_t *test_asm_name(const char* str, bool cf);
