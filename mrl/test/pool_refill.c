#include <mrl/gen/pool.h>

#define CAP 1024

#define phint(p, h) *((int*)pool_access(p, h))

int main(int argc, char** argv)
{
    pool* p = pool_create(sizeof(int), CAP);
    phandle hs[CAP];
    int n = 0;

    //allocate the whole pool
    for(; n < CAP; n++)
    {
	hs[n] = pool_alloc(p);
	if(!pool_valid(hs[n]))
	    return -1;
	phint(p, hs[n]) = n;
    }

    //make sure we've allocated everything
    phandle over = pool_alloc(p);
    if(pool_valid(over)) return -1;

    //make sure our values are all correct
    for(n = 0; n < CAP; n++)
	if(phint(p, hs[n]) != n) return -1;

    //free every even-indexed item
    for(n = 0; n < CAP; n += 2)
	if(!pool_free(p, hs[n])) return -1;
    
    //reallocate those items, with new values
    for(n = 0; n < CAP; n += 2)
	if(!pool_valid(hs[n] = pool_alloc(p))) return -1;
	else phint(p, hs[n]) = CAP - n;
    
    //make sure our new indices took
    for(n = 0; n < CAP; n++)
	if(phint(p, hs[n]) != ((n & 1) ? n : CAP - n)) return -1;

    //free the whole pool
    for(n = 0; n < CAP; n++)
	if(!pool_free(p, hs[n])) return -1;

    //try reallocating the whole pool
    for(n = 0; n < CAP; n++)
	if(!pool_valid(hs[n] = pool_alloc(p))) return -1;
	else phint(p, hs[n]) = CAP - n;

    //check new values
    for(n = 0; n < CAP; n++)
	if(phint(p, hs[n]) != CAP - n) return -1;

    //all done!
    pool_destroy(p);
    return 0;
}
