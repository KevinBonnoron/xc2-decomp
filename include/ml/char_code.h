#pragma once
#include "types.h"

extern "C" {

bool mlUTF8toUTF16(u16 *destination, u32 destinationLength, const char *source);
bool mlUTF16toSJIS(char *destination, u32 destinationSize, const u16 *source);
}
