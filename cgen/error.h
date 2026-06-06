#include "micros.h"

#ifndef METACORE___META_CGEN_ERROR_H
#define METACORE___META_CGEN_ERROR_H

#ifdef __cplusplus
    #ifdef METACORE___META_HPP
    namespace meta {
    namespace cgen {
    #endif // METACORE___META_HPP
#endif

cobject(cerror,
    cstrptr name;
    cstrptr description;
    cstrptr file;
    cstrptr time;
    size_t line;
);

static inline cerror cerror_init() {
    cerror err;
    err.name = NULL;
    err.description = NULL;
    err.file = NULL;
    err.time = NULL;
    err.line = 0;
    return err;
}

static inline void printError(cerror err) {
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

static inline cerror indexing_error(cstrptr description) {
    cerror err;
    err.name = "Indexing Error";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror declaration_error(cstrptr description) {
    cerror err;
    err.name = "Declaration Error";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror construction_error(cstrptr description) {
    cerror err;
    err.name = "Construction Error";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror bad_input_error(cstrptr description) {
    cerror err;
    err.name = "Bad Input";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror undefined_behavior_error(cstrptr description) {
    cerror err;
    err.name = "Undefined Behavior";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror invalid_argument_error(cstrptr description) {
    cerror err;
    err.name = "Invalid Argument";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror OutOfRange_error(cstrptr description) {
    cerror err;
    err.name = "Out Of Range";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror internal_problem_error(cstrptr description) {
    cerror err;
    err.name = "Internal Problem";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static void free_cerror(cerror* self) {
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

#endif // METACORE___META_CGEN_ERROR_H