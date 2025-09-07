#ifndef UTILS_H
#define UTILS_H

#include "config.h"
#include "cJSON.h"


int splitCommand(char *originalString, char array[][MAX_TOKEN_LEN]);
    

void splitByDelimitter(char *originalString, char array[][MAX_TOKEN_LEN],int *len,char *delimitter);



void patch_value(cJSON *json, char *key, char *value);




char *pathMaker(char *col, char *doc );

#endif