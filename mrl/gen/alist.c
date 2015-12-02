#include <mrl/gen/alist.h>

list alist_set(list a, alist_cmp c, void* k, void* v)
{
    list orig = a;

    while(true)
    {
	if(!a)
	{
	    pair* d = (pair*)malloc(sizeof(pair));
	    pair_car(d) = k;
	    pair_cdr(d) = v;
	    return list_cons(d, orig);
	}
	
	pair* data = (pair*)list_car(a);
	if(c(k, pair_car(data)))
	{
	    pair_cdr(data) = v;
	    return orig;
	}
	
	a = list_cdr(a);
    }
}

pair* alist_ref(list a, alist_cmp c, void* k)
{
    while(a)
    {
	pair* data = (pair*)list_car(a);
	if(c(k, pair_car(data)))
	    return data;
	a = list_cdr(a);
    }
    
    return NULL;
}

void* alist_get(list a, alist_cmp c, void* k)
{
    return list_cdr(alist_ref(a, c, k));
}
