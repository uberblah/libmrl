#ifndef COMMANDER_STRSPLIT_H
#define COMMANDER_STRSPLIT_H

#include <mrl/gen/list.h>

//a simple utility using strtok to split a string across certain chars
//WARNING!!!!!: DESTRUCTIVE! INSERTS NULL CHARS IN STR
list strsplit(char* str, char* chars);

#endif
