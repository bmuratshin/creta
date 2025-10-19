#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string>

#include "Optarg.h"
#include "gramm/zasm_driver.h"

int usage()
{
    printf("Use zasm [-v][-f name][-V]\n");
    exit(1);
    return 0;
}

const char *versionIDstr = "zasm version 0.0.1\n";
const char* filename = "";
bool verbose = false;

int main(int argc, char* const *argv)
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

    std::string text;
    {
        FILE* fl = fopen(filename, "r");
        if (NULL == fl) {
            fprintf(stderr, "\n	ERROR: can't open input file '%s;\n", filename);
            return -1;
        }
        char buf[4096];
        for (;;)
        {
            char* tmp;
            tmp = fgets(buf, sizeof(buf) / sizeof(buf[0]), fl);
            if (NULL == tmp)
                break;
            text += buf;
        }
        fclose(fl);
        fl = NULL;
    }

    setlocale(LC_ALL, "C");
    zasm_driver_t drv(filename);
    if (0 > drv.parse(text.c_str()))
        fprintf(stderr, "\nERROR(parse): %s\n", drv.error_.c_str());

    return 0;
}

