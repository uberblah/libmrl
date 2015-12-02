#include <mrl/gen/pool.h>

static void* getentry(void* data, size_t size, uint32_t idx)
{
    return (void*)(((char*)data) + (size * idx));
}

pool* pool_create(size_t size, uint32_t cap)
{
    if(cap == 0) return NULL;
    //bugs could happen if we pretend to have this many
    if(cap == -1) cap = -2;
    //make sure we have space for our freelist nodes
    if(size < sizeof(uint32_t))
	size = sizeof(uint32_t);

    pool* p = (pool*)malloc(sizeof(pool));
    p->size = size;
    p->cap = cap;
    void* data = malloc(size * cap);
    p->data = data;
    uint32_t* meta = (uint32_t*)malloc(sizeof(uint32_t) * (cap + 1));
    p->meta = meta;
    p->frees = 0;
    p->count = 0;
    
    for(uint32_t i = 0; i < cap; i++)
    {
	meta[i] = 0;
	uint32_t* lst = (uint32_t*)getentry(data, size, i);
	*lst = i + 1; //if full, frees will point to index cap
    }
    
    return p;
}

bool pool_alive(pool* p)
{
    return p->data && p->meta && p->size >= sizeof(uint32_t) && p->cap;
}

phandle pool_alloc(pool* p)
{
    phandle h;
    h.idx = -1;
    h.gen = -1;
    //if the pool is dead or full, return invalid handle
    if(!pool_alive(p) || p->frees >= p->cap) return h;
    
    uint32_t idx = p->frees;
    uint32_t sz = p->size;
    void* dt = p->data;
    uint32_t* mt = p->meta;

    //what the hell? our freehead is allocated!
    if(mt[idx] & 0x1) return h;
    
    uint32_t nf = *((uint32_t*)getentry(dt, sz, idx));

    //what the hell? the next item in the freelist is invalid!
    if(nf > p->cap) return h;

    //all good! advance the freelist, update gen and off we go!
    p->frees = nf;
    mt[idx]++;
    h.gen = mt[idx];
    h.idx = idx;
    p->count++;
    
    return h; //here you go :)
}

bool pool_valid(phandle h)
{
    return h.idx != -1 && h.gen & 0x1;
}

bool pool_check(pool* p, phandle h)
{
    if(!pool_alive(p)) return false;
    if(h.idx >= p->cap) return false;
    if(p->meta[h.idx] != h.gen) return false;
    return true;
}

void* pool_next(pool* p, void* item)
{
    if(!pool_alive(p)) return NULL;
    
    void* data = p->data;
    uint32_t* meta = p->meta;
    uint32_t idx = ((char*)item - (char*)data) / p->size;
    uint32_t cap = p->cap;
    if(idx > cap) return NULL;
    uint32_t ni = (idx + 1) % cap;

    //no service for the unallocated
    if(!(meta[idx] & 0x1)) return NULL;

    //find the next allocated spot, in memory order if possible
    while(ni != idx)
    {
	if(meta[ni] & 0x1) return getentry(data, p->size, ni);
	ni = (ni + 1) % cap;
    }

    return NULL;
}

void* pool_access(pool* p, phandle h)
{
    if(!pool_check(p, h)) return NULL;
    return getentry(p->data, p->size, h.idx);
}

//free a position and push it to the freelist
bool pool_free(pool* p, phandle h)
{
    if(!pool_check(p, h)) return false;

    void* data = p->data;
    uint32_t* meta = p->meta;

    meta[h.idx]++; //mark as deallocated
    uint32_t* nf = (uint32_t*)getentry(data, p->size, h.idx);
    *nf = p->frees;
    p->frees = h.idx;
    p->count--;

    return true;
}

void pool_destroy(pool* p)
{
    if(!p) return;
    if(p->data)
    {
	free(p->data);
	p->data = NULL;
    }
    if(p->meta)
    {
	free(p->meta);
	p->meta = NULL;
    }
    if(p->size) p->size = 0;
    if(p->cap) p->cap = 0;
}

uint32_t pool_count(pool* p)
{
    return p->count;
}

uint32_t pool_iterate(pool* p, bool(*iterator)(void*, void*), void* farg2)
{
    if(!pool_alive(p)) return 0;

    void* data = p->data;
    uint32_t* meta = p->meta;
    uint32_t cap = p->cap;
    uint32_t ni = 0;
    uint32_t count = 0;

    while(ni != cap)
    {
	if(meta[ni] & 0x1)
	{
	    if(!iterator(getentry(data, p->size, ni), farg2))
		break;
	    count++;
	}
	ni++;
    }

    return count;
}

