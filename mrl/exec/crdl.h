#ifndef UGL_CRDL_H
#define UGL_CRDL_H

//purpose: to provide a cross-platform solution for loading modules,
//    and for getting symbols from those modules.

#ifndef _WIN32
#include <dlfcn.h>
typedef void* crdl_module;
#else
#include <direct.h>
#include <windows.h>
typedef HINSTANCE crdl_module;
#endif

typedef void* crdl_symbol;

crdl_module crdl_load(char* filename);
crdl_symbol crdl_get(crdl_module module, char* name);
void crdl_unload(crdl_module module);

#endif

