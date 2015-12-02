#include <mrl/gen/list.h>

list list_cons(void* v, list l)
{
    list n = (list)malloc(sizeof(pair));
    list_car(n) = v;
    list_cdr(n) = l;
    return n;
}

void list_free(list l, void(*freer)(void*))
{
    list curs = l;
    while(curs)
    {
	freer(list_car(curs));
	list doomed = curs;
	curs = list_cdr(curs);
	free(doomed);
    }
}

void list_iter(list l, void*(*doer)(void*,void*), void* arg2)
{
    list curs = l;
    while(curs)
    {
	list_car(curs) = doer(list_car(curs), arg2);
	curs = list_cdr(curs);
    }
}

list list_reverse(list l)
{
    list c = l;
    l = list_cdr(c);
    list_cdr(c) = NULL;
    while(l)
    {
	list p = list_cdr(l);
	list_cdr(l) = c;
	c = l;
	l = p;
    }    
    return c;
}

list list_last(list l)
{
    list curs = l;
    while(list_cdr(curs))
	curs = list_cdr(curs);
    return curs;
}

void list_append(list a, list b)
{
    list la = list_last(a);
    list_cdr(la) = b;
}
