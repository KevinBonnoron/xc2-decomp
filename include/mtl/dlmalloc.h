#pragma once
#include <stddef.h>

// Entry point of the dlmalloc linked into the game (mspace API); the name is a game symbol.
extern "C" {

void *create_mspace_with_base(void *base, size_t capacity);
}
