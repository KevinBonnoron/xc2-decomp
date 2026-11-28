#pragma once
// Public declarations of the zlib that monolib_mm embeds. The game's binary names the library by two strings: zlibVersion()
// returns "1.2.8.f-NINTENDO-SDK-v1" (zlib 1.2.8 as modified by the Nintendo SDK) and the middleware information string is
// "SDK MW+Nintendo+NintendoSDK_libz-3_5_0-Release". The declarations below are the ones of zlib 1.2.8's zlib.h and zconf.h that
// the game's code uses, written for a 64-bit little-endian target (sizeof(uLong) == 8, sizeof(z_off_t) == 8, no Z_PREFIX).
//
// zlib is (C) 1995-2013 Jean-loup Gailly and Mark Adler, distributed under the zlib licence:
//
//   This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for
//   any damages arising from the use of this software.
//
//   Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and
//   redistribute it freely, subject to the following restrictions:
//
//   1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use
//      this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
//   2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
//   3. This notice may not be removed or altered from any source distribution.

#define ZLIB_VERSION "1.2.8.f-NINTENDO-SDK-v1"

typedef unsigned char Byte;
typedef unsigned int uInt;
typedef unsigned long uLong;
typedef Byte Bytef;
typedef void *voidpf;
typedef long z_off_t;
typedef long z_off64_t;
typedef unsigned int z_crc_t;

typedef voidpf (*alloc_func)(voidpf opaque, uInt items, uInt size);
typedef void (*free_func)(voidpf opaque, voidpf address);

typedef struct z_stream_s {
  const Bytef *next_in;         /* next input byte */
  uInt avail_in;                /* number of bytes available at next_in */
  uLong total_in;               /* total number of input bytes read so far */
  Bytef *next_out;              /* next output byte should be put there */
  uInt avail_out;               /* remaining free space at next_out */
  uLong total_out;              /* total number of bytes output so far */
  const char *msg;              /* last error message, NULL if no error */
  struct internal_state *state; /* not visible by applications */
  alloc_func zalloc;            /* used to allocate the internal state */
  free_func zfree;              /* used to free the internal state */
  voidpf opaque;                /* private data object passed to zalloc and zfree */
  int data_type;                /* best guess about the data type: binary or text */
  uLong adler;                  /* adler32 value of the uncompressed data */
  uLong reserved;               /* reserved for future use */
} z_stream;

typedef z_stream *z_streamp;

/* gzip header information passed to and from zlib routines. */
typedef struct gz_header_s {
  int text;       /* true if compressed data believed to be text */
  uLong time;     /* modification time */
  int xflags;     /* extra flags (not used when writing a gzip file) */
  int os;         /* operating system */
  Bytef *extra;   /* pointer to extra field or Z_NULL if none */
  uInt extra_len; /* extra field length (valid if extra != Z_NULL) */
  uInt extra_max; /* space at extra (only when reading header) */
  Bytef *name;    /* pointer to zero-terminated file name or Z_NULL */
  uInt name_max;  /* space at name (only when reading header) */
  Bytef *comment; /* pointer to zero-terminated comment or Z_NULL */
  uInt comm_max;  /* space at comment (only when reading header) */
  int hcrc;       /* true if there was or will be a header crc */
  int done;       /* true when done reading gzip header (not used when writing a gzip file) */
} gz_header;

typedef gz_header *gz_headerp;

#define Z_NO_FLUSH 0
#define Z_PARTIAL_FLUSH 1
#define Z_SYNC_FLUSH 2
#define Z_FULL_FLUSH 3
#define Z_FINISH 4
#define Z_BLOCK 5
#define Z_TREES 6

#define Z_OK 0
#define Z_STREAM_END 1
#define Z_NEED_DICT 2
#define Z_ERRNO (-1)
#define Z_STREAM_ERROR (-2)
#define Z_DATA_ERROR (-3)
#define Z_MEM_ERROR (-4)
#define Z_BUF_ERROR (-5)
#define Z_VERSION_ERROR (-6)

#define Z_DEFLATED 8

#define Z_NULL 0

extern "C" {
const char *zlibVersion();
int inflateInit_(z_streamp strm, const char *version, int stream_size);
int inflate(z_streamp strm, int flush);
int inflateEnd(z_streamp strm);
int inflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength);
int inflateGetDictionary(z_streamp strm, Bytef *dictionary, uInt *dictLength);
int inflateSync(z_streamp strm);
int inflateCopy(z_streamp dest, z_streamp source);
int inflateReset(z_streamp strm);
int inflateReset2(z_streamp strm, int windowBits);
int inflatePrime(z_streamp strm, int bits, int value);
long inflateMark(z_streamp strm);
int inflateGetHeader(z_streamp strm, gz_headerp head);
uLong adler32(uLong adler, const Bytef *buf, uInt len);
uLong adler32_combine(uLong adler1, uLong adler2, z_off_t len2);
uLong crc32(uLong crc, const Bytef *buf, uInt len);
uLong crc32_combine(uLong crc1, uLong crc2, z_off_t len2);
int inflateInit2_(z_streamp strm, int windowBits, const char *version, int stream_size);
int inflateUndermine(z_streamp strm, int subvert);
int inflateResetKeep(z_streamp strm);
int inflateSyncPoint(z_streamp strm);
const z_crc_t *get_crc_table();
uLong zlibCompileFlags();
const char *zError(int err);
uLong adler32_combine64(uLong adler1, uLong adler2, z_off64_t len2);
uLong crc32_combine64(uLong crc1, uLong crc2, z_off64_t len2);
}
