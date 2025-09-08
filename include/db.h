#ifndef DB_H
#define DB_H

void create_document(const char *col, const char *doc, const char *data);

char* read_doc(char *col, char *doc);

void change_value(char *col, char *doc, char *key_value);

#endif