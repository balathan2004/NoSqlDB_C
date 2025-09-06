#ifndef UTILS_H
#define UTILS_H


void splitCommand(char *originalString, char array[][MAX_TOKEN_LEN],int *len);
    

void splitByDelimitter(char *originalString, char array[][MAX_TOKEN_LEN],int *len,char *delimitter);


// void readFile(char *filePath,char *text);


void patch_value(cJSON *json, char *key, char *value);


void writeFile(char *filepath,char *value);


char * pathMaker(char *col, char *doc );

#endif