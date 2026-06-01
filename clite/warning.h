#include "micros.h"

#ifndef METACORE___CLITE_WARNING_H
#define METACORE___CLITE_WARNING_H

cobject(cwarning,
    cstrptr name;
    cstrptr description;
    cstrptr file;
    cstrptr time;
    size_t line;
);

static inline cwarning wrong_indexing(cstrptr description) {
    cwarning w;
    w.name = "Wrong Indexing";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

static inline cwarning wrong_declaration(cstrptr description) {
    cwarning w;
    w.name = "Wrong declaration";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

static inline cwarning wrong_construction(cstrptr description) {
    cwarning w;
    w.name = "Wrong Construction";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

static inline cwarning bad_input(cstrptr description) {
    cwarning w;
    w.name = "Bad Input";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

static inline cwarning undefined_behavior(cstrptr description) {
    cwarning w;
    w.name = "Undefined Behavior";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

static inline cwarning invalid_argument(cstrptr description) {
    cwarning w;
    w.name = "Invalid Argument";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

static inline cwarning OutOfRange(cstrptr description) {
    cwarning w;
    w.name = "Out Of Range";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

static inline cwarning internal_problem(cstrptr description) {
    cwarning w;
    w.name = "Internal Problem";
    w.description = description;
    w.file = __FILE_NAME__;
    w.time = __TIME__;
    w.line = __LINE__;
    return w;
}

#endif // METACORE___CLITE_WARNING_H