#define _POSIX_C_SOURCE 200809L
#include "utils.h"
#include "cJSON.h"
#include "config.h"
#include "file_function.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void splitByDelimitter(char *originalString, char array[][MAX_TOKEN_LEN],
                       int *len, char *delimitter) {

  char *saveptr;

  int count = 0;

  char *token = strtok_r(originalString, delimitter, &saveptr);

  while (token != NULL) {

    strcpy(array[count++], token);
    // array[count++] = token; // store token

    token = strtok_r(NULL, delimitter, &saveptr);
  }

  *len = count;
}

int splitCommand(char *input, char array[][MAX_TOKEN_LEN]) {

  char buffer[1024];

  int buffIndex = 0;
  int isBackTicks = 0;
  int arrayCount = 0;

  size_t inputLen = strlen(input);

  int backtickCount = 0;
  for (int i = 0; input[i] != '\0'; i++) {
    if (input[i] == '`')
      backtickCount++;
  }

  if (backtickCount % 2 != 0) {
    printf("Error: unmatched backticks in input.\n");
    return 0;
  }

  for (size_t i = 0; i < inputLen; i++) {

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
    } else if (c != '\0') {
      buffer[buffIndex++] = c;
    }
  }

  if (buffIndex > 0) {
    buffer[buffIndex] = '\0';
    strcpy(array[arrayCount++], buffer);
  }

  return arrayCount;
}

char *pathMaker(const char *col,const char *doc) {

  char *filepath = malloc(256);

  if (!doc) {
    snprintf(filepath, 256, "%s%s", BASE_COLLECTION_PATH, col);

    return filepath;
  }

  snprintf(filepath, 256, "%s%s/%s.json", BASE_COLLECTION_PATH, col, doc);

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

void change_value(char *col, char *doc, char *key_value) {

  char splitedKey[2][MAX_TOKEN_LEN];
  int len = 0;

  splitByDelimitter(key_value, splitedKey, &len, "=");

  char *filepath = pathMaker(col, doc);

  char *textContent = readFileIfExist(filepath);

  cJSON *json = cJSON_Parse(textContent);

  patch_value(json, splitedKey[0], splitedKey[1]);

  textContent = cJSON_Print(json);

  writeFile(filepath, textContent);
}

