#ifndef UTILS_H
#define UTILS_H

void split(char *originalString, char **array,int *len,char* delimitter) ;

void readFile(char *filePath,char *text);


void patch_value(cJSON *json, char *key, char *value);


void writeFile(char *filepath,char *value);


char * pathMaker(char *col, char *doc );

#endif