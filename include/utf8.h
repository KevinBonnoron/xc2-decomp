#pragma once
#include <stddef.h>
#include <stdint.h>

// utf8.h by Neil Henning (https://github.com/sheredom/utf8.h), public domain (The Unlicense). The game embeds an early
// 2017 revision of this single-header library, compiled as C++ with C linkage: see
// src/libs/monolib_mm/source/util/utf8.cpp for the evidence. The function names, `utf8_int32_t` and the two macros
// below are the library's own public source (like the names of the dlmalloc code in mtl/dlmalloc.inl), not names
// invented for this project.
//
// The library defines every function with `utf8_weak`, which makes the definitions weak (interposable), so that clang
// never inlines one into another (the game calls utf8str from utf8chr and utf8size from utf8dup). `utf8_restrict`
// qualifies the destination and source of the copy functions. The library's `utf8_nonnull`, `utf8_pure` and
// `utf8_null` are not needed: nothing in the binary shows them.
#define utf8_weak __attribute__((weak))
#define utf8_restrict __restrict__

typedef int32_t utf8_int32_t;

extern "C" {

int utf8casecmp(const void *src1, const void *src2);
void *utf8cat(void *utf8_restrict dst, const void *utf8_restrict src);
void *utf8chr(const void *src, utf8_int32_t chr);
int utf8cmp(const void *src1, const void *src2);
void *utf8cpy(void *utf8_restrict dst, const void *utf8_restrict src);
size_t utf8cspn(const void *src, const void *reject);
void *utf8dup(const void *src);
size_t utf8len(const void *str);
int utf8ncasecmp(const void *src1, const void *src2, size_t n);
void *utf8ncat(void *utf8_restrict dst, const void *utf8_restrict src, size_t n);
int utf8ncmp(const void *src1, const void *src2, size_t n);
void *utf8ncpy(void *utf8_restrict dst, const void *utf8_restrict src, size_t n);
void *utf8pbrk(const void *str, const void *accept);
void *utf8rchr(const void *src, utf8_int32_t chr);
size_t utf8size(const void *str);
size_t utf8spn(const void *src, const void *accept);
void *utf8str(const void *haystack, const void *needle);
void *utf8casestr(const void *haystack, const void *needle);
void *utf8valid(const void *str);
void *utf8codepoint(const void *utf8_restrict str, utf8_int32_t *utf8_restrict out_codepoint);
size_t utf8codepointsize(utf8_int32_t chr);
void *utf8catcodepoint(void *utf8_restrict str, utf8_int32_t chr, size_t n);
int utf8islower(utf8_int32_t chr);
int utf8isupper(utf8_int32_t chr);
void utf8lwr(void *utf8_restrict str);
void utf8upr(void *utf8_restrict str);
}
