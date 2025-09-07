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

char fullPath[256];
struct stat st = {0};

int create_collection(const char *col) {

  // Create the base directory if it doesn't exist

  char *filepath;

  int isFileExist = isFolderExists(BASE_COLLECTION_PATH);

  if (!isFileExist) {
    printf("Error Folder creation");
    return;
  }

  // filepath = ;

  int res = createFolderRecursive(pathMaker(col, NULL));

  return res;
}

char *read_doc(char *collectionName, char *docName) {

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

  char filepath[1048];

  filepath = pathMaker(col, doc);

  snprintf(filepath, sizeof(filepath), "%s%s", BASE_COLLECTION_PATH, col);

  if (stat(filepath, &st) == -1) {
    if (mkdir(filepath, 0777) == -1) {
      perror("Failed to create collection directory");
      return;
    }
  }

  snprintf(filepath, sizeof(filepath), "%s%s/%s.%s", BASE_COLLECTION_PATH, col,
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
    FILE *fp = fopen(filepath, "w");
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
    FILE *fp = fopen(filepath, "w");
    if (fp == NULL) {
      perror("Failed to create document");
      return;
    }

    fclose(fp);
    perror("Empty doc created");
    return;
  }

  printf("Document %s created\n", filepath);
}
