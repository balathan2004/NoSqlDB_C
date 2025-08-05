#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *spiltByIndex(char value[], int index, int end) {
  char *newString = malloc((end - index) + 1);
  for (int i = index; i < end; i++) {
    newString[i - index] = value[i];
  }
  newString[end - index] = '\0';
  return newString;
}

void acceptCommand() {
  char command[1024];

  printf("\n>>> ");
  fgets(command, sizeof(command), stdin);

  int len = strlen(command);
  if (command[len - 1] == '\n') command[len - 1] = '\0'; // Remove newline

  int start = 0;
  for (int i = 0; i <= len; i++) {
    if (command[i] == ' ' || command[i] == '\0') {
      if (i > start) {
        char *part = spiltByIndex(command, start, i);
        printf("Token: %s\n", part);
        free(part);
      }
      start = i + 1;
    }
  }
}



void main() { acceptCommand(); }