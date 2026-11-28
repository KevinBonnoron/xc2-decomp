// utf8.h by Neil Henning (https://github.com/sheredom/utf8.h), public domain (The Unlicense).
// The game embeds an early revision of the library (2017: the functions work byte by byte; utf8casecmp compares
// lower-cased bytes, utf8len knows lead bytes up to four bytes, utf8lwr and utf8upr only map ASCII, utf8islower is the
// negation of utf8isupper, utf8ncat and utf8ncpy copy the first byte before testing n), compiled as C++ with the
// functions' C linkage; the symbols keep the library's own names. The functions are at 0x7100758bd4-0x71007597e8 and
// are written in the game's order (the library's own order differs: the game has utf8str after its first user
// utf8chr and utf8size after utf8dup).
//
// Evidence of the library's own `utf8_weak` and `utf8_restrict` macros (include/utf8.h): without weak linkage clang
// inlines utf8str into utf8chr and utf8size into utf8dup, while the game calls them; utf8ncat and utf8ncpy only get
// the game's load/store order with restrict-qualified destination and source. utf8islower and utf8isupper are not weak
// here: the game inlines the range test of utf8isupper into utf8islower and utf8lwr.
#include "utf8.h"

#include <stdlib.h>

extern "C" {

utf8_weak int utf8casecmp(const void *src1, const void *src2) {
  const unsigned char *s1 = static_cast<const unsigned char *>(src1);
  const unsigned char *s2 = static_cast<const unsigned char *>(src2);

  while (('\0' != *s1) || ('\0' != *s2)) {
    unsigned char a = *s1;
    unsigned char b = *s2;

    if (('A' <= a) && ('Z' >= a)) {
      a |= 0x20;
    }

    if (('A' <= b) && ('Z' >= b)) {
      b |= 0x20;
    }

    if (a < b) {
      return -1;
    } else if (a > b) {
      return 1;
    }

    s1++;
    s2++;
  }

  return 0;
}

utf8_weak void *utf8cat(void *utf8_restrict dst, const void *utf8_restrict src) {
  char *d = static_cast<char *>(dst);
  const char *s = static_cast<const char *>(src);

  while ('\0' != *d) {
    d++;
  }

  while ('\0' != *s) {
    *d++ = *s++;
  }

  *d = '\0';

  return dst;
}

utf8_weak void *utf8chr(const void *src, utf8_int32_t chr) {
  char c[5] = {'\0', '\0', '\0', '\0', '\0'};

  if (0 == chr) {
    const char *s = static_cast<const char *>(src);
    while ('\0' != *s) {
      s++;
    }
    return const_cast<char *>(s);
  } else if (0 == (static_cast<utf8_int32_t>(0xffffff80) & chr)) {
    c[0] = static_cast<char>(chr);
  } else if (0 == (static_cast<utf8_int32_t>(0xfffff800) & chr)) {
    c[0] = 0xc0 | static_cast<char>(chr >> 6);
    c[1] = 0x80 | static_cast<char>(chr & 0x3f);
  } else if (0 == (static_cast<utf8_int32_t>(0xffff0000) & chr)) {
    c[0] = 0xe0 | static_cast<char>(chr >> 12);
    c[1] = 0x80 | static_cast<char>((chr >> 6) & 0x3f);
    c[2] = 0x80 | static_cast<char>(chr & 0x3f);
  } else {
    c[0] = 0xf0 | static_cast<char>(chr >> 18);
    c[1] = 0x80 | static_cast<char>((chr >> 12) & 0x3f);
    c[2] = 0x80 | static_cast<char>((chr >> 6) & 0x3f);
    c[3] = 0x80 | static_cast<char>(chr & 0x3f);
  }

  return utf8str(src, c);
}

utf8_weak void *utf8str(const void *haystack, const void *needle) {
  const char *h = static_cast<const char *>(haystack);

  if ('\0' == *(static_cast<const char *>(needle))) {
    return const_cast<void *>(haystack);
  }

  while ('\0' != *h) {
    const char *maybeMatch = h;
    const char *n = static_cast<const char *>(needle);

    while (*h == *n && (*h != '\0' && *n != '\0')) {
      n++;
      h++;
    }

    if ('\0' == *n) {
      return const_cast<char *>(maybeMatch);
    } else {
      if ('\0' != *h) {
        do {
          h++;
        } while (0x80 == (0xc0 & *h));
      }
    }
  }

  return nullptr;
}

utf8_weak int utf8cmp(const void *src1, const void *src2) {
  const unsigned char *s1 = static_cast<const unsigned char *>(src1);
  const unsigned char *s2 = static_cast<const unsigned char *>(src2);

  while (('\0' != *s1) || ('\0' != *s2)) {
    if (*s1 < *s2) {
      return -1;
    } else if (*s1 > *s2) {
      return 1;
    }

    s1++;
    s2++;
  }

  return 0;
}

utf8_weak void *utf8cpy(void *utf8_restrict dst, const void *utf8_restrict src) {
  char *d = static_cast<char *>(dst);
  const char *s = static_cast<const char *>(src);

  while ('\0' != *s) {
    *d++ = *s++;
  }

  *d = '\0';

  return dst;
}

utf8_weak size_t utf8cspn(const void *src, const void *reject) {
  const char *s = static_cast<const char *>(src);
  size_t chars = 0;

  while ('\0' != *s) {
    const char *r = static_cast<const char *>(reject);
    size_t offset = 0;

    while ('\0' != *r) {
      if ((0x80 != (0xc0 & *r)) && (0 < offset)) {
        return chars;
      } else {
        if (*r == s[offset]) {
          offset++;
          r++;
        } else {
          offset = 0;

          do {
            r++;
          } while (0x80 == (0xc0 & *r));
        }
      }
    }

    do {
      s++;
    } while (0x80 == (0xc0 & *s));
    chars++;
  }

  return chars;
}

utf8_weak void *utf8dup(const void *src) {
  const char *s = static_cast<const char *>(src);
  char *n = nullptr;

  size_t bytes = utf8size(src);

  n = static_cast<char *>(malloc(bytes));

  if (nullptr == n) {
    return nullptr;
  } else {
    bytes = 0;

    while ('\0' != s[bytes]) {
      n[bytes] = s[bytes];
      bytes++;
    }

    n[bytes] = '\0';
    return n;
  }
}

utf8_weak size_t utf8size(const void *str) {
  const char *s = static_cast<const char *>(str);
  size_t size = 0;
  while ('\0' != s[size]) {
    size++;
  }

  size++;
  return size;
}

utf8_weak size_t utf8len(const void *str) {
  const unsigned char *s = static_cast<const unsigned char *>(str);
  size_t length = 0;

  while ('\0' != *s) {
    if (0xf0 == (0xf8 & *s)) {
      s += 4;
    } else if (0xe0 == (0xf0 & *s)) {
      s += 3;
    } else if (0xc0 == (0xe0 & *s)) {
      s += 2;
    } else {
      s++;
    }

    length++;
  }

  return length;
}

utf8_weak int utf8ncasecmp(const void *src1, const void *src2, size_t n) {
  const unsigned char *s1 = static_cast<const unsigned char *>(src1);
  const unsigned char *s2 = static_cast<const unsigned char *>(src2);

  while ((('\0' != *s1) || ('\0' != *s2)) && (0 != n--)) {
    unsigned char a = *s1;
    unsigned char b = *s2;

    if (('A' <= a) && ('Z' >= a)) {
      a |= 0x20;
    }

    if (('A' <= b) && ('Z' >= b)) {
      b |= 0x20;
    }

    if (a < b) {
      return -1;
    } else if (a > b) {
      return 1;
    }

    s1++;
    s2++;
  }

  return 0;
}

utf8_weak void *utf8ncat(void *utf8_restrict dst, const void *utf8_restrict src, size_t n) {
  char *d = static_cast<char *>(dst);
  const char *s = static_cast<const char *>(src);

  while ('\0' != *d) {
    d++;
  }

  do {
    *d++ = *s++;
  } while (('\0' != *s) && (0 != --n));

  *d = '\0';

  return dst;
}

utf8_weak int utf8ncmp(const void *src1, const void *src2, size_t n) {
  const unsigned char *s1 = static_cast<const unsigned char *>(src1);
  const unsigned char *s2 = static_cast<const unsigned char *>(src2);

  while ((('\0' != *s1) || ('\0' != *s2)) && (0 != n--)) {
    if (*s1 < *s2) {
      return -1;
    } else if (*s1 > *s2) {
      return 1;
    }

    s1++;
    s2++;
  }

  return 0;
}

utf8_weak void *utf8ncpy(void *utf8_restrict dst, const void *utf8_restrict src, size_t n) {
  char *d = static_cast<char *>(dst);
  const char *s = static_cast<const char *>(src);

  do {
    *d++ = *s++;
  } while (('\0' != *s) && (0 != --n));

  while (0 != n--) {
    *d++ = '\0';
  }

  return dst;
}

utf8_weak void *utf8rchr(const void *src, utf8_int32_t chr) {
  const char *s = static_cast<const char *>(src);
  const char *match = nullptr;
  char c[5] = {'\0', '\0', '\0', '\0', '\0'};

  if (0 == chr) {
    while ('\0' != *s) {
      s++;
    }
    return const_cast<char *>(s);
  } else if (0 == (static_cast<utf8_int32_t>(0xffffff80) & chr)) {
    c[0] = static_cast<char>(chr);
  } else if (0 == (static_cast<utf8_int32_t>(0xfffff800) & chr)) {
    c[0] = 0xc0 | static_cast<char>(chr >> 6);
    c[1] = 0x80 | static_cast<char>(chr & 0x3f);
  } else if (0 == (static_cast<utf8_int32_t>(0xffff0000) & chr)) {
    c[0] = 0xe0 | static_cast<char>(chr >> 12);
    c[1] = 0x80 | static_cast<char>((chr >> 6) & 0x3f);
    c[2] = 0x80 | static_cast<char>(chr & 0x3f);
  } else {
    c[0] = 0xf0 | static_cast<char>(chr >> 18);
    c[1] = 0x80 | static_cast<char>((chr >> 12) & 0x3f);
    c[2] = 0x80 | static_cast<char>((chr >> 6) & 0x3f);
    c[3] = 0x80 | static_cast<char>(chr & 0x3f);
  }

  while ('\0' != *s) {
    size_t offset = 0;

    while (s[offset] == c[offset]) {
      offset++;
    }

    if ('\0' == c[offset]) {
      match = s;
      s += offset;
    } else {
      s += offset;

      if ('\0' != *s) {
        do {
          s++;
        } while (0x80 == (0xc0 & *s));
      }
    }
  }

  return const_cast<char *>(match);
}

utf8_weak void *utf8pbrk(const void *str, const void *accept) {
  const char *s = static_cast<const char *>(str);

  while ('\0' != *s) {
    const char *a = static_cast<const char *>(accept);
    size_t offset = 0;

    while ('\0' != *a) {
      if ((0x80 != (0xc0 & *a)) && (0 < offset)) {
        return const_cast<char *>(s);
      } else {
        if (*a == s[offset]) {
          offset++;
          a++;
        } else {
          offset = 0;

          do {
            a++;
          } while (0x80 == (0xc0 & *a));
        }
      }
    }

    if (offset > 0) {
      return const_cast<char *>(s);
    }

    do {
      s++;
    } while (0x80 == (0xc0 & *s));
  }

  return nullptr;
}

utf8_weak size_t utf8spn(const void *src, const void *accept) {
  const char *s = static_cast<const char *>(src);
  size_t chars = 0;

  while ('\0' != *s) {
    const char *a = static_cast<const char *>(accept);
    size_t offset = 0;

    while ('\0' != *a) {
      if ((0x80 != (0xc0 & *a)) && (0 < offset)) {
        chars++;
        s += offset;
        break;
      } else {
        if (*a == s[offset]) {
          offset++;
          a++;
        } else {
          offset = 0;

          do {
            a++;
          } while (0x80 == (0xc0 & *a));
        }
      }
    }

    if ('\0' == *a) {
      return chars;
    }
  }

  return chars;
}

utf8_weak void *utf8casestr(const void *haystack, const void *needle) {
  const char *h = static_cast<const char *>(haystack);

  if ('\0' == *(static_cast<const char *>(needle))) {
    return const_cast<void *>(haystack);
  }

  while ('\0' != *h) {
    const char *maybeMatch = h;
    const char *n = static_cast<const char *>(needle);

    for (;;) {
      unsigned char a = *h;
      unsigned char b = *n;

      if (('A' <= a) && ('Z' >= a)) {
        a |= 0x20;
      }

      if (('A' <= b) && ('Z' >= b)) {
        b |= 0x20;
      }

      if (a != b) {
        break;
      }

      h++;
      n++;
    }

    if ('\0' == *n) {
      return const_cast<char *>(maybeMatch);
    } else {
      if ('\0' != *h) {
        do {
          h++;
        } while (0x80 == (0xc0 & *h));
      }
    }
  }

  return nullptr;
}

utf8_weak void *utf8valid(const void *str) {
  const char *s = static_cast<const char *>(str);

  while ('\0' != *s) {
    if (0xf0 == (0xf8 & *s)) {
      if ((0x80 != (0xc0 & s[1])) || (0x80 != (0xc0 & s[2])) || (0x80 != (0xc0 & s[3]))) {
        return const_cast<char *>(s);
      }

      if (0x80 == (0xc0 & s[4])) {
        return const_cast<char *>(s);
      }

      if ((0 == (0x07 & s[0])) && (0 == (0x30 & s[1]))) {
        return const_cast<char *>(s);
      }

      s += 4;
    } else if (0xe0 == (0xf0 & *s)) {
      if ((0x80 != (0xc0 & s[1])) || (0x80 != (0xc0 & s[2]))) {
        return const_cast<char *>(s);
      }

      if (0x80 == (0xc0 & s[3])) {
        return const_cast<char *>(s);
      }

      if ((0 == (0x0f & s[0])) && (0 == (0x20 & s[1]))) {
        return const_cast<char *>(s);
      }

      s += 3;
    } else if (0xc0 == (0xe0 & *s)) {
      if (0x80 != (0xc0 & s[1])) {
        return const_cast<char *>(s);
      }

      if (0x80 == (0xc0 & s[2])) {
        return const_cast<char *>(s);
      }

      if (0 == (0x1e & s[0])) {
        return const_cast<char *>(s);
      }

      s += 2;
    } else if (0x00 == (0x80 & *s)) {
      s += 1;
    } else {
      return const_cast<char *>(s);
    }
  }

  return nullptr;
}

utf8_weak void *utf8codepoint(const void *utf8_restrict str, utf8_int32_t *utf8_restrict out_codepoint) {
  const char *s = static_cast<const char *>(str);

  if (0xf0 == (0xf8 & s[0])) {
    *out_codepoint = ((0x07 & s[0]) << 18) | ((0x3f & s[1]) << 12) | ((0x3f & s[2]) << 6) | (0x3f & s[3]);
    s += 4;
  } else if (0xe0 == (0xf0 & s[0])) {
    *out_codepoint = ((0x0f & s[0]) << 12) | ((0x3f & s[1]) << 6) | (0x3f & s[2]);
    s += 3;
  } else if (0xc0 == (0xe0 & s[0])) {
    *out_codepoint = ((0x1f & s[0]) << 6) | (0x3f & s[1]);
    s += 2;
  } else {
    *out_codepoint = s[0];
    s += 1;
  }

  return const_cast<char *>(s);
}

utf8_weak size_t utf8codepointsize(utf8_int32_t chr) {
  if (0 == (static_cast<utf8_int32_t>(0xffffff80) & chr)) {
    return 1;
  } else if (0 == (static_cast<utf8_int32_t>(0xfffff800) & chr)) {
    return 2;
  } else if (0 == (static_cast<utf8_int32_t>(0xffff0000) & chr)) {
    return 3;
  } else {
    return 4;
  }
}

utf8_weak void *utf8catcodepoint(void *utf8_restrict str, utf8_int32_t chr, size_t n) {
  char *s = static_cast<char *>(str);

  if (0 == (static_cast<utf8_int32_t>(0xffffff80) & chr)) {
    if (n < 1) {
      return nullptr;
    }
    s[0] = static_cast<char>(chr);
    s += 1;
  } else if (0 == (static_cast<utf8_int32_t>(0xfffff800) & chr)) {
    if (n < 2) {
      return nullptr;
    }
    s[0] = 0xc0 | static_cast<char>(chr >> 6);
    s[1] = 0x80 | static_cast<char>(chr & 0x3f);
    s += 2;
  } else if (0 == (static_cast<utf8_int32_t>(0xffff0000) & chr)) {
    if (n < 3) {
      return nullptr;
    }
    s[0] = 0xe0 | static_cast<char>(chr >> 12);
    s[1] = 0x80 | static_cast<char>((chr >> 6) & 0x3f);
    s[2] = 0x80 | static_cast<char>(chr & 0x3f);
    s += 3;
  } else {
    if (n < 4) {
      return nullptr;
    }
    s[0] = 0xf0 | static_cast<char>(chr >> 18);
    s[1] = 0x80 | static_cast<char>((chr >> 12) & 0x3f);
    s[2] = 0x80 | static_cast<char>((chr >> 6) & 0x3f);
    s[3] = 0x80 | static_cast<char>(chr & 0x3f);
    s += 4;
  }

  return s;
}

int utf8islower(utf8_int32_t chr) { return !utf8isupper(chr); }

int utf8isupper(utf8_int32_t chr) { return ((0x41 <= chr) && (0x5a >= chr)); }

utf8_weak void utf8lwr(void *utf8_restrict str) {
  void *p, *pn;
  utf8_int32_t cp;

  p = str;
  pn = utf8codepoint(p, &cp);

  while (0 != cp) {
    if (utf8isupper(cp)) {
      cp |= 0x20;
      utf8catcodepoint(p, cp, 1);
    }

    p = pn;
    pn = utf8codepoint(p, &cp);
  }
}

utf8_weak void utf8upr(void *utf8_restrict str) {
  void *p, *pn;
  utf8_int32_t cp;

  p = str;
  pn = utf8codepoint(p, &cp);

  while (0 != cp) {
    if ((0x61 <= cp) && (0x7a >= cp)) {
      cp &= ~0x20;
      utf8catcodepoint(p, cp, 1);
    }

    p = pn;
    pn = utf8codepoint(p, &cp);
  }
}
}
