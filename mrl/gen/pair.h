#ifndef MRL_PAIR_H
#define MRL_PAIR_H

typedef struct pair pair;
struct pair
{
    void* car;
    void* cdr;
};

pair* pair_cons(void* a, void* b);
void pair_free(pair* p, void(*fcar)(void*), void(*fcdr)(void*));

#ifdef MRL_DEBUG
void* pair_car(pair* p);
void* pair_cdr(pair* p);
#else
#define pair_car(p) p->car
#define pair_cdr(p) p->cdr
#endif

#endif
