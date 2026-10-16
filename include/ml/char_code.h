#pragma once
#include <stddef.h>

#include "types.h"

extern "C" {

bool mlUTF8toUTF16(u16 *destination, size_t destinationLength, const char *source);
bool mlUTF16toSJIS(char *destination, size_t destinationSize, const u16 *source);
}
