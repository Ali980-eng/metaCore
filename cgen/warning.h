#include "micros.h"

#ifndef METACORE___META_CGEN_WARNING_H
#define METACORE___META_CGEN_WARNING_H

#ifdef __cplusplus
    #ifdef METACORE___META_HPP
    namespace meta {
    namespace cgen {
    #endif // METACORE___META_HPP
#endif


size_t cwarningCounter = 0;

cobject(cwarning,
    cstrptr name;
    cstrptr description;
    cstrptr file;
    cstrptr time;
    size_t line;
    size_t number;
);

static inline cwarning cwarning_init() {
    cwarning w;
    w.name = NULL;
    w.description = NULL;
    w.file = NULL;
    w.time = NULL;
    w.line = 0;
    w.number = cwarningCounter;
    cwarningCounter++;
    return w;
}

static inline void printWarning(cwarning w) {
    printf("\n");
    printf("------------\n");
    printf("<<< WARNING >>>\n");
    printf("------------\n");
    if(w.name != NULL && strlen(w.name) != 0) {
        printf("NAME: %s \n", w.name);
    }
    if(w.description != NULL && strlen(w.description) != 0) {
        printf("DESCRIPTION: %s \n", w.description);
    }
    printf("FILE: %s \n", w.file);
    printf("TIME: %s \n", w.time);
    printf("LINE: %d \n", w.line);
    printf("NUMBER: %d \n", w.number);
    printf("------------\n");
}

static inline cwarning wrong_indexing(cstrptr description) {
    cwarning w;
    w.name = "Wrong Indexing";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    w.number = cwarningCounter;
    cwarningCounter++;
    return w;
}

static inline cwarning wrong_declaration(cstrptr description) {
    cwarning w;
    w.name = "Wrong declaration";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    w.number = cwarningCounter;
    cwarningCounter++;
    return w;
}

static inline cwarning wrong_construction(cstrptr description) {
    cwarning w;
    w.name = "Wrong Construction";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    w.number = cwarningCounter;
    cwarningCounter++;
    return w;
}

static inline cwarning bad_input(cstrptr description) {
    cwarning w;
    w.name = "Bad Input";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    w.number = cwarningCounter;
    cwarningCounter++;
    return w;
}

static inline cwarning undefined_behavior(cstrptr description) {
    cwarning w;
    w.name = "Undefined Behavior";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    w.number = cwarningCounter;
    cwarningCounter++;
    return w;
}

static inline cwarning invalid_argument(cstrptr description) {
    cwarning w;
    w.name = "Invalid Argument";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    w.number = cwarningCounter;
    cwarningCounter++;
    return w;
}

static inline cwarning OutOfRange(cstrptr description) {
    cwarning w;
    w.name = "Out Of Range";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    w.number = cwarningCounter;
    cwarningCounter++;
    return w;
}

static inline cwarning internal_problem(cstrptr description) {
    cwarning w;
    w.name = "Internal Problem";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    w.number = cwarningCounter;
    cwarningCounter++;
    return w;
}

static void free_cwarning(cwarning* self) {
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

#endif // METACORE___META_CGEN_WARNING_H