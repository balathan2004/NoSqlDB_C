#include "utils.h"
#include <limits.h>
#include <stdio.h>
#include <unistd.h> // Required for getcwd()
#include "command_handler.h"
#include "file_function.h"
#include "config.h"


int main() {

  acceptCommand();

  return 1;
}