#ifndef _optarg_h
#define _optarg_h

extern int opterr,	optind, optopt;
extern char *optarg;

extern int
getopt(int nargc, char *const nargv[], const char *ostr);

#endif
