#include <mrl/gen/pool.h>

#define CAP 1024

#define phint(p, h) *((int*)pool_access(p, h))

int main(int argc, char** argv)
{
    pool* p = pool_create(sizeof(int), CAP);
    phandle hs[CAP];
    int n = 0;

    for(; n < CAP; n++)
    {
	hs[n] = pool_alloc(p);
	if(!pool_valid(hs[n]))
	    return -1;
	phint(p, hs[n]) = n;
    }

    for(n = 0; n < CAP; n++)
	if(phint(p, hs[n]) != n) return -1;

    pool_destroy(p);

    return 0;
}
