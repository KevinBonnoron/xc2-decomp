#pragma once
// zutil.h of zlib 1.2.8 (see zlib.h for the provenance and the licence): internal declarations shared by the files of the library.
#include "zlib/zlib.h"

#define ZALLOC(strm, items, size) (*((strm)->zalloc))((strm)->opaque, (items), (size))
#define ZFREE(strm, addr) (*((strm)->zfree))((strm)->opaque, (voidpf)(addr))

#define ERR_MSG(err) z_errmsg[Z_NEED_DICT - (err)]

/* Reverse the bytes in a 32-bit value */
#define ZSWAP32(q) ((((q) >> 24) & 0xff) + (((q) >> 8) & 0xff00) + (((q) & 0xff00) << 8) + (((q) & 0xff) << 24))

extern "C" {
extern const char *const z_errmsg[10];
extern const char inflate_copyright[];

voidpf zcalloc(voidpf opaque, unsigned items, unsigned size);
void zcfree(voidpf opaque, voidpf ptr);

// Added by the Nintendo SDK: inflate() calls it first, it keeps the middleware information string linked into the program.
void Libz_SigloMiddlewareInfo();
}
