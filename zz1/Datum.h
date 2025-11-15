#ifndef _Datum_h
#define _Datum_h

union Datum {
	int              ival;
	int64_t          lval;
	double           dval;
	wchar_t         *Sval;
	const void      *Sym;
	Datum           *Dval;

	void Zero(){ memset(this, 0, sizeof(Datum)); };
};

#endif /* _Datum_h */
