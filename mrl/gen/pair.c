#include <stdlib.h>
#include <mrl/gen/pair.h>

pair* pair_cons(void* a, void* b)
{
    pair* p = (pair*)malloc(sizeof(pair));
    p->car = a;
    p->cdr = b;
    return p;
}

void pair_free(pair* p, void(*fcar)(void*), void(*fcdr)(void*))
{
    fcar(pair_car(p));
    fcdr(pair_cdr(p));
    free(p);
}

#ifdef MRL_DEBUG

void* pair_car(pair* p)
{
    return p->car;
}

void* pair_cdr(pair* p)
{
    return p->cdr;
}

#endif
