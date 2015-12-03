#include <mrl/str/strsplit.h>
#include <string.h>

list strsplit(char* str, char* chars)
{
    list parts = list_null;
    char* part = strtok(str, chars);
    while(part)
    {
	//prepend the token to our list
	parts = list_cons((void*)part, parts);
	//get a new token
	part = strtok(NULL, chars);
    }
    return list_reverse(parts);
}
