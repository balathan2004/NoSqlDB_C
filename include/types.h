#ifndef TYPES_H   // Include guard
#define TYPES_H

#include <stdbool.h>  // if you're using bool

// Define the struct and create a typedef in one step
typedef struct User {
    char name[50];
    int age;
    bool isActive;
} User;

#endif // TYPES_H
