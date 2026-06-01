#include "micros.h"

#ifndef METACORE___CLITE_ERROR_H
#define METACORE___CLITE_WARNING_H

cobject(cerror,
    cstrptr name;
    cstrptr description;
    cstrptr file;
    cstrptr time;
    size_t line;
);


static inline cerror wrong_indexing(cstrptr description) {
    cerror w;
    w.name = "Wrong Indexing";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

static inline cerror wrong_declaration(cstrptr description) {
    cerror w;
    w.name = "Wrong declaration";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

static inline cerror wrong_construction(cstrptr description) {
    cerror w;
    w.name = "Wrong Construction";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

static inline cerror bad_input(cstrptr description) {
    cerror w;
    w.name = "Bad Input";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

static inline cerror undefined_behavior(cstrptr description) {
    cerror w;
    w.name = "Undefined Behavior";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

static inline cerror invalid_argument(cstrptr description) {
    cerror w;
    w.name = "Invalid Argument";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

static inline cerror OutOfRange(cstrptr description) {
    cerror w;
    w.name = "Out Of Range";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

static inline cerror internal_problem(cstrptr description) {
    cerror w;
    w.name = "Internal Problem";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

#endif // METACORE___CLITE_WARNING_H