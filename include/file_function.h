#ifndef FILE_FUNCTION_H
#define FILE_FUNCTION_H
#include<stdio.h>

int isFileExist(char *filepath);



int isFolderExists(const char *filepath);

int createFolder(char *filpath);


int createFolderRecursive(char *filepath);

FILE *returnFilePathExists(char *filepath,char *mode);

char *readFileIfExist(char *filepath);


void writeFile(char *filepath,char *value);

#endif
