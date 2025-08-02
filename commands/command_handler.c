#define _POSIX_C_SOURCE 200809L
#include "command_handler.h"
#include "../libs/cJSON/cJSON.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const char *BASE_COLLECTION_PATH = "collections/";

char fullPath[256];
struct stat st = {0};

const int ARGLEN = 3;

void acceptCommand() {

  char command[256];

  printf(">>> ");

  fgets(command, sizeof(command), stdin);

  command[strcspn(command, "\n")] = 0;

  int len = 0;
  char *tokens[ARGLEN];

  split(command, tokens, &len, " ");

  if (len == 2) {
    if (!strcmp(tokens[0], "create_col") && strlen(tokens[1]) > 0) {

      create_collection(tokens[1]);
    }
  }
  if (len == 3) {

    if (!strcmp(tokens[0], "create_doc") && strlen(tokens[1]) > 0 &&
        strlen(tokens[2]) > 0) {

      create_document(tokens[1], tokens[2], NULL);
    }

    if (!strcmp(tokens[0], "read_doc") && strlen(tokens[1]) > 0 &&
        strlen(tokens[2]) > 0) {

      char *buffer = read_doc(tokens[1], tokens[2]);
      printf("%s", buffer);

      return;
    }
  }
  if (len == 4) {

    if (!strcmp(tokens[0], "create_doc") && strlen(tokens[1]) > 0 &&
        strlen(tokens[2]) > 0) {

      create_document(tokens[1], tokens[2], tokens[3]);
    }

    if (!strcmp(tokens[0], "change_value") && strlen(tokens[1]) > 0 &&
        strlen(tokens[2]) > 0) {

      change_value(tokens[1], tokens[2], tokens[3]);
    }

  } else {
    printf("Unknown Command \n");
  }
}

void handle_command(const char *input) {
  (void)input;
  // actual code here
}

int create_collection(const char *col) {

  // Create the base directory if it doesn't exist
  if (stat(BASE_COLLECTION_PATH, &st) == -1) {
    if (mkdir(BASE_COLLECTION_PATH, 0777) == -1) {
      perror("Failed to create base collections directory");
      return 0;
    }
  }

  snprintf(fullPath, sizeof(fullPath), "%s%s", BASE_COLLECTION_PATH,
           col); // will edit fullpath as usable path

  if (stat(fullPath, &st) == -1) {
    int check = mkdir(fullPath, 0777);

    if (check == 0) {
      printf("%s collection created\n", fullPath);
    } else {
      perror("mkdir failed");
    }
    return !check;
  } else {
    printf("File already exist");
    return 0;
  }
}

char *read_doc(char *collectionName, char *docName) {

  char *buffer = malloc(1024);

  char *filepath = pathMaker(collectionName, docName);

  if (stat(filepath, &st) == -1) {
    printf("file not found \n");
    return;
  }

  readFile(filepath, buffer);
  return buffer;
}

void create_document(const char *col, const char *doc, const char *data) {

  char colPath[256];
  snprintf(colPath, sizeof(colPath), "%s%s", BASE_COLLECTION_PATH, col);

  if (stat(colPath, &st) == -1) {
    if (mkdir(colPath, 0777) == -1) {
      perror("Failed to create collection directory");
      return;
    }
  }

  snprintf(colPath, sizeof(colPath), "%s%s/%s.%s", BASE_COLLECTION_PATH, col,
           doc, "json");

  if (data != NULL) {

    cJSON *json = cJSON_Parse(data);

    if (json == NULL) {
      printf("Invalid JSON string.\n");
      return;
    }

    char *formatted = cJSON_Print(json);

    printf("%s", formatted);
    if (!formatted) {
      printf("Failed to format JSON.\n");
      cJSON_Delete(json);
      return;
    }

    // Open file and write formatted JSON
    FILE *fp = fopen(colPath, "w");
    if (fp == NULL) {
      perror("Failed to create document");
      free(formatted);
      cJSON_Delete(json);
      return;
    }

    fputs(formatted, fp);
    fclose(fp);

    free(formatted);
    cJSON_Delete(json);

  } else {
    perror("Failed to create document");
    return;
  }

  printf("Document %s created\n", colPath);
}

void change_value(char *col, char *doc, char *key_value) {

  char *splitedKey[2];
  int len = 0;

  (void)col;
  (void)doc;

  split(key_value, splitedKey, &len, "=");

  char *textContent = read_doc(col, doc);

  cJSON *json = cJSON_Parse(textContent);

  patch_value(json, splitedKey[0], splitedKey[1]);

  textContent = cJSON_Print(json);

  char *filepath = pathMaker(col, doc);

  writeFile(filepath, textContent);
}
