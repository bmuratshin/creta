// zz1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "C_driver.h"
#include "Optarg.h"

#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>

#ifndef WIN32
#define _putenv putenv
#endif 
int
get_mtime_(void)
{
#ifdef WIN32
	struct _timeb tv;
	(void)_ftime(&tv);
	return (tv.millitm);
#else
	struct timeval tv;
	(void)gettimeofday(&tv, NULL);
	return (tv.tv_usec / 100);
#endif
}

char *err_tstamp_(void)
{
	static char *months[] = { 
		"Jan", "Feb", "Mar", "Apr", "May", "Jun",
		"Jul", "Aug", "Sep", "Oct", "Nov", "Dec" 
	};
	static char str[128];
	struct tm *tmp;
	time_t currt = time(NULL);

	tmp = localtime(&currt);
	sprintf(str, "[%02d/%s/%d:%02d:%02d:%02d:%03d] ", tmp->tm_mday,
		months[tmp->tm_mon], 1900 + tmp->tm_year, tmp->tm_hour,
		tmp->tm_min, tmp->tm_sec, get_mtime_());
	return str;
}


int usage()
{
	printf("Use zz1 [-v][-f name][-V]\n");
	exit(1);
	return 0;
}
const char* versionIDstr = "zasm version 0.0.1\n";
const char* filename = "";
bool verbose = false;


int main(int argc, char* const* argv)
{
	optind = 1;
	int ch;
	while ((ch = getopt(argc, argv, "vVf:")) != EOF)
	{
		switch (ch) {
		case 'V':
			printf(versionIDstr);

			printf("Build: %s %s\n", __DATE__, __TIME__);
			printf("Path:  %s\n\n", argv[0]);

			break;

		case 'v':
			verbose = 1;
			break;

		case 'f':
		{
			filename = optarg;
			break;
		}
		case '?':
		default:
			usage();
		}
	}

	fprintf(stderr, "\nINFO: start %s\n", err_tstamp_());
	setlocale(LC_ALL, "C");
	c_driver_t drv(filename);
	if (0 > drv.parse())
		fprintf(stderr, "\nERROR(parse): %s\n", drv.error_.c_str());
	else 
		fprintf(stderr, "\nINFO: OK %s\n", err_tstamp_());
	drv.outcode();
	fprintf(stderr, "\nINFO: fin %s\n", err_tstamp_());
	return 0;
}

