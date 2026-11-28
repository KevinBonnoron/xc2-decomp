// zutil.c of zlib 1.2.8 (see zlib.h for the provenance and the licence): target dependent utility functions for the compression
// library, followed by the Nintendo SDK's Libz_SigloMiddlewareInfo().

#include "zlib/zutil.h"

#include <stdlib.h>

#include "zlib/zlib.h"

namespace nn {
namespace util {
// Import of the SDK (_ZN2nn4util11ReferSymbolEPKv); the result type is not part of the mangled name.
void ReferSymbol(const void *symbol);
} // namespace util
} // namespace nn

const char *const z_errmsg[10] = {"need dictionary",      /* Z_NEED_DICT       2  */
                                  "stream end",           /* Z_STREAM_END      1  */
                                  "",                     /* Z_OK              0  */
                                  "file error",           /* Z_ERRNO         (-1) */
                                  "stream error",         /* Z_STREAM_ERROR  (-2) */
                                  "data error",           /* Z_DATA_ERROR    (-3) */
                                  "insufficient memory",  /* Z_MEM_ERROR     (-4) */
                                  "buffer error",         /* Z_BUF_ERROR     (-5) */
                                  "incompatible version", /* Z_VERSION_ERROR (-6) */
                                  ""};

const char *zlibVersion() { return ZLIB_VERSION; }

uLong zlibCompileFlags() {
  uLong flags;

  flags = 0;
  switch ((int)(sizeof(uInt))) {
  case 2:
    break;
  case 4:
    flags += 1;
    break;
  case 8:
    flags += 2;
    break;
  default:
    flags += 3;
  }
  switch ((int)(sizeof(uLong))) {
  case 2:
    break;
  case 4:
    flags += 1 << 2;
    break;
  case 8:
    flags += 2 << 2;
    break;
  default:
    flags += 3 << 2;
  }
  switch ((int)(sizeof(voidpf))) {
  case 2:
    break;
  case 4:
    flags += 1 << 4;
    break;
  case 8:
    flags += 2 << 4;
    break;
  default:
    flags += 3 << 4;
  }
  switch ((int)(sizeof(z_off_t))) {
  case 2:
    break;
  case 4:
    flags += 1 << 6;
    break;
  case 8:
    flags += 2 << 6;
    break;
  default:
    flags += 3 << 6;
  }
  return flags;
}

const char *zError(int err) { return ERR_MSG(err); }

voidpf zcalloc(voidpf opaque, unsigned items, unsigned size) {
  if (opaque)
    items += size - size; /* make compiler happy */
  return sizeof(uInt) > 2 ? (voidpf)malloc(items * size) : (voidpf)calloc(items, size);
}

void zcfree(voidpf opaque, voidpf ptr) {
  free(ptr);
  if (opaque)
    return; /* make compiler happy */
}

// Inferred role: the middleware information string of the Nintendo SDK's libz (game address 0x7101170004, in the rodata of the
// module, right after the build id note), the only thing Libz_SigloMiddlewareInfo() refers to; original name unknown.
static const char unknown001[] = "SDK MW+Nintendo+NintendoSDK_libz-3_5_0-Release";

void Libz_SigloMiddlewareInfo() { nn::util::ReferSymbol(unknown001); }
