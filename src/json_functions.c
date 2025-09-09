#include "json_functions.h"
#include "cJSON.h"

char *returnWritableJson(char *textContent) {

  cJSON *json = cJSON_Parse(textContent);

  if (!json) {
    return NULL;
  }

  return cJSON_Print(json);
}
