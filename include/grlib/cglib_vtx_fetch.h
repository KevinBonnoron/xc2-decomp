#pragma once
#include <stddef.h>

#include "types.h"

struct NVNvertexAttribState;

enum GrlVtxFormat {
  GRL_VTX_FORMAT_R32F = 10,
  GRL_VTX_FORMAT_R32UI = 11,
  GRL_VTX_FORMAT_UNKNOWN_13 = 13,
  GRL_VTX_FORMAT_RG16F = 17,
  GRL_VTX_FORMAT_RG16SN = 19,
  GRL_VTX_FORMAT_RG16UI = 20,
  GRL_VTX_FORMAT_RG32F = 22,
  GRL_VTX_FORMAT_RGB32F = 34,
  GRL_VTX_FORMAT_RGBA8 = 37,
  GRL_VTX_FORMAT_RGBA8SN = 38,
  GRL_VTX_FORMAT_RGBA8UI = 39,
  GRL_VTX_FORMAT_RGBA16 = 42,
  GRL_VTX_FORMAT_RGBA16SN = 43,
  GRL_VTX_FORMAT_RGBA16I = 45,
  GRL_VTX_FORMAT_RGBA32F = 46,
  GRL_VTX_FORMAT_RGBA32UI = 47,
};

namespace grlib {

struct CGLibVtxAttr {
  GrlVtxFormat unknown00; // Inferred role: format; original member name unknown.
  u32 unknown04;          // Inferred role: location; original member name unknown.
  u32 unknown08;          // Inferred role: offset; original member name unknown.
  u32 unknown0c;          // Inferred role: buffer index; original member name unknown.
};

class CGLibVtxFetch {
public:
  CGLibVtxFetch();
  ~CGLibVtxFetch();
  void release();
  void createFetchObj(CGLibVtxAttr *attributes, int num);
  void createMemFetchObj(void *memory, CGLibVtxAttr *attributes, int num);
  static int calcFetchWorkSize(int num);

  NVNvertexAttribState *unknown00; // Inferred role: attribute states; original member name unknown.
  u16 unknown08;                   // Inferred role: attribute num; original member name unknown.
  u16 unknown0a;                   // Inferred role: owns attribute states; original member name unknown.
  u8 _0c[0x10 - 0x0c];
};

static_assert(offsetof(CGLibVtxFetch, unknown0a) == 0x0a, "");

} // namespace grlib
