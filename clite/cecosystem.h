#include "IOUtilitys.h"
#include "warning.h"
#include "error.h"
#include "UnitTest.h"

#ifndef METACORE___CLITE_CECOSYSTEM_H
#define METACORE___CLITE_CECOSYSTEM_H

cobject(csystem64,
    CTEST* csys_test;
    cwarning* csys_w;
    cerror csys_e;
);

csystem64 cecosystem;

#endif // METACORE___CLITE_CECOSYSTEM_H