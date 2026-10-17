#pragma once
#include <stddef.h>

extern "C" {

char *strtok_r(char *string, const char *delimiters, char **context);
char *strtok(char *string, const char *delimiters);
size_t strlen(const char *string);
void *memcpy(void *destination, const void *source, size_t size);
int strcmp(const char *left, const char *right);
char *strcpy(char *destination, const char *source);
}
