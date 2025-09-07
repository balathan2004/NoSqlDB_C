#ifndef FILE_FUNCTION_H
#define FILE_FUNCTION_H
#include<stdio.h>

int isFileExist(char *filepath);

void createFile(char *filepath);

int isFolderExists(char *filepath);

void createFolder(char *filpath);


int createFolderRecursive(char *filepath);

FILE *returnFilePathExists(char *filepath,char *mode);

char *readFileIfExist(char *filepath);


void writeFile(char *filepath,char *value);

#endif
