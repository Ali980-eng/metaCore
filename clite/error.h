#include "micros.h"

#ifndef METACORE___CLITE_ERROR_H
#define METACORE___CLITE_ERROR_H

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

static inline cerror wrong_indexing(cstrptr description) {
    cerror err;
    err.name = "Wrong Indexing";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror wrong_declaration(cstrptr description) {
    cerror err;
    err.name = "Wrong declaration";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror wrong_construction(cstrptr description) {
    cerror err;
    err.name = "Wrong Construction";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror bad_input(cstrptr description) {
    cerror err;
    err.name = "Bad Input";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror undefined_behavior(cstrptr description) {
    cerror err;
    err.name = "Undefined Behavior";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror invalid_argument(cstrptr description) {
    cerror err;
    err.name = "Invalid Argument";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror OutOfRange(cstrptr description) {
    cerror err;
    err.name = "Out Of Range";
    err.description = description;
    err.file = __FILE_NAME__;
    err.time = __TIME__;
    err.line = __LINE__;
    return err;
}

static inline cerror internal_problem(cstrptr description) {
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

#endif // METACORE___CLITE_ERROR_H