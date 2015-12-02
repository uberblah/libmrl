#include <string.h>
#include <mrl/gen/alist.h>

void nop(void* a)
{

}

bool c(void* a, void* b)
{
    return !a ? !b : !b ? !a :
	(a == b) || (!strcmp((char*)a, (char*)b));
}

typedef struct smp smp;
struct smp
{
    char* k;
    char* v;
};

#define N 5

smp map[N] =
{
    {"a", "hello"},
    {"b", "blah!"},
    {"c", "guest"},
    {"uberblah", "password"},
    {"hats", "five hundred"}
};

int main(int argc, char** argv)
{
    list a = list_null;
    int i = 0;
    for(; i < N; i++)
    {
	smp* s = map + i;
	a = alist_set(a, c, (void*)s->k, (void*)s->v);
    }

    for(i = 0; i < N; i++)
    {
	smp* s = map + i;
	char* v = (char*)alist_get(a, c, (void*)s->k);
	if(strcmp(v, s->v)) return -1;
    }

    return 0;
}
