#ifndef UTILS_H
#define UTILS_H

#include "config.h"
#include "cJSON.h"


int splitCommand(char *originalString, char array[][MAX_TOKEN_LEN]);
    

void splitByDelimitter(char *originalString, char array[][MAX_TOKEN_LEN],int *len,char *delimitter);



void patch_value(cJSON *json, char *key, char *value);




char *pathMaker(const char *col,const char *doc );

void update_doc(const char *filepath,char *textContent);


#endif