#include <stdlib.h>
#include <mrl/gen/list.h>

#define LSIZE 100

#define voidint(a) *((int*)(&a))

void nop(void* a)
{

}

int main(int argc, char** argv)
{
    list l1 = list_null;
    list l2 = list_null;
    int i = 0;
    void* v = NULL;
    for(; i < LSIZE / 2; i++)
    {
	voidint(v) = i;
	l1 = list_cons(v, l1);
    }
    for(; i < LSIZE; i++)
    {
	voidint(v) = i;
	l2 = list_cons(v, l2);
    }
    list_append(l2, l1);

    list curs = l2;
    for(i = LSIZE - 1; i >= 0; i--)
    {
	v = list_car(curs);
	if(voidint(v) != i) return -1;
	curs = list_cdr(curs);
    }

    list_free(l2, nop);

    return 0;
}
