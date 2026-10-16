#pragma once
#include <stddef.h>

extern "C" {

char *strtok_r(char *string, const char *delimiters, char **context);
char *strtok(char *string, const char *delimiters);
size_t strlen(const char *string);
}
