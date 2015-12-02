#include <stdlib.h>
#include <mrl/gen/byteblob.h>

#define NCHUNKS 13

int main(int argc, char** argv)
{
    size_t tots = NCHUNKS * BYTEBLOB_VISCOSITY / sizeof(int);
    
    byteblob* b = byteblob_create();
 
    srand(0);
    int i;
    for(i = 0; i < tots; i++)
    {
	int r = rand() & 0xffffffff;
	if(byteblob_append(b, &r, sizeof(int)) < sizeof(int)) return -1;
    }
    
    int* buf = NULL;
    size_t size = 0;
    byteblob_join(b, (void**)&buf, &size);
    if(size < tots || !buf) return -1;
    byteblob_free(b);

    srand(0);
    for(i = 0; i < tots; i++)
	if(buf[i] != (rand() & 0xffffffff)) return -1;

    free(buf);

    return 0;
}
