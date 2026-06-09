
#ifndef METACORE___CGEN_MICROS_STRUCTURE_H
#define METACORE___CGEN_MICROS_STRUCTURE_H

    #define MAIN   \
        int main() {

    #define RET(retval)         \
            return (int)retval; }

    #define cobject typedef struct 

    #define cenum typedef enum

    #define jump(label) goto label

    #define jump_if(condition, label) \
        if (condition) goto label

    #ifdef __cplusplus

        #include <string>
        #include <functional>
        #include <vector>
        #include <queue>

        #define object class

        #define func std::function
        
        #define vec std::vector

        #define str std::string

        #define que std::queue

        #define lambda_func(capture_clause, parameters, return_type, script) \
            [capture_clause] parameters -> return_type { script }

    #endif // __cplusplus

#endif // METACORE___CGEN_MICROS_STRUCTURE_H