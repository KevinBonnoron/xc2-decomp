// crc32.c of zlib 1.2.8 (see zlib.h for the provenance and the licence): compute the CRC-32 of a data stream. The game builds it
// with BYFOUR (the tables are the precomputed ones of crc32.h, DYNAMIC_CRC_TABLE is not defined).

#include "zlib/crc32.h"

#include <stddef.h>

#include "zlib/zlib.h"
#include "zlib/zutil.h"

const z_crc_t *get_crc_table() { return (const z_crc_t *)crc_table; }

// clang-format off
#define DO1 crc = crc_table[0][((int)crc ^ (*buf++)) & 0xff] ^ (crc >> 8)
#define DO8 DO1; DO1; DO1; DO1; DO1; DO1; DO1; DO1
// clang-format on

static unsigned long crc32_little(unsigned long crc, const unsigned char *buf, unsigned len);
static unsigned long crc32_big(unsigned long crc, const unsigned char *buf, unsigned len);

uLong crc32(uLong crc, const Bytef *buf, uInt len) {
  if (buf == Z_NULL)
    return 0UL;

  if (sizeof(void *) == sizeof(ptrdiff_t)) {
    z_crc_t endian;

    endian = 1;
    if (*((unsigned char *)(&endian)))
      return crc32_little(crc, buf, len);
    else
      return crc32_big(crc, buf, len);
  }
  crc = crc ^ 0xffffffffUL;
  while (len >= 8) {
    DO8;
    len -= 8;
  }
  if (len)
    do {
      DO1;
    } while (--len);
  return crc ^ 0xffffffffUL;
}

/* This BYFOUR code accesses the passed unsigned char * buffer with a 32-bit integer pointer type. This violates the strict
   aliasing rule, where a compiler can assume, for optimization purposes, that two pointers to fundamentally different types
   won't ever point to the same memory.  This can manifest as a problem only if one of the pointers is written to. This code only
   reads from those pointers.  So long as this code remains isolated in this compilation unit, there won't be a problem. */
// clang-format off
#define DOLIT4 c ^= *buf4++; \
        c = crc_table[3][c & 0xff] ^ crc_table[2][(c >> 8) & 0xff] ^ \
            crc_table[1][(c >> 16) & 0xff] ^ crc_table[0][c >> 24]
#define DOLIT32 DOLIT4; DOLIT4; DOLIT4; DOLIT4; DOLIT4; DOLIT4; DOLIT4; DOLIT4
// clang-format on

static unsigned long crc32_little(unsigned long crc, const unsigned char *buf, unsigned len) {
  z_crc_t c;
  const z_crc_t *buf4;

  c = (z_crc_t)crc;
  c = ~c;
  while (len && ((ptrdiff_t)buf & 3)) {
    c = crc_table[0][(c ^ *buf++) & 0xff] ^ (c >> 8);
    len--;
  }

  buf4 = (const z_crc_t *)(const void *)buf;
  while (len >= 32) {
    DOLIT32;
    len -= 32;
  }
  while (len >= 4) {
    DOLIT4;
    len -= 4;
  }
  buf = (const unsigned char *)buf4;

  if (len)
    do {
      c = crc_table[0][(c ^ *buf++) & 0xff] ^ (c >> 8);
    } while (--len);
  c = ~c;
  return (unsigned long)c;
}

// clang-format off
#define DOBIG4 c ^= *++buf4; \
        c = crc_table[4][c & 0xff] ^ crc_table[5][(c >> 8) & 0xff] ^ \
            crc_table[6][(c >> 16) & 0xff] ^ crc_table[7][c >> 24]
#define DOBIG32 DOBIG4; DOBIG4; DOBIG4; DOBIG4; DOBIG4; DOBIG4; DOBIG4; DOBIG4
// clang-format on

static unsigned long crc32_big(unsigned long crc, const unsigned char *buf, unsigned len) {
  z_crc_t c;
  const z_crc_t *buf4;

  c = ZSWAP32((z_crc_t)crc);
  c = ~c;
  while (len && ((ptrdiff_t)buf & 3)) {
    c = crc_table[4][(c >> 24) ^ *buf++] ^ (c << 8);
    len--;
  }

  buf4 = (const z_crc_t *)(const void *)buf;
  buf4--;
  while (len >= 32) {
    DOBIG32;
    len -= 32;
  }
  while (len >= 4) {
    DOBIG4;
    len -= 4;
  }
  buf4++;
  buf = (const unsigned char *)buf4;

  if (len)
    do {
      c = crc_table[4][(c >> 24) ^ *buf++] ^ (c << 8);
    } while (--len);
  c = ~c;
  return (unsigned long)(ZSWAP32(c));
}

#define GF2_DIM 32 /* dimension of GF(2) vectors (length of CRC) */

static unsigned long gf2_matrix_times(unsigned long *mat, unsigned long vec) {
  unsigned long sum;

  sum = 0;
  while (vec) {
    if (vec & 1)
      sum ^= *mat;
    vec >>= 1;
    mat++;
  }
  return sum;
}

static void gf2_matrix_square(unsigned long *square, unsigned long *mat) {
  int n;

  for (n = 0; n < GF2_DIM; n++)
    square[n] = gf2_matrix_times(mat, mat[n]);
}

static uLong crc32_combine_(uLong crc1, uLong crc2, z_off64_t len2) {
  int n;
  unsigned long row;
  unsigned long even[GF2_DIM]; /* even-power-of-two zeros operator */
  unsigned long odd[GF2_DIM];  /* odd-power-of-two zeros operator */

  /* degenerate case (also disallow negative lengths) */
  if (len2 <= 0)
    return crc1;

  /* put operator for one zero bit in odd */
  odd[0] = 0xedb88320UL; /* CRC-32 polynomial */
  row = 1;
  for (n = 1; n < GF2_DIM; n++) {
    odd[n] = row;
    row <<= 1;
  }

  /* put operator for two zero bits in even */
  gf2_matrix_square(even, odd);

  /* put operator for four zero bits in odd */
  gf2_matrix_square(odd, even);

  /* apply len2 zeros to crc1 (first square will put the operator for one zero byte, eight zero bits, in even) */
  do {
    /* apply zeros operator for this bit of len2 */
    gf2_matrix_square(even, odd);
    if (len2 & 1)
      crc1 = gf2_matrix_times(even, crc1);
    len2 >>= 1;

    /* if no more bits set, then done */
    if (len2 == 0)
      break;

    /* another iteration of the loop with odd and even swapped */
    gf2_matrix_square(odd, even);
    if (len2 & 1)
      crc1 = gf2_matrix_times(odd, crc1);
    len2 >>= 1;

    /* if no more bits set, then done */
  } while (len2 != 0);

  /* return combined crc */
  crc1 ^= crc2;
  return crc1;
}

uLong crc32_combine(uLong crc1, uLong crc2, z_off_t len2) { return crc32_combine_(crc1, crc2, len2); }

uLong crc32_combine64(uLong crc1, uLong crc2, z_off64_t len2) { return crc32_combine_(crc1, crc2, len2); }
