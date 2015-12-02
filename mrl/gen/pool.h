#ifndef MRL_POOL_H
#define MRL_POOL_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct phandle phandle;
struct phandle
{
    uint32_t idx;
    uint32_t gen;
};

typedef struct pool pool;
struct pool
{
    void* data;
    uint32_t* meta;
    size_t size;
    uint32_t cap;
    uint32_t count;
    uint32_t frees;
};

pool* pool_create(size_t size, uint32_t cap);
bool pool_alive(pool* p);
phandle pool_alloc(pool* p);
bool pool_valid(phandle h);
bool pool_check(pool* p, phandle h);
void* pool_next(pool* p, void* item);
void* pool_access(pool* p, phandle h);
bool pool_free(pool* p, phandle h);
void pool_destroy(pool* p);

uint32_t pool_count(pool* p);
uint32_t pool_iterate(pool* p, bool(*iitem)(void*,void*), void* iarg2);

#endif
