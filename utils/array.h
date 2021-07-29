/**
 * @author zouxiaoliang
 * @date 2021/7/29
 */
#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define _C_ARRAY_NEW(Type)                                                     \
    typedef struct {                                                           \
        Type* data;                                                            \
        size_t length;                                                         \
        size_t allocated;                                                      \
    } ARRAY_##Type;

#define _C_ARRAY_INIT(Type)                                                    \
    static ARRAY_##Type* Type##_init(size_t default_allocated) {               \
        ARRAY_##Type* array = (ARRAY_##Type*)calloc(1, sizeof(ARRAY_##Type));  \
        if (NULL == array) {                                                   \
            return NULL;                                                       \
        }                                                                      \
        array->data =                                                          \
            (Type*)realloc(array->data, default_allocated * sizeof(Type));     \
        array->length = 0;                                                     \
        array->allocated = default_allocated;                                  \
        return array;                                                          \
    }

#define _C_ARRAY_FINI(Type)                                                    \
    static void Type##_fini(ARRAY_##Type* array) {                             \
        if (NULL != array) {                                                   \
            if (NULL != array->data) {                                         \
                free(array->data);                                             \
            }                                                                  \
            free(array);                                                       \
        }                                                                      \
    }                                                                          \
                                                                               \
    static void Type##_fini_with_callback(ARRAY_##Type* array,                 \
                                          void (*free_value)(Type)) {         \
        if (NULL != array) {                                                   \
            if (NULL != array->data) {                                         \
                size_t i = 0;                                                  \
                for (i = 0; i < array->length; ++i) {                          \
                    free_value(array->data[i]);                               \
                }                                                              \
                free(array->data);                                             \
            }                                                                  \
            free(array);                                                       \
        }                                                                      \
    }

#define _C_ARRAY_PUSH(Type, increase)                                          \
    static bool Type##_append(ARRAY_##Type* array, Type value) {               \
        if (NULL == array) {                                                   \
            return false;                                                      \
        }                                                                      \
        if (array->length == array->allocated) {                               \
            array->data = (Type*)realloc(                                      \
                array->data, (array->allocated + increase) * sizeof(Type));    \
            array->allocated += increase;                                      \
        }                                                                      \
        array->data[array->length] = value;                                    \
        array->length += 1;                                                    \
        return true;                                                           \
    }

#define C_ARRAY_VAL(array, id) (array->data[id])

#define C_ARRAY(Type)                                                          \
    _C_ARRAY_NEW(Type)                                                         \
    _C_ARRAY_INIT(Type)                                                        \
    _C_ARRAY_FINI(Type)                                                        \
    _C_ARRAY_PUSH(Type, 8)

#define C_ARRAY_WITH_INCREASE(Type, increase)                                  \
    _C_ARRAY_NEW(Type)                                                         \
    _C_ARRAY_INIT(Type)                                                        \
    _C_ARRAY_FINI(Type)                                                        \
    _C_ARRAY_PUSH(Type, increase)

/** example.c

#include "array.h"
#include <inttypes.h>
#include <stdio.h>

typedef struct {
    int v;
} Value, *ValuePtr;

void free_value(Value* v) {
    free(v);
}

C_ARRAY(Value);
C_ARRAY(ValuePtr);

int main(int argc, char* argv[]) {
    ARRAY_ValuePtr* vptr_l = ValuePtr_init(12000);
    int i = 0;
    for (i = 0; i < 11234; ++i) {
        Value* v = calloc(1, sizeof(Value));
        v->v = i;
        ValuePtr_append(vptr_l, v);
    }

    printf("vptr_l, allocated: %zu, length: %zu\n",
           vptr_l->allocated,
           vptr_l->length);
    for (i = 0; i < vptr_l->length; ++i) {
        printf(" -- %d\n", C_ARRAY_VAL(vptr_l, i)->v);
    }
    ValuePtr_fini_with_callback(vptr_l, free_value);

    ARRAY_Value* v_l = Value_init(12000);
    for (i = 0; i < 11234; ++i) {
        Value v;
        v.v = i;
        Value_append(v_l, v);
    }

    printf("vl, allocated: %zu, length: %zu\n", v_l->allocated, v_l->length);
    for (i = 0; i < v_l->length; ++i) {
        printf(" -- %d\n", C_ARRAY_VAL(v_l, i).v);
    }
    Value_fini(v_l);

    return 0;
}
*/
#endif // ARRAY_H
