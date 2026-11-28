#pragma once

// Public interface of FastLZ 0.1.0 (see src/libs/monolib_mm/source/util/fastlz.cpp).
extern "C" {

int fastlz_compress(const void *input, int length, void *output);
int fastlz_compress_level(int level, const void *input, int length, void *output);
int fastlz_decompress(const void *input, int length, void *output, int maxout);
}
