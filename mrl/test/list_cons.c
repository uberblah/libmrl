#include <stdlib.h>
#include <mrl/gen/list.h>

#define LSIZE 100

void nop(void* a)
{

}

int main(int argc, char** argv)
{
    list l = list_null;
    int i = 0;
    void* v = NULL;
    for(; i < LSIZE; i++)
    {
	*((int*)(&v)) = i;
	l = list_cons(v, l);
    }

    list curs = l;
    for(i = LSIZE - 1; i >= 0; i--)
    {
	v = list_car(curs);
	if(*((int*)(&v)) != i) return -1;
	curs = list_cdr(curs);
    }

    list_free(l, nop);

    return 0;
}
