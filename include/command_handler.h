#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

void handle_command(const char *input);


void acceptCommand();

void create_document(const char *col, const char *doc, const char *data);

char* read_doc(char *col, char *doc);

void change_value(char *col, char *doc, char *key_value);

#endif