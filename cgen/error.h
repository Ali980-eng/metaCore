#include "micros.h"

#ifndef METACORE___CGEN_ERROR_H
#define METACORE___CGEN_ERROR_H

#ifdef __cplusplus
#ifdef METACORE___META_HPP
namespace meta {
namespace cgen {
#endif // METACORE___META_HPP
#endif

cobject {
    cstrptr name;
    cstrptr description;
    cstrptr file;
    cstrptr time;
    size_t line;
} cerror;

static inline cerror errInit() {
    cerror err;
    err.name = NULL;
    err.description = NULL;
    err.file = NULL;
    err.time = NULL;
    err.line = 0;
    return err;
}

static inline void errPrint(cerror err) {
    printf("\n");
    printf("------------\n");
    printf("<<< ERROR >>>\n");
    printf("------------\n");
    if(err.name != NULL && strlen(err.name) != 0) {
        printf("NAME: %s \n", err.name);
    }
    if(err.description != NULL && strlen(err.description) != 0) {
        printf("DESCRIPTION: %s \n", err.description);
    }
    printf("FILE: %s \n", err.file);
    printf("TIME: %s \n", err.time);
    printf("LINE: %d \n", err.line);
    printf("------------\n");
}

static inline cerror errIndexing(cstrptr description) {
    cerror err;
    err.name = "Indexing Error";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror errDeclaration(cstrptr description) {
    cerror err;
    err.name = "Declaration Error";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror errConstruction(cstrptr description) {
    cerror err;
    err.name = "Construction Error";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror errBadInput(cstrptr description) {
    cerror err;
    err.name = "Bad Input";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror errUndefinedBehavior(cstrptr description) {
    cerror err;
    err.name = "Undefined Behavior";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror errInvalidArgument(cstrptr description) {
    cerror err;
    err.name = "Invalid Argument";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror errOutOfRange(cstrptr description) {
    cerror err;
    err.name = "Out Of Range";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror errInternalProblem(cstrptr description) {
    cerror err;
    err.name = "Internal Problem";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static void errFree(cerror* self) {
    free(self->name);
    free(self->description);
    free(self->file);
    free(self->time);
}

#ifdef __cplusplus
#ifdef METACORE___META_HPP
}}
#endif // METACORE___META_HPP
#endif

#endif // METACORE___CGEN_ERROR_H