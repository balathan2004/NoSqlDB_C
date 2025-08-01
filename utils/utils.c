#define _POSIX_C_SOURCE 200809L
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void split(char *originalString, char **array, int *len,char *delimitter) {

  char *saveptr;

  int count = 0;

  char *token = strtok_r(originalString, delimitter, &saveptr);

  while (token != NULL) {
    array[count++] = token; // store token

    token = strtok_r(NULL, delimitter, &saveptr);
  }

  *len = count;
}

void readFile(char *filePath,char *text) {
  FILE *fp = fopen(filePath, "rb");

  if (fp == NULL) {
    perror("Error opening file"); // perror gives a more detailed error message
    fprintf(stderr, "Could not open file at path: %s\n", filePath);
    // Indicate an error
  }

  fseek(fp, 0, SEEK_END);

  long len = ftell(fp);

  rewind(fp);

  char *buffer = malloc(len + 1);

  if (!buffer) {
    fprintf(stderr, "malloc failed\n");
    fclose(fp);
    return;
  }

  fread(buffer, 1, len, fp);
  buffer[len] = '\0';

  strcpy(text,buffer);

  free(buffer);
  fclose(fp);
}