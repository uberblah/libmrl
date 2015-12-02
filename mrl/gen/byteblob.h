#ifndef MRL_VECTOR_H
#define MRL_VECTOR_H

#include <mrl/gen/list.h>

#ifndef BYTEBLOB_VISCOSITY
#define BYTEBLOB_VISCOSITY 1024
#endif

typedef struct byteblob byteblob;
struct byteblob
{
    list l;
    list tail;
    size_t i;
    size_t t;
};

byteblob* byteblob_create();
size_t byteblob_append(byteblob* v, void* data, size_t size);
void byteblob_join(byteblob* v, void** out, size_t* tot);
void byteblob_free(byteblob* v);

#endif
