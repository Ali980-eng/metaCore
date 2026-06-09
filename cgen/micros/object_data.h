#include <stdint.h>

#ifndef METACORE___CGEN_MICROS_OBJECT_DATA_H
#define METACORE___CGEN_MICROS_OBJECT_DATA_H

    /// Section attribute for placing data in a specific section of memory
    #define DATA_SEC __attribute__((section(".cdata_space")))

    /// Boolean definitions
    #define cbool(name, val) const _Bool name = val;

    /// 8-bit integer definitions
    #define cchar(name, val) const char name = val;

    /// 16-bit integer definitions
    #define cshort(name, val) const short name = val;

    /// 32-bit integer definitions
    #define cint(name, val) const int name = val;

    /// 32-bit floating-point definitions
    #define cfloat(name, val) const float name = val;

    /// 64-bit floating-point definitions
    #define cdouble(name, val) const double name = val;

    /// 64-bit integer definitions
    #define clong(name, val) const long name = val;

    /// 64-bit integer definitions
    #define cint8(name, val) const int8_t name = val;

    /// 16-bit integer definition
    #define cint16(name, val) const int16_t name = val;

    /// 32-bit integer definition
    #define cint32(name, val) const int32_t name = val;

    /// 8-bit unsigned integer definition
    #define cuint8(name, val) const uint8_t name = val;

    /// 16-bit unsigned integer definition
    #define cuint16(name, val) const uint16_t name = val;

    /// 32-bit unsigned integer definition
    #define cuint32(name, val) const uint32_t name = val;

    /// String definitions
    #define cstring(name, val) const char name[] = val;

    /// In strict mode, we can use 'const auto' for type inference. In non-strict mode, we fall back to 'const __typeof__' for compatibility.
    #ifndef STRICT_MODE

    /// In non-strict mode, we use 'const __typeof__' to infer the type of the value.
    #define cauto(name, val) const auto name = val;

    /// In non-strict mode, we use 'const __typeof__' to infer the type of the value.
    #define cdynamic(name, val) const __typeof__(val) name = val;

    #endif // STRICT_MODE

    /// 64-bit integer definitions with alignment for 64-bit platforms
    #if defined(_WIN64)

    /// On Windows 64-bit, __int64 is already 8-byte aligned, so no special attribute is needed.
    #define cint64(name, val) const int64_t name __attribute__((aligned(8))) = val;

    /// On Windows 64-bit, __int64 is already 8-byte aligned, so no special attribute is needed.
    #define cuint64(name, val) const uint64_t name __attribute__((aligned(8))) = val;

    #endif // _WIN64

    /// Array definitions
    #define carray_i32(name, ...) const int32_t name[] = {__VA_ARGS__};

    /// Array definitions
    #define carray_f64(name, ...) const double name[] = {__VA_ARGS__};

    // allows for using in regular libraries without previnting basic language features
    #ifndef ALLOW_LOGIC_MODE

    /// Function definitions
    #define void ERROR_FUNCTIONS_NOT_ALLOWED

    /// Control flow definitions
    #define if ERROR_LOGIC_NOT_ALLOWED

    /// Loop definitions
    #define for ERROR_LOGIC_NOT_ALLOWED

    /// Switch-case definitions
    #define do ERROR_LOGIC_NOT_ALLOWED

    /// Switch-case definitions
    #define switch ERROR_LOGIC_NOT_ALLOWED

    /// Jump definitions
    #define while ERROR_LOGIC_NOT_ALLOWED

    /// Structure definitions
    #define struct ERROR_STRUCT_NOT_ALLOWED

    /// Union definitions
    #define register ERROR_NOT_ALLOWED

    /// Type definitions
    #define goto ERROR_LOGIC_NOT_ALLOWED

    /// Type definitions
    #define typedef ERROR_TYPE_NOT_ALLOWED

    #endif // ALLOW_LOGIC_MODE

#endif // METACORE___CGEN_MICROS_OBJECT_DATA_H