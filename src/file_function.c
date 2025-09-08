#include "file_function.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

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

FILE *returnFilePathExists(char *filepath, char *mode) {

  FILE *file;

  if (mode == NULL) {
    file = fopen(filepath, "r");
  } else {
    file = fopen(filepath, mode);
  }

  if (!file) {
    printf("\n File Doesn't exist");
    return NULL;
  }

  // fclose(file);

  return file;
}



int createFolderRecursive(char *filepath) {

  char tmp[1048];
  char *p = NULL;
  size_t len;

  snprintf(tmp, sizeof(tmp), "%s", filepath); // Copy path into tmp buffer
  len = strlen(tmp);

  if (len > 0 && tmp[len - 1] == '/') {
    tmp[len-1] = '\0';
  }

  for (p = tmp + 1; *p; p++) {

    if (*p == '/') {
      *p = '\0';

       if (!isFolderExists(tmp)) {
                if (createFolder(tmp) != 0) {
                    return -1; // Stop if folder creation fails
                }
            }

      *p = '/';
    }
  }

    if (!isFolderExists(tmp)) {
        if (createFolder(tmp) != 0) {
            return -1;
        }
    }

    return 1;

  
}

int isFolderExists(const char *filepath) {

  struct stat st;

  if (stat(filepath, &st) == 0 && S_ISDIR(st.st_mode)) {
    return 1;
  }
  return 0;
}

int createFolder(char *filepath) {

  struct stat st = {0};

  if (stat(filepath, &st) == 0) {
    if (!S_ISDIR(st.st_mode)) {
      fprintf(stderr, "Path exists but is not a directory\n");
      return 0;
    }
    printf("Folder exists\n");
    return 1; // Folder exists
  }

  if (mkdir(filepath, 0755) == -1) {
    perror("Failed to create base collections directory");
    return 0;
  }

  printf("Folder Created\n");

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



void writeFile(char *filepath, char *value) {

  FILE *file = fopen(filepath, "w");

  if (file == NULL) {
    printf("Failed to open file: %s\n", filepath);
    return;
  }

  if (value == NULL || strlen(value) == 0) {
    printf("No value to write\n");
    fclose(file);
    return;
  }

  fprintf(file, value);
  fclose(file);
}