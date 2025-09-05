#define _POSIX_C_SOURCE 200809L
#include "../libs/cJSON/cJSON.h"
#include "utils.h"
#include "../config/config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>



void splitByDelimitter(char *originalString, char array[][MAX_TOKEN_LEN], int *len, char *delimitter) {

  char *saveptr;

  int count = 0;

  char *token = strtok_r(originalString, delimitter, &saveptr);

  while (token != NULL) {

    strcpy(array[count++],token);
    // array[count++] = token; // store token

    token = strtok_r(NULL, delimitter, &saveptr);
  }

  *len = count;
}


void splitCommand(char *input, char  array[][MAX_TOKEN_LEN],int *len) {

  char buffer[1024];

  int buffIndex = 0;
  int isBackTicks = 0;
  int arrayCount = 0;

  int backtickCount = 0;
  for (int i = 0; input[i] != '\0'; i++) {
    if (input[i] == '`')
      backtickCount++;
  }


  if (backtickCount % 2 != 0) {
    printf("Error: unmatched backticks in input.\n");
    return;
  }

  for (int i = 0; i < strlen(input); i++) {

    char c = input[i];

    if (c == '`') {
      isBackTicks = !isBackTicks;

      continue;
    }

    if (!isBackTicks && (c == ' ' || c == '\0')) {
      buffer[buffIndex] = '\0';
      if (buffIndex > 0) {
        strcpy(array[arrayCount++], buffer);
        // printf("[%s]", buffer);
        buffIndex = 0;
      }
    } else if(c!='\0') {
      buffer[buffIndex++] = c;
    }

    

  
  }


    if (buffIndex > 0) {
        buffer[buffIndex] = '\0';
        strcpy(array[arrayCount++], buffer);
    }

 *len=arrayCount;
  
}




void readFile(char *filePath, char *text) {
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

  strcpy(text, buffer);

  free(buffer);
  fclose(fp);
}

char *pathMaker(char *col, char *doc) {

  const char *BASE_COLLECTION_PATH = "collections/";

  char *filepath = malloc(1024);

  snprintf(filepath, 1024, "%s%s/%s.json", BASE_COLLECTION_PATH, col, doc);

  return filepath;
}

void patch_value(cJSON *json, char *key, char *value) {

  cJSON *name = cJSON_GetObjectItemCaseSensitive(json, key);

  if (!cJSON_IsString(name) || name->valuestring == NULL) {
    printf("seems key is missing \n");
    return;
  }

  char *oldName = malloc(sizeof(name->valuestring));

  strcpy(oldName, name->valuestring);

  cJSON_SetValuestring(name, value);
}

void writeFile(char *filepath, char *value) {

  FILE *file = fopen(filepath, "w");

  if (file == NULL || strlen(value) < 0) {
    printf("File isnt exist\n");

    return;
  }
  fprintf(file, value);
  fclose(file);
}