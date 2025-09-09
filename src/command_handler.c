#define _POSIX_C_SOURCE 200809L
#include "command_handler.h"
#include "cJSON.h"
#include "config.h"
#include "db.h"
#include "file_function.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void acceptCommand() {

  char command[2048];

  printf(">>> ");

  fgets(command, sizeof(command), stdin);

  command[strcspn(command, "\n")] = 0;

  char tokens[MAX_ARGS][MAX_TOKEN_LEN];

  int len = splitCommand(command, tokens);

  for (int i = 0; i < len; i++) {
    printf("token:%d-%s\n", i, tokens[i]);
  }

  if (len == 2) {
    if (!strcmp(tokens[0], "create_col") && strlen(tokens[1]) > 0) {
      char *path = pathMaker(tokens[1], NULL);
      createFolder(path);
      return;
    }
  }

  else if (len == 3) {

    if (!strcmp(tokens[0], "create_doc") && strlen(tokens[1]) > 0 &&
        strlen(tokens[2]) > 0) {

      create_document(tokens[1], tokens[2], NULL);
      return;
    }

    if (!strcmp(tokens[0], "read_doc") && strlen(tokens[1]) > 0 &&
        strlen(tokens[2]) > 0) {

      char *buffer = read_doc(tokens[1], tokens[2]);
      printf("%s", buffer);

      return;
    }

  

  } else if (len == 4) {

    if (!strcmp(tokens[0], "create_doc") && strlen(tokens[1]) > 0 &&
        strlen(tokens[2]) > 0) {

      create_document(tokens[1], tokens[2], tokens[3]);
      return;
    }

    if (!strcmp(tokens[0], "change_value") && strlen(tokens[1]) > 0 &&
        strlen(tokens[2]) > 0) {

      change_value(pathMaker(tokens[1], tokens[2]), tokens[3]);
      return;
    }

      if (!strcmp(tokens[0], "update_doc"),
        strlen(tokens[1]) > 0 && strlen(tokens[2]) > 0) {
      update_doc(pathMaker(tokens[1], tokens[2]),tokens[3]);
      return;
    }

  } else {
    printf("Unknown Command \n");
  }
}