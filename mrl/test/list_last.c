#include <stdlib.h>
#include <mrl/gen/list.h>

#define LSIZE 100

#define voidint(a) *((int*)(&a))

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

    list last = list_last(l);
    v = list_car(last);
    if(voidint(v) != 0) return -1;

    list_free(l, nop);

    return 0;
}
