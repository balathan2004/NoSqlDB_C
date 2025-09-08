#define _POSIX_C_SOURCE 200809L
#include "cJSON.h"
#include "command_handler.h"
#include "config.h"
#include "file_function.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int create_collection(const char *col) {

  int isFileExist = isFolderExists(BASE_COLLECTION_PATH);

  if (!isFileExist) {
    printf("Error Folder creation");
    return 0;
  }

  int res = createFolderRecursive(pathMaker(col, NULL));

  return res;
}

char *read_doc(char *collectionName, char *docName) {

  struct stat st = {0};

  char *buffer = malloc(1024);

  char *filepath = pathMaker(collectionName, docName);

  if (stat(filepath, &st) == -1) {
    printf("file not found \n");
    return NULL;
  }

  buffer = readFileIfExist(filepath);
  return buffer;
}

void create_document(const char *col, const char *doc, const char *data) {

  char *filepath;

  filepath = pathMaker(col, NULL);

  if (!createFolderRecursive(filepath)) {
    printf("Error Creating File");
    return;
  }

  filepath = pathMaker(col, doc);

  if (data != NULL) {

    cJSON *json = cJSON_Parse(data);

    if (json == NULL) {
      printf("Invalid JSON string.\n");
      return;
    }

    char *formatted = cJSON_Print(json);

    writeFile(filepath, formatted);

    free(formatted);
    cJSON_Delete(json);

  } else {

    char *text = readFileIfExist(filepath);

    if (text == NULL || strlen(text) <= 0) {
      writeFile(filepath, NULL);
    }

    printf("Empty doc created");
    return;
  }

  printf("Document %s created\n", filepath);
}
