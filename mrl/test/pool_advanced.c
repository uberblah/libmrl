#include <mrl/gen/pool.h>
#include <stdio.h>

#define CAP 1024

#define phint(p, h) *((int*)pool_access(p, h))

bool summer(void* item, void* ext)
{
    int* i = (int*)item;
    int* e = (int*)ext;
    if(*i >= (CAP / 2)) return false;
    *e += *i;
    return true;
}

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

    phandle over = pool_alloc(p);
    if(pool_valid(over))
	return -1;

    for(n = 0; n < CAP; n += 5)
	if(!pool_free(p, hs[n]))
	    return -1;
    
    bool have[CAP];
    for(n = 0; n < CAP; n++) have[n] = false;
    void* head = pool_access(p, hs[1]);
    if(!head)
	return -1;
    void* curs = head;
    
    do
    {
	have[*((int*)curs)] = true;
	curs = pool_next(p, curs);
	if(!curs || !head)
	    return -1;
    }
    while(head != curs);

    for(n = 0; n < CAP; n++)
	if(((n % 5) != 0) ^ have[n])
	    return -1;

    int sum = 0;
    pool_iterate(p, summer, (void*)&sum);

    int altsum = 0;
    for(n = 0; n < (CAP / 2); n++)
	if((n % 5) != 0) altsum += n;

    if(sum != altsum)
	return -1;
    
    pool_destroy(p);

    return 0;
}
