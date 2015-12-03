#ifndef COMMANDER_STRTRIM_H
#define COMMANDER_STRTRIM_H

//a simple function for trimming chars from start and end
//WARNING: DESTRUCTIVE!!! INSERTS NULLS AT END OF STRING
char* strtrim(char* str, char* chars);

#endif
