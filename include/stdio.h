#pragma once
#include <stdarg.h>
#include <stddef.h>

extern "C" {

int vsprintf(char *buffer, const char *format, va_list args);
int vsnprintf(char *buffer, size_t size, const char *format, va_list args);
}
