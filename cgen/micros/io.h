#include <stdio.h>

#ifndef METACORE___CGEN_MICROS_IO_H
#define METACORE___CGEN_MICROS_IO_H

    #define nl '\n'

    #define tab '\t'

    #define cprint(output) \
        printf(output)

    #define cprintln(output) \
        printf(output);      \
        printf(nl)

    #define cprint_if(condition, output) \
        if(condition) printf(output)

    #define cprintln_if(condition, output) \
        if(condition) printf(output);      \
        printf(nl)

#endif // METACORE___CGEN_MICROS_IO_H