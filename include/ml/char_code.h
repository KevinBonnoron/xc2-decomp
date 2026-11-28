#pragma once
#include <stddef.h>

#include "types.h"

extern "C" {

bool mlUTF16toSJIS(char *destination, size_t destinationSize, const u16 *source);
bool mlSJIStoUTF16(u16 *destination, size_t destinationLength, const char *source);
bool mlUTF8toUTF16(u16 *destination, size_t destinationLength, const char *source);
char *mlGetSJIS(const u16 *source);
u16 *mlGetUTF16(const char *source);
u16 *mlGetUTF16ByUTF8(const char *source);
bool mlSJIStoUTF8();
void mlGetUtf16Info(const void **table, size_t *size);
long mlUtf8len(const char *source);
}
