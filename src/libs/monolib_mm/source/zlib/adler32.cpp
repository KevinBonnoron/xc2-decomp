// adler32.c of zlib 1.2.8 (see zlib.h for the provenance and the licence): compute the Adler-32 checksum of a data stream.

#include "zlib/zlib.h"

#define BASE 65521U /* largest prime smaller than 65536 */
#define NMAX 5552
/* NMAX is the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1 */

// clang-format off
#define DO1(buf,i)  {adler += (buf)[i]; sum2 += adler;}
#define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
#define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
#define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
#define DO16(buf)   DO8(buf,0); DO8(buf,8);
// clang-format on

#define MOD(a) a %= BASE
#define MOD28(a) a %= BASE
#define MOD63(a) a %= BASE

uLong adler32(uLong adler, const Bytef *buf, uInt len) {
  unsigned long sum2;
  unsigned n;

  /* split Adler-32 into component sums */
  sum2 = (adler >> 16) & 0xffff;
  adler &= 0xffff;

  /* in case user likes doing a byte at a time, keep it fast */
  if (len == 1) {
    adler += buf[0];
    if (adler >= BASE)
      adler -= BASE;
    sum2 += adler;
    if (sum2 >= BASE)
      sum2 -= BASE;
    return adler | (sum2 << 16);
  }

  /* initial Adler-32 value (deferred check for len == 1 speed) */
  if (buf == Z_NULL)
    return 1L;

  /* in case short lengths are provided, keep it somewhat fast */
  if (len < 16) {
    while (len--) {
      adler += *buf++;
      sum2 += adler;
    }
    if (adler >= BASE)
      adler -= BASE;
    MOD28(sum2); /* only added so many BASE's */
    return adler | (sum2 << 16);
  }

  /* do length NMAX blocks -- requires just one modulo operation */
  while (len >= NMAX) {
    len -= NMAX;
    n = NMAX / 16; /* NMAX is divisible by 16 */
    do {
      DO16(buf); /* 16 sums unrolled */
      buf += 16;
    } while (--n);
    MOD(adler);
    MOD(sum2);
  }

  /* do remaining bytes (less than NMAX, still just one modulo) */
  if (len) { /* avoid modulos if none remaining */
    while (len >= 16) {
      len -= 16;
      DO16(buf);
      buf += 16;
    }
    while (len--) {
      adler += *buf++;
      sum2 += adler;
    }
    MOD(adler);
    MOD(sum2);
  }

  /* return recombined sums */
  return adler | (sum2 << 16);
}

static uLong adler32_combine_(uLong adler1, uLong adler2, z_off64_t len2) {
  unsigned long sum1;
  unsigned long sum2;
  unsigned rem;

  /* for negative len, return invalid adler32 as a clue for debugging */
  if (len2 < 0)
    return 0xffffffffUL;

  /* the derivation of this formula is left as an exercise for the reader */
  MOD63(len2); /* assumes len2 >= 0 */
  rem = (unsigned)len2;
  sum1 = adler1 & 0xffff;
  sum2 = rem * sum1;
  MOD(sum2);
  sum1 += (adler2 & 0xffff) + BASE - 1;
  sum2 += ((adler1 >> 16) & 0xffff) + ((adler2 >> 16) & 0xffff) + BASE - rem;
  if (sum1 >= BASE)
    sum1 -= BASE;
  if (sum1 >= BASE)
    sum1 -= BASE;
  if (sum2 >= (BASE << 1))
    sum2 -= (BASE << 1);
  if (sum2 >= BASE)
    sum2 -= BASE;
  return sum1 | (sum2 << 16);
}

uLong adler32_combine(uLong adler1, uLong adler2, z_off_t len2) { return adler32_combine_(adler1, adler2, len2); }

uLong adler32_combine64(uLong adler1, uLong adler2, z_off64_t len2) { return adler32_combine_(adler1, adler2, len2); }
