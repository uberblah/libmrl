#include <stdlib.h>
#include <mrl/gen/list.h>

#define LSIZE 100

#define voidint(a) *((int*)(&a))

void* addn(void* a, void* b)
{
    voidint(a) += voidint(b);
    return a;
}

void nop(void* a)
{

}

#define N 5

int main(int argc, char** argv)
{
    list l = list_null;
    int i = 0;
    void* v = NULL;
    for(; i < LSIZE; i++)
    {
	voidint(v) = i;
	l = list_cons(v, l);
    }

    voidint(v) = N;
    list_iter(l, addn, v);

    list curs = l;
    for(i = LSIZE + N - 1; i >= N; i--)
    {
	v = list_car(curs);
	if(voidint(v) != i) return -1;
	curs = list_cdr(curs);
    }

    list_free(l, nop);

    return 0;
}
