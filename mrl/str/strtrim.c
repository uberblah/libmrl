#include <mrl/str/strtrim.h>
#include <string.h>

char* strtrim(char* str, char* chars)
{
    while(strchr(chars, *str)) str++;
    char* end = str + strlen(str) - 1;
    while(strchr(chars, *end)) *(end--) = '\0';
    return str;
}
