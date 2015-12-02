#include <stdlib.h>
#include <string.h>
#include <mrl/gen/byteblob.h>

byteblob* byteblob_create()
{
    byteblob* v = (byteblob*)malloc(sizeof(byteblob));
    list l = (list)malloc(sizeof(list));
    v->l = l;
    v->tail = l;
    list_car(l) = malloc(BYTEBLOB_VISCOSITY);
    list_cdr(l) = NULL;
    v->i = 0;
    v->t = 0;
    return v;
}

size_t byteblob_append(byteblob* v, void* data, size_t size)
{
    size_t copied = 0;
    void* b = list_car(v->tail);
    while(copied < size)
    {
	if(v->i >= BYTEBLOB_VISCOSITY)
	{
	    b = malloc(BYTEBLOB_VISCOSITY);
	    if(!b) return copied;
	    list l = v->tail;
	    list_cdr(l) = (list*)malloc(sizeof(list));
	    l = list_cdr(l);
	    list_car(l) = b;
	    list_cdr(l) = NULL;
	    v->tail = l;
	    v->i = 0;
	}
	
	size_t rb = BYTEBLOB_VISCOSITY - v->i;
	size_t rc = size - copied;
	size_t n = rb <= rc ? rb : rc;
	memcpy(((char*)b) + v->i, ((char*)data) + copied, n);
	v->i += n;
	v->t += n;
	copied += n;
    }

    return copied;
}

void byteblob_join(byteblob* v, void** out, size_t* tot)
{
    char* b = (char*)malloc(v->t + 1);
    size_t copied = 0;
    list curr = v->l;
    while(curr && copied < v->t)
    {
	size_t r = v->t - copied;
	size_t n = r < BYTEBLOB_VISCOSITY ? r : BYTEBLOB_VISCOSITY;
	memcpy(b + copied, list_car(curr), n);
	copied += n;
	curr = list_cdr(curr);
    }
    b[v->t] = '\0';
    *out = (void*)b;
    *tot = v->t;
}

void byteblob_free(byteblob* v)
{
    list head = v->l;
    while(head)
    {
	list doomed = head;
	head = list_cdr(head);
	free(list_car(doomed));
	free(doomed);
    }
    free(v);
}
