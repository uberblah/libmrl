#include <mrl/exec/crdl.h>
#include <stdlib.h>

crdl_module crdl_load(char* filename)
{
#ifndef _WIN32
    return dlopen(filename, RTLD_LAZY);
#else
    return LoadLibrary(filename);
#endif
}

crdl_symbol crdl_get(crdl_module module, char* name)
{
#ifndef _WIN32
    char* error;
    void* symbol = dlsym(module, name);
    if((error = dlerror()) != NULL) return NULL;
    return symbol;
#else
    void* symbol = (void*)GetProcAddress(module, name);
    if(!mod) return NULL;
    return symbol;
#endif
}

void crdl_unload(crdl_module module)
{
#ifndef WIN32
    dlclose(module);
#else
    FreeLibrary(module);
#endif
}

