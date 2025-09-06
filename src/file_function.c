#include "file_function.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "config.h"

int isFileExist(char *filepath) {

  FILE *file;

  file = fopen(filepath, "r");

  if (!file) {
    printf("\n File Doesn't exist");
    return 0;
  }

  fclose(file);

  return 1;
}

int isFolderExistCreate(char *filepath) {

  struct stat st = {0};

  if (stat(filepath, &st) == 0) {
    if (!S_ISDIR(st.st_mode)) {
      fprintf(stderr, "Path exists but is not a directory\n");
      return 0;
    }
    return 1; // Folder exists
  }

  if (mkdir(filepath, 0755) == -1) {
    perror("Failed to create base collections directory");
    return 0;
  }

  return 1;
}

char *readFileIfExist(char *filepath) {

  FILE *file = fopen(filepath, "rb");

  if (!file)
    return NULL;

  if (fseek(file, 0, SEEK_END) != 0) { // [ADDED] check fseek success
    fclose(file);
    return NULL;
  }

  long len = ftell(file);
  if (len < 0) {
    fclose(file);
    return NULL;
  }

  rewind(file);

  char *buffer = malloc(len + 1);

  if (!buffer) {
    fprintf(stderr, "malloc failed\n");
    fclose(file);
    return NULL;
  }

  size_t bytesRead = fread(buffer, 1, len, file);

  buffer[bytesRead] = '\0';
  fclose(file);
  return buffer;
}

