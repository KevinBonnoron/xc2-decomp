/*
  FastLZ - lightning-fast lossless compression library

  Copyright (C) 2007 Ariya Hidayat (ariya@kde.org)
  Copyright (C) 2006 Ariya Hidayat (ariya@kde.org)
  Copyright (C) 2005 Ariya Hidayat (ariya@kde.org)

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

// FastLZ 0.1.0 (https://github.com/ariya/FastLZ, the library's only revision before 2020: fastlz.c of 19 June 2007).
// The game embeds it as C++ with C linkage at 0x710075c3c8-0x710075d38c: fastlz_compress, the two compressors
// fastlz1_compress (0x710075c3d8) and fastlz2_compress (0x710075c810) that fastlz_compress and fastlz_compress_level
// reach by tail calls, fastlz_decompress with both decompressors inlined, then fastlz_compress_level. The library
// compiles its level-dependent code twice by including its own source (fastlz.c includes "fastlz.c"); here that code is
// fastlz_level.inl. The names, macros and the goto statements are the library's own source.
#include "fastlz.h"

/*
 * Always check for bound when decompressing.
 * Generally it is best to leave it defined.
 */
#define FASTLZ_SAFE

/*
 * Give hints to the compiler for branch prediction optimization.
 * The library enables them for GNU C compilers (__GNUC__ > 2), which clang is: without them the blocks of
 * fastlz_decompress are laid out differently from the game's.
 */
#define FASTLZ_EXPECT_CONDITIONAL(c) (__builtin_expect((c), 1))
#define FASTLZ_UNEXPECT_CONDITIONAL(c) (__builtin_expect((c), 0))

/*
 * Use inlined functions for supported systems.
 */
#define FASTLZ_INLINE inline

/*
 * Prevent accessing more than 8-bit at once, except on x86 architectures.
 */
#define FASTLZ_STRICT_ALIGN

/*
 * FIXME: use preprocessor magic to set this on different platforms!
 */
typedef unsigned char flzuint8;
typedef unsigned short flzuint16;
typedef unsigned int flzuint32;

#define MAX_COPY 32
#define MAX_LEN 264 /* 256 + 8 */
#define MAX_DISTANCE 8192

#define FASTLZ_READU16(p) ((p)[0] | (p)[1] << 8)

#define HASH_LOG 13
#define HASH_SIZE (1 << HASH_LOG)
#define HASH_MASK (HASH_SIZE - 1)
#define HASH_FUNCTION(v, p)                                                                                                                                                                            \
  {                                                                                                                                                                                                    \
    v = FASTLZ_READU16(p);                                                                                                                                                                             \
    v ^= FASTLZ_READU16(p + 1) ^ (v >> (16 - HASH_LOG));                                                                                                                                               \
    v &= HASH_MASK;                                                                                                                                                                                    \
  }

#undef FASTLZ_LEVEL
#define FASTLZ_LEVEL 1

#undef FASTLZ_COMPRESSOR
#undef FASTLZ_DECOMPRESSOR
#define FASTLZ_COMPRESSOR fastlz1_compress
#define FASTLZ_DECOMPRESSOR fastlz1_decompress
static FASTLZ_INLINE int FASTLZ_COMPRESSOR(const void *input, int length, void *output);
static FASTLZ_INLINE int FASTLZ_DECOMPRESSOR(const void *input, int length, void *output, int maxout);
#include "util/fastlz_level.inl"

#undef FASTLZ_LEVEL
#define FASTLZ_LEVEL 2

#undef MAX_DISTANCE
#define MAX_DISTANCE 8191
#define MAX_FARDISTANCE (65535 + MAX_DISTANCE - 1)

#undef FASTLZ_COMPRESSOR
#undef FASTLZ_DECOMPRESSOR
#define FASTLZ_COMPRESSOR fastlz2_compress
#define FASTLZ_DECOMPRESSOR fastlz2_decompress
static FASTLZ_INLINE int FASTLZ_COMPRESSOR(const void *input, int length, void *output);
static FASTLZ_INLINE int FASTLZ_DECOMPRESSOR(const void *input, int length, void *output, int maxout);
#include "util/fastlz_level.inl"

extern "C" {

int fastlz_compress(const void *input, int length, void *output) {
  /* for short block, choose fastlz1 */
  if (length < 65536)
    return fastlz1_compress(input, length, output);

  /* else... */
  return fastlz2_compress(input, length, output);
}

int fastlz_decompress(const void *input, int length, void *output, int maxout) {
  /* magic identifier for compression level */
  int level = ((*(const flzuint8 *)input) >> 5) + 1;

  if (level == 1)
    return fastlz1_decompress(input, length, output, maxout);
  if (level == 2)
    return fastlz2_decompress(input, length, output, maxout);

  /* unknown level, trigger error */
  return 0;
}

int fastlz_compress_level(int level, const void *input, int length, void *output) {
  if (level == 1)
    return fastlz1_compress(input, length, output);
  if (level == 2)
    return fastlz2_compress(input, length, output);

  return 0;
}
}
