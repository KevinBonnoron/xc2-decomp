#pragma once
#include "types.h"

extern "C" {

void mlStackTrace(void **stack);
void mlGetStackAdr(u64 *address, u64 *size);
}
