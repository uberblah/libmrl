#ifndef MRL_ALIST_H
#define MRL_ALIST_H

#include <mrl/gen/list.h>
#include <stdbool.h>

typedef bool(*alist_cmp)(void*,void*);

list alist_set(list a, alist_cmp c, void* k, void* v);
pair* alist_ref(list a, alist_cmp c, void* k);
void* alist_get(list a, alist_cmp c, void* k);

#endif
