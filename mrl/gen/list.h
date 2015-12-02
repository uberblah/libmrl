#ifndef MRL_LIST_H
#define MRL_LIST_H

#include <stdlib.h>
#include <mrl/gen/pair.h>

typedef pair* list;
#define list_null NULL

list list_cons(void* v, list l);
void list_free(list l, void(*freer)(void*));
void list_iter(list l, void*(*doer)(void*,void*), void* arg2);
list list_reverse(list l);
list list_last(list l);
void list_append(list a, list b);

#define list_car(l) (l->car)
#define list_cdr(l) (l->cdr)

#endif
